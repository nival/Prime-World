//
// this file contains Lua::TableLinkBase template methods implementation
// DO NOT INCLUDE THIS FILE DIRECTLY!
// 

#include "LuaValues.h"

namespace Lua
{
  inline bool TableLinkBase::CallHandler(char const* name)
  {
    // Find the handler
    if( false == PrepareHandlerCall(name) )
      return false;// No such handler in script
    
    return MakeHandlerCall(name, 0);
  } 

  template<class ARG1>
  bool TableLinkBase::CallHandler(char const* name, ARG1 arg1)
  {
    // Find the handler
    if(!PrepareHandlerCall(name) )
      return false; // No such handler in script

    LUA_NATIVE

    // push params...
    int nParams = 0;
    nParams += lua_values<ARG1>::put(pLuaState, arg1);

    return MakeHandlerCall(name, nParams);
  }

  template<class ARG1, class ARG2>
  bool            TableLinkBase::CallHandler(char const* name, ARG1 arg1, ARG2 arg2)
  {
    // Find the handler
    if(!PrepareHandlerCall(name) )
      return false;// No such handler in script

    LUA_NATIVE

    // push params...
    int nParams = 0;
    nParams += lua_values<ARG1>::put(pLuaState, arg1);
    nParams += lua_values<ARG2>::put(pLuaState, arg2);
    
    return MakeHandlerCall(name, nParams);
  }

  template<class ARG1, class ARG2, class ARG3>
  bool            TableLinkBase::CallHandler(char const* name, ARG1 arg1, ARG2 arg2, ARG3 arg3)
  {
    // Find the handler
    if(!PrepareHandlerCall(name) )
      return false;// No such handler in script

    LUA_NATIVE

    // push params...
    int nParams = 0;
    nParams += lua_values<ARG1>::put(pLuaState, arg1);
    nParams += lua_values<ARG2>::put(pLuaState, arg2);
    nParams += lua_values<ARG3>::put(pLuaState, arg3);

    return MakeHandlerCall(name, nParams);
  }

