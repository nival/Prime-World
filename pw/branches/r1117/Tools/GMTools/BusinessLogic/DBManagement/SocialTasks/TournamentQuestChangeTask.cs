using System;
using System.Collections.Generic;
using BusinessLogic.Social;
using DAL.Entities;
using DAL.Repositories;

namespace BusinessLogic.DBManagement
{

  public class TournamentQuestChangeTask : BaseMultipleTask<TournamentQuestChangeInfoBL>
  {

    private readonly IRepository<TournamentQuestChange> dquestChangeRepository;
    private readonly IPlayerRepository playerRepository;


    public TournamentQuestChangeTask( IEnumerable<TournamentQuestChangeInfoBL> infos )
      : this( infos, new Repository<TournamentQuestChange>(), new PlayerRepository() )
    {
    }

    public TournamentQuestChangeTask( IEnumerable<TournamentQuestChangeInfoBL> infos, IRepository<TournamentQuestChange> dqrepo, IPlayerRepository prepo )
      : base( infos )
    {
      this.dquestChangeRepository = dqrepo;
      this.playerRepository = prepo;
    }


    protected override void Execute( TournamentQuestChangeInfoBL info )
    {
      Player player = playerRepository.GetById( info.Auid );
      if ( player == null )
        throw new Exception( String.Format( "Cannot write quest change {0}, player is not exists", info ) );

      var dqchange = new TournamentQuestChange
      {
        Player = player,
        QuestIndex = info.QuestIndex,
        QuestName = info.QuestName,
        CompleteType = (TournamentQuestResult)info.Reason,
        Timestamp = info.Timestamp,
        AlternativeLine = info.Alternativeline
      };
      dquestChangeRepository.Add( dqchange );
    }

  }

}