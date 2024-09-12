#pragma once

#include "PFAnimController.h"
#include "PFClientBaseUnit.h"
#include "PFFlagpole.h"

namespace NGameX
{

class PFClientFlagpole : public PFClientBaseUnit, public IAnimatedClientObject
{
  CLIENT_OBJECT_WORLD(PFClientFlagpole, NWorld::PFFlagpole)
public:
  PFClientFlagpole(PF_Core::WorldObjectRef pWO, const NDb::AdvMapObject &mapObject, NScene::IScene* pScene);

  void OnRaiseFlag( int _teamId );
  void OnStartRaiseFlag();
  void OnDropFlag();
  void OnAfterReset( bool isRaised, int _teamId );

  void Hide(bool hide);

protected:
  PFClientFlagpole() : teamId( 0 ) {}

  virtual void OnAttack( float attackTimeOffset, const CVec2& vTarget ) { NI_ALWAYS_ASSERT( "Invoke dummy method" ); }
  virtual void OnStartedFighting() { NI_ALWAYS_ASSERT("Invoke dummy method"); }
  virtual void OnFinishedFighting() { NI_ALWAYS_ASSERT("Invoke dummy method"); }
  virtual void OnAttackDispatchStarted() { NI_ALWAYS_ASSERT("Invoke dummy method"); }

  virtual void OnUseMagic(int id, NWorld::Target const& target, float timeOffset, NWorld::ELookKind lookAtTarget) { NI_ALWAYS_ASSERT("Invoke dummy method"); }
  virtual void OnUseAbility( const char* node, const char* marker,NWorld::Target const& target, float timeOffset, NWorld::ELookKind lookAtTarget, bool syncVisual )
    { NI_ALWAYS_ASSERT("Invoke dummy method"); }
  virtual void OnUnitDie() {}
  virtual void OnStunned( bool stunned )  { NI_ALWAYS_ASSERT("Invoke dummy method"); }
  virtual void OnFreeze( bool freezed )  { NI_ALWAYS_ASSERT("Invoke dummy method"); }

  virtual void OnBecameIdle() {};
  virtual void ForceIdle() {};

	virtual void SetSceneObject( const NDb::DBSceneObject* sceneObjectDesc );
	virtual void OnWorldObjectDie();


  virtual unsigned  GetCurrentStateId() const;
  virtual unsigned  GetNextStateId() const;
  virtual unsigned  GetStateIdByName(char const* name) const;
  virtual unsigned  GetNumNodes() const;
  virtual bool      SetAnimStateId(unsigned int nodeId);
  virtual bool      ReachStateMarker(char const* sMarker, float time, bool preferShortestPath = true, bool preferDefaultNextNode = false);
  virtual void      SetCinematicPause( bool pause ) {}

  virtual void Update( float timeDiff );
  virtual void UpdateMinimap() const;
  virtual void OnEffectAttach(PF_Core::BasicEffectAttached *pEffect);
private:
  static DiInt32 OnFlagRaised(  const DiAnGrCallbackParams& params );
  static DiInt32 OnFlagDropped( const DiAnGrCallbackParams& params );
  void OnRaised();
  NScene::AnimatedSceneComponent *pAnimatedRoot;
  DiAnimGraph                    *pAG;
  int teamId;
  CObj<PF_Core::BasicEffect>      pEffect;
  unsigned int idleNodeID;
  unsigned int startNodeID;
  unsigned int waitNodeID;
};

} // End of namespace NGameX