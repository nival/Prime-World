//!Component('Scripts/all')
//!Component('Scripts/TestScripts')
//!Component('System/Ptr')
//!Component('System/SystemLog')
//!Component('System/FileSystem')
//!Component('System/Texts')
//!Component('System/Random')

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include <iostream>
#include "lua.hpp"
#include "Script.h"
#include "LuaBase.h"
#include "LuaSubclass.h"

#include "System/RandomGen.h"
#include "System/FileSystem/WinFileSystem.h"
#include "System/FileSystem/FileUtils.h"

#pragma push_macro("LUA_IMPL_ERROR_NOTIFY")
#undef  LUA_IMPL_ERROR_NOTIFY
#define LUA_IMPL_ERROR_NOTIFY(NAME) \
  {std::cout << "Failed to call handler <" << NAME << ">" << endl; }

namespace
{
  NScript::Script TestScriptMachine;  
};

int LuaCLog( lua_State* pState )
{
  LUA_NATIVE
  for (int i = 1, count = lua_gettop(pState); i <= count; ++i)
  {
    if (i > 1) 
      std::cout << "\t";

    if( lua_isstring(pState,i) )
      std::cout << lua_tostring(pState, i);
    else 
    if( lua_isnil(pState, i) )
      std::cout << "nil";
    else 
    if( lua_isboolean(pState, i) )
      std::cout << (lua_toboolean(pState, i) ? "true" : "false");
    else
      std::cout << lua_typename(pState, lua_type(pState, i) ) << ":" << lua_topointer(pState, i);
  }
  std::cout << std::endl;
  return 0;
}

int LuaInclude(lua_State* pState)
{
  LUA_NATIVE
  if( LUA_TSTRING != lua_type( pState, -1 ) )
  {
    std::cout << "LUA Include: invalid parameter" << endl;
    return 0;
  }
  
  TestScriptMachine.DoFile( lua_tostring( pState, -1 ) );
  
  return 0;
}
  
class SimpleLuaSubclassed : public Lua::LuaSubclass, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( SimpleLuaSubclassed, BaseObjectST, Lua::LuaSubclass )

  int   someValue;
  float secondValue;
  Lua::LuaSubclass* pLinked;
public:
  SimpleLuaSubclassed() : someValue(0), secondValue(0.0f), pLinked(NULL) {}

  int  GetValue() const    { return someValue; }
  void SetValue(int value) { someValue = value; }

  void TestNativeFunction()
  {
  }

  Lua::LuaSubclass* GetLinked() const { return pLinked; }
  void SetLinked(Lua::LuaSubclass* pOther){ pLinked = pOther; }

  DECLARE_LUA_TYPEINFO(SimpleLuaSubclassed);
  DEFINE_LUA_PROPERTY(secondValue, float, secondValue);

  friend class  LuaTest;
};

BEGIN_LUA_TYPEINFO_NOBASE(SimpleLuaSubclassed)
  LUA_METHOD(TestNativeFunction)
  LUA_METHOD(GetLinked)
  LUA_METHOD(SetLinked)
  LUA_PROPERTY(secondValue)
  LUA_PROPERTY_EX(value, GetValue, SetValue)
END_LUA_TYPEINFO(SimpleLuaSubclassed)

class LuaImplementedClass : public Lua::LuaSubclass, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( LuaImplementedClass, BaseObjectST, Lua::LuaSubclass )

  int randomValue;
public:
  LuaImplementedClass()
    : randomValue(NRandom::Random(0, 100))
  {
  }

  int    LuaImplementedMethod()  { LUA_METHOD_IMPL_RV(int, LuaImplementedMethod) }
  string LuaImplementedMethod1(int arg) { LUA_METHOD_IMPL_RV_1(string, LuaImplementedMethod1, arg)  }  
  float  LuaImplementedMethod2(float arg1, float arg2) { LUA_METHOD_IMPL_RV_2(float, LuaImplementedMethod2, arg1, arg2) }  

  int    GetValue() const { return randomValue; }

  DECLARE_LUA_TYPEINFO(LuaImplementedClass);
  friend class  LuaTest;
};

BEGIN_LUA_TYPEINFO_NOBASE(LuaImplementedClass)
  LUA_METHOD(GetValue)
END_LUA_TYPEINFO(LuaImplementedClass)

class LuaComplexTypesTestClass : public Lua::LuaSubclass, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( LuaComplexTypesTestClass, BaseObjectST, Lua::LuaSubclass )

public:

  const CVec3         vec1;
  const CVec3         vec2;
  const CTRect<float> rect1;
  const CTRect<float> rect2;

  LuaComplexTypesTestClass() 
    : vec1(NRandom::Random(0, 100), NRandom::Random(0, 100), NRandom::Random(0, 100))
    , vec2(NRandom::Random(0, 100), NRandom::Random(0, 100), NRandom::Random(0, 100))
    , rect1(NRandom::Random(0, 50), NRandom::Random(0, 50), NRandom::Random(60, 100), NRandom::Random(60, 100))
    , rect2(NRandom::Random(0, 50), NRandom::Random(0, 50), NRandom::Random(60, 100), NRandom::Random(60, 100))
  {
  }

  void CheckVectorValue(CVec3 arg);
  void CheckPointValue(CTPoint<float> point);
  void CheckRectValue(CTRect<float> point);
  

  DECLARE_LUA_TYPEINFO(LuaComplexTypesTestClass);
  friend class  LuaTest;
};

void LuaComplexTypesTestClass::CheckVectorValue(CVec3 arg)
{
  TS_ASSERT_EQUALS(arg.x, vec1.x + vec2.x);
  TS_ASSERT_EQUALS(arg.y, vec1.y + vec2.y);
  TS_ASSERT_EQUALS(arg.z, vec1.z + vec2.z);
}

