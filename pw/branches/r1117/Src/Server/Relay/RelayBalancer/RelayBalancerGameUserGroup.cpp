#include "stdafx.h"
#include "RelayBalancer/RelayBalancerGameUserGroup.h"
#include "RelayBalancer/RelayBalancerUserContext.h"

NI_DEFINE_REFCOUNT(Relay::GameUserGroup);

namespace Relay
{
  GameUserGroup::GameUserGroup(TGameUserGroupId _id, Cluster::TGameId const & _gameid)
    :id_(_id),
    gameid_(_gameid)
  {
    string gameid = Cluster::FmtGameId(gameid_);
    fmtid_ = NI_STRFMT("%s/%d", gameid.c_str(), id_);
  }

  GameUserGroup::~GameUserGroup()
  {
  }

  int GameUserGroup::attachUser(UserContextPtr const & _uctx)
  {
    if (users_.insert(make_pair(_uctx->userid(), _uctx)).second)
      return 0;

    return -1;
  }

  UserContextPtr GameUserGroup::detachUser(Transport::TClientId const & _userid)
  {
    UserContextPtr uctx;
    UserContextsT::iterator it = users_.find(_userid);
    if (it != users_.end())
    {
      uctx = it->second;
      users_.erase(it);
      return uctx;
    }

    return uctx;
  }
}
