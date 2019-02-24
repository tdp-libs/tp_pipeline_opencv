#ifndef tp_pipeline_opencv_Globals_h
#define tp_pipeline_opencv_Globals_h

#include "tp_utils/StringID.h"

namespace tp_data
{
class CollectionFactory;
}

namespace tp_pipeline
{
class StepDelegateMap;
}

//##################################################################################################
//! Add opencv to the pipeline pipeline.
namespace tp_pipeline_opencv
{
TDP_DECLARE_ID(                       opencvSID,                           "Opencv")
TDP_DECLARE_ID(             featureExtractorSID,                "Feature extractor")
TDP_DECLARE_ID(                 detectorTypeSID,                    "Detector type")
TDP_DECLARE_ID(                        cvMatSID,                           "CV mat")
TDP_DECLARE_ID(                convertImagesSID,                   "Convert images")

//##################################################################################################
//! Add the step delegates that this module provides to the StepDelegateMap
void createStepDelegates(tp_pipeline::StepDelegateMap& stepDelegates, const tp_data::CollectionFactory* collectionFactory);
}

#endif
