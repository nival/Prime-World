//!Component("System/Pointers/Pointers")
//!Component("System/Pointers/Tests/TestClasses")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include <string>

#include "System/Pointers/Pointers.h"

#include "TestClassB.h"
#include "TestInterface.h"
#include "TestFaceMt.h"


class Myclass : public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_1( Myclass, BaseObjectST )

public:
  static int s_instancesCount;

  Myclass( const char * _name ) : name( _name ) { ++s_instancesCount; }
  ~Myclass() { --s_instancesCount; };

  const std::string & Name() const { return name; }
  void SetName( const char * _name ) { name = _name; }

private:
  std::string name;
};

int Myclass::s_instancesCount = 0;




class TestClassA;
class ITestFaceMT;

class Test_Pointeras : public CxxTest::TestSuite
{
public:
  virtual void setUp()
  {
  }



  virtual void tearDown()
  {
  }



  void test_BasicFunctionality()
  {
    TS_ASSERT_EQUALS( Myclass::s_instancesCount, 0 );
    Strong<Myclass> my = new Myclass( "kuku" );
    TS_ASSERT_EQUALS( Myclass::s_instancesCount, 1 );

    //Weak<Myclass> w = my;
    Weak<Myclass> w( my );

    {
      Myclass * c = w;
      TS_ASSERT( c );
      TS_ASSERT_EQUALS( c->Name(), "kuku" );

      //Strong<Myclass> my2 = w;
      Strong<Myclass> my2( w );
      TS_ASSERT( my2 );
      my2->SetName( "mumu" );

      //Weak<Myclass> w2 = my2;
      Weak<Myclass> w2( my2 );
      TS_ASSERT( w2 );
      TS_ASSERT_EQUALS( w2->Name(), "mumu" );
    }

    TS_ASSERT( w );
    TS_ASSERT_EQUALS( Myclass::s_instancesCount, 1 );
    my = 0;
    TS_ASSERT_EQUALS( Myclass::s_instancesCount, 0 );
    TS_ASSERT( !w );
  }

  void test_templateClass()
  {
#ifndef NI_POINTERS_TMP_USE_DYNCAST
    TS_ASSERT_EQUALS( TemplateTestClass<int>::StaticRuntimeClassId(), TestClassB::GetIntTemplateTestClassId() );
#endif //NI_POINTERS_TMP_USE_DYNCAST
    TS_ASSERT_DIFFERS( TemplateTestClass<int>::StaticRuntimeClassId(), TemplateTestClass<float>::StaticRuntimeClassId() );

    Strong<TemplateTestClass<int> > intTempl = new TemplateTestClass<int>( 33 );
    TS_ASSERT( intTempl );

    //Weak<TemplateTestClass<int> > intTemplWeak = intTempl;
    Weak<TemplateTestClass<int> > intTemplWeak( intTempl );
    TS_ASSERT( intTemplWeak.Valid() );

    Strong<TemplateTestClass<float> > floatTempl = new TemplateTestClass<float>( intTempl->Value() );
    TS_ASSERT( floatTempl );
    TS_ASSERT_EQUALS( floatTempl->Value(), 33.0f );
    TS_ASSERT_EQUALS( string( intTempl->ClassName() ), string( floatTempl->ClassName() ) );

    TS_ASSERT_EQUALS( intTemplWeak->Value(), 33.0f );

    StrongMT<TemplateTestClassMT<float> > mtStrognTempl = new TemplateTestClassMT<float>( 3.14f );
    //WeakMT<TemplateTestClassMT<float> > mtWeakTempl = mtStrognTempl;
    WeakMT<TemplateTestClassMT<float> > mtWeakTempl( mtStrognTempl );
    TS_ASSERT_EQUALS( mtWeakTempl.Lock()->Value(), 3.14f );
  }

  void test_interfacesAndForwarded()
  {
    Strong<TestClassB> b = new TestClassB( 1980 );
    TS_ASSERT( b );

    Strong<ITestInterface> ti = ITestInterface::Produce( b, "clean" );
    TS_ASSERT( ti );
    TS_ASSERT_EQUALS( ti->Name(), "clean" );

    b->SetTestIF( ti );

    {
      Weak<ITestInterface> wti( ti );
      TS_ASSERT( wti );
      TS_ASSERT_EQUALS( strcmp( wti->ClassName(), "TestClassA" ), 0 );

#ifndef NI_POINTERS_TMP_USE_DYNCAST
      //Test 'dynamic cast'
      TestClassA * upcastedA = ni_detail::GetDerivedObjectImpl2<TestClassA>( wti.Get(), (TestClassA *)0, (TestClassA *)0 );
      TS_ASSERT( upcastedA );

      //Test completely forwarded pointers
      TS_ASSERT( b->TestCompletelyForwardedPointer( upcastedA ) );
#endif // NI_POINTERS_TMP_USE_DYNCAST

      wti->SetName( "dirty" );
      TS_ASSERT_EQUALS( ti->Name(), "dirty" );
    }

    b->UpdateTestIFName();
    TS_ASSERT_EQUALS( ti->Name(), "1980" );
  }


  void test_MT()
  {
    StrongMT<ITestFaceMT> strong = ProduceTestClassMT( 8 );
    TS_ASSERT( strong );

    TS_ASSERT_EQUALS( strong->GetFooAmout(), 8 );

    WeakMT<ITestFaceMT> weak( strong );

    {
      StrongMT<ITestFaceMT> locked = weak.Lock();
      TS_ASSERT( locked );
      TS_ASSERT_EQUALS( locked->GetFooAmout(), 8 );
      locked->SetFooAmount( -10 );
    }

    TS_ASSERT_EQUALS( strong->GetFooAmout(), -10 );

    strong = 0;

    StrongMT<ITestFaceMT> locked = weak.Lock();
    TS_ASSERT( !locked );
  }
};
