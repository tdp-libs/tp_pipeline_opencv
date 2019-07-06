TARGET = tp_pipeline_opencv
TEMPLATE = lib

DEFINES += TP_PIPELINE_OPENCV_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tp_pipeline_opencv/Globals.h

SOURCES += src/Enums.cpp
HEADERS += inc/tp_pipeline_opencv/Enums.h

#-- Delegates --------------------------------------------------------------------------------------
SOURCES += src/step_delegates/ConvertImagesStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/ConvertImagesStepDelegate.h

SOURCES += src/step_delegates/FeatureExtractorStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/FeatureExtractorStepDelegate.h

SOURCES += src/step_delegates/FeatureMatcherStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/FeatureMatcherStepDelegate.h

SOURCES += src/step_delegates/BlurStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/BlurStepDelegate.h

SOURCES += src/step_delegates/ErosionDilationStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/ErosionDilationStepDelegate.h

SOURCES += src/step_delegates/MorphologyStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/MorphologyStepDelegate.h

SOURCES += src/step_delegates/ThresholdingStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/ThresholdingStepDelegate.h

SOURCES += src/step_delegates/Filter2DStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/Filter2DStepDelegate.h

SOURCES += src/step_delegates/AddBorderStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/AddBorderStepDelegate.h

SOURCES += src/step_delegates/SobelStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/SobelStepDelegate.h
