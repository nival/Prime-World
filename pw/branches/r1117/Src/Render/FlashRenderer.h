#pragma once

#include "../UI/Flash/GameSWFIntegration/SwfTypes.h"

#include "FlashRendererInterface.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{

class BaseMaterial;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class FlashRenderer : public IFlashRenderer, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( FlashRenderer, IFlashRenderer, BaseObjectST );

public:
	FlashRenderer();
  ~FlashRenderer();

  // from IFlashRenderer
  virtual bool Initialize();
  virtual void Release(); 

  virtual void StartFrame();
  virtual void BeginQueue();
  virtual void EndQueue();

  virtual void BreakQueue();

  virtual void Render( int _firstElement, int _lastElement, const Render::Texture2DRef& pMainRT0, const Render::Texture2DRef& pMainRT0Copy );

  virtual void SetResolutionCoefs( float x, float y, float widthScale, float heightScale );

  virtual void SetMatrix( const flash::SWF_MATRIX& _m );
  virtual void SetColorTransform( const flash::SWF_CXFORMWITHALPHA& cx );
  virtual void SetBlendMode( EFlashBlendMode::Enum blendMode );

  virtual void SetFillStyleBitmap( IBitmapInfo* bi, const flash::SWF_MATRIX& m, EBitmapWrapMode::Enum wm, bool primary );

  virtual void SetLineWidth( float width );
  virtual void SetLineColor( const flash::SWF_RGBA& color );

  // from gameswf::render_handler

  virtual IBitmapInfo* CreateBitmap( int width, int height );
  virtual IBitmapInfo* CreateBitmapFromTexture( const Texture2DRef& _texture );
  virtual IBitmapInfo* CreateBitmapInfoRgba( image::rgba* im, bool repeatable );
  virtual IBitmapInfo* CreateBitmapFromFile( const nstl::string& filename );
  virtual IBitmapInfo* CreateGradientBitmap( const flash::SWF_GRADIENT& gradient );

  virtual void	BeginDisplay(
    int viewport_x0, int viewport_y0,
    int viewport_width, int viewport_height,
    float x0, float x1, float y0, float y1,
    bool useScissorRect );
  virtual void	EndDisplay();

  virtual void DrawBitmap( IBitmapInfo* bi, float width, float height, int uniqueID, bool smoothing );
  virtual void DrawBitmapScale9Grid( IBitmapInfo* bi, float width, float height, const flash::SWF_RECT& scale9Grid, float aspectX, float aspectY, int uniqueID, bool smoothing );
  virtual void DrawTriangleList( ShapeVertex* vertices, int count, int uniqueID );
  virtual void DrawLineStrip( const nstl::vector<CVec2>& coords, int uniqueID );

  virtual void SetMorph( float rate );

  virtual void SetScale9Grid( const CVec4& constX, const CVec4& constY, const CVec4& trans );
  virtual void ResetScale9Grid();

  virtual void BeginSubmitMask();
  virtual void EndSubmitMask();
  virtual void BeginUnSubmitMask();
  virtual void DisableMask();

  virtual void BeginColorMatrix( const SHMatrix& _colorMatrix, const CVec4& _addColor );
  virtual void EndColorMatrix();

  virtual void RenderText( int _partID );
  virtual void RenderTextBevel( bool withBevel, const flash::SWF_RGBA& color, Texture* fontTexture );

  virtual void ClearCaches();

  virtual void DebugNextBatch();

