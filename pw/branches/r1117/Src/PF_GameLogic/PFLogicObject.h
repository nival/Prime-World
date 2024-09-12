#pragma once

#include "PFWorldObjectBase.h"
#include "../../Data/GameLogic/FormulaPars.h"
#include "DBUnit.h"
#include "System/StarForce/HiddenVars.h"

namespace NGameX
{
  class PFClientLogicObject;
  class PFClientSingleStateObject;
}

namespace NWorld
{
class PFWorld;
class PFBaseUnit;

//
class PFLogicObject : public PFWorldObjectBase, public IUnitFormulaPars
{
  typedef Protection::HiddenVar<CVec3, 1> TPosition;
public:
  seDECLARE_COBJRING(PFLogicObject, ringField,      LORing);

  PFLogicObject(PFWorld* pWorld, const CVec3 &pos, const NDb::GameObject* objectDesc);

  virtual bool            IsHero() const { return type == NDb::UNITTYPE_HEROFEMALE || type == NDb::UNITTYPE_HEROMALE; }
  virtual bool            IsTrueHero() const { return false; } // It is a Hero and not a clone, see PFBaseHero method
  bool                    IsCreep() const { return type == NDb::UNITTYPE_CREEP || type == NDb::UNITTYPE_SIEGECREEP || type == NDb::UNITTYPE_FACTIONCHAMPION; }
  NDb::EUnitType          GetUnitType() const { return type; }
	void                    SetUnitType(NDb::EUnitType t) { type = t; }
  int                     GetOppositeFactionFlags() const;
  int                     GetFactionMask( int flags ) const;
  NDb::EFaction           GetFaction() const { return faction; }
  NDb::EFaction           GetOppositeFaction() const;
  int                     GetPlayerId() const { return playerId; }
  const float             GetHealth() const { return health; }
  const bool              IsDead() const { return health < EPS_VALUE; }
  TPosition::TConstRef    GetPosition() const { return position; }
  void                    UpdateHiddenState( bool bVisiblility );
  int                     GetHiddenCounter() const { return hiddenCounter; } 
  virtual NDb::EFaction   GetWarfogFaction() const { return faction; }

  virtual bool            IsInRange( const CVec2& aimerPos, float range ) const;
  bool                    IsInRange( const PFLogicObject* pAimer, float range ) const { return IsInRange( pAimer->GetPosition().AsVec2D(), range ); }
  bool                    IsObjectInRange( const PFLogicObject* pTargetObject, float range ) const;
  bool                    IsPositionInRange( const CVec2& targetPos, float range ) const;

  CVec3                   GetClientPosition() const;
  CVec3                   GetVisualPosition3D() const;                     // will place on terrain
  CVec2                   GetPos() const { return position.AsVec2D(); }
  float                   GetObjectSize() const { return objectSize; }
  int                     GetObjectTileSize() const { return objectTileSize; }
  int                     GetObjectDynamicTileSize() const { return objectDynTileSize; }
  void                    SetObjectSize(float size) { objectSize = size; }
  void                    SetObjectTileSize(int tileSize) { objectTileSize = tileSize; }
  void                    SetObjectDynamicTileSize(int dynamicTileSize) { objectDynTileSize = dynamicTileSize; }
  void                    SetObjectSizes(float size, int tileSize, int dynamicTileSize);
  bool                    IsRounded() const { return isRounded; }
  int                     GetTeamId()const;

  virtual int             GetOriginalTeamId() const { return GetTeamId(); }
  virtual NDb::EFaction   GetOriginalFaction() const { return GetFaction(); }

  virtual bool            IsVisibleForEnemy( int ) const { return true; } /// Should return true if object is visible for enemy units
  virtual bool            IsVisibleForFaction( int ) const { return true; }
  virtual bool            CanObserveNature() const { return !IsDead(); }

  virtual void            ChangeFaction( NDb::EFaction newFaction );
  virtual void            OnDie();
  virtual void            OnDestroyContents();
  virtual void            UpdateNatureType();
  virtual void            UpdateDayNightState(const bool night);

  virtual bool            IsMounted() const { return false; }
  virtual bool            IsMount() const { return false; }
  virtual bool            IsVulnerable() const { return true; }
  virtual bool            IsFlying() const { return false; }

  virtual bool            IsRecommended( int stat ) const { return false; }

