//!Component("System/Savers")
//!Component("System/NSTL")
#include "stdafx.h"
#include "ChunklessSaver.h"
#include "BinChunkSerializer.h"
#include "Ring.h"
#include "cxxtest/TestSuite.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class SimplePointerHolder : public IPointerHolder, public CObjectBase
//{
//	OBJECT_METHODS( 0x1E4A8B41, SimplePointerHolder );
//	hash_map<int, CObjectBase*> objects;
//public:
//	int GetObjectID( CObjectBase *p ) { return (int)p; }
//	CObjectBase *GetObject( int nID ) 
//	{
//		hash_map<int, CObjectBase*>::const_iterator pos = objects.find( nID );
//		if ( pos == objects.end() )
//			return 0;
//		
//		return pos->second;
//	}
//	
//	void RegisterObject( CObjectBase *p ) { objects[(int)p] = p; }
//};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SaversTest : public CxxTest::TestSuite
{
public:
  //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class SerializeTestObject : public CObjectBase
  {
  public:
    SerializeTestObject() : field1( 0 ) {}

    ZDATA
    int field1;
    string field2;

    vector<int> vec1;

    CPtr<SerializeTestObject> pObject1;
    CObj<SerializeTestObject> pObject2;
  public:
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&field1); f.Add(3,&field2); f.Add(4,&vec1); f.Add(5,&pObject1); f.Add(6,&pObject2); return 0; }

    OBJECT_METHODS( 0x9A67EB80, SerializeTestObject )
  };
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  class RingTestObject1 : public CObjectBase
  {
  public:
    seDECLARE_COBJRING_CLASS(RingTestObject1, ring1, Ring );
    seDECLARE_COBJRING_CLASS(RingTestObject1, ring2, LORing );

    Ring::Part ring1;
    LORing::Part ring2;
    ZDATA
      int param;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&param); return 0; }

    RingTestObject1() : param( 0 ) {}
    RingTestObject1( int _param ) : param(_param) {}
    OBJECT_METHODS( 0x9A67A340, RingTestObject1 )
  };
  class RingTestObject2 : public CObjectBase
  {
  public:
    ZDATA
    RingTestObject1::Ring objRing;
    RingTestObject1::LORing loRing;
    CObj<RingTestObject2> obj2;

    hash_map<int, CObj<RingTestObject1> > objRegistry;
    ZEND int operator&( IBinSaver &f ) { f.Add(2,&objRing); f.Add(3,&loRing); f.Add(4,&obj2); f.Add(5,&objRegistry); return 0; }

    RingTestObject2(){}
    void Add( RingTestObject1* obj ) { objRegistry[obj->param] = obj; objRing.addLast( obj ); }
    void AddLO( RingTestObject1* obj ) { loRing.addLast( obj ); }
    OBJECT_METHODS( 0x9A67A341, RingTestObject2 )
  };

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void TestRingSerialize()
  {
    CObj<RingTestObject2> o = new RingTestObject2();
    for ( int i = 0; i < 512; ++i )
      o->Add( new RingTestObject1( 10 + i * 10 ) );

    TS_ASSERT_EQUALS( o->objRing.first(), o->objRegistry[10] );
    TS_ASSERT_EQUALS( RingTestObject1::Ring::prev( o->objRing.last() ), o->objRegistry[5120] );

    CObj<MemoryStream> pStream = new MemoryStream();
    {
      CPtr<IBinSaver> pSaver = CreateWriteBinSaver( pStream, 0, false );
      (*o) & (*pSaver);
    }

    CObj<RingTestObject2> o2 = new RingTestObject2();;
    pStream->Seek( 0, SEEKORIGIN_BEGIN );
    {
      CPtr<IBinSaver> pSaver = CreateReadBinSaver( pStream,	0 );
      (*o2) & (*pSaver);
    }

    TS_ASSERT_EQUALS( o->objRegistry.size(), o2->objRegistry.size() );

    for ( int i = 0; i < 512; ++i )
      TS_ASSERT_EQUALS( o->objRegistry[10 + i * 10]->param, o2->objRegistry[10 + i * 10]->param );

    for (ring::Range<RingTestObject1::Ring> r(o2->objRing); r; ++r)
    {
      TS_ASSERT_EQUALS( o2->objRegistry[r->param], r.operator ->() );
    }

    TS_ASSERT_EQUALS( o2->objRing.first(), o2->objRegistry[10] );
    TS_ASSERT_EQUALS( RingTestObject1::Ring::prev( o->objRing.last() ), o->objRegistry[5120] );

    while( o->objRing.first() != o->objRing.last() )
      o->objRing.remove( o->objRing.first() );
    while( o2->objRing.first() != o2->objRing.last() )
      o2->objRing.remove( o2->objRing.first() );
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void TestRingSerialize2()
  {
    CObj<RingTestObject2> o = new RingTestObject2();
    CObj<RingTestObject2> p = new RingTestObject2();
    for ( int i = 0; i < 512; ++i )
      o->Add( new RingTestObject1( 10 + i * 10 ) );

    for (ring::Range<RingTestObject1::Ring> r(o->objRing); r; ++r)
    {
      ++r;
      p->AddLO( r.operator ->() );
    }
    o->obj2 = p;

    CObj<MemoryStream> pStream = new MemoryStream();
    {
      CPtr<IBinSaver> pSaver = CreateWriteBinSaver( pStream, 0, false );
      (*o) & (*pSaver);
    }

    CObj<RingTestObject2> o2 = new RingTestObject2();;
    pStream->Seek( 0, SEEKORIGIN_BEGIN );
    {
      CPtr<IBinSaver> pSaver = CreateReadBinSaver( pStream,	0 );
      (*o2) & (*pSaver);
    }

    TS_ASSERT_EQUALS( o->objRegistry.size(), o2->objRegistry.size() );

    for ( int i = 0; i < 512; ++i )
      TS_ASSERT_EQUALS( o->objRegistry[10 + i * 10]->param, o2->objRegistry[10 + i * 10]->param );

    for (ring::Range<RingTestObject1::Ring> r(o2->objRing); r; ++r)
    {
      TS_ASSERT_EQUALS( o2->objRegistry[r->param], r.operator ->() );
    }

    ring::Range<RingTestObject1::LORing> r1(p->loRing);
    ring::Range<RingTestObject1::LORing> r2(o2->obj2->loRing);
    for (; r1 && r2; ++r1, ++r2)
    {
      TS_ASSERT_EQUALS( r1->param, r2->param );
    }

    TS_ASSERT_EQUALS( o2->objRing.first(), o2->objRegistry[10] );
    TS_ASSERT_EQUALS( RingTestObject1::Ring::prev( o->objRing.last() ), o->objRegistry[5120] );

    while( o->obj2->loRing.first() != o->obj2->loRing.last() )
      o->obj2->loRing.remove( o->obj2->loRing.first() );
    while( o2->obj2->loRing.first() != o2->obj2->loRing.last() )
      o2->obj2->loRing.remove( o2->obj2->loRing.first() );

    while( o->objRing.first() != o->objRing.last() )
      o->objRing.remove( o->objRing.first() );
    while( o2->objRing.first() != o2->objRing.last() )
      o2->objRing.remove( o2->objRing.first() );
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//REGISTER_SAVELOAD_CLASS( SimplePointerHolder );
REGISTER_SAVELOAD_CLASS_NM( SerializeTestObject, SaversTest );
REGISTER_SAVELOAD_CLASS_NM( RingTestObject1, SaversTest );
REGISTER_SAVELOAD_CLASS_NM( RingTestObject2, SaversTest );

