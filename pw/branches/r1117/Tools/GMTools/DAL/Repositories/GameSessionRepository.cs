using System;
using System.Collections.Generic;
using DAL.Entities;
using log4net;
using NHibernate.Criterion;

namespace DAL.Repositories
{
  public interface IGameSessionRepository : IRepository<GameSession>
  {
    int WriteStarted(GameSession data);
    int WriteEnded(long persistentid, int result, DateTime endTime, int sideWon, int surrendervote);
    GameSession GetByPersistentId(long persistentId);
  }

  public class GameSessionRepository : Repository<GameSession>, IGameSessionRepository
  {
    private static ILog _log = LogManager.GetLogger(typeof (GameSessionRepository));
    
    /// <summary>
    /// Запись информации о начале сессии.
    /// </summary>
    public int WriteStarted(GameSession data)
    {
      using (Session.BeginTransaction())
      {
        Session.Save(data);
        Session.Transaction.Commit();
      }
      return data.Id;
    }

    /// <summary>
    /// Запись информации об окончании сессии.
    /// </summary>
    public int WriteEnded(long persistentid, int result, DateTime endTime, int sideWon, int surrendervote)
    {
      var gameSession = GetByPersistentId(persistentid);
      if (gameSession == null)
        throw new DALException(String.Format("Cannot write end of the session(persistentid={0}), this session was not found in database", persistentid));
      
      SessionResult sessionResult;
      if (!Enum.IsDefined(typeof(SessionResult), result))
      {
        sessionResult = SessionResult.Undefined;
        _log.WarnFormat("Invalid result value {0} for session(id={1})", result, gameSession.Id);
      }
      else
      {
        sessionResult = (SessionResult) result;
      }
      if (gameSession.SessionResult != SessionResult.Undefined)
        _log.WarnFormat("Session result already defined for session(id={0})", gameSession.Id);

      using (Session.BeginTransaction())
      {
        gameSession.EndTime = endTime;
        gameSession.SideWon = sideWon;
        gameSession.SurrenderVote = surrendervote;
        gameSession.SessionResult = sessionResult;

        Session.Save(gameSession);
        Session.Transaction.Commit();
      }

      _log.DebugFormat("Session(gsid={0}) has ended", gameSession.Id);
      return gameSession.Id;
    }

    /// <summary>
    /// Получить объект сессии по уникальному серверному ид
    /// </summary>
    public GameSession GetByPersistentId(long persistentId)
    {
      return Session.CreateCriteria<GameSession>()
        .Add(Restrictions.Eq("PersistentId", persistentId))
        .UniqueResult<GameSession>();
    }

    public IEnumerable<GameSession> GetByTime(DateTime datefrom, DateTime dateto)
    {
      return Session.CreateCriteria<GameSession>()
        .Add(Restrictions.Between("StartTime", datefrom, dateto))
        .List<GameSession>();
    }
  }
}
