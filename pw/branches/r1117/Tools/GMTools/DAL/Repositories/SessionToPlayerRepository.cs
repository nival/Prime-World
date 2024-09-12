using System;
using System.Linq;
using System.Collections.Generic;
using DAL.Entities;
using NHibernate.Criterion;
using NHibernate.Transform;

namespace DAL.Repositories
{
  public interface ISessionToPlayerRepository : IRepository<SessionToPlayer>
  {
    /// <summary>
    /// Создание новой записи о сессии конкретного игрока.
    /// </summary>
    int Create(int gsid, PlayerCharacter playerCharacter, Faction faction);
    void LogSessionResults(int gameSessionId, Player player, int finalLevel, bool leaver,
                           int score, int kills, int deaths, int assists, int enemyCreepsKilled, int neutralCreepsKilled);
    void MaxLevelReached(int sessionToPlayerId);
    Dictionary<Character, int> GetSessionCount(IEnumerable<Character> characters, DateTime dateFrom, DateTime dateTo);
    Dictionary<int, int> GetCharacterLevels(Character c, DateTime dateFrom, DateTime dateTo);
    List<SessionToPlayerCountDTO> GetSessionToPlayerCount(DateTime dateFrom, DateTime dateTo);
    IEnumerable<SessionToPlayer> SelectByGameSession(GameSession gs);
    SessionToPlayer GetByPersistentId(long persistentId, Player player);
  }

  public class SessionToPlayerCountDTO
  {
    public DateTime Date { get; set; }
    public Character Character { get; set; }
    public int Count { get; set; }
  }

  public class SessionToPlayerRepository : Repository<SessionToPlayer>, ISessionToPlayerRepository
  {
    public int Create(int gsid, PlayerCharacter playerCharacter, Faction faction)
    {
      using (Session.BeginTransaction())
      {
        var gs = Session.Get<GameSession>(gsid);
        var stp = new SessionToPlayer
                    {
                      GameSession = gs,
                      PlayerCharacter = playerCharacter,
                      Guild = playerCharacter.Player.Guild,
                      RelayAddress = gs.ServerAddress,
                      Faction = faction,
                      StartTime = gs.StartTime
                    };
        Session.Save(stp);
        Session.Transaction.Commit();
        return stp.Id;
      }
    }

    public void LogSessionResults(int gameSessionId, Player player, int finalLevel, bool leaver,
        int score, int kills, int deaths, int assists, int enemyCreepsKilled, int neutralCreepsKilled)
    {
      var sessionToPlayer = Session.CreateCriteria<SessionToPlayer>()
        .CreateAlias("PlayerCharacter", "pc")
        .Add(Restrictions.Eq("GameSession.Id", gameSessionId))
        .Add(Restrictions.Eq("pc.Player", player))
        .UniqueResult<SessionToPlayer>();

      if (sessionToPlayer == null)
        throw new DALException(String.Format("Session with gsid={0} not found", gameSessionId));

      sessionToPlayer.FinalLevel = finalLevel;
      sessionToPlayer.Leaver = leaver;
      sessionToPlayer.Score = score;
      sessionToPlayer.Kills = kills;
      sessionToPlayer.Deaths = deaths;
      sessionToPlayer.Assists = assists;
      sessionToPlayer.EnemyCreepsKilled = enemyCreepsKilled;
      sessionToPlayer.NeutralCreepsKilled = neutralCreepsKilled;

      using (Session.BeginTransaction())
      {
        Session.Save(sessionToPlayer);
        Session.Transaction.Commit();
      }
    }

    public void MaxLevelReached(int sessionToPlayerId)
    {
      using (Session.BeginTransaction())
      {
        var stp = Session.Load<SessionToPlayer>(sessionToPlayerId);
        stp.MaxLevelReached = (int) (DateTime.UtcNow - stp.GameSession.StartTime).TotalMinutes;
        Session.Save(stp);
        Session.Transaction.Commit();
      }
    }

