#include "UserManagerSvc/stdafx.h"
#include "UserManagerSvc/UserContext.h"

NI_DEFINE_REFCOUNT(UserManager::UserContext);

namespace UserManager
{
  UserContext::UserContext()
    :userid_(Cluster::INVALID_USER_ID)
  {
  }

  UserContext::UserContext(Cluster::TUserId const & _userid, string const & _sessionKey, 
                           Transport::TServiceId const & _sessionPath, wstring const & _username, 
                           bool _partialReconnectSupport, unsigned int _partialReconnectRetriesCount, unsigned int _partialReconnectRetryTimeout)
    :userid_(_userid),
    sessionKey_(_sessionKey),
    sessionPath_(_sessionPath),
    username_(_username),
    partialReconnectSupport_(_partialReconnectSupport),
    partialReconnectRetriesCount_(_partialReconnectRetriesCount),
    partialReconnectRetryTimeout_(_partialReconnectRetryTimeout)
  {
  }

  UserContext::~UserContext()
  {
  }
}
