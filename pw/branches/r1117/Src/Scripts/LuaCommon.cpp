#include "stdafx.h"
#include "LuaCommon.h"
#include "LuaMetaData.h"

#include "lua.hpp"

#include "../System/DebugVar.h"

#define WEAKREF_STORAGE "WeakReferences"
#pragma warning (disable: 4996)

// This variable is used to form the unique 'light userdata' index to place the pointer to the table link there
namespace 
{
  int TABLE_LINK_INDEX     = 0;
  char const* errDebugName = NULL;

  int ForbiddenCreator(lua_State* L)
  {
    systemLog(NLogg::LEVEL_ASSERT) << "Tried to use class constructor. Objects of this type may be only created from the C++ code." << endl;
    return 0;
  }

  int ForbiddenDestroyer(lua_State* L)
  {
    //systemLog(NLogg::LEVEL_ASSERT) << "The LUA object, that is managed from C++ is being garbage -collected!!!." << endl;
    return 0;
  }

  void FillMethodTable(lua_State* L, Lua::LuaTypeInfo const* pTypeInfo, int metatable)
  {
    LUA_STACK_CHECKER(L, 0)

      for(int i = 0, count = pTypeInfo->GetMethodsCount(); i < count; ++i)
      {
        if(Lua::LuaMethodEntry const* pMethod = pTypeInfo->GetMethod(i) )
        {
          lua_pushstring(L,   pMethod->Name());
          lua_pushcclosure(L, pMethod->Get(), 0);
          lua_settable(L,     metatable);
        }
        else
        {
          NI_ALWAYS_ASSERT("Can`t find method entry!");
        }
      }
  }

  void FillPropertiesTable(lua_State* L, Lua::LuaTypeInfo const* pTypeInfo, int metatable)
  {
    lua_pushstring(L, "__props");
    lua_newtable(L);
    lua_settable(L, metatable);

    lua_pushstring(L, "__props");
    lua_gettable(L, metatable);

    NI_ASSERT(lua_istable(L, -1), "LUA: table must be on the top of the stack");

    int props = lua_gettop(L);
    for(int i = 0, count = pTypeInfo->GetFieldsCount(); i < count; ++i)
    {
      if(Lua::LuaFieldEntry const* pField = pTypeInfo->GetField(i) )
      {
        lua_pushstring(L, pField->Name());
        lua_newtable(L);
        lua_settable(L, props);

        lua_pushstring(L, pField->Name());
        lua_gettable(L, props);

        int handler = lua_gettop(L);

        lua_pushstring(L, "set");
        lua_pushcclosure(L, pField->GetManipulator(), 0);
        lua_settable(L, handler);

        lua_pushstring(L, "get");
        lua_pushcclosure(L, pField->GetAccessor(), 0);
        lua_settable(L, handler);

        lua_pop(L, 1); // drop property table
      }
      else
      {
        NI_ALWAYS_ASSERT("Can`t find method entry!");
      }
    }

    lua_pop(L, 1); // drop __props table
  }

