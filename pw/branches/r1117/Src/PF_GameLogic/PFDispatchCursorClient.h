#pragma once
#include "../PF_Core/BasicEffect.h"
#include "PFDispatchCursor.h"
#include "PFClientObjectBase.h"
#include "VisibilityHelper.h"

namespace PF_Core
{
  class LightningEffect;
}

namespace NGameX
{

class PFDispatchCursorClient : public NWorld::PFClientObjectBase, public VisibilityHelper
{
  CLIENT_OBJECT_METHODS(0x8D85F280, PFDispatchCursorClient, NWorld::PFDispatchCursor)


public:
  explicit PFDispatchCursorClient() {}
  PFDispatchCursorClient(PF_Core::WorldObjectRef pWO, NScene::IScene *pScene);

  virtual void OnWorldObjectDie();

  virtual void Update(float timeDelta);

  virtual NScene::SceneObject *GetSceneObject() const;
  const CObj<PF_Core::BasicEffectStandalone> &GetEffect() const { return pEffect; }

private:
  bool GetStartPos( CVec3& result, Matrix43& matrix ) const;
  void UpdateCursor();

  CPtr<NScene::IScene> pScene;
  CObj<PF_Core::BasicEffectStandalone> pEffect;
  CObj<PF_Core::LightningEffect> pLinkEffect;
  CVec3 dest;

  // current client object position
  CVec3 currentPos;
  Matrix43 startMatrix;

  bool needSendCommandUpdateCursor;
  float updateCursorTime;
  bool aoeIsVisible;

  void Start();
  void RetrieveTargetCoords();
};

}