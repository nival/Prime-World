#include "transport/stdafx.h"
#include "transport/TLChannelFactory.h"
#include "transport/TLChannel.h"
#include "transport/TLMulticastChannel.h"
#include "transport/TLConnection.h"
#include <naio/ConnectionContext.h>

namespace TransportLayer
{
  ChannelFactory::ChannelFactory()
  {}

  ChannelFactory::~ChannelFactory()
  {
  }

  IChannelInternalSP ChannelFactory::CreateChannel(Transport::EChannelType::Enum _channeltype, bool isactive, TL::ConnectionSP const & spconn, Transport::Address const & addr, 
    Transport::TLoginData const & logindata, Transport::MessageFactory* mf, unsigned int openChannelTimeout, unsigned int pingPeriod)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);

    if (Transport::EChannelType::Unicast == _channeltype)
    {
      StrongMT<Channel> spchnl = new TL::Channel(isactive, addr, logindata, mf);
      spchnl->setConnection_(spconn);
      spchnl->messageBlockFactory_(spconn->messageBlockFactory_());
      spchnl->setOpenTimeout_(openChannelTimeout);
      spchnl->setPingPeriod_(pingPeriod);

      spchnl->ChannelSuperBase::_SetStatus(EChannelStatus::CONNECTING);
      return static_cast<ChannelSuperBase*>(spchnl.Get());
    }
    else
    if (Transport::EChannelType::Multicast == _channeltype)
    {
      StrongMT<MulticastChannel> spchnl = new TL::MulticastChannel(isactive, addr, mf);
      spchnl->setConnection_(spconn);
      spchnl->messageBlockFactory_(spconn->messageBlockFactory_());
      spchnl->setOpenTimeout_(openChannelTimeout);
      spchnl->setPingPeriod_(pingPeriod);

      spchnl->ChannelSuperBase::_SetStatus(EChannelStatus::CONNECTING);

      return static_cast<ChannelSuperBase*>(spchnl.Get());
    }

    return 0;
  }

  void ChannelFactory::DestroyChannel(IChannelInternalSP const & spch)
  {
    NI_PROFILE_BLOCK(__FUNCTION__);
  }

}
