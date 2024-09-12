#include "stdafx.h"

#include "PFAIContainer.h"
#include "LuaScript.h"

#include "PFWorld.h"
#include "PFPlayer.h"
#include "AdventureScreen.h"
#include "PFHero.h"
#include "HeroSpawn.h"
#include "PFMaleHero.h"
#include "PFCheat.h"
#include "HeroActions.h"
#include "PFCreep.h"
#include "PFCommonCreep.h"
#include "PFNeutralCreep.h"
#include "PFMainBuilding.h"
#include "PFSimpleObject.h"
#include "PFFlagPole.h"
#include "PFTree.h"
#include "PFImpulsiveBuffs.h"
#include "Client/MainTimer.h"
#include "System/MainFrame.h"
#include "PFTalent.h"
#include "PFGlyph.h"
#include "PFWorldNatureMap.h"
#include "PFScriptedFlagpole.h"
#include "PFApplSpecial.h"
#include "ForceCalc.h"

#include "Scripts/Script.h"
#include "Scripts/lua.hpp"
#include "Scripts/LuaConstants.h"
#include "Scripts/ScriptMacroses.h"
#include "Scripts/FuncCallMacroses.h"

#include "MoveToCameraController.h"
#include "SplineCameraController.h"
#include "AdventureCameraController.hpp"
#include "AdventureScreenLogic.h"
#include "ShopController.h"
#include "Scene/Camera.h"
#include "Scene/CameraControllersContainer.h"
#include "PFClientVisibilityMap.h"
#include "PFConsumable.h"
#include "Render/AOERenderer.h"
#include "..\PF_Core\EffectsPool.h"
#include "PFClientHero.h"
#include "ObjectsInfo2d.h"

#include "UIBlockingController.h"
#include "System/InlineProfiler.h"
#include "SessionEventType.h"
#include "GameLogicStatisticsTypes.h"
#include "System/GeomMisc.h"

#include "PW_Client/GameStatGuard.h"

bool g_logLuaCalls = false;
REGISTER_DEV_VAR( "log_lua_calls", g_logLuaCalls, STORAGE_NONE );
bool g_enableLuaSerialization = true;
REGISTER_DEV_VAR( "enable_lua_serialization", g_enableLuaSerialization, STORAGE_NONE );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Lua functionality (temporary all in one file)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const string& GetCallInfo( lua_State* L )
{
  static string callInfo;

  lua_Debug ar;
  const int MAX_FRAME_CNT = 5;
  int frameCnt = 1;
  while ( frameCnt < MAX_FRAME_CNT )
  {
    if ( lua_getstack( L, frameCnt, &ar ) == 0 )
      break;
    lua_getinfo( L, "nSl", &ar );
    if ( ar.name == NULL )
      break;

    if ( frameCnt == 1 )
      callInfo = string(ar.short_src) + ":" + NStr::IntToStr(ar.currentline) ;
    else 
      callInfo += string("<-") + ar.name;

    ++frameCnt;
  }
  callInfo += ": ";

  return callInfo;
}

#ifdef _SHIPPING
#define  LUA_VERIFY( expr, user_text, statement ) NI_VERIFY( expr, user_text, statement ) 
#else
#define  LUA_VERIFY( expr, user_text, statement )  \
{ const bool bCheck = (expr); if (!bCheck) { string msg = GetCallInfo(L) + (user_text); NI_FORCE_ASSERT( bCheck, NLogg::LEVEL_ASSERT, #expr, msg.c_str() ); } if ( !bCheck ) { statement; } }
#endif

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char * LuaTypeToString(int type)
{
  switch (type)
  {
  case LUA_TNIL:
    return "Nil";
  case LUA_TBOOLEAN:
    return "Boolean";
  case LUA_TLIGHTUSERDATA:
    return "Light User Data";
  case LUA_TNUMBER:
    return "Number";
  case LUA_TSTRING:
    return "String";
  case LUA_TTABLE:
    return "Table";
  case LUA_TFUNCTION:
    return "Function";
  case LUA_TUSERDATA:
    return "User Data";
  case LUA_TTHREAD:
    return "Thread";
  }
  return "<Unknown>";
}

bool CheckStackParameterType(lua_State *L, int idx, int type, const char * func)
{
  LUA_VERIFY( lua_type( L, idx ) == type, 
    NStr::StrFmt("%s: type mismatch for parameter %d, %s received, while %s expected", 
                    func, idx, LuaTypeToString(lua_type( L, idx )), LuaTypeToString(type)), return false );
  return true;
}


void luaValueSetter::Set(lua_State *L, const char* value)
{
  lua_pushstring(L, value);
}

void luaValueSetter::Set(lua_State *L, double value)
{
  lua_pushnumber(L, value);
}

void luaValueSetter::Set(lua_State *L, float value)
{
  lua_pushnumber(L, static_cast<lua_Number>(value));
}

void luaValueSetter::Set(lua_State *L, int value)
{
  lua_pushnumber(L, static_cast<lua_Number>(value));
}

void luaValueSetter::Set(lua_State *L, bool value)
{
  lua_pushboolean(L, value);
}

void luaValueSetter::Set(lua_State *L, const string& value)
{
  lua_pushstring(L, value.c_str());
}

void luaValueSetter::Set(lua_State *L, const ILuaValueSettable& value)
{
  value.Set( L );
}

void luaValueSetter::Set(lua_State *L, const CVec2& value)
{
  lua_createtable( L, 0, 2 );
  LUA_VALUE_SETTABLE_PROPERTY_EX( "x", value.x )
  LUA_VALUE_SETTABLE_PROPERTY_EX( "y", value.y )
}

void luaValueSetter::Set(lua_State *L, const CVec3& value)
{
  lua_createtable( L, 0, 3 );
  LUA_VALUE_SETTABLE_PROPERTY_EX( "x", value.x )
  LUA_VALUE_SETTABLE_PROPERTY_EX( "y", value.y )
  LUA_VALUE_SETTABLE_PROPERTY_EX( "z", value.z )
}

template<class T> struct luaValue;

template<> struct luaValue<const char *>
{
  static bool Get(lua_State *L, int idx, const char** value, const char* func);
  static void Set(lua_State *L, const char* value);
};

template<> struct luaValue<int>
{
  static bool Get(lua_State *L, int idx, int* value, const char* func);
  static void Set(lua_State *L, int value);
};

template<> struct luaValue<float>
{
  static bool Get(lua_State *L, int idx, float* value, const char* func);
  static void Set(lua_State *L, float value);
};

template<> struct luaValue<double>
{
  static bool Get(lua_State *L, int idx, double* value, const char* func);
  static void Set(lua_State *L, double value);
};

template<> struct luaValue<bool>
{
  static bool Get(lua_State *L, int idx, bool* value, const char* func);
  static void Set(lua_State *L, bool value);
};
template<class T> struct luaValue<vector<T>>
{
  static bool Get(lua_State *L, int idx, vector<T>* value, const char* func);
  static void Set(lua_State *L, const vector<T>& value);
};

struct LuaUnitIdParam
{
  LuaUnitIdParam() : pStrValue(0), objId(0) {}

  const char* pStrValue;
  int objId;
};

template<> struct luaValue<LuaUnitIdParam>
{
  static bool Get(lua_State *L, int idx, LuaUnitIdParam* value, const char* func);
};

struct OtherArgs
{
  vector<string> args;
  vector<int> types;
};

template<> struct luaValue<OtherArgs>
{
  static bool Get(lua_State *L, int idx, OtherArgs* value, const char* func);
  static void Set(lua_State *L, OtherArgs value);
};

bool luaValue<const char*>::Get(lua_State *L, int idx, const char** value, const char * func)
{
  if (CheckStackParameterType(L, idx, LUA_TSTRING, func))
  {
    NI_VERIFY( *value = lua_tostring(L, idx), 
      NStr::StrFmt("%s: failed to get the parameter %d", func, idx), return false );
    return true;
  }
  return false;
}

void luaValue<const char*>::Set(lua_State *L, const char* value)
{
  lua_pushstring(L, value);
}

bool luaValue<int>::Get(lua_State *L, int idx, int* value, const char * func)
{
  if (CheckStackParameterType(L, idx, LUA_TNUMBER, func))
  {
    *value = static_cast<int>(lua_tonumber(L, idx));
    return true;
  }
  return false;
}

void luaValue<int>::Set(lua_State *L, int value)
{
  lua_pushnumber(L,static_cast<lua_Number>(value));
}

bool luaValue<float>::Get(lua_State *L, int idx, float* value, const char * func)
{
  if (CheckStackParameterType(L, idx, LUA_TNUMBER, func))
  {
    *value = static_cast<float>(lua_tonumber(L, idx));
    return true;
  }
  return false;
}

void luaValue<float>::Set(lua_State *L, float value)
{
  lua_pushnumber(L,static_cast<lua_Number>(value));
}

bool luaValue<double>::Get(lua_State *L, int idx, double* value, const char * func)
{
  if (CheckStackParameterType(L, idx, LUA_TNUMBER, func))
  {
    *value = lua_tonumber(L, idx);
    return true;
  }
  return false;
}

void luaValue<double>::Set(lua_State *L, double value)
{
  lua_pushnumber(L, value);
}

bool luaValue<bool>::Get(lua_State *L, int idx, bool* value, const char * func)
{
  if (CheckStackParameterType(L, idx, LUA_TBOOLEAN, func))
  {
    *value = lua_toboolean(L, idx);
    return true;
  }
  return false;
}

void luaValue<bool>::Set(lua_State *L, bool value)
{
  lua_pushboolean(L, value);
}

template<class T>
bool luaValue<vector<T>>::Get(lua_State *L, int idx, vector<T>* value, const char * func)
{
  if (CheckStackParameterType(L, idx, LUA_TTABLE, func))
  {
    int sz = lua_objlen(L, idx );
    value->resize(sz);
    for ( int i = 0; i < sz; ++i )
    {
      lua_pushinteger( L, i+1 );
      lua_gettable( L, idx );
      luaValue<T>::Get( L, -1, value->begin() + i, func );
    }
    return true;
  }
  return false;
}

bool luaValue<OtherArgs>::Get(lua_State *L, int idx, OtherArgs* value, const char* func)
{
  int nargs = lua_gettop(L) - idx + 1;
  value->args.resize(nargs);
  value->types.resize(nargs);

  for ( int i = 0; i < nargs; ++i )
  {
    value->types[i] = lua_type( L, idx + i );
    value->args[i] = lua_tostring(L, idx + i );
    
  }
  return true;
}

bool luaValue<LuaUnitIdParam>::Get(lua_State *L, int idx, LuaUnitIdParam* value, const char* func)
{
  int luaType = lua_type( L, idx );

  if ( luaType != LUA_TNUMBER && luaType != LUA_TSTRING )
  {
    NI_ALWAYS_ASSERT( NStr::StrFmt("%s: type mismatch for parameter %d, %s received, while string or int expected", func, idx, LuaTypeToString(luaType) ) );
    return false;
  }

  value->pStrValue = lua_tostring( L, idx );

  if ( luaType == LUA_TNUMBER )
  {
    value->objId = static_cast<int>(lua_tonumber( L, idx ));
  }

  return true;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class LuaParamVariant : public NNameMap::Variant, NonCopyable
{
public:
  LuaParamVariant( const string& value, int _type )
    : value(value)
    , type(NNameMap::VariantType::None)
  {
    if ( _type == LUA_TSTRING )
      type = NNameMap::VariantType::String;
    else if ( _type == LUA_TNUMBER )
    {
      type = NStr::IsDecNumber(value) ? NNameMap::VariantType::Int : NNameMap::VariantType::Float;
    }
  }

  virtual float GetFloat() const
  {
    if ( type != NNameMap::VariantType::Int && type != NNameMap::VariantType::Float )
      return 0.0f;

    return NStr::ToFloat( value );
  }

  virtual int GetInt() const
  {
    if ( type != NNameMap::VariantType::Int )
      return 0;

    return NStr::ToInt( value );
  }

  virtual bool GetBool() const
  {
    return !value.empty() && value != "0";
  }

  virtual NNameMap::VariantType::Enum GetType() const { return type; }
  virtual bool IsReadonly() const                     { return true; }

private:
  string value;
  NNameMap::VariantType::Enum type;
};

struct LuaParamsNameMap : NNameMap::Map
{
protected:
  virtual bool ResolveNameByMacro ( const char * _mapElementName, int _mapElementNameLength, const char * _mapElementArgs, int _mapElementArgsLength, NNameMap::Map ** ppMap, NNameMap::Variant ** ppVariant, void* prms, bool _readonlyNeeded ) { return 0; }
  virtual NNameMap::Variant * ResolveVariant( const char * name, int length, const char * args, int argsLength, void* prms, bool readonly )
  {
    for ( int i = 0; i < pArgs->args.size(); i += 2 )
    {
      if ( i+1 >= pArgs->args.size() )
        continue;
      if ( pArgs->args[i] == name )
        return new LuaParamVariant( pArgs->args[i+1], pArgs->types[i+1] );
    }
    return 0;
  }
public:
  LuaParamsNameMap(OtherArgs const* _pArgs) : pArgs(_pArgs) {}
private:
  OtherArgs const* pArgs;
};

namespace NWorld
{

static NScript::LuaFunctionsList scriptFunctionsList;
PFScript * GetLuaScript()
{
  return PFAIContainer::s_luaScript;
}

Weak<PFScript> PFAIContainer::s_luaScript;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFBaseUnit* FindUnit( PFAIContainer* pAIContainer, const ::LuaUnitIdParam& unit )
{
  if ( unit.objId )
  {
    return dynamic_cast<PFBaseUnit*>(pAIContainer->GetWorld()->GetObjectById( unit.objId ));
  }

  return pAIContainer->FindUnit( unit.pStrValue );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _GET_LUA_ARG( argType, index )                                                                                       \
  argType arg##index;                                                                                                        \
  if( !luaValue<argType>::Get(L, index, &arg##index, __FUNCTION__) ) return 0;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _GET_LUA_ARG_COUNT()                                                                                       \
  lua_gettop(L)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define ADD_LUA2CPP_FUNCTION( name )                                                                                         \
static struct AddScriptFunction_##__LINE__##_##name                                                                          \
{                                                                                                                            \
  AddScriptFunction_##__LINE__##_##name##()                                                                                  \
  {                                                                                                                          \
    scriptFunctionsList[#name] = name;                                                                                       \
  }                                                                                                                          \
} addScriptFunction_##__LINE__##_##name##;


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _START_LUA2CPP_FUNCTION_HEAD( name, argsCount )                                                                      \
int name( lua_State * L );                                                                                                   \
ADD_LUA2CPP_FUNCTION(name)                                                                                                   \
int name( lua_State * L )                                                                                                    \
{                                                                                                                            \
  if (g_logLuaCalls) DebugTrace( "[LUA] " #name );                                                                           \
  PFScript * pScript = GetLuaScript();                                                                                       \
  NI_VERIFY( pScript, #name " failed to get script object!", return 0 );                                                     \
  PFAIContainer * pAIContainer = pScript->GetAIContainer();                                                                  \
  NI_VERIFY( pAIContainer, #name " failed to get AIContainer object!", return 0 );                                           \
  LUA_VERIFY( lua_gettop(L) >= argsCount, #name " takes " #argsCount " parameters", return 0 );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define START_LUA2CPP_FUNCTION( name )                                                                                       \
  _START_LUA2CPP_FUNCTION_HEAD( name, 0 )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define START_LUA2CPP_FUNCTION_ARG1( name, arg1type )                                                                        \
  _START_LUA2CPP_FUNCTION_HEAD( name, 1 )                                                                                    \
  _GET_LUA_ARG( arg1type, 1 )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define START_LUA2CPP_FUNCTION_ARG2( name, arg1type, arg2type )                                                              \
  _START_LUA2CPP_FUNCTION_HEAD( name, 2 )                                                                                    \
  _GET_LUA_ARG( arg1type, 1 )                                                                                                \
  _GET_LUA_ARG( arg2type, 2 )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define START_LUA2CPP_FUNCTION_ARG3( name, arg1type, arg2type, arg3type )                                                    \
  _START_LUA2CPP_FUNCTION_HEAD( name, 3 )                                                                                    \
  _GET_LUA_ARG( arg1type, 1 )                                                                                                \
  _GET_LUA_ARG( arg2type, 2 )                                                                                                \
  _GET_LUA_ARG( arg3type, 3 )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define START_LUA2CPP_FUNCTION_ARG4( name, arg1type, arg2type, arg3type, arg4type )                                          \
  _START_LUA2CPP_FUNCTION_HEAD( name, 4 )                                                                                    \
  _GET_LUA_ARG( arg1type, 1 )                                                                                                \
  _GET_LUA_ARG( arg2type, 2 )                                                                                                \
  _GET_LUA_ARG( arg3type, 3 )                                                                                                \
  _GET_LUA_ARG( arg4type, 4 )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define START_LUA2CPP_FUNCTION_ARG5( name, arg1type, arg2type, arg3type, arg4type, arg5type )                                \
  _START_LUA2CPP_FUNCTION_HEAD( name, 5 )                                                                                    \
  _GET_LUA_ARG( arg1type, 1 )                                                                                                \
  _GET_LUA_ARG( arg2type, 2 )                                                                                                \
  _GET_LUA_ARG( arg3type, 3 )                                                                                                \
  _GET_LUA_ARG( arg4type, 4 )                                                                                                \
  _GET_LUA_ARG( arg5type, 5 )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define START_LUA2CPP_FUNCTION_ARG6( name, arg1type, arg2type, arg3type, arg4type, arg5type, arg6type )                      \
  _START_LUA2CPP_FUNCTION_HEAD( name, 6 )                                                                                    \
  _GET_LUA_ARG( arg1type, 1 )                                                                                                \
  _GET_LUA_ARG( arg2type, 2 )                                                                                                \
  _GET_LUA_ARG( arg3type, 3 )                                                                                                \
  _GET_LUA_ARG( arg4type, 4 )                                                                                                \
  _GET_LUA_ARG( arg5type, 5 )                                                                                                \
  _GET_LUA_ARG( arg6type, 6 )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define START_LUA2CPP_FUNCTION_ARG7( name, arg1type, arg2type, arg3type, arg4type, arg5type, arg6type, arg7type )            \
  _START_LUA2CPP_FUNCTION_HEAD( name, 7 )                                                                                    \
  _GET_LUA_ARG( arg1type, 1 )                                                                                                \
  _GET_LUA_ARG( arg2type, 2 )                                                                                                \
  _GET_LUA_ARG( arg3type, 3 )                                                                                                \
  _GET_LUA_ARG( arg4type, 4 )                                                                                                \
  _GET_LUA_ARG( arg5type, 5 )                                                                                                \
  _GET_LUA_ARG( arg6type, 6 )                                                                                                \
  _GET_LUA_ARG( arg7type, 7 )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define END_LUA2CPP_FUNCTION                                                                                                 \
  return 0;                                                                                                                  \
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define _SET_LUA_RET( ret )                                                                                                  \
  luaValueSetter::Set( L, ret );

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define END_LUA2CPP_FUNCTION_RET1( ret1 )                                                                                    \
  _SET_LUA_RET( ret1 )                                                                                                       \
  return 1;                                                                                                                  \
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define END_LUA2CPP_FUNCTION_RET2( ret1, ret2 )                                                                              \
  _SET_LUA_RET( ret1 )                                                                                                       \
  _SET_LUA_RET( ret2 )                                                                                                       \
  return 2;                                                                                                                  \
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define END_LUA2CPP_FUNCTION_RET3( ret1, ret2, ret3 )                                                                        \
  _SET_LUA_RET( ret1 )                                                                                                       \
  _SET_LUA_RET( ret2 )                                                                                                       \
  _SET_LUA_RET( ret3 )                                                                                                       \
  return 3;                                                                                                                  \
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define END_LUA2CPP_FUNCTION_RET4( ret1, ret2, ret3, ret4 )                                                                  \
  _SET_LUA_RET( ret1 )                                                                                                       \
  _SET_LUA_RET( ret2 )                                                                                                       \
  _SET_LUA_RET( ret3 )                                                                                                       \
  _SET_LUA_RET( ret4 )                                                                                                       \
  return 4;                                                                                                                  \
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LUA_VALUE_SETTABLE_BEGIN(Target, 2)
  LUA_VALUE_SETTABLE_PROPERTY( type )
  LUA_VALUE_SETTABLE_PROPERTY_EX( "position", vPosition )
  LUA_VALUE_SETTABLE_PROPERTY_EX( "objectId", ::IsValid(pObject) ? pObject->GetWOID() : 0 )
LUA_VALUE_SETTABLE_END

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaDebugTrace, const char * )

#ifndef _SHIPPING
  DebugTrace( "[Lua] %s", arg1 );
#endif // _SHIPPING

END_LUA2CPP_FUNCTION



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaAssert, const char* )

#ifndef _SHIPPING
  NI_ALWAYS_ASSERT( NStr::StrFmt( "[Lua] %s", arg1) );
#endif // _SHIPPING

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaMessageToChat, const char* )

#ifndef _SHIPPING
  pAIContainer->SendMessage(arg1);
#endif // _SHIPPING

END_LUA2CPP_FUNCTION



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaRandom, int ,int )
  PFWorld* pWorld = pAIContainer->GetWorld();
  int res = pWorld->GetRndGen()->Next(arg1,arg2);
END_LUA2CPP_FUNCTION_RET1(res)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroGetPosition, const char* )

  PFBaseHero * pHero = pAIContainer->FindHero(arg1);
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  PFBaseHero * pHeroLocal = pAIContainer->GetLocalHero();
  LUA_VERIFY( pHeroLocal, NStr::StrFmt( "Local hero not found!" ), return 0; );

  CVec3 position(-1,-1,-1);
  // This function works only if the hero is visible for us or if we are in a single player game
  if (pHero->IsVisibleForFaction(pHeroLocal->GetFaction()) || pAIContainer->GetWorld()->IsAllScriptFunctionsEnabled() )
  {
    position =  pHero->GetPosition();
  }

END_LUA2CPP_FUNCTION_RET2( position.x, position.y )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( TestLuaHeroGetPosition, const char* )

  CVec3 position(-1.0f, -1.0f, -1.0f);

#ifndef _SHIPPING
  PFBaseHero * pHero = pAIContainer->FindHero(arg1);
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  position = pHero->GetPosition();
#endif // _SHIPPING

END_LUA2CPP_FUNCTION_RET2( position.x, position.y )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaUnitGetPosition, const char* )

  PFLogicObject * pUnit = dynamic_cast<PFLogicObject*>(pAIContainer->FindObject(arg1));
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  PFBaseHero * pHeroLocal = pAIContainer->GetLocalHero();
  LUA_VERIFY( pHeroLocal, NStr::StrFmt( "Local hero not found!" ), return 0; );

  CVec3 position(-1,-1,-1);
  // This function works only if the hero is visible for us or if we are in a single player game
  if (pUnit->IsVisibleForFaction(pHeroLocal->GetFaction()) || pAIContainer->GetWorld()->IsAllScriptFunctionsEnabled() )
  {
    position =  pUnit->GetPosition();
  }

END_LUA2CPP_FUNCTION_RET2( position.x, position.y )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( TestLuaUnitGetPosition, const char* )

  CVec3 position(-1.0f, -1.0f, -1.0f);

#ifndef _SHIPPING
  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  position = pUnit->GetPosition();
#endif // _SHIPPING

END_LUA2CPP_FUNCTION_RET2( position.x, position.y )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaUnitGetHealth, const char* )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  PFBaseHero * pHeroLocal = pAIContainer->GetLocalHero();
  LUA_VERIFY( pHeroLocal, NStr::StrFmt( "Local hero not found!" ), return 0; );

  float health = -1.0f;
  float maxHealth = -1.0f;
  // This function works only if the hero is visible for us or if we are in a single player game
  if (pUnit->IsVisibleForFaction(pHeroLocal->GetFaction()) || pAIContainer->GetWorld()->IsAllScriptFunctionsEnabled() )
  {
    health = pUnit->GetHealth();
    maxHealth = pUnit->GetMaxHealth();
  }

END_LUA2CPP_FUNCTION_RET2( health, maxHealth )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( TestLuaUnitGetHealth, const char* )

  float health = -1.0f;
  float maxHealth = -1.0f;

#ifndef _SHIPPING
  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  health = pUnit->GetHealth();
  maxHealth = pUnit->GetMaxHealth();
#endif // _SHIPPING

END_LUA2CPP_FUNCTION_RET2( health, maxHealth )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroGetMana, const char* )

  PFBaseHero * pHero = pAIContainer->FindHero(arg1);
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  float mana = pHero->GetMana();
  float maxMana = pHero->GetMaxMana();

END_LUA2CPP_FUNCTION_RET2( mana, maxMana )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaGetLocalFaction )

  PFBaseHero * pHero = pAIContainer->GetLocalHero();
  LUA_VERIFY( pHero, "Failed to get the local hero!", return 0 );

  int faction = pHero->GetFaction();

END_LUA2CPP_FUNCTION_RET1( faction )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaGetLocalHero )

PFBaseHero * pHero = pAIContainer->GetLocalHero();
LUA_VERIFY( pHero, "Failed to get the local hero!", return 0 );

  string name;
  pAIContainer->FindObjectName( name, pHero );

END_LUA2CPP_FUNCTION_RET1( name.c_str() )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaGetUnitObjectNameById, int )

  PFBaseUnit * pUnit = dynamic_cast<PFBaseUnit*>(pAIContainer->GetWorld()->GetObjectById(arg1));
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit id = %d not found!", arg1 ), return 0; );

  string name;
  pAIContainer->FindObjectName( name, pUnit );

END_LUA2CPP_FUNCTION_RET1( name.c_str() )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaGetUnitIdByObjectName, const char* )

PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
LUA_VERIFY( pUnit, NStr::StrFmt( "Unit id = %d not found!", arg1 ), return 0; );

END_LUA2CPP_FUNCTION_RET1( pUnit->GetWOID() )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaUnitsInRange, int, int, float )

PFBaseUnit * pUnit1 = dynamic_cast<PFBaseUnit*>(pAIContainer->GetWorld()->GetObjectById(arg1));
LUA_VERIFY( pUnit1, NStr::StrFmt( "Unit id = %d not found!", arg1 ), return 0; );

PFBaseUnit * pUnit2 = dynamic_cast<PFBaseUnit*>(pAIContainer->GetWorld()->GetObjectById(arg2));
LUA_VERIFY( pUnit2, NStr::StrFmt( "Unit id = %d not found!", arg2 ), return 0; );

bool isInRange = pUnit1->IsInRange(pUnit2, arg3);

END_LUA2CPP_FUNCTION_RET1( isInRange )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitApplyApplicator(PFBaseUnit * pReceiver, PFBaseUnit * pSender, const char * dbid)
{
  NDb::Ptr<NDb::BaseApplicator> dbObj = NDb::Get<NDb::BaseApplicator>( NDb::DBID( dbid ) );
  NI_DATA_VERIFY( IsValid( dbObj ), NStr::StrFmt( "Resource \"%s\" not found!", dbid ), return; );

  CObj<PFAbilityInstance> ability;
  NWorld::PFApplCreatePars cp(ability, Target(pReceiver));
  cp.pDBAppl = dbObj;
  cp.pWorld = pReceiver->GetWorld();
  cp.pOwner = pSender;
  CObj<PFBaseApplicator> pAppl(cp.pDBAppl->Create(cp));
  if (pAppl)
  {
    if (!pAppl->Init())
      pAppl = 0; // Kill applicator
    else
      pReceiver->OnApplicatorApply(pAppl);
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UnitRemoveApplicator(PFBaseUnit * pUnit, const char * dbid)
{
  struct ApplicatorRemover: public NonCopyable
  { 
    PFBaseUnit * pUnit;
    nstl::string applDbid;

    ApplicatorRemover( PFBaseUnit * _pUnit, const char * _applDbid )
      : pUnit(_pUnit), applDbid(_applDbid) 
    {
      nstl::replace( applDbid.begin(), applDbid.end(), '\\', '/' ); // Convert '\' to '/', as used in dbid
      if (applDbid.find( ".xdb" ) == nstl::string::npos)
        applDbid.append( ".xdb" ); // Append ".xdp" extension, as used in dbid
      if (applDbid[0] == '/')
        applDbid.erase( 0, 1 ); // Remove '/' from the beginning, as used in dbid
    }
    
    void operator()(PFBaseApplicator * pAppl)
    {
      if (pAppl && pAppl->GetDBBase()->GetDBID().GetFileName() == applDbid )
      {
        CObj<PFBaseApplicator> applToRemove(pAppl);
        applToRemove->Stop();
        MemorizeApplicator( applToRemove );
      }
    }
  } applRemover(pUnit, dbid);

  pUnit->ForAllAppliedApplicators( applRemover );
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2(LuaHeroApplyApplicator, const char*, const char*)

  PFBaseHero * pHero = pAIContainer->FindHero(arg1);
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  UnitApplyApplicator( pHero, 0, pAIContainer->GetFileNameByKey(arg2) );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2(LuaUnitApplyApplicator, const char*, const char*)

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  UnitApplyApplicator( pUnit, pUnit, pAIContainer->GetFileNameByKey(arg2) );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3(LuaUnitApplyApplicatorFromUnit, const char*, const char*, const char*)

  PFBaseUnit * pReceiver = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pReceiver, NStr::StrFmt( "%s: Unit \"%s\" not found!", __FUNCTION__, arg1 ), return 0; );
  PFBaseUnit * pSender = pAIContainer->FindUnit(arg2);
  LUA_VERIFY( pSender, NStr::StrFmt( "%s: Unit \"%s\" not found!", __FUNCTION__, arg2 ), return 0; );

  UnitApplyApplicator( pReceiver, pSender, pAIContainer->GetFileNameByKey(arg3) );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2(LuaHeroRemoveApplicator, const char*, const char*)

  PFBaseHero * pHero = pAIContainer->FindHero(arg1);
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  UnitRemoveApplicator( pHero, pAIContainer->GetFileNameByKey(arg2) );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2(LuaUnitRemoveApplicator, const char*, const char*)

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  UnitRemoveApplicator( pUnit, pAIContainer->GetFileNameByKey(arg2) );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroSetInvulnerable, const char* )

  PFBaseHero * pHero = pAIContainer->FindHero(arg1);
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  pHero->AddFlag( NDb::UNITFLAG_FORBIDDEATH );
  pHero->AddFlag( NDb::UNITFLAG_FORBIDTAKEDAMAGE );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroAddFlag, const char*, int )

  PFBaseHero * pHero = pAIContainer->FindHero(arg1);
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  pHero->AddFlag(arg2);

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaUnitAddFlag, const char*, int )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  pUnit->AddFlag(arg2);

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroRemoveFlag, const char*, int )

  PFBaseHero * pHero = pAIContainer->FindHero(arg1);
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  pHero->RemoveFlag(arg2);

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaUnitRemoveFlag, const char*, int )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  for (int i = 0, count = NDb::KnownEnum<NDb::EUnitFlagType>::SizeOf(); i < count; ++i)
  {
    if( arg2 & (1 << i) )
      LUA_VERIFY( pUnit->CheckFlagType( (NDb::EUnitFlagType)i ), NStr::StrFmt( "Unit \"%s\" hasn't all flags (removing %d)!", arg1, arg2 ), ; );
  }

  pUnit->RemoveFlag(arg2);

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaUnitCheckFlag, const char*, int )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  bool res = pUnit->CheckFlag( arg2 );

