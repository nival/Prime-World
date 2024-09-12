using DAL.Entities;

namespace DAL.Repositories
{
  public interface ICreatureRepository : IRepository<Creature>
  {
    Creature GetById(string id);
  }

  public class CreatureRepository : Repository<Creature>, ICreatureRepository
  {
    public Creature GetById(string id)
    {
      return Session.Get<Creature>(id);
    }
  }
}