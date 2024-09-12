using System;
using System.Collections.Generic;
using DAL.Entities;
using NHibernate.Criterion;

namespace DAL.Repositories
{
  public interface IGMOperationRepository : IRepository<GMOperation>
  {
    IEnumerable<GMOperation> GetOperationsByPlayer(long playerid, List<GMOperationType> types);
    IEnumerable<GMOperation> GetOperationsByPlayer(Player player, List<GMOperationType> types);
  }

  public class GMOperationRepository : Repository<GMOperation>, IGMOperationRepository
  {
    public IEnumerable<GMOperation> GetOperationsByPlayer(long playerid, List<GMOperationType> types)
    {
      var player = Session.Get<Player>(playerid);
      if (player == null)
        throw new DALException(String.Format("Player(id={0}) was not found in database", playerid));

      return GetOperationsByPlayer(player, types);
    }

    public IEnumerable<GMOperation> GetOperationsByPlayer(Player player, List<GMOperationType> types)
    {
      if (player == null)
        throw new ArgumentNullException("player");

      var criteria = Session.CreateCriteria<GMOperation>()
                            .Add(Restrictions.Eq("Player", player));

      if (types != null)
        foreach (var t in types)
          criteria.Add(Restrictions.Eq("Type", t));

      return criteria.List<GMOperation>();
    }
  }
}