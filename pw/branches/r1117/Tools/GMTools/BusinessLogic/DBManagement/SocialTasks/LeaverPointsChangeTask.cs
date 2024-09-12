using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{

  public class LeaverPointsChangeTask : BaseMultipleTask<LeaverPointsChangeInfoBL>
  {
    private readonly IPlayerRepository playerRepository;
    private readonly IRepository<LeaverPointsLog> leaverPointsLogRepository;

    public LeaverPointsChangeTask(IEnumerable<LeaverPointsChangeInfoBL> infos)
      : this(infos, new PlayerRepository(), new Repository<LeaverPointsLog>())
    {
    }

    public LeaverPointsChangeTask(IEnumerable<LeaverPointsChangeInfoBL> infos, IPlayerRepository prepo, IRepository<LeaverPointsLog> lplrepo)
      : base(infos)
    {
      playerRepository = prepo;
      leaverPointsLogRepository = lplrepo;
    }


    protected override void Execute(LeaverPointsChangeInfoBL info)
    {
      var p = playerRepository.CheckAndGetById(info.Auid);

      var obj = new LeaverPointsLog
                {
                  Player = p,
                  PersistentId = info.PersistentId,
                  Type = info.Type,
                  LeaverPointsChange = info.LeaverPointsChange,
                  LeaverPointsTotal = info.LeaverPointsTotal,
                  IsLeaverChanged = info.IsLeaverChanged,
                  IsLeaver = info.IsLeaver,
                  IsBadBehaviour = info.IsBadBehaviour,
                  Timestamp = info.Timestamp
                };
      leaverPointsLogRepository.Add(obj);

      p.LeaverPoints = info.LeaverPointsTotal;
      p.IsLeaver = info.IsLeaver;
      if (info.IsLeaver && info.IsLeaverChanged)
      {
        // Hardcode! Но не хочется тащить енум с типами через трифт ради определения операции ГМа
        if (info.Type != null && info.Type.IndexOf("GM", StringComparison.InvariantCultureIgnoreCase) != -1)
          p.LeaverGMCount = (p.LeaverGMCount ?? 0) + 1;
        else
          p.LeaverCount = (p.LeaverCount ?? 0) + 1;
      }
      playerRepository.Update(p);
    }

  }

}