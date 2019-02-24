#include "tp_pipeline_opencv/ImageConversion.h"

#include "tp_image_utils/ColorMap.h"
#include "tp_image_utils/ByteMap.h"

#include <opencv2/core.hpp>

namespace tp_pipeline_opencv
{

//##################################################################################################
void convertImage(const tp_image_utils::ColorMap& in, cv::Mat& out)
{
  int rows = int(in.height());
  int cols = int(in.width());

  out = cv::Mat(rows, cols, CV_8UC4);

  {
    const TPPixel* i = in.constData();
    const TPPixel* iMax = i+(rows*cols);
    uint8_t* o = out.data;
    for(; i<iMax; i++, o+=4)
    {
      o[0] = i->b;
      o[1] = i->g;
      o[2] = i->r;
      o[3] = i->a;
    }
  }
}

//##################################################################################################
void convertImage(const tp_image_utils::ByteMap& in, cv::Mat& out)
{
  int rows = int(in.height());
  int cols = int(in.width());

  out = cv::Mat(rows, cols, CV_8UC1);

  {
    const uint8_t* i = in.constData();
    const uint8_t* iMax = i+(rows*cols);
    uint8_t* o = out.data;
    for(; i<iMax; i++, o++)
    {
      (*o) = (*i);
    }
  }
}

//##################################################################################################
void convertImage(const cv::Mat& in, tp_image_utils::ColorMap& out)
{
  size_t rows = size_t(in.rows);
  size_t cols = size_t(in.cols);

  if(in.type() != CV_8UC4)
    return;

  out = tp_image_utils::ColorMap(cols, rows);

  {
    TPPixel* o = out.data();
    TPPixel* oMax = o+(rows*cols*4);
    uint8_t* i = in.data;
    for(; o<oMax; i++, o+=4)
    {
      o->b = i[0];
      o->g = i[1];
      o->r = i[2];
      o->a = i[3];
    }
  }
}

//##################################################################################################
void convertImage(const cv::Mat& in, tp_image_utils::ByteMap& out)
{
  size_t rows = size_t(in.rows);
  size_t cols = size_t(in.cols);

  if(in.type() != CV_8UC1)
    return;

  out = tp_image_utils::ByteMap(cols, rows);

  {
    uint8_t* o = out.data();
    uint8_t* oMax = o+(rows*cols);
    uint8_t* i = in.data;
    for(; o<oMax; i++, o+=4)
      (*o) = (*i);
  }
}

}
