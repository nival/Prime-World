#include "stdafx.h"
#include "Binds.h"
#include "InputCommandInstance.h"
#include "Section.h"
#include "../System/InlineProfiler.h"


namespace Input
{
static const int VERBOSITY_BINDS = 1;

BindsManager *BindsManager::Instance()
{
  static BindsManager bindsManager;
  return &bindsManager;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void BindsManager::SetBinds( Binds * binds )
{
  s_binds = binds;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Binds * BindsManager::GetBinds(void)
{
  return IsValid( s_binds ) ? s_binds : 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Binds::Binds() :
isNonDefaultSectionsMuted( false )
//currentBindContext(DEFAULT_CONFIG_CONTEXT)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Binds::Binds( IHwInput * _hwInput ) :
hwInput( _hwInput ),
isNonDefaultSectionsMuted( false )
//currentBindContext(DEFAULT_CONFIG_CONTEXT)
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Binds::~Binds()
{
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ICommandInstance * Binds::DefineCommand( const char * name, bool inverted, const vector<string> & controlNames, float factor, bool factorIsUndefined, bool isRebind )
{
  CObj<ICommandInstanceImplementation> cmd;

  TCommands::iterator it = FindCommandImpl( name );
  if ( it != commands.end() )
  {
    cmd = *it;
    NI_DATA_ASSERT( inverted == cmd->Inverted(), NStr::StrFmt( "Second definition of bind '%s' has different inversion flag!", name ) );
  }
  else
  {
    cmd = new CommandInstance( hwInput, name, inverted );
    commands.push_back( cmd );
  }
  cmd->AddBind( controlNames, currentConfigSection, factor, factorIsUndefined, isRebind );

  if (isRebind)
  {
    UpdateAllCommandsSupersets();
  }
  else
  {
    AddSingleCommandSupersets( cmd );
  }

  return cmd;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::DeleteCommand( const char * name )
{
  TCommands::iterator it = FindCommandImpl( name );
  if ( it != commands.end() )
    commands.erase( it );

  UpdateAllCommandsSupersets();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::DeleteAllCommands()
{
  vector<string> todel;

  // Prevent delete "win_XXX" commands from SystemEvents::SystemEvents
  for ( TCommands::const_iterator it = commands.begin(); it != commands.end(); ++it )
    if ( (*it)->Name().find( "win_" ) == nstl::string::npos )
      todel.push_back( (*it)->Name() );
  
  for ( int i = 0; i < todel.size(); i++ )
  {
    DeleteCommand( todel[i].c_str() );
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
ICommandInstance * Binds::FindCommand( const char * name )
{
  TCommands::iterator it = FindCommandImpl( name );
  if ( it != commands.end() )
    return *it;
  else
    return 0;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::DefineCustomCommand( const char * name, ICommandInstanceImplementation * cmd )
{
  TCommands::iterator it = FindCommandImpl( name );
  NI_VERIFY( it == commands.end(), NStr::StrFmt( "Custom command '%s' already defined" ), return );
  NI_ASSERT( strcmp( name, cmd->Name().c_str() ) == 0, "Invalid bind name" );
  commands.push_back( cmd );

  AddSingleCommandSupersets( cmd );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Binds::TCommands::iterator Binds::FindCommandImpl( const char * name )
{
  for ( TCommands::iterator it = commands.begin(); it != commands.end(); ++it )
    if ( !strcmp( (*it)->Name().c_str(), name ) )
      return it;
  return commands.end();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Binds::TCommands::const_iterator Binds::FindCommandImpl( const char * name ) const
{
  for ( TCommands::const_iterator it = commands.begin(); it != commands.end(); ++it )
    if ( !strcmp( (*it)->Name().c_str(), name ) )
      return it;
  return commands.end();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::AddSingleCommandSupersets( ICommandInstanceImplementation * cmd )
{
  for ( TCommands::const_iterator it = commands.begin(); it != commands.end(); ++it )
    if ( *it != cmd )
      (*it)->UpdateControlsSupersets( cmd->AccessControlsSet() );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Full heavy NxN update
void Binds::UpdateAllCommandsSupersets()
{
  for ( TCommands::const_iterator it = commands.begin(); it != commands.end(); ++it )
    (*it)->ClearControlsSupersets();

  for ( TCommands::const_iterator it = commands.begin(); it != commands.end(); ++it )
    for ( TCommands::const_iterator it2 = commands.begin(); it2 != commands.end(); ++it2 )
      if ( *it != *it2 )
        (*it)->UpdateControlsSupersets( (*it2)->AccessControlsSet() );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::Update( float deltaTime, bool appFocus )
{
  NI_PROFILE_FUNCTION;

  UpdateMutiness();

  hwInput->OnApplicationFocus( appFocus );

  hwEventsBuffer.clear();
  hwInput->Poll( hwEventsBuffer );

  //Deliver hardware events
  for ( int i = 0; i < hwEventsBuffer.size(); ++i )
  {
    for ( TCommands::iterator it = commands.begin(); it != commands.end(); ++it )
      (*it)->ProcessHwEvent( hwEventsBuffer[i], eventz );
  }
  hwEventsBuffer.clear();

  //
  for ( TCommands::iterator it = commands.begin(); it != commands.end(); ++it )
    (*it)->Update( deltaTime, eventz, appFocus );

  //
  if ( GetVerbosityLevel() >= VERBOSITY_BINDS )
    for ( int i = 0; i < eventz.size(); ++i )
      DebugTrace( "Passed bind '%s' event", eventz[i].Command()->Name().c_str() );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::ParseDefineCommand( const string & command, const vector<string> & keys, float factor, bool factorIsUndefined, bool isRebind )
{
  NI_ASSERT( !keys.empty(), "" );

  //UGLY: nice way to work out left and right 'ctrl' & 'alt'
  vector<string> keysCopy( keys );
  for ( int k = 0; k < keys.size(); ++k )
  {
    if ( keysCopy[k] == "CTRL" )
    {
      keysCopy[k] = "LCTRL";
      ParseDefineCommand( command, keysCopy, factor, factorIsUndefined );
      keysCopy[k] = "RCTRL";
      ParseDefineCommand( command, keysCopy, factor, factorIsUndefined );
      return;
    }
    if ( keysCopy[k] == "ALT" )
    {
      keysCopy[k] = "LALT";
      ParseDefineCommand( command, keysCopy, factor, factorIsUndefined );
      keysCopy[k] = "RALT";
      ParseDefineCommand( command, keysCopy, factor, factorIsUndefined );
      return;
    }
    if ( keysCopy[k] == "SHIFT" )
    {
      keysCopy[k] = "LSHIFT";
      ParseDefineCommand( command, keysCopy, factor, factorIsUndefined );
      keysCopy[k] = "RSHIFT";
      ParseDefineCommand( command, keysCopy, factor, factorIsUndefined );
      return;
    }
  }

  bool inverted = false;
  string commandCopy( command );
  switch ( commandCopy[0] )
  {
    case '!':
      inverted = true;
      NStr::TrimLeft( commandCopy, '!' );
      break;

    default:
      break;
  }

  DefineCommand( commandCopy.c_str(), inverted, keys, factor, factorIsUndefined, isRebind );
  //TODO: NInput::currentSection
}




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::SetCurrentConfigSection( const char * name )
{
  if ( !name || !name[0] )
  {
    currentConfigSection = 0;
    return;
  }

  CObj<Section> & section = sections[name];
  if ( !section )
    section = new Section( name );

  section->Activate( true );

  currentConfigSection = section;
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::ActivateSection( const char * name )
{
  for ( TCommands::iterator it = commands.begin(); it != commands.end(); it++ )
  {
    (*it)->Reset( eventz );
  }

  TSections::iterator it = sections.find( name );
  if ( it != sections.end() )
    it->second->Activate( true );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::DeactivateSection( const char * name )
{
  for ( TCommands::iterator it = commands.begin(); it != commands.end(); it++ )
  {
    (*it)->Reset( eventz );
  }

  TSections::iterator it = sections.find( name );
  if ( it != sections.end() )
    it->second->Activate( false );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::DeactivateAllSections()
{
  for ( TCommands::iterator it = commands.begin(); it != commands.end(); it++ )
  {
    (*it)->Reset( eventz );
  }

  for ( TSections::iterator it = sections.begin(); it != sections.end(); ++it )
    it->second->Activate( false );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::MuteNonDefaultSections( IBaseInterfaceST * owner )
{
  if ( muteOwners.insert( owner ).second )
    UpdateMutiness();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::UnmuteNonDefaultSections( IBaseInterfaceST * owner )
{
  TMuteOwners::iterator it = muteOwners.find( owner );
  if( it != muteOwners.end() )
  {
    muteOwners.erase( it );
    UpdateMutiness();
  }
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Binds::UpdateMutiness()
{
  bool muted = false;

  for( TMuteOwners::iterator it = muteOwners.begin(); it != muteOwners.end(); )
    if( *it )
    {
      muted = true;
      ++it;
    }
    else
    {
      TMuteOwners::iterator next = it;
      ++next;
      muteOwners.erase( it );
      it = next;
    }

  if ( muted && isNonDefaultSectionsMuted )
    return;
  if ( !muted && !isNonDefaultSectionsMuted )
    return;

  isNonDefaultSectionsMuted = muted;

  for ( TSections::iterator it = sections.begin(); it != sections.end(); ++it )
    it->second->Mute( muted );
}

nstl::vector<Event>& Binds::GetEvents()
{
  return eventz;
}

void Binds::ClearEvents()
{
  eventz.clear();
}

void Binds::SetBindStringContext(const wstring& context)
{
  currentBindContext = context;
}

void Binds::RegisterBindString( const wstring& context, const char * name, const vector<wstring> & _paramsSet )
{
  SetBindStringContext(context);
  RegisterBindString(name, _paramsSet);
}

bool Binds::IsBindStringAlreadyRegistered(const nstl::string& bndStr, const wstring& ctx)
{
  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();
  Input::TBinds::const_iterator iter = binds->GetBindStrings().find(ctx);

  if(iter == binds->GetBindStrings().end())
    return false;

  const Input::TBindsEntry& entry = *iter;


  TBindStrings::const_iterator found = nstl::find(entry.second.begin(), entry.second.end(), bndStr);
  return found != entry.second.end();
}

void Binds::RegisterBindString( const char * name, const vector<wstring> & _paramsSet )
{
  nstl::string bindStr( name );
  for ( int i = 0; i < _paramsSet.size(); i++ )
  {
    nstl::string param;
    NStr::ToMBCS( &param, _paramsSet[i] );
    bindStr += " " + param;
  }

  //if(!IsBindStringAlreadyRegistered(bindStr, currentBindContext))
    bindStrings[currentBindContext].push_back( bindStr );
}

void Binds::ClearBindStrings()
{
  bindStrings.clear();
}

const TBinds& Binds::GetBindStrings()
{
  return bindStrings;
}

void Binds::ReplaceString(const wstring& context, const char * name, const vector<wstring> & _paramsSet, int index)
{
  nstl::string bindStr( name );
  for ( int i = 0; i < _paramsSet.size(); i++ )
  {
    nstl::string param;
    NStr::ToMBCS( &param, _paramsSet[i] );
    bindStr += " " + param;
  }

  bindStrings[context].eraseByIndex(index);
  bindStrings[context].insert(bindStrings[context].begin() + index, bindStr);
}

///////////////////////////////////////////////////////////////////////////////

void SaveInputConfig( const string &szFileName, const Input::TBinds& bindStrings, const wstring &ctx )
{
  NFile::CreatePath( NFile::GetFilePath( szFileName ) );

  FILE *pFile = NULL;
#ifdef WIN32	
  if ( fopen_s( &pFile, szFileName.c_str(), "w" ) != 0 )
#else
  if ( (pFile = fopen( szFileName.c_str(), "w" )) != 0 )
#endif

    pFile = NULL;

  if ( pFile == NULL )
  {
    systemLog( NLogg::LEVEL_ASSERT ) << "Can't open " << szFileName << endl;
    return;
  }

  fprintf( pFile, "unbindall\n" );

  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();
  Input::TBinds::const_iterator iter = binds->GetBindStrings().find(ctx);

  //if(iter == bindStrings.end())
  //  iter = bindStrings.find("global");

  if(iter != binds->GetBindStrings().end())
  {
    const Input::TBindsEntry& entry = *iter;

    for ( int i = 0; i < entry.second.size(); i++ )
    {
      fprintf( pFile, "%s\n", entry.second[i].c_str() );
    }
  }

  fclose( pFile );
}

void SaveInputConfig(const string &filePath, const wstring &ctx)
{
  Input::Binds* binds = Input::BindsManager::Instance()->GetBinds();
  if(binds)
  {
    Input::SaveInputConfig( filePath, binds->GetBindStrings(), ctx );
  }
}



} //namespace Input
