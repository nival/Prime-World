#ifndef SOCIALLOBBYREMOTEMM_H_INCLUDED
#define SOCIALLOBBYREMOTEMM_H_INCLUDED

#include "Network/TransportTypes.h"
#include <map>

namespace mmaking
{
  class ILiveMMaking;
  class ILiveMMakingClient;

  namespace EServiceGameModes { enum Enum; }
}



namespace socialLobby
{

class Config;
class IMaps;


template <class THostClass, typename TState>
class TSimpleFSM
{
public:
  TSimpleFSM( TState _initialState, timer::Time _now ) :
  state( _initialState ),
  now( _now ),
  currentStateTimeoutMoment( -1 )
  {}

  TState State() const { return state; }

  bool Poll( timer::Time _now ) {
    now = _now;

    if ( currentStateTimeoutMoment >= 0 )
      if ( now >= currentStateTimeoutMoment ) {
        return false;
      }

    return true;
  }

protected:
  void ChangeState( TState _newState ) { ChangeState( _newState, -1 ); }

  void ChangeState( TState _newState, timer::Time _timeout ) {
    state = _newState;

    if ( _timeout < 0 )
      currentStateTimeoutMoment = -1;
    else
      currentStateTimeoutMoment = now + _timeout;
  }

private:
  TState        state;
  timer::Time   now;
  timer::Time   currentStateTimeoutMoment;
};



namespace RemoteMmState
{
  enum Enum { Init, SettingUp, Active, ToRemove };
}


class RemoteMmLogic : public BaseObjectST, public TSimpleFSM<RemoteMmLogic, RemoteMmState::Enum>
{
  NI_DECLARE_REFCOUNT_CLASS_1( RemoteMmLogic, BaseObjectST );

public:
  RemoteMmLogic( Config * _cfg, const Transport::TServiceId & _svcId, mmaking::ILiveMMaking * _remote, mmaking::ILiveMMakingClient * _mmClient, const string & _mapId, timer::Time _now );
  bool Poll( timer::Time _now );

  const Transport::TServiceId & SvcId() const { return svcId; }
  const string & MapId() const { return mapId; }
  void SetupResult( bool _result );

  mmaking::ILiveMMaking * Interface() { return remote; }

private:
  const Transport::TServiceId       svcId;
  const string                      mapId;
  Strong<Config>                    config;
  StrongMT<mmaking::ILiveMMaking>   remote;
  WeakMT<mmaking::ILiveMMakingClient> mmClient;
};





class MmLogix : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( MmLogix, BaseObjectST );

public:
  MmLogix( Config * _cfg, IMaps * _maps, mmaking::ILiveMMakingClient * _mmClient );

  void SetupResult( const Transport::TServiceId & _svcId, bool _result );
  void RegisterMmLogic( const Transport::TServiceId & _svcId, mmaking::ILiveMMaking * _logic, mmaking::EServiceGameModes::Enum _gameModes );
  RemoteMmLogic * GetMmLogic( const string & mapId ) const;
  void Poll( timer::Time _now );

private:
  struct UnassignedLogic
  {
    UnassignedLogic() : modes( (mmaking::EServiceGameModes::Enum)0 ) {}

    UnassignedLogic( mmaking::ILiveMMaking * _logic, mmaking::EServiceGameModes::Enum _modes ) :
    logic( _logic ),
    modes( _modes )
    {}

    StrongMT<mmaking::ILiveMMaking> logic;
    mmaking::EServiceGameModes::Enum  modes;
  };

  typedef std::map<string, Strong<RemoteMmLogic>>  TLogics;
  typedef std::map<Transport::TServiceId, UnassignedLogic>  TUnassignedLogics;

  Strong<Config>      config;
  Strong<IMaps>       maps;
  WeakMT<mmaking::ILiveMMakingClient> mmClient;
  TLogics             logics;
  TUnassignedLogics   unassigned;
  timer::Time         now;

  string FindUnassignedGameMode( mmaking::EServiceGameModes::Enum _modes ) const;
  void AssignGameMode( const Transport::TServiceId & _svcId, mmaking::ILiveMMaking * _logic, const string & _mapId );
};

} //namespace socialLobby

#endif //SOCIALLOBBYREMOTEMM_H_INCLUDED
