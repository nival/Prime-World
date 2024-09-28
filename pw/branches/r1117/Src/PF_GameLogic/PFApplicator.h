#ifndef PFAPPLICATION_H_INCLUDED
#define PFAPPLICATION_H_INCLUDED

#include "../System/Ring.h"
//#include "../System/LoggerBuffer.h"
#include "DBAbility.h"
#include "PFUniTarget.h"
//#include "PFAIWorld.h"
#include "PFDBLinker.h"
#include "PFAbilityInstance.h"
#include "PFAbilityData.h"
#include "../../Data/GameLogic/FormulaPars.h"
#include "System/InlineProfiler.h"
#include "../PF_Core/BasicEffect.h"

namespace NWorld
{
class PFWorld;
class PFBaseUnit;
class PFAbilityInstance;
class PFAbilityData;
class PFDispatch;

class PFBaseApplicator;
bool ActivateApplicator(CObj<PFBaseApplicator> app, CObj<PFAbilityInstance> const& pAbility);
void MemorizeApplicator(CObj<PFBaseApplicator> app);
void CreateAndActivateApplicators(const vector<NDb::Ptr<NDb::BaseApplicator>> &applicators, const CObj<PFAbilityInstance> &pAbility, 
																	Target const &target, CPtr<PFBaseApplicator> pParent);

enum ApplStopReason 	 
{ 	 
  APPL_STOP_REASON_NONE = 0, 	 
  APPL_STOP_REASON_ONDEATH, 	 
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplCreatePars : private NonCopyable
{
public:
	PFApplCreatePars(CObj<PFAbilityInstance> const& pAbility_
    , Target const &target_
    , CPtr<PFBaseApplicator> const& pParent_ = CPtr<PFBaseApplicator>()
    , PFDispatch *	pDispatch_ = 0
    , bool bPassive = false
    , PFAbilityData* pUpgraderAbilityData_ = NULL 
    , PFWorld * pWorld_ = 0)
    : pAbility(pAbility_), target(target_), pParent(pParent_), pDispatch(pDispatch_)
    , bPassive(bPassive), pUpgraderAbilityData(pUpgraderAbilityData_), pWorld(pWorld_)
	{}

	CObj<PFAbilityInstance>       pAbility;
	Target const                 &target;
	CPtr<PFBaseApplicator>        pParent;
	NDb::Ptr<NDb::BaseApplicator> pDBAppl;
	PFDispatch *									pDispatch;
  bool                          bPassive;
  PFAbilityData*                pUpgraderAbilityData;
  CPtr<PFWorld>                 pWorld;   // Optional. Useful when pAbility is NULL.
  CPtr<PFBaseUnit>              pOwner;   // Optional. Useful when pAbility is NULL.
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBaseApplicator: public PFWorldObjectBase, public IMiscFormulaPars, public PF_Core::IEffectEnableConditionCallback
{
  WORLD_OBJECT_METHODS(0xE5CC387, PFBaseApplicator);

protected:
  ZDATA_(PFWorldObjectBase)
  ZPARENT(IMiscFormulaPars)
  ZNOPARENT(PF_Core::IEffectEnableConditionCallback)
  CObj<PFBaseUnit>              pOwner;
  CObj<PFAbilityInstance>       pAbility;
	CObj<PFDispatch>              pDispatch;  // creator and holder of this ability
  CPtr<PFBaseUnit>              pReceiver;
  CPtr<PFBaseApplicator>        pParent;
	NDb::Ptr<NDb::BaseApplicator> pDBAppl;
private:
  Target                          target;
  CObj<PFAbilityData>             pUpgraderAbilityData;
protected:
	int                             flags;
  float                           markerTime;
  bool                            bPassive;
  ApplStopReason                  stopReason;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,(IMiscFormulaPars*)this); f.Add(3,&pOwner); f.Add(4,&pAbility); f.Add(5,&pDispatch); f.Add(6,&pReceiver); f.Add(7,&pParent); f.Add(8,&pDBAppl); f.Add(9,&target); f.Add(10,&pUpgraderAbilityData); f.Add(11,&flags); f.Add(12,&markerTime); f.Add(13,&bPassive); f.Add(14,&stopReason); return 0; }

	virtual bool NeedToBeStepped() { return false; }

protected:
	typedef PFApplCreatePars CreateParams;

	enum
	{
		FLAG_ENABLED      = (1 << 0),
		FLAG_STOPPED      = (1 << 1),
		FLAG_BLOCKED      = (1 << 2),
		FLAG_CHANGED      = (1 << 3),
		FLAG_DELEGATED    = (1 << 4),
		FLAG_PRIVATE_LAST = FLAG_DELEGATED,
	};

private:
  struct StepFunc
  {
    StepFunc(float dtInSeconds): dtInSeconds(dtInSeconds) {}

