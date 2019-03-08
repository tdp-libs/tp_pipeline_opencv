TARGET = tp_pipeline_opencv
TEMPLATE = lib

DEFINES += TP_PIPELINE_OPENCV_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tp_pipeline_opencv/Globals.h

#-- Delegates --------------------------------------------------------------------------------------
SOURCES += src/step_delegates/ConvertImagesStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/ConvertImagesStepDelegate.h

SOURCES += src/step_delegates/FeatureExtractorStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/FeatureExtractorStepDelegate.h

SOURCES += src/step_delegates/FeatureMatcherStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/FeatureMatcherStepDelegate.h

