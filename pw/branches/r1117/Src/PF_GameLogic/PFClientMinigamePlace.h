#pragma once


#include "PFClientBuilding.h"

namespace NWorld
{
  class PFMinigamePlace;
}

namespace NGameX
{

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFClientMinigamePlace : public PFBuilding
{
	CLIENT_OBJECT_METHODS( 0x9D635300, PFClientMinigamePlace, NWorld::PFMinigamePlace )
public:
	PFClientMinigamePlace() {}
	PFClientMinigamePlace(PF_Core::WorldObjectRef pWO, const CreatePars& cp, NScene::IScene* pScene, const NDb::GameObject* gameObject);

  virtual void SetVisibility( bool bVisible );

  void OnLocked();
  void OnUnlocked();
  void SetIdleEffect( NDb::Ptr<NDb::BasicEffectAttached> effect ) { pNdbEffect = effect; }

  virtual void Update( float timeDiff );
protected:
  virtual void OnUnitDie() {}
private:

  float currentOpacity;
  NDb::Ptr<NDb::BasicEffectAttached> pNdbEffect;
  CObj<PF_Core::BasicEffectAttached> pEffect;
  bool locked;
};

} //NGameX
