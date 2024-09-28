#pragma once
#include "./Vec2_Base.h"

#ifndef ZDATA
  #define ZDATA
#endif

#ifndef ZEND
  #define ZEND
#endif

// FORMULA_VERSION duplicated in DBExecString.cs in DBVersion attribute for class BaseExecutableString
#define FORMULA_VERSION ((unsigned char)21)
struct IBinSaver;

#define random(a,b)       pMisc->GetRandom( (a), (b) ) 
#define tal(a)        ( ( pFirst->GetTalent( a ) != 0 ) ? pFirst->GetTalent( a )->IsTalentBought() : false )
#define talconst(a,b) ( ( tal(a) )                      ? pFirst->GetTalent( a )->GetConstant( (b) , pFirst, pSecond ) : 0 )
#define talconstNoCheck(a,b) ( ( pFirst->GetTalent( a ) != 0 ) ? pFirst->GetTalent( a )->GetConstant( (b) , pFirst, pSecond ) : 0 )
#define stalconst(a,b,c) ( ( tal(a) ) ? pFirst->GetTalent( a )->GetConstant( (b) , pFirst, pSecond ) : (c) )
#define mastertal(a)        ( ( pFirst->GetObjectMaster() != pFirst && pFirst->GetObjectMaster()->GetTalent( a ) != 0 ) ? pFirst->GetObjectMaster()->GetTalent( a )->IsTalentBought() : false )
#define mastertalconst(a,b)        ( ( mastertal(a) ) ? pFirst->GetObjectMaster()->GetTalent( a )->GetConstant( (b) , pFirst, pSecond ) : 0 )
#define smastertalconst(a,b,c)        ( ( mastertal(a) ) ? pFirst->GetObjectMaster()->GetTalent( a )->GetConstant( (b) , pFirst, pSecond ) : (c) )
#define abilityScale(stat,s50,s160,...)    pMisc->GetAbilityScale( false, (stat), ABILITYSCALEMODE_STAT, (s50), (s160), __VA_ARGS__ )
#define abilityScaleLife(s50,s160,...)    pMisc->GetAbilityScale( false, pFirst->GetLife(), ABILITYSCALEMODE_LIFE, (s50), (s160), __VA_ARGS__  )
#define abilityScaleEnergy(s50,s160,...)    pMisc->GetAbilityScale( false, pFirst->GetEnergy(), ABILITYSCALEMODE_ENERGY, (s50), (s160), __VA_ARGS__  )
#define abilityScaleMaxLife(s50,s160,...)    pMisc->GetAbilityScale( false, pFirst->GetMaxLife(), ABILITYSCALEMODE_LIFE, (s50), (s160), __VA_ARGS__  )
#define abilityScaleMaxEnergy(s50,s160,...)    pMisc->GetAbilityScale( false, pFirst->GetMaxEnergy(), ABILITYSCALEMODE_ENERGY, (s50), (s160), __VA_ARGS__  )
#define abilityScaleCustomLife(stat, s50,s160,...)    pMisc->GetAbilityScale( false, (stat), ABILITYSCALEMODE_LIFE, (s50), (s160), __VA_ARGS__  )
#define abilityScaleCustomEnergy(stat, s50,s160,...)    pMisc->GetAbilityScale( false, (stat), ABILITYSCALEMODE_ENERGY, (s50), (s160), __VA_ARGS__  )
#define damageScale(stat,s50,s160,...)    pMisc->GetAbilityScale( true, (stat), ABILITYSCALEMODE_STAT, (s50), (s160), __VA_ARGS__  )
#define damageScaleCustomLife(stat,s50,s160,...)    pMisc->GetAbilityScale( true, (stat), ABILITYSCALEMODE_LIFE, (s50), (s160), __VA_ARGS__  )
#define damageScaleCustomEnergy(stat,s50,s160,...)    pMisc->GetAbilityScale( true, (stat), ABILITYSCALEMODE_ENERGY, (s50), (s160), __VA_ARGS__  )
#define nt(nativeValue,otherValue)      (pFirst->GetTerrainType() == pFirst->GetFctn() ? (nativeValue) : (otherValue))
#define nativeTerrain(nativeValue,otherValue)   nt(nativeValue,otherValue)
#define $ApplTarget               ( pMisc->GetObject("Target") )
#define $ParentAppl               ( pMisc->GetObjectParent() )
#define $ParentApplTarget         ( ($ParentAppl)->GetObject("Target") )
#define $ParentApplVariable(var)  ( ($ParentAppl)->GetVariable(var) )
#define $IsAppliedOnSelf          ( pFirst == pSecond )
#define smartRandom(outcomes,decr) pMisc->GetSmartRandom( (outcomes), (decr), pFirst, pSecond )
#define smartRoll(prob,maxfails,maxsuccs) pMisc->GetSmartRoll( (prob), (maxfails), (maxsuccs), pFirst, pSecond )
#define refineScale(s0,s6) pMisc->GetRefineAbilityScale( (s0), (s6) )
#define getTalentRefineRate(talId, defVal) ( (pFirst->GetTalent( talId ) != 0) ? pFirst->GetTalent( talId )->GetRefineRate() : defVal )
#define getStatusDispellPriority(a) pMisc->GetStatusDispellPriority( pSecond, (a) )

