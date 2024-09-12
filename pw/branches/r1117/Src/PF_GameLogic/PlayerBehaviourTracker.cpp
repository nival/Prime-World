#include "stdafx.h"
#include "PlayerBehaviourTracker.h"

#include "PFWorld.h"
#include "PFAIWorld.h"

#include "Server/Statistic/StatisticsCommonTypes.h"

REGISTER_WORLD_OBJECT_NM(PlayerBehaviourTracker, NWorld);

namespace
{
  using NWorld::PFWorld;
  using NWorld::PFAIWorld;

  const NDb::Ptr<NDb::BehaviourTrackerParams>& GetBehaviourTrackerParams(const CPtr<PFWorld>& world)
  {
    static const NDb::Ptr<NDb::BehaviourTrackerParams> l_dummy;

    NI_VERIFY(IsValid(world), "World is not set!", return l_dummy);

    PFAIWorld* const aiWorld = world->GetAIWorld();

    NI_VERIFY(!!aiWorld, "AIWorld is not set!", return l_dummy);

    const NDb::Ptr<NDb::BehaviourTrackerParams>& params = aiWorld->GetBahaviourTrackerParams();

    NI_DATA_ASSERT(IsValid(params), "Behaviour tracker params must be defined");

    return params;
  }

  const int GetBehaviourTrackerDeathHistoryCapacity(const CPtr<PFWorld>& world)
  {
    const NDb::Ptr<NDb::BehaviourTrackerParams>& params = GetBehaviourTrackerParams(world);

    if (!IsValid(params))
      return 1;

    // 25 смертей - это даже слишком
    return Clamp(params->feederDeathCount, 0, 25);
  }

  inline const char* GetBehaviourEventName(const EPlayerBehaviourEvent::Enum event)
  {
    switch (event)
    {
    case EPlayerBehaviourEvent::Gone:
      return "Gone";
    case EPlayerBehaviourEvent::Died:
      return "Died";
    case EPlayerBehaviourEvent::GotNaftaForKill:
      return "GotNaftaForKill";
    case EPlayerBehaviourEvent::ServedTeamNaftaForKill:
      return "ServedNaftaForKill";
    case EPlayerBehaviourEvent::ServedTeamNaftaForPresence:
      return "ServedNaftaForPresence";
    case EPlayerBehaviourEvent::EnteredZuma:
      return "EnteredZuma";
    case EPlayerBehaviourEvent::LeftZuma:
      return "LeftZuma";
    case EPlayerBehaviourEvent::TookScroll:
      return "TookScroll";
    case EPlayerBehaviourEvent::GaveScroll:
      return "GaveScroll";
    case EPlayerBehaviourEvent::GotBadBehaviourComplaint:
      return "GotBadBehaviourComplaint";
    case EPlayerBehaviourEvent::GotToxicPlayerComplaint:
      return "GotToxicPlayerComplaint";
    case EPlayerBehaviourEvent::AutoMuteMessage:
        return "MessageInFilter";
    case EPlayerBehaviourEvent::MessageInFilter:
      return "MessageInFilter";
    case EPlayerBehaviourEvent::CapsMeessage:
      return "CapsMeessage";
    case EPlayerBehaviourEvent::AutoMuteMessageLength: 
      return "AutoMuteMessageLength";
    case EPlayerBehaviourEvent::SpamDetected:
      return "SpamDetected";
    default:
      return "N/A";
    }
  }

  inline const char* GetBehaviourMarkName(const NWorld::PlayerBehaviourTracker::EMark::Enum mark)
  {
    switch (mark)
    {
    case NWorld::PlayerBehaviourTracker::EMark::None:
      return "None";
    case NWorld::PlayerBehaviourTracker::EMark::Idler:
      return "Idler";
    case NWorld::PlayerBehaviourTracker::EMark::Feeder:
      return "Feeder";
    case NWorld::PlayerBehaviourTracker::EMark::BadPlayer:
      return "BadPlayer";
    case NWorld::PlayerBehaviourTracker::EMark::BadZumaPlayer:
      return "BadZumaPlayer";
    case NWorld::PlayerBehaviourTracker::EMark::Reported:
      return "Reported";
    case NWorld::PlayerBehaviourTracker::EMark::ToxicPlayer:
      return "ToxicPlayer";
    case NWorld::PlayerBehaviourTracker::EMark::ToxicPlayerReported:
      return "ToxicPlayerReported";
    default:
      return "N/A";
    }
  }
}

