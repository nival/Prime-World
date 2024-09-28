#pragma once

#include "PFApplBuff.h"
#include "PFBaseUnitEvent.h"

namespace NWorld
{

  class PFWorld;
  class PFBaseUnit;
  class PFTriggerApplicator;

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorBase : public PFWorldObjectBase
  {
    WORLD_OBJECT_METHODS(0xF7563C1, PFEventProcessorBase);

  protected:
    ZDATA_(PFWorldObjectBase)
    NDb::Ptr<NDb::EventProcessorBase> dbData;
    CPtr<PFTriggerApplicator> pOwner;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&dbData); f.Add(3,&pOwner); return 0; }

    typedef NDb::EventProcessorBase CreateParams;
    
		PFEventProcessorBase() {}
		PFEventProcessorBase(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
    PFEventProcessorBase(CreateParams const& dbData, PFWorld* world) : PFWorldObjectBase( world, 0 ), dbData(&dbData) {}

    virtual ~PFEventProcessorBase() {}
    virtual void Initialize(CPtr<PFTriggerApplicator> const& pOwner);
    NDb::EApplicatorApplyTarget GetApplicationTarget() const;

    virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent)  { return false; } // return true, if processed
    virtual float GetVariable(const char* varName) const { return 0.0f; }
    virtual int GetAccessibleEventsMask() const { return 0xFFFFFFFF; } // all events accessible by default

		virtual bool NeedToBeStepped() { return false; }

  protected:
    // Internal
    NDb::Ptr<NDb::EventProcessorBase> const& GetDBBase() const { return dbData; }
    void DoSpell( const CPtr<PFBaseUnit> &pEventSender = NULL ) const;
    CPtr<PFBaseUnit> const& GetReceiver() const;
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFTriggerApplicator
    : public DBLinker<PFApplBuff, NDb::TriggerApplicator>
    , public PFBaseUnitEventListener
  {
    WORLD_OBJECT_METHODS(0xF7224C0, PFTriggerApplicator);

    ///TODO: should be inside ZDATA. To put into ZDATA  we need proper serialization for AutoPtr class!!!
    ZDATA_(DBLinker);
    CObj<PFEventProcessorBase> eventProcessor;  
    ZNOPARENT(PFBaseUnitEventListener)
    int actionsCount;
    int maxActionsCount;
    float scale;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&eventProcessor); f.Add(3,&actionsCount); f.Add(4,&maxActionsCount); f.Add(5,&scale); return 0; }

    PFTriggerApplicator(PFApplCreatePars const &cp);
    PFTriggerApplicator() { }
    
  protected:
    virtual bool Start();
    virtual void Enable();
    virtual void Disable();
    virtual bool Step(float dtInSeconds);

    virtual unsigned int OnEvent(const PFBaseUnitEvent *pEvent);

    virtual float GetVariable(const char* varName) const;
    
    friend class PFEventProcessorCondition;
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFAbsorbShieldApplicator
    : public DBLinker<PFApplBuff, NDb::AbsorbShieldApplicator>
    , public PFBaseUnitEventListener
  {
    WORLD_OBJECT_METHODS(0x2B82CC01, PFAbsorbShieldApplicator);

    void ModifyReceiverShield(const float delta) const;

    float shield;
    float damage;

    ZDATA_(DBLinker);
    ZNOPARENT(PFBaseUnitEventListener)
    float damageToAbsorb;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&damageToAbsorb); return 0; }

    PFAbsorbShieldApplicator( const PFApplCreatePars& cp );

    float GetVariable(const char* varName) const;
    virtual EListenerType GetListenerType() const { return LISTENER_SHIELD; }
    virtual float GetListenerPriority() const { return GetDuration(); }

    float GetDamageToAbsorb() const { return damageToAbsorb; }
  protected:
    PFAbsorbShieldApplicator();
    virtual bool Start();
    virtual void Enable();
    virtual void Disable();
    virtual bool Step( float dtInSeconds );

    virtual unsigned int OnEvent( const PFBaseUnitEvent* pEvent);
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // Event processors
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  class PFEventProcessorGroup : public DBLinker<PFEventProcessorBase, NDb::EventProcessorGroup>
  {
    WORLD_OBJECT_METHODS(0xF756440, PFEventProcessorGroup);

    ZDATA_(DBLinker)
    vector< CObj<PFEventProcessorBase> > processors;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&processors); return 0; }

		PFEventProcessorGroup() {}
		PFEventProcessorGroup(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
		PFEventProcessorGroup(CreateParams const& dbData, PFWorld* world) : Base(dbData, world) {}

		virtual void Initialize(CPtr<PFTriggerApplicator> const& pOwner);
    virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual int GetAccessibleEventsMask() const;
  };
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorCondition : public DBLinker<PFEventProcessorBase, NDb::EventProcessorCondition>
  {
    WORLD_OBJECT_METHODS(0xF756441, PFEventProcessorCondition);

    ZDATA_(DBLinker)
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

		PFEventProcessorCondition() {}
		PFEventProcessorCondition(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
		PFEventProcessorCondition(CreateParams const& dbData, PFWorld* world) : Base(dbData, world) {}

		virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual int GetAccessibleEventsMask() const { return GetDB().events; } // all events accessible by default
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorCancelDispatch: public DBLinker<PFEventProcessorBase, NDb::EventProcessorCancelDispatch>
  {
    WORLD_OBJECT_METHODS(0xF756442, PFEventProcessorCancelDispatch);

    ZDATA_(DBLinker)
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

		PFEventProcessorCancelDispatch() {}
		PFEventProcessorCancelDispatch(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
		PFEventProcessorCancelDispatch(CreateParams const& dbData, PFWorld* world) : Base(dbData, world) {}

		virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual int GetAccessibleEventsMask() const { return 1 << NDb::BASEUNITEVENT_DISPATCHAPPLIED; }
  };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorPickupGlyph: public DBLinker<PFEventProcessorBase, NDb::EventProcessorPickupGlyph>
  {
    WORLD_OBJECT_METHODS(0x37A78C41, PFEventProcessorPickupGlyph);

    ZDATA_(DBLinker)
    static int glyphNumber;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&glyphNumber); return 0; }

    PFEventProcessorPickupGlyph() {}
    PFEventProcessorPickupGlyph(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
    PFEventProcessorPickupGlyph(CreateParams const& dbData, PFWorld* world) : Base(dbData, world){}

    virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual int GetAccessibleEventsMask() const { return 1 << NDb::BASEUNITEVENT_PICKUP; }
    virtual float GetVariable(const char* varName) const;

    static const char* glyphNumberVariableName;
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorDamageTransformer : public DBLinker<PFEventProcessorBase, NDb::EventProcessorDamageTransformer>
  {
    static const char* damageConvertedVariableName;
    static const char* rawDamageVariableName;
    WORLD_OBJECT_METHODS(0xF756443, PFEventProcessorDamageTransformer);

    struct DummyFormulaPars;

    ZDATA_(DBLinker);
    float damageConverted;
    float rawDamage;
    vector<CPtr<PFAbilityInstance> > processedAbilityInstances;
    bool bProcessedThisStep;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&damageConverted); f.Add(3,&rawDamage); f.Add(4,&processedAbilityInstances); f.Add(5,&bProcessedThisStep); return 0; }

		PFEventProcessorDamageTransformer() {}
		PFEventProcessorDamageTransformer(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
		PFEventProcessorDamageTransformer(CreateParams const& dbData, PFWorld* world) : Base(dbData, world), damageConverted(0), rawDamage(0), bProcessedThisStep(false) {}

    virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual float GetVariable(const char* varName) const;
    virtual int GetAccessibleEventsMask() const { return 1 << NDb::BASEUNITEVENT_DAMAGE; }
    virtual bool Step(float dtInSeconds);
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorIncomingDamage : public DBLinker<PFEventProcessorBase, NDb::EventProcessorIncomingDamage>
  {
    WORLD_OBJECT_METHODS(0xE78A3CC1, PFEventProcessorIncomingDamage);

    ZDATA_(DBLinker);
    float damage;
    float delegatedDamage;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&damage); f.Add(3,&delegatedDamage); return 0; }

		PFEventProcessorIncomingDamage(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
		PFEventProcessorIncomingDamage(CreateParams const& dbData, PFWorld* world) : Base(dbData, world), damage(0), delegatedDamage(0) {}

    virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual float GetVariable(const char* varName) const;
    virtual int GetAccessibleEventsMask() const { return 1 << NDb::BASEUNITEVENT_DAMAGE; }

  private:
  	PFEventProcessorIncomingDamage() {}
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorAbilityManacostTransformer : public DBLinker<PFEventProcessorBase, NDb::EventProcessorAbilityManacostTransformer>
  {
    static const char* manaCostVariableName;
    WORLD_OBJECT_METHODS(0xF756444, PFEventProcessorAbilityManacostTransformer);

    ZDATA_(DBLinker);
    float manaCost;
    float baseManaCost;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&manaCost); f.Add(3,&baseManaCost); return 0; }

		PFEventProcessorAbilityManacostTransformer() {}
		PFEventProcessorAbilityManacostTransformer(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
		PFEventProcessorAbilityManacostTransformer(CreateParams const& dbData, PFWorld* world) : Base(dbData, world), manaCost(0), baseManaCost(0) {}

    virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual float GetVariable(const char* varName) const;
    virtual int GetAccessibleEventsMask() const { return (1 << NDb::BASEUNITEVENT_CASTMAGIC) | (1 << NDb::BASEUNITEVENT_USECONSUMABLE) | (1 << NDb::BASEUNITEVENT_USETALENT); }
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorApplicatorApplied : public DBLinker<PFEventProcessorBase, NDb::EventProcessorApplicatorApplied>
  {
    WORLD_OBJECT_METHODS(0xF756445, PFEventProcessorApplicatorApplied);

    struct DummyFormulaPars;

    ZDATA_(DBLinker);
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

		PFEventProcessorApplicatorApplied() {}
		PFEventProcessorApplicatorApplied(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
		PFEventProcessorApplicatorApplied(CreateParams const& dbData, PFWorld* world) : Base(dbData, world) {}

    virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual int GetAccessibleEventsMask() const { return 1 << NDb::BASEUNITEVENT_APPLICATORAPPLIED; }
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorOnDeath : public DBLinker<PFEventProcessorBase, NDb::EventProcessorOnDeath>
  {
    WORLD_OBJECT_METHODS(0xF756446, PFEventProcessorOnDeath);

    ZDATA_(DBLinker);
    float castSpellDelay;
    CPtr<PFBaseUnit> pTempEventSender;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&castSpellDelay); f.Add(3,&pTempEventSender); return 0; }

		PFEventProcessorOnDeath() {}
		PFEventProcessorOnDeath(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
		PFEventProcessorOnDeath(CreateParams const& dbData, PFWorld* world) : Base(dbData, world), castSpellDelay(0.0f) {}

		virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual int GetAccessibleEventsMask() const { return 1 << NDb::BASEUNITEVENT_APPLICATORSTEP | 1 << NDb::BASEUNITEVENT_DEATH; }
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorOnTarget : public DBLinker<PFEventProcessorBase, NDb::EventProcessorOnTarget>
  {
    WORLD_OBJECT_METHODS(0xF756447, PFEventProcessorOnTarget);

    ZDATA_(DBLinker);
    CObj<PFTargetSelector> pTargetSelector;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

		PFEventProcessorOnTarget() {}
		PFEventProcessorOnTarget(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
		PFEventProcessorOnTarget(CreateParams const& dbData, PFWorld* world);

		virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual int GetAccessibleEventsMask() const { return 1 << NDb::BASEUNITEVENT_APPLICATORSTEP; }
		virtual void Initialize(CPtr<PFTriggerApplicator> const& pOwner);
  };
  
  
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorUnitDieNearMe : public DBLinker<PFEventProcessorBase, NDb::EventProcessorUnitDieNearMe>
  {
    WORLD_OBJECT_METHODS(0xF756448, PFEventProcessorUnitDieNearMe);

    ZDATA_(DBLinker);
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

		PFEventProcessorUnitDieNearMe() {}
		PFEventProcessorUnitDieNearMe(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
		PFEventProcessorUnitDieNearMe(CreateParams const& dbData, PFWorld* world) : Base(dbData, world) {}

		virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual int GetAccessibleEventsMask() const { return 1 << NDb::BASEUNITEVENT_DEATH; }
  private:
    bool CheckKiller( CPtr<PFBaseUnit> const& pKiller ) const;
    bool CheckVictim( CPtr<PFBaseUnit> const& pVictim ) const;
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorOnUseAbilityForceStrike : public DBLinker<PFEventProcessorBase, NDb::EventProcessorOnUseAbilityForceStrike>
  {
    WORLD_OBJECT_METHODS(0xF756449, PFEventProcessorOnUseAbilityForceStrike);

    ZDATA_(DBLinker);
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

		PFEventProcessorOnUseAbilityForceStrike() {}
		PFEventProcessorOnUseAbilityForceStrike(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
		PFEventProcessorOnUseAbilityForceStrike(CreateParams const& dbData, PFWorld* world) : Base(dbData, world) {}

    virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual int GetAccessibleEventsMask() const { return (1 << NDb::BASEUNITEVENT_CASTMAGIC) | (1 << NDb::BASEUNITEVENT_USECONSUMABLE) | (1 << NDb::BASEUNITEVENT_USETALENT); }
  };

  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFEventProcessorLastHit : public DBLinker<PFEventProcessorBase, NDb::EventProcessorLastHit>
  {
    WORLD_OBJECT_METHODS(0xE7768540, PFEventProcessorLastHit);

    ZDATA_(DBLinker);
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

		PFEventProcessorLastHit() {}
		PFEventProcessorLastHit(CreateParams const& dbData) { NI_ALWAYS_ASSERT("Bad constructor") }
		PFEventProcessorLastHit(CreateParams const& dbData, PFWorld* world) : Base(dbData, world) {}

		virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
    virtual int GetAccessibleEventsMask() const { return (1 << NDb::BASEUNITEVENT_LASTHIT); }
  };

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFEventProcessorOnConsumableObtained : public DBLinker<PFEventProcessorBase, NDb::EventProcessorOnConsumableObtained>
{
  WORLD_OBJECT_METHODS(0xE79BA400, PFEventProcessorOnConsumableObtained);

  explicit PFEventProcessorOnConsumableObtained() {}

  ZDATA_(DBLinker);
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFEventProcessorOnConsumableObtained(CreateParams const& dbData, PFWorld* world) : Base(dbData, world) {}

  virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
  virtual int GetAccessibleEventsMask() const { return (1 << NDb::BASEUNITEVENT_CONSUMABLEOBTAINED); }
};

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFEventProcessorOutgoingDamage : public DBLinker<PFEventProcessorBase, NDb::EventProcessorOutgoingDamage>
{
  WORLD_OBJECT_METHODS(0xE7A69381, PFEventProcessorOutgoingDamage);

  struct DummyFormulaPars;

  explicit PFEventProcessorOutgoingDamage() {}

  ZDATA_(DBLinker);
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); return 0; }

  PFEventProcessorOutgoingDamage(CreateParams const& dbData, PFWorld* world) : Base(dbData, world) {}

  virtual bool ProcessEvent(const PFBaseUnitEvent *pEvent);
  virtual int GetAccessibleEventsMask() const { return (1 << NDb::BASEUNITEVENT_OUTGOINGDAMAGE); }
};
}
