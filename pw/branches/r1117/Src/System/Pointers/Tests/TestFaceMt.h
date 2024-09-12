#ifndef TESTFACEMT_H_INCLUDED
#define TESTFACEMT_H_INCLUDED

#include "System/Pointers/Pointers.h"

class ITestFaceMT : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS( ITestFaceMT )
    NI_DECLARE_BASE( IBaseInterfaceMT )
  NI_DECLARE_END

public:
  virtual int GetFooAmout() const = 0;
  virtual void SetFooAmount( int amount ) = 0;
};

ITestFaceMT * ProduceTestClassMT( int fooAmount );



template<typename T>
class TemplateTestClassMT : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS( TemplateTestClassMT )
    NI_DECLARE_BASE( BaseObjectMT )
  NI_DECLARE_END

public:
  TemplateTestClassMT( const T & _val ) : val ( _val ) {}
  const T & Value() const { return val; }
  
private:
  T val;
};

#endif //TESTFACEMT_H_INCLUDED
