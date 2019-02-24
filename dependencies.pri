DEPENDENCIES += tp_pipeline_image_utils
DEPENDENCIES += tp_pipeline_math_utils
DEPENDENCIES += tp_data_features
INCLUDEPATHS += tp_pipeline_opencv/inc/
LIBRARIES    += tp_pipeline_opencv

LIBS += -lopencv_features2d
LIBS += -lopencv_core
LIBS += -lopencv_highgui
LIBS += -lopencv_imgproc