  void PrepareClassMetatable(lua_State* L, char const* nativeClass, Lua::LuaTypeInfo const* pTypeInfo, lua_CFunction Creator, lua_CFunction Destroyer)
  {
    LUA_NATIVE
    LUA_STACK_CHECKER(L, 0)

    // create table for methods
    lua_newtable(L);
    int methods = lua_gettop(L);
    // stack:  methods
    // create metatable
    luaL_newmetatable(L, pTypeInfo->GetTypeName());
    int metatable = lua_gettop(L);
    // stack:  methods  metatable

    // register class in global table
    // this is required to provide script access to engine static methods (ConsoleVariable.Method() etc)
    lua_pushstring(L, pTypeInfo->GetTypeName());
    lua_pushvalue(L,  methods);
    lua_settable(L,   LUA_GLOBALSINDEX); // globals[className] = methodsTable

    lua_pushliteral(L, "__methods");
    lua_pushvalue(L,   methods);
    lua_settable(L,    metatable);        // metatable.__index = methods

    lua_pushliteral(L, LUA_NATIVE_CLASS_NAME);
    lua_pushstring(L,  nativeClass);
    lua_settable(L,    metatable);        // metatable.name = className

    lua_pushstring(L, "ProxyIndex");
    lua_gettable(L,   LUA_GLOBALSINDEX);
    lua_pushstring(L, "__index");
    lua_pushvalue(L,  -2);
    lua_remove(L,     -3);
    lua_settable(L,    metatable);

    lua_pushstring(L, "PropertyManipulator");
    lua_gettable(L,   LUA_GLOBALSINDEX);
    lua_pushstring(L, "__newindex");
    lua_pushvalue(L,  -2);
    lua_remove(L,     -3);
    lua_settable(L,    metatable);

    lua_pushliteral(L,   "__gc");
    lua_pushcfunction(L, Destroyer);
    lua_settable(L, metatable);        // metatable.__gc = Destroyer

    lua_newtable(L);                   // mt for method table
    int mt = lua_gettop(L);
    // stack:  methods  metatable  mt

    lua_pushliteral(L, "__call");
    lua_pushcfunction(L, Creator);
    // stack:  methods  metatable  mt  "__call"  Creator()

    lua_pushliteral(L, "new");
    lua_pushvalue(L, -2);              // dup new_T function (== Creator)
    // stack:  methods  metatable  mt  "__call"  Creator()  "new"  Creator()
    lua_settable(L, methods);          // add new_T to method table

    lua_settable(L, mt);               // mt.__call = new_T

    // stack:  methods  metatable  mt
    lua_setmetatable(L, methods);      // methods.metatable = mt
    // stack:  methods  metatable

    FillMethodTable(L, pTypeInfo, methods);

    FillPropertiesTable(L, pTypeInfo, metatable);

    lua_pop(L, 2);  // drop metatable and method table
  }

  void GetWeakreferencesTable(lua_State* L)
  {
    lua_pushliteral(L, WEAKREF_STORAGE);
    lua_gettable(L, LUA_REGISTRYINDEX);

    if(lua_isnil(L, -1))
    {
      // Table is not yet created
      lua_pushliteral(L, WEAKREF_STORAGE);
      lua_newtable(L);

      int storage = lua_gettop(L);
      lua_newtable(L);          // Metatable to define object table 'weakness'

      int weakMT = lua_gettop(L);
      lua_pushliteral(L, "__mode");
      lua_pushliteral(L, "v");
      lua_settable(L, weakMT);  // set mode to weak values
      lua_setmetatable(L, storage);

      lua_settable(L, LUA_REGISTRYINDEX);// Now the object table is on the stack
      lua_pop(L, 1);

      lua_pushliteral(L, WEAKREF_STORAGE);
      lua_gettable(L,    LUA_REGISTRYINDEX);
    }
  }

  void MakeWeakRef(lua_State* L, void* pObject)
  {
    int LuaObject = lua_gettop(L);

    NI_ASSERT(lua_istable(L, LuaObject), "There must be my table!" );
    
    GetWeakreferencesTable(L);
    NI_ASSERT(lua_istable(L, -1), "Object table must be present here");

    lua_pushlightuserdata(L, pObject);
    lua_pushvalue(L, LuaObject);
    lua_settable(L, -3);                         // Now my pointer is in the objects table
    lua_pop(L, 1);                               // Drop the table from the stack
  }

  int ErrorHook(lua_State* L)
  {
    const char* message = lua_tostring(L, -1);
    
    systemLog(NLogg::LEVEL_ASSERT) << "Lua: ";
    if (errDebugName)
      systemLog(NLogg::LEVEL_ASSERT) << errDebugName << ": ";
    systemLog(NLogg::LEVEL_ASSERT) << message << endl;
    
    errDebugName = NULL;

    systemLog(NLogg::LEVEL_ASSERT) << Lua::GetLuaCallStack(L, 1) << endl;
    return 1;
  }

