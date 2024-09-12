#pragma once

#include "PFWorldObjectBase.h"
#include "PFDBLinker.h"
#include "PFUniTarget.h"
namespace NWorld
{
 class PFAbilityInstance;
 struct MultipleTargetSelectorFormulaPars;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ITargetAction
{
	virtual void operator()(const Target &target) = 0;
	ZDATA
public:
	ZEND int operator&( IBinSaver &f ) { return 0; }
};

struct ITargetCondition;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFTargetSelector : public PFWorldObjectBase
{
	WORLD_OBJECT_METHODS(0x9E6C82C2, PFTargetSelector);

protected:
	typedef NDb::TargetSelector CreateParams;

  ZDATA_(PFWorldObjectBase)
	NDb::Ptr<NDb::TargetSelector> pDB;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&pDB); return 0; }

	PFTargetSelector() {}
	PFTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFTargetSelector(const NDb::TargetSelector &db, PFWorld* world) : PFWorldObjectBase( world, 0 ), pDB(&db) {}

	virtual ~PFTargetSelector() {}

	virtual bool NeedToBeStepped() { return false; }

	NDb::Ptr<NDb::TargetSelector> GetDBBase() const { return pDB; }

  struct RequestParams : NonCopyable
  {
    RequestParams(const PFBaseApplicator &appl_, const Target &requester_);
    RequestParams(const PFBaseApplicator &appl_, const Target &requester_, const ITargetCondition& cond);
    RequestParams(const PFBaseApplicator &appl_, const Target &requester_, const ITargetCondition* const cond);
    RequestParams(const CPtr<PFBaseUnit> &pOwner_, const IMiscFormulaPars * pMiscPars_, const Target &requester_);
    RequestParams(const CPtr<PFBaseUnit> &pOwner_, const IMiscFormulaPars * pMiscPars_, const Target &requester_, const ITargetCondition& cond);
    RequestParams(const CPtr<PFBaseUnit> &pOwner_, const IMiscFormulaPars * pMiscPars_, const Target &requester_, const ITargetCondition* const cond);

    const IMiscFormulaPars * pMiscPars;
    CPtr<PFBaseUnit>         pOwner;
    const Target *           pRequester;
    CPtr<PFAbilityInstance>  pAbility;
    CPtr<PFBaseUnit>         pReceiver;

    const ITargetCondition* const condition;
  };

  template<class U> struct TargetsCollector : public ITargetAction, public NonCopyable
  {
    TargetsCollector( vector<U*>& units_ ) : units(units_) {}

    void operator()(const Target &target)
    {
      NI_VERIFY( target.IsUnit(), "Collected target is not a unit", return );
      U* pUnit = target.GetUnit();
      if ( IsUnitValid( pUnit ) )
        units.push_back( pUnit );
    }

    vector<U*>& units;
  };

	virtual void EnumerateTargets(ITargetAction &/*action*/, const RequestParams &/*pars*/) {}

  static bool s_DumpSelectors;

protected:
	static float RetrieveParam(ExecutableFloatString const &par, const RequestParams &pars, float defaultValue = 0.0f);
  static int RetrieveParam(ExecutableIntString const &par, const RequestParams &pars, int defaultValue = 0);
  string GetDebugName() const;
  string DumpTarget( const Target& target ) const;
  friend struct DumpTargetWrapper;
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFMultipleTargetSelector : public PFTargetSelector
{
	WORLD_OBJECT_METHODS(0x9E676B81, PFMultipleTargetSelector);

protected:
	ZDATA_(PFTargetSelector)
	int            runCount; 
	vector<Target> rememberedTargets;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFTargetSelector*)this); f.Add(2,&runCount); f.Add(3,&rememberedTargets); return 0; }

	PFMultipleTargetSelector() {}
	PFMultipleTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFMultipleTargetSelector(const NDb::TargetSelector &db, PFWorld* world) : PFTargetSelector( db, world ), runCount(0) {}

public:
	virtual void EnumerateTargets(ITargetAction &action, const RequestParams &pars);

  friend struct MultipleTargetSelectorFormulaPars;

