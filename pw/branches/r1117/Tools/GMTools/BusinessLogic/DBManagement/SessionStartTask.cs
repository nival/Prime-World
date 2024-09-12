using System;
using System.Collections.Generic;
using BusinessLogic.Game;
using DAL.Entities;
using DAL.Repositories;
using log4net;

namespace BusinessLogic.DBManagement
{
  public class SessionStartTask : BaseTask
  {
    private static ILog _log = LogManager.GetLogger(typeof (SessionStartTask));

    private readonly long persistentId;
    private readonly string map;
    private readonly string server;
    private readonly string serveraddress;
    private readonly string cluster;
    private readonly int sessionType;
    private readonly DateTime timestamp;
    private readonly List<SessionStartPlayerInfo> players;

    private readonly IGameSessionRepository gameSessionRepository;
    private readonly IPlayerRepository playerRepository;
    private readonly IPlayerCharacterRepository playerCharacterRepository;
    private readonly ISessionToPlayerRepository sessionToPlayerRepository;

    private GameSession gameSession;

    public SessionStartTask(long persistentId, string map, string server, string serveraddress, string cluster, int sessionType, DateTime timestamp, IEnumerable<SessionStartPlayerInfo> players)
      : this(persistentId, map, server, serveraddress, cluster, sessionType, timestamp, players,
             new GameSessionRepository(), new PlayerRepository(), new PlayerCharacterRepository(), new SessionToPlayerRepository())
    {
    }

    public SessionStartTask(long persistentId, string map, string server, string serveraddress, string cluster, int sessionType, DateTime timestamp, IEnumerable<SessionStartPlayerInfo> players,
                            IGameSessionRepository gsrepo, IPlayerRepository prepo, IPlayerCharacterRepository pcrepo, ISessionToPlayerRepository stprepo)
    {
      if (players == null) throw new ArgumentNullException("players");

      this.persistentId = persistentId;
      this.map = map;
      this.server = server;
      this.serveraddress = serveraddress;
      this.cluster = cluster;
      this.sessionType = sessionType;
      this.timestamp = timestamp;
      this.players = new List<SessionStartPlayerInfo>(players);

      this.gameSessionRepository = gsrepo;
      this.playerRepository = prepo;
      this.playerCharacterRepository = pcrepo;
      this.sessionToPlayerRepository = stprepo;
    }

    public override bool Execute()
    {
      try
      {
        if (!Enum.IsDefined(typeof(SessionType), sessionType))
          _log.Warn("Undefined session type " + sessionType);

        if (gameSession == null)
        {
          var gs = new GameSession
                     {
                       PersistentId = persistentId,
                       Map = map,
                       Server = server,
                       ServerAddress = serveraddress,
                       Cluster = cluster,
                       SessionResult = SessionResult.Undefined,
                       StartTime = timestamp,
                       SideWon = -1,
                       SessionType = (SessionType) sessionType
                     };
          gameSessionRepository.WriteStarted(gs);
          gameSession = gs;
          _log.DebugFormat("Created GameSession(gsid={0},persistentId={1})", gs.Id, persistentId);
        }

        var playersCopy = new List<SessionStartPlayerInfo>(players);
        foreach (var p_info in playersCopy)
        {
          var player = playerRepository.CreateOrUpdate(p_info.UserId, p_info.Nickname, p_info.Sex, (Faction)p_info.Faction, null, null, null, null);
          var playercharacter = playerCharacterRepository.GetOrCreateByParams(player, p_info.HeroId);
          if (playercharacter == null)
            continue;

          int id = sessionToPlayerRepository.Create(gameSession.Id, playercharacter, player.Faction);
          _log.DebugFormat("Created SessionToPlayer(id={0},gsid={1},Player(id={2}),Character(id={3}))", id, gameSession.Id, p_info.UserId, p_info.HeroId);
          players.Remove(p_info);
        }
      }
      catch (Exception ex)
      {
        _log.Error("Failed task SessionStartTask", ex);
        ErrorCount++;
        LastErrorMessage = ex.Message;
        return false;
      }
      this.gameSessionRepository.Dispose();
      this.playerRepository.Dispose();
      this.playerCharacterRepository.Dispose();
      this.sessionToPlayerRepository.Dispose();
      return true;
    }
  }
}