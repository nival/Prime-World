#include "stdafx.h"
#include "NLClientHandler.h"
#include <IOTerabit/AsynchChannel.h>

namespace NetworkLayer
{
#pragma warning( push )
#pragma warning( disable : 4355)
ClientHandler::ClientHandler()
  :network_handler_(this)
#pragma warning( pop )
{
}

ClientHandler::~ClientHandler()
{
}

ACE_Message_Block* 
ClientHandler::AllocBuffer(Terabit::MessageBlockFactory & outmbf, unsigned int dataSize)
{
  return network_handler_.AllocBuffer(outmbf, dataSize);
}

naio::StatusT 
ClientHandler::HandleInput(size_t length, const char *data, size_t& readBytes, 
                naio::ConnectionContextStrongPtr const & spconn, 
                Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  LOG_M(logname).Trace("%s", data);

  //poutmb = AllocBuffer(outmbf, length);
  //poutmb->copy(data, length);

  readBytes = length;

  return naio::status::SUCCESS;
}

naio::StatusT 
ClientHandler::HandleOutput(size_t size, char const * data, 
                            naio::ConnectionContextStrongPtr const & spconn, 
                            Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  ACE_Message_Block* pmb = AllocBuffer(outmbf, size);
  poutmb = pmb;
  return network_handler_.HandleOutput(*pmb, true, spconn, outmbf, poutmb);
}

}