END_LUA2CPP_FUNCTION_RET1( res )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaCreatureHide, const char*, bool )

  if (PFCreature * pCreature = pAIContainer->FindCreature(arg1))
  {
    pCreature->Hide(arg2);
  }
  else if (PFBaseUnit * pUnit =  pAIContainer->FindUnit(arg1))
  {
    pUnit->Hide(arg2);
  }
  else if ( PFWorldObjectBase *pObject = dynamic_cast<PFWorldObjectBase*>(pAIContainer->FindObject(arg1)) )
  {
    pObject->Hide(arg2);
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaGroupHide, const char*, bool )

  struct Hider
  {
    bool hide;

    Hider(bool _hide) : hide(_hide) {}

    void operator()(PF_Core::WorldObjectBase * obj)
    {
      if (PFWorldObjectBase * obj2 = dynamic_cast<PFWorldObjectBase *>(obj))
        obj2->Hide(hide);
    }
  } hider(arg2);

  if (PFAIContainer::TObjectGroup * group = pAIContainer->FindGroup(arg1))
  {
    for_each(group->begin(), group->end(), hider);
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaCreatureMoveTo, const char*, float, float, float )

  pAIContainer->MoveTo( arg1, arg2, arg3, arg4 );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( TestLuaCreatureMoveTo, const char*, float, float, float )

#ifndef _SHIPPING
  if (PFCreature * pCreature = pAIContainer->FindCreature(arg1))
  {
    CVec2 target(arg2, arg3);
    pCreature->MoveTo(target, arg3);
  }
#endif // _SHIPPING

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaCreatureIsMoving, const char* )

  bool isMoving = false;

  if (PFCreature * pCreature = pAIContainer->FindCreature(arg1))
  {
    isMoving = pCreature->IsMoving();
  }

END_LUA2CPP_FUNCTION_RET1(isMoving)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaCanCreatureMoveTo, const char*, float, float, float )

  bool canMove = false;
  PFCreature * pCreature = pAIContainer->FindCreature(arg1);
  LUA_VERIFY( pCreature, NStr::StrFmt( "Creature \"%s\" not found", arg1 ), return 0 );
  CVec2 targ( arg2, arg3 );
  canMove = pCreature->MoveTo( targ, arg4 );
  if ( canMove )
  {
    CVec2 dest = pCreature->GetDestination();
    canMove = fabs2( dest - targ ) <= arg4 * arg4;
  }
  pCreature->Stop();

END_LUA2CPP_FUNCTION_RET1(canMove)


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaGroupMoveTo, const char*, float, float, float )

  struct MoveTo
  {
    CVec2 position;
    float distance;

    MoveTo(float x, float y, float _distance) : position(x, y), distance(_distance) {}

    void operator()(PF_Core::WorldObjectBase * obj)
    {
      if (PFBaseMovingUnit * obj2 = dynamic_cast<PFBaseMovingUnit *>(obj))
      {
        if (!obj2->IsDead())
        {
          obj2->MoveTo(position, distance);
        }
      }
    }
  } moveTo(arg2, arg3, arg4);

  if (PFAIContainer::TObjectGroup * group = pAIContainer->FindGroup(arg1))
  {
    for_each(group->begin(), group->end(), moveTo);
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaCreatureTeleportTo, const char*, float, float )

  if (PFCreature * pCreature = pAIContainer->FindCreature(arg1))
  {
    pCreature->TeleportTo(CVec2(arg2, arg3));
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG6( LuaCreateCreep, const char*, const char*, float, float, int, float )

  bool success = pAIContainer->SpawnCreep(arg1, pAIContainer->GetFileNameByKey(arg2), arg3, arg4, arg5, arg6);

END_LUA2CPP_FUNCTION_RET1( success )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaReplaceCreep, const char*, const char*, int )

bool success = pAIContainer->ReplaceCreep(arg1, pAIContainer->GetFileNameByKey(arg2), arg3 );

END_LUA2CPP_FUNCTION_RET1( success )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaUnitAttackUnit, const char*, const char* )

  pAIContainer->AttackUnitToUnit( arg1, arg2 );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroAttackUnit, const char*, const char* )

  pAIContainer->AttackUnit( arg1, arg2 );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroGetLastDealtDamageStep, const char* )

  PFBaseHero * pHero = pAIContainer->FindHero(arg1);
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  int lastDealtDamageStep = pHero->GetHeroStatistics()->GetLastDealtDamageStep();

END_LUA2CPP_FUNCTION_RET1( lastDealtDamageStep )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroGetKillsTotal, const char* )

  int killsTotal = 0;

  PFBaseHero * pHero = pAIContainer->FindHero(arg1);
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  killsTotal = pHero->GetHeroStatistics()->GetNumKillsTotal();

