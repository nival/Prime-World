using DAL.Entities;

namespace DAL.Repositories
{
  public interface IAchievementRepository : IRepository<Achievement>
  {
  }

  public class AchievementRepository : Repository<Achievement>, IAchievementRepository
  {
  }
}