    void operator()(CObj<PFBaseApplicator> &applicator)
    {
      if (applicator->Step(dtInSeconds))
      {
        CObj<PFBaseApplicator> pHolder(applicator);
        applicator->Stop();
        MemorizeApplicator(pHolder);
      }
    }

    float dtInSeconds;
    unsigned int flag;
  };

public:
	enum 
	{
		FLAG_BASE_ATTACK  = FLAG_PRIVATE_LAST << 1,
		FLAG_MELEE        = FLAG_PRIVATE_LAST << 2,
		FLAG_REFLECTED    = FLAG_PRIVATE_LAST << 3,
		FLAG_PUBLIC_LAST  = FLAG_REFLECTED,
	};

	PFBaseApplicator(PFApplCreatePars const &cp);
  PFBaseApplicator();
  virtual ~PFBaseApplicator();

  seDECLARE_COBJRING_CLASS(PFBaseApplicator, appliedRingPart, AppliedRing);
  seDECLARE_COBJRING_CLASS(PFBaseApplicator, sentRingPart, SentRing);

  seDECLARE_CPTRRING_CLASS(PFBaseApplicator, namedRingPart, NamedRing);

  bool IsLinkedToAppliedRing() const {return appliedRingPart.isLinked();}
  bool IsLinkedToSentRing() const {return sentRingPart.isLinked();}

	bool IsAlive() const { return (flags & FLAG_STOPPED) == 0; }

  virtual bool Start();
	virtual bool Init(); // This function is called after constructor (use it to calculate formulas and do some vtbl related calls)
  virtual void Stop();
  virtual bool Step(float dtInSeconds);
  virtual bool CanBeAppliedOnDead() {return false;}
  virtual void OnDispatchStep( PFDispatch* ) {}
  virtual void OnDispatchTargetDropped( const PFDispatch* ) {}
  virtual void OnDispatchMissed( const PFDispatch* ) {}

  NDb::Ptr<NDb::BaseApplicator> const &GetDBBase() const;

  virtual string const& GetApplicatorName() const;

  // Method is called on changing of external parameters to reevaluate formulas
  virtual void  Recalculate();

  // Logs info
  virtual void DumpInfo( NLogg::CChannelLogger & logger ) const;
  static bool CheckDamageTypeFilter( int flags, int damageType, NDb::EDamageFilter filterFlags, bool enableReflected );

  // Return true, if applicator must be stopped on targets death
  virtual bool NeedToStopOnDeath() const { return true; }
  virtual bool NeedToStopOnSenderDeath() const { return true; }
  virtual bool NeedToDisableOnDeath() const { return true; }

  virtual bool GetRemainingLifeTime(float &time) const { return false; }

  const CObj<PFAbilityInstance>& GetAbility() const { return pAbility; }
  const PFAbilityData* GetAbilityData() const { return pUpgraderAbilityData ? pUpgraderAbilityData : ( pAbility ? pAbility->GetData() : 0 ); }

  void AddFlags(int f) { flags |= f; }
  int  GetFlags() const { return flags; }

  bool IsEnabled() const { return (flags & FLAG_ENABLED) != 0; }
  bool IsBlocked() const { return (flags & FLAG_BLOCKED) != 0; }
  bool IsChanged() const { return (flags & FLAG_CHANGED) != 0; }
  bool IsDelegated() const { return (flags & FLAG_DELEGATED) != 0; }
  void SetEnabled(bool isEnabled);
  void SetBlocked(bool isBlocked);
  void SetChanged(bool isChanged);

	const CPtr<PFBaseUnit>& GetReceiver() const { return pReceiver; }

	CPtr<PFBaseUnit> GetAbilityOwner() const;
  const Target&    GetTarget() const { return target; }
  void SetTarget(const Target &target_) { target = target_; }

	const CPtr<PFBaseApplicator>& GetParentAppl() const { return pParent; }

	const CObj<PFDispatch>& GetDispatch() const;

  const CObj<PFAbilityData>& GetUpgraderAbilityData() const { return pUpgraderAbilityData; }
  NDb::UnitConstant const* GetConstant( const char *name ) const;

  //from IMiscFormulaPars
  virtual const IUnitFormulaPars* GetObjectOwner()  const {return NULL;}
  virtual const IUnitFormulaPars* GetObject( char const* objName ) const;
  CVec2 GetTargetPos(void) const; 
  