  virtual bool            CheckFlagType(NDb::EUnitFlagType/* type*/) const { return false; }

  virtual int GetNafta() const { return 0; }
  virtual int GetTotalNaftaEarned() const { return 0; }

  template<typename Predicate>
  static CVec3 GetFreePlaceForObject(CVec3 const& position, float objectSize, Predicate& pred);

  virtual bool            IsUsableBy( PFBaseUnit const* ) const { return false; }

  // for client purposes
  // TODO: better name
  virtual bool            IsVisibleForFactionInternal(const NDb::EFaction faction) const { return IsVisibleForFaction(faction); }

protected:
  // ~~ Initialize ~~
  struct InitData
  {
    int              playerId;
    NDb::EFaction    faction;
    NDb::EUnitType   type;
    NDb::GameObject const* pObjectDesc;
    explicit InitData() : playerId(-1), faction(NDb::FACTION_NEUTRAL), type(NDb::UNITTYPE_CREEP), pObjectDesc(NULL) {}
  };
  virtual void Initialize(InitData const& data);
  virtual void RegisterInAIWorld();

  // ~~ World Objects stuff ~~
  explicit PFLogicObject() {}
  WORLD_OBJECT_CLIENT(NGameX::PFClientLogicObject);
  OBJECT_BASIC_METHODS(PFLogicObject);

  // IUnitFormulaPars does not contain data and should not be serialized
protected:
  ZDATA_(PFWorldObjectBase);
  ZPARENT(IUnitFormulaPars)
  NDb::EUnitType  type;
  NDb::EFaction   faction;
  int             playerId;
  Protection::HiddenVar<float, 5>::T health;
  int             natureType;
  int             hiddenCounter;

  TPosition::T position;       // object position
private:
  //ZNOCRC
  float           objectSize;     // unit size, in meters (rounded up to tile size)
  int             objectTileSize; // unit size, in tiles
  int             objectDynTileSize; // unit size, in tiles
  //ZNOCRCEND
  bool            isRounded;      // whether moving unit use rounded mark on TileMap or not

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,(IUnitFormulaPars*)this); f.Add(3,&type); f.Add(4,&faction); f.Add(5,&playerId); f.Add(6,&health); f.Add(7,&natureType); f.Add(8,&hiddenCounter); f.Add(9,&position); f.Add(10,&objectSize); f.Add(11,&objectTileSize); f.Add(12,&objectDynTileSize); f.Add(13,&isRounded); return 0; }

