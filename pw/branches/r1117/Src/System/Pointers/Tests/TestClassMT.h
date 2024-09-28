#ifndef TESTCLASSMT_H_INCLUDED
#define TESTCLASSMT_H_INCLUDED

#include "TestFaceMt.h"

class TestClassMT : public BaseObjectMT, public ITestFaceMT
{
  NI_DECLARE_REFCOUNT_CLASS( TestClassMT )
    NI_DECLARE_BASE( BaseObjectMT )
    NI_DECLARE_BASE( ITestFaceMT )
  NI_DECLARE_END

public:
  TestClassMT( int _fooAmount ) : fooAmount( _fooAmount ) {}

  virtual int GetFooAmout() const
  {
    return fooAmount;
  }

  virtual void SetFooAmount( int amount )
  {
    fooAmount = amount;
  }

private:
  int fooAmount;
};

#endif //TESTCLASSMT_H_INCLUDED
