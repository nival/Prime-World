#pragma once
#include "naio/Operation.h"
#include <ace/INET_Addr.h>

class ACE_Message_Block;

namespace naio
{
  //namespace op
  //{
    //////////////////////////////////////////////////////////////////////////
    //  OpenConnection
    //
    class OpenConnectionOp : public Operation
    {
    public:
      OpenConnectionOp(ACE_INET_Addr const & addr, ConnectionContextStrongPtr const & conn);
      ~OpenConnectionOp();

    public:
      ACE_INET_Addr const & addr() const;
      ConnectionContextStrongPtr const & connctx() const;

      void OnConnection(bool success, ChannelContextStrongPtr const & spcc);

    protected:
      ACE_INET_Addr addr_;
      ConnectionContextStrongPtr conn_;
    };

    inline
    ACE_INET_Addr const & OpenConnectionOp::addr() const
    {
      return addr_;
    }

    inline
    ConnectionContextStrongPtr const & OpenConnectionOp::connctx() const
    {
      return conn_;
    }

    //////////////////////////////////////////////////////////////////////////
    //  CloseConnectionOp
    //
    class CloseConnectionOp : public Operation
    {
    public:
      CloseConnectionOp(ConnectionContextStrongPtr const & spctx);
      ~CloseConnectionOp();
    };

    //////////////////////////////////////////////////////////////////////////
    //  
    //
    class SendData : public Operation
    {
    public:
      SendData(unsigned int size, char const * data, bool preallocated, ConnectionContextStrongPtr const & spctx);
      ~SendData();

    public:
      ACE_Message_Block* mb();
      bool preallocated() const;

    protected:
      ACE_Message_Block* pmb_;
      bool preallocated_;
    };

    inline
    bool SendData::preallocated() const
    {
      return preallocated_;
    }

    inline
    ACE_Message_Block* SendData::mb()
    {
      return pmb_;
    }
//  }
}
