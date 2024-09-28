using DAL.Entities;

namespace DAL.Repositories
{
  public interface IConsumableRepository : IRepository<Consumable>
  {
  }

  public class ConsumableRepository : Repository<Consumable>, IConsumableRepository
  {
  }
}