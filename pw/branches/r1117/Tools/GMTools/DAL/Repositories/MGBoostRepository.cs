using DAL.Entities;

namespace DAL.Repositories
{
  public interface IMGBoostRepository : IRepository<MGBoost>
  {
  }

  public class MGBoostRepository : Repository<MGBoost>, IMGBoostRepository
  {
  }
}
