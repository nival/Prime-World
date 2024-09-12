///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#pragma once
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct lua_State;
typedef int (*lua_CFunction) (lua_State *L);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Global functions description
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define REGISTER_LUA_GLOBAL_SFUNCTION( fname )																																								\
static int _##fname##_cb( lua_State *L )																																											\
{																																																															\
	return LuaCallBack( #fname, L, &##fname##);																																									\
}																																																															\
static struct SRegisterScriptFunction_##fname																																									\
{																																																															\
	SRegisterScriptFunction_##fname##()																																													\
	{																																																														\
		NScript::AddSFunctionToGlobals( #fname, &_##fname##_cb );																																	\
	}																																																														\
} registerScriptFunction_##fname##;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define REGISTER_LUA_SFUNCTION( ScriptEngine, fname )																																					\
static int _##fname##_cb( lua_State *L )																																											\
{																																																															\
	return LuaCallBack( #fname, L, &##fname##);																																									\
}																																																															\
static struct SRegisterScriptFunction_##fname																																									\
{																																																															\
	SRegisterScriptFunction_##fname##()																																													\
	{																																																														\
		ScriptEngine.AddFunctionToRegList( #fname, &_##fname##_cb );																															\
	}																																																														\
} registerScriptFunction_##fname##;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Регистрация глобальной скриптовой функции без биндинга, вызывается функция такого типа:
// int CallbackFunction(lua_State * L)
#define REGISTER_LUA_SFUNCTION_IMMEDIATE( ScriptEngine, fname )																																\
static struct SRegisterScriptFunction_##__LINE__##_##fname																																		\
{																																																															\
	SRegisterScriptFunction_##__LINE__##_##fname##()																																						\
	{																																																														\
		ScriptEngine.AddFunctionToRegList( #fname, &fname );																																			\
	}																																																														\
} registerScriptFunction_##__LINE__##_##fname##;