protected:
	virtual void ForAllTargets(ITargetAction &/*action*/, const RequestParams &/*pars*/) {}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFSingleTargetSelector : public PFTargetSelector
{
	WORLD_OBJECT_METHODS(0x9E6C8300, PFSingleTargetSelector);

protected:
	ZDATA_(PFTargetSelector)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFTargetSelector*)this); return 0; }

	PFSingleTargetSelector() {}
	PFSingleTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFSingleTargetSelector(const NDb::TargetSelector &db, PFWorld* world) : PFTargetSelector( db, world ) {}

public:
	virtual void EnumerateTargets(ITargetAction &action, const RequestParams &pars);

	virtual bool FindTarget(const RequestParams &/*pars*/, Target &/*target*/) { return false; }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFAreaTargetSelector : public DBLinker<PFMultipleTargetSelector, NDb::AreaTargetSelector>
{
	WORLD_OBJECT_METHODS(0x9E676B80, PFAreaTargetSelector);

protected:
	ZDATA_(DBLinker)
  CObj<PFSingleTargetSelector> pTargetSelector;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

	PFAreaTargetSelector() {}
	PFAreaTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFAreaTargetSelector(const NDb::TargetSelector &db, PFWorld* world);

protected:
#ifndef _SHIPPING
  bool debug_show;
#endif
	virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFDblPointTargetSelector : public PFMultipleTargetSelector
{
	WORLD_OBJECT_METHODS(0x9E6C8A41, PFDblPointTargetSelector);

protected:
	ZDATA_(PFMultipleTargetSelector)
	CVec2 prevPos;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFMultipleTargetSelector*)this); f.Add(2,&prevPos); return 0; }

	PFDblPointTargetSelector() {}
	PFDblPointTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFDblPointTargetSelector(const NDb::TargetSelector &db, PFWorld* world) : PFMultipleTargetSelector( db, world ), prevPos( VNULL2 ) {}

protected:
	void MakePos(const RequestParams &pars, NDb::ETargetSelectorPoint pointSpec, CVec2 &pos) const;
	virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);

	virtual void OnForAllTargets(ITargetAction &/*action*/, const RequestParams &/*pars*/) {}
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFSectorTargetSelector : public DBLinker<PFDblPointTargetSelector, NDb::SectorTargetSelector>
{
	WORLD_OBJECT_METHODS(0x9E6CB4C0, PFSectorTargetSelector);

protected:
	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFSectorTargetSelector() {}
	PFSectorTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFSectorTargetSelector(const NDb::TargetSelector &db, PFWorld* world) : Base( db, world ) {}

protected:
	virtual void OnForAllTargets(ITargetAction &action, const RequestParams &pars);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFCapsuleTargetSelector : public DBLinker<PFDblPointTargetSelector, NDb::CapsuleTargetSelector>
{
	WORLD_OBJECT_METHODS(0x9E6CB4C1, PFCapsuleTargetSelector);

protected:
	ZDATA_(DBLinker)
  CVec2 origin;
  CObj<PFSingleTargetSelector> pSegmentEndTargetSelector;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&origin); f.Add(3,&pSegmentEndTargetSelector); return 0; }

	PFCapsuleTargetSelector() {}
	PFCapsuleTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFCapsuleTargetSelector(const NDb::TargetSelector &db, PFWorld* world);

