using DAL.Entities;

namespace DAL.Repositories
{
  public interface IAbilityTypeRepository : IRepository<AbilityType>
  {
  }

  public class AbilityTypeRepository : Repository<AbilityType>, IAbilityTypeRepository
  {
  }
}