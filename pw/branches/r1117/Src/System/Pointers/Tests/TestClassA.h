#ifndef TESTCLASSA_H_INCLUDED
#define TESTCLASSA_H_INCLUDED

#include "System/Pointers/BaseObjectST.h"
#include "TestInterface.h"


class TestClassA : public BaseObjectST, public ITestInterface
{
  NI_DECLARE_REFCOUNT_CLASS( TestClassA )
    NI_DECLARE_BASE( BaseObjectST )
    NI_DECLARE_BASE( ITestInterface )
  NI_DECLARE_END

public:
  TestClassA( TestClassB * _owner, const char * _name ) : name( _name ), owner( _owner ) {}
  ~TestClassA();

  virtual const string & Name() const { return name; }
  virtual void SetName( const char * _name ) { name = _name; }

private:
  string name;
  Weak<TestClassB> owner;
};

#endif //TESTCLASSA_H_INCLUDED
