using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{
  public class TalentLogTask : BaseMultipleTask<TalentChangeInfoBL>
  {
    private readonly ITalentLogRepository talentLogRepository;

    public TalentLogTask(IEnumerable<TalentChangeInfoBL> infos)
      : this(infos, new TalentLogRepository())
    {
    }

    public TalentLogTask(IEnumerable<TalentChangeInfoBL> infos, ITalentLogRepository trrepo)
      : base(infos)
    {
      this.talentLogRepository = trrepo;
      repos = new List<IDisposable> {trrepo};
    }

    protected override void Execute(TalentChangeInfoBL info)
    {
      talentLogRepository.Create(info.Operation, info.Data, info.Auid, info.TalentId, info.TalentInstanceId,
                                 info.BoundHero != 0 ? info.BoundHero : (int?) null, null, info.Timestamp);
    }
  }
}