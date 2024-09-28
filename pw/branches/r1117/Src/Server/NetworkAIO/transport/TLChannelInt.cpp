#include "transport/stdafx.h"
#include "transport/TLChannelInt.h"

namespace TransportLayer
{

NI_ENUM_BEGIN_STD(EChannelStatus);
NI_ENUM_ITEM( INVALID );
NI_ENUM_ITEM( INIT );
NI_ENUM_ITEM( CLOSING );
NI_ENUM_ITEM( CLOSED );
NI_ENUM_ITEM( CONNECTED );
NI_ENUM_ITEM( CONNECTING );
NI_ENUM_END_STD;

ChannelSuperBase::ChannelSuperBase(Transport::EChannelType::Enum _type, bool _active, Transport::Address const & _taddr)
  :channeltype_(_type),
  active_(_active),
  taddr_(_taddr),
  sts_((long)EChannelStatus::INIT)
{
}



ChannelSuperBase::~ChannelSuperBase()
{
}



void ChannelSuperBase::close()
{
  if (EChannelStatus::CLOSED == _GetStatus())
    return;

  _SetStatus(EChannelStatus::CLOSED);
}



EChannelStatus::Enum ChannelSuperBase::_SetStatus(EChannelStatus::Enum _sts)
{
  EChannelStatus::Enum oldsts = (EChannelStatus::Enum)sts_.value();
  sts_ = (long)_sts;
  return oldsts;
}

}
