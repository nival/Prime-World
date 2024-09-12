using System;
using DAL.Entities;
using System.Linq;

namespace DAL.Repositories
{
  public interface IGuildMembershipRepository : IRepository<GuildMembership>
  {
    GuildMembership GetByParams(Player player, Guild guild);
  }


  public class GuildMembershipRepository : Repository<GuildMembership>, IGuildMembershipRepository
  {
    public GuildMembership GetByParams(Player player, Guild guild)
    {
      if (player == null) throw new ArgumentNullException("player");
      if (guild == null) throw new ArgumentNullException("guild");

      return Session.QueryOver<GuildMembership>()
                    .Where(gm => gm.Guild == guild && gm.Player == player)
                    .OrderBy(gm => gm.JoinDate).Desc
                    .Take(1).List()
                    .FirstOrDefault();
    }
  }
}