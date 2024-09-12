#include "stdafx.h"
#include "RelayBalancer/RelayBalancerGameContext.h"
#include "RelayBalancer/RelaySvcContext.h"

NI_DEFINE_REFCOUNT(Relay::GameContext);

namespace Relay
{
  GameContext::GameContext(Cluster::TGameId const & _gameid)
    :gameid_(_gameid),
    group1_(new GameUserGroup(1, _gameid)),
    group2_(new GameUserGroup(2, _gameid))
  {
  }

  GameContext::~GameContext()
  {
    group2_ = 0;
    group1_ = 0;
  }

  GameUserGroupPtr GameContext::selectGroup4relayAllocation()
  {
    if (group1_->usercount() <= group2_->usercount())
      return group1_;
    else
      return group2_;
  }

  SvcContextPtr GameContext::getExceptedPrimaryRelay4Group(GameUserGroupPtr const & _group)
  {
    SvcContextPtr svctx;
    if (_group == group1_)
      svctx = group2_->primaryRelay();
    else
    if (_group == group2_)
      svctx = group1_->primaryRelay();

    if (svctx && !svctx->isopen())
      svctx = 0;

    return svctx;
  }

  SvcContextPtr GameContext::getExceptedSecondaryRelay4Group(GameUserGroupPtr const & _group)
  {
    SvcContextPtr svctx;
    if (_group == group1_)
      svctx = group2_->secondaryRelay();
    else
    if (_group == group2_)
      svctx = group1_->secondaryRelay();

    if (svctx && !svctx->isopen())
      svctx = 0;

    return svctx;
  }
}
