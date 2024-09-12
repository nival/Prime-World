#include "stdafx.h"

#include "System/FixedVector.h"
#include "System/nvector.h"
#include "System/nhash_map.h"
// #include "../System/StackWalk.h"
#include "System/FileSystem/FileUtils.h"
#include "System/LogFileName.h"

#include "Vendor/DTW/inc/dbghelp.h"
// 
// #include "Vendor/DirectX/Include/d3d9.h"
// #include "Vendor/DirectX/Include/d3dx9.h"
#include "../MemoryLib/SymAccess.h"
#include "dxutils.h"
#include "DxResourcesControl.h"
#include "smartrenderer.h"

namespace
{

NDebug::DebugVar<int> mem_Surfaces( "01_SF", "Statistics" );
NDebug::DebugVar<int> mem_Textures( "02_TX", "Statistics" );
NDebug::DebugVar<int> mem_VertexBuffer( "03_VB", "Statistics" );
NDebug::DebugVar<int> mem_IndexBuffer( "04_IB", "Statistics" );
NDebug::DebugVar<int> mem_Other( "05_Other", "Statistics" );
NDebug::DebugVar<int> mem_TotalRenderResource( "00_Total", "Statistics" );
NDebug::DebugVar<int> mem_SurfacesDP( "01_SF_DP", "Statistics" );
NDebug::DebugVar<int> mem_TexturesDP( "02_TX_DP", "Statistics" );
NDebug::DebugVar<int> mem_VertexBufferDP( "03_VB_DP", "Statistics" );
NDebug::DebugVar<int> mem_IndexBufferDP( "04_IB_DP", "Statistics" );
NDebug::DebugVar<int> mem_OtherDP( "05_Other_DP", "Statistics" );
NDebug::DebugVar<int> mem_TotalRenderResourceDP( "00_Total_DP", "Statistics" );
NDebug::DebugVar<int> res_Surfaces( "01_SF_I", "Statistics" );
NDebug::DebugVar<int> res_Textures( "02_TX_I", "Statistics" );
NDebug::DebugVar<int> res_VertexBuffer( "03_VB_I", "Statistics" );
NDebug::DebugVar<int> res_IndexBuffer( "04_IB_I", "Statistics" );
NDebug::DebugVar<int> res_Other( "05_Other_I", "Statistics" );
NDebug::DebugVar<int> res_TotalRenderResource( "00_Total_I", "Statistics" );

#define MAX_STACK_SIZE 64

struct ResourcePool;

struct DxResInfo
{
  DXPtrType     type;
  UINT          size;
  ResourcePool *pool;
  D3DPOOL       poolDX;

#ifdef DX_RESOURCE_STACK
  DWORD stack[MAX_STACK_SIZE];
#endif
};

void IncrementTotalCounter(const DxResInfo &res);
void DecrementTotalCounter(const DxResInfo &res);

struct ResourcePool
{
  int  memory;

  ResourcePool() : memory(0) {}

  void AddResource(DxResInfo &res)
  {
    memory += res.size;
    res.pool = this;
    IncrementTotalCounter(res);
  }