// Additional functions
#ifndef min
inline float min(float a, float b)
{
	return a < b ? a : b;
}
#endif

#ifndef max
inline float max(float a, float b)
{
	return a > b ? a : b;
}
#endif

#ifndef clamp
#define clamp(a,b,c) (min(max((a),(b)),(c)))
#endif

#ifndef lerp
inline float lerp( float param, float minvalue, float maxvalue)
{
	return minvalue * ( 1.0f - param ) + maxvalue * param;
}
#endif

inline bool isinbounds( float x, float left, float right )
{
	return left <= x && x <= right;
}

#ifndef round
__forceinline float round( float fVal )
{
  if (fVal >= 0.0f)
    return (floor(fVal + 0.5f));
  else
    return (ceil(fVal - 0.5f));
};
#endif

inline float t(int index, float neutral, float a, float b)
{
	switch (index)
	{
	case 0: return neutral;
	case 1: return a;
	case 2: return b;
	}
	return 0.0f;
}

inline float SwitchByAbilityRank(int rank, float lvl1, float lvl2, float lvl3, float lvl4)
{
	switch (rank)
	{
	case 1: return lvl1;
	case 2: return lvl2;
	case 3: return lvl3;
	case 4: return lvl4;
	}
	return 0.0f;
}

inline float SwitchByBool(bool bVal, float trueVal, float falseVal)
{
	return bVal ? trueVal : falseVal;
}

inline int f2l_nosse(float f)
{
  unsigned short int cwOld;
  unsigned short int cwNew;
  int nI;
   __asm
  {
    fld         dword ptr[f]            // загрузка значения float
    fnstcw      word ptr[cwOld]         // сохранение FPUCW
    movzx       eax, word ptr[cwOld]
    or          eax, 0x0c00             // установка режима округления в сторону нуля (truncate)
    mov         dword ptr[cwNew], eax
    fldcw       word ptr[cwNew]         // загрузка нового значения FPUCW
    fistp       dword ptr[nI]           // сохранение значения int
    fldcw       word ptr[cwOld]         // восстановление FPUCW
  }
  return nI;
}

inline int f2l_sse3(float f)
{
  int nI;
  __asm
  {
    fld         dword ptr[f] // загрузка значения float
    fisttp      dword ptr[nI] // сохранение значения int в режиме truncate
  }
  return nI;
}

inline __declspec(naked) int f2l(float f)
{
  __asm
  {
    MOV EAX,1               //request CPU feature flags
    CPUID                   //0Fh, 0A2h CPUID instruction
    TEST EDX, 0x4000000    //test bit 26 (SSE2)
    jz noSSE
    cvttss2si   eax, dword ptr[esp + 4]
    ret 
  }
noSSE:
  __asm
  {
    jmp f2l_nosse
  }
}

enum EAbilityScaleMode
{
  ABILITYSCALEMODE_STAT   = 0,
  ABILITYSCALEMODE_LIFE   = 1,
  ABILITYSCALEMODE_ENERGY = 2
};

enum { ZZSEX_UNDEFINED, ZZSEX_MALE, ZZSEX_FEMALE };

enum
{
	TERR_N = 0,
	TERR_A = 1,
	TERR_B = 2
};

enum UnitCheckID
{
	UNITCHECKID_ISHERO = 0,
	UNITCHECKID_ISBUILDING = 1
};

enum
{
  FCTN_N = 0,
  FCTN_A = 1,
  FCTN_B = 2
};


