#pragma once
#include "PFClientLogicObject.h"

namespace NGameX
{
class VisibilityMapClient;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFClientMultiStateObject : public PFClientLogicObject, public NScene::ISceneObjectUpdateHook
{
  CLIENT_OBJECT_METHODS(0xF643300, PFClientMultiStateObject, NWorld::PFLogicObject);
public:
  PFClientMultiStateObject(const PF_Core::WorldObjectRef &pWO, NScene::IScene* pScene, NDb::AdvMapObject const& advMapObject, int faction);
  virtual void  SetState(const int _natureType, const bool _night);
  virtual void  SetVisibility(bool bVisible);
	void DoFreeze();
  void Hide(bool hide);

  virtual void OnWorldObjectDie();

protected:
  static int SelectSceneObjectIndex(const int natureType, const bool night);

  explicit PFClientMultiStateObject() :isVisibleUnderWarfog(false) {}
  virtual void  OnSceneObjectUpdate(NScene::SceneObject &sceneObject, float timeDiff);
	virtual bool  OnSceneObjectBecomeVisible(class SceneObject &sceneObject, float timeBeingInvisible);
  virtual void  Update(float timeDelta);

  virtual bool NeedToUpdate() const;
  void SubscribeToUpdate();
	bool      active;

private:
  NDb::Ptr<NDb::MSOTransactions> dbTrans;
	bool isFreezed;
	VisibilityMapClient* visMapClient;
	CVec2 visPos;
  bool isHeightObject;
  bool isVisibleUnderWarfog;
};

} //namespace NGameX