#pragma once

#include "texture.h"

namespace flash
{
  struct SWF_MATRIX;
  struct SWF_CXFORMWITHALPHA;
  struct SWF_RGBA;
  struct SWF_RECT;
  struct SWF_GRADIENT;
}

namespace image
{
  struct rgba;
}

namespace EFlashBlendMode
{
  enum Enum
  {
    NORMAL = 1, // in SWF Normal = 0 or 1

    LAYER = 2,
    MULTIPLY = 3,
    SCREEN = 4,
    LIGHTEN = 5,
    DARKEN = 6,
    _DIFFERENCE = 7,
    ADD = 8,
    SUBTRACT = 9,
    INVERT = 10,
    ALPHA = 11,
    ERASE = 12,
    OVERLAY = 13,
    HARDLIGHT = 14,

    SHADER = 15,
  };
}

namespace EBitmapWrapMode
{
  enum Enum
  {
    REPEAT,
    CLAMP
  };
};

namespace Render
{
  struct ShapeVertex
  {
    float x, y;
    Color color;
    float alignHelper;
  };

  struct FlashVertex
  {
    float x, y;
    float xShift, yShift;
    Color color;
    float aliasing; 
    float aliasingScale;
    CVec2 distanceUV;
    CVec2 textureUV;

    FlashVertex() : 
      x(0), y(0), xShift(0.f), yShift(0.f), color(0,0,0), aliasing(1.f), aliasingScale(0.f),
      distanceUV(0,0), textureUV(0,0)
    {}
  };

  _interface IBitmapInfo : public IBaseInterfaceST
  {
    NI_DECLARE_CLASS_1( IBitmapInfo, IBaseInterfaceST )

    virtual int GetWidth() const  = 0; 
    virtual int GetHeight() const  = 0;

    virtual const CVec2& GetUV1() const = 0;
    virtual const CVec2& GetUV2() const = 0;

    virtual IBitmapInfo* Clone() = 0;
    virtual void Draw( IBitmapInfo* source, const flash::SWF_MATRIX& _matrix, int x1, int y1, int x2, int y2 ) = 0;
  };

  _interface IFlashRenderer : public IBaseInterfaceST
  {
    NI_DECLARE_CLASS_1( IFlashRenderer, IBaseInterfaceST )

    virtual bool Initialize() = 0;
    virtual void Release() = 0;

    virtual void StartFrame() = 0;
    virtual void BeginQueue() = 0;
    virtual void EndQueue() = 0;

    virtual void BreakQueue() = 0;

    virtual void SetResolutionCoefs( float x, float y, float widthScale, float heightScale ) = 0;

    virtual void SetMatrix( const flash::SWF_MATRIX& _m ) = 0;
    virtual void SetColorTransform( const flash::SWF_CXFORMWITHALPHA& cx ) = 0;
    virtual void SetBlendMode( EFlashBlendMode::Enum blendMode ) = 0;

    virtual void SetFillStyleBitmap( IBitmapInfo* bi, const flash::SWF_MATRIX& m, EBitmapWrapMode::Enum wm, bool primary  ) = 0;

    virtual void DrawBitmap( IBitmapInfo* bi, float width, float height, int uniqueID, bool smoothing ) = 0;
    virtual void DrawBitmapScale9Grid( IBitmapInfo* bi, float width, float height, const flash::SWF_RECT& scale9Grid, float aspectX, float aspectY_, int uniqueID, bool smoothing ) = 0;
    virtual void DrawTriangleList( ShapeVertex* vertices, int count, int uniqueID ) = 0;
    virtual void DrawLineStrip( const nstl::vector<CVec2>& coords, int uniqueID ) = 0;

    virtual void SetMorph( float rate ) = 0;

    virtual void SetScale9Grid( const CVec4& constX, const CVec4& constY, const CVec4& trans ) = 0;
    virtual void ResetScale9Grid() = 0;

    virtual void SetLineWidth( float width ) = 0;
    virtual void SetLineColor( const flash::SWF_RGBA& color ) = 0;

    virtual void BeginDisplay(
      int viewport_x0, int viewport_y0,
      int viewport_width, int viewport_height,
      float x0, float x1, float y0, float y1,
      bool useScissorRect ) = 0;
    virtual void EndDisplay() = 0;

    virtual void BeginSubmitMask() = 0;
    virtual void EndSubmitMask() = 0;
    virtual void BeginUnSubmitMask() = 0;
    virtual void DisableMask() = 0;

    virtual void BeginColorMatrix( const SHMatrix& _colorMatrix, const CVec4& _addColor ) = 0;
    virtual void EndColorMatrix() = 0;

    virtual void RenderText( int _partID ) = 0;
    virtual void RenderTextBevel( bool withBevel, const flash::SWF_RGBA& color, Texture* fontTexture ) = 0;

    virtual IBitmapInfo* CreateBitmap( int width, int height ) = 0;
    virtual IBitmapInfo* CreateBitmapFromTexture( const Texture2DRef& _texture ) = 0;
    virtual IBitmapInfo* CreateBitmapInfoRgba( image::rgba* im, bool repeatable ) = 0;
    virtual IBitmapInfo* CreateBitmapFromFile( const nstl::string& filename ) = 0;
    virtual IBitmapInfo* CreateGradientBitmap( const flash::SWF_GRADIENT& gradient ) = 0;

    virtual void ClearCaches() = 0;

    virtual void DebugNextBatch() = 0;
  };

} // namespace Render
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
