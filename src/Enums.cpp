#include "tp_pipeline_opencv/Enums.h"

namespace tp_pipeline_opencv
{

//##################################################################################################
const std::vector<std::string>& morphShapes()
{
  static const std::vector<std::string> modes
  {
    "MORPH_RECT",
    "MORPH_CROSS",
    "MORPH_ELLIPSE"
  };

  return modes;
}

//##################################################################################################
cv::MorphShapes morphShapeFromString(const std::string& morphShapeString)
{
  if(morphShapeString == "MORPH_RECT")
    return cv::MORPH_RECT;

  if(morphShapeString == "MORPH_CROSS")
    return cv::MORPH_CROSS;

  if(morphShapeString == "MORPH_ELLIPSE")
    return cv::MORPH_ELLIPSE;

  return cv::MORPH_RECT;
}

//##################################################################################################
const std::vector<std::string>& morphTypes()
{
  static const std::vector<std::string> modes
  {
    "MORPH_ERODE",
    "MORPH_DILATE",
    "MORPH_OPEN",
    "MORPH_CLOSE",
    "MORPH_GRADIENT",
    "MORPH_TOPHAT",
    "MORPH_BLACKHAT",
    "MORPH_HITMISS"
  };

  return modes;
}

//##################################################################################################
cv::MorphTypes morphTypeFromString(const std::string& morphTypeString)
{
  if(morphTypeString == "MORPH_ERODE")
    return cv::MORPH_ERODE;

  if(morphTypeString == "MORPH_DILATE")
    return cv::MORPH_DILATE;

  if(morphTypeString == "MORPH_OPEN")
    return cv::MORPH_OPEN;

  if(morphTypeString == "MORPH_CLOSE")
    return cv::MORPH_CLOSE;

  if(morphTypeString == "MORPH_GRADIENT")
    return cv::MORPH_GRADIENT;

  if(morphTypeString == "MORPH_TOPHAT")
    return cv::MORPH_TOPHAT;

  if(morphTypeString == "MORPH_BLACKHAT")
    return cv::MORPH_BLACKHAT;

  if(morphTypeString == "MORPH_HITMISS")
    return cv::MORPH_HITMISS;

  return cv::MORPH_ERODE;
}

}
