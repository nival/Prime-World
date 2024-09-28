using DAL.Entities;

namespace DAL.Repositories
{
  public interface IUnitTypeRepository : IRepository<UnitType>
  {
  }

  public class UnitTypeRepository : Repository<UnitType>, IUnitTypeRepository
  {
  }
}