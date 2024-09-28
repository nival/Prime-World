using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{
  public class GuildShopBuyTask : BaseMultipleTask<GuildShopBuyInfoBL>
  {
    private readonly IPlayerRepository playerRepository;
    private readonly IGuildRepository guildRepository;
    private readonly IRepository<GuildShopItem> guildShopItemRepository;
    private readonly IRepository<GuildShopBuy> guildShopBuyRepository;
    private readonly IRepository<GuildPointsLog> guildPointsLogRepository;
    private readonly IRepository<ResourceLog> resourcesLogRepository;


    public GuildShopBuyTask(IEnumerable<GuildShopBuyInfoBL> infos)
      : this(infos, new PlayerRepository(), new GuildRepository(), new Repository<GuildShopItem>(), new Repository<GuildShopBuy>(), new Repository<GuildPointsLog>(), new Repository<ResourceLog>())
    {
    }

    public GuildShopBuyTask(IEnumerable<GuildShopBuyInfoBL> infos, IPlayerRepository prepo, IGuildRepository grepo, IRepository<GuildShopItem> gsirepo, IRepository<GuildShopBuy> gsbrepo, IRepository<GuildPointsLog> gplrepo, IRepository<ResourceLog> rlrepo)
      : base(infos)
    {
      playerRepository = prepo;
      guildRepository = grepo;
      guildShopItemRepository = gsirepo;
      guildShopBuyRepository = gsbrepo;
      guildPointsLogRepository = gplrepo;
      resourcesLogRepository = rlrepo;
      repos = new List<IDisposable> { prepo, grepo, gsirepo, gsbrepo, gplrepo, rlrepo };
    }

    protected override void Execute(GuildShopBuyInfoBL info)
    {
      var player = playerRepository.CheckAndGetById(info.Auid);
      var guild = guildRepository.CheckAndGetById(info.GuildId);

      var gplog = new GuildPointsLog
                    {
                      Type = GuildPointsLogType.GuildShopBuy,
                      Guild = guild,
                      Player = player,
                      GuildPointsChange = info.GuildPointsChange,
                      GuildPointsTotal = info.GuildPointsTotal,
                      PlayerPointsChange = info.PlayerPointsChange,
                      PlayerPointsTotal = info.PlayerPointsTotal,
                      PersistentId = null,
                      Timestamp = info.Timestamp
                    };
      guildPointsLogRepository.Add(gplog);

      guildShopBuyRepository.Add(new GuildShopBuy
                                   {
                                     Player = player,
                                     Guild = guild,
                                     GuildShopItem = guildShopItemRepository.CheckAndGetById(info.ShopItemId),
                                     GuildPointsLog = gplog,
                                     ShopLevel = info.ShopLevel,
                                     HasSuzerain = info.HasSuzerain,
                                     Timestamp = info.Timestamp
                                   });

      resourcesLogRepository.Add(new ResourceLog()
      {
          Player = player,
          Gain = false,
          Source = "guildshopbuy",
          GoldChange = -info.ResourceTableChange.Gold,
          SilverChange = -info.ResourceTableChange.Silver,
          PerlChange = -info.ResourceTableChange.Perl,
          RedPerlChange = -info.ResourceTableChange.RedPerl,
          PopulationChange = -info.ResourceTableChange.Population,
          Resource1Change = -info.ResourceTableChange.Resource1,
          Resource2Change = -info.ResourceTableChange.Resource2,
          Resource3Change = -info.ResourceTableChange.Resource3,
          ShardChange = -info.ResourceTableChange.Shard,
          CurrencyName = info.ResourceTableChange.CurrencyName,
          CurrencyChangeValue = -info.ResourceTableChange.CurrencyValue,
          GoldTotal = info.ResourceTableTotal.Gold,
          SilverTotal = info.ResourceTableTotal.Silver,
          PerlTotal = info.ResourceTableTotal.Perl,
          RedPerlTotal = info.ResourceTableTotal.RedPerl,
          PopulationTotal = info.ResourceTableTotal.Population,
          Resource1Total = info.ResourceTableTotal.Resource1,
          Resource2Total = info.ResourceTableTotal.Resource2,
          Resource3Total = info.ResourceTableTotal.Resource3,
          ShardTotal = info.ResourceTableTotal.Shard,
          CurrencyTotalValue = info.ResourceTableTotal.CurrencyValue,
          Timestamp = info.Timestamp
      });
    }
  }
}