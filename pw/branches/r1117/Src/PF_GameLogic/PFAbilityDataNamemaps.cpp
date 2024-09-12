#include "stdafx.h"

#include "PFAbilityData.h"
#include "PFBaseUnit.h"
#include "PFHero.h"
#include "PFAIWorld.h"

#include "PrecompiledTooltips.h"


namespace NWorld
{

namespace
{

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // AbilityVariantContext
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class AbilityVariantContext : public IUnitFormulaPars, public IMiscFormulaPars, public NonCopyable
  {
    CPtr<PFBaseUnit> pOwner;
    PFAbilityData const* pAbility;
    typedef hash_map<string, float> ParamsMap;
    ParamsMap externalParams;

  public:
    AbilityVariantContext( PFAbilityData const* pAbility, NGameX::PrecompiledTooltipVariantParameters const* pPrms )
      : pAbility(pAbility)
      , pOwner( pAbility->GetOwner() )
    {
      if ( pPrms )
      {
        typedef vector<NGameX::PrecompiledTooltipVariantParameters::Parameter> Parameters;
        Parameters const& params = pPrms->rgPrms;
        for ( Parameters::const_iterator iPrm = params.begin(), iEnd = params.end(); iPrm != iEnd; ++iPrm )
        {
          NI_VERIFY( !iPrm->name.empty(), "Empty parameter spipped!", continue; );
          NI_ASSERT( externalParams.find(iPrm->name) == externalParams.end(), NStr::StrFmt("Duplicated parameter '%s'!", iPrm->name) );
          float fValue = NStr::ToFloat(iPrm->value);
          externalParams[iPrm->name] = fValue;
        }
      }
    }
    inline PFAbilityData const* GetAbility() const {
      return pAbility;
    }

  private:

#define GET_EXT__PARAM( Name )                                                                        \
    {                                                                                                 \
      ParamsMap::const_iterator iExternalPrm = externalParams.find( #Name );                          \
      return ( iExternalPrm != externalParams.end() ) ? iExternalPrm->second : pOwner->Get##Name##(); \
    }   

#define GET_UNIT_PARAM( Name ) { return pOwner->Get##Name##(); }

    virtual float GetLife()      const { GET_EXT__PARAM( Life      ); }
    virtual float GetEnergy()    const { GET_EXT__PARAM( Energy    ); }
    virtual float GetMaxLife()   const { GET_EXT__PARAM( MaxLife   ); }
    virtual float GetMaxEnergy() const { GET_EXT__PARAM( MaxEnergy ); }

    virtual float	GetRange()              const { GET_UNIT_PARAM( Range              ); }
    virtual float GetMoveSpeed()          const { GET_UNIT_PARAM( MoveSpeed          ); }
    virtual float GetAttackSpeed()        const { GET_UNIT_PARAM( AttackSpeed        ); }
    virtual float GetCritMult()           const { GET_UNIT_PARAM( CritMult           ); }
    virtual float GetLifeRegen()          const { GET_UNIT_PARAM( LifeRegen          ); }
    virtual float GetEnergyRegen()        const { GET_UNIT_PARAM( EnergyRegen        ); }
    virtual float GetLifeRegenAbs()       const { GET_UNIT_PARAM( LifeRegenAbs       ); }
    virtual float GetEnergyRegenAbs()     const { GET_UNIT_PARAM( EnergyRegenAbs     ); }
    virtual float GetEvasion()            const { GET_UNIT_PARAM( Evasion            ); }
    virtual float GetLifeDrain()          const { GET_UNIT_PARAM( LifeDrain          ); }
    virtual float GetEnergyDrain()        const { GET_UNIT_PARAM( EnergyDrain        ); }
    virtual float GetSummonCnt()          const { GET_UNIT_PARAM( SummonCnt          ); }
    virtual float GetTimeStanding()       const { GET_UNIT_PARAM( TimeStanding       ); }

    virtual int   GetTerrainType()        const { GET_UNIT_PARAM( TerrainType        ); }
    virtual int   GetUnitKind()           const { GET_UNIT_PARAM( UnitKind           ); }
    virtual int   GetFctn()               const { GET_UNIT_PARAM( Fctn               ); }
    virtual int   GetOriginalFctn()       const { GET_UNIT_PARAM( OriginalFctn       ); }
    virtual int   GetNativeDefenceIndex() const { GET_UNIT_PARAM( NativeDefenceIndex ); }
    virtual int   GetNativeAttackIndex()  const { GET_UNIT_PARAM( NativeAttackIndex  ); }
    virtual int   GetDevPoints()          const { GET_UNIT_PARAM( DevPoints          ); }
    virtual int   GetWOID()               const { GET_UNIT_PARAM( WOID               ); }

    virtual bool  GetOnBase() const { GET_UNIT_PARAM( OnBase ); }
    virtual int   GetZZimaSex() const { GET_UNIT_PARAM( ZZimaSex ); }
    virtual float GetObjectSize() const { GET_UNIT_PARAM( ObjectSize ); }
    virtual float GetDamageTaken( float dt ) const { return pOwner->GetDamageTaken( dt ); }
    virtual float GetDamageDealt( float dt ) const { return pOwner->GetDamageDealt( dt ); }
    virtual float GetDamageTakenEx( float dt, const unsigned mask, const IMiscFormulaPars* const pMisc ) const { return pOwner->GetDamageTakenEx( dt, mask, pMisc ); }
    virtual float GetDamageDealtEx( float dt, const unsigned mask, const IMiscFormulaPars* const pMisc ) const { return pOwner->GetDamageDealtEx( dt, mask, pMisc ); }

    virtual bool  IsMoving() const  { return pOwner->IsMoving(); }
    virtual bool  IsHero()   const  { return pOwner->IsHero();   }
    virtual bool  IsMale()   const  { return pOwner->IsMale();   }
    virtual bool  IsEvading() const { return pOwner->IsEvading(); }

    virtual int   GetKillStreak() const { return pOwner->GetKillStreak(); }
    virtual int   GetDeathStreak() const { return pOwner->GetDeathStreak(); }
    virtual int   GetAssistersCount() const { return pOwner->GetAssistersCount(); }
    virtual int   GetSpecCount() const { return pOwner->GetSpecCount(); }
    virtual int   GetPresentTeamActiveMembers() const { return pOwner->GetPresentTeamActiveMembers(); }
    virtual bool  IsSkinUsed( const char * skinId ) const { return pOwner->IsSkinUsed(skinId); }

    virtual bool  IsVisibleForEnemy( int faction ) const { return pOwner->IsVisibleForEnemy( faction ); }

    virtual bool  GetFlag( unsigned int flag ) const { return pOwner->GetFlag(flag); }


    //Base Stats
    virtual float GetBaseLife()                       const { GET_UNIT_PARAM( BaseLife                       ); }
    virtual float GetBaseEnergy()                     const { GET_UNIT_PARAM( BaseEnergy                     ); }
    virtual float GetCoreEnergy()                     const { GET_UNIT_PARAM( CoreEnergy                     ); }
    virtual float GetBaseRange()                      const { GET_UNIT_PARAM( BaseRange                      ); }
    virtual float GetBaseMoveSpeed()                  const { GET_UNIT_PARAM( BaseMoveSpeed                  ); }
    virtual float GetBaseAttackSpeed()                const { GET_UNIT_PARAM( BaseAttackSpeed                ); }
    virtual float GetBaseCriticalChance()             const { GET_UNIT_PARAM( BaseCriticalChance             ); }
    virtual float GetBaseCriticalMultiplier()         const { GET_UNIT_PARAM( BaseCriticalMultiplier         ); }
    virtual float GetBaseLifeDrain()                  const { GET_UNIT_PARAM( BaseLifeDrain                  ); }
    virtual float GetBaseEnergyDrain()                const { GET_UNIT_PARAM( BaseEnergyDrain                ); }
    virtual float GetBaseEvasion()                    const { GET_UNIT_PARAM( BaseEvasion                    ); }
    virtual float GetBaseLifeRegeneration()           const { GET_UNIT_PARAM( BaseLifeRegeneration           ); }
    virtual float GetBaseLifeRegenerationAbsolute()   const { GET_UNIT_PARAM( BaseLifeRegenerationAbsolute   ); }
    virtual float GetBaseEnergyRegeneration()         const { GET_UNIT_PARAM( BaseEnergyRegeneration         ); }
    virtual float GetBaseEnergyRegenerationAbsolute() const { GET_UNIT_PARAM( BaseEnergyRegenerationAbsolute ); }
    virtual float GetBaseVisibilityRange()            const { GET_UNIT_PARAM( BaseVisibilityRange            ); }
    virtual float GetBaseStrength()                   const { GET_UNIT_PARAM( BaseStrength                   ); }
    virtual float GetBaseIntellect()                  const { GET_UNIT_PARAM( BaseIntellect                  ); }
    virtual float GetBaseDexterity()                  const { GET_UNIT_PARAM( BaseDexterity                  ); }
    virtual float GetBaseBaseAttack()                 const { GET_UNIT_PARAM( BaseBaseAttack                 ); }
    virtual float GetBaseStamina()                    const { GET_UNIT_PARAM( BaseStamina                    ); }
    virtual float GetBaseWill()                       const { GET_UNIT_PARAM( BaseWill                       ); }
    virtual float GetBaseNaftaMult()                  const { return 0.0f; }
    virtual float GetBaseNaftaSpecForKill()           const { GET_UNIT_PARAM( BaseNaftaSpecForKill           ); }
    virtual float GetBaseNaftaForKill()               const { GET_UNIT_PARAM( BaseNaftaForKill               ); }
    virtual float GetBaseNaftaForAssist()             const { GET_UNIT_PARAM( BaseNaftaForAssist             ); }
    virtual float GetBaseTeamNaftaForKill()           const { GET_UNIT_PARAM( BaseTeamNaftaForKill           ); }
    virtual float GetBaseTeamNaftaForPresence()       const { GET_UNIT_PARAM( BaseTeamNaftaForPresence       ); }
    virtual float GetBaseCritChanceBonus()            const { GET_UNIT_PARAM( BaseCritChanceBonus            ); }
    virtual float GetBaseEnergyDamageDecrease()       const { GET_UNIT_PARAM( BaseEnergyDamageDecrease       ); }
    virtual float GetBaseMaterialDamageDecrease()     const { GET_UNIT_PARAM( BaseMaterialDamageDecrease     ); }
    virtual float GetBaseMissChance()                 const { GET_UNIT_PARAM( BaseMissChance                 ); }

    //Derivate stats
    virtual float GetLifeRegenTotal()             const { GET_UNIT_PARAM( LifeRegenTotal             ); }
    virtual float GetEnergyRegenTotal()           const { GET_UNIT_PARAM( EnergyRegenTotal           ); }
    virtual float GetDamageMin()                  const { GET_UNIT_PARAM( DamageMin                  ); }
    virtual float GetDamageMax()                  const { GET_UNIT_PARAM( DamageMax                  ); }
    virtual float GetDexterityDamageMult()        const { GET_UNIT_PARAM( DexterityDamageMult        ); }
    virtual float GetMoveSpeedMpS()               const { GET_UNIT_PARAM( MoveSpeedMpS               ); }
    virtual float GetCritChance()                 const { GET_UNIT_PARAM( CritChance                 ); }
    virtual float GetAttacksPerSecond()           const { GET_UNIT_PARAM( AttacksPerSecond           ); }
    virtual float GetBodyDefence()                const { GET_UNIT_PARAM( BodyDefence                ); }
    virtual float GetSpiritDefence()              const { GET_UNIT_PARAM( SpiritDefence              ); }
    virtual float GetPenetrationFromAttackSpeed() const { GET_UNIT_PARAM( PenetrationFromAttackSpeed ); }
    virtual float GetPenetrationFromDexterity()   const { GET_UNIT_PARAM( PenetrationFromDexterity   ); }
    virtual float GetPenetrationTotal()           const { GET_UNIT_PARAM( PenetrationTotal           ); }

    //New RPG system
    virtual float GetStrength()           const { GET_UNIT_PARAM( Strength   ); }
    virtual float GetIntellect()          const { GET_UNIT_PARAM( Intellect  ); }
    virtual float GetDexterity()          const { GET_UNIT_PARAM( Dexterity  ); }
    virtual float GetBaseAttack()         const { GET_UNIT_PARAM( BaseAttack ); }
    virtual float GetStamina()            const { GET_UNIT_PARAM( Stamina    ); }
    virtual float GetWill()               const { GET_UNIT_PARAM( Will       ); }
    virtual float GetNaftaMult()          const { return 0.0f; }

    virtual int GetNaftaSpecForKill()     const { GET_UNIT_PARAM( NaftaSpecForKill      ); }
    virtual int GetNaftaForKill()         const { GET_UNIT_PARAM( NaftaForKill          ); }
    virtual int GetNaftaForAssist()       const { GET_UNIT_PARAM( NaftaForAssist        ); }
    virtual int GetNafta()                const { GET_UNIT_PARAM( Gold                  ); }
    virtual int GetTotalNaftaEarned()     const { GET_UNIT_PARAM( TotalNaftaEarned      ); }
    virtual int GetTeamNaftaForKill()     const { GET_UNIT_PARAM( TeamNaftaForKill      ); }
    virtual int GetTeamNaftaForPresence() const { GET_UNIT_PARAM( TeamNaftaForPresence  ); }
    virtual int GetNaftaLevel()           const { GET_UNIT_PARAM( NaftaLevel            ); }

    virtual float GetCritChanceBonus()        const { GET_UNIT_PARAM( CritChanceBonus        ); }
    virtual float GetEnergyDamageDecrease()   const { GET_UNIT_PARAM( EnergyDamageDecrease   ); }
    virtual float GetMaterialDamageDecrease() const { GET_UNIT_PARAM( MaterialDamageDecrease ); }
    virtual float GetMissChance()             const { GET_UNIT_PARAM( MissChance             ); }
      
    
    virtual int GetEffectiveClassMask() const { return pOwner->GetEffectiveClassMask(); }
    virtual int CountStatusesForDispel( const IUnitFormulaPars* pDispeller ) const { return 0; }
    virtual float GetForce( bool bCountPersistentStats = false ) const { return pOwner->GetForce( bCountPersistentStats ); }
    virtual float GetHeroStatisticsValue( HeroStatisticsId heroStatId ) const { return pOwner->GetHeroStatisticsValue( heroStatId ); }
    virtual int GetHeroAchievementCount( const char* achievId ) const { return pOwner->GetHeroAchievementCount( achievId ); }

    virtual bool  IsRecommended( int stat ) const { return pOwner->IsRecommended( stat ); }
    
    virtual bool  UnitCheck(UnitCheckID id) const { return pOwner->UnitCheck(id); }

		virtual float GetVariable(const char *name) const { return pOwner->GetVariable(name); }
    virtual const IMiscFormulaPars* FindApplicator(   const char* name, const IMiscFormulaPars*, ApplicatorSearchType searchType ) const { return pOwner->FindApplicator(  name, pAbility, searchType ); }
    virtual int                     CountApplicators( const char* name, const IMiscFormulaPars*, ApplicatorSearchType searchType ) const { return pOwner->CountApplicators( name, pAbility, searchType ); }
    virtual IMiscFormulaPars const* GetAblt(AbilityID) const { return NULL; }
    virtual IMiscFormulaPars const* GetTalent(const char* id) const { return pOwner->GetTalent( id ); }
    virtual IUnitFormulaPars const* GetObjectMaster() const { return NULL; }
    virtual IUnitFormulaPars const* GetObjectFavorite() const { return NULL; }
    virtual IUnitFormulaPars const* GetObjectTarget() const { return NULL; }
    virtual const IUnitFormulaPars* GetObjectOwner() const { return NULL; }
    virtual const IUnitFormulaPars* GetObject( char const*) const { return NULL; }
    virtual CVec2 GetPos()       const { NI_ALWAYS_ASSERT("Undefined"); return VNULL2; }
    virtual CVec2 GetTargetPos() const { NI_ALWAYS_ASSERT("Undefined"); return VNULL2; }
    virtual int                     GetRandom(int from, int to)const { return from; }
    virtual bool  GetSmartRoll( float probability, int maxFailReps, int maxSuccessReps, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const { return pAbility->GetSmartRoll( probability, maxFailReps, maxSuccessReps, pFirst, pSecond ); }
    virtual int   GetSmartRandom( int outcomesNumber, float probDecrement, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const { return pAbility->GetSmartRandom( outcomesNumber, probDecrement, pFirst, pSecond ); }
    virtual int   GetScrollLevel() const { return pOwner->GetWorld()->GetAIWorld()->GetAveragePriestessLvl(pOwner->GetFaction()); }
    virtual bool  IsNight() const { return pOwner->GetWorld()->IsNight(); }
    virtual bool  CheckUpgradePerCastPerTarget() const { NI_ALWAYS_ASSERT("Undefined"); return false; }
#undef GET_EXT__PARAM
#undef GET_UNIT_PARAM

#define GET_EXT__PARAM( Name )                                                                    \
    {                                                                                               \
    ParamsMap::const_iterator iExternalPrm = externalParams.find(#Name);                          \
    return (iExternalPrm != externalParams.end()) ? iExternalPrm->second : pAbility->Get##Name##(); \
    }   

    virtual int   GetRank               ()const { GET_EXT__PARAM(Rank              ); }
    virtual bool  IsAbilityOn           ()const { return pAbility->IsOn(); }

    virtual float GetDist2Target        ()const { return 0.f; }
    virtual float GetScale              ()const { return pAbility->GetScale(); }
    virtual float GetParentScale        ()const { return 1.f; }
    virtual float GetPreparedness       ()const { return pAbility->GetCurrentCooldown(); }
    virtual float GetCooldown           ()const { return pAbility->GetCooldown(); }
    virtual float GetManaCost           ()const { return pAbility->GetManaCost(); }
    virtual int   GetNaftaCost          ()const { return pAbility->GetNaftaCost(); }
    virtual int   GetRefineRate         ()const { return pAbility->GetRefineRate(); }
    virtual float GetRefineAbilityScale( float valueAtRefineLevel0, float valueAtRefineLevel6  ) const { return pAbility->GetRefineAbilityScale(valueAtRefineLevel0, valueAtRefineLevel6); }
    virtual int   GetTalentLevel        ()const { return pAbility->GetTalentLevel(); }
    virtual bool  IsTalentBought        ()const { return pAbility->IsTalentBought(); }
    virtual int   GetTalentDevPoints    ()const { return pAbility->GetTalentDevPoints(); }
    virtual int   GetAbilityType        ()const { return (int)pAbility->GetType(); }      
    virtual bool  Roll             (float)const { return false; }
    virtual float GetConstant(const char *name, IUnitFormulaPars const *, IUnitFormulaPars const*) const { return pAbility->CalcParam(name, this, this, this); } 
		virtual const IMiscFormulaPars* GetObjectParent() const { return this; }
    virtual float GetAbilityScale( bool isDamage, float statValue, EAbilityScaleMode abScaleMode, float valueLeft, float valueRight, bool bRound = true ) const { return pAbility->GetAbilityScale( isDamage, statValue, abScaleMode, valueLeft, valueRight, bRound ); }
    virtual int   GetAlternativeTargetIndex() const { return pAbility->GetAlternativeTargetIndex(); }
    virtual float GetTerrainPart(int faction) const { return pAbility->GetTerrainPart(faction); }
    virtual int   GetActivatedWithinKit() const { return pAbility->GetActivatedWithinKit(); }
    virtual int   GetTalentsWithinKit() const { return pAbility->GetTalentsWithinKit(); }
    virtual bool  HasTalentFromPack( const char* id ) const { return pOwner->HasTalentFromPack( id ); }
    virtual float GetStatusDispellPriority( const IUnitFormulaPars* pUnit, bool returnDuration ) const { return pAbility->GetStatusDispellPriority( pUnit, returnDuration ); }
    virtual CVec2 GetVectorVariable(const char *name) const { return pAbility->GetVectorVariable(name); }

    virtual int GetTerrianTypeUnderCursor() const {return pAbility->GetTerrianTypeUnderCursor(); }
    virtual int GetNatureTypeInPos(CVec2 pos) const {return pAbility->GetNatureTypeInPos(pos); }

#undef GET_EXT__PARAM

  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // AbilityFloatFormulaVariant
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class AbilityFloatFormulaVariant : public NNameMap::Variant, NonCopyable
  {
  public:
    AbilityFloatFormulaVariant(PFAbilityData const* pAbility, ExecutableFloatString const& formula, NDb::EAbilityModMode modId, NGameX::PrecompiledTooltipVariantParameters const* pPrms )
      : context(pAbility, pPrms)
      , formula(formula)
      , formulaSecondState(formula)
      , modId(modId)
      , useAbilityMods(true)
    {
    }

    AbilityFloatFormulaVariant(
      PFAbilityData const* pAbility,
      ExecutableFloatString const& formula,
      ExecutableFloatString const& formulaSecondState,
      NDb::EAbilityModMode modId,
      NGameX::PrecompiledTooltipVariantParameters const* pPrms )
      : context(pAbility, pPrms)
      , formula(formula)
      , formulaSecondState(formulaSecondState)
      , modId(modId)
      , useAbilityMods(true)
    {
    }

    AbilityFloatFormulaVariant(PFAbilityData const* pAbility, ExecutableFloatString const& formula, NGameX::PrecompiledTooltipVariantParameters const* pPrms )
      : context(pAbility, pPrms)
      , formula(formula)
      , formulaSecondState(formula)
      , useAbilityMods(false)
    {
    }

    virtual float GetFloat() const
    {
      float value;
      if (context.GetAbility()->IsSecondState())
        value = formulaSecondState( &context, &context, &context, 0.0f );
      else
        value = formula( &context, &context, &context, 0.0f );
      return !useAbilityMods ? value : context.GetAbility()->GetModifiedValue(value, modId);
    }

    virtual NNameMap::VariantType::Enum GetType() const { return NNameMap::VariantType::Float; }
    virtual bool IsReadonly() const                     { return true; }

  private:
    AbilityVariantContext         context;
    ExecutableFloatString const&  formula;
    ExecutableFloatString const&  formulaSecondState;
    bool                          useAbilityMods;
    NDb::EAbilityModMode          modId;
  };

  class AbilityBoolFormulaVariant : public NNameMap::Variant, NonCopyable
  {
  public:
    AbilityBoolFormulaVariant(PFAbilityData const* pAbility, ExecutableBoolString const& formula, NGameX::PrecompiledTooltipVariantParameters const* pPrms )
      : context(pAbility, pPrms)
      , formula(formula)
    {
    }

    virtual bool GetBool() const
    {
      return formula( &context, &context, &context, 0.0f );
    }

    virtual NNameMap::VariantType::Enum GetType() const { return NNameMap::VariantType::Bool; }
    virtual bool IsReadonly() const                     { return true; }

  private:
    AbilityVariantContext       context;
    ExecutableBoolString const& formula;
  };
} // unnamed namespace

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// const
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NAMEMAP_BEGIN(PFAbilityData::ConstantsResolver)
NAMEMAP_END;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NNameMap::Variant * PFAbilityData::ConstantsResolver::ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly )
{
  NDb::UnitConstant const* pConst = pAbility->GetConstant(name);
  if (NULL == pConst)
    return NULL;
  
  const NGameX::PrecompiledTooltipVariantParameters* pPrms = reinterpret_cast<NGameX::PrecompiledTooltipVariantParameters*>(prms);
  return new AbilityFloatFormulaVariant( pAbility, pConst->var, pPrms );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// if
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NAMEMAP_BEGIN(PFAbilityData::ConditionsResolver)
NAMEMAP_END;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NNameMap::Variant * PFAbilityData::ConditionsResolver::ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly )
{
  CPtr<PFBaseUnit> pOwner = pAbility->GetOwner();
  NI_VERIFY( IsValid(pOwner), "ConditionsResolver : ability owner is invalid!", return NULL; );

  for ( vector<NDb::Ptr<NDb::ConditionFormula>>::const_iterator iCond = pAbility->GetDBDesc()->conditionFormulas.begin(), iEnd = pAbility->GetDBDesc()->conditionFormulas.end(); iCond != iEnd; ++iCond )
    if ( (*iCond)->name == name )
      return new AbilityBoolFormulaVariant( pAbility, (*iCond)->condition, reinterpret_cast<NGameX::PrecompiledTooltipVariantParameters*>(prms) );

  NI_VERIFY( pOwner->GetWorld() && pOwner->GetWorld()->GetAIWorld(), "ConditionsResolver : World is invalid!", return NULL; )
    const NDb::AILogicParameters& aiParams = pOwner->GetWorld()->GetAIWorld()->GetAIParameters();

  for ( vector<NDb::Ptr<NDb::ConditionFormula>>::const_iterator iCond = aiParams.conditionFormulas.begin(), iEnd = aiParams.conditionFormulas.end(); iCond != iEnd; ++iCond )
    if ( (*iCond)->name == name )
      return new AbilityBoolFormulaVariant( pAbility, (*iCond)->condition, reinterpret_cast<NGameX::PrecompiledTooltipVariantParameters*>(prms) );

  NI_ALWAYS_ASSERT( NStr::StrFmt("Condition '%s' not found in vector 'conditionFormulas' in ability %s nor GameLogic/AILogic.AIPL!", name, pAbility->GetDBDesc()->GetDBID().GetFileName().c_str() ) );

  return NULL;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// cooldown
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NNameMap::Variant* CreateCooldownTimeVariable(PFAbilityData* pAbility, const NGameX::PrecompiledTooltipVariantParameters* pPrms)
{
  return new AbilityFloatFormulaVariant( pAbility, pAbility->GetDBDesc()->cooldownTime,
                                          pAbility->GetDBDesc()->cooldownTimeSecondState, NDb::ABILITYMODMODE_COOLDOWN, pPrms );
}


NAMEMAP_BEGIN(PFAbilityData)
  NAMEMAP_CUSTOM_SUBMAP(unit, pOwner, pOwner)
  NAMEMAP_CUSTOM_SUBMAP(const, &constResolver, &constResolver)
  NAMEMAP_VAR_RO(manaCost)
  NAMEMAP_CUSTOM_VARIANT(cooldown, CreateCooldownTimeVariable(this, reinterpret_cast<const NGameX::PrecompiledTooltipVariantParameters*>(prms)), true)
  NAMEMAP_VAR_RO(rank)
  NAMEMAP_VAR_RO(zzCost)
  NAMEMAP_FUNC_RO(abilityName, &PFAbilityData::GetAbilityName)
  NAMEMAP_FUNC_RO(name, &PFAbilityData::GetAbilityName)      
  NAMEMAP_CUSTOM_SUBMAP(if, &condsResolver, &condsResolver)
  NAMEMAP_FUNC_RO(castLimit, &PFAbilityData::IsCastSelfLimitationPassed)
  NAMEMAP_FUNC_RO(spendsLife, &PFAbilityData::DoesSpendLifeInsteadEnergy)
NAMEMAP_END;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFAbilityConstantsMap
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

PFAbilityConstantsMap::PFAbilityConstantsMap( CPtr<PFAbilityData> const& pAbility, const NDb::Ability* pDBDesc )
: pAbility(pAbility)
{
  const NDb::UnitConstantsContainer* pConstants = pDBDesc->constants.GetPtr();
  if ( pConstants )
  {
    for ( vector<NDb::Ptr<NDb::UnitConstant>>::const_iterator iConst = pConstants->vars.begin(), iEnd = pConstants->vars.end(); iConst != iEnd; ++iConst )
    {
      NI_VERIFY( *iConst, NStr::StrFmt( "Constants container in unit '%s' contains uninitialized constant!", pDBDesc->GetDBID().GetFileName() ), continue; );
      NI_ASSERT( constMap.end() == constMap.find((*iConst)->name), NStr::StrFmt( "Duplicated constant '%s' in unit '%s'", (*iConst)->name, pDBDesc->GetDBID().GetFileName() ) );
      constMap[(*iConst)->name] = (*iConst);
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NDb::UnitConstant const* PFAbilityConstantsMap::Get(const char *name) const
{
  //@iA@TODO: There is a random hangup in the hash_map::find() function, during playtesting in release configuration; 
  //At least one case detected at trunk revision 12599
  ConstMap::const_iterator iConst = constMap.find(name);
  if ( iConst != constMap.end() )
    return iConst->second;

  NI_ASSERT(IsValid(pAbility->GetOwner()), "Ability owner isn't valid");
  NI_VERIFY(pAbility->GetOwner()->GetWorld() != NULL, "Ability owner has NULL world reference inside.", return NULL;);
  NI_VERIFY(pAbility->GetOwner()->GetWorld()->GetAIWorld() != NULL, "Ability owner has NULL AI world reference inside.", return NULL;);
	const vector<NDb::Ptr<NDb::UnitConstant>>& glob = pAbility->GetOwner()->GetWorld()->GetAIWorld()->GetAIParameters().globalConstants->vars;
  for( vector<NDb::Ptr<NDb::UnitConstant>>::const_iterator iConst = glob.begin(), iEnd = glob.end(); iConst != iEnd; ++iConst )
    if ( (*iConst) && (*iConst)->name == name )
      return (*iConst).GetPtr();

  return NULL;
}


} //namespace NWorld