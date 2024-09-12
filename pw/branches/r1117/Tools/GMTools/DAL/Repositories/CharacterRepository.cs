using DAL.Entities;

namespace DAL.Repositories
{
  public interface ICharacterRepository : IRepository<Character>
  {
  }

  public class CharacterRepository : Repository<Character>, ICharacterRepository
  {
  }
}
