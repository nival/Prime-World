#include "stdafx.h"
#include "LuaTableLinks.h"
#include "LuaCommon.h"
#include "LuaValues.h"
#include "LuaMetaData.h"


namespace Lua
{
  TableLinkBase::TableLinkBase(lua_State* pLuaState)
    : pLuaState(pLuaState)
  {
  }

  TableLinkBase::~TableLinkBase()
  {
  }
  
  bool TableLinkBase::PrepareHandlerCall(char const* name)
  {
    if( NULL == pLuaState)
      return false;

    if( false == MyTableToStack() )
      return false;

    return RetrieveObjectMehtod(pLuaState, name);
  }

  bool TableLinkBase::MakeHandlerCall(char const* name, int nParams, int nResults)
  {
    return MakePreparedCall(pLuaState, name, nParams + 1 /* do not forget about 'this' ! */, nResults);
  }

  bool TableLinkBase::Has(char const* subtable, char const* name) const
  {
    return false;
  }


  ObjectTableLink::ObjectTableLink(lua_State* pLuaState)
    : TableLinkBase(pLuaState)
  {
  }

  ObjectTableLink::~ObjectTableLink()
  {
    Disconnect();
  }
  
  static char const* STR_CLASS_FACTORY = "ClassFactory";
  bool ObjectTableLink::CreateLinkedTableInternal( LuaTypeInfo const* pTypeInfo, string const& nativeClass, string const& subclassName )
  {
    LUA_STACK_CHECKER(pLuaState, 0)

    // Prepare our metatable
    if(!PrepareTablePath(pLuaState, "Sys") || !FindObjectMehtod(pLuaState, STR_CLASS_FACTORY))
    {
      systemLog(NLogg::LEVEL_ASSERT) << "LUA fatal: Failed to get method Sys:ClassFactory" << endl;
      return false;
    }

    lua_values<const char*>::put(pLuaState, pTypeInfo->GetTypeName()/*nativeClass.c_str()*/);
    lua_values<const char*>::put(pLuaState, subclassName.c_str());
    
    MetatableToStack(pLuaState, nativeClass.c_str(), pTypeInfo);

    if(!MakePreparedCall(pLuaState, STR_CLASS_FACTORY, 4, 1))
      return false;

    if(lua_isnil(pLuaState, -1))
    {
      lua_pop(pLuaState, 1);
      return false;
    }
    if(!lua_istable(pLuaState, -1))
    {
      systemLog(NLogg::LEVEL_ASSERT) << "LUA: Failed to Create object by table link. Not a table from ClassFactory." << endl;
      lua_pop(pLuaState, 1);
      return false;
    }
    
    MetatableToStack(pLuaState, nativeClass.c_str(), pTypeInfo);
    UserdataToObject(pLuaState, pObject);
    lua_pop(pLuaState, 1); // Drop the metatable
    TableLinkToTable(pLuaState, this);

#ifdef _DEBUG
    // Check that this object is not yet connected
    lua_pushlightuserdata(pLuaState, pObject);
    lua_gettable(pLuaState, LUA_REGISTRYINDEX);
    NI_ASSERT(lua_isnil(pLuaState, -1), "LUA: Connecting the table to the object that is already connected");
    lua_pop(pLuaState, 1);
#endif

    // Put the object to the registry
    lua_pushlightuserdata(pLuaState, pObject);
    lua_pushvalue(pLuaState, -2);// dup the object table
    lua_settable(pLuaState, LUA_REGISTRYINDEX);

    lua_pop(pLuaState, 1);// Drop the object table
    return true;
  }

  void ObjectTableLink::Disconnect()
  {
    LUA_NATIVE
    
    LUA_STACK_CHECKER(pLuaState, 0)

    if(GetObjectByStrongRef(pLuaState, pObject))
      DropDeadObjectTable(pLuaState);

    KillStrongRef(pLuaState, pObject);
  }
  
  bool ObjectTableLink::MyTableToStack() const
  {
    return pLuaState ? GetObjectByStrongRef(pLuaState, pObject) : false;
  }  

  bool ParameterTableLink::MyTableToStack()const
  {
    if(!lua_istable(pLuaState, pos))
      return false;

    lua_pushvalue(pLuaState, pos);
    return true;
  }

} // namespace Lua
