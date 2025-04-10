
#include "TTYProtocol.h"
#include "ace/OS_NS_string.h"
#include "ace/OS_NS_strings.h"

TTYProtocol::TTYProtocol(Terabit::ProtocolFactory& factory)
: Terabit::Protocol (factory)
{
}

TTYProtocol::~TTYProtocol()
{
}



int
TTYProtocol::on_read_completed (Terabit::AsynchChannel *channel,
                                const char             *data,
                                size_t                  length)
{
    unsigned int consumed = 0;

    while (length > 0)
    {
        const char *msg = data;

        const char *ptr_nl = (const char*) ACE_OS::memchr (data, '\n', length);
        if (ptr_nl == 0)    // no NL in the buffer
        {
            if (length < channel->get_read_size())
            {
                break; // read more
            }

            // read buffer is full, but no NL
            return -1;  // protocol error
        }

        size_t  msglen = (ptr_nl - msg) + 1;

        if (process_message (channel, msg, msglen) < 0)
        {
            return -1;
        }

        data   += msglen;
        length -= msglen;
        consumed += msglen;
    }
    return consumed;
}

