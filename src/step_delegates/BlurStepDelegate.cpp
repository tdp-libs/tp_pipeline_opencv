#include "tp_pipeline_opencv/step_delegates/BlurStepDelegate.h"

#include "tp_data_opencv/members/CVMatMember.h"

#include "tp_pipeline_image_utils/Globals.h"

#include "tp_pipeline/StepDetails.h"
#include "tp_pipeline/StepInput.h"

#include "tp_data/Collection.h"

#include <opencv2/imgproc.hpp>

namespace tp_pipeline_opencv
{

namespace
{

//##################################################################################################
enum class Mode_lt
{
  Blur,
  GaussianBlur,
  MedianBlur,
  BilateralFilter,
  BoxFilter,
  SqrBoxFilter
};

//##################################################################################################
const std::vector<std::string>& modes()
{
  static const std::vector<std::string> modes
  {
    "Blur",
    "GaussianBlur",
    "MedianBlur",
    "BilateralFilter",
    "BoxFilter",
    "SqrBoxFilter"
  };

  return modes;
}

//##################################################################################################
Mode_lt modeFromString(const std::string& modeString)
{
  if(modeString == "Blur")
    return Mode_lt::Blur;

  if(modeString == "GaussianBlur")
    return Mode_lt::GaussianBlur;

  if(modeString == "MedianBlur")
    return Mode_lt::MedianBlur;

  if(modeString == "BilateralFilter")
    return Mode_lt::BilateralFilter;

  if(modeString == "BoxFilter")
    return Mode_lt::BoxFilter;

  if(modeString == "SqrBoxFilter")
    return Mode_lt::SqrBoxFilter;

  return Mode_lt::Blur;
}

//##################################################################################################
const std::vector<std::string>& borderTypes()
{
  static const std::vector<std::string> borderTypes
  {
    "BORDER_CONSTANT",
    "BORDER_REPLICATE",
    "BORDER_REFLECT",
    "BORDER_WRAP",
    "BORDER_REFLECT_101",
    "BORDER_TRANSPARENT",
    "BORDER_REFLECT101",
    "BORDER_DEFAULT",
    "BORDER_ISOLATED"
  };

  return borderTypes;
}

//##################################################################################################
cv::BorderTypes borderTypeFromString(const std::string& borderTypeString)
{
  if(borderTypeString == "BORDER_CONSTANT")
    return cv::BorderTypes::BORDER_CONSTANT;

  if(borderTypeString == "BORDER_REPLICATE")
    return cv::BorderTypes::BORDER_REPLICATE;

  if(borderTypeString == "BORDER_REFLECT")
    return cv::BorderTypes::BORDER_REFLECT;

  if(borderTypeString == "BORDER_WRAP")
    return cv::BorderTypes::BORDER_WRAP;

  if(borderTypeString == "BORDER_REFLECT_101")
    return cv::BorderTypes::BORDER_REFLECT_101;

  if(borderTypeString == "BORDER_TRANSPARENT")
    return cv::BorderTypes::BORDER_TRANSPARENT;

  if(borderTypeString == "BORDER_REFLECT101")
    return cv::BorderTypes::BORDER_REFLECT101;

  if(borderTypeString == "BORDER_DEFAULT")
    return cv::BorderTypes::BORDER_DEFAULT;

  if(borderTypeString == "BORDER_ISOLATED")
    return cv::BorderTypes::BORDER_ISOLATED;

  return cv::BorderTypes::BORDER_DEFAULT;
}

}

//##################################################################################################
BlurStepDelegate::BlurStepDelegate():
  tp_pipeline::AbstractStepDelegate(blurSID(), {opencvSID()})
{

}

//##################################################################################################
void BlurStepDelegate::executeStep(tp_pipeline::StepDetails* stepDetails,
                                   const tp_pipeline::StepInput& input,
                                   tp_data::Collection& output) const
{
  auto mode = modeFromString(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::modeSID()));
  auto borderType = borderTypeFromString(stepDetails->parameterValue<std::string>(borderTypeSID()));

  int kernelW = stepDetails->parameterValue<int>( kernelWidthSID());
  int kernelH = stepDetails->parameterValue<int>(kernelHeightSID());
  int ksize   = stepDetails->parameterValue<int>(  kernelSizeSID());
  int diameter=1;
  int ddepth = -1;

  bool normalize = true;

  double sigmaX = stepDetails->parameterValue<double>(sigmaXSID());
  double sigmaY = stepDetails->parameterValue<double>(sigmaYSID());

