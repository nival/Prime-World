using DAL.Entities;

namespace DAL.Repositories
{
  public interface ITalentRepository : IRepository<Talent>
  {
  }

  public class TalentRepository : Repository<Talent>, ITalentRepository
  {
  }
}