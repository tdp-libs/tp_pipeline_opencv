#include "tp_pipeline_opencv/step_delegates/ConvertImagesStepDelegate.h"
#include "tp_pipeline_opencv/Enums.h"

#include "tp_data_opencv/members/CVMatMember.h"
#include "tp_data_opencv/ImageConversion.h"

#include "tp_data_image_utils/members/ColorMapMember.h"
#include "tp_data_image_utils/members/ByteMapMember.h"

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
  ColorMapToMat,
  ByteMapToMat,
  MatToColorMap,
  MatToMat
};

//##################################################################################################
std::vector<std::string> modes()
{
  return {"ColorMap to Mat", "ByteMap to Mat", "Mat to ColorMap", "Mat to Mat"};
}

//##################################################################################################
Mode_lt modeFromString(const std::string& typeString)
{
  if(typeString == "ColorMap to Mat")
    return Mode_lt::ColorMapToMat;

  if(typeString == "ByteMap to Mat")
    return Mode_lt::ByteMapToMat;

  if(typeString == "Mat to ColorMap")
    return Mode_lt::MatToColorMap;

  if(typeString == "Mat to Mat")
    return Mode_lt::MatToMat;

  return Mode_lt::ColorMapToMat;
}

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
  auto conversionType = colorConversionCodeFromString(stepDetails->parameterValue<std::string>(conversionTypeSID()));

  switch(mode)
  {
  case Mode_lt::ColorMapToMat: //-------------------------------------------------------------------
  {
    tp_data_image_utils::ColorMapMember* in{nullptr};
    input.memberCast(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::colorImageSID()), in);
    if(!in)
    {
      output.addError("Failed to find input ColorMap data.");
      return;
    }

    auto out = new tp_data_opencv::CVMatMember(stepDetails->lookupOutputName("Output data"));
    output.addMember(out);

    tp_data_opencv::convertImage(in->data, out->data);

    break;
  }

  case Mode_lt::ByteMapToMat: //-------------------------------------------------------------------
  {
    tp_data_image_utils::ByteMapMember* in{nullptr};
    input.memberCast(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::grayImageSID()), in);
    if(!in)
    {
      output.addError("Failed to find input ByteMap data.");
      return;
    }

    auto out = new tp_data_opencv::CVMatMember(stepDetails->lookupOutputName("Output data"));
    output.addMember(out);

    tp_data_opencv::convertImage(in->data, out->data);

    break;
  }

  case Mode_lt::MatToColorMap: //-------------------------------------------------------------------
  {
    tp_data_opencv::CVMatMember* in{nullptr};
    input.memberCast(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::colorImageSID()), in);
    if(!in)
    {
      output.addError("Failed to find input cv::Mat data.");
      return;
    }

    auto out = new tp_data_image_utils::ColorMapMember(stepDetails->lookupOutputName("Output data"));
    output.addMember(out);

    tp_data_opencv::convertImage(in->data, out->data);

    break;
  }

  case Mode_lt::MatToMat: //------------------------------------------------------------------------
  {
    tp_data_opencv::CVMatMember* in{nullptr};
    input.memberCast(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::colorImageSID()), in);
    if(!in)
    {
      output.addError("Failed to find input cv::Mat data.");
      return;
    }

    auto out = new tp_data_opencv::CVMatMember(stepDetails->lookupOutputName("Output data"));
    output.addMember(out);

    try
    {
      cvtColor(in->data, out->data, conversionType);
    }
    catch( cv::Exception& e )
    {
      output.addError(e.what());
      return;
    }

    break;
  }
  }
}

//##################################################################################################
void ConvertImagesStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
{
  stepDetails->setOutputNames({"Output data"});

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

  auto mode = modeFromString(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::modeSID()));

  {
    const tp_utils::StringID& name = conversionTypeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Conversion type";
    param.setEnum(colorConversionCodes());
    param.enabled = mode==Mode_lt::MatToMat;

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const auto& name = tp_pipeline_image_utils::colorImageSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The input image.";
    param.setNamedData();

    param.enabled = (mode != Mode_lt::ByteMapToMat);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const auto& name = tp_pipeline_image_utils::grayImageSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The input image.";
    param.setNamedData();

    param.enabled = (mode == Mode_lt::ByteMapToMat);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  stepDetails->setParametersOrder(validParams);
  stepDetails->setValidParameters(validParams);
}

}
