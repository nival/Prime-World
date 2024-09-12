using System;
using System.Collections.Generic;
using System.Linq;
using DAL.Entities;
using NHibernate;
using NHibernate.Transform;
using log4net;
using NHibernate.Criterion;
using NHibernate.Linq.Functions;

namespace DAL.Repositories
{

  public interface IHistoryRecordsRepository : IRepository<DictionaryEntity>
  {
    IEnumerable<SocialSession> GetSessionsByPlayerId( long playerId, int pageNum, out int pageQuant );

    IEnumerable<CharacterUnlock> GetCharacterUnlocksByPlayerId( long playerId, int pageNum, out int pageQuant, out string errorIfExist );
    
    IEnumerable<PlayerResourcesDTO> GetPlayerResources(long playerid, DateTime startdate, DateTime enddate, List<Int32> talents, bool? gain,
      bool spentgold, bool spentsilver, bool spentperl, bool spentredperl, bool spentresN, bool talentchange, String resourcesEvent, String talentsEvent,
      int offset, int limit, out int rows);
    
    IEnumerable<FactionChange> GetFractionChangesByPlayerId(long playerId, int pageNum, out int pageQuant);
    
    IEnumerable<CWPlayerPointsDTO> GetCWPlayerPoints(long playerid, DateTime startdate, DateTime enddate, int offset, int limit, out int rows);

    IEnumerable<CWGuildPointsDTO> GetCWGuildPoints(long guildid, DateTime startdate, DateTime enddate, int offset, int limit, out int rows);

    IEnumerable<LeaverPointsLog> GetLeaverPoints(long playerid, DateTime startdate, DateTime enddate, int offset, int limit, out int rows);

    IEnumerable<RuneOperationDTO> GetRuneOperations(long playerid, DateTime startdate, DateTime enddate);

  }



  public class HistoryRecordsRepository : Repository<DictionaryEntity>, IHistoryRecordsRepository
  {
    private static int pageSize = 50;//количество записей на странице
    private static ILog log = LogManager.GetLogger( typeof( HistoryRecordsRepository ) );


    public IEnumerable<SocialSession> GetSessionsByPlayerId( long playerId, int pageNum, out int pageQuant )
    {
      var player = Session.Get<Player>( playerId );
      var rowCount = this.Session.CreateCriteria<SocialSession>()
          .Add( Restrictions.Eq( "Player", player ) )
          .SetProjection( Projections.RowCount() ).FutureValue<Int32>();

      var results = Session.CreateCriteria<SocialSession>()
        .Add( Restrictions.Eq( "Player", player ) )
        .AddOrder(Order.Desc("StartTime"))
        .SetFirstResult( ( pageNum - 1 ) * pageSize )
        .SetMaxResults( pageSize )
        .Future<SocialSession>()
        .ToList<SocialSession>();
      pageQuant = (int)Math.Ceiling( (double)rowCount.Value / pageSize );
      return results;
    }


    public IEnumerable<CharacterUnlock> GetCharacterUnlocksByPlayerId( long playerId, int pageNum, out int pageQuant, out string errorIfExist )
    {
      pageQuant = 0;
      errorIfExist = null;
      var player = Session.Get<Player>( playerId );
      if ( player == null )
      {
        log.WarnFormat( "Cannot get GmDeleteTalent collection, player with id = {0} was not found", playerId );
        errorIfExist = string.Format( "Cannot get GmDeleteTalent collection, player with id = {0} was not found", playerId );
        return null;
      }
      CharacterUnlock cu = null;
      PlayerCharacter pc = null;
      Character c = null;

      var rowCount = Session.QueryOver<CharacterUnlock>( () => cu )
            .JoinAlias( () => cu.PlayerCharacter, () => pc )
            .Where( () => pc.Player == player )
            .Select( Projections.Count( Projections.Id() ) )
            .FutureValue<int>();
      var products = Session.QueryOver<CharacterUnlock>( () => cu )
                .JoinAlias( () => cu.PlayerCharacter, () => pc )
                .JoinAlias( () => pc.Character, () => c )
                .Where( () => pc.Player == player )
                .Skip( ( pageNum - 1 ) * pageSize )
                .Take( pageSize )
                .Future()
                .ToList<CharacterUnlock>();
      products.ForEach( x => x.CharacterName = x.PlayerCharacter.Character.Name );
      pageQuant = (int)Math.Ceiling( (double)rowCount.Value / pageSize );
      return products;
    }


