#include "stdafx.h"
#include "LuaSubclass.h"
#include "LuaCommon.h"

#include "lua.hpp"

namespace Lua
{ 
  LuaSubclass::LuaSubclass()
    : pLuaState(NULL)
    , pTable(NULL)
  {
  }

  LuaSubclass::~LuaSubclass()
  {
    if(pLuaState)
      KillWeakRef(pLuaState, this);

    UnSubclass();
  }

  bool LuaSubclass::Subclass(lua_State* pState, string const& subclass, void* pThis)
  {
    NI_VERIFY(NULL == Get(pTable), "Object is already subclassed!", return false; ); 
    NI_VERIFY(NULL != pState,      "Invalid LuaState",              return false; );

    LuaTypeInfo const* pTypeInfo = QueryLuaTypeInfo();
    NI_VERIFY(NULL != pTypeInfo,   "Invalid typeinfo",              return false; );
    
    subclassName = subclass;
    pLuaState    = pState;
    Reset(pTable, new ObjectTableLink(pState) );
     
    bool success = pTable->CreateLinkedTable(pThis, pTypeInfo, ClassName(), subclass);
    //NI_ASSERT(success, "Subclassing failed!")
    return success;
  }

  bool LuaSubclass::UnSubclass()
  {
    if( Get(pTable) )
    {
      Reset(pTable, NULL);
      subclassName = "";
      pLuaState    = NULL;
      return true;
    }

    return false;
  }


  int          lua_values<LuaSubclass*>::put(lua_State* L, LuaSubclass* value)
  {
    if( Lua::LuaTypeInfo const* pTypeInfo = value ? value->QueryLuaTypeInfo() : NULL )
      if(int result = PutWeakObjectToStack(L, pTypeInfo->GetTypeName(), pTypeInfo, value->QueryNativeLuaObject() ) )
        return result;

    lua_pushnil(L);
    return 1;
  }

  LuaSubclass* lua_values<LuaSubclass*>::get(lua_State *L, int idx)
  {
    LuaSubclass* pObject = reinterpret_cast<LuaSubclass*>( ObjectPtrFromMeta(L, (void*)NULL, idx) );
    return pObject;
  }

  int          lua_values<LuaSubclass const*>::put(lua_State *L, LuaSubclass const* value)
  {
    if( Lua::LuaTypeInfo const* pTypeInfo = value ? value->QueryLuaTypeInfo() : NULL )
      if(int result = PutWeakObjectToStack(L, pTypeInfo->GetTypeName(), pTypeInfo, value->QueryNativeLuaObject() ) )
        return result;

    lua_pushnil(L);
    return 1;
  }

  LuaSubclass const* lua_values<LuaSubclass const*>::get(lua_State *L, int idx)
  {
    LuaSubclass const* pObject = reinterpret_cast<LuaSubclass const*>( ObjectPtrFromMeta(L, (void*)NULL, idx) );
    return pObject;
  }

} // namespace Lua