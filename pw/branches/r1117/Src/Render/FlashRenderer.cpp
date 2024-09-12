#include "stdafx.h"

#include "../UI/Flash/GameSWFIntegration/Image.h"

#include "batch.h"
#include "FlashRenderer.h"
#include "MaterialSpec.h"
#include "smartrenderer.h"
#include "uirenderer.h"
#include "GlobalMasks.h"
#include "ImmediateRenderer.h"
#include "UITextureCacheInterface.h"

#include "../System/InlineProfiler.h"
#include "../System/RandomGen.h"

namespace
{
  static NDebug::DebugVar<int> flash_VerticesCount( "Flash Vertices", "Flash" );
  static NDebug::DebugVar<int> flash_VBSize( "Flash VB Size", "Flash" );
  static NDebug::DebugVar<int> flash_VBShapeSize( "Flash VBShape Size", "Flash" );
  static NDebug::DebugVar<int> flash_BatchesCount( "Flash Batches", "Flash" );
  static NDebug::DebugVar<int> flash_DrawCalls( "Flash Draw Calls", "Flash" );
  static NDebug::DebugVar<int> flash_TargetSwitch( "Flash Target Switch", "Flash" );
  static NDebug::DebugVar<int> flash_BitmapCount( "Bitmap Count", "Flash" );
  static NDebug::DebugVar<int> flash_BuiltinBitmapSize( "Builtin Bitmap Size", "Flash" );

  bool gSkipFlashRender = false;
  REGISTER_DEV_VAR( "skip_flash_render", gSkipFlashRender, STORAGE_NONE );

  static bool flashTest = false;
  REGISTER_DEV_VAR( "flashTest", flashTest, STORAGE_NONE );
}

namespace Render
{

#define TEXTURE_MATRIX  VIEWPROJECTION

static const int MAX_VERTEX_COUNT = 1024 * 48;
static const int MAX_BATCHES = 4096 * 2; // Total allocated batch size ~ 2 Mb 

// bitmap_info_d3d declaration
class BitmapInfoD3D : public IBitmapInfo, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( BitmapInfoD3D, IBitmapInfo, BaseObjectST );

public:

  int m_width;
  int m_height;
  int m_lineID; // for linear gradients
  Texture2DRef m_texture;

  CVec2 uv1;
  CVec2 uv2;

  BitmapInfoD3D() :
    m_width(0),
    m_height(0),
    m_lineID(0),
    uv1( 0.f, 0.f ),
    uv2( 1.f, 1.f )
  {
  }

  BitmapInfoD3D( const flash::SWF_GRADIENT& gradient ) :
    m_lineID(0),
    uv1( 0.f, 0.f ),
    uv2( 1.f, 1.f )
  {
    m_texture = GetUIRenderer()->GetTextureCache()->GetGradientTexture( gradient );

    m_width = m_texture->GetWidth();
    m_height = m_texture->GetHeight();

    flash_BitmapCount.AddValue( 1 );
  }

  BitmapInfoD3D( const Texture2DRef& _texture ) :
    m_texture( _texture ),
    uv1( 0.f, 0.f ),
    uv2( 1.f, 1.f )
  { 
    m_width = m_texture->GetWidth();
    m_height = m_texture->GetHeight();

    flash_BitmapCount.AddValue( 1 );
  }


  BitmapInfoD3D( image::rgba* im, bool repeatable ) :
    m_width(im->m_width),
    m_height(im->m_height),
    uv1( 0.f, 0.f ),
    uv2( 1.f, 1.f )
  {
    m_texture = GetUIRenderer()->GetTextureCache()->PlaceImageToAtlas( im, uv1, uv2, repeatable );
  }

  BitmapInfoD3D( const nstl::string& filename ) :
    uv1( 0.f, 0.f ),
    uv2( 1.f, 1.f )
  {
    m_texture = Render::Load2DTextureFromFile( filename );

    if ( m_texture )
    {
      m_width = m_texture->GetWidth();
      m_height = m_texture->GetHeight();
    }

    flash_BitmapCount.AddValue( 1 );
  }

  BitmapInfoD3D( int width, int height ):
    m_width(width),
    m_height(height),
    uv1( 0.f, 0.f ),
    uv2( 1.f, 1.f )
  {
    m_texture = Render::CreateTexture2D( width, height, 1, RENDER_POOL_MANAGED, FORMAT_A8R8G8B8 );

    flash_BitmapCount.AddValue( 1 );
  }

  ~BitmapInfoD3D()
  {
    flash_BitmapCount.AddValue( -1 );
  }

  virtual int GetWidth() const { return m_width; }
  virtual int GetHeight() const { return m_height; }
  virtual const CVec2& GetUV1() const { return uv1; }
  virtual const CVec2& GetUV2() const { return uv2; }

  virtual IBitmapInfo* Clone() 
  {
    BitmapInfoD3D * cloneBmp = new BitmapInfoD3D();
    cloneBmp->m_texture = Render::CreateTexture2D( m_width, m_height, 1, RENDER_POOL_MANAGED, FORMAT_A8R8G8B8 );

    LockedRect lockedRectDest = cloneBmp->m_texture->LockRect( 0, LOCK_DEFAULT );
    LockedRect lockedRectSource = m_texture->LockRect( 0, LOCK_DEFAULT );

    memcpy( lockedRectDest.data, lockedRectSource.data, m_width * m_height * 4 );

    cloneBmp->m_texture->UnlockRect( 0 );
    m_texture->UnlockRect( 0 );

    cloneBmp->m_width = m_width;
    cloneBmp->m_height = m_height;

    return cloneBmp;
  }

