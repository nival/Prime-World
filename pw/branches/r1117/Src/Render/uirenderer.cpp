#include "stdafx.h"

#include "uirenderer.hpp"

#include "FlashRendererInterface.h"
#include "TextureManager.h"
#include "smartrenderer.h"
#include "shadercompiler.h"
#include "../System/Float16.h"
#include "MaterialSpec.h"
#include "batch.h"
#include "GlobalMasks.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Render
{

DECLARE_NULL_RENDER_FLAG

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const UIRect noCrop(-1,-1,-1,-1);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static NDebug::DebugVar<int> render_QuadCounter( "UIQuads", "Render" );

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CAlignedFreeHelper
{
	void *p;
public:
	CAlignedFreeHelper( void *_p ): p( _p ) {}
	~CAlignedFreeHelper() { if (p) Aligned_Free(p); p = 0; }
	void Cancel() { p = 0; }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
IUIRenderer* GetUIRenderer()
{
  static DeviceLostWrapper<UIRenderer> uiRenderer;
  return &uiRenderer;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRenderer::UIRenderer() :
  initialized(false),
  queeOverflowed(false),
  resolutionCoefs( 1.0f, 1.0f, 0.0f, 0.0f ),
  projMatrix( CVec3(0, 0, 0) ),
  viewMatrix( CVec3(0, 0, 0) ), 
  invViewMatrix( CVec3(0, 0, 0) ),
  projViewMatrix( CVec3(0, 0, 0) ), 
  invProjViewMatrix( CVec3(0, 0, 0) ),
  mode(E3DMode::_2D),
  current3DBlock(NULL),

  saturationValue(0.f),
  saturationColor(1.f,1.f,1.f,1.f),
  saturate(false),
  forbidSaturate(false),

  que2D( ques[0] ),
  que3D( ques[1] )
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRenderer::~UIRenderer()
{

}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIRenderer::Initialize()
{
	if( initialized )
		return false;

  flashRenderer = new FlashRenderer();
  textureCache = new UITextureCache();

  // Check if compiler made any padding
  NI_STATIC_ASSERT( sizeof(VertexStride) == 28, VertexStride_size_wrong );
	NI_STATIC_ASSERT( sizeof(QuadStride) == 28*4, QuadStride_size_wrong );

		// Initialize vertex format
	{
		VertexFormatDescriptor formatDescriptor;
		formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 0, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_POSITION, 0) );
		formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 8, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_TEXCOORD, 0) );
		formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 16, VERTEXELEMENTTYPE_FLOAT2,VERETEXELEMENTUSAGE_TEXCOORD, 1) );
		formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 24, VERTEXELEMENTTYPE_D3DCOLOR, VERETEXELEMENTUSAGE_COLOR, 0) );

		pVDecl = SmartRenderer::GetVertexFormatDeclaration( formatDescriptor );
		dipDesc.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;
	}

		// Build indexes buffer
	{
		const int quadsIndexesCount = QUAD_INDEX_COUNT * QUAD_MAX_COUNT;
		unsigned int *pIndexes = (unsigned int *)Aligned_MAlloc( quadsIndexesCount * sizeof(unsigned int), 16 );
		if ( !pIndexes )
		{
			NI_ASSERT( 0, "UIRenderer: Failed to allocate memory (temporary indexes)!" );
			return false;
		}

		CAlignedFreeHelper freeIndexes( pIndexes );

		int quadVertex = 0;
		unsigned int *pIndex = pIndexes;
		for( unsigned int i = 0; i < quadsIndexesCount; i+=6 )
		{
			*pIndex++ = quadVertex;
			*pIndex++ = quadVertex + 1;
			*pIndex++ = quadVertex + 2;
			*pIndex++ = quadVertex;
			*pIndex++ = quadVertex + 2;
			*pIndex++ = quadVertex + 3;
			quadVertex += 4;
		}

		const int indexesSize = quadsIndexesCount * sizeof(unsigned int);
		pIB = CreateIB( indexesSize, RENDER_POOL_MANAGED, pIndexes );
		if ( !Get(pIB) )
		{
			NI_ASSERT( 0, "UIRenderer: Failed to create index buffer!" );
			return false;
		}
	}

  const int quadsVerticesSize = QUAD_MAX_COUNT * sizeof(QuadStride);

	// Create vertex buffer
	pVB.Resize(quadsVerticesSize);
	if ( !Get(pVB) )
	{
		NI_ASSERT( 0, "UIRenderer: Failed to create vertex buffer!" );
		return false;
	}

	// Other initializations
	SetResolutionCoefs( 1.0f / 1024.0f , 1.0f / 768.0f, 1024.f / 1280.f, 768.0f / 1024.f );

  //Reset transforms
  SHMatrix null(CVec3(0,0,0));
  projMatrix = null;
  viewMatrix = null;
  invViewMatrix = null;
  projViewMatrix = null;
  invProjViewMatrix = null;

  // Flash
  if ( !flashRenderer->Initialize() )
    return false;

  // Done
	initialized = true;
	StartFrame();
	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::Release()
{
	if ( !initialized )
		return;

  flashRenderer->Release();
  flashRenderer = 0;

  textureCache->Release();
  textureCache = 0;

  pVB.Reset();
	pIB = 0;
	pVDecl = 0;

	initialized = false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline UIRenderer::RenderQueue& UIRenderer::GetQueue()
{
  return ( E3DMode::_2D == mode ) ? que2D : que3D;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::StartFrame()
{
  if(RENDER_DISABLED)
    return;

  flashRenderer->StartFrame();

  render_QuadCounter.SetValue(que2D.quadCounter + que3D.quadCounter);
  for(int i = 0; i < 2; ++i)
  {
    ques[i].quadCounter = 0;
	  ques[i].quadFirstText = quadFirstTextOff;
    ques[i].parts.clear();
  }

  mode = E3DMode::_2D;
  current3DBlock = NULL;
  blocksSorter.clear();

	cropRects.clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::PushCrop( const UIRect & cropRect )
{
	cropRects.push_back( cropRect );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::PushNoCrop()
{
	cropRects.push_back( noCrop );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::PopCrop()
{
	NI_VERIFY( !cropRects.empty(), "UIRenderer: Crop rects stack underflow!", return );
	cropRects.pop_back();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UIRenderer::CropQuadInternal( UIQuad& quad, const UIRect & cropRect )
{
	CTRect<float> croppedRect( quad.tl.x, quad.tl.y,  quad.br.x, quad.br.y );
  CTRect<float> floatCropRect( cropRect );
	croppedRect.Intersect( floatCropRect );

	if ( croppedRect.minx >= croppedRect.maxx )
		return false;
	if ( croppedRect.miny >= croppedRect.maxy )
		return false;

	if ( quad.tl.x < croppedRect.x1 )
	{
		float dx = ( quad.br.x - quad.tl.x );
		float cx = ( croppedRect.x1 - quad.tl.x );
		quad.uv.u += (( quad.uvl.u - quad.uv.u ) * cx) / dx;
		quad.uv2.u += (( quad.uvl2.u - quad.uv2.u ) * cx) / dx;
		quad.tl.x = croppedRect.x1;
	}

	if ( quad.tl.y < croppedRect.y1 )
	{
		float dy = ( quad.br.y - quad.tl.y );
		float cy = ( croppedRect.y1 - quad.tl.y );
		quad.uv.v += (( quad.uvl.v - quad.uv.v ) * cy) / dy;
		quad.uv2.v += (( quad.uvl2.v - quad.uv2.v ) * cy) / dy;
		quad.tl.y = croppedRect.y1;
	}

	if ( quad.br.x > croppedRect.x2 )
	{
		float dx = ( quad.br.x - quad.tl.x );
		float cx = ( croppedRect.x2 - quad.br.x );
		quad.uvl.u += (( quad.uvl.u - quad.uv.u ) * cx) / dx;
		quad.uvl2.u += (( quad.uvl2.u - quad.uv2.u ) * cx) / dx;
		quad.br.x = croppedRect.x2;
	}

	if ( quad.br.y > croppedRect.y2 )
	{
		float dy = ( quad.br.y - quad.tl.y );
		float cy = ( croppedRect.y2 - quad.br.y );
		quad.uvl.v += (( quad.uvl.v - quad.uv.v ) * cy) / dy;
		quad.uvl2.v += (( quad.uvl2.v - quad.uv2.v ) * cy) / dy;
		quad.br.y = croppedRect.y2;
	}

	return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void ExtPointTransform( float & x, float & y, const CVec2 & pivot, float ksn, float kcs )
{
	float px = x - pivot.x;
	float py = y - pivot.y;
	float nx = pivot.x + px * kcs + py * ksn;
	float ny = pivot.y - px * ksn + py * kcs;
	x = nx;
	y = ny;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int UIRenderer::AddQuadInternal( const UIQuad & _quad, const Color& _color )
{
  RenderQueue & queue = GetQueue();
	NI_VERIFY( initialized, "UIRenderer: Not initialized!", return 0 );

  if(queue.quadCounter < QUAD_MAX_COUNT)
    queeOverflowed = false;
  else {
    NI_VERIFY_TRACE( queeOverflowed, "UIRenderer: Quads overflow!", queeOverflowed = true );
    return 0;
  }

  QuadStride & stride = queue.quadsQueue[queue.quadCounter];

	//	1-----0
	//	|		/	|
	//	|	 /  |
	//	|	/		|
	//	2-----3

//   const Render::RenderMode & renderMode = Render::GetRenderer()->GetCurrentRenderMode();
//   const float kw = renderMode.width > 0 ? ( float(1280) / float(renderMode.width) ) : 1.0f;
//   const float kh = renderMode.height > 0 ? ( float(1024) / float(renderMode.height) ) : 1.0f;

  const float shiftX = 0;//0.5f * kw; 
  const float shiftY = 0;//0.5f * kh; 

	////0
	stride.v0.x = _quad.br.x - shiftX;
	stride.v0.y = _quad.tl.y - shiftY;
	stride.v0.u = _quad.uvl.x;
	stride.v0.v = _quad.uv.y;
	stride.v0.u2 = _quad.uvl2.x;
	stride.v0.v2 = _quad.uv2.y;
	stride.v0.color.Dummy = _color.Dummy;
	////1
	stride.v1.x = _quad.tl.x - shiftX;
	stride.v1.y = _quad.tl.y - shiftY;
	stride.v1.u = _quad.uv.x;
	stride.v1.v = _quad.uv.y;
	stride.v1.u2 = _quad.uv2.x;
	stride.v1.v2 = _quad.uv2.y;
	stride.v1.color.Dummy = _color.Dummy;
	////2
	stride.v2.x = _quad.tl.x - shiftX;
	stride.v2.y = _quad.br.y - shiftY;
	stride.v2.u = _quad.uv.x;
	stride.v2.v = _quad.uvl.y;
	stride.v2.u2 = _quad.uv2.x;
	stride.v2.v2 = _quad.uvl2.y;
	stride.v2.color.Dummy = _color.Dummy;
	////3
	stride.v3.x = _quad.br.x - shiftX;
	stride.v3.y = _quad.br.y - shiftY;
	stride.v3.u = _quad.uvl.x;
	stride.v3.v = _quad.uvl.y;
	stride.v3.u2 = _quad.uvl2.x;
	stride.v3.v2 = _quad.uvl2.y;
	stride.v3.color.Dummy = _color.Dummy;

	if ( _quad.ext )
	{
		CVec2 pivot = _quad.pivot;
		pivot.x -=  shiftX;
		pivot.y -=  shiftY;
		float ksn = sinf( _quad.angle ) * _quad.scale;
		float kcs = cosf( _quad.angle ) * _quad.scale;
		ExtPointTransform( stride.v0.x, stride.v0.y, pivot, ksn, kcs );
		ExtPointTransform( stride.v1.x, stride.v1.y, pivot, ksn, kcs );
		ExtPointTransform( stride.v2.x, stride.v2.y, _quad.pivot, ksn, kcs );
		ExtPointTransform( stride.v3.x, stride.v3.y, _quad.pivot, ksn, kcs );

		// Following code is test for rotating/scaling quads:
		//SVector s( _quad.tl.x + (_quad.br.x - _quad.tl.x) * 0.66f, _quad.tl.y + (_quad.br.y - _quad.tl.y) * 0.3f );
		//_quad.SetExtParams( s, (GetTickCount() * 3.14f)/1000.0f, sinf(GetTickCount()*3.14f*0.001f)*2.0f+1.0f );
	}

	return ++queue.quadCounter;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::BeginFlashParts( int startFlashElement )
{
  RenderQueue & queue = GetQueue();

  queue.currentFlashPart = queue.parts.size();
  queue.parts.push_back( SRenderPart( startFlashElement, -1 ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::EndFlashParts( int _lastFlashElement )
{
  RenderQueue & queue = GetQueue();

  NI_VERIFY( queue.currentFlashPart >= 0, "Flash render parts was not started", return );

  SRenderPart & part = queue.parts[queue.currentFlashPart];

  NI_VERIFY( part.firstFlashElement >= 0, "", return );
  NI_VERIFY( _lastFlashElement >= part.firstFlashElement, "", return );

  part.lastFlashElement = _lastFlashElement;
  queue.currentFlashPart = -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::AddQuad( UIQuad & _quad, Render::BaseMaterial* _renderMaterial, const SMaterialParams & params )
{
  if ( !_renderMaterial )
    return;

  if ( !_quad.ext && !cropRects.empty() && !cropRects.back().IsSame( noCrop ) )
    if ( !CropQuadInternal( _quad, cropRects.back() ) )
      return;

  RenderQueue & queue = GetQueue();

  CVec4 color1, color2, coefs;

  _renderMaterial->ModifyCoefs( params.coef3, params.coef4 );
  coefs.z = params.coef3;
  coefs.w = params.coef4;

  const unsigned int next = AddQuadInternal( _quad, SaturateColor( params.color0 ) );
  bool startNewPart = false;

  if (next == 1 || ( mode == E3DMode::_3DNewBlock ))
  {
    startNewPart = true;
  }
  else
  {
    const SRenderPart & prev = queue.parts.back();

    if ( prev.renderMaterial != _renderMaterial )
      startNewPart = true;
  }

  if ( startNewPart )
  {
    queue.parts.push_back( SRenderPart( 
      _renderMaterial,
      next - 1, 1,
      color1, color2,
      coefs ) );

    if ( mode == E3DMode::_3DNewBlock )
      mode = E3DMode::_3D;
  }
  else
  {
    queue.parts.back().quadCount += 1; 
    NI_ASSERT( queue.parts.back().quadCount < MAX_DIP_LENGTH, "UIRenderer: Index buffer overflow #2!" );
  }

  queue.quadFirstText = quadFirstTextOff;

  flashRenderer->BreakQueue();  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::BeginText()
{
	GetQueue().quadFirstText = GetQueue().quadCounter;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::AddTextQuad( UIQuad & _quad, const SMaterialParams & params )
{
  RenderQueue & queue = GetQueue();
	NI_VERIFY( queue.quadFirstText != quadFirstTextOff, "UIRenderer: Trying to render text outside BeginText/EndText!", return );

	_quad.ext = false; // not supported for texts

	if ( !cropRects.empty() && !cropRects.back().IsSame( noCrop ) )
		if ( !CropQuadInternal( _quad, cropRects.back() ) )
			return;

  if ( queue.currentFlashPart >= 0 ) // in Flash
    AddQuadInternal( _quad, params.color0 );
  else
    AddQuadInternal( _quad, SaturateColor( params.color0 ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::EndText( Render::BaseMaterial* _renderMaterial )
{
  if ( !_renderMaterial )
    return;

  RenderQueue & queue = GetQueue();
	NI_VERIFY( queue.quadFirstText != quadFirstTextOff, "UIRenderer: Trying to render text outside BeginText/EndText!", return );
	const unsigned int quadLastText = queue.quadCounter;
	
	NI_VERIFY( queue.quadFirstText <= quadLastText, "UIRenderer: Text rendering failure!", return );

	const unsigned int len = quadLastText - queue.quadFirstText;
	if ( len == 0 )
		return;

	NI_ASSERT( len < MAX_DIP_LENGTH, "UIRenderer: Index buffer overflow #3!" );

 	CVec4 color1, color2, coefs;

  queue.parts.push_back( SRenderPart(
    _renderMaterial,
    queue.quadFirstText, len,
    color1, color2,
    coefs ) );

  if ( queue.currentFlashPart >= 0 )
  {
    flashRenderer->RenderText( queue.parts.size() - 1 );  
    queue.parts.back().textInFlash = true;
  }

  if ( mode == E3DMode::_3DNewBlock )
    mode = E3DMode::_3D;
		
	queue.quadFirstText = quadFirstTextOff;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::SetViewMatrices(const SHMatrix & view, const SHMatrix & projection)
{
  viewMatrix = view;
  projMatrix = projection;
  Invert(&invViewMatrix, viewMatrix);

  Multiply(&projViewMatrix, projection, view);
  Invert(&invProjViewMatrix, projViewMatrix);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::SetWorldMatrix(const SHMatrix & world, ETransformMode::Enum transformMode, const CVec3 & pivot, float depthBias)
{
  SHMatrix combined;
  Multiply(&combined, projViewMatrix, world);
 
  mode = E3DMode::_3DNewBlock;

  int firstPart = que3D.parts.size();

  float depth = CalcDepth(pivot);
  pair<BlocksSorter::iterator, bool> result =
    blocksSorter.insert(BlocksSorter::value_type(SBlockKey(-depth, blocksSorter.size()), Parts3DBlock(firstPart, 0, combined)));
  NI_ASSERT(result.second, "Parts 3D block was not inserted into map");

  current3DBlock = &result.first->second;

  if ( ETransformMode::DepthOnly == transformMode )
  {
    CVec4 t;
    combined.RotateHVector(&t, CVec4(0, 0, 0, 1));
    current3DBlock->forcedZ = t.z + depthBias;
    current3DBlock->forcedW = t.w;
    current3DBlock->transform.Set(CVec3(0, 0, 0));
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::ResetWorldMatrix()
{
  if ( current3DBlock && mode == E3DMode::_3D || mode == E3DMode::_3DNewBlock )
  {
    current3DBlock->size = que3D.parts.size() - current3DBlock->firstPart;
    current3DBlock = NULL;
  }

  mode = E3DMode::_2D;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::GetBillboardMatrix(SHMatrix * pCombined, const SHMatrix & world, ETransformMode::Enum transformMode, const CVec3 & pivot, float depthBias)
{
  //FIXME: Не очень оптимальная работа с матицами
  //TODO: iA: Надо бы упростить расчет матриц; Думаю, можно свести все к 3-4 умножениям в самом сложном случае

  //Rotation = PivotOffset * (~viewMatrix) * swap * (~PivotOffset);
  SHMatrix RotLeft;
  SHMatrix tmp = viewMatrix;
  for(int i = 0; i < 3; ++i) tmp.m[i][3] = 0;
  Invert(&RotLeft, tmp);

  for(int i = 0; i < 3; ++i) RotLeft.m[i][3] = pivot[i];

  SHMatrix RotRight(
    1, 0, 0, -pivot.x,
    0, 0, 1, -pivot.z,
    0, 1, 0, -pivot.y + depthBias,
    0, 0, 0, 1
    );

  SHMatrix Rotation;
  Multiply(&Rotation, RotLeft, RotRight);

/*
  Render::Color C[3] = {Color(0xffff0000), Color(0xff00ff00), Color(0xff0000ff)};
  for(int i = 0; i < 3; ++i)
  {
    CVec3 X(0,0,0);
    X[i] = 5;
    CVec3 A, B;
    Rotation.RotateHVector(&A, pivot);
    Rotation.RotateHVector(&B, pivot + X * 2);
    Render::DebugRenderer::DrawLine3D(A, B, C[i], C[i], false);
    Render::DebugRenderer::DrawLine3D(pivot, pivot + X, C[i], C[i], false);
  }
*/
  if ( transformMode == ETransformMode::AxisBillboard )
  {
    const CVec3 axis(0, 0, 1);
    CVec3 tAxis;
    Rotation.RotateVector(&tAxis, axis);
    Normalize(&tAxis);
    CVec3 XP = axis ^ tAxis;
    float XPLen = XP.Length();
    float angle = asinf(XPLen); //FIXME: we just ignore 180 grad case
    if(fabs(angle) > 1e-4f)
    {
      XP /= XPLen;
      CQuat q(-angle, XP, false);
      SHMatrix axisFix(q);

      Rotation = SHMatrix(pivot) * axisFix * SHMatrix(-pivot) * Rotation;
      //Multiply(&tmp, axisFix, RotLeft);
      //RotLeft = tmp;
    }
  }

  //*pCombined = Rotation * world
  Multiply(pCombined, Rotation, world);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::GetRay(CVec3 * pOrigin, CVec3 * pDir, int sx, int sy)
{
  invViewMatrix.RotateHVector(pOrigin, CVec3(0, 0, 0));

  CVec4 point, screen(sx * resolutionCoefs.x - 1.0f, 1.0f - sy * resolutionCoefs.y, 1.0f, 1.0f);
  invProjViewMatrix.RotateHVector(&point, screen);

  for(int i = 0; i < 3; ++i)
    (*pDir)[i] = point[i] / point.w - (*pOrigin)[i];
  Normalize(pDir);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float UIRenderer::CalcDepth(const CVec3 & point)
{
  CVec3 localPos;
  viewMatrix.RotateHVector(&localPos, point);
  return localPos.z;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::SetResolutionCoefs( const float x, const float y, const float widthScale, const float heightScale )
{
	resolutionCoefs.x = x;
	resolutionCoefs.y = y;
  resolutionCoefs.z = widthScale;
  resolutionCoefs.w = heightScale;

  flashRenderer->SetResolutionCoefs( x, y, widthScale, heightScale );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const CVec4& UIRenderer::GetResolutionCoefs() const
{
  return resolutionCoefs;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::SetFontTextureSize( const int width, const int height )
{
  fontTextureSize.z = width;
  fontTextureSize.w = height;
  fontTextureSize.x = fontTextureSize.z > 0 ? 1.0f / fontTextureSize.z : 0.0f;
  fontTextureSize.y = fontTextureSize.w > 0 ? 1.0f / fontTextureSize.w : 0.0f;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::RenderPart( const SRenderPart & part, bool alphaTest )
{
  if ( part.renderMaterial )
    part.renderMaterial->PrepareRenderer();

  if ( alphaTest )
    GetDevice()->SetRenderState( D3DRS_ALPHATESTENABLE, TRUE );

  dipDesc.baseVertexIndex = part.quadFirst * QUAD_VERTEX_COUNT;	
  dipDesc.numVertices = part.quadCount * QUAD_VERTEX_COUNT;
  dipDesc.primitiveCount = part.quadCount * QUAD_PRIMITIVE_COUNT;

  SmartRenderer::DrawIndexedPrimitive( dipDesc );

  if ( alphaTest )
    GetDevice()->SetRenderState( D3DRS_ALPHATESTENABLE, FALSE );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::BeginQueue()
{
  if(RENDER_DISABLED)
    return;

  StartFrame();
  flashRenderer->BeginQueue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::EndQueue()
{
  if(RENDER_DISABLED)
    return;
  flashRenderer->EndQueue();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::Render( ERenderWhat::Enum what, const Render::Texture2DRef& pMainRT0, const Render::Texture2DRef& pMainRT0Copy )
{
	if ( !initialized )
		return;

  RenderQueue & queue = (what == ERenderWhat::_2D) ? que2D : que3D;

	if( queue.quadCounter == 0 )
		return;

	if ( ERenderWhat::_2D == what )
  {
	  GetStatesManager()->SetStateDirect( D3DRS_ZENABLE, D3DZB_FALSE );
  }
  else if ( ERenderWhat::_3D == what )
  {
    GetStatesManager()->SetStateDirect( D3DRS_ZENABLE, D3DZB_TRUE );
    GetStatesManager()->SetStateDirect( D3DRS_ZWRITEENABLE, FALSE );
  }
  else
  {
    NI_ALWAYS_ASSERT("Dont know what to render");
  }

  GetStatesManager()->SetStateDirect( D3DRS_CULLMODE, D3DCULL_NONE );

	FillVB( Get(pVB), queue.quadCounter * sizeof(QuadStride), &queue.quadsQueue, D3DLOCK_DISCARD );

	GetRenderer()->SetPixelShaderConstantsVector4( PSHADER_LOCALCONST3, resolutionCoefs );
	GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST3, resolutionCoefs );

  // Font Texture size
  GetRenderer()->SetPixelShaderConstantsVector4( PSHADER_LOCALCONST2, fontTextureSize );
  GetRenderer()->SetVertexShaderConstantsVector4( VSHADER_LOCALCONST2, fontTextureSize );

  bool wasFlash = true; // to bind buffers at first part

  if ( ERenderWhat::_2D == what )
  {
	  for( int i = 0; i < queue.parts.size(); ++i )
    {
      SRenderPart& renderPart = queue.parts[i];

      if ( renderPart.textInFlash )
        continue;

      if ( renderPart.flashElement )
      {
        NI_ASSERT( renderPart.lastFlashElement >= 0, "Not finished flash render part!" );
        flashRenderer->Render( renderPart.firstFlashElement, renderPart.lastFlashElement, pMainRT0, pMainRT0Copy );
        wasFlash = true;
      }
      else
      {
        if ( wasFlash )
        {
          PrepareRender();
        }

        RenderPart( queue.parts[i], false );

        wasFlash = false;
      }
    }
  }
  else //what == eRender3D
  {
    PrepareRender();

    for ( BlocksSorter::iterator it = blocksSorter.begin(); it != blocksSorter.end(); ++it )
    {
      const Parts3DBlock & block = it->second;

      GetRenderer()->SetVertexShaderConstantsMatrix( WORLD, block.transform );
      GetRenderer()->SetVertexShaderConstantsFloat( VSHADER_LOCALCONST5, block.forcedZ );
      GetRenderer()->SetVertexShaderConstantsFloat( VSHADER_LOCALCONST6, block.forcedW );

      for ( int i = 0; i < block.size; ++i )
      {
        int partIdx = block.firstPart + i;
        NI_ASSERT(partIdx >= 0 && partIdx < queue.parts.size(), "Part index out of range");
        RenderPart( queue.parts[partIdx], false );
      }
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::RenderPart( int _partID, ERenderWhat::Enum what, bool alphaTest )
{
  RenderQueue & queue = (what == ERenderWhat::_2D) ? que2D : que3D;
  NI_ASSERT( _partID >= 0 && _partID < queue.parts.size(), "Part index out of range" );
  RenderPart( queue.parts[_partID], alphaTest );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseMaterial* UIRenderer::GetPartMaterial( int _partID, ERenderWhat::Enum what )
{
  RenderQueue & queue = (what == ERenderWhat::_2D) ? que2D : que3D;
  NI_VERIFY( _partID >= 0 && _partID < queue.parts.size(), "Part index out of range", return 0 );
  return queue.parts[_partID].renderMaterial;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::PrepareRender()
{
  const Render::RenderMode & renderMode = Render::GetRenderer()->GetCurrentRenderMode();

  SmartRenderer::BindVertexDeclaration( pVDecl );
  SmartRenderer::BindIndexBuffer( pIB );
  SmartRenderer::BindVertexBuffer( 0, Get(pVB), sizeof(VertexStride)	);

  //Clean combined transform matrix
  GetRenderer()->SetVertexShaderConstantsMatrix( WORLD, SHMatrix( CVec3( -1.f / renderMode.width, +1.f / renderMode.height, 0 )) );
  GetRenderer()->SetVertexShaderConstantsFloat( VSHADER_LOCALCONST5, 0.0f );
  GetRenderer()->SetVertexShaderConstantsFloat( VSHADER_LOCALCONST6, 1.0f );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::PrepareRenderFromFlash()
{
  SmartRenderer::BindVertexDeclaration( pVDecl );
  SmartRenderer::BindIndexBuffer( pIB );
  SmartRenderer::BindVertexBuffer( 0, Get(pVB), sizeof(VertexStride)	);
  
  GetRenderer()->SetVertexShaderConstantsFloat( VSHADER_LOCALCONST5, 0.0f );
  GetRenderer()->SetVertexShaderConstantsFloat( VSHADER_LOCALCONST6, 1.0f );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderer::SetSaturation( float _val, const CVec4& _color, bool _saturate )
{
  saturationValue = _val;
  saturationColor = _color; 
  saturate = _saturate;
}

bool UIRenderer::ForbidSaturation( bool _forbid)
{
  bool oldValue = forbidSaturate;
  forbidSaturate = _forbid;
  return oldValue;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::Color UIRenderer::SaturateColor( const Render::Color& _color )
{
  if ( !saturate || forbidSaturate )
    return _color;

  return Render::Color( Render::Saturate( Render::HDRColor( _color ), saturationValue, saturationColor ) );  
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRenderMaterial::UIRenderMaterial() :
  renderMaterial( 0 ),
  texturePoolId( 0 )
{
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRenderMaterial::UIRenderMaterial( const UIRenderMaterial& other ) :
  renderMaterial( 0 ),
  texturePoolId( 0 )
{
  SetDBMaterial( other.dbMaterial, other.texturePoolId );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRenderMaterial& UIRenderMaterial::operator = ( const UIRenderMaterial& other )
{
  SetDBMaterial( other.dbMaterial, other.texturePoolId );

  return *this;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRenderMaterial::UIRenderMaterial( const NDb::BaseUIMaterial* _material ) :
  renderMaterial( 0 ),
  texturePoolId( 0 )
{
  SetDBMaterial( _material, 0 );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRenderMaterial::UIRenderMaterial( const NDb::BaseUIMaterial* _material, void * _texturePoolId ) :
  renderMaterial( 0 )
{
  SetDBMaterial( _material, _texturePoolId );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UIRenderMaterial::~UIRenderMaterial()
{
  if ( renderMaterial )
    delete renderMaterial;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void  UIRenderMaterial::Release()
{
  if ( renderMaterial )
    delete renderMaterial;

  renderMaterial = 0;
  dbMaterial = 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderMaterial::CreateDefaultMaterial()
{
  renderMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterial( NDb::UIBaseMaterial::typeId ) );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UIRenderMaterial::SetDBMaterial( const NDb::BaseUIMaterial * _material, void * _texturePoolId, bool forceReload /*= false*/ )
{
  if ( (_material == dbMaterial) && !forceReload && renderMaterial )
    return;

  dbMaterial = _material;

  if ( IsValid( dbMaterial ) )
  {
    if ( renderMaterial )
      delete renderMaterial;

    renderMaterial = static_cast<Render::BaseMaterial*>( Render::CreateRenderMaterialInPool( dbMaterial, _texturePoolId ) );
    texturePoolId = _texturePoolId;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::BaseMaterial* UIRenderMaterial::GetRenderMaterial()
{
  return renderMaterial;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::BaseUIMaterial* UIRenderMaterial::GetDBMaterial() const
{
  return dbMaterial;
}


} // namespace Render
