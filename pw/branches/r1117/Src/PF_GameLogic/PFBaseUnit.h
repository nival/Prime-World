#ifndef PFBASEUNIT_H_INCLUDED
#define PFBASEUNIT_H_INCLUDED

#include "DBGameLogic.h"


#include "PFApplMod.h"
#include "PFBehaviour.h"
#include "PFDebug.h"
#include "PFDispatchStrike1.h"
#include "PFLogicObject.h"
#include "PFUnitAbilities.h"
#include "PFWorldObjectBase.h"
#include "Stat.hpp"


#include "../System/NameMap.h"
#include "LuaValueSettable.h"

extern bool bUseOldUpdateHistoryMethod;

namespace NDb
{
struct Unit;
struct UnitLogicParameters;
struct DerivativeStatsContainer;

// [AZ] Code for ASynch detection
template<>
inline
int Ptr<UnitTargetingParameters>::operator&( IBinSaver &saver )
{
  if ( saver.IsChecksum() )
  {
    int hashValue = IsEmpty() ? 0 : CastToDBResource(pResource)->GetDBID().GetHashKey();
    saver.Add( 3, &hashValue );

    if ( pResource )
    {
      saver.Add( 4, const_cast<float*>(&(pResource->unitTypeTableWeight)) );
      saver.Add( 5, const_cast<nstl::vector<float>*>(&(pResource->unitTargetWeight)) );
    }
  }
  else if ( saver.IsReading() )
  {
    string str;
    saver.Add( 3, &str );
    if ( str.empty() || str == "[db:empty]" )
      pResource = 0;
    else
    {
      SetPtr( NDb::Get<UnitTargetingParameters>( DBID( str ) ) );
      pActiveState = pResource;
    }
  }
  else
  {
    string str;
    if ( IsEmpty() )
      str = "[db:empty]";
    else
      str = GetFormattedDbId( CastToDBResource(pResource)->GetDBID() );

    saver.Add( 3, &str );
  }
  return 0;
}

}

namespace NDebug { class DebugObject; }
namespace NGameX 
{ 
  class PFClientBaseUnit; 
  class DerStatsNameMap;
}

namespace NWorld
{
class PFWorld;
class TileMap;
class PathMap;
struct ScreamTarget;
class ConstantsMap;
class PFBaseAttackData;
class PFAbilityInstance;
class PFDispatch;
class PFAbilityInstance;
class PFAbilityData;
class PFBaseApplicator;
class PFDispatchUniformLinearMove;
class PFTalent;
class PFNeutralCreepSpawner;
class PFGlyph;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ISummonAction
{
	virtual void operator()(PFBaseUnit * pUnit) = 0;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Damage description structure

struct PFBaseUnitDamageDesc
{
  PFBaseUnitDamageDesc() : delegatedDamage(0.0f), delegated(false), ignoreDefences(false), isDelegatedCriticalDamage(false) {}

  CPtr<PFBaseUnit> pSender;
  float            amount;
  int              damageType;
  int              flags;
  NDb::EDamageMode damageMode;
  bool             dontAttackBack;
  bool             delegated;
  bool             ignoreDefences;

  // Optional part
  const PFBaseApplicator* pDealerApplicator; // could be NULL

  // Used only for damage delegation
  mutable float delegatedDamage;
  mutable bool isDelegatedCriticalDamage;
};

struct DeathParamsInfo : ILuaValueSettable
{
  LUA_VALUE_SETTABLE_DECLARE

  DeathParamsInfo() : isAutoAttack(false), isMelee(false) {}

  bool isAutoAttack;
  bool isMelee;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DropCooldownParams : public NonCopyable
{
  DropCooldownParams( int flags, vector<NDb::Ptr<NDb::Ability>> const& talentsList = vector<NDb::Ptr<NDb::Ability>>(), NDb::EUseMode mode = NDb::USEMODE_LISTASRULE, PFAbilityData const* exceptAbility = 0, float cooldownReduction = 0.0f, bool reduceByPercent = false )
    : flags(flags), talentsList(talentsList), mode(mode), exceptAbility(exceptAbility), cooldownReduction(cooldownReduction), reduceByPercent(reduceByPercent) {}

  int flags;
  PFAbilityData const* exceptAbility;
  vector<NDb::Ptr<NDb::Ability>> const& talentsList;
  NDb::EUseMode mode;
  float cooldownReduction;
  bool reduceByPercent;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct UnsummonCriterion
{
  UnsummonCriterion( ExecutableFloatString const* criterionFormula_, PFBaseUnit const* pOwner_, IMiscFormulaPars const* pMisc_ )
    : criterionFormula(criterionFormula_)
    , pOwner(pOwner_)
    , pMisc(pMisc_)
  {}

  bool operator()( PFSummonBehaviour* pFirst, PFSummonBehaviour* pSecond );

  ExecutableFloatString const* criterionFormula;
  PFBaseUnit const* pOwner;
  IMiscFormulaPars const* pMisc;
};

_interface ISkinnable
{
  virtual bool SetSkin( const nstl::string& skinId ) { return false; }
  virtual const nstl::string&  GetSkinId() const {  static const string emptyString; return emptyString; }
  virtual const NDb::DbResource* GetSkin() const { return 0; }
};

struct NaftaAward
{
  float toKiller;
  float toAssister;
  float toSpectator;
  float toKillerTeam;
  float toPresentTeam;

  NaftaAward()
    : toKiller(0.f)
    , toAssister(0.f)
    , toSpectator(0.f)
    , toKillerTeam(0.f)
    , toPresentTeam(0.f)
  {

  }

  void Reset()
  {
    toKiller = 0.f;
    toAssister = 0.f;
    toSpectator = 0.f;
    toKillerTeam = 0.f;
    toPresentTeam = 0.f;
  }
};

struct MurderContext
{
  int assisterCount;
  int spectatorCount;
  int presentTeamActiveMembers;

  MurderContext()
    : assisterCount(0)
    , spectatorCount(0)
    , presentTeamActiveMembers(0)
  {

  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnit : public PFLogicObject, public PFFsm, public PFUnitAbilities, public NNameMap::Map, public ISkinnable
{
  WORLD_OBJECT_METHODS_WITH_CLIENT(0xE5CBCC0, PFBaseUnit, NGameX::PFClientBaseUnit);

	seDECLARE_CPTRRING(PFBaseUnit, attackersRingPart, AttackersRing);

	struct Variable
	{
		seDECLARE_RING(Variable, ringPart, Ring);

		ZDATA
		string             name;
		ValueWithModifiers var;
		ZEND int operator&( IBinSaver &f ) { f.Add(2,&name); f.Add(3,&var); return 0; }
	};

  typedef StaticArray< CObj<PFBehaviourGroup>, NDb::KnownEnum<NDb::SummonType>::sizeOf> SummonedUnits;

  typedef vector<CObj<PFAbilityInstance> > AbilityInstances; 

  typedef PFDispatchUniformLinearMove::UnitDispatchesRing UnitDispatchesRing;

  struct ConditionsResolver : NNameMap::Map
  {
    NAMEMAP_DECLARE;
    virtual NNameMap::Variant * ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly );
  public:
    void Init(const PFBaseUnit * _unit) {unit = _unit;}
  private:
    ConstPtr<PFBaseUnit> unit;
  };

  void UpdateExternalAbilities(float dtInSeconds);

  ConditionsResolver            condsResolver;
  CObj<NGameX::DerStatsNameMap> derStats;

  struct AttackSector
  {
    AttackSector() : attackers(0), direction(VNULL2) {}

    ZDATA
    int   attackers;
    CVec2 direction;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&attackers); f.Add(3,&direction); return 0; }
  };

  struct AttackData
  {
    AttackData() : pVictim(0), timePassed(0.0f), byAutoAttack(false), originalFaction(NDb::FACTION_NEUTRAL) {}

    void Clear() { pVictim = 0; }

    ZDATA
    CPtr<PFBaseUnit>  pVictim;
    float             timePassed;
    bool              byAutoAttack;
    NDb::EFaction     originalFaction;
    //ConstPtr<PFNeutralCreepSpawner> pSpawner;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&pVictim); f.Add(3,&timePassed); f.Add(4,&byAutoAttack); f.Add(5,&originalFaction); return 0; }
  };

  struct AttackDataHelper;
  friend AttackDataHelper;

  struct WarFogData
  {
    WarFogData();

    void Clear();

    ZDATA
    int     warFogObjectID;
    float   timeOut;
    float   visRadius;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&warFogObjectID); f.Add(3,&timeOut); f.Add(4,&visRadius); return 0; }
  };

