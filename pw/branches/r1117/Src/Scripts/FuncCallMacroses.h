#pragma once

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CALL_LUA_FUNCTION_ON_STACK( state, nargs, nresults )                                                                 \
if ( lua_pcall( state, nargs, nresults, 0 ) )                                                                                \
{                                                                                                                            \
  const char* err = lua_tostring( L, -1 );                                                                                   \
  NI_ALWAYS_ASSERT( NStr::StrFmt( "Lua error: %s", err ) )                                                                   \
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CALL_LUA_FUNCTION_START( script, function, assert )                                                                 \
{                                                                                                                            \
  lua_State * L = script->GetState();                                                                                        \
  lua_getglobal( L, function );                                                                                              \
  if ( !lua_isfunction( L, -1 ) )                                                                                            \
  {                                                                                                                          \
    if (assert)                                                                                                              \
      NI_ALWAYS_ASSERT( NStr::StrFmt( "Failed to get function \"%s\" from the script", function ) )                          \
    lua_remove( L, -1 );                                                                                                     \
  }                                                                                                                          \
  else                                                                                                                       \
  {

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _CALL_LUA_FUNCTION_END( nargs )                                                                                      \
    CALL_LUA_FUNCTION_ON_STACK( L, nargs, 0 )                                                                                \
  }                                                                                                                          \
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _SET_LUA_ARG( arg )                                                                                                  \
luaValueSetter::Set( L, arg );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CALL_LUA_FUNCTION( script, function, assert )                                                                      \
_CALL_LUA_FUNCTION_START( script, function, assert )                                                                       \
_CALL_LUA_FUNCTION_END( 0 )                                                                                                \

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CALL_LUA_FUNCTION_ARG1( script, function, assert, arg1 )                                                           \
_CALL_LUA_FUNCTION_START( script, function, assert )                                                                       \
  _SET_LUA_ARG( arg1 )                                                                                                     \
_CALL_LUA_FUNCTION_END( 1 )                                                                                                \

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CALL_LUA_FUNCTION_ARG2( script, function, assert, arg1, arg2 )                                                     \
_CALL_LUA_FUNCTION_START( script, function, assert )                                                                       \
  _SET_LUA_ARG( arg1 )                                                                                                     \
  _SET_LUA_ARG( arg2 )                                                                                                     \
_CALL_LUA_FUNCTION_END( 2 )                                                                                                \

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CALL_LUA_FUNCTION_ARG3( script, function, assert, arg1, arg2, arg3 )                                               \
_CALL_LUA_FUNCTION_START( script, function, assert )                                                                       \
  _SET_LUA_ARG( arg1 )                                                                                                     \
  _SET_LUA_ARG( arg2 )                                                                                                     \
  _SET_LUA_ARG( arg3 )                                                                                                     \
_CALL_LUA_FUNCTION_END( 3 )                                                                                                \

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define CALL_LUA_FUNCTION_ARG4( script, function, assert, arg1, arg2, arg3, arg4 )                                         \
_CALL_LUA_FUNCTION_START( script, function, assert )                                                                       \
  _SET_LUA_ARG( arg1 )                                                                                                     \
  _SET_LUA_ARG( arg2 )                                                                                                     \
  _SET_LUA_ARG( arg3 )                                                                                                     \
  _SET_LUA_ARG( arg4 )                                                                                                     \
_CALL_LUA_FUNCTION_END( 4 )                                                                                                \

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// This macro expects args as vector of wstrings, where first cell contains function's name
#define CALL_LUA_FUNCTION_ARGS_WS( script, assert, args )                                                                \
_CALL_LUA_FUNCTION_START( script, NStr::ToMBCS(args[0]).c_str(), assert )                                                \
for ( int i = 1; i < args.size(); ++i )                                                                                  \
{                                                                                                                        \
  _SET_LUA_ARG( NStr::ToMBCS(args[i]) )                                                                                  \
}                                                                                                                        \
_CALL_LUA_FUNCTION_END( args.size() - 1 )                                                                                \

