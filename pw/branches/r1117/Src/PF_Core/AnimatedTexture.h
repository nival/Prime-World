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
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class IUpdateableTexture
{
public:
  void Subscribe(); 
  void Unsubscribe();

  virtual void Update(float renderTime) = 0;

  static void ProceedUpdate(float renderTime);
  static void ForcedClear();

protected:
  IUpdateableTexture(bool bAutoAdd = true) 
  {
    if (bAutoAdd)
      Subscribe();
  }

  virtual ~IUpdateableTexture()
  {
    Unsubscribe();
  }

  seDECLARE_RING( IUpdateableTexture, part, Ring );

private:
  static Ring					s_objects;
  static IUpdateableTexture *s_pUpdateIterator;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class AnimatedTexture : public Render::Texture2D, public IUpdateableTexture
{
public:
  // From Render::DeviceLostHandler
  virtual void OnDeviceReset() { }

  // From IUpdateableTexture
  virtual void Update(float renderTime);

protected:
  explicit AnimatedTexture(const NDb::TextureAnimated &tex);

  void ResetDXTexture();

  NDb::Ptr<NDb::TextureAnimated>  pDBObj;
  vector<Render::Texture2DRef>  frames;
  int curFrame;
  float frameOffset;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Render::TextureRef LoadAnimatedTexture(const NDb::TextureAnimated &tex);
Render::TextureRef LoadAnimatedTextureIntoPool( const NDb::TextureAnimated &tex, bool canBeVisualDegrade, void * texturePoolId ); // texturePoolId is unused for now

}