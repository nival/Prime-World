#ifndef LOCATIONSERVERRUNNER_H_E380F82C
#define LOCATIONSERVERRUNNER_H_E380F82C

#include <Network/Transport.h>
#include <ServerAppBase/ServerFactory.h>

#include "LocationServer.h"
#include "Protocol.h"
#include "System/HPTimer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Location
{

class LocationServerRunner : public Transport::IServerRunner, public CObjectBase
{
  OBJECT_BASIC_METHODS( LocationServerRunner )
public:
  LocationServerRunner() : thisThread(0)
  {

  }

  virtual ~LocationServerRunner()
  {
    StopInstance( Transport::TServiceId() );
  }

  virtual void SetInterfacePolicies( Coordinator::ICoordinatorServer* _coordinator ) 
  {
    vector<Transport::TServiceId> dependencies( 1, Protocol::battleServerId );
    _coordinator->SetServicePolicy( Protocol::locationServerId, Coordinator::SInterfacePolicy( Coordinator::SInterfacePolicy::SINGLE, dependencies ) );
  }

  virtual const vector<Transport::TServiceId>& GetInterfaces() const
  {
    static vector<Transport::TServiceId> interfaces( 1, Protocol::locationServerId );
    return interfaces;
  }
  virtual void StartInstance( const Transport::TServiceId& serviceId, Transport::ITransportSystem* transport, Coordinator::ICoordinatorClient* _coordClient )
  {
    server = new LocationServer( transport, serviceId );
    thisThread = new ServerThread( *this );
  }

  virtual void StopInstance( const Transport::TServiceId& serviceId )
  {
    thisThread = 0;
    server = 0;
  }

  int Process( const bool& isRunning )
  {
    threading::SetDebugThreadName( "Location Server" );

    if ( !server->Init() )
      return 0;

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
  CObj<LocationServer> server;

  typedef threading::ProcessingThread<LocationServerRunner> ServerThread;
  ServerThread* thisThread;
};

} // namespace Location

#endif //#define LOCATIONSERVERRUNNER_H_E380F82C