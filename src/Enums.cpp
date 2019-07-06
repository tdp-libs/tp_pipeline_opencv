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

//##################################################################################################
const std::vector<std::string>& colorConversionCodes()
{
  static const std::vector<std::string> modes
  {
    "COLOR_BGR2BGRA",
    "COLOR_RGB2RGBA",
    "COLOR_BGRA2BGR",
    "COLOR_RGBA2RGB",
    "COLOR_BGR2RGBA",
    "COLOR_RGB2BGRA",
    "COLOR_RGBA2BGR",
    "COLOR_BGRA2RGB",
    "COLOR_BGR2RGB",
    "COLOR_RGB2BGR",
    "COLOR_BGRA2RGBA",
    "COLOR_RGBA2BGRA",
    "COLOR_BGR2GRAY",
    "COLOR_RGB2GRAY",
    "COLOR_GRAY2BGR",
    "COLOR_GRAY2RGB",
    "COLOR_GRAY2BGRA",
    "COLOR_GRAY2RGBA",
    "COLOR_BGRA2GRAY",
    "COLOR_RGBA2GRAY",
    "COLOR_BGR2BGR565",
    "COLOR_RGB2BGR565",
    "COLOR_BGR5652BGR",
    "COLOR_BGR5652RGB",
    "COLOR_BGRA2BGR565",
    "COLOR_RGBA2BGR565",
    "COLOR_BGR5652BGRA",
    "COLOR_BGR5652RGBA",
    "COLOR_GRAY2BGR565",
    "COLOR_BGR5652GRAY",
    "COLOR_BGR2BGR555",
    "COLOR_RGB2BGR555",
    "COLOR_BGR5552BGR",
    "COLOR_BGR5552RGB",
    "COLOR_BGRA2BGR555",
    "COLOR_RGBA2BGR555",
    "COLOR_BGR5552BGRA",
    "COLOR_BGR5552RGBA",
    "COLOR_GRAY2BGR555",
    "COLOR_BGR5552GRAY",
    "COLOR_BGR2XYZ",
    "COLOR_RGB2XYZ",
    "COLOR_XYZ2BGR",
    "COLOR_XYZ2RGB",
    "COLOR_BGR2YCrCb",
    "COLOR_RGB2YCrCb",
    "COLOR_YCrCb2BGR",
    "COLOR_YCrCb2RGB",
    "COLOR_BGR2HSV",
    "COLOR_RGB2HSV",
    "COLOR_BGR2Lab",
    "COLOR_RGB2Lab",
    "COLOR_BGR2Luv",
    "COLOR_RGB2Luv",
    "COLOR_BGR2HLS",
    "COLOR_RGB2HLS",
    "COLOR_HSV2BGR",
    "COLOR_HSV2RGB",
    "COLOR_Lab2BGR",
    "COLOR_Lab2RGB",
    "COLOR_Luv2BGR",
    "COLOR_Luv2RGB",
    "COLOR_HLS2BGR",
    "COLOR_HLS2RGB",
    "COLOR_BGR2HSV_FULL",
    "COLOR_RGB2HSV_FULL",
    "COLOR_BGR2HLS_FULL",
    "COLOR_RGB2HLS_FULL",
    "COLOR_HSV2BGR_FULL",
    "COLOR_HSV2RGB_FULL",
    "COLOR_HLS2BGR_FULL",
    "COLOR_HLS2RGB_FULL",
    "COLOR_LBGR2Lab",
    "COLOR_LRGB2Lab",
    "COLOR_LBGR2Luv",
    "COLOR_LRGB2Luv",
    "COLOR_Lab2LBGR",
    "COLOR_Lab2LRGB",
    "COLOR_Luv2LBGR",
    "COLOR_Luv2LRGB",
    "COLOR_BGR2YUV",
    "COLOR_RGB2YUV",
    "COLOR_YUV2BGR",
    "COLOR_YUV2RGB",
    "COLOR_YUV2RGB_NV12",
    "COLOR_YUV2BGR_NV12",
    "COLOR_YUV2RGB_NV21",
    "COLOR_YUV2BGR_NV21",
    "COLOR_YUV420sp2RGB",
    "COLOR_YUV420sp2BGR",
    "COLOR_YUV2RGBA_NV12",
    "COLOR_YUV2BGRA_NV12",
    "COLOR_YUV2RGBA_NV21",
    "COLOR_YUV2BGRA_NV21",
    "COLOR_YUV420sp2RGBA",
    "COLOR_YUV420sp2BGRA",
    "COLOR_YUV2RGB_YV12",
    "COLOR_YUV2BGR_YV12",
    "COLOR_YUV2RGB_IYUV",
    "COLOR_YUV2BGR_IYUV",
    "COLOR_YUV2RGB_I420",
    "COLOR_YUV2BGR_I420",
    "COLOR_YUV420p2RGB",
    "COLOR_YUV420p2BGR",
    "COLOR_YUV2RGBA_YV12",
    "COLOR_YUV2BGRA_YV12",
    "COLOR_YUV2RGBA_IYUV",
    "COLOR_YUV2BGRA_IYUV",
    "COLOR_YUV2RGBA_I420",
    "COLOR_YUV2BGRA_I420",
    "COLOR_YUV420p2RGBA",
    "COLOR_YUV420p2BGRA",
    "COLOR_YUV2GRAY_420",
    "COLOR_YUV2GRAY_NV21",
    "COLOR_YUV2GRAY_NV12",
    "COLOR_YUV2GRAY_YV12",
    "COLOR_YUV2GRAY_IYUV",
    "COLOR_YUV2GRAY_I420",
    "COLOR_YUV420sp2GRAY",
    "COLOR_YUV420p2GRAY",
    "COLOR_YUV2RGB_UYVY",
    "COLOR_YUV2BGR_UYVY",
    "COLOR_YUV2RGB_Y422",
    "COLOR_YUV2BGR_Y422",
    "COLOR_YUV2RGB_UYNV",
    "COLOR_YUV2BGR_UYNV",
    "COLOR_YUV2RGBA_UYVY",
    "COLOR_YUV2BGRA_UYVY",
    "COLOR_YUV2RGBA_Y422",
    "COLOR_YUV2BGRA_Y422",
    "COLOR_YUV2RGBA_UYNV",
    "COLOR_YUV2BGRA_UYNV",
    "COLOR_YUV2RGB_YUY2",
    "COLOR_YUV2BGR_YUY2",
    "COLOR_YUV2RGB_YVYU",
    "COLOR_YUV2BGR_YVYU",
    "COLOR_YUV2RGB_YUYV",
    "COLOR_YUV2BGR_YUYV",
    "COLOR_YUV2RGB_YUNV",
    "COLOR_YUV2BGR_YUNV",
    "COLOR_YUV2RGBA_YUY2",
    "COLOR_YUV2BGRA_YUY2",
    "COLOR_YUV2RGBA_YVYU",
    "COLOR_YUV2BGRA_YVYU",
    "COLOR_YUV2RGBA_YUYV",
    "COLOR_YUV2BGRA_YUYV",
    "COLOR_YUV2RGBA_YUNV",
    "COLOR_YUV2BGRA_YUNV",
    "COLOR_YUV2GRAY_UYVY",
    "COLOR_YUV2GRAY_YUY2",
    "COLOR_YUV2GRAY_Y422",
    "COLOR_YUV2GRAY_UYNV",
    "COLOR_YUV2GRAY_YVYU",
    "COLOR_YUV2GRAY_YUYV",
    "COLOR_YUV2GRAY_YUNV",
    "COLOR_RGBA2mRGBA",
    "COLOR_mRGBA2RGBA",
    "COLOR_RGB2YUV_I420",
    "COLOR_BGR2YUV_I420",
    "COLOR_RGB2YUV_IYUV",
    "COLOR_BGR2YUV_IYUV",
    "COLOR_RGBA2YUV_I420",
    "COLOR_BGRA2YUV_I420",
    "COLOR_RGBA2YUV_IYUV",
    "COLOR_BGRA2YUV_IYUV",
    "COLOR_RGB2YUV_YV12",
    "COLOR_BGR2YUV_YV12",
    "COLOR_RGBA2YUV_YV12",
    "COLOR_BGRA2YUV_YV12",
    "COLOR_BayerBG2BGR",
    "COLOR_BayerGB2BGR",
    "COLOR_BayerRG2BGR",
    "COLOR_BayerGR2BGR",
    "COLOR_BayerBG2RGB",
    "COLOR_BayerGB2RGB",
    "COLOR_BayerRG2RGB",
    "COLOR_BayerGR2RGB",
    "COLOR_BayerBG2GRAY",
    "COLOR_BayerGB2GRAY",
    "COLOR_BayerRG2GRAY",
    "COLOR_BayerGR2GRAY",
    "COLOR_BayerBG2BGR_VNG",
    "COLOR_BayerGB2BGR_VNG",
    "COLOR_BayerRG2BGR_VNG",
    "COLOR_BayerGR2BGR_VNG",
    "COLOR_BayerBG2RGB_VNG",
    "COLOR_BayerGB2RGB_VNG",
    "COLOR_BayerRG2RGB_VNG",
    "COLOR_BayerGR2RGB_VNG",
    "COLOR_BayerBG2BGR_EA",
    "COLOR_BayerGB2BGR_EA",
    "COLOR_BayerRG2BGR_EA",
    "COLOR_BayerGR2BGR_EA",
    "COLOR_BayerBG2RGB_EA",
    "COLOR_BayerGB2RGB_EA",
    "COLOR_BayerRG2RGB_EA",
    "COLOR_BayerGR2RGB_EA"
  };

  return modes;
}

