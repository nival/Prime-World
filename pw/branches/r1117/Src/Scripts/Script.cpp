////////////////////////////////////////////////////////////////////////////////////////////////////
// This source file is part of the Script (Lua Wrapper) source distribution
// and is Copyright 2000 by Joshua C. Jensen (jjensen@workspacewhiz.com).
// The latest version may be obtained from http://www.workspacewhiz.com/.
//
// The code presented in this file may be freely used and modified for all
// non-commercial and commercial purposes.
////////////////////////////////////////////////////////////////////////////////////////////////////
#include "StdAfx.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include "lua.hpp"
#include "Script.h"
#include "ScriptMacroses.h"
#include "System/FileSystem/FileSystem.h"
#include "System/Crc32Checksum.h"
#include "ScriptLog.h"
#include "NameMap.h"
#include "LuaPreprocessor.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace
{

bool g_writePreprocessedFiles = false;

int StartLuaThreadCallBack( lua_State *pLuaState );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LuaWarning( lua_State *pLuaState )
{
  int paramCount = lua_gettop( pLuaState );
  int luaType = LUA_TNIL;
  for ( int i = 1; i <= paramCount; ++i )
  {
    luaType = lua_type( pLuaState, i );
    if ( luaType == LUA_TNUMBER || luaType == LUA_TSTRING )
    {
      scriptLog( NLogg::LEVEL_ASSERT ) << lua_tostring( pLuaState, i );
    }
  }
  scriptLog( NLogg::LEVEL_ASSERT ) << "" << endl;
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LuaLog( lua_State *pLuaState )
{
  int paramCount = lua_gettop( pLuaState );
  int luaType = LUA_TNIL;
  for ( int i = 1; i <= paramCount; ++i )
  {
    luaType = lua_type( pLuaState, i );
    if ( luaType == LUA_TNUMBER || luaType == LUA_TSTRING )
    {
      scriptLog( NLogg::LEVEL_MESSAGE ) << lua_tostring( pLuaState, i );
    }
  }
  scriptLog( NLogg::LEVEL_MESSAGE ) << "" << endl;
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int LuaInclude( lua_State  *pLuaState )
{
  int luaType = lua_type( pLuaState, -1 );
  if( luaType != LUA_TSTRING )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "LUA Include: invalid parameter" << endl;
    return 0;
  }
  lua_getglobal( pLuaState, "ScriptObject" );
  void* res = lua_touserdata( pLuaState, -1 );
  NScript::Script *pScript = static_cast<NScript::Script*>( res );
  if ( !pScript )
    return 0;

  pScript->DoFile( lua_tostring( pLuaState, -2 ) );

  return 0;
}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScript
{
hash_map<string, lua_CFunction>& GetGlobalRegList()
{
  static hash_map<string, lua_CFunction> GlobalRegList;
  return GlobalRegList;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Script::Script()
  : ownState(false)
  , isInited(false)
  , isReadOnly( true )
  , state(0)
  , calculateCrc(false)
  , crc(0)
{
  Reinit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Script::Script(bool _calculateCrc)
  : ownState(false)
  , isInited(false)
  , isReadOnly( true )
  , state(0)
  , calculateCrc(_calculateCrc)
  , crc(0)
{
  Reinit();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Script::Reinit()
{
  if ( state )
  {
    threads.clear();

    lua_close( state );
  }

  ClearCache();

  state = lua_open();
  ownState = true;
  lua_pushlightuserdata( state, (void*)this );
  lua_setglobal( state, "ScriptObject" );

  lua_getuserdata( state )->pScript = (void*)this;
  lua_getuserdata( state )->pContext = 0;

  luaopen_base( state );
  luaopen_math( state );
  luaopen_string( state );
#ifndef _SHIPPING
  luaopen_debug( state );
#endif
  

  lua_gc( state, LUA_GCSETPAUSE, 50 );
  isInited = false;

  GetScriptLog().SetHeaderFormat( NLogg::EHeaderFormat::Severity );
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Script::RegisterGlobals()
{
  if (isInited)
    return;

  lua_pushcfunction( state, LuaLog );
  lua_setglobal ( state, "clog" );

  lua_pushcfunction( state, LuaWarning );
  lua_setglobal ( state, "warning" );

  lua_pushcfunction( state, StartLuaThreadCallBack );
  lua_setglobal ( state, "StartThread" );

  lua_pushcfunction( state, LuaInclude );
  lua_setglobal ( state, "include" );

  for (hash_map<string, lua_CFunction>::iterator it = GetGlobalRegList().begin(); it != GetGlobalRegList().end(); ++it)
  {
    lua_pushcfunction( state, it->second );
    lua_setglobal ( state, it->first.c_str() );
  }
  for (hash_map<string, lua_CFunction>::iterator it = RegList.begin(); it != RegList.end(); ++it)
  {
    lua_pushcfunction( state, it->second );
    lua_setglobal ( state, it->first.c_str() );
  }
  isInited = true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool Script::StartThread(  lua_State* pParentState, int numberOfArguments )
{
  Thread* pThread = lua_newthread( GetState() );
  NI_VERIFY( pThread, "Invalid created lua thread!", return false; );

  // register reference to avoid GC clean
  const int threadReference = lua_ref( GetState(), true );

  // push main function and parameters on stack
  lua_xmove( pParentState, pThread, numberOfArguments );

  // first run
  const int result = lua_resume( pThread, numberOfArguments - 1 );

  // error check
  if ( result != LUA_YIELD && result != 0 )
  {
    luaD_seterrorobj( pThread, result, pThread->top );
    scriptLog( NLogg::LEVEL_ASSERT ) << "Script error: " << lua_tostring( pThread, -1 ) << endl;
  }

  if( result != LUA_YIELD )
  {
    lua_unref( GetState(), threadReference );
    return result == 0;
  }
  else
  {
    const int numberOfArguments = pThread->top - pThread->ci->base;
    NI_ASSERT( numberOfArguments >= 0, "Invalid number of arguments!" );
    const ThreadInfo info( pThread, threadReference, numberOfArguments );
    threads.push_back( info );
    return true;
  }		
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Script::ThreadContainer::iterator Script::UnRegisterLuaThread( const ThreadContainer::iterator& it )
{
  if( it != threads.end() )
    lua_unref( GetState(), it->luaRef );
  return threads.erase( it );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Script::StepLuaThreads()
{
  ThreadContainer::iterator it = threads.begin();
  ThreadContainer::iterator itEnd = threads.end();

  for(; it != itEnd; )
  {
    Thread* pThread = it->pThread;
    const int numberOfArguments = it->numberOfArguments;
    const int result = lua_resume( pThread , numberOfArguments );
    if ( result != LUA_YIELD && result != 0 )
    {
      string msg = lua_tostring( pThread, -1 );
      scriptLog( NLogg::LEVEL_ASSERT ) << "Script error: " << msg << endl;
    }

    if( result != LUA_YIELD )
      it = UnRegisterLuaThread( it );
    else
    {
      // store number of returned arguments
      const int numberOfArguments = static_cast<int>( pThread->top - pThread->ci->base );
      NI_ASSERT( numberOfArguments >= 0, "Invalid number of arguments!" );
      it->numberOfArguments = numberOfArguments;				
      ++it;
    }
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Script::DoString( const string& str )					
{ 
  int ret = luaL_dostring( state, str.c_str() );
  if ( ret != 0 )
  {
    string msg = lua_tostring( state, -1 );
    systemLog( NLogg::LEVEL_ASSERT ) << "LUA Include: error loading file " << str << ": " << msg << endl;
  }
  return ret;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int Script::DoFile( const string& str )
{
  if( str.empty() || loadedFiles[ str ] )
    return 0;

  CObj<Stream> pStream = RootFileSystem::OpenFile( str, FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
  if ( pStream )
  {
    loadedFiles.insert( str );
    scriptLog( NLogg::LEVEL_MESSAGE ) << "LUA Include: file loaded: " << str << endl;

    string scriptData;
    Lua::LuaPreprocessor::Instance().Preprocess(scriptData, pStream->GetBuffer(), pStream->GetSize());
    if(g_writePreprocessedFiles)
    {
      CObj<Stream> pDump = new FileStream(NFile::GetBaseDir() + "Data/" + str + ".preprocessed", FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
      if( pDump && pDump->IsOk() )
      {
        pDump->WriteString(scriptData);
      }
      else
      {
        NI_ALWAYS_ASSERT("Can`t write preprocessed file!");
      }
    }

    if (calculateCrc)
    {
      Crc32Checksum scriptCrc;
      crc ^= scriptCrc.AddString( scriptData.c_str() ).Get();
    }

    int ret = luaL_loadbuffer(state, scriptData.c_str(), scriptData.size(), str.c_str()) || lua_pcall(state, 0, LUA_MULTRET, 0);
    if ( ret != 0 )
    {
      string msg = lua_tostring( state, -1 );
      NI_ALWAYS_ASSERT( NStr::StrFmt(  "LUA Include: error loading file %s: %s", str.c_str(), msg.c_str() ) );
    }
    return 0;
  }

  NI_ALWAYS_ASSERT( NStr::StrFmt(  "LUA Include: file not found: %s", str.c_str() ) );
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Script::~Script()
{
  if (ownState)
    lua_close(state);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddSFunctionToGlobals( const char *fname, lua_CFunction Func )
{
	GetGlobalRegList()[fname] = Func;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NScript::Script *GetScript( lua_State *pLuaState )
{
  return static_cast<NScript::Script*>( lua_getuserdata( pLuaState )->pScript );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace
{
/** CallBack to start new Lua thread */
int StartLuaThreadCallBack( lua_State *pLuaState )
{
  NScript::Script* scriptMashine = NScript::GetScript( pLuaState );
  if ( !scriptMashine )
  {
    lua_pushstring( pLuaState, "Can't get Script Object!" );
    return 1;
  }

  // check: is first function parameter on stack function?
  const int stackIndex = static_cast<int>( pLuaState->top - pLuaState->ci->base );
  if ( !lua_isfunction( pLuaState, -stackIndex ) )
  {
    lua_pushstring( pLuaState, "To start thread you have to pass function as first argument!" );
    return 1;
  }

  if( !scriptMashine->StartThread( pLuaState, stackIndex ) )
  {
    lua_pushstring( pLuaState, "Can't create new thread and call function!" );
    return 1;
  }	
  return 0;
}
}

REGISTER_DEV_VAR("lua_writePreprocessedFiles", g_writePreprocessedFiles, STORAGE_USER);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
