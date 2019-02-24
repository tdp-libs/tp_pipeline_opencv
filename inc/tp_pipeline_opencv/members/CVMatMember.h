#ifndef tp_pipeline_opencv_CVMatMember_h
#define tp_pipeline_opencv_CVMatMember_h

#include "tp_pipeline_opencv/Globals.h"

#include "tp_data/AbstractMember.h"

#include <opencv2/core/mat.hpp>

namespace tp_pipeline_opencv
{

//##################################################################################################
class CVMatMember : public tp_data::AbstractMember
{
public:
  //################################################################################################
  CVMatMember(const std::string& name=std::string());

  cv::Mat data;
};

}

#endif