namespace NWorld
{

  PlayerBehaviourTracker::PlayerBehaviourTracker()
    : params()
    , deathTimeHistoryCapacity(0)
    , deathTimeHistory()
    , spamDetectedHistory()
    , state(EState::Disabled)
    
  {

  }

  PlayerBehaviourTracker::PlayerBehaviourTracker(const CPtr<PFWorld>& world, const CPtr<PFPlayer>& player, const bool enabled /*= true*/)
    : PFWorldObjectBase(world, 0)
    , params(GetBehaviourTrackerParams(world))
    , deathTimeHistoryCapacity(GetBehaviourTrackerDeathHistoryCapacity(world))
    , startTime(0.f)
    , goodActionTime(0.f)
    , deathTimeHistory()
    , spamDetectedHistory()
    , zuma(false)
    , zumaEnteredTime(0.f)
    , zumaElapsedTime(0.f)
    , marks(0U)
    , tracking(0U)
    , complaints(0U)
    , insultComplaints(0U)
    , state(EState::Disabled)
    , firstDetectedMark(EMark::None)
    , player(player)
  {
    if (!IsValid(params))
      return;
    if (!enabled)
      return;

    const bool trackIdler = true;
    const bool trackFeeder =
      (deathTimeHistoryCapacity > 0) &&
      (params->feederDeathCount > 0) &&
      (params->feederDeathTime > 0);
    const bool trackBadPlayer =
      (params->goodActionTimeout > 0);
    const bool trackBadZumaPlayer =
      (params->goodZumaActionTimeout > 0);
    const bool trackReports =  (params->badBehaviourComplaintsThreshold > 0);
    const bool trackMessage =(params->insultComplaintsThreshold);

    if (trackIdler)
      AddTracking(EMark::Idler);
    if (trackFeeder)
      AddTracking(EMark::Feeder);
    if (trackBadPlayer)
      AddTracking(EMark::BadPlayer);
    if (trackBadZumaPlayer)
      AddTracking(EMark::BadZumaPlayer);
    if (trackReports)
      AddTracking(EMark::Reported);
    if (trackMessage)
      AddTracking(EMark::ToxicPlayer);
    if (trackMessage)
      AddTracking(EMark::ToxicPlayerReported);

    const bool disabled = ((tracking & EMark::GetValidMarksMask()) == 0U);

    if (disabled)
      return;

    if (params->idleTime < 1)
    {
      Arm();
    }
    else
    {
      const float time = GetElapsedTime();

      startTime = time + static_cast<float>(params->idleTime);

      state = EState::Idle;
    }
  }

  PlayerBehaviourTracker::~PlayerBehaviourTracker()
  {

  }

  void PlayerBehaviourTracker::AddMark(const EMark::Enum mark)
  {
    if (!EMark::IsValid(mark))
      return;

    const unsigned bits = 1U << static_cast<unsigned>(mark);

    marks |= bits;
    tracking &= ~bits;

    if (!EMark::IsValid(firstDetectedMark))
    {
      if (EMark::IsDetectable(mark))
        firstDetectedMark = mark;
    }

    const bool fired =
      (IsBadBehaviourDetected() &&
      IsBadBehaviourReported())  || (IsToxicPlayer()  && IsToxicPlayerDetected()) ;

    if (fired)
      state = EState::Fired;

    DevTrace("### behaviour mark: %s (uid=%d)", GetBehaviourMarkName(mark), GetPlayerUserId());
  }

  void PlayerBehaviourTracker::AddTracking(const EMark::Enum mark)
  {
    if (!EMark::IsValid(mark))
      return;

    const unsigned bits = 1U << static_cast<unsigned>(mark);

    tracking |= bits;
  }