protected:
	virtual void OnForAllTargets(ITargetAction &action, const RequestParams &pars);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFNearestInAreaTargetSelector : public DBLinker<PFMultipleTargetSelector, NDb::NearestInAreaTargetSelector>
{
	WORLD_OBJECT_METHODS(0x9E67EC01, PFNearestInAreaTargetSelector);

protected:
	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFNearestInAreaTargetSelector() {}
	PFNearestInAreaTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFNearestInAreaTargetSelector(const NDb::TargetSelector &db, PFWorld* world) : Base( db, world ) {}

protected:
	virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFSummonEnumerator : public DBLinker<PFMultipleTargetSelector, NDb::SummonEnumerator>
{
	WORLD_OBJECT_METHODS(0x9E677281, PFSummonEnumerator);

protected:
	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFSummonEnumerator() {}
	PFSummonEnumerator(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFSummonEnumerator(const NDb::TargetSelector &db, PFWorld* world) : Base( db, world ) {}

protected:
	virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFUnitEnumerator : public DBLinker<PFMultipleTargetSelector, NDb::UnitEnumerator>
{
	WORLD_OBJECT_METHODS(0x9E677301, PFUnitEnumerator);

protected:
	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFUnitEnumerator() {}
	PFUnitEnumerator(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFUnitEnumerator(const NDb::TargetSelector &db, PFWorld* world) : Base( db, world ) {}

protected:
	virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFHeroEnumerator : public DBLinker<PFMultipleTargetSelector, NDb::HeroEnumerator>
{
	WORLD_OBJECT_METHODS(0x9E67AB02, PFHeroEnumerator);

protected:
	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFHeroEnumerator() {}
	PFHeroEnumerator(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFHeroEnumerator(const NDb::TargetSelector &db, PFWorld* world) : Base( db, world ) {}

protected:
	virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFNearestTargetSelector : public DBLinker<PFSingleTargetSelector, NDb::NearestTargetSelector>
{
	WORLD_OBJECT_METHODS(0x9E6C8341, PFNearestTargetSelector);

protected:
	ZDATA_(DBLinker)
	CObj<PFTargetSelector> pTargetSelector;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

	PFNearestTargetSelector() {}
	PFNearestTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFNearestTargetSelector(const NDb::TargetSelector &db, PFWorld* world);

public:
	virtual bool FindTarget(const RequestParams &pars, Target &target);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFUnitPlaceCorrector : public DBLinker<PFSingleTargetSelector, NDb::UnitPlaceCorrector>
{
	WORLD_OBJECT_METHODS(0x9E72DB81, PFUnitPlaceCorrector);

protected:
	ZDATA_(DBLinker)
	CObj<PFSingleTargetSelector> pTargetSelector;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

	PFUnitPlaceCorrector() {}
	PFUnitPlaceCorrector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFUnitPlaceCorrector(const NDb::TargetSelector &db, PFWorld* world);

public:
	virtual bool FindTarget(const RequestParams &pars, Target &target);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFConvertTargetToLand : public DBLinker<PFSingleTargetSelector, NDb::ConvertTargetToLand>
{
	WORLD_OBJECT_METHODS(0x9E71EBC2, PFConvertTargetToLand);

protected:
	ZDATA_(DBLinker)
  CObj<PFTargetSelector> pTargetSelector;
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

	PFConvertTargetToLand() {}
	PFConvertTargetToLand(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFConvertTargetToLand(const NDb::TargetSelector &db, PFWorld* world);

public:
	virtual bool FindTarget(const RequestParams &pars, Target &target);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFMainBuildingTargetSelector : public DBLinker<PFSingleTargetSelector, NDb::MainBuildingTargetSelector>
{
  WORLD_OBJECT_METHODS(0xB720B43, PFMainBuildingTargetSelector);

protected:
  ZDATA_(DBLinker)
  CPtr<PFLogicObject> m_pMainBuilding;
	NDb::EFaction       m_faction;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&m_pMainBuilding); f.Add(3,&m_faction); return 0; }

	PFMainBuildingTargetSelector() {}
	PFMainBuildingTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFMainBuildingTargetSelector(const NDb::TargetSelector &db, PFWorld* world) : Base( db, world ), m_faction(NDb::FACTION_NEUTRAL) {}

public:
  virtual bool FindTarget(const RequestParams &pars, Target &target);
  virtual void operator()(PFLogicObject &object);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFFountainTargetSelector : public DBLinker<PFSingleTargetSelector, NDb::FountainTargetSelector>
{
  WORLD_OBJECT_METHODS(0xB720BC0, PFFountainTargetSelector);

protected:
  ZDATA_(DBLinker)
  CPtr<PFLogicObject> m_pFountain;
	NDb::EFaction       m_faction;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&m_pFountain); f.Add(3,&m_faction); return 0; }

	PFFountainTargetSelector() {}
	PFFountainTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFFountainTargetSelector(const NDb::TargetSelector &db, PFWorld* world) : Base( db, world ), m_faction(NDb::FACTION_NEUTRAL) {}
public:
  virtual bool FindTarget(const RequestParams &pars, Target &target);
  virtual void operator()(PFLogicObject &object);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFShopTargetSelector : public DBLinker<PFSingleTargetSelector, NDb::ShopTargetSelector>
{
  WORLD_OBJECT_METHODS(0xF756BC1, PFShopTargetSelector);

protected:
  ZDATA_(DBLinker)
  CPtr<PFLogicObject> m_pShop;
	NDb::EFaction       m_faction;
	CVec3               m_ownerPos;
	float               m_minDist;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&m_pShop); f.Add(3,&m_faction); f.Add(4,&m_ownerPos); f.Add(5,&m_minDist); return 0; }

	PFShopTargetSelector() {}
	PFShopTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFShopTargetSelector(const NDb::TargetSelector &db, PFWorld* world) 
		: Base( db, world ), m_faction(NDb::FACTION_NEUTRAL), m_ownerPos(VNULL3), m_minDist(0.0f) {}
public:
  virtual bool FindTarget(const RequestParams &pars, Target &target);
  virtual void operator()(PFLogicObject &object);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFRelativeUnitTargetSelector : public DBLinker<PFSingleTargetSelector, NDb::RelativeUnitTargetSelector>
{
	WORLD_OBJECT_METHODS(0x9E6C8440, PFRelativeUnitTargetSelector);

protected:
	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFRelativeUnitTargetSelector() {}
	PFRelativeUnitTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFRelativeUnitTargetSelector(const NDb::TargetSelector &db, PFWorld* world) : Base( db, world ) {}

public:
	virtual bool FindTarget(const RequestParams &pars, Target &target);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFUnitShiftTarget : public DBLinker<PFSingleTargetSelector, NDb::UnitShiftTarget>
{
	WORLD_OBJECT_METHODS(0x9E73DB81, PFUnitShiftTarget);

protected:
	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFUnitShiftTarget() {}
	PFUnitShiftTarget(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFUnitShiftTarget(const NDb::TargetSelector &db, PFWorld* world) : Base( db, world ) {}

public:
	virtual bool FindTarget(const RequestParams &pars, Target &target);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFPointTargetSelector : public DBLinker<PFSingleTargetSelector, NDb::PointTargetSelector>
{
  WORLD_OBJECT_METHODS(0xF738CC0, PFPointTargetSelector);

protected:
  ZDATA_(DBLinker)
  CObj<PFSingleTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

	PFPointTargetSelector() {}
	PFPointTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFPointTargetSelector(const NDb::TargetSelector &db, PFWorld* world);

public:
  virtual bool FindTarget(const RequestParams &pars, Target &target);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFFirstTargetSelector : public DBLinker<PFSingleTargetSelector, NDb::FirstTargetSelector>
{
  WORLD_OBJECT_METHODS(0xF738B40, PFFirstTargetSelector);

protected:
  ZDATA_(DBLinker)
  CObj<PFTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

	PFFirstTargetSelector() {}
	PFFirstTargetSelector(const NDb::FirstTargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFFirstTargetSelector(const NDb::FirstTargetSelector &db, PFWorld* world);

public:
  virtual bool FindTarget(const RequestParams &pars, Target &target);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFWeightTargetSelector : public DBLinker<PFSingleTargetSelector, NDb::WeightTargetSelector>
{
  WORLD_OBJECT_METHODS(0x2282AB40, PFWeightTargetSelector);

protected:
  ZDATA_(DBLinker)
  CObj<PFTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

	PFWeightTargetSelector() {}
	PFWeightTargetSelector(const NDb::WeightTargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFWeightTargetSelector(const NDb::WeightTargetSelector &db, PFWorld* world);

public:
  virtual bool FindTarget(const RequestParams &pars, Target &target);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFListOfTargetSelectors : public DBLinker<PFMultipleTargetSelector, NDb::ListOfTargetSelectors>
{
  WORLD_OBJECT_METHODS(0xF738B41, PFListOfTargetSelectors);

protected:
  ZDATA_(DBLinker);
  vector< CObj<PFTargetSelector> > targetSelectors;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&targetSelectors); return 0; }

	PFListOfTargetSelectors() {}
	PFListOfTargetSelectors(const NDb::ListOfTargetSelectors &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFListOfTargetSelectors(const NDb::ListOfTargetSelectors &db, PFWorld* world);

public:
  virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFFilterTargetSelector : public DBLinker<PFMultipleTargetSelector, NDb::FilterTargetSelector>
{
  WORLD_OBJECT_METHODS(0xF738B43, PFFilterTargetSelector);

protected:
  ZDATA_(DBLinker);
  CObj<PFTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

	PFFilterTargetSelector() {}
	PFFilterTargetSelector(const NDb::FilterTargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFFilterTargetSelector(const NDb::FilterTargetSelector &db, PFWorld* world);

public:
  virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFConditionTargetSelector : public DBLinker<PFMultipleTargetSelector, NDb::ConditionTargetSelector>
{
  WORLD_OBJECT_METHODS(0x2B7BBAC0, PFConditionTargetSelector);

  ZDATA_(DBLinker);
  CObj<PFTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

	PFConditionTargetSelector() {}
	PFConditionTargetSelector(const NDb::ConditionTargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFConditionTargetSelector(const NDb::ConditionTargetSelector &db, PFWorld* world);

public:
  virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFCountingTargetSelector : public DBLinker<PFMultipleTargetSelector, NDb::CountingTargetSelector>
{
  WORLD_OBJECT_METHODS(0xE776A5C0, PFCountingTargetSelector);

protected:
  ZDATA_(DBLinker);
  CObj<PFTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

	PFCountingTargetSelector() {}
	PFCountingTargetSelector(const NDb::CountingTargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFCountingTargetSelector(const NDb::CountingTargetSelector &db, PFWorld* world);

public:
  virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFComparingTargetSelector : public DBLinker<PFSingleTargetSelector, NDb::ComparingTargetSelector>
{
  WORLD_OBJECT_METHODS(0xE776B440, PFComparingTargetSelector);

protected:
  ZDATA_(DBLinker);
  CObj<PFTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

	PFComparingTargetSelector() {}
	PFComparingTargetSelector(const NDb::ComparingTargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFComparingTargetSelector(const NDb::ComparingTargetSelector &db, PFWorld* world);

public:
  virtual bool FindTarget(const RequestParams &pars, Target &target);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFSelectApplicatorTarget : public DBLinker<PFSingleTargetSelector, NDb::SelectApplicatorTarget>
{
	WORLD_OBJECT_METHODS(0xE77B1C81, PFSelectApplicatorTarget);

protected:
	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFSelectApplicatorTarget() {}
	PFSelectApplicatorTarget(const NDb::SelectApplicatorTarget &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFSelectApplicatorTarget(const NDb::SelectApplicatorTarget &db, PFWorld* world) : Base( db, world ) {}

public:
	virtual bool FindTarget(const RequestParams &pars, Target &target);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFApplicatorRecipientsTargetSelector : public DBLinker<PFMultipleTargetSelector, NDb::ApplicatorRecipientsTargetSelector>
{
	WORLD_OBJECT_METHODS(0xE7832C01, PFApplicatorRecipientsTargetSelector);

protected:
	ZDATA_(DBLinker)
public:
	ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

	PFApplicatorRecipientsTargetSelector() {}
	PFApplicatorRecipientsTargetSelector(const NDb::ApplicatorRecipientsTargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
	PFApplicatorRecipientsTargetSelector(const NDb::ApplicatorRecipientsTargetSelector &db, PFWorld* world) : Base( db, world ) {}

public:
	virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFFixToCenterTargetSelector : public DBLinker<PFSingleTargetSelector, NDb::FixToCenterTargetSelector>
{
  WORLD_OBJECT_METHODS(0xEF9752C0, PFFixToCenterTargetSelector);

protected:
  ZDATA_(DBLinker)
  CObj<PFSingleTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

  PFFixToCenterTargetSelector() {}
  PFFixToCenterTargetSelector(const NDb::FixToCenterTargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
  PFFixToCenterTargetSelector(const NDb::FixToCenterTargetSelector &db, PFWorld* world);

public:
  virtual bool FindTarget(const RequestParams &pars, Target &target);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFBetweenUnitsTargetSelector : public DBLinker<PFMultipleTargetSelector, NDb::BetweenUnitsTargetSelector>
{
  WORLD_OBJECT_METHODS(0x9A9CE3C1, PFBetweenUnitsTargetSelector);

protected:
  ZDATA_(DBLinker)
  CObj<PFMultipleTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

  PFBetweenUnitsTargetSelector() {}
  PFBetweenUnitsTargetSelector(const NDb::BetweenUnitsTargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
  PFBetweenUnitsTargetSelector(const NDb::BetweenUnitsTargetSelector &db, PFWorld* world);

public:
  virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFWallTargetSelector : public DBLinker<PFMultipleTargetSelector, NDb::WallTargetSelector>
{
  WORLD_OBJECT_METHODS(0xE79C9481, PFWallTargetSelector);

  explicit PFWallTargetSelector() {}
protected:
  ZDATA_(DBLinker)
  CObj<PFSingleTargetSelector> pOriginTS;
  CObj<PFSingleTargetSelector> pDirectionTS;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pOriginTS); f.Add(3,&pDirectionTS); return 0; }

  PFWallTargetSelector(const NDb::TargetSelector &db, PFWorld* world);

protected:
  virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFAttackersTargetSelector : public DBLinker<PFMultipleTargetSelector, NDb::AttackersTargetSelector>
{
  WORLD_OBJECT_METHODS(0x9A9D43C1, PFAttackersTargetSelector);

  explicit PFAttackersTargetSelector() {}
protected:
  ZDATA_(DBLinker)
  CObj<PFSingleTargetSelector> pTargetSelector;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

  PFAttackersTargetSelector(const NDb::TargetSelector &db, PFWorld* world);

protected:
  virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Debugging
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef _SHIPPING
#define DUMP_SELECTOR_TARGET( target ) 
#define DUMP_SELECTOR_START() 
#define DUMP_TARGET( target ) 
#define DUMP_TARGET2( sel, target )
#define DUMP_SELECTOR_END() 
#else
#define DUMP_SELECTOR_TARGET( target )     \
  if ( PFTargetSelector::s_DumpSelectors ) { DebugTrace( "Target(%s): %s ", GetDebugName().c_str(), DumpTarget((target)).c_str() ); }
#define DUMP_SELECTOR_START()       \
  if ( PFTargetSelector::s_DumpSelectors ) { DebugTrace( "++Selector %s", GetDebugName().c_str()); }
#define DUMP_TARGET2( sel, target ) \
  if ( PFTargetSelector::s_DumpSelectors ) { DebugTrace( "Target: %s ", sel->DumpTarget((target)).c_str() ); }
#define DUMP_TARGET( target ) \
  if ( PFTargetSelector::s_DumpSelectors ) { DebugTrace( "Target: %s ", DumpTarget((target)).c_str() ); }
#define DUMP_SELECTOR_END() \
  if ( PFTargetSelector::s_DumpSelectors ) { DebugTrace( "--Selector %s", GetDebugName().c_str() ); }
#endif
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct DumpTargetWrapper
{
  DumpTargetWrapper( PFTargetSelector* selector, ITargetAction& action )
    :selector(selector), action(&action) {}
  inline void operator()(const Target &target) const
  {
    DUMP_TARGET2( selector, target );
    (*action)(target);
  }

  PFTargetSelector* selector; 
  ITargetAction* action;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct ITargetCondition
{
  virtual bool operator()(const Target& target, const PFAbilityData* const ability) const = 0;

  ZDATA
  ZEND int operator&( IBinSaver &f ) { return 0; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}