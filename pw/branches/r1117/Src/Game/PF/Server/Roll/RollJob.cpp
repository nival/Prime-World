#include "stdafx.h"
#include "RollJob.h"
#include "RollSeClient.h"
#include "RollLog.h"
#include "RollServiceInstance.h"
#include "RollServiceInstanceRunner.h"

namespace roll
{


  static const StatisticService::SessionPlayerScoring* FindScoringByClientId( const vector<SPostGamePerUserData>& _postData, UserId _clientId )
  {
    for ( int i = 0, count = _postData.size(); i < count; ++i )
    {
      if ( _postData[i].clientId == _clientId )
        return &_postData[i].scoring;
    }
    return 0;
  }

  static const StatisticService::SessionPlayerExtra* FindExtraByClientId( const vector<SPostGamePerUserData>& _postData, UserId _clientId )
  { 

    
    for ( int i = 0, count = _postData.size(); i < count; ++i )
    {
      if ( _postData[i].clientId == _clientId )
      {
        //ROLL_LOG_DBG("FindExtraByClientId: partySize %d, enemyPartySize %d",_postData[i].extra.partySize, _postData[i].extra.enemyPartySize );
        return &_postData[i].extra;
      }
    }

    return 0;
  }


  BaseJob::BaseJob( DropNRoll * _logic, IClient * _client, SeClientWorker * _seClient ) :
  logic( _logic ), client( _client ),
    seClient( _seClient ),
    state( EState::Rolling )
  {}



  bool BaseJob::Poll()
  {
    switch ( state )
    {
    case EState::Rolling:
      Roll();
      SwitchTo( EState::ClientNotification );
      break;

    case EState::ClientNotification:
      NotifyClient();
      BeginDelivery();
      SwitchTo( EState::Delivery );
      break;

    case EState::Delivery:
      if ( CheckDelivery() )
        SwitchTo( EState::Done );
      break;

    default:
    case EState::Done:
      return false;
    }

    return true;
  }



  void BaseJob::ImplAddNewMessage( SeMessageBase * msg )
  {
    //FIXME: realyy we dont have to store handles / monitor their delivery
    //it's done mainly to track service load
    //Wich probably will be low anyways

    seClient->AddMessage( msg );
    seMessages.push_back( msg );
  }



  bool BaseJob::CheckDelivery()
  {
    int delivered = 0, failed = 0;
    for ( int i = 0; i < seMessages.size(); ++i )
      switch ( seMessages[i]->DeliveryStatus() )
    {
      case ESeMsgStatus::Delivered:
        ++delivered;
        break;
      case ESeMsgStatus::Failed:
        ++failed;
        break;
    }

    if ( ( delivered + failed ) >= seMessages.size() )
    {
      DeliveryFinished( delivered, failed );
      return true;
    }

    return false;
  }






  SessionRollJob::SessionRollJob( DropNRoll * _logic, IClient * _client, SeClientWorker * _seClient, const SPreGameData & _preGame, const SPostGameData & _postGame, Instance* _instance ) :
  BaseJob( _logic, _client, _seClient ),
    preGame( _preGame ), postGame( _postGame ), instance(_instance)
  {}



  void SessionRollJob::Roll()
  {
    ROLL_LOG_MSG( "Rolling awards. game_id=%016x, mode=%s(%d)", preGame.socialLobbyGameId, EMode::ToString( preGame.mode ), (int)preGame.mode );

    Logic()->RollAwards( result, guildResult, preGame, postGame );
  }



  void SessionRollJob::NotifyClient()
  {
    if ( Client() )
    {
      ROLL_LOG_MSG( "Notifying client about roll results. game_id=%016x", preGame.socialLobbyGameId );
      Client()->RollResults( result );
    }
  }



  void SessionRollJob::BeginDelivery()
  {
    begin_delivery_time = timer::Now();
    for ( int i = 0; i < result.size(); ++i )
    {
      
      const StatisticService::SessionPlayerScoring* scoring = FindScoringByClientId( postGame.users, result[i].userId );
      NI_ASSERT( scoring, "Scoring not found" );
      const StatisticService::SessionPlayerExtra* extra = FindExtraByClientId( postGame.users, result[i].userId );
      NI_ASSERT( extra, "Extra not found" );
      ROLL_LOG_DBG("BeginDelivery: partySize %d, enemyPartySize %d", extra->partySize, extra->enemyPartySize );
      ImplAddNewMessage( new SeUserMessageFromGame( SeClient()->Config(), preGame.socialLobbyGameId, result[i], preGame.mapDesc, preGame.mode == EMode::CustomGame, *scoring, *extra ) );
    }

    map<NCore::TGuildAuid, SGuildAward>::iterator it = guildResult.begin();
    for ( ; it != guildResult.end(); ++it )
      ImplAddNewMessage( new SeGuildMessage( SeClient()->Config(), preGame.socialLobbyGameId, it->second ) );

    if (instance && instance->InstSvc()){
      instance->InstSvc()->AutoPerfCounterRate("begin_delivery_awards_count", result.size());
      instance->InstSvc()->AutoPerfCounterRate("begin_delivery_guild_awards_count", guildResult.size());
      ROLL_LOG_MSG( "Roll begin delivery. game_id=%016x, bd_awards_count=%d, bd_guild_awards_count=%d", preGame.socialLobbyGameId, result.size(), guildResult.size() );
    }

  }



  void SessionRollJob::DeliveryFinished( int delivered, int failed )
  {
    if (instance && instance->InstSvc())
    {
      instance->InstSvc()->AutoPerfCounterRate("awards_delivered_count", delivered);
      instance->InstSvc()->AutoPerfCounterRate("awards_failed_count", failed);
      int lsz = SeClient()->LineSize();
      instance->InstSvc()->AutoPerfCounterValue("awards_line_size", lsz);
      long awards_in_line_time =  timer::Now() - begin_delivery_time;
      instance->InstSvc()->AutoPerfCounterValue("awards_in_line_time", awards_in_line_time ); 
    
      ROLL_LOG_MSG( "Roll result delivery done. game_id=%016x, delivered=%d, failed=%d, line_size=%d, awards_in_line_time=%d sec", preGame.socialLobbyGameId, delivered, failed, lsz, awards_in_line_time );
    } 
    else 
    {
      ROLL_LOG_WRN( "Service instance is bad. Roll result delivery done. game_id=%016x, delivered=%d, failed=%d", preGame.socialLobbyGameId, delivered, failed);
    }

  }







  ForgeRollJob::ForgeRollJob( DropNRoll * _logic, IClient * _client, SeClientWorker * _seClient, const SForgeRollData & _data ) :
  BaseJob( _logic, _client, _seClient ),
    data( _data )
  {}



  void ForgeRollJob::Roll()
  {
    ROLL_LOG_MSG( "Rolling for forge. uid=%d, roll_id=%016x", data.uid, data.rollId );

    Logic()->RollForge( result, data );
  }



  void ForgeRollJob::NotifyClient()
  {
    if ( Client() )
    {
      ROLL_LOG_MSG( "Notifying client about forge roll results. uid=%d, roll_id=%016x", data.uid, data.rollId );
      Client()->ForgeRollAck();
    }
  }



  void ForgeRollJob::BeginDelivery()
  {
    ImplAddNewMessage( new SeUserMessage( SeClient()->Config(), data.rollId, result ) );
  }



  void ForgeRollJob::DeliveryFinished( int delivered, int failed )
  {
    ROLL_LOG_MSG( "Forge roll result delivery done. uid=%d, roll_id=%016x, delivered=%d, failed=%d", data.uid, data.rollId, delivered, failed );
  }

} //namespace roll
