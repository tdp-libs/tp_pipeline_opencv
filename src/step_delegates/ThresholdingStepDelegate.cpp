#include "tp_pipeline_opencv/step_delegates/ThresholdingStepDelegate.h"
#include "tp_pipeline_opencv/Enums.h"

#include "tp_data_opencv/members/CVMatMember.h"

#include "tp_pipeline_image_utils/Globals.h"

#include "tp_image_utils_functions/ConvolutionMatrix.h"

#include "tp_pipeline/StepDetails.h"
#include "tp_pipeline/StepInput.h"

#include "tp_data/Collection.h"

#include <opencv2/imgproc.hpp>

namespace tp_pipeline_opencv
{

namespace
{
enum class Mode_lt
{
  Basic,
  InRange
};

//##################################################################################################
Mode_lt modeFromString(const std::string& modeString)
{
  if(modeString == "Basic")
    return Mode_lt::Basic;

  if(modeString == "In range")
    return Mode_lt::InRange;

  return Mode_lt::Basic;
}

//##################################################################################################
const std::vector<std::string>& modes()
{
  static const std::vector<std::string> modes
  {
    "Basic",
    "In range"
  };

  return modes;
}
}

//##################################################################################################
ThresholdingStepDelegate::ThresholdingStepDelegate():
  tp_pipeline::AbstractStepDelegate(thresholdingSID(), {opencvSID()})
{

}

//##################################################################################################
void ThresholdingStepDelegate::executeStep(tp_pipeline::StepDetails* stepDetails,
                                           const tp_pipeline::StepInput& input,
                                           tp_data::Collection& output) const
{
  auto mode = modeFromString(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::modeSID()));

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
    if(mode == Mode_lt::Basic)
    {
      double thresh = stepDetails->parameterValue<double>(threshSID());
      double maxval = stepDetails->parameterValue<double>(maxvalSID());
      auto type = thresholdTypeFromString(stepDetails->parameterValue<std::string>(thresholdTypeSID()));
      cv::threshold(src, dst, thresh, maxval, type);
    }
    else
    {
      int ch1Low  = stepDetails->parameterValue<int>(channel1LowSID());
      int ch2Low  = stepDetails->parameterValue<int>(channel2LowSID());
      int ch3Low  = stepDetails->parameterValue<int>(channel3LowSID());
      int ch1High = stepDetails->parameterValue<int>(channel1HighSID());
      int ch2High = stepDetails->parameterValue<int>(channel2HighSID());
      int ch3High = stepDetails->parameterValue<int>(channel3HighSID());
      cv::inRange(src,
                  cv::Scalar(ch1Low, ch2Low, ch3Low, 0),
                  cv::Scalar(ch1High, ch2High, ch3High, 255),
                  dst);
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
void ThresholdingStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
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
    const tp_utils::StringID& name = thresholdTypeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Threshold type.";
    param.setEnum(thresholdTypes());

    param.enabled = (mode == Mode_lt::Basic);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = threshSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Thresh.";
    param.type = tp_pipeline::doubleSID();
    param.min = 0.0;
    param.max = DBL_MAX;
    param.validateBounds<double>(128.0);

    param.enabled = (mode == Mode_lt::Basic);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = maxvalSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Maxval.";
    param.type = tp_pipeline::doubleSID();
    param.min = 0.0;
    param.max = DBL_MAX;
    param.validateBounds<double>(128.0);

    param.enabled = (mode == Mode_lt::Basic);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  auto addChannel = [&](const auto& name, const auto& description)
  {
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = description;
    param.type = tp_pipeline::intSID();
    param.min = 0;
    param.max = 255;
    param.validateBounds(128);

    param.enabled = (mode == Mode_lt::InRange);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  };

  addChannel(channel1LowSID() , "Channel 1 low threshold.");
  addChannel(channel2LowSID() , "Channel 2 low threshold.");
  addChannel(channel3LowSID() , "Channel 3 low threshold.");
  addChannel(channel1HighSID(), "Channel 1 high threshold.");
  addChannel(channel2HighSID(), "Channel 2 high threshold.");
  addChannel(channel3HighSID(), "Channel 3 high threshold.");

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
