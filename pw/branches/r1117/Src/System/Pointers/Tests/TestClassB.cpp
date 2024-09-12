#include "stdafx.h"
#include "TestClassB.h"
#include "TestInterface.h"
#include "System/Pointers/Weak.h"
#include "System/Pointers/BaseInterface.h"


NI_DEFINE_REFCOUNT( TestClassB );


class TestClassA;

TestClassB::~TestClassB()
{
}



void TestClassB::UpdateTestIFName()
{
  if ( a )
  {
    char buf[64];
    //sprintf_s( buf, "%d", id );
    NStr::Printf( buf, sizeof( buf ), "%d", id );
    a->SetName( buf );
  }
}



bool TestClassB::TestCompletelyForwardedPointer( TestClassA * pa )
{
  //TODO: We temporarily use dynamic_cast<> in weak pointers
  //And dynamic_cast<> cannot work with forward-declared pointers
#ifdef NI_POINTERS_DBG_USE_DYNCAST
  return pa ? true : false;
#else //NI_POINTERS_DBG_USE_DYNCAST
  Weak<TestClassA> w( pa );
  return w;
#endif //NI_POINTERS_DBG_USE_DYNCAST
}



ni_detail::ClassTypeId TestClassB::GetIntTemplateTestClassId()
{
  return TemplateTestClass<int>::StaticRuntimeClassId();
}
