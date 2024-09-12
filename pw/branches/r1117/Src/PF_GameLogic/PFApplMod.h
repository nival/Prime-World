#pragma once

#include "DBGameLogic.h"

#include "PFApplBuff.h"
#include "PFBaseUnitEvent.h"
#include "ValueWithModifiers.hpp"

#include "ClientVisibilityFlags.hpp"

#include <stack>

namespace NDb
{
struct UnitTargetingParameters;
}

namespace NWorld
{

class PFWorld;
class PFBaseUnit;
class PFBaseBehaviour;
class PFBaseAttackData;
class PFBaseMaleHero;
class PFBaseHero;
class PFAbilityData;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplStatMod : public DBLinker<PFApplBuff, NDb::StatModApplicator>
{
  WORLD_OBJECT_METHODS(0xE5CC382, PFApplStatMod);

  ZDATA_(DBLinker)
  int modifierID;
  float mul;
  float add;
  float statModConstant;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&modifierID); f.Add(3,&mul); f.Add(4,&add); f.Add(5,&statModConstant); return 0; }
  
  PFApplStatMod(PFApplCreatePars const &cp) : Base(cp), modifierID(INVALID_MODIFIER_ID), mul(1.0), add(0.0), statModConstant(0.0f), pStat(0) {}
  PFApplStatMod() : pStat(0) {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  virtual void Reset();
  virtual float GetVariable(const char* sVariableName) const;

  string const& GetStatModName() const;

  bool GetStatModConstant( float& value ) const;

protected:
  virtual bool Start();
  virtual void Enable();
  virtual void Disable();
  virtual void DumpInfo(NLogg::CChannelLogger &logger) const;
  virtual bool Step(float dtInSeconds);
  virtual float GetAbsModification();

  friend class PFApplStatus;  // PFApplStatus must be able to control PFApplStatMod via Disable/Enable

  ValueWithModifiers* pStat; //TODOLOF
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplPermanentStatMod : public DBLinker<PFBaseApplicator, NDb::PermanentStatModApplicator>
{
	WORLD_OBJECT_METHODS(0x9E688C01, PFApplPermanentStatMod);

	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFApplPermanentStatMod(PFApplCreatePars const &cp) : Base(cp) {}
	PFApplPermanentStatMod() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
	virtual bool Start();
	virtual void DumpInfo(NLogg::CChannelLogger &logger) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplAbilityMod : public DBLinker<PFApplBuff, NDb::AbilityModApplicator>
{
  WORLD_OBJECT_METHODS(0xF6BCC80, PFApplAbilityMod);

  ZDATA_(DBLinker)
  float cachedAdd;
  float cachedMul;
  int talCdAddModifierId;
  int talCdMulModifierId;
  int talMcAddModifierId;
  int talMcMulModifierId;
  CPtr<PFBaseHero> pHero;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&cachedAdd); f.Add(3,&cachedMul); f.Add(4,&talCdAddModifierId); f.Add(5,&talCdMulModifierId); f.Add(6,&talMcAddModifierId); f.Add(7,&talMcMulModifierId); f.Add(8,&pHero); return 0; }

  PFApplAbilityMod(PFApplCreatePars const &cp) : Base(cp), cachedAdd(0.0f), cachedMul(1.0f), talCdAddModifierId(INVALID_MODIFIER_ID), talCdMulModifierId(INVALID_MODIFIER_ID), talMcAddModifierId(INVALID_MODIFIER_ID), talMcMulModifierId(INVALID_MODIFIER_ID), pTalCdAddVar(0), pTalMcAddVar(0) {}
  PFApplAbilityMod() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  virtual void Reset();

  NDb::EAbilityModMode GetMode() const { return GetDB().mode; }
  bool IsApplicable(NDb::EAbilityModMode mode, NDb::EAbilityTypeId abilityType, NDb::Ptr<NDb::Ability> const& dbAbility);
  void AddModifier(float& add, float& mul, NDb::EAbilityModMode mode, NDb::EAbilityTypeId abilityType, NDb::Ptr<NDb::Ability> const& dbAbility );
  
  seDECLARE_CPTRRING_CLASS(PFApplAbilityMod, abilityModRing, Ring);

protected:
  virtual bool Start();
  virtual void Enable();
  virtual void Disable();
  virtual void DumpInfo(NLogg::CChannelLogger &logger) const;
  virtual bool Step(float dtInSeconds);

  void CheckCachedValues();

  ValueWithModifiers* pTalCdAddVar;
  ValueWithModifiers* pTalCdMulVar;
  ValueWithModifiers* pTalMcAddVar;
  ValueWithModifiers* pTalMcMulVar;

private:
  Ring::Part abilityModRing;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplAbilityUpgrade : public DBLinker<PFApplBuff, NDb::AbilityUpgradeApplicator>
{
  typedef nstl::vector<nstl::pair<int, int>> TalentLastUseRecordVector;

  WORLD_OBJECT_METHODS(0xF6C0C80, PFApplAbilityUpgrade);

  ZDATA_(DBLinker);
  int appliesCount;
  int maxCount;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&appliesCount); f.Add(3,&maxCount); return 0; }

  PFApplAbilityUpgrade(PFApplCreatePars const &cp) : Base(cp), appliesCount(0), maxCount(0) {}
  PFApplAbilityUpgrade() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  void UpgradeAbilityApplicators( CPtr<PFAbilityData> const& abilityData, vector<NDb::Ptr<NDb::BaseApplicator>>& applicators, vector<NDb::Ptr<NDb::BaseApplicator>>& persistentApplicators, bool& useOriginal );

  seDECLARE_CPTRRING_CLASS(PFApplAbilityUpgrade, upgradesRing, Ring);

protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds);
  virtual void Enable();
  virtual void Disable();
  virtual void DumpInfo(NLogg::CChannelLogger &logger) const;
  inline bool CheckAppliesCount() const { return (maxCount <= 0 || appliesCount < maxCount); }
private:
  Ring::Part upgradesRing;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplTechAbilityUpgrade : public DBLinker<PFBaseApplicator, NDb::AbilityUpgradeTechApplicator>
{
  WORLD_OBJECT_METHODS(0x15DC6041, PFApplTechAbilityUpgrade);
public:
  PFApplTechAbilityUpgrade(const PFApplCreatePars& cp);
  PFApplTechAbilityUpgrade();
  virtual ~PFApplTechAbilityUpgrade();

  virtual bool Start();
private:
  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplStatus : public DBLinker<PFApplBuff, NDb::StatusApplicator>
{
	WORLD_OBJECT_METHODS(0x9E688BC1, PFApplStatus);
public:
  typedef nstl::list< CPtr<NWorld::PFApplStatus> >   TApplStatuses;
  typedef nstl::list< CPtr<NWorld::PFBaseApplicator> >   TApplicators;

private:
	ZDATA_(DBLinker)
  int   m_applicatorCount;
  bool  m_isComparableByValue;
  TApplStatuses blockApplicators;
  TApplStatuses blockedByApplicators;
  TApplStatuses mergeApplicators;
  TApplicators  childApplicators;
  bool bStarted;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&m_applicatorCount); f.Add(3,&m_isComparableByValue); f.Add(4,&blockApplicators); f.Add(5,&blockedByApplicators); f.Add(6,&mergeApplicators); f.Add(7,&childApplicators); f.Add(8,&bStarted); return 0; }

  seDECLARE_COBJRING_CLASS(PFApplStatus, activeStatusesPart, ActiveStatusRing);

	PFApplStatus(PFApplCreatePars const &cp) : Base(cp), m_applicatorCount(0), m_isComparableByValue(true), bStarted(false) {}
	PFApplStatus() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  void ForceUpdateLifetime( float newLifetime, float newDuration );
	virtual const NDb::Texture* GetStatusImage() const;

  bool IsComparableByValue() const { return m_isComparableByValue; };
  void GetChildrenStatMods( vector<PFApplStatMod const*>& statModContainer, bool activeOnly = false ) const;

  virtual void OnChildApplicatorCreated(CObj<PFBaseApplicator> & childApplicator)
  {
    if (childApplicator)
    {
      childApplicators.push_back(childApplicator.GetPtr());
    }
  }

  virtual float GetModifiedDuration(float original) const;

protected:
	virtual bool Start();
	virtual void Enable();
	virtual void Disable();
  virtual bool Step(float dtInSeconds);
  virtual void Stop();
  virtual void OnNotification(PFBaseApplicator &appl, NDb::EParentNotification note);

  virtual void CompareByPower(PFApplStatus * pSecond);
  virtual void MergeByValue();
private:
  ActiveStatusRing::Part activeStatusesPart;
public:
  template <class R, class F> static void ForallRing(R &applicators, F &f)
  {
    R processed;
    while (!applicators.empty())
    {
      PFApplStatus *app = applicators.first();
      CObj<PFApplStatus> applObj(app);
      R::remove(app);
      processed.addLast(app);

      f(applObj);
    }
    while (!processed.empty())
    {
      PFApplStatus *app = processed.first();
      CObj<PFApplStatus> applObj(app);
      R::remove(app);
      applicators.addLast(app);
    }
  }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplFlags : public DBLinker<PFApplBuff, NDb::FlagsApplicator>
{
  WORLD_OBJECT_METHODS(0xE5CC389, PFApplFlags);

  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
  
  PFApplFlags(PFApplCreatePars const &cp) : Base(cp) {}
  PFApplFlags() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
  virtual void Reset();
protected:
  virtual void Enable();
  virtual void Disable();
	virtual void DumpInfo(NLogg::CChannelLogger &logger) const;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplChangeBaseAttack : public DBLinker<PFApplBuff, NDb::ChangeBaseAttackApplicator>
{
	WORLD_OBJECT_METHODS(0x9E678B00, PFApplChangeBaseAttack);

	ZDATA_(DBLinker)
	CObj<PFBaseAttackData> pSavedBaseAttack;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pSavedBaseAttack); return 0; }

	PFApplChangeBaseAttack(PFApplCreatePars const &cp) : Base(cp) {}
	PFApplChangeBaseAttack() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
