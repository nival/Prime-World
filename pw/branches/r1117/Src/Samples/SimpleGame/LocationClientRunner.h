#ifndef LOCATIONCLIENTRUNNER_H_23C161E2
#define LOCATIONCLIENTRUNNER_H_23C161E2

#include "LocationClient.h"
#include "Protocol.h"
#include "System/HPTimer.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace Location
{

class LocationClientRunner
{
public:
  LocationClientRunner() : prevTime(0) {}

  void Set( Transport::ClientTransportSystem* _transport )
  {
    clientTransportSystem = _transport;
  }

  int Process( const bool& isRunning )
  {
    threading::SetDebugThreadName( "Location Client" );

    client = new LocationClient( clientTransportSystem );

    if ( !client->Init() )
      return 0;

    while ( isRunning )
    {
      Protocol::AbsoluteTime currTime = NHPTimer::GetScalarTime();
      Protocol::Time deltaTime = prevTime ? ( currTime - prevTime ) : 0;
      prevTime = currTime;

      client->Step( deltaTime, currTime );

      Sleep( 5 );
    }

    client = 0;

    return 0;
  }

  LocationClient* GetClient() { return client; }

private:
  CObj<Transport::ClientTransportSystem> clientTransportSystem;
  CObj<LocationClient> client;

  Protocol::AbsoluteTime prevTime;
};

} // namespace Location

#endif //#define LOCATIONCLIENTRUNNER_H_23C161E2