END_LUA2CPP_FUNCTION_RET1( killsTotal )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroStatisticsGetScore, const char* )

int score = 0;

PFBaseHero * pHero = pAIContainer->FindHero(arg1);
LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

score = pHero->GetHeroStatistics()->GetScore();

END_LUA2CPP_FUNCTION_RET1( score )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaStatisticsGetTotalNumHeroKills, const char* )

int kills = 0;

PFBaseHero * pHero = pAIContainer->FindHero(arg1);
LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

kills = pHero->GetHeroStatistics()->GetTotalNumHeroKills();

END_LUA2CPP_FUNCTION_RET1( kills )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaStatisticsGetTotalNumHeroAssists, const char* )

int assists = 0;

PFBaseHero * pHero = pAIContainer->FindHero(arg1);
LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

assists = pHero->GetHeroStatistics()->GetTotalNumHeroAssists();

END_LUA2CPP_FUNCTION_RET1( assists )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaSetSpawnCreeps, bool )

  if (NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance())
  {
    if (PFWorld *world = advScreen->GetWorld())
    {
      if (PFAIWorld * aiWorld = world->GetAIWorld())
      {
        aiWorld->SetSpawnCreeps(arg1);
      }
    }
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaSetSpawnNeutralCreeps, bool )

  if (NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance())
  {
    if (PFWorld *world = advScreen->GetWorld())
    {
      if (PFAIWorld * aiWorld = world->GetAIWorld())
      {
        aiWorld->SetSpawnNeutralCreeps(arg1);
      }
    }
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaHeroActivateTalent, const char*, int, int, bool )

  PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>( pAIContainer->FindHero( arg1 ) );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  bool success = pAIContainer->ActivateTalentImpl( pHero, arg2, arg3, true, arg4 );

END_LUA2CPP_FUNCTION_RET1( success )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaHeroUseTalent, const char*, int, int )

  PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>( pAIContainer->FindHero( arg1 ) );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  bool success = pAIContainer->UseTalentImpl( pHero, arg2, arg3 );

END_LUA2CPP_FUNCTION_RET1( success )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaHeroUseTalentPos, const char*, int, int, float, float )

  PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>( pAIContainer->FindHero( arg1 ) );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  bool success = pAIContainer->UseTalentPosImpl( pHero, arg2, arg3, arg4, arg5 );

END_LUA2CPP_FUNCTION_RET1( success )


START_LUA2CPP_FUNCTION_ARG3( LuaUsePortalToPos, const char*, float, float )
  bool success = pAIContainer->UsePortalTo( arg1, arg2, arg3 );
END_LUA2CPP_FUNCTION_RET1( success )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaHeroUseTalentUnit, const char*, int, int, const char* )

  PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>( pAIContainer->FindHero( arg1 ) );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg4);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg4 ), return 0; );

  bool success = pAIContainer->UseTalentUnitImpl( pHero, arg2, arg3, pUnit );

END_LUA2CPP_FUNCTION_RET1( success )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaHeroCanActivateTalent, const char*, int, int )

  PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>( pAIContainer->FindHero( arg1 ) );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  PFTalent * pTalent = pHero->GetTalent( arg2, arg3 );
  if ( !pTalent )
    return false;

  bool canActivateTalent = pTalent->IsActivated() ? false : pHero->GetGold() >= pTalent->GetNaftaCost() && pTalent->CanBeActivated();

END_LUA2CPP_FUNCTION_RET1( canActivateTalent )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFTalent * GetTalent(PFAIContainer * pAIContainer, const char * hero, int level, int slot)
{
  PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>( pAIContainer->FindHero( hero ) );
  NI_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", hero ), return 0; );

  PFTalent * pTalent = pHero->GetTalent( level, slot );
  NI_ASSERT( pTalent, NStr::StrFmt( "Talent in level %d slot %d for hero \"%s\" not found!", level, slot, hero ) );

  return pTalent;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaHeroIsTalentActivated, const char*, int, int )

  bool isTalentActivated = false;
  if (PFTalent * pTalent = GetTalent(pAIContainer, arg1, arg2, arg3))
  {
    isTalentActivated = pTalent->IsActivated();
  }

END_LUA2CPP_FUNCTION_RET1( isTalentActivated )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaHeroIsGenderTalent, const char*, int, int )

  bool isGenderTalent = false;
  if (PFTalent * pTalent = GetTalent(pAIContainer, arg1, arg2, arg3))
  {
    isGenderTalent = pTalent->IsGenderTalent();
  }

END_LUA2CPP_FUNCTION_RET1( isGenderTalent )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaHeroGetTalentType, const char*, int, int )

  int talentType = NDb::ABILITYTYPE_SIMPLE;
  if (PFTalent * pTalent = GetTalent(pAIContainer, arg1, arg2, arg3))
  {
    talentType = pTalent->GetType();
  }

END_LUA2CPP_FUNCTION_RET1( talentType )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaHeroGetTalentUseStep, const char*, int, int )

  int useStep = -1;
  if (PFTalent * pTalent = GetTalent(pAIContainer, arg1, arg2, arg3))
  {
    useStep = pTalent->GetLastUseStep();
  }

END_LUA2CPP_FUNCTION_RET1( useStep )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaHeroGetTalentActivatedStep, const char*, int, int )

int activatedStep = -1;
if (PFTalent * pTalent = GetTalent(pAIContainer, arg1, arg2, arg3))
{
  activatedStep = pTalent->GetLastActivatedStep();
}

END_LUA2CPP_FUNCTION_RET1( activatedStep )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroGetTalentsLevel, const char* )

  PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>( pAIContainer->FindHero( arg1 ) );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  int talentsLevel = pHero->GetTalentsSet()->GetLevelOfDevelopmentCapped();

END_LUA2CPP_FUNCTION_RET1( talentsLevel )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroGetLastTalentUseStep, const char* )

  PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>( pAIContainer->FindHero( arg1 ) );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  int lastTalentUseStep = pHero->GetLastTalentUseStep();

END_LUA2CPP_FUNCTION_RET1( lastTalentUseStep )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroGetLevel, const char* )

  PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>( pAIContainer->FindHero( arg1 ) );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  int heroLevel = pHero->GetDevPoints();

END_LUA2CPP_FUNCTION_RET1( heroLevel )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaSpawnerGetLastWave, const char* )

  int lastWave = -1; // Wrong wave in case of error

  if (const PF_Core::WorldObjectBase * pObject = pAIContainer->FindObject(arg1))
  {
    if (const PFBaseSpawner * pSpawner = dynamic_cast<const PFBaseSpawner *>(pObject))
    {
      lastWave = pSpawner->GetLastWave(); // Get last vave number or 0 if no waves counted
    }
  }

END_LUA2CPP_FUNCTION_RET1( lastWave )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaSpawnerSpawnWave, const char* )

  int lastWave = -1;
  int creepsCount = 0;

  if (PF_Core::WorldObjectBase * pObject = pAIContainer->FindObject(arg1))
  {
    if (PFBaseSpawner * pSpawner = dynamic_cast<PFBaseSpawner *>(pObject))
    {
      pSpawner->SpawnWave();
      lastWave = pSpawner->GetLastWave();
      creepsCount = pSpawner->GetCreepsInLastWave();
    }
  }

END_LUA2CPP_FUNCTION_RET2( lastWave, creepsCount )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaCameraMoveToPos, float, float )

  if (NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance())
  {
    advScreen->MoveCameraTo( CVec3(arg1, arg2, 0.0f) );
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSetCameraFree, const char*, int )

if (NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance())
{
  if( NDb::Ptr<NDb::AdvMapCameraSpline> cameraSpline = NDb::Get<NDb::AdvMapCameraSpline>( NDb::DBID(arg1) ) )
  {
    LUA_VERIFY(arg2 < cameraSpline->points.size(), "number: invalid argument", return 0)

    const Placement basePlacement = pAIContainer->GetPlacementCameraSpline( cameraSpline->GetDBID() );

    advScreen->SetFreeCameraController( true );

    CVec3 correctPosition = basePlacement.rot.Rotate( cameraSpline->points[arg2].position );
    correctPosition += basePlacement.pos;

    CVec3 correctRotation = RotateEulerAnglesByQuat( cameraSpline->points[arg2].rotation, basePlacement.rot );

    advScreen->SetCameraFree( correctRotation, correctPosition );
  }
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaUnSetCameraFree )

if (NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance())
   advScreen->UnSetCameraFree();

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaCameraMoveToUnit, const char* )

  if (PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1))
  {
    if (NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance())
    {
      advScreen->MoveCameraTo( pUnit );
    }
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaCameraObserveUnit, const char* )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);

  if (NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance())
  {
    const PFBaseHero * hero = dynamic_cast< const PFBaseHero* > ( pUnit );
    if ( hero && hero == advScreen->GetHero() )
    {
      advScreen->LockCamera( true );
    }
    else
    {
      advScreen->LockCamera( false ); // Drop previous, if was 
      advScreen->SetObservingObject( pUnit );
    }
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaCameraMoveToPosTimed, float, float, float )

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    PF_Core::MoveToCameraController *pMoveToCtrl = new PF_Core::MoveToCameraController;

    struct CallBackCameraController : public NScene::ICallBackCameraController
    {
      OBJECT_BASIC_METHODS(CallBackCameraController);
      NScene::ICameraController* cameraController;
      float x, y, time;
    public:
      CallBackCameraController( ) : cameraController( 0 ) {}
      CallBackCameraController( NScene::ICameraController* _cameraController, float _x, float _y, float _time ) : 
      cameraController( _cameraController ),
      x( _x ),
      y( _y ),
      time( _time )
      {}

      virtual void CallBack()
      {
        NI_ASSERT( cameraController, "bad camera controller" );

        if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
        {
          NScene::SCameraPosition posFrom;
          NScene::SCameraPosition posTo;
          pAdvScreen->GetCamera()->GetCameraPosition(&posFrom);
          posTo = posFrom;
          posTo.vAnchor.x = x;
          posTo.vAnchor.y = y;

          float terrainHeight;
          pAdvScreen->GetWorld()->GetScene()->GetHeightsController().GetHeight( posTo.vAnchor.x, posTo.vAnchor.y, 1, &terrainHeight, NULL);
          posTo.vAnchor.z = terrainHeight;

          if( PF_Core::MoveToCameraController* moveToCamera = dynamic_cast<PF_Core::MoveToCameraController*>( cameraController ) )
          {
            moveToCamera->Init( posFrom, posTo, time );
            pAdvScreen->GetScene()->GetCameraControllers()->AddCameraController( moveToCamera );
          }
        }
      }
    };

    CallBackCameraController* callback = new CallBackCameraController( pMoveToCtrl, arg1, arg2, arg3 );

    pAdvScreen->GetCamera()->SetSmoothMotionRodCallback( pAdvScreen->GetCamera()->GetSettings().maxRod, callback );
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaCameraMoveToPosTimed2, float, float, float, float, float )

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    PF_Core::MoveToCameraController *pMoveToCtrl = new PF_Core::MoveToCameraController;
    NScene::SCameraPosition posFrom;
    NScene::SCameraPosition posTo;
    pAdvScreen->GetCamera()->GetCameraPosition(&posFrom);
    posFrom.fRod = pAdvScreen->GetCamera()->GetSettings().maxRod;
    posFrom.vAnchor.x = arg1;
    posFrom.vAnchor.y = arg2;
    posTo = posFrom;
    posTo.vAnchor.x = arg3;
    posTo.vAnchor.y = arg4;

    float terrainHeightTo, terrainHeightFrom;
    pAdvScreen->GetWorld()->GetScene()->GetHeightsController().GetHeight( posTo.vAnchor.x, posTo.vAnchor.y, 1, &terrainHeightTo, NULL);
    pAdvScreen->GetWorld()->GetScene()->GetHeightsController().GetHeight( posFrom.vAnchor.x, posFrom.vAnchor.y, 1, &terrainHeightFrom, NULL);
    posFrom.vAnchor.z = terrainHeightFrom;
    posTo.vAnchor.z = terrainHeightTo;

    pMoveToCtrl->Init( posFrom, posTo, arg5 );

    struct CallBackCameraController : public NScene::ICallBackCameraController
    {
      OBJECT_BASIC_METHODS(CallBackCameraController);
      NScene::ICameraController* cameraController;

    public:
      CallBackCameraController( ) : cameraController( 0 ) {}
      CallBackCameraController( NScene::ICameraController* _cameraController ): 
      cameraController( _cameraController )
      {}

      virtual void CallBack()
      {
        NI_ASSERT( cameraController, "bad camera controller" );

        if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
        {
          pAdvScreen->GetScene()->GetCameraControllers()->AddCameraController( cameraController );
        }
      }
    };

    CallBackCameraController* callback = new CallBackCameraController( pMoveToCtrl );

    pAdvScreen->GetCamera()->SetSmoothMotionRodCallback( posFrom.fRod, callback );
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaCameraGetPos )

  NScene::SCameraPosition pos;

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    pAdvScreen->GetCamera()->GetCameraPosition(&pos);
  }

END_LUA2CPP_FUNCTION_RET3( pos.vAnchor.x, pos.vAnchor.y, pos.fRod )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaCameraLock, bool )

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    pAdvScreen->GetCamera()->LockZoom(arg1);
    pAdvScreen->GetCamera()->LockObserve(arg1);
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaSetManualGameFinish, bool )

  // This function works only if we are in a single player game
  if (pAIContainer->GetWorld()->IsAllScriptFunctionsEnabled())
  {
    if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
    {
      pAdvScreen->GetWorld()->SetManualGameFinish(arg1);
    }
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaGameFinish, int )

  // This function works only if we are in a single player game
  if (pAIContainer->GetWorld()->IsAllScriptFunctionsEnabled())
  {
    if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
    {
      pAdvScreen->GetWorld()->GameFinish((NDb::EFaction)arg1);
    }
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaSetAchievmentsEnabled, bool )

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    if (PFWorld * pWorld = pAdvScreen->GetWorld())
    {
      for (int i = 0; i < pWorld->GetPlayersCount(); ++i)
      {
        if (PFPlayer * pPlayer = pWorld->GetPlayer(i))
        {
          if (PFBaseHero * pHero = pPlayer->GetHero())
          {
            pHero->GetHeroStatistics()->SetAchievmentsEnabled(arg1);
          }
        }
      }
    }
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaSetVisMapMode, int )

  bool success = false;
  // This function works only if we are in a single player game
  if (pAIContainer->GetWorld()->IsAllScriptFunctionsEnabled())
  {
    success = NGameX::VisibilityMapClient::SetVisMapMode(arg1);
    NI_ASSERT( success, "Wrong visibility map mode!" );
  }

END_LUA2CPP_FUNCTION_RET1( success )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaUnitIsDead, const char* )

  bool isDead  = true;
  bool isFound = false;

  if (PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1))
  {
    isDead  = pUnit->IsDead();
    isFound = true;
  }
  else
  {
    isFound = pAIContainer->FindDeadObjectName(arg1);
  }

END_LUA2CPP_FUNCTION_RET2( isDead, isFound )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroUseConsumable, const char*, const char* )

  bool success = pAIContainer->UseConsumable( arg1, pAIContainer->GetFileNameByKey(arg2) );

END_LUA2CPP_FUNCTION_RET1( success )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaHeroUseConsumablePos, const char*, const char*, float, float )

  bool success = pAIContainer->UseConsumable( arg1, pAIContainer->GetFileNameByKey(arg2), 0, arg3, arg4 );

END_LUA2CPP_FUNCTION_RET1( success )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaHeroUseConsumableUnit, const char*, const char*, const char* )

  bool success = pAIContainer->UseConsumable( arg1, pAIContainer->GetFileNameByKey(arg2), arg3 );

END_LUA2CPP_FUNCTION_RET1( success )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroTakeConsumable, const char*, const char* )

  bool success = true;

  PFBaseHero* pHero = pAIContainer->FindHero( arg1 );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), success = false; );

  NDb::Ptr<NDb::Consumable> pDbConsumable = NDb::Get<NDb::Consumable>( NDb::DBID( pAIContainer->GetFileNameByKey(arg2) ) );
  NI_DATA_VERIFY( IsValid( pDbConsumable ), NStr::StrFmt( "Consumable \"%s\" not found!", pAIContainer->GetFileNameByKey(arg2) ), success = false; );

  if ( success && !pHero->TakeConsumable( pDbConsumable, 1, NDb::CONSUMABLEORIGIN_SCRIPT ) )
  {
    pHero->GetWorld()->GetIAdventureScreen()->NotifyOfSimpleUIEvent( pHero, NDb::ERRORMESSAGETYPE_OUTOFINVENTORY);
    success = false;
  }

END_LUA2CPP_FUNCTION_RET1( success )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroHasConsumable, const char*, const char* )

  bool hasConsumable = false;
  int  slot = -1;

  PFBaseHero* pHero = pAIContainer->FindHero( arg1 );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  string consumableDbid(pAIContainer->GetFileNameByKey(arg2));
  nstl::replace( consumableDbid.begin(), consumableDbid.end(), '\\', '/' ); // Convert \ to /, as used in dbid

  int slotCount = pHero->GetSlotCount();

  for (int i = 0; !hasConsumable && i < slotCount; ++i)
  {
    if (const PFConsumable * pConsumable = pHero->GetConsumable(i))
    {
      if (pConsumable->GetDBDesc()->GetDBID().GetFileName() == consumableDbid)
      {
        hasConsumable = true;
        slot = i;
      }
    }
  }

END_LUA2CPP_FUNCTION_RET2( hasConsumable, slot )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroGetConsumablesCount, const char* )

  int consumablesCount = 0;

  PFBaseHero* pHero = pAIContainer->FindHero( arg1 );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  int slotCount = pHero->GetSlotCount();

  for (int i = 0; i < slotCount; ++i)
  {
    if (const PFConsumable * pConsumable = pHero->GetConsumable(i))
    {
      consumablesCount += pConsumable->GetQuantity();
    }
  }

