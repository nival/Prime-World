#include "stdafx.h"

#include "smartrenderer.h"

#include "shadercompiler.h"
#include "renderresourcemanager.h"
#include "uirenderer.h"
#include "../System/staticarray.h"
#include "texture.h"
#include "renderflagsconverter.h"
#include "OcclusionQueries.h"
#include "GlobalMasks.h"
#include "DXWarnSignal.h"
#include <vector>

static DXWarnSignal s_DXWarnLevel;

static bool nullrender = false;
REGISTER_VAR( "nodip", nullrender, STORAGE_NONE );

#ifdef _SUPRESS_HWI
static bool s_supressDrawCall = false;
static bool s_supressHWI = false;
REGISTER_DEV_VAR( "supressHWI", s_supressHWI, STORAGE_NONE );
#endif // _SUPRESS_HWI

#ifndef _SHIPPING

namespace
{
  NDebug::DebugVar<int> g_numVSu( "numVSUniq", "Statistics" );
  NDebug::DebugVar<int> g_numPSu( "numPSUniq", "Statistics" );
  NDebug::DebugVar<int> g_numVSt( "numVSTotal", "Statistics" );
  NDebug::DebugVar<int> g_numPSt( "numPSTotal", "Statistics" );
  NDebug::DebugVar<int> g_numVS( "numVS", "Statistics", true );
  NDebug::DebugVar<int> g_numPS( "numPS", "Statistics", true );
  hash_set<void*>  psMap, vsMap, psMapTotal, vsMapTotal;
}

#endif // _SHIPPING

static unsigned int  triangleCount = 0;
static unsigned int  dipCount = 0;

namespace Render
{
namespace SmartRenderer
{

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct InitIdxVB : public IntrusivePtrDeleter
  {
    typedef DXVertexBufferRef Type;

    void Init(Type& _result)
    {
      // Create & fill second vertex buffer
      _result = CreateVB(MAX_INSTANCES_COUNT * sizeof(int), RENDER_POOL_MANAGED);
      NI_VERIFY( _result, "Couldn't create instance idx VB", return );

      if( int * const pBuff = LockVB<int>(Get(_result), 0) )
      {
        for(size_t i = 0; i < MAX_INSTANCES_COUNT; i++)
          pBuff[i] = i;

        _result->Unlock();
      }
      else
        _result.Attach(0);
    }
  };

  static ManagedResource<InitIdxVB> s_pInstanceIndexVB;

///////////////////////////////////// 
static nstl::hash_map< VertexFormatDescriptor, DXVertexDeclarationRef > VertexDeclaraionsCash;
typedef nstl::hash_map< VertexFormatDescriptor, DXVertexDeclarationRef >::iterator VertexDeclarationsCashIterator;

enum StateValueType
{
  SVT_REQUESTED = 0,
  SVT_ACTIVE,
  SVT_TOTAL_NUM // this value MUST be last!
};

static const unsigned int MAX_STREAMS_COUNT = 16;
static StaticArray<IDirect3DVertexBuffer9*,MAX_STREAMS_COUNT> lastVertexBuffersPtrs;
static StaticArray<unsigned int,MAX_STREAMS_COUNT> lastVertexBuffersOffsets;
static StaticArray<unsigned int,MAX_STREAMS_COUNT> lastStreamSourceFreqs[SVT_TOTAL_NUM];
static IDirect3DIndexBuffer9* pLastIndexBuffer = 0; 

struct SamplerInfo
{
	const Texture *pTex;
	bool     bProtected;
};
static StaticArray<SamplerInfo, Sampler::MAX_VS_SAMPLER_INDEX+1> lastTexturesPtrs;

static IDirect3DVertexDeclaration9* pLastVertexDeclaration = 0;

static IDirect3DPixelShader9* pLastPixelShader = 0;
static IDirect3DVertexShader9* pLastVertexShader = 0;

static const unsigned int MAX_COLOR_RT = 8;
static StaticArray<IDirect3DSurface9*,MAX_COLOR_RT> curColorSurface;
static DWORD curColorSurfaceWidth = 1, curColorSurfaceHeight = 1;
static DWORD curDepthSurfaceWidth = 1, curDepthSurfaceHeight = 1;
static IDirect3DSurface9* curDepthSurface( 0 );

static IDirect3DSurface9* pDefaultRT0( 0 );
static IDirect3DSurface9* pDefaultRT1( 0 );
static IDirect3DSurface9* pDefaultDepth( 0 );

static D3DVIEWPORT9 viewport = { 0 };

namespace {
  bool useViewport = false;
  bool instancingEnabled = false;


