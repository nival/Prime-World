#include "stdafx.h"
#include "DebugVarsSender.h"

#include "System/DebugVar.h"
#include "Server/Statistic/GameStatClient.h"
#include "Server/Statistic/StatisticsDebugTypes.h"

NI_DEFINE_REFCOUNT( Game::DebugVarsSender );

namespace Game
{

DebugVarsSender::DebugVarsSender() :
sessionId( 0 ),
userId( 0 )
{
  NGlobal::RegisterContextCmd( "sendvar", this, &DebugVarsSender::CommandSendVar );
  NGlobal::RegisterContextCmd( "stopvar", this, &DebugVarsSender::CommandStopVar );
}



DebugVarsSender::~DebugVarsSender()
{
  NGlobal::UnregisterCmd( "sendvar" );
  NGlobal::UnregisterCmd( "stopvar" );
}



void DebugVarsSender::OnSessionStart( StatisticService::GameStatClient * _statistics, lobby::TGameId _sessionId, int _userId )
{
  statistics = _statistics;
  sessionId = _sessionId;
  userId = _userId;

  NHPTimer::FTime now = NHPTimer::GetScalarTime();

  if ( statistics && sessionId )
    for ( TVarsToSend::iterator it = varsToSend.begin(); it != varsToSend.end(); ++it )
        if ( !it->period )
          SendVar( *it, now, 0 );
}



void DebugVarsSender::PollSession( int worldStep )
{
  if ( !statistics || !sessionId )
    return;

  NHPTimer::FTime now = NHPTimer::GetScalarTime();

  for ( TVarsToSend::iterator it = varsToSend.begin(); it != varsToSend.end(); ++it )
  {
    if ( !it->period )
      continue;

    bool have2Send = false;

    if ( it->var->IsWarning() != it->prevWarningStatus )
      have2Send = true;

    if ( now > it->nextSendTime )
      have2Send = true;

    if ( !have2Send )
      continue;

    SendVar( *it, now, worldStep );
  }
}



void DebugVarsSender::OnDebugVarEvent( NDebug::IDebugVar * debugVar )
{
  for ( TVarsToSend::iterator it = varsToSend.begin(); it != varsToSend.end(); ++it )
    if ( it->var == debugVar )
    {
      if ( !it->period )
        SendVar( *it, NHPTimer::GetScalarTime(), 0 );
    }
}


#pragma warning( disable : 4996 ) // This function or variable may be unsafe.

void DebugVarsSender::SendVar( SVarEntry & debugVar, NHPTimer::FTime now, int worldStep )
{
  debugVar.nextSendTime = now + debugVar.period;
  debugVar.prevWarningStatus = debugVar.var->IsWarning();

  wchar_t value[128] = L"";
  debugVar.var->FormatValue( value, 128 );

  //check if var string contains step index
  wchar_t * column = wcschr( value, L':' );
  if ( column && column[0] )
  {
    int newStep = 0;
    if ( swscanf( column + 1, L"%d", &newStep ) == 1 )
      worldStep = newStep;
    else
      NI_ALWAYS_ASSERT( "Failed to parse world step index" );

    *column = 0;
  }

  StatisticService::RPC::DebugVarMessage msg;
  msg.sessionId = sessionId;
  msg.playerId = userId;
  msg.step = worldStep;
  msg.debugVarName = debugVar.var->GetName();
  msg.debugVarValue = value;
  statistics->Message( msg );
}



bool DebugVarsSender::CommandSendVar( const char * name, const vector<wstring> & args )
{
  if ( args.size() == 2 )
  {
    const wstring & varName = args[0];
    wchar_t * parseEndPtr = 0;
    float period = wcstod( args[1].c_str(), &parseEndPtr );
    if ( !*parseEndPtr && ( period >= 0 ) )
    {
      NDebug::IDebugVar * var = NDebug::FindDebugVar( varName.c_str() );
      if ( !var )
      {
        DebugTrace( "Unknown debug var '%s'", NStr::ToMBCS( varName ).c_str() );
        return true;
      }
      for ( TVarsToSend::iterator it = varsToSend.begin(); it != varsToSend.end(); ++it )
        if ( it->var == var )
        {
          varsToSend.erase( it );
          break;
        }
      varsToSend.push_back( SVarEntry( var, period ) );
      var->AddChangeWatcher( this );
      return true;
    }
  }

  DebugTrace( "usage: sendvar <var_name> <period_seconds>" ); // шлите нам переменную var_name раз в столько секунд (float)
  return true;
}



bool DebugVarsSender::CommandStopVar( const char * name, const vector<wstring> & args )
{
  if ( args.size() == 1 )
  {
    const wstring & varName = args[0];
    if ( !_wcsicmp( varName.c_str(), L"all" ) != 0 )
    {
      varsToSend.clear();
      return true;
    }

    NDebug::IDebugVar * var = NDebug::FindDebugVar( varName.c_str() );
    if ( !var )
    {
      DebugTrace( "Unknown debug var '%s'", NStr::ToMBCS( varName ).c_str() );
      return true;
    }

    for ( TVarsToSend::iterator it = varsToSend.begin(); it != varsToSend.end(); ++it )
      if ( it->var == var )
      {
        varsToSend.erase( it );
        break;
      }
    return true;
  }
  DebugTrace( "usage: stopvar <var_name | ALL>" ); // шлите нам переменную var_name раз в столько секунд (float)
  return true;
}

} //namespace Game
