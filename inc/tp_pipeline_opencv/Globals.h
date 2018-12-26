#ifndef tp_pipeline_opencv_Globals_h
#define tp_pipeline_opencv_Globals_h

#include "tp_utils/StringID.h"

namespace tp_pipeline
{
class StepDelegateMap;
}

//##################################################################################################
//! Add opencv to the pipeline pipeline.
namespace tp_pipeline_opencv
{
TDP_DECLARE_ID(                       opencvSID,                          "Opencv")

//##################################################################################################
//! Add the step delegates that this module provides to the StepDelegateMap
void createStepDelegates(tp_pipeline::StepDelegateMap& stepDelegates);
}

#endif
