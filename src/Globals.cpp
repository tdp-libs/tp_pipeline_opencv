#include "tp_pipeline_opencv/Globals.h"
#include "tp_pipeline_opencv/step_delegates/ConvertImagesStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/FeatureExtractorStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/BlurStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/ErosionDilationStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/MorphologyStepDelegate.h"

#include "tp_pipeline/StepDelegateMap.h"

//##################################################################################################
namespace tp_pipeline_opencv
{
TDP_DEFINE_ID(                       opencvSID,                           "Opencv")
TDP_DEFINE_ID(                         blurSID,                             "Blur")
TDP_DEFINE_ID(              erosionDilationSID,                 "Erosion dilation")
TDP_DEFINE_ID(                   morphologySID,                       "Morphology")
TDP_DEFINE_ID(             featureExtractorSID,                "Feature extractor")
TDP_DEFINE_ID(                 detectorTypeSID,                    "Detector type")
TDP_DEFINE_ID(                         modeSID,                             "Mode")
TDP_DEFINE_ID(                        cvMatSID,                           "CV mat")
TDP_DEFINE_ID(                convertImagesSID,                   "Convert images")
TDP_DEFINE_ID(                   borderTypeSID,                      "Border type")
TDP_DEFINE_ID(                  kernelWidthSID,                     "Kernel width")
TDP_DEFINE_ID(                 kernelHeightSID,                    "Kernel height")
TDP_DEFINE_ID(                   kernelSizeSID,                      "Kernel size")
TDP_DEFINE_ID(                       sigmaXSID,                          "Sigma x")
TDP_DEFINE_ID(                       sigmaYSID,                          "Sigma y")
TDP_DEFINE_ID(                   sigmaColorSID,                      "Sigma color")
TDP_DEFINE_ID(                   sigmaSpaceSID,                      "Sigma space")
TDP_DEFINE_ID(                     diameterSID,                         "Diameter")
TDP_DEFINE_ID(                 elementShapeSID,                    "Element shape")
TDP_DEFINE_ID(                  elementSizeSID,                     "Element size")
TDP_DEFINE_ID(                    morphTypeSID,                       "Morph type")

//##################################################################################################
void createStepDelegates(tp_pipeline::StepDelegateMap& stepDelegates, const tp_data::CollectionFactory* collectionFactory)
{
  TP_UNUSED(collectionFactory);
  stepDelegates.addStepDelegate(new ConvertImagesStepDelegate);
  stepDelegates.addStepDelegate(new FeatureExtractorStepDelegate);
  stepDelegates.addStepDelegate(new BlurStepDelegate);
  stepDelegates.addStepDelegate(new ErosionDilationStepDelegate);
  stepDelegates.addStepDelegate(new MorphologyStepDelegate);
}

REGISTER_CREATE_STEP_DELEGATES;

//##################################################################################################
int staticInit()
{
  return 0;
}
}
