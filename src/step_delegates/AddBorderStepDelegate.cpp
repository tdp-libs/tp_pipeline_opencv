#include "tp_pipeline_opencv/step_delegates/AddBorderStepDelegate.h"
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
AddBorderStepDelegate::AddBorderStepDelegate():
  tp_pipeline::AbstractStepDelegate(addBorderSID(), {opencvSID()})
{

}

//##################################################################################################
void AddBorderStepDelegate::executeStep(tp_pipeline::StepDetails* stepDetails,
                                       const tp_pipeline::StepInput& input,
                                       tp_data::Collection& output) const
{
  auto borderType  = borderTypeFromString(stepDetails->parameterValue<std::string>(borderTypeSID()));
  TPPixel color(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::colorSID()));

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
    cv::Scalar value(color.r, color.g, color.b, 255);

    int top    = stepDetails->parameterValue<int>(   topSID());
    int right  = stepDetails->parameterValue<int>( rightSID());
    int bottom = stepDetails->parameterValue<int>(bottomSID());
    int left   = stepDetails->parameterValue<int>(  leftSID());
    cv::copyMakeBorder(src, dst, top, bottom, left, right, borderType, value);
  }
  catch(cv::Exception& e)
  {
    output.addError(e.what());
    return;
  }

  auto out = new tp_data_opencv::CVMatMember(stepDetails->lookupOutputName("Output data"));
  out->data = dst;
  output.addMember(out);
}

//##################################################################################################
void AddBorderStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
{
  stepDetails->setOutputNames({"Output data"});

  std::vector<tp_utils::StringID> validParams;
  const auto& parameters = stepDetails->parameters();

  {
    const tp_utils::StringID& name = borderTypeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The border type to use.";
    param.setEnum(borderTypes());

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  auto borderType  = borderTypeFromString(stepDetails->parameterValue<std::string>(borderTypeSID()));

  {
    tp_utils::StringID name = tp_pipeline_image_utils::colorSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The color to fill the border with.";
    param.type = tp_pipeline_image_utils::colorSID();

    tp_pipeline_image_utils::validateColor(param, TPPixel("#000000"));

    param.enabled = borderType == cv::BorderTypes::BORDER_CONSTANT;

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }


  auto borderWidth = [&](const tp_utils::StringID& name)
  {
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The " + name.keyString() + " border width.";
    param.type = tp_pipeline::intSID();
    param.min = 0;
    param.max = INT_MAX;
    param.validateBounds(5);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  };

  borderWidth(   topSID());
  borderWidth( rightSID());
  borderWidth(bottomSID());
  borderWidth(  leftSID());

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
