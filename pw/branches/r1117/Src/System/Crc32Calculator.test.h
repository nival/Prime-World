//!Component("System/Crc32Calculator")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"

#include "Crc32Calculator.h"

class SomeTestObject : public CObjectBase
{
  OBJECT_BASIC_METHODS( SomeTestObject );

  void OnSerialize( IBinSaver &f ) { ++count; }
public:
  SomeTestObject() : count( 0 ), i( 0 ) { }


  void SetInnerValue( int i ) { this->i = i; }
  void SetInnerSelf( SomeTestObject* self ) { this->self = self; }
  int GetSerializeCount() const { return count; }

private:
   
  int count;
  ZDATA
  int i;
  CPtr<SomeTestObject> self;
  ZONSERIALIZE
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&i); f.Add(3,&self); OnSerialize( f ); return 0; }
};

class ContextCommandTest2 : public CxxTest::TestSuite 
{
public:
  void TestSimpleCalculatedValue()
  {
    Crc32Calculator<NullStatsCollector> calc;

    int i = 10;
    calc.Calculate( i, true );
    const unsigned long crc = calc.GetCrc();
    TS_ASSERT_DIFFERS( 0, calc.GetCrc() );
    
    calc.Calculate( i, true );
    TS_ASSERT_EQUALS( crc, calc.GetCrc() );
  }

  void TestObjectCalculatedValue()
  {
    Crc32Calculator<NullStatsCollector> calc;
    
    int i = 10;
    calc.Calculate( i, true );
    const unsigned long crc = calc.EndCalculate();

    SomeTestObject obj;
    obj.SetInnerValue( 11 );

    calc.Calculate( &obj, true );
    calc.EndCalculate();
    TS_ASSERT_DIFFERS( 0, calc.GetCrc() );
    TS_ASSERT_DIFFERS( crc, calc.GetCrc() );
  }

  void TestObjectCalculatedValue2()
  {
    Crc32Calculator<NullStatsCollector> calc;
    
    int i = 10;
    calc.Calculate( i, true );
    const unsigned long crc = calc.EndCalculate();

    SomeTestObject obj;
    obj.SetInnerValue( 10 );

    calc.Calculate( &obj, true );
    calc.EndCalculate();
    TS_ASSERT_DIFFERS( 0, calc.GetCrc() );
    TS_ASSERT_EQUALS( crc, calc.GetCrc() );
  }

  void TestObjectSingleSerialization()
  {
    CObj<SomeTestObject> a = new SomeTestObject();
    CObj<SomeTestObject> b = new SomeTestObject();
    CObj<SomeTestObject> c = new SomeTestObject();
    a->SetInnerSelf( c );
    b->SetInnerSelf( c );
    
    Crc32Calculator<NullStatsCollector> calc;
    calc.BeginCalculate( true );
    calc.Calculate( a, false );
    calc.Calculate( b, false );
    calc.EndCalculate();

    TS_ASSERT_EQUALS( 1, a->GetSerializeCount() );
    TS_ASSERT_EQUALS( 1, b->GetSerializeCount() );
    TS_ASSERT_EQUALS( 1, c->GetSerializeCount() );
  }
};
