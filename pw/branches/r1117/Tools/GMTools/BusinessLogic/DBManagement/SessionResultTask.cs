using System;
using System.Collections.Generic;
using BusinessLogic.Game;
using DAL.Repositories;
using log4net;

namespace BusinessLogic.DBManagement
{
  public class SessionResultTask : BaseTask
  {
    private static ILog _log = LogManager.GetLogger(typeof(SessionResultTask));

    private readonly long persistentId;
    private readonly int result;
    private readonly int sideWon;
    private readonly int surrendervote;
    private readonly List<SessionResultPlayerInfo> players;
    private readonly DateTime timestamp;

    private readonly IGameSessionRepository gameSessionRepository;
    private readonly IPlayerRepository playerRepository;
    private readonly ISessionToPlayerRepository sessionToPlayerRepository;

    private int gameSessionId;

    public SessionResultTask(long persistentId, int result, int sideWon, int surrendervote, DateTime timestamp, IEnumerable<SessionResultPlayerInfo> players)
      : this(persistentId, result, sideWon, surrendervote, timestamp, players,
             new GameSessionRepository(), new PlayerRepository(), new SessionToPlayerRepository())
    {
    }

    public SessionResultTask(long persistentId, int result, int sideWon, int surrendervote, DateTime timestamp, IEnumerable<SessionResultPlayerInfo> players,
                             IGameSessionRepository gsrepo, IPlayerRepository prepo, ISessionToPlayerRepository stprepo)
    {
      if (players == null) throw new ArgumentNullException("players");

      this.persistentId = persistentId;
      this.result = result;
      this.sideWon = sideWon;
      this.surrendervote = surrendervote;
      this.players = new List<SessionResultPlayerInfo>(players);
      this.timestamp = timestamp;

      this.gameSessionRepository = gsrepo;
      this.playerRepository = prepo;
      this.sessionToPlayerRepository = stprepo;
    }

    public override bool Execute()
    {
      try
      {
        if (gameSessionId == 0) // ≈сли gameSessionId не был сохранен, значит WriteEnded не отработал
        {
          gameSessionId = gameSessionRepository.WriteEnded(persistentId, result, timestamp, sideWon, surrendervote);
        }

        var playersCopy = new List<SessionResultPlayerInfo>(players);
        foreach (var p_info in playersCopy)
        {
          var player = playerRepository.GetById(p_info.UserId);
          if (player == null)
            continue;

          sessionToPlayerRepository.LogSessionResults(gameSessionId, player, p_info.FinalLevel, p_info.Leaver, p_info.Score, p_info.Kills, p_info.Deaths,
                                                      p_info.Assists, p_info.EnemyCreepsKilled, p_info.NeutralCreepsKilled);
          _log.DebugFormat("Wrote session(gsid={0}) result for the player(id={1})", gameSessionId, p_info.UserId);
          players.Remove(p_info);
        }
      }
      catch (Exception ex)
      {
        _log.Error("Failed task SessionResultTask", ex);
        ErrorCount++;
        LastErrorMessage = ex.Message;
        return false;
      }
      return true;
    }
  }
}