    public Dictionary<Character, int> GetSessionCount(IEnumerable<Character> characters, DateTime dateFrom, DateTime dateTo)
    {
      var result = new Dictionary<Character, int>();
      foreach (var c in characters)
      {
        int count = Session
          .CreateCriteria<SessionToPlayer>()
          .CreateAlias("PlayerCharacter", "pc")
          .Add(Restrictions.Eq("pc.Character", c))
          .CreateAlias("GameSession", "gs")
          .Add(Expression.Between("gs.StartTime", dateFrom, dateTo))
          .SetResultTransformer(new DistinctRootEntityResultTransformer())
          .List<SessionToPlayer>()
          .Count;
        result.Add(c, count);
      }
      return result;
    }

    public Dictionary<int, int> GetCharacterLevels(Character c, DateTime dateFrom, DateTime dateTo)
    {
      var result = new Dictionary<int, int>();

      var characterLevelsCriteria = Session
        .CreateCriteria<SessionToPlayer>()
        .CreateAlias("GameSession", "gs")
        .Add(Restrictions.Between("gs.StartTime", dateFrom, dateTo))
        .SetProjection(Projections.ProjectionList()
                         .Add(Projections.GroupProperty("FinalLevel"))
                         .Add(Projections.RowCount()));
      if (c != null)
      {
        characterLevelsCriteria = characterLevelsCriteria
          .CreateAlias("PlayerCharacter", "pc")
          .Add(Restrictions.Eq("pc.Character", c));
      }

      foreach (var usage in characterLevelsCriteria.List<object[]>())
      {
        result.Add((int)usage[0], (int)usage[1]);
      }
      return result;
    }

    public List<SessionToPlayerCountDTO> GetSessionToPlayerCount(DateTime dateFrom, DateTime dateTo)
    {
      var dtos = Session
        .CreateCriteria<SessionToPlayer>()
        .CreateAlias("GameSession", "gs")
        .Add(Restrictions.Between("gs.StartTime", dateFrom, dateTo))
        .CreateAlias("PlayerCharacter", "pc")
        .SetProjection(Projections.ProjectionList()
          .Add(Projections.Property("gs.StartTime").As("Date"))
          .Add(Projections.Property("pc.Character").As("Character")))
        .SetResultTransformer(new AliasToBeanResultTransformer(typeof(SessionToPlayerCountDTO)))
        .List<SessionToPlayerCountDTO>();

      // NHibernate.Dialect.PostgreSQLDialect не поддерживает функцию date_trunc
      // поэтому группировку по дате и персонажу средствами чистого SQL сделать не получилось.
      // Приходится работу с коллекциями частично осуществлять на стороне C#

      var characters = dtos.Select(d => d.Character).Distinct();
      var result = new List<SessionToPlayerCountDTO>();
      foreach (var c in characters)
      {
        var grouped = dtos.Where(d => d.Character == c).GroupBy(d => d.Date.Date);
        foreach (var g in grouped)
        {
          result.Add(new SessionToPlayerCountDTO
                       {
                         Character = c,
                         Date = g.Key,
                         Count = g.Count()
                       });
        }
      }

      return result;
    }

    public IEnumerable<SessionToPlayer> SelectByGameSession(GameSession gs)
    {
      return Session.CreateCriteria<SessionToPlayer>()
        .Add(Restrictions.Eq("GameSession", gs))
        .List<SessionToPlayer>();
    }

    public SessionToPlayer GetByPersistentId(long persistentId, Player player)
    {
      GameSession gs = null;
      PlayerCharacter pc = null;

      return Session.QueryOver<SessionToPlayer>()
        .JoinAlias(s => s.GameSession, () => gs)
        .JoinAlias(s => s.PlayerCharacter, () => pc)
        .Where(() => gs.PersistentId == persistentId && pc.Player == player)
        .SingleOrDefault<SessionToPlayer>();
    }
  }
}