END_LUA2CPP_FUNCTION_RET1( consumablesCount )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroFollowCreature, const char*, const char* )

  PFBaseHero* pHero = pAIContainer->FindHero( arg1 );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  PFCreature* pCreature = pAIContainer->FindCreature( arg2 );
  NI_DATA_VERIFY( IsValid( pCreature ), NStr::StrFmt( "Creature \"%s\" not found!", arg2 ), return 0; );

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    CObj<NCore::WorldCommand> pCommand;
    pCommand = NWorld::CreateCmdFollowUnit(pHero, pCreature, 0.f, 0.f, true);
    pAdvScreen->SendGameCommand( pCommand );
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaLoadTalantSet, const char*, const char* )

PFBaseHero* pHero = pAIContainer->FindHero( arg1 );
NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

if( PFBaseMaleHero* maleHero = dynamic_cast<PFBaseMaleHero*>( pHero ) )
{
  maleHero->LoadTalents( pAIContainer->GetFileNameByKey(arg2) );

  if( NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance() )
  {
    if( pAdvScreen->GetHero() == maleHero )
      pAdvScreen->SetLogicHero( pAdvScreen->GetHero() );
  }
}

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroGetForce, const char* )
  PFBaseHero* pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  int res = pHero->GetForce(false);

END_LUA2CPP_FUNCTION_RET1( res )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroSetRefineRate, const char*, int )

  PFBaseHero* pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  CPtr<NWorld::PFBaseMaleHero> pMaleHero = dynamic_cast<NWorld::PFBaseMaleHero*>( pHero );
  LUA_VERIFY( pMaleHero, NStr::StrFmt( "Hero \"%s\" must be a male hero!", arg1 ), return 0 );

  if ( !pAIContainer->GetWorld()->IsAllScriptFunctionsEnabled() )
    return 0;

  struct ChangeRefineRate : NonCopyable
  {
    int newRefineRate;
    ChangeRefineRate( int newRefineRate_ ) : newRefineRate( newRefineRate_ ) {}

    void operator()( NWorld::PFTalent* pTalent, int level, int slot )
    {
      pTalent->SetRefineRate(newRefineRate);
    }
  } changeRefineRate( arg2 );
  pMaleHero->ForAllTalents(changeRefineRate);
  pMaleHero->SetForce( NWorld::Force::CalculateForce(pMaleHero) );
  if( NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance() )
  {
    if( pAdvScreen->GetHero() == pMaleHero )
      pAdvScreen->SetLogicHero( pAdvScreen->GetHero() );
  }
END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaUnitClearStates, const char* )

  PFBaseUnit* pUnit = pAIContainer->FindUnit( arg1 );
  NI_DATA_VERIFY( IsValid( pUnit ), NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  pUnit->Cleanup();
  pUnit->CancelChannelling();

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaDirectionHintSet, const char*, float, float, float )

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    pAdvScreen->SetDirectionHint(pAIContainer->GetFileNameByKey(arg1), arg2, arg3, arg4);
    pAdvScreen->SetDirectionHintSize(arg2, arg2, 0.0f);
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaDirectionHintSet2, const char*, float, float, float, float )

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    pAdvScreen->SetDirectionHint(pAIContainer->GetFileNameByKey(arg1), arg2, arg3);
    pAdvScreen->SetDirectionHintSize(arg2, arg4, arg5);
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaDirectionHintSetSizes, float, float, float )

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    pAdvScreen->SetDirectionHintSize(arg1, arg2, arg3);
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaDirectionHintShow, float, float )

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    pAdvScreen->SetDirectionHintPos(CVec3(arg1, arg2, 0.0f));
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaDirectionHintHide )

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    pAdvScreen->SetDirectionHintPos(VNULL3);
    pAdvScreen->ResetDirectionHint();
  }

END_LUA2CPP_FUNCTION


bool PFAIContainer::ScriptEffect::Create( NScene::IScene* pScene )
{
  NDb::Ptr<NDb::EffectBase> dbObj = NDb::Get<NDb::EffectBase>( dbid );

  if ( !pObject )
  {
    CObj<PF_Core::BasicEffectStandalone> effect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffectStandalone>( dbObj );
    NI_DATA_VERIFY( effect, NStr::StrFmt( "Effect \"%s\" is not BasicEffectStandalone!", dbid ), return false );
    pEffect = effect;

    float terrainHeight = 0;
    pScene->GetHeightsController().GetHeight( x, y, 0, &terrainHeight, 0 );

    Placement place( CVec3(x, y, terrainHeight) );
    effect->SetPosition( place );
    effect->AddToScene( pScene );
  }
  else 
  {
    pEffect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffect>( dbObj );
    CPtr<PF_Core::ClientObjectBase> pClientObj = pObject->ClientObject();
    pEffect->Apply( pClientObj );
  }
  return true;
}

void PFAIContainer::ScriptEffect::Remove()
{
  if ( IsValid( pEffect ) && pEffect->IsActive() )
  {
    pEffect->Die();
    pEffect = 0;
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::PlaceStandaloneEffect( const char* name, const char* dbid, float x, float y )
{
  NI_DATA_VERIFY( scriptEffects.find( name ) == scriptEffects.end(), NStr::StrFmt( "Effect \"%s\" is already registered", name ), return );

  NDb::Ptr<NDb::EffectBase> dbObj = NDb::Get<NDb::EffectBase>( NDb::DBID( dbid ) );
  NI_DATA_VERIFY( IsValid( dbObj ), NStr::StrFmt( "Effect \"%s\" not found!", dbid ), return );

  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return;

  NScene::IScene* pScene = advScreen->GetScene();
  if ( !pScene )
    return;

  ScriptEffect se( NDb::DBID( dbid ), x, y ); 

  if ( se.Create( pScene ) )
    scriptEffects[name] = se;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::PlaceAttachedEffect( const char* name, const char* dbid, const char* parentName )
{
  NI_DATA_VERIFY( scriptEffects.find( name ) == scriptEffects.end(), NStr::StrFmt( "Effect \"%s\" is already registered", name ), return );

  NDb::Ptr<NDb::EffectBase> dbObj = NDb::Get<NDb::EffectBase>( NDb::DBID( dbid ) );
  NI_DATA_VERIFY( IsValid( dbObj ), NStr::StrFmt( "Effect \"%s\" not found!", dbid ), return );

  PFLogicObject *pObject = dynamic_cast<PFLogicObject*>(FindObject( parentName ));
  NI_DATA_VERIFY( pObject, NStr::StrFmt( "Object \"%s\" not found!", pObject ), return );

  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return;

  NScene::IScene* pScene = advScreen->GetScene();
  if ( !pScene )
    return;

  ScriptEffect se( NDb::DBID( dbid ), pObject ); 

  if ( se.Create( pScene ) )
    scriptEffects[name] = se;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::RemoveStandaloneEffect( const char* name )
{
  TScriptEffects::iterator it = scriptEffects.find( name );
  NI_DATA_VERIFY( it != scriptEffects.end(), NStr::StrFmt( "Effect \"%s\" is not registered", name ), return );

  it->second.Remove();
  scriptEffects.erase( it );
  }
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::PlaceClientEffect( const char* dbid, float x, float y )
{
  NDb::Ptr<NDb::EffectBase> dbObj = NDb::Get<NDb::EffectBase>( NDb::DBID( dbid ) );
  NI_DATA_VERIFY( IsValid( dbObj ), NStr::StrFmt( "Effect \"%s\" not found!", dbid ), return );

  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return;

  NScene::IScene* pScene = advScreen->GetScene();
  if ( !pScene )
    return;

  ScriptEffect se( NDb::DBID( dbid ), x, y ); 

  se.Create( pScene );
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaPlaceStandaloneEffect, const char*, const char*, float, float )

  pAIContainer->PlaceStandaloneEffect( arg1, pAIContainer->GetFileNameByKey(arg2), arg3, arg4 );

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaPlaceAttachedEffect, const char*, const char*, const char* )

pAIContainer->PlaceAttachedEffect( arg1, pAIContainer->GetFileNameByKey(arg2), arg3 );

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaRemoveStandaloneEffect, const char* )

  pAIContainer->RemoveStandaloneEffect( arg1 );

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaPlaceClientEffect, const char*, float, float )

  pAIContainer->PlaceClientEffect( pAIContainer->GetFileNameByKey(arg1), arg2, arg3 );

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::PlaceSimpleObject( const char* name, const char* dbid, float x, float y, float z )
{
  NDb::Ptr<NDb::SimpleObject> dbObj = NDb::Get<NDb::SimpleObject>( NDb::DBID( dbid ) );
  NI_DATA_VERIFY( IsValid( dbObj ), NStr::StrFmt( "SimpleObject \"%s\" not found!", dbid ), return );

  NI_VERIFY(simpleObjects.find(name) == simpleObjects.end(), 
    NStr::StrFmt("Object with script name \"%s\" already registered!", name), return; );

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    if (PFWorld *pWorld = pAdvScreen->GetWorld())
    {
      CVec3 position(x, y, z);

      NDb::AdvMapObject dbObject;
      dbObject.gameObject = dbObj;
      dbObject.offset = CPlacement( position, QNULL, CVec3(1.f, 1.f, 1.f));

      CPtr<PFSimpleObject> sObj = new PFSimpleObject(pWorld, dbObject);

      if(IsValid(sObj))
      {
        simpleObjects[name] = sObj;
      }
    }
  }
}

void PFAIContainer::PlaceSimpleObject( const char* name, const char* dbid, float x, float y, float z, float roll, float pitch, float yaw )
{
  NDb::Ptr<NDb::SimpleObject> dbObj = NDb::Get<NDb::SimpleObject>( NDb::DBID( dbid ) );
  NI_DATA_VERIFY( IsValid( dbObj ), NStr::StrFmt( "SimpleObject \"%s\" not found!", dbid ), return );

  NI_VERIFY(simpleObjects.find(name) == simpleObjects.end(), 
    NStr::StrFmt("Object with script name \"%s\" already registered!", name), return; );

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    if (PFWorld *pWorld = pAdvScreen->GetWorld())
    {
      CVec3 position(x, y, z);
      CQuat rotation(yaw, pitch, roll);

      NDb::AdvMapObject dbObject;
      dbObject.gameObject = dbObj;
      dbObject.offset = CPlacement( position, rotation, CVec3(1.f, 1.f, 1.f));

      CPtr<PFSimpleObject> sObj = new PFSimpleObject(pWorld, dbObject);

      if(IsValid(sObj))
      {
        simpleObjects[name] = sObj;
      }
    }
  }
}

void PFAIContainer::RemoveSimpleObject( const char* name )
{
  TSimpleObjects::iterator it = simpleObjects.find( name );

  if(it == simpleObjects.end())
    return;

  const CPtr<PFSimpleObject> so(it->second);

  if (IsValid(so))
    so->Die();

  // ???
  it->second = NULL;

  simpleObjects.erase(it);
}

void PFAIContainer::HideSimpleObject( const char* name )
{
  TSimpleObjects::const_iterator it = simpleObjects.find( name );

  if(it == simpleObjects.end())
    return;

  const CPtr<PFSimpleObject> so(it->second);

  if (IsValid(so))
    so->Hide(true);
}

void PFAIContainer::ShowSimpleObject( const char* name )
{
  TSimpleObjects::const_iterator it = simpleObjects.find( name );

  if(it == simpleObjects.end())
    return;

  const CPtr<PFSimpleObject> so(it->second);

  if (IsValid(so))
    so->Hide(false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// TODO: shouldn't be here
template <typename T>
static inline T DegToRad(const T& x)
{
  return (x / T(180)) * T(FP_PI);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaPlaceSimpleObject, const char*, float, float, float )

switch (_GET_LUA_ARG_COUNT())
{
case 4:
  {
    pAIContainer->PlaceSimpleObject( arg1, pAIContainer->GetFileNameByKey(arg1), arg2, arg3, arg4 );
  }
  break;
case 5:
  {
    _GET_LUA_ARG(float, 5)
    pAIContainer->PlaceSimpleObject( arg1, pAIContainer->GetFileNameByKey(arg1), arg2, arg3, arg4, DegToRad(arg5), 0.0f, 0.0f );
  }
  break;
case 6:
  {
    _GET_LUA_ARG(float, 5)
    _GET_LUA_ARG(float, 6)
    pAIContainer->PlaceSimpleObject( arg1, pAIContainer->GetFileNameByKey(arg1), arg2, arg3, arg4, DegToRad(arg5), DegToRad(arg6), 0.0f );
  }
  break;
case 7:
  {
    _GET_LUA_ARG(float, 5)
    _GET_LUA_ARG(float, 6)
    _GET_LUA_ARG(float, 7)
    pAIContainer->PlaceSimpleObject( arg1, pAIContainer->GetFileNameByKey(arg1), arg2, arg3, arg4, DegToRad(arg5), DegToRad(arg6), DegToRad(arg7) );
  }
  break;
default:
  break;
}

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaRemoveSimpleObject, const char* )

pAIContainer->RemoveSimpleObject( arg1 );

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHideSimpleObject, const char* )

pAIContainer->HideSimpleObject( arg1 );

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaShowSimpleObject, const char* )

pAIContainer->ShowSimpleObject( arg1 );

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaSetPause, bool )

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    pAdvScreen->ProcessGamePause( arg1 ? NGameX::PAUSE_HARD : NGameX::PAUSE_OFF, 0 );
  }

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaSetCinematicPause, bool )

if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
{
  pAdvScreen->ProcessGamePause( arg1 ? NGameX::PAUSE_CINEMATIC : NGameX::PAUSE_OFF, 0 );
}

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroSetForbidRespawn, const char*, bool )

  PFBaseHero* pHero = pAIContainer->FindHero( arg1 );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  pHero->SetForbidRespawn(arg2);

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroRespawn, const char* )

  PFBaseHero* pHero = pAIContainer->FindHero( arg1 );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );
  
  if(!pHero->IsResurrecting())
    pHero->Resurrect();

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaHeroSetRespawnPoint, const char*, float, float )

  PFBaseHero* pHero = pAIContainer->FindHero( arg1 );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  CVec3 pos( arg2, arg3, 0.f );
  pHero->SetRespawnPosition( pos );

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroIsRespawning, const char* )

  PFBaseHero* pHero = pAIContainer->FindHero( arg1 );
  NI_DATA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  bool isRespawning = pHero->IsResurrecting();

END_LUA2CPP_FUNCTION_RET1( isRespawning )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaFlagGetFaction, int, int )

  int faction = -1;

  if (PFFlagpole* pFlag = pAIContainer->FindFlag( arg1, arg2 ))
  {
    faction = pFlag->GetFaction();
  }

END_LUA2CPP_FUNCTION_RET1( faction )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaFlagIsRising, int, int )

  bool isRising = false;
  if (PFFlagpole* pFlag = pAIContainer->FindFlag( arg1, arg2 ))
  {
    isRising = pFlag->IsRising();
  }

END_LUA2CPP_FUNCTION_RET1( isRising )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaGetControlStyle )

bool leftClickMove = false;

if (NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance())
{
  leftClickMove = advScreen->GetControlStyle();
}

END_LUA2CPP_FUNCTION_RET1( leftClickMove )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaGetScriptArea, const char* )

  float x = 0, y = 0, range = 0;
  if ( const NDb::ScriptArea* pScriptArea = pAIContainer->GetScriptArea( arg1 ) )
  {
    x     = pScriptArea->position.x;
    y     = pScriptArea->position.y;
    range = pScriptArea->radius;
  }

END_LUA2CPP_FUNCTION_RET3( x, y, range )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaGetScriptPath, const char* )

  const vector<CVec2>* pPath = pAIContainer->GetScriptPath( arg1 );
  LUA_VERIFY( pPath, NStr::StrFmt( "Scruipt path \"%s\" not found!", arg1 ), return 0; );

  vector<float> path;
  path.reserve( pPath->size() * 2 );
  for ( int i = 0; i < pPath->size(); ++i )
  {
    path.push_back( (*pPath)[i].x ); 
    path.push_back( (*pPath)[i].y ); 
  }

END_LUA2CPP_FUNCTION_RET1( path )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaSetUnitStat, const char*, int, float )

  PFBaseUnit* pUnit = pAIContainer->FindUnit( arg1 );
  NI_DATA_VERIFY( IsValid( pUnit ), NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );
  
  if ( ValueWithModifiers* pVWM = pUnit->GetStat( (NDb::EStat)arg2 ) )
    pVWM->SetValue( arg3 );

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaGetUnitStat, LuaUnitIdParam, int )

  PFBaseUnit* pUnit = FindUnit( pAIContainer, arg1 );

  NI_DATA_VERIFY( IsValid( pUnit ), NStr::StrFmt( "Unit \"%s\" not found!", arg1.pStrValue ), return 0; );

  float value = pUnit->GetStatValue( (NDb::EStat)arg2 );

END_LUA2CPP_FUNCTION_RET1(value)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaGetUnitVariableById, int, const char* )

  PFBaseUnit const* pUnit = dynamic_cast<PFBaseUnit const*>(pAIContainer->GetWorld()->GetObjectById( arg1 ));
  NI_DATA_VERIFY( IsValid( pUnit ), NStr::StrFmt( "Unit id = %d not found!", arg1 ), return 0; );

  float value = pUnit->GetVariableValue( arg2 );