  void* CheckUserData(lua_State* L, int ud, void* /*TargetClass*/)
  {
    // note: ud always points to top of stack
    // top of stack: self[luserdata(0)] == userdata
    if (!lua_getmetatable(L, ud))
      return NULL;        // no metatable?

    // top of stack: userdata  metatable
    lua_pushstring(L, LUA_NATIVE_CLASS_NAME);
    lua_gettable(L, -2);

    // top of stack: userdata  metatable  className
    if (const char* tn = lua_tostring(L, -1))
    {
      lua_pop(L, 2);                                 // drop metatable and className
      return lua_touserdata(L, ud);
    }

    lua_pop(L, 2);
    return NULL;
  }
}

namespace Lua
{
  bool RetrieveObjectMehtod(lua_State* L, char const* name)
  {
    LUA_NATIVE
    
    //The object is on the top of the stack
    NI_ASSERT(lua_istable(L, -1), "Object on the top of the stack must present!");
    
    lua_pushstring(L, name);  // function name
    lua_gettable(L, -2);         // function to be called
    //  lua_remove(L, -2);       // drop the method table
    //  lua_remove(L, -3);       // drop the object table
    if(lua_isnil(L, -1))
    {
      lua_remove(L, -2);         // drop the object table
      // Looks like no such func exists
      lua_pop(L, 1);             // balance the stack (throw the func)
      return false;
    }

    // Exchange the table and the function on the stack
    lua_pushvalue(L, -2);
    lua_remove(L, -3);

    return true;
  }

  bool MakePreparedCall(lua_State* L, char const* name, int nParams, int nResults)
  {
    LUA_SCRIPT
  
    errDebugName = name;
    int base     = lua_gettop(L) - nParams;   // stack index for callback: before 1st argument

    lua_pushcfunction(L, ErrorHook);
    lua_insert(L, base);
    if (lua_pcall(L, nParams, nResults, base) != 0)
    {
      lua_remove(L, base);                // remove traceback function
      lua_pop(L, 1);                      // remove error message
      return false;
    }

    lua_remove(L, base);                  // remove traceback function
    return true;
  }

  bool GetObjectByStrongRef(lua_State* L, void* object)
  {
    lua_pushlightuserdata(L, object);
    lua_gettable(L, LUA_REGISTRYINDEX);
    if(!lua_istable(L, -1))
    {
      lua_pop(L, 1);
      return false;
    }
    return true;
  }

  void KillStrongRef(lua_State* L, void* object)
  {
    // Kill the link from the registry
    lua_pushlightuserdata(L, object);
    lua_pushnil(L);
    lua_settable(L, LUA_REGISTRYINDEX);
  }

  void DropDeadObjectTable(lua_State* L)
  {
    // Make sure there will be no call from lua table to the dead C++ object
    NI_ASSERT(lua_istable(L, -1), "There must be target table on the top of the stack!");
    LUA_STACK_CHECKER(L, -1);// Drops target table

    // Remove the metatable
    lua_pushvalue(L, -1);// Table is now its own metatable
    lua_setmetatable(L, -2);// Assign empty table as the metatable

    // Remove 'this'
    lua_pushlightuserdata(L, NULL);// key
    lua_pushnil(L);// value
    lua_settable(L, -3);

    // Remove table link (if any)
    lua_pushlightuserdata(L, &TABLE_LINK_INDEX);// key
    lua_pushnil(L);// value
    lua_settable(L, -3);
    
    lua_pop(L, 1); // Drop the object table
  }

  bool FindObjectMehtod(lua_State* L, char const* name)
  {
    LUA_NATIVE
   
    NI_ASSERT(lua_istable(L, -1), "The object is on the top of the stack");

    lua_pushstring(L, name);  // function name
    lua_gettable(L, -2);         // function to be called
    //  lua_remove(L, -2);       // drop the method table
    //  lua_remove(L, -3);       // drop the object table
    if(lua_isnil(L, -1))
    {
      lua_remove(L, -2);         // drop the object table
      // Looks like no such func exists
      lua_pop(L, 1);             // balance the stack (throw the func)
      return false;
    }

    // Exchange the table and the function on the stack
    lua_pushvalue(L, -2);
    lua_remove(L, -3);

    return true;
  }