  void PlayerBehaviourTracker::Arm()
  {
    const float time = GetElapsedTime();

    goodActionTime = time;

    zumaEnteredTime = zuma ? time : 0.f;
    zumaElapsedTime = 0.f;

    marks = 0U;
    complaints = 0U;

    firstDetectedMark = EMark::None;

    state = EState::Armed;

    DevTrace("### behaviour tracker: armed (uid=%d)", GetPlayerUserId());
  }

  void PlayerBehaviourTracker::UpdateAndCheckFeeder(const float time)
  {
    NI_ASSERT(HasTracking(EMark::Feeder), "Invalid state");

    while (deathTimeHistory.size() >= deathTimeHistoryCapacity)
      deathTimeHistory.pop_front();

    deathTimeHistory.push_back(time);

    const int deathCount = static_cast<int>(deathTimeHistory.size());

    if (deathCount < params->feederDeathCount)
      return;

    NI_ASSERT(deathCount == params->feederDeathCount, "Invariant");

    const int checkTime = static_cast<int>(floor(time - deathTimeHistory.front()));

    if (checkTime > params->feederDeathTime)
      return;

    AddMark(EMark::Feeder);
  }
  bool PlayerBehaviourTracker::CheckSpamMessage(const float time)
  {
    NI_ASSERT(HasTracking(EMark::ToxicPlayer), "Invalid state");

    while (spamDetectedHistory.size() >= params->autoMuteMessagePerTime)
      spamDetectedHistory.pop_front();

    spamDetectedHistory.push_back(time);

    const int messCount = static_cast<int>(spamDetectedHistory.size());

    if (messCount < params->autoMuteMessagePerTime)
      return false;

    NI_ASSERT(messCount == params->autoMuteMessagePerTime, "Invariant");
    
    const int checkTime = static_cast<int>(floor(time - deathTimeHistory.front()));

    if (checkTime > params->autoMuteTimeLimit)
      return false;

    return true;

  }
  void PlayerBehaviourTracker::CheckBadPlayer(const float time)
  {
    NI_ASSERT(HasTracking(EMark::BadPlayer), "Invalid state");

    const int checkTime = static_cast<int>(floor(time - goodActionTime));

    if (checkTime < params->goodActionTimeout)
      return;

    AddMark(EMark::BadPlayer);
  }

  void PlayerBehaviourTracker::CheckBadZumaPlayer(const float time)
  {
    NI_ASSERT(HasTracking(EMark::BadZumaPlayer), "Invalid state");

    const int checkTime = zuma
      ? static_cast<int>(floor(time - zumaEnteredTime))
      : static_cast<int>(floor(zumaElapsedTime));

    if (checkTime < params->goodZumaActionTimeout)
      return;

    AddMark(EMark::BadZumaPlayer);
  }

  void PlayerBehaviourTracker::UpdateAndCheckToxicPlayer(bool isBadMessage=false)
  {
    NI_ASSERT(HasTracking(EMark::ToxicPlayerReported), "Invalid state");

    const int checkReports = static_cast<int>(insultComplaints);

    if (checkReports < params->insultComplaintsThreshold && isBadMessage)
      return;
    DevTrace("### behaviour: ToxicPlayer detected! (uid=%d)", GetPlayerUserId());
    AddMark(EMark::ToxicPlayerReported);
  }

  void PlayerBehaviourTracker::UpdateAndCheckReported()
  {
    NI_ASSERT(HasTracking(EMark::Reported), "Invalid state");

    ++complaints;

    const int checkReports = static_cast<int>(complaints);

    if (checkReports < params->badBehaviourComplaintsThreshold)
      return;

    AddMark(EMark::Reported);
  }
  

  bool PlayerBehaviourTracker::Step(float deltaTime)
  {
    if (IsDisabled())
    {
      /* placeholder */
    }
    else
    {
      Update();
    }

    return PFWorldObjectBase::Step(deltaTime);
  }

