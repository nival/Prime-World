using System;
using System.Collections.Generic;
using DAL.Entities;
using NHibernate.Criterion;

namespace DAL.Repositories
{
  public interface IResourceLogRepository : IRepository<ResourceLog>
  {
    ResourceLog GetById(long id);
    IList<ResourceLog> GetByParametersPaged(long playerid, DateTime datefrom, DateTime dateto, bool? gain, int offset, int limit,
      bool spentgold, bool spentsilver, bool spentperl, bool spentredperl, bool spentresN, out int rows );
  }

  public class ResourceLogRepository : Repository<ResourceLog>, IResourceLogRepository
  {
    public override ResourceLog GetById(int id)
    {
      return GetById((long)id);
    }

    public ResourceLog GetById(long id)
    {
      return Session.Get<ResourceLog>(id);
    }

    public IList<ResourceLog> GetByParametersPaged(long playerid, DateTime datefrom, DateTime dateto, bool? gain, int offset, int limit,
      bool spentgold, bool spentsilver, bool spentperl, bool spentredperl, bool spentresN, out int rows)
    {
      if (datefrom >= dateto)
        throw new ArgumentException("DateFrom cannot be greater than DateTo", "datefrom");

      var query = Session.QueryOver<ResourceLog>()
        .Where(r => r.Player.Id == playerid && r.Timestamp >= datefrom && r.Timestamp <= dateto);
      if (gain != null)
        query.And(r => r.Gain == gain);

      var d = new Disjunction();
      if (spentgold)
        d.Add<ResourceLog>(r => r.GoldChange != 0);
      if (spentsilver)
        d.Add<ResourceLog>(r => r.SilverChange != 0);
      if (spentperl)
        d.Add<ResourceLog>(r => r.PerlChange != 0);
      if ( spentredperl )
        d.Add<ResourceLog>( r => r.RedPerlChange != 0 );
      if (spentresN)
        d.Add<ResourceLog>(r => r.Resource1Change != 0 || r.Resource2Change != 0 || r.Resource3Change != 0 || r.ShardChange != 0 || r.CurrencyChangeValue != 0);
      query.And(d);
     
      rows = query.RowCount();

      return query.OrderBy(r => r.Timestamp).Desc
        .Skip(offset).Take(limit)
        .List();
    }

  }
}
