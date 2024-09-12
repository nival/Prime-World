using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{

  public class GuildSiegeTask : BaseMultipleTask<GuildSiegeInfoBL>
  {

    private readonly IGuildRepository guildRepository;
    private readonly IRepository<GuildSiege> guildSiegeRepository;
    private readonly IRepository<GuildSiegeParticipant> guildSiegeParticipantRepository;
    private readonly IRepository<GuildPointsLog> guildPointsLogRepository;


    public GuildSiegeTask(IEnumerable<GuildSiegeInfoBL> infos)
      : this(infos, new GuildRepository(), new Repository<GuildSiege>(), new Repository<GuildSiegeParticipant>(), new Repository<GuildPointsLog>())
    {
    }

    public GuildSiegeTask(IEnumerable<GuildSiegeInfoBL> infos, IGuildRepository grepo, IRepository<GuildSiege> gsrepo, IRepository<GuildSiegeParticipant> gsprepo, IRepository<GuildPointsLog> gplrepo)
      : base(infos)
    {
      guildRepository = grepo;
      guildSiegeRepository = gsrepo;
      guildSiegeParticipantRepository = gsprepo;
      guildPointsLogRepository = gplrepo;
      repos = new List<IDisposable> { grepo, gsrepo, gsprepo, gplrepo };
    }


    protected override void Execute(GuildSiegeInfoBL info)
    {
      var g = guildRepository.GetOrCreateById(info.GuildId);
      var tg = guildRepository.GetOrCreateById(info.TargetGuildId);
      var wg = guildRepository.GetOrCreateById(info.WinnerGuildId);

      Guild tsg = null;
      if (info.TargetSuzerainId != 0)
        tsg = guildRepository.GetOrCreateById(info.TargetSuzerainId);


      var gplog = new GuildPointsLog
      {
        Type = GuildPointsLogType.GuildSiege,
        Guild = g,
        GuildPointsChange = info.GuildPointsChange,
        GuildPointsTotal = info.GuildPointsTotal,
        PersistentId = null,
        Timestamp = info.StartTimestamp
      };
      guildPointsLogRepository.Add(gplog);


      var gsiege = new GuildSiege
                     {
                       Id = info.SiegeId,
                       Guild = g,
                       TargetGuild = tg,
                       TargetSuzerainGuild = tsg,
                       Rating = info.GuildRating,
                       TargetRating = info.TargetGuildRating,
                       TargetSuzerainRating = tsg != null ? info.TargetSuzerainRating : (int?) null,
                       GuildPointsLog = gplog,
                       StartTime = info.StartTimestamp,
                       EndTime = info.EndTimestamp,
                       Winner = wg
                     };
      guildSiegeRepository.Add(gsiege);

      foreach (var p in info.Participants)
      {
        var g_p = guildRepository.GetOrCreateById(p.GuildId);

        GuildPointsLog gplog_p = p.GuildId == info.GuildId
                                   ? gplog
                                   : new GuildPointsLog
                                       {
                                         Type = GuildPointsLogType.GuildSiege,
                                         Guild = g_p,
                                         GuildPointsChange = p.GuildPointsChange,
                                         GuildPointsTotal = p.GuildPointsTotal,
                                         PersistentId = null,
                                         Timestamp = p.StartTimestamp
                                       };
        guildPointsLogRepository.Add(gplog_p);

        var gsiegepart = new GuildSiegeParticipant
                           {
                             GuildSiege = gsiege,
                             Guild = g_p,
                             Rating = p.GuildRating,
                             GuildPointsLog = gplog_p,
                             SiegePoints = p.SiegePoints,
                             StartTime = p.StartTimestamp,
                             EndTime = p.EndTimestamp
                           };
        guildSiegeParticipantRepository.Add(gsiegepart);
      }

    }

  }

}