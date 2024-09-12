using System;
using System.Linq;
using DAL.Repositories;
using log4net;

namespace BusinessLogic.DBManagement
{
  public class SessionRelayInfoTask : BaseTask
  {
    private static ILog _log = LogManager.GetLogger(typeof (SessionRelayInfoTask));

    private readonly long persistentId;
    private readonly long playerId;
    private readonly string relayAddress;

    private readonly IGameSessionRepository gameSessionRepository;
    private readonly ISessionToPlayerRepository sessionToPlayerRepository;

    public SessionRelayInfoTask(long persistentId, long playerId, string relayAddress)
      : this (persistentId, playerId, relayAddress, new GameSessionRepository(), new SessionToPlayerRepository())
    {
    }

    public SessionRelayInfoTask(long persistentId, long playerId, string relayAddress,
      IGameSessionRepository gsrepo, ISessionToPlayerRepository stprepo)
    {
      this.persistentId = persistentId;
      this.playerId = playerId;
      this.relayAddress = relayAddress;

      this.gameSessionRepository = gsrepo;
      this.sessionToPlayerRepository = stprepo;
    }

    public override bool Execute()
    {
      try
      {
        var gs = gameSessionRepository.GetByPersistentId(persistentId);
        if (gs == null)
          return Error(String.Format("GameSession(persistentid={0}) doesn't exist in database.", persistentId));
        var stp = sessionToPlayerRepository.SelectByGameSession(gs).SingleOrDefault(s => s.PlayerCharacter.Player.Id == playerId);
        if (stp != null)
        {
          if (stp.RelayAddress == null)
          {
            stp.RelayAddress = relayAddress;
            sessionToPlayerRepository.Update(stp);
          }
        }
        else
          return Error();
      }
      catch (Exception ex)
      {
        _log.Error("Failed task SessionRelayInfoTask", ex);
        return Error(ex.Message);
      }
      return true;
    }

    private bool Error()
    {
      ErrorCount++;
      return false;
    }

    private bool Error(string message)
    {
      LastErrorMessage = message;
      return Error();
    }

  }
}