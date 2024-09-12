#pragma once

namespace Transport
{
  struct IClientsVerifier;
  struct OpenChannelRequest;
}

namespace Relay
{

class NewClientVerifier
{
public:
  NewClientVerifier(Transport::IClientsVerifier* verifier);
  ~NewClientVerifier();

public:
  bool VerifyClient(Transport::OpenChannelRequest* pmsg);
  void NotifyClientDisconnected( int userId );

private:
  Transport::IClientsVerifier* verifier_;
};

}
