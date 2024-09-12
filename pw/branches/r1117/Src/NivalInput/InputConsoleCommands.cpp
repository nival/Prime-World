#include "stdafx.h"
#include "Binds.h"

namespace
{

bool CharIsNumber( wchar_t c )
{
  if ( ( c == L'.' ) || ( c == L'-' ) || ( c == L'+') )
    return true;
  if ( ( c >= L'0' ) || ( c <= L'9' ) )
    return true;
  return false;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandBind( const char * name, const vector<wstring> & _paramsSet, const wstring &_ctx )
{
  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();
  if(binds)
    binds->RegisterBindString(_ctx, name, _paramsSet );

  string command( _paramsSet.empty() ? string() : NStr::ToMBCS( _paramsSet[0] ) );
  NStr::TrimBoth( command, "\t\n\r\'" );

  float factor = 1.0f;
  bool factorIsUndefined = true;
  if ( ( _paramsSet.size() >= 2 ) && !_paramsSet[1].empty() && CharIsNumber( _paramsSet[1][0] ) )
  {
    wchar_t * endptr = 0;
    double f = wcstod( _paramsSet[1].c_str(), &endptr );
    if ( f && endptr && !*endptr )
    {
      factor = f;
      factorIsUndefined = false;
    }
  }

  int startFrom = factorIsUndefined ? 1 : 2;

  vector<string> keys;
  keys.reserve( _paramsSet.size() );
  for ( int k = startFrom; k < _paramsSet.size(); ++k )
  {
    if ( !_paramsSet[k].compare( L"+" ) ) //skip '+'
      continue;

    keys.push_back( string() );
    NStr::ToMBCS( &keys.back(), _paramsSet[k] );
    NStr::TrimBoth( keys.back(), "\t\n\r\'" );
  }

  if ( keys.empty() || command.empty() )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << "[floating point factor] [!]'bind-id' 'KEY' + ...";
    systemLog( NLogg::LEVEL_MESSAGE ) << "'!' - on release";
    return true;
  }

  if(binds)
    binds->ParseDefineCommand( command, keys, factor, factorIsUndefined );

  return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandRebind( const char * name, const vector<wstring> & _paramsSet, const wstring &_ctx )
{
  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();

  string command( _paramsSet.empty() ? string() : NStr::ToMBCS( _paramsSet[0] ) );
  NStr::TrimBoth( command, "\t\n\r\'" );   

  float factor = 1.0f;
  bool factorIsUndefined = true;
  if ( ( _paramsSet.size() >= 2 ) && !_paramsSet[1].empty() && CharIsNumber( _paramsSet[1][0] ) )
  {
    wchar_t * endptr = 0;
    double f = wcstod( _paramsSet[1].c_str(), &endptr );
    if ( f && endptr && !*endptr )
    {
      factor = f;
      factorIsUndefined = false;
    }
  }

  string commandEx(command);
  commandEx.insert(commandEx.begin(), ' ');
  commandEx.push_back(' ');

  if (!factorIsUndefined)
  {
    if (factor == 1.0f)
    {
      commandEx.push_back('1');
    }
    else if (factor == -1.0f)
    {
      commandEx.push_back('-');
      commandEx.push_back('1');
    }
  }

  // перезапись bindStrings
  if(binds)
  {
    Input::TBinds::const_iterator iter = binds->GetBindStrings().find(_ctx);

    if(iter != binds->GetBindStrings().end())
    {
      const Input::TBindsEntry& entry = *iter;

      int findIndex = -1;

      for ( int i = 0; i < entry.second.size(); i++ )
      {
        if (entry.second[i].find(commandEx) != -1)
        {
          findIndex = i;
          break;
        }
      }

      if (findIndex != -1)
      {
        binds->ReplaceString(_ctx, "bind", _paramsSet, findIndex);
      }
    }
  } 

  int startFrom = factorIsUndefined ? 1 : 2;

  vector<string> keys;
  keys.reserve( _paramsSet.size() );
  for ( int k = startFrom; k < _paramsSet.size(); ++k )
  {
    if ( !_paramsSet[k].compare( L"+" ) ) //skip '+'
      continue;

    keys.push_back( string() );
    NStr::ToMBCS( &keys.back(), _paramsSet[k] );
    NStr::TrimBoth( keys.back(), "\t\n\r\'" );
  }

  if ( keys.empty() || command.empty() )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << "[floating point factor] [!]'bind-id' 'KEY' + ...";
    systemLog( NLogg::LEVEL_MESSAGE ) << "'!' - on release";
    return true;
  }

  if(binds)
    binds->ParseDefineCommand( command, keys, factor, factorIsUndefined, true );

  return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandUnbind( const char* name, const vector<wstring> &paramsSet )
{
  if ( paramsSet.size() < 1 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << "'bind-id'" << endl;
    return true;
  }

  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();
  if(binds)
    binds->DeleteCommand( NStr::ToMBCS( paramsSet.front() ).c_str() );

  return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandUnbindAll( const char* name, const vector<wstring> &paramsSet )
{
  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();
  if(binds)
  {
    binds->ClearBindStrings();
    binds->DeleteAllCommands();
  }
  return true;
}


////////////////////////////////////////////////////////////////////////////////////////////////////
bool CommandBindSection( const char* name, const vector<wstring> &paramsSet, const wstring &_ctx )
{
  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();
  if(binds)
    binds->RegisterBindString(_ctx, name, paramsSet );

  if ( binds && paramsSet.size() >= 1 )
     binds->SetCurrentConfigSection( NStr::ToMBCS( paramsSet.front() ).c_str() );
  else
     binds->SetCurrentConfigSection( 0 );

  return true;
}

} //namespace

////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_CMD_EX( bind, CommandBind )
REGISTER_CMD_EX( rebind, CommandRebind )
REGISTER_CMD( unbind, CommandUnbind )
REGISTER_CMD( unbindall, CommandUnbindAll )
REGISTER_CMD_EX( bindsection, CommandBindSection )
