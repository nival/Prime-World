#pragma once
#include <Network/TransportTypes.h>

namespace Relay
{
  class UserContext : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( UserContext, BaseObjectMT );

  public:
    UserContext(Transport::TClientId const & userid);
    ~UserContext();

  public:
    Transport::TClientId const & userid() const;

    uint count() const;
    uint incrementCount();
    uint decrementCount();

    GameUserGroupPtr gameusergroup() const;
    void gameusergroup(GameUserGroupPtr const & _gameusergroup);

  private:
    Transport::TClientId userid_;
    uint count_;
    GameUserGroupPtr gameusergroup_;
  };

  inline
  Transport::TClientId const & UserContext::userid() const
  {
    return userid_;
  }

  inline
  uint UserContext::count() const
  {
    return count_;
  }

  inline
  uint UserContext::incrementCount()
  {
    return ++count_;
  }

  inline
  uint UserContext::decrementCount()
  {
    NI_ASSERT(count_ > 0, "");
    return --count_;
  }

  inline
  GameUserGroupPtr UserContext::gameusergroup() const
  {
    return gameusergroup_;
  }

  inline
  void UserContext::gameusergroup(GameUserGroupPtr const & _gameusergroup)
  {
    gameusergroup_ = _gameusergroup;
  }

}
