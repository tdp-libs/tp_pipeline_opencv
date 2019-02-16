TARGET = tp_pipeline_opencv
TEMPLATE = lib

DEFINES += TP_PIPELINE_OPENCV_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tp_pipeline_opencv/Globals.h


#-- Delegates --------------------------------------------------------------------------------------
SOURCES += src/step_delegates/StubStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/StubStepDelegate.h

SOURCES += src/step_delegates/FeatureExtractorStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/FeatureExtractorStepDelegate.h

SOURCES += src/step_delegates/FeatureMatcherStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/FeatureMatcherStepDelegate.h


#-- Members ----------------------------------------------------------------------------------------
SOURCES += src/members/StubMember.cpp
HEADERS += inc/tp_pipeline_opencv/members/StubMember.h
