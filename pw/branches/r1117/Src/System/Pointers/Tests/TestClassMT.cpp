#include "stdafx.h"
#include "TestClassMT.h"

NI_DEFINE_REFCOUNT( ITestFaceMT );

ITestFaceMT * ProduceTestClassMT( int fooAmount )
{
  return new TestClassMT( fooAmount );
}

