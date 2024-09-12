#pragma once

#include "../PF_Core/ClientObject.h"
#include "PFClientObjectBase.h"
#include "PFAnimController.h"
#include "PFTower.h"
#include "PFBuildings.h"
#include "PFMainBuilding.h"

#include "../Scene/GeometryBuilders.h"
#include "../Scene/SceneObject.h"

#include "PFClientBaseUnit.h"

namespace NGameX
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBuilding : public PFClientBaseUnit, public IAnimatedClientObject
{
	CLIENT_OBJECT_METHODS( 0x2C5BE440, PFBuilding, NWorld::PFBuilding )
public:
  explicit PFBuilding() {}
	PFBuilding(PF_Core::WorldObjectRef pWO, const CreatePars& cp, NScene::IScene* pScene, const NDb::GameObject* gameObject);
  virtual ~PFBuilding();

  void OnHeal(float health, float delta);

  void MakeRuined();

  void Hide(bool hide);

  void ApplyHealthEffects();
  void ShowFragEffect();

  void              SetAnimState( string animStateName, bool skipAnimTransaction );
  virtual void      SetCinematicPause( bool pause ) {}

protected:
	virtual void  OnMoveTo( const CVec2& vPos ) {}
  virtual void  OnTeleportTo( const CVec2& vPos ) {}
  virtual void  OnStop() {}
  virtual void  OnBecameIdle() {}
  virtual void  ForceIdle() {}

  virtual void  SetVisibility(bool bVisible);
  
	virtual void SetSceneObject( const NDb::DBSceneObject* sceneObjectDesc );

  // damageable
  virtual void  OnDamage(float health,  float damage);
  virtual void  OnAttack( float attackTimeOffset, const CVec2& target ) {}
  virtual void  OnStartedFighting() {}
  virtual void  OnFinishedFighting() {}
  virtual void  OnAttackDispatchStarted() {}
  virtual void  OnStunned( bool stunned ) {}
  virtual void  OnFreeze( bool freezed ) {}

  virtual void  OnUseMagic(int id, NWorld::Target const& target, float timeOffset, NWorld::ELookKind lookAtTarget) {}
  virtual void  OnUseAbility( const char* node, const char* marker,
    NWorld::Target const& target, float timeOffset, NWorld::ELookKind lookAtTarget, bool syncVisual ) {}
  virtual void  OnUnitDie();
   
  // IUpdateable
  virtual void Update( float timeDiff );
  virtual void UpdateMinimap() const;

  // IAnimatedClientObject
  virtual unsigned  GetCurrentStateId() const;
  virtual unsigned  GetNextStateId() const;
  virtual unsigned  GetStateIdByName(char const* name) const;
  virtual unsigned  GetNumNodes() const;
  virtual bool      SetAnimStateId(unsigned int nodeId);
  virtual bool      ReachStateMarker(char const* sMarker, float time, bool preferShortestPath = true, bool preferDefaultNextNode = false);
  
  //
  bool IsVisibleOnMinimap() const;

  void SetHealthEffectsNumber( int newEffectsCount );

  void SwitchModel();
  void ShowOnDestructionEffect();
  int explCompsCount;       // общее количество эффектов горения
  int turnedOnExplEffects;  // количество включённых эффектов горения

  int fragLocatorsCount;
  NDb::Ptr<NDb::EffectBase> onDamageFragEffect;
  NDb::Ptr<NDb::BasicEffectStandalone> onDestructionEffect;
  
  enum State {
    State_Normal = 0, // обычное здание
    State_Dying,      // умершее, но ещё не пропавшее здание
    State_Died,       // умершее (пропала модель здания), но ещё не превратившееся в руины
    State_Ruin,       // руины
  };
  State state;
  float showRuinDelay;
  
  
  AutoPtr<NScene::SceneObject> pRuinSceneObject;
  NScene::Locator const* pRuinLocator;

  bool updateUnderWarfog;
private:
  DiAnimGraph *pAG;
};