  class DeclMap : public DeviceDeleteHandler
  {
    typedef nstl::hash_map<void*, DXVertexDeclarationRef> Cache;

    Cache cache;

  public:
    virtual void OnDeviceDelete()
    {
      cache.clear();
    }

    IDirect3DVertexDeclaration9* Get(IDirect3DVertexDeclaration9 *_pDecl)
    {
      Cache::iterator it = cache.find(_pDecl);
      if(cache.end() == it)
      {
        D3DVERTEXELEMENT9 decl[MAXD3DDECLLENGTH];
        UINT numElements;
        HRESULT hr = _pDecl->GetDeclaration(decl, &numElements); hr;

        for(UINT n = 0; n < numElements-1; ++n)
          if(decl[n].Stream)
            ++decl[n].Stream;

        static const D3DVERTEXELEMENT9 instanceElement = {1, 0, D3DDECLTYPE_SHORT2, 0, D3DDECLUSAGE_BLENDINDICES, 0};
        static const D3DVERTEXELEMENT9 declEnd = D3DDECL_END();

        decl[numElements-1] = instanceElement;
        decl[numElements] = declEnd;

        IDirect3DVertexDeclaration9 *pNewDecl = 0;
        hr = GetDevice()->CreateVertexDeclaration(decl, &pNewDecl);
        cache[_pDecl] = pNewDecl;
        return pNewDecl;
      }
      return ::Get(it->second);
    }
  };