  void PlayerBehaviourTracker::HandleEvent(const EPlayerBehaviourEvent::Enum event)
  {
    if (IsDisabled())
      return;

    DevTrace("### behaviour event: %s (uid=%d)", GetBehaviourEventName(event), GetPlayerUserId());

    const float time = GetElapsedTime();

    switch (event)
    {
    case EPlayerBehaviourEvent::Gone:
      if (HasTracking(EMark::Idler))
      {
        AddMark(EMark::Idler);
      }
      break;
    case EPlayerBehaviourEvent::Died:
      if (HasTracking(EMark::Feeder))
      {
        UpdateAndCheckFeeder(time);
      }
      break;
    case EPlayerBehaviourEvent::GotNaftaForKill:
    case EPlayerBehaviourEvent::ServedTeamNaftaForKill:
    case EPlayerBehaviourEvent::ServedTeamNaftaForPresence:
      if (HasTracking(EMark::BadPlayer))
      {
        goodActionTime = time;
      }
      break;
    case EPlayerBehaviourEvent::EnteredZuma:
      if (zuma)
      {
        DevTrace("### behaviour: %s is not applicable! (uid=%d)", GetBehaviourEventName(event), GetPlayerUserId());
      }
      
      zuma = true; 
      if (HasTracking(EMark::BadZumaPlayer))
      {
        zumaEnteredTime = time;
      }
      break;
    case EPlayerBehaviourEvent::LeftZuma:
      if (!zuma)
      {
        DevTrace("### behaviour: %s is not applicable! (uid=%d)", GetBehaviourEventName(event), GetPlayerUserId());
      }

      zuma = false;

      if (HasTracking(EMark::BadZumaPlayer))
      {
        NI_ASSERT(!(zumaEnteredTime > time), "Invariant");

        zumaElapsedTime += time;
        zumaElapsedTime -= zumaEnteredTime;

        CheckBadZumaPlayer(time);
      }
      break;
    case EPlayerBehaviourEvent::TookScroll:
      if (!zuma)
      {
        DevTrace("### behaviour: %s is not applicable! (uid=%d)", GetBehaviourEventName(event), GetPlayerUserId());
        break;
      }

      if (HasTracking(EMark::BadPlayer))
      {
        goodActionTime = time;
      }
      break;
    case EPlayerBehaviourEvent::GaveScroll:
      if (!zuma)
      {
        DevTrace("### behaviour: %s is not applicable! (uid=%d)", GetBehaviourEventName(event), GetPlayerUserId());
        break;
      }

      if (HasTracking(EMark::BadPlayer))
      {
        goodActionTime = time;
      }
      if (HasTracking(EMark::BadZumaPlayer))
      {
        zumaEnteredTime = time;
        zumaElapsedTime = 0.f;
      }
      break;
    case EPlayerBehaviourEvent::SpamDetected:
      DevTrace("### behaviour: %s is applicable! (uid=%d)", GetBehaviourEventName(event), GetPlayerUserId());
      if (HasTracking(EMark::ToxicPlayer))
      {
        bool res = CheckSpamMessage(time);
        UpdateAndCheckToxicPlayer(res);
      }
      break;
    case EPlayerBehaviourEvent::MessageInFilter:
    case EPlayerBehaviourEvent::CapsMeessage:
    case EPlayerBehaviourEvent::AutoMuteMessageLength: 
    case EPlayerBehaviourEvent::AutoMuteMessage:
        DevTrace("### behaviour: %s is applicable! (uid=%d)", GetBehaviourEventName(event), GetPlayerUserId());
        if (HasTracking(EMark::ToxicPlayer))
        {
          UpdateAndCheckToxicPlayer(true);
        }
      break;
    case EPlayerBehaviourEvent::GotToxicPlayerComplaint:
      if (HasTracking(EMark::ToxicPlayer))
      {
        ++insultComplaints;
      }
      break;

    default:
      break;
    }
  }