void LuaComplexTypesTestClass::CheckPointValue(CTPoint<float> arg)
{
  TS_ASSERT_EQUALS(arg.x, vec1.x * vec2.x);
  TS_ASSERT_EQUALS(arg.y, vec1.y * vec2.y);
}

void LuaComplexTypesTestClass::CheckRectValue(CTRect<float> arg)
{
  TS_ASSERT_EQUALS(arg.x1, min(rect1.x1, rect2.x1));
  TS_ASSERT_EQUALS(arg.y1, min(rect1.y1, rect2.y1));
  TS_ASSERT_EQUALS(arg.x2, max(rect1.x2, rect2.x2));
  TS_ASSERT_EQUALS(arg.y2, max(rect1.y2, rect2.y2));
}

BEGIN_LUA_TYPEINFO_NOBASE(LuaComplexTypesTestClass)
  LUA_METHOD(CheckVectorValue)
  LUA_METHOD(CheckPointValue)
  LUA_METHOD(CheckRectValue)
END_LUA_TYPEINFO(LuaComplexTypesTestClass)

class testLua : public CxxTest::TestSuite
{
public:
void setUpSuite()
{

  RootFileSystem::RegisterFileSystem( new WinFileSystem( "./", false ) );
  
  lua_pushcfunction( TestScriptMachine.GetState(), LuaCLog );
  lua_setglobal( TestScriptMachine.GetState(), "clog" );

  lua_pushcfunction( TestScriptMachine.GetState(), LuaInclude );
  lua_setglobal( TestScriptMachine.GetState(), "include" );

  TestScriptMachine.DoFile( "Scripts/inc.lua" );
  TestScriptMachine.DoFile( "Scripts/Test.lua" );
}

void testSubclassing()
{
  SimpleLuaSubclassed s;
  if(!s.Subclass(TestScriptMachine.GetState(), "TestLuaClass", &s))
  {
    TS_ASSERT(!"Subclassing failed!");
    return;
  }

  TS_ASSERT( s.CallHandler("Function0") );
  TS_ASSERT(s.CallHandler("Function1", 128) );
  TS_ASSERT(s.CallHandler("Function1", 256.0f) );
  TS_ASSERT(s.CallHandler("Function2", "somestring", false) );
  TS_ASSERT(s.CallHandler("CallAnotherFunction", "EnumerateMetatable") );

  int result = 0;
  if(s.CallMethod("SquareArgument", result, 2))
  {
    TS_ASSERT_EQUALS(4, result);
  }
  else
  {
    TS_ASSERT(!"Failed to call requested method!");
  }

  if(!s.CallHandler("CallAnotherFunction", "TestNativeFunction"))
  {
    TS_ASSERT(!"Failed to call special handler!");
  }

  if(!s.CallHandler("CallAnotherFunction", "TestProperties"))
  {
    TS_ASSERT(!"Failed to  test properties!");   
  }
}

void testObjectTransfer()
{
  SimpleLuaSubclassed obj1, obj2;
  if(!obj1.Subclass(TestScriptMachine.GetState(), "TestLuaClass", &obj1))
  {
    TS_ASSERT(!"Subclassing failed!");
    return;
  }

  if(!obj2.Subclass(TestScriptMachine.GetState(), "TestLuaClass", &obj2))
  {
    TS_ASSERT(!"Subclassing failed!");
    return;
  }

  obj1.SetValue(10);
  obj2.SetValue(20);

  obj1.SetLinked(&obj2);
  if(!obj1.CallHandler("TestObjectTransfer"))
  {
    TS_ASSERT(!"Object transfer test failed!");
    return;
  }

  obj2.SetLinked(&obj1);
  if(!obj2.CallHandler("TestObjectTransfer"))
  {
    TS_ASSERT(!"Object transfer test failed!");
    return;
  }
}

void testLuaImplMethod()
{
  LuaImplementedClass obj;
  if(!obj.Subclass(TestScriptMachine.GetState(), "LuaImplementedClass", &obj))
  {
    TS_ASSERT(!"Subclassing failed!");
    return;
  }

  TS_ASSERT_EQUALS(obj.GetValue(), obj.LuaImplementedMethod());
  TS_ASSERT_EQUALS(NStr::IntToStr(obj.GetValue()), obj.LuaImplementedMethod1(obj.GetValue()));

  int additionalValue = NRandom::Random(0, 100);
  TS_ASSERT_EQUALS(additionalValue * obj.GetValue(), obj.LuaImplementedMethod2(obj.GetValue(), additionalValue));
}

void testComplexTypes()
{
  LuaComplexTypesTestClass obj;
  if(!obj.Subclass(TestScriptMachine.GetState(), "LuaComplexTypesTestClass", &obj))
  {
    TS_ASSERT(!"Subclassing failed!");
    return;
  }
  
  if(!obj.CallHandler("TestVector3", obj.vec1, obj.vec2))
  {
    TS_ASSERT(!"TestVector3  failed!");
    return;
  }

  CTPoint<float> pt1(obj.vec1.x, obj.vec1.y), pt2(obj.vec2.x, obj.vec2.y);
  if(!obj.CallHandler("TestPoint", pt1, pt2))
  {
    TS_ASSERT(!"TestPoint  failed!");
    return;
  }
  
  if(!obj.CallHandler("TestRect", obj.rect1, obj.rect2))
  {
    TS_ASSERT(!"TestRect  failed!");
    return;
  }
}
};
//REGISTER_SAVELOAD_CLASS( SimpleLuaSubclassed );
//REGISTER_SAVELOAD_CLASS( LuaImplementedClass );
//REGISTER_SAVELOAD_CLASS( LuaComplexTypesTestClass );

#pragma pop_macro("LUA_IMPL_ERROR_NOTIFY")