END_LUA2CPP_FUNCTION_RET1(value)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSetUnitHealth, const char*, float )

  PFBaseUnit* pUnit = pAIContainer->FindUnit( arg1 );
  NI_DATA_VERIFY( IsValid( pUnit ), NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  pUnit->SetHealth( arg2 );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSetUnitEnergy, const char*, float )

  PFBaseUnit* pUnit = pAIContainer->FindUnit( arg1 );
  NI_DATA_VERIFY( IsValid( pUnit ), NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  pUnit->SetEnergy( arg2 );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void SetGlobalStatScale(NDb::EStat stat, float statScale, NDb::EUnitType unitType, NDb::EFaction unitFaction)
{
  struct UnitStatModify : NonCopyable
  {
    NDb::EStat      stat;
    float           statScale;
    NDb::EUnitType  unitType;
    NDb::EFaction   unitFaction;

    UnitStatModify(NDb::EStat _stat, float _statScale, NDb::EUnitType _unitType, NDb::EFaction _unitFaction) 
      : stat(_stat), statScale(_statScale), unitType(_unitType), unitFaction(_unitFaction) {}

    void operator()( PF_Core::WorldObjectBase & worldObject )
    {
      // Apply if unit
      CDynamicCast<NWorld::PFBaseUnit> pUnit = &worldObject;
      if (IsValid(pUnit) && (unitType == NDb::UNITTYPE_INVALID || pUnit->GetUnitType() == unitType)
          && (unitFaction == -1 || pUnit->GetFaction() == unitFaction))
      {
        NWorld::ValueWithModifiers *unitValue(pUnit->GetStat(stat));
        if (unitValue)
        {
          unitValue->AddModifier(statScale, 0.0f, PF_Core::WORLD_ID, true);
        }
      }
      else
      {
        // Apply if spawner
        if (unitType == NDb::UNITTYPE_INVALID)
        {
          CDynamicCast<NWorld::PFBaseSpawner> pSpawner = &worldObject;
          if (IsValid(pSpawner) && (unitFaction == -1 || pSpawner->GetFaction() == unitFaction))
          {
            pSpawner->AddStatModifier(stat, statScale, true);
          }
        }
        else if (unitType == NDb::UNITTYPE_CREEP || unitType == NDb::UNITTYPE_SIEGECREEP)
        {
          CDynamicCast<NWorld::PFCreepSpawner> pSpawner = &worldObject;
          if (IsValid(pSpawner) && (unitFaction == -1 || pSpawner->GetFaction() == unitFaction))
          {
            pSpawner->AddStatModifier(stat, statScale, true);
          }
        }
        else if (unitType == NDb::UNITTYPE_NEUTRALCREEP)
        {
          CDynamicCast<NWorld::PFNeutralCreepSpawner> pSpawner = &worldObject;
          if (IsValid(pSpawner) && (unitFaction == -1 || pSpawner->GetFaction() == unitFaction))
          {
            pSpawner->AddStatModifier(stat, statScale, true);
          }
        }
      }
    }
  } unitStatModify(stat, statScale, unitType, unitFaction);

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    if (PFWorld * pWorld = pAdvScreen->GetWorld())
    {
      // Go through all world objects and apply global stat modifier
      pWorld->ForAllObjectsBeingStepped(unitStatModify);
    }
  }
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaSetGlobalStatScale, int, float, int )

  LUA_VERIFY( arg2 > 0.0f, "Wrong stat scale: %f", return 0; );

  SetGlobalStatScale((NDb::EStat)arg1, arg2, (NDb::EUnitType)arg3, (NDb::EFaction)-1);

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaSetGlobalStatScale2, int, float, int, int )

  LUA_VERIFY( arg2 > 0.0f, "Wrong stat scale: %f", return 0; );

  SetGlobalStatScale((NDb::EStat)arg1, arg2, (NDb::EUnitType)arg3, (NDb::EFaction)arg4);

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaGetUnitsInArea, int, int, float, float, float )

  int count = 0;

  if (NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance())
  {
    if (PFWorld* pWorld = advScreen->GetWorld())
    {
      if (PFAIWorld* pAIWorld = pWorld->GetAIWorld())
      {
        CVec2 pos(arg3, arg4);
        struct UnitsCounter : public NonCopyable
        {
          UnitsCounter( CVec2 const& pos, float range, int& counter ) : pos(pos), range(range), counter(counter) {}

          void operator()( PFLogicObject &unit )
          {
            if ( unit.IsInRange( pos, range ) )
              counter++;
          }

          CVec2 const &pos;
          float        range;
          int         &counter;
        } func( pos, arg5, count );
	      pAIWorld->ForAllInRange( CVec3(arg3, arg4, 0.0f), arg5 + pAIWorld->GetMaxObjectSize() * 0.5f, func, UnitMaskingPredicate( arg1, arg2 ) );
      }
    }
  }

END_LUA2CPP_FUNCTION_RET1( count )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaGetLastTalentClicked )

int level = -1;
int column = -1;

if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
{
  if (NGameX::AdventureScreenLogic* pAdvScreenLogic = dynamic_cast<NGameX::AdventureScreenLogic*>(pAdvScreen->GetLogic()))
  {
    pAdvScreenLogic->GetLastTalentClicked( level, column );
  }
}

END_LUA2CPP_FUNCTION_RET2( level, column )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaGetLastItemClicked )

string item;

if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
{
  if (NGameX::AdventureScreenLogic* pAdvScreenLogic = dynamic_cast<NGameX::AdventureScreenLogic*>(pAdvScreen->GetLogic()))
  {
    pAdvScreenLogic->GetLastItemClicked( item );
  }
}

END_LUA2CPP_FUNCTION_RET1( item.c_str() )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaIsShopOpen )

  bool isShopOpen = false;

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    if (NGameX::AdventureScreenLogic* pAdvScreenLogic = dynamic_cast<NGameX::AdventureScreenLogic*>(pAdvScreen->GetLogic()))
    {
      if (NGameX::ShopController* pShopController = pAdvScreenLogic->GetShopController())
      {
        isShopOpen = pShopController->IsShopOpen();
      }
    }
  }

END_LUA2CPP_FUNCTION_RET1( isShopOpen )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaShowTutorialTalentHighlight, int, int, bool )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->ShowTutorialTalentHighlight( arg1, arg2, arg3 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaShowTutorialInventoryItemHighlight, int, bool )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->ShowTutorialInventoryItemHighlight( arg1, arg2 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaShowTutorialShopItemHighlight, int, bool )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->ShowTutorialShopItemHighlight( arg1, arg2 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaShowTutorialActionBarItemHighlight, int, bool )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->ShowTutorialActionBarItemHighlight( arg1, arg2 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaShowTutorialElementHighlight, const char*, bool )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->ShowTutorialElementHighlight( arg1, arg2 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaShowTutorialHeroHighlight, const char*, bool )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  advScreen->ShowTutorialHeroHighlight( pHero->GetPlayerId(), arg2 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaShowTutorialHeroLevelHighlight, const char*, bool )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  advScreen->ShowTutorialHeroLevelHighlight( pHero->GetPlayerId(), arg2 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaShowTutorialOvertipLevelHighlight, const char*, bool )

  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  NGameX::ObjectsInfo2dLogic::SetLevelHighlighting( pHero, arg2 );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaBeginBlockSection )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->OnEscape();
  advScreen->HideCurrentTooltip();
  advScreen->GetUIBlockingController()->BeginBlockSection();
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaAddNonBlockedElement, const char*, bool );
if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->GetUIBlockingController()->AddNonBlockedElement( arg1, false );
}
END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaAddNonBlockedElementTalentBar, int, int, bool );
if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->GetUIBlockingController()->AddNonBlockedElementTalentBar( arg1, arg2, false );
}
END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaAddNonBlockedElementActionBar, int, bool );
if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->GetUIBlockingController()->AddNonBlockedElementActionBar( arg1, false );
}
END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaAddNonBlockedElementHero, const char*, bool );
if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  advScreen->GetUIBlockingController()->AddNonBlockedElementHero( pHero->GetPlayerId(), false );
}
END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaAddNonBlockedElementBubble, const char*, bool );
if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->GetUIBlockingController()->AddNonBlockedElement( arg1, true );
}
END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaAddNonBlockedElementTalentBarBubble, int, int, bool );
if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->GetUIBlockingController()->AddNonBlockedElementTalentBar( arg1, arg2, true );
}
END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaAddNonBlockedElementActionBarBubble, int, bool );
if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->GetUIBlockingController()->AddNonBlockedElementActionBar( arg1, true );
}
END_LUA2CPP_FUNCTION


START_LUA2CPP_FUNCTION_ARG2( LuaAddNonBlockedElementInventoryBarBubble, int, bool );
if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->GetUIBlockingController()->AddNonBlockedElementInventory( arg1, true );
}
END_LUA2CPP_FUNCTION


START_LUA2CPP_FUNCTION_ARG2( LuaAddNonBlockedElementShopBarBubble, int, bool );
if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->GetUIBlockingController()->AddNonBlockedElementShop( arg1, true );
}
END_LUA2CPP_FUNCTION



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaAddNonBlockedElementHeroBubble, const char*, bool );
if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  advScreen->GetUIBlockingController()->AddNonBlockedElementHero( pHero->GetPlayerId(), true );
}
END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaEndBlockSection, float )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->GetUIBlockingController()->EndBlockSection( arg1 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaClearBlocking, float )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->GetUIBlockingController()->ClearBlocking( arg1 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaAddSessionQuest, const char* )
_GET_LUA_ARG( OtherArgs, 2 ) // Hack to make second argument optional. luaValue<OtherArgs>::Get() checks number of arguments on lua stack itself

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  LuaParamsNameMap pMap( &arg2 );
  advScreen->AddSessionQuest( arg1, &pMap );

  if (pAIContainer->GetLogScriptEvents())
  {
    StatisticService::RPC::SessionEventInfo params;
    params.strParam1 = NStr::ToUnicode(arg1);
    advScreen->LogWorldSessionEvent(SessionEventType::ScriptEvent, params);
  }
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaUpdateSessionQuest, const char*, int )

bool isCompleted = false;

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  isCompleted = advScreen->UpdateSessionQuestCounter( arg1, arg2 );
}

END_LUA2CPP_FUNCTION_RET1( isCompleted )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaRemoveSessionQuest, const char* )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->RemoveSessionQuest( arg1 );
}

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaUpdateSessionQuestText, const char*, OtherArgs )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  LuaParamsNameMap pmap( &arg2 );
  advScreen->UpdateSessionQuestText( arg1, &pmap );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSessionQuestRemoveSignal, const char*, const char*  )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->SessionQuestRemoveSignal( arg1, arg2 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaSessionQuestUpdateSignal, const char*, const char*, float, float )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->SessionQuestUpdateSignal( arg1, arg2, arg3, arg4 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaShowUIBlock, const char*, bool )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->ShowUIBlock( arg1, arg2 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaShowAllUIBlocks, bool )

  if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
  {
    advScreen->ShowAllUIBlocks( arg1 );
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaBlockActionBarChange, bool )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->BlockActionBar( arg1 );
}

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//arg1 - dialog id
//arg2 - hintId
//arg3 - imageId

START_LUA2CPP_FUNCTION_ARG3( LuaShowHintDialog, const char*, const char*, const char*)

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  NDb::Ptr<NDb::UITexture> pDBDesc = NDb::Get<NDb::UITexture>( NDb::DBID( pAIContainer->GetFileNameByKey(arg3) ) );
  NI_ASSERT( IsValid(pDBDesc), NStr::StrFmt( "Preloaded resource with id = '%s' not found", arg3 ) );

  const char * dialogHintImagePath = IsValid(pDBDesc) ? pDBDesc->textureFileName.c_str() : "" ;

  advScreen->StartHintDialog( arg1, arg2, dialogHintImagePath);

  if (pAIContainer->GetLogScriptEvents())
  {
    StatisticService::RPC::SessionEventInfo params;
    params.strParam1 = NStr::ToUnicode(arg1);
    advScreen->LogWorldSessionEvent(SessionEventType::ScriptEvent, params);
  }
}

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaStartDialog, const char* )

  if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
  {
    advScreen->StartDialog( arg1, false );

    if (pAIContainer->GetLogScriptEvents())
    {
      StatisticService::RPC::SessionEventInfo params;
      params.strParam1 = NStr::ToUnicode(arg1);
      advScreen->LogWorldSessionEvent(SessionEventType::ScriptEvent, params);
    }
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaIsDialogFinished, const char* )

  bool finished = true;
  if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
  {
    finished = advScreen->IsDialogFinished( arg1 );
  }

END_LUA2CPP_FUNCTION_RET1( finished )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaIsPhraseFinished, const char* )

  bool finished = true;
  if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
  {
    finished = advScreen->IsPhraseFinished( arg1 );
  }

END_LUA2CPP_FUNCTION_RET1( finished )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaPauseDialog, bool )

  if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
  {
    advScreen->PauseDialog( arg1 );
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaStartCinematic, const char* )

  if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
  {
    advScreen->StartDialog( arg1, true );

    if (pAIContainer->GetLogScriptEvents())
    {
      StatisticService::RPC::SessionEventInfo params;
      params.strParam1 = NStr::ToUnicode(arg1);
      advScreen->LogWorldSessionEvent(SessionEventType::ScriptEvent, params);
    }
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaZoomCamera, float, float  )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->GetCamera()->SetManualZoom( arg1, arg2 );
}

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

static void CreateCameraSpline(NGameX::AdventureScreen* pAdvScreen, const NDb::AdvMapCameraSpline* cameraSpline, const Placement basePlacement, float time, bool correctTiming)
{
  PF_Core::SplineCameraController *pMoveToCtrl = new PF_Core::SplineCameraController(correctTiming);
  vector<CVec3> positions;
  vector<CVec3> rotations;
  vector<float> tensions;


  for( int i = 0; i < cameraSpline->points.size(); ++i )
  {
    CVec3 correctPosition = basePlacement.rot.Rotate( cameraSpline->points[i].position );
    correctPosition += basePlacement.pos;

    CVec3 correctRotation = RotateEulerAnglesByQuat( cameraSpline->points[i].rotation, basePlacement.rot );

    positions.push_back( correctPosition );
    rotations.push_back( correctRotation );
    tensions.push_back( cameraSpline->points[i].tension );
  }

  pMoveToCtrl->Init( positions, rotations, time, tensions );

  PF_Core::SplineCameraController *pMoveStartCtrl = NULL;
  PF_Core::SplineCameraController *pMoveEndCtrl = NULL;

  NScene::SCameraPosition posFrom;
  pAdvScreen->GetCamera()->GetCameraPosition(&posFrom);

  // конвертация в градусы, потому что эйлеровы углы хранятся в градусах
  posFrom.ConvertFromRadToDeg();

  float pitch = posFrom.fPitch;
  float roll = posFrom.fRoll;
  float yaw = posFrom.fYaw;

  posFrom.ConvertFromDegToRad();

  const int size = cameraSpline->points.size();
  NI_ASSERT( size > 1, "Spline should have at least 2 points" );

  if( cameraSpline->SmoothStart )
  {
    NI_ASSERT( cameraSpline->StartTime, "StartTime should not be zero")

      pMoveStartCtrl = new PF_Core::SplineCameraController(correctTiming);;

    positions.clear();
    rotations.clear();

    rotations.push_back( CVec3( pitch, roll, yaw ) );

    positions.push_back( posFrom.GetCameraPos() );

    CVec3 temp( cameraSpline->points[0].position + basePlacement.pos );
    positions.push_back( temp );

    rotations.push_back( cameraSpline->points[0].rotation );

    pMoveStartCtrl->Init( positions, rotations, cameraSpline->StartTime );
  }

  if( cameraSpline->SmoothEnd )
  {
    NI_ASSERT( cameraSpline->EndTime, "EndTime should not be zero")

      pMoveEndCtrl = new PF_Core::SplineCameraController(correctTiming);;

    positions.clear();
    rotations.clear();

    CVec3 temp( cameraSpline->points[size-1].position + basePlacement.pos );
    positions.push_back( temp );

    rotations.push_back( cameraSpline->points[size-1].rotation );

    rotations.push_back( CVec3( pitch, roll, yaw ) );

    positions.push_back( posFrom.GetCameraPos() );

    pMoveEndCtrl->Init( positions, rotations, cameraSpline->EndTime );
  }

  if( pMoveEndCtrl )
    pAdvScreen->GetScene()->GetCameraControllers()->AddCameraController( pMoveEndCtrl );

  pAdvScreen->GetScene()->GetCameraControllers()->AddCameraController( pMoveToCtrl );

  if( pMoveStartCtrl )
    pAdvScreen->GetScene()->GetCameraControllers()->AddCameraController( pMoveStartCtrl );

}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSplineCameraTimed, const char*, float )

const char* resName = pAIContainer->GetFileNameByKey(arg1);

if ( NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance() )
{

  if( NDb::Ptr<NDb::AdvMapCameraSpline> cameraSpline = NDb::Get<NDb::AdvMapCameraSpline>( NDb::DBID(resName) ) )
  {
    const Placement& basePlacement = pAIContainer->GetPlacementCameraSpline( cameraSpline->GetDBID() );

    CreateCameraSpline( pAdvScreen, cameraSpline, basePlacement, arg2, false );
  }
}

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSplineCameraTimedNew, const char*, float )

const char* resName = pAIContainer->GetFileNameByKey(arg1);

if ( NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance() )
{

  if( NDb::Ptr<NDb::AdvMapCameraSpline> cameraSpline = NDb::Get<NDb::AdvMapCameraSpline>( NDb::DBID(resName) ) )
  {
    const Placement& basePlacement = pAIContainer->GetPlacementCameraSpline( cameraSpline->GetDBID() );

    CreateCameraSpline( pAdvScreen, cameraSpline, basePlacement, arg2, true );
  }
}

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaIsSplineCameraActive)

  bool ret = false;
  if ( NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance() )
  {
    NScene::ICameraController* pCont = pAdvScreen->GetScene()->GetCameraControllers()->GetActiveController();
    if ( IsValid(pCont) )
    {
      ret = dynamic_cast<PF_Core::SplineCameraController*>(pCont) != 0;
    }

  }
END_LUA2CPP_FUNCTION_RET1( ret )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaSplineCameraShutdown )

if ( NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance() )
{
  NScene::ICameraController* pCont = pAdvScreen->GetScene()->GetCameraControllers()->GetActiveController();
  if(IsValid(pCont))
  {
    if(PF_Core::SplineCameraController* pSplineCam = dynamic_cast<PF_Core::SplineCameraController*>(pCont))
    {
      pSplineCam->Shutdown();
    }
  }
}

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSetHintLine, const char*, const char* )

  if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
  {
    advScreen->SetHintLine( arg1, arg2 );
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaShowMessageBox, const char*, const char* )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->ShowScriptMessageBox( arg1, arg2 );
}

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaGetMessageBoxResult )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  _SET_LUA_RET( advScreen->GetLastMessageBoxResult() );
  return 1;
}