inline float d(const CVec2 &pos1, const CVec2 &pos2)
{
  const CVec2 dd( pos1.x - pos2.x, pos1.y - pos2.y);
  return sqrt(dd.x*dd.x + dd.y * dd.y);
}

enum ApplicatorSearchType
{
  GLOBAL,
  UNIT,
  ABILITY,
  DISPATCH,
  UNIT_AND_SUMMONS,
};

enum AbilityID
{
  BASE_ATTACK = -1,
  ABILITY0 = 0,
  ABILITY1,
  ABILITY2,
  ABILITY3,
  ABILITY4,
};

enum HeroClassId
{
  PROTECTOR = 1,
  VANGUARD = 2,
  EXECUTIONER = 4,
  FIGHTER = 8,
  SUPPORT = 16,
};

enum HeroStatisticsId
{
  TOWERS_DESTROYED,
  BARRACKS_DESTROYED,
  HERO_KILLS,
  ASSISTS,
  DEATHS,
  GLYPHS_PICKUPED,
  ACHIEVEMENTS_SCORE,
  TOTAL_SCORE
};

namespace DamageSource
{
  enum
  {
    UNIT,

    APPLICATOR_ABILITY,

    ABILITY_ATTACK,
    ABILITY_SPECIAL,

    ABILITY1,
    ABILITY2,
    ABILITY3,
    ABILITY4,
    ABILITY5,

    TALENT,

    TALENT_CLASS,
    TALENT_ORDINARY,
    TALENT_GOOD,
    TALENT_EXCELLENT,
    TALENT_MAGNIFICENT,
    TALENT_EXCLUSIVE,
    TALENT_OUTSTANDING,

    TALENT_TIER1,
    TALENT_TIER2,
    TALENT_TIER3,
    TALENT_TIER4,
    TALENT_TIER5,
    TALENT_TIER6,
  };
}

enum DamageSourceFlags
{
  DMG_UNIT = (1 << DamageSource::UNIT),

  DMG_APPLICATOR_ABILITY = (1 << DamageSource::APPLICATOR_ABILITY),

  DMG_ABILITY_ATTACK = (1 << DamageSource::ABILITY_ATTACK),
  DMG_ABILITY_SPECIAL = (1 << DamageSource::ABILITY_SPECIAL),

  DMG_ABILITY1 = (1 << DamageSource::ABILITY1),
  DMG_ABILITY2 = (1 << DamageSource::ABILITY2),
  DMG_ABILITY3 = (1 << DamageSource::ABILITY3),
  DMG_ABILITY4 = (1 << DamageSource::ABILITY4),
  DMG_ABILITY5 = (1 << DamageSource::ABILITY5),

  DMG_TALENT = (1 << DamageSource::TALENT),

  DMG_TALENT_CLASS = (1 << DamageSource::TALENT_CLASS),
  DMG_TALENT_ORDINARY = (1 << DamageSource::TALENT_ORDINARY),
  DMG_TALENT_GOOD = (1 << DamageSource::TALENT_GOOD),
  DMG_TALENT_EXCELLENT = (1 << DamageSource::TALENT_EXCELLENT),
  DMG_TALENT_MAGNIFICENT = (1 << DamageSource::TALENT_MAGNIFICENT),
  DMG_TALENT_EXCLUSIVE = (1 << DamageSource::TALENT_EXCLUSIVE),
  DMG_TALENT_OUTSTANDING = (1 << DamageSource::TALENT_OUTSTANDING),

  DMG_TALENT_TIER1 = (1 << DamageSource::TALENT_TIER1),
  DMG_TALENT_TIER2 = (1 << DamageSource::TALENT_TIER2),
  DMG_TALENT_TIER3 = (1 << DamageSource::TALENT_TIER3),
  DMG_TALENT_TIER4 = (1 << DamageSource::TALENT_TIER4),
  DMG_TALENT_TIER5 = (1 << DamageSource::TALENT_TIER5),
  DMG_TALENT_TIER6 = (1 << DamageSource::TALENT_TIER6),

  // shortened
  DMG_APPL_ABLT = DMG_APPLICATOR_ABILITY,

  DMG_ATTACK = DMG_ABILITY_ATTACK,
  DMG_SPECIAL = DMG_ABILITY_SPECIAL,

