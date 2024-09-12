#pragma once

#include "LuaValueSettable.h"

struct luaValueSetter
{
  static void Set(lua_State *L, const char* value);
  static void Set(lua_State *L, double value);
  static void Set(lua_State *L, float value);
  static void Set(lua_State *L, int value);
  static void Set(lua_State *L, bool value);
  static void Set(lua_State *L, const string& value);
  template<class T>
  static void Set(lua_State *L, const vector<T>& value)
  {
    lua_createtable( L, value.size(), 0 );

    for ( int i = 0; i < value.size(); ++i )
    {
      luaValueSetter::Set( L, value[i] );
      lua_rawseti( L, -2, i+1 );
    }
  }
  static void Set(lua_State *L, const ILuaValueSettable& value);
  static void Set(lua_State *L, const CVec2& value);
  static void Set(lua_State *L, const CVec3& value);
};

#define LUA_VALUE_SETTABLE_BEGIN(structName,paramsNumber) \
  int structName::Set( lua_State *L ) const       \
{                                                       \
  lua_createtable( L, 0, paramsNumber );

#define LUA_VALUE_SETTABLE_PROPERTY_EX(name,param) \
  luaValueSetter::Set( L, name );          \
  luaValueSetter::Set( L, param );         \
  lua_settable( L, -3 );

#define LUA_VALUE_SETTABLE_PROPERTY(param) LUA_VALUE_SETTABLE_PROPERTY_EX(#param,param)

#define LUA_VALUE_SETTABLE_END \
  return 1;                  \
}


namespace NWorld
{
class PFAIContainer;

class PFScript : public NScript::Script
{
  NI_DECLARE_REFCOUNT_CLASS_1( PFScript, NScript::Script );

public:
  PFScript() : NScript::Script(true), pPFAIContainer(0), isLoaded(false) {}
  PFScript(PFAIContainer * _pPFAIContainer) : NScript::Script(true), pPFAIContainer(_pPFAIContainer), isLoaded(false) {}

  void SetAIContainer(PFAIContainer * _pPFAIContainer) { pPFAIContainer = _pPFAIContainer; }
  PFAIContainer* GetAIContainer() const { return pPFAIContainer; }
  void SetLoaded(bool loaded) { isLoaded = loaded; }
  bool IsLoaded() const { return isLoaded; }
  void Step();

  int operator&( IBinSaver &f );

private:
  CPtr<PFAIContainer> pPFAIContainer;
  bool                isLoaded;
};

struct PFScriptSerializer
{
public:
  int operator&( IBinSaver &f );

  void Init( PFScript* _script ) { script = _script; }

private:
  Weak<PFScript> script;
};

} // namespace NWorld