#ifndef tp_pipeline_opencv_Enums_h
#define tp_pipeline_opencv_Enums_h

#include "tp_pipeline_opencv/Globals.h"

#include <opencv2/imgproc.hpp>

namespace tp_pipeline_opencv
{

//##################################################################################################
const std::vector<std::string>& morphShapes();

//##################################################################################################
cv::MorphShapes morphShapeFromString(const std::string& morphShapeString);

//##################################################################################################
const std::vector<std::string>& morphTypes();

//##################################################################################################
cv::MorphTypes morphTypeFromString(const std::string& morphTypeString);

}

#endif
