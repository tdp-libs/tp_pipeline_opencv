#include "tp_pipeline_opencv/step_delegates/ErosionDilationStepDelegate.h"
#include "tp_pipeline_opencv/Enums.h"

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
  Erosion,
  Dilation
};

//##################################################################################################
const std::vector<std::string>& modes()
{
  static const std::vector<std::string> modes
  {
    "Erosion",
    "Dilation"
  };

  return modes;
}

//##################################################################################################
Mode_lt modeFromString(const std::string& modeString)
{
  if(modeString == "Erosion")
    return Mode_lt::Erosion;

  if(modeString == "Dilation")
    return Mode_lt::Dilation;

  return Mode_lt::Erosion;
}

}

//##################################################################################################
ErosionDilationStepDelegate::ErosionDilationStepDelegate():
  tp_pipeline::AbstractStepDelegate(erosionDilationSID(), {opencvSID()})
{

}

//##################################################################################################
void ErosionDilationStepDelegate::executeStep(tp_pipeline::StepDetails* stepDetails,
                                              const tp_pipeline::StepInput& input,
                                              tp_data::Collection& output) const
{
  auto mode = modeFromString(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::modeSID()));
  auto morphShape = morphShapeFromString(stepDetails->parameterValue<std::string>(elementShapeSID()));

  int elementSize = stepDetails->parameterValue<int>(elementSizeSID());

  tp_data_opencv::CVMatMember* in{nullptr};
  input.memberCast(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::colorImageSID()), in);
  if(!in)
  {
    output.addError("Failed to find input cv::Mat data.");
    return;
  }

  cv::Mat element = cv::getStructuringElement(morphShape,
                                              cv::Size(2*elementSize + 1, 2*elementSize+1),
                                              cv::Point(-1,-1));

  const cv::Mat& src = in->data;
  cv::Mat dst;
  try
  {
    switch(mode)
    {
    case Mode_lt::Erosion:
      cv::erode(src, dst, element);
      break;

    case Mode_lt::Dilation:
      cv::dilate(src, dst, element);
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
void ErosionDilationStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
{
  stepDetails->setOutputNames({"Output data"});

  std::vector<tp_utils::StringID> validParams;
  const auto& parameters = stepDetails->parameters();

  {
    const tp_utils::StringID& name = tp_pipeline_image_utils::modeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Erode or dilate.";
    param.setEnum(modes());

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const tp_utils::StringID& name = borderTypeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Element shape.";
    param.setEnum(morphShapes());

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    tp_utils::StringID name = elementSizeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The element size.";
    param.type = tp_pipeline::intSID();
    param.min = 1;
    param.max = 31;
    param.validateBounds(4);

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
