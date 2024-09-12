#include "stdafx.h"

#include "../System/Singleton.h"
#include "../System/FastMath.h"
#include "../System/InlineProfiler.h"

#include "aabb.h"
#include "debugrenderer.h"
#include "smartrenderer.h"
#include "renderresourcemanager.h"
#include "shadercompiler.h"
#include "ConvexVolume.h"
#include "batch.h"

#define DEBUG_VSHADER_CONST0  0
#define DEBUG_VSHADER_CONST4  4
#define DEBUG_VSHADER_CONST8  8

static bool drawGrid = false;
DEV_VAR_STATIC bool renderDataInitialized = false;

DEFINE_DEV_VAR(g_wireframeGroupIndex, 0, "wireframe_grp", STORAGE_NONE);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static NDebug::DebugVar<float> gpuMemoryReserved ( "DebugGpuMemReserved", "DebugRender" );
static NDebug::DebugVar<float> gpuMemoryUsed     ( "DebugGpuMemUsed", "DebugRender" );

namespace Render
{

#ifdef _DEBUG
  void WireframeEnable(bool enable, WireframeGroup groupIndex)
  {
    if (groupIndex == g_wireframeGroupIndex)
      GetStatesManager()->SetStateDirect(D3DRS_FILLMODE, enable ? D3DFILL_WIREFRAME : D3DFILL_SOLID);
  }
#else
  void WireframeEnable(bool , WireframeGroup ) {}
#endif


namespace DebugRenderer
{

// Forward declarations
void DrawLines2D(int &vbOffset);
void DrawLines3D(int &vbOffset);
void DrawPoints3D(int &vbOffset);
void DrawPoints2D(int &vbOffset);

struct VertexStride
{
	float x, y, z, u;
	Render::Color color;
};

struct PointVertexStride
{
	float x, y, z;
	float uv[2];
	Render::Color color;
};

struct Points
{
	PointVertexStride p[4];
};

struct UberLine
{
	VertexStride p1, p2;
};

struct SDebugText2D
{
  wstring   text;
  CVec2     uiCoords;
  int       size;
  Render::Color color;
  ETextHAlign hAlign;
  ETextVAlign vAlign;
};

struct SDebugText3D
{
  wstring   text;
  CVec3     pos;
  int       size;
  Render::Color color;
  ETextHAlign hAlign;
  ETextVAlign vAlign;
};

struct PrimBuffer
{
  nstl::vector<UberLine> lines2D, lines3D, lines3DZ;
  nstl::vector<Points> points2D, points3D, points3DZ;
  nstl::vector<SDebugText2D> debugTexts2D;
  nstl::vector<SDebugText3D> debugTexts3D;

  int GetMemoryUsed2D() { return sizeof(UberLine) * lines2D.size() + sizeof(Points) * points2D.size(); }
  int GetMemoryUsed3D() { return sizeof(UberLine) * ( lines3D.size() + lines3DZ.size() ) +
                                 sizeof(Points)   * ( points3D.size() + points3DZ.size() ); }

  void Clear()
  {
    lines3D.clear();
    lines3DZ.clear();
    points3D.clear();
    points3DZ.clear();

    lines2D.clear();
    points2D.clear();

    debugTexts2D.clear();
    debugTexts3D.clear();
  }
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct RenderData : public Singleton<RenderData>
{
  static const unsigned int MIN_MEMORY_COUNT = 1 * 1024 * 1024;
  static const unsigned int MAX_MEMORY_COUNT = 100 * 1024 * 1024;
  
  // @BVS@SHADERS ARE NOT REMOVED!!!
  DXPixelShaderRef pLine2D_SimplePS;
  DXPixelShaderRef pLine3D_SimplePS;
  DXPixelShaderRef pPoint3D_SimplePS;
  DXPixelShaderRef pPoint2D_SimplePS;
  DXVertexShaderRef pUberLine2DVS;
  DXVertexShaderRef pUberLine3DVS;
  DXVertexShaderRef pPoint3D_SimpleVS;
  DXVertexShaderRef pPoint2D_SimpleVS;
  
  bool debugRendererInitialized;
  
  DipDescriptor debugDipDescriptor;
	DXVertexDeclarationRef   pLinesVDecl;
	DXVertexDeclarationRef   pPointsVDecl;
  DipDescriptor debugPointsDipDescriptor;

  DXVertexBufferDynamicRef::Wrapped pVertexBuffer;
  DXIndexBufferRef         pIndexBuffer;
  int curMaxMemoryCount;
  
  nstl::vector<DebugRenderBuffer> bufferStack;
  
  FixedVector<PrimBuffer, DRBUFFER_COUNT> buffers;
  PrimBuffer &CurBuffer() { return buffers[bufferStack.back()]; }
  
//             ITexture2D* pTexture;
//             
//             CVec2 debugRendererBaseResolution = CVec2(1024,768);

  SHMatrix viewMatrix;
  SHMatrix projMatrix;
  ConvexVolume frustum;

  RenderData();
  ~RenderData();

  bool InitBuffers(int vbSize);
  void DestroyBuffers();
  bool TryToAllocateMemory(int addition);
  void PrepareData3D();
  void PrepareData2D();

  int GetMemoryUsed2D();
  int GetMemoryUsed3D();
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RenderData::RenderData()
: pLine2D_SimplePS(0)
  , pLine3D_SimplePS(0)
  , pPoint3D_SimplePS(0)
  , pPoint2D_SimplePS(0)
  , pUberLine2DVS(0)
  , pUberLine3DVS(0)
  , pPoint3D_SimpleVS(0)
  , pPoint2D_SimpleVS(0)
//             , debugRendererInitialized(0)
  , curMaxMemoryCount(0)
{
  // check if compiler made any padding
  NI_STATIC_ASSERT( sizeof(VertexStride) == 20, VertexStride_size_wrong );
  NI_STATIC_ASSERT( sizeof(UberLine) == sizeof(VertexStride)*2, LineStride_size_wrong );
  NI_STATIC_ASSERT( sizeof(PointVertexStride) == 24, VertexStride_size_wrong );
  NI_STATIC_ASSERT( sizeof(Points) == sizeof(PointVertexStride)*4, LineStride_size_wrong );

#ifndef _SHIPPING
//             if( debugRendererInitialized )
//             {
//                 return;
//             }
// 
//             //pTexture = RenderResourceManager::Load2DTextureFromFile( "../Data/line1d.dds" );
// 
//             debugRendererInitialized = true;

  if( Compatibility::IsRunnedUnderWine() )  
    return;

  NI_PROFILE_FUNCTION

  VertexFormatDescriptor formatDescriptor;
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 0, VERTEXELEMENTTYPE_FLOAT3, VERETEXELEMENTUSAGE_POSITION, 0) );
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 12, VERTEXELEMENTTYPE_FLOAT1, VERETEXELEMENTUSAGE_TEXCOORD, 0) );
  formatDescriptor.AddVertexElement( VertexElementDescriptor(0, 16, VERTEXELEMENTTYPE_D3DCOLOR, VERETEXELEMENTUSAGE_COLOR, 0) );

