//!Component("System/Threading")
//!Component("System/Timer")
//!Component("System/Threading")
//!Component("System/DebugVar")
//!Component("Server/DebugVarUpdate/Request")

#include "stdafx.h"
#include "DebugVarRequester.h"
#include "System/DebugVar.h"

#include "cxxtest/TestSuite.h"

using namespace NDebug; 

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Test_DebugVarRequester: public CxxTest::TestSuite, DebugVarRequester
{

void test_Case1()
{
  wstring value;

  ReqVarOnce( L"var1" ); // эту спросим 1 раз
  ReqVar( L"var2", 0.1 ); // эту будем спрашивать 10 раз в секунду

  ReqVar( L"var3", 0.2 ); // эту будем спрашивать 5 раз в секунду
  RemoveVar( L"var3" ); // нет, лучше не будем

  NI_ASSERT( vars.size() == 2, "bad vars count" ); 
  NI_ASSERT( false == GetValue( L"var1", value ), "var1 returned w/o request" ); // lastReceived не инициализировано
    
  TIMESTAMP t1 = NHPTimer::GetScalarTime();

  // бегаем пару секунд 
  while( NHPTimer::GetScalarTime() - t1 < 0.5 )
  {
    UpdateStep();
    Sleep( 50 );
  }

  TIMESTAMP t2 = NHPTimer::GetScalarTime();

  NI_ASSERT( vars.size() == 2, "bad vars size" ); 
  
  TClientVars::iterator it = vars.find( L"var1" );
  NI_ASSERT( it != vars.end(), "no var1" );
  NI_ASSERT( it->second.lastRequested > 0, "var1 not requested" ); // запрос вызывался  
  NI_ASSERT( it->second.lastRequested - t1 < 0.2, "bad var1 request time" ); // вызывался достаточно давно, т.е. вероятно однократно

  it = vars.find( L"var2" );
  NI_ASSERT( it != vars.end(), "no var2" );
  NI_ASSERT( it->second.lastRequested > 0, "var2 not requested" ); // запрос вызывался  
  NI_ASSERT( t2 - it->second.lastRequested < 0.2, "bad var2 request time" ); // вызывался недавно, т.е. периодически

  CallbackValueReceive( L"var1|value1" );
  bool ok = GetValue( L"var1", value );
  NI_ASSERT( ok, "dummy callback var1 value not set" );
  NI_ASSERT( value == L"value1", "dummy callback var1 value not match" );
}

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Test_DebugVarRequesterMap: public CxxTest::TestSuite, DebugVarRequesterMap
{
  void test_Case1();
};



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static int g_ForEach_CallCount = 0;
static void OnVarChanged(TUserId& userId, wstring& name, wstring& value, void*)
{
  LOG_D(0) << "changed user " << userId << ", var " << name << ", value " << value;
  g_ForEach_CallCount++;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Test_DebugVarRequesterMap::test_Case1()
{// тест всего Map
  AddScenario( L"var1" ).AddScenario( L"var2", 1.0 );

  DebugVarRequester *req1 = AddRequester( 1, NULL );
  DebugVarRequester *req2 = AddRequester( 2, NULL );

  DebugVarRequester *req3 = AddRequester( 3, NULL );
  req3->ReqVar( L"UNKNOWN", 20 );

  RemoveRequester( 3 );

  NI_ASSERT( requesters.size() == 2, "bad vars size" ); 

  UpdateStep();

  NI_ASSERT( GetNextUpdated() == NULL, "GetNextUpdated returns with no updates" ); 

  // теперь якобы вернем что-нибудь
  req2->CallbackValueReceive( L"var1|some_val" );

  DebugVarRequester *updated = GetNextUpdated();
  NI_ASSERT( updated, "GetNextUpdated doesnt return after forced receive" );  
  
  if ( updated )
  {
    wstring name, value;
    bool gotVar = updated->GetNextUpdatedVar( name, value ); 
    NI_ASSERT( gotVar, "GetNextUpdatedVar doesnt return after forced receive" );  

    gotVar = updated->GetNextUpdatedVar( name, value ); 
    NI_ASSERT( !gotVar, "GetNextUpdatedVar returns twice after single forced receive" );  
  }

  updated->SetChecked();
  NI_ASSERT( GetNextUpdated() == NULL, "GetNextUpdated returns after SetChecked" ); 

  // якобы вернем 2 переменных
  req1->CallbackValueReceive( L"var2|some_val2" );
  req2->CallbackValueReceive( L"var1|some_val1" );
  
  // и натравим ForEach, с подсчетом кол-ва изменившихся
  g_ForEach_CallCount = 0;
  int retCount = ForEachUpdatedVar( &OnVarChanged, NULL );

  NI_ASSERT( retCount == 2, "bad foreach return count" );
  NI_ASSERT( g_ForEach_CallCount == 2, "bad callback use count" );
}

//void TEST_DebugVarRequester()
//{
//  Test_DebugVarRequester obj;
//  obj.TEST_Case1();
//
//  Test_DebugVarRequesterMap reqMap;
//  reqMap.TEST_Case1();
//}