  struct LastDamage
  {
    LastDamage() : timeOver(0.f) { }
    ZDATA
    NDb::DBID  abilityDbid;
    float timeOver;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&abilityDbid); f.Add(3,&timeOver); return 0; }
  };

  struct PriorityTarget
  {
    PriorityTarget() : timeOut (0.0f), objectId(-1) {}
    //PriorityTarget( const CPtr<PFBaseUnit>&  pTarget, int oId ) : pTarget(pTarget), timeOut (0.0f) {}
    PriorityTarget( const CPtr<PFBaseUnit>&  pTarget, int objectId, float timeOut ) : pTarget(pTarget), objectId(objectId), timeOut (timeOut) {}

    ZDATA
    CPtr<PFBaseUnit>  pTarget;
    float timeOut;
    int objectId;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&pTarget); f.Add(3,&timeOut); f.Add(4,&objectId); return 0; }

    bool operator==( const PriorityTarget& other ) const
    {
      return other.pTarget == pTarget && timeOut > 0.0f;
    }
  };
  typedef hash_map<int, PriorityTarget> TPriorityTargets;


  bool shouldRestoreStatusEffects;  // Not serialized, because it is used asynchronously on reconnect

  float shield;
  unsigned invalidAbilityTargetCounter;

  ZDATA_(PFLogicObject);
  ZPARENT(PFFsm);
  ZPARENT(PFUnitAbilities)
  ZNOPARENT(NNameMap::Map)
  ZNOPARENT(ISkinnable)
  ZONSERIALIZE

	nstl::list<CObj<PFBaseUnitEventListener> > eventListeners;
	mutable PFBaseApplicator::AppliedRing appliedApplicatorsHistory;
	mutable PFBaseApplicator::SentRing    sentApplicatorsHistory;
	PFBaseApplicator::NamedRing namedApplicators;

	mutable PFBaseApplicator::AppliedRing  appliedApplicators;
	mutable PFBaseApplicator::SentRing     sentApplicators;
  mutable PFApplStatus::ActiveStatusRing statusApplicators;

  TauntApplicatorManager tauntApplicators;

  AbilityInstances       abilityInstances;
	AttackersRing          attackersRing;

  vector<int>            forbidFlags;

	Variable::Ring         variablesRing;

  bool                   bStrongTarget;  // Target can not be auto-changed
  CPtr<PFBaseUnit>       pCurrentTarget; // Use GetCurrentTarget & AssignTarget!
  
  NDb::Ptr<NDb::DerivativeStatsContainer> derivativeStatsContainer;

  NDb::Ptr<NDb::UnitTargetingParameters> unitTargetingParams;

  // [AZ] Only for async detection
  NDb::Ptr<NDb::UnitTargetingParameters> baseUnitTargetingParams;

protected:
  NDb::Ptr<NDb::Unit>    dbUnitDesc;

  CObj<PFStatContainer>     stats;

  SummonedUnits          summonedUnits;

  Protection::HiddenVar<int, 13>::T     naftaLevel;
  float                                 timeSinceLevelUp;
  Protection::HiddenVar<float, 9>::T    energy;   // mana
  float                                 targetRevisionTime;
  CPtr<PFBaseUnit>                      pMaster;
  PFBaseBehaviour::UnitRing             behaviourList;
  vector<WarFogData>                    visUnitData;
  Protection::HiddenVar<bool, 31>::T    visibleForEnemy;
  Protection::HiddenVar<bool, 32>::T    visibleForNeutral;
  CObj<PFBaseAttackData>                pAttackAbility;
  Protection::HiddenVar<float, 10>::T   maxHealth;    // Updated every Step
  Protection::HiddenVar<float, 11>::T   maxEnergy;  // Updated every Step
  Protection::HiddenVar<float, 12>::T   gold; //current gold unit has or carry
  bool                                  canApplyDispatch;
  bool                                  isInCombat;

  TPriorityTargets   priorityTargets;
  vector<ScreamTarget>   screamTargets;

  bool shouldRestoreSceneObject;
  NDb::Ptr<NDb::DBSceneObject> pOriginalSceneObject;

  PFApplAbilityUpgrade::Ring abilitiesUpgrades;
  UnitDispatchesRing         inboundDispatches;

  StaticArray<map<string, int>, NDb::KnownEnum<NDb::SummonType>::sizeOf>   maxAllowedSummons; // !!!!!!!

  int                   attackSectorsCount;
  float                 attackSectorsAngle;
  vector<AttackSector>  attackSectors;

  CPtr<PFBaseUnit>      pAlphaSummon;

  AttackData            lastAttack;
  AttackData            lastHeroAttack;

  LastDamage lastDamage;

  vector<CObj<PFAbilityData> > externalPassiveAbilities;

  float sleepDelay;
  bool bSleep;
  bool isInTaunt;

public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFLogicObject*)this); f.Add(2,(PFFsm*)this); f.Add(3,(PFUnitAbilities*)this); OnSerialize( f ); f.Add(4,&eventListeners); f.Add(5,&appliedApplicatorsHistory); f.Add(6,&sentApplicatorsHistory); f.Add(7,&namedApplicators); f.Add(8,&appliedApplicators); f.Add(9,&sentApplicators); f.Add(10,&statusApplicators); f.Add(11,&tauntApplicators); f.Add(12,&abilityInstances); f.Add(13,&attackersRing); f.Add(14,&forbidFlags); f.Add(15,&variablesRing); f.Add(16,&bStrongTarget); f.Add(17,&pCurrentTarget); f.Add(18,&derivativeStatsContainer); f.Add(19,&unitTargetingParams); f.Add(20,&baseUnitTargetingParams); f.Add(21,&dbUnitDesc); f.Add(22,&stats); f.Add(23,&summonedUnits); f.Add(24,&naftaLevel); f.Add(25,&timeSinceLevelUp); f.Add(26,&energy); f.Add(27,&targetRevisionTime); f.Add(28,&pMaster); f.Add(29,&behaviourList); f.Add(30,&visUnitData); f.Add(31,&visibleForEnemy); f.Add(32,&visibleForNeutral); f.Add(33,&pAttackAbility); f.Add(34,&maxHealth); f.Add(35,&maxEnergy); f.Add(36,&gold); f.Add(37,&canApplyDispatch); f.Add(38,&isInCombat); f.Add(39,&priorityTargets); f.Add(40,&screamTargets); f.Add(41,&shouldRestoreSceneObject); f.Add(42,&pOriginalSceneObject); f.Add(43,&abilitiesUpgrades); f.Add(44,&inboundDispatches); f.Add(45,&maxAllowedSummons); f.Add(46,&attackSectorsCount); f.Add(47,&attackSectorsAngle); f.Add(48,&attackSectors); f.Add(49,&pAlphaSummon); f.Add(50,&lastAttack); f.Add(51,&lastHeroAttack); f.Add(52,&lastDamage); f.Add(53,&externalPassiveAbilities); f.Add(54,&sleepDelay); f.Add(55,&bSleep); f.Add(56,&isInTaunt); return 0; }