  VertexFormatDescriptor formatDescriptorPoint;
  formatDescriptorPoint.AddVertexElement( VertexElementDescriptor(0, 0, VERTEXELEMENTTYPE_FLOAT3, VERETEXELEMENTUSAGE_POSITION, 0) );
  formatDescriptorPoint.AddVertexElement( VertexElementDescriptor(0, 12, VERTEXELEMENTTYPE_FLOAT2, VERETEXELEMENTUSAGE_TEXCOORD, 0) );
  formatDescriptorPoint.AddVertexElement( VertexElementDescriptor(0, 20, VERTEXELEMENTTYPE_D3DCOLOR, VERETEXELEMENTUSAGE_COLOR, 0) );

  pLinesVDecl = SmartRenderer::GetVertexFormatDeclaration(formatDescriptor);
  debugDipDescriptor.primitiveType = RENDERPRIMITIVE_LINELIST;
  pPointsVDecl = SmartRenderer::GetVertexFormatDeclaration(formatDescriptorPoint);
  debugPointsDipDescriptor.primitiveType = RENDERPRIMITIVE_TRIANGLELIST;

  debugPointsDipDescriptor.baseVertexIndex = 0;
  debugPointsDipDescriptor.numVertices = 4;
  debugPointsDipDescriptor.primitiveCount = 2;
  debugPointsDipDescriptor.startIndex = 0;

  pUberLine2DVS = CompileVertexShaderFromFile("deprecated_shaders/debug_shader.hlsl");
  pLine2D_SimplePS = CompilePixelShaderFromFile("deprecated_shaders/debug_shader.hlsl");

  pUberLine3DVS = CompileVertexShaderFromFile("deprecated_shaders/debug3d_shader.hlsl");
  pLine3D_SimplePS = CompilePixelShaderFromFile("deprecated_shaders/debug3d_shader.hlsl");

  pPoint3D_SimpleVS = CompileVertexShaderFromFile("deprecated_shaders/debug_points3d_shader.hlsl");;
  pPoint3D_SimplePS = CompilePixelShaderFromFile("deprecated_shaders/debug_points3d_shader.hlsl");;

  pPoint2D_SimpleVS = CompileVertexShaderFromFile("deprecated_shaders/debug_points2d_shader.hlsl");;
  pPoint2D_SimplePS = CompilePixelShaderFromFile("deprecated_shaders/debug_points2d_shader.hlsl");;

  gpuMemoryReserved.SetValue(0);
  gpuMemoryUsed.SetValue(0);

