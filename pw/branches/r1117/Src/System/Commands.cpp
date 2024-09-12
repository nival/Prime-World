#include "stdafx.h"

#include "Commands.h"
#include "StrProc.h"

#ifdef WIN32
  #include <shellapi.h>
#endif

#include <System/ported/cwfn.h>

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static vector<wstring> commandsHistory;

int     NGlobal::g_commandLineArgc = 0;
char **NGlobal::g_commandLineArgv = NULL;


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// aliases
typedef hash_map<string, wstring> TAliases;
static TAliases g_aliases;


#ifndef WIN32
float _wtof( const wchar_t *str)
{
  float ret = 0.0f;
  swscanf(str, L"%f", &ret);
  return ret;
}
#endif

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool AddAlias( const string &szAliasName, const wstring &wszCommand )
{
	if ( g_aliases.find( szAliasName ) != g_aliases.end() )
		return false;
	g_aliases[szAliasName] = wszCommand;
	return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const wstring &GetAlias( const string &szAliasName )
{
	TAliases::const_iterator pos = g_aliases.find( szAliasName );
	if ( pos != g_aliases.end() )
		return pos->second;

	static wstring WSZ_EMPTY;
	return WSZ_EMPTY;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CRecordInfo
{
	NGlobal::VariantValue defValue;
	NGlobal::TCmdHandler pCmdHandler;
  NGlobal::TCmdHandlerEx pCmdHandlerEx;
  CObj<NGlobal::IVariable> pVariable;
  CObj<NGlobal::IContextFunctor> pContextCmdFunctor;
	EStorageClass storage;

	static EStorageClass defStorage;
public:
	CRecordInfo(): pCmdHandler( 0 ), pCmdHandlerEx(0), pContextCmdFunctor( 0 ), storage( STORAGE_NONE ) {}
	CRecordInfo( NGlobal::TCmdHandler _pCmd ) : pCmdHandler( _pCmd ), pCmdHandlerEx(0), pContextCmdFunctor( 0 ), storage( STORAGE_NONE ) {}
  CRecordInfo( NGlobal::TCmdHandlerEx _pCmd ) : pCmdHandlerEx( _pCmd ), pCmdHandler( 0 ), pContextCmdFunctor( 0 ), storage( STORAGE_NONE ) {}
  CRecordInfo( NGlobal::IContextFunctor* _pContextCmdFunctor ) : pCmdHandler( 0 ), pCmdHandlerEx(0), pContextCmdFunctor( _pContextCmdFunctor ), storage( STORAGE_NONE ) {}
	CRecordInfo( CObj<NGlobal::IVariable> pVariable, const EStorageClass _storage )
		: defValue( pVariable->Get() ), pCmdHandler(0), pVariable(pVariable),  pContextCmdFunctor( 0 ), pCmdHandlerEx(0)
	{
		if ( _storage == STORAGE_DONT_CARE && defStorage == STORAGE_DONT_CARE )
			storage = STORAGE_NONE;
		else if ( _storage == STORAGE_DONT_CARE )
			storage = defStorage;
		else
			storage = _storage;
	}

	const NGlobal::VariantValue GetValue() const 
	{ 
	  NI_ASSERT( pVariable != 0, "Commands initialization error" );
	  return pVariable->Get(); 
	}
	
	void SetValue( const NGlobal::VariantValue &_value )
	{
		NI_ASSERT( pVariable != 0, "Commands initialization error" );
		pVariable->Set(_value);
	}
	
	bool VerifyValue( const NGlobal::VariantValue &_value ) const
	{
	  NI_ASSERT( pVariable != 0, "Commands initialization error" );
		return pVariable->VerifyValue(_value);
	}
	
	void Reset()
	{
		SetValue( defValue );
	}
	
	void Apply()
	{
    NI_ASSERT( pVariable != 0, "Commands initialization error" );
    pVariable->Apply();
	}
 
  bool CanExecuteContextCmd() const { return pContextCmdFunctor; }
	bool CanExecute() const { return pCmdHandler || pContextCmdFunctor; }
  bool CanExecuteEx() const { return pCmdHandlerEx; }

  bool Execute( const char *name, const vector<wstring> &params  )
	{
    if ( pContextCmdFunctor )
      return (*pContextCmdFunctor)( name, params );

		if ( pCmdHandler )
			return pCmdHandler( name, params );
    
    return true;
	}

  bool Execute( const char *name, const vector<wstring> &params, const wstring &ctx )
  {
    if ( pCmdHandlerEx )
      return pCmdHandlerEx( name, params, ctx );

    return true;
  }

	bool CheckStorage( const EStorageClass _storage ) const { return storage == _storage; }

  const char* GetStorageName() const
  {
    switch( storage )
    {
    case STORAGE_DONT_CARE:
      return "STORAGE_DONT_CARE";
    case STORAGE_NONE:
      return "STORAGE_NONE";
    case STORAGE_GLOBAL:
      return "STORAGE_GLOBAL";
    case STORAGE_USER:
      return "STORAGE_USER";
    case STORAGE_PLAYER:
      return "STORAGE_PLAYER";
    case STORAGE_SAVE:
      return "STORAGE_SAVE";
    default:
      return "";
    }
  }

	static void SetDefaultStorage( const EStorageClass _storage ) { defStorage = _storage; }
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
EStorageClass CRecordInfo::defStorage;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
typedef hash_map<string, CRecordInfo> TRecords;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
TRecords &GetRecords()
{
	static TRecords records;
	return records;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void _PrintVarWithValue( TRecords::const_iterator itValue )
{
  if ( itValue->second.CanExecute() )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << itValue->first << " (command)" << endl;
  }
  else
  {
    const NGlobal::VariantValue &value = NGlobal::GetVar( itValue->first, NGlobal::VariantValue() );
    systemLog( NLogg::LEVEL_MESSAGE ) << itValue->first << " (" << itValue->second.GetStorageName() 
              << ") = \"" << value.GetString() << "\" (" << value.GetFloat() << ")" << endl;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NGlobal
{

bool VariantValue::IsConvertibleImpl( Type toType, const VariantValue &from )
{
  if( from.type != STRING || from.type == toType ) 
    return true;
    
  switch(toType)
  {
    case FLOAT:
    {
      wchar_t *endptr;
      const double rez = wcstod( from.szVal.c_str(), &endptr );
      
      return endptr == from.szVal.c_str() + from.szVal.size() && 
             rez > -FLT_MAX && rez < FLT_MAX;
    }     
    case INT:   
    {
      wchar_t *endptr;
      const __int64 rez = _wcstoi64( from.szVal.c_str(), &endptr, 10 );
      
      return endptr == from.szVal.c_str() + from.szVal.size() && 
             rez > _I64_MIN && rez < _I64_MAX;
    }    
    case UINT:  
    {
      wchar_t *endptr;
      const __int64 rez = _wcstoui64( from.szVal.c_str(), &endptr, 10 );
      
      return endptr == from.szVal.c_str() + from.szVal.size() && 
             rez < _UI64_MAX;
    }
    default:
      return false;
  } 
} 
 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const wstring &GetCommandHistory( int &index )
{
	if ( index < 0 )
		index = 0;
	if ( index >= commandsHistory.size() - 1 )
		index = commandsHistory.size() - 1;
	int _index = commandsHistory.size() - index - 1;
	return commandsHistory[_index];
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SaveCommand( const wstring &command )
{
	commandsHistory.push_back( command );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SaveCommand( const wstring &command, vector<wstring> &parameters )
{
	wstring cmd(command);
	vector<wstring>::iterator it = parameters.begin();
	vector<wstring>::iterator end = parameters.end();
	for ( ; it != end ; ++it )
		cmd += L" " + *it;
	commandsHistory.push_back( cmd );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RegisterCmd( const string &szID, TCmdHandler pHandler )
{
	if ( GetRecords().find( szID ) != GetRecords().end() )
		return false; 

	GetRecords()[szID] = CRecordInfo( pHandler );
	return true;
}

bool RegisterCmdEx( const string &szID, TCmdHandlerEx pHandler )
{
  if ( GetRecords().find( szID ) != GetRecords().end() )
    return false; 

  GetRecords()[szID] = CRecordInfo( pHandler );
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RegisterContextFunctor( const string &szID, IContextFunctor* _functor )
{
  if ( GetRecords().find( szID ) != GetRecords().end() )
    return false;

  GetRecords()[szID] = CRecordInfo( _functor );
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool UnregisterCmd( const string &szID )
{
  TRecords::iterator it = GetRecords().find( szID );

  if ( it == GetRecords().end() )
    return false;

  GetRecords().erase( szID );
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RegisterVar( const string &szID, CObj<IVariable> pVar, EStorageClass storage )
{
	NI_VERIFY( storage != STORAGE_DONT_CARE, NI_STRFMT( "Cannot register new variable %s with STORAGE_DONT_CARE", szID.c_str() ), return false );
	NI_VERIFY( GetRecords().find( szID ) == GetRecords().end(), NI_STRFMT( "Variable %s already registred", szID.c_str() ), return false );

	GetRecords()[szID] = CRecordInfo( pVar, storage );
	return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool UnregisterVar( const string &szID )
{
  return GetRecords().erase( szID ) > 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool CompareVariablesByName( const VariantVariable &s1, const VariantVariable &s2 )
{
	return s1.GetName() < s2.GetName();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int GetVarsByStorage( vector<VariantVariable> *pVariables, const EStorageClass storage )
{
	int nCount = 0;
	for( TRecords::const_iterator it = GetRecords().begin(); it != GetRecords().end(); ++it )
	{
		if ( storage == STORAGE_DONT_CARE || it->second.CheckStorage( storage ) )
		{
			++nCount;
			if ( pVariables )
				pVariables->push_back( VariantVariable( it->first, it->second.GetValue() ) );
		}
	}

	if ( pVariables )
		sort( pVariables->begin(), pVariables->end(), CompareVariablesByName );

	return nCount;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const VariantValue GetVar( const string &szID, const VariantValue &defValue )
{
	TRecords::const_iterator pos = GetRecords().find( szID );
	if ( pos == GetRecords().end() )
		return defValue;

	return pos->second.GetValue();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsCommand( const string &szName )
{
	TRecords::const_iterator pos = GetRecords().find( szName );
	if ( pos == GetRecords().end() )
		return true;

	return pos->second.CanExecute();
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsCommandRegistred( const string &szName )
{
  return ( GetRecords().find( szName ) != GetRecords().end() );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class DummyVariable: public IVariable, public CObjectBase
{
  OBJECT_BASIC_METHODS( DummyVariable );
public:
  DummyVariable() {}
  explicit DummyVariable(const VariantValue &var): var(var) {}
  virtual VariantValue Get() { return var; }
  virtual void Set( const VariantValue &val ){ var = val; }

private:
  VariantValue var;            
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SetVar( const string &szID, const VariantValue &value, const EStorageClass newStorage )
{
	TRecords::iterator pos = GetRecords().find( szID );
	if ( pos == GetRecords().end() )
	{
    systemLog( NLogg::LEVEL_MESSAGE ) << "Value '" << szID << "' is not registered";
    
    if ( !RegisterVar( szID, new DummyVariable(value), newStorage ) )
		  return;

		pos = GetRecords().find( szID );
	}

  if( !pos->second.VerifyValue(value) )
  {
    systemLog( NLogg::LEVEL_ERROR ) << "setvar error: " << szID << " value '" << value.GetString() << "' cannot be verified";
    return;
  }

	pos->second.SetValue( value );
  systemLog( NLogg::LEVEL_MESSAGE ) << "setvar " << szID << " = \"" << pos->second.GetValue().GetString() << "\"";
}
////////////////////////////////////////////////////////////////////////////////////////////////////
void ResetVars( const EStorageClass storage )
{
	for( TRecords::iterator it = GetRecords().begin(); it != GetRecords().end(); ++it )
	{
		if ( storage == STORAGE_DONT_CARE || it->second.CheckStorage( storage ) )
			it->second.Reset();
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void SplitCommandToWords( vector<wstring> *pWords, const wstring &wszCommand )
{
	pWords->clear();
	bool bCommentFound = false;
	for ( NStr::CStringIterator<wchar_t, const wstring&, NStr::CBracketMulticharSeparator<wchar_t, NStr::SQuoteTest<wchar_t> > > it( wszCommand, ' ' ); !it.IsEnd() && !bCommentFound; it.Next() )
	{
		if ( !it.Get().empty() )
		{
			if ( it.Get().compare( 0, 2, L"//" ) == 0 )
				bCommentFound = true;
			else
				pWords->push_back( it.Get() );
		}
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void RemoveQuotes( vector<wstring> *pWords )
{
	for ( vector<wstring>::iterator it = pWords->begin(); it != pWords->end(); ++it )
	{
		if ( it->size() > 2 && (*it)[0] == L'\"' && (*it)[it->size() - 1] == L'\"' )
			*it = it->substr( 1, it->size() - 2 );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static void RunDefaultHandler( const string &szID, const vector<wstring> &params )
{
	if ( params.empty() )
	{
		const NGlobal::VariantValue &value = GetVar( szID, VariantValue() );
		systemLog( NLogg::LEVEL_MESSAGE ) << szID << " = \"" << value.GetString() << "\" (" << value.GetFloat() << ")" << endl;
	}
	else
		SetVar( szID, VariantValue( params.front() ), STORAGE_DONT_CARE );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RunCommand( const string &command, const vector<wstring> &args, const wstring &context )
{
	TRecords::iterator pos = GetRecords().find( command );
	if ( pos == GetRecords().end() )
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << "Unknown command or variable \"" << command << "\"" << endl;
		systemLog( NLogg::LEVEL_MESSAGE ) << "Type 'help' to list available commands" << endl;
		return true;
	}

	if ( pos->second.CanExecute() )
		return pos->second.Execute( pos->first.c_str(), args);
  else if(pos->second.CanExecuteEx())
    return pos->second.Execute( pos->first.c_str(), args, context );
	else
		RunDefaultHandler( command, args );

  return true;
}

#pragma warning(disable:4530)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool RunCommand( const wstring &commandLine, const wstring &ctx )
{
	vector<wstring> words;
	SplitCommandToWords( &words, commandLine );

  string szCommandName = "";

  //TODO
  try
  {
    if ( words.empty() )
      return true;

    SaveCommand( commandLine );

    szCommandName = NStr::ToMBCS( *words.begin() );
    words.erase( words.begin() );
  }
  catch (...)
  {
    NI_ALWAYS_ASSERT( NStr::ToMBCS( commandLine ).c_str() );
  }

	wstring aliasCommand = GetAlias( szCommandName );
	if ( !aliasCommand.empty() )
	{
		for ( vector<wstring>::const_iterator it = words.begin(); it != words.end(); ++it )
			aliasCommand != L" " + *it;

		return RunCommand( aliasCommand, ctx);
	}

	RemoveQuotes( &words );
	return RunCommand( szCommandName, words, ctx );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MatchCommands( vector<wstring> *pRes, const wstring &match )
{
	NI_VERIFY( pRes, "No output value", return );
	if ( match.empty() )
		return;

	wstring wsTemp;
	for ( TRecords::const_iterator it = GetRecords().begin(); it != GetRecords().end(); ++it )
	{
			const string& sTemp = it->first;
			NStr::ToUnicode( &wsTemp, sTemp );

			if ( wsTemp.length() < match.length() )
				continue;

			if ( match == wsTemp.substr( 0, match.length() ) )
				pRes->push_back( wsTemp );
	}
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintVarWithValue( const string &szName )
{
	TRecords::const_iterator pos = GetRecords().find( szName );
	if ( pos == GetRecords().end() )
		return;

	_PrintVarWithValue(pos);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PrintVarsWithValueByPrefix( const string &szPrefix )
{
  if (szPrefix.empty())
    return;

  TRecords::const_iterator it = GetRecords().begin();
  TRecords::const_iterator itEnd = GetRecords().end();
  const int prefixSize = szPrefix.size();

  for (; it != itEnd; ++it)
  {
    if (!it->first.compare( 0, prefixSize,  szPrefix ))
    {
      _PrintVarWithValue(it);
    }
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace NGlobal

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool CommandAlias( const char *name, const vector<wstring> &params ) 
{
	if ( params.size() < 3 || params[1].compare( L"=" ) != 0 )
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " <alias> = <command>" << endl;
		return true;
	}

	const string szAliasName = NStr::ToMBCS( params[0] );
	wstring wszCommand = params[2];
	for ( int i = 3; i < params.size(); ++i )
		wszCommand = wszCommand + L" " + params[i];

	if ( !AddAlias( szAliasName, wszCommand ) )
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << "alias " << szAliasName << " already exist" << endl;		
	}

  return true;
}



static bool CommandSetVar( const char *name, const vector<wstring> &params ) 
{
  if ( params.size() == 2 )
  {
    if ( params[1] == L"=" )
      NGlobal::SetVar( NStr::ToMBCS( params[0] ), NGlobal::VariantValue( L"" ), STORAGE_NONE );
    else
      NGlobal::SetVar( NStr::ToMBCS( params[0] ), NGlobal::VariantValue( params[1] ), STORAGE_NONE );
  }
  else if ( params.size() == 3 && ( params[1] == L"=" ) )
  {
    NGlobal::SetVar( NStr::ToMBCS( params[0] ), NGlobal::VariantValue( params[2] ), STORAGE_NONE );
  }
  else
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " setvar <name> = <value>";
  }

  return true;
}



static bool CommandHelp( const char *name, const vector<wstring> &) 
{
	vector<string> commands, vars;
	for ( TRecords::const_iterator it = GetRecords().begin(); it != GetRecords().end(); ++it )
	{
		if ( it->second.CanExecute() )
			commands.push_back( it->first );
		else
			vars.push_back( it->first );
	}

	sort( commands.begin(), commands.end() );
	sort( vars.begin(), vars.end() );

	systemLog( NLogg::LEVEL_MESSAGE ) << "Available commands:" << endl;

	for ( vector<string>::const_iterator it = commands.begin(); it != commands.end(); ++it )
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << "    " << (*it) << endl;
	}
	systemLog( NLogg::LEVEL_MESSAGE ) << "Available variables:" << endl;

	for ( vector<string>::const_iterator it = vars.begin(); it != vars.end(); ++it )
	{
		NGlobal::PrintVarWithValue( *it );
	}
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef WIN32

static wchar_t ** _BuildCommandLine(int *numArgs)
{
  int     i, j, l;
  wchar_t **argList;
  
  *numArgs = NGlobal::g_commandLineArgc;
  
  argList = (wchar_t **)malloc( NGlobal::g_commandLineArgc * sizeof(wchar_t*) );
  
  for (i = 0; i < NGlobal::g_commandLineArgc; i++)
  {
    l = strlen(NGlobal::g_commandLineArgv[i]);
    argList[i] = (wchar_t*)malloc( l + 2);
    for (j = 9; j < l ; j++)
    {
      argList[i][j] = (wchar_t)NGlobal::g_commandLineArgv[i][j];
    }
    argList[i][j] = 0;
  }
  return argList;
}

#endif

namespace detail {

	struct CommandInfo {
		string command;
		vector< wstring > args;
	};

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static bool CommandLine( const char * /*name*/ , const vector<wstring> &params ) 
{
	// prevent multiple launch this command
	static bool executed = false;
	if( executed )
		return true;

	executed = true;

  const wstring COMMAND_SEPARATOR = L";";
  const wstring COMMAND_CONTEXT = L"commandline";

  vector< detail::CommandInfo > commands;
	int nArgs;

#ifdef WIN32
	wchar_t **argsList = CommandLineToArgvW( GetCommandLineW(), &nArgs );
#else
  wchar_t **argsList = _BuildCommandLine( &nArgs );
#endif	
	if( argsList == NULL )
	{
		systemLog( NLogg::LEVEL_MESSAGE ) << "CommandLineToArgvW failed!" << endl;
		return true;
	}

  int currentArg = 1;

  //Skip normal command line arguments
  while( ( currentArg < nArgs ) )
    if ( argsList[currentArg] && argsList[currentArg][0] == L'-' )
      ++currentArg;
    else
      break;

  if ( currentArg < nArgs )
  {
    while ( currentArg < nArgs )
    { 
      // Use commands from commandLine
      detail::CommandInfo info;
      info.command = NStr::ToMBCS( argsList[ currentArg++ ] );
      for ( ; currentArg < nArgs; ++currentArg )
      {
        wstring arg = argsList[currentArg];
        if ( arg == COMMAND_SEPARATOR )
        {
          ++currentArg;
          break;
        }
        info.args.push_back( arg );
      }
      commands.push_back( info );
    }
  }
  else if (params.size() >= 1)
  {
    // Use params
    detail::CommandInfo info;
    info.command = NStr::ToMBCS( params[0] );
    for( int i = 1; i < params.size(); ++i )
      info.args.push_back( params[i] );
    commands.push_back( info );
  }
  else
  {
    // nothing to do
    return true;
  }

#ifdef WIN32	
	LocalFree(argsList);
#else
  free(argsList);
#endif	

  for ( int i = 0; i < commands.size(); ++i )
  {
    NGlobal::SaveCommand( NStr::ToUnicode( commands[i].command ), commands[i].args );
    NGlobal::RunCommand( commands[i].command, commands[i].args, COMMAND_CONTEXT );
  }

  return true;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool ApplyVariable( const char *name, const vector<wstring> &params )
{
  if ( params.size() != 1 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "usage: " << name << " <variable name>" << endl;
    return false;
  }
  
  const string varName = NStr::ToMBCS(params[0]);
  TRecords::iterator pos = GetRecords().find( varName );
  
  if ( pos == GetRecords().end() )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "variable: " << varName << "not found" << endl;
    return false; 
  }

  pos->second.Apply();

  return true;
} 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static bool DoNothingCommand( const char *, const vector<wstring> & )
{
  return true;
} 

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_CMD( alias, CommandAlias )
REGISTER_CMD( setvar, CommandSetVar )
REGISTER_CMD( help, CommandHelp )
REGISTER_CMD( command_line, CommandLine )
REGISTER_CMD( apply_variable, ApplyVariable )
REGISTER_CMD( do_nothing, DoNothingCommand )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