class PFBattleBuilding : public PFBuilding
{
  CLIENT_OBJECT_METHODS( 0x2C6CEAC0, PFBattleBuilding, NWorld::PFBattleBuilding )
public:
  explicit PFBattleBuilding() {}
	PFBattleBuilding(PF_Core::WorldObjectRef pWO, const CreatePars& cp, NScene::IScene* pScene, const NDb::GameObject* gameObject);

  void         OnRotationChanged( float angle, bool forced = false );
  virtual void Update( float timeDiff );
  virtual void  SetVisibility( bool _bVisible );

protected:
    
  float                   baseRotation;
  float                   turretPitch;
  float                   turretRoll;
  float                   currentRotation;
  float                   targetRotation;
  NScene::SceneComponent* pTurret;
  NScene::SceneComponent* pBase;

  
  enum EAnimTarget
  {
    Base,
    Turret,
    Both
  };

  struct AnimatedData
  {
    DiAnimGraph* pAG;
    DiUInt32*    ids;
    int          statesCount;

    AnimatedData();
    ~AnimatedData();
    void Reset();
    void Init(DiAnimGraph* pAG, char const** stateNames, const int count);
  };

  AnimatedData           base;
  AnimatedData           turret;  

  struct AGCommand
  {
    enum EAGCommandType{ CT_Invalid, CT_SetState, CT_ReachMarker, CT_Nope } ;

    EAGCommandType type;
    EAnimTarget part;
    int targetNode; 
    nstl::string marker;
    float timeOffset;
    NScene::Time time;

    explicit AGCommand() 
      : type(CT_Invalid)
      , part(Both)
      , targetNode(DIANGR_NO_SUCH_ELEMENT)
      , marker("")
      , timeOffset(-1.0f)
      , time(-1.0f)
      {}
  };

  typedef nstl::vector<AGCommand> TCommandQueue;
  TCommandQueue commandQueue;

  bool SetAnimState( int target, EAnimTarget part = Both, float* nodeDuration = 0);
  bool ReachMarker( string const& marker, const float time, EAnimTarget part = Both);

  void RotateTurret(float angle);
  void AttackInternal(float attackTimeOffset, CVec2 const& target, char const* marker, int stateId);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFTower : public PFBattleBuilding
{
	CLIENT_OBJECT_METHODS( 0x2C5BE342, PFTower, NWorld::PFTower )
public:
	explicit PFTower() {}
	PFTower(PF_Core::WorldObjectRef pWO, const CreatePars& cp, NScene::IScene* pScene, const NDb::GameObject* gameObject);

  virtual void OnAttack(float attackTimeOffset, CVec2 const& target);

  void OnTargetAssigned();
  void OnTargetDropped();
  virtual void  OnUnitDie();

private:
  enum EAnimStates
  {
    Idle,
    Attack,
    EAnimStatesCount,
  };

  CObj<PF_Core::BasicEffectAttached> towerAttackEffect;

  void CreateTowerAttackEffect( NDb::EEffects effect, NScene::SceneObject* sceneObj );
};

class PFClientMainBuilding : public PFBattleBuilding
{
  CLIENT_OBJECT_METHODS( 0x2C6CC480, PFClientMainBuilding, NWorld::PFMainBuilding )

  float onDie;
  bool isDying;
	
public:

  explicit PFClientMainBuilding() {}
	PFClientMainBuilding(PF_Core::WorldObjectRef pWO, const CreatePars& cp, NScene::IScene* pScene, const NDb::GameObject* gameObject);

  void OnActivate(bool activate);
  void OnActivated(bool activated);
  
  virtual void OnAttack(float attackTimeOffset, CVec2 const& target);

  virtual void OnUnitDie();
  virtual void Update( float timeDiff );

private:

  enum EAnimStates
  {
    Idle,
    Activate,
    Deactivate,
    BattleIdle,
    AttackRange,
    AttackMelee,
    AttackAOE,
    Death,
    EAnimStatesCount,
  };

};

}