//##################################################################################################
cv::ColorConversionCodes colorConversionCodeFromString(const std::string& colorConversionCodeString)
{
  if(colorConversionCodeString == "COLOR_BGR2BGRA")       return cv::COLOR_BGR2BGRA;
  if(colorConversionCodeString == "COLOR_RGB2RGBA")       return cv::COLOR_RGB2RGBA;
  if(colorConversionCodeString == "COLOR_BGRA2BGR")       return cv::COLOR_BGRA2BGR;
  if(colorConversionCodeString == "COLOR_RGBA2RGB")       return cv::COLOR_RGBA2RGB;
  if(colorConversionCodeString == "COLOR_BGR2RGBA")       return cv::COLOR_BGR2RGBA;
  if(colorConversionCodeString == "COLOR_RGB2BGRA")       return cv::COLOR_RGB2BGRA;
  if(colorConversionCodeString == "COLOR_RGBA2BGR")       return cv::COLOR_RGBA2BGR;
  if(colorConversionCodeString == "COLOR_BGRA2RGB")       return cv::COLOR_BGRA2RGB;
  if(colorConversionCodeString == "COLOR_BGR2RGB")        return cv::COLOR_BGR2RGB;
  if(colorConversionCodeString == "COLOR_RGB2BGR")        return cv::COLOR_RGB2BGR;
  if(colorConversionCodeString == "COLOR_BGRA2RGBA")      return cv::COLOR_BGRA2RGBA;
  if(colorConversionCodeString == "COLOR_RGBA2BGRA")      return cv::COLOR_RGBA2BGRA;
  if(colorConversionCodeString == "COLOR_BGR2GRAY")       return cv::COLOR_BGR2GRAY;
  if(colorConversionCodeString == "COLOR_RGB2GRAY")       return cv::COLOR_RGB2GRAY;
  if(colorConversionCodeString == "COLOR_GRAY2BGR")       return cv::COLOR_GRAY2BGR;
  if(colorConversionCodeString == "COLOR_GRAY2RGB")       return cv::COLOR_GRAY2RGB;
  if(colorConversionCodeString == "COLOR_GRAY2BGRA")      return cv::COLOR_GRAY2BGRA;
  if(colorConversionCodeString == "COLOR_GRAY2RGBA")      return cv::COLOR_GRAY2RGBA;
  if(colorConversionCodeString == "COLOR_BGRA2GRAY")      return cv::COLOR_BGRA2GRAY;
  if(colorConversionCodeString == "COLOR_RGBA2GRAY")      return cv::COLOR_RGBA2GRAY;
  if(colorConversionCodeString == "COLOR_BGR2BGR565")     return cv::COLOR_BGR2BGR565;
  if(colorConversionCodeString == "COLOR_RGB2BGR565")     return cv::COLOR_RGB2BGR565;
  if(colorConversionCodeString == "COLOR_BGR5652BGR")     return cv::COLOR_BGR5652BGR;
  if(colorConversionCodeString == "COLOR_BGR5652RGB")     return cv::COLOR_BGR5652RGB;
  if(colorConversionCodeString == "COLOR_BGRA2BGR565")    return cv::COLOR_BGRA2BGR565;
  if(colorConversionCodeString == "COLOR_RGBA2BGR565")    return cv::COLOR_RGBA2BGR565;
  if(colorConversionCodeString == "COLOR_BGR5652BGRA")    return cv::COLOR_BGR5652BGRA;
  if(colorConversionCodeString == "COLOR_BGR5652RGBA")    return cv::COLOR_BGR5652RGBA;
  if(colorConversionCodeString == "COLOR_GRAY2BGR565")    return cv::COLOR_GRAY2BGR565;
  if(colorConversionCodeString == "COLOR_BGR5652GRAY")    return cv::COLOR_BGR5652GRAY;
  if(colorConversionCodeString == "COLOR_BGR2BGR555")     return cv::COLOR_BGR2BGR555;
  if(colorConversionCodeString == "COLOR_RGB2BGR555")     return cv::COLOR_RGB2BGR555;
  if(colorConversionCodeString == "COLOR_BGR5552BGR")     return cv::COLOR_BGR5552BGR;
  if(colorConversionCodeString == "COLOR_BGR5552RGB")     return cv::COLOR_BGR5552RGB;
  if(colorConversionCodeString == "COLOR_BGRA2BGR555")    return cv::COLOR_BGRA2BGR555;
  if(colorConversionCodeString == "COLOR_RGBA2BGR555")    return cv::COLOR_RGBA2BGR555;
  if(colorConversionCodeString == "COLOR_BGR5552BGRA")    return cv::COLOR_BGR5552BGRA;
  if(colorConversionCodeString == "COLOR_BGR5552RGBA")    return cv::COLOR_BGR5552RGBA;
  if(colorConversionCodeString == "COLOR_GRAY2BGR555")    return cv::COLOR_GRAY2BGR555;
  if(colorConversionCodeString == "COLOR_BGR5552GRAY")    return cv::COLOR_BGR5552GRAY;
  if(colorConversionCodeString == "COLOR_BGR2XYZ")        return cv::COLOR_BGR2XYZ;
  if(colorConversionCodeString == "COLOR_RGB2XYZ")        return cv::COLOR_RGB2XYZ;
  if(colorConversionCodeString == "COLOR_XYZ2BGR")        return cv::COLOR_XYZ2BGR;
  if(colorConversionCodeString == "COLOR_XYZ2RGB")        return cv::COLOR_XYZ2RGB;
  if(colorConversionCodeString == "COLOR_BGR2YCrCb")      return cv::COLOR_BGR2YCrCb;
  if(colorConversionCodeString == "COLOR_RGB2YCrCb")      return cv::COLOR_RGB2YCrCb;
  if(colorConversionCodeString == "COLOR_YCrCb2BGR")      return cv::COLOR_YCrCb2BGR;
  if(colorConversionCodeString == "COLOR_YCrCb2RGB")      return cv::COLOR_YCrCb2RGB;
  if(colorConversionCodeString == "COLOR_BGR2HSV")        return cv::COLOR_BGR2HSV;
  if(colorConversionCodeString == "COLOR_RGB2HSV")        return cv::COLOR_RGB2HSV;
  if(colorConversionCodeString == "COLOR_BGR2Lab")        return cv::COLOR_BGR2Lab;
  if(colorConversionCodeString == "COLOR_RGB2Lab")        return cv::COLOR_RGB2Lab;
  if(colorConversionCodeString == "COLOR_BGR2Luv")        return cv::COLOR_BGR2Luv;
  if(colorConversionCodeString == "COLOR_RGB2Luv")        return cv::COLOR_RGB2Luv;
  if(colorConversionCodeString == "COLOR_BGR2HLS")        return cv::COLOR_BGR2HLS;
  if(colorConversionCodeString == "COLOR_RGB2HLS")        return cv::COLOR_RGB2HLS;
  if(colorConversionCodeString == "COLOR_HSV2BGR")        return cv::COLOR_HSV2BGR;
  if(colorConversionCodeString == "COLOR_HSV2RGB")        return cv::COLOR_HSV2RGB;
  if(colorConversionCodeString == "COLOR_Lab2BGR")        return cv::COLOR_Lab2BGR;
  if(colorConversionCodeString == "COLOR_Lab2RGB")        return cv::COLOR_Lab2RGB;
  if(colorConversionCodeString == "COLOR_Luv2BGR")        return cv::COLOR_Luv2BGR;
  if(colorConversionCodeString == "COLOR_Luv2RGB")        return cv::COLOR_Luv2RGB;
  if(colorConversionCodeString == "COLOR_HLS2BGR")        return cv::COLOR_HLS2BGR;
  if(colorConversionCodeString == "COLOR_HLS2RGB")        return cv::COLOR_HLS2RGB;
  if(colorConversionCodeString == "COLOR_BGR2HSV_FULL")   return cv::COLOR_BGR2HSV_FULL;
  if(colorConversionCodeString == "COLOR_RGB2HSV_FULL")   return cv::COLOR_RGB2HSV_FULL;
  if(colorConversionCodeString == "COLOR_BGR2HLS_FULL")   return cv::COLOR_BGR2HLS_FULL;
  if(colorConversionCodeString == "COLOR_RGB2HLS_FULL")   return cv::COLOR_RGB2HLS_FULL;
  if(colorConversionCodeString == "COLOR_HSV2BGR_FULL")   return cv::COLOR_HSV2BGR_FULL;
  if(colorConversionCodeString == "COLOR_HSV2RGB_FULL")   return cv::COLOR_HSV2RGB_FULL;
  if(colorConversionCodeString == "COLOR_HLS2BGR_FULL")   return cv::COLOR_HLS2BGR_FULL;
  if(colorConversionCodeString == "COLOR_HLS2RGB_FULL")   return cv::COLOR_HLS2RGB_FULL;
  if(colorConversionCodeString == "COLOR_LBGR2Lab")       return cv::COLOR_LBGR2Lab;
  if(colorConversionCodeString == "COLOR_LRGB2Lab")       return cv::COLOR_LRGB2Lab;
  if(colorConversionCodeString == "COLOR_LBGR2Luv")       return cv::COLOR_LBGR2Luv;
  if(colorConversionCodeString == "COLOR_LRGB2Luv")       return cv::COLOR_LRGB2Luv;
  if(colorConversionCodeString == "COLOR_Lab2LBGR")       return cv::COLOR_Lab2LBGR;
  if(colorConversionCodeString == "COLOR_Lab2LRGB")       return cv::COLOR_Lab2LRGB;
  if(colorConversionCodeString == "COLOR_Luv2LBGR")       return cv::COLOR_Luv2LBGR;
  if(colorConversionCodeString == "COLOR_Luv2LRGB")       return cv::COLOR_Luv2LRGB;
  if(colorConversionCodeString == "COLOR_BGR2YUV")        return cv::COLOR_BGR2YUV;
  if(colorConversionCodeString == "COLOR_RGB2YUV")        return cv::COLOR_RGB2YUV;
  if(colorConversionCodeString == "COLOR_YUV2BGR")        return cv::COLOR_YUV2BGR;
  if(colorConversionCodeString == "COLOR_YUV2RGB")        return cv::COLOR_YUV2RGB;
  if(colorConversionCodeString == "COLOR_YUV2RGB_NV12")   return cv::COLOR_YUV2RGB_NV12;
  if(colorConversionCodeString == "COLOR_YUV2BGR_NV12")   return cv::COLOR_YUV2BGR_NV12;
  if(colorConversionCodeString == "COLOR_YUV2RGB_NV21")   return cv::COLOR_YUV2RGB_NV21;
  if(colorConversionCodeString == "COLOR_YUV2BGR_NV21")   return cv::COLOR_YUV2BGR_NV21;
  if(colorConversionCodeString == "COLOR_YUV420sp2RGB")   return cv::COLOR_YUV420sp2RGB;
  if(colorConversionCodeString == "COLOR_YUV420sp2BGR")   return cv::COLOR_YUV420sp2BGR;
  if(colorConversionCodeString == "COLOR_YUV2RGBA_NV12")  return cv::COLOR_YUV2RGBA_NV12;
  if(colorConversionCodeString == "COLOR_YUV2BGRA_NV12")  return cv::COLOR_YUV2BGRA_NV12;
  if(colorConversionCodeString == "COLOR_YUV2RGBA_NV21")  return cv::COLOR_YUV2RGBA_NV21;
  if(colorConversionCodeString == "COLOR_YUV2BGRA_NV21")  return cv::COLOR_YUV2BGRA_NV21;
  if(colorConversionCodeString == "COLOR_YUV420sp2RGBA")  return cv::COLOR_YUV420sp2RGBA;
  if(colorConversionCodeString == "COLOR_YUV420sp2BGRA")  return cv::COLOR_YUV420sp2BGRA;
  if(colorConversionCodeString == "COLOR_YUV2RGB_YV12")   return cv::COLOR_YUV2RGB_YV12;
  if(colorConversionCodeString == "COLOR_YUV2BGR_YV12")   return cv::COLOR_YUV2BGR_YV12;
  if(colorConversionCodeString == "COLOR_YUV2RGB_IYUV")   return cv::COLOR_YUV2RGB_IYUV;
  if(colorConversionCodeString == "COLOR_YUV2BGR_IYUV")   return cv::COLOR_YUV2BGR_IYUV;
  if(colorConversionCodeString == "COLOR_YUV2RGB_I420")   return cv::COLOR_YUV2RGB_I420;
  if(colorConversionCodeString == "COLOR_YUV2BGR_I420")   return cv::COLOR_YUV2BGR_I420;
  if(colorConversionCodeString == "COLOR_YUV420p2RGB")    return cv::COLOR_YUV420p2RGB;
  if(colorConversionCodeString == "COLOR_YUV420p2BGR")    return cv::COLOR_YUV420p2BGR;
  if(colorConversionCodeString == "COLOR_YUV2RGBA_YV12")  return cv::COLOR_YUV2RGBA_YV12;
  if(colorConversionCodeString == "COLOR_YUV2BGRA_YV12")  return cv::COLOR_YUV2BGRA_YV12;
  if(colorConversionCodeString == "COLOR_YUV2RGBA_IYUV")  return cv::COLOR_YUV2RGBA_IYUV;
  if(colorConversionCodeString == "COLOR_YUV2BGRA_IYUV")  return cv::COLOR_YUV2BGRA_IYUV;
  if(colorConversionCodeString == "COLOR_YUV2RGBA_I420")  return cv::COLOR_YUV2RGBA_I420;
  if(colorConversionCodeString == "COLOR_YUV2BGRA_I420")  return cv::COLOR_YUV2BGRA_I420;
  if(colorConversionCodeString == "COLOR_YUV420p2RGBA")   return cv::COLOR_YUV420p2RGBA;
  if(colorConversionCodeString == "COLOR_YUV420p2BGRA")   return cv::COLOR_YUV420p2BGRA;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_420")   return cv::COLOR_YUV2GRAY_420;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_NV21")  return cv::COLOR_YUV2GRAY_NV21;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_NV12")  return cv::COLOR_YUV2GRAY_NV12;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_YV12")  return cv::COLOR_YUV2GRAY_YV12;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_IYUV")  return cv::COLOR_YUV2GRAY_IYUV;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_I420")  return cv::COLOR_YUV2GRAY_I420;
  if(colorConversionCodeString == "COLOR_YUV420sp2GRAY")  return cv::COLOR_YUV420sp2GRAY;
  if(colorConversionCodeString == "COLOR_YUV420p2GRAY")   return cv::COLOR_YUV420p2GRAY;
  if(colorConversionCodeString == "COLOR_YUV2RGB_UYVY")   return cv::COLOR_YUV2RGB_UYVY;
  if(colorConversionCodeString == "COLOR_YUV2BGR_UYVY")   return cv::COLOR_YUV2BGR_UYVY;
  if(colorConversionCodeString == "COLOR_YUV2RGB_Y422")   return cv::COLOR_YUV2RGB_Y422;
  if(colorConversionCodeString == "COLOR_YUV2BGR_Y422")   return cv::COLOR_YUV2BGR_Y422;
  if(colorConversionCodeString == "COLOR_YUV2RGB_UYNV")   return cv::COLOR_YUV2RGB_UYNV;
  if(colorConversionCodeString == "COLOR_YUV2BGR_UYNV")   return cv::COLOR_YUV2BGR_UYNV;
  if(colorConversionCodeString == "COLOR_YUV2RGBA_UYVY")  return cv::COLOR_YUV2RGBA_UYVY;
  if(colorConversionCodeString == "COLOR_YUV2BGRA_UYVY")  return cv::COLOR_YUV2BGRA_UYVY;
  if(colorConversionCodeString == "COLOR_YUV2RGBA_Y422")  return cv::COLOR_YUV2RGBA_Y422;
  if(colorConversionCodeString == "COLOR_YUV2BGRA_Y422")  return cv::COLOR_YUV2BGRA_Y422;
  if(colorConversionCodeString == "COLOR_YUV2RGBA_UYNV")  return cv::COLOR_YUV2RGBA_UYNV;
  if(colorConversionCodeString == "COLOR_YUV2BGRA_UYNV")  return cv::COLOR_YUV2BGRA_UYNV;
  if(colorConversionCodeString == "COLOR_YUV2RGB_YUY2")   return cv::COLOR_YUV2RGB_YUY2;
  if(colorConversionCodeString == "COLOR_YUV2BGR_YUY2")   return cv::COLOR_YUV2BGR_YUY2;
  if(colorConversionCodeString == "COLOR_YUV2RGB_YVYU")   return cv::COLOR_YUV2RGB_YVYU;
  if(colorConversionCodeString == "COLOR_YUV2BGR_YVYU")   return cv::COLOR_YUV2BGR_YVYU;
  if(colorConversionCodeString == "COLOR_YUV2RGB_YUYV")   return cv::COLOR_YUV2RGB_YUYV;
  if(colorConversionCodeString == "COLOR_YUV2BGR_YUYV")   return cv::COLOR_YUV2BGR_YUYV;
  if(colorConversionCodeString == "COLOR_YUV2RGB_YUNV")   return cv::COLOR_YUV2RGB_YUNV;
  if(colorConversionCodeString == "COLOR_YUV2BGR_YUNV")   return cv::COLOR_YUV2BGR_YUNV;
  if(colorConversionCodeString == "COLOR_YUV2RGBA_YUY2")  return cv::COLOR_YUV2RGBA_YUY2;
  if(colorConversionCodeString == "COLOR_YUV2BGRA_YUY2")  return cv::COLOR_YUV2BGRA_YUY2;
  if(colorConversionCodeString == "COLOR_YUV2RGBA_YVYU")  return cv::COLOR_YUV2RGBA_YVYU;
  if(colorConversionCodeString == "COLOR_YUV2BGRA_YVYU")  return cv::COLOR_YUV2BGRA_YVYU;
  if(colorConversionCodeString == "COLOR_YUV2RGBA_YUYV")  return cv::COLOR_YUV2RGBA_YUYV;
  if(colorConversionCodeString == "COLOR_YUV2BGRA_YUYV")  return cv::COLOR_YUV2BGRA_YUYV;
  if(colorConversionCodeString == "COLOR_YUV2RGBA_YUNV")  return cv::COLOR_YUV2RGBA_YUNV;
  if(colorConversionCodeString == "COLOR_YUV2BGRA_YUNV")  return cv::COLOR_YUV2BGRA_YUNV;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_UYVY")  return cv::COLOR_YUV2GRAY_UYVY;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_YUY2")  return cv::COLOR_YUV2GRAY_YUY2;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_Y422")  return cv::COLOR_YUV2GRAY_Y422;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_UYNV")  return cv::COLOR_YUV2GRAY_UYNV;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_YVYU")  return cv::COLOR_YUV2GRAY_YVYU;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_YUYV")  return cv::COLOR_YUV2GRAY_YUYV;
  if(colorConversionCodeString == "COLOR_YUV2GRAY_YUNV")  return cv::COLOR_YUV2GRAY_YUNV;
  if(colorConversionCodeString == "COLOR_RGBA2mRGBA")     return cv::COLOR_RGBA2mRGBA;
  if(colorConversionCodeString == "COLOR_mRGBA2RGBA")     return cv::COLOR_mRGBA2RGBA;
  if(colorConversionCodeString == "COLOR_RGB2YUV_I420")   return cv::COLOR_RGB2YUV_I420;
  if(colorConversionCodeString == "COLOR_BGR2YUV_I420")   return cv::COLOR_BGR2YUV_I420;
  if(colorConversionCodeString == "COLOR_RGB2YUV_IYUV")   return cv::COLOR_RGB2YUV_IYUV;
  if(colorConversionCodeString == "COLOR_BGR2YUV_IYUV")   return cv::COLOR_BGR2YUV_IYUV;
  if(colorConversionCodeString == "COLOR_RGBA2YUV_I420")  return cv::COLOR_RGBA2YUV_I420;
  if(colorConversionCodeString == "COLOR_BGRA2YUV_I420")  return cv::COLOR_BGRA2YUV_I420;
  if(colorConversionCodeString == "COLOR_RGBA2YUV_IYUV")  return cv::COLOR_RGBA2YUV_IYUV;
  if(colorConversionCodeString == "COLOR_BGRA2YUV_IYUV")  return cv::COLOR_BGRA2YUV_IYUV;
  if(colorConversionCodeString == "COLOR_RGB2YUV_YV12")   return cv::COLOR_RGB2YUV_YV12;
  if(colorConversionCodeString == "COLOR_BGR2YUV_YV12")   return cv::COLOR_BGR2YUV_YV12;
  if(colorConversionCodeString == "COLOR_RGBA2YUV_YV12")  return cv::COLOR_RGBA2YUV_YV12;
  if(colorConversionCodeString == "COLOR_BGRA2YUV_YV12")  return cv::COLOR_BGRA2YUV_YV12;
  if(colorConversionCodeString == "COLOR_BayerBG2BGR")    return cv::COLOR_BayerBG2BGR;
  if(colorConversionCodeString == "COLOR_BayerGB2BGR")    return cv::COLOR_BayerGB2BGR;
  if(colorConversionCodeString == "COLOR_BayerRG2BGR")    return cv::COLOR_BayerRG2BGR;
  if(colorConversionCodeString == "COLOR_BayerGR2BGR")    return cv::COLOR_BayerGR2BGR;
  if(colorConversionCodeString == "COLOR_BayerBG2RGB")    return cv::COLOR_BayerBG2RGB;
  if(colorConversionCodeString == "COLOR_BayerGB2RGB")    return cv::COLOR_BayerGB2RGB;
  if(colorConversionCodeString == "COLOR_BayerRG2RGB")    return cv::COLOR_BayerRG2RGB;
  if(colorConversionCodeString == "COLOR_BayerGR2RGB")    return cv::COLOR_BayerGR2RGB;
  if(colorConversionCodeString == "COLOR_BayerBG2GRAY")   return cv::COLOR_BayerBG2GRAY;
  if(colorConversionCodeString == "COLOR_BayerGB2GRAY")   return cv::COLOR_BayerGB2GRAY;
  if(colorConversionCodeString == "COLOR_BayerRG2GRAY")   return cv::COLOR_BayerRG2GRAY;
  if(colorConversionCodeString == "COLOR_BayerGR2GRAY")   return cv::COLOR_BayerGR2GRAY;
  if(colorConversionCodeString == "COLOR_BayerBG2BGR_VNG")return cv::COLOR_BayerBG2BGR_VNG;
  if(colorConversionCodeString == "COLOR_BayerGB2BGR_VNG")return cv::COLOR_BayerGB2BGR_VNG;
  if(colorConversionCodeString == "COLOR_BayerRG2BGR_VNG")return cv::COLOR_BayerRG2BGR_VNG;
  if(colorConversionCodeString == "COLOR_BayerGR2BGR_VNG")return cv::COLOR_BayerGR2BGR_VNG;
  if(colorConversionCodeString == "COLOR_BayerBG2RGB_VNG")return cv::COLOR_BayerBG2RGB_VNG;
  if(colorConversionCodeString == "COLOR_BayerGB2RGB_VNG")return cv::COLOR_BayerGB2RGB_VNG;
  if(colorConversionCodeString == "COLOR_BayerRG2RGB_VNG")return cv::COLOR_BayerRG2RGB_VNG;
  if(colorConversionCodeString == "COLOR_BayerGR2RGB_VNG")return cv::COLOR_BayerGR2RGB_VNG;
  if(colorConversionCodeString == "COLOR_BayerBG2BGR_EA") return cv::COLOR_BayerBG2BGR_EA;
  if(colorConversionCodeString == "COLOR_BayerGB2BGR_EA") return cv::COLOR_BayerGB2BGR_EA;
  if(colorConversionCodeString == "COLOR_BayerRG2BGR_EA") return cv::COLOR_BayerRG2BGR_EA;
  if(colorConversionCodeString == "COLOR_BayerGR2BGR_EA") return cv::COLOR_BayerGR2BGR_EA;
  if(colorConversionCodeString == "COLOR_BayerBG2RGB_EA") return cv::COLOR_BayerBG2RGB_EA;
  if(colorConversionCodeString == "COLOR_BayerGB2RGB_EA") return cv::COLOR_BayerGB2RGB_EA;
  if(colorConversionCodeString == "COLOR_BayerRG2RGB_EA") return cv::COLOR_BayerRG2RGB_EA;
  if(colorConversionCodeString == "COLOR_BayerGR2RGB_EA") return cv::COLOR_BayerGR2RGB_EA;
  return cv::COLOR_BGR2BGRA;
}



