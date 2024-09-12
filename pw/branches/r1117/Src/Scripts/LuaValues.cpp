#include "stdafx.h"
#include "LuaValues.h"

#include "lua.hpp"

namespace Lua
{
  bool CheckStackParameterIdx(lua_State *L, int idx)
  {
    if(lua_gettop(L) >= idx)
      return true;

    systemLog( NLogg::LEVEL_ASSERT ) << "Lua function parameter " << idx << " is not specified! Using default" << endl;
    return false;
  }

  double lua_values<double>::get(lua_State *L, int idx)
  {
    return CheckStackParameterIdx(L, idx)? lua_tonumber(L, idx): 0.0;
  }

  int lua_values<double>::put(lua_State *L, double value)
  {
    lua_pushnumber(L, value);
    return 1;
  }

  float lua_values<float>::get(lua_State *L, int idx)
  {
    return CheckStackParameterIdx(L, idx)? static_cast<float>(lua_tonumber(L, idx)) : 0.0f;
  }

  int lua_values<float>::put(lua_State *L, float value)
  {
    lua_pushnumber(L,value);
    return 1;
  }

  bool lua_values<bool>::get(lua_State *L, int idx)
  {
    return CheckStackParameterIdx(L, idx)? !!lua_toboolean(L, idx) : false;
  }

  int lua_values<bool>::put(lua_State *L, bool value)
  {
    lua_pushboolean(L,value);
    return 1;
  }

  int lua_values<int>::get(lua_State *L, int idx)
  {
    return CheckStackParameterIdx(L, idx)? static_cast<int>(lua_tonumber(L, idx)) : false;
  }

  int lua_values<int>::put(lua_State *L, int value)
  {
    lua_pushnumber(L,static_cast<double>(value));
    return 1;
  }

  uint lua_values<uint>::get(lua_State *L, int idx)
  {
    return CheckStackParameterIdx(L, idx)? static_cast<uint>(lua_tonumber(L, idx)) : false;
  }

  int lua_values<uint>::put(lua_State *L, uint value)
  {
    lua_pushnumber(L,static_cast<double>(value));
    return 1;
  }

  char lua_values<char>::get(lua_State *L, int idx)
  {
    return CheckStackParameterIdx(L, idx)? static_cast<char>(lua_tonumber(L, idx)) : false;
  }

  int lua_values<char>::put(lua_State *L, char value)
  {
    lua_pushnumber(L,static_cast<double>(value));
    return 1;
  }

  short lua_values<short>::get(lua_State *L, int idx)
  {
    return CheckStackParameterIdx(L, idx)? static_cast<short>(lua_tonumber(L, idx)): false;
  }

  int lua_values<short>::put(lua_State *L, short value)
  {
    lua_pushnumber(L,static_cast<double>(value));
    return 1;
  }

  const char* lua_values<const char*>::get(lua_State *L, int idx)
  {
    return CheckStackParameterIdx(L, idx)? lua_tostring(L, idx) : "";
  }

  int lua_values<const char*>::put(lua_State *L, const char* value)
  {
    lua_pushstring(L,value);
    return 1;
  }

  string lua_values<string const&>::get(lua_State *L, int idx)
  {
    if(!CheckStackParameterIdx(L, idx))
      return string();

    if(const char* str = lua_tostring(L, idx))
      return string(str);

    systemLog( NLogg::LEVEL_ASSERT ) << "Lua: Failed to convert function parameter #" << idx << "  to a string" << endl;
    return string();
  }

  string lua_values<string>::get(lua_State *L, int idx)
  {
    return lua_values<string const&>::get(L, idx);
  }

  int lua_values<string const&>::put(lua_State *L, string const& value)
  {
    lua_pushstring(L, value.c_str());
    return 1;
  }

  int lua_values<string>::put(lua_State *L, string const& value)
  {
    lua_pushstring(L, value.c_str());
    return 1;
  };

} // namespace Lua