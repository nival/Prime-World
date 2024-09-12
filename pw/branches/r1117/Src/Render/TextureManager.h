#pragma once

#include "../System/2Darray.h"
#include "dxutils.h"
#include "renderformat.h"
#include "texture.h"

namespace NDb
{
	struct Texture;
	struct TextureRecolorable;
}

namespace Render
{

struct DefaultTextures
{
  void Init();
  void Term();

	Texture2DRef pTexture;
	Texture2DRef pEmptyTexture;
	Texture2DRef pWhiteTexture;
};

DefaultTextures& GetDefaultTextures();

const Texture2DRef& GetDefaultTexture2D();
const Texture2DRef& GetEmptyTexture2D();
const Texture2DRef& GetWhiteTexture2D();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Texture2DRef CreateARGBTextureFromFileInMemory(const char* pData, int sizeInFile, UINT skipMipLevels);
Texture2DRef CreateTextureFromFileInMemory(const char* pData, int sizeInFile, UINT skipMipLevels);
Texture2DRef Create2DTextureFromArray2D(const CArray2D<Render::Color> & src);
Texture2DRef CreateTexture2D(unsigned int width, unsigned int height, unsigned int level, PoolType poolType, ERenderFormat formatType );
Texture2DRef CreateRenderTexture2D(unsigned int width, unsigned int height, ERenderFormat formatType, bool autoMipmaps = FALSE );
TextureCubeRef CreateRenderCubeTexture(unsigned int edgeLen, ERenderFormat formatType);

Texture2DRef   Load2DTextureFromFile( const nstl::string& filename, bool bForceReload = false );
TextureCubeRef LoadCubeTextureFromFileIntoPoolRef( const nstl::string& filename, bool canBeVisualDegrade, void * poolId );
TextureCubeRef LoadCubeTextureFromFileRef( const nstl::string& filename );

Texture2DRef LoadTexture2DIntoPool( const NDb::Texture &txt, bool canBeVisualDegrade, void * poolId );
Texture2DRef    LoadTexture2D( const NDb::Texture &txt );

RenderSurfaceRef CreateDepthStencilSurface( unsigned int width, unsigned int height );

void OnTextureDestruction(Texture *tex);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Reset2DTextureFromFile( const nstl::string& filename );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnloadAllTextures();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ReloadTextures( bool bModifiedOnly );
void ShowMipmapsWithReload( bool show );

void UnloadTexturePool( void * poolId );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TextureProc : public NonCopyable
{
  virtual void operator()(string const &file, TextureRef tex) {}
};

void ForAllTextures(TextureProc &p);
}