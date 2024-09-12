#pragma once

#include "../System/NameMap.h"
#include "PFWorldObjectBase.h"


class DiAnimGraph;

namespace NNameMap
{
  extern const wstring wstrNoname;
  extern const string strNoname;
}

namespace EAbilityState
{
  enum Enum
  {
    First = 0,
    Second,
    _Count,
  };
}

namespace NWorld
{

enum ELookKind
{
  DontLook,
  Turn,
  TurnInstantly,
};

class PFWorld;
class PFBaseUnit;
class PFAbilityInstance;
class PFAbilityConstantsMap;
class Target;
class AbilityTarget;
class PFAbilityData;
class PFSingleTargetSelector;
class PFTalent;
class PFBaseMaleHero;
class PFBaseUnitEventListener;

struct ITargetCondition;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFAbilityData
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PFAbilityData : public PFWorldObjectBase, public NNameMap::Map, public IMiscFormulaPars
{
  WORLD_OBJECT_METHODS(0x0F66F440, PFAbilityData);
  NAMEMAP_DECLARE;

  friend class PFConsumable; // for access to ResolveNameByMacro
  friend CObj<PFTalent> CreatePortalTalent( CPtr<PFBaseMaleHero> const& );

  typedef vector<CPtr<PFAbilityInstance>> InstancesVec;

public:
  PFAbilityData( CPtr<PFBaseUnit> const& pOwner, NDb::Ptr<NDb::Ability> const& pDBDesc, NDb::EAbilityTypeId abilityType, bool needRegisterInWorld = true, bool isInteractionAbility = false );

  NDb::CastLimitation const* CheckCastLimitations( const Target& target ) const;
	virtual bool NeedToBeStepped() { return false; }

  void                            ApplyPassivePart(bool bApply = true);
  bool                            HasPassiveInstance() { return pPassiveInstance;}
  virtual CObj<PFAbilityInstance> ApplyToTarget( Target const& target );
	bool                            FindAutoTarget(Target & target);
	bool                            FindMicroAITarget(Target & target);
  bool                            FindMicroAITargetTemp(Target & target) const;
  bool                            FindMicroAITargetTemp(Target & target, const ITargetCondition& condition) const;
  
  void                            CancelAbility();
  void                            CancelActiveInstances();
  const InstancesVec&             GetActiveInstances() const { return rgInstances; }

  int                             GetActiveInstancesCount() const;
  
  void                            SetRank( int _rank ) { rank = _rank; }
  void                            AddForbid( const PFBaseApplicator* pAppl = 0 );
  void                            RemoveForbid();
  void                            LevelUp();

  // fullUpdate = true  means full update: cooldown, active and passive parts, etc
  // fullUpdate = false means cooldown update only
  virtual void                    Update(float dt, bool fullUpdate);

  CObj<PFAbilityInstance>         Toggle( Target const& target );
  bool                            IsOn() const { return isOn; }
  void                            SwitchOff();
  void                            SwitchOn();

  void                            SetState(EAbilityState::Enum _abilityState) { abilityState = _abilityState; }
  EAbilityState::Enum             GetState() const { return abilityState; }
  bool                            IsSecondState() const { return abilityState == EAbilityState::Second; }

  bool                            IsReady() const;
  bool                            IsEnoughMana() const;
  bool                            IsForbidded() const { return forbids > 0; }
  bool const &                    IsCastSelfLimitationPassed() const { return castSelfLimitationPassed; }
  virtual bool                    CanBeUsed() const;
  bool                            IsInstaCast() const;
  bool                            IsAbilitySupposedToStopUnit() const;
  bool                            IsAbilitySupposedToSyncVisual() const;
  virtual void                    RestartCooldown(float cooldownTime_ = -1);
  void                            RecalculateAndRestartCooldown();

  NDb::EAbilityType               GetType() const { return pDBDesc->type; } 
	NDb::ESpellTarget               GetTargetType() const { return pDBDesc->targetType; }
  float                           GetAOEHeight() const { return pDBDesc->aoeHeight; }
  int                             GetRank() const { return rank; } // Do not use this rank for applicators! (it may differs with rank from PFAbilityInstance)
  float                           GetBaseManaCost() const;
  float                           GetManaCost() const { return manaCost; }
  float const &                   GetManaCostRef() const { return manaCost; }
  float                           GetCooldown() const { return cooldownTime[abilityState]; }
  float                           GetCurrentCooldown() const { return cooldown[abilityState]; }
  float                           GetUseRange() const;
  float                           GetUseRange(const PFBaseUnit * pTarget) const;
  float                           GetUseRange(const NWorld::Target & target) const;
  NDb::AlternativeTarget const*   GetAlternativeTarget( Target const& origTarget, const bool bFromMinimap, Target& newTarget ) const;
  bool                            IsInteractionAbility() const { return isInteractionAbility; }
  void                            SpendMana() const;
  bool                            DoesSpendLifeInsteadEnergy() const;
  bool                            IsActiveCustomTrigger() const;
  bool                            DoesApplyToDead() const;

  virtual int                     GetTalentRarity() const { return -1; }

  void                            SetZZCost( int _zzCost ) { zzCost = _zzCost; }

  CPtr<PFBaseUnit> const&         GetOwner() const { return pOwner; }
  NDb::Ability const*             GetDBDesc() const { return pDBDesc; }
  NDb::UnitConstant const*        GetConstant(char const *name) const;
  wstring const&                  GetAbilityName() const;
  bool                            IsActive() const;
  bool                            IsSingleTarget() const;
  bool                            IsAutoAttack() const { return GetAbilityTypeId() == NDb::ABILITYTYPEID_BASEATTACK; }
  virtual bool                    IsMelee() const { return false; }
  bool                            IsMultiState() const;
  
  NDb::EAbilityTypeId             GetAbilityTypeId() const { return abilityType; }
  const char*                     GetAbilityNode()   const;
  const char*                     GetAbilityMarker() const;

  bool                            GetEventTypeByAbilityTypeId( NDb::EBaseUnitEvent& eventType );
  
  virtual float                   GetWorkTime() const;
  virtual float                   GetSpeed() const;
  float                           GetTimeOffset( bool getRawTime = false ) const;

  unsigned                        GetFlags() const;
  float                           GetAoeSize() const;

  // ~~~ Cooldown ~~~
  void                            DropCooldown(bool forAllStates, float cooldownReduction = 0.0f, bool reduceByPercent = false);
  float                           GetPreparedness() const;

  // For formulas
  float                           GetModifiedValue(float value, NDb::EAbilityModMode mode) const;
  float                           CalcParam(const char *name, IUnitFormulaPars const *pSender, IUnitFormulaPars const* pReceiver, IMiscFormulaPars const* pMisc) const;
  virtual float                   GetScale() const;

  // For PFAbilityInstance
  void                            OnAbilityInstanceRemoved( PFAbilityInstance const* pInstance );
  void                            RemoveApplicatorsFrom(CPtr<PFBaseUnit> const& pUnit) const;
  void                            OnDispatchStarted() const;
  bool                            IsTargetValid( Target const& target, bool bAllowDead = false ) const;
  virtual void                    NotifyCastProcessed() {}
  virtual void                    PlayAck( const PFBaseHero* pAuxAckRecipient ) const {}

  static bool IsAbilitySuitable( NDb::Ability const* pAbilityData, vector<NDb::Ptr<NDb::Ability>> const& dbAbilities, NDb::EUseMode mode );

  void                            SubscribeChanneling( PFBaseUnitEventListener *pListener );
  void                            UnsubscribeChanneling( PFBaseUnitEventListener *pListener );

protected:
  PFAbilityData();
  
  void  UpdateAbilityModifiers();
  void  RecalculateManaCost();
  void  RecalculateCooldown();

  void  AddInstance(CObj<PFAbilityInstance> const& inst);

	NScene::SceneObject* GetSO( bool& needDelete ) const;
	::DiAnimGraph* GetAG( NScene::SceneObject* so ) const;

private:

	float GetAttackTimeOffset() const;
	float GetMarkerPlace( NScene::SceneObject* pSO, const nstl::string &nodeName, const nstl::string &markerName ) const;
  void DropCooldown(EAbilityState::Enum forAbilityState, float cooldownReduction, bool reduceByPercent);
  // ~~~ NameMaps stuff ~~~
  struct ConstantsResolver : NNameMap::Map
  {
    NAMEMAP_DECLARE;
    virtual NNameMap::Variant * ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly );
  public:
		ConstantsResolver() : pAbility(0) {}
    void Init(PFAbilityData const* pAbility_);
  private:
    PFAbilityData const* pAbility;
  };
  struct ConditionsResolver : NNameMap::Map
  {
    NAMEMAP_DECLARE;
    virtual NNameMap::Variant * ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly );
  public:
		ConditionsResolver() : pAbility(0) {}
    void Init(PFAbilityData const* pAbility_);
  private:
    PFAbilityData const* pAbility;
  };
  ConstantsResolver             constResolver;
  ConditionsResolver            condsResolver;
  AutoPtr<PFAbilityConstantsMap>pConstantsMap; //TODOLOF

  // ~~~
  friend class PFAbilityInstance;
  
  struct Modifier {
    inline Modifier() { clear(); }
    inline void clear() { add=0.0f; mul=1.0f;  }
    float add, mul;
  };

  typedef StaticArray<float, EAbilityState::_Count> TCooldown;
  typedef StaticArray<Modifier, NDb::KnownEnum<NDb::EAbilityModMode>::sizeOf> ModifiersArray;
  
  PFMicroAI* CreateMicroAI() const;

  bool                          isInPassivePartUpdate; // No need to serialize this field
  static int                    baseRefineRate;

  ZDATA_(PFWorldObjectBase)
  ZNOPARENT(NNameMap::Map)
  ZNOPARENT(IMiscFormulaPars)
  NDb::Ptr<NDb::Ability>        pDBDesc;
  NDb::EAbilityTypeId           abilityType;
  CObj<PFAbilityInstance>       pPassiveInstance;
  InstancesVec                  rgInstances;
  CPtr<PFBaseUnit>              pOwner;
  int                           rank;
  TCooldown                     cooldownTime;
  TCooldown                     cooldown;
  float                         manaCost;
  int                           zzCost;
  bool                          isOn;
  int                           forbids;
  CObj<PFSingleTargetSelector>  pAutoTargetSelector;
  CObj<PFMicroAI>               pMicroAI;
  bool                          castSelfLimitationPassed;
  bool                          isInteractionAbility;
  EAbilityState::Enum           abilityState;

  // Ability modifiers cache
  mutable ModifiersArray modifiers;
  mutable float cachedModifiersTime;

  list<CObj<PFBaseUnitEventListener>> channelings;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&pDBDesc); f.Add(3,&abilityType); f.Add(4,&pPassiveInstance); f.Add(5,&rgInstances); f.Add(6,&pOwner); f.Add(7,&rank); f.Add(8,&cooldownTime); f.Add(9,&cooldown); f.Add(10,&manaCost); f.Add(11,&zzCost); f.Add(12,&isOn); f.Add(13,&forbids); f.Add(14,&pAutoTargetSelector); f.Add(15,&pMicroAI); f.Add(16,&castSelfLimitationPassed); f.Add(17,&isInteractionAbility); f.Add(18,&abilityState); f.Add(19,&modifiers); f.Add(20,&cachedModifiersTime); f.Add(21,&channelings); return 0; }

  virtual int  GetRefineRate()       const { return 0;     }
  virtual float GetRefineAbilityScale( float valueAtRefineLevel0, float valueAtRefineLevel6 ) const;
  virtual int  GetTalentLevel()      const { return 0;     }
  virtual int  GetTalentDevPoints()  const { return 0;     }
  virtual int  GetNaftaCost()        const { return 0;     }
  virtual bool IsTalentBought()      const { return false; }
  virtual float GetAbilityScale( bool isDamage, float statValue, EAbilityScaleMode abScaleMode, float valueLeft, float valueRight, bool bRound = true ) const;
  virtual bool  GetSmartRoll( float probability, int maxFailReps, int maxSuccessReps, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const;
  virtual int   GetSmartRandom( int outcomesNumber, float probDecrement, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const;
  virtual int   GetAlternativeTargetIndex() const { return -1; }
  virtual float GetTerrainPart(int faction) const;
  virtual int   GetActivatedWithinKit() const;
  virtual int   GetTalentsWithinKit() const;
  virtual float GetStatusDispellPriority( const IUnitFormulaPars* pUnitToCheck, bool returnDuration ) const;
  virtual CVec2 GetVectorVariable(const char *name) const { return VNULL2; }

  virtual int GetTerrianTypeUnderCursor() const;
  virtual int GetNatureTypeInPos(CVec2 pos) const;


	virtual void Reset();

protected:
  virtual bool  IsAbilityOn() const { return IsOn(); }
  virtual float GetDist2Target() const;
  virtual float GetParentScale() const;
  virtual int   GetAbilityType() const;
  virtual int   GetScrollLevel() const;
  virtual bool  IsNight() const;
  virtual const IUnitFormulaPars* GetObjectOwner() const;
  virtual bool  Roll(float /*probability*/) const;
  virtual int   GetRandom(int , int ) const;
  virtual float GetConstant(const char *name, IUnitFormulaPars const *pSender, IUnitFormulaPars const* pReceiver) const;
  virtual int   GetTerrainType() const { return 0; }
  virtual const IMiscFormulaPars* GetObjectParent() const { return this; }
  virtual float GetVariable(const char *) const { return 0.0f; }
  virtual const IUnitFormulaPars* GetObject( char const*) const {return NULL;}
  virtual CVec2 GetTargetPos() const { NI_ALWAYS_ASSERT("Undefined"); return VNULL2; }
  virtual bool  CheckUpgradePerCastPerTarget() const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFConsumableAbilityData : public PFAbilityData
{
  WORLD_OBJECT_METHODS(0xE791C400, PFConsumableAbilityData);

public:
  PFConsumableAbilityData( CPtr<PFBaseUnit> const& pOwner_, NDb::Ptr<NDb::Ability> const& pDBDesc, NDb::EAbilityTypeId abilityType, bool needRegisterInWorld = true, bool = false );
  void SetUsingConsumable( PFConsumable* pConsumable ) { pUsingConsumable = pConsumable; }
  virtual void NotifyCastProcessed();
  virtual void RestartCooldown( float cooldownTime_ );
  PFBaseHero* GetOwner() { return pOwner; }
  CPtr<PFConsumable> const& GetUsingConsumable() const {return pUsingConsumable; }
  NDb::ConsumableGroup const* GetGroup() const { return pDBGroup; }
  void SetGroup( NDb::ConsumableGroup const* pDBGroup_ ) { pDBGroup = pDBGroup_; }
private:
  PFConsumableAbilityData() : PFAbilityData(), pDBGroup(0) {}
  NDb::ConsumableGroup const* pDBGroup; // do not need to be serialized
  ZDATA_(PFAbilityData)
  CPtr<PFBaseHero> pOwner;
  CPtr<PFConsumable> pUsingConsumable;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFAbilityData*)this); f.Add(2,&pOwner); f.Add(3,&pUsingConsumable); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// PFAbilityConstantsMap
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class PFAbilityConstantsMap
{
public:
  PFAbilityConstantsMap( CPtr<PFAbilityData> const& pAbility, const NDb::Ability* pDBDesc );
  NDb::UnitConstant const* Get(const char *name) const;
private:
  typedef nstl::hash_map<string, NDb::Ptr<NDb::UnitConstant>> ConstMap;
  ConstMap            constMap;
  CPtr<PFAbilityData> pAbility;
};

//////////////////////////////////////////////////////////////////////////
inline void PFAbilityData::RemoveForbid()
{
  NI_VERIFY( forbids > 0, NStr::StrFmt( "Can't unforbid talent %s: is not currently forbidded!", GetAbilityName() ), return );
  forbids--;
}
inline wstring const& PFAbilityData::GetAbilityName() const
{
  return pDBDesc ? pDBDesc->name.GetText() : NNameMap::wstrNoname;
}
inline bool PFAbilityData::IsActive() const
{
  return pDBDesc->type == NDb::ABILITYTYPE_ACTIVE || pDBDesc->type == NDb::ABILITYTYPE_MULTIACTIVE || pDBDesc->type == NDb::ABILITYTYPE_CHANNELLING || pDBDesc->type == NDb::ABILITYTYPE_SWITCHABLE;
}
inline bool PFAbilityData::IsSingleTarget() const
{
  return IsActive() && pDBDesc->targetType != 0;
}
inline float PFAbilityData::GetPreparedness() const
{
  return ( cooldown[abilityState] > 0 ) && ( cooldownTime[abilityState] > 0 ) ? ( cooldownTime[abilityState] - min( cooldown[abilityState], cooldownTime[abilityState] ) ) / cooldownTime[abilityState] : 1.0f;
}
inline int PFAbilityData::GetActiveInstancesCount() const 
{
  return rgInstances.size();
}
inline const char* PFAbilityData::GetAbilityNode() const
{
  return pDBDesc->node.c_str();
}
inline const char* PFAbilityData::GetAbilityMarker() const
{
  return pDBDesc->marker.c_str();
}
inline bool PFAbilityData::IsMultiState() const
{
  return GetType() == NDb::ABILITYTYPE_SWITCHABLE || GetType() == NDb::ABILITYTYPE_MULTIACTIVE;
}

//////////////////////////////////////////////////////////////////////////
inline void PFAbilityData::ConstantsResolver::Init(PFAbilityData const* pAbility_)
{
  pAbility = pAbility_;
}
inline void PFAbilityData::ConditionsResolver::Init(PFAbilityData const* pAbility_)
{
  pAbility = pAbility_;
}

} //namespace NWorld
