#ifndef TESTINTERFACE_H_INCLUDED
#define TESTINTERFACE_H_INCLUDED

//#include <string>

class TestClassB;

_interface ITestInterface : public IBaseInterfaceST
{
public:
  NI_DECLARE_CLASS_1( ITestInterface, IBaseInterfaceST )

  virtual const string & Name() const = 0;
  virtual void SetName( const char * _name ) = 0;

  static ITestInterface * Produce( TestClassB * _owner, const char * name );
};

#endif //TESTINTERFACE_H_INCLUDED
