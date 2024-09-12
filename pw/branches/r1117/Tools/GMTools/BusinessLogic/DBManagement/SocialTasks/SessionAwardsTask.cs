using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;
using log4net;

namespace BusinessLogic.DBManagement
{
  public class SessionAwardsTask : BaseMultipleTask<SessionAwardsInfoBL>
  {
    private static ILog _log = LogManager.GetLogger(typeof(SessionAwardsTask));

    public const string RLOG_SOURCE = "session";
    public const string TLOG_SOURCE = "sessionroll";

    private readonly IPlayerRepository playerRepository;
    private readonly ITalentLogRepository talentLogRepository;
    private readonly IResourceLogRepository resourceLogRepository;
    private readonly IRepository<GuildPointsLog> guildPointsLogRepository;
    private readonly IRepository<LeaverPointsLog> leaverPointsLogRepository;

    public SessionAwardsTask(IEnumerable<SessionAwardsInfoBL> awards)
      : this(awards, new PlayerRepository(), new TalentLogRepository(), new ResourceLogRepository(), new Repository<GuildPointsLog>(), new Repository<LeaverPointsLog>())
    {
    }

    public SessionAwardsTask(IEnumerable<SessionAwardsInfoBL> awards,
      IPlayerRepository prepo, ITalentLogRepository trrepo, IResourceLogRepository rlrepo, IRepository<GuildPointsLog> gplrepo, IRepository<LeaverPointsLog> lplrepo)
      : base(awards)
    {
      this.playerRepository = prepo;
      this.talentLogRepository = trrepo;
      this.resourceLogRepository = rlrepo;
      this.guildPointsLogRepository = gplrepo;
      this.leaverPointsLogRepository = lplrepo;
      repos = new List<IDisposable> {prepo, trrepo, rlrepo, gplrepo, lplrepo};
    }

    protected override void Execute(SessionAwardsInfoBL award)
    {
      Player p = playerRepository.GetById(award.Auid);
      if (p == null)
        throw new Exception(String.Format("Cannot write session award {0}, Player(id={1}) was not found", award, award.Auid));

      if (award.GuildPointsChange != 0 || award.PlayerPointsChange != 0)
      {
        if (p.Guild != null)
        {
          //var gplog = new GuildPointsLog
          //              {
          //                Type = GuildPointsLogType.Session,
          //                Guild = p.Guild,
          //                Player = p,
          //                GuildPointsChange = award.GuildPointsChange,
          //                GuildPointsTotal = award.GuildPointsTotal,
          //                PlayerPointsChange = award.PlayerPointsChange,
          //                PlayerPointsTotal = award.PlayerPointsTotal,
          //                PersistentId = award.SessionPersistentId,
          //                Timestamp = award.Timestamp,
          //              };
          //guildPointsLogRepository.Add(gplog);
        }
        else
        {
          _log.ErrorFormat("Can't write GuildPointsLog for Player(id={0}), because his Guild is null", p.Id);
        }
      }

      if (award.RChange != null && !award.RChange.IsEmpty && award.ResourceLog == null)
      {
        var rl = new ResourceLog
        {
          Player = p,
          Gain = true,
          Source = RLOG_SOURCE,
          PersistentId = award.SessionPersistentId,
          GoldChange = award.RChange.Gold,
          SilverChange = award.RChange.Silver,
          PerlChange = award.RChange.Perl,
          RedPerlChange = award.RChange.RedPerl,
          PopulationChange = award.RChange.Population,
          Resource1Change = award.RChange.Resource1,
          Resource2Change = award.RChange.Resource2,
          Resource3Change = award.RChange.Resource3,
          ShardChange = award.RChange.Shard,
        CurrencyName = award.RChange.CurrencyName,
        CurrencyChangeValue = -award.RChange.CurrencyValue,
            GoldTotal = award.RTotal.Gold,
          SilverTotal = award.RTotal.Silver,
          PerlTotal = award.RTotal.Perl,
          RedPerlTotal = award.RTotal.RedPerl,
          PopulationTotal = award.RTotal.Population,
          Resource1Total = award.RTotal.Resource1,
          Resource2Total = award.RTotal.Resource2,
          Resource3Total = award.RTotal.Resource3,
          ShardTotal = award.RTotal.Shard,
            CurrencyTotalValue = award.RTotal.CurrencyValue,
            Timestamp = award.Timestamp
        };
        resourceLogRepository.Add(rl);
        award.ResourceLog = rl;
      }

      if (award.LeaverPointsChange.LeaverPointsChange != 0 || award.LeaverPointsChange.LeaverPointsTotal > 0)
      {
        var task = new LeaverPointsChangeTask(new[] { award.LeaverPointsChange }, playerRepository, leaverPointsLogRepository);
        task.Execute();
      }

      if (award.Talents != null)
      {
        var talentsCopy = new List<SessionAwardsInfoBL.TalentInfoBL>(award.Talents);
        foreach (var t in talentsCopy)
        {
          talentLogRepository.Create(TLOG_SOURCE, null, award.Auid, t.Id, t.InstanceId, null, award.SessionPersistentId, award.Timestamp);
          award.Talents.Remove(t);
        }
      }
    }
  }
}