#ifndef BATTLESERVERRUNNER_H_A9059566_43
#define BATTLESERVERRUNNER_H_A9059566_43

#include <Network/Transport.h>
#include <ServerAppBase/ServerFactory.h>

#include "BattleServer.h"
#include "Protocol.h"
#include "System/HPTimer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Battle
{

class BattleServerRunner : public Transport::IServerRunner, public CObjectBase
{
  OBJECT_BASIC_METHODS( BattleServerRunner )
public:
  BattleServerRunner() : thisThread(0)
  {

  }

  virtual ~BattleServerRunner()
  {
    StopInstance( Transport::TServiceId() );
  }

  virtual void SetInterfacePolicies( Coordinator::ICoordinatorServer* _coordinator ) 
  {
    _coordinator->SetServicePolicy( Protocol::battleServerId, Coordinator::SInterfacePolicy( Coordinator::SInterfacePolicy::SINGLE ) );
  }

  virtual const vector<Transport::TServiceId>& GetInterfaces() const
  {
    static vector<Transport::TServiceId> interfaces( 1, Protocol::battleServerId );
    return interfaces;
  }
  virtual void StartInstance( const Transport::TServiceId& serviceId, Transport::ITransportSystem* transport, Coordinator::ICoordinatorClient* _coordClient )
  {
    server = new BattleServer( transport, serviceId );
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
    threading::SetDebugThreadName( "Battle Server" );

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
  CObj<BattleServer> server;

  typedef threading::ProcessingThread<BattleServerRunner> ServerThread;
  ServerThread* thisThread;
};

} // namespace Location

#endif //#define BATTLESERVERRUNNER_H_A9059566_43