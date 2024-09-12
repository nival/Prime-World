#pragma once

namespace NGameX
{

namespace IgnoreList
{
  typedef unsigned long long TUserId;
  typedef nstl::wstring TUserNickname;

  typedef nstl::set<TUserId> TUserSet;
  typedef nstl::map<TUserId, TUserNickname> TUserNicknameMap;
}

using IgnoreList::TUserId;
using IgnoreList::TUserNickname;

_interface IIgnoreListListener : public IBaseInterfaceST
{
  NI_DECLARE_CLASS_1( IIgnoreListListener, IBaseInterfaceST );

  virtual void OnUserAddedToIgnoreList(const TUserId auid) = 0;
  virtual void OnUserRemovedFromIgnoreList(const TUserId auid) = 0;
};


class IgnoreListStorage: public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( IgnoreListStorage, BaseObjectST );
public:
  explicit IgnoreListStorage(const TUserId _auid);

  void AddListener(IIgnoreListListener* const listener);

  void AddUser(const TUserId auid);
  void RemoveUser(const TUserId auid);

  void AddUserNickname(const TUserId auid, const TUserNickname& nickname);

  bool ContainsUser(const TUserId auid) const
  {
    return (users.find(auid) != users.end());
  }

  void LoadFromFile();
  void SaveToFile() const;

  const IgnoreList::TUserSet& GetIgnoredUsers() const
  {
    return users;
  }
private:
  typedef Weak<IIgnoreListListener> TListenerWeakPtr;
  typedef Strong<IIgnoreListListener> TListenerPtr;
  typedef list<TListenerWeakPtr> TListeners;

  IgnoreListStorage();
  IgnoreListStorage(const IgnoreListStorage&);
  IgnoreListStorage& operator=(const IgnoreListStorage&);

  const TUserId ownerUserId;

  TListeners listeners;

  IgnoreList::TUserSet users;
  IgnoreList::TUserNicknameMap nicknames;
};

}
