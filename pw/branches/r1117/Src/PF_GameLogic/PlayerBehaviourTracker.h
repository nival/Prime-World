#pragma once

#include "DBGameLogic.h"
#include "PFWorldObjectBase.h"
#include "PlayerBehaviourTracking.h"

namespace NWorld
{
  class PFWorld;
}

// TODO: better namespace
namespace NWorld
{
  class PlayerBehaviourTracker
    : public PFWorldObjectBase
    , public NonCopyable
  {
    WORLD_OBJECT_METHODS(0x15C41480, PlayerBehaviourTracker);
  public:
    struct EMark
    {
      enum Enum
      {
        None,
        Idler,
        Feeder,
        BadPlayer,
        BadZumaPlayer,
        Reported,
        ToxicPlayer,
        ToxicPlayerReported
      };

      static inline bool IsValid(const Enum value)
      {
        switch (value)
        {
        case Idler:
        case Feeder:
        case BadPlayer:
        case BadZumaPlayer:
        case Reported:
        case ToxicPlayer:
        case ToxicPlayerReported:
          return true;
        default:
          return false;
        }
      }

      static inline bool IsDetectable(const Enum value)
      {
        switch (value)
        {
        case Idler:
        case Feeder:
        case BadPlayer:
        case BadZumaPlayer:
        case ToxicPlayer:
        default:
          return false;
        }
      }

      static inline unsigned GetValidMarksMask()
      {
        enum
        {
          Mask =
            (1 << Idler) |
            (1 << Feeder) |
            (1 << BadPlayer) |
            (1 << BadZumaPlayer) |
            (1 << Reported) | 
            (1 << ToxicPlayer)|
            (1 << ToxicPlayerReported)
        };

        return static_cast<unsigned>(Mask);
      }

      static inline unsigned GetDetectedMarksMask()
      {
        enum
        {
          Mask =
            (1 << Idler) |
            (1 << Feeder) |
            (1 << BadPlayer) |
            (1 << BadZumaPlayer)
        };

        return static_cast<unsigned>(Mask);
      }

      static inline unsigned GetToxicPlayerDetectedMarksMask()
      {
        enum
        {
          Mask =(1 << ToxicPlayer)

        };

        return static_cast<unsigned>(Mask);
      }

      static inline unsigned GetReportedMarksMask()
      {
        enum
        {
          Mask =
            (1 << Reported)
        };

        return static_cast<unsigned>(Mask);
      }

      static inline unsigned GetToxicPlayerMarksMask()
      {
        enum
        {
          Mask =
          (1 << ToxicPlayerReported)
        };

        return static_cast<unsigned>(Mask);
      }

    };

    explicit PlayerBehaviourTracker(const CPtr<PFWorld>& world, const CPtr<PFPlayer>& player, const bool enabled = true);
    virtual ~PlayerBehaviourTracker();

    virtual bool Step(float deltaTime);

    void HandleEvent(const EPlayerBehaviourEvent::Enum event);

    bool IsTrackingEnabled() const
    {
      return IsArmed();
    }

    bool IsFired() const
    {
      switch (state)
      {
      case EState::Fired:
        return true;
      default:
        return false;
      }
    }

    bool IsBadBehaviourDetected() const
    {
      return ((marks & EMark::GetDetectedMarksMask()) != 0U);
    }

    bool IsToxicPlayerDetected() const
    {
      return ((marks & EMark::GetToxicPlayerDetectedMarksMask()) != 0U);
    }


    bool IsBadBehaviourReported() const
    {
      return ((marks & EMark::GetReportedMarksMask()) != 0U);
    }

    bool IsToxicPlayer() const
    {
      return ((marks & EMark::GetToxicPlayerMarksMask()) != 0U);
    }


    EMark::Enum GetFirstDetectedMark() const
    {
      return firstDetectedMark;
    }

    unsigned GetMarks() const
    {
      return marks;
    }
  protected:
    PlayerBehaviourTracker();
  private:
    struct EState
    {
      enum Enum
      {
        Disabled,
        Idle,
        Armed,
        Fired,
      };
    };

    bool IsArmed() const
    {
      switch (state)
      {
      case EState::Armed:
        return true;
      default:
        return false;
      }
    }

    bool IsDisabled() const
    {
      switch (state)
      {
      case EState::Disabled:
      case EState::Fired:
        return true;
      default:
        return false;
      }
    }

    bool HasMark(const EMark::Enum mark) const
    {
      if (!EMark::IsValid(mark))
        return false;

      const unsigned bits = 1U << static_cast<unsigned>(mark);

      return ((marks & bits) != 0U);
    }

    bool HasTracking(const EMark::Enum mark) const
    {
      if (!IsArmed())
        return false;

      if (!EMark::IsValid(mark))
        return false;

      const unsigned bits = 1U << static_cast<unsigned>(mark);

      return ((marks & bits) == 0U) && ((tracking & bits) != 0U);
    }

    void AddMark(const EMark::Enum mark);
    void AddTracking(const EMark::Enum mark);

    void Arm();

    void UpdateAndCheckFeeder(const float time);
    void CheckBadPlayer(const float time);
    void CheckBadZumaPlayer(const float time);
    bool CheckSpamMessage(const float time);
  
    void UpdateAndCheckReported();
    void UpdateAndCheckToxicPlayer(bool isBadMessage);

    void Update();

    float GetElapsedTime() const;

    int GetPlayerUserId() const;

    const NDb::Ptr<NDb::BehaviourTrackerParams> params;

    const int deathTimeHistoryCapacity;

    ZDATA_(PFWorldObjectBase)
    ZNOPARENT(NonCopyable)
    float startTime;
    float goodActionTime;

    list<float> deathTimeHistory;

    bool zuma;

    float zumaEnteredTime;
    float zumaElapsedTime;

    unsigned marks;
    unsigned tracking;
    unsigned complaints;
    



    EState::Enum state;

    EMark::Enum firstDetectedMark;

    CPtr<PFPlayer> player;
    list<float> spamDetectedHistory;
    unsigned insultComplaints;
  public:

    ZEND int operator&( IBinSaver &f ) { 
      f.Add(1,(PFWorldObjectBase*)this); 
      f.Add(2,&startTime); 
      f.Add(3,&goodActionTime); 
      f.Add(4,&deathTimeHistory); 
      f.Add(5,&zuma); 
      f.Add(6,&zumaEnteredTime); 
      f.Add(7,&zumaElapsedTime); 
      f.Add(8,&marks); 
      f.Add(9,&tracking); 
      f.Add(10,&complaints); 
      f.Add(11,&state); 
      f.Add(12,&firstDetectedMark); 
      f.Add(13,&player); 
      f.Add(14, &firstDetectedMark); 
      f.Add(15,&spamDetectedHistory); 
      f.Add(16,&insultComplaints);
      return 0; }
  };
}
