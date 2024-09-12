using System;
using System.Collections.Generic;
using System.Linq;
using DAL.Entities;
using NHibernate;
using NHibernate.Criterion;
using NHibernate.Transform;
using log4net;

namespace DAL.Repositories
{
  public interface IClaimRepository : IRepository<Claim>
  {
    IEnumerable<Claim> GetActiveClaimsByPlayerId(long playerId, string locale);
    IEnumerable<Claim> GetClaimsByGMUserOperationId(int operationId);
    IEnumerable<Claim> GetClaimsByGMUserOperation(GMUserOperation operation);

    IEnumerable<PlayerClaimCountDTO> GetPlayerClaimCounts(PlayerClaimFilter filter, string orderby, bool asc, int offset, int limit);
  }

  public class PlayerClaimCountDTO
  {
    public long PlayerId { get; set; }
    public string PlayerNickname { get; set; }
    public int ClaimsCount { get; set; }
    public string ClaimsLocaleCount { get; set; }
    public int OffenceClaimsCount { get; set; }
    public int UnfairClaimsCount { get; set; }
    public int BotClaimsCount { get; set; }
    public int GMUserOperationsCount { get; set; }
    public int GMBansCount { get; set; }
    public int GMUnbansCount { get; set; }
    public int GMMutesCount { get; set; }
    public int GMUnmutesCount { get; set; }
    public int GMForgivesCount { get; set; }
    public int GMLeaverPointsCount { get; set; }
    public int GMModeratorMuteCount { get; set; }
    public string Muted { get; set; }
    public string Banned { get; set; }
    public int TotalRows { get; set; }
    public int LeaverPoints { get; set; }
    public int LeaverChanged { get; set; }
    public int LeaverChangedByGM { get; set; }
  }

  public class PlayerClaimFilter
  {
    public enum ComplaintsType
    {
      Offence,
      Unfair,
      BotUsage
    }

    public enum HistoryType
    {
      Bans,
      Mutes,
      Unbans,      
      Unmutes,
      Forgives,  
      LeaverPoints,
      ModeratorMute
      
    }

    public DateTime StartDate;
    public DateTime EndDate;
    public ComplaintsType? CurrentComplaintsType;
    public int? MinComplaints;
    public int? MaxComplaints;
    public HistoryType? CurrentHistoryType;
    public int? MinHistory;
    public int? MaxHistory;
    public string Locale;
    public List<string> Muids;
    public long? ReportedBy;

    public int? MinLeaverPoints;
    public int? MaxLeaverPoints;
    public int? MinLeaverStatusChanges;
    public int? MaxLeaverStatusChanges;
    public int? MinLeaverStatusChangesByGM;
    public int? MaxLeaverStatusChangesByGM;
  }

  public class ClaimRepository : Repository<Claim>, IClaimRepository
  {
    private static ILog _log = LogManager.GetLogger(typeof(ClaimRepository));

    public IEnumerable<Claim> GetActiveClaimsByPlayerId(long playerId, string locale)
    {
      var player = Session.Get<Player>(playerId);
      if (player == null)
        throw new DALException(String.Format("Player(id={0}) is not found in database", playerId));

      var query = Session.QueryOver<Claim>()
                      .Where(c => c. ToPlayer == player && c.GMUserOperation == null);

      if (!String.IsNullOrEmpty(locale))
      {
        return query.JoinQueryOver(c => c.FromPlayer)
                    .And(p => p.Locale == locale)
                    .List<Claim>();
      }

      return query.List<Claim>();
    }

    public IEnumerable<Claim> GetClaimsByGMUserOperationId(int operationId)
    {
      var operation = Session.Get<GMUserOperation>(operationId);
      if (operation == null)
        throw new DALException(String.Format("GMUserOperation(id={0}) is not found in database", operationId));

      return GetClaimsByGMUserOperation(operation);
    }

    public IEnumerable<Claim> GetClaimsByGMUserOperation(GMUserOperation operation)
    {
      if (operation == null)
        throw new ArgumentNullException("operation");

      return Session.CreateCriteria<Claim>()
                    .Add(Restrictions.Eq("GMUserOperation", operation))
                    .List<Claim>();
    }

