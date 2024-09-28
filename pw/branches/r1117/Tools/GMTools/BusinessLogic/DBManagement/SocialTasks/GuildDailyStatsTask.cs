using System;
using System.Collections.Generic;
using System.Linq;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{
  public class GuildDailyStatsTask : BaseMultipleTask<GuildDailyStatsInfoBL>
  {
    
    private readonly IGuildRepository guildRepository;
    private readonly IRepository<GuildDailyStats> guildDailyStatsRepository;

    public GuildDailyStatsTask(IEnumerable<GuildDailyStatsInfoBL> infos)
      : this(infos, new GuildRepository(), new Repository<GuildDailyStats>())
    {
    }

    public GuildDailyStatsTask(IEnumerable<GuildDailyStatsInfoBL> infos, IGuildRepository grepo, IRepository<GuildDailyStats> gsrepo)
      : base(infos)
    {
      this.guildRepository = grepo;
      this.guildDailyStatsRepository = gsrepo;
      repos = new List<IDisposable> { grepo, gsrepo };
    }


    protected override void Execute(GuildDailyStatsInfoBL info)
    {
      var obj = new GuildDailyStats
                  {
                    Guild = guildRepository.CheckAndGetById(info.GuildId),
                    Rating = info.GuildRating,
                    Rank = info.GuildRank,
                    GuildPoints = info.GuildPoints,
                    GuildPointsToday = info.GuildRatingToday,
                    Timestamp = info.Timestamp,
                  };
      if (info.Vassals != null && info.Vassals.Count > 0)
      {
        obj.VassalsCount = info.Vassals.Count;
        obj.VassalsPoints = (int) info.Vassals.Values.Sum();
      }
      
      guildDailyStatsRepository.Add(obj);
    }

  }

}