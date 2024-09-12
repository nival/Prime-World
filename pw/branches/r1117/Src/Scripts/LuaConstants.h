#pragma once 

namespace Lua
{
  class LuaSimpleDefine
  {
  public:
    explicit LuaSimpleDefine(const char* prefix, char const* name, char const* value);
    explicit LuaSimpleDefine(const char* prefix, char const* name, int value);
  };
  
  template<typename NDBEnum>
  class LuaNDbEnumDefine
  {
  public:
    LuaNDbEnumDefine( int firstValue, const char* prefix )
    {
      for(int i = firstValue, lastValue = firstValue + NDb::KnownEnum<NDBEnum>::sizeOf; i < lastValue; ++i)
      {
        LuaSimpleDefine item(prefix, NDb::KnownEnum<NDBEnum>::ToString(static_cast<NDBEnum>(i)), i);
        item;
      }
    }
  };
  
  template<typename NDBEnum>
  class LuaNDbEnumValueDefine
  {
  public:
    LuaNDbEnumValueDefine(NDBEnum value)
    {
      LuaSimpleDefine item("", NDb::KnownEnum<NDBEnum>::ToString(value), value);
      item;
    }
  };
}

#define CONCATENATE_DIRECT(A, B) A##B
#define CONCATENATE(A, B)        CONCATENATE_DIRECT(A, B)

#define LUA_EXPORT_CONSTANT(NAME)         Lua::LuaSimpleDefine CONCATENATE(luaDefine, __LINE__)("", #NAME, NAME);
#define LUA_EXPORT_CONSTANT2(NAME, VALUE) Lua::LuaSimpleDefine CONCATENATE(luaDefine, __LINE__)("", NAME, VALUE);
#define LUA_EXPORT_NDBENUM(NDBENUM)       Lua::LuaNDbEnumDefine<NDBENUM> CONCATENATE(luaDefine, __LINE__)(0, "");
#define LUA_EXPORT_NDBENUM_EX(NDBENUM, FIRSTVALUE, PREFIX)  Lua::LuaNDbEnumDefine<NDBENUM> CONCATENATE(luaDefine, __LINE__)(FIRSTVALUE, PREFIX);
#define LUA_EXPORT_NDBENUM_VALUE(NDBENUM, VALUE)  Lua::LuaNDbEnumValueDefine<NDBENUM> CONCATENATE(luaDefine, __LINE__)(VALUE);