END_LUA2CPP_FUNCTION_RET1( 0 )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaRotateHero, const char*, float, float, float, bool )

  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  PFBaseMovingUnit* pTarget = pHero;
  if ( pHero->IsMounted() )
    pTarget = pHero->GetMount();

  NGameX::PFClientBaseMovingUnit* pClientObject = pTarget->ClientObject();

  if ( !pClientObject )
    return 0;

  pClientObject->LookTo( CVec2( arg2, arg3 ), arg4 < EPS_VALUE ? true : false, arg4 );

  if (!arg5 )
    return 0;

  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return 0;

  NScene::IScene* pScene = advScreen->GetScene();
  if ( !pScene )
    return 0;

  CObj<PF_Core::BasicEffect> pEffect = PF_Core::EffectsPool::Get()->RetrieveKnownEffect<PF_Core::BasicEffect>( NDb::EFFECTS_ROTATEANIMATIONEFFECT );

  if ( !pEffect )
    return 0;

  struct Func
  {
    Func() : found( false ){}
    void operator()(const CObj<PFBaseApplicator>&pAppl )
    {
      if ( pAppl->GetTypeId() == PFApplChangeAnimation::typeId || pAppl->GetTypeId() == PFApplChangeAnimSet::typeId )
        found = true;
    }
    bool found;
  } func;

  pTarget->ForAllAppliedApplicators( func );

  if ( !func.found )
  {
    pEffect->SetDeathType( NDb::EFFECTDEATHTYPE_TIME, arg4 );
    pEffect->Apply( pClientObject );
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaIsHeroMale, const char* )

  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  bool bIsMale = pHero->IsMale();

END_LUA2CPP_FUNCTION_RET1( bIsMale )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSetAdventureControlsEnabled, bool, bool )

  if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
  {
    advScreen->SetAdventureControlsEnabled( arg1, arg2 );
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroGetPrime, const char* )

  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  int prime = pHero->GetGold();

END_LUA2CPP_FUNCTION_RET1( prime )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroAddPrime, const char*, int )

  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  pHero->OnAddGold(0, arg2, false);

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG6( LuaShowTalentBubble, int, int, bool, const char*, const char*, int )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->ShowTalentBubble( arg1, arg2, arg3, arg4, arg5, arg6 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaShowActionBarButtonBubble, int, bool, const char*, const char*, int )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->ShowActionBarButtonBubble( arg1, arg2, arg3, arg4, arg5 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaShowInventoryBarButtonBubble, int, bool, const char*, const char*, int )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->ShowInventoryBarButtonBubble( arg1, arg2, arg3, arg4, arg5 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaShowShopBarButtonBubble, int, bool, const char*, const char*, int )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->ShowShopBarButtonBubble( arg1, arg2, arg3, arg4, arg5 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaShowHeroBubble, const char*, bool, const char*, const char*, int )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  advScreen->ShowHeroBubble( pHero->GetPlayerId(), arg2, arg3, arg4, arg5 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaShowBubble, const char*, bool, const char*, const char*, int )

if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  advScreen->ShowBubble( arg1, arg2, arg3, arg4, arg5 );
}

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaKillUnit, LuaUnitIdParam )

  PFBaseUnit * pUnit = FindUnit( pAIContainer, arg1 );
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1.pStrValue ), return 0 );
  if ( !pUnit->IsDead() )
    pUnit->KillUnit();

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaIsWindowVisible, int )

  bool bVisible = false;
  if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
  {
    bVisible = advScreen->IsWindowVisible( arg1 );
  }

END_LUA2CPP_FUNCTION_RET1( bVisible )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaGetTalentActionBarIndex, int, int )

int index = -1;
if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  index = advScreen->GetTalentActionBarIndex( arg1, arg2 );
}

END_LUA2CPP_FUNCTION_RET1( index )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaGetInventoryItemActionBarIndex, const char* )

int index = -1;
if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
{
  const PFBaseHero* pHero = pAIContainer->GetLocalHero();
  int slotCount = pHero->GetSlotCount();

  string consumableDbid(pAIContainer->GetFileNameByKey(arg1));
  nstl::replace( consumableDbid.begin(), consumableDbid.end(), '\\', '/' ); // Convert \ to /, as used in dbid

  for ( int i = 0; i < slotCount; ++i )
  {
    if ( const PFConsumable * pConsumable = pHero->GetConsumable(i) )
    {
      if ( pConsumable->GetDBDesc()->GetDBID().GetFileName() == consumableDbid )
      {
        index = advScreen->GetInventoryItemActionBarIndex( i );
        break;
      }
    }
  }
}

END_LUA2CPP_FUNCTION_RET1( index )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaSetHeroRespawnParams, const char* )

  if ( NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance() )
  {
    if ( NWorld::PFWorld* pWorld = pAdvScreen->GetWorld() )
    {
      if ( NWorld::PFAIWorld* pAIWorld = pWorld->GetAIWorld() )
      {
        NDb::Ptr<NDb::HeroRespawnParams> const& pDBParams = NDb::Get<NDb::HeroRespawnParams>( NDb::DBID( pAIContainer->GetFileNameByKey( arg1 ) ) );
        NI_DATA_VERIFY( pDBParams, "Trying to set invalid HeroRespawnParams", return 0 );
        pAIWorld->SetHeroRespawnParams( pDBParams );
      }
    }
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaSubscribeUnitEvent, const char*, int, const char* )

  pAIContainer->RegisterEventScriptHandler( arg1, (NDb::EBaseUnitEvent)arg2, arg3 );

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaUnsubscribeUnitEvent, const char*, int )

  pAIContainer->UnregisterEventScriptHandler( arg1, (NDb::EBaseUnitEvent)arg2 );

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaApplyPassiveAbility, const char*, const char* )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0 );

  NDb::Ptr<NDb::Ability> pDBDesc = NDb::Get<NDb::Ability>( NDb::DBID( pAIContainer->GetFileNameByKey(arg2) ) );
  LUA_VERIFY( pDBDesc, NI_STRFMT( "Ability \"%s\" not found", arg2 ), return 0 );

  CObj<PFAbilityData> pAbility = new PFAbilityData( pUnit, pDBDesc, NDb::ABILITYTYPEID_SPECIAL, true, true );

  pUnit->RegisterExternalPassiveAbility( pAbility );
  pAbility->ApplyPassivePart(true);
  int id = pAbility->GetObjectId();

END_LUA2CPP_FUNCTION_RET1(id)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaRemovePassiveAbility, const char*, int )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0 );

  PFWorld* pWorld =  pUnit->GetWorld();

  CDynamicCast<PFAbilityData> pAbility( pWorld->GetObjectById( arg2 ) );
  LUA_VERIFY( pAbility, NStr::StrFmt( "Object #%d is not PFAbilityData!", arg2 ), return 0 );

  LUA_VERIFY( pUnit->UnregisterExternalPassiveAbility( pAbility ), NStr::StrFmt( "Unit \"%s\" has no registered ability #%d!", arg1, arg2 ), return 0 );

  pAbility->ApplyPassivePart(false);

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaUnitInvokeItsAbility, const char*, int, const char* )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0 );

  PFBaseUnit * pTarget = pAIContainer->FindUnit(arg3);
  LUA_VERIFY( pTarget, NStr::StrFmt( "Unit \"%s\" not found!", arg3 ), return 0 );

  CObj<IPFState> pState = pUnit->InvokeAbility( arg2, Target( pTarget ) );
  if ( IsValid(pState) )
  {
    pUnit->EnqueueState( pState, true );
  }

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_LUA2CPP_FUNCTION_ARG3( LuaChangeNatureMap, const char*, int, int )

  const NDb::ScriptArea* pScriptArea = pAIContainer->GetScriptArea(arg1);
  LUA_VERIFY( pScriptArea, NStr::StrFmt( "Script area \"%s\" not found!", arg1 ), return 0 );

  LUA_VERIFY( arg2 < NDb::KnownEnum<NDb::ENatureType>::sizeOf, "Nature type 'from' should be valid nature type or -1", return 0 );
  LUA_VERIFY( arg3 >= 0 && arg3 < NDb::KnownEnum<NDb::ENatureType>::sizeOf, "Nature type 'to' should be valid nature type", return 0 );

  pAIContainer->ChangeNatureMap( pScriptArea->position.x, pScriptArea->position.y, pScriptArea->radius, (NDb::ENatureType)arg2, (NDb::ENatureType)arg3 );
  
END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaChangeNatureMapXY, float, float, float, int, int )


LUA_VERIFY( arg4 < NDb::KnownEnum<NDb::ENatureType>::sizeOf, "Nature type 'from' should be valid nature type or -1", return 0 );
LUA_VERIFY( arg5 >= 0 && arg5 < NDb::KnownEnum<NDb::ENatureType>::sizeOf, "Nature type 'to' should be valid nature type", return 0 );

pAIContainer->ChangeNatureMap( arg1, arg2, arg3, (NDb::ENatureType)arg4, (NDb::ENatureType)arg5 );

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaChangeNatureMapPolyArea, const char*, const char*, int, int )

  LUA_VERIFY( arg3 < NDb::KnownEnum<NDb::ENatureType>::sizeOf, "Nature type 'from' should be valid nature type or -1", return 0 );
  LUA_VERIFY( arg4 >= 0 && arg4 < NDb::KnownEnum<NDb::ENatureType>::sizeOf, "Nature type 'to' should be valid nature type", return 0 );
  struct Func
  {
    PFWorldNatureMap* pMap;
    NDb::ENatureType from;
    NDb::ENatureType to;
    Func( PFWorldNatureMap* pMap, NDb::ENatureType from, NDb::ENatureType to ):pMap(pMap),from(from), to(to) {}
    void operator()( const vector<CVec2>& polygon )
    {
      pMap->ChangeNature( polygon, from, to );
    }
  } func(pAIContainer->GetWorld()->GetNatureMap(),(NDb::ENatureType)arg3, (NDb::ENatureType)arg4);

  LUA_VERIFY( pAIContainer->ForAllPartsInPolygonArea(arg1, arg2, func), NStr::StrFmt( "Script polygon area \"%s\".\"%s\" not found!", arg1, arg2 ), return 0 );

END_LUA2CPP_FUNCTION
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::ChangeNatureMap( const float x, const float y, const float radius, NDb::ENatureType from, NDb::ENatureType to)
{
  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( !advScreen )
    return false;

  PFWorld *world = advScreen->GetWorld();
  if ( !world )
    return false;  

  world->GetNatureMap()->ChangeNature( CVec2(x,y), radius, from, to );
  return true;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSetHeroProgress, const char*, float )

  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );
  
  LUA_VERIFY( arg2 >= 0.f && arg2 <= 1.f, "LuaSetHeroProgress: progress should be between 0 and 1!", arg2 = Clamp( arg2, 0.f, 1.f ) );
  pHero->SetScriptControlledProgressValue( arg2 ); 


END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSetCreepFaction, const char*, int )

  PFLogicObject *pObject = pAIContainer->FindUnit( arg1 );
  if (!pObject)
  pObject = dynamic_cast<PFLogicObject*>(pAIContainer->FindObject(arg1));

  LUA_VERIFY( pObject, NStr::StrFmt( "Object \"%s\" not found!", arg1 ), return 0 );

  pObject->ChangeFaction( (NDb::EFaction)arg2 );

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSetCreepWarfogFaction, const char*, int )

  PFBaseCreep *pCreep =  dynamic_cast<PFBaseCreep*>(pAIContainer->FindUnit( arg1 ));
  LUA_VERIFY( pCreep, NStr::StrFmt( "Creep \"%s\" not found!", arg1 ), return 0 );

  pCreep->SetWarfogFaction( (NDb::EFaction)arg2 );

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaGetUnitFaction, const char* )

  PFLogicObject *pObject = pAIContainer->FindUnit( arg1 );
  if (!pObject)
    pObject = dynamic_cast<PFLogicObject*>(pAIContainer->FindObject(arg1));

  LUA_VERIFY( pObject, NStr::StrFmt( "Object \"%s\" not found!", arg1 ), _SET_LUA_RET( -1 ); return 1 );

END_LUA2CPP_FUNCTION_RET1( (int)pObject->GetFaction() )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaGetUnitFactionById, int )

  PFLogicObject *pObject = dynamic_cast<PFLogicObject*>(pAIContainer->GetWorld()->GetObjectById(arg1));

  LUA_VERIFY( pObject, NStr::StrFmt( "Object id = %d not found!", arg1 ), _SET_LUA_RET( -1 ); return 1 );

END_LUA2CPP_FUNCTION_RET1( (int)pObject->GetFaction() )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaForceAnimation, const char*, const char*, int )

  PFCreature *pObject = dynamic_cast<PFCreature*>(pAIContainer->FindUnit( arg1 ));
  LUA_VERIFY( pObject, NStr::StrFmt( "Creature \"%s\" not found!", arg1 ), return 0 );

  pObject->ForceAnimation(arg2, arg3);

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaStopForcedAnimation, const char* )

  PFCreature *pObject = dynamic_cast<PFCreature*>(pAIContainer->FindUnit( arg1 ));
  LUA_VERIFY( pObject, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0 );

  pObject->StopForcedAnimation();

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaHeroAIPushPath, const char*, const char*, bool )
  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  const vector<CVec2> *pPath = pAIContainer->GetScriptPath( arg2 );
  LUA_VERIFY( pPath, NStr::StrFmt( "Script path \"%s\" not found!", arg2 ), return 0 );

  IPFSeriesAIController *controler = pAIContainer->AddSeriesController( pHero, arg3 );
  controler->StartPushPath(*pPath);

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroAIFollowHero, const char*, const char* )
  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  PFBaseUnit * pMaster = pAIContainer->FindCreature( arg2 );
  LUA_VERIFY( pMaster, NStr::StrFmt( "Creature \"%s\" not found!", arg2 ), return 0 );

  IPFSeriesAIController *controler = pAIContainer->AddSeriesController( pHero, true );
  controler->StartSupport(pMaster);
END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaHeroAIGuardScriptArea, const char*, const char*, bool )
  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  const NDb::ScriptArea* pScriptArea = pAIContainer->GetScriptArea(arg2);
  LUA_VERIFY( pScriptArea, NStr::StrFmt( "Script area \"%s\" not found!", arg2 ), return 0 );

  IPFSeriesAIController *controler = pAIContainer->AddSeriesController( pHero, arg3 );
  controler->StartGuardPoint(pScriptArea->position, pScriptArea->radius, 0.f );

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaHeroAIGuardArea2, const char*, float, float, float, float )
  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );
  
  CVec2 pos( arg2, arg3 );
  IPFSeriesAIController *controler = pAIContainer->AddSeriesController( pHero, true );
  controler->StartGuardPoint( pos, arg4, arg5 );
END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroAIDisable, const char* )
  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  pAIContainer->Remove( pHero );
END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroAIReceiveMinimapSignals, const char*, bool )
  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0 );

  IPFSeriesAIController *controller = pAIContainer->AddSeriesController( pHero, true );
  controller->EnableMinimapSignal( arg2 );
END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class UnitType>
struct UnitIdsCollector : NonCopyable
{
  UnitIdsCollector() {}

  void operator()(PFLogicObject &baseUnit)
  {
    CDynamicCast<UnitType> unit = &baseUnit;
    if (unit)
      objectsIds.insert( unit->GetObjectId() );
  }

  hash_set<int> objectsIds;
};

START_LUA2CPP_FUNCTION_ARG4( LuaGetCreepsInArea, float, float, float, int )

  vector<const char*> res;

  if ( NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance() )
  {
    if ( NWorld::PFWorld* pWorld = pAdvScreen->GetWorld() )
    {
      if ( NWorld::PFAIWorld* pAIWorld = pWorld->GetAIWorld() )
      {
          UnitIdsCollector<PFBaseCreep> collector;
          pAIWorld->ForAllUnitsInRange(CVec3( arg1, arg2,0), arg3, collector, UnitMaskingPredicate(arg4) );
          pAIContainer->GetCreepNames(collector.objectsIds, &res);
      }
    }
  }

END_LUA2CPP_FUNCTION_RET1( res )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaIsUnitVisible, const char* )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  PFBaseHero * pHeroLocal = pAIContainer->GetLocalHero();
  LUA_VERIFY( pHeroLocal, NStr::StrFmt( "Local hero not found!" ), return 0; );

  bool res = pUnit->IsVisibleForEnemy(pHeroLocal->GetFaction());

END_LUA2CPP_FUNCTION_RET1( res )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaCreateMinimapSignal, float, float )

  PFBaseHero * pHeroLocal = pAIContainer->GetLocalHero();
  LUA_VERIFY( pHeroLocal, NStr::StrFmt( "Local hero not found!" ), return 0; );

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    CObj<NCore::WorldCommand> pCommand;

    Target t( CVec3(arg1, arg2, 0) );
    pCommand = CreateCmdMinimapSignal(pHeroLocal, 0, t, pHeroLocal->GetFaction(), true );
    pAdvScreen->SendGameCommand( pCommand );
  }

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaGetUnitType, const char* )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  int res = pUnit->GetUnitType();
END_LUA2CPP_FUNCTION_RET1(res)


START_LUA2CPP_FUNCTION_ARG1( LuaGetUnitTypeById, int )

  PFBaseUnit * pUnit = dynamic_cast<PFBaseUnit*>(pAIContainer->GetWorld()->GetObjectById(arg1));
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit id = %d not found!", arg1 ), return 0; );

  int res = pUnit->GetUnitType();
END_LUA2CPP_FUNCTION_RET1(res)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaIsUnitAttacked, const char* )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  struct HasAnyPred
  {
    HasAnyPred() : found(false) {}
    bool operator()( PFLogicObject& _unit )
    {
        found = true;
        return true;
    }
    bool found;
  } pr;
  pUnit->ForAllAttackersOnce( pr );

