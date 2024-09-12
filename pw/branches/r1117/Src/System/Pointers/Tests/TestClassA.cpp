#include "stdafx.h"
#include "TestClassA.h"
#include "System/Pointers/Strong.h"

NI_DEFINE_REFCOUNT( TestClassA );
NI_DEFINE_REFCOUNT( ITestInterface );

TestClassA::~TestClassA()
{
}



ITestInterface * ITestInterface::Produce( TestClassB * _owner, const char * name )
{
  return new TestClassA( _owner, name );
}
