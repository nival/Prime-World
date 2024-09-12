#include "transport/stdafx.h"
#include "transport/TLTransportModule.h"
#include "transport/TLCfg.h"
#include <Network/AddressTranslator.h>
#include "transport/TLChannel.h"
#include "transport/TLChannelWrapper.h"
#include "transport/TLConnection.h"
#include "transport/TLChannelListener.h"
#include "transport/TLDefaultLogCallback.h"
#include "transport/TLMulticastChannel.h"
#include <Network/TransportMessages.h>

namespace TransportLayer
{


TransportModule::TransportModule() :
Transport::TransportSystemBase(),
initialized_(0),
bFiniNaio_(false)
{
}



TransportModule::~TransportModule()
{
  NI_PROFILE_FUNCTION;

  Fini();
}



bool TransportModule::Init( TL::Cfg const & cfg, naio::DriverSP const & spdrv )
{
  NI_PROFILE_FUNCTION;

  freePortsFinder = Network::NewFreePortsFinder( cfg.firstServerPort );

  if (initialized_ != 0)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] Already initialized")));
    return false;
  }

  //  init ace
  if (ACE::init() < 0)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] Can't initialize ACE framework")));
    return false;
  }

  bool res = true;
  //  init message factory
  if (!cfg.mf_)
    Transport::RegisterMessages(&msgFactory_);
  else
    msgFactory_ = *(cfg.mf_);

  MessageBlockFactorySP mbf;
  if (!cfg.mbHeapPerConnection_)
  {
    mbf = MessageBlockFactorySP(new TL::MessageBlockFactory(cfg.mbHeapName_.c_str(), cfg.mbHeapDumpFreq_));
    mbf->threshold(TL::MBType::NOTYPE_BLOCK, cfg.mbNotypeUseThreshold_);
    mbf->threshold(TL::MBType::WRITE_BLOCK, cfg.mbWriteUseThreshold_);
    mbf->threshold(TL::MBType::READ_BLOCK, cfg.mbReadUseThreshold_);
  }

  //  init protocol handler factory
  phFactory_.Init(&msgFactory_, &channelFactory_, mbf);

  //  init naio driver
  if (!spdrv.null())
  {
    spdrv_ = spdrv;
  }
  else
  {
    naio::Cfg ncfg((naio::Cfg&)cfg);
    if (!ncfg.phf_) 
      ncfg.phf_ = &phFactory_;

    spdrv_.reset(new naio::Driver());
    res = spdrv_->Init(ncfg);
    bFiniNaio_ = true;
  }

  //  init others
  if (res)
  {
    spConnMngr_.reset(new ConnectionManager(spdrv_, mbf));
    spConnMngr_->setWeakPtr(spConnMngr_);
    SetAddressTranslator( cfg.at_ );
  }

  ++initialized_;
  return res;
}



void TransportModule::Fini()
{
  NI_PROFILE_FUNCTION;

  if (initialized_ == 0)
  {
    ACE_ERROR((LM_ERROR, ACE_TEXT("[TL] Transport module not initialized yet or Fini() already was called")));
    return;
  }

  --initialized_;

  SetAddressTranslator( 0 );

  if (!spdrv_.null() && bFiniNaio_)
    spdrv_->Fini();

  spConnMngr_.reset();
  spdrv_.reset();
  ACE::fini();
}



Network::NetAddress TransportModule::AllocateServerAddress( const Network::NetAddress & _ip )
{
  int port = freePortsFinder->GetFreePort();
  return _ip + ":" + NStr::IntToStr( port );
}



StrongMT<Transport::IChannel> TransportModule::OpenChannelDirect( const Transport::Address& address, const Transport::TLoginData& loginData, 
                                                                  const Network::NetAddress& netAddress, unsigned int pingperiod, unsigned int to )
{
  NI_PROFILE_FUNCTION;

  if (netAddress.empty())
    return 0;

  ConnectionSP spconn = spConnMngr_->OpenConnection(netAddress);
  TL::IChannelInternalSP spchnl = channelFactory_.CreateChannel(Transport::EChannelType::Unicast, true, spconn, address, loginData, &msgFactory_, to, pingperiod);
  if (spconn != 0)
  {
    if (Connection::CONNECTED == spconn->status())
    { //  connection is already established

      int rc = spconn->startOpenChannel(spchnl);
      if (rc < 0)
      {
        ResetPtr(spchnl);
      }
    }
    else
    if (Connection::CONNECTING == spconn->status())
    {
      int rc = spconn->startOpenChannel(spchnl);
      if (rc < 0)
      {
        ResetPtr(spchnl);
      }
    }
    else
    { //  Connection::CLOSED
      ResetPtr(spchnl);
    }
  }
  else
  {
    ResetPtr(spchnl);
  }

  if (!TL::IsValid(spchnl))
    return 0;

  return new ChannelWrapper(spchnl);
}