protected:
	virtual void Enable();
	virtual void Disable();

	virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
	virtual bool IsStackableWithTheSameType() const { return false; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplCreepBehaviourChange : public DBLinker<PFApplBuff, NDb::CreepBehaviourChangeApplicator>
{
	WORLD_OBJECT_METHODS(0x9E677A80, PFApplCreepBehaviourChange);
	ZDATA_(DBLinker)
	CObj<PFBaseBehaviour> pBehaviour;
  NDb::Ptr<NDb::UnitTargetingParameters> oldTargetingParams;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pBehaviour); f.Add(3,&oldTargetingParams); return 0; }

	PFApplCreepBehaviourChange(PFApplCreatePars const &cp) : Base(cp) {}
	PFApplCreepBehaviourChange() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
protected:
	virtual void Enable();
	virtual void Disable();

	virtual bool IsStackableWithTheSameType() const;
	virtual int  GetAcceptableUnitTypeFlags() const 
	{ 
    return NDb::SPELLTARGET_CREEP | NDb::SPELLTARGET_SIEGECREEP | NDb::SPELLTARGET_SUMMON | NDb::SPELLTARGET_ALLNEUTRALS | NDb::SPELLTARGET_FACTIONCHAMPION; 
	}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplDamageReflect: public DBLinker<PFApplBuff, NDb::DamageReflectApplicator>
{
  WORLD_OBJECT_METHODS(0xE5CC392, PFApplDamageReflect);
  ZDATA_(DBLinker)
  float amountInPersent;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&amountInPersent); return 0; }

  PFApplDamageReflect(PFApplCreatePars const &cp)
    : Base(cp), amountInPersent(GetDB().amountInPersent) {}
  PFApplDamageReflect() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
protected:
  virtual float OnDamage(CPtr<PFBaseUnit> pSender, float damageInput, float damage4Apply, int damageType);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplOnDamage : public DBLinker<PFApplBuff, NDb::OnDamageApplicator>, public PFBaseUnitEventListener
{
  WORLD_OBJECT_METHODS(0xE5CC390, PFApplOnDamage);
  ZDATA_(DBLinker)
  ZNOPARENT(PFBaseUnitEventListener)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }
  
  PFApplOnDamage(PFApplCreatePars const &cp) : Base(cp) {}
  PFApplOnDamage() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
protected:
	virtual void Enable();
	virtual void Disable();
	virtual unsigned int OnEvent(const PFBaseUnitEvent *pEvent);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplInvisibility : public DBLinker<PFApplBuff, NDb::InvisibilityApplicator>, public PFBaseUnitEventListener
{
  enum State
  {
    FADEIN,
    INVISIBLE,
    CANCEL,
  };

  WORLD_OBJECT_METHODS(0xB724A81, PFApplInvisibility);


  ZDATA_(DBLinker)
  ZNOPARENT(PFBaseUnitEventListener)
  State            state;
  float            time;
  bool             invisible;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&state); f.Add(3,&time); f.Add(4,&invisible); return 0; }

  PFApplInvisibility(PFApplCreatePars const &cp);
protected:
  PFApplInvisibility() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

  void becomeInvisible();
  void becomeVisible();

  virtual bool Start();
  virtual void Enable();
  virtual void Disable();
  virtual bool Step(float dtInSeconds);
  virtual unsigned int OnEvent(const PFBaseUnitEvent *pEvent);

private:  
  virtual void PrepareEffects( bool manualDeathTypeOnly );
  
private:
  void ApplyPartialVisibility(const bool enabled, const bool force = false);
  void DoSwitchEffects(const bool visibleForPlayer) const;
  void UpdateVisibility(const bool resetPartialVisibility = false);

  NGameX::ClientVisibilityFlags visibilityFlags; // for client purposes

  bool partialVisibilityEnabled;
  int partialVisibilityRevision;
};

class PFApplTargetsCounter : public DBLinker<PFApplBuff, NDb::TargetsCounterApplicator>
{
  WORLD_OBJECT_METHODS(0xF739D00, PFApplTargetsCounter);
  
  static const char* targetsCountVariableName;

