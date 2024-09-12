#include "stdafx.h"
#include "GameTestClient_Roll.h"
#include "Server/Roll/LRollClient.auto.h"


namespace gtc
{

struct Client_Roll::RollClientCb : public roll::IClient, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( RollClientCb, roll::IClient, BaseObjectMT );

  RollClientCb( Client_Roll * _owner ) : owner( _owner ) {}

  virtual void RollResults( const vector<roll::SUserAward> & _award ) {
    if ( StrongMT<Client_Roll> locked = owner.Lock() )
      locked->OnRollResults( _award );
  }

  virtual void ForgeRollAck() {}

  virtual void RollFailed() {
    if ( StrongMT<Client_Roll> locked = owner.Lock() )
      locked->OnRollFailed();
  }

  WeakMT<Client_Roll> owner;
};



Client_Roll::Client_Roll( const TestClientBaseParams & _params ) :
TestClientBase( _params ),
stage( ERollTestStage::Init )
{
}



StepResult Client_Roll::MainStep()
{
  NI_PROFILE_FUNCTION;

  StepResult result = TestClientBase::MainStep();
  if ( !result.Ok() || result.Handled() )
    return result;

  if ( stage_ != Stage::LOGIN_FINISHED )
    return StepResult( false, true );
  else
    return StepResult( true, StepRollTest() );
}



bool Client_Roll::StepRollTest()
{
  if ( balancer )
    balancer->step();

  switch ( stage )
  {
    case ERollTestStage::Init:
      MessageTrace( "Requesting roll balancer..." );

      factory_->RegisterAttach<roll::IClient, roll::LIClient>();

      balancer = new rpc::IfaceRequester<roll::RIBalancer>;
      balancer->init( gateKeeper_, roll::serviceIds::BalancerService, roll::serviceIds::BalancerInterface );
      ChangeRollStage( ERollTestStage::WaitingBalancer );
      return true;

    case ERollTestStage::WaitingBalancer:
      if ( balancer->isopen() )
      {
        MessageTrace( "Got roll balancer, allocating instance..." );
        balancer->iface()->AllocateInstance( this, &Client_Roll::OnInstanceAllocation );
        ChangeRollStage( ERollTestStage::WaitingInstance );
      }
      return true;

    case ERollTestStage::WaitingInstance:
      return true;

    case ERollTestStage::WaitingRoll:
      return true;

    case ERollTestStage::Finished:
      return false;

    default:
      return false;
  }
}


void Client_Roll::OnInstanceAllocation( roll::RIInstance * inst )
{
  NI_VERIFY( RollStage() == ERollTestStage::WaitingInstance, "", return );

  MessageTrace( "Roll instance allocated. Requesting roll..." );

  rollInstance = inst;

  roll::SPreGameData preGameData;
  roll::SPostGameData postGameData;
  GenerateRollData( preGameData, postGameData );

  clientCb = new RollClientCb( this );
  rollInstance->Roll( clientCb, preGameData, postGameData );

  ChangeRollStage( ERollTestStage::WaitingRoll );
}



void Client_Roll::OnRollResults( const vector<roll::SUserAward> & _award )
{
  NI_VERIFY( RollStage() == ERollTestStage::WaitingRoll, "", return );

  MessageTrace( "Roll results: %d pcs", _award.size() );

  clientCb = 0;
  rollInstance = 0;

  ChangeRollStage( ERollTestStage::Finished );
}



void Client_Roll::OnRollFailed()
{
  MessageTrace( "Roll failed!" );

  clientCb = 0;
  rollInstance = 0;

  ChangeRollStage( ERollTestStage::Finished );
}



void Client_Roll::GenerateRollData( roll::SPreGameData & preGame, roll::SPostGameData & postGame )
{
  const int base = 10;
  const mmaking::EBasket::Enum basket = mmaking::EBasket::Newbie;

  preGame.mode = roll::EMode::PvP;
  preGame.socialLobbyGameId = rand();
  preGame.users.resize( base );
  preGame.mapDesc = "/Maps/Multiplayer/PFmap/PVP.ADMPDSCR";
  preGame.mmBasket = basket;
  for ( int i = 0; i < preGame.users.size(); ++i )
  {
    roll::SPreGamePerUserData & perUser = preGame.users[i];
    perUser.clientId = 1000 + rand() % 99000;
    perUser.faction = ( i % 2 ) ? lobby::ETeam::Team1 : lobby::ETeam::Team2;
    perUser.playerInfo.auid = userId_;
    perUser.playerInfo.heroEnergy = 100;
    perUser.playerInfo.avatarLevel = 5 + rand() % 10;
    perUser.playerInfo.heroLevel = 10 + rand() % 10;
    perUser.playerInfo.guardRating = 1200 + rand() % 500;
    perUser.playerInfo.playerRating = 1200 + rand() % 500;
    perUser.playerInfo.heroRating = 1200 + rand() % 500;
    perUser.playerInfo.hasPremium = true;
    //perUser.playerInfo.talentRollData.previousPremiumState = false;
    perUser.playerInfo.dropRate = 2.0f;
    perUser.playerInfo.basket = (NCore::EBasket::Enum)basket;
    perUser.playerInfo.fwod = true;
  }

  postGame.gameResult = lobby::EGameResult::SyncResults;
  postGame.victoriousFaction = ( rand() % 2 ) ? lobby::ETeam::Team1 : lobby::ETeam::Team2;
  postGame.users.resize( base );
  postGame.totalSeconds = 60 * 30;
  for ( int i = 0; i < postGame.users.size(); ++i )
  {
    roll::SPostGamePerUserData & perUser = postGame.users[i];
    perUser.clientId = preGame.users[i].clientId;
    perUser.scoring.score = 100 + rand() % 100;
    perUser.statistics.clientId = perUser.clientId;
    perUser.statistics.clientState = Peered::EGameFinishClientState::FinishedGame;
  }
  postGame.users[0].statistics.clientState = Peered::EGameFinishClientState::Disconnected;
}

} //namespace gtc
