#pragma once

#include "PFEaselPlayer.h"

namespace NGameX { class PFBaseClientHero; }

namespace SessionEventType{ enum EventType;}

namespace NWorld
{

class PFTalent;
_interface ITalentCalculator;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseMaleHero : public PFEaselPlayer
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0x2C61EC00, PFBaseMaleHero, NGameX::PFBaseClientHero )
    NAMEMAP_DECLARE();

  struct PersistentBuff
  {
    ZDATA
    NCore::PlayerBuffValue buffVal;
    bool applied;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&buffVal); f.Add(3,&applied); return 0; }
    PersistentBuff():applied(false){}
    PersistentBuff(const NCore::PlayerBuffValue& buff):applied(false), buffVal(buff){}
  };

public:
  typedef StaticArray<float, NDb::KnownEnum<NDb::EStat>::sizeOf> TPersistentStats;
  typedef StaticArray<PersistentBuff, NDb::KnownEnum<NDb::EStat>::sizeOf> TPersistentBuffs;

  PFBaseMaleHero(PFWorld* pWorld, const PFBaseHero::SpawnInfo &info, NDb::EFaction faction, NDb::EFaction _originalFaction);

  virtual void             OnDie();
 
  virtual void             DropCooldowns( DropCooldownParams const& dropCooldownParams );

  PFTalent *                GetPortal() const {return portal;}
  // Talents
  PFTalent*                 GetTalent(int level, int slot) const;
  const CObj<PFTalentsSet>& GetTalentsSet() const { return pTalents; }
  ETalentActivation::Enum   CanActivateTalent(int level, int slot) const;
  bool                      HasFreshTalentsToBuy() const;
  bool                      ActivateTalent(int level, int slot);
  void                      OnTalentActivated( const int level, const int slot, const float statsIncrementFraction );
  void                      LoadTalents(string const& strTalentsSetPath);

  virtual void              DoLevelups(int count, float statsBonusBudget = 0.0f);
  virtual void              DoHeroLevelups(const int count, const float statsBonusBudget, const float fraction);
  void                      ExecuteCommandUseConsumable( int slot, const Target& target, bool isPlayerCommand );
  virtual void              DoPetLogic();

  bool                      CanUseTalent(int level, int slot) const;
  bool                      CanUseTalent(PFTalent * talent) const;
  CObj<PFAbilityInstance>   UseTalent( int index, Target const& target );
  CObj<PFAbilityInstance>   UseTalent( int level, int slot, Target const& target ); //2nd interface
  CObj<PFAbilityInstance>   UseTalent( PFTalent* talent, Target const& target );

  virtual float GetManaCostModifier( bool altCost = false ) const;
  void                      RecalculateManaCostModifier();

  virtual int               GetDevPoints() const;
  int const &               GetDevPointsRef() const;
  virtual float             GetForce( bool countPersistentStats = false ) const;
  float                     GetTalentsAcquiredBudgetPercent() const;
  void                      DropTalentsCooldowns( DropCooldownParams const& dropCooldownParams ) const;
  void                      RestartGroupCooldowns( PFTalent const* pTalent );

  TPersistentStats const&   GetPersistentStats() const { return persistentStats; }
  float&                    GetCheatBudgetRef() { return cheatBudget; }
  // currently used for hero_force cheat only
  static void               FillPersistentStats( const NCore::PlayerInfo playerInfo, TPersistentStats& stats );
  static void               ModifyForceByStats( const PFBaseMaleHero::TPersistentStats& stats, const NDb::AILogicParameters* pAIParams, float& force );
  
  static void               FillPersistentBuffs( const NCore::PlayerInfo playerInfo, TPersistentBuffs& stats );

  int                       GetLastTalentUseStep() const { return lastTalentUseStep; }

  int                       GetEffectiveClassMask() const;
protected:
  explicit PFBaseMaleHero() {}
  
  virtual bool              Step(float dtInSeconds);
  virtual void              InitHero( NDb::BaseHero const* pDesc, bool initTalents, bool usePlayerInfoTalentSet, const NCore::PlayerInfo& playerInfo, bool initInventory );
  void                      ApplyPersistentStats( const NCore::PlayerInfo& playerInfo );
  void                      LoadInventory( const NWorld::PFResourcesCollection* collection );

  virtual IUnitFormulaPars const* GetObjectFavorite() const;


  ZDATA_(PFEaselPlayer);
  CObj<PFTalentsSet>  pTalents;
  float manaCostForceModifier;
  float lifeCostForceModifier;
  int lastTalentUseStep;
  CObj<PFTalent> portal;
  TPersistentStats persistentStats;
  nstl::vector<int> inventory;
  TPersistentBuffs persistentBuffs;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFEaselPlayer*)this); f.Add(2,&pTalents); f.Add(3,&manaCostForceModifier); f.Add(4,&lifeCostForceModifier); f.Add(5,&lastTalentUseStep); f.Add(6,&portal); f.Add(7,&persistentStats); f.Add(8,&inventory); f.Add(9,&persistentBuffs); return 0; }
private:
  
  float cheatBudget;
};

} // namespace NWorld
