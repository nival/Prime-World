#include "stdafx.h"
#include "renderflagsconverter.h"
#include "renderer.h"
#include "TextureManager.h"
#include "DxResourcesControl.h"
#include "ReadDDS.h"

#include "smartrenderer.h"
#include "../System/nalgoritm.h"
#include "libdb/DbResourceCache.h"

static NDebug::DebugVar<unsigned int> render_TexturesCount( "TexturesCount", "Statistics" );
static NDebug::PerformanceDebugVar render_TexturesLoadTime( "LoadTimeTextures", "RenderOffline", 100, 100, false );

static bool g_disableTextureLoads = false;
REGISTER_DEV_VAR("no_texture_loads", g_disableTextureLoads, STORAGE_NONE);


namespace Render
{

namespace RenderResourceManager
{
  bool IsSecondaryThread();
}

DECLARE_NULL_RENDER_FLAG

// Internal functions
namespace
{

struct PoolTextureWrapper
{
public :
  PoolTextureWrapper(  ) : texPtr(NULL), sizeInFile(0) {}
  PoolTextureWrapper( TextureRef texRef_, SWin32Time modificationTime_, UINT skipMipLevels, bool canBeVisualDegrade, void * firstPoolId, int sizeInFile_ ) :
    texPtr( texRef_ ),
    modificationTime( modificationTime_ ),
    skipMipLevels( skipMipLevels ),
    canBeVisualDegrade( canBeVisualDegrade ),
    sizeInFile( sizeInFile_ )
  {
    usedInPools.reserve( 4 );
    usedInPools.push_back( firstPoolId );
  }

public :
  TextureRef texPtr;
  SWin32Time modificationTime;
  UINT skipMipLevels;
  bool canBeVisualDegrade;
  //Я использую vector<> сознательно - операции вставки/поиска/удаления происходят редко, а размер вектора будет небольшим
  vector<void *> usedInPools;
  int sizeInFile;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//============================================================================================================
class PoolMT
{
public:
  ~PoolMT()
  {
    Clear();
  }

protected:
  typedef nstl::hash_map<nstl::string, PoolTextureWrapper> TexturesPool;
  TexturesPool texturesPool;
  TexturesPool loadingPool;

  threading::Mutex loadMutex;

  bool FindMain(const nstl::string& _filename, PoolTextureWrapper* _result)
  {
    TexturesPool::iterator it = texturesPool.find(_filename);
    if(texturesPool.end() != it) {
      *_result = it->second;
      return true;
    }

    threading::MutexLock lock(loadMutex);

    it = loadingPool.find(_filename);
    if(loadingPool.end() == it)
      return false;
    // Unfortunately, we MUST copy it->second (i.e.PoolTextureWrapper) here, because loadingPool iterators are not stable
    *_result = it->second;
    return true;
  }

  bool FindSecondary(const nstl::string& _filename, PoolTextureWrapper* _result)
  {
    threading::MutexLock lock(loadMutex);

    TexturesPool::iterator it = texturesPool.find(_filename);
    if(texturesPool.end() != it) {
      *_result = it->second;
      return true;
    }
    it = loadingPool.find(_filename);
    if(loadingPool.end() == it)
      return false;

    *_result = it->second;
    return true;
  }

public:
  bool Find(const nstl::string& filename, PoolTextureWrapper* _result)
  {
    return RenderResourceManager::IsSecondaryThread() ? FindSecondary(filename, _result)
                                                      : FindMain(filename, _result);
  }

  void MarkAsLoaded(const PoolTextureWrapper& _wrapper, const nstl::string& _filename)
  {
    threading::MutexLock lock(loadMutex);
    loadingPool.insert( make_pair(_filename, _wrapper) );
  }

  void MoveMarkedInPool()
  {
    threading::MutexLock lock(loadMutex);
    texturesPool.insert( loadingPool.begin(), loadingPool.end() );
    loadingPool.clear();
  }

  void Clear()
  {
    threading::MutexLock lock(loadMutex);
    loadingPool.clear();
    texturesPool.clear();
  }

