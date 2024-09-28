#pragma once
#include "RelayPipe.h"
#include <list>

namespace Relay
{
  class MulticastPipe : public Pipe
  {
    struct Recipient
    {
      Recipient(Transport::TPipeId _cpid, ClientContextSP _cctx)
        :cpid_(_cpid),
        cctx_(_cctx)
      {
      }

      Transport::TPipeId cpid_;
      ClientContextSP cctx_;
    };

    typedef std::list<Recipient> RecipientsT;

  public:
    MulticastPipe();

    MulticastPipe(Transport::TServiceId const & _svcid,
      Transport::TPipeId const & _svcpid,
      BackendContextSP const & _svctx,
      StrongMT<ITrafficTracker> const & _tt);

  public:
    int AddRecipient(Transport::TPipeId _cpid, ClientContextSP const & _cctx);
    Transport::TPipeId RemoveRecipient(Transport::TClientId const & _cid);
    int HandleOutput(char const * _data, size_t _size);
    int HandleCloseChannel();

  private:
    mutable ACE_Thread_Mutex recipientsMutex_;
    RecipientsT recipients_;
  };
}
