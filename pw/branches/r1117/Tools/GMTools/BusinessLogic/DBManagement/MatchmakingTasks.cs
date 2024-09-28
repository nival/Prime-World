using System;
using System.Collections.Generic;
using BusinessLogic.Game;
using DAL.Entities;
using DAL.Repositories;
using log4net;

namespace BusinessLogic.DBManagement
{
  /// <summary>
  /// Таск по записи матчмейкинга игрока
  /// </summary>
  public class MMakingPlayerTask : BaseTask
  {
    private static ILog _log = LogManager.GetLogger(typeof (MMakingPlayerTask));

    private IPlayerRepository playerRepository;
    private IPlayerCharacterRepository playerCharacterRepository;
    private IMMakingPlayerRepository mmakingPlayerRepository;

    private readonly MMakingPlayerInfo mmplayer;
    private readonly MMakingSession mmsession;
    private readonly DateTime timestamp;

    public MMakingPlayerTask(MMakingPlayerInfo mmplayer, DateTime timestamp)
    {
      this.mmplayer = mmplayer;
      this.timestamp = timestamp;
    }

    public MMakingPlayerTask(MMakingPlayerInfo mmplayer, MMakingSession mmsession, DateTime timestamp,
                             IPlayerRepository prepo, IPlayerCharacterRepository pcrepo, IMMakingPlayerRepository mprepo)
      : this(mmplayer, timestamp)
    {
      if (prepo == null) throw new ArgumentNullException("prepo");
      if (pcrepo == null) throw new ArgumentNullException("pcrepo");
      if (mprepo == null) throw new ArgumentNullException("mprepo");

      this.playerRepository = prepo;
      this.playerCharacterRepository = pcrepo;
      this.mmakingPlayerRepository = mprepo;

      this.mmsession = mmsession;
    }

    public override bool Execute()
    {
      _log.Debug("Executing MMakingPlayerTask");
      bool localRepos = playerRepository == null || playerCharacterRepository == null || mmakingPlayerRepository == null;
      if (localRepos)
      {
        playerRepository = new PlayerRepository();
        playerCharacterRepository = new PlayerCharacterRepository();
        mmakingPlayerRepository = new MMakingPlayerRepository();
      }

      try
      {
        var player = playerRepository.CreateOrUpdate(mmplayer.UserId, null, mmplayer.Sex, (Faction)mmplayer.Faction, null, null, null, null);
        var playercharacter = playerCharacterRepository.GetOrCreateByParams(player, mmplayer.HeroId);
        if (playercharacter == null)
          throw new Exception(String.Format("Cannot get or create Playercharacter(Player(id={0}),Character(id={1}))", player.Id, mmplayer.HeroId));

        var mm = new MMakingPlayer
                   {
                     MMakingSession = mmsession,
                     PlayerCharacter = playercharacter,
                     Sex = mmplayer.Sex,
                     Faction = mmplayer.Faction,
                     Rating = mmplayer.Rating,
                     PlayerRating = mmplayer.PlayerRating,
                     Force = mmplayer.Force,
                     Party = mmplayer.PartyId,
                     WaitInterval = mmplayer.WaitTime,
                     LoseStreak = mmplayer.LoseStreak,
                     FameLevel = mmplayer.FameLevel,
                     Basket = mmplayer.Basket,
                     LobbyReaction = mmplayer.LobbyReaction,
                     LobbyReactionTime = mmplayer.LobbyReactionTime,
                     Timestamp = timestamp
                   };
        mmakingPlayerRepository.Add(mm);
        _log.DebugFormat("Added new MMakingPlayer(id={0},PlayerCharacter(id={1}))", mm.Id, mm.PlayerCharacter.Id);
      }
      catch (Exception ex)
      {
        _log.ErrorFormat("Failed task MMakingPlayerTask: mmplayer={0}, mmsession(id={1})\n{2}",
                         mmplayer, mmsession != null ? mmsession.Id.ToString() : "(null)", ex);
        ErrorCount++;
        LastErrorMessage = ex.Message;
        return false;
      }
      if (localRepos)
      {
        playerRepository.Dispose();
        playerCharacterRepository.Dispose();
        mmakingPlayerRepository.Dispose();
      }
      _log.Debug("Finished MMakingPlayerTask");
      return true;
    }
  }

