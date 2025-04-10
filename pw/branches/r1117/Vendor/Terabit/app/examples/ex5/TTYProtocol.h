#ifndef TTY_PROTOCOL_H
#define TTY_PROTOCOL_H

#include "IOTerabit/AsynchChannel.h"
#include "IOTerabit/Protocol.h"


// *************************************************************
//   TTY Protocol - basic for client and servers
// *************************************************************

class TTYProtocol :
    public Terabit::Protocol
{

public:
   
    TTYProtocol(Terabit::ProtocolFactory& factory);

    virtual ~TTYProtocol();


private:
    // must be overriden in derived classed
    // called from on_read_completed
    virtual int process_message(Terabit::AsynchChannel *channel,
                                const char             *payload,
                                size_t                  length) = 0;

  

    // this is main parsing method
    virtual int on_read_completed (Terabit::AsynchChannel *channel,
                                   const char    *data,
                                   size_t         length);



};

#endif  // TTY_PROTOCOL_H

