#pragma once
#include <Network/TransportTypes.h>
#include <ClusterTypes/ClusterTypes.h>

namespace Relay
{
  class UserContext;

  typedef unsigned int TGameUserGroupId;

  class GameUserGroup : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( GameUserGroup, BaseObjectMT );

    typedef nstl::map<Transport::TClientId, UserContextPtr> UserContextsT;

  public:
    GameUserGroup(TGameUserGroupId _id, Cluster::TGameId const & _gameid);
    ~GameUserGroup();

  public:
    Cluster::TGameId gameid() const;
    TGameUserGroupId id() const;
    char const * fmtid() const;

    SvcContextPtr const & primaryRelay() const;
    SvcContextPtr const & secondaryRelay() const;

    void primaryRelay(SvcContextPtr const & _svctx);
    void secondaryRelay(SvcContextPtr const & _svctx);

    int attachUser(UserContextPtr const & _uctx);
    UserContextPtr detachUser(Transport::TClientId const & _userid);

    unsigned int usercount() const;

  private:
    TGameUserGroupId id_;
    Cluster::TGameId gameid_;
    SvcContextPtr primary_;
    SvcContextPtr secondary_;
    UserContextsT users_;
    string fmtid_;
  };

  inline
  TGameUserGroupId GameUserGroup::id() const
  {
    return id_;
  }

  inline
  Cluster::TGameId GameUserGroup::gameid() const
  {
    return gameid_;
  }

  inline
  SvcContextPtr const & GameUserGroup::primaryRelay() const
  {
    return primary_;
  }

  inline
  SvcContextPtr const & GameUserGroup::secondaryRelay() const
  {
    return secondary_;
  }

  inline
  void GameUserGroup::primaryRelay(SvcContextPtr const & _svctx)
  {
    primary_ = _svctx;
  }

  inline
  void GameUserGroup::secondaryRelay(SvcContextPtr const & _svctx)
  {
    secondary_ = _svctx;
  }

  inline
  unsigned int GameUserGroup::usercount() const
  {
    return (unsigned int)users_.size();
  }

  inline
  char const * GameUserGroup::fmtid() const
  {
    return fmtid_.c_str();
  }
}
