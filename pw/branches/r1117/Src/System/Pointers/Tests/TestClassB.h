#ifndef TESTCLASSB_H_INCLUDED
#define TESTCLASSB_H_INCLUDED

#include "System/Pointers/BaseObjectST.h"
#include "System/Pointers/Strong.h"

_interface ITestInterface;
class TestClassA;

class TestClassB : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( TestClassB, BaseObjectST )

public:
  TestClassB( int _id ) : id( _id ) {}
  ~TestClassB();

  void SetTestIF( ITestInterface * _a ) { a = _a; }

  void UpdateTestIFName();

  bool TestCompletelyForwardedPointer( TestClassA * a );

  static ni_detail::ClassTypeId GetIntTemplateTestClassId();

private:
  int id;
  Strong<ITestInterface> a;
};



template<typename T>
class TemplateTestClass : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS( TemplateTestClass )
    NI_DECLARE_BASE( BaseObjectST )
  NI_DECLARE_END

public:
  TemplateTestClass( const T & _val ) : val ( _val ) {}
  const T & Value() const { return val; }
  
private:
  T val;
};

#endif //TESTCLASSB_H_INCLUDED
