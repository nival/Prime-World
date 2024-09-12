#pragma once

#include "NameMap.h"
#include "ScriptLog.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct lua_State;
typedef int (*lua_CFunction) (lua_State *L);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NScript
{
_interface INameMapElement;

typedef hash_map<string, lua_CFunction> LuaFunctionsList;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Script : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( Script, BaseObjectST )

private:
  lua_State* state;
  bool ownState;
  bool isInited;
  bool isReadOnly;

  LuaFunctionsList RegList;

  typedef lua_State Thread;
  struct ThreadInfo
  {
    ///< thread state
    Thread* pThread;
    ///< thread reference index
    int luaRef;
    ///< number of arguments on stack from last resume call
    int numberOfArguments;

    ThreadInfo( Thread* _pThread, int index, int arguments = 0 )
      : pThread( _pThread )
      , luaRef( index )
      , numberOfArguments( arguments )
    {}
  };
  typedef list<ThreadInfo> ThreadContainer;
  ThreadContainer threads;

  hash_set<string> loadedFiles;

  bool          calculateCrc;
  unsigned long crc;

  ThreadContainer::iterator UnRegisterLuaThread( const ThreadContainer::iterator& it );

public:
  Script();
  Script(bool _calculateCrc);
  virtual ~Script();

  void Reinit();
  void ClearCache() { loadedFiles.clear(); }
  void RemoveFromCache( const string& str ) { loadedFiles.erase(str); }

  // "do" functions(run Lua code)
  int DoString( const string& str);
  int DoFile( const string& str);

  operator lua_State*() { return state; }
  lua_State* GetState() const	{ return state;	}

  void EnableWriteableProperties( bool enable ) { isReadOnly = !enable; }

  void AddFunctionToRegList( const char *fname, lua_CFunction Func ) { RegList[fname] = Func; }
  void AddFunctionsToRegList( const LuaFunctionsList & functionsList  ) 
  { 
    RegList.insert(functionsList.begin(), functionsList.end()); 
  }

  void RegisterGlobals();

  /**
  *	start new thread and call main function
  *	which passed thought stack [bottom stack] ... mainFunction, param1, param2, ... [top stack]
  */
  bool StartThread( lua_State* pParentState, int numberOfArguments );
  void StepLuaThreads();
  //	int operator&( IBinSaver &f );

  unsigned long GetCrc() const { return crc; };
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void AddSFunctionToGlobals( const char *fname, lua_CFunction Func );
Script *GetScript( lua_State *pLuaState );

} // namespace NScript


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/** helper function to resolve context of Lua property access and checking parameters */
template<class LuaObject>
LuaObject *dispatchLuaCall( lua_State *pLuaState, int index )
{
return ( dynamic_cast<LuaObject*>( NScript::DispatchLuaCallInternal( pLuaState, index ) ) );
}
