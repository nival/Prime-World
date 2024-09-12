using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{

  public class DynamicQuestChangeTask : BaseMultipleTask<DynamicQuestChangeInfoBL>
  {

    private readonly IRepository<DynamicQuestChange> dquestChangeRepository;
    private readonly IPlayerRepository playerRepository;


    public DynamicQuestChangeTask(IEnumerable<DynamicQuestChangeInfoBL> infos) 
      : this(infos, new Repository<DynamicQuestChange>(), new PlayerRepository())
    {
    }

    public DynamicQuestChangeTask(IEnumerable<DynamicQuestChangeInfoBL> infos, IRepository<DynamicQuestChange> dqrepo, IPlayerRepository prepo)
      : base(infos)
    {
      this.dquestChangeRepository = dqrepo;
      this.playerRepository = prepo;
    }


    protected override void Execute(DynamicQuestChangeInfoBL info)
    {
      Player player = playerRepository.GetById(info.Auid);
      if (player == null)
        throw new Exception(String.Format("Cannot write quest change {0}, player is not exists", info));

      var dqchange = new DynamicQuestChange
                       {
                         Player = player,
                         QuestIndex = info.QuestIndex,
                         QuestName = info.QuestName,
                         ChangeType = (QuestChangeType) info.Reason,
                         Timestamp = info.Timestamp,
                         AlternativeLine =info.Alternativeline
                       };
      dquestChangeRepository.Add(dqchange);
    }

  }

}