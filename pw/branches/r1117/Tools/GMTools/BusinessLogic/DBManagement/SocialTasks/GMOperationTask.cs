using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{
  public class GMOperationTask : BaseMultipleTask<GMOperationInfoBL>
  {
    private readonly IPlayerRepository playerRepository;
    private readonly IGMOperationRepository gmoperationRepository;

    public GMOperationTask(IEnumerable<GMOperationInfoBL> infos)
      :this(infos, new PlayerRepository(), new GMOperationRepository())
    {
    }

    public GMOperationTask(IEnumerable<GMOperationInfoBL> infos, IPlayerRepository prepo, IGMOperationRepository gmrepo)
      : base(infos)
    {
      playerRepository = prepo;
      gmoperationRepository = gmrepo;
      repos = new List<IDisposable> {prepo, gmrepo};
    }

    protected override void Execute(GMOperationInfoBL info)
    {
      Player p = playerRepository.GetById(info.UserId);
      if (p == null)
        throw new Exception(String.Format("Player(id={0}) was not found", info.UserId));

      var gm = new GMOperation
                 {
                   Player = p,
                   Type = (GMOperationType) Enum.Parse(typeof (GMOperationType), info.Type, true),
                   Data = info.Data,
                   GMLogin = info.GMLogin,
                   Timestamp = info.Timestamp
                 };
      gmoperationRepository.Add(gm);
    }
  }
}