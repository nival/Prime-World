#pragma once

#include "LuaBase.h"
#include "LuaTableLinks.h"

struct lua_State;

namespace Lua
{
  class LuaTypeInfo;
  
  class LuaSubclass : public IBaseInterfaceST
  {
    NI_DECLARE_CLASS_1( LuaSubclass, IBaseInterfaceST );

  public:
             LuaSubclass();
    virtual ~LuaSubclass();
    
    bool       Subclass(lua_State* pState, string const& subclass, void* pThis);
    bool       UnSubclass();
    bool       IsSubclassed() const { return !!Get(pTable); }
    lua_State* GetState() { return pLuaState ;}

    virtual LuaTypeInfo const* QueryLuaTypeInfo()     const { return NULL; }
    virtual void*              QueryNativeLuaObject() const { return NULL; }  
    bool            CallHandler(char const* name);
    template<class ARG1>
    bool            CallHandler(char const* name, ARG1 arg1);
    template<class ARG1, class ARG2>
    bool            CallHandler(char const* name, ARG1 arg1, ARG2 arg2);
    template<class ARG1, class ARG2, class ARG3>
    bool            CallHandler(char const* name, ARG1 arg1, ARG2 arg2, ARG3 arg3);
    template<class ARG1, class ARG2, class ARG3, class ARG4>
    bool            CallHandler(char const* name, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4);
    template<class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
    bool            CallHandler(char const* name, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5);

    template<class RV>
    bool            CallMethod(char const* name, RV& result);
    template<class RV, class ARG1>
    bool            CallMethod(char const* name, RV& result, ARG1 arg1);
    template<class RV, class ARG1, class ARG2>
    bool            CallMethod(char const* name, RV& result, ARG1 arg1, ARG2 arg2);
    template<class RV, class ARG1, class ARG2, class ARG3>
    bool            CallMethod(char const* name, RV& result, ARG1 arg1, ARG2 arg2, ARG3 arg3);
    template<class RV, class ARG1, class ARG2, class ARG3, class ARG4>
    bool            CallMethod(char const* name, RV& result, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4);
    template<class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
    bool            CallMethod(char const* name, RV& result, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5);
     
  private:
    AutoPtr<ObjectTableLink> pTable;
    lua_State*               pLuaState; 
    string                   subclassName;
  };

  inline bool     LuaSubclass::CallHandler(char const* name)
  {
    if(!!Get(pTable))
    {
      LUA_STACK_CHECKER(pTable->GetState(), 0)
      return pTable->CallHandler(name);
    }
    return false;
  }

  template<class ARG1>
  bool            LuaSubclass::CallHandler(char const* name, ARG1 arg1)
  {
    if(!!Get(pTable))
    {
      LUA_STACK_CHECKER(pTable->GetState(), 0)
      return pTable->CallHandler(name, arg1);
    }
    return false;

  }

  template<class ARG1, class ARG2>
  bool            LuaSubclass::CallHandler(char const* name, ARG1 arg1, ARG2 arg2)
  {
    if(!!Get(pTable))
    {
      LUA_STACK_CHECKER(pTable->GetState(), 0)
      return pTable->CallHandler(name, arg1, arg2);
    }
    return false;

  }

  template<class ARG1, class ARG2, class ARG3>
  bool            LuaSubclass::CallHandler(char const* name, ARG1 arg1, ARG2 arg2, ARG3 arg3)
  {
    if(!!Get(pTable))
    {
      LUA_STACK_CHECKER(pTable->GetState(), 0)
      return pTable->CallHandler(name, arg1, arg2, arg3);
    }
    return false;
  }

  template<class ARG1, class ARG2, class ARG3, class ARG4>
  bool            LuaSubclass::CallHandler(char const* name, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
  {
    if(!!Get(pTable))
    {
      LUA_STACK_CHECKER(pTable->GetState(), 0)
      return pTable->CallHandler(name, arg1, arg2, arg3, arg4);
    }
    return false;
  }

  template<class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  bool            LuaSubclass::CallHandler(char const* name, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
  {
    if(!!Get(pTable))
    {
      LUA_STACK_CHECKER(pTable->GetState(), 0)
      return pTable->CallHandler(name, arg1, arg2, arg3, arg4, arg5);
    }
    return false;
  }

  template<class RV>
  bool            LuaSubclass::CallMethod(char const* name, RV& result)
  {
    if(!!Get(pTable))
    {
      LUA_STACK_CHECKER(pTable->GetState(), 0)
      return pTable->CallMethod(name, result);
    }
    return false;
  }

  template<class RV, class ARG1>
  bool            LuaSubclass::CallMethod(char const* name, RV& result, ARG1 arg1)
  {
    if(!!Get(pTable))
    {
      LUA_STACK_CHECKER(pTable->GetState(), 0)
      return pTable->CallMethod(name, result, arg1);
    }
    return false;
  }

  template<class RV, class ARG1, class ARG2>
  bool            LuaSubclass::CallMethod(char const* name, RV& result, ARG1 arg1, ARG2 arg2)
  {
    if(!!Get(pTable))
    {
      LUA_STACK_CHECKER(pTable->GetState(), 0)
      return pTable->CallMethod(name, result, arg1, arg2);
    }
    return false;
  }

  template<class RV, class ARG1, class ARG2, class ARG3>
  bool            LuaSubclass::CallMethod(char const* name, RV& result, ARG1 arg1, ARG2 arg2, ARG3 arg3)
  {
    if(!!Get(pTable))
    {
      LUA_STACK_CHECKER(pTable->GetState(), 0)
      return pTable->CallMethod(name, result, arg1, arg2, arg3);
    }
    return false;
  }

  template<class RV, class ARG1, class ARG2, class ARG3, class ARG4>
  bool            LuaSubclass::CallMethod(char const* name, RV& result, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4)
  {
    if(!!Get(pTable))
    {
      LUA_STACK_CHECKER(pTable->GetState(), 0)
      return pTable->CallMethod(name, result, arg1, arg2, arg3, arg4);
    }
    return false;
  }

  template<class RV, class ARG1, class ARG2, class ARG3, class ARG4, class ARG5>
  bool            LuaSubclass::CallMethod(char const* name, RV& result, ARG1 arg1, ARG2 arg2, ARG3 arg3, ARG4 arg4, ARG5 arg5)
  {
    if(!!Get(pTable))
    {
      LUA_STACK_CHECKER(pTable->GetState(), 0)
      return pTable->CallMethod(name, result, arg1, arg2, arg3, arg4, arg5);
    }
    return false;
  }

  template<> struct lua_values<LuaSubclass*>
  {
    static LuaSubclass* get(lua_State *L, int idx);
    static int          put(lua_State *L, LuaSubclass* value);
  };

  template<> struct lua_values<LuaSubclass const*>
  {
    static LuaSubclass const* get(lua_State *L, int idx);
    static int                put(lua_State *L, LuaSubclass const* value);
  };
  
} // namespace Lua