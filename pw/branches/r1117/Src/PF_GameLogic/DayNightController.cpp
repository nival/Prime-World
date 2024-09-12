#include "stdafx.h"
#include "DayNightController.h"

#include "PFAIWorld.h"
#include "PFSimpleObject.h"
#include "PFTree.h"

REGISTER_WORLD_OBJECT_NM(DayNightController, NWorld);

namespace
{
  DEV_VAR_STATIC bool g_cycle = true;
}

REGISTER_DEV_VAR("day_night_cycle", g_cycle, STORAGE_NONE);

namespace
{
  bool g_twilight = false;
}

REGISTER_VAR("day_night_twilight", g_twilight, STORAGE_NONE)

namespace NWorld
{

  DayNightController::DayNightController(const CPtr<PFWorld>& world)
    : PFWorldObjectBase(world, 0)
    , _settings()
    , _canSwitchLighting(false)
    , _state(EState::Noon)
    , _time(0.f)
    , _nightFraction(0.f)
    , _cycle(false)
  {

  }

  DayNightController::DayNightController()
  {

  }

  DayNightController::~DayNightController()
  {

  }

  void DayNightController::Initialize()
  {
    const NDb::AdvMapDescription* const mapDesc = GetWorld()->GetMapDescription();

    NI_VERIFY(!!mapDesc, "Invalid map description!", return);
    NI_VERIFY(!!mapDesc->map, "Invalid map!", return);

    _canSwitchLighting =
      IsValid(mapDesc->map->lightEnvironment) &&
      IsValid(mapDesc->map->nightLightEnvironment);

    _settings = mapDesc->map->dayNightSettings;

    NI_DATA_ASSERT(_settings.dayDuration > 0.f, "Invalid day duration!");
    NI_DATA_ASSERT(_settings.nightDuration > 0.f, "Invalid night duration!");

    Switch(_settings.initialState, _settings.initialStateFraction);

    _nightFraction = CalculateNightFraction();
    _cycle = _canSwitchLighting;

    ApplyNightFraction(true);

    {
      NScene::IScene* const scene = GetWorld()->GetScene();

      NI_VERIFY(!!scene, "Scene is not set yet!", return);

      scene->SetNightSpecularReduction(_settings.nightSpecularReduction);
    }
  }

  void DayNightController::Update(const float dt)
  {
    if (g_cycle && _cycle)
      AdvanceTime(dt);

    ApplyNightFraction(AdvanceNightFraction(dt));
  }

  void DayNightController::Switch(const NDb::EDayNightState state, const float stateFraction /*= 0.f*/)
  {
    switch (state)
    {
    case NDb::DAYNIGHTSTATE_DAY:
      _state = EState::Noon;
      break;
    case NDb::DAYNIGHTSTATE_NIGHT:
      _state = EState::Midnight;
      break;
    }

    if (stateFraction > 0.f)
      _time = GetStateDuration() * Min(stateFraction, 1.f);
    else
      _time = 0.f;

    AdvanceTime(0.f);
  }

  void DayNightController::AdvanceTime(const float dt)
  {
    if (dt > EPS_VALUE)
      _time += dt;

    const float duration = GetStateDuration();
    const float t = _time / duration;

    if (t < 1.f)
    {
      switch (_state)
      {
      case EState::Noon:
        if (g_twilight && HasTwilight() && !(_time < GetTwilightStart()))
          _state = EState::Dusk;
        break;
      case EState::Midnight:
        if (g_twilight && HasTwilight() && !(_time < GetTwilightStart()))
          _state = EState::Dawn;
        break;
      }
    }
    else
    {
      _time = (t - floorf(t)) * duration;

      switch (_state)
      {
      case EState::Noon:
      case EState::Dusk:
        _state = EState::Midnight;
        break;
      case EState::Midnight:
      case EState::Dawn:
        _state = EState::Noon;
        break;
      }

      AdvanceTime(0.f);
    }
  }

  bool DayNightController::AdvanceNightFraction(const float dt)
  {
    const float fraction = CalculateNightFraction();
    const float difference = fraction - _nightFraction;

    if (fabs(difference) < EPS_VALUE)
      return false;

    const bool day1 = IsDayByFraction();

    if (_settings.transitionDuration > 0.f)
    {
      const float speed = 1.f / _settings.transitionDuration;
      const float delta = Sign(difference) * speed * dt;

      _nightFraction += delta;

      if (difference < 0.f)
        _nightFraction = Max(_nightFraction, 0.f);
      else
        _nightFraction = Min(_nightFraction, 1.f);
    }
    else
    {
      _nightFraction = fraction;
    }

    const bool day2 = IsDayByFraction();

    return (day1 != day2);
  }

  void DayNightController::ApplyNightFraction(const bool transition)
  {
    if (_canSwitchLighting)
    {
      if (NScene::IScene* const scene = GetWorld()->GetScene())
      {
        scene->SetNightFraction(_nightFraction);
      }
    }

    if (!transition)
      return;

    const bool night = IsNightByFraction();

    if (_canSwitchLighting)
    {
      if (night)
        Render::GetLightsManager()->SetLightsDataFilterFlags(NDb::POINTLIGHTFLAGS_NIGHT);
      else
        Render::GetLightsManager()->SetLightsDataFilterFlags(NDb::POINTLIGHTFLAGS_DAY);
    }

    struct Updater : NonCopyable
    {
      explicit Updater(const bool night)
        : night(night)
      {
      }

      void operator()(PFLogicObject& object) const
      {
        switch (object.GetTypeId())
        {
        case PFTree::typeId:
        case PFMultiStateObject::typeId:
          object.UpdateDayNightState(night);
          break;
        default:
          break;
        }
      }
    private:
      Updater()
        : night(false)
      {
      }

      const bool night;
    };

    if (PFAIWorld* const aiWorld = GetWorld()->GetAIWorld())
    {
      const Updater updater(night);

      aiWorld->ForAllObjects(updater);
    }
  }

  float DayNightController::CalculateNightFraction() const
  {
    switch (_state)
    {
    case EState::Noon:
      return 0.f;
    case EState::Dusk:
      return _settings.twilightFraction;
    case EState::Midnight:
      return 1.f;
    case EState::Dawn:
      return _settings.twilightFraction;
    default:
      return 0.f;
    }
  }

}
