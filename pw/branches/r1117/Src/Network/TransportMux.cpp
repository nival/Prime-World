#include "stdafx.h"
#include "Transport.h"
#include "TransportMux.h"
#include "TransportChannel.h"
#include "System/LogStreamBuffer.h"
#include "System/get_tick_count.h"
#include "System/Thread.h"

namespace Transport
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConnectionMux::Init( MessageFactory* _factory, Network::IConnection* _pConn, bool _canAcceptNewConnections, 
                         TClientId* _nextAutoAssignId, Network::IStreamAllocator* _pAlloc )
{
  localAutoAssignId = firstAutoAssignId;
  if  ( _nextAutoAssignId )
    nextAutoAssignId = _nextAutoAssignId;
  else
    nextAutoAssignId = &localAutoAssignId;

  factory = _factory;
  pConn = _pConn;
  prevNetStatus = Network::ConnectionState::Initialized;
  state = S_CONNECTING;
  canAcceptNewConnections = _canAcceptNewConnections;

  pAlloc = _pAlloc;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConnectionMux::SetAddressPacking( bool _packAddress, TClientId _packedUserId )
{
  packAddress = _packAddress;
  packedUserId = _packedUserId;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ConnectionMux::~ConnectionMux()
{
  if ( pConn )
    pConn->AsyncClose();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
StrongMT<IChannel> ConnectionMux::OpenChannel( const Address& address, const TLoginData& loginData )
{
  {  //TODO SE: Remove this block together with clientConnectionsByAddress map if not nessesary
    if ( address.client != autoAssignClientId )
    {
      threading::MutexLock lock( clientConnectionsMutex );
      TClientByAddressMap::iterator itConn = clientConnectionsByAddress.find( address );
      NI_VERIFY( itConn == clientConnectionsByAddress.end() || itConn->second->GetStatus() == Network::ConnectionState::Closed
        , (string("Trying to open channel duplicate for address ") + AddressToString( address )).c_str()
        , return itConn->second );
    }
  }

  ClientIdGenerator& idGen = clientIdGenerator[ address.client ];
  int pipeId =  idGen.GeneratePipeForInterface( address.target );
  NI_VERIFY( pipeId != EKnownPipeId::Invalid , "ConnectionMux Out of pipeIds!", return 0 );

  ChannelAddr localChAddr( pipeId, address.client, address.sender );

  StrongMT<Channel> pCConn = new Channel( false, address, loginData, factory, pAlloc, packAddress );
  pCConn->SetStatus( pConn->GetStatus() == Network::ConnectionState::Closed ? Network::ConnectionState::Closed : Network::ConnectionState::Connecting );

  OpenChannelRequest msg;
  msg.clientAddress = address;
  msg.loginData = loginData;
  msg.localPipeId = localChAddr.pipe;
  SendInt( ChannelAddr( EKnownPipeId::NetLogic, address.client, address.sender ), &msg );

  threading::MutexLock lock( clientConnectionsMutex );
  clientConnections[localChAddr] = pCConn;
  clientConnectionsByAddress[address] = pCConn;

  return pCConn.Get();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConnectionMux::CheckNetStatus()
{
  Network::ConnectionState::Enum netStatus = pConn->GetStatus();

  if ( netStatus == prevNetStatus )
    return;

  if ( netStatus == Network::ConnectionState::Connected && state == S_CONNECTING )
  {
    state = S_CONNECTED;
  }
  else if ( netStatus == Network::ConnectionState::Closed )
  {
    state = S_CLOSED;
    TClientMap::iterator it = clientConnections.begin(), itEnd = clientConnections.end(); 
    for ( ;it != itEnd ; ++it )
    {
      (*it).second->SetStatus( netStatus );
    }

    if ( netStatus == Network::ConnectionState::Closed )
      clientConnections.clear();
  }

  prevNetStatus = netStatus;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConnectionMux::CloseConnection( TClientMap::iterator it )
{
  StrongMT<Channel> pCConn = it->second;
  const Address& addr = pCConn->GetAddress();

  if ( !pCConn->IsClosedRemotely() )
  {
    CloseChannelMessage msg;
    msg.clientAddress = pCConn->GetChannelAddr();

    SendInt( ChannelAddr( EKnownPipeId::NetLogic, (*it).first.client ), &msg );

    systemLog( NLogg::LEVEL_MESSAGE ) << "ConnectionMux Closing channel " << AddressToString( addr ) << endl;
  }
  else
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "ConnectionMux Closing channel " << AddressToString( addr ) << " by remote request " << endl;
  }

  clientConnectionsByAddress.erase( addr );
  clientConnections.erase( it );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConnectionMux::Receive()
{
  while( CObj<Stream> pS = pConn->Receive() )
  {
    ChannelAddr chAddr;
    chAddr.client = packedUserId;
    {
      ReadAddress( pS, chAddr );
      pS->Seek( 0, SEEKORIGIN_BEGIN );
    }

    if( chAddr.pipe == EKnownPipeId::NetLogic )
    {
      MessageBase* pMsg = 0;
      UnpackNetMessage( pS, factory, chAddr, &pMsg );

      NetLogicMessage* pNLMsg = dynamic_cast<NetLogicMessage*>( pMsg );
      if( pNLMsg )
      {
        ProcessReceivedNetMessage( pNLMsg, chAddr );

        //systemLog(NLogg::LEVEL_MESSAGE) << "transport: netlogic: recv message (msg=" << pMsg->GetTypeId()
        //  << " userid=" << packedUserId
        //  << " tid=" << threading::CurrentThreadID()
        //  << ")" << endl;
      }
      else
      {
        systemLog(NLogg::LEVEL_ASSERT) 
          << "ConnectionMux transport: netlogic: recv message (userid=" << packedUserId 
          << " tid=" << threading::CurrentThreadID()
          << ")" << endl;
      }

      delete pMsg;
      pConn->ReleaseReceived( pS );
    }
    else
    {
      TClientMap::iterator it = clientConnections.find( chAddr );
      if ( it == clientConnections.end() )
      {
        systemLog(NLogg::LEVEL_ASSERT) 
          << "ConnectionMux transport: recv packet with unknown address ("
          << " userid=" << packedUserId
          << " pipe=" << chAddr.pipe
          << " tid=" << threading::CurrentThreadID()
          << ")" << endl;
        //NI_ALWAYS_ASSERT( NI_STRFMT( "Received packet with unknown address %d:%d", chAddr.pipe, chAddr.client ) );

        pConn->ReleaseReceived( pS );
        continue;
      }

      (*it).second->AddReceivedMsg( pS );
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConnectionMux::ProcessReceivedNetMessage( NetLogicMessage* pNLMsg, ChannelAddr &addr )
{
  if ( pNLMsg->GetType() == ENetLogicMessage::OpenChannelReq )
  {
    OpenChannelRequest* pCastedMsg = static_cast<OpenChannelRequest*>( pNLMsg );

    OpenChannelResponse msg;
    Address clientAddr = pCastedMsg->clientAddress;

    systemLog(NLogg::LEVEL_DEBUG).Trace("ConnectionMux New channel request received(c=%d t=%s s=%s sndr=%d)",
      clientAddr.client, clientAddr.target.c_str(), clientAddr.source.c_str(), clientAddr.sender);

    ClientIdGenerator& idGen = clientIdGenerator[ clientAddr.client ];
    NI_VERIFY( idGen.HasFreeID(), "ConnectionMux Out of  pipeIds!", return );
    ChannelAddr localChAddr( idGen.GeneratePipeForInterface( clientAddr.target ), clientAddr.client, clientAddr.sender );

    if ( localChAddr.client == autoAssignClientId )
      localChAddr.client = (*nextAutoAssignId)++;

    msg.clientAddress = clientAddr;
    msg.remoteAddr = localChAddr;
    msg.localPipeId = pCastedMsg->localPipeId;
    msg.success = canAcceptNewConnections; //TODO: verification

    SendInt( ChannelAddr( EKnownPipeId::NetLogic, pCastedMsg->clientAddress.client, pCastedMsg->clientAddress.sender ), &msg );

    if ( msg.success )
    {
      swap( clientAddr.source, clientAddr.target );
      //if( localChAddr.pipe == EKnownPipeId::Client )
      //  swap( clientAddr.client, clientAddr.sender );

      StrongMT<Channel> pCConn = new Channel( true, clientAddr, pCastedMsg->loginData, factory, pAlloc, packAddress );
      pCConn->InitAdresses( ChannelAddr( pCastedMsg->localPipeId, localChAddr.client, localChAddr.sender ), clientAddr );

      pCConn->SetStatus( pConn->GetStatus() );
      clientConnections[ localChAddr ] = pCConn;
      clientConnectionsByAddress[ clientAddr ] = pCConn;

      systemLog(NLogg::LEVEL_DEBUG).Trace("ConnectionMux New channel request accepted(c=%d t=%s s=%s sndr=%d)",
        clientAddr.client, clientAddr.target.c_str(), clientAddr.source.c_str(), clientAddr.sender);
    }
    else
    {
      systemLog(NLogg::LEVEL_WARNING).Trace("ConnectionMux New channel request REFUSED(c=%d t=%s s=%s sndr=%d)",
        clientAddr.client, clientAddr.target.c_str(), clientAddr.source.c_str(), clientAddr.sender);
    }

  }
  else if ( pNLMsg->GetType() == ENetLogicMessage::CloseChannel )
  {
    CloseChannelMessage* pCastedMsg = static_cast<CloseChannelMessage*>( pNLMsg );

    systemLog(NLogg::LEVEL_DEBUG).Trace("ConnectionMux Close channel request received(c=%d p=%d s=%d)",
      pCastedMsg->clientAddress.client, pCastedMsg->clientAddress.pipe, pCastedMsg->clientAddress.sender);

    TClientMap::iterator it = clientConnections.find( pCastedMsg->clientAddress );
    if ( it != clientConnections.end() )
    {
      (*it).second->CloseRemotely();
    }
    else
    {
      systemLog(NLogg::LEVEL_WARNING).Trace("ConnectionMux Received close channel command with unknown address(c=%d p=%d s=%d)",
        pCastedMsg->clientAddress.client, pCastedMsg->clientAddress.pipe, pCastedMsg->clientAddress.sender);
    }
  }
  else if ( pNLMsg->GetType() == ENetLogicMessage::OpenChannelResp )
  {
    OpenChannelResponse* pCastedMsg = static_cast<OpenChannelResponse*>( pNLMsg );

    ChannelAddr oldChannelAddr( pCastedMsg->localPipeId, pCastedMsg->clientAddress.client, pCastedMsg->clientAddress.sender );

    systemLog(NLogg::LEVEL_DEBUG).Trace("ConnectionMux New channel response received(res=%d c=%d t=%s s=%s lp=%d rp=%d)",
      pCastedMsg->success, pCastedMsg->clientAddress.client, pCastedMsg->clientAddress.target.c_str(),
      pCastedMsg->clientAddress.source.c_str(), pCastedMsg->localPipeId, pCastedMsg->remoteAddr.pipe);

    TClientMap::iterator it = clientConnections.find( oldChannelAddr );
    if( it != clientConnections.end() )
    {
      StrongMT<Channel> pCConn = it->second;
      Address oldAddr = pCConn->GetAddress(); 
      Address newAddr( oldAddr.target, pCastedMsg->clientAddress.client, pCastedMsg->clientAddress.sender );

      pCConn->InitAdresses( pCastedMsg->remoteAddr, pCastedMsg->clientAddress );
      if ( pCConn->GetStatus() != Network::ConnectionState::Closed  )
        pCConn->SetStatus( pCastedMsg->success ? Network::ConnectionState::Connected : Network::ConnectionState::Closed );

      if( pCastedMsg->clientAddress.client == autoAssignClientId )
      {
        clientConnections.erase( it );
        clientConnections[ ChannelAddr( pCastedMsg->localPipeId, pCastedMsg->remoteAddr.client, pCastedMsg->remoteAddr.sender ) ] = pCConn;
        clientConnectionsByAddress.erase( oldAddr );
        clientConnectionsByAddress[ newAddr ] = pCConn;
      }
    }
    else 
    {
      //valid situation - channel was closed before NewConnectionResult message arrrives
    }
  }
  else if ( pNLMsg->GetType() == ENetLogicMessage::PingMessage )
  {
    PingMessage* pCastedMsg = static_cast<PingMessage*>( pNLMsg );
    if ( !pCastedMsg->reply )
    {
      TClientMap::iterator it = clientConnections.find( pCastedMsg->requestingChannel );
      if ( it != clientConnections.end() )
      {
        pCastedMsg->requestingChannel.pipe = it->second->GetChannelAddr().pipe;
        pCastedMsg->reply = true;
        SendInt( ChannelAddr( EKnownPipeId::NetLogic, addr.client, addr.sender ), pCastedMsg );
      }
    }
    else
    {
      TClientMap::iterator it = clientConnections.find( pCastedMsg->requestingChannel );
      if( it != clientConnections.end() )
      {
        int pingTime = nival::get_tick_count() - pCastedMsg->sendTime;
        it->second->UpdatePingTime( pingTime );
      }
    }
  }

}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConnectionMux::Send()
{
  TClientMap::iterator it = clientConnections.begin(), itEnd = clientConnections.end(); 
  for ( ; it != itEnd; ++it )
  {
    if ( it->second->GetStatus() == Network::ConnectionState::Connecting )
      continue;

    if ( it->second->NeedCheckPing() )
    {
      PingMessage msg;
      msg.requestingChannel = it->second->GetChannelAddr();
      msg.sendTime = nival::get_tick_count();

      SendInt( ChannelAddr( EKnownPipeId::NetLogic, msg.requestingChannel.client ), &msg );
    }

    while( CObj<Stream> pMsg = (*it).second->GetMsgToSend() )
    {
      pConn->Send( pMsg );
    }
  }

  it = clientConnections.begin(); 
  for ( ; it != clientConnections.end(); )
  {
    if ( (*it).second->GetStatus() == Network::ConnectionState::Closed )
    {
      TClientMap::iterator itOld = it;
      ++it;
      CloseConnection( itOld );
    }
    else if ( (*it).second->IsClosePending() )
    {
      if ( (*it).second->GetChannelAddr().pipe != EKnownPipeId::Invalid )
        (*it).second->Close();
      ++it;
    }
    else
      ++it;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ConnectionMux::Step()
{
  threading::MutexLock lock( clientConnectionsMutex);
  CheckNetStatus();
  Send();
  Receive();
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ConnectionMux::HasNetConnection() const
{
  return prevNetStatus != Network::ConnectionState::Closed;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
