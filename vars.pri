TARGET = tp_pipeline_opencv
TEMPLATE = lib

DEFINES += TP_PIPELINE_OPENCV_LIBRARY

SOURCES += src/Globals.cpp
HEADERS += inc/tp_pipeline_opencv/Globals.h

SOURCES += src/ImageConversion.cpp
HEADERS += inc/tp_pipeline_opencv/ImageConversion.h

#-- Delegates --------------------------------------------------------------------------------------
SOURCES += src/step_delegates/ConvertImagesStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/ConvertImagesStepDelegate.h

SOURCES += src/step_delegates/FeatureExtractorStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/FeatureExtractorStepDelegate.h

SOURCES += src/step_delegates/FeatureMatcherStepDelegate.cpp
HEADERS += inc/tp_pipeline_opencv/step_delegates/FeatureMatcherStepDelegate.h


#-- Members ----------------------------------------------------------------------------------------
SOURCES += src/members/CVMatMember.cpp
HEADERS += inc/tp_pipeline_opencv/members/CVMatMember.h

SOURCES += src/members/CVFeaturesMember.cpp
HEADERS += inc/tp_pipeline_opencv/members/CVFeaturesMember.h

SOURCES += src/members/CVMatchesMember.cpp
HEADERS += inc/tp_pipeline_opencv/members/CVMatchesMember.h
