#include "tp_pipeline_opencv/step_delegates/MorphologyStepDelegate.h"
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

  tp_data_opencv::CVMatMember* in{nullptr};
  input.memberCast(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::colorImageSID()), in);
  if(!in)
  {
    output.addError("Failed to find input cv::Mat data.");
    return;
  }

  cv::Mat element;

  if(morphType == cv::MORPH_HITMISS)
  {
    tp_image_utils_functions::ConvolutionMatrix matrix(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::kernelSID()));
    element = cv::Mat_<int>(int(matrix.height()), int(matrix.width()));

    for(size_t x=0; x<matrix.width(); x++)
      for(size_t y=0; y<matrix.height(); y++)
        element.at<int>(int(y), int(x)) = matrix.matrixData().at((y*matrix.width()));
  }
  else
  {
    int elementSize = stepDetails->parameterValue<int>(elementSizeSID());
    element = cv::getStructuringElement(morphShape,
                                        cv::Size(2*elementSize + 1, 2*elementSize+1),
                                        cv::Point(-1,-1));
  }





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

  auto morphType = morphTypeFromString(stepDetails->parameterValue<std::string>(morphTypeSID()));

  {
    const tp_utils::StringID& name = elementShapeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Element shape.";
    param.setEnum(morphShapes());

    param.enabled = (morphType == cv::MORPH_HITMISS);

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

    param.enabled = (morphType != cv::MORPH_HITMISS);

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const auto& name = tp_pipeline_image_utils::kernelSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The hit and miss kernel.";
    param.type = tp_pipeline::convolutionMatrixSID();

    param.value = tp_image_utils_functions::ConvolutionMatrix(tpGetVariantValue<std::string>(param.value)).toString();

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
