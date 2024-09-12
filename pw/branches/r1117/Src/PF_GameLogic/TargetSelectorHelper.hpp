#pragma once

#include "PFTargetSelector.h"

namespace NWorld
{
  namespace Private
  {
    static inline const PFAbilityData* GetAbilityData(const PFAbilityData* const data)
    {
      return data;
    }

    static inline const PFAbilityData* GetAbilityData(const CPtr<PFAbilityInstance>& ability)
    {
      if (!IsValid(ability))
        return NULL;

      return GetAbilityData(ability->GetData());
    }

    static inline const PFAbilityData* GetAbilityData(const PFTargetSelector::RequestParams& request)
    {
      return GetAbilityData(request.pAbility);
    }
  }

  static inline bool CheckTargetCondition(const Target& target, const PFTargetSelector::RequestParams& request)
  {
    if (!request.condition)
      return true;

    return request.condition->operator()(target, Private::GetAbilityData(request));
  }

  static inline bool CheckTargetCondition(const Target& target, const ITargetCondition* const condition, const PFAbilityData* const ability)
  {
    if (!condition)
      return true;

    return condition->operator()(target, Private::GetAbilityData(ability));
  }

  static inline bool CheckTargetCondition(PFLogicObject& obj, const PFTargetSelector::RequestParams& request)
  {
    if (!request.condition)
      return true;

    const Target target(&obj);

    return request.condition->operator()(target, Private::GetAbilityData(request));
  }

  static inline bool CheckTargetCondition(const CPtr<PFLogicObject>& obj, const PFTargetSelector::RequestParams& request)
  {
    if (!request.condition)
      return true;

    const Target target(obj.GetPtr());

    return request.condition->operator()(target, Private::GetAbilityData(request));
  }

  static inline bool CheckTargetCondition(PFBaseUnit& obj, const PFTargetSelector::RequestParams& request)
  {
    if (!request.condition)
      return true;

    const Target target(&obj);

    return request.condition->operator()(target, Private::GetAbilityData(request));
  }

  static inline bool CheckTargetCondition(const CPtr<PFBaseUnit>& obj, const PFTargetSelector::RequestParams& request)
  {
    if (!request.condition)
      return true;

    const Target target(obj.GetPtr());

    return request.condition->operator()(target, Private::GetAbilityData(request));
  }

  struct CheckValidAbilityTargetCondition : ITargetCondition, NonCopyable
  {
    CheckValidAbilityTargetCondition()
    {
    }

    virtual bool operator()(const Target& target, const PFAbilityData* const ability) const
    {
      if (!target.IsUnitValid(true))
        return true;

      if (!ability || ability->IsAutoAttack())
        return true;

      return !target.GetUnit()->IsInvalidAbilityTarget();
    }
  };
}