  DMG_ABLT1 = DMG_ABILITY1,
  DMG_ABLT2 = DMG_ABILITY2,
  DMG_ABLT3 = DMG_ABILITY3,
  DMG_ABLT4 = DMG_ABILITY4,
  DMG_ABLT5 = DMG_ABILITY5,

  DMG_TAL = DMG_TALENT,

  DMG_CLASS = DMG_TALENT_CLASS,
  DMG_ORDINARY = DMG_TALENT_ORDINARY,
  DMG_GOOD = DMG_TALENT_GOOD,
  DMG_EXCELLENT = DMG_TALENT_EXCELLENT,
  DMG_MAGNIFICENT = DMG_TALENT_MAGNIFICENT,
  DMG_EXCLUSIVE = DMG_TALENT_EXCLUSIVE,
  DMG_OUTSTANDING = DMG_TALENT_OUTSTANDING,

  DMG_TAL1 = DMG_TALENT_TIER1,
  DMG_TAL2 = DMG_TALENT_TIER2,
  DMG_TAL3 = DMG_TALENT_TIER3,
  DMG_TAL4 = DMG_TALENT_TIER4,
  DMG_TAL5 = DMG_TALENT_TIER5,
  DMG_TAL6 = DMG_TALENT_TIER6,
};

struct IMiscFormulaPars;

struct IUnitFormulaPars
{
	// 
	virtual float GetLife()   const = 0;
	virtual float GetEnergy() const = 0;

  virtual bool  IsMale()    const = 0;

	// Stats
	virtual float GetMaxLife()        const = 0;
	virtual float GetMaxEnergy()      const = 0;
	virtual float	GetRange()          const = 0;
	virtual float GetMoveSpeed()      const = 0;
	virtual float GetAttackSpeed()    const = 0;
	virtual float GetCritMult()       const = 0;
	virtual float GetLifeRegen()      const = 0;
	virtual float GetEnergyRegen()    const = 0;
	virtual float GetLifeRegenAbs()   const = 0;
	virtual float GetEnergyRegenAbs() const = 0;
	virtual float GetEvasion()        const = 0;
	virtual float GetLifeDrain()      const = 0;
	virtual float GetEnergyDrain()    const = 0;

	// Misc information
	virtual float GetSummonCnt()             const = 0;
	virtual bool  IsMoving()                 const = 0;
	virtual float GetTimeStanding()          const = 0;
	virtual int   GetTerrainType()           const = 0;
	virtual int   GetUnitKind()              const = 0;
	virtual bool  IsHero()                   const = 0;
	virtual bool  UnitCheck(UnitCheckID id)  const = 0;
  virtual int   GetNativeDefenceIndex()    const = 0;
  virtual int   GetNativeAttackIndex()     const = 0;
  virtual int   GetDevPoints()             const = 0;
  virtual bool  GetFlag(unsigned int flag) const = 0;
  virtual bool  GetOnBase()                const = 0;
  virtual int   GetZZimaSex()              const = 0;
  virtual bool  IsVisibleForEnemy(int)     const = 0;
  virtual float GetObjectSize()            const = 0;

  //Base Stats
  virtual float GetBaseLife()                       const = 0;
  virtual float GetBaseEnergy()                     const = 0;
  virtual float GetBaseRange()                      const = 0;
  virtual float GetBaseMoveSpeed()                  const = 0;
  virtual float GetBaseAttackSpeed()                const = 0;
  virtual float GetBaseCriticalChance()             const = 0;
  virtual float GetBaseCriticalMultiplier()         const = 0;
  virtual float GetBaseLifeDrain()                  const = 0;
  virtual float GetBaseEnergyDrain()                const = 0;
  virtual float GetBaseEvasion()                    const = 0;
  virtual float GetBaseLifeRegeneration()           const = 0;
  virtual float GetBaseLifeRegenerationAbsolute()   const = 0;
  virtual float GetBaseEnergyRegeneration()         const = 0;
  virtual float GetBaseEnergyRegenerationAbsolute() const = 0;
  virtual float GetBaseVisibilityRange()            const = 0;
  virtual float GetBaseStrength()                   const = 0;
  virtual float GetBaseIntellect()                  const = 0;
  virtual float GetBaseDexterity()                  const = 0;
  virtual float GetBaseBaseAttack()                 const = 0;
  virtual float GetBaseStamina()                    const = 0;
  virtual float GetBaseWill()                       const = 0;
  virtual float GetBaseNaftaMult()                  const = 0;
  virtual float GetBaseNaftaSpecForKill()           const = 0;
  virtual float GetBaseNaftaForKill()               const = 0;
  virtual float GetBaseNaftaForAssist()             const = 0;
  virtual float GetBaseTeamNaftaForKill()           const = 0;
  virtual float GetBaseTeamNaftaForPresence()       const = 0;
  virtual float GetBaseCritChanceBonus()            const = 0;
  virtual float GetBaseEnergyDamageDecrease()       const = 0;
  virtual float GetBaseMaterialDamageDecrease()     const = 0;
  virtual float GetBaseMissChance()                 const = 0;

