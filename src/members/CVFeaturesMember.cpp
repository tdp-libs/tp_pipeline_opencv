#include "tp_pipeline_opencv/members/CVFeaturesMember.h"

namespace tp_pipeline_opencv
{

//##################################################################################################
CVFeaturesMember::CVFeaturesMember(const std::string& name):
  tp_data_features::FeaturesMember(name, tp_data_features::featuresSID())
{

}

//##################################################################################################
CVFeaturesMember::~CVFeaturesMember() = default;

//##################################################################################################
void CVFeaturesMember::populateFeatures()
{
  //    tp_math_utils::RNG rng;
  //    auto randomColor = [&]()
  //    {
  //      return glm::vec4(rng.randF()*0.4f+0.4f, rng.randF()*0.4f+0.4f, rng.randF()*0.4f+0.4f, 1.0f);
  //    };
  //    for(int i=0; i<int(featureCollection->kp.size()); i++)
  //    {
  //      const cv::KeyPoint& featurePoint = featureCollection->kp.at(i);
  //      OpenCVFeature* feature = new OpenCVFeature();
  //      feature->frame = 0;
  //      feature->coord2D = {featurePoint.pt.x, featurePoint.pt.y};
  //      feature->coord2DNormalized = {(f.x*float(feature->coord2D.x))-1.0f, (f.y*float(feature->coord2D.y))+1.0f};
  //      feature->kp = featurePoint;
  //      feature->color = tpGetMapValue(featureColors, feature->coord2D, randomColor());
  //      feature->meanColor = wrldcv_basic_types::meanColor(image->image, feature->coord2D, 5);
  //      featureCollection->addFeature(feature);
  //    }
  //  }
}
}

