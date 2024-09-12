using DAL.Entities;
using log4net;

namespace DAL.Repositories
{
  public interface IGuildRepository : IRepository<Guild>
  {
    Guild GetOrCreateById(long id);
  }
  
  public class GuildRepository : Repository<Guild>, IGuildRepository
  {
    public Guild GetOrCreateById(long id)
    {
      var guild = GetById(id);
      if (guild == null)
      {
        guild = new Guild { Id = id };
        Add(guild);
      }
      return guild;
    }
  }
}