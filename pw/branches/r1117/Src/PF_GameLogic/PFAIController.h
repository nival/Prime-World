#pragma once

#include "PFBaseAIController.h"
#include "PFLogicObject.h"

namespace NWorld
{

class PFShop;
class PFBaseMaleHero;
class PFTalent;

class AIBaseState;
class AIMoveToState;




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
enum EHealPhase
{
  HEAL_NONE,									// not healing now
  HEAL_RETREAT,								// retreating to base
  HEAL_HEALING								// standing near spawn position
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFAIController : public PFBaseAIController
{
  OBJECT_BASIC_METHODS(PFAIController);

public:
  PFAIController( PFBaseHero* unit, NCore::ITransceiver* pTransceiver, int line , int shift = 0);


  /////////////////////////////////////////////////////////////////////////////
  virtual void Step( float timeDelta );
  virtual void OnDie();
  virtual void OnRespawn();
  virtual int GetLineNumber() const { return lineNumber; }
  /////////////////////////////////////////////////////////////////////////////
  

  /////////////////////////////////////////////////////////////////////////////
  // inventory
  /////////////////////////////////////////////////////////////////////////////
  bool CanUseConsumable( int slot );

  // use consumable by default on self
  void UseConsumable( int slot, PFLogicObject* pTarget = NULL );
  void UseConsumable( int slot, const CVec2 &target );

  /////////////////////////////////////////////////////////////////////////////
  // higher level functions
  /////////////////////////////////////////////////////////////////////////////
  void WalkByRoad( bool backToBase );
  void GoToOwnBase() { WalkByRoad( true ); }
  void GoToEnemyBase();
  void GoToSpawnPos();
  void GoToShop();

  void Heal( bool respawned );
  void ProcessHealing();

  void RecoverMana();
  void RecoverHealth();

  void ActivateTalents();
  void UseTalents();

  void RaiseFlags();

  bool TryTeleport();

  void CheckWarFront( float timeDelta );
  CVec2 GetRoadPointByOffset( CVec2 const& pos, float offset );
  const vector<CVec2>& GetRoad() const { return road; }
  void EscapeFromTower();
  void AttackTower();
  void DoNotAttackTower();

protected:
  PFAIController() {}

  virtual void OnBecameIdle();

private:

  void SetLine( int num , int shift = 0 );

  // constant fields
  int											  lineNumber;
  int                       lineShift;
  vector<CVec2>						  road;

  // dynamic fields
  bool       isRespawned;
  EHealPhase healing;
  int        healingTick;
  float      warFrontTimeDist;

  TalentWrapper GetFirstTalent() { return TalentWrapper( GetHero(), 0, 0 ); }
  TalentWrapper GetLastTalent();

  // delays
  int useConsumableDelay;
  int activateTalentDelay;
  int useTalentDelay;
  int	usePotionDelay;
  int	blessDelay;
  int	mountDelay;

  // priestess fields
  vector<CPtr<PFBaseMaleHero>> blessers;
  vector<CPtr<PFBaseMaleHero>> mounters;

  int findFlagDelay;


public:
  struct TowerFinder
  {
    TowerFinder() : found(false), unit(0) {}
    bool operator()( PFLogicObject& _unit )
    {
      if ( _unit.GetUnitType() == NDb::UNITTYPE_TOWER || _unit.GetUnitType() == NDb::UNITTYPE_MAINBUILDING )
      {
        found = true;
        unit = &_unit;
        return true;
      }

      return false;
    }
    bool found;
    PFLogicObject* unit;
  };
};




} // namespace