#pragma once

namespace image
{
  struct rgba;
}

namespace Render
{

class UITextureAtlasItem : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( UITextureAtlasItem, BaseObjectST );

public:
	UITextureAtlasItem( int _size );
  ~UITextureAtlasItem();

  bool PlaceImage( unsigned char* data, int width, int height, CVec2& uv1, CVec2& uv2, bool swizzle ); 

  Texture2DRef GetTexture() { return texture; }

private:

  typedef nstl::vector<int> FreeSpace;
  FreeSpace freeSpace;
  int size;

  Texture2DRef texture;
};

} // namespace Render
