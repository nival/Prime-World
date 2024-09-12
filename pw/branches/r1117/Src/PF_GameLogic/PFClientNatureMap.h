#pragma once

/////////////////////////////////////////////////////////////////////////////////
// Includes
/////////////////////////////////////////////////////////////////////////////////

//#include "../PF_Core/ClientObject.h"
#include "PFClientObjectBase.h"
#include "PFWorldNatureMap.h"

//#include "../Scene/RenderableScene.h"
//#include "../Render/RenderInterface.h"
//#include "../Render/Renderer.h"
//#include "../Render/batch.h"
#include "../Render/texture.h"

namespace NGameX
{

class PFClientNatureMap : public NWorld::PFClientObjectBase
{
  CLIENT_OBJECT_METHODS(0x165C9B81, PFClientNatureMap, NWorld::PFWorldNatureMap)

public:
  PFClientNatureMap() {}
  explicit PFClientNatureMap(const PF_Core::WorldObjectRef &pWorldObject);
	~PFClientNatureMap() 
	{
		Unsubscribe();
	}

  Render::Texture2DRef GetTexture() /*const*/;

  // Inherited from NScene::IUpdateable
  virtual void Update(float dt);
};

} // namespace NGameX