  //Derivative Stats
  virtual float GetLifeRegenTotal()             const = 0;
  virtual float GetEnergyRegenTotal()           const = 0;
  virtual float GetDamageMin()                  const = 0;
  virtual float GetDamageMax()                  const = 0;
  virtual float GetDexterityDamageMult()        const = 0;
  virtual float GetMoveSpeedMpS()               const = 0;
  virtual float GetCritChance()                 const = 0;
  virtual float GetAttacksPerSecond()           const = 0;
  virtual float GetBodyDefence()                const = 0;
  virtual float GetSpiritDefence()              const = 0;
  virtual float GetPenetrationFromAttackSpeed() const = 0;
  virtual float GetPenetrationFromDexterity()   const = 0;
  virtual float GetPenetrationTotal()           const = 0;

  virtual bool  IsRecommended(int stat) const = 0;

  //New RPG system
  virtual float GetStrength()               const = 0;
  virtual float GetIntellect()              const = 0;
  virtual float GetDexterity()              const = 0;
  virtual float GetBaseAttack()             const = 0;
  virtual float GetStamina()                const = 0;
  virtual float GetWill()                   const = 0;
  virtual float GetNaftaMult()              const = 0;
  virtual int   GetNaftaSpecForKill()       const = 0;
  virtual int   GetNaftaForKill()           const = 0;
  virtual int   GetNaftaForAssist()         const = 0;
  virtual int   GetTeamNaftaForKill()       const = 0;
  virtual int   GetTeamNaftaForPresence()   const = 0;
  virtual int   GetNaftaLevel()             const = 0;
  virtual int   GetNafta()                  const = 0;
  virtual int   GetTotalNaftaEarned()       const = 0;
  virtual float GetCritChanceBonus()        const = 0;
  virtual float GetEnergyDamageDecrease()   const = 0;
  virtual float GetMaterialDamageDecrease() const = 0;
  virtual float GetMissChance()             const = 0;

  //universal interface
  virtual IUnitFormulaPars const * GetObjectMaster() const = 0;
  //virtual IUnitFormulaPars       * GetObjectMaster() = 0;
  virtual IUnitFormulaPars const * GetObjectFavorite() const = 0;
  //virtual IUnitFormulaPars       * GetObjectFavorite() = 0;
  virtual IUnitFormulaPars const * GetObjectTarget() const = 0;
  //virtual IUnitFormulaPars       * GetObjectTarget() = 0;
  virtual float GetVariable(const char *name) const = 0;

  //distance
  virtual CVec2 GetPos() const = 0;

  //other
	virtual int   GetFctn() const = 0;
  virtual int   GetOriginalFctn() const = 0;

	virtual int   GetWOID() const = 0;

  virtual const IMiscFormulaPars* FindApplicator(   const char* name, const IMiscFormulaPars* pMisc, ApplicatorSearchType searchType ) const = 0;
  virtual int                     CountApplicators( const char* name, const IMiscFormulaPars* pMisc, ApplicatorSearchType searchType ) const = 0;

  virtual IMiscFormulaPars const* GetAblt(AbilityID abilityId) const = 0;

  virtual IMiscFormulaPars const* GetTalent(const char* id) const = 0;

  virtual float GetDamageTaken(float dt)   const = 0;
  virtual float GetDamageDealt(float dt)   const = 0;

  virtual float GetCoreEnergy() const = 0;
  virtual bool  HasTalentFromPack( const char* id ) const = 0;

  virtual int GetEffectiveClassMask() const = 0;
  virtual int CountStatusesForDispel( const IUnitFormulaPars* pDispeller ) const = 0;
  virtual float GetForce( bool = false ) const = 0;
  virtual float GetHeroStatisticsValue( HeroStatisticsId heroStatId ) const = 0;
  virtual int GetHeroAchievementCount( const char* achievId ) const = 0;

