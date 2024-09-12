using DAL.Entities;

namespace DAL.Repositories
{
  public interface IImpulsiveBuffRepository : IRepository<ImpulsiveBuff>
  {
  }

  public class ImpulsiveBuffRepository : Repository<ImpulsiveBuff>, IImpulsiveBuffRepository
  {
  }
}