  ZDATA_(DBLinker)
  int targetsCount;
  CObj<PFTargetSelector> targetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&targetsCount); f.Add(3,&targetSelector); return 0; }
  PFApplTargetsCounter(PFApplCreatePars const &cp) : Base(cp), targetsCount(0) {}
  PFApplTargetsCounter() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
  virtual float GetVariable(const char* varName) const;
protected:
  void EnumerateTargets();

  virtual bool Start();
  virtual bool Step(float dtInSeconds);
};

class PFApplValue : public DBLinker<PFApplBuff, NDb::ValueApplicator>
{
  WORLD_OBJECT_METHODS(0xF73D480, PFApplValue);

  ZDATA_(DBLinker)
  float value;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&value); return 0; }
  PFApplValue(PFApplCreatePars const &cp) : Base(cp), value(0) {}
  PFApplValue() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
  // Overriders
  virtual float GetVariable(const char* varName) const;
protected:
  virtual bool Start();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplMarker : public DBLinker<PFApplBuff, NDb::MarkerApplicator>
{
  WORLD_OBJECT_METHODS(0xE778BC83, PFApplMarker);

  ZDATA_(DBLinker)
  int modifierID;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&modifierID); return 0; }
  
  PFApplMarker(PFApplCreatePars const &cp) : Base(cp), modifierID(INVALID_MODIFIER_ID), pStat(0) {}
  PFApplMarker() : modifierID(INVALID_MODIFIER_ID), pStat(0) {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

	virtual void Reset();

protected:
  virtual bool Start();
  virtual void Enable();
  virtual void Disable();
  virtual float GetVariable(const char* varName) const;

  ValueWithModifiers* pStat;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplChangeHeroState : public DBLinker<PFApplBuff, NDb::ChangeHeroStateApplicator>
{
  WORLD_OBJECT_METHODS(0x22CC6D81, PFApplChangeHeroState);

  ZDATA_(DBLinker)
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFApplChangeHeroState( PFApplCreatePars const& cp) : Base( cp ) {}
  PFApplChangeHeroState() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
protected:
  virtual void Enable();
  virtual void Disable();
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplSceneObjectChange : public DBLinker<PFApplBuff, NDb::SceneObjectChangeApplicator>
{
  WORLD_OBJECT_METHODS(0x2B7B8C41, PFApplSceneObjectChange);

  ZDATA_(DBLinker)
  NDb::Ptr<NDb::DBSceneObject> oldSceneObject;
  int sceneObjectIndex;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&oldSceneObject); f.Add(3,&sceneObjectIndex); return 0; }

  PFApplSceneObjectChange( PFApplCreatePars const& cp) : Base( cp ), sceneObjectIndex(-1) {}
  PFApplSceneObjectChange() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}
protected:
  virtual bool Start();
  virtual void Enable();
  virtual void Disable();
  virtual bool Step( float dtInSeconds );

  virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }

  virtual bool NeedEnableAfterReset() const { return true; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplTaunt: public DBLinker<PFApplBuff, NDb::TauntApplicator>
{
  WORLD_OBJECT_METHODS(0xE5CC380, PFApplTaunt);
  ZDATA_(DBLinker)
  CPtr<PFBaseUnit> tauntSource;
  CVec2 lastVisiblePos;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&tauntSource); f.Add(3,&lastVisiblePos); return 0; }
  PFApplTaunt(PFApplCreatePars const &cp) : Base(cp), lastVisiblePos(VNULL2) {}
  PFApplTaunt() {/*NI_ALWAYS_ASSERT("Should be never invoked.");*/}

protected:
  virtual bool Start();
  virtual bool Step(float dtInSeconds);
  virtual void Stop();

  virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_UNIT; }
  CPtr<PFBaseUnit>& GetTauntSource(){return tauntSource;}
};

///////////////////////////////////////////////////////////////////////////////

class TauntApplicatorManager
{
  typedef nstl::vector<CObj<PFApplTaunt>> TTauntsStack;

public:
  TauntApplicatorManager(){ };
  ~TauntApplicatorManager(){ };

  static bool IsTauntApplicator(CObj<PFBaseApplicator> const& pApplicator) {
    return pApplicator->typeId == PFApplTaunt::typeId;
  };

  void AddLast(CObj<PFApplTaunt> tauntAppl)
  {
    taunts.push_back(tauntAppl);
  };

  void RemoveLast(){
    if(!taunts.empty())
      taunts.pop_back();
  }

  CObj<PFApplTaunt> GetLast(){
    if(!taunts.empty())
      return taunts.back();
    else return 0;
  }

  int GetCount(){
    return taunts.size();
  }

  bool IsItLast(CObj<PFApplTaunt> tauntAppl)
  {
    return tauntAppl == GetLast();
  }

  void clear()
  {
    taunts.clear();
  }


private:
  ZDATA
  TTauntsStack taunts;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&taunts); return 0; }
};

}