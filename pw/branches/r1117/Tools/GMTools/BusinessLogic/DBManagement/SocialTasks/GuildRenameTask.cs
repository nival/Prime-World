using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{
  public class GuildRenameTask : BaseMultipleTask<GuildInfoBL>
  {
    public const string RLOG_SOURCE = "guildrename";

    private readonly IGuildRepository guildRepository;
    private readonly IGuildMembershipRepository guildMembershipRepository;
    private readonly IPlayerRepository playerRepository;
    private readonly IResourceLogRepository resourceLogRepository;

    public GuildRenameTask(IEnumerable<GuildInfoBL> infos)
      : this(infos, new GuildRepository(), new GuildMembershipRepository(), new PlayerRepository(), new ResourceLogRepository())
    {
    }

    public GuildRenameTask(IEnumerable<GuildInfoBL> infos,
                           IGuildRepository grepo, IGuildMembershipRepository gmrepo, IPlayerRepository prepo, IResourceLogRepository rlrepo)
      : base(infos)
    {
      this.guildRepository = grepo;
      this.guildMembershipRepository = gmrepo;
      this.playerRepository = prepo;
      this.resourceLogRepository = rlrepo;
      repos = new List<IDisposable> {grepo, prepo, rlrepo};
    }

    protected override void Execute(GuildInfoBL info)
    {
      Player p = playerRepository.CheckAndGetById(info.Auid);

      Guild g = guildRepository.GetOrCreateById(info.GuildId);
      g.ShortName = info.ShortName;
      g.FullName = info.FullName;
      guildRepository.Update(g);

      if (!info.RChange.IsEmpty && info.ResourceLog == null)
      {
        var rl = new ResourceLog
                   {
                     Player = p,
                     Gain = false,
                     Source = RLOG_SOURCE,
                     GoldChange = -info.RChange.Gold,
                     SilverChange = -info.RChange.Silver,
                     PerlChange = -info.RChange.Perl,
                     RedPerlChange = -info.RChange.RedPerl,
                     PopulationChange = -info.RChange.Population,
                     Resource1Change = -info.RChange.Resource1,
                     Resource2Change = -info.RChange.Resource2,
                     Resource3Change = -info.RChange.Resource3,
                     ShardChange = -info.RChange.Shard,
                     CurrencyName = info.RChange.CurrencyName,
                     CurrencyChangeValue = -info.RChange.CurrencyValue,
                     GoldTotal = info.RTotal.Gold,
                     SilverTotal = info.RTotal.Silver,
                     PerlTotal = info.RTotal.Perl,
                     RedPerlTotal = info.RTotal.RedPerl,
                     PopulationTotal = info.RTotal.Population,
                     Resource1Total = info.RTotal.Resource1,
                     Resource2Total = info.RTotal.Resource2,
                     Resource3Total = info.RTotal.Resource3,
                     ShardTotal = info.RTotal.Shard,
                     CurrencyTotalValue = info.RTotal.CurrencyValue,
                     Timestamp = info.Timestamp
                   };
        resourceLogRepository.Add(rl);
        info.ResourceLog = rl;
      }

      var gm = guildMembershipRepository.GetByParams(p, g);
      if (gm == null)
      {
        gm = new GuildMembership
               {
                 Guild = g,
                 Player = p,
                 JoinDate = info.Timestamp,
                 LeaveDate = null,
                 Kicked = null
               };
        guildMembershipRepository.Add(gm);

        p.Guild = g;
        playerRepository.Update(p);
      }
    }
  }
}