#pragma once

#include "../UI/DBUI.h"

#include "uirenderer.h"
#include "FlashRenderer.h"
#include "UITextureCache.h"

namespace Render
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace E3DMode
{
  enum Enum
  {
    _2D,
    _3DNewBlock,
    _3D
  };
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const unsigned int MAX_DIP_LENGTH = 1024*16; //actually determines the max length of DIP
static const int QUAD_MAX_COUNT = 20000;

static const int QUAD_VERTEX_COUNT = 4;
static const int QUAD_PRIMITIVE_COUNT = 2;
static const int QUAD_INDEX_COUNT = 6;
static const unsigned int quadFirstTextOff = 0xFFFFFFFF;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class UIRenderer : public IUIRenderer, public Render::DeviceLostHandler
{
protected:
  UIRenderer();

public:
  ~UIRenderer();

  virtual bool Initialize();
  virtual void Release();

  virtual void StartFrame();

  virtual void PushCrop( const UIRect & cropRect );
  virtual void PushNoCrop();
  virtual void PopCrop();

  virtual void AddQuad( UIQuad & _quad, Render::BaseMaterial* _renderMaterial, const SMaterialParams & params );
  virtual void BeginFlashParts( int _startFlashElement );
  virtual void EndFlashParts( int _lastFlashElement );

  virtual void BeginText();
  virtual void AddTextQuad( UIQuad & _quad, const SMaterialParams & params );
  virtual void EndText( Render::BaseMaterial* _renderMaterial );

  virtual void SetViewMatrices( const SHMatrix & view, const SHMatrix & projection );
  virtual void SetWorldMatrix( const SHMatrix & world, ETransformMode::Enum transformMode, const CVec3 & pivot, float depthBias );
  virtual void ResetWorldMatrix();
  virtual void GetBillboardMatrix( SHMatrix * pCombined, const SHMatrix & world, ETransformMode::Enum transformMode, const CVec3 & pivot, float depthBias );
  virtual void GetRay( CVec3 * pOrigin, CVec3 * pDir, int sx, int sy );
  virtual float CalcDepth( const CVec3 & point );

  virtual void SetResolutionCoefs( const float x, const float y, const float widthScale, const float heightScale );
  virtual const CVec4& GetResolutionCoefs() const;

  virtual void SetFontTextureSize( const int width, const int height );

  virtual void BeginQueue();
  virtual void EndQueue();

  virtual void Render( ERenderWhat::Enum what, const Render::Texture2DRef& pMainRT0, const Render::Texture2DRef& pMainRT0Copy );

  virtual void PrepareRender();
  virtual void PrepareRenderFromFlash();
  virtual void RenderPart( int _partID, ERenderWhat::Enum what, bool alphaTest );
  virtual BaseMaterial* GetPartMaterial( int _partID, ERenderWhat::Enum what );

  virtual void SetSaturation( float _val, const CVec4& _color, bool _saturate );
  virtual bool ForbidSaturation( bool _forbid);

  virtual IFlashRenderer* GetFlashRenderer() { return flashRenderer; }
  virtual IUITextureCache* GetTextureCache() { return textureCache; }

  // From Render::DeviceLostHandler
  virtual void OnDeviceLost() {}
  virtual void OnDeviceReset() { StartFrame(); }

private:

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct SRenderPart
  {
    BaseMaterial* renderMaterial;
    CVec4 color1;
    CVec4 color2;
    CVec4 coefs;
    unsigned int quadFirst;
    unsigned int quadCount;

    bool flashElement;
    int firstFlashElement;
    int lastFlashElement;

    bool textInFlash;

    SRenderPart(
      BaseMaterial* _renderMaterial,
      unsigned int _quadFirst,	unsigned int _quadCount,
      const CVec4 & _color1, const CVec4 & _color2, const CVec4 & _coefs
      )
      : renderMaterial( _renderMaterial )
      , quadFirst( _quadFirst ), quadCount( _quadCount )
      , color1( _color1 ), color2( _color2 ), coefs( _coefs )
      , flashElement( false ), firstFlashElement( -1 ), lastFlashElement( -1 )
      , textInFlash( false )
    {
      NI_ASSERT( quadCount < MAX_DIP_LENGTH, "UIRenderer: Index buffer overflow #1!" );
    }

    SRenderPart( int _firstFlashElement, int _lastFlashElement )
      : renderMaterial( 0 )
      , quadFirst( 0 ), quadCount( 0 )
      , flashElement( true ), firstFlashElement( _firstFlashElement ), lastFlashElement( _lastFlashElement )
      , textInFlash( false )
    {
    }

    SRenderPart() : renderMaterial(0), quadFirst(0), quadCount(0), flashElement( false ), textInFlash( false )
    {
      NI_ALWAYS_ASSERT( "don't call me" );
    }

    const SRenderPart & operator =( const SRenderPart& _element )
    {
      NI_ALWAYS_ASSERT( "don't call me" ); return _element;
    }
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct VertexStride
  {
    float x;
    float y;
    float u;
    float v;
    float u2;
    float v2;
    Color color;
  };

  __declspec(align(16))
  struct QuadStride
  {
    VertexStride v0, v1, v2, v3;
  };

  struct RenderQueue
  {
    unsigned int quadCounter;
    QuadStride quadsQueue[QUAD_MAX_COUNT];
    unsigned int quadFirstText; //assigned in BeginText() and cleared in EndText()
    vector<SRenderPart> parts;
    int currentFlashPart;
    RenderQueue() : quadCounter(0), quadFirstText(quadFirstTextOff), currentFlashPart(-1) {}
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  bool CropQuadInternal( UIQuad & quad, const UIRect & cropRect );
  unsigned int AddQuadInternal( const UIQuad& _quad, const Color& _color );
  void RenderPart( const SRenderPart & part, bool alphaTest );
  RenderQueue& UIRenderer::GetQueue();

  Render::Color SaturateColor( const Render::Color& _color );

  struct Parts3DBlock
  {
    int       firstPart;
    int       size;
    SHMatrix  transform;
    float     forcedZ, forcedW;
    Parts3DBlock(int _firstPart = 0, int _size = 0, const SHMatrix & _transform = SHMatrix(CVec3(0, 0, 0))) :
    firstPart(_firstPart), size(_size), transform(_transform), forcedZ(0.0f), forcedW(1.0f) {}
  };

  //У нас нету мультимапы, поэтому сколхозим свою при помощи ключа
  struct SBlockKey
  {
    friend bool operator < (const SBlockKey & lhv, const SBlockKey & rhv);
    float depth;
    int random;
    SBlockKey() : depth(0), random(0) {}
    SBlockKey(float _depth, int _random = 0) : depth(_depth), random(_random) {}

    friend inline bool operator < (const SBlockKey & lhv, const SBlockKey & rhv)
    {
      if(lhv.depth < rhv.depth)
        return true;
      if(lhv.depth > rhv.depth)
        return false;
      return lhv.random < rhv.random;
    }
  };

  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  typedef map<SBlockKey, Parts3DBlock>  BlocksSorter; // depth -> Parts3DBlock

  vector<UIRect> cropRects;
  bool initialized;
  bool queeOverflowed;

  DipDescriptor dipDesc;
  DXVertexDeclarationRef pVDecl;
  DXIndexBufferRef  pIB;
  DXVertexBufferDynamicRef::Wrapped pVB;

  CVec4 fontTextureSize; 
  CVec4 resolutionCoefs;
  SHMatrix projMatrix;
  SHMatrix viewMatrix;
  SHMatrix invViewMatrix;
  SHMatrix projViewMatrix; 
  SHMatrix invProjViewMatrix;
  E3DMode::Enum mode;
  BlocksSorter blocksSorter;
  Parts3DBlock* current3DBlock;

  RenderQueue ques[2];
  RenderQueue& que2D;
  RenderQueue& que3D;

  float saturationValue;
  CVec4 saturationColor; 
  bool saturate;
  bool forbidSaturate;

  Strong<FlashRenderer> flashRenderer;
  Strong<UITextureCache> textureCache;
};

} // namespace Render
