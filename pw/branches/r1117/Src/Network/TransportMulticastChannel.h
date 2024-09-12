#pragma once
#include "Network/ConnectionState.h"
#include "Network/TransportError.h"
#include "Network/TransportAddress.h"

namespace Transport
{
  struct IMulticastChannel : public IBaseInterfaceMT
  {
    NI_DECLARE_CLASS_1( IMulticastChannel, IBaseInterfaceMT )

    virtual Network::ConnectionState::Enum GetStatus() const = 0;
    virtual EError::Enum Close() = 0;

    virtual Address const & GetAddress() const = 0;
    virtual EError::Enum SendRaw(byte const * _data, int _size) = 0;

    virtual EError::Enum AddRecipient(Transport::TClientId const & _recipient) = 0;
    virtual EError::Enum RemoveRecipient(Transport::TClientId const & _recipient) = 0;
    virtual bool FindRecipient(Transport::TClientId const & _recipient) = 0;
    virtual unsigned int Recipients() const = 0;

    virtual Transport::TClientId GetFirstRecipient(int & _bypass) = 0;
    virtual Transport::TClientId GetNextRecipient(int _bypass) = 0;
  };
}
