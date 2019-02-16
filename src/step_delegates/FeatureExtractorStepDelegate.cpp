#include "tp_pipeline_opencv/step_delegates/FeatureExtractorStepDelegate.h"

#include "tp_pipeline/StepDetails.h"
#include "tp_pipeline/StepInput.h"

#include "tp_data/Collection.h"

#include <opencv2/features2d.hpp>

namespace tp_pipeline_opencv
{

namespace
{

//##################################################################################################
enum class DetectorType_lt
{
  ORB,
  BRISK
};

//##################################################################################################
enum class Mode_lt
{
  DetectAndExtract, //!< Use opencv to detect and extract features from the image.
  Extract           //!< Extract features from the image using coords from a feature observation.
};

}

//##################################################################################################
FeatureExtractorStepDelegate::FeatureExtractorStepDelegate():
  tp_pipeline::AbstractStepDelegate(featureExtractorSID(), {opencvSID()})
{

}

//##################################################################################################
void FeatureExtractorStepDelegate::executeStep(tp_pipeline::StepDetails* stepDetails,
                                               const tp_pipeline::StepInput& input,
                                               tp_data::Collection& output) const
{
  TP_UNUSED(stepDetails);
  TP_UNUSED(input);
  TP_UNUSED(output);

  DetectorType_lt detectorType  = DetectorType_lt::ORB;
  Mode_lt         mode          = Mode_lt::DetectAndExtract;
  int             maxFeatures   = 5000;

  const int   briskThreshl       = 30;
  const int   briskOctaves       = 3;
  const float briskPatternScales = 1.0f;

  cv::Ptr<cv::ORB>     orb      = cv::ORB::create();
  orb->setMaxFeatures(maxFeatures);

  cv::Ptr<cv::BRISK> brisk      = cv::BRISK::create(briskThreshl, briskOctaves, briskPatternScales);

  cv::Feature2D* extractor{nullptr};
  switch(detectorType)
  {
  case DetectorType_lt::ORB:
    extractor = orb;
    break;

  case DetectorType_lt::BRISK:
    extractor = brisk;
    break;
  }


}

//##################################################################################################
void FeatureExtractorStepDelegate::fixupParameters(tp_pipeline::StepDetails* stepDetails) const
{
  stepDetails->setOutputNames({"Output image"});

  std::vector<tp_utils::StringID> validParams;
  //  const auto& parameters = stepDetails->parameters();

  //  {
  //    const auto& name = tp_pipeline_image_utils::colorImageSID();
  //    auto param = tpGetMapValue(parameters, name);
  //    param.name = name;
  //    param.description = "The source color image to draw on.";
  //    param.type = tp_pipeline::namedDataSID();

  //    stepDetails->setParamerter(param);
  //    validParams.push_back(name);
  //  }

  //  {
  //    const auto& name = tp_pipeline_math_utils::polygonsSID();
  //    auto param = tpGetMapValue(parameters, name);
  //    param.name = name;
  //    param.description = "The polygons to draw.";
  //    param.type = tp_pipeline::namedDataSID();

  //    stepDetails->setParamerter(param);
  //    validParams.push_back(name);
  //  }

  stepDetails->setParametersOrder(validParams);
  stepDetails->setValidParameters(validParams);
}

}


//#include "wrldcv_opencv/processes/FeatureExtractorProcess.h"
//#include "wrldcv_opencv/observations/FeatureMatchObservation.h"
//#include "wrldcv_opencv/ImageConversion.h"

//#include "wrldcv_basic_types/observations/ImageObservation.h"
//#include "wrldcv_basic_types/observations/FeatureCollectionObservation.h"
//#include "wrldcv_basic_types/observations/NameObservation.h"

//#include "wrldcv_core/Network.h"

//#include "tp_math_utils/Globals.h"

//#include "tp_quad_tree/QuadTreeInt.h"

//#include "tp_utils/DebugUtils.h"
//#include "tp_utils/TimeUtils.h"

//#include <unordered_set>

//namespace  wrldcv_opencv
//{

//namespace
//{
//}

////##################################################################################################
//FeatureExtractorProcess::FeatureExtractorProcess(const std::string& description,
//                                                 FeatureExtractorProcess::DetectorType detectorType,
//                                                 FeatureExtractorProcess::Mode mode):
//  wrldcv_core::AbstractProcess(description),
//  d(new Private(detectorType, mode))
//{

//}

////##################################################################################################
//FeatureExtractorProcess::~FeatureExtractorProcess()
//{
//  delete d;
//}

////##################################################################################################
//void FeatureExtractorProcess::run(std::string& error, const std::vector<const wrldcv_core::Network*>& input, wrldcv_core::Network& output)
//{
//  //We expect this input
//  // - Serialized stream of data
//  // - Feature collections...

//  //We produce this output
//  // - Feature descriptors

