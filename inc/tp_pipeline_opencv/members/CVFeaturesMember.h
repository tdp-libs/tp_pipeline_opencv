#ifndef tp_pipeline_opencv_CVFeaturesMember_h
#define tp_pipeline_opencv_CVFeaturesMember_h

#include "tp_pipeline_opencv/Globals.h"

#include "tp_data_features/members/FeaturesMember.h"

#include <opencv2/features2d.hpp>

namespace tp_pipeline_opencv
{

//##################################################################################################
class CVFeaturesMember : public tp_data_features::FeaturesMember
{
public:
  //################################################################################################
  CVFeaturesMember(const std::string& name=std::string());

  //################################################################################################
  ~CVFeaturesMember() override;

  //################################################################################################
  void populateFeatures();

  cv::Mat desc;
  std::vector<cv::KeyPoint> kp;
};

}

#endif
