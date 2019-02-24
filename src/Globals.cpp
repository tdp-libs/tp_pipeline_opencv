#include "tp_pipeline_opencv/Globals.h"
#include "tp_pipeline_opencv/step_delegates/ConvertImagesStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/FeatureExtractorStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/FeatureMatcherStepDelegate.h"

#include "tp_pipeline/StepDelegateMap.h"

//##################################################################################################
namespace tp_pipeline_opencv
{
TDP_DEFINE_ID(                       opencvSID,                           "Opencv")
TDP_DEFINE_ID(             featureExtractorSID,                "Feature extractor")
TDP_DEFINE_ID(                 detectorTypeSID,                    "Detector type")
TDP_DEFINE_ID(                         modeSID,                             "Mode")
TDP_DEFINE_ID(                        cvMatSID,                           "CV mat")
TDP_DEFINE_ID(                convertImagesSID,                   "Convert images")

//##################################################################################################
void createStepDelegates(tp_pipeline::StepDelegateMap& stepDelegates, const tp_data::CollectionFactory* collectionFactory)
{
  TP_UNUSED(collectionFactory);
  stepDelegates.addStepDelegate(new ConvertImagesStepDelegate);
  stepDelegates.addStepDelegate(new FeatureExtractorStepDelegate);
  //stepDelegates.addStepDelegate(new FeatureMatcherStepDelegate);
}
}