    public IEnumerable<PlayerClaimCountDTO> GetPlayerClaimCounts(PlayerClaimFilter filter, string orderby, bool asc,
      int offset, int limit)
    {
      if (filter.StartDate > filter.EndDate)
        return null;

      if (typeof (PlayerClaimCountDTO).GetProperties().All(p => p.Name != orderby))
      {
        _log.WarnFormat("Invalid ordering by '{0}'", orderby);
        orderby = "ClaimsCount";
        asc = false;
      }

      // Да, это может шокировать неподготовленного читателя,
      // но иначе, как средствами SQL этого сделать нельзя.
      //   (за автоматический реформат текста ниже - бан и проклятье)

      string sql = @"
select sq.*,
  count(g.id) as ""GMUserOperationsCount"",
  count(case when g.type = 0 then g.id end) as ""GMBansCount"",
  count(distinct case when g.type = 1 then g.id end) as ""GMMutesCount"",
  count(distinct case when g.type = 2 then g.id end) as ""GMUnbansCount"",
  count(distinct case when g.type = 3 then g.id end) as ""GMUnmutesCount"",
  count(distinct case when g.type = 4 then g.id end) as ""GMForgivesCount"",
  count(distinct case when g.type = 5 then g.id end) as ""GMLeaverPointsCount"",
  count(distinct case when g.type = 6 then g.id end) as ""GMModeratorMuteCount"",

  case coalesce(max(
    case when g.type = 1 
           and (g.minutes = 0 or g.timestamp + interval'1minute'*g.minutes > now() at time zone 'utc')
           and not exists (
             select 1 from gm_useroperation g2 
             where g2.type in (1,3) and g2.timestamp > g.timestamp 
               and g2.player = g.player)
         then (case when g.minutes = 0 then cast('infinity' as timestamp)
                    else g.timestamp + interval'1minute'*g.minutes end) end), cast('-infinity' as timestamp) )
  when 'infinity' then 'perm. muted' when '-infinity' then null else 'muted' end as ""Muted"",

  case coalesce(max(
    case when g.type = 0 
           and (g.minutes = 0 or g.timestamp + interval'1minute'*g.minutes > now() at time zone 'utc')
           and not exists (
             select 1 from gm_useroperation g2 
             where g2.type in (0,2) and g2.timestamp > g.timestamp 
               and g2.player = g.player)
         then (case when g.minutes = 0 then cast('infinity' as timestamp)
                    else g.timestamp + interval'1minute'*g.minutes end) end), cast('-infinity' as timestamp) )
   when 'infinity' then 'perm. banned' when '-infinity' then null else 'banned' end as ""Banned""
   
from
(

select 
  c.toplayer as ""PlayerId"", 
  tp.nickname as ""PlayerNickname"",
  tp.leaverpoints as ""LeaverPoints"",
  coalesce(tp.leavercount, 0) as ""LeaverChanged"",
  coalesce(tp.leavergmcount, 0) as ""LeaverChangedByGM"",
  count(distinct c.id) as ""ClaimsCount"",
  count(distinct case when category = 0 then c.id else null end) as ""OffenceClaimsCount"",
  count(distinct case when category = 1 then c.id else null end) as ""UnfairClaimsCount"",
  count(distinct case when category = 2 then c.id else null end) as ""BotClaimsCount"",
  cast (array_agg (c.locale) as varchar) as ""ClaimsLocaleCount"",
  count(*) over () as ""TotalRows""

from claim c
 join player tp on tp.id = c.toplayer
" + (filter.Locale != null ? " join player fp on fp.id = c.fromplayer" : "") + @"

where c.gmuseroperation is null
  and c.timestamp between :startDate and :endDate

" + (filter.Locale != null ? String.Format("and c.locale = '{0}' and fp.locale = '{0}'\n", filter.Locale) : "")

  + (filter.Muids != null && filter.Muids.Count > 0 ? String.Format("and c.muid in ({0})\n", String.Join(",", filter.Muids.Select(m => "'" + m + "'").ToArray())) : "") 
  
  + (filter.ReportedBy.HasValue ? " and c.fromplayer = " + filter.ReportedBy : "")

  + (filter.MinLeaverPoints.HasValue || filter.MaxLeaverPoints.HasValue
      ? String.Format(" and tp.leaverpoints between {0} and {1}\n", filter.MinLeaverPoints ?? 0, filter.MaxLeaverPoints ?? Int32.MaxValue) : "")

  + (filter.MinLeaverStatusChanges.HasValue || filter.MaxLeaverStatusChanges.HasValue
      ? String.Format(" and coalesce(tp.leavercount, 0) between {0} and {1}", filter.MinLeaverStatusChanges ?? 0, filter.MaxLeaverStatusChanges ?? Int32.MaxValue) : "")

  + (filter.MinLeaverStatusChangesByGM.HasValue || filter.MaxLeaverStatusChangesByGM.HasValue
      ? String.Format(" and coalesce(tp.leavergmcount, 0) between {0} and {1}", filter.MinLeaverStatusChangesByGM ?? 0, filter.MaxLeaverStatusChangesByGM ?? Int32.MaxValue) : "")

  + @"

group by c.toplayer, tp.nickname, tp.leaverpoints, tp.leavercount, tp.leavergmcount
"
  + ( filter.MinComplaints.HasValue || filter.MaxComplaints.HasValue
      ? ( "having "
        + (filter.CurrentComplaintsType.HasValue
             ? String.Format("count(distinct case when category = {0} then c.id else null end) ", (int)filter.CurrentComplaintsType.Value)
             : "count(distinct c.id) ")
        + String.Format("between {0} and {1}", filter.MinComplaints ?? 0, filter.MaxComplaints ?? Int32.MaxValue) )
      : "" ) + @"

) sq

left join gm_useroperation g on g.player = sq.""PlayerId""

group by
  sq.""PlayerId"",
  sq.""PlayerNickname"",
  sq.""LeaverPoints"",
  sq.""LeaverChanged"",
  sq.""LeaverChangedByGM"",
  sq.""ClaimsCount"",
  sq.""OffenceClaimsCount"",
  sq.""UnfairClaimsCount"",
  sq.""BotClaimsCount"",
  sq.""ClaimsLocaleCount"",
  sq.""TotalRows""

"
  + (filter.CurrentHistoryType.HasValue
       ? String.Format("having count(distinct case when g.type = {0} then g.id else null end) between {1} and {2}",
                       (int)filter.CurrentHistoryType.Value, filter.MinHistory ?? 0, filter.MaxHistory ?? Int32.MaxValue)
       : "") + @"

order by """ + orderby + (asc ? "\"" : "\" desc");

      return Session
        .CreateSQLQuery(sql)
        .AddScalar("PlayerId", NHibernateUtil.Int64)
        .AddScalar("PlayerNickname", NHibernateUtil.String)
        .AddScalar("ClaimsCount", NHibernateUtil.Int32)
        .AddScalar("ClaimsLocaleCount", NHibernateUtil.String)
        .AddScalar("OffenceClaimsCount", NHibernateUtil.Int32)
        .AddScalar("UnfairClaimsCount", NHibernateUtil.Int32)
        .AddScalar("BotClaimsCount", NHibernateUtil.Int32)
        .AddScalar("GMUserOperationsCount", NHibernateUtil.Int32)
        .AddScalar("GMBansCount", NHibernateUtil.Int32)
        .AddScalar("GMUnbansCount", NHibernateUtil.Int32)
        .AddScalar("GMMutesCount", NHibernateUtil.Int32)
        .AddScalar("GMUnmutesCount", NHibernateUtil.Int32)
        .AddScalar("GMForgivesCount", NHibernateUtil.Int32)
        .AddScalar("GMLeaverPointsCount", NHibernateUtil.Int32)
        .AddScalar("GMModeratorMuteCount", NHibernateUtil.Int32)
        .AddScalar("Muted", NHibernateUtil.String)
        .AddScalar("Banned", NHibernateUtil.String)
        .AddScalar("TotalRows", NHibernateUtil.Int32)
        .AddScalar("LeaverPoints", NHibernateUtil.Int32)
        .AddScalar("LeaverChanged", NHibernateUtil.Int32)
        .AddScalar("LeaverChangedByGM", NHibernateUtil.Int32)
        .SetParameter("startDate", filter.StartDate)
        .SetParameter("endDate", filter.EndDate)
        .SetResultTransformer(new AliasToBeanResultTransformer(typeof(PlayerClaimCountDTO)))
        .SetFirstResult(offset)
        .SetMaxResults(limit)
        .List<PlayerClaimCountDTO>();
    }

  }

}