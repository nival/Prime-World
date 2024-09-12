#ifndef SOCIALLOBBYPARTY_H_INCLUDED
#define SOCIALLOBBYPARTY_H_INCLUDED

#include "SocialLobbyTypes.h"

namespace NDb
{
  struct AdvMapDescription;
}

namespace socialLobby
{

namespace EPartyState
{
  enum Enum { WaitingMembers, InLine, InOperation, Incomplete };
}


class Config;
class UserContext;
class IControl;
class RemoteMmLogic;

class Party : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( Party, BaseObjectST );

public:
  Party( Config * _cfg, timer::Time _now, UserContext * _firstMember, IControl * _control );

  EPartyState::Enum State() const { return state; }
  TPartyId Id() const { return id; }
  mmaking::TRequestUId MmReqId() const { return mmReqId; }
  int PlayersNumber() const;

  const mmaking::SRequestCommonData & CommonData() const { return commonData; }

  int Size() const { return members.size(); }
  UserContext * Member( int _idx ) { NI_VERIFY( _idx >= 0 && _idx < members.size(), "", return 0 ); return members[_idx]; }
  void ResetMember( int _idx ) { NI_VERIFY( _idx >= 0 && _idx < members.size(), "", return ); members[_idx] = 0; }
  bool HasMember( UserContext * _ctx ) const;
  bool MmLogicIsValid() const { return logic.Valid(); }
  const string & MapId() const { return mapId; }
  bool HasEnemyLineup() const { return !enemyLineup.empty(); }

  bool Add( UserContext * _ctx );
  bool Completed() const;
  bool PutRequestInLine( mmaking::TRequestUId _mmReqId, timer::Time _addWaitTime, bool _canBeEmpty );
  void RemoveRequestFromLine();
  void ResetRequestInLine();
  void ChangeAllMembersStatus( ERequestStatus::Enum _newStatus );
  void RemoveAllRequests( bool _logStatistics = true, UserContext * _exceptThis = 0 );

  bool SetupCustomGame( mmaking::SGame & _mmData, const NDb::AdvMapDescription * _map );

  bool Poll( timer::Time _now );

private:
  const TPartyId                id;
  const timer::Time             creationTime;
  const string                  mapId;
  mmaking::SRequestCommonData   commonData;
  const vector<TUId>            lineup;
  const vector<TUId>            enemyLineup;

  Strong<Config>                config;

  EPartyState::Enum             state;
  WeakMT<IControl>              control;
  mmaking::TRequestUId          mmReqId;
  vector<Weak<UserContext>>     members; //Can contain dead/zero pointers
  Weak<RemoteMmLogic>           logic;

  bool UpdateLineup( UserContext * _ctx );
};

} //namespace socialLobby

#endif //SOCIALLOBBYPARTY_H_INCLUDED
