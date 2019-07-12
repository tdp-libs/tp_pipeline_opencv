#include "tp_pipeline_opencv/step_delegates/HistogramEqualizationStepDelegate.h"
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
HistogramEqualizationStepDelegate::HistogramEqualizationStepDelegate():
  tp_pipeline::AbstractStepDelegate(histogramEqualizationSID(), {opencvSID()})
{

}

//##################################################################################################
void HistogramEqualizationStepDelegate::executeStep(tp_pipeline::StepDetails* stepDetails,
                                                    const tp_pipeline::StepInput& input,
                                                    tp_data::Collection& output) const
{
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
    cv::equalizeHist(src, dst);
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
void HistogramEqualizationStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
{
  stepDetails->setOutputNames({"Output data"});

  std::vector<tp_utils::StringID> validParams;
  const auto& parameters = stepDetails->parameters();

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
