#ifndef tp_pipeline_opencv_CVMatchesMember_h
#define tp_pipeline_opencv_CVMatchesMember_h

#include "tp_pipeline_opencv/Globals.h"

#include "tp_data_features/members/MatchesMember.h"

#include <opencv2/core/mat.hpp>

namespace tp_pipeline_opencv
{

//##################################################################################################
class CVMatchesMember : public tp_data_features::MatchesMember
{
public:
  //################################################################################################
  CVMatchesMember(const std::string& name=std::string());

  //################################################################################################
  void populateFields();

  //cv::Mat data;
};

}

#endif