  static DeclMap s_instancedVDecl;
}


//
// This part of smart renderer handles batching and deferred rendering execution
//
struct Vertex2D
{
  Vertex2D(float x, float y, float z, DWORD color)
  {
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = 1.0f;
    this->color = color;
  }
  float x, y, z, w;
  DWORD color;
};

std::vector<Vertex2D> g_deferredVerts;
void AddRect(float l, float t, float r, float b, int R, int G, int B)
{
  DWORD color = D3DCOLOR_XRGB(R, G, B);
  std::vector<Vertex2D>& verts = g_deferredVerts;
  verts.push_back(Vertex2D(l, t, 0.0f, color));
  verts.push_back(Vertex2D(r, t, 0.0f, color));
  verts.push_back(Vertex2D(l, b, 0.0f, color));
  verts.push_back(Vertex2D(l, b, 0.0f, color));
  verts.push_back(Vertex2D(r, t, 0.0f, color));
  verts.push_back(Vertex2D(r, b, 0.0f, color));
}

void AddLine(float sx, float sy, float ex, float ey, int R, int G, int B, float width /* 1.0f */)
{
  DWORD color = D3DCOLOR_XRGB(R, G, B);
  std::vector<Vertex2D>& verts = g_deferredVerts;
  verts.push_back(Vertex2D(sx, sy, 0.0f, color));
  verts.push_back(Vertex2D(sx + width, sy, 0.0f, color));
  verts.push_back(Vertex2D(ex, ey, 0.0f, color));
  verts.push_back(Vertex2D(ex, ey, 0.0f, color));
  verts.push_back(Vertex2D(sx + width, sy, 0.0f, color));
  verts.push_back(Vertex2D(ex + width, ey, 0.0f, color));
}

void RenderDeferred2D()
{
  if(g_deferredVerts.size() > 2)
  {
    // Use fixed-function transformation to avoid custom extra shader here.
    // Draw call uses currently bound font shader which is good enough, thus
    // this function might not work if shader is not the font shader anymore.

    std::vector<Vertex2D>& verts = g_deferredVerts;   

    GetDevice()->SetVertexShader(NULL);
    GetDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
    GetDevice()->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
    GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLELIST, verts.size() / 3, &verts[0], sizeof(Vertex2D));

    verts.clear();
  }
}



//////////////////////////////////////////////////////////////////////////
void GetTriangleAndDipCount(unsigned int& triangles, unsigned int& dips)
{
  triangles = triangleCount;
  dips = dipCount;
}

//////////////////////////////////////////////////////////////////////////
void ResetTriangleAndDipCount()
{
  triangleCount = 0;
  dipCount = 0;
}

// Lazy states application system
static void ApplyStates()
{
  IDirect3DDevice9* const device = GetDevice();
  StaticArray<unsigned int,MAX_STREAMS_COUNT> &ssfActive = lastStreamSourceFreqs[SVT_ACTIVE],
                                              &ssfRequested = lastStreamSourceFreqs[SVT_REQUESTED];
#ifndef _SUPRESS_HWI
  //if(ssfActive[1] != ssfRequested[1] && ssfRequested[1] == 1)
  //  UnBindVertexBufferRaw(1);

  for(UINT n = 0; n < MAX_STREAMS_COUNT; ++n)
    if( ssfActive[n] != ssfRequested[n] )
      device->SetStreamSourceFreq(n, ssfActive[n] = ssfRequested[n]);
#else
  bool isInstanced = false;
  for(UINT n = 0; n < MAX_STREAMS_COUNT; ++n)
    if( ssfActive[n] != ssfRequested[n] )
      if( s_supressHWI )
        isInstanced |= ssfRequested[n] != 1;
      else
        device->SetStreamSourceFreq(n, ssfActive[n] = ssfRequested[n]);

  s_supressDrawCall = s_supressHWI && isInstanced;
#endif // _SUPRESS_HWI
}

//////////////////////////////////////////////////////////////////////////
static void NullLastPointers()
{
  pLastIndexBuffer = 0;
  for (unsigned int i = 0; i < MAX_STREAMS_COUNT; ++i) 
  {
    lastVertexBuffersPtrs[i] = 0;
    lastVertexBuffersOffsets[i] = 0;
  }
  for (unsigned int i = 0; i < Sampler::MAX_VS_SAMPLER_INDEX; ++i) 
  {
    lastTexturesPtrs[i].pTex = 0;
    lastTexturesPtrs[i].bProtected = false;
  }

  pLastPixelShader = 0;
  pLastVertexShader = 0;
  pLastVertexDeclaration = 0;

  curDepthSurface = 0;
  for (unsigned int i = 0; i < MAX_COLOR_RT; ++i) 
    curColorSurface[i] = 0;

  DisableHardwareInstancing();
}

//////////////////////////////////////////////////////////////////////////
void NullThePointers()
{
// Sorry for profiling code [11/17/2009 smirnov]
//  _DebugSamplerBindReset();

  NullLastPointers();

	pDefaultRT0 = 0;
	pDefaultRT1 = 0;
	pDefaultDepth = 0;
}


//////////////////////////////////////////////////////////////////////////
void OnFrameStart()
{
#ifndef _SHIPPING
  g_numPSu.SetValue( psMap.size() );
  g_numVSu.SetValue( vsMap.size() );
  g_numPSt.SetValue( psMapTotal.size() );
  g_numVSt.SetValue( vsMapTotal.size() );

  psMap.clear(); vsMap.clear();
#endif // _SHIPPING
  NullLastPointers();
  OcclusionQueriesBank::OnFrameStart();
}

bool IsResourceBound(const IUnknown* const ptr)
{
  if((ptr == pLastIndexBuffer)||(ptr == pLastVertexShader)||(ptr == pLastPixelShader)
     ||(ptr == pLastVertexDeclaration)||(ptr == Get(curDepthSurface) ))
    return true;

	for(UINT n = 0; n < MAX_COLOR_RT; ++n) 
		if( ptr == Get(curColorSurface[n]) )
      return true;

	for(UINT n = 0; n < Sampler::MAX_VS_SAMPLER_INDEX; ++n)
		if( const Texture *pTex = lastTexturesPtrs[n].pTex )
		  if( ptr == Get(pTex->GetDXTexture()) )
        return true;

  for(UINT n = 0; n < MAX_STREAMS_COUNT; ++n)
	  if( ptr == lastVertexBuffersPtrs[n] )
      return true;

    return false;
}


void Init()
{
	NullThePointers();

	RenderResourceManager::Init();
}

///
void BindVertexBufferRaw(unsigned int streamNumber, IDirect3DVertexBuffer9* buffer, unsigned int stride, unsigned int offset)
{
	NI_VERIFY(streamNumber < MAX_STREAMS_COUNT, "Invalid vertex stream number!", return; );
	NI_VERIFY(buffer != 0, "Invalid vertex buffer!", return; );

	if (lastVertexBuffersPtrs[streamNumber] == buffer && lastVertexBuffersOffsets[streamNumber] == offset) 
		return;

	lastVertexBuffersPtrs[streamNumber] = buffer;
  lastVertexBuffersOffsets[streamNumber] = offset;
	HRESULT hr = GetDevice()->SetStreamSource(streamNumber, buffer, offset, stride);
  NI_DX_THROW(hr, "BindVertexBufferRaw");
}

///
void BindVertexBuffer(unsigned int streamNumber, IDirect3DVertexBuffer9* buffer, unsigned int stride, unsigned int offset)
{
  if(instancingEnabled && streamNumber)
    ++streamNumber;
  BindVertexBufferRaw(streamNumber, buffer, stride, offset);
}

void BindInstanceVB(unsigned int offset)
{
  BindVertexBufferRaw(1, s_pInstanceIndexVB.Get(), 4, offset);
}

///
void UnBindVertexBufferRaw(unsigned int streamNumber)
{
  NI_VERIFY(streamNumber < MAX_STREAMS_COUNT, "Invalid vertex stream number!", return; );

  if(!lastVertexBuffersPtrs[streamNumber]) 
    return;

  lastVertexBuffersPtrs[streamNumber] = 0;
  lastVertexBuffersOffsets[streamNumber] = 0;
  GetDevice()->SetStreamSource(streamNumber, 0, 0, 0);
}

///
void UnBindVertexBuffer(unsigned int streamNumber)
{
  if(instancingEnabled && streamNumber)
    ++streamNumber;
  UnBindVertexBufferRaw(streamNumber);
}

///
void EnableHardwareInstancing(UINT _numInstances, UINT _lastGeomStream, UINT _instanceStream)
{
  NI_VERIFY(_lastGeomStream < MAX_STREAMS_COUNT, "Invalid geometry streams number!", return; );
  NI_VERIFY(_numInstances < D3DSTREAMSOURCE_INDEXEDDATA, "Invalid instances number!", return; );

  if(_instanceStream == UINT_MAX)
    _instanceStream = _lastGeomStream + 1;

  NI_VERIFY(_instanceStream < MAX_STREAMS_COUNT, "Invalid instance stream number!", return; );

  instancingEnabled = true;

  for(UINT stream = 0; stream <= _lastGeomStream; ++stream)
  {
    lastStreamSourceFreqs[SVT_REQUESTED][stream] = UINT(D3DSTREAMSOURCE_INDEXEDDATA)|_numInstances;
  }
  lastStreamSourceFreqs[SVT_REQUESTED][_instanceStream] = UINT(D3DSTREAMSOURCE_INSTANCEDATA)|1;
}

///
void DisableHardwareInstancing()
{
  instancingEnabled = false;
  for(UINT stream = 0; stream < MAX_STREAMS_COUNT; ++stream)
    lastStreamSourceFreqs[SVT_REQUESTED][stream] = 1;
}

///                                                                     
bool InstancingEnabled() { return instancingEnabled; }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetFVF(DWORD _fvf)
{
  GetDevice()->SetFVF(_fvf);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
  //#define _DEBUG_VIEWPORT
#endif // _DEBUG

void DrawIndexedPrimitive(const DipDescriptor& _descr)
{
  if(nullrender)
    return;

  ApplyStates();

#ifdef _SUPRESS_HWI
  if(s_supressDrawCall)
    return;
#endif // _SUPRESS_HWI

#ifdef _DEBUG_VIEWPORT
  D3DVIEWPORT9 vp;
  GetDevice()->GetViewport(&vp);
#endif // _DEBUG_VIEWPORT

  NI_VERIFY(_descr.numVertices, "null dip", return; );
  NI_VERIFY(_descr.primitiveCount, "null dip", return;);
  HRESULT hr = GetDevice()->DrawIndexedPrimitive( ConvertPrimitiveType(_descr.primitiveType), 
    _descr.baseVertexIndex, _descr.minIndex, _descr.numVertices, _descr.startIndex, _descr.primitiveCount );

  //NI_ASSERT(hr == D3D_OK, NStr::StrFmt("DrawIndexedPrimitive() failed! code: 0x%08X, error: %s description: %s", hr, DXGetErrorStringA(hr), DXGetErrorDescriptionA(hr)) );
  if(s_DXWarnLevel)
    NI_DX_WARN(hr, "DrawIndexedPrimitive");
  triangleCount += _descr.primitiveCount;
  ++dipCount;

  /* {
    IDirect3DDevice9* const device = GetDevice();
    DWORD val;
    hr = device->GetRenderState(D3DRS_STENCILENABLE, &val);
    hr = device->GetRenderState(D3DRS_STENCILFAIL, &val);
    hr = device->GetRenderState(D3DRS_STENCILZFAIL, &val);
    hr = device->GetRenderState(D3DRS_STENCILPASS, &val);
    hr = device->GetRenderState(D3DRS_STENCILFUNC, &val);
    hr = device->GetRenderState(D3DRS_STENCILREF, &val);
    hr = device->GetRenderState(D3DRS_STENCILMASK, &val);
    hr = device->GetRenderState(D3DRS_STENCILWRITEMASK, &val);

    hr = device->GetRenderState(D3DRS_ZFUNC, &val);
    hr = hr;
  } */

  return;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DrawIndexedPrimitiveUP(const DipDescriptor& _descr, const WORD* pIndexData,
                            const void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
  if(nullrender)
    return;

  ApplyStates();

#ifdef _SUPRESS_HWI
  if(s_supressDrawCall)
    return;
#endif // _SUPRESS_HWI

  NI_VERIFY(_descr.numVertices, "null dip", return; );
  NI_VERIFY(_descr.primitiveCount, "null dip", return;);
  HRESULT hr = GetDevice()->DrawIndexedPrimitiveUP(
                  static_cast<D3DPRIMITIVETYPE>( ConvertPrimitiveType(_descr.primitiveType) ), 
                  _descr.minIndex, _descr.numVertices, _descr.primitiveCount,
                  pIndexData, D3DFMT_INDEX16, pVertexStreamZeroData, VertexStreamZeroStride);

  if(s_DXWarnLevel)
    NI_DX_WARN(hr, "DrawIndexedPrimitiveUP");
  triangleCount += _descr.primitiveCount;
  ++dipCount;

  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DrawPrimitive(const DipDescriptor& _descr)
{
  if(nullrender)
    return;

  ApplyStates();

#ifdef _SUPRESS_HWI
  if(s_supressDrawCall)
    return;
#endif // _SUPRESS_HWI

#ifdef _DEBUG_VIEWPORT
  D3DVIEWPORT9 vp;
  GetDevice()->GetViewport(&vp);
#endif // _DEBUG_VIEWPORT

  NI_VERIFY(_descr.primitiveCount, "null dip", return;);
  HRESULT hr = GetDevice()->DrawPrimitive(
    static_cast<D3DPRIMITIVETYPE>( ConvertPrimitiveType(_descr.primitiveType) ), 
    _descr.startIndex, _descr.primitiveCount );

  if(s_DXWarnLevel)
    NI_DX_WARN(hr, "DrawPrimitive");
  triangleCount += _descr.primitiveCount;
  ++dipCount;

  return;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DrawPrimitiveUP(const DipDescriptor& _descr, const void* pVertexStreamZeroData, UINT VertexStreamZeroStride)
{
  if(nullrender)
    return;

  ApplyStates();

#ifdef _SUPRESS_HWI
  if(s_supressDrawCall)
    return;
#endif // _SUPRESS_HWI

  NI_VERIFY(_descr.primitiveCount, "null dip", return;);
  HRESULT hr = GetDevice()->DrawPrimitiveUP(static_cast<D3DPRIMITIVETYPE>(ConvertPrimitiveType(_descr.primitiveType)),
                                            _descr.primitiveCount, pVertexStreamZeroData, VertexStreamZeroStride);
  if(s_DXWarnLevel)
    NI_DX_WARN(hr, "DrawPrimitiveUP");
  triangleCount += _descr.primitiveCount;
  ++dipCount;

  return;
}

///
void BindIndexBuffer(IDirect3DIndexBuffer9* buffer)
{
	NI_VERIFY(buffer != 0, "Invalid index buffer!", return; );
	if (pLastIndexBuffer == buffer) 
		return;

	pLastIndexBuffer = buffer;
	HRESULT hr = GetDevice()->SetIndices(pLastIndexBuffer);
  if(s_DXWarnLevel > 1)
    NI_DX_WARN(hr, "BindIndexBuffer");
}

///
const DXVertexDeclarationRef & GetVertexFormatDeclaration(const VertexFormatDescriptor& descr)
{
	VertexDeclarationsCashIterator it = VertexDeclaraionsCash.find(descr);
	if ( it != VertexDeclaraionsCash.end() )
		return it->second;

	VertexDeclaraionsCash[descr] = GetRenderer()->CreateVertexFormatDeclaration(descr);
	return VertexDeclaraionsCash[descr];
}

///
void BindVertexDeclarationRaw(IDirect3DVertexDeclaration9 *pDecl)
{
	if(pLastVertexDeclaration == pDecl) 
		return;

  HRESULT hr = GetDevice()->SetVertexDeclaration(pDecl);
  if(s_DXWarnLevel > 1)
    NI_DX_WARN(hr, "BindVertexDeclarationRaw");
	pLastVertexDeclaration = pDecl;
}

///
void BindVertexDeclaration(DXVertexDeclarationRef const &pDecl)
{
	IDirect3DVertexDeclaration9 *decl = Get(pDecl);
  if(instancingEnabled)
    decl = s_instancedVDecl.Get(decl);

	BindVertexDeclarationRaw(decl);
}


///
void Release()
{
	VertexDeclaraionsCash.clear();
	RenderResourceManager::Release();

	NullThePointers();
}

///
void BindTexture(unsigned int samplerIndex, const Texture* pTexture, bool bProtect)
{
	if (!pTexture) // @BVS@MAT
		return;
	NI_ASSERT(!lastTexturesPtrs[samplerIndex].bProtected || bProtect, "Polluting protected sampler");
	if ( lastTexturesPtrs[samplerIndex].pTex == pTexture) 
		return;
	
	lastTexturesPtrs[samplerIndex].pTex       = pTexture;
#ifdef _DEBUG
	lastTexturesPtrs[samplerIndex].bProtected = bProtect;
#endif
  HRESULT hr = GetDevice()->SetTexture( samplerIndex, Get(pTexture->GetDXTexture()) );
  if(s_DXWarnLevel > 1)
    NI_DX_WARN(hr, "BindTexture");
}

///
void UnBindTexture(unsigned int samplerIndex)
{
	if( !lastTexturesPtrs[samplerIndex].pTex ) 
		return;
	
	lastTexturesPtrs[samplerIndex].pTex = 0;
	GetDevice()->SetTexture(samplerIndex, 0);
}

///
void UnBindTexture(const Texture* texture)
{
  for(uint n = 0; n <= Sampler::MAX_PS_SAMPLER_INDEX; ++n)
    if(lastTexturesPtrs[n].pTex == texture) {
      UnBindTexture(n);
      break;
    }
}

///
void BindVertexShader(IDirect3DVertexShader9 *shader)
{
	NI_ASSERT(shader, "pointer to vertex shader is not valid!");
	if(pLastVertexShader == shader)
		return;

#ifndef _SHIPPING
  vsMap.insert(shader);
  vsMapTotal.insert(shader);
  g_numVS.AddValue( 1 );
#endif // _SHIPPING

	pLastVertexShader = shader;
	GetDevice()->SetVertexShader(shader);
}

/// 
void BindPixelShader(IDirect3DPixelShader9 *shader)
{
	NI_ASSERT(shader, "pointer to pixel shader is not valid!");
	if(pLastPixelShader == shader)
    return;

#ifndef _SHIPPING
  psMap.insert(shader);
  psMapTotal.insert(shader);
  g_numPS.AddValue( 1 );
#endif // _SHIPPING

	pLastPixelShader = shader;
	GetDevice()->SetPixelShader(shader);
}


void BindRenderTargetColor( unsigned int renderTargetIndex, IDirect3DSurface9* pColorSurface )
{
  if ( pColorSurface != curColorSurface[renderTargetIndex] )
	{
    HRESULT hr = GetDevice()->SetRenderTarget( renderTargetIndex, pColorSurface );
    curColorSurface[renderTargetIndex] = pColorSurface;
    if(s_DXWarnLevel > 1)
      NI_DX_WARN(hr, "BindRenderTargetColor");

    if (0 == renderTargetIndex)
    {
      D3DSURFACE_DESC rtDesc;
      pColorSurface->GetDesc(&rtDesc);
      curColorSurfaceWidth = rtDesc.Width;
      curColorSurfaceHeight = rtDesc.Height;
    }
	}
}

void BindRenderTargetDepth( IDirect3DSurface9* pDepthStencilSurface )
{
	if ( pDepthStencilSurface != curDepthSurface )
	{
    HRESULT hr = GetDevice()->SetDepthStencilSurface(pDepthStencilSurface);
		curDepthSurface = pDepthStencilSurface;
    if(s_DXWarnLevel > 1)
      NI_DX_WARN(hr, "BindRenderTargetDepth");

    if(curDepthSurface) {
      D3DSURFACE_DESC desc;
      curDepthSurface->GetDesc(&desc);
      curDepthSurfaceWidth = desc.Width;
      curDepthSurfaceHeight = desc.Height;
    }
	}
}

void SetDefaultRenderTarget(const DXSurfaceRef &pRT0, const DXSurfaceRef &pDepth)
{
	pDefaultRT0 = ::Get(pRT0);
	pDefaultRT1 = 0;
	pDefaultDepth = ::Get(pDepth);
}

void SetDefaultRenderTarget(const DXSurfaceRef &pRT0, const DXSurfaceRef &pRT1, const DXSurfaceRef &pDepth)
{
	pDefaultRT0 = ::Get(pRT0);
	pDefaultRT1 = ::Get(pRT1);
	pDefaultDepth = ::Get(pDepth);
}

void BindRenderTargetDefault()
{
	BindRenderTargetColor(0, pDefaultRT0);
	BindRenderTargetColor(1, pDefaultRT1);
	BindRenderTargetDepth(pDefaultDepth);

  if(useViewport) {
    HRESULT hr = GetDevice()->SetViewport( &viewport ); // smirnov [2009/7/15]: why set it here? why only here?
    if(s_DXWarnLevel > 1)
      NI_DX_WARN(hr, "BindRenderTargetDefault");
  }
}

void BindRenderTarget(const Texture2DRef& pColorTexture)
{
  NI_VERIFY(pColorTexture, "Texture Ref Should be valid!", return;);
  const DXSurfaceRef &pDXColorSurface = pColorTexture->GetSurface(0);
  BindRenderTargetColor(0, pDXColorSurface);
	BindRenderTargetColor(1, 0);
	BindRenderTargetDepth(0);
  FixViewport();
}

void BindRenderTarget(const Texture2DRef& pColorTexture, const RenderSurfaceRef& pDepthSurface)
{
	const DXSurfaceRef &pDXColorSurface = pColorTexture->GetSurface(0);
	const DXSurfaceRef &pDXDepthSurface = pDepthSurface->GetDXSurface();
	BindRenderTargetColor(0, pDXColorSurface);
	BindRenderTargetColor(1, 0);
	BindRenderTargetDepth(pDXDepthSurface);
  FixViewport();
}

IDirect3DSurface9* GetRenderTarget(unsigned int renderTargetIndex)
{
	return curColorSurface[renderTargetIndex];
}

IDirect3DSurface9* GetRenderTargetDepth()
{
	return curDepthSurface;
}

int GetRenderTargetWidth()
{
  return curColorSurfaceWidth;
}

int GetRenderTargetHeight()
{
  return curColorSurfaceHeight;
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// smirnov [2009/7/15]: it's better to place these functions into Render::Renderer
// just because SmartRenderer is a *CACHE* for dx resources like textures, targets 
// and buffers. It has nothing to do with other render functionality.
// BEGIN {

static int screenshotCount = 0;

void DumpScreenshot( const nstl::string& filename, bool keepAlpha )
{
  // extract extension
  size_t pos = filename.rfind('.');
  string extension = (pos == string::npos) ? string(".bmp") : NStr::GetLower(filename.substr(pos));

  // find proper format
  static struct
  {
    const char* name;
    D3DXIMAGE_FILEFORMAT format;
  } supported[] =
  {
    {".bmp", D3DXIFF_BMP},
    {".jpg", D3DXIFF_JPG},
    {".jpeg",D3DXIFF_JPG},
    {".png", D3DXIFF_PNG},
    {".dds", D3DXIFF_DDS},
    {".hdr", D3DXIFF_HDR},
  };
  D3DXIMAGE_FILEFORMAT format = D3DXIFF_BMP;
  for (int i = 0; i < ARRAY_SIZE(supported); ++i)
    if (extension == supported[i].name)
      format = supported[i].format;

  if (keepAlpha)
  {
    // just write to file backbuffer as is
    HRESULT hr = D3DXSaveSurfaceToFile( filename.c_str(), format, Get(GetRenderer()->GetColorSurface()), 0, 0 );
    NI_DX_THROW(hr, __FUNCTION__);
  }
  else // convert surface to get rid of alpha
  {
    DXSurfacePtr const& pSource = GetRenderer()->GetColorSurface();
    D3DSURFACE_DESC desc;
    HRESULT hr = pSource->GetDesc(&desc);
    NI_DX_THROW(hr, __FUNCTION__);

    desc.Format = D3DFMT_X8R8G8B8;
    desc.MultiSampleType = D3DMULTISAMPLE_NONE;
    desc.MultiSampleQuality = 0;
    RenderSurfaceRef pDest = Create<RenderSurface>(desc);
    hr = D3DXLoadSurfaceFromSurface(Get(pDest->GetDXSurface()), NULL, NULL, Get(pSource), NULL, NULL, D3DX_FILTER_NONE, 0);
    NI_DX_THROW(hr, __FUNCTION__);

    hr = D3DXSaveSurfaceToFile( filename.c_str(), format, Get(pDest->GetDXSurface()), NULL, NULL );
    NI_DX_THROW(hr, __FUNCTION__);
  }

  ++screenshotCount;
}

int GetScreenshotCount()
{
  return screenshotCount;
}

byte* DumpScreenshotToMemory( int width, int height )
{
  int headerSize = 128;
  LPD3DXBUFFER pBuffer = 0;
  D3DXSaveSurfaceToFileInMemory( &pBuffer, D3DXIFF_DDS, Get(Render::GetRenderer()->GetColorSurface()), 0, 0 );
  byte* ptr = (byte*)(pBuffer)->GetBufferPointer();
  unsigned int len = (pBuffer)->GetBufferSize();
  int realLength = len-headerSize;
  NI_ASSERT( width*height*4 == realLength, "Bad Array" );
  byte* realPtr = ptr+headerSize;
  byte* res = new byte[realLength];
  memcpy(res,realPtr,realLength);
  pBuffer->Release();  
  return res;
}

void SetMainViewport( int x, int y, int width, int height ) // smirnov [2009/7/15]: why "Main"?
{
  viewport.X = x;
  viewport.Y = y;
  viewport.Width = width;
  viewport.Height = height;
  viewport.MinZ = 0;
  viewport.MaxZ = 1;

  useViewport = true;
}

void GetMainViewport( int& x, int& y, int& width, int& height )
{
  D3DVIEWPORT9 tempVP;
  D3DVIEWPORT9 *pVP = &viewport;
  if(!useViewport) {
    GetDevice()->GetViewport(&tempVP);
    pVP = &tempVP;
  }

  x = pVP->X;
  y = pVP->Y;
  width = pVP->Width;
  height = pVP->Height;
}

void ResetMainViewport()
{
  HRESULT hr = GetDevice()->SetViewport( &viewport );
  if(s_DXWarnLevel > 1)
    NI_DX_WARN(hr, "ResetMainViewport");
}

void FixViewport() // clip viewport size by depth-stencil's surface size
{
  if(!curDepthSurface)
    return;

  const bool smallViewPort = (curColorSurfaceWidth > viewport.Width || curColorSurfaceHeight > viewport.Height);
  if(useViewport && smallViewPort) {
    HRESULT hr = GetDevice()->SetViewport(&viewport);
    if(s_DXWarnLevel > 1)
      NI_DX_WARN(hr, "FixViewport");
  }
}

void SetUseMainViewport( bool _useViewport ) // smirnov [2009/7/15]: make it return previous value
{
  useViewport = _useViewport; // smirnov [2009/7/15]: who will restore viewport to original value? will wait until next SetRenderTarget()?
}

bool UseMainViewport()
{
  return useViewport;
}

// } END

}; // namespace SmartRenderer
}; // namespace Render
