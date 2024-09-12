#include "stdafx.h"
#include "Network/stdafx.h"
#include "System/ThreadHelpers.h"
#include "Network/AddressTranslator.h"
#include "Network/Message.h"
#include "Network/TransportMessages.h"
#include "RelayServer2.h"
#include "RelayClientsVerifier.h"
#include "RelayServer2Cfg.h"

using namespace threading;

namespace Relay
{

RelayServer2::RelayServer2( const Transport::ServiceParams & _svcParams, const Transport::CustomServiceParams & _customParams,
Transport::TServiceId const & _frontendSvcid, Transport::TServiceId const & _backendSvcid ) :
Transport::BaseService( _svcParams, _customParams ),
frontendSvcid( _frontendSvcid ),
backendSvcid( _backendSvcid )
{
  RegisterMessages( &factory );

  frontendListenAddr = CoordClient()->GetFrontendAddressTranslator()->GetSvcAddress( SvcId() );
  backendListenAddr = CoordClient()->GetBackendAddressTranslator()->GetSvcAddress( backendSvcid );

  MessageTrace( "Starting relay server. front_listen_addr=%s, back_listen_addr=%s", frontendListenAddr, backendListenAddr );

  int idx = Transport::GetServerIndex(backendSvcid);
  nstl::string logFilePostfix = "relay_";
  logFilePostfix += NStr::IntToStr(idx);

  logStream = new NLogg::CChannelLogger( logFilePostfix.c_str() );
  logDumper = NLogg::BasicTextFileDumper::New( logStream, logFilePostfix.c_str() );

  logcb = new LogCallback( *logStream );

  verifier = new Relay::ClientsVerifier( backendSvcid, RelayServer2Cfg::Get2NewConnectionTimeout(), BackendGk(), this );
}



RelayServer2::~RelayServer2() 
{
  if ( logcb )
    delete logcb;

  if ( logDumper )
    delete logDumper;

  if ( logStream )
    delete logStream;
}

} //namespace Relay
