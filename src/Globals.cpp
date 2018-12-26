#include "tp_pipeline_opencv/Globals.h"
//#include "tp_pipeline_opencv/step_delegates/StubStepDelegate.h"

#include "tp_pipeline/StepDelegateMap.h"

//##################################################################################################
namespace tp_pipeline_opencv
{
TDP_DEFINE_ID(                       opencvSID,                           "Opencv")

//##################################################################################################
void createStepDelegates(tp_pipeline::StepDelegateMap& stepDelegates)
{
  TP_UNUSED(stepDelegates);
  //stepDelegates.addStepDelegate(new StubStepDelegate);
}
}
