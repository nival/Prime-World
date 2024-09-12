#ifndef REMOTESESSIONDEBUGVARS_H_INCLUDED
#define REMOTESESSIONDEBUGVARS_H_INCLUDED

#include "server/lobbypvx/commontypes.h"

namespace StatisticService
{
  class GameStatClient;
}

namespace Game
{

class DebugVarsSender : public BaseObjectST, public NDebug::IDebugVarWatcher
{
  NI_DECLARE_REFCOUNT_CLASS_2( DebugVarsSender, BaseObjectST, NDebug::IDebugVarWatcher );

public:
  DebugVarsSender();
  ~DebugVarsSender();

  void OnSessionStart( StatisticService::GameStatClient * _statistics, lobby::TGameId _sessionId, int _userId );
  void PollSession( int worldStep );

protected:
  //NDebug::IDebugVarWatcher
  virtual void OnDebugVarEvent( NDebug::IDebugVar * debugVar );

private:
  struct SVarEntry
  {
    NDebug::IDebugVar * var;
    NHPTimer::FTime     period;
    NHPTimer::FTime     nextSendTime;
    bool                prevWarningStatus;

    SVarEntry( NDebug::IDebugVar * _var, NHPTimer::FTime _period ) :
    var( _var ), period( _period ), nextSendTime( 0 ), prevWarningStatus( _var->IsWarning() )
    {}

    SVarEntry() : var( 0 ), period( 0 ), nextSendTime( 0 ), prevWarningStatus( false ) {}
  };

  typedef list<SVarEntry>  TVarsToSend;

  StrongMT<StatisticService::GameStatClient> statistics;
  lobby::TGameId sessionId;
  int           userId;
  TVarsToSend   varsToSend;

  void SendVar( struct SVarEntry & debugVar, NHPTimer::FTime now, int worldStep );

  bool CommandSendVar( const char * name, const vector<wstring> & args );
  bool CommandStopVar( const char * name, const vector<wstring> & args );
};

} //namespace Game

#endif //REMOTESESSIONDEBUGVARS_H_INCLUDED