public:
  // Unit parameters block
  virtual float GetLife()                  const { return health; }
  virtual float GetEnergy()                const { return 0.0f; }
  virtual float GetMaxLife()               const { return 0.0f; }
  virtual float GetMaxEnergy()             const { return 0.0f; }
  virtual float	GetRange()                 const { return 0.0f; }
  virtual float GetMoveSpeed()             const { return 0.0f; }
  virtual float GetAttackSpeed()           const { return 0.0f; }
	virtual float GetCritMult()              const { return 0.0f; }
  virtual float GetLifeRegen()             const { return 0.0f; }
  virtual float GetEnergyRegen()           const { return 0.0f; }
	virtual float GetLifeRegenAbs()          const { return 0.0f; }
	virtual float GetEnergyRegenAbs()        const { return 0.0f; }
  virtual float GetEvasion()               const { return 0.0f; }
  virtual float GetLifeDrain()             const { return 0.0f; }
  virtual float GetEnergyDrain()           const { return 0.0f; }
  virtual int   GetNativeDefenceIndex()    const { return 0; }
  virtual int   GetNativeAttackIndex()     const { return 0; }
  virtual int   GetDevPoints()             const { return 0; }
  virtual bool  GetFlag(unsigned int flag) const { return false; }
  virtual bool  GetOnBase()                const;
  virtual int   GetZZimaSex()              const { return 0; }
  virtual float GetDamageTaken(float dt)   const { return 0.0f; }
  virtual float GetDamageDealt(float dt)   const { return 0.0f; }

  virtual float GetDamageTakenEx(float dt, const unsigned mask, const IMiscFormulaPars* const pMisc)  const { return 0.0f; }
  virtual float GetDamageDealtEx(float dt, const unsigned mask, const IMiscFormulaPars* const pMisc)  const { return 0.0f; }

  //Base Stats
  virtual float GetBaseLife()                       const { return 0.0f; }
  virtual float GetBaseEnergy()                     const { return 0.0f; }
  virtual float GetCoreEnergy()                     const { return 0.0f; }
  virtual float GetBaseRange()                      const { return 0.0f; }
  virtual float GetBaseMoveSpeed()                  const { return 0.0f; }
  virtual float GetBaseAttackSpeed()                const { return 0.0f; }
  virtual float GetBaseCriticalChance()             const { return 0.0f; }
  virtual float GetBaseCriticalMultiplier()         const { return 0.0f; }
  virtual float GetBaseLifeDrain()                  const { return 0.0f; }
  virtual float GetBaseEnergyDrain()                const { return 0.0f; }
  virtual float GetBaseEvasion()                    const { return 0.0f; }
  virtual float GetBaseLifeRegeneration()           const { return 0.0f; }
  virtual float GetBaseLifeRegenerationAbsolute()   const { return 0.0f; }
  virtual float GetBaseEnergyRegeneration()         const { return 0.0f; }
  virtual float GetBaseEnergyRegenerationAbsolute() const { return 0.0f; }
  virtual float GetBaseVisibilityRange()            const { return 0.0f; }
  virtual float GetBaseStrength()                   const { return 0.0f; }
  virtual float GetBaseIntellect()                  const { return 0.0f; }
  virtual float GetBaseDexterity()                  const { return 0.0f; }
  virtual float GetBaseBaseAttack()                 const { return 0.0f; }
  virtual float GetBaseStamina()                    const { return 0.0f; }
  virtual float GetBaseWill()                       const { return 0.0f; }
  virtual float GetBaseNaftaMult()                  const { return 0.0f; }
  virtual float GetBaseNaftaSpecForKill()           const { return 0.0f; }
  virtual float GetBaseNaftaForKill()               const { return 0.0f; }
  virtual float GetBaseNaftaForAssist()             const { return 0.0f; }
  virtual float GetBaseTeamNaftaForKill()           const { return 0.0f; }
  virtual float GetBaseTeamNaftaForPresence()       const { return 0.0f; }
  virtual float GetBaseCritChanceBonus()            const { return 0.0f; }
  virtual float GetBaseEnergyDamageDecrease()       const { return 0.0f; }
  virtual float GetBaseMaterialDamageDecrease()     const { return 0.0f; }
  virtual float GetBaseMissChance()                 const { return 0.0f; }

  //Derivative Stats
  virtual float GetLifeRegenTotal()             const { return 0.0f; }
  virtual float GetEnergyRegenTotal()           const { return 0.0f; }
  virtual float GetDamageMin()                  const { return 0.0f; }
  virtual float GetDamageMax()                  const { return 0.0f; }
  virtual float GetDexterityDamageMult()        const { return 0.0f; }
  virtual float GetMoveSpeedMpS()               const { return 0.0f; }
  virtual float GetCritChance()                 const { return 0.0f; }
  virtual float GetAttacksPerSecond()           const { return 0.0f; }
  virtual float GetBodyDefence()                const { return 0.0f; }
  virtual float GetSpiritDefence()              const { return 0.0f; }
  virtual float GetPenetrationFromAttackSpeed() const { return 0.0f; }
  virtual float GetPenetrationFromDexterity()   const { return 0.0f; }
  virtual float GetPenetrationTotal()           const { return 0.0f; }

  //New RPG system
  virtual float GetStrength()               const { return 0.0f; }
  virtual float GetIntellect()              const { return 0.0f; }
  virtual float GetDexterity()              const { return 0.0f; }
  virtual float GetBaseAttack()             const { return 0.0f; }
  virtual float GetStamina()                const { return 0.0f; }
  virtual float GetWill()                   const { return 0.0f; }
  virtual float GetNaftaMult()              const { return 0.0f; }
  virtual int   GetNaftaSpecForKill()       const { return 0; }
  virtual int   GetNaftaForKill()           const { return 0; }
  virtual int   GetNaftaForAssist()         const { return 0; }
  virtual int   GetTeamNaftaForKill()       const { return 0; }
  virtual int   GetTeamNaftaForPresence()   const { return 0; }
  virtual int   GetNaftaLevel()             const { return 0; }
  virtual float GetCritChanceBonus()        const { return 0.0f; }
  virtual float GetEnergyDamageDecrease()   const { return 0.0f; }
  virtual float GetMaterialDamageDecrease() const { return 0.0f; }
  virtual float GetMissChance()             const { return 0.0f; }

  virtual IUnitFormulaPars const* GetObjectMaster()   const { return this; }
  virtual IUnitFormulaPars const* GetObjectTarget()   const { return NULL; }
  virtual IUnitFormulaPars const* GetObjectFavorite() const { return NULL; }

	// Misc information
  virtual float GetSummonCnt() const { return 0; }
  virtual bool  IsMoving() const { return false; }
  virtual float GetTimeStanding() const { return 10000.0f; }
  virtual int   GetTerrainType() const { return natureType; }
  virtual int   GetUnitKind() const { return type; }
  virtual bool  UnitCheck(UnitCheckID id) const;

  virtual bool  IsEvading() const { return false; }

  virtual int GetKillStreak() const { return 0; }
  virtual int GetDeathStreak() const { return 0; }
  virtual int GetAssistersCount() const { return 0; }
  virtual int GetSpecCount() const { return 0; }
  virtual int GetPresentTeamActiveMembers() const { return 0; }

  virtual bool  IsMale() const { NI_ALWAYS_ASSERT( "Invoke dummy method" ); return true; }
  virtual int GetEffectiveClassMask() const { return 0; }
  virtual int CountStatusesForDispel( const IUnitFormulaPars* pDispeller ) const  { return 0; }

  virtual int   GetFctn() const { return GetFaction(); }
  virtual int   GetOriginalFctn() const { return GetOriginalFaction(); }
	virtual int   GetWOID() const { return objectId; }

	virtual float GetVariable(const char *name)    const { return 0.0f; }
  virtual const IMiscFormulaPars* FindApplicator(   const char* name, const IMiscFormulaPars* pMisc, ApplicatorSearchType searchType ) const { return NULL; }
  virtual int                     CountApplicators( const char* name, const IMiscFormulaPars* pMisc, ApplicatorSearchType searchType ) const { return 0; }
  virtual IMiscFormulaPars const* GetAblt(AbilityID abilityId) const { return NULL; }
  virtual IMiscFormulaPars const* GetTalent(const char* id) const { return NULL; }
  virtual bool  HasTalentFromPack( const char* id ) const { return false; }
  virtual float GetForce( bool = false ) const { return 0; }
  virtual float GetHeroStatisticsValue( HeroStatisticsId heroStatId ) const { return 0; }
  virtual int GetHeroAchievementCount( const char* achievId ) const { return 0; }
  virtual bool IsSkinUsed( const char * skinId ) const { return false; }

};

