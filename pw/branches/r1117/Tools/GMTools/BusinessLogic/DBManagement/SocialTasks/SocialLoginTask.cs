using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{
  public class SocialLoginTask : BaseMultipleTask<LoginInfoBL>
  {
    private readonly IPlayerRepository playerRepository;
    private readonly ISocialSessionRepository socialSessionRepository;
    private readonly IGuildRepository guildRepository;

    public SocialLoginTask(IEnumerable<LoginInfoBL> infos)
      : this(infos, new PlayerRepository(), new SocialSessionRepository(), new GuildRepository())
    {
    }

    public SocialLoginTask(IEnumerable<LoginInfoBL> infos, IPlayerRepository prepo, ISocialSessionRepository srepo, IGuildRepository grepo)
      : base(infos)
    {
      this.playerRepository = prepo;
      this.socialSessionRepository = srepo;
      this.guildRepository = grepo;
      repos = new List<IDisposable> { prepo, srepo, grepo };
    }

    protected override void Execute(LoginInfoBL info)
    {
      Player p = playerRepository.CreateOrUpdate(info.UserId, info.Login, null, (Faction) info.Faction, info.IsDeveloper, info.Locale, info.LeaverPoints, info.IsLeaver);

      var session = new SocialSession
                      {
                        Player = p,
                        PlayerIp = info.Ip,
                        Server = info.Server,
                        Cluster = info.Cluster,
                        StartTime = info.Timestamp
                      };
      socialSessionRepository.Add(session);

      if (info.GuildId != 0)
      {
        var guild = guildRepository.GetById(info.GuildId);
        if (guild == null)
        {
          guild = new Guild
                    {
                      Id = info.GuildId,
                      ShortName = info.GuildShortName,
                      FullName = info.GuildFullName
                    };
          guildRepository.Add(guild);
        }
        else if (!String.IsNullOrEmpty(info.GuildShortName) && !String.IsNullOrEmpty(info.GuildFullName)
                 && (guild.ShortName != info.GuildShortName || guild.FullName != info.GuildFullName))
        {
          guild.ShortName = info.GuildShortName;
          guild.FullName = info.GuildFullName;
          guildRepository.Update(guild);
        }

        if (p.Guild == null || p.Guild.Id != guild.Id)
        {
          p.Guild = guild;
          playerRepository.Update(p);
        }
      }
      else
      {
        if (p.Guild != null)
        {
          p.Guild = null;
          playerRepository.Update(p);
        }
      }
    }
  }

}