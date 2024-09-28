#include "stdafx.h"

#include "LuaEventResult.h"
#include "../Scripts/lua.hpp"


namespace Lua
{

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
UI::EEventResult::Enum lua_values< UI::EEventResult::Enum >::get( lua_State * L, int idx )
{
  if( !CheckStackParameterIdx( L, idx ) )
    return UI::EEventResult::Unhandled;
  const int type = lua_type( L, idx );
  if( type == LUA_TNIL )
    return UI::EEventResult::Unhandled;
  return lua_toboolean( L, idx ) ? UI::EEventResult::Processed : UI::EEventResult::Skipped;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int lua_values< UI::EEventResult::Enum >::put( lua_State * L, UI::EEventResult::Enum value )
{
  switch( value )
  {
    case UI::EEventResult::Skipped:
      lua_pushboolean( L, false );
      break;
    case UI::EEventResult::Processed:
      lua_pushboolean( L, true );
      break;
    default:
    case UI::EEventResult::Unhandled:
      lua_pushnil( L );
      break;
  }
  return 1;
}

} //namespace Lua