  void TableLinkToTable(lua_State* L, TableLinkBase* pLink)
  {
    LUA_STACK_CHECKER(L, 0)
    lua_pushlightuserdata(L, &TABLE_LINK_INDEX);// Key
    lua_pushlightuserdata(L, pLink);// value
    lua_settable(L, -3);
  }

  void UserdataToObject(lua_State *L, void* object)
  {
    LUA_STACK_CHECKER(L, 0)

    // stack: table  metatable
    NI_ASSERT(lua_istable(L, -1), "There must be a metatable");
    NI_ASSERT(lua_istable(L, -2), "There must be a table for the object");

    int metatable = lua_gettop(L);
    lua_pushlightuserdata(L, NULL); // userdata obj at index 0
    // stack: table  metatable  luserdata(0)

    *(void**)lua_newuserdata(L, sizeof(void *)) = object;
    // stack: table  metatable  luserdata(0)  userdata(object)

    lua_pushvalue(L, metatable);
    lua_setmetatable(L, -2);                     // userdata._metatable = metatable
    // stack: table  metatable  luserdata(0)  userdata(object)

    lua_settable(L, -4);                         // table[luserdata] = userdata
    // stack: table  metatable
  }

  bool FindSubtable(lua_State* L, char const* name)
  {
    NI_ASSERT(lua_istable(L, -1), "Start table must be on the top of the stack"); 

    if (name[0])
    {
      char const* s = name;
      do
      {
        char buf[256];
        char const* d = strchr(s, '.');
        if (d)
        {
          strncpy(buf, s, min<size_t>(sizeof(buf)/sizeof(buf[0]), d - s + 1));
          ++d;              // skip '.'
        }
        else
        {
          strcpy(buf, s);
        }

        lua_pushstring(L, buf);
        strncpy(buf, s, sizeof(buf) / sizeof(buf[0]) );
        lua_gettable(L, -2);// Get required subtable
        if (!lua_istable(L, -1))
        {
          lua_pop(L, 2);
          return false;     // One of the subtables not found
        }
        lua_remove(L, -2);  // Drop the previous table
        s = d;              // continue with next name part
      } while (s);
    }
    return true;            // The table is on the stack
  }
  
  bool PrepareSubtablePath(lua_State* L, char const* name)
  {
    NI_ASSERT(lua_istable(L, -1), "Start table must be on the top of the stack"); 

    if(name[0])
    {
      char const* s = name;
      do
      {
        char buf[256];
        char const* d = strchr(s, '.');
        if (d)
        {
          strncpy(buf, s, min<size_t>(sizeof(buf)/sizeof(buf[0]), d - s + 1));
          ++d;                             // skip '.'
        }
        else
        {
          strcpy(buf, s );
        }

        lua_pushstring(L, buf);
        lua_gettable(L, -2);               // Get required subtable
        if (lua_isnil(L, -1))
        {
          lua_pop(L, 1);
          lua_newtable(L);                 // Create an empty table
          lua_pushstring(L, buf);          // The key
          lua_pushvalue(L, -2);            // dup the new empty table
          lua_settable(L, -4);             // Move the table to the upper one. A copy of a table is left on the stack
        }
        else 
          if (!lua_istable(L, -1))
          {
            systemLog(NLogg::LEVEL_ASSERT) << "Lua: cannot prepare table " << name << ": an object " 
              << buf << "already exists, but it's type is not a table" << endl;

            lua_pop(L, 1);
            return false;                    // error
          }
          lua_remove(L, -2);                 // Drop the previous table
          s = d;                             // continue with next name part
      } while(s);
    }
    return true;                           // The table is on the stack
  }