private:

  struct BatchTexture
  {
    bool useDiffuse;
    bool scale9Grid;
    Texture2DRef texture;
    EBitmapWrapMode::Enum textureMode;
    CVec4 matrixRow1;
    CVec4 matrixRow2;
    bool smoothing;

    BatchTexture() :
      useDiffuse(false),
      scale9Grid(false),
      textureMode(EBitmapWrapMode::REPEAT),
      smoothing(true)
    {}
  };

  struct Batch
  {
    SHMatrix viewMatrix;
    SHMatrix modelMatrix;
    bool needChangeView;
    bool needChangeModelMatrix;

    bool needChandeCXForm;
    Render::HDRColor multColorCXF;
    Render::HDRColor addColorCXF;

    bool beginSubmitMask;
    bool endSubmitMask;
    bool beginUnsubmitMask;
    bool disbaleMask;

    DipDescriptor dip;

    bool isLine;

    float pixelScale;

    BatchTexture diffuse1;
    BatchTexture diffuse2;

    bool isText;
    bool hasBevel;
    Render::HDRColor bevelColor;
    int textPartID;

    bool morph;
    float morphRate;

    bool changeBlendMode;
    EFlashBlendMode::Enum blendMode;

    bool visible;

    bool colorMatrixBegin;
    bool colorMatrixEnd;
    SHMatrix colorMatrix;
    CVec4 colorAdd;

    bool debug;

    bool useScale9Grid;
    bool clearScale9Grid;
    CVec4 scaleConstX;
    CVec4 scaleConstY;
    CVec4 transScale9;

    void (FlashRenderer::*prepareFunc)( const Batch& batch );

    void Clear()
    {
      colorMatrixBegin = false;
      colorMatrixEnd = false;
      isLine = false;
      visible = true;
      changeBlendMode = false;
      debug = false;
      morph = false;
      isText = false;
      beginSubmitMask = false;
      endSubmitMask = false;
      beginUnsubmitMask = false;
      disbaleMask = false;
      useScale9Grid = false;
      clearScale9Grid = false;
      diffuse1.useDiffuse = false;
      diffuse2.useDiffuse = false;
      diffuse1.smoothing = true;
      diffuse2.smoothing = true;
      diffuse1.scale9Grid = false;
      diffuse2.scale9Grid = false;
      needChandeCXForm = false;
      needChangeModelMatrix = false;
      prepareFunc = 0;
    }

    Batch() : 
      needChangeView(false),
      needChangeModelMatrix(false),
      needChandeCXForm(false),
      beginSubmitMask(false),
      endSubmitMask(false),
      beginUnsubmitMask(false),
      disbaleMask(false),
      isLine(false),
      pixelScale(1.f),
      visible(false),
      changeBlendMode(false),
      blendMode(EFlashBlendMode::NORMAL),
      colorMatrixBegin(false),
      colorMatrixEnd(false),
      debug(false),
      morph(false),
      morphRate(0.f),
      isText(false),
      textPartID(-1),
      useScale9Grid(false),
      clearScale9Grid(false),
      hasBevel(false),
      prepareFunc(0)
    {
      Identity( &modelMatrix );
    }
  };

  typedef nstl::vector<Batch> Batches;

  struct ColorMatrixElement
  {
    SHMatrix colorMatrix;
    CVec4 colorAdd;
  };

  typedef nstl::list<ColorMatrixElement> ColorMatrixStack;

  void PrepareShape( const Batch& batch );
  void PrepareLine( const Batch& batch );
  void PrepareBitmap( const Batch& batch );

  void InitVertexDeclaration();
  void InitShapeVertexDeclaration();

  void BeginSubmitMaskApply();
  void EndSubmitMaskApply();
  void BeginUnSubmitMaskApply();
  void DisableMaskApply();

  void ApplyBlendMode( EFlashBlendMode::Enum blendMode );
  bool NeedToCopyBackground( EFlashBlendMode::Enum blendMode ) const;
  void SetScreenToTextureTransform( const Render::Texture2DRef& pMainRT0 );

  void AddRectangle( int firstVertex, float x1, float y1, float x2, float y2, float u1, float v1, float u2, float v2 );

  void PreapreStates();
  void PrepareTexture( BatchTexture& batch, bool primary );
  void ChangeMatricies( Batch& batch );

  void NextBatch();

  void PrepareFontMaterial( BaseMaterial* _material, bool _drawBevel, const Render::HDRColor& _color );

  D3DXMATRIX modelViewMatrix;
  D3DXMATRIX projMatrix;

  DXVertexDeclarationRef vertexDeclaration;
  DXVertexDeclarationRef vertexDeclarationShape;

  DXVertexBufferDynamicRef::Wrapped vertexBuffer;
  DXVertexBufferDynamicRef::Wrapped vertexBufferShape;
  DXVertexBufferDynamicRef::Wrapped vertexBufferTexture;
  DipDescriptor dipDescriptor;

  ShapeVertex* vertexBufferShapeRaw;
  FlashVertex* vertexBufferRaw;

  BaseMaterial* flashMaterial;

  Texture2DRef bevelTexture;

  float resolutionXCoef;
  float resolutionYCoef;
  float widthScale;
  float heightScale;

  Batches batches;
  int numBatches;
  int numVertices;
  int numVerticesShape;
  int numRendered;
  int numDIP;
  int numTargetSwitches;
  bool isLocked;

  bool alphaLayer;

  int maskLevel;

  float lineWidthHalf;
  Color lineColor;

  CVec4 flashConstants;

  flash::SWF_MATRIX lastModelMatrix;
  bool modelMatrixCached;

  flash::SWF_CXFORMWITHALPHA lastColorTransform;
  bool colorTransformCached;

  bool nextTextWithBevel;
  Render::HDRColor bevelColor; 
  Texture* fontTexture;

  float currentPixelScale;

  ColorMatrixStack colorMatrixStack;
};

} // namespace Render
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