//  if(input.empty())
//  {
//    error = "ORBFeatureExtractorProcess::run expects 1 or more inputs: (Serialized stream of data, Feature collections...).";
//    return;
//  }

//  const wrldcv_core::Network* srcData      = input.at(0);

//  std::string frameName = wrldcv_basic_types::NameObservation::getValue(*srcData, "frameName");
//  output.addObservation(new wrldcv_basic_types::NameObservation("frameName", tp_utils::currentTimeMS(), frameName));

//  //Assuming that we are processing data from the survey_app the front facing camera chould be
//  //available, see: survey_app/wrldcv_qt/src/processes/CameraProcess.cpp
//  wrldcv_basic_types::ImageObservation* image=nullptr;
//  srcData->observationCast("mainCamera", image);

//  if(!image)
//  {
//    error = "ORBFeatureExtractorProcess::run failed to find mainCamera image.";
//    return;
//  }

//  FeatureMatchObservation* featureCollection =
//      new FeatureMatchObservation("2dFeatures",
//                                  tp_utils::currentTimeMS(),
//                                  wrldcv_basic_types::FeatureCollectionType::features2D);

//  //Find some features
//  // https://docs.opencv.org/3.0-beta/doc/tutorials/features2d/akaze_tracking/akaze_tracking.html
//  {
//    wrldcv_basic_types::Frame* frame = new wrldcv_basic_types::Frame();
//    frame->name  = frameName;
//    frame->frame = 0;
//    frame->size  = {image->image.width, image->image.height};
//    featureCollection->addFrame(frame);

//    glm::vec2 f = {2.0f/float(frame->size.x), -2.0f/float(frame->size.y)};

//    cv::Mat cvImage;
//    convertImage(image->image, cvImage);

//    std::unordered_map<glm::ivec2, glm::vec4> featureColors;

//    //== Extract the features ======================================================================
//    switch(d->mode)
//    {
//    case Mode::DetectAndExtract: //-- DetectAndExtract ---------------------------------------------
//    {
//      //Find and extract feature descriptors from the source image.
//      d->extractor->detectAndCompute(cvImage,
//                                     cv::noArray(),
//                                     featureCollection->kp,
//                                     featureCollection->desc);

//      break;
//    }

//    case Mode::Extract: //-- Extract ---------------------------------------------------------------
//    {
//      //Find all wrldcv_basic_types::FeatureCollectionObservation that have the same frame sizes
//      //and extract feature descriptors for them from the source image.

//      glm::ivec2 frameSize = frame->size;
//      tp_quad_tree::QuadTreeInt coords(0, frameSize.x, 0, frameSize.y, 30);
//      std::vector<const OpenCVFeature*> newFeatures;

//      for(int i=1; i<int(input.size()); i++)
//      {
//        const wrldcv_core::Network* featuresNetwork = input.at(i);

//        int maxFeatures = d->maxFeatures;
//        featuresNetwork->observationCast<FeatureMatchObservation*>
//            ([frameSize, maxFeatures, &coords, &newFeatures, &error](FeatureMatchObservation* obs)
//        {
//          if(int(newFeatures.size())>=maxFeatures)
//            return;

//          const wrldcv_basic_types::Frame* frame = obs->frame(0);

//          if(!frame)
//          {
//            error = "Failed to find frame for: " + obs->name();
//            return;
//          }

//          if(frame->size != frameSize)
//            return;

//          for(const wrldcv_basic_types::Feature* feature : obs->features())
//          {
//            if(int(newFeatures.size())>=maxFeatures)
//              break;

//            if(feature->frame == 0)
//            {
//              const OpenCVFeature* feat = dynamic_cast<const OpenCVFeature*>(feature);
//              if(feat)
//              {
//                int distSQ = feat->isMatch?1:4;
//                distSQ=distSQ*distSQ;
//                int max = distSQ;
//                tp_quad_tree::QuadTreeInt::Coord c(feat->coord2D.x, feat->coord2D.y);
//                coords.closestPoint(c, distSQ);

//                if(distSQ==max)
//                {
//                  coords.addCoord(c);
//                  newFeatures.push_back(feat);
//                }
//              }
//            }
//          }
//        });
//      }

//      featureCollection->kp.reserve(newFeatures.size());
//      for(const OpenCVFeature* i : newFeatures)
//      {
//        cv::KeyPoint kp = i->kp;
//        kp.pt.x = i->coord2D.x;
//        kp.pt.y = i->coord2D.y;
//        featureCollection->kp.push_back(kp);
//        featureColors[i->coord2D] = i->color;
//      }

//      d->extractor->compute(cvImage,
//                            featureCollection->kp,
//                            featureCollection->desc);

//      break;
//    }
//    }


//    //== Populate our Feature structure from the OpenCV data =======================================
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

//  output.addObservation(featureCollection);
//}

//}
