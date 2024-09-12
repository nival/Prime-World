#include "stdafx.h"
#include "LuaComplexTypes.h"

#include "../System/Texts.h"
#include "../Scripts/NameMap.h"
#include "LuaBase.h"

#define TABLE2VALUE(val, idx)                                                                           \
  lua_pushstring(L, #val);                                                                              \
  lua_gettable(L, idx);                                                                                 \
  if(!lua_isnumber(L, -1))                                                                              \
  {                                                                                                     \
    systemLog( NLogg::LEVEL_ASSERT ) << "Lua table transfer: " << #val << " is not a number!" << endl; \
  }                                                                                                     \
  else                                                                                                  \
    result.val = static_cast<float>(lua_tonumber(L, -1));                                               \
  lua_pop(L, 1);// balance the stack

#define VALUE2TABLE(val)                                                                                \
  lua_pushstring(L, #val);                                                                              \
  lua_pushnumber(L, value.val);                                                                         \
  lua_settable(L, -3);

#define NORMALIZE_INDEX() if(idx < 0 ) { idx = lua_gettop(L) + idx + 1; } else {;}

namespace Lua
{
  CVec3         lua_values<CVec3>::get(lua_State *L, int idx)
  {
    CVec3 result = CVec3(0, 0, 0);
    if( CheckStackParameterIdx(L, idx) )
    {
      NORMALIZE_INDEX();
      
      TABLE2VALUE(x, idx);
      TABLE2VALUE(y, idx);
      TABLE2VALUE(z, idx);
    }

    return result;
  }
  
  int           lua_values<CVec3>::put(lua_State *L, CVec3 const& value)
  {
    LUA_NATIVE
    LUA_STACK_CHECKER(L, 1)

    lua_getfield(L, LUA_GLOBALSINDEX, "Vector3");
    if(lua_isfunction(L, -1))
    {
      lua_pushnumber(L, value.x);
      lua_pushnumber(L, value.y);
      lua_pushnumber(L, value.z);
      lua_call(L, 3, 1);
    }
    else
    {
      systemLog( NLogg::LEVEL_ASSERT ) << "Lua table transfer: failed to transfer CVec3 correctly!" << endl; 
      // Prepare table
      lua_createtable(L, 0, 3);

      VALUE2TABLE(x);
      VALUE2TABLE(y);
      VALUE2TABLE(z);
    }

    return 1;
  }
  
  CTPoint<int>   lua_values<CTPoint<int> >::get(lua_State *L, int idx)
  {
    CTPoint<int> result = CTPoint<int>(0, 0);
    if( CheckStackParameterIdx(L, idx) )
    {
      NORMALIZE_INDEX();

      TABLE2VALUE(x, idx);
      TABLE2VALUE(y, idx);
    }

    return result;
  }

  int            lua_values<CTPoint<int> >::put(lua_State *L, CTPoint<int> const& value)
  {   
    LUA_NATIVE
    LUA_STACK_CHECKER(L, 1)

    lua_getfield(L, LUA_GLOBALSINDEX, "Point");
    if(lua_isfunction(L, -1))
    {
      lua_pushnumber(L, value.x);
      lua_pushnumber(L, value.y);
      lua_call(L, 2, 1);
    }
    else
    {
      systemLog( NLogg::LEVEL_ASSERT ) << "Lua table transfer: failed to transfer CTPoint correctly!" << endl; 

      lua_createtable(L, 0, 2);

      VALUE2TABLE(x);
      VALUE2TABLE(y);
    }
    
    return 1;
  }
 
  CTPoint<float>   lua_values<CTPoint<float> >::get(lua_State *L, int idx)
  {
    CTPoint<float> result = CTPoint<float>(0.0f, 0.0f);
    if( CheckStackParameterIdx(L, idx) )
    {
      NORMALIZE_INDEX();

      TABLE2VALUE(x, idx);
      TABLE2VALUE(y, idx);
    }

    return result;
  }

  int            lua_values<CTPoint<float> >::put(lua_State *L, CTPoint<float> const& value)
  {
    LUA_NATIVE
    LUA_STACK_CHECKER(L, 1)

    lua_getfield(L, LUA_GLOBALSINDEX, "Point");
    if(lua_isfunction(L, -1))
    {
      lua_pushnumber(L, value.x);
      lua_pushnumber(L, value.y);
      lua_call(L, 2, 1);
    }
    else
    {
      systemLog( NLogg::LEVEL_ASSERT ) << "Lua table transfer: failed to transfer CTPoint correctly!" << endl; 

      lua_createtable(L, 0, 2);

      VALUE2TABLE(x);
      VALUE2TABLE(y);
    }

    return 1;
  }
  
  CTRect<int>   lua_values<CTRect<int> >::get(lua_State *L, int idx)
  {
    CTRect<int> result = CTRect<int>(0, 0, 0, 0);
    if( CheckStackParameterIdx(L, idx) )
    {
      NORMALIZE_INDEX();

      TABLE2VALUE(x1,     idx);
      TABLE2VALUE(y1,     idx);
      TABLE2VALUE(x2,     idx);
      TABLE2VALUE(y2,     idx);
    }

    return result;
  }

  int            lua_values<CTRect<int> >::put(lua_State *L, CTRect<int> const& value)
  {
    LUA_NATIVE
    LUA_STACK_CHECKER(L, 1)

    lua_getfield(L, LUA_GLOBALSINDEX, "Rect");
    if(lua_isfunction(L, -1))
    {
      lua_pushnumber(L, value.x1);
      lua_pushnumber(L, value.y1);
      lua_pushnumber(L, value.x2);
      lua_pushnumber(L, value.y2);

      lua_call(L, 4, 1);
    }
    else
    {
      systemLog( NLogg::LEVEL_ASSERT ) << "Lua table transfer: failed to transfer CTPoint correctly!" << endl; 

      lua_createtable(L, 0, 4);

      VALUE2TABLE(x1);
      VALUE2TABLE(y1);
      VALUE2TABLE(x2);
      VALUE2TABLE(y2);
    }
    
    return 1;
  }

  CTRect<float>   lua_values<CTRect<float> >::get(lua_State *L, int idx)
  {
    CTRect<float> result = CTRect<float>(0.0f, 0.0f, 0.0f, 0.0f);
    if( CheckStackParameterIdx(L, idx) )
    {
      NORMALIZE_INDEX();

      TABLE2VALUE(x1,     idx);
      TABLE2VALUE(y1,     idx);
      TABLE2VALUE(x2,     idx);
      TABLE2VALUE(y2,     idx);
    }

    return result;
  }

  int            lua_values<CTRect<float> >::put(lua_State *L, CTRect<float> const& value)
  {
    LUA_NATIVE
    LUA_STACK_CHECKER(L, 1)

    lua_getfield(L, LUA_GLOBALSINDEX, "Rect");
    if(lua_isfunction(L, -1))
    {
      lua_pushnumber(L, value.x1);
      lua_pushnumber(L, value.y1);
      lua_pushnumber(L, value.x2);
      lua_pushnumber(L, value.y2);

      lua_call(L, 4, 1);
    }
    else
    {
      systemLog( NLogg::LEVEL_ASSERT ) << "Lua table transfer: failed to transfer CTPoint correctly!" << endl; 

      lua_createtable(L, 0, 4);

      VALUE2TABLE(x1);
      VALUE2TABLE(y1);
      VALUE2TABLE(x2);
      VALUE2TABLE(y2);
    }

    return 1;
  }

  wstring lua_values<const wstring &>::get(lua_State *L, int idx)
  {
    wstring result;

    if( CheckStackParameterIdx(L, idx) )
    {
      NORMALIZE_INDEX();

      int length = 0;
      lua_pushstring(L, "size");   
      lua_gettable(L,   idx);
      if(lua_isnumber(L, -1))
        length = static_cast<int>(lua_tonumber(L, -1));

      lua_pushstring(L, "c_wstr");
      lua_gettable(L,   idx);
      if(!lua_isnil(L, -1))
        if( wchar_t const* data = reinterpret_cast<wchar_t const*>(lua_tostring(L, -1)) )
          result.assign(data, length);
    }

    return result;
  }

  int lua_values<const wstring &>::put(lua_State *L, wstring const& value)
  {
    lua_createtable(L, 0, 4);
    
    lua_pushstring(L, "size");                                                                                  
    lua_pushnumber(L, value.size());                                                                            
    lua_settable(L, -3);

    lua_pushstring(L, "empty");                                                                                 
    lua_pushnumber(L, value.empty());                                                                           
    lua_settable(L, -3);

    lua_pushstring(L, "toNumber");                                                                              
    lua_pushnumber(L, NStr::ToInt(value));                                                                      
    lua_settable(L, -3);

    lua_pushstring(L, "c_wstr");
    lua_pushlstring(L, reinterpret_cast<char const*>(value.c_str()), value.size() * 2);
    lua_settable(L, -3);

    return 1;
  }


  wstring lua_values<wstring>::get(lua_State *L, int idx)
  {
    return lua_values<const wstring &>::get( L, idx );
  }

  int lua_values<wstring>::put(lua_State *L, wstring const& value)
  {
    return lua_values<const wstring &>::put( L, value );
  }
  
  class NullType {};
  template<> struct lua_values<NullType> { static int put(lua_State *L, NullType const& value) { return 0; } };

  template<int> struct VarTypeHelper                                
  { 
    typedef NullType type; 
    static  NullType ExtractValue(NScript::VariantValue const& /*value*/) { return NullType(); }
  };

  template<>    struct VarTypeHelper<NScript::VariantValue::BOOL>   
  { 
    typedef bool type; 
    static  bool ExtractValue(NScript::VariantValue const& value) { return value.GetBool(); }
  };

  template<>    struct VarTypeHelper<NScript::VariantValue::INT>    { typedef int      type; };
  template<>    struct VarTypeHelper<NScript::VariantValue::FLOAT>  { typedef float    type; };
  template<>    struct VarTypeHelper<NScript::VariantValue::STRING> { typedef string   type; };
  template<>    struct VarTypeHelper<NScript::VariantValue::TEXT>   { typedef wstring  type; };
  
  int            lua_values<NScript::NamedValues>::put(lua_State *L, NScript::NamedValues const& value)
  {
    LUA_STACK_CHECKER(L, 1)
    lua_newtable(L);

    for( NScript::NamedValuesConstIterator it( value ); it.Valid(); ++it )
    {
      switch(it.GetValue().GetType())
      {
      case NScript::VariantValue::BOOL:
        lua_pushstring(L, it.GetKey().c_str());
        lua_pushboolean(L, it.GetValue().GetBool());
        lua_settable(L, -3);
        break;
      case NScript::VariantValue::INT: 
        lua_pushstring(L, it.GetKey().c_str());
        lua_pushnumber(L, it.GetValue().GetInt());
        lua_settable(L, -3);
        break;
      case NScript::VariantValue::FLOAT: 
        lua_pushstring(L, it.GetKey().c_str());
        lua_pushnumber(L, it.GetValue().GetFloat());
        lua_settable(L, -3);
        break;
      case NScript::VariantValue::STRING:
        lua_pushstring(L, it.GetKey().c_str());
        lua_pushstring(L, it.GetValue().GetString().c_str());
        lua_settable(L, -3);
        break;
      case NScript::VariantValue::TEXT:
        lua_pushstring(L, it.GetKey().c_str());
        lua_values<wstring>::put(L, it.GetValue().GetText() );
        lua_settable(L, -3);
        break;
      default:
        NI_ALWAYS_ASSERT( "Invalid named values item type" );
        break;
      }
    }

    return 1;
  }


} // namespace Lua