  bool PrepareTablePath(lua_State* L, char const* name)
  {
    LUA_NATIVE

    char const* s = strchr(name, '.');
    char buf[256];
    if(s)
    {
      strncpy(buf, name, min<size_t>( sizeof(buf)/sizeof(buf[0]), s - name + 1) );
      ++s;
    }
    else
    {
      strncpy(buf, name, sizeof(buf)/sizeof(buf[0]));
    }

    lua_pushstring(L, buf);
    lua_gettable(L, LUA_GLOBALSINDEX);
    if (lua_isnil(L, -1))
    {
      // table not yet exists
      lua_pop(L, 1);
      lua_newtable(L);                     // Create an empty table
      lua_pushstring(L, buf);              // The key
      lua_pushvalue(L, -2);                // dup the new empty tabls
      lua_settable(L, LUA_GLOBALSINDEX);   // Move the table to the registry. A copy of a table is left on the stack
    }
    else 
    if (!lua_istable(L, -1))
    {
      // object with such name exists, but it is not a table
      systemLog(NLogg::LEVEL_ASSERT) << "Lua: cannot prepare table " << name << ": an object " 
        << buf << "already exists, but it's type is not a table" << endl;

      lua_pop(L, 1);
      return false;                        // error
    }
    // else -- table already exists

      return (NULL != s) ? PrepareSubtablePath(L, s) : true;  // build rest of path
  }
  
  void* ObjectPtrFromMetaCall(lua_State* L, void* TargetClass)
  {
    // stack: self  <arguments...>
    if( void* rv = ObjectPtrFromMeta(L, TargetClass, 1))
    {
      bool isDestructorCall =lua_isuserdata(L, 1);
      lua_pop(L, 1);
      if(!isDestructorCall)
        lua_remove(L, 1);  // remove self so member function args start at index 1
      return rv;
    }
    return NULL;
  }

  bool GetObjectByWeakRef(lua_State* L, const void* object)
  {
    GetWeakreferencesTable(L);  
    NI_ASSERT(lua_istable(L, -1), "Object table must be present here");

    lua_pushlightuserdata(L, (void*)object);
    lua_gettable(L, -2);
    if(!lua_istable(L, -1))
    {
      lua_pop(L, 2);             // drop value and objects table
      return false;
    }

    lua_remove(L, -2);           // Drop the objects' table
    return true;
  }

  void MetatableToStack(lua_State* L, char const* className, LuaTypeInfo const* pTypeInfo)
  {
    LUA_STACK_CHECKER(L, 1)

    // Prepare the metatable for this class
    luaL_getmetatable(L, pTypeInfo->GetTypeName());  // lookup metatable in Lua registry

    // Stack +2
    if(lua_isnil(L, -1))
    {
      lua_pop(L, 1);// drop metatable
      
      lua_CFunction destoryer = ForbiddenDestroyer;
      for(int i = 0, count = pTypeInfo->GetMethodsCount(); i < count; ++i)
      {
        if(Lua::LuaMethodEntry const* pMethod = pTypeInfo->GetMethod(i) )
        {
          if( !strcmp(pMethod->Name(), LUA_DESTRUCTOR_NAME) )
          {
            destoryer = pMethod->Get();
            break;
          }
        }
      }
      
      PrepareClassMetatable(L, className, pTypeInfo, ForbiddenCreator, destoryer);

      luaL_getmetatable(L, pTypeInfo->GetTypeName());  // lookup metatable in Lua registry
      NI_ASSERT(lua_istable(L, -1), "The metatable must be assigned here");
    }
  }

  void ConnectMetatable(lua_State* L, char const* className, LuaTypeInfo const* pTypeInfo, void* pObject)
  {
    LUA_STACK_CHECKER(L, 0)
    
    // stack: table
    MetatableToStack(L, className, pTypeInfo);
   
    // stack: table  metatable
    UserdataToObject(L, pObject);
    lua_setmetatable(L, -2);                     // table._metatable = metatable
    // stack: <empty>
  }

  int PutWeakObjectToStack(lua_State* L, char const* className, LuaTypeInfo const* pTypeInfo, void* pObject)
  {
    LUA_STACK_CHECKER(L, 1);

    if(GetObjectByStrongRef(L, pObject) || GetObjectByWeakRef(L, pObject))
      return 1;// this is a unit or a PersistentTableLink, or ObjectTableLink

    // Reference does not exists. Create it now
    lua_newtable(L);
    ConnectMetatable(L, className, pTypeInfo, pObject );

    // Create the table on the registry and the weak link to it
    MakeWeakRef(L, pObject);

    return 1;
  }

