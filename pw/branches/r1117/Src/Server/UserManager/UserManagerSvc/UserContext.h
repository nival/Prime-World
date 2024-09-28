#pragma once
#include <Network/TransportTypes.h>

namespace UserManager
{
  class UserContext : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( UserContext, BaseObjectMT );

  public:
    UserContext();
    UserContext(Cluster::TUserId const & _userid, string const & _sessionKey, Transport::TServiceId const & _sessionPath, 
      wstring const & _username, bool _partialReconnectSupport, unsigned int _partialReconnectRetriesCount, unsigned int _partialReconnectRetryTimeout);
    ~UserContext();

  public:
    Cluster::TUserId const & userid() const;
    string const & sessionKey() const;
    Transport::TServiceId const & sessionPath() const;
    void shadowTime(NHPTimer::FTime const & _shadowTime);
    NHPTimer::FTime const & shadowTime() const;
    wstring const & username() const;
    bool partialReconnectSupport() const;
    unsigned int decPartialReconnectRetriesCount();
    unsigned int partialReconnectRetryTimeout() const;

  private:
    Cluster::TUserId userid_;
    string sessionKey_;
    Transport::TServiceId sessionPath_;
    NHPTimer::FTime shadowTime_;
    wstring username_;
    bool partialReconnectSupport_;
    unsigned int partialReconnectRetriesCount_;
    unsigned int partialReconnectRetryTimeout_;
  };

  inline
  Cluster::TUserId const & UserContext::userid() const
  {
    return userid_;
  }

  inline
  string const & UserContext::sessionKey() const
  {
    return sessionKey_;
  }

  inline
  Transport::TServiceId const & UserContext::sessionPath() const
  {
    return sessionPath_;
  }

  inline
  NHPTimer::FTime const & UserContext::shadowTime() const
  {
    return shadowTime_;
  }

  inline
  void UserContext::shadowTime(NHPTimer::FTime const & _shadowTime)
  {
    shadowTime_ = _shadowTime;
  }

  inline
  wstring const & UserContext::username() const
  {
    return username_;
  }

  inline
  bool UserContext::partialReconnectSupport() const
  {
    return partialReconnectSupport_;
  }

  inline
  unsigned int UserContext::decPartialReconnectRetriesCount()
  {
    if (partialReconnectRetriesCount_ > 0)
      --partialReconnectRetriesCount_;

    return partialReconnectRetriesCount_;
  }

  inline
  unsigned int UserContext::partialReconnectRetryTimeout() const
  {
    return partialReconnectRetryTimeout_;
  }
}