template<typename Predicate>
CVec3 PFLogicObject::GetFreePlaceForObject(CVec3 const& position, float objectSize, Predicate& pred)
{
  // check center
  if ( pred(position.AsVec2D()) )
    return position;

#define OFFSET(delta) (static_cast<float>(delta) * objectSize)

  static const int maxOffset = 20;
  for (int offset = 1; offset <= maxOffset; offset++)
  {
    // check top and bottom lines
    for (int dx = -offset; dx <= offset; dx++)
    {
      {
        CVec3 checkPos(position.x + OFFSET(dx), position.y + OFFSET(offset), 0.0f); // top
        if ( pred(checkPos.AsVec2D()) )
          return checkPos;
      }
      {
        CVec3 checkPos(position.x + OFFSET(dx), position.y - OFFSET(offset), 0.0f); // bottom
        if ( pred(checkPos.AsVec2D()) )
          return checkPos;
      }
    }
    // check left and right lines (2 last points are already tested by loop above)
    for (int dy = -offset+1; dy <= offset-1; dy++)
    {
      {
        CVec3 checkPos(position.x + OFFSET(offset), position.y + OFFSET(dy), 0.0f); // top
        if ( pred(checkPos.AsVec2D()) )
          return checkPos;
      }
      {
        CVec3 checkPos(position.x - OFFSET(offset), position.y + OFFSET(dy), 0.0f); // bottom
        if ( pred(checkPos.AsVec2D()) )
          return checkPos;
      }
    }
  }

#undef OFFSET

  return position; // cannot place object!
}

class ILogicStatesMapObject
{
public:
  virtual void SetState( const string& newStateName ) = 0;
};

} //namespace NWorld
