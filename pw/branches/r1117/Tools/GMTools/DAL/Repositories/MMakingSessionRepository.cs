using DAL.Entities;

namespace DAL.Repositories
{
  public interface IMMakingSessionRepository : IRepository<MMakingSession>
  {
  }

  public class MMakingSessionRepository : Repository<MMakingSession>, IMMakingSessionRepository
  {
  }
}