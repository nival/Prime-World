#pragma once

#define LUA_DESTRUCTOR_NAME    "_destructor"
#define LUA_NATIVE_CLASS_NAME  "_nativeClass"
#define LUA_TYPEINFO_NAME      "_nativeTypeInfo"
#define LUA_GET_TYPEINFO(ARGT) ( (void*) NULL )

struct lua_State;

namespace Lua
{
  class TableLinkBase;
  class LuaTypeInfo;

  // internal functions, used by wrapper
  bool RetrieveObjectMehtod(lua_State* L, char const* name);
  bool MakePreparedCall(lua_State* L, char const* name, int nParams, int nResults);
  
  bool GetObjectByStrongRef(lua_State* L, void* object);
  void KillStrongRef(lua_State* L, void* object);

  bool GetObjectByWeakRef(lua_State* L, void const* object);
  void KillWeakRef(lua_State* L, void* pObject);

  void ConnectMetatable(lua_State* L, char const* className, LuaTypeInfo const* pTypeInfo, void* pObject);
  void MetatableToStack(lua_State* L, char const* className, LuaTypeInfo const* pTypeInfo);

  int  PutWeakObjectToStack(lua_State* L, char const* className, LuaTypeInfo const* pTypeInfo, void* pObject);

  void DropDeadObjectTable(lua_State* L);
  bool FindObjectMehtod(lua_State* L, char const* name);
  void TableLinkToTable(lua_State* L, TableLinkBase* pLink);
  void UserdataToObject(lua_State *L, void* object);

  bool FindSubtable(lua_State* L, char const* name);
  bool PrepareSubtablePath(lua_State* L, char const* name);
  bool PrepareTablePath(lua_State* L, char const* name);

  void* ObjectPtrFromMeta(lua_State *L, void* TargetClass, int nStackPos);
  void* ObjectPtrFromMetaCall(lua_State *L, void* TargetClass);

  template <class T>
  T* TypedObjectPtrFromMeta(lua_State* L)
  {
    return reinterpret_cast<T*>(ObjectPtrFromMetaCall(L, LUA_GET_TYPEINFO(T) ) );
  }

  string GetLuaCallStack(lua_State* pState, int startLevel = 0);
  
  class StackChecker
  {
    lua_State*  pState;
    int         requiredTop;
  public:
    StackChecker(lua_State* pState, int offset);
    ~StackChecker();
  };
  
  void OnEnterLuaScript();
  void OnLeaveLuaScript();

  void OnEnterLuaNative();
  void OnLeaveLuaNative();

  struct LuaNativeGuard
  {
    LuaNativeGuard()  { OnEnterLuaNative(); }
    ~LuaNativeGuard() { OnLeaveLuaNative(); }
  };

  struct LuaScriptGuard
  {
    LuaScriptGuard()  { OnEnterLuaScript(); }
    ~LuaScriptGuard() { OnLeaveLuaScript(); }
  };
} // namespace Lua

#ifndef _SHIPPING
# define LUA_NATIVE                       Lua::LuaNativeGuard luaNativeGuard;
# define LUA_SCRIPT                       Lua::LuaScriptGuard luaScriptGuard;
# define LUA_STACK_CHECKER(state, offset) Lua::StackChecker luaStackCheckerInstance(state, offset);
#else
# define LUA_NATIVE                      
# define LUA_SCRIPT                      
# define LUA_STACK_CHECKER(state, offset)
#endif