StrongMT<Transport::IChannelListener> TransportModule::CreateChannelListenerDirect( Transport::TServiceId const & interfaceId, const nstl::string & listenAddress )
{
  NI_PROFILE_FUNCTION;

  ACE_INET_Addr listenAddr(listenAddress.c_str());
  if (listenAddress.empty())
    return 0;

  StrongMT<ChannelListener> spcl = new ChannelListener( interfaceId, listenAddr );

  AsynchCompletionPointer2<TL::ChannelListenerInternal, TL::ConnectionManager>* acp = new AsynchCompletionPointer2<TL::ChannelListenerInternal, TL::ConnectionManager>(spcl.Get(), spConnMngr_);

  spcl->acceptorHandle( spdrv_->OpenAcceptor( listenAddr, acp ) );

  if ( spcl->acceptorHandle().invalid() )
  {
    delete acp;
    return 0;
  }

  return spcl.Get();
}



bool TransportModule::ResolveAddress(Transport::TServiceId const & serviceid, ACE_INET_Addr & inetaddr)
{
  NI_PROFILE_FUNCTION;

  Transport::TServiceId svcid = GetAddressTranslator()->GetLastServiceInstance( serviceid );

  Network::NetAddress naddr = GetAddressTranslator()->GetSvcAddress( svcid );
  inetaddr = ACE_INET_Addr(naddr.c_str());
  return !naddr.empty();
}



StrongMT<Transport::IMulticastChannel> TransportModule::OpenMulticastChannel(Transport::Address const & _taddr, 
                                                              unsigned int _pingperiod, unsigned int _opentimeout)
{
  NI_PROFILE_FUNCTION;

  if (!GetAddressTranslator())
    return 0;

  Transport::Address taddr(_taddr);
  taddr.target = GetAddressTranslator()->GetLastServiceInstance(_taddr.target);

  Network::NetAddress naddr = GetAddressTranslator()->GetSvcAddress(taddr.target);

  return OpenMulticastChannelDirect(taddr, naddr, _pingperiod, _opentimeout);
}



StrongMT<Transport::IMulticastChannel> TransportModule::OpenMulticastChannelDirect(Transport::Address const & _taddr, Network::NetAddress const & _netaddr,
                                                                unsigned int _pingperiod, unsigned int _opentimeout)
{
  NI_PROFILE_FUNCTION;

  if (_netaddr.empty())
    return 0;

  ConnectionSP spconn = spConnMngr_->OpenConnection(_netaddr, _taddr.target);
  TL::IChannelInternalSP spchnl = channelFactory_.CreateChannel(Transport::EChannelType::Multicast, true, spconn, _taddr, "", &msgFactory_, _opentimeout, _pingperiod);
  if (spconn != 0)
  {
    if (Connection::CONNECTED == spconn->status())
    { //  connection is already established

      int rc = spconn->startOpenChannel(spchnl);
      if (rc < 0)
      {
        ResetPtr(spchnl);
      }
    }
    else
    if (Connection::CONNECTING == spconn->status())
    {
      int rc = spconn->startOpenChannel(spchnl);
      if (rc < 0)
      {
        ResetPtr(spchnl);
      }
    }
    else
    { //  Connection::CLOSED
      ResetPtr(spchnl);
    }
  }
  else
  {
    ResetPtr(spchnl);
  }

  if (!TL::IsValid(spchnl))
    return 0;

  MulticastChannel* realchnl = static_cast<MulticastChannel*>(spchnl.Get());
  return static_cast<Transport::IMulticastChannel*>(realchnl);
}



StrongMT<TL::TransportModule> CreateTransportSystem(TL::Cfg const & cfg)
{
  NI_PROFILE_FUNCTION;

  StrongMT<TL::TransportModule> tm(new TransportModule);

  TL::Cfg cfg_(cfg);
  if (cfg.spLogMsgCb_.null())
    cfg_.spLogMsgCb_.reset(new TransportLayer::LogCallback(::GetSystemLog()));

  if (!tm->Init(cfg_, naio::DriverSP()))
  {
    return StrongMT<TL::TransportModule>();
  }
  return tm;
}



StrongMT<Transport::IChannelListener> TransportModule::GetDefaultChannelListener() const
{
  ChannelListener* cl = static_cast<ChannelListener*>(spConnMngr_->defaultChannelListener().Get());
  return cl;
}

}


NI_DEFINE_REFCOUNT( TransportLayer::TransportModule );