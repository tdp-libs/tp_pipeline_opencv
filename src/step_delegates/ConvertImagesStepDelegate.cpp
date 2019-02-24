#include "tp_pipeline_opencv/step_delegates/ConvertImagesStepDelegate.h"
#include "tp_pipeline_opencv/members/CVMatMember.h"
#include "tp_pipeline_opencv/ImageConversion.h"

#include "tp_data_image_utils/members/ColorMapMember.h"

#include "tp_pipeline_image_utils/Globals.h"

#include "tp_pipeline/StepDetails.h"
#include "tp_pipeline/StepInput.h"

#include "tp_data/Collection.h"



namespace tp_pipeline_opencv
{

//##################################################################################################
enum class Mode_lt
{
  ColorMapToMat,
  MatToColorMap
};

//##################################################################################################
std::vector<std::string> modes()
{
  return {"ColorMap to Mat", "Mat to ColorMap"};
}

//##################################################################################################
Mode_lt modeFromString(const std::string& typeString)
{
  if(typeString == "ColorMap to Mat")
    return Mode_lt::ColorMapToMat;

  return Mode_lt::MatToColorMap;
}

//##################################################################################################
ConvertImagesStepDelegate::ConvertImagesStepDelegate():
  tp_pipeline::AbstractStepDelegate(convertImagesSID(), {opencvSID()})
{

}

//##################################################################################################
void ConvertImagesStepDelegate::executeStep(tp_pipeline::StepDetails* stepDetails,
                                            const tp_pipeline::StepInput& input,
                                            tp_data::Collection& output) const
{
  auto mode = modeFromString(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::modeSID()));
  switch(mode)
  {
  case Mode_lt::ColorMapToMat:
  {
    tp_data_image_utils::ColorMapMember* in{nullptr};
    input.memberCast(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::colorImageSID()), in);
    if(!in)
    {
      output.addError("Failed to find input ColorMap data.");
      return;
    }

    auto out = new CVMatMember(stepDetails->lookupOutputName("Output image"));
    output.addMember(out);

    convertImage(in->data, out->data);

    break;
  }

  case Mode_lt::MatToColorMap:
  {
    CVMatMember* in{nullptr};
    input.memberCast(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::colorImageSID()), in);
    if(!in)
    {
      output.addError("Failed to find input cv::Mat data.");
      return;
    }

    auto out = new tp_data_image_utils::ColorMapMember(stepDetails->lookupOutputName("Output image"));
    output.addMember(out);

    convertImage(in->data, out->data);

    break;
  }
  }
}

//##################################################################################################
void ConvertImagesStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
{
  stepDetails->setOutputNames({"Output image"});

  std::vector<tp_utils::StringID> validParams;
  const auto& parameters = stepDetails->parameters();

  {
    const tp_utils::StringID& name = tp_pipeline_image_utils::modeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The mode to operate in.";
    param.setEnum(modes());

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
