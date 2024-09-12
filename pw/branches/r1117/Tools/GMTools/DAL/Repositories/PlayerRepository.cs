using System;
using DAL.Entities;
using log4net;
using NHibernate.Criterion;

namespace DAL.Repositories
{
  public interface IPlayerRepository : IRepository<Player>
  {
    void Add(ref Player obj);
    Player GetById(long id);
    Player GetByLogin(string login);
    Player CreateOrUpdate(long id, string nickname, int? sex, Faction? faction, bool? nival, string locale, int? leaverpoints, bool? isleaver);
  }

  public class PlayerRepository : Repository<Player>, IPlayerRepository
  {
    private static ILog _log = LogManager.GetLogger(typeof(PlayerRepository));
    private static readonly object addlocker = new object();

    public void Add(ref Player obj)
    {
      lock (addlocker)
      {
        var cached = Session.Get<Player>(obj.Id);
        if (cached == null)
        {
          Add(obj);
        }
        else
        {
          _log.DebugFormat("Object {0} already exists, return from cache", obj);
          obj = cached;
        }
      }
    }

    public override Player GetById(int id)
    {
      return GetById((long)id);
    }

    public Player GetById(long id)
    {
      return Session.Get<Player>(id);
    }

    public Player GetByLogin(string login)
    {
      if (login == null) throw new ArgumentNullException("login");
      try
      {
        return Session.CreateCriteria<Player>()
        .Add(Restrictions.InsensitiveLike("Login", login))
        .UniqueResult<Player>();
      }
      catch (NHibernate.HibernateException ex)
      {
        throw new DALException(String.Format("Failed to get player by login = '{0}'", login), ex);
      }
    }

    public Player CreateOrUpdate(long id, string nickname, int? sex, Faction? faction, bool? nival, string locale, int? leaverpoints, bool? isleaver)
    {
      var player = GetById(id);
      if (player == null)
      {
        player = new Player
                   {
                     Id = id,
                     Nickname = nickname,
                     Sex = sex ?? 0,
                     Faction = faction ?? Faction.None,
                     Nival = nival ?? false,
                     Locale = locale ?? Player.DefaultLocale,
                     LeaverPoints = leaverpoints ?? 0,
                     IsLeaver = isleaver ?? false
                   };
        Add(ref player);
      }
      else if ((nickname != null && player.Nickname != nickname) ||
               (sex.HasValue && player.Sex != sex) ||
               (faction.HasValue && player.Faction != faction) ||
               (nival.HasValue && player.Nival != nival) ||
               (!String.IsNullOrEmpty(locale) && player.Locale != locale) ||
               (leaverpoints.HasValue && player.LeaverPoints != leaverpoints) ||
               (isleaver.HasValue && player.IsLeaver != isleaver))
      {
        if (nickname != null) player.Nickname = nickname;
        if (sex.HasValue) player.Sex = sex.Value;
        if (faction.HasValue) player.Faction = faction.Value;
        if (nival.HasValue) player.Nival = nival.Value;
        if (!String.IsNullOrEmpty(locale)) player.Locale = locale;
        if (leaverpoints.HasValue) player.LeaverPoints = leaverpoints.Value;
        if (isleaver.HasValue) player.IsLeaver = isleaver.Value;
        Update(player);
      }
      return player;
    }
  }
}
