#ifndef tp_pipeline_opencv_AddBorderStepDelegate_h
#define tp_pipeline_opencv_AddBorderStepDelegate_h

#include "tp_pipeline_opencv/Globals.h"

#include "tp_pipeline/AbstractStepDelegate.h"

namespace tp_pipeline_opencv
{

//##################################################################################################
class AddBorderStepDelegate: public tp_pipeline::AbstractStepDelegate
{
public:
  //################################################################################################
  AddBorderStepDelegate();

  //################################################################################################
  void executeStep(tp_pipeline::StepDetails* stepDetails,
                   const tp_pipeline::StepInput& inputs,
                   tp_data::Collection& output) const override;

  //################################################################################################
  void fixupParameters(tp_pipeline::StepDetails* stepDetails)const override;
};

}

#endif
