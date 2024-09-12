using System;
using System.Collections.Generic;
using System.Linq;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{

  public class AfterPartyTask : BaseMultipleTask<AfterPartyInfoBL>
  {

    private readonly IPlayerRepository playerRepo;
    private readonly IRepository<AfterParty> afterPartyRepo;
    private readonly IRepository<AfterPartyMember> afterPartyMemberRepo;


    public AfterPartyTask(IEnumerable<AfterPartyInfoBL> infos)
      : this(infos, new PlayerRepository(), new Repository<AfterParty>(), new Repository<AfterPartyMember>())
    {
    }

    public AfterPartyTask(IEnumerable<AfterPartyInfoBL> infos, IPlayerRepository prepo, IRepository<AfterParty> aprepo, IRepository<AfterPartyMember> apmrepo) 
      : base(infos)
    {
      this.playerRepo = prepo;
      this.afterPartyRepo = aprepo;
      this.afterPartyMemberRepo = apmrepo;
      repos = new List<IDisposable> {apmrepo, aprepo, prepo};
    }


    protected override void Execute(AfterPartyInfoBL info)
    {
      long persistentid = info.Members
        .Where(m => m.SessionPersistentId != 0)
        .Select(m => m.SessionPersistentId)
        .FirstOrDefault();

      var afterparty = new AfterParty
                       {
                         PersistentId = persistentid,
                         MMStarted = info.MMStarted,
                         Timestamp = info.Timestamp
                       };
      afterPartyRepo.Add(afterparty);

      foreach (var member in info.Members)
      {
        var player = playerRepo.CheckAndGetById(member.Auid);
        
        afterPartyMemberRepo.Add(new AfterPartyMember
                                 {
                                   AfterParty = afterparty,
                                   Player = player,
                                   PersistentId = member.SessionPersistentId != 0 ? member.SessionPersistentId : (long?)null,
                                   Kicked = member.Kicked,
                                   Leaved = member.Leaved,
                                   Timestamp = info.Timestamp
                                 });
      }
    }

  }

}