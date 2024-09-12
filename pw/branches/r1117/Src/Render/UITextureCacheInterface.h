#pragma once

#include "../UI/Flash/GameSWFIntegration/SwfTypes.h"

namespace image
{
  struct rgba;
}

namespace flash
{
  struct SWF_GRADIENT;
}

namespace Render
{

_interface IUITextureCache : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IUITextureCache, IBaseInterfaceST )

  virtual Texture2DRef GetGradientTexture( const flash::SWF_GRADIENT& gradient ) = 0;
  virtual Texture2DRef PlaceImageToAtlas( unsigned char* data, int width, int height, CVec2& uv1, CVec2& uv2, bool swizzle ) = 0;
  virtual Texture2DRef PlaceImageToAtlas( image::rgba* source, CVec2& uv1, CVec2& uv2, bool repeatable ) = 0;
  virtual Texture2DRef PlaceTextureToAtlas( const nstl::string& source, CVec2& uv1, CVec2& uv2 ) = 0;
  virtual Texture2DRef PlaceTextureToAtlas( const Texture2DRef& source, CVec2& uv1, CVec2& uv2 ) = 0;
};

} // namespace Render
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
