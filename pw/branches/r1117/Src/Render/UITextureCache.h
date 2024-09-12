#pragma once

#include "UITextureCacheInterface.h"
//#include "../UI/Flash/GameSWFIntegration/SwfTypes.h"

namespace image
{
  struct rgba;
}

namespace flash
{
  struct SWF_GRADIENT;
}

template<> struct hash<flash::SWF_GRADIENT>
{
  size_t operator()(const flash::SWF_GRADIENT& _gradient ) const 
  { 
    unsigned int __h = 0; 

    nstl::vector<flash::SWF_GRADRECORD>::const_iterator it = _gradient.GradientRecords.begin();
    nstl::vector<flash::SWF_GRADRECORD>::const_iterator last = _gradient.GradientRecords.end();

    for (; it != last; ++it)
    {
      __h = 5 * __h + it->Color.r;
      __h = 5 * __h + it->Color.g;
      __h = 5 * __h + it->Color.b;
      __h = 5 * __h + it->Color.a;
      __h = 5 * __h + it->Ratio;
    }

    return __h;
  }
};

namespace Render
{

class UITextureAtlasItem;

class UITextureCache : public IUITextureCache, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( UITextureCache, IUITextureCache, BaseObjectST );

public:
	UITextureCache();
  ~UITextureCache();

  bool Release();

  virtual Texture2DRef GetGradientTexture( const flash::SWF_GRADIENT& gradient );
  virtual Texture2DRef PlaceImageToAtlas( unsigned char* data, int width, int height, CVec2& uv1, CVec2& uv2, bool swizzle );
  virtual Texture2DRef PlaceImageToAtlas( image::rgba* source, CVec2& uv1, CVec2& uv2, bool repeatable );
  virtual Texture2DRef PlaceTextureToAtlas( const nstl::string& source, CVec2& uv1, CVec2& uv2 );
  virtual Texture2DRef PlaceTextureToAtlas( const Texture2DRef& source, CVec2& uv1, CVec2& uv2 );

private:

  Texture2DRef CreateLinearGradient( const flash::SWF_GRADIENT& gradient );
  Texture2DRef CreateRadialGradient( const flash::SWF_GRADIENT& gradient );
  flash::SWF_RGBA SampleGradient( const flash::SWF_GRADIENT& gradient, int ratio );

  Texture2DRef CreateSimpleTexture( image::rgba* source, CVec2& uv1, CVec2& uv2 );
  Texture2DRef CreateClampedTexture( image::rgba* source, CVec2& uv1, CVec2& uv2, int maxSize );

  typedef nstl::hash_map<flash::SWF_GRADIENT, Texture2DRef> GradientTextures2;
  GradientTextures2 gradientTextures2;

  typedef nstl::list<Strong<UITextureAtlasItem>> Atlases; 
  Atlases atlases;
};

} // namespace Render
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