  void* ObjectPtrFromMeta(lua_State *L, void* TargetClass, int nStackPos)
  {
    // useful stack information started with offset nStackPos
    // stack: self  <arguments...>
    if(lua_isnil(L, nStackPos) || lua_gettop(L) < nStackPos)
      return NULL;// It's OK - nil means NULL
    
    bool isTable = lua_istable(L, nStackPos);
    if(!isTable && !lua_isuserdata(L, nStackPos))
    {
      systemLog( NLogg::LEVEL_MESSAGE ) << "LUA: Failed to get object pointer - not a table on the stack! Stack pos: " << nStackPos << endl;
      return NULL;
    }

    if(nStackPos < 0)
    { // convert negative offset (from stack end) to positive (from stack start)
      nStackPos = lua_gettop(L) + nStackPos + 1;
    }

    if( isTable )
    {
      lua_pushlightuserdata(L, NULL);
      lua_gettable(L, nStackPos);
      // stack:  self  <arguments...>  self[luserdata(0)]
    }
    
    void **rv = static_cast<void**>(CheckUserData(L, -1, TargetClass));
    if(!rv)
    {
      systemLog( NLogg::LEVEL_MESSAGE ) <<  "LUA: Failed to get object pointer - no object link or wrong type! Stack pos: " << nStackPos << endl;
      return NULL;
    }

    return *rv;  // pointer to T object
  }

  void KillWeakRef(lua_State* L, void* pObject)
  {
    LUA_STACK_CHECKER(L, 0);
    
    GetWeakreferencesTable(L);  
    NI_ASSERT(lua_istable(L, -1), "Object table must be present here");

    lua_pushlightuserdata(L, pObject);
    lua_pushnil(L);
    lua_settable(L, -3);
    lua_pop(L, 1);// Drop the objects table
  }

  string GetLuaCallStack(lua_State* pState, int startLevel)
  {
    if(NULL != pState)
    {
      string result = "LUA Call stack: \n";
      lua_Debug DebugInfo;
      while (lua_getstack(pState, startLevel++, &DebugInfo))
      {
        lua_getinfo(pState, "lnS", &DebugInfo);
        if (!strcmp(DebugInfo.what, "C"))
          result += NStr::StrFmt("  C: %s", DebugInfo.name ? DebugInfo.name : "<unknown>");
        else
        {
          result += NStr::StrFmt("     %s %s %s %s:",
            DebugInfo.what, 
            DebugInfo.namewhat[0] ? DebugInfo.namewhat : "",
            DebugInfo.name ? DebugInfo.name : "<unknown>", 
            DebugInfo.short_src);
        
          if( -1 != DebugInfo.currentline)
            result += NStr::StrFmt("%d\n", DebugInfo.currentline);
          else
            result += "<unknown>\n";
        }
      } 

      return result;
    }

    NI_ALWAYS_ASSERT("Invalid LUA state!")
    return string();
  }

  StackChecker::StackChecker(lua_State* pState, int offset)
    : pState(pState)
    , requiredTop(lua_gettop(pState) + offset)
  {
  }

  StackChecker::~StackChecker()
  {
    int currentTop = lua_gettop(pState);
    NI_ASSERT(currentTop == requiredTop, "Lua stack disbalanced!");
  }

  NDebug::PerformanceDebugVar lua_native( "LUA.Native", "MainPerf", 10, 10, true );
  NDebug::PerformanceDebugVar lua_script( "LUA.Script", "MainPerf", 10, 10, true );
  
  void OnEnterLuaScript()
  {
    lua_script.Start();
  }

  void OnLeaveLuaScript()
  {
    lua_script.Stop();
  }

  void OnEnterLuaNative()
  {
    lua_native.Start();
  }

  void OnLeaveLuaNative()
  {
    lua_native.Stop();
  }



} // namespace Lua
