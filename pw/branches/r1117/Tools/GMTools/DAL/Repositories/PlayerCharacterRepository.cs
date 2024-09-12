using System;
using System.Data;
using DAL.Entities;
using log4net;
using NHibernate;
using NHibernate.Criterion;

namespace DAL.Repositories
{
  public interface IPlayerCharacterRepository : IRepository<PlayerCharacter>
  {
    void Add(ref PlayerCharacter obj);
    PlayerCharacter GetByParams(Player player, Character character);
    PlayerCharacter GetOrCreateByParams(Player player, int characterid);
  }

  public class PlayerCharacterRepository : Repository<PlayerCharacter>, IPlayerCharacterRepository
  {
    private static ILog _log = LogManager.GetLogger(typeof (PlayerCharacterRepository));
    private static readonly object addlocker = new object();

    public override void Add(PlayerCharacter obj)
    {
      _log.Warn("Object reference can be changed. Please, use method Add(ref PlayerCharacter obj)");
      Add(ref obj);
    }

    public void Add(ref PlayerCharacter obj)
    {
      if (Session.Get<Player>(obj.Player.Id) == null) 
        throw new DALException("Cannot add " + obj + ", player is not exists");
      if (Session.Get<Character>(obj.Character.Id) == null)
        throw new DALException("Cannot add " + obj + ", character is not exists");

      lock (addlocker)
      {
        obj.Player = Session.Merge(obj.Player);
        obj.Character = Session.Merge(obj.Character);

        var cached = Session.CreateCriteria<PlayerCharacter>()
          .Add(Restrictions.Eq("Player", obj.Player))
          .Add(Restrictions.Eq("Character", obj.Character))
          .UniqueResult<PlayerCharacter>();
        
        if (cached == null)
        {
          _log.DebugFormat("PlayerCharacter object for Player#{0},Character#{1} wasn't found in cache/db", obj.Player.Id, obj.Character.Id);
          using (var tran = Session.BeginTransaction())
          {
            Session.Save(obj);
            tran.Commit();
          }
          _log.Debug("Added new object " + obj);
        }
        else
        {
          _log.DebugFormat("Object {0} already exists, return from cache (PlayerCharacter#{1})", obj, cached.Id);
          obj = cached;
        }
      }
    }

    public PlayerCharacter GetByParams(Player player, Character character)
    {
      if (player == null) throw new ArgumentNullException("player");
      if (character == null) throw new ArgumentNullException("character");

      return Session.CreateCriteria<PlayerCharacter>()
        .Add(Restrictions.Eq("Player", player))
        .Add(Restrictions.Eq("Character", character))
        .UniqueResult<PlayerCharacter>();
    }

    public PlayerCharacter GetOrCreateByParams(Player player, int characterid)
    {
      if (player == null) throw new ArgumentNullException("player");

      var character = Session.Get<Character>(characterid);
      if (character == null)
      {
        _log.WarnFormat("Cannot get or create PlayerCharacter: character with id = {0} is not exists", characterid);
        return null;
      }

      var playercharacter = GetByParams(player, character);
      if (playercharacter == null)
      {
        playercharacter = GetByParams(player, character);
        if (playercharacter == null)
        {
          playercharacter = new PlayerCharacter {Player = player, Character = character};
          Add(ref playercharacter);
        }
      }
      return playercharacter;
    }
  }
}
