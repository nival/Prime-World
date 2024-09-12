#pragma once

namespace StatisticService
{
  namespace EDetectedBadBehaviour
  {
    enum Enum
    {
      None,
      AFK,
      Feeding,
      Futility,
      ToxicPlayer,
    };
  }

  struct SessionPlayerExtra
  {
    ZDATA
    bool tutorialSkipped;
    int  partySize;
    int  enemyPartySize;
    int  badBehaviourDetected; // EDetectedBadBehaviour::Enum
    bool badBehaviourReported;
    bool isGuildFight;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&tutorialSkipped); f.Add(3,&partySize); f.Add(4,&enemyPartySize); f.Add(5,&badBehaviourDetected); f.Add(6,&badBehaviourReported); f.Add(7,&isGuildFight); return 0; }

    SessionPlayerExtra()
      : tutorialSkipped(false)
      , partySize(0)
      , enemyPartySize(0)
      , badBehaviourDetected(EDetectedBadBehaviour::None)
      , badBehaviourReported(false)
      , isGuildFight(false)
    {}

    bool operator==(const SessionPlayerExtra& other) const
    {
      return
        (tutorialSkipped == other.tutorialSkipped) &&
        (partySize == other.partySize) &&
        (enemyPartySize == other.enemyPartySize) &&
        (badBehaviourDetected == other.badBehaviourDetected) &&
        (badBehaviourReported == other.badBehaviourReported) &&
        (isGuildFight == other.isGuildFight);
    }
  };
}