using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{
  public class GuildDisbandTask : BaseMultipleTask<GuildCoreInfoBL>
  {
    private readonly IGuildRepository guildRepository;
    private readonly IGuildMembershipRepository guildMembershipRepository;
    private readonly IPlayerRepository playerRepository;

    public GuildDisbandTask(IEnumerable<GuildCoreInfoBL> infos)
      : this(infos, new GuildRepository(), new GuildMembershipRepository(), new PlayerRepository())
    {
    }

    public GuildDisbandTask(IEnumerable<GuildCoreInfoBL> infos,
                            IGuildRepository grepo, IGuildMembershipRepository gmrepo, IPlayerRepository prepo)
      : base(infos)
    {
      this.guildRepository = grepo;
      this.guildMembershipRepository = gmrepo;
      this.playerRepository = prepo;
      repos = new List<IDisposable> {grepo, gmrepo, prepo};
    }

    protected override void Execute(GuildCoreInfoBL info)
    {
      Player p = playerRepository.GetById(info.Auid);
      if (p == null)
        throw new Exception(String.Format("Player(id={0}) was not found", info.Auid));

      Guild g = guildRepository.GetById(info.GuildId);
      if (g == null)
        throw new Exception(String.Format("Guild(id={0}) was not found", info.GuildId));

      g.DisbandingDate = info.Timestamp;
      guildRepository.Update(g);

      var gm = guildMembershipRepository.GetByParams(p, g);
      gm.Kicked = false;
      gm.LeaveDate = info.Timestamp;
      guildMembershipRepository.Update(gm);

      p.Guild = null;
      playerRepository.Update(p);
    }
  }
}