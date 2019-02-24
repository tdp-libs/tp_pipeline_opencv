#ifndef tp_pipeline_opencv_ImageConversion_h
#define tp_pipeline_opencv_ImageConversion_h

#include "tp_pipeline_opencv/Globals.h"

namespace tp_image_utils
{
struct ColorMap;
struct ByteMap;
}

namespace cv
{
class Mat;
}

namespace tp_pipeline_opencv
{

//##################################################################################################
void convertImage(const tp_image_utils::ColorMap& in, cv::Mat& out);

//##################################################################################################
void convertImage(const tp_image_utils::ByteMap& in, cv::Mat& out);

//##################################################################################################
void convertImage(const cv::Mat& in, tp_image_utils::ColorMap& out);

//##################################################################################################
void convertImage(const cv::Mat& in, tp_image_utils::ByteMap& out);

}

#endif