	void MakeApplicationTarget(Target &targ, NDb::EApplicatorApplyTarget applyTarget) const;
	void MakeApplicationTarget(Target &targ) const { MakeApplicationTarget(targ, pDBAppl->applyTarget); }
	CVec3 AcquireApplicationPosition() const;

	int  MakeSpellTargetFactionFlags(NDb::ESpellTarget spellTarget) const;

	virtual void OnNotification(PFBaseApplicator &appl, NDb::EParentNotification /*note*/) {}
  inline void NotifyParent(NDb::EParentNotification note) { if (IsValid(pParent)) pParent->OnNotification(*this, note); }

  float GetMarkerTime() const { return markerTime; }
  void SetMarkerTime(float deathTime_) { markerTime = deathTime_; }

	virtual const NDb::Texture* GetStatusImage() const { return 0; }

  virtual float GetVariable(const char *) const { return 0.0f; }

  void RemoveFromAppliedRing()
  {
    AppliedRing::remove(this);
  }

  void RemoveFromSentRing()
  {
    SentRing::remove(this);
  }

  void RemoveFromRingsSafe()
  {
    if (IsLinkedToAppliedRing())
    {
      RemoveFromAppliedRing();
    }
    if (IsLinkedToSentRing())
    {
      RemoveFromSentRing();
    }
  }

  template <class R, class F> static void ForallRing(R &applicators, F &f)
  {
    ForallRingSafe(applicators, f);
  }

  template <class R, class F, class C> static void ForallRingSafeWhileBack(R &applicators, F &f, C &c)
  {
    R processed;
    while (!applicators.empty())
    {
      PFBaseApplicator *app = applicators.back();

      CObj<PFBaseApplicator> applObj(app);

      if (!c(applObj))
        break;

      R::remove(app);
      processed.addLast(app);

      f(applObj);
    }

    while(!processed.empty())
    {
      PFBaseApplicator *app = processed.back();

      CObj<PFBaseApplicator> applObj(app);

      R::remove(app);
      applicators.addLast(app);
    }
  }

  template <class R, class F, class C> static void ForallRingSafeWhile(R &applicators, F &f, C &c)
  {
    R processed;
    while (!applicators.empty())
    {
      PFBaseApplicator *app = applicators.first();

      CObj<PFBaseApplicator> applObj(app);

      if (!c(applObj))
        break;

      R::remove(app);
      processed.addLast(app);

      f(applObj);
    }

    while(!processed.empty())
    {
      PFBaseApplicator *app = processed.back();

      CObj<PFBaseApplicator> applObj(app);

      R::remove(app);
      applicators.addFirst(app);
    }
  }

  template <class R, class F> static void ForallRingSafe(R &applicators, F &f)
  {
    NI_PROFILE_FUNCTION

    R processed;
    while (!applicators.empty())
    {
      PFBaseApplicator *app = applicators.first();

      CObj<PFBaseApplicator> applObj(app);

      R::remove(app);
      processed.addLast(app);

      f(applObj);
    }

    while (!processed.empty())
    {
      PFBaseApplicator *app = processed.first();

      CObj<PFBaseApplicator> applObj(app);

      R::remove(app);
      applicators.addLast(app);
    }
  }

  template <class R> static void StepRing(R &applicators, float dtInSeconds)
  {
    StepFunc stepFunc(dtInSeconds);
    ForallRing(applicators, stepFunc);
  }

  virtual void OnChildApplicatorCreated(CObj<PFBaseApplicator> & pChildApplicator) {};

  float RetrieveParam( const ExecutableFloatString& par, float defaultValue = 0.0f)  const;
  bool  RetrieveParam( const ExecutableBoolString&  par, bool  defaultValue = false) const;
  int   RetrieveParam( const ExecutableIntString&   par, int   defaultValue = 0)     const;

#ifndef _SHIPPING
  static map<NDb::DBID, int> s_ActiveApplicatorsCountByDBID;
#endif

  ApplStopReason& GetStopReason() {return stopReason; }
  ApplStopReason  SetStopReason(ApplStopReason _stopReason) 
  {
    ApplStopReason prevValue = stopReason;
    stopReason = _stopReason; 
    return prevValue;
  }

protected:
	bool CheckTarget(const Target &target) const;

	const char* ErrorStr(const char *str) const;

	void RemoveChildrenApplicators();
	void RemoveChildrenApplicatorsFromUnit(PFBaseUnit *pUnit);

  IUnitFormulaPars const *RetriveReciever() const;

  virtual bool NeedEnableAfterReset() const { return false; }
  virtual bool NeedDisableAfterReset() const { return false; }

  virtual void OnAfterReset();