  /// <summary>
  /// Таск по записи сессии матчмейкинга
  /// </summary>
  public class MMakingSessionTask : BaseTask
  {
    private static ILog _log = LogManager.GetLogger(typeof(MMakingSessionTask));

    private IPlayerRepository playerRepository;
    private IPlayerCharacterRepository playerCharacterRepository;
    private IMMakingPlayerRepository mmakingPlayerRepository;
    private IMMakingSessionRepository mmakingSessionRepository;

    private readonly ulong persistentId;
    private readonly int status;
    private readonly int manoeuvresFaction;
    private readonly int basket;
    private readonly string map;
    private readonly DateTime timestamp;
    private readonly List<MMakingPlayerInfo> mmplayers;

    /// <summary>
    /// Сохраняется уже записанный в базу объект, чтобы не записаться повторно при перезапуске таска
    /// </summary>
    private MMakingSession mmakingSession;

    public MMakingSessionTask(ulong persistentId, int status, int manoeuvresFaction, int basket, string map, DateTime timestamp, IEnumerable<MMakingPlayerInfo> mmplayers)
    {
      if (mmplayers == null) throw new ArgumentNullException("mmplayers");

      this.persistentId = persistentId;
      this.status = status;
      this.manoeuvresFaction = manoeuvresFaction;
      this.basket = basket;
      this.map = map;
      this.timestamp = timestamp;
      this.mmplayers = new List<MMakingPlayerInfo>(mmplayers);
    }

    public MMakingSessionTask(ulong persistentId, int status, int manoeuvresFaction, int basket, string map, DateTime timestamp, IEnumerable<MMakingPlayerInfo> mmplayers,
                              IPlayerRepository prepo, IPlayerCharacterRepository pcrepo, IMMakingPlayerRepository mprepo, IMMakingSessionRepository msrepo)
      : this(persistentId, status, manoeuvresFaction, basket, map, timestamp, mmplayers)
    {
      if (prepo == null) throw new ArgumentNullException("prepo");
      if (pcrepo == null) throw new ArgumentNullException("pcrepo");
      if (mprepo == null) throw new ArgumentNullException("mprepo");

      this.playerRepository = prepo;
      this.playerCharacterRepository = pcrepo;
      this.mmakingPlayerRepository = mprepo;
      this.mmakingSessionRepository = msrepo;
    }

    public override bool Execute()
    {
      _log.Debug("Executing MMakingSessionTask");
      bool localRepos = playerRepository == null || playerCharacterRepository == null ||
                        mmakingPlayerRepository == null || mmakingSessionRepository == null;
      if (localRepos)
      {
        playerRepository = new PlayerRepository();
        playerCharacterRepository = new PlayerCharacterRepository();
        mmakingPlayerRepository = new MMakingPlayerRepository();
        mmakingSessionRepository = new MMakingSessionRepository();
      }

      try
      {
        if (mmakingSession == null)
        {
          var mm = new MMakingSession
          {
            PersistentId = (long)persistentId,
            Status = status,
            ManoeuvresFaction = manoeuvresFaction,
            Basket = basket,
            Map = map ?? String.Empty,
            Timestamp = timestamp
          };
          mmakingSessionRepository.Add(mm);
          mmakingSession = mm;
          _log.DebugFormat("Added new MMakingSession(id={0})", persistentId);
        }

        var mmplayersCopy = new List<MMakingPlayerInfo>(mmplayers);
        foreach (var mmplayer in mmplayersCopy)
        {
          var task = new MMakingPlayerTask(mmplayer, mmakingSession, timestamp, playerRepository, playerCharacterRepository, mmakingPlayerRepository);
          if (task.Execute())
            mmplayers.Remove(mmplayer);
          else
            throw new Exception("Failed execution of task " + task);
        }
      }
      catch (Exception ex)
      {
        _log.Error("Failed task MMakingSessionTask", ex);
        ErrorCount++;
        LastErrorMessage = ex.Message;
        return false;
      }
      if (localRepos)
      {
        playerRepository.Dispose();
        playerCharacterRepository.Dispose();
        mmakingPlayerRepository.Dispose();
        mmakingSessionRepository.Dispose();
      }
      _log.Debug("Finished MMakingPlayerTask");
      return true;
    }
  }
}