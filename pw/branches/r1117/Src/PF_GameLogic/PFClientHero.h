#ifndef PFCLIENTHERO_H_INCLUDED
#define PFCLIENTHERO_H_INCLUDED

#include "PFClientCreature.h"
#include "PFClientObjectBase.h"
#include "PFMaleHero.h"
#include "../Scene/AttacherSceneComponent.h"
#include "../Sound/SoundUI.h"
#include "../Scene/SoundSceneComponent.h"

namespace PF_Core
{
  class BasicEffectAttached;
}

namespace NGameX
{
class AdventureCameraController;

struct AskData
{
  float minInterval;
  float cooldownTimer;
  NDb::EAskRecipient ask3dRecipient;
};


class PFBaseClientHero : public PFClientCreature
{
	CLIENT_OBJECT_METHODS( 0x2C59BC81, PFBaseClientHero, NWorld::PFBaseMaleHero )
public:
  struct CreatePars : public PFClientCreature::CreatePars
  {
    CreatePars(const NDb::BaseHero &unit, NDb::AnimSet const* pAnimSet, NScene::IScene *pS, NDb::EFaction _faction, const nstl::string& nodeName, const nstl::string& skinId)
    : PFClientCreature::CreatePars(SelectSceneObj(unit, _faction, skinId), pAnimSet, pS, nodeName)
    , faction(_faction)
    , pDesc(&unit)
    {}
    
    static NDb::Ptr<NDb::DBSceneObject> const& SelectSceneObj(const NDb::BaseHero &unit, NDb::EFaction faction, const nstl::string& skinId ) 
    {
      if (!skinId.empty())
      {
        vector<NDb::Ptr<NDb::HeroSkin>>::const_iterator it = unit.heroSkins.begin();
        for ( ; it != unit.heroSkins.end(); ++it )
        {
          if ((*it)->persistentId == skinId)
          {
            return (*it)->sceneObject;  
          }
        }  
      }

      NDb::ETeamID teamID = NDb::TEAMID_A;

      if (faction == NDb::FACTION_FREEZE)
      {
        teamID = NDb::TEAMID_A;
      }
      else if (faction == NDb::FACTION_BURN)
      {
        teamID = NDb::TEAMID_B;
      }
      else
      {
        NI_ALWAYS_ASSERT("Invalid faction");
      }

      if (!IsValid( unit.heroSceneObjects[teamID] ))
      {
        teamID = (teamID == NDb::TEAMID_A) ? NDb::TEAMID_B : NDb::TEAMID_A;
      }

      if (IsValid( unit.heroSceneObjects[teamID] ))
      {
        return unit.heroSceneObjects[teamID];
      }
      else
      {
        return unit.sceneObject;
      }
    }

    NDb::BaseHero const* pDesc;
    NDb::EFaction faction;
  };

	PFBaseClientHero(PF_Core::WorldObjectRef pWO, const CreatePars &cp);
  virtual ~PFBaseClientHero();

  // form PFClientObjectBase
  virtual void OnBecameActive(bool bActive);

  // From IUpdateable (temporary camera stuff (@IgorKaa))
  virtual void Update( float timeDiff );
  virtual void UpdateMinimap() const;
  virtual void UpdateAsks( float timeDiff );

	// From PFClientBaseUnit
  virtual void RenderDebug();

	virtual void OnDamage(float health, float damage);
  
	virtual void OnUnitDie();

  void ActivateSound( int soundScene );
	        void OnResurrect();

	virtual void OnKill( CPtr<NWorld::PFBaseUnit> const& pVictim, bool lastHit );
	virtual void OnAddGold( CPtr<NWorld::PFBaseUnit> const& pSender, const float award );

          void OnBecameLocal(bool isLocal);
          
          bool PlayAskSound(int id, NWorld::PFBaseHero const * pTarget = 0, int announcePriority = -1 );

  virtual bool OnLevelUp(int level);

  void OnMountSpecial( CPtr<NWorld::PFBaseMovingUnit> const& pMount );
  void OnUnmountSpecial();

  void UnsubscribeMinigameAfterReconnect();

  //void UpdateBattleSound( float time, bool force = false );

  void OnScrollReceived();
  virtual void  SetCinematicPause( bool pause );
protected:
  explicit PFBaseClientHero() {}

  void ProcessEffectsOnMount(bool mounted);
  virtual void OnEffectAttach(PF_Core::BasicEffectAttached *pEffect);

  void UpdateHeartbeating();

  // Asks manipulation functions
  void InitializeAsks(bool isLocal);
  void InitializeAsksData(const NDb::AskSounds* heroAsksSecondSate, EHeroState::Enum forHeroState);
  void Create2dAsks(NDb::AskSounds const* pHeroAsks, EHeroState::Enum forHeroState);
  void Create3dAsks(NDb::AskSounds const* pHeroAsks, EHeroState::Enum forHeroState, bool isLocal);
  void Attach3dAsks();
  void Detach3dAsks();
  void Destroy2dAsks();
  void Destroy3dAsks();

private:
  CObj< NScene::AttacherSceneComponent<PFClientLogicObjectAttacherPolicy> > pAttacher;
  CObj<PF_Core::BasicEffectAttached> pControlledEffect;
  
  float lastHealthPercent;

  // Ask sounds
  typedef vector<Strong<NSound::AskCommands>> TAsks;
  StaticArray<TAsks, EHeroState::_Count> soundsCommands;
  Strong<NSound::AskCommands> lastHitSound;

  // Ask sounds 3d
  typedef vector<CObj<NScene::SoundSceneComponent>> TAsks3d;
  StaticArray<TAsks3d, EHeroState::_Count> sounds3dCommands;

  typedef vector<AskData> TAsksData;
  StaticArray<TAsksData, EHeroState::_Count> soundsData;

  int minimapIconId;

  bool unsubscribeMinigameAfterReconnect;
  int unsubscribeMinigameWorldStep;

  void ResetControlledEffect( bool isLocal );
  virtual void SetSceneObject( const NDb::DBSceneObject* sceneObjectDesc );

  float timerBattleSound;

  float timerIdle;
  // Functor
  struct UnitBattleFunctor : public NonCopyable
  {
    CVec2         pos;
    float         range;
    NDb::EFaction faction;
    bool          battle;

    UnitBattleFunctor( const CVec2 &pos_, float range_, NDb::EFaction _faction )
      : pos(pos_), range(range_), faction(_faction), battle(false)
    {
    } 

    void operator()( NWorld::PFLogicObject& unit )
    {
      if( battle )
        return;

      if ( unit.IsInRange( pos, range ) ) 
      {
        if( unit.GetFaction() != NDb::FACTION_NEUTRAL )
        {
          if( unit.GetFaction() != faction )
          {
            battle = true;
            return;
          }
        }  
        else
        {
          if( const NWorld::PFBaseUnit* baseUnit = dynamic_cast<NWorld::PFBaseUnit*>(&unit) )
          {
            if( IsValid( baseUnit->GetCurrentTarget() ) ) // потому что нейтралы могут ещё и просто спать
            {
              battle = true;
              return;
            }
          }
        }
      }
    }

    bool InBattle() { return battle; }
  };
};

} //namespace NGameX

#endif //PFCLIENTHERO_H_INCLUDED