  virtual void Draw( IBitmapInfo* source, const flash::SWF_MATRIX& _matrix, int x1, int y1, int x2, int y2 )
  {
    if ( x1 > x2 )
      return;

    if ( y1 > y2 )
      return;

    x1 = Clamp( x1, 0, source->GetWidth() - 1 ); 
    x2 = Clamp( x2, 0, source->GetWidth() - 1 ); 
    y1 = Clamp( y1, 0, source->GetHeight() - 1 ); 
    y2 = Clamp( y2, 0, source->GetHeight() - 1 ); 

    BitmapInfoD3D* sourceD3D = dynamic_cast<BitmapInfoD3D*>( source );

    if ( !sourceD3D )
      return;

    LockedRect lockedRectDest = m_texture->LockRect( 0, LOCK_DEFAULT );
    LockedRect lockedRectSource = sourceD3D->m_texture->LockRect( 0, LOCK_DEFAULT );
    
    for ( int i = x1; i <= x2 && i < m_width; ++i )
    {
      for ( int j = y1; j <= y2 && j < m_height; ++j )
      {
        int base1 = ( j * m_width + i ) * 4;
        int base2 = ( j * source->GetWidth() + i ) * 4;

        lockedRectDest.data[ base1 + 0 ] = lockedRectSource.data[ base2 + 0 ];
        lockedRectDest.data[ base1 + 1 ] = lockedRectSource.data[ base2 + 1 ];
        lockedRectDest.data[ base1 + 2 ] = lockedRectSource.data[ base2 + 2 ];
        lockedRectDest.data[ base1 + 3 ] = lockedRectSource.data[ base2 + 3 ];
      }
    }

    sourceD3D->m_texture->UnlockRect( 0 );
    m_texture->UnlockRect( 0 );
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlashRenderer::FlashRenderer() : 
  numBatches(0),
  numVertices(0),
  numVerticesShape(0),
  numRendered(0),
  numDIP(0),
  numTargetSwitches(0),
  isLocked(false),
  vertexBufferRaw(0),
  vertexBufferShapeRaw(0),
  resolutionXCoef(1.f),
  resolutionYCoef(1.f),
  widthScale(1.f),
  heightScale(1.f),
  maskLevel(0),

  flashMaterial(0),

  lineWidthHalf(40.f),

  flashConstants(1.f, 1.f, 1.f, 1.f),

  nextTextWithBevel(false),
  fontTexture(0),

  currentPixelScale(20.f),
  modelMatrixCached(false),
  colorTransformCached(false)
{
  batches.resize(MAX_BATCHES);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FlashRenderer::~FlashRenderer()
{
  if ( flashMaterial )
    delete flashMaterial;

  flashMaterial = 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::InitVertexDeclaration()
{
  VertexFormatDescriptor formatDescriptor;

  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 0, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_POSITION, 0) );
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 8, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_TEXCOORD, 0) );
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 16, VERTEXELEMENTTYPE_D3DCOLOR, VERETEXELEMENTUSAGE_COLOR, 0) );
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 20, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_TEXCOORD, 1) );
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 28, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_TEXCOORD, 2) );
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 36, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_TEXCOORD, 3) );

  vertexDeclaration = SmartRenderer::GetVertexFormatDeclaration( formatDescriptor );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::InitShapeVertexDeclaration()
{
  VertexFormatDescriptor formatDescriptor;

  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 0, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_POSITION, 0) );
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 8, VERTEXELEMENTTYPE_D3DCOLOR, VERETEXELEMENTUSAGE_COLOR, 0) );
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 12, VERTEXELEMENTTYPE_FLOAT1, VERETEXELEMENTUSAGE_TEXCOORD, 0) );

  vertexDeclarationShape = SmartRenderer::GetVertexFormatDeclaration( formatDescriptor );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FlashRenderer::Initialize()
{
  InitVertexDeclaration();
  InitShapeVertexDeclaration();

  dipDescriptor.primitiveType = RENDERPRIMITIVE_TRIANGLESTRIP;

  // Create vertex buffer
  vertexBuffer.Resize( MAX_VERTEX_COUNT * sizeof(FlashVertex) );
  NI_VERIFY( Get( vertexBuffer ), "FlashRenderer: Failed to create vertex buffer!", return false );

  vertexBufferShape.Resize( MAX_VERTEX_COUNT * sizeof(ShapeVertex) );
  NI_VERIFY( Get( vertexBufferShape ), "FlashRenderer: Failed to create shape vertex buffer!", return false );

  // Material
  flashMaterial =  static_cast<BaseMaterial*>( Render::CreateRenderMaterial( NDb::UIFlashMaterial::typeId ) );

  // Bevel texture
  bevelTexture = Render::CreateTexture2D( 4, 4, 1, RENDER_POOL_MANAGED, FORMAT_L8 );
  LockedRect lockedRect = bevelTexture->LockRect( 0, LOCK_DEFAULT );
  unsigned char* data = reinterpret_cast<unsigned char*>( lockedRect.data );

  const float bevelConst = 0.17421356f;

#define BIAS_BEVEL( val ) unsigned char( ( (val + 1.f) / 2.f ) * 255.f );

  data[ 0 * 4 + 0 ] = BIAS_BEVEL( bevelConst );
  data[ 0 * 4 + 1 ] = BIAS_BEVEL( 0.f );
  data[ 0 * 4 + 2 ] = BIAS_BEVEL( bevelConst );
  data[ 0 * 4 + 3 ] = BIAS_BEVEL( bevelConst );

  data[ 1 * 4 + 0 ] = BIAS_BEVEL( 0.f );
  data[ 1 * 4 + 1 ] = BIAS_BEVEL( -1.f );
  data[ 1 * 4 + 2 ] = BIAS_BEVEL( 0.f );
  data[ 1 * 4 + 3 ] = BIAS_BEVEL( 0.f );

  data[ 2 * 4 + 0 ] = BIAS_BEVEL( 0.f );
  data[ 2 * 4 + 1 ] = BIAS_BEVEL( -1.f );
  data[ 2 * 4 + 2 ] = BIAS_BEVEL( 0.f );
  data[ 2 * 4 + 3 ] = BIAS_BEVEL( 0.f );

  data[ 3 * 4 + 0 ] = BIAS_BEVEL( bevelConst );
  data[ 3 * 4 + 1 ] = BIAS_BEVEL( 0.f );
  data[ 3 * 4 + 2 ] = BIAS_BEVEL( bevelConst );
  data[ 3 * 4 + 3 ] = BIAS_BEVEL( bevelConst );

#undef BIAS_BEVEL

  bevelTexture->UnlockRect( 0 );

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::Release()
{
  vertexDeclaration = 0;
  vertexDeclarationShape = 0;

  vertexBuffer.Reset();
  vertexBufferShape.Reset();
  vertexBufferTexture.Reset();

  batches.clear();

  if ( flashMaterial )
	{
    delete flashMaterial;
		flashMaterial = 0;
	}

  bevelTexture = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::BeginQueue()
{
  maskLevel = 0;
  numVertices = 0;
  numVerticesShape = 0;
  numBatches = 0;
  numRendered = 0;
  numDIP = 0;
  numTargetSwitches = 0;
  batches[numBatches].Clear();
  vertexBufferRaw = LockVB<FlashVertex>( Get( vertexBuffer ), D3DLOCK_DISCARD );
  vertexBufferShapeRaw = LockVB<ShapeVertex>( Get( vertexBufferShape ), D3DLOCK_DISCARD );
  isLocked = true;
  colorMatrixStack.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::EndQueue()
{
  NI_ASSERT( isLocked, "Buffer is not locked!" );
  isLocked = false;

  vertexBuffer->Unlock();
  vertexBufferRaw = 0;
  vertexBufferShape->Unlock();
  vertexBufferShapeRaw = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::BreakQueue()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::StartFrame()
{
  flash_VBSize.SetValue( numVertices );
  flash_VBShapeSize.SetValue( numVerticesShape );
  flash_BatchesCount.SetValue( numBatches );
  flash_VerticesCount.SetValue( numRendered );
  flash_DrawCalls.SetValue( numDIP );
  flash_TargetSwitch.SetValue( numTargetSwitches );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::SetResolutionCoefs( float _x, float _y, float _widthScale, float _heightScale )
{
  resolutionXCoef = _x;
  resolutionYCoef = _y;
  widthScale = _widthScale;
  heightScale = _heightScale;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::PreapreStates()
{
  flashConstants.x = resolutionXCoef;
  GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST7, flashConstants );

  Render::GetStatesManager()->SetSampler(2, Render::SamplerState::PRESET_CLAMP_BILINEAR(), bevelTexture );

  Render::GetStatesManager()->SetStateDirect( D3DRS_CULLMODE, D3DCULL_NONE );

  GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::PrepareTexture( BatchTexture& batch, bool primary )
{
  if ( batch.useDiffuse )
  {
    batch.useDiffuse = false;
    NDb::SamplerState sampleState;
    sampleState.mipFilter = NDb::MIPFILTERTYPE_NONE;
    sampleState.magFilter = batch.smoothing ? NDb::MAGFILTERTYPE_LINEAR : NDb::MAGFILTERTYPE_POINT;
    sampleState.minFilter = batch.smoothing ? NDb::MINFILTERTYPE_LINEAR : NDb::MINFILTERTYPE_POINT;
    sampleState.addressU = (batch.textureMode == EBitmapWrapMode::REPEAT) ? NDb::TEXTUREADDRESSTYPE_WRAP : NDb::TEXTUREADDRESSTYPE_CLAMP;
    sampleState.addressV = sampleState.addressU;
    sampleState.addressW = sampleState.addressU;

    if ( primary )
    {
      flashMaterial->SetUseDiffuse( NDb::BOOLEANPIN_PRESENT );
      flashMaterial->SetScale9GridBitmap( batch.scale9Grid ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE );
      flashMaterial->GetDiffuseMap()->SetTexture( batch.texture );
      flashMaterial->GetDiffuseMap()->SetSamplerState( sampleState );
      GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST9 + 1, batch.matrixRow1 );
      GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST9 + 2, batch.matrixRow2 );
    }
    else
    {
      flashMaterial->SetUseDiffuse2( NDb::BOOLEANPIN_PRESENT );
      flashMaterial->GetDiffuseMap2()->SetTexture( batch.texture );
      flashMaterial->GetDiffuseMap2()->SetSamplerState( sampleState );
      GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST9 + 3, batch.matrixRow1 );
      GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST9 + 4, batch.matrixRow2 );
    }
  }
  else
  {
    if ( primary )
    {
      flashMaterial->SetScale9GridBitmap( NDb::BOOLEANPIN_NONE );
      flashMaterial->SetUseDiffuse( NDb::BOOLEANPIN_NONE );
    }
    else
    {
      flashMaterial->SetUseDiffuse2( NDb::BOOLEANPIN_NONE );
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::ChangeMatricies( Batch& nextBatch )
{
  if ( nextBatch.needChangeView )
  {
    nextBatch.needChangeView = false;

    GetRenderer()->SetVertexShaderConstantsMatrix( VIEW, nextBatch.viewMatrix );
    currentPixelScale = nextBatch.pixelScale;

    GetDevice()->SetRenderState( D3DRS_STENCILENABLE, FALSE );
    GetDevice()->SetRenderState( D3DRS_STENCILFUNC, D3DCMP_ALWAYS );
    GetDevice()->SetRenderState( D3DRS_STENCILREF, 0 );
  }

  if ( nextBatch.needChangeModelMatrix )
  {
    nextBatch.needChangeModelMatrix = false;

    float xScale = fabs( nextBatch.modelMatrix.GetXAxis3() );
    float yScale = fabs( nextBatch.modelMatrix.GetYAxis3() );
    float scale = 0.6f * currentPixelScale / sqrt( xScale * yScale );
    flashConstants.y = scale;

    GetRenderer()->SetVertexShaderConstantsMatrix( WORLD, nextBatch.modelMatrix );
  }

  flashConstants.z = nextBatch.morphRate;
  GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST7, flashConstants );
  GetRenderer()->SetPixelShaderConstantsVector4( PSHADER_LOCALCONST7, flashConstants );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::Render( int _firstElement, int _lastElement, const Render::Texture2DRef& pMainRT0 , const Render::Texture2DRef& pMainRT0Copy )
{
  if ( gSkipFlashRender )
    return;

  SetScreenToTextureTransform( pMainRT0 );
  PreapreStates();

  Render::SamplerState samplerState = Render::SamplerState::PRESET_CLAMP_BILINEAR();

  bool wasLine = false;
  bool wasText = false;

  EFlashBlendMode::Enum lastBlendMode = EFlashBlendMode::NORMAL;

  flashMaterial->SetUseDiffuse( NDb::BOOLEANPIN_NONE );
  flashMaterial->SetShaderForLines( NDb::BOOLEANPIN_NONE );

  for ( int i =  _firstElement; i < _lastElement && i < numBatches; ++i )
  {
    Batch& nextBatch = batches[i];

    if ( wasLine ^ nextBatch.isLine )
    {  
      if ( nextBatch.isLine )
        flashMaterial->SetShaderForLines( NDb::BOOLEANPIN_PRESENT );
      else
        flashMaterial->SetShaderForLines( NDb::BOOLEANPIN_NONE );

      wasLine = nextBatch.isLine;
    }

    if ( wasText ^ nextBatch.isText )
    {
      if ( nextBatch.isText )
        GetUIRenderer()->PrepareRender();//FromFlash();
      else
        PreapreStates();

      wasText = nextBatch.isText;
    }

    PrepareTexture( nextBatch.diffuse1, true );
    PrepareTexture( nextBatch.diffuse2, false );

    ChangeMatricies( nextBatch );

    if ( nextBatch.needChandeCXForm )
    {
      nextBatch.needChandeCXForm = false;
      GetRenderer()->SetPixelShaderConstantsHDRColor( PSHADER_LOCALCONST0, nextBatch.multColorCXF );
      GetRenderer()->SetPixelShaderConstantsHDRColor( PSHADER_LOCALCONST1, nextBatch.addColorCXF );
    }

    bool beginMask = false;

    if ( nextBatch.beginSubmitMask )
    {
      beginMask = true;
      nextBatch.beginSubmitMask = false;
      BeginSubmitMaskApply();
    }

    if ( nextBatch.endSubmitMask )
    {
      nextBatch.endSubmitMask = false;
      EndSubmitMaskApply();
    }

    if ( nextBatch.beginUnsubmitMask )
    {
      beginMask = true;
      nextBatch.beginUnsubmitMask = false;
      BeginUnSubmitMaskApply();
    }

    if ( nextBatch.disbaleMask )
    {
      nextBatch.disbaleMask = false;
      DisableMaskApply();
    }

    if ( nextBatch.isText )
    {
      BaseMaterial* baseMaterial = GetUIRenderer()->GetPartMaterial( nextBatch.textPartID, ERenderWhat::_2D );

      if ( baseMaterial )
        PrepareFontMaterial( baseMaterial, nextBatch.hasBevel, nextBatch.bevelColor );

      GetUIRenderer()->RenderPart( nextBatch.textPartID, ERenderWhat::_2D, beginMask ); 

      continue;
    }

    if ( nextBatch.changeBlendMode )
      lastBlendMode = nextBatch.blendMode;

    if ( nextBatch.colorMatrixBegin )
    {
      flashMaterial->SetUseColorFilter( NDb::BOOLEANPIN_PRESENT );

      GetRenderer()->SetPixelShaderConstantsVector4( PSHADER_LOCALCONST8, nextBatch.colorAdd );
      GetRenderer()->SetPixelShaderConstantsMatrix( PSHADER_LOCALCONST9, nextBatch.colorMatrix );

      ColorMatrixElement& elem = colorMatrixStack.push_back();
      elem.colorAdd = nextBatch.colorAdd;
      elem.colorMatrix = nextBatch.colorMatrix;
    }

    if ( nextBatch.useScale9Grid )
    {
      flashMaterial->SetScale9Grid( NDb::BOOLEANPIN_PRESENT );
      GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST9 + 5, nextBatch.scaleConstX );
      GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST9 + 6, nextBatch.scaleConstY );
      GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST9 + 7, nextBatch.transScale9 );
    }

    if ( nextBatch.clearScale9Grid )
      flashMaterial->SetScale9Grid( NDb::BOOLEANPIN_NONE );

    if ( nextBatch.colorMatrixEnd )
    {
      NI_ASSERT( !colorMatrixStack.empty(), "Wrong ColorMatrix sequence" );

      if ( !colorMatrixStack.empty() )
        colorMatrixStack.pop_back();

      if ( !colorMatrixStack.empty() )
      {
        ColorMatrixElement& elem = colorMatrixStack.back();

        GetRenderer()->SetPixelShaderConstantsVector4( PSHADER_LOCALCONST8, elem.colorAdd );
        GetRenderer()->SetPixelShaderConstantsMatrix( PSHADER_LOCALCONST9, elem.colorMatrix );
      }
      else
      {
        flashMaterial->SetUseColorFilter( NDb::BOOLEANPIN_NONE );
      }
    }

    flashMaterial->SetMorphShapes( nextBatch.morph ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE );

    if ( nextBatch.visible )
    {
      NI_VERIFY( nextBatch.prepareFunc, "Wrong prepare function", continue );

      (this->*(nextBatch.prepareFunc))( nextBatch ); 

      if ( NeedToCopyBackground( lastBlendMode ) )
      {
        SmartRenderer::BindRenderTargetColor( 0, pMainRT0Copy->GetSurface( 0 ) );
        SmartRenderer::BindTexture( 3, pMainRT0 );

        flashMaterial->SetFlashBlendModePin( NDb::FLASHBLENDMODEPIN_COPY_BACKGRUOND );
        flashMaterial->PrepareRenderer();

        GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
        GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
        GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ZERO);

        SmartRenderer::DrawPrimitive( nextBatch.dip );
        numRendered += nextBatch.dip.numVertices;
        numDIP++;
        numTargetSwitches++;

        SmartRenderer::BindRenderTargetColor( 0, pMainRT0->GetSurface( 0 ) );
        SmartRenderer::BindTexture( 3, pMainRT0Copy );
      }

      ApplyBlendMode( lastBlendMode );

      SmartRenderer::DrawPrimitive( nextBatch.dip );
      numRendered += nextBatch.dip.numVertices;
      numDIP++;
    }
  }

  // $TODO check
  GetDevice()->SetRenderState( D3DRS_BLENDOP, D3DBLENDOP_ADD );
  GetDevice()->SetRenderState( D3DRS_BLENDOPALPHA, D3DBLENDOP_ADD );

  GetStatesManager()->SetStencilState(STENCILSTATE_INVALID);
  GetDevice()->SetRenderState( D3DRS_STENCILENABLE, FALSE );
  GetDevice()->SetRenderState( D3DRS_COLORWRITEENABLE, 0x0000000F );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::PrepareShape( const Batch& batch )
{
  SmartRenderer::BindVertexDeclaration( vertexDeclarationShape );
  SmartRenderer::BindVertexBuffer( 0, Get(vertexBufferShape), sizeof(ShapeVertex)	);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::PrepareLine( const Batch& batch )
{
  SmartRenderer::BindVertexDeclaration( vertexDeclaration );
  SmartRenderer::BindVertexBuffer( 0, Get(vertexBuffer), sizeof(FlashVertex)	);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::PrepareBitmap( const Batch& batch )
{
  SmartRenderer::BindVertexDeclaration( vertexDeclaration );
  SmartRenderer::BindVertexBuffer( 0, Get(vertexBuffer), sizeof(FlashVertex)	);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::ApplyBlendMode( EFlashBlendMode::Enum blendMode )
{
  flashMaterial->SetFlashBlendModePin( NDb::FLASHBLENDMODEPIN__NORMAL );

  switch ( blendMode )
  {
  case EFlashBlendMode::ADD :
    flashMaterial->SetFlashBlendModePin( NDb::FLASHBLENDMODEPIN_ADD );
    break;
  case EFlashBlendMode::INVERT :
    flashMaterial->SetFlashBlendModePin( NDb::FLASHBLENDMODEPIN_INVERT );
    break;
  case EFlashBlendMode::DARKEN :
    flashMaterial->SetFlashBlendModePin( NDb::FLASHBLENDMODEPIN_DARKEN );
    break;
  case EFlashBlendMode::MULTIPLY :
    flashMaterial->SetFlashBlendModePin( NDb::FLASHBLENDMODEPIN_MULTIPLY );
    break;
  case EFlashBlendMode::_DIFFERENCE :
    flashMaterial->SetFlashBlendModePin( NDb::FLASHBLENDMODEPIN__DIFFERENCE );
    break;
  case EFlashBlendMode::OVERLAY :
    flashMaterial->SetFlashBlendModePin( NDb::FLASHBLENDMODEPIN_OVERLAY );
    break;
  case EFlashBlendMode::HARDLIGHT :
    flashMaterial->SetFlashBlendModePin( NDb::FLASHBLENDMODEPIN_HARDLIGHT );
    break;
  case EFlashBlendMode::SCREEN :
    flashMaterial->SetFlashBlendModePin( NDb::FLASHBLENDMODEPIN_SCREEN );
    break;
  }

  flashMaterial->PrepareRenderer();

  GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);

  switch ( blendMode )
  {
  case EFlashBlendMode::ADD :
     GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
     GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    break;
  case EFlashBlendMode::MULTIPLY :
     GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ZERO);
     GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_SRCCOLOR);
    break;
  case EFlashBlendMode::DARKEN :
     GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
     GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
     GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_MIN);
    break;
  case EFlashBlendMode::SCREEN :
    GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
    GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    break;
  case EFlashBlendMode::LIGHTEN :
    GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
    GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_MAX);
    break;
  case EFlashBlendMode::SUBTRACT :
    GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_ONE);
    GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
    GetDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_REVSUBTRACT);
    break;
  case EFlashBlendMode::INVERT :
    GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_INVDESTCOLOR);
    GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    break;

  case EFlashBlendMode::_DIFFERENCE :
  case EFlashBlendMode::OVERLAY :
  case EFlashBlendMode::HARDLIGHT :
    GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
    GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    break;

  default:
     GetDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
     GetDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
    break;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool FlashRenderer::NeedToCopyBackground( EFlashBlendMode::Enum blendMode ) const
{
  switch ( blendMode )
  {
  case EFlashBlendMode::_DIFFERENCE :
  case EFlashBlendMode::HARDLIGHT :
  case EFlashBlendMode::OVERLAY :
    return true;
  }

  return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::SetScreenToTextureTransform( const Render::Texture2DRef& pMainRT0 )
{
  CVec4 screenScaleOffset;
  screenScaleOffset.x = 1.0f / pMainRT0->GetWidth();
  screenScaleOffset.y = 1.0f / pMainRT0->GetHeight();
  screenScaleOffset.z = 0.5f * screenScaleOffset.x;
  screenScaleOffset.w = 0.5f * screenScaleOffset.y;

  GetRenderer()->SetPixelShaderConstantsVector4(SCREEN_TO_TEXTURE, screenScaleOffset);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IBitmapInfo* FlashRenderer::CreateBitmap( int width, int height )
{
  return new BitmapInfoD3D( width, height );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IBitmapInfo* FlashRenderer::CreateBitmapFromTexture( const Texture2DRef& _texture )
{
  return new BitmapInfoD3D( _texture );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IBitmapInfo* FlashRenderer::CreateBitmapInfoRgba( image::rgba* im, bool repeatable )
{
//  return new BitmapInfoD3D( "Tech/checker256.dds" );
  return new BitmapInfoD3D( im, repeatable );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IBitmapInfo* FlashRenderer::CreateBitmapFromFile( const nstl::string& filename )
{
  return new BitmapInfoD3D( filename );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IBitmapInfo* FlashRenderer::CreateGradientBitmap( const flash::SWF_GRADIENT& gradient )
{
  return new BitmapInfoD3D( gradient );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::BeginDisplay(
                            int viewport_x0, int viewport_y0,
                            int viewport_width, int viewport_height,
                            float x0, float x1, float y0, float y1,
                            bool useScissorRect )
{
  if ( numBatches >= MAX_BATCHES )
    return;

  modelMatrixCached = false;
  colorTransformCached = false;

  GetUIRenderer()->BeginFlashParts( numBatches );

  batches[ numBatches ].needChangeView = true;
  Identity( &batches[ numBatches ].viewMatrix );

  batches[ numBatches ].viewMatrix._11 = 1.0f / (x1 - x0);
  batches[ numBatches ].viewMatrix._22 = -1.0f / (y1 - y0);
  batches[ numBatches ].viewMatrix._41 = -((x1 + x0) / (x1 - x0));
  batches[ numBatches ].viewMatrix._42 = ((y1 + y0) / (y1 - y0));

  SHMatrix windowMatrix;
  Identity( &windowMatrix );

  float viewportWidth = static_cast<float>( viewport_width );
  float viewportHeight = static_cast<float>( viewport_height );
  float viewportX0 = static_cast<float>( viewport_x0 );
  float viewportY0 = static_cast<float>( viewport_y0 );

  windowMatrix._11 = viewportWidth * resolutionXCoef;
  windowMatrix._22 = viewportHeight * resolutionYCoef;
  windowMatrix._41 = -1.0f + viewportX0 * resolutionXCoef + viewportWidth * resolutionXCoef;
  windowMatrix._42 = 1.0f - viewportY0 * resolutionYCoef - viewportHeight * resolutionYCoef;

  batches[ numBatches ].viewMatrix = batches[ numBatches ].viewMatrix * windowMatrix;
  batches[ numBatches ].pixelScale = (x1 - x0) / ( viewportWidth * widthScale );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void	FlashRenderer::EndDisplay()
{
  GetUIRenderer()->EndFlashParts( numBatches );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::SetMatrix( const flash::SWF_MATRIX& m )
{
  if ( numBatches >= MAX_BATCHES )
    return;

  if ( modelMatrixCached && m == lastModelMatrix )
    return;

  Batch& batch = batches[ numBatches ];

  batch.needChangeModelMatrix = true;

  batch.modelMatrix._11 = m.m_[0][0]; batch.modelMatrix._12 = m.m_[1][0];
  batch.modelMatrix._21 = m.m_[0][1]; batch.modelMatrix._22 = m.m_[1][1];
  batch.modelMatrix._41 = m.m_[0][2]; batch.modelMatrix._42 = m.m_[1][2];

  lastModelMatrix = m;
  modelMatrixCached = true;
}

void FlashRenderer::SetColorTransform( const flash::SWF_CXFORMWITHALPHA& cx )
{
  if ( numBatches >= MAX_BATCHES )
    return;

  if ( colorTransformCached && cx == lastColorTransform )
    return;

  Batch& batch = batches[ numBatches ];

  batch.needChandeCXForm = true;

  batch.multColorCXF.R = cx.m_[0][0];
  batch.multColorCXF.G = cx.m_[1][0];
  batch.multColorCXF.B = cx.m_[2][0];
  batch.multColorCXF.A = cx.m_[3][0];

  batch.addColorCXF.R = cx.m_[0][1] / 255.f;
  batch.addColorCXF.G = cx.m_[1][1] / 255.f;
  batch.addColorCXF.B = cx.m_[2][1] / 255.f;
  batch.addColorCXF.A = cx.m_[3][1] / 255.f;

  lastColorTransform = cx;
  colorTransformCached = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::SetBlendMode( EFlashBlendMode::Enum blendMode )
{
  if ( numBatches >= MAX_BATCHES )
    return;

  batches[ numBatches ].changeBlendMode = true;
  batches[ numBatches ].blendMode = blendMode;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::DrawTriangleList( ShapeVertex* vertices, int vertex_count, int uniqueID )
{
  NI_PROFILE_FUNCTION

  if(!vertexBufferShapeRaw)
    return;

  if ( numBatches >= MAX_BATCHES )
    return;

  if ( numVerticesShape + vertex_count > MAX_VERTEX_COUNT )
    return;

  Batch& batch = batches[ numBatches ];

  batch.prepareFunc = &FlashRenderer::PrepareShape;

  memcpy( &vertexBufferShapeRaw[numVerticesShape], vertices, vertex_count * sizeof( ShapeVertex ) );

  batch.dip.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
  batch.dip.baseVertexIndex = numVerticesShape;	
  batch.dip.startIndex = numVerticesShape;	// $TODO error in Render
  batch.dip.numVertices = vertex_count;
  batch.dip.primitiveCount = (vertex_count / 3);

  numVerticesShape += vertex_count;

  NextBatch();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::SetMorph( float rate )
{
  if ( numBatches >= MAX_BATCHES )
    return;

  Batch& batch = batches[ numBatches ];

  batch.morph = true;
  batch.morphRate = rate;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::SetScale9Grid( const CVec4& constX, const CVec4& constY, const CVec4& trans )
{
  if ( numBatches >= MAX_BATCHES )
    return;

  Batch& batch = batches[ numBatches ];

  batch.useScale9Grid = true;
  batch.scaleConstX = constX;
  batch.scaleConstY = constY;
  batch.transScale9 = trans;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::ResetScale9Grid()
{
  if ( numBatches >= MAX_BATCHES )
    return;

  batches[ numBatches ].clearScale9Grid = true;
  batches[ numBatches ].visible = false;

  NextBatch();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::DrawLineStrip( const nstl::vector<CVec2>& _coords, int uniqueID )
{
#if 1
  if ( !vertexBufferRaw )
    return;

  if ( numBatches >= MAX_BATCHES )
    return;

  int point_count = _coords.size();

  if ( point_count < 2 )
    return;

  int vertex_count = ( point_count * 2 - 2) * 2 + 4;

  if ( numVertices + vertex_count > MAX_VERTEX_COUNT )
    return;

  int segment_count = point_count - 1;

  int vertexID = numVertices;

  const float coord0 = 0.123f;
  const float coord1 = 0.375f;
  const float coord2 = 0.625f;
  const float coord3 = 0.875f;

  float segU0 = coord1;
  float segDelta = (coord2 - coord1) / float( segment_count );
  float segU1 = coord1 + segDelta;

  for ( int i = 0; i < segment_count; ++i )
  {
    float perpX = float(_coords[i + 1].y - _coords[i].y);
    float perpY = float(_coords[i].x - _coords[i + 1].x);

    Normalize( perpX, perpY );

    float normX = -perpY;
    float normY = perpX;

    if ( i == 0 )
    {
      vertexBufferRaw[vertexID].x = _coords[i].x - normX * lineWidthHalf + perpX * lineWidthHalf;
      vertexBufferRaw[vertexID].y = _coords[i].y - normY * lineWidthHalf + perpY * lineWidthHalf;
      vertexBufferRaw[vertexID].xShift = perpX;
      vertexBufferRaw[vertexID].yShift = perpY;
      vertexBufferRaw[vertexID].color = lineColor;
      vertexBufferRaw[vertexID].aliasing = 0.f;
      vertexBufferRaw[vertexID].aliasingScale = lineWidthHalf;
      vertexBufferRaw[vertexID].distanceUV = CVec2( coord0, coord0 );
      vertexID++;

      vertexBufferRaw[vertexID].x = _coords[i].x - normX * lineWidthHalf - perpX * lineWidthHalf;
      vertexBufferRaw[vertexID].y = _coords[i].y - normY * lineWidthHalf - perpY * lineWidthHalf;
      vertexBufferRaw[vertexID].xShift = -perpX;
      vertexBufferRaw[vertexID].yShift = -perpY;
      vertexBufferRaw[vertexID].color = lineColor;
      vertexBufferRaw[vertexID].aliasing = 0.f;
      vertexBufferRaw[vertexID].aliasingScale = lineWidthHalf;
      vertexBufferRaw[vertexID].distanceUV = CVec2( coord2, coord0 );
      vertexID++;
    }

    vertexBufferRaw[vertexID].x = _coords[i].x + perpX * lineWidthHalf;
    vertexBufferRaw[vertexID].y = _coords[i].y + perpY * lineWidthHalf;
    vertexBufferRaw[vertexID].xShift = perpX;
    vertexBufferRaw[vertexID].yShift = perpY;
    vertexBufferRaw[vertexID].color = lineColor;
    vertexBufferRaw[vertexID].aliasing = 0.f;
    vertexBufferRaw[vertexID].aliasingScale = lineWidthHalf;
    vertexBufferRaw[vertexID].distanceUV = CVec2( coord0, segU0 );
    vertexID++;

    vertexBufferRaw[vertexID].x = _coords[i].x - perpX * lineWidthHalf;
    vertexBufferRaw[vertexID].y = _coords[i].y - perpY * lineWidthHalf;
    vertexBufferRaw[vertexID].xShift = -perpX;
    vertexBufferRaw[vertexID].yShift = -perpY;
    vertexBufferRaw[vertexID].color = lineColor;
    vertexBufferRaw[vertexID].aliasing = 1.f;
    vertexBufferRaw[vertexID].aliasingScale = lineWidthHalf;
    vertexBufferRaw[vertexID].distanceUV = CVec2( coord2, segU0 );
    vertexID++;

    vertexBufferRaw[vertexID].x = _coords[i+1].x + perpX * lineWidthHalf;
    vertexBufferRaw[vertexID].y = _coords[i+1].y + perpY * lineWidthHalf;
    vertexBufferRaw[vertexID].xShift = perpX;
    vertexBufferRaw[vertexID].yShift = perpY;
    vertexBufferRaw[vertexID].color = lineColor;
    vertexBufferRaw[vertexID].aliasing = 0.f;
    vertexBufferRaw[vertexID].aliasingScale = lineWidthHalf;
    vertexBufferRaw[vertexID].distanceUV = CVec2( coord0, segU1 );
    vertexID++;

    vertexBufferRaw[vertexID].x = _coords[i+1].x - perpX * lineWidthHalf;
    vertexBufferRaw[vertexID].y = _coords[i+1].y - perpY * lineWidthHalf;
    vertexBufferRaw[vertexID].xShift = -perpX;
    vertexBufferRaw[vertexID].yShift = -perpY;
    vertexBufferRaw[vertexID].color = lineColor;
    vertexBufferRaw[vertexID].aliasing = 1.f;
    vertexBufferRaw[vertexID].aliasingScale = lineWidthHalf;
    vertexBufferRaw[vertexID].distanceUV = CVec2( coord2, segU1 );
    vertexID++;

    segU0 += segDelta;
    segU1 += segDelta;

    if ( i == segment_count - 1 )
    {
      vertexBufferRaw[vertexID].x = _coords[i+1].x + normX * lineWidthHalf + perpX * lineWidthHalf;
      vertexBufferRaw[vertexID].y = _coords[i+1].y + normY * lineWidthHalf + perpY * lineWidthHalf;
      vertexBufferRaw[vertexID].xShift = perpX;
      vertexBufferRaw[vertexID].yShift = perpY;
      vertexBufferRaw[vertexID].color = lineColor;
      vertexBufferRaw[vertexID].aliasing = 0.f;
      vertexBufferRaw[vertexID].aliasingScale = lineWidthHalf;
      vertexBufferRaw[vertexID].distanceUV = CVec2( coord0, coord3 );
      vertexID++;

      vertexBufferRaw[vertexID].x = _coords[i+1].x + normX * lineWidthHalf - perpX * lineWidthHalf;
      vertexBufferRaw[vertexID].y = _coords[i+1].y + normY * lineWidthHalf - perpY * lineWidthHalf;
      vertexBufferRaw[vertexID].xShift = -perpX;
      vertexBufferRaw[vertexID].yShift = -perpY;
      vertexBufferRaw[vertexID].color = lineColor;
      vertexBufferRaw[vertexID].aliasing = 0.f;
      vertexBufferRaw[vertexID].aliasingScale = lineWidthHalf;
      vertexBufferRaw[vertexID].distanceUV = CVec2( coord2, coord3 );
      vertexID++;
    }
  }

  Batch& batch = batches[numBatches];

  batch.prepareFunc = &FlashRenderer::PrepareLine;

  batch.dip.primitiveType = RENDERPRIMITIVE_TRIANGLESTRIP;
  batch.dip.baseVertexIndex = numVertices;	
  batch.dip.startIndex = numVertices;	// $TODO error in Render
  batch.dip.numVertices = vertex_count;
  batch.dip.primitiveCount = vertex_count - 2;

  batch.isLine = true;

  numVertices += vertex_count;

  NextBatch();
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::SetFillStyleBitmap( IBitmapInfo* bi, const flash::SWF_MATRIX& m, EBitmapWrapMode::Enum wm, bool primary )
{
  if ( numBatches >= MAX_BATCHES )
    return;

  if ( primary )
  {
    batches[ numBatches ].diffuse1.matrixRow1 = CVec4( m.m_[0][0], m.m_[0][1], m.m_[0][2], 0.f );
    batches[ numBatches ].diffuse1.matrixRow2 = CVec4( m.m_[1][0], m.m_[1][1], m.m_[1][2], 0.f );
    batches[ numBatches ].diffuse1.useDiffuse = true;
    batches[ numBatches ].diffuse1.texture = static_cast<BitmapInfoD3D*>( bi )->m_texture;
    batches[ numBatches ].diffuse1.textureMode = wm;
    batches[ numBatches ].diffuse1.smoothing = true;
  }
  else
  {
    batches[ numBatches ].diffuse2.matrixRow1 = CVec4( m.m_[0][0], m.m_[0][1], m.m_[0][2], 0.f );
    batches[ numBatches ].diffuse2.matrixRow2 = CVec4( m.m_[1][0], m.m_[1][1], m.m_[1][2], 0.f );
    batches[ numBatches ].diffuse2.useDiffuse = true;
    batches[ numBatches ].diffuse2.texture = static_cast<BitmapInfoD3D*>( bi )->m_texture;
    batches[ numBatches ].diffuse2.textureMode = wm;
    batches[ numBatches ].diffuse2.smoothing = true;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::SetLineWidth( float width )
{
  lineWidthHalf = width * 0.5f;// + PIXELS_TO_TWIPS( 1 ); 
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::SetLineColor( const flash::SWF_RGBA& color )
{
  lineColor.A = color.a;
  lineColor.R = color.r;
  lineColor.G = color.g;
  lineColor.B = color.b;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::DrawBitmap( IBitmapInfo* bi, float width, float height, int uniqueID, bool smoothing )
{
#if 1
  if ( !vertexBufferRaw )
    return;

  if ( numBatches >= MAX_BATCHES )
    return;

  if ( numVertices + 4 > MAX_VERTEX_COUNT )
    return;

  Batch& batch = batches[numBatches];

  batch.prepareFunc = &FlashRenderer::PrepareBitmap;

  float scaleU = bi->GetUV2().x - bi->GetUV1().x;
  float scaleV = bi->GetUV2().y - bi->GetUV1().y;

  batch.diffuse1.useDiffuse = true;
  batch.diffuse1.texture = static_cast<BitmapInfoD3D*>( bi )->m_texture;
  batch.diffuse1.matrixRow1 = CVec4( scaleU / width, 0.f, bi->GetUV1().x, 0.f );
  batch.diffuse1.matrixRow2 = CVec4( 0.f, scaleV / height, bi->GetUV1().y, 0.f );
  batch.diffuse1.scale9Grid = false;
  batch.diffuse1.textureMode = EBitmapWrapMode::CLAMP;
  batch.diffuse1.smoothing = smoothing;

  vertexBufferRaw[numVertices+0].x = 0.f; vertexBufferRaw[numVertices+0].textureUV.x = bi->GetUV1().x;
  vertexBufferRaw[numVertices+0].y = 0.f; vertexBufferRaw[numVertices+0].textureUV.y = bi->GetUV1().y;

  vertexBufferRaw[numVertices+1].x = 0.f; vertexBufferRaw[numVertices+1].textureUV.x = bi->GetUV1().x;
  vertexBufferRaw[numVertices+1].y = height; vertexBufferRaw[numVertices+1].textureUV.y = bi->GetUV2().y;

  vertexBufferRaw[numVertices+2].x = width; vertexBufferRaw[numVertices+2].textureUV.x = bi->GetUV2().x;
  vertexBufferRaw[numVertices+2].y = 0.f; vertexBufferRaw[numVertices+2].textureUV.y = bi->GetUV1().y;

  vertexBufferRaw[numVertices+3].x = width; vertexBufferRaw[numVertices+3].textureUV.x = bi->GetUV2().x;
  vertexBufferRaw[numVertices+3].y = height; vertexBufferRaw[numVertices+3].textureUV.y = bi->GetUV2().y;

  for ( int i = 0; i < 4; ++i )
  {
    vertexBufferRaw[numVertices + i].xShift = 0.f;
    vertexBufferRaw[numVertices + i].yShift = 0.f;
    vertexBufferRaw[numVertices + i].aliasing = 1.f;
    vertexBufferRaw[numVertices + i].aliasingScale = 1.f;
  }

  batch.dip.primitiveType = RENDERPRIMITIVE_TRIANGLESTRIP;
  batch.dip.baseVertexIndex = numVertices;	
  batch.dip.startIndex = numVertices;
  batch.dip.numVertices = 4;
  batch.dip.primitiveCount = 2;

  numVertices += 4;

  NextBatch();
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::AddRectangle( int firstVertex, float x1, float y1, float x2, float y2, float u1, float v1, float u2, float v2 )
{
  if ( !vertexBufferRaw )
    return;

  // first face
  vertexBufferRaw[firstVertex+0].x = x1; vertexBufferRaw[firstVertex+0].textureUV.x = u1;
  vertexBufferRaw[firstVertex+0].y = y1; vertexBufferRaw[firstVertex+0].textureUV.y = v1;
 
  vertexBufferRaw[firstVertex+1].x = x1; vertexBufferRaw[firstVertex+1].textureUV.x = u1;
  vertexBufferRaw[firstVertex+1].y = y2; vertexBufferRaw[firstVertex+1].textureUV.y = v2;

  vertexBufferRaw[firstVertex+2].x = x2; vertexBufferRaw[firstVertex+2].textureUV.x = u2;
  vertexBufferRaw[firstVertex+2].y = y1; vertexBufferRaw[firstVertex+2].textureUV.y = v1;

  // second face
  vertexBufferRaw[firstVertex+3].x = x1; vertexBufferRaw[firstVertex+3].textureUV.x = u1;
  vertexBufferRaw[firstVertex+3].y = y2; vertexBufferRaw[firstVertex+3].textureUV.y = v2;

  vertexBufferRaw[firstVertex+4].x = x2; vertexBufferRaw[firstVertex+4].textureUV.x = u2;
  vertexBufferRaw[firstVertex+4].y = y1; vertexBufferRaw[firstVertex+4].textureUV.y = v1;

  vertexBufferRaw[firstVertex+5].x = x2; vertexBufferRaw[firstVertex+5].textureUV.x = u2;
  vertexBufferRaw[firstVertex+5].y = y2; vertexBufferRaw[firstVertex+5].textureUV.y = v2;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::DrawBitmapScale9Grid( IBitmapInfo* bi, float width, float height, const flash::SWF_RECT& scale9Grid, float aspectX, float aspectY, int uniqueID, bool smoothing )
{
#if 1
  if ( !vertexBufferRaw )
    return;

  if ( numBatches >= MAX_BATCHES )
    return;

  if ( ( numVertices + 6 * 9 ) > MAX_VERTEX_COUNT )
    return;

  Batch& batch = batches[numBatches];

  batch.prepareFunc = &FlashRenderer::PrepareBitmap;

  batch.diffuse1.useDiffuse = true;
  batch.diffuse1.texture = static_cast<BitmapInfoD3D*>( bi )->m_texture;
  batch.diffuse1.scale9Grid = true;
  batch.diffuse1.textureMode = EBitmapWrapMode::CLAMP;
  batch.diffuse1.smoothing = smoothing;

  float u[4] = { 0.f, (scale9Grid.X1) / float( bi->GetWidth() ), (scale9Grid.X2 ) / float( bi->GetWidth() ), 1.f };
  float v[4] = { 0.f, (scale9Grid.Y1) / float( bi->GetHeight() ), (scale9Grid.Y2) / float( bi->GetHeight() ), 1.f };

  float x[4] = { 0.f, u[1] * width / aspectX, (1.f - (1.f - u[2] ) / aspectX) * width, width };
  float y[4] = { 0.f, v[1] * height / aspectY, (1.f - (1.f - v[2]) / aspectY) * height, height };

  float scaleU = bi->GetUV2().x - bi->GetUV1().x;
  float scaleV = bi->GetUV2().y - bi->GetUV1().y;

  for ( int  i = 0; i < 4; ++i )
  {
    u[i] = bi->GetUV1().x + u[i] * scaleU;
    v[i] = bi->GetUV1().y + v[i] * scaleV;
  }

  int nextID = 0;

  for ( int i = 0; i < 3; ++i )
  {
    for ( int j = 0; j < 3; ++j )
    {
      AddRectangle( numVertices + nextID, x[i], y[j], x[i+1], y[j+1], u[i], v[j], u[i+1], v[j+1] );
      nextID += 6;
    }
  }

  for ( int i = 0; i < 6 * 9; ++i )
  {
    vertexBufferRaw[numVertices + i].xShift = 0.f;
    vertexBufferRaw[numVertices + i].yShift = 0.f;
    vertexBufferRaw[numVertices + i].aliasing = 1.f;
    vertexBufferRaw[numVertices + i].aliasingScale = 1.f;
  }

  batch.dip.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
  batch.dip.baseVertexIndex = numVertices;	
  batch.dip.startIndex = numVertices;
  batch.dip.numVertices = 6 * 9;
  batch.dip.primitiveCount = 2 * 9;

  numVertices += 6 * 9;

  NextBatch();
#endif
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::BeginSubmitMask()
{
  if ( numBatches >= MAX_BATCHES )
    return;

  batches[ numBatches ].beginSubmitMask = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::EndSubmitMask()
{
  if ( numBatches >= MAX_BATCHES )
    return;

  batches[ numBatches ].endSubmitMask = true;
  batches[ numBatches ].visible = false;

  NextBatch();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::BeginUnSubmitMask()
{
  if ( numBatches >= MAX_BATCHES )
    return;

  batches[ numBatches ].beginUnsubmitMask = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::DisableMask()
{
  if ( numBatches >= MAX_BATCHES )
    return;

  batches[ numBatches ].disbaleMask = true;
  batches[ numBatches ].visible = false;

  NextBatch();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::BeginColorMatrix( const SHMatrix& _colorMatrix, const CVec4& _addColor )
{
  if ( numBatches >= MAX_BATCHES )
    return;

  batches[ numBatches ].colorMatrixBegin = true;
  batches[ numBatches ].colorMatrixEnd = false;
  batches[ numBatches ].colorMatrix = _colorMatrix;
  batches[ numBatches ].colorAdd = _addColor / 255.f;
  batches[ numBatches ].visible = false;

  NextBatch();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::ClearCaches()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::DebugNextBatch()
{
  if ( numBatches >= MAX_BATCHES )
    return;

  batches[ numBatches ].debug = true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::EndColorMatrix()
{
  if ( numBatches >= MAX_BATCHES )
    return;

  batches[ numBatches ].colorMatrixBegin = false;
  batches[ numBatches ].colorMatrixEnd = true;
  batches[ numBatches ].visible = false;

  NextBatch();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::RenderText( int _partID )
{
  if ( numBatches >= MAX_BATCHES )
    return;

  colorTransformCached = false;
  modelMatrixCached = false;

  batches[ numBatches ].isText = true;
  batches[ numBatches ].visible = false;
  batches[ numBatches ].hasBevel = nextTextWithBevel;
  batches[ numBatches ].bevelColor = bevelColor;
  batches[ numBatches ].textPartID = _partID;

  NextBatch();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::RenderTextBevel( bool withBevel, const flash::SWF_RGBA& _color, Texture* _fontTexture )
{
  nextTextWithBevel = withBevel;
  bevelColor = Render::HDRColor( _color.r / 255.f, _color.g / 255.f, _color.b / 255.f, _color.a / 255.f );
  fontTexture = _fontTexture;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::PrepareFontMaterial( BaseMaterial* _material, bool _drawBevel, const Render::HDRColor& _color )
{
  NDb::UIFontMaterial fontMaterialDesc;

  fontMaterialDesc.PrimaryColor = Render::HDRColor( 1.f, 1.f, 1.f, 1.f );
  fontMaterialDesc.SecondaryColor = _color;
  fontMaterialDesc.DrawContour = _drawBevel ? NDb::BOOLEANPIN_PRESENT : NDb::BOOLEANPIN_NONE;
  fontMaterialDesc.renderState.blendMode = NDb::BLENDMODE_LERPBYALPHA;

  fontMaterialDesc.DiffuseMap.samplerState.addressU = NDb::TEXTUREADDRESSTYPE_CLAMP;
  fontMaterialDesc.DiffuseMap.samplerState.addressV = NDb::TEXTUREADDRESSTYPE_CLAMP;
  fontMaterialDesc.DiffuseMap.samplerState.addressW = NDb::TEXTUREADDRESSTYPE_CLAMP;

  fontMaterialDesc.DiffuseMap.samplerState.magFilter = NDb::MAGFILTERTYPE_LINEAR;
  fontMaterialDesc.DiffuseMap.samplerState.minFilter = NDb::MINFILTERTYPE_LINEAR;
  fontMaterialDesc.DiffuseMap.samplerState.mipFilter = NDb::MIPFILTERTYPE_POINT;

  _material->FillMaterial( &fontMaterialDesc, 0, false );

  _material->SetUseDiffuse( NDb::BOOLEANPIN_PRESENT );

  if ( fontTexture )
    _material->GetDiffuseMap()->SetTexture( fontTexture );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::BeginSubmitMaskApply()
{
  if ( maskLevel == 0 )
  {
    GetDevice()->SetRenderState(D3DRS_STENCILENABLE, TRUE);
    GetDevice()->SetRenderState(D3DRS_STENCILFAIL, D3DSTENCILOP_KEEP);
    GetDevice()->SetRenderState(D3DRS_STENCILZFAIL, D3DSTENCILOP_KEEP);
    GetDevice()->SetRenderState(D3DRS_STENCILFUNC, D3DCMP_EQUAL );
    GetDevice()->SetRenderState(D3DRS_STENCILMASK, 0xFFFFFFFF);
    GetDevice()->SetRenderState(D3DRS_STENCILWRITEMASK, 0xFFFFFFFF);
//    GetDevice()->Clear(0, NULL, D3DCLEAR_STENCIL, 0, 1.0f, 0);
  }

  GetDevice()->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);
  GetDevice()->SetRenderState(D3DRS_STENCILREF, maskLevel);
  GetDevice()->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_INCR);

  maskLevel++;
}

void FlashRenderer::BeginUnSubmitMaskApply()
{
  GetDevice()->SetRenderState(D3DRS_COLORWRITEENABLE, 0x00000000);
  GetDevice()->SetRenderState(D3DRS_STENCILREF, maskLevel);
  GetDevice()->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_DECR);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::EndSubmitMaskApply()
{
  GetDevice()->SetRenderState(D3DRS_STENCILREF, maskLevel);
  GetDevice()->SetRenderState(D3DRS_STENCILPASS, D3DSTENCILOP_KEEP);
  GetDevice()->SetRenderState(D3DRS_COLORWRITEENABLE, 0x0000000F);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::DisableMaskApply()
{
  NI_ASSERT( maskLevel > 0, " Mask level is wrong! " );

  --maskLevel;

  if ( maskLevel > 0 )
  {
    EndSubmitMaskApply();
  }

  if ( maskLevel == 0 )
  {
    GetDevice()->SetRenderState( D3DRS_STENCILENABLE, FALSE );
    GetDevice()->SetRenderState( D3DRS_COLORWRITEENABLE, 0x0000000F );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void FlashRenderer::NextBatch()
{
  numBatches++;

  if ( numBatches >= MAX_BATCHES )
    return;

  batches[ numBatches ].Clear();
}

} // namespace Render

NI_DEFINE_REFCOUNT( Render::IBitmapInfo );

