#pragma once

struct lua_State;

struct ILuaValueSettable
{
  virtual int Set( lua_State *L ) const = 0;
};

#define LUA_VALUE_SETTABLE_DECLARE \
  virtual int Set( lua_State *L ) const;
