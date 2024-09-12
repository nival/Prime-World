#ifndef AISERVERRUNNER_H_A9059566_43
#define AISERVERRUNNER_H_A9059566_43

#include <Network/Transport.h>
#include <ServerAppBase/ServerFactory.h>

#include "AIServer.h"
#include "../SimpleGame/Protocol.h"
#include "System/HPTimer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace AI
{

class AIServerRunner : public Transport::IServerRunner, public CObjectBase
{
  OBJECT_BASIC_METHODS( AIServerRunner )
public:
  AIServerRunner() : thisThread(0)
  {

  }

  virtual ~AIServerRunner()
  {
    StopInstance( Transport::TServiceId() );
  }

  virtual int GetStartSequence() const { return 3; }

  virtual void SetInterfacePolicies( Coordinator::ICoordinatorServer* _coordinator ) 
  {
    vector<Transport::TServiceId> dependencies( 1, Protocol::locationServerId );
    _coordinator->SetServicePolicy( AI::aiServerId, Coordinator::SInterfacePolicy( Coordinator::SInterfacePolicy::SINGLE, dependencies ) );
  }

  virtual const vector<Transport::TServiceId>& GetInterfaces() const
  {
    static vector<Transport::TServiceId> interfaces( 1, AI::aiServerId );
    return interfaces;
  }
  virtual void StartInstance( const Transport::TServiceId& serviceId, Transport::ITransportSystem* transport, Coordinator::ICoordinatorClient* _coordClient )
  {
    server = new AIServer( transport, serviceId );
    thisThread = new ServerThread( *this );
  }
  virtual void StopInstance( const Transport::TServiceId& serviceId )
  {
    if ( thisThread )
      thisThread->Stop( true, 1000 );

    delete thisThread;    
    server = 0;
  }

  int Process( const bool& isRunning )
  {
    threading::SetDebugThreadName( "AI Server" );

    while ( isRunning )
    {
      NHPTimer::STime frameStartTime;
      NHPTimer::GetTime( frameStartTime );

      server->Step( Protocol::LOGIC_FRAME_TIME_SEC, frameStartTime );

      NHPTimer::STime frameEndTime; 
      NHPTimer::GetTime( frameEndTime );

      int frameMs = NHPTimer::Time2Seconds( frameEndTime - frameStartTime ) * 1000.0;

      if ( frameMs > ( Protocol::LOGIC_FRAME_TIME_MSEC ) )
      {
        systemLog( NLogg::LEVEL_MESSAGE ) << "Overload" << endl;
      }

      Sleep( Max( Protocol::LOGIC_FRAME_TIME_MSEC - frameMs, 0 ) );
    }

    return 0;
  }

private:
  CObj<AIServer> server;

  typedef threading::ProcessingThread<AIServerRunner> ServerThread;
  ServerThread* thisThread;
};

} // namespace AI

#endif //#define AISERVERRUNNER_H_A9059566_43