//##################################################################################################
const std::vector<std::string>& thresholdTypes()
{
  static const std::vector<std::string> thresholdTypes
  {
    "THRESH_BINARY",
    "THRESH_BINARY_INV",
    "THRESH_TRUNC",
    "THRESH_TOZERO",
    "THRESH_TOZERO_INV",
    "THRESH_MASK",
    "THRESH_OTSU",
    "THRESH_TRIANGLE"
  };

  return thresholdTypes;
}

//##################################################################################################
cv::ThresholdTypes thresholdTypeFromString(const std::string& thresholdTypeString)
{
  if(thresholdTypeString == "THRESH_BINARY")     return cv::THRESH_BINARY;
  if(thresholdTypeString == "THRESH_BINARY_INV") return cv::THRESH_BINARY_INV;
  if(thresholdTypeString == "THRESH_TRUNC")      return cv::THRESH_TRUNC;
  if(thresholdTypeString == "THRESH_TOZERO")     return cv::THRESH_TOZERO;
  if(thresholdTypeString == "THRESH_TOZERO_INV") return cv::THRESH_TOZERO_INV;
  if(thresholdTypeString == "THRESH_MASK")       return cv::THRESH_MASK;
  if(thresholdTypeString == "THRESH_OTSU")       return cv::THRESH_OTSU;
  if(thresholdTypeString == "THRESH_TRIANGLE")   return cv::THRESH_TRIANGLE;
  return cv::THRESH_BINARY;
}

