using System;
using System.Collections.Generic;
using System.Linq;
using BusinessLogic.Game;


namespace StatisticService.RPC
{
  public class SessionStartEvent : ISerializable
  {
    public long sessionid;
    public ulong mmPersistentId;
    public string map;
    public string server;
    public string cluster;
    public string serverAddr;
    public int sessionType;
    public List<SessionStartPlayer> players = new List<SessionStartPlayer>();

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref sessionid);
      s.Add(ref mmPersistentId);
      s.Add(ref map);
      s.Add(ref server);
      s.Add(ref cluster);
      s.Add(ref serverAddr);
      s.Add(ref sessionType);
      s.Add(players);
    }

    public override string ToString()
    {
      return String.Format("SessionStartEvent(sessionid = {0}, mmPersistentId={1:x016}, map = {2}, server = {3}, cluster = {4}, serverAddr = {5}, sessionType = {6}, players = List({7}))",
                           sessionid, mmPersistentId, map, server, cluster, serverAddr, sessionType, String.Join(", ", players.Select(p => p.ToString()).ToArray()));
    }
  }



  public class SessionStartPlayer : ISerializable
  {
    public int userid;
    public int faction;
    public int sex;
    public int heroid;
    public string nickname;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref userid);
      s.Add(ref faction);
      s.Add(ref sex);
      s.Add(ref heroid);
      s.Add(ref nickname);
    }

    public override string ToString()
    {
      return String.Format("SessionStartPlayer(userid = {0}; faction = {1}, sex = {2}, heroid = {3}, nick = {4})",
                           userid, faction, sex, heroid, nickname);
    }

    public static explicit operator SessionStartPlayerInfo(SessionStartPlayer value)
    {
      return new SessionStartPlayerInfo
               {
                 UserId = value.userid,
                 Faction = value.faction,
                 Sex = value.sex,
                 HeroId = value.heroid,
                 Nickname = value.nickname
               };
    }
  }



  //Clone of C++ Peered::EGameFinishClientState::Enum
  public enum EGameFinishClientState
  {
    NotConnected = 0,
    FinishedGame = 1,
    Disconnected = 2
  }


  public class SessionServerResultsPlayer : ISerializable
  {
    public int userid;
    public int finishStatus; //Peered::EGameFinishClientState::Enum

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref userid);
      s.Add(ref finishStatus);
    }

    public override string ToString()
    {
      return String.Format("SessionServerResultsPlayer(userid = {0}; finishStatus = {1})",
                           userid, finishStatus);
    }
  };


  public class SessionClientResults : ISerializable
  {
    public int sideWon;
    public int surrenderVote;
    public List<SessionClientResultsPlayer> players = new List<SessionClientResultsPlayer>();

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref sideWon);
      s.Add(ref surrenderVote);
      s.Add(players);
    }

    public override string ToString()
    {
      return String.Format("SessionClientResults(sideWon={0}, surrenderVote = {1}, players = List({2}))",
                           sideWon, surrenderVote, String.Join(", ", players.Select(p => p.ToString()).ToArray()));
    }
  }


  public class SessionResultEvent : ISerializable
  {
    public int result;
    public long sessionid;
    public SessionClientResults clientData = new SessionClientResults();
    public List<SessionServerResultsPlayer> serverPlayersInfo = new List<SessionServerResultsPlayer>();

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref result);
      s.Add(ref sessionid);
      s.Add(clientData);
      s.Add(serverPlayersInfo);
    }

    public override string ToString()
    {
      return String.Format("SessionResultEvent(result={0}, sessionid = {1}, clientData = {2}, serverPlayersInfo = {3})",
                           result, sessionid, clientData, serverPlayersInfo);
    }
  }


  public class SessionPlayerScoring : ISerializable
  {
    public int score;
    public int specialPoints;
    public int finalLevel;
    public int kills;
    public int deaths;
    public int assists;
    public int enemyCreepsKilled;
    public int neutralCreepsKilled;
    public int totalNumTowersKilled;
    public int totalNumTowersAssisted;
    public int flagsRaised;
    public int flagsDestroyed;
    public int totalMedalsCountFailed;
    public int totalMedalsCountDone;
    public int totalMedalsCountSilver;
    public int totalMedalsCountGold;
    public float timeInDeath;
    public float damageDealedMagic;
    public float damageDealedMaterial;
    public float damageDealedPure;
    public float damageDealedTotal;
    public float damageReceivedMagic;
    public float damageReceivedMaterial;
    public float damageReceivedPure;
    public float damageReceivedTotal;
    public int sexHelp;
    public float healedAmount;
    public int totalNumQuartersDestroyed;
    public int numBossKillsAssist;
    public int numCatKillAssist;
    public int numDragonKillAssist;
    public int numKillsTotal;
    public float money;
    public int currentKillSpree;
    public int currentDeathSpree;
    public float saviourTime;
    public float timeInIdle;
    public int killedByNeutrals;
    public int usedPotions;
    public float timeAtHome;
    public int teleportsByAbility;
    public int glyphsPickuped;
    public int achievScore;
    public float damageReceivedFromHeroesMagic;
    public float damageReceivedFromHeroesMaterial;
    public float damageReceivedFromHeroesPure;
    public float damageReceivedFromHeroesTotal;
    public float damageDealedToHeroesMagic;
    public float damageDealedToHeroesMaterial;
    public float damageDealedToHeroesPure;
    public float damageDealedToHeroesTotal;
    public int grandScore;
    public int timeElapsed;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add( ref score );
      s.Add( ref specialPoints );
      s.Add( ref finalLevel );
      s.Add( ref kills );
      s.Add( ref deaths );
      s.Add( ref assists );
      s.Add( ref enemyCreepsKilled );
      s.Add( ref neutralCreepsKilled );
      s.Add( ref totalNumTowersKilled );
      s.Add( ref totalNumTowersAssisted );
      s.Add( ref flagsRaised );
      s.Add( ref flagsDestroyed );
      s.Add( ref totalMedalsCountFailed );
      s.Add( ref totalMedalsCountDone );
      s.Add( ref totalMedalsCountSilver );
      s.Add( ref totalMedalsCountGold );
      s.Add( ref timeInDeath );
      s.Add( ref damageDealedMagic );
      s.Add( ref damageDealedMaterial );
      s.Add( ref damageDealedPure );
      s.Add( ref damageDealedTotal );
      s.Add( ref damageReceivedMagic );
      s.Add( ref damageReceivedMaterial );
      s.Add( ref damageReceivedPure );
      s.Add( ref damageReceivedTotal );
      s.Add( ref sexHelp );
      s.Add( ref healedAmount );
      s.Add( ref totalNumQuartersDestroyed );
      s.Add( ref numBossKillsAssist );
      s.Add( ref numCatKillAssist);
      s.Add( ref numDragonKillAssist);
      s.Add( ref numKillsTotal );
      s.Add( ref money );
      s.Add( ref currentKillSpree );
      s.Add( ref currentDeathSpree );
      s.Add( ref saviourTime );
      s.Add( ref timeInIdle );
      s.Add( ref killedByNeutrals );
      s.Add( ref usedPotions );
      s.Add( ref timeAtHome );
      s.Add( ref teleportsByAbility );
      s.Add( ref glyphsPickuped );
      s.Add( ref achievScore );
      s.Add( ref damageReceivedFromHeroesMagic );
      s.Add( ref damageReceivedFromHeroesMaterial );
      s.Add( ref damageReceivedFromHeroesPure );
      s.Add( ref damageReceivedFromHeroesTotal );
      s.Add( ref damageDealedToHeroesMagic );
      s.Add( ref damageDealedToHeroesMaterial );
      s.Add( ref damageDealedToHeroesPure );
      s.Add( ref damageDealedToHeroesTotal );
      s.Add( ref grandScore );
      s.Add( ref timeElapsed );
    }

    public override string ToString()
    {
      return String.Format("SessionPlayerScoring(score={0}; specialPoints={1}, finalLevel={2}, kills={3}, deaths={4}, assists={5}, enemyCreepsKilled={6}, neutralCreepsKilled={7})",
                           score, specialPoints, finalLevel, kills, deaths, assists, enemyCreepsKilled, neutralCreepsKilled);
    }
  };

  // StatisticService::EDetectedBadBehaviour::Enum (C++)
  public enum EDetectedBadBehaviour
  {
    None,
    AFK,
    Feeding,
    Futility,
  }

  public class SessionPlayerExtra : ISerializable
  {
    public bool tutorialSkipped;
    public int  partySize;
    public int  enemyPartySize;
    public int  badBehaviourDetected; // EDetectedBadBehaviour (above) <- StatisticService::EDetectedBadBehaviour::Enum (C++)
    public bool badBehaviourReported;
    public bool isGuildFight;
    public override void Serialize(IChunklessSerializer s)
    {
        s.Add(ref tutorialSkipped);
        s.Add(ref partySize);
        s.Add(ref enemyPartySize);
        s.Add(ref badBehaviourDetected);
        s.Add(ref badBehaviourReported);
        s.Add(ref isGuildFight);
    }

    public override string ToString()
    {
        return String.Format("SessionPlayerExtra (tutorialSkipped={0}, enemyPartySize={1}, enemyPartySize={2}, badBehaviourDetected={3}, badBehaviourReported={4}, isGuildFight={5}",
          tutorialSkipped, partySize, enemyPartySize, badBehaviourDetected, badBehaviourReported, isGuildFight);
    }
  };

  public class SessionClientResultsPlayer : ISerializable
  {
    public int userid;
    public SessionPlayerScoring scoring = new SessionPlayerScoring();
    public SessionPlayerExtra extra = new SessionPlayerExtra();

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref userid);
      s.Add(scoring);
      s.Add(extra);
    }

    public override string ToString()
    {
      return String.Format("SessionClientResultsPlayer(userid={0}; scoring={1}; extra={2})",
                           userid, scoring, extra);
    }
  }


  public class MMakingMember : ISerializable
  {
    public int    userid;
    public int    faction;
    public int    sex;
    public int    heroid;
    public int    heroRating;
    public int    playerRating;
    public int    guardRating;
    public float  force;
    public int    partyId;
    public float  waitTime;
    public int    loseStreak;
    public int    fameLevel;
    public int    basket; //mmaking::EBasket::Enum { Undefined(-1), Newbie(0), Normal(1), Leaver (2) }
    public int    lobbyReaction; //ELobbyReaction
    public float  lobbyReactionTime;
    public int    original_faction;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref userid);
      s.Add(ref faction);
      s.Add(ref sex);
      s.Add(ref heroid);
      s.Add(ref heroRating );
      s.Add(ref playerRating );
      s.Add(ref guardRating );
      s.Add(ref force);
      s.Add(ref partyId);
      s.Add(ref waitTime);
      s.Add(ref loseStreak);
      s.Add(ref fameLevel);
      s.Add(ref basket);
      s.Add(ref lobbyReaction);
      s.Add(ref lobbyReactionTime);
      s.Add(ref original_faction);
    }

    public override string ToString()
    {
      return String.Format("MMakingMember(userid = {0}; faction = {1}, sex = {2}, heroid = {3}, heroRating = {4}, playerRating = {5}, guardRating = {6}, force = {7}, partyId = {8}, waitTime = {9}, loseStreak = {10}, fameLevel = {11}, basket = {12}, lobbyReaction = {13}, lobbyReactionTime = {14}, original_faction = {15} )",
                           userid, faction, sex, heroid, heroRating, playerRating, guardRating, force, partyId, waitTime, loseStreak, fameLevel, basket, lobbyReaction, lobbyReactionTime, original_faction);
    }

    public static explicit operator MMakingPlayerInfo(MMakingMember value)
    {
      return new MMakingPlayerInfo
               {
                 UserId = value.userid,
                 Faction = value.faction,
                 Sex = value.sex,
                 HeroId = value.heroid,
                 Rating = value.heroRating,
                 PlayerRating = value.playerRating,
                 Force = value.force,
                 PartyId = value.partyId,
                 WaitTime = value.waitTime,
                 LoseStreak = value.loseStreak,
                 FameLevel = value.fameLevel,
                 Basket = value.basket,
                 LobbyReaction = value.lobbyReaction,
                 LobbyReactionTime = value.lobbyReactionTime
               };
    }
  }


  public class MMakingGame : ISerializable
  {
    public ulong persistentId;
    public int status; //ELobbyGameStatus
    public int basket; //mmaking::EBasket::Enum { Undefined(-1), Newbie(0), Normal(1), Leaver(2) }
    public List<MMakingMember> members = new List<MMakingMember>();
    public string map;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref persistentId);
      s.Add(ref status);
      s.Add(ref basket);
      s.Add(members);
      s.Add(ref map);
    }

    public override string ToString()
    {
      return String.Format("MMakingGame(persistentId = {0:x016}; status = {1}, basket = {2}, members = {3} pcs, map = {4} )",
                           persistentId, status, basket, members.Count, map );
    }
  }



  public class MMakingCanceled : ISerializable
  {
    public string map;
    public MMakingMember member = new MMakingMember();

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref map);
      s.Add(member);
    }

    public override string ToString()
    {
      return String.Format("MMakingCanceled(map = {0}, member = {1} )", map, member.ToString());
    }
  }



  public class ExceedingStepTimeInfoServer : ISerializable
  {
    public long sessionId;
    public int currentStep;
    public long startTime;
    public long finishTime;
    public int stepCount;
    public int stepTimeMin;
    public int stepTimeMax;
    public int stepTimeAvg;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref sessionId);
      s.Add(ref currentStep);
      s.Add(ref startTime);
      s.Add(ref finishTime);
      s.Add(ref stepCount);
      s.Add(ref stepTimeMin);
      s.Add(ref stepTimeMax);
      s.Add(ref stepTimeAvg);
    }

    public override string ToString()
    {
      return String.Format("ExceedingStepTimeInfoServer(SessionId={0},CurrentStep={1},StartTime={2},FinishTime={3},StepCount={4},StepTimeMin={5},StepTimeMax={6},StepTimeAvg={7})",
                           sessionId, currentStep, startTime, finishTime, stepCount, stepTimeMin, stepTimeMax, stepTimeAvg);
    }
  }


  public enum ReconnectType
  {
    Fast,
    Normal,
    Full
  }

  public enum ReconnectResult
  {
    Success,
    Failure,
    Cheated,
    GameFinished,
    WorldRequestFailed,
    NoReconnectIface,
    Disabled,
    WrongSesionState,
    ClientNotFound,
    IdAndIndexMissmatch,
    WrongStep,
    Disconnected
  }

  public class ReconnectAttemptInfo : ISerializable
  {
    public long sessionId;
    public int userId;
    public int currentStep;
    public int reconnectType; // ReconnectType
    public int resultCode;    // ReconnectResult

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref sessionId);
      s.Add(ref userId);
      s.Add(ref currentStep);
      s.Add(ref reconnectType);
      s.Add(ref resultCode);
    }

    public override string ToString()
    {
      return String.Format("ReconnectAttemptInfo(SessionId:{0},UserId:{1},CurrentStep:{2},ReconnectType:{3},ResultCode:{4})",
                           sessionId, userId, currentStep, reconnectType, resultCode);
    }
  }

  public class SessionTrafficInfo : ISerializable
  {
    public long sessionId;
    public int totalIn;
    public int totalOut;
    public float avgOutPerStep;
    public int maxOutPerStep;
    public int totalInReconnect;
    public int totalOutReconnect;
    public float avgOutReconnect;
    public int maxOutReconnect;
    public float avgCmdPerSecond;
    public int maxCmdPerSecond;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref sessionId);
      s.Add(ref totalIn);
      s.Add(ref totalOut);
      s.Add(ref avgOutPerStep);
      s.Add(ref maxOutPerStep);
      s.Add(ref totalInReconnect);
      s.Add(ref totalOutReconnect);
      s.Add(ref avgOutReconnect);
      s.Add(ref maxOutReconnect);
      s.Add(ref avgCmdPerSecond);
      s.Add(ref maxCmdPerSecond);
    }

    public override string ToString()
    {
      return String.Format("SessionTrafficInfo(SessionId:{0},totalIn:{1},totalOut:{2},avgOutPerStep:{3},maxOutPerStep:{4},totalInReconnect:{5},totalOutReconnect:{6},avgOutReconnect:{7},maxOutReconnect:{8},avgCmdPerSecond:{9},maxCmdPerSecond:{10})",
                           sessionId, totalIn, totalOut, avgOutPerStep, maxOutPerStep, totalInReconnect, totalOutReconnect, avgOutReconnect, maxOutReconnect, avgCmdPerSecond, maxCmdPerSecond);
    }
  }



  public class SessionUserContext : ISerializable
  {
    public long sessionid;
    public int userid;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ref sessionid);
      s.Add(ref userid);
    }

    public override string ToString()
    {
      return String.Format("SessionUserContext(sessionid={0},userid={1})", sessionid, userid);
    }
  }



  public class UserCheatEvent : ISerializable
  {
    public SessionUserContext ctx = new SessionUserContext();
    public int cheatType;
    public string clientIp;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ctx);
      s.Add(ref cheatType);
      s.Add(ref clientIp);
    }

    public override string ToString()
    {
      return String.Format("UserCheatEvent(ctx={0},cheatType={1}, clientIp={2})", ctx, cheatType, clientIp);
    }
  }



  public class UserDisconnectEvent : ISerializable
  {
    public SessionUserContext ctx = new SessionUserContext();
    public int reason;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ctx);
      s.Add(ref reason);
    }

    public override string ToString()
    {
      return String.Format("UserDisconnectEvent(ctx={0}, reason={1})", ctx, reason);
    }
  }


  public class UserStatusEvent : ISerializable
  {
    public SessionUserContext ctx = new SessionUserContext();
    public int status;
    public int step;
    public int reason;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(ctx);
      s.Add(ref status);
      s.Add(ref step);
      s.Add(ref reason);
    }

    public override string ToString()
    {
      return String.Format("UserStatusEvent(ctx={0}, status={1}, step={2}, reason={3})", ctx, status, step, reason);
    }
  }


  public class PermittedStatisticsMethods : ISerializable
  {
    public List<int> methods;
    public List<int> sessionEvents;

    public override void Serialize(IChunklessSerializer s)
    {
      s.Add(methods);
      s.Add(sessionEvents);
    }
  }
}
