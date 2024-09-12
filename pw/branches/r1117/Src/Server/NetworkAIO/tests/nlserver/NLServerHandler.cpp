#include "stdafx.h"
#include "NLServerHandler.h"
#include <IOTerabit/AsynchChannel.h>

namespace NetworkLayer
{
#pragma warning( push )
#pragma warning( disable : 4355)
ServerHandler::ServerHandler()
  :network_handler_(this)
#pragma warning( pop )
{
}

ServerHandler::~ServerHandler()
{
}

ACE_Message_Block* 
ServerHandler::AllocBuffer(Terabit::MessageBlockFactory & outmbf, unsigned int dataSize)
{
  return network_handler_.AllocBuffer(outmbf, dataSize);
}

naio::StatusT 
ServerHandler::HandleInput(size_t length, const char *data, size_t& readBytes, 
                naio::ConnectionContextStrongPtr const & spconn, 
                Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  if (0 == ::strncmp(data, "CLOSE", length))
  {
    return naio::status::FAIL;
  }
  else
  {
    LOG_M("nlserver").Trace("%s", data);

    poutmb = AllocBuffer(outmbf, length);
    poutmb->copy(data, length);
  }

  readBytes = length;

  return naio::status::SUCCESS;
}

naio::StatusT 
ServerHandler::HandleOutput(size_t size, char const * data, 
                            naio::ConnectionContextStrongPtr const & spconn, 
                            Terabit::MessageBlockFactory& outmbf, ACE_Message_Block*& poutmb)
{
  ACE_Message_Block* pmb = AllocBuffer(outmbf, size);
  poutmb = pmb;
  return network_handler_.HandleOutput(*pmb, true, spconn, outmbf, poutmb);
}

}
