#pragma once
#include <Network/TransportTypes.h>
#include <ClusterTypes/ClusterTypes.h>
#include "RelayBalancer/RelayBalancerGameUserGroup.h"

namespace Relay
{
  class UserContext;

  class GameContext : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( GameContext, BaseObjectMT );


  public:
    GameContext(Cluster::TGameId const & _gameid);
    ~GameContext();

  public:
    Cluster::TGameId const & gameid() const;

    GameUserGroupPtr selectGroup4relayAllocation();
    SvcContextPtr getExceptedPrimaryRelay4Group(GameUserGroupPtr const & _group);
    SvcContextPtr getExceptedSecondaryRelay4Group(GameUserGroupPtr const & _group);

    unsigned int usercount() const;

  private:
    Cluster::TGameId gameid_;
    GameUserGroupPtr group1_;
    GameUserGroupPtr group2_;
  };

  inline
  Cluster::TGameId const & GameContext::gameid() const
  {
    return gameid_;
  }

  inline
  unsigned int GameContext::usercount() const
  {
    return group1_->usercount() + group2_->usercount();
  }
}
