#include "stdafx.h"

#include "../Scene/SceneObject.h"
#include "PFClientObjectBase.h"
#include "PFSimpleObject.h"

using namespace NScene;

namespace NGameX
{
class VisibilityMapClient;

class PFClientSimpleObject : public NWorld::PFClientObjectBase
{
	CLIENT_OBJECT_METHODS( 0x2C59BAC0, PFClientSimpleObject, NWorld::PFSimpleObject )
	
	bool isFreezed;
	VisibilityMapClient* visMapClient;
	CVec2 visPos;
  bool isVisibleUnderWarfog;

public:
	explicit PFClientSimpleObject() : pSceneObject(NULL), isFreezed(false), visMapClient(0), visPos(VNULL2), isVisibleUnderWarfog(false) {}

	PFClientSimpleObject(PF_Core::WorldObjectRef pWO, NDb::AdvMapObject const& dbObject, IScene* pScene);
  void Hide(bool hide);
	void DoFreeze();

protected:
	AutoPtr<SceneObject> pSceneObject;
};


AutoPtr<NScene::SceneObject> CreateSceneObject(NDb::AdvMapObject const* pObject, int id, 
                                               NScene::IScene* pAtScene);


} // namespace NGameX

