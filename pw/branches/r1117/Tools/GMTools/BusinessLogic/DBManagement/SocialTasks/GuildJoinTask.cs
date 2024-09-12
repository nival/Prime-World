using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;
using log4net;

namespace BusinessLogic.DBManagement
{
  public class GuildJoinTask : BaseMultipleTask<GuildCoreInfoBL>
  {
    private static ILog _log = LogManager.GetLogger(typeof (GuildJoinTask));

    private readonly IGuildRepository guildRepository;
    private readonly IGuildMembershipRepository guildMembershipRepository;
    private readonly IPlayerRepository playerRepository;

    public GuildJoinTask(IEnumerable<GuildCoreInfoBL> infos)
      : this(infos, new GuildRepository(), new GuildMembershipRepository(), new PlayerRepository())
    {
    }

    public GuildJoinTask(IEnumerable<GuildCoreInfoBL> infos,
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
      Player p = playerRepository.CheckAndGetById(info.Auid);

      Guild g = guildRepository.GetById(info.GuildId);
      if (g == null)
      {
        g = new Guild
              {
                Id = info.GuildId,
                MembersCount = info.Members
              };
        guildRepository.Add(g);
      }
      else if (g.MembersCount != info.Members)
      {
        g.MembersCount = info.Members;
        guildRepository.Update(g);
      }

      var gm = new GuildMembership
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