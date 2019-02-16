//#include "wrldcv_opencv/processes/FeatureMatcherProcess.h"
//#include "wrldcv_opencv/observations/FeatureMatchObservation.h"

//#include "wrldcv_basic_types/observations/ImageObservation.h"
//#include "wrldcv_basic_types/observations/FeatureCollectionObservation.h"
//#include "wrldcv_basic_types/observations/NameObservation.h"

//#include "wrldcv_core/Network.h"

//#include "tp_utils/DebugUtils.h"
//#include "tp_utils/TimeUtils.h"

//#include <opencv2/features2d.hpp>

//namespace  wrldcv_opencv
//{
////##################################################################################################
//struct FeatureMatcherProcess::Private
//{
//  float maxDistance;
//  cv::Ptr<cv::DescriptorMatcher> matcher;

//  Private(float maxDistance_):
//    maxDistance(maxDistance_),
//    matcher(cv::DescriptorMatcher::create("BruteForce-Hamming"))
//  {
//    //-   `BruteForce` (it uses L2 )
//    //-   `BruteForce-L1`
//    //-   `BruteForce-Hamming`
//    //-   `BruteForce-Hamming(2)`
//    //-   `FlannBased`
//  }
//};

////##################################################################################################
//FeatureMatcherProcess::FeatureMatcherProcess(const std::string& description, float maxDistance):
//  wrldcv_core::AbstractProcess(description),
//  d(new Private(maxDistance))
//{

//}

////##################################################################################################
//FeatureMatcherProcess::~FeatureMatcherProcess()
//{
//  delete d;
//}

////##################################################################################################
//void FeatureMatcherProcess::run(std::string& error, const std::vector<const wrldcv_core::Network*>& input, wrldcv_core::Network& output)
//{
//  //We expect this input
//  // - Feature descriptors
//  // - Previous feature descriptors

//  //We produce this output
//  // - Filtered related features

//  if(input.size() != 2)
//  {
//    error = "MatchFeaturesStubProcess::run expects 2 inputs: (Feature descriptors, Previous feature descriptors).";
//    return;
//  }

//  const wrldcv_core::Network* currentFeatures = input.at(0);
//  const wrldcv_core::Network* prevFeatures    = input.at(1);

//  std::string frameName = wrldcv_basic_types::NameObservation::getValue(*currentFeatures, "frameName");
//  output.addObservation(new wrldcv_basic_types::NameObservation("frameName", tp_utils::currentTimeMS(), frameName));

//  //The 2D features from the current frame
//  FeatureMatchObservation* currentFeatureCollection;
//  currentFeatures->observationCast("2dFeatures", currentFeatureCollection);

//  if(!currentFeatureCollection)
//  {
//    error = "MatchFeaturesStubProcess::run Failed to find the feature collection for the current frame.";
//    return;
//  }

//  FeatureMatchObservation dummyPreviousFeatureCollection("2dFeatures",
//                                                         tp_utils::currentTimeMS(),
//                                                         wrldcv_basic_types::FeatureCollectionType::features2D);

//  //The 2D features from the previous frame
//  FeatureMatchObservation* previousFeatureCollection;
//  prevFeatures->observationCast("2dFeatures", previousFeatureCollection);

//  //On the first frame this will not exist.
//  if(!previousFeatureCollection)
//    previousFeatureCollection = &dummyPreviousFeatureCollection;

//  FeatureMatchObservation* featureCollection =
//      new FeatureMatchObservation("2DFeatureMatches",
//                                  tp_utils::currentTimeMS(),
//                                  wrldcv_basic_types::FeatureCollectionType::matches2D);

//  {
//    const wrldcv_basic_types::Frame*  currentFrameExisting =  currentFeatureCollection->frame(0);
//    const wrldcv_basic_types::Frame* previousFrameExisting = previousFeatureCollection->frame(0);

//    wrldcv_basic_types::Frame*  currentFrame = new wrldcv_basic_types::Frame();
//    wrldcv_basic_types::Frame* previousFrame = new wrldcv_basic_types::Frame();


//    currentFrame ->frame =  0;
//    previousFrame->frame = -1;

//    if(currentFrameExisting)
//    {
//      currentFrame->size = currentFrameExisting->size;
//      currentFrame->name = currentFrameExisting->name;
//    }

//    if(previousFrameExisting)
//    {
//      previousFrame->size = previousFrameExisting->size;
//      previousFrame->name = previousFrameExisting->name;
//    }
//    else
//      previousFrame->size = currentFrame->size;

//    featureCollection->addFrame(currentFrame);
//    featureCollection->addFrame(previousFrame);
//  }

//  std::unordered_map<int, std::unordered_map<int, int>> indexLookup;

//  //frame: 0=current frame, -1=previousFrame
//  auto addFeature =
//      [&indexLookup,
//      previousFeatureCollection,
//      currentFeatureCollection,
//      featureCollection](int frame, int index, const glm::vec4& color) -> int
//  {
//    std::unordered_map<int, int>& frameIndexes = indexLookup[frame];
//    auto it = frameIndexes.find(index);
//    if(it == frameIndexes.end())
//    {
//      FeatureMatchObservation* sourceFeatureCollection = ((frame == 0)?currentFeatureCollection:previousFeatureCollection);

//      int i = featureCollection->features().size();
//      OpenCVFeature* feature = new OpenCVFeature();
//      feature->isMatch = true;
//      OpenCVFeature* f = dynamic_cast<OpenCVFeature*>(sourceFeatureCollection->features().at(index));
//      if(f)
//        (*feature) = (*f);
//      feature->frame = frame;
//      feature->color = color;
//      featureCollection->addFeature(feature);
//      frameIndexes[index] = i;
//      return i;
//    }

//    return it->second;
//  };

//  auto addMatch = [featureCollection, addFeature](int indexPrev, int indexCurrent, float score, const glm::vec4& color)
//  {
//    wrldcv_basic_types::FeatureMatch* featureMatch = new wrldcv_basic_types::FeatureMatch();
//    featureMatch->score = score;
//    featureMatch->features.push_back(addFeature(-1, indexPrev, color));
//    featureMatch->features.push_back(addFeature(0, indexCurrent, color));
//    featureCollection->addFeatureMatch(featureMatch);
//  };

//  //Match some features
//  {
//    std::vector<cv::DMatch> matches;
//    d->matcher->match(previousFeatureCollection->desc,
//                      currentFeatureCollection->desc,
//                      matches);

//    std::sort(matches.begin(), matches.end());

//    const float maxDistance = d->maxDistance;
//    const int maxMatches = 5000;

//    //The indexes relate like this:
//    // m.queryIdx --> previousFeatureCollection
//    // m.trainIdx --> currentFeatureCollection
//    for(const cv::DMatch& m : matches)
//    {
//      if(int(featureCollection->featureMatches().size())>=maxMatches)
//        break;

//      if(m.distance>maxDistance)
//        break;

//      addMatch(m.queryIdx,
//               m.trainIdx,
//               1.0f - (m.distance/maxDistance),
//               previousFeatureCollection->features().at(m.queryIdx)->color);
//    }
//  }

//  output.addObservation(featureCollection);
//}

//}
