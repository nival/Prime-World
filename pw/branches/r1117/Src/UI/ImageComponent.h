#pragma once

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "Render/texture.h"
#include "Render/uirenderer.h"
#include "System/2Darray.h"
#include "Defines.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{
  class BaseMaterial;
}

namespace UI
{

class ScreenLogicBase;


class ImageShape
{
  vector<char> data;
public:
  bool IsCorrect() const
  {
    return data.size() >= 8 && data[0] == 'S' && data[1] == 'H' && data[2] == 'P' && data[3] == ' ';
  }

  bool Set( const vector<char> & _data )
  {
    data = _data;
    return IsCorrect();
  }

  bool HitTest( int x, int y, int iw, int ih, const NDb::BaseUIMaterial* _material ) const;
  void FillBitmap( CArray2D<Render::Color> *pBitmap, int iw, int ih, const NDb::BaseUIMaterial* _material, const Render::Color & c0, const Render::Color & c1 ) const;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ImageComponent
{
  bool renderable;
  int skinTag;

  Rect	drawRect;
  Rect	cropRect;

  Render::Color color;
  int opacity;

  bool needUpdateStyle;

  Render::UIRenderMaterial material;

  Point imgUV;
  Point imgUVL;
  Point imgTileUV;
  Point imgTileUVL;
  Point extUV;
  Point extUVL;

  Render::SMaterialParams materialParams;
  void UpdateMaterialParams();

  CVec2	uvPoint, uvlPoint;
  CVec2	uvTile, uvlTile;

  Point textureSize, uvTextureSize, uvTileTextureSize;

  bool drawTop, drawBottom, drawLeft, drawRight;
  int hTiles, vTiles;

  bool ext;
  Point pivot;
  float angle;
  float scale;

  bool useShape;
  Render::UIRenderMaterial shapeMaterial;
  ImageShape shape;

public:
  ImageComponent();
  ~ImageComponent();

  void SetRenderable( bool _renderable ) { renderable = _renderable; }

  void SetDrawRect( const Rect & rect ) { drawRect = rect; needUpdateStyle = true; }
  void SetCropRect( const Rect & rect ) { cropRect = rect; needUpdateStyle = true; }

  void SetMaterialColor( const Render::Color & _color );
  void SetMaterialOpacity( int _opacity );
  void SetMaterialCoef3( float c3 );
  void SetMaterialCoef4( float c4 );

  // use only for non-tiled non-clipping images, like particles
  void SetExtended( const Point & _pivot, float _angle, float _scale );

  Render::UIRenderMaterial& GetRenderMaterial() { return material; }
  const NDb::BaseUIMaterial* GetMaterial() const { return material.GetDBMaterial(); }

  void SetImageTexture( const Render::Texture2DRef& _pTexture ); // Added by oleg

  bool SetImageMaterial( const NDb::BaseUIMaterial * _material, ScreenLogicBase * logicAsTexturePool, bool forceReload = false );
  bool SetImageMaterial( const string& _resourceName, ScreenLogicBase * logicAsTexturePool, bool forceReload = false );

  bool SetShapeMaterial( const NDb::BaseUIMaterial * _material );
  bool HitTest( int x, int y ) const;

  bool SetImageTextureFromShape( const Render::Color & c0, const Render::Color & c1 );

  const Point & GetTextureSize() { return textureSize; }

  void UpdateStyleTexture();

private:
  void DrawTile( const Point & _tlPoint, const Point & _brPoint, const CVec2 & scaleRectToMask, NDb::EUIImageDrawMode vertMode, NDb::EUIImageDrawMode horizMode );
  void DrawLine( const Point & _tlPoint, const Point & _brPoint, Point *tlPoint, Point *brPoint, CVec2 *uv, CVec2 *uvl, CVec2 *muv, CVec2 *muvl, const CVec2 & scaleRectToMask, NDb::EUIImageDrawMode horizMode );

  virtual void Update() {}
public:
  virtual void Render();
};


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////