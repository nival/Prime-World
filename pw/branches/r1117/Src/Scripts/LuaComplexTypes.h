#pragma once

#include "LuaValues.h"
#include "lua.hpp"

namespace NScript
{
  class NamedValues;
}

namespace Lua
{
  
  template<> struct lua_values<CVec3>
  {
    static CVec3          get(lua_State *L, int idx);
    static int            put(lua_State *L, CVec3 const& value);
  };

  template<> struct lua_values<CTPoint<int> >
  {
    static CTPoint<int>   get(lua_State *L, int idx);
    static int            put(lua_State *L, CTPoint<int> const& value);
  };
  
  template<> struct lua_values<CTPoint<float> >
  {
    static CTPoint<float> get(lua_State *L, int idx);
    static int            put(lua_State *L, CTPoint<float> const& value);
  };

  template<> struct lua_values<CTRect<int> >
  {
    static CTRect<int>    get(lua_State *L, int idx);
    static int            put(lua_State *L, CTRect<int> const& value);
  };

  template<> struct lua_values<CTRect<float> >
  {
    static CTRect<float>  get(lua_State *L, int idx);
    static int            put(lua_State *L, CTRect<float> const& value);
  };

  template<> struct lua_values<wstring>
  {
    static wstring        get(lua_State *L, int idx);
    static int            put(lua_State *L, wstring const& value);
  };

  template<> struct lua_values<const wstring &>
  {
    static wstring        get(lua_State *L, int idx);
    static int            put(lua_State *L, wstring const& value);
  };
  
  template<> struct lua_values<NScript::NamedValues>
  {
    static int            put(lua_State *L, NScript::NamedValues const& value);
  };

  template<class T> struct lua_values<T*>
  {
    static T* get(lua_State *L, int idx)
    {
      T* pObject = reinterpret_cast<T*>( ObjectPtrFromMeta(L, (void*)NULL, idx) );
      return pObject;
    }

    static int    put(lua_State *L, T* value)
    {
      if( Lua::LuaTypeInfo const* pTypeInfo = value ? value->QueryLuaTypeInfo() : NULL )
        if(int result = PutWeakObjectToStack(L, pTypeInfo->GetTypeName(), pTypeInfo, value->QueryNativeLuaObject() ) )
          return result;
      lua_pushnil(L);
      return 1;
    }
  };

  template<class T> struct lua_values<T const*>
  {
    static T const* get(lua_State *L, int idx)
    {
      T const* pObject = reinterpret_cast<T const*>( ObjectPtrFromMeta(L, (void*)NULL, idx) );
      return pObject;
    }
    static int    put(lua_State *L, T const* value)
    {
      if( Lua::LuaTypeInfo const* pTypeInfo = value ? value->QueryLuaTypeInfo() : NULL )
        if(int result = PutWeakObjectToStack(L, pTypeInfo->GetTypeName(), pTypeInfo, value->QueryNativeLuaObject() ) )
          return result;
      lua_pushnil(L);
      return 1;
    }
  };

  template<class TKey, class TValue> struct lua_values< const map<TKey, TValue> & >
  {
    typedef map<TKey, TValue> TMapType;

    static TMapType get( lua_State *L, int idx )
    {
      TMapType result;
      if ( CheckStackParameterIdx( L, idx ) )
      {
        if ( lua_istable( L, idx ) )
        {
          lua_pushvalue( L, idx );
          for ( lua_pushnil( L ); lua_next( L, -2 ) != 0; lua_pop( L, 1 ) )
            result.insert( TMapType::value_type( lua_values<TKey>::get( L, -2 ), lua_values<TValue>::get( L, -1 ) ) );
          lua_pop( L, 1 );
        }
      }
      return result;
    }

    static int put( lua_State *L, const TMapType & value )
    {
      lua_createtable( L, 0, value.size() );
      for( TMapType::iterator it = value.begin(); it != value.end(); ++it )
      {
        lua_values<TKey>::put( L, it->first );
        lua_values<TValue>::put( L, it->second );
        lua_settable( L, -3 );
      }
      return 1;
    }
  };

  template<class TKey, class TValue> struct lua_values< map<TKey, TValue> >
  {
    typedef map<TKey, TValue> TMapType;

    static TMapType get( lua_State *L, int idx )
    {
      return lua_values< const TMapType & >::get( L, idx);
    }

    static int put( lua_State *L, const TMapType & value )
    {
      return lua_values< const TMapType & >::put( L, value );
    }
  };
}