END_LUA2CPP_FUNCTION_RET1(pr.found)
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaIsUnitAttackedByObject, const char*, const char*  )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), _SET_LUA_RET( false ); return 1 );

  PFLogicObject *pObject = dynamic_cast<PFLogicObject*>(pAIContainer->FindObject(arg2));

  LUA_VERIFY( pObject, NStr::StrFmt( "Object \"%s\" not found!", arg2 ), _SET_LUA_RET( false ); return 1 );

  struct HasObjectPred
  {
    HasObjectPred(PFLogicObject* _toFind) : found(false), toFind(_toFind) {}
    bool operator()( PFLogicObject& _unit )
    {
      if ( (&_unit) != toFind )
        return false;
      found = true;
      return true;
    }
    bool found;
    PFLogicObject* toFind;
  } pr(pObject);
  pUnit->ForAllAttackersOnce( pr );

END_LUA2CPP_FUNCTION_RET1(pr.found)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG4( LuaCreateGlyph, const char*, const char*, float, float )

  NDb::Ptr<NDb::Glyph> dbObj = NDb::Get<NDb::Glyph>( NDb::DBID( pAIContainer->GetFileNameByKey(arg2) ) );
  NI_DATA_VERIFY( IsValid( dbObj ), NStr::StrFmt( "Glyph \"%s\" not found!", pAIContainer->GetFileNameByKey(arg2) ), return 0 );

  PFWorld* pWorld = pAIContainer->GetWorld();
  PFGlyph * pGlyph = new PFGlyph( pWorld, dbObj, CVec3( arg3, arg4, 0 ) );
  pGlyph->SetScriptName( string(arg1) );

  NI_ASSERT( pAIContainer->FindObject( arg1 ) == 0, NStr::StrFmt( "Object %s already registered", arg2 ) );
  pAIContainer->RegisterObject( pGlyph, string(arg1), "" );

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaEnableGlyph, const char*, bool )

  PF_Core::WorldObjectBase* pObject = pAIContainer->FindObject( arg1 );
  LUA_VERIFY( pObject, NStr::StrFmt( "Object \"%s\" not found!", arg1 ), return 0 );
  PFGlyph* pGlyph = dynamic_cast<PFGlyph*>(pObject);
  LUA_VERIFY( pObject, NStr::StrFmt( "Object \"%s\" is not a glyph!", arg1 ), return 0 );

  pGlyph->SetEnabled( arg2 );

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaIsObjectExists, const char* )

  bool res = false;
  PF_Core::WorldObjectBase* pObject = pAIContainer->FindObject( arg1 );
  if ( IsValid(pObject) )
    res = true;

END_LUA2CPP_FUNCTION_RET1(res);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaAddHeroToInfoPanel, const char* )

  PFBaseHero * pHero = pAIContainer->FindHero( arg1 );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero %s not found!", arg1 ), return 0; );

  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    pAdvScreen->AddHeroToInfoPanel( pHero );
  }
END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaFadeScene, int, float )

  LUA_VERIFY( arg1 >= 0 && arg1 <= 255 , NStr::StrFmt( "Fade value %d, should be in range [0..255]!", arg1 ), arg1 = Clamp( arg1, 0, 255) );
  if (NGameX::AdventureScreen* pAdvScreen = NGameX::AdventureScreen::Instance())
  {
    pAdvScreen->FadeScene( arg1, arg2 );
  }
END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaSetCreepBasePlace, const char*, float, float )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), _SET_LUA_RET( false ); return 1 );

  PFNeutralCreep* pCreep = dynamic_cast<PFNeutralCreep*>(pUnit);
  LUA_VERIFY( pCreep, NStr::StrFmt( "Unit \"%s\" is not a neutral creep!", arg1 ), _SET_LUA_RET( false ); return 1 );

  CVec2 place(arg2, arg3);
  CVec2 foundPos;
  const bool placeFound = pCreep->FindFreePlace( place, pCreep->GetUnitRadius() * 8, foundPos );

  LUA_VERIFY( placeFound, NStr::StrFmt( "Cannot place unit near %.1f,%.1f: no free space!", arg2, arg3 ), _SET_LUA_RET( false ); return 1 );

  pCreep->SetPositionBySpawner(foundPos);
  pCreep->Cleanup();

END_LUA2CPP_FUNCTION_RET1( true )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaIsUnitInPolyArea, const char*, const char*, const char* )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  struct UnitsChecker
  {
    CVec2 pos;
    bool inArea;
    UnitsChecker( const CVec2& pos ):pos(pos),inArea(false) {}
    void operator()( const vector<CVec2>& polygon )
    {
      if ( ClassifyPolygon( polygon, pos ) != CP_OUTSIDE )
        inArea = true;
    }
  } func(pUnit->GetPos());
  LUA_VERIFY( pAIContainer->ForAllPartsInPolygonArea(arg2, arg3, func), NStr::StrFmt( "Script polygon area \"%s\".\"%s\" not found!", arg2, arg3 ), return 0 );

END_LUA2CPP_FUNCTION_RET1( func.inArea )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaCreateFlagpoleChain, const char*, vector<const char*> )

  vector<PFScriptedFlagpole*> flagpoles;
  for ( int i = 0; i < arg2.size(); ++i )
  {
    PFScriptedFlagpole* pPole = dynamic_cast<PFScriptedFlagpole*>(pAIContainer->FindUnit(arg2[i]));
    LUA_VERIFY( pPole, NStr::StrFmt( "ScriptedFlagpole \"%s\" not found!", arg2[i] ), continue );
    flagpoles.push_back(pPole);
  }
  if ( flagpoles.empty() )
    return 0;
  PFScriptedFlagpole::CreateGroup(flagpoles, arg1);
END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaGetRaisedFlagpolesInChain, const char* )
  int res = PFScriptedFlagpole::GetRaisedCountInGroup( arg1 );
END_LUA2CPP_FUNCTION_RET1(res)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaSetRaisedFlagpolesInChain, const char*, int, const char* )
  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg3);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg3 ), return 0; );

  PFScriptedFlagpole::SetRaisedCountInGroup( arg1, arg2, pUnit );
END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSetNatureProgress, float, float )

  pAIContainer->GetWorld()->GetNatureMap()->SetCustomNaturePercents( arg1, arg2 );
END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::CreateZombie( PFCreature const* pCreature, const char* dbid, const NDb::EFaction faction )
{
  NDb::Ptr<NDb::AdvMapCreep> creepDb = NDb::Get<NDb::AdvMapCreep>( NDb::DBID( dbid ) );
  NI_DATA_VERIFY( IsValid( creepDb ), NStr::StrFmt( "Creep \"%s\" not found", dbid ), return false );

  Placement place;
  place.pos = pCreature->GetPosition();
  place.rot = CQuat( CVec3(pCreature->GetMoveDirection(), 0 ), true );

  PFCreepSpawner* pSpawner = GetWorld()->GetAIWorld()->FindSpawnerWithRouteNearestToPoint( place.pos.AsVec2D(), faction );
  if ( pSpawner )
  {
    PFCommonCreep* pCreep = new PFCommonCreep( GetWorld(), *creepDb, (NDb::EFaction)faction, place, pSpawner->GetPath(), 0, 0, pSpawner );
    pSpawner->InitializeCreep( pCreep, creepDb->recolor );
    pCreep->DoLevelups( pCreature->GetNaftaLevel() - pCreep->GetNaftaLevel() );

    DevTrace("pSpawner->GetDBDesc().routeID=%d", (int)pSpawner->GetDBDesc()->routeID);
  }

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaCreateZombieById, int, const char*, int )

  PFCreature const* pCreature = dynamic_cast<PFCreature const*>( pAIContainer->GetWorld()->GetObjectById( arg1 ) );
  LUA_VERIFY( pCreature, NStr::StrFmt( "Creature id = %d not found!", arg1 ), return false );

  bool success = pAIContainer->CreateZombie(pCreature, pAIContainer->GetFileNameByKey(arg2), (NDb::EFaction)arg3 );

END_LUA2CPP_FUNCTION_RET1( success )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG3( LuaSetCreepBehavior, const char*, const char*, OtherArgs )

  PFNeutralCreep* pCreep = dynamic_cast<PFNeutralCreep*>( pAIContainer->FindCreature( arg1 ) );
  LUA_VERIFY( pCreep, NStr::StrFmt( "Creep %s not found!", arg1 ), return 0 );

  pCreep->SetCreepBehavior( arg2, arg3.args );
END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1(LuaGetDbid, const char*)
  const char* ret = pAIContainer->GetFileNameByKey(arg1);
END_LUA2CPP_FUNCTION_RET1( ret )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaUnitGetDbid, const char* )

  PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
  LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

  string id = pUnit->DbUnitDesc()->GetDBID().GetFormatted();

END_LUA2CPP_FUNCTION_RET1( id.c_str() )
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MakeUnitLevelupsForTimeDelta( PFWorld* pWorld, float dtInSeconds )
{
  struct UnitLeveluper : NonCopyable
  {
    float dtInSeconds;

    UnitLeveluper(float dtInSeconds) 
      : dtInSeconds(dtInSeconds){}

    void operator()( PF_Core::WorldObjectBase & worldObject )
    {
      CDynamicCast<NWorld::PFBaseCreep> pCreep( &worldObject );
      if ( IsValid(pCreep) )
      {
        pCreep->MakeLevelupsForTimeDelta( dtInSeconds );
        return;
      }
      CDynamicCast<NWorld::PFBaseSpawner> pSpawner( &worldObject );
      if ( IsValid(pSpawner) )
      {
        pSpawner->MakeLevelupsForTimeDelta( dtInSeconds );
        return;
      }
      CDynamicCast<NWorld::PFBuilding> pBuilding( &worldObject );
      if ( IsValid(pBuilding) )
      {
        pBuilding->MakeLevelupsForTimeDelta( dtInSeconds );
        return;
      }
    }
  } unitLeveluper(dtInSeconds);

  pWorld->ForAllObjectsBeingStepped(unitLeveluper);
}
START_LUA2CPP_FUNCTION_ARG1( LuaMakeUnitLevelupsForTimeDelta, float )

  LUA_VERIFY( arg1 > 0.0f, "Time delta should be positive!", return 0 );

  MakeUnitLevelupsForTimeDelta( pAIContainer->GetWorld(), arg1 );
END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG5( LuaPlaceMinimapIcon, const char*, int, float, float, int )
  LUA_VERIFY( arg2 >= 0 && arg2 < NDb::KnownEnum<NDb::EMinimapIcons>::sizeOf, NStr::StrFmt( "Minimap icons index %d is not valid!", arg2 ), return 0  );
  NDb::EMinimapIcons icon = (NDb::EMinimapIcons)arg2;

  NDb::EUnitType unitType = NDb::UNITTYPE_FLAGPOLE;
  if( arg5 == 1 )
    unitType = NDb::UNITTYPE_BUILDING;
  else if ( arg5 == 2)
    unitType = NDb::UNITTYPE_HEROMALE;

  pAIContainer->PlaceMinimapIcon( arg1, icon, arg3, arg4, unitType );

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaRemoveMinimapIcon, const char* )

  pAIContainer->RemoveMinimapIcon( arg1 );

END_LUA2CPP_FUNCTION
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaHeroIsCloneById, int )

  PFBaseHero const* pHero = dynamic_cast<PFBaseHero const*>( pAIContainer->GetWorld()->GetObjectById( arg1 ) );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero id = %d not found!", arg1 ), return false );

  bool isClone = pHero->IsClone();

END_LUA2CPP_FUNCTION_RET1( isClone )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaUnitIsIdle, const char* )

PFBaseUnit * pUnit = pAIContainer->FindUnit(arg1);
LUA_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0; );

END_LUA2CPP_FUNCTION_RET1( pUnit->IsIdle() )


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroRaiseFlag, const char*, const char* )

  pAIContainer->HeroRaiseFlag( arg1, arg2 );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaGetDBIDByKey, const char* )
END_LUA2CPP_FUNCTION_RET1( pAIContainer->GetFileNameByKey(arg1) )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

START_LUA2CPP_FUNCTION( LuaGetLastPlayerActivityStep )
  float ret = 0.f;
  if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
  {
    ret = advScreen->GetLastPlayerActivityStep();
  }
END_LUA2CPP_FUNCTION_RET1( ret )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaSetCreepsLevelupPaused, bool )

  pAIContainer->GetWorld()->GetAIWorld()->SetCreepLevelupPaused( arg1 );

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaHeroReplace, const char*, const char* )

  PFBaseMaleHero* pHero = dynamic_cast<PFBaseMaleHero*>( pAIContainer->FindHero( arg1 ) );
  LUA_VERIFY( pHero, NStr::StrFmt( "Hero \"%s\" not found!", arg1 ), return 0; );

  const char* newName = pAIContainer->GetFileNameByKey(arg2);
  NDb::Ptr<NDb::BaseHero> pDBHero = NDb::Get<NDb::BaseHero>( NDb::DBID( newName ) );
  LUA_VERIFY( pDBHero, NStr::StrFmt( "Hero data \"%s\" not found!", newName ), return 0; );

  PFPlayer* pPlayer = pHero->GetPlayer();
  PFWorld* world = pAIContainer->GetWorld();

  int inTeamId = 1;
  for( int i = 0; i < world->GetPlayersCount(); ++i )
  {
    PFPlayer* player = world->GetPlayer( i );
    if ( player == pPlayer )
      break;
    if ( player->GetTeamID() == pPlayer->GetTeamID() )
      ++inTeamId;
  }

  PFBaseHero::SpawnInfo info;
  info.pHero     = pDBHero;
  info.playerId  = pPlayer->GetPlayerID();
  info.placement = Placement(pHero->GetPosition(), QNULL, CVec3(1.0f, 1.0f, 1.0f) );
  info.faction   = pHero->GetFaction();
  info.originalFaction = pHero->GetOriginalFaction();
  info.inTeamId  = inTeamId;
  info.isClone   = false;

  pHero->DetachFromPlayer();
  pPlayer->DetachHero();

  PFBaseHero* pNewHero = NWorld::CreateHero(world, info);

  pNewHero->ChangeFaction( pHero->GetFaction() );
  pNewHero->AddGold( pHero->GetGold(), false );

  pHero->SetForbidRespawn( true );
  pHero->DebugDie();
  //pHero->KillUnit( 0, PFBaseUnit::UNITDIEFLAGS_FORCEREMOVECORPSE );

  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( advScreen )
  {
    uint overrideId = Crc32Checksum().AddString(pDBHero->persistentId.c_str()).Get();
    const wstring& nickname = NWorld::FindHeroNickname( world->GetMapDescription(), pDBHero );
    advScreen->OverrideHeroId( pPlayer->GetPlayerID(), overrideId, "", nickname );
  }

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaCameraGetLock )

 bool lock = false;
 if ( NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance() )
 {
   lock = advScreen->GetCamera()->IsObservingMode();
 }

END_LUA2CPP_FUNCTION_RET1( lock )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaGetObjectId, const char* )

  const PFLogicObject* pObj = dynamic_cast<const PFLogicObject*>(pAIContainer->FindObject( arg1 ));
  LUA_VERIFY( pObj, NStr::StrFmt( "Object \"%s\" as PFLogicObject not found!", arg1 ), return 0 );

  int id = pObj->GetWOID();

END_LUA2CPP_FUNCTION_RET1( id )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaGetAllUnits, int, int )
  
  vector<int> unitsTable;

  struct CreepCollector : public NonCopyable
  {
    vector<int>& unitsTable;
    UnitMaskingPredicate umPred;
    CreepCollector( vector<int>& _unitsTable, int _faction, int _unitTypeMask ) : unitsTable(_unitsTable), umPred( 1 << _faction, _unitTypeMask )  {}
    void operator()(const PFBaseUnit& unit)
    {
      if ( umPred( unit ) )
        unitsTable.push_back( unit.GetWOID() );
    }
  } creepCollector( unitsTable, arg1, arg2 );

  pAIContainer->GetWorld()->GetAIWorld()->ForAllUnits( creepCollector );

END_LUA2CPP_FUNCTION_RET1( unitsTable )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG2( LuaSetHeroSpecialPoints, LuaUnitIdParam, int )

  PFBaseUnit* pUnit = FindUnit( pAIContainer, arg1 );

  LUA_VERIFY( IsValid( pUnit ), NStr::StrFmt( "Unit \"%s\" not found!", arg1.pStrValue ), return 0 );

  LUA_VERIFY( pUnit->IsTrueHero(), "LuaSetHeroSpecialPoints: Not a true hero", return 0 );

  PFBaseHero* pHero = static_cast<PFBaseHero*>(pUnit);
  PFHeroStatistics* pStatistics = pHero->GetHeroStatistics();

  NI_VERIFY( pStatistics, "No hero statistics",  return 0 );

  pStatistics->SetSpecialPoints( arg2 );

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaGetGSLogicParam1 )

  float param1 = 0.0f;

  if (NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance())
  {
    param1 = advScreen->GetGSClientSettings().logicParam1;
  }

END_LUA2CPP_FUNCTION_RET1( param1 )

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaEnableEventLogging, bool )

  pAIContainer->SetLogScriptEvents(arg1);

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaPrintWorldSessionEventGuardStatistic )

NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
if ( advScreen )
{
  Weak<StatisticService::GameStatGuard> statGuard = advScreen->GetStatisticsGuard();
  if(statGuard)
    statGuard->PrintGuardStatistic();
}

END_LUA2CPP_FUNCTION