  double sigmaColor = stepDetails->parameterValue<double>(sigmaColorSID());
  double sigmaSpace = stepDetails->parameterValue<double>(sigmaSpaceSID());

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
    case Mode_lt::Blur:
      cv::blur(src, dst, cv::Size(kernelW, kernelH), cv::Point(-1,-1), borderType);
      break;

    case Mode_lt::GaussianBlur:
      cv::GaussianBlur(src, dst, cv::Size(kernelW, kernelH), sigmaX, sigmaY, borderType);
      break;

    case Mode_lt::MedianBlur:
      cv::medianBlur(src, dst, ksize);
      break;

    case Mode_lt::BilateralFilter:
      cv::bilateralFilter(src, dst, diameter, sigmaColor, sigmaSpace, borderType);
      break;

    case Mode_lt::BoxFilter:
      cv::boxFilter(src, dst, ddepth, cv::Size(kernelW, kernelH), cv::Point(-1,-1), normalize, borderType);
      break;

    case Mode_lt::SqrBoxFilter:
      cv::sqrBoxFilter(src, dst, ddepth,cv::Size(kernelW, kernelH), cv::Point(-1,-1), normalize, borderType);
      break;
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
void BlurStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
{
  stepDetails->setOutputNames({"Output data"});

  std::vector<tp_utils::StringID> validParams;
  const auto& parameters = stepDetails->parameters();

  {
    const tp_utils::StringID& name = tp_pipeline_image_utils::modeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The type of blur to perform.";
    param.setEnum(modes());

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  auto mode = modeFromString(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::modeSID()));

  {
    const tp_utils::StringID& name = borderTypeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The border type to use.";
    param.setEnum(borderTypes());

    param.enabled = (mode==Mode_lt::Blur           ||
                     mode==Mode_lt::GaussianBlur   ||
                     mode==Mode_lt::BilateralFilter||
                     mode==Mode_lt::BoxFilter      ||
                     mode==Mode_lt::SqrBoxFilter);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = kernelWidthSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The kernel width.";
    param.type = tp_pipeline::intSID();
    param.min = 1;
    param.max = 31;
    param.validateBounds(1);

    param.enabled = (mode==Mode_lt::Blur           ||
                     mode==Mode_lt::GaussianBlur   ||
                     mode==Mode_lt::BoxFilter      ||
                     mode==Mode_lt::SqrBoxFilter);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = kernelHeightSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The kernel height.";
    param.type = tp_pipeline::intSID();
    param.min = 1;
    param.max = 31;
    param.validateBounds(1);

    param.enabled = (mode==Mode_lt::Blur           ||
                     mode==Mode_lt::GaussianBlur   ||
                     mode==Mode_lt::BoxFilter      ||
                     mode==Mode_lt::SqrBoxFilter);

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
    param.validateBounds(1);

    param.enabled = (mode==Mode_lt::MedianBlur);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = diameterSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The diameter of the pixel neighborhood that is used during filtering.";
    param.type = tp_pipeline::intSID();
    param.min = 1;
    param.max = 31;
    param.validateBounds(1);

    param.enabled = (mode==Mode_lt::BilateralFilter);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  //  int ddepth = -1;

  //  bool normalize = true;

  {
    tp_utils::StringID name = sigmaXSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Sigma x.";
    param.type = tp_pipeline::doubleSID();
    param.min = 0.0;
    param.max = 1.0;
    param.validateBounds<double>(0.0);

    param.enabled = (mode==Mode_lt::GaussianBlur);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = sigmaYSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Sigma y.";
    param.type = tp_pipeline::doubleSID();
    param.min = 0.0;
    param.max = 1.0;
    param.validateBounds<double>(0.0);

    param.enabled = (mode==Mode_lt::GaussianBlur);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = sigmaColorSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Sigma color.";
    param.type = tp_pipeline::doubleSID();
    param.min = 0.0;
    param.max = 255.0;
    param.validateBounds<double>(2.0);

    param.enabled = (mode==Mode_lt::BilateralFilter);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = sigmaSpaceSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Sigma space.";
    param.type = tp_pipeline::doubleSID();
    param.min = 0.0;
    param.max = 255.0;
    param.validateBounds<double>(2.0);

    param.enabled = (mode==Mode_lt::BilateralFilter);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const auto& name = tp_pipeline_image_utils::colorImageSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The input image.";
    param.type = tp_pipeline::namedDataSID();

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  stepDetails->setParametersOrder(validParams);
  stepDetails->setValidParameters(validParams);
}

}