  template <class TDbAppl>
  TDbAppl const &GetDBAppl() const { return *static_cast<TDbAppl const*>(GetDBBase().GetPtr()); }

  // Called from Step
  virtual void Enable();
  virtual void Disable();

  virtual void Block();
  virtual void Unblock();

	// Acceptable flags for checking
	virtual int  GetAcceptableTargetFlags() const { return Target::FLAG_ALL; }
  virtual int  GetAcceptableUnitTypeFlags() const { return NDb::SPELLTARGET_ALL | NDb::SPELLTARGET_SHOP | (1 << NDb::UNITTYPE_PET); }
	virtual bool IsStackableWithTheSameType() const { return true; }

  // fly-off text stuff (used in Damage, Heal and FlyOff applicators)
  friend struct ApplFlyOffTextNameNamemap;

  // From IMiscFormulaPars
  virtual int   GetRank() const;
  virtual bool  IsAbilityOn() const;
  virtual float GetDist2Target() const;
  virtual float GetScale() const;
  virtual float GetParentScale() const;
  virtual float GetManaCost() const;
  virtual float GetPreparedness() const;
  virtual int   GetAbilityType() const;
	virtual bool  Roll(float probability) const;
  virtual int   GetRandom(int from, int to) const;
  virtual float GetConstant(const char *name, struct IUnitFormulaPars const *pSender, struct IUnitFormulaPars const* pReceiver) const;
  virtual int   GetTerrainType() const;
  virtual int   GetRefineRate() const { return GetAbilityData()->GetRefineRate(); }
  virtual float GetRefineAbilityScale( float valueAtRefineLevel0, float valueAtRefineLevel6  ) const { return GetAbilityData()->GetRefineAbilityScale(valueAtRefineLevel0, valueAtRefineLevel6); }
  virtual int   GetTalentLevel() const { return GetAbilityData()->GetTalentLevel(); }
  virtual bool  IsTalentBought() const { return GetAbilityData()->IsTalentBought(); }
  virtual int   GetTalentDevPoints() const { return GetAbilityData()->GetTalentDevPoints(); }
  virtual int   GetNaftaCost() const  { return GetAbilityData()->GetNaftaCost(); }
  virtual float GetCooldown() const { return GetAbilityData()->GetCooldown(); }
	virtual const IMiscFormulaPars* GetObjectParent() const { return IsValid( pParent ) ? pParent.GetPtr() : this; }
  virtual int   GetScrollLevel() const;
  virtual bool  IsNight() const;
  virtual float GetAbilityScale( bool isDamage, float statValue, EAbilityScaleMode abScaleMode, float valueLeft, float valueRight, bool bRound = true ) const;
  virtual bool  GetSmartRoll( float probability, int maxFailReps, int maxSuccessReps, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const;
  virtual int   GetSmartRandom( int outcomesNumber, float probDecrement, const IUnitFormulaPars* pFirst, const IUnitFormulaPars* pSecond ) const;
  virtual int   GetAlternativeTargetIndex() const;
  virtual float GetTerrainPart(int faction) const;
  virtual int   GetActivatedWithinKit() const;
  virtual int   GetTalentsWithinKit() const;
  virtual float GetStatusDispellPriority( const IUnitFormulaPars* pUnit, bool returnDuration ) const;
  virtual CVec2 GetVectorVariable(const char *name) const { return VNULL2; }
  
  AppliedRing::Part appliedRingPart;
  SentRing::Part sentRingPart;
  NamedRing::Part namedRingPart;
  
	friend bool ActivateApplicator(CObj<PFBaseApplicator> app, CObj<PFAbilityInstance> const& pAbility);

  virtual bool CheckEffectEnabled( const PF_Core::BasicEffect &effect );

  virtual int GetTerrianTypeUnderCursor() const;
  virtual int GetNatureTypeInPos(CVec2 pos) const;

  virtual bool CheckUpgradePerCastPerTarget() const;
protected:
  inline static const char* GetTalentLastUseStepVariableName(const int talentObjectId);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T, class DBT>
PFBaseApplicator* CreateApplicator(DBT const &/*dbAppl*/, PFApplCreatePars const &cp)
{
	return new T(cp);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class T>
PFBaseApplicator* CreateApplicator(NDb::ApplicatorNameOverrider const &dbAppl, PFApplCreatePars const &cp)
{
  return dbAppl.applicator->Create(cp);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
inline const char* PFBaseApplicator::GetTalentLastUseStepVariableName(const int talentObjectId)
{
  return NI_STRFMT("$TalLastUse:%d", talentObjectId);
}

} //namespace NWorld

#endif //PFAPPLICATION_H_INCLUDED