//##################################################################################################
const std::vector<std::string>& depths()
{
  static const std::vector<std::string> depths
  {
    "CV_8U",
    "CV_8S",
    "CV_16U",
    "CV_16S",
    "CV_32S",
    "CV_32F",
    "CV_64F"
  };

  return depths;
}

//##################################################################################################
int depthFromString(const std::string& depthString)
{
  if(depthString == "CV_8U")
    return CV_8U;

  if(depthString == "CV_8S")
    return CV_8S;

  if(depthString == "CV_16U")
    return CV_16U;

  if(depthString == "CV_16S")
    return CV_16S;

  if(depthString == "CV_32S")
    return CV_32S;

  if(depthString == "CV_32F")
    return CV_32F;

  if(depthString == "CV_64F")
    return CV_64F;

  return CV_8U;
}



//##################################################################################################
const std::vector<std::string>& borderTypes()
{
  static const std::vector<std::string> borderTypes
  {
    "BORDER_CONSTANT",
    "BORDER_REPLICATE",
    "BORDER_REFLECT",
    "BORDER_WRAP",
    "BORDER_REFLECT_101",
    "BORDER_TRANSPARENT",
    "BORDER_REFLECT101",
    "BORDER_DEFAULT",
    "BORDER_ISOLATED"
  };

  return borderTypes;
}

