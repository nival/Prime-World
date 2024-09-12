using DAL.Entities;

namespace DAL.Repositories
{
  public interface IBuildingRepository : IRepository<Building>
  {
    Building GetById(string id);
  }

  public class BuildingRepository : Repository<Building>, IBuildingRepository
  {
    public Building GetById(string id)
    {
      return Session.Get<Building>(id);
    }
  }
}