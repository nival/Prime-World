#pragma warning( push )
#pragma warning( disable : 4996)
#include "stdafx.h"
#include "TransportMessagesHeaders.h"
#include "Network/TransportClientsVerifier.h"
#pragma warning (pop)

#include "NewClientVerifier.h"

using namespace Transport;

namespace Relay
{

NewClientVerifier::NewClientVerifier(IClientsVerifier* verifier)
  :verifier_(verifier)
{
}

NewClientVerifier::~NewClientVerifier()
{
}

bool NewClientVerifier::VerifyClient(OpenChannelRequest* pmsg)
{
  ASSERT(pmsg->clientAddress.target == ENetInterface::FrontEnd);

  if (verifier_)
      return verifier_->VerifyNewClientConnected(pmsg->clientAddress.client, pmsg->loginData);

  return true;
}

void NewClientVerifier::NotifyClientDisconnected( int userId )
{
  if (verifier_)
    verifier_->NotifyClientDisconnected(userId);
}

}
