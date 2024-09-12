using DAL.Entities;

namespace DAL.Repositories
{
  public interface ICharacterUnlockRepository : IRepository<CharacterUnlock>
  {
  }

  public class CharacterUnlockRepository : Repository<CharacterUnlock>, ICharacterUnlockRepository
  {
  }
}