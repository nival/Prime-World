#pragma once

#include "PFClientBaseMovingUnit.h"
#include "PFAnimController.h"
#include "PF_Core/WorldObject.h"

namespace NDb
{
  struct AnimSet;
};


namespace NWorld
{
  class PFCreature;
};

namespace NGameX
{
  class PFClientCreature : public PFClientBaseMovingUnit, public PFAnimController, public NScene::ISceneObjectUpdateHook
  {
    CLIENT_OBJECT_WORLD( PFClientCreature, NWorld::PFCreature )
  public:
    enum ELifeState
    {
      Living,
      Dying,
      Perished,
      Corpse
    };

    struct CreatePars : public PFClientBaseMovingUnit::CreatePars
    {
			CreatePars(NDb::Ptr<NDb::DBSceneObject> const& sceneObject, NDb::AnimSet const* pAnimSet, NScene::IScene *pS, const nstl::string& nodeName, bool startIdleAnimation = false) 
        : PFClientBaseMovingUnit::CreatePars(sceneObject, pS, nodeName)
        , pAnimSet(pAnimSet), startIdleAnimation(startIdleAnimation)
      {}
      
      NDb::AnimSet const* pAnimSet;
      bool startIdleAnimation;
    };

		PFClientCreature(PF_Core::WorldObjectRef const& pWO, const CreatePars &cp);
    
    // animation graph external parameters
    void SetMoveSpeed( float speed );
    void SetAttackSpeed( float speed );
    void StartFallThrough( float fallingSpeed );
    void Resurrect();

    // current animation set functions
    float GetCurAnimSetSurfSpeed() const;
    void  SetCurAnimSetSurfSpeed( float speed );

    virtual void MultiplyAnimSpeed( float scale );

    void UpdateCurAnimSetSurfSpeedMultiplier();

    void OnEmote(NDb::EEmotion emotion);

    int  ReplaceAnimSet( NDb::Ptr<NDb::AnimSet> pSet );
    bool RollbackAnimSet( int setId );
    int  ReplaceAnimation( NDb::EAnimStates state, char const* name, char const* marker, bool upper, bool affectAllSets);
    bool RollbackAnimation( NDb::EAnimStates state, int id, bool upper);

    void OnAbilityDispatchStarted( int id );
    void OnAbilityDispatchStarted( const char* marker );

    virtual void OnAttackDispatchStarted();
    virtual void OnUseAbility( const char* node, const char* marker, NWorld::Target const& target, float timeOffset, NWorld::ELookKind lookAtTarget, bool syncVisual );

    virtual void OnStunned( bool stunned );
    virtual void  OnFreeze( bool freezed );
    virtual float ForceAnimation( const string& anim );
    virtual void StopForcedAnimation();
    virtual void Summon();
		void  Idle(bool forced = false);
    virtual void OnTeleportTo( const CVec2& target );

    ELifeState  GetLifeState()  const { return lifeState;  }

    virtual EHappyState::Type GetHappyState() const { return happyState; }
    virtual void              SetHappyState( EHappyState::Type _happyState );

    virtual float GetTimeDead() const { return deadTime; }

		virtual void SetSceneObject( const NDb::DBSceneObject* sceneObjectDesc );
		void CreateStandaloneEffect();
    virtual bool IsInAttackNode() const;

    void RemoveGlowEffect();
    void AttachGlowEffect();
    virtual void  SetCinematicPause( bool pause );

    virtual void SetVisibility(bool bVisible);

    virtual bool IsPartiallyVisible() const;
  protected:
    PFClientCreature() : pAnimSet(0) {}

    // base moving unit events
    virtual void OnStartMoving(bool animate = true);
    virtual void OnStopped();
    virtual void OnMoveFailed( const CVec2& target );
    
    // base unit events
    virtual void OnAttack( float attackTimeOffset, const CVec2& vTarget );
    virtual void OnStartedFighting();
    virtual void OnFinishedFighting();

    virtual void OnUseMagic(int id, NWorld::Target const& target, float timeOffset, NWorld::ELookKind lookAtTarget);
    virtual void OnUnitDie();
    virtual void OnUnsummon();
    virtual void OnBecameIdle();

    virtual void OnFakeUnsummon();
    
    virtual void OnWorldObjectDie();
    virtual void OnDestroyContents();

    // IUpdateable
    virtual void Update( float timeDiff );

    bool Initialize( NScene::SceneObject* pSceneObject, NDb::AnimSet const* const* pAnimSets, unsigned const count, bool isDeath, unsigned const defaultSet, bool isHero ); 
    int  RegisterAnimSet( NDb::AnimSet const* pAnimSet );
    bool UnRegisterAnimSet( int id );
    bool ActivateAnimSet( int id );

    int  GetAnimSetId( int idx )const;

    void SetCommandQueueDepth(const float seconds);

    virtual bool OnSceneObjectBecomeVisible(NScene::SceneObject& sceneObject, float /*timeBeingInvisible*/);
    virtual void OnSceneObjectBecomeInvisible(NScene::SceneObject& sceneObject);

    virtual void ForceIdle();
  private:
    bool  isMoveAnimAllowed;
    bool  isMoveAnimated;
    float fallingTime;
    float fallingSpeed;
    float attackSpeed;
    float baseAttackSpeed;
    float deadTime;
    float moveSpeed;

    bool  isFighting;
    bool  isStunned;
    bool  needUpdateStun;
    
    ELifeState lifeState;

    EHappyState::Type happyState;
    float happyStateTimer;
    float happyStateRestingTimer;

    string forcedAnim;
    float forcedAnimRestartTimer;

    NDb::AnimSet const* pAnimSet;

    typedef StaticArray<pair<bool, bool>, NDb::KnownEnum<NDb::EEmotion>::sizeOf> EmoteSettings;
    typedef map<unsigned, EmoteSettings>                                         EmoParams; 

    enum EAttackMarker { None = 1, Main = 2, Predictable = 4, Special = 8};

    bool          doFirePending;
    bool          doFireAlreadyHappened; 
    EAttackMarker attackMarkerState;
    bool          predictMarkerPending; 
    bool          stopAttackAnimation;

    struct AnimSetParams
    {
      int       setId;
      int       prevSetId;
      
      float     surfSpeed;

      EmoParams emoParams;

      AnimSetParams() : setId(-1), prevSetId(-1), surfSpeed(0.0f) {}
    };

    typedef vector<AnimSetParams> TAnimSetParams;

    int            currentAnimSet;
    TAnimSetParams animSetParams;

    enum {AbilitiesCount = NDb::ANIMSTATES_ABILITY4 - NDb::ANIMSTATES_ABILITY1 + 1};
    StaticArray<bool, AbilitiesCount> abilityAnims; 
    StaticArray<bool, AbilitiesCount> upperAbilityAnims;
    NDb::EAnimStates                  deathAnimState;

    CObj<PF_Core::BasicEffect> pGlowEffect;

    bool  IsAbilityAnimPlaying() const;

    // Animation callbacks
    void  OnDeathAnimFinished();
    void  OnActionAnimFinished(AnimEventParams const& event);
    void  OnDoFireHappened();

    void  Attack(float timeOffset);

    void  OnDispatchStarted( NDb::EAnimStates state );
    void  OnDispatchStarted( const char* marker );

    void  PredictAttackMarker( int const allowedState = None );
    float GetAttackDuration() const;
  };


} // namespace NGameX
