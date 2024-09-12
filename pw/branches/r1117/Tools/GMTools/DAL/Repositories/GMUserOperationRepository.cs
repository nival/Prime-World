using System;
using System.Collections.Generic;
using DAL.Entities;
using NHibernate.Criterion;

namespace DAL.Repositories
{
  public interface IGMUserOperationRepository : IRepository<GMUserOperation>
  {
    IEnumerable<GMUserOperation> GetOperationsByPlayerId(long playerId);
    IEnumerable<GMUserOperation> GetOperationsByPlayer(Player player);
  }

  public class GMUserOperationRepository : Repository<GMUserOperation>, IGMUserOperationRepository
  {
    public IEnumerable<GMUserOperation> GetOperationsByPlayerId(long playerId)
    {
      var player = Session.Get<Player>(playerId);
      if (player == null)
        throw new DALException(String.Format("Player(id={0}) is not found in database", playerId));

      return GetOperationsByPlayer(player);
    }

    public IEnumerable<GMUserOperation> GetOperationsByPlayer(Player player)
    {
      if (player == null)
        throw new ArgumentNullException("player");

      return Session.CreateCriteria<GMUserOperation>()
              .Add(Restrictions.Eq("Player", player))
              .List<GMUserOperation>();
    }
  }
}