#pragma once

#include "../Scene/SceneObject.h"
#include "../Scene/CollisionHull.h"
#include "PFClientLogicObject.h"
#include "PFBaseUnit.h"

namespace NGameX
{

namespace EHappyState
{
  enum Type
  {
    Ready,
    Happy,
    Resting
  };
};

class PFClientBaseUnit : public PFClientSingleStateObject
{
	CLIENT_OBJECT_WORLD( PFClientBaseUnit, NWorld::PFBaseUnit )
public:
  int UiBarsScreenSize() const { return uiBarsScreenSize; }
  float UiBarsWorldSize() const { return uiBarsWorldSize; }
	
  virtual EHappyState::Type GetHappyState() const { return EHappyState::Resting; }
  virtual void              SetHappyState( EHappyState::Type _happyState ) { }

  virtual void Update( float timeDiff );
  virtual void UpdateMinimap() const;
   
	virtual void OnDamage(float health, float damage);
	
  virtual void OnAttack( float attackTimeOffset, const CVec2& vTarget )											      = 0;
  virtual void OnStartedFighting()                                                                = 0;
  virtual void OnFinishedFighting()                                                               = 0;
  virtual void OnAttackDispatchStarted()                                                          = 0;

  virtual void OnUseMagic(int id, NWorld::Target const& target, float timeOffset, NWorld::ELookKind lookAtTarget) = 0;
  virtual void OnUseAbility( const char* node, const char* marker,
    NWorld::Target const& target, float timeOffset, NWorld::ELookKind lookAtTarget, bool syncVisual )    = 0;
  virtual void OnUnitDie()                                                                        = 0;
  virtual void OnBecameIdle()                                                                     = 0;
  virtual void ForceIdle()                                                                        = 0;

  virtual void OnStunned( bool stunned )                                                          = 0;
  virtual void OnFreeze( bool freezed )                                                           = 0;

  virtual void OnUnsummon() { OnUnitDie(); }
	virtual void OnAddGold(const CPtr<NWorld::PFBaseUnit> & pSender, const float amount);

	void         OnMiss(CPtr<NWorld::PFBaseUnit> const &pTarget);
  virtual bool OnLevelUp(int level);

  virtual void OnHide(bool hide);

	virtual void RenderDebug();

  virtual void Recolor(const Render::HDRColor& recolor );
          void ResetColor();
  virtual void UpdateColor();
          const Render::HDRColor& GetRecolor() const { return recolor; }

  virtual void EnableById( string id, bool bEnable );
  virtual void ProcessExternalEvent( const char* externalEvent );

  void AcknowledgeAuraChange( bool isAlly, bool isEnabled );
  void OnSelfAuraChange(      bool isAlly, bool isEnabled );
  void SetSelfAuras( int allyAurasCount, int enemyAurasCount );

  const NDb::DBSceneObject* GetSceneObjectDesc();
  virtual void SetSceneObject( const NDb::DBSceneObject* sceneObjectDesc ) = 0;

protected:
	// @BVS@TODO: Remove this ctor when CObj/Cptr permits
	PFClientBaseUnit() {}
	PFClientBaseUnit( const PF_Core::WorldObjectRef &pWO, const CreatePars &cp, const NDb::GameObject* gameObject = 0 );

  void InitializeUIBars( NScene::IScene * scene);

  Render::HDRColor recolor;

  int   uiBarsScreenSize;
  float uiBarsWorldSize;

	int   allyAuraCount;
	int   enemyAuraCount;

  int   castingAllyAuraCount;
  int   castingEnemyAuraCount;

  CObj<PF_Core::BasicEffectAttached> pAuraEffect;
  CObj<PF_Core::BasicEffectAttached> pSelfAuraEffect;
};

}

