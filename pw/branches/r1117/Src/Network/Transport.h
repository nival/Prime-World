#pragma once
#include "Network.h"
#include "TransportLoginData.h"
#include "TransportAddress.h"
#include "TransportDefaults.h"
#include "TransportError.h"
#include "TransportMulticastChannel.h"

namespace Transport
{

struct MessageBase;
class IAddressTranslator;


struct MessageMiscInfo
{
  NHPTimer::STime   queueAbsTime; //TODO: convert into timer::Time
  timer::Time       recvAbsTime;

  MessageMiscInfo() :
  queueAbsTime( 0 ),
  recvAbsTime( 0 )
  {}
};


struct IChannel : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IChannel, IBaseInterfaceMT )

  virtual Network::ConnectionState::Enum GetStatus() const = 0;
  virtual void Close() = 0;

  virtual const Address& GetAddress() const = 0;
  virtual const TLoginData& GetLoginData() const = 0;
  virtual TClientId GetInternalClientId() const = 0;
  virtual bool IsIncomingConnection() const = 0;

  virtual void SendMsg( MessageBase* pMessage ) = 0;
  virtual MessageBase* ReceiveMsg() = 0;
  virtual MessageBase* PeekMsg() = 0;

  virtual void SendRaw( const byte* data, int size ) = 0;
  virtual bool ReceiveRaw( vector<byte>* data ) = 0;
  virtual bool ReceiveRaw( vector<byte>* data, MessageMiscInfo & _miscInfo ) { return false; };
  virtual bool PeekRaw( vector<byte>* data ) = 0;

  virtual Ping GetPingTime() const = 0;

  virtual void KeepAlivePeriod(unsigned int sec) {};

  virtual void FillDebugString( string & _outStr ) = 0;

  template<class TMessage>
  TMessage* ReceiveCast();
};



template<class TMessage>
TMessage* IChannel::ReceiveCast()
{
  MessageBase* pMsg = ReceiveMsg();
  if ( !pMsg )
    return 0;
  TMessage* pCasted = dynamic_cast<TMessage*>( pMsg );
  if ( !pCasted )
    return 0;
  return pCasted;
}



typedef vector<StrongMT<Transport::IChannel> > TChannels;

_interface IChannelListener: public IBaseInterfaceMT 
{
  NI_DECLARE_CLASS_1( IChannelListener, IBaseInterfaceMT )

  virtual const TServiceId& GetServiceId() const = 0; 
  virtual void GetNewConnections( TChannels* pConnections ) = 0;
};



class IFrontendTransportKickCallback : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IFrontendTransportKickCallback, IBaseInterfaceMT )

public:
  virtual void KickUser( TClientId _uid ) = 0;
};



class IFrontendTransportAuth : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IFrontendTransportAuth, IBaseInterfaceMT )

public:
  virtual bool AuthorizeUser( TClientId _uid, const string & _key, IFrontendTransportKickCallback * _cb ) = 0;
};



class ITransportSystem : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ITransportSystem, IBaseInterfaceMT )

  virtual IAddressTranslator* GetAddressTranslator() const = 0;

  virtual Network::NetAddress AllocateServerAddress( const Network::NetAddress & _ip ) = 0;

  virtual StrongMT<IChannel> OpenChannel( const Address& address, const TLoginData& loginData, 
                                          unsigned int pingperiod = Defaults::GetPingPeriod(),
                                          unsigned int to = Defaults::GetOpenChannelTimeout() ) = 0;

  virtual StrongMT<IChannelListener> CreateChannelListener( TServiceId interfaceId ) = 0;

  virtual StrongMT<IChannel> OpenChannelDirect( const Address& address, const TLoginData& loginData, 
    const Network::NetAddress& netAddress, 
    unsigned int pingperiod = Defaults::GetPingPeriod(),
    unsigned int to = Defaults::GetOpenChannelTimeout() ) = 0;

  virtual StrongMT<IChannelListener> CreateChannelListenerDirect( TServiceId const & interfaceId, const string & listenAddress ) = 0;


  virtual StrongMT<IMulticastChannel> OpenMulticastChannel(Address const & _taddr, 
    unsigned int _pingperiod = Defaults::GetPingPeriod(),
    unsigned int _opentimeout = Defaults::GetOpenChannelTimeout()) { return 0; }

  virtual StrongMT<IMulticastChannel> OpenMulticastChannelDirect(Address const & _taddr, Network::NetAddress const & _netaddr,
    unsigned int _pingperiod = Defaults::GetPingPeriod(),
    unsigned int _opentimeout = Defaults::GetOpenChannelTimeout()) { return 0; }

  //UGLY method, used only on client and only in 'multicast' mode
  virtual StrongMT<IChannelListener> GetDefaultChannelListener() const { return 0; };

  virtual void AddFrontendAuth( const TServiceId & interfaceId, IFrontendTransportAuth * _auth ) = 0;
};

} //namespace Transport
