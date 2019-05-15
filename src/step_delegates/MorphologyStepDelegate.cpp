#include "tp_pipeline_opencv/step_delegates/MorphologyStepDelegate.h"
#include "tp_pipeline_opencv/Enums.h"

#include "tp_data_opencv/members/CVMatMember.h"

#include "tp_pipeline_image_utils/Globals.h"

#include "tp_pipeline/StepDetails.h"
#include "tp_pipeline/StepInput.h"

#include "tp_data/Collection.h"

#include <opencv2/imgproc.hpp>

namespace tp_pipeline_opencv
{

//##################################################################################################
MorphologyStepDelegate::MorphologyStepDelegate():
  tp_pipeline::AbstractStepDelegate(morphologySID(), {opencvSID()})
{

}

//##################################################################################################
void MorphologyStepDelegate::executeStep(tp_pipeline::StepDetails* stepDetails,
                                         const tp_pipeline::StepInput& input,
                                         tp_data::Collection& output) const
{
  auto morphType = morphTypeFromString(stepDetails->parameterValue<std::string>(morphTypeSID()));
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
    morphologyEx(src, dst, morphType, element);
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
void MorphologyStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
{
  stepDetails->setOutputNames({"Output data"});

  std::vector<tp_utils::StringID> validParams;
  const auto& parameters = stepDetails->parameters();

  {
    const tp_utils::StringID& name = morphTypeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Morph type.";
    param.setEnum(morphTypes());

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const tp_utils::StringID& name = elementShapeSID();
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
    param.type = tp_pipeline::namedDataSID();

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  stepDetails->setParametersOrder(validParams);
  stepDetails->setValidParameters(validParams);
}

}