//##################################################################################################
cv::BorderTypes borderTypeFromString(const std::string& borderTypeString)
{
  if(borderTypeString == "BORDER_CONSTANT")
    return cv::BorderTypes::BORDER_CONSTANT;

  if(borderTypeString == "BORDER_REPLICATE")
    return cv::BorderTypes::BORDER_REPLICATE;

  if(borderTypeString == "BORDER_REFLECT")
    return cv::BorderTypes::BORDER_REFLECT;

  if(borderTypeString == "BORDER_WRAP")
    return cv::BorderTypes::BORDER_WRAP;

  if(borderTypeString == "BORDER_REFLECT_101")
    return cv::BorderTypes::BORDER_REFLECT_101;

  if(borderTypeString == "BORDER_TRANSPARENT")
    return cv::BorderTypes::BORDER_TRANSPARENT;

  if(borderTypeString == "BORDER_REFLECT101")
    return cv::BorderTypes::BORDER_REFLECT101;

  if(borderTypeString == "BORDER_DEFAULT")
    return cv::BorderTypes::BORDER_DEFAULT;

  if(borderTypeString == "BORDER_ISOLATED")
    return cv::BorderTypes::BORDER_ISOLATED;

  return cv::BorderTypes::BORDER_DEFAULT;
}

}
