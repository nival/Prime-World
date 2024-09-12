#include "stdafx.h"

#include "CommandBinds.h"
#include "NivalInput/BindsContainer.h"
#include "NivalInput/Binds.h"


namespace CommandBinds
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class KeyCombination
{
public:
  KeyCombination() {}
  
  explicit KeyCombination( const vector<string> & _keys ) :
  keys( _keys )
  {
    nstl::sort( keys.begin(), keys.end() );
  }

  ~KeyCombination() {}

  bool operator < ( const KeyCombination & other ) const
  {
    if ( keys.size() < other.keys.size() )
      return true;
    if ( keys.size() > other.keys.size() )
      return false;
    
    NI_ASSERT( keys.size() == other.keys.size(), "" );
    for ( int i = 0; i < keys.size(); ++i )
    {
      if ( keys[i] < other.keys[i] )
        return true;
      if ( keys[i] > other.keys[i] )
        return false;
    }
    return false;
  }

  const vector<string> & Get() const { return keys; }

private:
  vector<string> keys;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct SCommandBindInfo
{
  int     id;
  string  command;

  SCommandBindInfo() : id( 0 ) {}
  explicit SCommandBindInfo( const string & cmd ) : id( 0 ), command( cmd ) {}
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef map<KeyCombination, SCommandBindInfo> TCommandsMapping;

static TCommandsMapping s_mapping;
static Input::BindsContainer s_handlers;
static int s_nextCommandBindId = 1;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool CommandHandler( const KeyCombination & id )
{
  TCommandsMapping::const_iterator it = s_mapping.find( id );
  if ( it != s_mapping.end() )
  {
    vector<string> commands;
    NStr::SplitString( it->second.command, &commands, ';' );

    for ( int i = 0; i < commands.size(); ++i )
      NGlobal::RunCommand( NStr::ToUnicode( commands[i] ) );
  }
  return true;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void BindCommand( const vector<string> & keys, const string & command )
{
  KeyCombination key( keys );

  SCommandBindInfo & info = s_mapping[ key ];

  if ( !info.id )
  {
    //New key combination
    string commandId( NStr::StrFmt( "internal_command_bind_event_%x", s_nextCommandBindId ) );
    ++s_nextCommandBindId;

     Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();
     if(binds)
       binds->ParseDefineCommand( commandId, keys );


    s_handlers.AddActivationHandler( commandId.c_str(), CommandHandler, key );
  }
  else
  {
    //These keys is already used
  }

  info.command = command;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool ProcessEvent( const Input::Event & event )
{
  return s_handlers.ProcessEvent( event, 0 );
}


} //namespace CommandBinds

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool CommandBindCommand( const char* name, const vector<wstring> &_paramsSet, const wstring &_ctx )
{
  if ( _paramsSet.size() > 1 )
  {
    vector<wstring> newParams(_paramsSet);
    newParams.back() = L"\"" + newParams.back() + L"\"";

    Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();
    if(binds)
      binds->RegisterBindString(_ctx, name, newParams );

    vector<string> keys;
    keys.reserve( _paramsSet.size() - 1 );

    for ( int k = 0; k < _paramsSet.size() - 1; ++k )
    {
      if ( _paramsSet[k].compare( L"+" ) == 0 )
        continue;
      keys.push_back( string() );
      NStr::ToMBCS( &keys.back(), _paramsSet[k] );
      NStr::TrimBoth( keys.back(), "\t\n\r\'" );
    }

    if ( !keys.empty() )
      CommandBinds::BindCommand( keys, NStr::ToMBCS( _paramsSet.back() ) );
  }

  return true;
}

REGISTER_CMD_EX( bind_command, CommandBindCommand );
