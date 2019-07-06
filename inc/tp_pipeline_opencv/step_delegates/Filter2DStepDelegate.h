#ifndef tp_pipeline_opencv_Filter2DStepDelegate_h
#define tp_pipeline_opencv_Filter2DStepDelegate_h

#include "tp_pipeline_opencv/Globals.h"

#include "tp_pipeline/AbstractStepDelegate.h"

namespace tp_pipeline_opencv
{

//##################################################################################################
class Filter2DStepDelegate: public tp_pipeline::AbstractStepDelegate
{
public:
  //################################################################################################
  Filter2DStepDelegate();

  //################################################################################################
  void executeStep(tp_pipeline::StepDetails* stepDetails,
                   const tp_pipeline::StepInput& inputs,
                   tp_data::Collection& output) const override;

  //################################################################################################
  void fixupParameters(tp_pipeline::StepDetails* stepDetails)const override;
};

}

#endif
