#pragma once

#include "../System/Singleton4DLL.h"
#include "../Render/Texture.h"
#include "../Render/material.h"
#include "DBEffect.h"

namespace NScene
{
	class SceneObject;
}

namespace PF_Core
{

////////////////////////////////////////////////////////////////////////////////////////
class RecolorableTextureCache : public Render::DeviceLostHandler
{
public:
  void Reset();

  Render::Texture2DRef AcquireTexture(Render::HDRColor const& recolor);

  // From Render::DeviceLostHandler
  virtual void OnDeviceLost();
  virtual void OnDeviceReset();

protected:
  // one shouldn't try to create his own cache but rather acquire it from RecolorableTextureManager
  RecolorableTextureCache(const NDb::TextureRecolorable &tex);

  void FillTexture(Render::Texture2DRef const& tex, Render::HDRColor const& recolor);


  Render::Texture2DRef  baseTex;
  Render::Texture2DRef  maskTex;

  typedef map<Render::HDRColor, Render::Texture2DRef> TextureMap;
  TextureMap textures;

  Render::SamplerState  samplerState;
};

////////////////////////////////////////////////////////////////////////////////////////
class RecolorableTextureManager : public Singleton4DLL<RecolorableTextureManager>
{
public:
  RecolorableTextureManager() : bEnableRecolor(true) {}
  ~RecolorableTextureManager();

  RecolorableTextureCache *AcquireCache(const NDb::TextureRecolorable &tex);
  void ResetCache();
  
  bool IsRecolorEnabled() const { return bEnableRecolor; }
  void EnableRecolor(bool bEnable);

  void ForceDXTexRebuild();

protected:
  typedef hash_map<string, RecolorableTextureCache*> CacheListT;

  CacheListT  cache;
  bool        bEnableRecolor;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class RecolorableTexture : public Render::Texture2D
{
public:
  seDECLARE_RING_CLASS(RecolorableTexture, rtRingPart, RecolorableTexRing);

  ~RecolorableTexture();

  void Recolor(Render::HDRColor const& _recolor) { recolor = _recolor; ResetDXTexture(); }
  void ResetColor() { recolor  = pDBObj->baseRGB; ResetDXTexture(); }

  // From Render::DeviceLostHandler
  virtual void OnDeviceReset() { ResetDXTexture(); }

  void ResetDXTexture();
  
  //struct Proc : public NonCopyable
  //{
  //  virtual void operator() (RecolorableTexture &tex) = 0;
  //};

  template<class Proc>
  static void ForAll(Proc &proc)
  {
    RecolorableTexture *tex = rtRing.first();
    for (; tex != rtRing.last(); tex = tex->rtRingPart.next)
    {
      proc(*tex);
    }
  }

  static void AllowRecolor(bool _allow);
  static bool RecolorAllowed();

protected:
  explicit RecolorableTexture(const NDb::TextureRecolorable &tex);

  NDb::Ptr<NDb::TextureRecolorable>  pDBObj;
  RecolorableTextureCache *texCache;
  Render::HDRColor recolor;

  RecolorableTexRing::Part   rtRingPart;
  static RecolorableTexRing  rtRing;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::TextureRef LoadRecolorableTexture(const NDb::TextureRecolorable &tex);
Render::TextureRef LoadRecolorableTextureInPool(const NDb::TextureRecolorable &tex, bool canBeVisualDegrade, void * texturePoolId ); //Dummy one, 'texturePoolId' is unused

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void RecolorSceneObject(NScene::SceneObject &so, Render::HDRColor const& recolor);
void RecolorSceneComponent(NScene::SceneObject &so, const nstl::string &_componentID, Render::HDRColor const& recolor);
void ResetSceneObjectRecolor(NScene::SceneObject &so);

} //PF_Core
