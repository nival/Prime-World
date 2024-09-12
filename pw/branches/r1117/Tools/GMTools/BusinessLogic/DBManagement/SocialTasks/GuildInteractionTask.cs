using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{
  public class GuildInteractionTask : BaseMultipleTask<GuildInteractionInfoBL>
  {

    private readonly IGuildRepository guildRepository;
    private readonly IRepository<GuildSiege> guildSiegeRepository;
    private readonly IRepository<GuildInteraction> guildInteractionRepository;


    public GuildInteractionTask(IEnumerable<GuildInteractionInfoBL> infos)
      : this(infos, new GuildRepository(), new Repository<GuildSiege>(), new Repository<GuildInteraction>())
    {
    }

    public GuildInteractionTask(IEnumerable<GuildInteractionInfoBL> infos, IGuildRepository grepo, IRepository<GuildSiege> gsrepo, IRepository<GuildInteraction> girepo)
      : base(infos)
    {
      this.guildRepository = grepo;
      this.guildSiegeRepository = gsrepo;
      this.guildInteractionRepository = girepo;
      repos = new List<IDisposable> { grepo, gsrepo, girepo };
    }


    protected override void Execute(GuildInteractionInfoBL info)
    {
      var obj = new GuildInteraction
                  {
                    Guild = guildRepository.CheckAndGetById(info.GuildId),
                    TargetGuild = guildRepository.CheckAndGetById(info.TargetGuildId),
                    GuildSiege = info.SiegeId != 0 ? guildSiegeRepository.CheckAndGetById(info.SiegeId) : null,
                    Type = (GuildInteractionType) Enum.Parse(typeof (GuildInteractionType), info.Type, true),
                    WaitingTime = info.WaitingTime,
                    Timestamp = info.Timestamp
                  };
      guildInteractionRepository.Add(obj);
    }

  }

}