static bool g_WorldSessionEventGuardEnabled = true;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG7( LuaLogWorldSessionEvent, const char*, const char*, int, int, int, int, int )

  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( advScreen )
  {
    StatisticService::RPC::SessionEventInfo params;
    params.strParam1 = NStr::ToUnicode(arg1);
    params.strParam2 = NStr::ToUnicode(arg2);
    params.intParam1 = arg3;
    params.intParam2 = arg4;
    params.intParam3 = arg5;
    params.intParam4 = arg6;
    params.intParam5 = arg7;

    if (g_WorldSessionEventGuardEnabled)
    {
      Weak<StatisticService::GameStatGuard> statGuard = advScreen->GetStatisticsGuard();
      if(statGuard)
      {
        StatisticService::GuardDataInspectResult inspectResult = statGuard->Inspect(params, pAIContainer->GetWorld()->GetStepNumber());

        LUA_VERIFY( inspectResult == StatisticService::INSPECT_OK,
          NStr::StrFmt("LuaLogWorldSessionEvent receive a lot of messages (%s) %s",NStr::ToMBCS(*(advScreen->GetStatisticsGuard()->GetLastInspectedMsg())).c_str(), inspectResult == StatisticService::INSPECT_STEP_ERR ? "steps cap" : "count cap"),
          return false);
      }
    }
    else
    {
      const nstl::string eventName(NStr::ToMBCS(params.strParam1));

      DevTrace("[Lua] LuaLogWorldSessionEvent('%s') bypassed game statistics guard!", eventName.c_str());

      g_WorldSessionEventGuardEnabled = true;
    }

    advScreen->LogWorldSessionEvent(SessionEventType::ScriptEvent, params);
  }

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION( LuaDontGuardNextWorldSessionEvent )

  g_WorldSessionEventGuardEnabled = false;

END_LUA2CPP_FUNCTION

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
START_LUA2CPP_FUNCTION_ARG1( LuaSetTimeScale, float )

  NGlobal::RunCommand(NStr::StrFmtW(L"timescale %f", arg1));

END_LUA2CPP_FUNCTION


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//arg1 unitScriptName
//arg2 faction 0|1|2
//arg3 flag status, raised or lowered
//
START_LUA2CPP_FUNCTION_ARG3( LuaCaptureTheFlag, const char*, int, bool )

LUA_VERIFY( arg2 >= 0 && arg2 < NDb::KnownEnum<NDb::EFaction>::sizeOf, NStr::StrFmt( "Faction index %d is not valid!", arg2 ), return false  );

  pAIContainer->CaptureTheFlag(arg1, (NDb::EFaction)arg2, arg3);

END_LUA2CPP_FUNCTION

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//arg1 unitScriptName
//arg2 faction on|off
//arg3 line number
//
START_LUA2CPP_FUNCTION_ARG3( LuaAISwitcher, const char*, bool, int )

  LUA_VERIFY( arg3 >= 0 && arg3 < NDb::KnownEnum<NDb::ENatureRoad>::sizeOf, NStr::StrFmt( "Line index %d is not valid!", arg3 ), return false  );

  PFBaseHero* pHero = pAIContainer->FindHero(arg1);

  LUA_VERIFY( IsValid( pHero ), NStr::StrFmt( "Unit \"%s\" not found!", arg1 ), return 0 );

  if(IsValid(pHero))
  {
  if(arg2)
    pAIContainer->Add(pHero, arg3);
  else
    pAIContainer->Remove(pHero);
  }

END_LUA2CPP_FUNCTION


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
LUA_EXPORT_NDBENUM(NDb::EFaction);
LUA_EXPORT_NDBENUM(NDb::EAbilityType);
LUA_EXPORT_NDBENUM_EX(NDb::EBaseUnitEvent, NDb::BASEUNITEVENT_MOVE, "Event");
LUA_EXPORT_NDBENUM_EX(NDb::EStat, NDb::STAT_LIFE, "Stat");
LUA_EXPORT_NDBENUM_EX(NDb::EUnitType, NDb::UNITTYPE_INVALID, "UnitType");
LUA_EXPORT_NDBENUM_EX(NDb::ENatureRoad, NDb::NATUREROAD_TOP, "NatureRoad");
// EUnitFlag enum is exported one by one because it is not consecutive
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDMOVE)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDSELECTTARGET)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDATTACK)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBID_ABILITY1)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBID_ABILITY2)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBID_ABILITY3)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBID_ABILITY4)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDTAKEDAMAGE)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDAUTOTARGETME)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDUSECONSUMABLES)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDUSETALENTS)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_ISOLATED)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_INVISIBLE)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_CANSEEINVISIBLE)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_STUN)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDLIFERESTORE)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDENERGYRESTORE)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_IGNOREINVISIBLE)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDMOVESPECIAL)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDDEATH)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDINTERACT)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FLYING)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDAUTOATTACK)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDPICK)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDPLAYERCONTROL)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_CANTURNWHILEFORBIDMOVE)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FREEZE)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_IGNOREPUSH)
LUA_EXPORT_NDBENUM_VALUE(NDb::EUnitFlag, NDb::UNITFLAG_FORBIDINVISIBILITY)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LoadLuaScript( const string & scriptName, bool isReconnecting )
{
  PFScript * pScript = GetLuaScript();
  NI_VERIFY( pScript, "Failed to get lua script machine!", return false; );
  NI_VERIFY( !pScript->IsLoaded(), "Script already loaded!", return false; );

  pScript->AddFunctionsToRegList(scriptFunctionsList);
  pScript->RegisterGlobals();
  pScript->DoFile( scriptName );
  pScript->SetLoaded(true);

  CALL_LUA_FUNCTION_ARG3(pScript, "Init", false, isReconnecting, 
                          pScript->GetAIContainer()->GetWorld()->GetStepLength(),
                          pScript->GetAIContainer()->GetWorld()->GetStepLengthInSeconds());
  CALL_LUA_FUNCTION_ARG3(pScript, "InitStates", false, isReconnecting, 
                          pScript->GetAIContainer()->GetWorld()->GetStepLength(),
                          pScript->GetAIContainer()->GetWorld()->GetStepLengthInSeconds());

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LoadLuaScript( const char* name, const vector<wstring>& params)
{
  if ( params.size() != 1 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "Usage: " << name << " <filename>" << endl;
    return true;
  }

  return LoadLuaScript(NStr::ToMBCS(params[0]), false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool CallLuaFunction( const char* name, const vector<wstring>& params )
{
  if ( params.size() < 1 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << "Usage: " << name << "<function name> [arguments]" << endl;
    return true;
  }

  PFScript * pScript = GetLuaScript();
  NI_VERIFY( pScript, "Failed to get lua script machine!", return true; );
  NI_VERIFY( pScript->IsLoaded(), "Script isn't loaded!", return true; );

  CALL_LUA_FUNCTION_ARGS_WS( pScript, true, params );

  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::RegisterObject(PF_Core::WorldObjectBase* pObject, nstl::string scriptName, nstl::string scriptGroupName )
{
  if (!scriptName.empty())
  {
    objectIdToName[pObject->GetObjectId()] = scriptName;

    if (PFBaseCreep * pCreep = dynamic_cast<PFBaseCreep *>(pObject))
    {
      NI_VERIFY(creeps.find(scriptName) == creeps.end(), 
        NStr::StrFmt("Creep with script name \"%s\" already registered!", scriptName.c_str()), return; );

      //DevTrace("[Lua] Register creep: %s", scriptName.c_str());
      creeps[scriptName]  = pCreep;
    }
    else if (PFBaseUnit * pUnit = dynamic_cast<PFBaseUnit *>(pObject))
    {
      NI_VERIFY(units.find(scriptName) == units.end(), 
        NStr::StrFmt("Unit with script name \"%s\" already registered!", scriptName.c_str()), return; );

      //DevTrace("[Lua] Register unit: %s", scriptName.c_str());
      units[scriptName]  = pUnit;
    }
    else
    {
      NI_VERIFY(objects.find(scriptName) == objects.end(), 
        NStr::StrFmt("Object with script name \"%s\" already registered!", scriptName.c_str()), return; );

      //DevTrace("[Lua] Register object: %s", scriptName.c_str());
      objects[scriptName]  = pObject;
    }
  }

  if (!scriptGroupName.empty())
  {
    //DevTrace("[Lua] Register group: %s", scriptGroupName.c_str());
    objectGroups[scriptGroupName].push_back( pObject );
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::LoadScript( const string & scriptName, const vector<NDb::ResourceDesc> & res, bool isReconnecting )
{
  for(int i = 0; i < res.size(); i++)
  {
    if(!res[i].key.empty())
      resources[res[i].key] = res[i].resource->GetDBID().GetFileName();
  }

  return LoadLuaScript(scriptName, isReconnecting);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const NDb::ScriptArea* PFAIContainer::GetScriptArea( const char* name )
{
  const NDb::ScriptArea* pSA = 0;
  for( TScriptAreas::const_iterator it = scriptAreas.begin(), itEnd = scriptAreas.end(); it != itEnd; ++it )
  {
    if ( it->name == name )
    {
      NI_VERIFY( pSA == 0, NI_STRFMT( "Different script areas with same name \"%s\" found. Position is (%.0f, %.0f).", name, it->position.x, it->position.y ), return pSA );
      pSA = it;
    }
  }
  return pSA;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::GetScriptAreasByName( const string& name, vector<const NDb::ScriptArea*>& _scriptAreas )
{
  _scriptAreas.clear();

  for( TScriptAreas::const_iterator it = scriptAreas.begin(), itEnd = scriptAreas.end(); it != itEnd; ++it )
  {
    if ( it->name == name && it)
      _scriptAreas.push_back(it);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
PFAIContainer::TObjectGroup * PFAIContainer::FindGroup( const char * group ) 
{
  TObjectGroups::iterator it = objectGroups.find(group);
  return (it != objectGroups.end())?(&it->second):(0);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool PFAIContainer::FindDeadObjectName(const char * objectName) const
{
  return (deadObjectNames.find( objectName ) != deadObjectNames.end());
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* PFAIContainer::FindObjectGroupName( const PF_Core::WorldObjectBase* object ) const
{
  for( TObjectGroups::const_iterator it = objectGroups.begin(); it != objectGroups.end(); ++it )
  {
    for( TObjectGroup::const_iterator itList = it->second.begin(); itList != it->second.end(); ++itList )
    {
      if (*itList == object)
        return it->first.c_str();
    }
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::GetCreepNames( const nstl::hash_set<int>& objectIds, vector<const char*>* pObjectNames )
{
  for ( TCreeps::const_iterator it = creeps.begin(); it != creeps.end(); ++it )
  {
    PFBaseCreep* object = it->second.GetPtr();

    if ( objectIds.find( object->GetObjectId() ) != objectIds.end() )
      pObjectNames->push_back( it->first.c_str() );
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char* PFAIContainer::GetFileNameByKey(const char* key)
{
  NI_VERIFY( key, "key cannot be null", return 0 );  

  ScriptResources::iterator it = resources.find( key );

  if ( it == resources.end() )
    return key;
  else 
    return it->second.c_str();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFAIContainer::OnReconnect()
{
  NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance();
  if ( advScreen )
  {
    NScene::IScene* pScene = advScreen->GetScene();
    if ( pScene )
    {
      for ( TScriptEffects::iterator it = scriptEffects.begin(); it != scriptEffects.end(); ++it )
        it->second.Create( pScene );
    }
  }
  BuildIdNameMap();

  CALL_LUA_FUNCTION(GetLuaScript(), "Reconnect", false);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class PFScriptEventListener : public PFBaseUnitEventListener, public PFWorldObjectBase
{
  WORLD_OBJECT_METHODS( 0xE795F440, PFScriptEventListener );
public:
  PFScriptEventListener( CPtr<PFAIContainer> pAIContainer_, const char* name_, NDb::EBaseUnitEvent eventType_, const char* callbackFunctionName_ )
    : PFWorldObjectBase( pAIContainer_->GetWorld(), 0 ), pAIContainer(pAIContainer_), name(name_), eventType(eventType_), callbackFunctionName(callbackFunctionName_) {}

  virtual unsigned int OnEvent( const PFBaseUnitEvent *pEvent )
  {
    if ( pEvent->GetType() != eventType )
      return 0;

    if ( IsValid( pAIContainer ) )
    {
      pAIContainer->InvokeEventCallback( name, callbackFunctionName, pEvent );
    }

    return 0;
  }
  NDb::EBaseUnitEvent GetEventType() const { return eventType; }
private:
  PFScriptEventListener() {}

  ZDATA_(PFWorldObjectBase)
  ZNOPARENT(PFBaseUnitEventListener)
  NDb::EBaseUnitEvent eventType;
  string callbackFunctionName;
  string name;
  CPtr<PFAIContainer> pAIContainer;
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFWorldObjectBase*)this); f.Add(2,&eventType); f.Add(3,&callbackFunctionName); f.Add(4,&name); f.Add(5,&pAIContainer); return 0; }
};
struct ScriptEventListenerFinder
{
  ScriptEventListenerFinder( NDb::EBaseUnitEvent eventType )
    :eventType(eventType) {}
  NDb::EBaseUnitEvent eventType;

  bool operator() (PFBaseUnitEventListener* listener)
  {
    if ( PFScriptEventListener* l = dynamic_cast<PFScriptEventListener*>(listener) )
      return eventType == l->GetEventType();
    return false;
  }
};


void PFAIContainer::RegisterEventScriptHandler( const char* name, NDb::EBaseUnitEvent eventType, const char* callbackFunctionName )
{
  PFBaseUnit* pUnit = FindUnit( name );
  NI_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", name ), return );

  PFScriptEventListener* pListener = new PFScriptEventListener( this, name, eventType, callbackFunctionName );
  pUnit->AddEventListener( pListener );
}
void PFAIContainer::UnregisterEventScriptHandler( const char* name, NDb::EBaseUnitEvent eventType )
{
  PFBaseUnit* pUnit = FindUnit( name );
  NI_VERIFY( pUnit, NStr::StrFmt( "Unit \"%s\" not found!", name ), return );

  ScriptEventListenerFinder pred( eventType );
  pUnit->RemoveEventListenerIf( pred );

}
void PFAIContainer::InvokeEventCallback( const string& name, const string& callbackFunctionName, const PFBaseUnitEvent *pEvent )
{
  lua_State * L = GetLuaScript()->GetState();
  lua_getglobal(L, callbackFunctionName.c_str());
  if (lua_isfunction(L, -1))
  {
    int nargs = 1;
    luaValueSetter::Set( L, name );
    nargs += pEvent->PushArgsForScript( L );
    lua_pcall(L, nargs, 0, 0);
  }
  else
  {
    lua_remove(L, -1);
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void PFScript::Step()
{
  if (IsLoaded())
  {
    if (NGameX::AdventureScreen* advScreen = NGameX::AdventureScreen::Instance())
    {
      if (PFWorld* world = advScreen->GetWorld())
      {
        int step = world->GetStepNumber();
        CALL_LUA_FUNCTION_ARG1(this, "Step", false, step);
        CALL_LUA_FUNCTION_ARG1(this, "StepStates", false, step);
      }
    }
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int write_func(lua_State *, const void * p, size_t data, void * ud)
{
  MemoryStream * ms = static_cast<MemoryStream *>(ud);

  ms->Write( p, data );

  return data;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
const char * read_func(lua_State *, void * ud, size_t * sz)
{
  MemoryStream * ms = static_cast<MemoryStream *>(ud);

  *sz = ms->GetSize();
  return ms->GetBuffer();
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void LuaPersist(lua_State *L, void* ud)
{
  pluto_persist(L, &write_func, ud);
}
void LuaUnpersist(lua_State *L, void* ud)
{
  pluto_unpersist(L, &read_func, ud);
}
int PFScript::operator&( IBinSaver &f )
{
  if (f.IsReading())
  {
    int nSize;
    f.Add(1, &nSize);
    MemoryStream scriptData( nSize );
    f.AddRawData( 2, scriptData.GetBuffer(), nSize );

    // Setup exclusions table and unpersist data to rootobj
    lua_State* L = GetState();
    lua_settop(L, 0);               // Clear stack
    lua_newtable(L);                // Stack: table
    lua_pushinteger(L, 1);          // Stack: table, 1
    lua_getglobal(L, "coroutine");  // Stack: table, 1, coroutine
    lua_getfield(L, -1, "yield");   // Stack: table, 1, coroutine, yield
    lua_remove(L, -2);              // Stack: table, 1, yield
    lua_settable(L, -3);            // table[1] = yield

    int status = luaD_pcall(L,&LuaUnpersist, &scriptData, savestack(L, L->top), 0);
    NI_ASSERT( status == 0, NStr::StrFmt( "Pluto error: %s", lua_tostring( L, -1 ) ) );

    lua_setglobal(L, "rootobj");    // Set unpersisted data to rootobj
  }
  else if (f.IsChecksum())
  {
    unsigned long scriptCrc = GetCrc();
    f.Add(1, &scriptCrc);
    f.Add(2, &isLoaded);
  }
  else
  {
    MemoryStream scriptData(64*1024);

    // Setup exclusions table and persist data from rootobj
    lua_State* L = GetState();
    lua_settop(L, 0);               // Clear stack
    lua_newtable(L);                // Stack: table
    lua_getglobal(L, "coroutine");  // Stack: table, coroutine
    lua_getfield(L, -1, "yield");   // Stack: table, coroutine, yield
    lua_remove(L, -2);              // Stack: table, yield
    lua_pushinteger(L, 1);          // Stack: table, yield, 1
    lua_settable(L, -3);            // table[yield] = 1
    lua_getglobal(L, "rootobj");    // Set rootobj as second parameter


    int status = luaD_pcall(L,&LuaPersist, &scriptData, savestack(L, L->top), 0);
    NI_ASSERT( status == 0, NStr::StrFmt( "Pluto error: %s", lua_tostring( L, -1 ) ) );

    int nSize = scriptData.GetPosition();
    f.Add(1, &nSize);
    f.AddRawData( 2, scriptData.GetBuffer(), nSize ); 
  }

  return 0; 
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int PFScriptSerializer::operator&( IBinSaver &f )
{
  NI_PROFILE_FUNCTION

  if (g_enableLuaSerialization && IsValid( script ) && script->IsLoaded())
  {
    script->operator &(f);
  }

  return 0;
}

} // namespace NWorld

//////////////////////////////////////////////////////////////////////////
REGISTER_DEV_CMD( load_lua_script, NWorld::LoadLuaScript );
REGISTER_DEV_CMD( call_lua_function, NWorld::CallLuaFunction );

NI_DEFINE_REFCOUNT( NWorld::PFScript );
REGISTER_WORLD_OBJECT_NM(PFScriptEventListener, NWorld)
