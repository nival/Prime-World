using DAL.Entities;
using NHibernate;

namespace DAL.Repositories
{
  public interface IMMakingPlayerRepository : IRepository<MMakingPlayer>
  {
  }

  public class MMakingPlayerRepository : Repository<MMakingPlayer>, IMMakingPlayerRepository
  {
    public override void Add(MMakingPlayer obj)
    {
      using (ITransaction tran = Session.BeginTransaction())
      {
        // Re-attach transient objects
        if (obj.MMakingSession != null)
          Session.Lock(obj.MMakingSession, LockMode.Read);

        Session.Save(obj);
        tran.Commit();
      }
    }
  }
}