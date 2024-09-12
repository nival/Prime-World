#pragma once

#include "DBDayNight.h"
#include "PFWorldObjectBase.h"

namespace NWorld
{
  class DayNightController
    : public PFWorldObjectBase
    , public NonCopyable
  {
    WORLD_OBJECT_METHODS(0x15CC0840, DayNightController);
  public:
    explicit DayNightController(const CPtr<PFWorld>& world);
    virtual ~DayNightController();

    void Initialize();
    // NOTE: must be updated manually, not stepped
    void Update(const float dt);

    void Switch(const NDb::EDayNightState state, const float stateFraction = 0.f);

    float GetCurrentStateFraction() const
    {
      return Clamp(_time / GetStateDuration(), 0.f, 1.f);
    }

    float GetNightFraction() const
    {
      return _nightFraction;
    }

    bool IsDay() const
    {
      switch (_state)
      {
      case EState::Noon:
      case EState::Dusk:
        return true;
      default:
        return false;
      }
    }

    bool IsNight() const
    {
      switch (_state)
      {
      case EState::Midnight:
      case EState::Dawn:
        return true;
      default:
        return false;
      }
    }
  protected:
    DayNightController();
  private:
    struct EState
    {
      enum Enum
      {
        Noon,
        Dusk,
        Midnight,
        Dawn,
      };
    };

    virtual bool NeedToBeStepped() { return false; }

    void AdvanceTime(const float dt);
    bool AdvanceNightFraction(const float dt);
    void ApplyNightFraction(const bool transition);

    float CalculateNightFraction() const;

    inline float GetStateDuration() const
    {
      switch (_state)
      {
      case EState::Noon:
      case EState::Dusk:
        // day
        return _settings.dayDuration;
      case EState::Midnight:
      case EState::Dawn:
        // night
        return _settings.nightDuration;
      default:
        return 60.f;
      }
    }

    inline float GetTwilightDuration() const
    {
      return Min(GetStateDuration(), _settings.twilightDuration);
    }

    inline float GetTwilightStart() const
    {
      return GetStateDuration() - GetTwilightDuration();
    }

    inline bool HasTwilight() const
    {
      return
        (_settings.twilightDuration > 0.f) &&
        (_settings.twilightFraction > 0.f);
    }

    inline bool IsDayByFraction() const
    {
      return (_nightFraction < _settings.transitionThreshold);
    }

    inline bool IsNightByFraction() const
    {
      return !IsDayByFraction();
    }

    NDb::DayNightSettings _settings;

    bool _canSwitchLighting;

    ZDATA_(PFWorldObjectBase)
    ZNOPARENT(NonCopyable)
    EState::Enum _state;
    float _time;
    float _nightFraction;
    bool _cycle;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&_state); f.Add(3,&_time); f.Add(4,&_nightFraction); f.Add(5,&_cycle); return 0; }
  };
}
