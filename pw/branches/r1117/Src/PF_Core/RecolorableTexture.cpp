#include "stdafx.h"

#include "../Render/TextureManager.h"
#include "../Render/RenderComponent.h"
#include "../Render/MaterialSpec.h"
#include "../Render/smartrenderer.h"
#include "../Render/renderstates.h"
#include "../Render/renderer.h"
#include "../Render/ImmediateRenderer.h"
#include "../Scene/SceneObjectUtils.h"
#include "RecolorableTexture.h"

#include "../Render/NullRenderSignal.h"

SINGLETON4DLL_DEF(PF_Core::RecolorableTextureManager);

#ifndef _SHIPPING
static NDebug::PerformanceDebugVar s_texFill("RecolorFill", "", 0, 100, false);
#endif // _SHIPPING

namespace PF_Core
{

DECLARE_NULL_RENDER_FLAG

//#define _DEBUG_RECOLOR
#ifdef _DEBUG_RECOLOR
  static RecolorableTexture const * pRecolorTex = 0;
#endif

RecolorableTexture::RecolorableTexRing  RecolorableTexture::rtRing;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RecolorableTextureCache

RecolorableTextureCache::RecolorableTextureCache(const NDb::TextureRecolorable &tex)
  : Render::DeviceLostHandler(HANDLERPRIORITY_LOW)
{
  baseTex = Render::LoadTexture2D(*tex.main);
  ASSERT(baseTex);
  
  if( IsValid(tex.mask) )
  {
    maskTex = Render::LoadTexture2D(*tex.mask);
  }
  else
  {
    maskTex = Render::GetWhiteTexture2D();
  }

  samplerState.SetAddressU(NDb::TEXTUREADDRESSTYPE_CLAMP);
	samplerState.SetAddressV(NDb::TEXTUREADDRESSTYPE_CLAMP);
	samplerState.SetMinFilter(NDb::MINFILTERTYPE_POINT);
	samplerState.SetMagFilter(NDb::MAGFILTERTYPE_POINT);
	samplerState.SetMipFilter(NDb::MIPFILTERTYPE_NONE);
}

void RecolorableTextureCache::Reset()
{
  textures.clear();
}

Render::Texture2DRef RecolorableTextureCache::AcquireTexture(Render::HDRColor const& recolor)
{
  if( RecolorableTextureManager::Get() && !RecolorableTextureManager::Get()->IsRecolorEnabled()
      || recolor.A <= 0.0f ) // special case for designers/artists: use original texture
  {
    ASSERT(baseTex);
    return baseTex;
  }

  TextureMap::iterator it = textures.find(recolor);
  if ( it != textures.end() )
  {
    ASSERT(it->second);
    return it->second;
  }

  // texture not found in cache, create one
  Render::Texture2DRef tex = Render::CreateRenderTexture2D(baseTex->GetWidth(), baseTex->GetHeight(), Render::FORMAT_A8R8G8B8, true);
  ASSERT(tex);
  if( tex->GetDXTexture() )
  {
    textures[recolor] = tex;
    FillTexture(tex, recolor);
    return tex;
  }
  else
    return baseTex;
}

void RecolorableTextureCache::FillTexture(Render::Texture2DRef const& tex, Render::HDRColor const& recolor)
{
  using namespace Render;

#ifndef _SHIPPING
  static DWORD threadID = GetCurrentThreadId();
  ASSERT(GetCurrentThreadId() == threadID);
#endif // _SHIPPING

  if( IsValidPtr(tex) ) {
    Renderer &renderer = *GetRenderer();
    renderer.BeginScene();

    SmartRenderer::BindRenderTarget(tex);

    RenderStatesManager &rsManager = *GetStatesManager();
    rsManager.SetState( RenderState::NoBlendNoTest() );

    rsManager.SetStateDirect(D3DRS_ZENABLE, 0);
    rsManager.SetStateDirect(D3DRS_SEPARATEALPHABLENDENABLE, FALSE);

    rsManager.SetSampler(0, samplerState, baseTex);
    rsManager.SetSampler(1, samplerState, maskTex);

    renderer.SetPixelShaderConstantsHDRColor(PSHADER_LOCALCONST0, recolor);
    GetImmRenderer()->RenderScreenQuad(ImmRenderer::Params("RecolorTexture"));  

    renderer.EndScene();

    // update mipmaps
    tex->GenerateMipSubLevels();

  }
}

void RecolorableTextureCache::OnDeviceLost()
{
  // clear cache
  textures.clear();
}

void RecolorableTextureCache::OnDeviceReset()
{
  //// re-render all textures
  //TextureMap::iterator it;
  //for ( it = textures.begin(); it != textures.end(); ++it )
  //{
  //  FillTexture(it->second, it->first);
  //}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RecolorableTextureManager

RecolorableTextureManager::~RecolorableTextureManager()
{
  hash_map<string, RecolorableTextureCache*>::iterator it;

  for (it = cache.begin(); it != cache.end(); ++it)
  {
    delete it->second;
  }
}

RecolorableTextureCache *RecolorableTextureManager::AcquireCache(const NDb::TextureRecolorable &tex)
{
  if ( !IsValid(tex.main) || tex.main->textureFileName.empty() )
  {
    return NULL;
  }

  hash_map<string, RecolorableTextureCache*>::iterator it = cache.find( tex.main->textureFileName );

  if ( it != cache.end() )
  {
    return it->second;
  }

  // create new cache
  RecolorableTextureCache *rtc = new Render::DeviceLostWrapper<RecolorableTextureCache>(tex);
  cache[ tex.main->textureFileName ] = rtc;
  return rtc;
}

void RecolorableTextureManager::ResetCache()
{
  // clear cache
  CacheListT::iterator it;
  for (it = cache.begin(); it != cache.end(); ++it)
  {
    it->second->Reset();
  }

  ForceDXTexRebuild();
}

void RecolorableTextureManager::EnableRecolor(bool bEnable)
{
  if (bEnableRecolor != bEnable)
  {
    bEnableRecolor = bEnable;
    ForceDXTexRebuild();
  }
}

void RecolorableTextureManager::ForceDXTexRebuild()
{
  struct Proc //: public RecolorableTexture::Proc
  {
    void operator() (RecolorableTexture &tex)
    {
      tex.ResetDXTexture();
    }
  } f;

#ifndef _SHIPPING
  NDebug::PerformanceDebugVarGuard guard(s_texFill, true);
#endif // _SHIPPING
  RecolorableTexture::ForAll(f);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// RecolorableTexture

volatile bool s_allowRecolor = false;

void RecolorableTexture::AllowRecolor(bool _allow) { s_allowRecolor = _allow; }
bool RecolorableTexture::RecolorAllowed()          { return s_allowRecolor; }

RecolorableTexture::RecolorableTexture(const NDb::TextureRecolorable &tex)
  : Render::Texture2D( NULL, HANDLERPRIORITY_SUPER_LOW ) // we need to handle device lost AFTER cache
  , pDBObj(&tex), texCache()
{
  if(!RENDER_DISABLED) {
    texCache = RecolorableTextureManager::Get()->AcquireCache(tex);
    ResetColor();
  }
  rtRing.addLast(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
RecolorableTexture::~RecolorableTexture()
{
  rtRing.remove(this);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RecolorableTexture::ResetDXTexture()
{
#ifdef _DEBUG_RECOLOR
  if(pRecolorTex != this)
    pRecolorTex = pRecolorTex;
  else
    pRecolorTex = 0;
#endif

  if(s_allowRecolor && texCache)
      SetTexture( *(texCache->AcquireTexture(recolor)) );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::TextureRef LoadRecolorableTexture(const NDb::TextureRecolorable &tex)
{
	return new Render::DeviceLostWrapper<RecolorableTexture>( tex );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::TextureRef LoadRecolorableTextureInPool(const NDb::TextureRecolorable &tex, bool canBeVisualDegrade, void *texturePoolId )
{
  return LoadRecolorableTexture( tex );
}

struct RecolorProc : public Render::IMaterialProcessor
{
  Render::HDRColor recolor;

  RecolorProc(Render::HDRColor const& recolor) : recolor(recolor) {}

  virtual void operator()(Render::BaseMaterial &_material)
  {
    Render::BaseMaterial* material = _material.GetAlternativeMaterial() ? static_cast<Render::BaseMaterial*>(_material.GetAlternativeMaterial()) : &_material;

    if ( material->GetDiffuseMap() )
    {
      PF_Core::RecolorableTexture *t = dynamic_cast<PF_Core::RecolorableTexture *>( material->GetDiffuseMap()->GetTexture().GetPtr() );
      if (t)
      {
        material->MarkMaterialUpdated();
#ifdef _DEBUG_RECOLOR
          pRecolorTex = t;
#endif
        t->Recolor(recolor);
      }
    }
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RecolorSceneObject(NScene::SceneObject &so, Render::HDRColor const& recolor)
{
  RecolorProc proc(recolor);
	NScene::ForAllMaterials(so, proc);
}

void RecolorSceneComponent( NScene::SceneObject &so, const nstl::string &_componentID, Render::HDRColor const& recolor )
{
	RecolorProc proc(recolor);
	NScene::ForAllComponentMaterials(so, _componentID, proc);
}

void ResetSceneObjectRecolor(NScene::SceneObject &so)
{
	struct ResetColorProc : public Render::IMaterialProcessor
	{
		virtual void operator()(Render::BaseMaterial &material)
		{
			if (material.GetDiffuseMap())
			{
				PF_Core::RecolorableTexture *t = dynamic_cast<PF_Core::RecolorableTexture *>( material.GetDiffuseMap()->GetTexture().GetPtr() );
				if (t)
				{
          material.MarkMaterialUpdated();
#ifdef _DEBUG_RECOLOR
          pRecolorTex = t;
#endif
					t->ResetColor();
				}
			}
		}
	} proc;
	NScene::ForAllMaterials(so, proc);
}

}