  renderDataInitialized = true;
#endif // _SHIPPING
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RenderData::~RenderData()
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RenderData::InitBuffers(int vbSize)
{
#ifdef _SHIPPING
  return false;
#else
  bool bRet = pVertexBuffer.Resize(vbSize);
  NI_VERIFY(bRet, "Failed to create vertex buffer", return bRet;);

  const int INDEX_COUNT_PER_QUAD = 6;
  int ibSize = (vbSize / sizeof(Points)) * INDEX_COUNT_PER_QUAD * sizeof(unsigned int);
  pIndexBuffer = CreateIB( ibSize, RENDER_POOL_MANAGED );
  NI_VERIFY(pIndexBuffer, "Failed to create index buffer", return false;);
  unsigned int* pIBData = LockIB( ::Get(pIndexBuffer), 0 );
  int quadNum = 0;
  for( int i = 0, endI = ibSize / sizeof(unsigned int); i < endI; i+=6 )
  {
      pIBData[i+0] = quadNum * 4 + 0;
      pIBData[i+1] = quadNum * 4 + 2;
      pIBData[i+2] = quadNum * 4 + 1;

      pIBData[i+3] = quadNum * 4 + 0;
      pIBData[i+4] = quadNum * 4 + 3;
      pIBData[i+5] = quadNum * 4 + 2;
      ++quadNum;
  }
  pIndexBuffer->Unlock();
  return bRet;
#endif // _SHIPPING
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderData::DestroyBuffers()
{
  if (curMaxMemoryCount == 0)
    return;

  pVertexBuffer.Reset();
  pIndexBuffer = 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RenderData::GetMemoryUsed2D()
{
  int size = 0;
  for(int i = 0; i < DRBUFFER_COUNT; ++i)
  {
    size += buffers[i].GetMemoryUsed2D();
  }

  return size;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int RenderData::GetMemoryUsed3D()
{
  int size = 0;
  for(int i = 0; i < DRBUFFER_COUNT; ++i)
  {
    size += buffers[i].GetMemoryUsed3D();
  }

  return size;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RenderData::TryToAllocateMemory(int addition)
{
#ifdef _SHIPPING
  return false;
#else
  int memoryUsed = GetMemoryUsed2D() + GetMemoryUsed3D();
  if (memoryUsed + addition < curMaxMemoryCount)
    return true;
  if (curMaxMemoryCount + MIN_MEMORY_COUNT > MAX_MEMORY_COUNT)
    return false;

  DestroyBuffers();
  curMaxMemoryCount += MIN_MEMORY_COUNT;
  
  bool bRet = InitBuffers(curMaxMemoryCount);
  NI_VERIFY(bRet, "Fail to init buffers.", return bRet;);

  gpuMemoryReserved.SetValue(curMaxMemoryCount);

  return bRet;
#endif // _SHIPPING
}


#define PrepareVertexBuffer(field, unitType)                        \
{                                                                   \
  for (int i = 0; i < DRBUFFER_COUNT; ++i)                          \
  {                                                                 \
    vector<unitType> &v = RenderData::Get()->buffers[i].field;      \
    int size = v.size() * sizeof(unitType);                         \
    if (size > 0)                                                   \
    {                                                               \
      memcpy(vbData, &v[0], size);                                  \
      vbData += size;                                               \
    }                                                               \
  }                                                                 \
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderData::PrepareData3D()
{
  int vbSize = GetMemoryUsed3D();

  if (vbSize == 0)
    return;

  if( char *vbData = LockVB<char>(::Get(pVertexBuffer), D3DLOCK_DISCARD, vbSize) )
  {
    PrepareVertexBuffer(points3D , Points);
    PrepareVertexBuffer(points3DZ, Points);
    PrepareVertexBuffer(lines3D  , UberLine);
    PrepareVertexBuffer(lines3DZ , UberLine);

    pVertexBuffer->Unlock();
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RenderData::PrepareData2D()
{
  if( int vbSize = GetMemoryUsed3D() + GetMemoryUsed2D() )
    if( char *vbData = LockVB<char>(::Get(pVertexBuffer), D3DLOCK_DISCARD, vbSize) ) 
    {
      vbData += GetMemoryUsed3D();

      PrepareVertexBuffer(points2D, Points);
      PrepareVertexBuffer(lines2D , UberLine);

      pVertexBuffer->Unlock();
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetMatrix(const SHMatrix& view, const SHMatrix& proj)
{
  if ( !renderDataInitialized )
    return;

  RenderData::Get()->viewMatrix = view;
	RenderData::Get()->projMatrix = proj;
  
  SHMatrix viewProj;
  Multiply(&viewProj, proj, view);
  RenderData::Get()->frustum.BuildFrustum(viewProj);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void SetupConstants()
{
#ifndef _SHIPPING
	Render::GetRenderer()->SetVertexShaderConstantsMatrix(DEBUG_VSHADER_CONST0, RenderData::Get()->viewMatrix);
	Render::GetRenderer()->SetVertexShaderConstantsMatrix(DEBUG_VSHADER_CONST4, RenderData::Get()->projMatrix);
#endif // _SHIPPING
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CheckInitialized()
{
#ifdef _SHIPPING
  return false;
#else
  NI_PROFILE_FUNCTION

  if ( !renderDataInitialized )
  {
    RenderData::Init();
    RenderData::Get()->buffers.setsize(DRBUFFER_COUNT);
    RenderData::Get()->bufferStack.push_back(DRBUFFER_DEFAULT);
  }
  return renderDataInitialized;
#endif // _SHIPPING
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Initialize()
{
#ifdef _SHIPPING
  return false;
#else
  return true;
#endif // _SHIPPING
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PushBuffer(DebugRenderBuffer buf)
{
  if( CheckInitialized() )
    RenderData::Get()->bufferStack.push_back(buf);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PopBuffer()
{
  if( CheckInitialized() )
  {
    NI_VERIFY(RenderData::Get()->bufferStack.size() > 1, "Pop without push", return;);
    RenderData::Get()->bufferStack.pop_back();
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawLine2D( int x1, int y1, int x2, int y2, Render::Color color1, Render::Color color2 )
{
  if( !CheckInitialized() )
    return;

  NI_VERIFY( RenderData::Get()->TryToAllocateMemory(sizeof(UberLine)), "Debug draw limit reached", return );

  UberLine line;

	line.p1.x = x1 + 0.5f;
	line.p1.y = y1 - 0.5f;
	line.p1.z = 0;
	line.p1.u = 0;
  line.p1.color.Dummy = color1.Dummy;

	line.p2.x = x2 + 0.5f;
	line.p2.y = y2 - 0.5f;
	line.p2.z = 0;
	line.p2.u = 1;
	line.p2.color.Dummy = color2.Dummy;

  RenderData::Get()->CurBuffer().lines2D.push_back(line);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawLine3D( const CVec3& p1, const CVec3& p2, Render::Color color1, Render::Color color2, bool zTest )
{
  if( !CheckInitialized() )
    return;

  // discard line if it's outside
  ConvexVolume const& f = RenderData::Get()->frustum;
  if ((f.CalculateClipCodes(p1) & f.CalculateClipCodes(p2)) != 0)
    return;

  NI_VERIFY( RenderData::Get()->TryToAllocateMemory(sizeof(UberLine)), "Debug draw limit reached", return );

  UberLine line;
	line.p1.x = p1.x;
	line.p1.y = p1.y;
	line.p1.z = p1.z;
	line.p1.u = 0;
	line.p1.color.Dummy = color1.Dummy;

	line.p2.x = p2.x;
	line.p2.y = p2.y;
	line.p2.z = p2.z;
	line.p2.u = 0;
	line.p2.color.Dummy = color2.Dummy;

	if(zTest)
    RenderData::Get()->CurBuffer().lines3DZ.push_back(line);
	else
    RenderData::Get()->CurBuffer().lines3D.push_back(line);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawPoint3D( const CVec3& p, float size, Render::Color color, bool zTest )
{
  if( !CheckInitialized() )
    return;

  // discard point if it's outside
  ConvexVolume const& f = RenderData::Get()->frustum;
  if (f.CalculateClipCodes(p) != 0)
    return;

  NI_VERIFY( RenderData::Get()->TryToAllocateMemory(sizeof(Points)), "Debug draw limit reached", return );

  Points point;

  for (int i = 0, endI = 4; i != endI; ++i)
  {
    point.p[i].x = p.x;
  	point.p[i].y = p.y;
	  point.p[i].z = p.z;
   	point.p[i].color = color;
  }
	point.p[0].uv[0] = size;
	point.p[0].uv[1] = -size;
	point.p[1].uv[0] = -size;
	point.p[1].uv[1] = -size;
	point.p[2].uv[0] = -size;
	point.p[2].uv[1] = size;
	point.p[3].uv[0] = size;
	point.p[3].uv[1] = size;

  if (zTest)
		RenderData::Get()->CurBuffer().points3DZ.push_back(point);
  else
    RenderData::Get()->CurBuffer().points3D.push_back(point);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawPoint2D( const int x, const int y, float size, Render::Color color )
{
  if( !CheckInitialized() )
    return;

  NI_VERIFY( RenderData::Get()->TryToAllocateMemory(sizeof(Points)), "Debug draw limit reached", return );

	Points point;
  for (int i = 0, endI = 4; i != endI; ++i)
  {
    point.p[i].x = x - 0.5f;
  	point.p[i].y = y - 0.5f;
   	point.p[i].color = color;
  }
	point.p[0].uv[0] = size;
	point.p[0].uv[1] = -size;
	point.p[1].uv[0] = -size;
	point.p[1].uv[1] = -size;
	point.p[2].uv[0] = -size;
	point.p[2].uv[1] = size;
	point.p[3].uv[0] = size;
	point.p[3].uv[1] = size;

  RenderData::Get()->CurBuffer().points2D.push_back(point);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AABBDrawer
{
	AABB  aabb;
	Color color;
	bool  zTest;

public:
	AABBDrawer( const AABB &_aabb, Color _color, bool _zTest ) : aabb(_aabb), color(_color), zTest(_zTest) {}
	void Draw( float x1s, float y1s, float z1s, float x2s, float y2s, float z2s )
	{
		DrawLine3D( CVec3(aabb.center.x + x1s * aabb.halfSize.x, aabb.center.y + y1s * aabb.halfSize.y, aabb.center.z + z1s * aabb.halfSize.z), 
								CVec3(aabb.center.x + x2s * aabb.halfSize.x, aabb.center.y + y2s * aabb.halfSize.y, aabb.center.z + z2s * aabb.halfSize.z),
								color, color, zTest );
	}
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawAABB( const AABB &aabb, Render::Color color, bool zTest )
{
	AABBDrawer drawer(aabb, color, zTest);
	drawer.Draw( -1.0f, -1.0f, -1.0f, -1.0f, +1.0f, -1.0f );
	drawer.Draw( +1.0f, -1.0f, -1.0f, +1.0f, +1.0f, -1.0f );
	drawer.Draw( -1.0f, +1.0f, -1.0f, +1.0f, +1.0f, -1.0f );
	drawer.Draw( -1.0f, -1.0f, -1.0f, +1.0f, -1.0f, -1.0f );
	
	drawer.Draw( -1.0f, -1.0f, +1.0f, -1.0f, +1.0f, +1.0f );
	drawer.Draw( +1.0f, -1.0f, +1.0f, +1.0f, +1.0f, +1.0f );
	drawer.Draw( -1.0f, +1.0f, +1.0f, +1.0f, +1.0f, +1.0f );
	drawer.Draw( -1.0f, -1.0f, +1.0f, +1.0f, -1.0f, +1.0f );

	drawer.Draw( -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, +1.0f );
	drawer.Draw( +1.0f, -1.0f, -1.0f, +1.0f, -1.0f, +1.0f );
	drawer.Draw( +1.0f, +1.0f, -1.0f, +1.0f, +1.0f, +1.0f );
	drawer.Draw( -1.0f, +1.0f, -1.0f, -1.0f, +1.0f, +1.0f );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawBox3D( const Matrix43 &mtx, float size, Render::Color color, bool zTest )
{
#ifndef _SHIPPING
	static int boxIndices[12*2] = {0, 1, 1, 3, 3, 2, 2, 0, 
																 4, 5, 5, 7, 7, 6, 6, 4, 
																 0, 4, 1, 5, 3, 7, 2, 6};

	float val[2];
	val[0] = -size;
	val[1] = size;

	int cnt = 0;
	CVec3 points[8];
	for (int z = 0; z < 2; z++)
		for (int y = 0; y < 2; y++)
			for (int x = 0; x < 2; x++)
				points[cnt++] = Transform( CVec3(val[x], val[y], val[z]), mtx );

	for (int i = 0; i < 12; i++)
		DrawLine3D(points[i*2], points[i*2+1], color, color, zTest);
#endif // _SHIPPING
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawBox3D( const Placement &pl, float size, Render::Color color, bool zTest )
{
#ifndef _SHIPPING
	Matrix43 mtx;
	pl.GetMatrix(&mtx);
	DrawBox3D(mtx, size, color, zTest);
#endif // _SHIPPING
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CalculateCrossVertices( CVec3 *p, const Matrix43 &mtx, float sizePos, float sizeNeg )
{
	p[0] = CVec3(-sizeNeg, 0.f, 0.f);
	p[1] = CVec3( sizePos, 0.f, 0.f);
	p[2] = CVec3(0.f, -sizeNeg, 0.f);
	p[3] = CVec3(0.f,  sizePos, 0.f);
	p[4] = CVec3(0.f, 0.f, -sizeNeg);
	p[5] = CVec3(0.f, 0.f,  sizePos);

	// transform points by L2W matrix
	for (int i = 0; i < 6; ++i)
		p[i] = Transform(p[i], mtx);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawCross3D( const Matrix43 &mtx, float sizePos, float sizeNeg, const CrossColorTable &colors, bool zTest )
{
#ifndef _SHIPPING
	CVec3 p[6];
	CalculateCrossVertices(p, mtx, sizePos, sizeNeg);

	for (int i = 0; i < 3; i++)
		DebugRenderer::DrawLine3D( p[i*2], p[i*2+1], colors.colorNeg[i], colors.colorPos[i], zTest );
#endif // _SHIPPING
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawCross3D( const Matrix43 &mtx, float sizePos, float sizeNeg, Render::Color color, bool zTest )
{
#ifndef _SHIPPING
	CVec3 p[6];
	CalculateCrossVertices(p, mtx, sizePos, sizeNeg);

	for (int i = 0; i < 3; i++)
		DebugRenderer::DrawLine3D( p[i*2], p[i*2+1], color, color, zTest );
#endif // _SHIPPING
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawCircle3D( CVec3 const &center, float radius, int numSegments, Render::Color color, bool zTest )
{
#ifndef _SHIPPING
  float dA = FP_2PI / numSegments;
  CVec3 prev = center + radius * CVec3(1.f, 0.f, 0.f);
  for (int i = 1; i <= numSegments; ++i)
  {
    CVec3 cur = center + radius * CVec3( NMath::Cos(dA * i), NMath::Sin(dA * i), 0.f);
    DrawLine3D(prev, cur, color, color, zTest);
    prev = cur;
  }
#endif // _SHIPPING
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Draw2D()
{
  if ( !renderDataInitialized )
    return;

  RenderData::Get()->PrepareData2D();

  gpuMemoryUsed.SetValue(RenderData::Get()->GetMemoryUsed2D() + RenderData::Get()->GetMemoryUsed3D());

	int vbOffset = RenderData::Get()->GetMemoryUsed3D();
  DrawPoints2D(vbOffset);
	DrawLines2D(vbOffset);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Draw3D()
{
  if ( !renderDataInitialized )
    return;

  gpuMemoryUsed.SetValue(RenderData::Get()->GetMemoryUsed2D() + RenderData::Get()->GetMemoryUsed3D());

  RenderData::Get()->PrepareData3D();

	int vbOffset = 0;
  DrawPoints3D(vbOffset);
	DrawLines3D(vbOffset);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ClearBuffer(DebugRenderBuffer buf)
{
  if ( !renderDataInitialized )
    return;

  NI_VERIFY(0 <= buf && buf < DRBUFFER_COUNT, "Invalid value", return;);
  RenderData::Get()->buffers[buf].Clear();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawPoints3D(int &vbOffset)
{
#ifndef _SHIPPING
	float tileSize = 2.5; // smirnov [2008/12/4]: any way to use Terrain::GridConstants.metersPerTile param?!

	if ( drawGrid )
	{
		for ( float x = 0; x < 256*tileSize; x+=tileSize )
		{
			for ( float y = 0; y < 256*tileSize; y+=tileSize )
			{
				DrawPoint3D( CVec3(x,y,0.1f), 0.05f, Color((unsigned char)255), true );
			}
		}

		for ( float x = 0; x < 256*tileSize; x+=(tileSize*16) )
		{
			for ( float y = 0; y < 256*tileSize; y+=(tileSize*16) )
			{
				DrawPoint3D( CVec3(x,y,0.2f), 0.1f, Color(0,255,0,255), true );
			}
		}

		for ( float x = 0; x < 256*tileSize; x+=(tileSize*32) )
		{
			for ( float y = 0; y < 256*tileSize; y+=(tileSize*32) )
			{
				DrawPoint3D( CVec3(x,y,0.2f), 0.15f, Color(255,0,0,255), true );
			}
		}
	}

  int totalPoints = 0;
  for (int i = 0; i < DRBUFFER_COUNT; ++i)
  {
    totalPoints += RenderData::Get()->buffers[i].points3D.size() + RenderData::Get()->buffers[i].points3DZ.size();
  }

  if (totalPoints == 0)
  {
    return;
  }

	{
		RenderState renderState;
		renderState.SetBlendMode(NDb::BLENDMODE_OFF);
		renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
		GetStatesManager()->SetState(renderState);
		GetStatesManager()->SetStateDirect(D3DRS_ZENABLE, 0);

		SmartRenderer::BindVertexDeclaration( RenderData::Get()->pPointsVDecl );

    SmartRenderer::BindIndexBuffer(RenderData::Get()->pIndexBuffer);

		SmartRenderer::BindVertexShader(RenderData::Get()->pPoint3D_SimpleVS);
		SmartRenderer::BindPixelShader(RenderData::Get()->pPoint3D_SimplePS);

    SetupConstants();

    for (int i = 0; i < DRBUFFER_COUNT; ++i)
    {
      int num = RenderData::Get()->buffers[i].points3D.size();
      
      if (num > 0)
      {
        SmartRenderer::BindVertexBuffer( 0, Get(RenderData::Get()->pVertexBuffer), sizeof(PointVertexStride), vbOffset );
        RenderData::Get()->debugPointsDipDescriptor.numVertices = num * 4;
        RenderData::Get()->debugPointsDipDescriptor.primitiveCount = num * 2;
        SmartRenderer::DrawIndexedPrimitive( RenderData::Get()->debugPointsDipDescriptor );

        vbOffset += num * sizeof(Points);
      }
    }
	}

	{
		RenderState renderState;
		renderState.SetBlendMode(NDb::BLENDMODE_OFF);
		renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
		GetStatesManager()->SetState(renderState);
		GetStatesManager()->SetStateDirect(D3DRS_ZENABLE, 1);

		SmartRenderer::BindVertexDeclaration(RenderData::Get()->pPointsVDecl);

    SmartRenderer::BindIndexBuffer(RenderData::Get()->pIndexBuffer);

		SmartRenderer::BindVertexShader(RenderData::Get()->pPoint3D_SimpleVS);
		SmartRenderer::BindPixelShader(RenderData::Get()->pPoint3D_SimplePS);

		SetupConstants();

    for (int i = 0; i < DRBUFFER_COUNT; ++i)
    {
      int num = RenderData::Get()->buffers[i].points3DZ.size();

      if (num > 0)
      {
        SmartRenderer::BindVertexBuffer( 0, Get(RenderData::Get()->pVertexBuffer), sizeof(PointVertexStride), vbOffset );
        RenderData::Get()->debugPointsDipDescriptor.numVertices = num * 4;
        RenderData::Get()->debugPointsDipDescriptor.primitiveCount = num * 2;
        SmartRenderer::DrawIndexedPrimitive( RenderData::Get()->debugPointsDipDescriptor );

        vbOffset += num * sizeof(Points);
      }
    }
	}
#endif // #ifndef _SHIPPING
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawLines3D(int &vbOffset)
{
#ifndef _SHIPPING
	float tileSize = 2.5; // smirnov [2008/12/4]: any way to use Terrain::GridConstants.metersPerTile param?!

	if ( drawGrid )
	{
		for ( float y = 0; y < 256*tileSize; y+=tileSize )
		{
			DrawLine3D( CVec3(y,0.f,0.1f), CVec3(y, 256*tileSize, 0.1f), Color((unsigned char)255), Color((unsigned char)255), true );
			DrawLine3D( CVec3(0.f,y,0.1f), CVec3(256*tileSize, y, 0.1f), Color((unsigned char)255), Color((unsigned char)255), true );
		}

		for ( float y = 0; y < 256*tileSize; y+=tileSize*16 )
		{
			DrawLine3D( CVec3(y,0.f,0.1f), CVec3(y, 256*tileSize, 0.1f), Color(0,255,0,255), Color(0,255,0,255), true );
			DrawLine3D( CVec3(0.f,y,0.1f), CVec3(256*tileSize, y, 0.1f), Color(0,255,0,255), Color(0,255,0,255), true );
		}

		for ( float y = 0; y < 256*tileSize; y+=tileSize*32 )
		{
			DrawLine3D( CVec3(y,0.f,0.1f), CVec3(y, 256*tileSize, 0.1f), Color(0,0,255,255), Color(0,0,255,255), true );
			DrawLine3D( CVec3(0.f,y,0.1f), CVec3(256*tileSize, y, 0.1f), Color(0,0,255,255), Color(0,0,255,255), true );
		}

		for ( float y = 0; y < 256*tileSize; y+=tileSize*64 )
		{
			DrawLine3D( CVec3(y,0.f,0.1f), CVec3(y, 256*tileSize, 0.1f), Color(255,0,0,255), Color(255,0,0,255), true );
			DrawLine3D( CVec3(0.f,y,0.1f), CVec3(256*tileSize, y, 0.1f), Color(255,0,0,255), Color(255,0,0,255), true );
		}
	}

  int totalLines = 0;
  for (int i = 0; i < DRBUFFER_COUNT; ++i)
  {
    totalLines += RenderData::Get()->buffers[i].lines3D.size() + RenderData::Get()->buffers[i].lines3DZ.size();
  }

  if (totalLines == 0)
  {
    return;
  }

	{
		RenderState renderState;
		renderState.SetBlendMode(NDb::BLENDMODE_OFF);
		renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
		GetStatesManager()->SetState(renderState);
		GetStatesManager()->SetStateDirect(D3DRS_ZENABLE, 0);

		SmartRenderer::BindVertexShader(RenderData::Get()->pUberLine3DVS);
		SmartRenderer::BindPixelShader(RenderData::Get()->pLine3D_SimplePS);

		SmartRenderer::BindVertexDeclaration(RenderData::Get()->pLinesVDecl);

		//SmartRenderer::BindTexture(0, pTexture);

		RenderData::Get()->debugDipDescriptor.startIndex = 0;
		SetupConstants();

    for (int i = 0; i < DRBUFFER_COUNT; ++i)
    {
      int num = RenderData::Get()->buffers[i].lines3D.size();

      if (num > 0)
      {
        SmartRenderer::BindVertexBuffer( 0, Get(RenderData::Get()->pVertexBuffer), sizeof(VertexStride), vbOffset );
        RenderData::Get()->debugDipDescriptor.primitiveCount = num;
        SmartRenderer::DrawPrimitive( RenderData::Get()->debugDipDescriptor );

        vbOffset += num * sizeof(UberLine);
      }
    }
	}

	{
		RenderState renderState;
		renderState.SetBlendMode(NDb::BLENDMODE_OFF);
		renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
		GetStatesManager()->SetState(renderState);
		GetStatesManager()->SetStateDirect(D3DRS_ZENABLE, 1);

		SmartRenderer::BindVertexShader(RenderData::Get()->pUberLine3DVS);
		SmartRenderer::BindPixelShader(RenderData::Get()->pLine3D_SimplePS);

		SmartRenderer::BindVertexDeclaration(RenderData::Get()->pLinesVDecl);

		//SmartRenderer::BindTexture(0, pTexture);

		RenderData::Get()->debugDipDescriptor.startIndex = 0;
		SetupConstants();

    for (int i = 0; i < DRBUFFER_COUNT; ++i)
    {
      int num = RenderData::Get()->buffers[i].lines3DZ.size();

      if (num > 0)
      {
        SmartRenderer::BindVertexBuffer( 0, Get(RenderData::Get()->pVertexBuffer), sizeof(VertexStride), vbOffset );
        RenderData::Get()->debugDipDescriptor.primitiveCount = num;
        SmartRenderer::DrawPrimitive( RenderData::Get()->debugDipDescriptor );

        vbOffset += num * sizeof(UberLine);
      }
    }
	}
#endif // _SHIPPING
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawPoints2D(int &vbOffset)
{
#ifndef _SHIPPING
  int totalPoints = 0;
  for (int i = 0; i < DRBUFFER_COUNT; ++i)
  {
    totalPoints += RenderData::Get()->buffers[i].points2D.size();
  }

  if (totalPoints == 0)
  {
    return;
  }

	RenderState renderState;
	renderState.SetBlendMode(NDb::BLENDMODE_OFF);
	renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
	GetStatesManager()->SetState(renderState);
	GetStatesManager()->SetStateDirect(D3DRS_ZENABLE, 0);

	SmartRenderer::BindIndexBuffer(RenderData::Get()->pIndexBuffer);

	SmartRenderer::BindVertexShader(RenderData::Get()->pPoint2D_SimpleVS);
	SmartRenderer::BindPixelShader(RenderData::Get()->pPoint2D_SimplePS);

	SmartRenderer::BindVertexDeclaration(RenderData::Get()->pPointsVDecl);

	SetupConstants();
	
	CVec4 debugRendererBaseResolution( 0, 0, 0, 0 );
	debugRendererBaseResolution.x = Render::GetRenderer()->GetCurrentRenderMode().width;
	debugRendererBaseResolution.y = Render::GetRenderer()->GetCurrentRenderMode().height;
	GetRenderer()->SetVertexShaderConstantsVector4(DEBUG_VSHADER_CONST8, debugRendererBaseResolution);

  for (int i = 0; i < DRBUFFER_COUNT; ++i)
  {
    int num = RenderData::Get()->buffers[i].points2D.size();

    if (num > 0)
    {
      SmartRenderer::BindVertexBuffer( 0, Get(RenderData::Get()->pVertexBuffer), sizeof(PointVertexStride), vbOffset );
      RenderData::Get()->debugPointsDipDescriptor.numVertices = num * 4;
      RenderData::Get()->debugPointsDipDescriptor.primitiveCount = num * 2;
      SmartRenderer::DrawIndexedPrimitive( RenderData::Get()->debugPointsDipDescriptor );

      vbOffset += num * sizeof(Points);
    }
  }
#endif // _SHIPPING
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawLines2D(int &vbOffset)
{
  if(!renderDataInitialized)
    return;

  int totalLines = 0;
  for (int i = 0; i < DRBUFFER_COUNT; ++i)
  {
    totalLines += RenderData::Get()->buffers[i].lines2D.size();
  }

  if (totalLines == 0)
  {
    return;
  }

  RenderState renderState;
	renderState.SetBlendMode(NDb::BLENDMODE_OFF);
	renderState.SetAlphaTest(NDb::ONOFFSTATE_OFF);
	GetStatesManager()->SetState(renderState);
	GetStatesManager()->SetStateDirect(D3DRS_ZENABLE, 0);

	SmartRenderer::BindVertexShader(RenderData::Get()->pUberLine2DVS);
	SmartRenderer::BindPixelShader(RenderData::Get()->pLine2D_SimplePS);

	CVec4 debugRendererBaseResolution( 0, 0, 0, 0 );
	debugRendererBaseResolution.x = Render::GetRenderer()->GetCurrentRenderMode().width;
	debugRendererBaseResolution.y = Render::GetRenderer()->GetCurrentRenderMode().height;
	GetRenderer()->SetVertexShaderConstantsVector4( DEBUG_VSHADER_CONST0, debugRendererBaseResolution);

	SmartRenderer::BindVertexDeclaration(RenderData::Get()->pLinesVDecl);

  //SmartRenderer::BindTexture(0, pTexture);

	RenderData::Get()->debugDipDescriptor.startIndex = 0;

  for (int i = 0; i < DRBUFFER_COUNT; ++i)
  {
    int num = RenderData::Get()->buffers[i].lines2D.size();

    if (num > 0)
    {
      SmartRenderer::BindVertexBuffer( 0, Get(RenderData::Get()->pVertexBuffer), sizeof(VertexStride), vbOffset );
      RenderData::Get()->debugDipDescriptor.primitiveCount = num;
      SmartRenderer::DrawPrimitive( RenderData::Get()->debugDipDescriptor );

      vbOffset += num * sizeof(UberLine);
    }
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Release()
{
  if ( renderDataInitialized )
    RenderData::Term();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ProjectPoint( CVec2 *pRes, const CVec3& point, int screenW, int screenH )
{
	SHMatrix transform = RenderData::Get()->projMatrix * RenderData::Get()->viewMatrix;

	CVec4 src;
	transform.RotateHVector( &src, point );

	pRes->x = (( src.x / src.w + 1.0 ) * screenW) / 2.0;
	pRes->y = screenH - (( src.y / src.w + 1.0 ) * screenH) / 2.0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawTriangle3D( const CVec3 &p1, const CVec3 &p2, const CVec3 &p3, Render::Color color, bool zTest)
{
    DrawLine3D(p1, p2, color, color, zTest);
    DrawLine3D(p2, p3, color, color, zTest);
    DrawLine3D(p3, p1, color, color, zTest);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawCustomMesh(const void *points, int stride, const int *indices, int indCount, Render::Color color, bool zTest)
{
#ifndef _SHIPPING
    int triCount = indCount / 3;

    NI_ASSERT(triCount * 3 == indCount, "indices count should be dividable by 3");

    for (int i = 0, triIndex = 0; i < triCount; i++, triIndex += 3)
    {
        CVec3 p1, p2, p3;
        p1 = *(CVec3 *)((byte *)points + indices[triIndex + 0] * stride);
        p2 = *(CVec3 *)((byte *)points + indices[triIndex + 1] * stride);
        p3 = *(CVec3 *)((byte *)points + indices[triIndex + 2] * stride);
        DrawTriangle3D(p1, p2, p3, color, zTest);
    }
#endif // _SHIPPING
}


static SHMatrix debugTextProjection;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawText( const char * text, const CVec2 & uiCoords, int size, const Render::Color & color, ETextHAlign hAlign, ETextVAlign vAlign)
{
  if( CheckInitialized() )
  {
    SDebugText2D &t = RenderData::Get()->CurBuffer().debugTexts2D.push_back();
    t.text = NStr::ToUnicode( text );
    t.uiCoords = uiCoords;
    t.size = size;
    t.color = color;
    t.hAlign = hAlign;
    t.vAlign = vAlign;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawText( const wchar_t * text, const CVec2 & uiCoords, int size, const Render::Color & color, ETextHAlign hAlign, ETextVAlign vAlign )
{
  if( CheckInitialized() )
  {
    SDebugText2D &t = RenderData::Get()->CurBuffer().debugTexts2D.push_back();
    t.text = text;
    t.uiCoords = uiCoords;
    t.size = size;
    t.color = color;
    t.hAlign = hAlign;
    t.vAlign = vAlign;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawText3D( const char * text, const CVec3 & pos, int size, const Render::Color & color )
{
  if( CheckInitialized() )
  {
    SDebugText3D &t = RenderData::Get()->CurBuffer().debugTexts3D.push_back();
    t.text = NStr::ToUnicode( text );
    t.pos = pos;
    t.size = size;
    t.color = color;
    t.hAlign = HA_Center;
    t.vAlign = VA_Center;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DrawText3D( const wchar_t * text, const CVec3 & pos, int size, const Render::Color & color )
{
  if( CheckInitialized() )
  {
    SDebugText3D &t = RenderData::Get()->CurBuffer().debugTexts3D.push_back();
    t.text = text;
    t.pos = pos;
    t.size = size;
    t.color = color;
    t.hAlign = HA_Center;
    t.vAlign = VA_Center;
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImplementationSet3DProjection( const SHMatrix & projectionMatrix )
{
  debugTextProjection = projectionMatrix;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ImplementationProcessDebugText( IDebugTextProcessor * processor )
{
  if ( !renderDataInitialized )
    return;

  for (int b = 0; b < DRBUFFER_COUNT; ++b)
  {
    PrimBuffer &buf = RenderData::Get()->buffers[b];

    for ( int i = 0; i < buf.debugTexts2D.size(); ++i )
    {
      SDebugText2D &t = buf.debugTexts2D[i];
      processor->On2DText( t.text, t.uiCoords, t.size, t.color, t.hAlign, t.vAlign );
    }

    for ( int i = 0; i < buf.debugTexts3D.size(); ++i )
    {
      SDebugText3D &t = buf.debugTexts3D[i];
      processor->On3DText( t.text, t.pos, t.size, t.color, debugTextProjection, t.hAlign, t.vAlign );
    }
  }
}

} //namespace DebugRenderer

void LogMarker(const char *_text)
{
  (void)_text;

#ifndef _SHIPPING
  if( Compatibility::IsRunnedUnderWine() )
    return;

  {
    WCHAR msg[MAX_PATH];
#pragma warning(push)
#pragma warning(disable:4996)
    if(UINT(mbstowcs(msg, _text, MAX_PATH)) < MAX_PATH)
      D3DPERF_SetMarker(D3DCOLOR_XRGB(255, 0, 0), msg);
#pragma warning(pop)
  }
  
  if (BatchQueue::IsLoggingActive())
  {
    DebugTrace(_text);
  }
#endif
}

void RenderSequenceMarker(const char *_text)
{
  (void)_text;

#ifndef _SHIPPING 
  if( Compatibility::IsRunnedUnderWine() )
    return;

#define HEADER_TEXT "RENDER SEQUENCE: "
  static char text[MAX_PATH] = HEADER_TEXT;
  static const int pos = sizeof(HEADER_TEXT) - 1;
#undef HEADER_TEXT
  strcpy_s(text + pos, MAX_PATH - pos, _text);
  LogMarker(text);
#endif
}

} //namespace Render

REGISTER_DEV_VAR( "showgrid", drawGrid, STORAGE_NONE );