  virtual bool  IsEvading()                const = 0;

  virtual int GetKillStreak() const = 0;
  virtual int GetDeathStreak() const = 0;
  // TODO: correct naming
  virtual int GetAssistersCount() const = 0;
  virtual int GetSpecCount() const = 0;
  virtual int GetPresentTeamActiveMembers() const = 0;
  virtual bool IsSkinUsed( const char * skinId ) const = 0;

  virtual float GetDamageTakenEx(float dt, const unsigned mask, const IMiscFormulaPars* const pMisc = 0) const = 0;
  virtual float GetDamageDealtEx(float dt, const unsigned mask, const IMiscFormulaPars* const pMisc = 0) const = 0;

  ZDATA
public:
	ZEND int operator&( IBinSaver &f ) { return 0; }
};

enum
{
  ABILITYTYPE_SIMPLE = 0,
  ABILITYTYPE_ACTIVE = 1,
  ABILITYTYPE_MULTIACTIVE = 2,
  ABILITYTYPE_PASSIVE = 3,
  ABILITYTYPE_AUTOCASTABLE = 4,
  ABILITYTYPE_SWITCHABLE = 5,
	ABILITYTYPE_CHANNELLING = 6,
};


struct IMiscFormulaPars
{
  //parameters
	virtual bool  IsAbilityOn() const = 0;
  virtual bool  IsTalentBought() const = 0;
	virtual int   GetRank() const = 0;
	virtual float GetDist2Target() const = 0;
	virtual float GetScale() const = 0;
	virtual float GetParentScale() const = 0;
  virtual float GetManaCost() const = 0;
  virtual float GetPreparedness() const = 0;
  virtual int   GetAbilityType() const = 0;
	virtual bool  Roll(float probability) const = 0;
  virtual int   GetTerrainType() const = 0;
  virtual int   GetRefineRate() const = 0;
  virtual int   GetTalentLevel() const = 0;
  virtual int   GetTalentDevPoints() const = 0;
  virtual int   GetNaftaCost() const = 0;
  virtual float GetCooldown() const = 0;
  virtual int   GetScrollLevel() const = 0;

  //objects
  virtual const IUnitFormulaPars* GetObjectOwner() const = 0;
	virtual const IMiscFormulaPars* GetObjectParent() const = 0;     
  
  virtual const IUnitFormulaPars* GetObject( char const*) const = 0;
  virtual float GetConstant(const char *name, IUnitFormulaPars const *pSender, IUnitFormulaPars const* pReceiver) const = 0;

  virtual float GetVariable(const char *name) const = 0;

  //distance
  virtual CVec2 GetTargetPos() const = 0;

  virtual int   GetRandom(int from, int to)const = 0;
  virtual float GetAbilityScale( bool isDamage, float statValue, EAbilityScaleMode abScaleMode, float valueLeft, float valueRight, bool bRound = true ) const = 0;
  virtual bool  GetSmartRoll( float probability, int maxFailReps, int maxSuccessReps, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const = 0;
  virtual int   GetSmartRandom( int outcomesNumber, float probDecrement, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const = 0; 
  virtual float GetRefineAbilityScale( float valueAtRefineLevel0, float valueAtRefineLevel6  ) const = 0;
  virtual int   GetAlternativeTargetIndex() const = 0;
  virtual float GetTerrainPart(int faction) const = 0;
  virtual int   GetActivatedWithinKit() const = 0;
  virtual int   GetTalentsWithinKit() const = 0;
  virtual float GetStatusDispellPriority( const IUnitFormulaPars* pUnitToCheck, bool returnDuration ) const = 0;
  virtual CVec2 GetVectorVariable(const char *name) const = 0;
  virtual int   GetTerrianTypeUnderCursor() const = 0;
  virtual int   GetNatureTypeInPos(CVec2 pos) const = 0;

  virtual bool  IsNight() const = 0;

  virtual bool  CheckUpgradePerCastPerTarget() const = 0;

	ZDATA
public:
  ZEND int operator&( IBinSaver &f ) { return 0; }
};

struct ICustomFormulaPars
{
  virtual CVec2 GetPos2D() const = 0;

  ZDATA
public:
  ZEND int operator&( IBinSaver &f ) { return 0; }
};
