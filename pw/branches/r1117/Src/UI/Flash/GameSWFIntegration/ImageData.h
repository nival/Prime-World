#pragma once

#include "swf_parse.h"

namespace Render
{
  struct IBitmapInfo;
}

namespace image
{
  struct rgba;
}

namespace flash
{

class Movie;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ImageData
{
  ImageData() : bitmapInfo(0) {} 

  void Load( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, bool repeatable );

  Render::IBitmapInfo* GetBitmapInfo() const { return bitmapInfo; }


private:

  void LoadJPEG( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, bool repeatable );
  void LoadJPEG3( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, bool repeatable );
  void LoadLOSSLESS2( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, bool withAlpha, bool repeatable );

  void LoadLOSSLESS2_8( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, int width, int height, image::rgba* _image );
  void LoadLOSSLESS2_16( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, int width, int height, image::rgba* _image, bool withAlpha );
  void LoadLOSSLESS2_32( Movie* movie, SwfStreamReader & streamReader, TagInfo & tagInfo, int width, int height, image::rgba* _image, bool withAlpha );

  Strong<Render::IBitmapInfo> bitmapInfo;
};

} //namespace flash