    public IEnumerable<PlayerResourcesDTO> GetPlayerResources(long playerid, DateTime startdate, DateTime enddate, List<Int32> talents, bool? gain,
      bool spentgold, bool spentsilver, bool spentperl, bool spentredperl, bool spentresN, bool talentchange, String resourcesEvent, String talentsEvent, int offset,
      int limit, out int rows)
    {
      // Полный трэш, но NHibernate не поддерживает union запросы
      // так что либо добавлять/маппить view, либо вот так.

      // Переводим входные параметры в фрагменты sql скрипта
      string rl_clause = "";
      if (!String.IsNullOrEmpty(resourcesEvent)) rl_clause += " and source = '" + resourcesEvent + "'";
      if (gain.HasValue) rl_clause += " and gain = " + gain.Value;
      var clauses = new List<string>();
      if (spentgold) clauses.Add("goldchange != 0");
      if (spentsilver) clauses.Add("silverchange != 0");
      if (spentperl) clauses.Add("perlchange != 0");
      if (spentredperl) clauses.Add("redperlchange != 0");
      if (spentresN) clauses.Add("resource1change != 0 or resource2change != 0 or resource3change != 0 or shardchange != 0 or currencychange is not null");
      if (clauses.Count > 0)
        rl_clause += " and (" + String.Join(" or ", clauses.ToArray()) + ")";
      else
        rl_clause = " and 1=0"; // Условие для моментального получения пустого результата

      string tl_clause = "";
      if (talentchange)
      {
        if (!String.IsNullOrEmpty(talentsEvent)) tl_clause += " and operation = '" + talentsEvent + "'";
        if (talents.Count > 0)
        {
          tl_clause += " and talent in (" + String.Join(", ", talents.Select(x => x.ToString()).ToArray()) + ")";
        }
      }
      else
      {
        tl_clause = " and 1=0";
      }

      // подсчет количества строк
      int count1 = Session
        .CreateSQLQuery(@"
          select count(*) as ""Count""
          from resourcelog
          where timestamp between :startdate and :enddate
            and player = :playerid
          " + rl_clause)
        .AddScalar("Count", NHibernateUtil.Int32)
        .SetParameter("startdate", startdate)
        .SetParameter("enddate", enddate)
        .SetParameter("playerid", playerid)
        .List<int>()[0];

      int count2 = Session
        .CreateSQLQuery(@"
          select count(*) as ""Count""
          from talentlog
          where timestamp between :startdate and :enddate
            and player = :playerid
          " + tl_clause)
        .AddScalar("Count", NHibernateUtil.Int32)
        .SetParameter("startdate", startdate)
        .SetParameter("enddate", enddate)
        .SetParameter("playerid", playerid)
        .List<int>()[0];

      rows = count1 + count2;

      // Основной запрос
      return Session
        .CreateSQLQuery(@"
        select
          timestamp as ""Timestamp"",
          case when gain then 'Income' else 'Expense' end ""Type"",
          source||(case when buildingname is not null then ' '||buildingname else '' end)  as ""Info"",
          abs(goldchange) as ""GoldChange"",
          abs(silverchange) as ""SilverChange"",
          abs(perlchange) as ""PerlChange"",
          abs(redperlchange) as ""RedPerlChange"",
          abs(resource1change) as ""Resource1Change"",
          abs(resource2change) as ""Resource2Change"",
          abs(resource3change) as ""Resource3Change"",
          abs(shardchange) as ""ShardChange"",
          currencychange as ""CurrencyChange"",
          currencychangevalue as ""CurrencyChangeValue"",
          goldtotal - goldchange as ""GoldBefore"",
          silvertotal - silverchange as ""SilverBefore"",
          perltotal - perlchange as ""PerlBefore"",
          redperltotal - redperlchange as ""RedPerlBefore"",
          resource1total - resource1change as ""Resource1Before"",
          resource2total - resource2change as ""Resource2Before"",
          resource3total - resource3change as ""Resource3Before"",
          shardtotal - shardchange as ""ShardBefore"",
          currencytotal as ""CurrencyBefore"",
          currencytotalvalue as ""CurrencyBeforeValue""
        from resourcelog
        where timestamp between :startdate and :enddate
          and player = :playerid
          " + rl_clause + @"

        union all

        select
          tl.timestamp,
          'Talent',
          operation||' '''||t.name||''' (id='||talentinstanceid||')'
            ||(case when c.name is not null then ', bound='''||c.name||'''' else '' end)
            ||(case when persistentid is not null then ', session='||persistentid else '' end)
            ||(case when data is not null then ', data='''||data||'''' else '' end),
          null, null, null, null, null, null, null, null, null, null,
          null, null, null, null, null, null, null, null, null, null
        from talentlog tl
          join talent t on t.id = tl.talent
          left join character c on c.id = tl.character
        where timestamp between :startdate and :enddate
          and player = :playerid
          " + tl_clause + @"

        order by 1 desc"
        )
        .AddScalar("Timestamp", NHibernateUtil.DateTime)
        .AddScalar("Type", NHibernateUtil.String)
        .AddScalar("Info", NHibernateUtil.String)
        .AddScalar("GoldChange", NHibernateUtil.Int32)
        .AddScalar("SilverChange", NHibernateUtil.Int32)
        .AddScalar("PerlChange", NHibernateUtil.Int32)
        .AddScalar("RedPerlChange", NHibernateUtil.Int32)
        .AddScalar("Resource1Change", NHibernateUtil.Int32)
        .AddScalar("Resource2Change", NHibernateUtil.Int32)
        .AddScalar("Resource3Change", NHibernateUtil.Int32)
        .AddScalar("ShardChange", NHibernateUtil.Int32)
        .AddScalar("CurrencyChange", NHibernateUtil.String)
        .AddScalar("CurrencyChangeValue", NHibernateUtil.Int32)
        .AddScalar("GoldBefore", NHibernateUtil.Int32)
        .AddScalar("SilverBefore", NHibernateUtil.Int32)
        .AddScalar("PerlBefore", NHibernateUtil.Int32)
        .AddScalar("RedPerlBefore", NHibernateUtil.Int32)
        .AddScalar("Resource1Before", NHibernateUtil.Int32)
        .AddScalar("Resource2Before", NHibernateUtil.Int32)
        .AddScalar("Resource3Before", NHibernateUtil.Int32)
        .AddScalar("ShardBefore", NHibernateUtil.Int32)
        .AddScalar("CurrencyBefore", NHibernateUtil.String)
        .AddScalar("CurrencyBeforeValue", NHibernateUtil.Int32)
        .SetParameter("startdate", startdate)
        .SetParameter("enddate", enddate)
        .SetParameter("playerid", playerid)
        .SetResultTransformer(new AliasToBeanResultTransformer(typeof (PlayerResourcesDTO)))
        .SetFirstResult(offset)
        .SetMaxResults(limit)
        .List<PlayerResourcesDTO>();
    }

    public IEnumerable<FactionChange> GetFractionChangesByPlayerId(long playerId, int pageNum, out int pageQuant)
    {
      pageQuant = 0;
      var player = Session.Get<Player>(playerId);
      if (player == null)
      {
        log.WarnFormat("Cannot get FractionChanges collection, player with id = {0} was not found", playerId);
        return null;
      }
      FactionChange factionChange = null;
      ResourceLog resourceLog = null;

      var rowCount = Session.QueryOver<FactionChange>(() => factionChange)
            .JoinAlias(() => factionChange.ResourceLog, () => resourceLog)
            .Where(() => factionChange.Player == player)
            .Select(Projections.Count(Projections.Id()))
            .FutureValue<int>();
      var products = Session.QueryOver<FactionChange>(() => factionChange)
                .Left.JoinAlias(() => factionChange.ResourceLog, () => resourceLog)
                .Where(() => factionChange.Player == player)
                .Skip((pageNum - 1) * pageSize)
                .Take(pageSize)
                .Future()
                .ToList<FactionChange>();
      pageQuant = (int)Math.Ceiling((double)rowCount.Value / pageSize);
      return products;
    }


    public IEnumerable<CWPlayerPointsDTO> GetCWPlayerPoints(
      long playerid, DateTime startdate, DateTime enddate, int offset, int limit, out int rows)
    {
      rows = Session.QueryOver<GuildPointsLog>()
                    .Where(l => l.Player.Id == playerid && l.Timestamp >= startdate && l.Timestamp <= enddate)
                    .RowCount();

      // Опять строковый запрос. Я снова оказался слишком умный (или тупой) для NHibernate
      // и не смог написать left join который бы джойнился не fkey->pkey, а наоборот

      return Session
        .CreateSQLQuery(@"
          select gpl.timestamp as ""Timestamp"",
                 gpl.type as ""Type"",
                 gpl.guildpointschange as ""GuildPointsChange"",
                 gpl.playerpointschange as ""PlayerPointsChange"",
                 gpl.guildpointstotal as ""GuildPointsTotal"",
                 gpl.playerpointstotal as ""PlayerPointsTotal"",
                 gsi.name as ""GuildShopItemName""
          from guildpointslog gpl
            left join guildshopbuy gsb on gsb.guildpointslog = gpl.id
              and gsb.timestamp between :startdate and :enddate
              and gsb.player = :playerid
            left join guildshopitem gsi on gsi.id = gsb.guildshopitem
          where gpl.timestamp between :startdate and :enddate
            and gpl.player = :playerid ")
        .AddScalar("Timestamp", NHibernateUtil.DateTime)
        .AddScalar("Type", NHibernateUtil.String)
        .AddScalar("GuildPointsChange", NHibernateUtil.Int32)
        .AddScalar("PlayerPointsChange", NHibernateUtil.Int32)
        .AddScalar("GuildPointsTotal", NHibernateUtil.Int32)
        .AddScalar("PlayerPointsTotal", NHibernateUtil.Int32)
        .AddScalar("GuildShopItemName", NHibernateUtil.String)
        .SetParameter("startdate", startdate)
        .SetParameter("enddate", enddate)
        .SetParameter("playerid", playerid)
        .SetResultTransformer(new AliasToBeanResultTransformer(typeof(CWPlayerPointsDTO)))
        .SetFirstResult(offset)
        .SetMaxResults(limit)
        .List<CWPlayerPointsDTO>();
    }
 
    public IEnumerable<CWGuildPointsDTO> GetCWGuildPoints(
      long guildid, DateTime startdate, DateTime enddate, int offset, int limit, out int rows)
    {
      rows = Session.QueryOver<GuildPointsLog>()
              .Where(l => l.Guild.Id == guildid && l.Timestamp >= startdate && l.Timestamp <= enddate && l.GuildPointsChange != 0)
              .RowCount();

      return Session
        .CreateSQLQuery(@"
                select gpl.timestamp as ""Timestamp"",
                       gpl.type as ""Type"",
                       gpl.player as ""Player"",
                       gpl.guildpointschange as ""GuildPointsChange"",
                       gpl.guildpointstotal as ""GuildPointsTotal"",
                       gsi.name as ""GuildShopItemName"",
                       coalesce(gs.id, 0) as ""SiegeId"",
                       coalesce(gs.targetguild, 0) as ""TargetGuild""
                from guildpointslog gpl
                  left join guildshopbuy gsb on gsb.guildpointslog = gpl.id 
                    and gsb.timestamp between :startdate and :enddate and gsb.guild = :guildid
                  left join guildshopitem gsi on gsi.id = gsb.guildshopitem
                  left join guildsiege gs on gs.guildpointslog = gpl.id
                    and gs.starttime between :startdate and :enddate and gs.guild = :guildid
                where gpl.timestamp between :startdate and :enddate
                  and gpl.guild = :guildid
                  and gpl.guildpointschange != 0")
        .AddScalar("Timestamp", NHibernateUtil.DateTime)
        .AddScalar("Type", NHibernateUtil.String)
        .AddScalar("Player", NHibernateUtil.Int64)
        .AddScalar("GuildPointsChange", NHibernateUtil.Int32)
        .AddScalar("GuildPointsTotal", NHibernateUtil.Int32)
        .AddScalar("GuildShopItemName", NHibernateUtil.String)
        .AddScalar("SiegeId", NHibernateUtil.Int64)
        .AddScalar("TargetGuild", NHibernateUtil.Int64)
        .SetParameter("startdate", startdate)
        .SetParameter("enddate", enddate)
        .SetParameter("guildid", guildid)
        .SetResultTransformer(new AliasToBeanResultTransformer(typeof(CWGuildPointsDTO)))
        .SetFirstResult(offset)
        .SetMaxResults(limit)
        .List<CWGuildPointsDTO>();
    }

    public IEnumerable<LeaverPointsLog> GetLeaverPoints(long playerid, DateTime startdate, DateTime enddate, int offset, int limit, out int rows)
    {
      var query = Session.QueryOver<LeaverPointsLog>()
        .Where(l => l.Player.Id == playerid && l.Timestamp >= startdate && l.Timestamp <= enddate);

      rows = query.RowCount();

      return query.OrderBy(l => l.Timestamp).Desc.Skip(offset).Take(limit).List();
    }

    public IEnumerable<RuneOperationDTO> GetRuneOperations(long playerid, DateTime startdate, DateTime enddate)
    {
      return Session.CreateSQLQuery(@"
        select timestamp as ""Timestamp"",
               'Roll' as ""Operation"",
               source||' '||(case when persistentid is not null and persistentid != 0 then cast(persistentid as text) else '' end) as ""Data"",
               percent as ""RunePercent"",
               runescountold as ""RunesCountOld"",
               runescountnew as ""RunesCountNew""
        from runeroll
          join rune on rune.id = runeroll.rune
        where timestamp between :startdate and :enddate
          and player = :playerid

        union all

        select timestamp,
               'Replenish',
               null,
               percent,
               null,
               null
        from runereplenish
          join rune on rune.id = runereplenish.rune
        where timestamp between :startdate and :enddate
          and player = :playerid

        union all

        select timestamp,
               'Expire',
               'trans left: '||transactionsleft||', bonusleft:'||bonusleft,
               percent,
               null,
               null
        from runeexpire
          join rune on rune.id = runeexpire.rune
        where timestamp between :startdate and :enddate
          and player = :playerid

        union all

        select timestamp,
               'RuneHeroApply',
               'hero: '||hero,
               percent,
               null,
               null
        from runeheroapply
          join rune on rune.id = runeheroapply.rune
        where timestamp between :startdate and :enddate
          and player = :playerid

        union all

        select timestamp,
               'Unsoulbound',
               'talentCrc: '||talent,
               percent,
               null,
               null
        from runeunsoulbound
          join rune on rune.id = runeunsoulbound.rune
        where timestamp between :startdate and :enddate
          and player = :playerid

        order by 1")
        .AddScalar("Timestamp", NHibernateUtil.DateTime)
        .AddScalar("Operation", NHibernateUtil.String)
        .AddScalar("Data", NHibernateUtil.String)
        .AddScalar("RunePercent", NHibernateUtil.Int32)
        .AddScalar("RunesCountOld", NHibernateUtil.Int32)
        .AddScalar("RunesCountNew", NHibernateUtil.Int32)
        .SetParameter("startdate", startdate)
        .SetParameter("enddate", enddate)
        .SetParameter("playerid", playerid)
        .SetResultTransformer(new AliasToBeanResultTransformer(typeof(RuneOperationDTO)))
        .List<RuneOperationDTO>();
    }

  }


  public class PlayerResourcesDTO
  {
    public DateTime Timestamp { get; set; }
    public string Type { get; set; }
    public string Info { get; set; }
    public int? GoldChange { get; set; }
    public int? SilverChange { get; set; }
    public int? PerlChange { get; set; }
    public int? RedPerlChange { get; set; }
    public int? Resource1Change { get; set; }
    public int? Resource2Change { get; set; }
    public int? Resource3Change { get; set; }
    public int? ShardChange { get; set; }
    public string CurrencyChange { get; set; }
    public int? CurrencyChangeValue { get; set; }
    public int? GoldBefore { get; set; }
    public int? SilverBefore { get; set; }
    public int? PerlBefore { get; set; }
    public int? RedPerlBefore { get; set; }
    public int? Resource1Before { get; set; }
    public int? Resource2Before { get; set; }
    public int? Resource3Before { get; set; }
    public int? ShardBefore { get; set; }
    public string CurrencyBefore { get; set; }
    public int? CurrencyBeforeValue { get; set; }
  }


  public class CWPlayerPointsDTO
  {
    public DateTime Timestamp { get; set; }
    public string Type { get; set; }
    public int GuildPointsChange { get; set; }
    public int PlayerPointsChange { get; set; }
    public int GuildPointsTotal { get; set; }
    public int PlayerPointsTotal { get; set; }
    public string GuildShopItemName { get; set; }
  }

  public class CWGuildPointsDTO
  {
    public DateTime Timestamp { get; set; }
    public string Type { get; set; }
    public long Player { get; set; }
    public int GuildPointsChange { get; set; }
    public int GuildPointsTotal { get; set; }
    public string GuildShopItemName { get; set; }
    public long SiegeId { get; set; }
    public long TargetGuild { get; set; }
  }

  public class RuneOperationDTO
  {
    public DateTime Timestamp { get; set; }
    public string Operation { get; set; }
    public string Data { get; set; }
    public int RunePercent { get; set; }
    public int? RunesCountOld { get; set; }
    public int? RunesCountNew { get; set; }
  }

}