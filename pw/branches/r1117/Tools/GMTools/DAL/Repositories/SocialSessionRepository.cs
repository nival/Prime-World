using System;
using System.Collections.Generic;
using System.Linq;
using DAL.Entities;
using log4net;
using NHibernate;
using NHibernate.Criterion;

namespace DAL.Repositories
{
  public interface ISocialSessionRepository : IRepository<SocialSession>
  {
    void WriteLogout(Player player, string server, string cluster, DateTime timestamp);
    IEnumerable<SocialSession> GetSessionsByPlayerId(long playerid);
  }
  
  public class SocialSessionRepository : Repository<SocialSession>, ISocialSessionRepository
  {
    private static ILog _log = LogManager.GetLogger(typeof (SocialSessionRepository));

    public override void Add(SocialSession obj)
    {
      using (ITransaction tran = Session.BeginTransaction())
      {
        Session.Save(obj);
        tran.Commit();
      }
    }

    public void WriteLogout(Player player, string server, string cluster, DateTime timestamp)
    {
      var sessions = Session.CreateCriteria<SocialSession>()
        .Add(Restrictions.Eq("Player", player))
        .Add(EqOrNull("Server", server))
        .Add(EqOrNull("Cluster", cluster))
        .Add(Restrictions.Eq("EndTime", DateTime.MinValue))
        .Add(Restrictions.Gt("StartTime", timestamp.AddDays(-2)))
        .List<SocialSession>();

      if (sessions.Count == 0)
      {
        _log.WarnFormat("Failed to write logout session for player(id={0}), cannot find any open session", player.Id);
        return;
      }
      if (sessions.Count > 1)
      {
        _log.WarnFormat("More than one open social session was found for player(id={0}): sessions ids=({1})",
                        player.Id, String.Join(",", sessions.Select(s => s.Id.ToString()).ToArray()));
      }

      var session = sessions.OrderByDescending(s => s.StartTime).First();
      session.EndTime = timestamp;
      Update(session);
    }

    public IEnumerable<SocialSession> GetSessionsByPlayerId(long playerid)
    {
      var player = Session.Get<Player>(playerid);
      if (player == null)
      {
        _log.WarnFormat("Cannot get social sessions, player with id = {0} was not found", playerid);
        return null;
      }

      return Session.CreateCriteria<SocialSession>()
        .Add(Restrictions.Eq("Player", player))
        .List<SocialSession>();
    }
  }
}