  void PlayerBehaviourTracker::Update()
  {
    struct Local
    {
      static bool IsPlayerInZuma(const CPtr<PFPlayer>& player)
      {
        if (!player)
          return false;

        const PFBaseHero* const hero = player->GetHero();

        if (!hero)
          return false;

        return hero->CheckFlagType(NDb::UNITFLAGTYPE_INMINIGAME);
      }
    };

    const float time = GetElapsedTime();

    if (state == EState::Idle)
    {
      if (time < startTime)
        return;

      Arm();
    }

    NI_VERIFY(state == EState::Armed, "Must be armed at this point", state = EState::Armed);

    {
      const bool actual_zuma_state = Local::IsPlayerInZuma(player);

      if (zuma != actual_zuma_state)
      {
        if (actual_zuma_state)
          HandleEvent(EPlayerBehaviourEvent::EnteredZuma);
        else
          HandleEvent(EPlayerBehaviourEvent::LeftZuma);
      }
    }

    if (HasTracking(EMark::BadPlayer))
    {
      NI_ASSERT(!(goodActionTime > time), "Invariant");

      CheckBadPlayer(time);
    }

    if (HasTracking(EMark::BadZumaPlayer) && zuma)
    {
      NI_ASSERT(!(zumaEnteredTime > time), "Invariant");

      CheckBadZumaPlayer(time);
    }
    /*
    if (HasTracking(EMark::ToxicPlayer))
    {
        UpdateAndCheckToxicPlayer();
    }*/

  }

  float PlayerBehaviourTracker::GetElapsedTime() const
  {
    NI_VERIFY(IsValid(pWorld), "World is invalid!", return 0.f);

    // TODO: ?
    const PFWorld* const world = static_cast<const PFWorld*>(pWorld.GetPtr());

    return world->GetTimeElapsed();
  }

  int PlayerBehaviourTracker::GetPlayerUserId() const
  {
    if (!IsValid(player))
      return -1;

    return player->GetUserID();
  }

} // namespace NWorld

namespace PlayerBehaviourTracking
{
  namespace Private
  {
    using NWorld::PlayerBehaviourTracker;

    void DispatchEventImpl(const CObj<PlayerBehaviourTracker>& tracker, const EPlayerBehaviourEvent::Enum event)
    {
      if (!IsValid(tracker))
        return;

      tracker->HandleEvent(event);
    }

    bool ShouldTrackBehaviourImpl(const CObj<PlayerBehaviourTracker>& tracker)
    {
      if (!IsValid(tracker))
        return false;

      return tracker->IsTrackingEnabled();
    }

    void UpdatePlayerStatisticsImpl(const CObj<PlayerBehaviourTracker>& tracker, StatisticService::RPC::SessionClientResultsPlayer& stats)
    {
      if (!IsValid(tracker))
        return;

      switch (tracker->GetFirstDetectedMark())
      {
      case PlayerBehaviourTracker::EMark::Idler:
        stats.extra.badBehaviourDetected = StatisticService::EDetectedBadBehaviour::AFK;
        break;
      case PlayerBehaviourTracker::EMark::Feeder:
        stats.extra.badBehaviourDetected = StatisticService::EDetectedBadBehaviour::Feeding;
        break;
      case PlayerBehaviourTracker::EMark::BadPlayer:
      case PlayerBehaviourTracker::EMark::BadZumaPlayer:
        stats.extra.badBehaviourDetected = StatisticService::EDetectedBadBehaviour::Futility;
        break;
      case PlayerBehaviourTracker::EMark::ToxicPlayer:
        stats.extra.badBehaviourDetected = StatisticService::EDetectedBadBehaviour::ToxicPlayer;
        break;
      default:
        stats.extra.badBehaviourDetected = StatisticService::EDetectedBadBehaviour::None;
      }

      {
          stats.extra.badBehaviourReported = tracker->IsBadBehaviourReported() || tracker->IsToxicPlayer();
      }
    }

    int UpdateFastCRCImpl(const CObj<PlayerBehaviourTracker>& tracker, IBinSaver& f, const int indexBase)
    {
      NI_ASSERT(IsValid(tracker), "PlayerBehaviourTracker must exist!");

      int value = (IsValid(tracker) ? tracker->GetMarks() : 0);

      f.Add(indexBase, &value);

      return 1;
    }

  } // namespace Private
} // namespace PlayerBehaviourTracking