private:
  void RecryptImpl()
  {
    Recrypt( position );
    Recrypt( health );
    Recrypt( naftaLevel );
    Recrypt( energy );
    Recrypt( visibleForEnemy );
    Recrypt( visibleForNeutral );
    Recrypt( maxHealth );
    Recrypt( maxEnergy );
    Recrypt( gold );
  }

  void OnSerialize(IBinSaver& f);

  const MurderContext* murderContext;

public:
  typedef PFBaseUnitDamageDesc DamageDesc;

	explicit PFBaseUnit( PFWorld * _pWorld, const CVec3 & pos, const NDb::Unit * _dbUnitDesc );
  virtual void                    OnDestroyContents();
  const NDb::Unit *               DbUnitDesc() const { return dbUnitDesc; }

  void AddToPriorityTargets( const CPtr<PFBaseUnit>& pTarget );
  void UpdatePriorityTargets( float dt );
  bool IsPriorityTarget( const CPtr<PFBaseUnit>& pTarget ) const;

  virtual void Reset();
  virtual void OnAfterReset();
  void  CountAuraApplicators( int& allyAuracount, int& enemyAuracount );

  int   OccupyAttackSector(CPtr<PFBaseMovingUnit> const & attacker);
  void  ReleaseAttackSector(int sector);
  void  ClearAttackSectors();
  CVec2 GetAttackSectorDir(int sector) const;
  CVec2 GetAttackSectorOffset(CPtr<PFBaseMovingUnit> const & attacker, int sector) const;
  void  InitAttackSectors(int count);
  int   GetAttackSectorsCount() const { return attackSectorsCount; }
  int   GetAttackSectorOccupies(int sector) const;

  virtual bool IsSleep() const { return bSleep; }

  //////////////////////////////////////////////////////////////////////////
  // initialize
  void                            InitializeLifeEnergy();
  virtual void                    Initialize(InitData const& data);
  void                            InitBaseAttack();

  // PFWorldObjectBase override
  virtual bool                    Step(float dtInSeconds);
  virtual void                    OnDie();

  void                            WakeUp();

  float GetNormalLevelling() const;

  // damage/health/energy methods
  virtual float                   OnDamage(const DamageDesc &desc);
  virtual float                   OnBeforeDamage(const DamageDesc &desc) { return( desc.amount ); }

  virtual float                   OnHeal        (CPtr<PFBaseUnit> pSender, float amount, bool ignoreHealingMods = false);
  virtual float                   OnBurnEnergy  (CPtr<PFBaseUnit> pSender, float amount);
  virtual float                   OnHealEnergy  (CPtr<PFBaseUnit> pSender, float amount);
  virtual bool                    IsVulnerable() const { return false == CheckFlag(NDb::UNITFLAG_FORBIDTAKEDAMAGE); }
  void                            SetVulnerable(bool vulnerable);
	void                            CleanupAfterDeath( bool bFullCleanUp = false );
  bool                            IsInCombat() const { return isInCombat; }
  void                            OnEnterCombat() { isInCombat = true; }
  void                            OnLeaveCombat() { isInCombat = false; }

  bool                            IsInTaunt() const { return isInTaunt; }
  void                            OnBeginTaunt() { isInTaunt = true; }
  void                            OnEndTaunt() { isInTaunt = false; }

  virtual void OnGameFinished( const NDb::EFaction failedFaction );

  void CheckAppliedApplicators();
  void PlanToRestoreStatusEffects() { shouldRestoreStatusEffects = true; }
  void PlanToRestoreSceneObject( NDb::Ptr<NDb::DBSceneObject>& sObj );
  void RestoreSceneObject();

	PFBaseAttackData*								GetAttackAbility();
  const PFBaseAttackData*					GetAttackAbility() const;

  bool                            IsAttackFinished() const;

  virtual int                     GetTotalNaftaEarned() const { NI_ALWAYS_ASSERT("Invoke dummy method"); return 0; }

	//
	const int                       GetGold() const { return int(gold); }
	virtual void                    OnAddGold   (CPtr<PFBaseUnit> pSender, float gold, bool showGold = true);
	virtual float                   OnRemoveGold(CPtr<PFBaseUnit> pSender, float gold);

  virtual const nstl::string&     GetSkinId() const { return IsValid(pMaster) ? pMaster->GetSkinId() : ISkinnable::GetSkinId(); }

	virtual void                    ChangeFaction( NDb::EFaction newFaction );

  virtual PFTalent*               GetTalent( int level, int slot ) const { NI_ALWAYS_ASSERT( "Invoke dummy method" ); return 0; }
  virtual IMiscFormulaPars const* GetTalent( const char* id )      const { NI_ALWAYS_ASSERT( NI_STRFMT( "Invoke dummy method. Param is: \"%s\"", id ) ); return 0; }
  virtual PFTalent*               GetTalentById( const char* id )      const { NI_ALWAYS_ASSERT( NI_STRFMT( "Invoke dummy method. Param is: \"%s\"", id ) ); return 0; }
  virtual bool                    HasTalentFromPack( const char* id ) const { NI_ALWAYS_ASSERT( NI_STRFMT( "Invoke dummy method. Param is: \"%s\"", id ) ); return 0; }

  bool                            CanSee(const CVec3 &pos) const;
  bool                            CanSee(const CVec2 &pos) const;
  bool                            CanSee(const PFLogicObject &obj) const;
  bool                            CanSee(const SVector& tile) const;

  enum UnitDieFlags {
    UNITDIEFLAGS_NONE = 0,
    UNITDIEFLAGS_DONTPLAYDEATHANIMATION = 1 << 0,
    UNITDIEFLAGS_FORCEREMOVECORPSE      = 1 << 1 | UNITDIEFLAGS_DONTPLAYDEATHANIMATION,
    UNITDIEFLAGS_UNSUMMON               = 1 << 2,
    UNITDIEFLAGS_DEFERREDDEATH          = 1 << 3,
    UNITDIEFLAGS_FORBIDREWARDS          = 1 << 4,
  };

  void                            KillUnit(const CPtr<PFBaseUnit>& pKiller = NULL, int flags = UNITDIEFLAGS_NONE, PFBaseUnitDamageDesc const* pDamageDesc = 0 );
  virtual void                    OnUnitDie(CPtr<PFBaseUnit> pKiller, int flags = UNITDIEFLAGS_NONE, PFBaseUnitDamageDesc const* pDamageDesc = 0 );

  // dispatch
  virtual bool                    CanApplyDispatch() { return canApplyDispatch; }
  virtual bool                    OnDispatchApply(PFDispatch const &dispatch);
  virtual void                    OnMiss(CPtr<PFBaseUnit> const &pTarget);
  void                            EnableDispatch(bool enable = true) { canApplyDispatch = enable; }


  bool                            HasAtackAbility() const;
  NDb::EApplicatorDamageType      GetBaseAttackDamageType() const;

  NDb::EApplicatorDamageType      GetNativeDamageType() const;

  const NDb::UnitTargetingParameters& GetTargetingParams() const;
  const NDb::UnitTargetingParameters* GetTargetingParamsPtr() const;
  
  void OverrideTargetingParams( NDb::Ptr<NDb::UnitTargetingParameters> _unitTargetingParams ) { unitTargetingParams = _unitTargetingParams; }

  // description manipulators/accessors
 
  float                           GetTimeSinceLevelUp() const { return timeSinceLevelUp; }

  virtual const wstring &         GetDescription() const { return description; }


  virtual const NDb::Texture *    GetUiAvatarImage() const { return pImage; }

  virtual NDb::EMinimapIcons      GetMinimapIcon() const { return DbUnitDesc()->minimapIcon; }
  //virtual PFVisMap*               GetVisMap()       { return visMap; }
  //virtual PFVisMap const*         GetVisMap() const { return visMap; }
  bool                            IsPlacementVisible( int faction ) const;
  virtual bool                    IsVisibleForEnemy( int faction ) const; // check Warfog if faction specified
  virtual bool                    IsVisibleForFaction( int faction ) const;
  virtual bool                    IsVisibleForFactionInternal(const NDb::EFaction faction) const;
  virtual bool                    IsFlying() const { return CheckFlag(NDb::UNITFLAG_FLYING); }

  void                            SetHealth( float value ) { health = clamp(value, 1.0f, maxHealth); }
  void                            SetEnergy( float value ) { energy = clamp(value, 1.0f, maxEnergy); }