  void ForAllTextures(TextureProc &p);
  void ReloadTextures(bool bModifiedOnly);
  void UnloadTexturePool(void * poolId);
  bool Dump(const char *name, const vector<wstring>& params);
};


PoolMT s_texturesPool;
bool g_showMipMap = false;
static int g_skipMipLevels = 0;


REGISTER_DEV_VAR( "show_mipmap", g_showMipMap, STORAGE_NONE );
REGISTER_VAR_PRED( "gfx_skip_mip_levels", g_skipMipLevels, STORAGE_USER, NGlobal::MakeMinMaxVerifyPred(0, 5) );


HRESULT ProcessMipMaps(IDirect3DTexture9 **ppD3DTexture, UINT skipMipLevels, Stream *pStream)
{
  static   int mipMapColors[8][4] = {{0xFF, 0xFF, 0xFF, 0xFF} // ARGB
  , {0xFF, 0xFF, 0, 0}
  , {0xFF, 0, 0xFF, 0}
  , {0xFF, 0, 0, 0xFF}
  , {0xFF, 0xFF, 0xFF, 0}
  , {0xFF, 0xFF, 0, 0xFF}
  , {0xFF, 0, 0xFF, 0xFF}
  , {0x80, 0x80, 0x80, 0x80}
  };

  if(RENDER_DISABLED)
    return S_FALSE;

  IDirect3DTexture9* pD3DTexture = 0;
  HRESULT hResult = D3DXCreateTextureFromFileInMemoryEx(GetDevice(), pStream->GetBuffer(), pStream->GetSize(),
    D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0, 
    D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE, D3DX_SKIP_DDS_MIP_LEVELS( skipMipLevels, D3DX_DEFAULT ), 
    0, 0, 0, &pD3DTexture );

  if (hResult == D3D_OK)
  {
    D3DLOCKED_RECT rect;
    for (DWORD level = 0, maxlevel = pD3DTexture->GetLevelCount(); level < maxlevel; level++)
    {
      int const* pColors = mipMapColors[Min(level, (DWORD)(ARRAY_SIZE(mipMapColors) - 1))];
      if (pD3DTexture->LockRect(level, &rect, 0, 0) == D3D_OK)
      {
        D3DSURFACE_DESC levelDesc;
        if (pD3DTexture->GetLevelDesc(level, &levelDesc) == D3D_OK)
        {
          if (levelDesc.Format == D3DFMT_A8R8G8B8)
          {
            for (unsigned int y = 0; y < levelDesc.Height; y++)
            {
              uint* pixel = (uint *)((byte*)rect.pBits + y * rect.Pitch);
              for (unsigned int x = 0; x < levelDesc.Width; x++)
              {
                byte b = *pixel & 0xFF, g = (*pixel >> 8) & 0xFF, r = (*pixel >> 16) & 0xFF, a = (*pixel >> 24) & 0xFF;
                *pixel = ((b * pColors[3]) >> 8) | (((g * pColors[2]) >> 8) << 8) | (((r * pColors[1]) >> 8) << 16) | (((a * pColors[0]) >> 8) << 24);
                *pixel++;
              }
            }
          }
        }
        pD3DTexture->UnlockRect(level);
      }
    }
  }

  *ppD3DTexture = pD3DTexture;
  return hResult;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static HRESULT CreateTextureFromFileInMemoryImpl(IDirect3DTexture9** _pResult, const char * _pBuffer, UINT _dataSize,
                                               UINT _skipMipLevels = 0, const char* _fileName = 0)
{
  IDirect3DBaseTexture9* pBaseTex = 0;
  const HRESULT hr = CreateTextureFromDDSFileInMemory(_pBuffer, _dataSize, _skipMipLevels, &pBaseTex);

  if( SUCCEEDED(hr) ) {
    NI_VERIFY(pBaseTex->GetType() == D3DRTYPE_TEXTURE,
              NStr::StrFmt("Inconsistent texture %s: 2D texture requested, yet it isn't", _fileName),
              pBaseTex->Release(); return E_INVALIDARG);
    *_pResult = static_cast<IDirect3DTexture9*>(pBaseTex);
    return hr;
  }
  else
    return D3DXCreateTextureFromFileInMemoryEx(GetDevice(), _pBuffer, _dataSize,
                                               D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0, 
                                               D3DFMT_FROM_FILE, D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE, 
                                               D3DX_SKIP_DDS_MIP_LEVELS(_skipMipLevels, D3DX_DEFAULT), 
                                               0, 0, 0, _pResult);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool LoadTextureFromFileImpl( const char* fileName, UINT skipMipLevels, Texture2DRef &pTexture, int& sizeInFile )
{
  if( g_disableTextureLoads )
    if( pTexture = GetDefaultTextures().pTexture )
      return true;

  NI_ASSERT( !NDb::GetDbResourceCache().IsAssertionLoadingFiles(), 
    NStr::StrFmt( "Not recommended loading resource \"%s\" after game starting", fileName ) 
  );

	CObj<Stream> pStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open file to load texture from: \"%s\"", fileName ), return false; );

  sizeInFile = pStream->GetSize();

	IDirect3DTexture9* pD3DTexture = 0;
  HRESULT hResult = E_FAIL;
  if(!g_showMipMap) 
    hResult = CreateTextureFromFileInMemoryImpl(&pD3DTexture, pStream->GetBuffer(), sizeInFile, skipMipLevels, fileName);
  else
    hResult = ProcessMipMaps(&pD3DTexture, skipMipLevels, pStream);

  pStream = 0;

  NI_DX_WARN(hResult, "LoadTextureFromFileImpl()");
	NI_VERIFY( SUCCEEDED( hResult ), NStr::StrFmt( "2D texture %s loading failed", fileName ), return false; );

  pTexture = Create<Texture2D>(pD3DTexture);
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool LoadTextureFromFileImpl(const char* fileName, UINT skipMipLevels, TextureCubeRef &pTexture, int& sizeInFile )
{
  NI_ASSERT( !NDb::GetDbResourceCache().IsAssertionLoadingFiles(), 
    NStr::StrFmt( "Not recommended loading resource \"%s\" after game starting", fileName ) 
  );

	CObj<Stream> pStream = RootFileSystem::OpenFile( fileName, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
	NI_VERIFY( pStream && pStream->IsOk(), NStr::StrFmt( "Cannot open file to load texture from: \"%s\"", fileName ), return false; );

  sizeInFile = pStream->GetSize();

	IDirect3DCubeTexture9* d3dtexture = 0;

  HRESULT hResult = E_FAIL;
  IDirect3DBaseTexture9* pBaseTex = 0;
  //if( Compatibility::IsRunnedUnderWine() )  
    hResult = CreateTextureFromDDSFileInMemory(pStream->GetBuffer(), sizeInFile, skipMipLevels, &pBaseTex);

  if( SUCCEEDED(hResult) ) {
    NI_VERIFY(pBaseTex->GetType() == D3DRTYPE_CUBETEXTURE,
              NStr::StrFmt("Inconsistent texture %s: cubemap texture requested, yet it isn't", fileName),
              pBaseTex->Release(); return false);
    d3dtexture = static_cast<IDirect3DCubeTexture9*>(pBaseTex);
  }
  else
	hResult = D3DXCreateCubeTextureFromFileInMemoryEx(GetDevice(), pStream->GetBuffer(), pStream->GetSize(), 
		                                                D3DX_DEFAULT, D3DX_DEFAULT, 0, D3DFMT_FROM_FILE, D3DPOOL_MANAGED,
		                                                D3DX_FILTER_TRIANGLE | D3DX_FILTER_MIRROR | D3DX_FILTER_DITHER,
		                                                D3DX_SKIP_DDS_MIP_LEVELS(skipMipLevels, D3DX_DEFAULT),
		                                                0, 0, 0, &d3dtexture);
	pStream = 0;

	NI_VERIFY(SUCCEEDED(hResult), NStr::StrFmt("Cube texture %s loading failed", fileName), return false);

  pTexture = Create<TextureCube>(d3dtexture);
	return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum LoadTextureFlag
{
  LTF_NONE                  = 0,
  LTF_FORCE_RELOAD          = 1 << 0,
  LTF_CAN_BE_VISUAL_DEGRADE = 1 << 1
};

UINT CalcSkipMipLevels( const bool canBeVisualDegrade )
{
  return canBeVisualDegrade ? static_cast<UINT>(g_skipMipLevels) : 0;
}

template <class T>
CObj<T> LoadTextureFromFile( const nstl::string& _filename, void * poolId, unsigned int flags )
{
  if(RENDER_DISABLED)
    return CObj<T>();

	NDebug::PerformanceDebugVarGuard render_TexturesLoadTimeGuard( render_TexturesLoadTime, false );

  nstl::string correctFileName = ( _filename[0] == '/' || _filename[0] == '\\' ) ? _filename : ( "/" + _filename );

  NI_ASSERT( g_skipMipLevels >= 0 && g_skipMipLevels <= 20, NStr::StrFmt("Incorrect value of gfx_skip_mip_levels = %d", g_skipMipLevels) );
  const bool canBeVisualDegrade = flags & LTF_CAN_BE_VISUAL_DEGRADE;
  const UINT skipMipLevels = CalcSkipMipLevels( canBeVisualDegrade );

	CObj<T> pTexture;
  PoolTextureWrapper wrapper;

	if( s_texturesPool.Find(correctFileName, &wrapper) )
  {
    if(flags & LTF_FORCE_RELOAD) {
      bool bResult = LoadTextureFromFileImpl( correctFileName.c_str(), skipMipLevels, pTexture, wrapper.sizeInFile );
      NI_VERIFY( bResult, NStr::StrFmt( "cant load texture: %s", correctFileName.c_str() ), GetDefaultTexture(pTexture); );
      
      dynamic_cast<T*>( wrapper.texPtr.GetPtr() )->SetTexture(*pTexture);
    }

    //Update texturePoolId
    int poolIdx = 0;
    for( ; poolIdx < wrapper.usedInPools.size(); ++poolIdx )
      if ( wrapper.usedInPools[poolIdx] == poolId )
        break;
    if ( poolIdx == wrapper.usedInPools.size() )
      wrapper.usedInPools.push_back( poolId );

    pTexture = dynamic_cast<T*>( wrapper.texPtr.GetPtr() );
    NI_VERIFY( pTexture, NStr::StrFmt( "requested texture doesn't match type: %s", correctFileName.c_str() ), GetDefaultTexture(pTexture); );
	}
	else
	{
    int sizeInFile = 0;
		bool bResult = LoadTextureFromFileImpl( correctFileName.c_str(), skipMipLevels, pTexture, sizeInFile );
		NI_VERIFY( bResult, NStr::StrFmt( "cant load texture: %s", correctFileName.c_str() ), GetDefaultTexture(pTexture); );

    //FIXME: Accessing filesystem twice!!! Maybe even reading file twice
    SFileInfo fileInfo;
    RootFileSystem::GetFileInfo( &fileInfo, correctFileName );
    s_texturesPool.MarkAsLoaded(PoolTextureWrapper(pTexture.GetPtr(), fileInfo.time, skipMipLevels, canBeVisualDegrade, poolId, sizeInFile),
                                correctFileName);
		render_TexturesCount.AddValue(1);
	}

	return pTexture;
}

void GetDefaultTexture(Texture2DRef &pTex) { pTex = GetDefaultTexture2D(); }
void GetDefaultTexture(TextureCubeRef &pTex) { pTex = TextureCubeRef(); }

struct CReloadTextures
{
  bool bModifiedOnly;

public :
  typedef pair< const nstl::string, PoolTextureWrapper > tex_info_type;

public :

 CReloadTextures(bool bModifiedOnly) : bModifiedOnly(bModifiedOnly) {}

 void operator()( tex_info_type &texInfo )
 {
   const bool needReload = UpdateTexInfo( texInfo );
   
   if ( bModifiedOnly && !needReload )
     return;
   
   if(RENDER_DISABLED)
     return;

   Texture2DRef   curTex2dRef;
   TextureCubeRef curTexCubeRef;
   if( curTex2dRef = dynamic_cast<Texture2D*>( texInfo.second.texPtr.GetPtr() ) )
   {
     Texture2DRef newTexRef;
     LoadTextureFromFileImpl( texInfo.first.c_str(), texInfo.second.skipMipLevels, newTexRef, texInfo.second.sizeInFile );
     
     curTex2dRef->SetTexture(*newTexRef);
   }
   else if ( curTexCubeRef = dynamic_cast<TextureCube*>( texInfo.second.texPtr.GetPtr() ) )
   {
     TextureCubeRef newTexRef;
     LoadTextureFromFileImpl( texInfo.first.c_str(), texInfo.second.skipMipLevels, newTexRef, texInfo.second.sizeInFile );
     
     curTexCubeRef->SetTexture(*newTexRef);
   }
	 
   systemLog( NLogg::LEVEL_MESSAGE ) << "Texture from " << texInfo.first.c_str() << " was reloaded " << endl;
 }

private :
  bool UpdateTexInfo( tex_info_type &texInfo )
  { 
    SFileInfo fileInfo;
    RootFileSystem::GetFileInfo( &fileInfo, texInfo.first );
    
    const UINT skipMipLevels = CalcSkipMipLevels( texInfo.second.canBeVisualDegrade );

    const bool needReload = 
      fileInfo.time.GetFullTime() != texInfo.second.modificationTime.GetFullTime() ||
      skipMipLevels != texInfo.second.skipMipLevels;
      
    texInfo.second.modificationTime = fileInfo.time;
    texInfo.second.skipMipLevels = skipMipLevels;
      
    return needReload;
  }
};

bool ReloadTexturesCmd( const char *name, const vector<wstring>& params )
{
  bool bModifiedOnly = true;
  if (params.size() == 1 && params[0] == L"all")
    bModifiedOnly = false;
  ReloadTextures( bModifiedOnly );
  return true;
}

bool DumpTexturePool( const char *name, const vector<wstring>& params )
{
  return s_texturesPool.Dump(name, params);
}

} // End of module internals

// Used in RenderResourceManager::FrameTick()
void TickTextureManager() { s_texturesPool.MoveMarkedInPool(); }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DefaultTextures defTextures;

DefaultTextures&    GetDefaultTextures()  { return defTextures; }
const Texture2DRef& GetDefaultTexture2D() { return defTextures.pTexture; }
const Texture2DRef& GetEmptyTexture2D() { return defTextures.pEmptyTexture; }
const Texture2DRef& GetWhiteTexture2D() { return defTextures.pWhiteTexture; }

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Texture2DRef CreateARGBTextureFromFileInMemory(const char* pData, int sizeInFile, UINT skipMipLevels)
{
  if( g_disableTextureLoads )
    return GetDefaultTextures().pTexture;

  IDirect3DTexture9* pD3DTexture = 0;
  HRESULT hResult = D3DXCreateTextureFromFileInMemoryEx(GetDevice(), pData, sizeInFile,
                                                        D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2, 0, 0, 
                                                        D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, D3DX_FILTER_TRIANGLE, 
                                                        D3DX_SKIP_DDS_MIP_LEVELS(skipMipLevels, D3DX_DEFAULT), 
                                                        0, 0, 0, &pD3DTexture);
  NI_DX_WARN(hResult, "CreateARGBTextureFromFileInMemory()");
  if( FAILED(hResult) )
    return Texture2DRef();

  return Create<Texture2D>(pD3DTexture);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Texture2DRef CreateTextureFromFileInMemory(const char* pData, int sizeInFile, UINT skipMipLevels)
{
  if( g_disableTextureLoads )
    return GetDefaultTextures().pTexture;

  IDirect3DTexture9* pD3DTexture = 0;
  HRESULT hResult = CreateTextureFromFileInMemoryImpl(&pD3DTexture, pData, sizeInFile, skipMipLevels);
  NI_DX_WARN(hResult, "CreateTextureFromFileInMemory()");
  if( FAILED(hResult) )
    return Texture2DRef();

  return Create<Texture2D>(pD3DTexture);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Texture2DRef CreateTexture2D(unsigned int width, unsigned int height, unsigned int level, PoolType poolType, ERenderFormat formatType)
{
	DWORD usage;
	D3DPOOL pool;
	GetD3DPoolAndUsagesParamaters( usage, pool, poolType );
	IDirect3DTexture9* pDirect3DTexture9 = 0;

  if(!RENDER_DISABLED) {
    HRESULT hr = GetDevice()->CreateTexture(width, height, level, usage, ConvertRenderFormat(formatType), pool, &pDirect3DTexture9, 0);
    NI_DX_THROW_CRITICAL( hr, "Couldn't create texture" );
  }
	return Create<Texture2D>( pDirect3DTexture9 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Texture2DRef CreateRenderTexture2D(unsigned int width, unsigned int height, ERenderFormat formatType, bool autoMipmaps /* = FALSE */)
{
  // this call may occur during lost device, it will be created ASAP
  D3DSURFACE_DESC desc = {ConvertRenderFormat(formatType), D3DRTYPE_SURFACE, D3DUSAGE_RENDERTARGET | (autoMipmaps ? D3DUSAGE_AUTOGENMIPMAP : 0),
    D3DPOOL_DEFAULT, D3DMULTISAMPLE_NONE, 0, width, height};
  Texture2DRef tex = Create<Texture2D>( desc );
  return tex;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureCubeRef CreateRenderCubeTexture(unsigned int edgeLen, ERenderFormat formatType)
{
  IDirect3DCubeTexture9* d3dCubetexture = 0;

  HRESULT res = GetDevice()->CreateCubeTexture(edgeLen, 1, D3DUSAGE_RENDERTARGET, ConvertRenderFormat(formatType), 
    D3DPOOL_DEFAULT, &d3dCubetexture, NULL);
  NI_VERIFY( res == D3D_OK, "cant create rendertexture!", return TextureCubeRef(); )

  return new TextureCube( d3dCubetexture ); // no safety in case of lost device [11/23/2009 smirnov]
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RenderSurfaceRef CreateDepthStencilSurface( unsigned int width, unsigned int height )
{
  // this call may occur during lost device, it will be created ASAP
  D3DSURFACE_DESC desc = {D3DFMT_D24S8, D3DRTYPE_SURFACE, D3DUSAGE_DEPTHSTENCIL, D3DPOOL_DEFAULT, D3DMULTISAMPLE_NONE, 0, width, height};
  return Create<RenderSurface>(desc);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Texture2DRef Create2DTextureFromArray2D( const CArray2D<Render::Color> & src )
{
  if(RENDER_DISABLED)
    return Texture2DRef();

	const int w = src.GetSizeX();
	const int h = src.GetSizeY();
	NI_VERIFY(w > 0 && h > 0, "Invalid CArray2D given for texture creation", return GetDefaultTexture2D(); );

	IDirect3DTexture9* pD3DTexture = 0;
  HRESULT hResult = GetDevice()->CreateTexture(w, h, 0, 0, D3DFMT_A8R8G8B8, D3DPOOL_MANAGED, &pD3DTexture, NULL);

	NI_VERIFY( SUCCEEDED( hResult ), NStr::StrFmt( "D3DXCreateTexture failed with result 0x%08X", hResult ), return GetDefaultTexture2D(); );

	D3DLOCKED_RECT rect;
	if ( SUCCEEDED( pD3DTexture->LockRect( 0, &rect, NULL, 0 ) ) )
	{
		char *p = (char *)rect.pBits;
		for ( int y = 0; y < h; ++y )
		{
			memcpy( p, &src[y][0], 4*w );
			p += rect.Pitch;
		}
		pD3DTexture->UnlockRect( 0 );
	}
	return Create<Texture2D>( pD3DTexture );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OnTextureDestruction(Texture *tex)
{
  //// remove from textures pool
  //TexturesPool::iterator it;
  //for (it = s_texturesPool.begin(); it != s_texturesPool.end(); ++it)
  //{
  //  if (it->second.texPtr == tex)
  //  {
  //    s_texturesPool.erase(it);
  //    render_TexturesCount.DecValue(1);
  //    break;
  //  }
  //}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Reset2DTextureFromFile( const nstl::string& filename )
{
  Load2DTextureFromFile( filename, true );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Texture2DRef Load2DTextureFromFile( const nstl::string& filename, bool bForceReload )
{
  return LoadTextureFromFile<Texture2D>( filename, 0, (bForceReload ? LTF_FORCE_RELOAD : LTF_NONE) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::TextureCubeRef LoadCubeTextureFromFileIntoPoolRef( const nstl::string& filename, bool canBeVisualDegrade, void * poolId )
{
  return LoadTextureFromFile<TextureCube>( filename, poolId, (canBeVisualDegrade ? LTF_CAN_BE_VISUAL_DEGRADE : LTF_NONE) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TextureCubeRef LoadCubeTextureFromFileRef( const nstl::string& filename )
{
  return LoadCubeTextureFromFileIntoPoolRef( filename, false, 0 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::Texture2DRef LoadTexture2DIntoPool( const NDb::Texture &txt, bool canBeVisualDegrade, void * poolId )
{
	if ( txt.textureFileName.size() > 0 )
    return LoadTextureFromFile<Texture2D>( txt.textureFileName, poolId, 
               (canBeVisualDegrade ? LTF_CAN_BE_VISUAL_DEGRADE : LTF_NONE) );
	else
		return GetWhiteTexture2D();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Texture2DRef LoadTexture2D( const NDb::Texture &txt )
{
  return LoadTexture2DIntoPool( txt, false, 0 );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnloadAllTextures()
{
  s_texturesPool.Clear();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReloadTextures( bool bModifiedOnly )
{
  s_texturesPool.ReloadTextures(bModifiedOnly);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnloadTexturePool( void * poolId )
{
  s_texturesPool.UnloadTexturePool(poolId);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShowMipmapsWithReload(bool show)
{
  if (g_showMipMap != show)
  {
    g_showMipMap = show;
    ReloadTextures(false);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ForAllTextures(TextureProc &p)
{
  s_texturesPool.ForAllTextures(p);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DefaultTextures::Init()
{
  if(RENDER_DISABLED)
    return;

	pEmptyTexture = Create<Texture2D>( (IDirect3DTexture9*)0 );

	// Load default texture
	pTexture = Load2DTextureFromFile( "Tech/Default/DefaultTexture.dds" );

	// Create white texture
	pWhiteTexture = CreateTexture2D( 1, 1, 1, Render::RENDER_POOL_MANAGED, FORMAT_A8R8G8B8 );
	LockedRect rect = pWhiteTexture->LockRect( 0,0,1,0,1, Render::LOCK_DEFAULT);
	*(uint*)rect.data = 0xFFFFFFFF;
	pWhiteTexture->UnlockRect(0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void DefaultTextures::Term()
{
  pWhiteTexture = 0;
  pTexture = 0;
  pEmptyTexture = 0;
}

//======================================================================================
// PoolMT implementation
//======================================================================================
void PoolMT::ForAllTextures(TextureProc &p)
{
  TexturesPool::iterator it;
  for (it = texturesPool.begin(); it != texturesPool.end(); ++it)
  {
    p(it->first, TextureRef(it->second.texPtr));
  }
}

bool PoolMT::Dump(const char *name, const vector<wstring>& params)
{
  typedef nstl::list<nstl::string> FileNames;
  typedef nstl::map<int, FileNames> SortMap;
  SortMap sortMap;

  {
    TexturesPool::const_iterator it = texturesPool.begin();
    TexturesPool::const_iterator last = texturesPool.end();

    for ( ; it != last; ++it )
    {
      sortMap[-it->second.sizeInFile].push_back( it->first );
    }
  }

  DebugTrace( "TEXTURE MANAGER DUMP");

  int countSize = 0;
  int countNumber = 0;

  {
    SortMap::iterator it = sortMap.begin();
    SortMap::iterator last = sortMap.end();

    for ( ; it != last; ++it )
    {
      FileNames::iterator itF = it->second.begin();
      FileNames::iterator lastF = it->second.end();

      for ( ; itF != lastF; ++itF )
      {
        countNumber++;
        countSize += abs(it->first);
        DebugTrace( "%8d %s", abs(it->first), *itF );
      }
    }
  }

  DebugTrace( "Total: %d bytes in %d textures", countSize, countNumber );

  return true;
}


void PoolMT::ReloadTextures( bool bModifiedOnly )
{
  SmartRenderer::NullThePointers();
  for_each( texturesPool.begin(), texturesPool.end(), CReloadTextures(bModifiedOnly) );
}

void PoolMT::UnloadTexturePool( void * poolId )
{
  for ( TexturesPool::iterator it = texturesPool.begin(); it != texturesPool.end(); )
  {
    TexturesPool::iterator curr = it++;
    curr->second.usedInPools.remove( poolId );
    if ( curr->second.usedInPools.empty() )
      texturesPool.erase( curr );
  }
}

} //namespace Render

//======================================================================================

REGISTER_DEV_CMD( reloadtextures, Render::ReloadTexturesCmd );
REGISTER_DEV_CMD( dump_textures, Render::DumpTexturePool );
