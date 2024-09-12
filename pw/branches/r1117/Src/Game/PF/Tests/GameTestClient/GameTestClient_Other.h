#pragma once

#include "GameTestClient_GS.h"
#include "ReplayCmdFeeder.h"
//#include "Server/Chat/ChatClient.h"


namespace gtc
{

class Client_Login : public TestClientBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( Client_Login, TestClientBase );

public:
  Client_Login( const TestClientBaseParams & _params ) :
  TestClientBase( _params ),
  timeLoginFinished_( 0 )
  {}

private:
  Timestamp timeLoginFinished_;

  virtual StepResult MainStep();
};




class Client_Replay : public Client_GS
{
  NI_DECLARE_REFCOUNT_CLASS_1( Client_Replay, Client_GS );

public:
  Client_Replay( const TestClientBaseParams & _params ) :
  Client_GS( _params ),
  timePlaySessionStarted( 0 )
  {}

  bool LoadReplay( const char * replayFileName, int replayClientId_ );

private:
  ReplayCommandFeeder replay;
  Timestamp           timePlaySessionStarted;

  virtual StepResult MainStep();
};

} //namespace gtc
