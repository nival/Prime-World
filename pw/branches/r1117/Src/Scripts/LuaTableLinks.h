#pragma once

#include "LuaValues.h"
#include "lua.hpp"

struct lua_State;

namespace Lua
{
  class LuaTypeInfo;

  class TableLinkBase
  {
  public:
    TableLinkBase(lua_State* pLuaState);
    virtual ~TableLinkBase();
        
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
    
    template<class ValueType, class KeyType>
    void            Set(char const* name, KeyType key, ValueType val);

    template<class T>
    bool            Get(char const* subtable, char const* name, T& val, T const& DefaultVal = T() ) const; 
    
    bool            Has(char const* subtable, char const* name = "") const;
    lua_State*      GetState() { return pLuaState; }
  protected:
    virtual bool    MyTableToStack() const = 0;

    lua_State*      pLuaState;
  private:
    bool            PrepareHandlerCall(char const* name);
    bool            MakeHandlerCall(char const* name, int nParams, int nResults = 0);
  };
  
  class ParameterTableLink : public TableLinkBase
  {
    int pos;
    template<typename T> friend struct lua_values;
  public:
    ParameterTableLink(lua_State* pLuaState, int pos) : TableLinkBase(pLuaState), pos(pos) {}
    virtual ~ParameterTableLink() {}
  protected:
    virtual bool    MyTableToStack() const;
  };

  template<>
  struct lua_values<ParameterTableLink>
  {
    static ParameterTableLink get(lua_State* L, int idx) { return ParameterTableLink(L, idx); }
  };

  template<>
  struct lua_values<ParameterTableLink const&>
  {
    static ParameterTableLink get(lua_State* L, int idx) { return ParameterTableLink(L, idx); }
  };
  
  class ObjectTableLink : public TableLinkBase
  {
  public:
            ObjectTableLink(lua_State* pLuaState);
    virtual ~ObjectTableLink();
  public:

    template<class LinkedObject>
    bool         CreateLinkedTable(LinkedObject* pObject, LuaTypeInfo const* pTypeInfo, string const& nativeClass, string const& subclassName)
    {
      this->pObject = pObject;
      return CreateLinkedTableInternal( pTypeInfo, nativeClass, subclassName );
    };
    
  protected:
    virtual bool MyTableToStack() const;
  private:
    void         Disconnect();
    bool         CreateLinkedTableInternal( LuaTypeInfo const* pTypeInfo, string const& nativeClass, string const& subclassName );
  private:
    string sourceTable;
    void*  pObject;
  };

}// namespace Lua

// include CallHandler and CallMethod implementation
#include "LuaTableLinksImpl.h"