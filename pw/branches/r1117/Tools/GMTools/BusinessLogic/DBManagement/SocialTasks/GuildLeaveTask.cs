using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;
using log4net;

namespace BusinessLogic.DBManagement
{
  public class GuildLeaveTask : BaseMultipleTask<GuildLeaveInfoBL>
  {
    private static ILog _log = LogManager.GetLogger(typeof (GuildLeaveTask));

    private readonly IGuildRepository guildRepository;
    private readonly IGuildMembershipRepository guildMembershipRepository;
    private readonly IPlayerRepository playerRepository;

    public GuildLeaveTask(IEnumerable<GuildLeaveInfoBL> infos)
      : this(infos, new GuildRepository(), new GuildMembershipRepository(), new PlayerRepository())
    {
    }

    public GuildLeaveTask(IEnumerable<GuildLeaveInfoBL> infos,
                          IGuildRepository grepo, IGuildMembershipRepository gmrepo, IPlayerRepository prepo)
      : base(infos)
    {
      this.guildRepository = grepo;
      this.guildMembershipRepository = gmrepo;
      this.playerRepository = prepo;
      repos = new List<IDisposable> { grepo, gmrepo, prepo };
    }

    protected override void Execute(GuildLeaveInfoBL info)
    {
      Player p = playerRepository.CheckAndGetById(info.Auid);

      Guild g = guildRepository.GetById(info.GuildId);
      if (g == null)
        return;

      g.MembersCount = info.Members;
      guildRepository.Update(g);

      var gm = guildMembershipRepository.GetByParams(p, g);
      gm.Kicked = info.Kicked;
      gm.LeaveDate = info.Timestamp;
      guildMembershipRepository.Update(gm);

      p.Guild = null;
      playerRepository.Update(p);
    }
  }
}