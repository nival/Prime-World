using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{
  public class GuildPointsChangeTask : BaseMultipleTask<GuildPointsChangeInfoBL>
  {
    private readonly IPlayerRepository playerRepository;
    private readonly IGuildRepository guildRepository;
    private readonly IRepository<GuildPointsLog> guildPointsLogRepository;


    public GuildPointsChangeTask(IEnumerable<GuildPointsChangeInfoBL> infos)
      : this(infos, new PlayerRepository(), new GuildRepository(), new Repository<GuildPointsLog>())
    {
    }

    public GuildPointsChangeTask(IEnumerable<GuildPointsChangeInfoBL> infos, IPlayerRepository prepo, IGuildRepository grepo, IRepository<GuildPointsLog> gplrepo)
      : base(infos)
    {
      playerRepository = prepo;
      guildRepository = grepo;
      guildPointsLogRepository = gplrepo;
      repos = new List<IDisposable> { prepo, grepo, gplrepo };
    }

    protected override void Execute(GuildPointsChangeInfoBL info)
    {
      var player = info.Auid != 0
                     ? playerRepository.CheckAndGetById(info.Auid)
                     : null;
      var guild = guildRepository.CheckAndGetById(info.GuildId);

      var gplog = new GuildPointsLog
                    {
                      Guild = guild,
                      Player = player,
                      GuildPointsChange = info.GuildPointsChange,
                      GuildPointsTotal = info.GuildPointsTotal,
                      PlayerPointsChange = info.PlayerPointsChange,
                      PlayerPointsTotal = info.PlayerPointsTotal,
                      PersistentId = null,
                      Timestamp = info.Timestamp
                    };
      try
      {
        gplog.Type = (GuildPointsLogType)Enum.Parse(typeof(GuildPointsLogType), info.Source, true);
      }
      catch
      {
        gplog.Type = GuildPointsLogType.Unknown;
      }

      guildPointsLogRepository.Add(gplog);
    }
  }
}