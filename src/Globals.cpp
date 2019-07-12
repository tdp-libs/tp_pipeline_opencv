#include "tp_pipeline_opencv/Globals.h"
#include "tp_pipeline_opencv/step_delegates/ConvertImagesStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/FeatureExtractorStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/BlurStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/ErosionDilationStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/MorphologyStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/ThresholdingStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/Filter2DStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/AddBorderStepDelegate.h"
#include "tp_pipeline_opencv/step_delegates/HistogramEqualizationStepDelegate.h"

#include "tp_pipeline/StepDelegateMap.h"

//##################################################################################################
namespace tp_pipeline_opencv
{
TDP_DEFINE_ID(                       opencvSID,                           "Opencv")
TDP_DEFINE_ID(                         blurSID,                             "Blur")
TDP_DEFINE_ID(              erosionDilationSID,                 "Erosion dilation")
TDP_DEFINE_ID(                   morphologySID,                       "Morphology")
TDP_DEFINE_ID(                 thresholdingSID,                     "Thresholding")
TDP_DEFINE_ID(                     filter2dSID,                        "Filter 2d")
TDP_DEFINE_ID(                    addBorderSID,                       "Add border")
TDP_DEFINE_ID(        histogramEqualizationSID,           "Histogram equalization")
TDP_DEFINE_ID(                        sobelSID,                            "Sobel")
TDP_DEFINE_ID(             featureExtractorSID,                "Feature extractor")
TDP_DEFINE_ID(                 detectorTypeSID,                    "Detector type")
TDP_DEFINE_ID(                         modeSID,                             "Mode")
TDP_DEFINE_ID(                        cvMatSID,                           "CV mat")
TDP_DEFINE_ID(                convertImagesSID,                   "Convert images")
TDP_DEFINE_ID(                   borderTypeSID,                      "Border type")
TDP_DEFINE_ID(                  outputDepthSID,                     "Output depth")
TDP_DEFINE_ID(                  kernelWidthSID,                     "Kernel width")
TDP_DEFINE_ID(                 kernelHeightSID,                    "Kernel height")
TDP_DEFINE_ID(                   kernelSizeSID,                      "Kernel size")
TDP_DEFINE_ID(                       sigmaXSID,                          "Sigma x")
TDP_DEFINE_ID(                       sigmaYSID,                          "Sigma y")
TDP_DEFINE_ID(                        deltaSID,                            "Delta")
TDP_DEFINE_ID(                       deltaXSID,                          "Delta x")
TDP_DEFINE_ID(                       deltaYSID,                          "Delta y")
TDP_DEFINE_ID(                   sigmaColorSID,                      "Sigma color")
TDP_DEFINE_ID(                   sigmaSpaceSID,                      "Sigma space")
TDP_DEFINE_ID(                     diameterSID,                         "Diameter")
TDP_DEFINE_ID(                 elementShapeSID,                    "Element shape")
TDP_DEFINE_ID(                  elementSizeSID,                     "Element size")
TDP_DEFINE_ID(                    morphTypeSID,                       "Morph type")
TDP_DEFINE_ID(               conversionTypeSID,                  "Conversion type")
TDP_DEFINE_ID(                thresholdTypeSID,                   "Threshold type")
TDP_DEFINE_ID(                       threshSID,                           "Thresh")
TDP_DEFINE_ID(                       maxvalSID,                           "Maxval")
TDP_DEFINE_ID(                  channel1LowSID,                    "Channel 1 low")
TDP_DEFINE_ID(                  channel2LowSID,                    "Channel 2 low")
TDP_DEFINE_ID(                  channel3LowSID,                    "Channel 3 low")
TDP_DEFINE_ID(                 channel1HighSID,                   "Channel 1 high")
TDP_DEFINE_ID(                 channel2HighSID,                   "Channel 2 high")
TDP_DEFINE_ID(                 channel3HighSID,                   "Channel 3 high")
TDP_DEFINE_ID(                          topSID,                              "Top")
TDP_DEFINE_ID(                        rightSID,                            "Right")
TDP_DEFINE_ID(                       bottomSID,                           "Bottom")
TDP_DEFINE_ID(                         leftSID,                             "Left")
TDP_DEFINE_ID(                 lowThresholdSID,                    "Low threshold")
TDP_DEFINE_ID(                highThresholdSID,                   "High threshold")

//##################################################################################################
void createStepDelegates(tp_pipeline::StepDelegateMap& stepDelegates, const tp_data::CollectionFactory* collectionFactory)
{
  TP_UNUSED(collectionFactory);
  stepDelegates.addStepDelegate(new ConvertImagesStepDelegate);
  stepDelegates.addStepDelegate(new FeatureExtractorStepDelegate);
  stepDelegates.addStepDelegate(new BlurStepDelegate);
  stepDelegates.addStepDelegate(new ErosionDilationStepDelegate);
  stepDelegates.addStepDelegate(new MorphologyStepDelegate);
  stepDelegates.addStepDelegate(new ThresholdingStepDelegate);
  stepDelegates.addStepDelegate(new Filter2DStepDelegate);
  stepDelegates.addStepDelegate(new AddBorderStepDelegate);
  stepDelegates.addStepDelegate(new HistogramEqualizationStepDelegate);
}

REGISTER_CREATE_STEP_DELEGATES;

//##################################################################################################
int staticInit()
{
  return 0;
}

}
