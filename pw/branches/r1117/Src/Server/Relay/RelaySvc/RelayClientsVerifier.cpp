#include "stdafx.h"
#include "RelayClientsVerifier.h"
#include "RelaySvc/RelaySvcNaming.h"
#include "RelayBalancer/RRelayBalancerClientNotifyIface.auto.h"
#include "rpc/GateKeeper.h"

namespace Relay
{

ClientsVerifier::ClientsVerifier( const Transport::TServiceId& _relayService, Timestamp _timeout, rpc::GateKeeper * _gk, Transport::IPerfCounters * _perCounters) :
relayService( _relayService ),
timeout( _timeout ),
gk(_gk),
perCounters( _perCounters ),
userCount_(0)
{
  gk->GetGate()->RegisterObject<Relay::IIncomingClientNotifySink>(this, Relay::IncomingClientNotifierRpcIface);
}



ClientsVerifier::~ClientsVerifier()
{
}



bool ClientsVerifier::VerifyNewClientConnected( Transport::TClientId userId, const Transport::TLoginData& loginData )
{
  bool found = false;
  {
    threading::MutexLock lock( usersTimeoutTimeLock );
    TUserToTime::iterator it = usersTimeoutTime.find( userId );
    found = ( it != usersTimeoutTime.end() );
    if ( found )
      usersTimeoutTime.erase( it );
  }
  if (!found)
  {
    WarningTrace("User connecting to wrong relay(u=%d)", userId);
    return false;
  }

  NI_ASSERT(outgoingClientsNotify->GetStatus() == rpc::Connected, "" );
  outgoingClientsNotify->ClientConnectedNotify(userId);

  if ( StrongMT<Transport::IPerfCounters> locked = perCounters.Lock() )
    locked->AutoPerfCounterRate( "users_inc_relay", 1 );

  MessageTrace("User successfully connected to relay(u=%d)", userId);
  return true;
}



void ClientsVerifier::NotifyClientDisconnected( Transport::TClientId userId )
{
  MessageTrace("User disconnected from relay(u=%d)", userId);

  if ( StrongMT<Transport::IPerfCounters> locked = perCounters.Lock() )
    locked->AutoPerfCounterRate( "users_out_relay", 1 );

  if (outgoingClientsNotify)
    OutgoingClientNotify(userId, OutgoingClientReason::Disconnect);
  else
    ErrorTrace("%s: can't notify about outgoing user. Interface is NULL(u=%d)", userId);
}



void ClientsVerifier::Step()
{
  if ( 0 == timeout )
    return;

  Timestamp time = NHPTimer::GetScalarTime();

  {
    threading::MutexLock lock( usersTimeoutTimeLock );
    for ( TUserToTime::iterator it = usersTimeoutTime.begin(); it != usersTimeoutTime.end(); )
    {
      if ( it->second < time )
      {
        systemLog(NLogg::LEVEL_MESSAGE).Trace("User hasn't connected to relay after login(u=%d to=%0.3f)", it->first, timeout);

        if (outgoingClientsNotify)
          OutgoingClientNotify(it->first, OutgoingClientReason::ConnectTimeoutExpired);
        else
          systemLog(NLogg::LEVEL_MESSAGE).Trace("outgoingClientsNotify callback is NULL(u=%d to=%0.3f)", it->first, timeout);

        it = usersTimeoutTime.erase( it );
      }
      else 
        ++it;
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ClientsVerifier::RegisterOutgoingClientNotifySink(Relay::IOutgoingClientNotifySink* notifySink)
{
  LOG_M(0).Trace( "%s", __FUNCTION__ );

  Relay::RIOutgoingClientNotifySink * casted = dynamic_cast<Relay::RIOutgoingClientNotifySink *>( notifySink );
  NI_ASSERT( casted, "" );

  outgoingClientsNotify.Set( casted );
  return ccu();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ClientsVerifier::IncomingClientNotify( Transport::TClientId clientid, string const & sessionkey)
{
  Timestamp time = NHPTimer::GetScalarTime() + timeout; 

  threading::MutexLock lock( usersTimeoutTimeLock );
  nstl::pair<TUserToTime::iterator, bool> res = usersTimeoutTime.insert(nstl::make_pair(clientid, time));
  if (!res.second)
  {
    LOG_E(0).Trace("User already waited(u=%d expiration_time=%0.3f suppose_time=%0.3f)", clientid, res.first->second, time);
  }
  else
  {
    inccu();
    LOG_M(0).Trace("Waiting for user on relay(u=%d to=%0.3f)", clientid, timeout);
  }

  return res.second;
}

void ClientsVerifier::OutgoingClientNotify(Transport::TClientId const & _userid, OutgoingClientReason::Enum _reason)
{
  deccu();

  NI_ASSERT(outgoingClientsNotify->GetStatus() == rpc::Connected, "" );
  outgoingClientsNotify->OutgoingClientNotify(_userid, _reason);
}

}
