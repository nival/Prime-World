#pragma once

struct lua_State;

namespace Lua
{
  bool CheckStackParameterIdx(lua_State *L, int idx);

  template<class T> struct lua_values;

  template<> struct lua_values<double>
  {
    static double      get(lua_State *L, int idx);
    static int         put(lua_State *L, double value);
  };
  
  template<> struct lua_values<float>
  {
    static float       get(lua_State *L, int idx);
    static int         put(lua_State *L, float value);
  };

  template<> struct lua_values<bool>{
    static bool        get(lua_State *L, int idx);
    static int         put(lua_State *L, bool value);
  };

  // Осторожно: в LUA есть только double. Здесь он приводится к int
  template<> struct lua_values<int>
  {
    static int         get(lua_State *L, int idx);
    static int         put(lua_State *L, int value);
  };
  
  template<> struct lua_values<uint>
  {
    static uint        get(lua_State *L, int idx);
    static int         put(lua_State *L, uint value);
  };
  
  template<> struct lua_values<char>
  {
    static char        get(lua_State *L, int idx);
    static int         put(lua_State *L, char value);
  };

  template<> struct lua_values<short>
  {
    static short       get(lua_State *L, int idx);
    static int         put(lua_State *L, short value);
  };
 
  template<> struct lua_values<const char*>
  {
    static const char* get(lua_State *L, int idx);
    static int         put(lua_State *L, const char*); // Be careful with that!!!
  };

  template<> struct lua_values<string const&>
  {
    static string      get(lua_State *L, int idx);
    static int         put(lua_State *L, string const& value);
  };

  template<> struct lua_values<string>
  {
    static string      get(lua_State *L, int idx);
    static int         put(lua_State *L, string const& value);
  };

} // namespace Lua