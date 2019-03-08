#include "tp_pipeline_opencv/step_delegates/FeatureExtractorStepDelegate.h"

#include "tp_data_opencv/members/CVMatMember.h"
#include "tp_data_opencv/members/CVFeaturesMember.h"

#include "tp_pipeline_image_utils/Globals.h"

#include "tp_pipeline/StepDetails.h"
#include "tp_pipeline/StepInput.h"

#include "tp_data/Collection.h"

#include "tp_utils/DebugUtils.h"

#include <opencv2/features2d.hpp>

namespace tp_pipeline_opencv
{

namespace
{

//##################################################################################################
enum class DetectorType_lt
{
  ORB,
  BRISK
};

//##################################################################################################
std::vector<std::string> detectorTypes()
{
  return {"ORB", "BRISK"};
}

//##################################################################################################
DetectorType_lt detectorTypeFromString(const std::string& typeString)
{
  if(typeString == "ORB")
    return DetectorType_lt::ORB;

  return DetectorType_lt::BRISK;
}

//##################################################################################################
enum class Mode_lt
{
  DetectAndExtract, //!< Use opencv to detect and extract features from the image.
  Extract           //!< Extract features from the image using coords from a feature observation.
};

//##################################################################################################
std::vector<std::string> modes()
{
  return {"Detect and extract", "Extract"};
}

//##################################################################################################
Mode_lt modeFromString(const std::string& typeString)
{
  if(typeString == "Detect and extract")
    return Mode_lt::DetectAndExtract;

  return Mode_lt::Extract;
}

}

//##################################################################################################
FeatureExtractorStepDelegate::FeatureExtractorStepDelegate():
  tp_pipeline::AbstractStepDelegate(featureExtractorSID(), {opencvSID()})
{

}

//##################################################################################################
void FeatureExtractorStepDelegate::executeStep(tp_pipeline::StepDetails* stepDetails,
                                               const tp_pipeline::StepInput& input,
                                               tp_data::Collection& output) const
{
  tp_data_opencv::CVMatMember* image{nullptr};
  input.memberCast(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::colorImageSID()), image);
  if(!image)
  {
    output.addError("Failed to find input cv::Mat data.");
    return;
  }

  auto detectorType = detectorTypeFromString(stepDetails->parameterValue<std::string>(detectorTypeSID()));
  auto mode         = modeFromString(stepDetails->parameterValue<std::string>(tp_pipeline_image_utils::modeSID()));

  int             maxFeatures   = 5000;

  const int   briskThreshl       = 30;
  const int   briskOctaves       = 3;
  const float briskPatternScales = 1.0f;

  //Construct the extractor that we are using.
  cv::Ptr<cv::ORB> orb;
  cv::Ptr<cv::BRISK> brisk;
  cv::Feature2D* extractor{nullptr};
  switch(detectorType)
  {
  case DetectorType_lt::ORB:
  {
    orb = cv::ORB::create();
    orb->setMaxFeatures(maxFeatures);
    extractor = orb;
    break;
  }

  case DetectorType_lt::BRISK:
  {
    brisk = cv::BRISK::create(briskThreshl, briskOctaves, briskPatternScales);
    extractor = brisk;
    break;
  }
  }

  auto out = new tp_data_opencv::CVFeaturesMember("features");
  output.addMember(out);

  //== Extract the features ========================================================================
  switch(mode)
  {
  case Mode_lt::DetectAndExtract: //-- DetectAndExtract --------------------------------------------
  {
    //Find and extract feature descriptors from the source image.
    extractor->detectAndCompute(image->data,
                                cv::noArray(),
                                out->kp,
                                out->desc);

    tpDebug() << out->kp.size();

    break;
  }

  case Mode_lt::Extract: //-- Extract --------------------------------------------------------------
  {
    //    out->kp.reserve(newFeatures.size());
    //    for(const OpenCVFeature* i : newFeatures)
    //    {
    //      cv::KeyPoint kp = i->kp;
    //      kp.pt.x = i->coord2D.x;
    //      kp.pt.y = i->coord2D.y;
    //      out->kp.push_back(kp);
    //      featureColors[i->coord2D] = i->color;
    //    }

    extractor->compute(image->data,
                       out->kp,
                       out->desc);

    break;
  }
  }

  out->populateFeatures();
}

//##################################################################################################
void FeatureExtractorStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
{
  stepDetails->setOutputNames({"Output image"});

  std::vector<tp_utils::StringID> validParams;
  const auto& parameters = stepDetails->parameters();

  {
    const tp_utils::StringID& name = detectorTypeSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "The type of feature detector to use.";
    param.setEnum(detectorTypes());

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

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
    param.description = "The source image to detect features from.";
    param.type = tp_pipeline::namedDataSID();

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  {
    const auto& name = tp_data_features::featuresSID();
    auto param = tpGetMapValue(parameters, name);
    param.name = name;
    param.description = "Input features for extraction.";
    param.type = tp_pipeline::namedDataSID();

    stepDetails->setParamerter(param);
    validParams.push_back(name);
  }

  stepDetails->setParametersOrder(validParams);
  stepDetails->setValidParameters(validParams);
}

}