#ifndef _SHIPPING
  char const*                       GetDebugDescription() const { return debugDescription.c_str(); }
  CObj<NDebug::DebugObject> const   &GetDebugObject() const { return debugObject; }
  virtual CObj<NDebug::DebugObject> CreateDebugObject();
#endif

  // params/stats methods
  float                           GetVisibilityRange( ) const;
  float                           GetChaseRange( ) const;
  float                           GetTargetingRange( ) const;
  float                           GetAttackRange( ) const;
  float                           GetScreamRange( ) const;
  float                           GetAggroRange( ) const;

  float                           GetHealthPercent() const { return (EPS_VALUE < maxHealth) ? (health / maxHealth) : 0.0f; }
  float                           GetMaxHealth() const { return maxHealth; }
  StatValueWithModifiers*         GetStat( NDb::EStat const stat);
  StatValueWithModifiers const*   GetStat( NDb::EStat const stat) const;
  const float                     GetStatValue( NDb::EStat const stat ) const;
  const float                     GetStatValue( NDb::EDerivativeStat const stat ) const;
  const float                     GetUnmodifiedValue( NDb::EStat const stat ) const;
  PFStatContainer const*          GetStatContainer() const { return stats; }

  void                            CopyStatModifiersFrom(PFBaseUnit * sourceUnit, int provider = PF_Core::INVALID_OBJECT_ID);

  ValueWithModifiers*             GetVariableVWM( char const* name );
  Variable*                       SearchVariable( char const* name ) const;
  ValueWithModifiers*             SearchVariableVWM( char const* name ) const;
  float                           GetVariableValue( char const* name ) const;
  float                           ModifyByVariable( char const* name, float value ) const;

  // attack methods
  bool                            IsRequireDirectSightToAttack();
  bool                            CanAttackFlying() const;
  bool                            CanAttackTarget(PFBaseUnit const* pTarget, bool ignoreInvulnerability = false ) const;
  bool                            CanSelectTarget(PFBaseUnit const* pTarget, bool mustSeeTarget) const;
  void                            AutoTarget( float dt );
  CPtr<PFBaseUnit>                FindTarget(float fRange, bool checkScreams = false, int targetFlags = 0, bool checkForbid = true );
  void                            AssignTarget(const CPtr<PFBaseUnit> &pTarget, bool strongTarget = true); // Do not auto-change target if strongTarget==true
  void                            DropTarget();
  void                            ClearScreamTargets();
  virtual void                    OnTargetAssigned() {}
  virtual void                    OnTargetDropped()  {}

  CPtr<PFBaseUnit>                GetCurrentTarget() const { return pCurrentTarget; }
  bool                            IsCurrentTargetStrong() { return bStrongTarget; }

  virtual bool                    IsReadyToAttack() const;
  bool                            DoAttack( bool allowAllies = false ); // Attack current target
  virtual void                    KilledTarget(const CPtr<PFBaseUnit> &pTarget) {} // Called when this kill someone
  virtual void                    OnTarget( const CPtr<PFBaseUnit>& pTarget, bool bStrongTarget = true ); // need to start attack this target (callback)
	void                            OnBeingTargeted( PFBaseUnit &attacker );
  void StopAttackingMe( bool ignorePursueDispatches = true );

  bool                            IsTargetInRange( const PFLogicObject* pTarget, float range ) const { return IsObjectInRange( pTarget, range ); }
  bool                            IsTargetInRange( const Target& target, float range ) const;

  bool                            IsTargetInAttackRange(const PFLogicObject *pTarget, bool useTargetInFormula = false) const;
  bool                            IsTargetInAttackRange(const Target &target, bool useTargetInFormula = false)  const;

  CObj<PFBaseAttackData>          ReplaceBaseAttack(CObj<PFBaseAttackData> const & pNewBaseAttack, bool applyPassivePart = true);
  void                            OnStartedFighting();
  void                            OnFinishedFighting();
  virtual void                    OnAttackDispatchStarted() const;

	void                            DropStates() { PFFsm::Cleanup(); }

  void Stacked( const bool stacked = true );

  CObj<PFAbilityInstance>         CreateAbilityInstance( PFAbilityData* pAbilityData, Target const& target );
  virtual CObj<PFAbilityInstance> UseAbility(int id, Target const &target);
  CObj<PFAbilityInstance>         UseExternalAbility( NDb::Ptr<NDb::Ability> const& pDesc, Target const& target );
  bool                            UseAbilityWithMicroAI();
  virtual CObj<IPFState>          InvokeAbility(int id, Target const &target);
  void                            RegisterExternalPassiveAbility( PFAbilityData* pAbilityData );
  bool                            UnregisterExternalPassiveAbility( PFAbilityData* pAbilityData );

  virtual void                    OnGlyphPickUp( const PFGlyph* pGlyph ) {}

  // Usable
  const NDb::Ability*             GetExternalAbility() const;
  virtual bool                    CanBeUsedBy( PFBaseUnit const* pUnit ) const;
  virtual bool                    IsUsableBy( PFBaseUnit const* pUnit ) const;
  virtual CObj<PFAbilityInstance> Use( PFBaseUnit* pHero );
  bool                            CheckUseLimitations( PFBaseUnit const* pUnit, NDb::CastLimitation const*& castLimitation ) const;
  virtual float                   GetUseRange( PFBaseUnit* pUser ) const;

	// Master
  CPtr<PFBaseUnit> const&         GetMasterUnit() const { return pMaster; }
  void                            SetMaster(CPtr<PFBaseUnit> const &pM) { pMaster = pM; }
  virtual bool                    UpdateClientColor();

	// Summons
  CObj<PFBehaviourGroup> const &  GetSummonedGroup(NDb::SummonType type) const { return summonedUnits[type]; }
  
  // for formulas
  virtual float            GetSummonCnt() const { return summonedUnits[NDb::SUMMONTYPE_PRIMARY]->GetSize(); }

  int GetSummonsCount( NDb::SummonType type, const string& summonGroupName ) const { return summonedUnits[type]->GetSize( summonGroupName ); }

  int GetMaxAllowedSummons( NDb::SummonType type, const string& summonGroupName ) const;
  void SetMaxAllowedSummons( NDb::SummonType type, const string& summonGroupName, int maxCount ) { maxAllowedSummons[type][summonGroupName] = maxCount; }

  int RemoveSummons( const int unsummonCount, const NDb::SummonType type, const string& summonGroupName, const NDb::Creature* pDBUnit = 0, const int maxCount = 0, UnsummonCriterion* pUnsummonCriterion = 0 );

	void ForAllSummons(ISummonAction &f, NDb::SummonType type);

	// Behaviour
	void AddBehaviourOnTop( PFBaseBehaviour* pBehaviour);
	void RemoveBehaviour( PFBaseBehaviour* pBehaviour);
	const PFBaseBehaviour* GetBehaviour() const { return !behaviourList.empty() ? behaviourList.first() : 0; }
  bool HasBehaviour() const          { return !behaviourList.empty(); }
  PFBaseBehaviour* Behaviour() const { return behaviourList.first();   }

  // Special for Night hero
  inline bool                     IsAlphaSummon() const { return IsValid(pMaster) && pMaster->GetAlphaSummon() == this; }
  CPtr<PFBaseUnit> const&         GetAlphaSummon() const { return pAlphaSummon; }
  void                            SetAlphaSummon( CPtr<PFBaseUnit> const& pAS ) { pAlphaSummon = pAS; }
  bool                            IsLikeHero() const; // NUM_TASK

  virtual bool                    IsAggressiveNeutralCreep() const { return false; }

  // magic stuff
  //virtual CObj<PFAbilityInstance> UseMagic(int id, Target const &target);
	const float                     GetMana() const { return energy; }
	float                           GetMaxMana() const { return maxEnergy; }
  const float                     GetManaPercent() const;
  bool                            HasMana() const;
  const bool                      ChangeHealth(float delta);
  const bool                      ChangeMana(float delta);
  void                            TakeMana(const float value);
  void                            TakeHealth(const float value);
  const bool                      CanUseAbility(int id, Target const &target) const;
	const bool                      CanUseAbility(int id) const;
  const bool                      CanUseAbility(CPtr<PFAbilityData> const &pAbility) const;
  virtual void                    OnAbilityDispatchStarted(PFAbilityData const* /*pData*/) const {}

  // used in PFApplInvisibility
  inline void                     UpdateInvisibility() { StepInvisibility(); }

  // applicators methods
  virtual bool                    OnApplicatorApply(CObj<PFBaseApplicator> pApplicator);
  void                            RegisterAppliedApplicator(CObj<PFBaseApplicator> applicator) {appliedApplicators.addLast(applicator);}
  void                            RegisterAppliedApplicatorToHistory(CObj<PFBaseApplicator> applicator) {appliedApplicatorsHistory.addLast(applicator);}
  void                            RegisterSentApplicator(CObj<PFBaseApplicator> applicator) {sentApplicators.addLast(applicator);}
  void                            RegisterSentApplicatorToHistory(CObj<PFBaseApplicator> applicator) {sentApplicatorsHistory.addLast(applicator);}
  void                            RegisterNamedApplicator(CPtr<PFBaseApplicator> applicator) { namedApplicators.addLast(applicator); }
  void                            RegisterStatusApplicator(CObj<PFApplStatus> const &applicator) { statusApplicators.addLast(applicator); }

  void                            RegisterTauntApplicator(CObj<PFApplTaunt> const &applicator) { tauntApplicators.AddLast(applicator); }

  TauntApplicatorManager& GetAppliedTaunts(){ return tauntApplicators;}

	// event listening
	void                            AddEventListener(CPtr<PFBaseUnitEventListener> pListener);
	void                            RemoveEventListener(CPtr<PFBaseUnitEventListener> pListener);
  template<class TPred>
  void                            RemoveEventListenerIf(TPred& pred)
  {
    nstl::list<CObj<PFBaseUnitEventListener> >::iterator findIter = find_if(eventListeners.begin(), eventListeners.end(), pred);
    while(findIter != eventListeners.end())
    {
      (*findIter)->SetAlive(false);
      if(++findIter != eventListeners.end())
        findIter = find_if(findIter, eventListeners.end(), pred);
    }
  }

	void                            EventHappened(const PFBaseUnitEvent &evt);
  const wstring&                  GetFactionName() const;

  virtual CPtr<PFBaseUnit>        GetMountedOn() const { return NULL; }

	PFVoxelMap*											GetVoxelMap() const;
	TileMap*												GetTileMap() const;
	const NDb::AILogicParameters&	  GetAIParameters() const;

  CObj<PFBaseAttackData> const &  GetAttackAbilityData() const { return pAttackAbility; }

  void                            SetLastAttackData(CPtr<PFBaseUnit> const & pVictim, const bool byAutoAttack, const NDb::EFaction originalFaction);
  void                            SetLastAttackDataEx(CPtr<PFBaseUnit> const & pVictim, const bool byAutoAttack, const bool byAggressiveDispatch, const NDb::EFaction originalFaction);
  AttackData const *              GetLastAttackData() const { return &lastAttack; }
  AttackData const *              GetLastHeroAttackData() const { return &lastHeroAttack; }
  void                            StepLastAttackData(float dtInSeconds);
  void                            RemoveLastAttackData();
  void                            RemoveLastHeroAttackData();
  inline bool                     IsAttackedUnitAlly( CPtr<PFBaseUnit> const & pTargetOfTarget, NDb::EFaction originalFaction ) const { return pTargetOfTarget->GetFaction() == faction || originalFaction == faction; }
  inline bool                     IsUnitAlly( CObj<PFBaseUnit> const & pUnit) const { return pUnit->GetFaction() == faction ; }

  void                            CancelChannelling();
  virtual void                    CancelAbilities();

  void                            CancelAllDispatchFromUnit( const PFBaseUnit* unit );

  void                            ModifyStatsByForce(const NDb::MapForceStatModifierApplication application = NDb::MAPFORCESTATMODIFIERAPPLICATION_ALL);
  virtual float                   GetManaCostModifier( bool = false ) const { return 1.0f; }

  virtual void                    SetHappy();

  // targeted dispatch register
  void RegisterLinearDispatch(PFDispatchUniformLinearMove *dispatch) { inboundDispatches.addLast(dispatch); }

  // For all applicators attached to base unit
  template <class F>
  void ForAllAppliedApplicators(F &f) const { PFBaseApplicator::ForallRing(appliedApplicators, f); }

  template <class F>
  void ForAllAppliedApplicatorsSafe(F &f) { PFBaseApplicator::ForallRingSafe(appliedApplicators, f); }

  // For all applicators attached to base unit
  template <class F>
  void ForAllStatusApplicators(F &f) const { PFApplStatus::ForallRing(statusApplicators, f); }

  // For all history applicators attached to base unit
  template <class F>
  void ForAllAppliedApplicatorsInHistory(F &f) const { PFBaseApplicator::ForallRing(appliedApplicatorsHistory, f); }

  // For all history applicators attached to base unit
  template <class F>
  void ForAllSentApplicators(F &f) const { PFBaseApplicator::ForallRing(sentApplicators, f); }

  // For all history applicators attached to base unit
  template <class F>
  void ForAllSentApplicatorsInHistory(F &f) const { PFBaseApplicator::ForallRing(sentApplicatorsHistory, f); }

  // For all history applicators attached to base unit
  template <class F, class C>
  struct TF
  {
    TF(PFWorld* world, F &f, C c, float time): pWorld(world), f(f), c(c), time(time) {}

    void operator()(CObj<PFBaseApplicator> &applicator)
    {
      float delta = pWorld->GetTimeElapsed() - applicator->GetMarkerTime();
      NI_ASSERT(delta >= 0.f, "Strange");
      if (c(delta, time))
      {
        f(applicator);
      }
    }

    F &f;
    C c;
    float time;
    PFWorld* pWorld;

  private:
    TF &operator = (TF const &); // calm down compiler
  };

  template<class C> struct CheckApplicatorTime
  {
    CheckApplicatorTime(PFWorld const* pWorld, C c, float time) : c(c), time(time), pWorld(pWorld) {}
    bool operator()(PFBaseApplicator const* appl)
    {
      float delta = pWorld->GetTimeElapsed() - appl->GetMarkerTime();
      NI_ASSERT(delta >= 0.f, "Strange");
      return c(delta, time);
    }
  private:
    C const& c;
    float time;
    PFWorld const* pWorld;
    CheckApplicatorTime& operator=(CheckApplicatorTime const&);
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class F>
  void ForAllAppliedApplicatorsInHistoryLess(F &f, float time)
  {
    CheckApplicatorTime<less> check(GetWorld(), less(), time);
    PFBaseApplicator::ForallRingSafeWhileBack(appliedApplicatorsHistory, f, check);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class F>
  void ForAllAppliedApplicatorsInHistoryLess(F &f, float time) const
  {
    CheckApplicatorTime<less> check(GetWorld(), less(), time);
    PFBaseApplicator::ForallRingSafeWhileBack(appliedApplicatorsHistory, f, check);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class F>
  void ForAllAppliedApplicatorsInHistoryGreater(F &f, float time)
  {
    CheckApplicatorTime<greater> check(GetWorld(), greater(), time);
    PFBaseApplicator::ForallRingSafeWhile(appliedApplicatorsHistory, f, check);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class F>
  void ForAllSentApplicatorsInHistoryLess(F &f, float time)
  {
    CheckApplicatorTime<less> check(GetWorld(), less(), time);
    PFBaseApplicator::ForallRingSafeWhileBack(sentApplicatorsHistory, f, check);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class F>
  void ForAllSentApplicatorsInHistoryLess(F &f, float time) const
  {
    CheckApplicatorTime<less> check(GetWorld(), less(), time);
    PFBaseApplicator::ForallRingSafeWhileBack(sentApplicatorsHistory, f, check);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  template <class F>
  void ForAllSentApplicatorsInHistoryGreater(F &f, float time)
  {
    CheckApplicatorTime<greater> check(GetWorld(), greater(), time);
    PFBaseApplicator::ForallRingSafeWhile(sentApplicatorsHistory, f, check);
  }

  void RemoveAppliedApplicators();
  void RemoveSentApplicators();

  void RemoveAppliedApplicatorsOnDeath();
  void RemoveSentApplicatorsOnDeath();

  void CleanupTauntApplicatorsStack();

  void CleanupHistoryApplicators();

  // Get ring of applicators in the case when ForAllApplicators isn't sufficient
  PFBaseApplicator::AppliedRing &GetAppliedApplicatorsRing() { return appliedApplicators; }
  PFBaseApplicator::AppliedRing const &GetAppliedApplicatorsRing() const { return appliedApplicators; }
  PFBaseApplicator::SentRing &GetSentApplicatorsRing() { return sentApplicators; }

  struct VectorCollector_
  {
    VectorCollector_(vector<CObj<PFBaseApplicator> > &applicators): applicators(applicators) {}
    void operator()(CObj<PFBaseApplicator> &applicator)
    {
      applicators.push_back(applicator);
    }
    vector<CObj<PFBaseApplicator> > &applicators;
  private:
    VectorCollector_ &operator = (VectorCollector_ const &); // calm down compiler
  };

  void GetAppliedApplicators(vector<CObj<PFBaseApplicator> > &applicators)
  {
    VectorCollector_ collector(applicators);
    ForAllAppliedApplicators(collector);
  }

  void GetSentApplicators(vector<CObj<PFBaseApplicator> > &applicators)
  {
    VectorCollector_ collector(applicators);
    ForAllSentApplicators(collector);
  }

  void                     AddFlag(unsigned int flag);
  void                     RemoveFlag(unsigned int flag);
  bool                     CheckFlag(unsigned int flag) const;
	virtual bool             CheckFlagType(NDb::EUnitFlagType type) const;
  virtual bool             GetFlag(unsigned int flag) const { return CheckFlag(flag); }
  void                     CopyFlagsFrom( const PFBaseUnit* pOther, bool addNotReplace );

  void                     Hide(bool hide);

  float                    GetTargetWeight(const CPtr<PFBaseUnit>& pTarget, const NDb::UnitTargetingParameters &unitPars, NWorld::PathMap* pPathMap = NULL) const;
  void                     DoScream( const CPtr<PFBaseUnit>& pTarget, ScreamTarget::ScreamType st );    // Scream to ally units to help me attack this target
  virtual void             OnScream( const CPtr<PFBaseUnit> pTarget, ScreamTarget::ScreamType st );

	virtual void             DumpInfo(NLogg::CChannelLogger &stream) const;
  void AddAbilityUpgradeApplicator( PFApplAbilityUpgrade *pAppl );
  void RemoveAbilityUpgradeApplicator( PFApplAbilityUpgrade *pAppl );
  PFApplAbilityUpgrade::Ring const& GetAbilityUpgradeApplicators() const;

  template<typename TPredicate, typename TFunctor>
  void ForAllAttackers(TPredicate const& p, TFunctor& f) const
  {
    for (ring::Range<AttackersRing> it(attackersRing); it; ++it)
      if( p( *it ) )
        f( *it );
  }

  template<typename TFunctor>
  void ForAllAttackersOnce(TFunctor& f) const
  {
    for (ring::Range<AttackersRing> it(attackersRing); it; ++it)
    {
      if( f( *it ) )
        return;
    }
  }

  template<typename TFunctor>
  void ForAllVariables(TFunctor& f) const
  {
    for (ring::Range<Variable::Ring> it(variablesRing); it; ++it)
      f( it->name, it->var );
  }

public:
  virtual void             DoLevelups(int count, float statsBonusBudget = 0.0f );
  void                     UpgradeStats(int count, float statsBonusBudget = 0.0f );
  void                     UpgradeHeroStats(const int count, const float statsBonusBudget, const float fraction);
  virtual void             OpenWarFog();
  virtual void             OpenWarFog(NDb::EFaction _faction, float timeout, float radius);
  virtual void             CloseWarFog(bool immediately = false);

  virtual const NDb::UnitDeathParameters* GetDeathParams() const;

  virtual void             ForceIdle();
  virtual void             Idle();
protected:
  explicit PFBaseUnit();
  virtual void             OnLevelUp();
  void                     RecalculateApplicators();

  virtual void             OnBecameIdle();
  

  void                     RestoreStatusEffects();

  virtual void             StepWarFog(float dtInSeconds);
  virtual void             StepInvisibility();

#ifndef _SHIPPING
  string                   debugDescription;
  CObj<NDebug::DebugObject>debugObject;
#endif

  wstring                  description;
  NDb::Ptr<NDb::Texture>   pImage;

  virtual void             RegisterInAIWorld();
  float                    GetAttackSpeedInternal() const;

  void                     AddStat( NDb::EStat stat, float value );

private:

  void                     StepApplicators(float dtInSeconds);
  void                     StepApplicatorsHistory();

  void                     ResetWarFog();

  void                     ApplyDamageReduction(float & damage, NDb::EApplicatorDamageType damageType, DamageDesc const& desc);
  void                     ApplyDrains( const DamageDesc &desc, float damage );

	void ApplyTopBehaviour();
	void RemoveBehaviour();

  bool                             IsStunned() const ;
  bool isDumpStates;
  // Unit parameters block
public:
  bool IsDumpStates() const { return isDumpStates; }
  void SetDumpStates( bool val ) { isDumpStates = val; }

  virtual float GetLife()      const { return health; }
  virtual float GetEnergy()    const { return energy; }
  virtual float GetMaxLife()   const { return maxHealth; }
  virtual float GetMaxEnergy() const { return maxEnergy; }

  virtual float GetRange()              const { return GetStatValue( NDb::STAT_RANGE ); }
  virtual float GetMoveSpeed()          const { return GetStatValue( NDb::STAT_MOVESPEED ); }
  virtual float GetAttackSpeed()        const { return GetStatValue( NDb::STAT_ATTACKSPEED ); }
  virtual float GetCritMult()           const { return GetStatValue( NDb::STAT_CRITICALMULTIPLIER ); }
  virtual float GetLifeRegen()          const { return GetStatValue( NDb::STAT_LIFEREGENERATION ); }
  virtual float GetEnergyRegen()        const { return GetStatValue( NDb::STAT_ENERGYREGENERATION ); }
  virtual float GetLifeRegenAbs()       const { return GetStatValue( NDb::STAT_LIFEREGENERATIONABSOLUTE ); }
  virtual float GetEnergyRegenAbs()     const { return GetStatValue( NDb::STAT_ENERGYREGENERATIONABSOLUTE ); }
  virtual float GetEvasion()            const { return GetStatValue( NDb::STAT_EVASION ); }
  virtual float GetLifeDrain()          const { return GetStatValue( NDb::STAT_LIFEDRAIN ); }
  virtual float GetEnergyDrain()        const { return GetStatValue( NDb::STAT_ENERGYDRAIN ); }

  virtual int   GetNativeDefenceIndex() const;
  virtual int   GetNativeAttackIndex()  const;

  //Base Stats
  virtual float GetBaseLife()                       const { return GetUnmodifiedValue( NDb::STAT_LIFE                       ); }
  virtual float GetCoreLife()                       const { return stats->GetCoreValue( NDb::STAT_LIFE ); }
  virtual float GetBaseEnergy()                     const { return GetUnmodifiedValue( NDb::STAT_ENERGY                     ); }
  virtual float GetCoreEnergy()                     const { return stats->GetCoreValue( NDb::STAT_ENERGY ); }
  virtual float GetBaseRange()                      const { return GetUnmodifiedValue( NDb::STAT_RANGE                      ); }
  virtual float GetBaseMoveSpeed()                  const { return GetUnmodifiedValue( NDb::STAT_MOVESPEED                  ); }
  virtual float GetBaseAttackSpeed()                const { return GetUnmodifiedValue( NDb::STAT_ATTACKSPEED                ); }
  virtual float GetBaseCriticalChance()             const { return GetUnmodifiedValue( NDb::STAT_CRITICALCHANCE             ); }
  virtual float GetBaseCriticalMultiplier()         const { return GetUnmodifiedValue( NDb::STAT_CRITICALMULTIPLIER         ); }
  virtual float GetBaseLifeDrain()                  const { return GetUnmodifiedValue( NDb::STAT_LIFEDRAIN                  ); }
  virtual float GetBaseEnergyDrain()                const { return GetUnmodifiedValue( NDb::STAT_ENERGYDRAIN                ); }
  virtual float GetBaseEvasion()                    const { return GetUnmodifiedValue( NDb::STAT_EVASION                    ); }
  virtual float GetBaseLifeRegeneration()           const { return GetUnmodifiedValue( NDb::STAT_LIFEREGENERATION           ); }
  virtual float GetBaseLifeRegenerationAbsolute()   const { return GetUnmodifiedValue( NDb::STAT_LIFEREGENERATIONABSOLUTE   ); }
  virtual float GetBaseEnergyRegeneration()         const { return GetUnmodifiedValue( NDb::STAT_ENERGYREGENERATION         ); }
  virtual float GetBaseEnergyRegenerationAbsolute() const { return GetUnmodifiedValue( NDb::STAT_ENERGYREGENERATIONABSOLUTE ); }
  virtual float GetBaseVisibilityRange()            const { return GetUnmodifiedValue( NDb::STAT_VISIBILITYRANGE            ); }
  virtual float GetBaseStrength()                   const { return GetUnmodifiedValue( NDb::STAT_STRENGTH                   ); }
  virtual float GetBaseIntellect()                  const { return GetUnmodifiedValue( NDb::STAT_INTELLECT                  ); }
  virtual float GetBaseDexterity()                  const { return GetUnmodifiedValue( NDb::STAT_DEXTERITY                  ); }
  virtual float GetBaseBaseAttack()                 const { return GetUnmodifiedValue( NDb::STAT_BASEATTACK                 ); }
  virtual float GetBaseStamina()                    const { return GetUnmodifiedValue( NDb::STAT_STAMINA                    ); }
  virtual float GetBaseWill()                       const { return GetUnmodifiedValue( NDb::STAT_WILL                       ); }
  virtual float GetBaseNaftaMult()                  const { return 0.0f; }
  virtual float GetBaseNaftaSpecForKill()           const { return GetUnmodifiedValue( NDb::STAT_NAFTASPECFORKILL           ); }
  virtual float GetBaseNaftaForKill()               const { return GetUnmodifiedValue( NDb::STAT_NAFTAFORKILL               ); }
  virtual float GetBaseNaftaForAssist()             const { return GetUnmodifiedValue( NDb::STAT_NAFTAFORASSIST             ); }
  virtual float GetBaseTeamNaftaForKill()           const { return GetUnmodifiedValue( NDb::STAT_TEAMNAFTAFORKILL           ); }
  virtual float GetBaseTeamNaftaForPresence()       const { return GetUnmodifiedValue( NDb::STAT_TEAMNAFTAFORPRESENCE       ); }
  virtual float GetBaseCritChanceBonus()            const { return GetUnmodifiedValue( NDb::STAT_CRITCHANCEBONUS            ); }
  virtual float GetBaseEnergyDamageDecrease()       const { return GetUnmodifiedValue( NDb::STAT_ENERGYDAMAGEDECREASE       ); }
  virtual float GetBaseMaterialDamageDecrease()     const { return GetUnmodifiedValue( NDb::STAT_MATERIALDAMAGEDECREASE     ); }
  virtual float GetBaseMissChance()                 const { return GetUnmodifiedValue( NDb::STAT_MISSCHANCE                 ); }

  //Derivative Stats
  virtual float GetLifeRegenTotal()             const { return GetStatValue( NDb::DERIVATIVESTAT_LIFEREGENTOTAL             ); }
  virtual float GetEnergyRegenTotal()           const { return GetStatValue( NDb::DERIVATIVESTAT_ENERGYREGENTOTAL           ); }
  virtual float GetDamageMin()                  const { return GetStatValue( NDb::DERIVATIVESTAT_DAMAGEMIN                  ); }
  virtual float GetDamageMax()                  const { return GetStatValue( NDb::DERIVATIVESTAT_DAMAGEMAX                  ); }
  virtual float GetDexterityDamageMult()        const { return GetStatValue( NDb::DERIVATIVESTAT_DEXTERITYDAMAGEMULT        ); }
  virtual float GetMoveSpeedMpS()               const { return GetStatValue( NDb::DERIVATIVESTAT_MOVESPEEDMPS               ); }
  virtual float GetCritChance()                 const { return GetStatValue( NDb::DERIVATIVESTAT_CRITCHANCE                 ); }
  virtual float GetAttacksPerSecond()           const { return GetStatValue( NDb::DERIVATIVESTAT_ATTACKSPERSECOND           ); }
  virtual float GetBodyDefence()                const { return GetStatValue( NDb::DERIVATIVESTAT_BODYDEFENCE                ); }
  virtual float GetSpiritDefence()              const { return GetStatValue( NDb::DERIVATIVESTAT_SPIRITDEFENCE              ); }
  virtual float GetPenetrationFromAttackSpeed() const { return GetStatValue( NDb::DERIVATIVESTAT_PENETRATIONFROMATTACKSPEED ); }
  virtual float GetPenetrationFromDexterity()   const { return GetStatValue( NDb::DERIVATIVESTAT_PENETRATIONFROMDEXTERITY   ); }
  virtual float GetPenetrationTotal()           const { return GetStatValue( NDb::DERIVATIVESTAT_PENETRATIONTOTAL           ); }

  //New RPG system
  virtual float GetStrength()               const { return GetStatValue( NDb::STAT_STRENGTH               ); }
  virtual float GetIntellect()              const { return GetStatValue( NDb::STAT_INTELLECT              ); }
  virtual float GetDexterity()              const { return GetStatValue( NDb::STAT_DEXTERITY              ); }
  virtual float GetBaseAttack()             const { return GetStatValue( NDb::STAT_BASEATTACK             ); }
  virtual float GetStamina()                const { return GetStatValue( NDb::STAT_STAMINA                ); }
  virtual float GetWill()                   const { return GetStatValue( NDb::STAT_WILL                   ); }
  virtual float GetNaftaMult()              const { return 0.0f; }
  virtual float GetCritChanceBonus()        const { return GetStatValue( NDb::STAT_CRITCHANCEBONUS        ); }
  virtual float GetEnergyDamageDecrease()   const { return GetStatValue( NDb::STAT_ENERGYDAMAGEDECREASE   ); }
  virtual float GetMaterialDamageDecrease() const { return GetStatValue( NDb::STAT_MATERIALDAMAGEDECREASE ); }
  virtual float GetMissChance()             const { return GetStatValue( NDb::STAT_MISSCHANCE             ); }

  virtual int GetNaftaSpecForKill()     const { return GetStatValue( NDb::STAT_NAFTASPECFORKILL       ); }
  virtual int GetNaftaForKill()         const { return GetStatValue( NDb::STAT_NAFTAFORKILL           ); }
  virtual int GetNaftaForAssist()       const { return GetStatValue( NDb::STAT_NAFTAFORASSIST         ); }
  virtual int GetTeamNaftaForKill()     const { return GetStatValue( NDb::STAT_TEAMNAFTAFORKILL       ); }
  virtual int GetTeamNaftaForPresence() const { return GetStatValue( NDb::STAT_TEAMNAFTAFORPRESENCE   ); }
  virtual int GetNaftaLevel()           const { return naftaLevel; }

  virtual IUnitFormulaPars const* GetObjectMaster() const;
  virtual IUnitFormulaPars const* GetObjectTarget() const;

  // Misc information
  virtual bool  IsMoving() const { return false; }
  virtual float GetTimeStanding() const { return 10000.0f; }
  virtual int   GetTerrainType() const { return natureType; }
  virtual int   GetUnitKind() const { return type; }
  virtual bool  IsEvading() const { return false; }

  virtual int   GetAssistersCount() const;
  virtual int   GetSpecCount() const;
  virtual int   GetPresentTeamActiveMembers() const;
  virtual bool  IsSkinUsed(const char * skinId) const { return false; }

	virtual float GetVariable(const char *name) const { return GetVariableValue(name); }

  virtual const IMiscFormulaPars* FindApplicator(   const char* name, const IMiscFormulaPars* pMisc, ApplicatorSearchType searchType ) const;
  virtual int                     CountApplicators( const char* name, const IMiscFormulaPars* pMisc, ApplicatorSearchType searchType ) const;
  virtual IMiscFormulaPars const* GetAblt(AbilityID abilityId) const;
  virtual const IMiscFormulaPars* FindApplicator(   const char* name, const IMiscFormulaPars* pMisc, ApplicatorSearchType searchType, int idx ) const;

  virtual float GetDamageTaken(float dt) const;
  virtual float GetDamageDealt(float dt) const;
  virtual float GetDamageTakenEx(float dt, const unsigned mask, const IMiscFormulaPars* const pMisc) const;
  virtual float GetDamageDealtEx(float dt, const unsigned mask, const IMiscFormulaPars* const pMisc) const;

  virtual int CountStatusesForDispel( const IUnitFormulaPars* pDispeller ) const;

  void SetNaftaLevel( int level );
  void SetMurderContext(const MurderContext* const context);

  float GetShield() const { return shield; }
  void SetShield(const float value) { shield = Max(value, 0.f); }

  void SetInvalidAbilityTarget(const bool invalid)
  {
    if (invalid)
    {
      ++invalidAbilityTargetCounter;
    }
    else
    {
      if (invalidAbilityTargetCounter == 0U)
        return;

      --invalidAbilityTargetCounter;
    }
  }

  bool IsInvalidAbilityTarget() const
  {
    return (invalidAbilityTargetCounter > 0U);
  }
private:
	friend class PFBaseUnitEventListener;
  NAMEMAP_DECLARE;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitDamageEvent : public PFBaseUnitEvent
{
public:
	PFBaseUnitDamageEvent(const PFBaseUnit::DamageDesc &desc, float damage2Deal_)
		: PFBaseUnitEvent(NDb::BASEUNITEVENT_DAMAGE), pDesc(&desc), damage2Deal(damage2Deal_) {}

  virtual bool IsEventHostileTo( PFBaseUnit const* ) const { return true; }

  virtual int PushArgsForScript( lua_State *L ) const;

	const PFBaseUnit::DamageDesc *pDesc;
	mutable float damage2Deal;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseUnitAssignTargetEvent : public PFBaseUnitEvent
{
public:
  PFBaseUnitAssignTargetEvent(const CPtr<PFBaseUnit> &pTarget, const CPtr<PFBaseUnit> &pLastTarget, bool strongTarget)
    : PFBaseUnitEvent(NDb::BASEUNITEVENT_ASSIGNTARGET), pTarget(pTarget), pLastTarget(pLastTarget), strongTarget(strongTarget)
  {}

  CPtr<PFBaseUnit> pTarget;
  CPtr<PFBaseUnit> pLastTarget;
  bool strongTarget;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int MakeSpellTargetFactionFlags(const PFBaseUnit &unit, NDb::ESpellTarget spellTarget);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// inlines
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

inline NDb::EApplicatorDamageType PFBaseUnit::GetNativeDamageType() const
{
  return dbUnitDesc->nativeAttack == NDb::DAMAGETYPE_MATERIAL ? NDb::APPLICATORDAMAGETYPE_MATERIAL : NDb::APPLICATORDAMAGETYPE_ENERGY;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Debug
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef _SHIPPING

class PFBaseUnitDebug : public NDebug::DebugObject
{
  OBJECT_METHODS(0xB757500 , PFBaseUnitDebug);
public:
  PFBaseUnitDebug(CPtr<PFBaseUnit> const &pUnit) : pOwner(pUnit) {}
  virtual bool IsObjectValid() const;
protected:
  PFBaseUnitDebug(){};
  virtual bool Process(Render::IDebugRender* pRender);

  CPtr<PFBaseUnit> pOwner;
};

#endif

} // namespace NWorld

#endif //PFBASEUNIT_H_INCLUDED
