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
  auto borderType  = borderTypeFromString(stepDetails->parameterValue<std::string>(borderTypeSID()));
  auto outputDepth = depthFromString(stepDetails->parameterValue<std::string>(outputDepthSID()));
  double delta = stepDetails->parameterValue<double>(deltaSID());

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
    cv::Point anchor = cv::Point( -1, -1 );
    cv::filter2D(src, dst, outputDepth, kernel, anchor, delta, borderType);
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
    const auto& name = tp_pipeline_image_utils::kernelSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The filter kernel.";
    param.type = tp_pipeline::convolutionMatrixSID();

    param.value = tp_image_utils_functions::ConvolutionMatrix(tpGetVariantValue<std::string>(param.value)).toString();

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const tp_utils::StringID& name = borderTypeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The border type to use.";
    param.setEnum(borderTypes());

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const tp_utils::StringID& name = outputDepthSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The depth of the output image.";
    param.setEnum(depths());

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
