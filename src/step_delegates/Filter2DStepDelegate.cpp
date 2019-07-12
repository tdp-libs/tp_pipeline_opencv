#include "tp_pipeline_opencv/step_delegates/Filter2DStepDelegate.h"
#include "tp_pipeline_opencv/Enums.h"

#include "tp_data_opencv/ImageConversion.h"
#include "tp_data_opencv/members/CVMatMember.h"

#include "tp_pipeline_image_utils/Globals.h"

#include "tp_image_utils_functions/ConvolutionMatrix.h"

#include "tp_pipeline/StepDetails.h"
#include "tp_pipeline/StepInput.h"

#include "tp_data/Collection.h"

#include "tp_utils/DebugUtils.h"

#include <opencv2/imgproc.hpp>

namespace tp_pipeline_opencv
{

namespace
{
//##################################################################################################
enum class Mode_lt
{
  Custom,
  Sobel,
  Laplace,
  Canny
};

//##################################################################################################
const std::vector<std::string>& modes()
{
  static const std::vector<std::string> modes
  {
    "Custom",
    "Sobel",
    "Laplace",
    "Canny"
  };

  return modes;
}

//##################################################################################################
Mode_lt modeFromString(const std::string& modeString)
{
  if(modeString == "Custom")
    return Mode_lt::Custom;

  if(modeString == "Sobel")
    return Mode_lt::Sobel;

  if(modeString == "Laplace")
    return Mode_lt::Laplace;

  if(modeString == "Canny")
    return Mode_lt::Canny;

  return Mode_lt::Custom;
}
}

//##################################################################################################
Filter2DStepDelegate::Filter2DStepDelegate():
  tp_pipeline::AbstractStepDelegate(filter2dSID(), {opencvSID()})
{

}

//##################################################################################################
void Filter2DStepDelegate::executeStep(tp_pipeline::StepDetails* stepDetails,
                                       const tp_pipeline::StepInput& input,
                                       tp_data::Collection& output) const
{
  auto mode = modeFromString(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::modeSID()));
  auto borderType  = borderTypeFromString(stepDetails->parameterValue<std::string>(borderTypeSID()));
  auto outputDepth = depthFromString(stepDetails->parameterValue<std::string>(outputDepthSID()));
  double delta = stepDetails->parameterValue<double>(deltaSID());
  double scale     = stepDetails->parameterValue<double>(tp_pipeline_image_utils::scaleSID());
  int dx           = stepDetails->parameterValue<int>(deltaXSID());
  int dy           = stepDetails->parameterValue<int>(deltaYSID());
  int ksize        = stepDetails->parameterValue<int>(kernelSizeSID());

  double  lowThreshold = stepDetails->parameterValue<double>( lowThresholdSID());
  double highThreshold = stepDetails->parameterValue<double>(highThresholdSID());

  cv::Mat kernel;
  tp_image_utils_functions::ConvolutionMatrix matrix(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::kernelSID()));
  tp_data_opencv::convertConvolutionMatrix(matrix, kernel);

  tp_data_opencv::CVMatMember* in{nullptr};
  input.memberCast(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::colorImageSID()), in);
  if(!in)
  {
    output.addError("Failed to find input cv::Mat data.");
    return;
  }

  const cv::Mat& src = in->data;
  cv::Mat dst;

  try
  {
    switch(mode)
    {
    case Mode_lt::Custom:
    {
      cv::Point anchor = cv::Point( -1, -1 );
      cv::filter2D(src, dst, outputDepth, kernel, anchor, delta, borderType);
      break;
    }

    case Mode_lt::Sobel:
    {
      cv::Sobel(src, dst, outputDepth, dx, dy, ksize, scale, delta, borderType);
      break;
    }

    case Mode_lt::Laplace:
    {
      cv::Laplacian(src, dst, outputDepth, ksize, scale, delta, borderType);
      break;
    }

    case Mode_lt::Canny:
    {
      cv::Canny(src, dst, lowThreshold, highThreshold, ksize);
      break;
    }
    }

  }
  catch( cv::Exception& e )
  {
    output.addError(e.what());
    return;
  }

  auto out = new tp_data_opencv::CVMatMember(stepDetails->lookupOutputName("Output data"));
  out->data = dst;
  output.addMember(out);
}

//##################################################################################################
void Filter2DStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
{
  stepDetails->setOutputNames({"Output data"});

  std::vector<tp_utils::StringID> validParams;
  const auto& parameters = stepDetails->parameters();

  {
    const tp_utils::StringID& name = tp_pipeline_image_utils::modeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Mode.";
    param.setEnum(modes());

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  auto mode = modeFromString(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::modeSID()));

  {
    const auto& name = tp_pipeline_image_utils::kernelSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The filter kernel.";
    param.type = tp_pipeline::convolutionMatrixSID();

    param.value = tp_image_utils_functions::ConvolutionMatrix(tpGetVariantValue<std::string>(param.value)).toString();

    param.enabled = (mode == Mode_lt::Custom);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const tp_utils::StringID& name = borderTypeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The border type to use.";
    param.setEnum(borderTypes());

    param.enabled = (mode == Mode_lt::Custom || mode == Mode_lt::Sobel || mode == Mode_lt::Laplace);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const tp_utils::StringID& name = outputDepthSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The depth of the output image.";
    param.setEnum(depths());

    param.enabled = (mode == Mode_lt::Custom || mode == Mode_lt::Sobel || mode == Mode_lt::Laplace);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = deltaSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Delta.";
    param.type = tp_pipeline::doubleSID();
    param.min = -DBL_MAX;
    param.max =  DBL_MAX;
    param.validateBounds<double>(0.0);    

    param.enabled = (mode == Mode_lt::Custom || mode == Mode_lt::Sobel || mode == Mode_lt::Laplace);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = tp_pipeline_image_utils::scaleSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Scale.";
    param.type = tp_pipeline::doubleSID();
    param.min = 1.0;
    param.max = 1000.0;
    param.validateBounds<double>(1.0);

    param.enabled = (mode == Mode_lt::Sobel || mode == Mode_lt::Laplace);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = deltaXSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Delta x.";
    param.type = tp_pipeline::intSID();
    param.min = -31;
    param.max = 31;
    param.validateBounds(1);

    param.enabled = (mode == Mode_lt::Sobel);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = deltaYSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Delta y.";
    param.type = tp_pipeline::intSID();
    param.min = -31;
    param.max = 31;
    param.validateBounds(1);

    param.enabled = (mode == Mode_lt::Sobel);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = kernelSizeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The kernel size.";
    param.type = tp_pipeline::intSID();
    param.min = 1;
    param.max = 31;
    param.validateBounds(3);

    param.enabled = (mode == Mode_lt::Sobel || mode == Mode_lt::Laplace || mode == Mode_lt::Canny);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = lowThresholdSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Low canny threshold..";
    param.type = tp_pipeline::doubleSID();
    param.min = 0.0;
    param.max = 10000.0;
    param.validateBounds<double>(0.0);

    param.enabled = (mode == Mode_lt::Canny);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = highThresholdSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "High canny threshold..";
    param.type = tp_pipeline::doubleSID();
    param.min = 0.0;
    param.max = 30000.0;
    param.validateBounds<double>(0.0);

    param.enabled = (mode == Mode_lt::Canny);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const auto& name = tp_pipeline_image_utils::colorImageSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The input image.";
    param.setNamedData();

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  stepDetails->setParametersOrder(validParams);
  stepDetails->setValidParameters(validParams);
}

}
