#include "stdafx.h"
#include "GenericAbuseController.h"

namespace NGameX
{

  GenericAbuseController::GenericAbuseController(const NDb::AbuseSettings& settings)
    : settings(settings)
    , cooldown(0.f)
    , time(0.f)
    , usages()
  {

  }

  GenericAbuseController::~GenericAbuseController()
  {

  }

  void GenericAbuseController::Update(const float dt)
  {
    if (cooldown > 0.f)
      cooldown -= dt;

    time += dt;
  }

  bool GenericAbuseController::Use()
  {
    const bool restricted = (cooldown > 0.f);

    const int allowedUsages = restricted
      ? settings.maxUsagesPerRestrictedPeriod
      : settings.maxUsagesPerPeriod;
    const float allowedPeriod = restricted
      ? settings.restrictedPeriod
      : settings.period;

    int usagesPerPeriod = 0;

    for (TUsages::iterator it = usages.begin(); it != usages.end(); ++it)
    {
      TUsages::reference usage = *it;

      usage += time;

      if (usage > allowedPeriod)
        it = usages.erase(it);
      else
        ++usagesPerPeriod;
    }

    time = 0.f;

    if (usagesPerPeriod < allowedUsages)
    {
      usages.push_front(time);

      return true;
    }

    if (!restricted || settings.refreshRestrictedPeriod)
      cooldown = settings.cooldownTime;

    return false;
  }

}