  void RemoveResource(DxResInfo &res)
  {
    NI_ASSERT(res.pool == this, "This resource was not allocated in this pool");
    res.pool = NULL;
    memory -= res.size;
    DecrementTotalCounter(res);
  }
};

static const DWORD D3DPOOLS_NUMBER = D3DPOOL_SCRATCH + 1;
typedef FixedVector<ResourcePool, DPT_COUNT>  PoolsByResource;
typedef FixedVector<PoolsByResource, D3DPOOLS_NUMBER>  PoolsByD3DResource;
typedef hash_map<string, PoolsByD3DResource>  PoolHash;

list<string> poolStack;
PoolHash pools;
nstl::hash_map<void*, DxResInfo> *pPtrs = 0;

NDebug::DebugVar<int> *totalMemCounters[DPT_COUNT + 1] =
{
  NULL, // DPT_VertexShader
  NULL, // DPT_PixelShader
  &mem_Textures, // DPT_Texture
  &mem_VertexBuffer, // DPT_VertexBuffer
  &mem_IndexBuffer, // DPT_IndexBuffer
  &mem_Surfaces, // DPT_Surface
  NULL, // DPT_VertexDeclaration
  &mem_Other
};

NDebug::DebugVar<int> *totalResCounters[DPT_COUNT + 1] =
{
  NULL, // DPT_VertexShader
  NULL, // DPT_PixelShader
  &res_Textures, // DPT_Texture
  &res_VertexBuffer, // DPT_VertexBuffer
  &res_IndexBuffer, // DPT_IndexBuffer
  &res_Surfaces, // DPT_Surface
  NULL, // DPT_VertexDeclaration
  &res_Other
};

NDebug::DebugVar<int> *defaultPoolCounters[DPT_COUNT + 1] =
{
  NULL, // DPT_VertexShader
  NULL, // DPT_PixelShader
  &mem_TexturesDP, // DPT_Texture
  &mem_VertexBufferDP, // DPT_VertexBuffer
  &mem_IndexBufferDP, // DPT_IndexBuffer
  &mem_SurfacesDP, // DPT_Surface
  NULL, // DPT_VertexDeclaration
  NULL
};

//////////////////////////////////////////////////////////////////////////////////////////////////
inline float BytesToMegabytes(int bytes)
{
  return (float)bytes / (1024.f * 1024.f);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
void IncrementTotalCounter(const DxResInfo &res)
{
  if( NDebug::DebugVar<int> *pCounter = totalMemCounters[res.type] )
    pCounter->AddValue(res.size);
  else
    mem_Other.AddValue(res.size);

  if( D3DPOOL_DEFAULT == res.poolDX )
  {
    mem_TotalRenderResourceDP.AddValue(res.size);
    if( NDebug::DebugVar<int> *pCounterDP = defaultPoolCounters[res.type] )
      pCounterDP->AddValue(res.size);
  }

  // update main total counter
  mem_TotalRenderResource.AddValue(res.size);

  // do all the same for instance counters
  if( NDebug::DebugVar<int> *pCounter = totalResCounters[res.type] )
    pCounter->AddValue(1);
  else
    res_Other.AddValue(1);

  // update main total counter
  res_TotalRenderResource.AddValue(1);
}

void DecrementTotalCounter(const DxResInfo &res)
{
  if(NDebug::DebugVar<int> *pCounter = totalMemCounters[res.type])
    pCounter->DecValue(res.size);
  else
    mem_Other.DecValue(res.size);

  if( D3DPOOL_DEFAULT == res.poolDX )
  {
    mem_TotalRenderResourceDP.DecValue(res.size);
    if( NDebug::DebugVar<int> *pCounterDP = defaultPoolCounters[res.type] )
      pCounterDP->DecValue(res.size);
  }

  // update main total counter
  mem_TotalRenderResource.DecValue(res.size);
}

#ifdef DX_RESOURCE_CONTROL
//////////////////////////////////////////////////////////////////////////////////////////////////
static void GetResourceSizeAndPool(IUnknown *ptr, DxResInfo *pInfo)
{
  switch( pInfo->type )
  {
    case DPT_Texture:
    {
      IDirect3DBaseTexture9 *pTex = static_cast<IDirect3DBaseTexture9*>(ptr);
      NI_ASSERT(pTex, "Failed to parse texture resource");
      if( pTex ) {
        const UINT  levelScale  = 1 << ( 2 * pTex->GetLevelCount() );
        const float mipMapScale = float(levelScale - 1) / (6 * levelScale);
        switch( pTex->GetType() )
        {
        case D3DRTYPE_TEXTURE:
          {
            D3DSURFACE_DESC desc;
            static_cast<IDirect3DTexture9*>(pTex)->GetLevelDesc(0, &desc);
            // Calculate approximate texture size in bytes
            pInfo->size = mipMapScale * desc.Width * desc.Height * Render::D3DFormatNumBits(desc.Format); // size including mip-maps
            pInfo->poolDX = desc.Pool;
            break;
          }
        case D3DRTYPE_VOLUMETEXTURE:
          {
            D3DVOLUME_DESC desc;
            static_cast<IDirect3DVolumeTexture9*>(pTex)->GetLevelDesc(0, &desc);
            // Calculate approximate texture size in bytes
            pInfo->size = mipMapScale * desc.Width * desc.Height * desc.Depth * Render::D3DFormatNumBits(desc.Format); // size including mip-maps
            pInfo->poolDX = desc.Pool;
            break;
          }
        case D3DRTYPE_CUBETEXTURE:
          {
            D3DSURFACE_DESC desc;
            static_cast<IDirect3DCubeTexture9*>(pTex)->GetLevelDesc(0, &desc);
            // Calculate approximate texture size in bytes
            pInfo->size = mipMapScale * desc.Width * desc.Height * Render::D3DFormatNumBits(desc.Format) * 6; // size including mip-maps
            pInfo->poolDX = desc.Pool;
            break;
          }
        default:
          NI_ALWAYS_ASSERT("GetResourceSizeAndPool - wrong texture identification");
        }
      }
      break;
    }
    case DPT_VertexBuffer:
    {
      IDirect3DVertexBuffer9 *pVB = static_cast<IDirect3DVertexBuffer9*>(ptr);
      if (pVB)
      {
        D3DVERTEXBUFFER_DESC desc;
        pVB->GetDesc(&desc);
        pInfo->size = desc.Size;
        pInfo->poolDX = desc.Pool;
      }
      break;
    }
    case DPT_IndexBuffer:
    {
      IDirect3DIndexBuffer9 *pIB = static_cast<IDirect3DIndexBuffer9*>(ptr);
      if (pIB)
      {
        D3DINDEXBUFFER_DESC desc;
        pIB->GetDesc(&desc);
        pInfo->size = desc.Size;
        pInfo->poolDX = desc.Pool;
      }
      break;
    }
    case DPT_Surface:
    {
      IDirect3DSurface9 *pSurf = static_cast<IDirect3DSurface9*>(ptr);
      NI_ASSERT(pSurf, "Failed to parse surface resource");
      if (pSurf)
      {
        D3DSURFACE_DESC desc;
        pSurf->GetDesc(&desc);
        pInfo->size = desc.Width * desc.Height * Render::D3DFormatNumBits(desc.Format) / 8;
        pInfo->poolDX = desc.Pool;
      }
      break;
    }
    case DPT_VertexShader:
    {
      IDirect3DVertexShader9 *pShader = static_cast<IDirect3DVertexShader9*>(ptr);
      NI_ASSERT(pShader, "Failed to parse shader resource");
      if (pShader)
      {
        UINT dataSize;
        pShader->GetFunction(NULL, &dataSize);
        pInfo->size = dataSize;
        pInfo->poolDX = D3DPOOL_MANAGED;
      }
      break;
    }
    case DPT_PixelShader:
    {
      IDirect3DPixelShader9 *pShader = static_cast<IDirect3DPixelShader9*>(ptr);
      NI_ASSERT(pShader, "Failed to parse shader resource");
      if (pShader)
      {
        UINT dataSize;
        pShader->GetFunction(NULL, &dataSize);
        pInfo->size = dataSize;
        pInfo->poolDX = D3DPOOL_MANAGED;
      }
      break;
    }
    case DPT_VertexDeclaration:
    {
      IDirect3DVertexDeclaration9 *pDecl = static_cast<IDirect3DVertexDeclaration9*>(ptr);
      NI_ASSERT(pDecl, "Failed to parse declaration resource");
      if (pDecl)
      {
        UINT dataCount;
        pDecl->GetDeclaration(NULL, &dataCount);
        pInfo->size = dataCount * sizeof(D3DVERTEXELEMENT9);
        pInfo->poolDX = D3DPOOL_MANAGED;
      }
      break;
    }
  }
}
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////
void Assign( ADDRESS64 *pRes, DWORD /*dwSeg*/, DWORD64 dwOffset )
{
  pRes->Mode = AddrModeFlat;
  pRes->Offset = dwOffset;
  pRes->Segment = 0;//dwSeg;
}

#pragma warning( disable : 4740 ) //warning C4740: flow in or out of inline asm code suppresses global optimization
int QuickCollectCallStack( DWORD *pAddresses, int nMaxEntries )
{
  DWORD dwAddr, dwEbp, dwEsp;
  __asm
  {
    call nxt
nxt:
    pop [dwAddr]
    mov dwEbp, ebp
      mov dwEsp, esp
  }

  CONTEXT ctx;
  EXCEPTION_POINTERS ep;
  ep.ContextRecord = &ctx;
  ctx.Eip = dwAddr;
  ctx.Ebp = dwEbp;
  ctx.Esp = dwEsp;

  STACKFRAME64 stkFrame;

  memset( &stkFrame, 0, sizeof( stkFrame ) );
  Assign( &stkFrame.AddrPC, ep.ContextRecord->SegCs, ep.ContextRecord->Eip );
  Assign( &stkFrame.AddrFrame, ep.ContextRecord->SegSs, ep.ContextRecord->Ebp );
  Assign( &stkFrame.AddrStack, ep.ContextRecord->SegSs, ep.ContextRecord->Eip );

  int nEntry = 0;
  for ( nEntry = 0; nEntry < nMaxEntries; ++nEntry )
  {
    BOOL bRes = StackWalk64( IMAGE_FILE_MACHINE_I386, GetCurrentProcess(), GetCurrentThread(), &stkFrame, ep.ContextRecord, 0, 
      SymFunctionTableAccess64, SymGetModuleBase64, 0 );
    if ( !bRes || stkFrame.AddrPC.Offset == 0 )
      break;
    pAddresses[nEntry] = (DWORD)stkFrame.AddrPC.Offset;
  }
  return nEntry;
}

bool DumpResourceMemory( const char *name, const vector<wstring>& params )
{
  char buf[256];

  systemLog( NLogg::LEVEL_MESSAGE ) << "Pool                    TX    VB    IB    SF    XX" << endl;
  systemLog( NLogg::LEVEL_MESSAGE ) << "----------------------------------------------------------" << endl;

  PoolHash::iterator it;
  for (it = pools.begin(); it != pools.end(); ++it)
  {
    for(DWORD n = 0; n < D3DPOOLS_NUMBER; ++n)
    {
      sprintf_s(buf, "D3DPOOL == %d\n", n);
      systemLog( NLogg::LEVEL_MESSAGE ) << buf;
      int j;
      for (j = 0; j < DPT_COUNT; ++j)
      {
        if (it->second[n][j].memory > 0)
          break;
      }

      // dump only non-empty pools
      if (j < DPT_COUNT)
      {
        PoolsByResource &pbr = it->second[n];

        int other = 0;
        for (int i = 0; i < DPT_COUNT; ++i)
        {
          if (totalMemCounters[i] == NULL)
          {
            other += pbr[i].memory;
          }
        }

        sprintf_s(buf, "%-20s %5.1f %5.1f %5.1f %5.1f %5.1f", it->first.c_str(), BytesToMegabytes(pbr[DPT_Texture].memory),
                                                              BytesToMegabytes(pbr[DPT_VertexBuffer].memory),
                                                              BytesToMegabytes(pbr[DPT_IndexBuffer].memory),
                                                              BytesToMegabytes(pbr[DPT_Surface].memory),
                                                              BytesToMegabytes(other));
        systemLog( NLogg::LEVEL_MESSAGE ) << buf;
      }
    }
  }

  systemLog( NLogg::LEVEL_MESSAGE ) << "----------------------------------------------------------" << endl;
  sprintf_s(buf, 256, "%-20s %5.1f %5.1f %5.1f %5.1f %5.1f %5.1f", "Total", BytesToMegabytes(totalMemCounters[DPT_Texture]->GetValue()),
                                                                BytesToMegabytes(totalMemCounters[DPT_VertexBuffer]->GetValue()),
                                                                BytesToMegabytes(totalMemCounters[DPT_IndexBuffer]->GetValue()),
                                                                BytesToMegabytes(totalMemCounters[DPT_Surface]->GetValue()),
                                                                BytesToMegabytes(mem_Other.GetValue()),
                                                                BytesToMegabytes(mem_TotalRenderResource.GetValue()));
  systemLog( NLogg::LEVEL_MESSAGE ) << buf;

  return true;
}


HANDLE logFile = INVALID_HANDLE_VALUE;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OpenLogFile()
{
  logFile = CreateFileA( NDebug::GenerateDebugFileName( "DXResourcesLeaks", "log" ).c_str(),
                         GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0 );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void CloseLogFile()
{
  if ( logFile != INVALID_HANDLE_VALUE )
  {
    CloseHandle( logFile );
    logFile = INVALID_HANDLE_VALUE;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DumpString( const char* message )
{
  if ( logFile == INVALID_HANDLE_VALUE )
    OutputDebugString( message );
  else
  {
    int bytesToWrite = strlen( message );
    DWORD bytesWritten = 0;
    WriteFile( logFile, message, bytesToWrite, &bytesWritten, 0 );
  }
}

const char *StrFmt( const char *pszFormat, ... )
{
  static char charBuff[1024] = { '\0' };
  va_list va;
  va_start( va, pszFormat );
  _vsnprintf_s( charBuff, 1024 - 1, pszFormat, va );
  va_end( va );
  return charBuff;
}

} // ns

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
string const &GetCurrentDXPool()
{
  return poolStack.front();
}

void PushDXPool(char const *pool)
{
  if (poolStack.empty())
  {
    poolStack.push_front("Default");
  }
  poolStack.push_front(string(pool));
}

void PopDXPool(char const *pool)
{
  NI_ASSERT(!poolStack.empty(), "Resource pool stack is empty when popping.");
  NI_ASSERT(poolStack.front() == pool, NStr::StrFmt("Incorrect order of resource pool marks: trying to release '%s' while '%s' is current", pool, poolStack.front()));
  poolStack.pop_front();
}

#ifdef DX_RESOURCE_CONTROL

void RegisterDXPtr(IDirect3DResource9 *ptr)
{
  if(!ptr)
    return;

  DXPtrType type = DXPtrType(); // initialize "type" just to make compiler happy
  switch( ptr->GetType() )
  {
  case D3DRTYPE_SURFACE:
  case D3DRTYPE_VOLUME:
    type = DPT_Surface; break;
  case D3DRTYPE_TEXTURE:
  case D3DRTYPE_VOLUMETEXTURE:
  case D3DRTYPE_CUBETEXTURE:
    type = DPT_Texture; break;
  case D3DRTYPE_VERTEXBUFFER:
    type = DPT_VertexBuffer; break;
  case D3DRTYPE_INDEXBUFFER:
    type = DPT_IndexBuffer; break;
  default:
    NI_ALWAYS_ASSERT("RegisterDXPtr - wrong resource type");
  }
  RegisterDXPtr(ptr, type);
}


void RegisterDXPtr(IUnknown *ptr, DXPtrType type)
{
  if( poolStack.empty() )
    poolStack.push_front("Default");

  if(!pPtrs)
    pPtrs = ::new nstl::hash_map<void*, DxResInfo>;

  nstl::hash_map<void*, DxResInfo>::iterator it = pPtrs->find(ptr);
  if( it != pPtrs->end() )
    return;

  DxResInfo &ptrInfo = (*pPtrs)[ptr];
  ptrInfo.type = type;
  GetResourceSizeAndPool(ptr, &ptrInfo);

  if (pools.find(GetCurrentDXPool()) == pools.end())
  {
    pools.insert(GetCurrentDXPool());
    PoolsByD3DResource &dxPools = pools[GetCurrentDXPool()];
    dxPools.setsize(D3DPOOLS_NUMBER);
    for(DWORD n = 0; n < D3DPOOLS_NUMBER; ++n)
      dxPools[n].setsize(DPT_COUNT);
  }

  pools[GetCurrentDXPool()][ptrInfo.poolDX][ptrInfo.type].AddResource(ptrInfo);

#ifdef DX_RESOURCE_STACK
  const int stackPos = QuickCollectCallStack( ptrInfo.stack, MAX_STACK_SIZE );

  if ( stackPos + 1 < MAX_STACK_SIZE )
    ptrInfo.stack[stackPos + 1] = 0;
#endif // DX_RESOURCE_STACK
}


void UnregisterDXPtr(IUnknown *ptr)
{
  if(!pPtrs) {
    NI_ALWAYS_ASSERT("Excessive UnregisterDXPtr call");
    return;
  }
  nstl::hash_map<void*, DxResInfo>::iterator ptrInfo = pPtrs->find( ptr );
  if ( ptrInfo != pPtrs->end() )
  {
    if( ptrInfo->second.pool )
      ptrInfo->second.pool->RemoveResource(ptrInfo->second);
    else
      NI_ALWAYS_ASSERT("Resource was not allocated in any pool, weird.");

    pPtrs->erase( ptrInfo );
  }
  else
  {
    //OutputDebugString( "Unregistering not registered DX resource pointer!.\n" );
  }

  if ( pPtrs->empty() )
  {
    delete pPtrs;
    pPtrs = 0;
  }
}

void DumpDXResourcesLeaks()
{
  if ( !pPtrs )
  {
    OutputDebugString( "No DX resources leaks detected. Looks like everything is fine ;-).\n" );
    return;
  }
  OutputDebugString( "DX resources leaks detected! See log file.\n" );

// 
// #ifdef DX_RESOURCE_STACK
//   if ( !g_dumpOnlyAmount )
//   {
//     if ( DUMP_LEAKS_TO_FILE )
    OpenLogFile();
    nstl::vector<DxResInfo> sortedPtrs;
    sortedPtrs.resize( pPtrs->size() );
    int index = 0;
    for( nstl::hash_map<void*, DxResInfo>::const_iterator it = pPtrs->begin(); it != pPtrs->end(); ++it, ++index )
      sortedPtrs[index] = it->second;

//     nstl::sort( sortedPtrs.begin(), sortedPtrs.end(), CompareAllocInfo );

    int leaksCount = sortedPtrs.size();
    int leaks2Show;
//     if (leaksCount <= MAX_LEAKS_TO_DUMP)
//     {	
      leaks2Show = leaksCount;
//     }
//     else
//     {
//       leaks2Show = MAX_LEAKS_TO_DUMP;
//       DumpString( StrFmt( "TOO MANY LEAKS. Showing first %d.\n", leaks2Show ) );
//     }
    DumpString( StrFmt( "%d resources are NOT released\n", leaksCount ) );
    int i;
    for( i = 0; i < leaks2Show; ++i )
    {
      DxResInfo *it = &sortedPtrs[i];
      static char *types[] = {"Vertex shader", "Pixel shader", "Texture", "Vertex buffer", "Index buffer", "Surface", "Vertex declaration"};
      NI_STATIC_ASSERT(ARRAY_SIZE(types) == DPT_COUNT, ARRAY_SIZE_MISMATCH);

      DumpString( StrFmt( "%d. %s:\n", i, types[it->type] ) );

//       DumpString( StrFmt( "[%d]: leaked %d bytes at 0x%08X:\n", it->mallocIndex, it->size, it->pData ) );
//       OutputDebugData( (char*)(it->pData), it->size );
#ifdef DX_RESOURCE_STACK
      static int interestingStack = 2;
      for ( int stackPos = interestingStack; stackPos < MAX_STACK_SIZE && it->stack[stackPos] != 0; ++stackPos )
      {
        int sourceLine;
        CSymString fileName;
        LockSymEngine().GetSymbol( it->stack[stackPos], 0, &fileName, &sourceLine, 0 );
        ReleaseSymEngine();

        DumpString( StrFmt( "  %s(%d):\n", fileName.szStr, sourceLine ) );
        //OutputDebugString( StrFmt( "0x%08X:\n", it->second.stack[stackPos] ) );
      }
#endif // DX_RESOURCE_STACK
      DumpString( "\n" );
    }
//     DumpString( StrFmt( "Total leaked %d bytes in %d calls of %d calls total\n", bytesLeaked, sortedPtrs.size(), g_mallocIndex ) );
    CloseLogFile();
//   }
//   else
//     OutputDebugString( StrFmt( "%d new(s) has no appropriate delete\n", g_unfreeMaloc ) );

// #else // DX_RESOURCE_STACK
//   OutputDebugString( StrFmt( "%d new(s) has no appropriate delete\n", g_unfreeMaloc ) );
// #endif // DX_RESOURCE_STACK
};

bool isInDefaultPool(IUnknown* ptr, DXPtrType type)
{
  IDirect3DResource9* pResource = 0;
  if( FAILED(ptr->QueryInterface(IID_IDirect3DResource9, (void**)&pResource)) )
    return false;

  D3DRESOURCETYPE dxType = pResource->GetType();
  if (dxType == D3DRTYPE_TEXTURE)
  {
    ASSERT(type == DPT_Texture);
    IDirect3DTexture9* pTexture = static_cast<IDirect3DTexture9*>(ptr);
    D3DSURFACE_DESC desc;
    pTexture->GetLevelDesc(0, &desc);
    return desc.Pool == D3DPOOL_DEFAULT;
  }
  else if (dxType == D3DRTYPE_CUBETEXTURE)
  {
    ASSERT(type == DPT_Texture);
    IDirect3DCubeTexture9* pTexture = static_cast<IDirect3DCubeTexture9*>(ptr);
    D3DSURFACE_DESC desc;
    pTexture->GetLevelDesc(0, &desc);
    return desc.Pool == D3DPOOL_DEFAULT;
  }
  else if (dxType == D3DRTYPE_SURFACE)
  {
    ASSERT(type == DPT_Surface);
    IDirect3DSurface9* pSurface = static_cast<IDirect3DSurface9*>(ptr);
    D3DSURFACE_DESC desc;
    pSurface->GetDesc(&desc);
    return desc.Pool == D3DPOOL_DEFAULT;
  }
  else if (dxType == D3DRTYPE_VERTEXBUFFER)
  {
    ASSERT(type == DPT_VertexBuffer);
    IDirect3DVertexBuffer9* pVertexBuffer = static_cast<IDirect3DVertexBuffer9*>(ptr);
    D3DVERTEXBUFFER_DESC desc;
    pVertexBuffer->GetDesc(&desc);
    return desc.Pool == D3DPOOL_DEFAULT;
  }
  else if (dxType == D3DRTYPE_INDEXBUFFER)
  {
    ASSERT(type == DPT_IndexBuffer);
    IDirect3DIndexBuffer9* pIndexBuffer = static_cast<IDirect3DIndexBuffer9*>(ptr);
    D3DINDEXBUFFER_DESC desc;
    pIndexBuffer->GetDesc(&desc);
    return desc.Pool == D3DPOOL_DEFAULT;
  }

  return false;
}

void DumpDXResourcesInDefaultPool()
{
  int i = 0;
  for (nstl::hash_map<void*, DxResInfo>::const_iterator it = pPtrs->begin(); it != pPtrs->end(); ++it)
  {
    IUnknown* ptr = (IUnknown*)(it->first);
    DxResInfo const* pInfo = &it->second;

    NI_ASSERT(*PDWORD(ptr) != 0xfeeefeee, "");
    if (!ptr || Render::SmartRenderer::IsResourceBound(ptr) || !isInDefaultPool(ptr, pInfo->type))
      continue;

    // report for the first time
    if (i == 0)
    {
      systemLog(NLogg::LEVEL_ASSERT) << "Found unreleased resources in D3DPOOL_DEFAULT. Reset() will probably fail." << endl;
      systemLog(NLogg::LEVEL_ASSERT) << "See resource dump in DXResourcesLeaks-XXX.log" << endl;
      OpenLogFile();
      DumpString("Some resources in D3DPOOL_DEFAULT are NOT released at the Reset() time\n");
    }

    static char *types[] = {"Vertex shader", "Pixel shader", "Texture", "Vertex buffer", "Index buffer", "Surface", "Vertex declaration"};
    NI_STATIC_ASSERT(ARRAY_SIZE(types) == DPT_COUNT, ARRAY_SIZE_MISMATCH);
    DumpString( StrFmt( "%d. %s:\n", i++, types[pInfo->type] ) );

#ifdef DX_RESOURCE_STACK
    static int interestingStack = 2;
    for ( int stackPos = interestingStack; stackPos < MAX_STACK_SIZE && pInfo->stack[stackPos] != 0; ++stackPos )
    {
      int sourceLine;
      CSymString fileName;
      LockSymEngine().GetSymbol( pInfo->stack[stackPos], 0, &fileName, &sourceLine, 0 );
      ReleaseSymEngine();

      DumpString( StrFmt( "  %s(%d):\n", fileName.szStr, sourceLine ) );
    }
#endif // DX_RESOURCE_STACK
    DumpString( "\n" );
  }
  CloseLogFile();
}

#endif // DX_RESOURCE_CONTROL

REGISTER_DEV_CMD( dump_resource_memory, DumpResourceMemory );
