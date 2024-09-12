#pragma once

#include "IOTerabit/Protocol.h"

namespace Relay
{

class INetworkBasedHandler
{
public:
  virtual int HandleInput(Terabit::AsynchChannel *channel, const char *data, size_t length) = 0;
};

class NetworkProtocolHandler
{
public:
  static const unsigned short  HEADER_SIZE = sizeof(unsigned short);
  static const unsigned short  MAX_PACKET_SIZE = 0xFFFF;
  static const unsigned short  MAX_DATA_SIZE = MAX_PACKET_SIZE - HEADER_SIZE;

public:
  NetworkProtocolHandler(INetworkBasedHandler* input_handler, char const * tagname);
  ~NetworkProtocolHandler();

public:
  ACE_Message_Block* AllocBuffer(Terabit::AsynchChannel *channel, unsigned int bodySize, unsigned long long tag = 0);
  int HandleInput(Terabit::AsynchChannel *channel, const char *data, size_t length);
  int HandleOutput(Terabit::AsynchChannel *channel, ACE_Message_Block& mb);
  int HandleOutput(Terabit::AsynchChannel *channel, ACE_Message_Block& mb,
    unsigned int& qlen, unsigned int& qlen_in_bytes);

  char const * tagname() const;

private:
  INetworkBasedHandler* input_handler_;
  char tagname_[16];
};

inline
char const * NetworkProtocolHandler::tagname() const
{
  return tagname_;
}

}
