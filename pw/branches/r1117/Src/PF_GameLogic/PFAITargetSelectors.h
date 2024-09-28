#pragma once

#include "PFDBLinker.h"
#include "PFUniTarget.h"
#include "PFTargetSelector.h"

namespace NWorld
{
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFMaximizingTargetSelector : public DBLinker<PFSingleTargetSelector, NDb::MaximizingTargetSelector>
  {
    WORLD_OBJECT_METHODS(0x9A9B0B80, PFMaximizingTargetSelector);

  protected:
    ZDATA_(DBLinker)
      CObj<PFTargetSelector> pTargetSelector;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

    PFMaximizingTargetSelector() {}
    PFMaximizingTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
    PFMaximizingTargetSelector(const NDb::MaximizingTargetSelector &db, PFWorld* world);

  public:
    virtual bool FindTarget(const RequestParams &pars, Target &target);
  };
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFDelayTargetSelector : public DBLinker<PFMultipleTargetSelector, NDb::DelayTargetSelector>
  {
    WORLD_OBJECT_METHODS(0x9A9C5C43, PFDelayTargetSelector);

  protected:
    ZDATA_(DBLinker);
    CObj<PFTargetSelector> pTargetSelector;
    hash_map<int, float> targetAppearTimes;
    float lastUpdateTime;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); f.Add(3,&targetAppearTimes); f.Add(4,&lastUpdateTime); return 0; }

    PFDelayTargetSelector() : lastUpdateTime(0.f) {}
    PFDelayTargetSelector(const NDb::DelayTargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
    PFDelayTargetSelector(const NDb::DelayTargetSelector &db, PFWorld* world);

  public:
    virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
  };
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFCheckConditionTargetSelector : public DBLinker<PFMultipleTargetSelector, NDb::CheckConditionTargetSelector>
  {
    WORLD_OBJECT_METHODS(0x9A9C5C44, PFCheckConditionTargetSelector);

  protected:
    ZDATA_(DBLinker);
    CObj<PFTargetSelector> pTargetSelector;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); return 0; }

    PFCheckConditionTargetSelector() {}
    PFCheckConditionTargetSelector(const NDb::CheckConditionTargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
    PFCheckConditionTargetSelector(const NDb::CheckConditionTargetSelector &db, PFWorld* world);

  public:
    virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
  };
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFNotTargetOfSameAbilitySelector : public DBLinker<PFMultipleTargetSelector, NDb::NotTargetOfSameAbilitySelector>
  {
    WORLD_OBJECT_METHODS(0x9A9C6C80, PFNotTargetOfSameAbilitySelector);

  protected:
    ZDATA_(DBLinker);
    CObj<PFTargetSelector> pTargetSelector;
    CObj<PFTargetSelector> pCastersSelector;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pTargetSelector); f.Add(3,&pCastersSelector); return 0; }

    PFNotTargetOfSameAbilitySelector() {}
    PFNotTargetOfSameAbilitySelector(const NDb::NotTargetOfSameAbilitySelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
    PFNotTargetOfSameAbilitySelector(const NDb::NotTargetOfSameAbilitySelector &db, PFWorld* world);

  public:
    virtual void ForAllTargets(ITargetAction &action, const RequestParams &pars);
  };
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class PFDamagingLinksTargetSelector : public DBLinker<PFSingleTargetSelector, NDb::DamagingLinksTargetSelector>
  {
    WORLD_OBJECT_METHODS(0x9A9B0B90, PFDamagingLinksTargetSelector);

  protected:
    ZDATA_(DBLinker)
    CObj<PFTargetSelector> pLinkEndsSelector;
    CObj<PFTargetSelector> pLinkTargetsSelector;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(DBLinker*)this); f.Add(2,&pLinkEndsSelector); f.Add(3,&pLinkTargetsSelector); return 0; }

    PFDamagingLinksTargetSelector() {}
    PFDamagingLinksTargetSelector(const NDb::TargetSelector &db) { NI_ALWAYS_ASSERT("Bad constructor") }
    PFDamagingLinksTargetSelector(const NDb::DamagingLinksTargetSelector &db, PFWorld* world);

  public:
    virtual bool FindTarget(const RequestParams &pars, Target &target);
  };
}