  template<class ARG1, class ARG2, class ARG3, class ARG4>
  bool            TableLinkBase::CallHandler(char const* name, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
  {
    // Find the handler
    if(!PrepareHandlerCall(name) )
      return false;// No such handler in script

    LUA_NATIVE

    // push params...
    int nParams = 0;
    nParams += lua_values<ARG1>::put(pLuaState, arg1);
    nParams += lua_values<ARG2>::put(pLuaState, arg2);
    nParams += lua_values<ARG3>::put(pLuaState, arg3);
    nParams += lua_values<ARG4>::put(pLuaState, arg4);

    return MakeHandlerCall(name, nParams);
  }


  template<class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  bool            TableLinkBase::CallHandler(char const* name, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
  {
    // Find the handler
    if(!PrepareHandlerCall(name) )
      return false;// No such handler in script

    LUA_NATIVE

    // push params...
    int nParams = 0;
    nParams += lua_values<ARG1>::put(pLuaState, arg1);
    nParams += lua_values<ARG2>::put(pLuaState, arg2);
    nParams += lua_values<ARG3>::put(pLuaState, arg3);
    nParams += lua_values<ARG4>::put(pLuaState, arg4);
    nParams += lua_values<ARG5>::put(pLuaState, arg5);
    
    return MakeHandlerCall(name, nParams);
  }

  template<class RV>
  bool            TableLinkBase::CallMethod(char const* name, RV& result)
  {
    // Find the handler
    if(!PrepareHandlerCall(name) )
      return false;// No such handler in script

    MakeHandlerCall(name, 0, 1);
    
    LUA_NATIVE
    
    result = lua_values<RV>::get(pLuaState, -1);
    lua_pop(pLuaState, 1);

    return true;
  }


  template<class RV, class ARG1>
  bool            TableLinkBase::CallMethod(char const* name, RV& result, ARG1 arg1)
  {
    // Find the handler
    if(!PrepareHandlerCall(name) )
      return false;// No such handler in script

    LUA_NATIVE

    // push params...
    int nParams = 0; 
    nParams += lua_values<ARG1>::put(pLuaState, arg1);

    if( MakeHandlerCall(name, nParams, 1) )
    {
      result = lua_values<RV>::get(pLuaState, -1);
      lua_pop(pLuaState, 1);
      return true;
    }

    result = RV();
    return false;
  }

  template<class RV, class ARG1, class ARG2>
  bool            TableLinkBase::CallMethod(char const* name, RV& result, ARG1 arg1, ARG2 arg2)
  {
    // Find the handler
    if(!PrepareHandlerCall(name) )
      return false;// No such handler in script

    LUA_NATIVE

    // push params...
    int nParams = 0; 
    nParams += lua_values<ARG1>::put(pLuaState, arg1);
    nParams += lua_values<ARG2>::put(pLuaState, arg2);

    if( MakeHandlerCall(name, nParams, 1) )
    {
      result = lua_values<RV>::get(pLuaState, -1);
      lua_pop(pLuaState, 1);
      return true;
    }
    
    result = RV();
    return false;
  }
  
  template<class RV, class ARG1, class ARG2, class ARG3>
  bool            TableLinkBase::CallMethod(char const* name, RV& result, ARG1 arg1, ARG2 arg2, ARG3 arg3)
  {
    // Find the handler
    if(!PrepareHandlerCall(name) )
      return false;// No such handler in script

    LUA_NATIVE

    // push params...
    int nParams = 0; 
    nParams += lua_values<ARG1>::put(pLuaState, arg1);
    nParams += lua_values<ARG2>::put(pLuaState, arg2);
    nParams += lua_values<ARG3>::put(pLuaState, arg3);

    if( MakeHandlerCall(name, nParams, 1) )
    {
      result = lua_values<RV>::get(pLuaState, -1);
      lua_pop(pLuaState, 1);
      return true;
    }

    result = RV();
    return false;
  }
  
  template<class RV, class ARG1, class ARG2, class ARG3, class ARG4>
  bool            TableLinkBase::CallMethod(char const* name, RV& result, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
  {
    {
      // Find the handler
      if(!PrepareHandlerCall(name) )
        return false;// No such handler in script

      LUA_NATIVE

      // push params...
      int nParams = 0; 
      nParams += lua_values<ARG1>::put(pLuaState, arg1);
      nParams += lua_values<ARG2>::put(pLuaState, arg2);
      nParams += lua_values<ARG3>::put(pLuaState, arg3);
      nParams += lua_values<ARG4>::put(pLuaState, arg4);

      if( MakeHandlerCall(name, nParams, 1) )
      {
        result = lua_values<RV>::get(pLuaState, -1);
        lua_pop(pLuaState, 1);
        return true;
      }

      result = RV();
      return false;
    }
  }
  
  template<class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  bool            TableLinkBase::CallMethod(char const* name, RV& result, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
  {
    {
      // Find the handler
      if(!PrepareHandlerCall(name) )
        return false;// No such handler in script

      LUA_NATIVE

      // push params...
      int nParams = 0; 
      nParams += lua_values<ARG1>::put(pLuaState, arg1);
      nParams += lua_values<ARG2>::put(pLuaState, arg2);
      nParams += lua_values<ARG3>::put(pLuaState, arg3);
      nParams += lua_values<ARG4>::put(pLuaState, arg4);
      nParams += lua_values<ARG5>::put(pLuaState, arg5);

      if( MakeHandlerCall(name, nParams, 1) )
      {
        result = lua_values<RV>::get(pLuaState, -1);
        lua_pop(pLuaState, 1);
        return true;
      }

      result = RV();
      return false;
    }
  }

  template<class ValueType, class KeyType>
  void  TableLinkBase::Set(char const* name, KeyType key, ValueType val)
  {
    if(!MyTableToStack())
      return;

    LUA_NATIVE

    if(!PrepareSubtablePath(pLuaState, name))
      return;

    LUA_STACK_CHECKER(pLuaState, -1)

    lua_values<KeyType>::put(pLuaState, key);       // Key
    if(!lua_values<ValueType>::put(pLuaState, val)) // Value                  
      lua_pushnil(pLuaState);                       // Set nil if we failed to put this value
    
    NI_ASSERT(lua_istable(pLuaState, -3), "Ensure table present");
    
    lua_settable(pLuaState, -3); // SetIt!
    lua_pop(pLuaState, 1);       // Drop the table
  }

  template<class T>
  bool  TableLinkBase::Get(char const* subtable, char const* name, T& val, T const& DefaultVal) const
  {
    LUA_STACK_CHECKER(pLuaState, 0)
    if(!MyTableToStack())
      return false;

    if(!FindSubtable(pLuaState, subtable))
      return false;

    LUA_NATIVE
    if(!name[0])
    { 
      // Special case for table itself
      val = lua_values<T>::get(pLuaState, -1);
      lua_pop(L, 1); // Drop the table 
      return true;
    }

    lua_values<const char*>::put(pLuaState, name); // Key
    
    NI_ASSERT(lua_istable(L, -2), "Table required!");
    lua_gettable(L, -2);
    
    if(!!lua_isnil(L, -1))
    {
      lua_pop(L, 2);// Drop the table and the value
      return false;
    }

    val = lua_values<T>::get(L, -1);

    lua_pop(L, 2);// Drop the table and the value

    return true;
  }
} // namespace Lua