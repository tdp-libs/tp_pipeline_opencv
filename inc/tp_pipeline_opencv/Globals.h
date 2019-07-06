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
TDP_DECLARE_ID(                         blurSID,                             "Blur")
TDP_DECLARE_ID(              erosionDilationSID,                 "Erosion dilation")
TDP_DECLARE_ID(                   morphologySID,                       "Morphology")
TDP_DECLARE_ID(                 thresholdingSID,                     "Thresholding")
TDP_DECLARE_ID(                     filter2dSID,                        "Filter 2d")
TDP_DECLARE_ID(                    addBorderSID,                       "Add border")
TDP_DECLARE_ID(                        sobelSID,                            "Sobel")
TDP_DECLARE_ID(             featureExtractorSID,                "Feature extractor")
TDP_DECLARE_ID(                 detectorTypeSID,                    "Detector type")
TDP_DECLARE_ID(                        cvMatSID,                           "CV mat")
TDP_DECLARE_ID(                convertImagesSID,                   "Convert images")
TDP_DECLARE_ID(                   borderTypeSID,                      "Border type")
TDP_DECLARE_ID(                  outputDepthSID,                     "Output depth")
TDP_DECLARE_ID(                  kernelWidthSID,                     "Kernel width")
TDP_DECLARE_ID(                 kernelHeightSID,                    "Kernel height")
TDP_DECLARE_ID(                   kernelSizeSID,                      "Kernel size")
TDP_DECLARE_ID(                       sigmaXSID,                          "Sigma x")
TDP_DECLARE_ID(                       sigmaYSID,                          "Sigma y")
TDP_DECLARE_ID(                        deltaSID,                            "Delta")
TDP_DECLARE_ID(                       deltaXSID,                          "Delta x")
TDP_DECLARE_ID(                       deltaYSID,                          "Delta y")
TDP_DECLARE_ID(                   sigmaColorSID,                      "Sigma color")
TDP_DECLARE_ID(                   sigmaSpaceSID,                      "Sigma space")
TDP_DECLARE_ID(                     diameterSID,                         "Diameter")
TDP_DECLARE_ID(                 elementShapeSID,                    "Element shape")
TDP_DECLARE_ID(                  elementSizeSID,                     "Element size")
TDP_DECLARE_ID(                    morphTypeSID,                       "Morph type")
TDP_DECLARE_ID(               conversionTypeSID,                  "Conversion type")
TDP_DECLARE_ID(                thresholdTypeSID,                   "Threshold type")
TDP_DECLARE_ID(                       threshSID,                           "Thresh")
TDP_DECLARE_ID(                       maxvalSID,                           "Maxval")
TDP_DECLARE_ID(                  channel1LowSID,                    "Channel 1 low")
TDP_DECLARE_ID(                  channel2LowSID,                    "Channel 2 low")
TDP_DECLARE_ID(                  channel3LowSID,                    "Channel 3 low")
TDP_DECLARE_ID(                 channel1HighSID,                   "Channel 1 high")
TDP_DECLARE_ID(                 channel2HighSID,                   "Channel 2 high")
TDP_DECLARE_ID(                 channel3HighSID,                   "Channel 3 high")
TDP_DECLARE_ID(                          topSID,                              "Top")
TDP_DECLARE_ID(                        rightSID,                            "Right")
TDP_DECLARE_ID(                       bottomSID,                           "Bottom")
TDP_DECLARE_ID(                         leftSID,                             "Left")


//##################################################################################################
//! Add the step delegates that this module provides to the StepDelegateMap
void createStepDelegates(tp_pipeline::StepDelegateMap& stepDelegates, const tp_data::CollectionFactory* collectionFactory);

//##################################################################################################
//! Static initialization of this module, see TP_STATIC_INIT in dependencies.pri
int staticInit();
}

#endif
