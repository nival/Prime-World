//!Component("System/Ptr")
//!Component("System/Savers")
//!Component("System/NSTL")
#include "stdafx.h"
#include "ChunklessSaver.h"
#include "BinChunkSerializer.h"
#include <TestSuite.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IObject1 : public IObjectBase
{
	virtual void A() = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
_interface IObject2 : public IObjectBase
{
	virtual void B() = 0;
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CObject : public CObjectBase, public IObject1, public IObject2
{
	OBJECT_METHODS( 0x1E4A8B42, CObject )
	int nParam;
	CPtr<IObject1> pObject1;
	CObj<IObject2> pObject2;
	
	int operator&( IBinSaver &f );
public:
	CObject() : nParam( 0 ) {}
	CObject( const int _nParam, IObject1 *_pObject1, IObject2 *_pObject2 ) : nParam( _nParam ), pObject1( _pObject1 ), pObject2( _pObject2 ) {}

	void A() { printf( "CObject::A()\n" ); }
	void B() { printf( "CObject::B()\n" ); }

	const int GetRefCount() const { return nRefCount; }
	const int GetObjCount() const { return nObjCount & ~INVALID_REF_MASK; }
	const int GetParam() const { return nParam; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int CObject::operator&( IBinSaver &f )
{
	f.Add(2,&nParam);
	f.Add(3,&pObject1);
	f.Add(4,&pObject2); return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CTestObject2 : public CObjectBase
{
  OBJECT_BASIC_METHODS( CTestObject2 )
  int nParam;
public:
  static int destroyContentsCalled;
  CPtr<CTestObject2> pPtr;
  void OnDestroyContents()
  {
    pPtr = 0;
    ++destroyContentsCalled;
  }

  CTestObject2() : nParam( 0 ) {}
  const int GetParam() const { return nParam; }
};
int CTestObject2::destroyContentsCalled = 0;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class SimplePointerHolder : public IPointerHolder, public CObjectBase
{
	OBJECT_METHODS( 0x1E4A8B41, SimplePointerHolder );
	hash_map<int, CObjectBase*> objects;
public:
	int GetObjectID( CObjectBase *p )
  {
    // return (int)p;
    return *(( int* )( &p ));
  }
	CObjectBase *GetObject( int nID ) 
	{
		hash_map<int, CObjectBase*>::const_iterator pos = objects.find( nID );
		if ( pos == objects.end() )
			return 0;
		
		return pos->second;
	}

  virtual int GetObjectIdST( BaseObjectST * object ) { TS_ASSERT( 0 ); return 0; }
  virtual BaseObjectST * GetObjectST( int id ) { TS_ASSERT( 0 ); return 0; }
  virtual int GetObjectIdMT( BaseObjectMT * pObject ) { TS_ASSERT( 0 ); return 0; }
	virtual BaseObjectMT * GetObjectMT( int id ) { TS_ASSERT( 0 ); return 0; }
	
	void RegisterObject( CObjectBase *p )
  {
    // objects[(int)p] = p;
    objects[*(( int* )( &p ))] = p;
  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CSmartPtrTests : public CxxTest::TestSuite
{
public:
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestBasic()
{
	CPtr<CObject> pObject = new CObject( 10, 0, 0 );;
	CPtr<IObject1> pObject1; pObject1.SetPtr( reinterpret_cast <IObject1*> (pObject.GetBarePtr()));
	CObj<IObject2> pObject2; pObject2.SetPtr( reinterpret_cast <IObject2*> (pObject.GetBarePtr()));

	TS_ASSERT_EQUALS( pObject->GetRefCount(), 2 );
	TS_ASSERT_EQUALS( pObject->GetObjCount(), 1 );
	TS_ASSERT_EQUALS( IsValid( pObject ), true );
	pObject1 = 0;
	TS_ASSERT_EQUALS( pObject->GetRefCount(), 1 );
	TS_ASSERT_EQUALS( pObject->GetObjCount(), 1 );
	TS_ASSERT_EQUALS( IsValid( pObject ), true );
	pObject2 = 0;
	TS_ASSERT_EQUALS( IsValid( pObject ), false );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestDestroyContentsObj()
{
  CObj<CTestObject2> p1 = new CTestObject2();
  CObj<CTestObject2> p2 = p1;
  CTestObject2::destroyContentsCalled = 0;
  p1 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 0 );
  p2 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 1 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestDestroyContentsPtr()
{
  CPtr<CTestObject2> p1 = new CTestObject2();
  CPtr<CTestObject2> p2 = p1;
  CTestObject2::destroyContentsCalled = 0;
  p1 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 0 );
  p2 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 1 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestDestroyContentsObjPtr()
{
  CObj<CTestObject2> p1 = new CTestObject2();
  CPtr<CTestObject2> p2( p1 );
  CPtr<CTestObject2> p3( p1 );
  CTestObject2::destroyContentsCalled = 0;
  p3 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 0 );
  p1 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 1 );
  p2 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 1 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestDestroyContentsPtrObj()
{
  CObj<CTestObject2> p1 = new CTestObject2();
  CPtr<CTestObject2> p2( p1 );
  CPtr<CTestObject2> p3( p1 );
  CTestObject2::destroyContentsCalled = 0;
  p3 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 0 );
  p2 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 0 );
  p1 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 1 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestDestroyContentsPtrObj2()
{
  CObj<CTestObject2> p1 = new CTestObject2();
  p1->pPtr = p1;

  CTestObject2::destroyContentsCalled = 0;
  p1 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 1 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestDestroyContentsPtrObj3()
{
  CObj<CTestObject2> p1 = new CTestObject2();
  CPtr<CTestObject2> p2( p1 );
  p1->pPtr = p1;

  CTestObject2::destroyContentsCalled = 0;
  p1 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 1 );
  p2 = 0;
  TS_ASSERT_EQUALS( CTestObject2::destroyContentsCalled, 1 );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestSerialization()
{
	CPtr<CObject> pObject1 = new CObject( 1, 0, 0 );
	CPtr<CObject> pObject2 = new CObject( 2, pObject1, 0 );
	CObj<CObject> pObject3 = new CObject( 3, pObject1, pObject2 );

	CObj<MemoryStream> pStream = new MemoryStream();
	CPtr<IBinSaver> pSaver = CreateWriteBinSaver( pStream, 0, false );
	pSaver->Add( 1, &pObject3 );
	pSaver = 0;

	TS_ASSERT_EQUALS( IsValid( pObject1 ), true );
	TS_ASSERT_EQUALS( IsValid( pObject2 ), true );
	TS_ASSERT_EQUALS( IsValid( pObject3 ), true );
	
	pObject3 = 0;
	TS_ASSERT_EQUALS( IsValid( pObject1 ), true );
	TS_ASSERT_EQUALS( IsValid( pObject2 ), false );
	TS_ASSERT_EQUALS( IsValid( pObject3 ), false );

	pStream->Seek( 0, SEEKORIGIN_BEGIN );
	pSaver = CreateReadBinSaver( pStream,	0 );
	pSaver->Add( 1, &pObject3 );
	pSaver = 0;
	TS_ASSERT_EQUALS( IsValid( pObject3 ), true );
	TS_ASSERT_EQUALS( pObject3->GetParam(), 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestChunklessSerialization()
{
	CPtr<CObject> pObject1 = new CObject( 1, 0, 0 );
	CPtr<CObject> pObject2 = new CObject( 2, pObject1, 0 );
	CObj<CObject> pObject3 = new CObject( 3, pObject1, pObject2 );

	CObj<SimplePointerHolder> pObjectsHolder = new SimplePointerHolder();
	pObjectsHolder->RegisterObject( pObject1 );
	pObjectsHolder->RegisterObject( pObject2 );
	pObjectsHolder->RegisterObject( pObject3 );
	
	CObj<MemoryStream> pStream = new MemoryStream();
	CPtr<IBinSaver> pSaver = CreateChunklessSaver( pStream, pObjectsHolder, false );
	pSaver->Add( 1, &pObject3 );
	pSaver = 0;

	CObj<CObject> pObject4 = 0;
	pStream->Seek( 0, SEEKORIGIN_BEGIN );
	pSaver = CreateChunklessSaver( pStream, pObjectsHolder, true );
	pSaver->Add( 1, &pObject4 );
	pSaver = 0;
	TS_ASSERT_EQUALS( IsValid( pObject4 ), true );
	TS_ASSERT_EQUALS( pObject4->GetParam(), 3 );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestSimpleSerialization()
{
	CObj<CObject> pObject1 = new CObject( 0x12345678, 0, 0 );

	MemoryStream stream = MemoryStream();
	CPtr<IBinSaver> pSaver = CreateWriteBinSaver( &stream, 0x12345678, false );
	pSaver->Add( 1, &pObject1 );
	pSaver = 0;
	//
	//FileStream file( "saver0.dat", FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
	//stream.Seek( 0, SEEKORIGIN_BEGIN );
	//file.CopyFrom( &stream );
	//file.Close();
	
	pObject1 = 0;
	TS_ASSERT_EQUALS( IsValid( pObject1 ), false );

	stream.Seek( 0, SEEKORIGIN_BEGIN );
	pSaver = CreateReadBinSaver( &stream,	0 );
	pSaver->Add( 1, &pObject1 );
	pSaver = 0;

	TS_ASSERT_EQUALS( IsValid( pObject1 ), true );
	TS_ASSERT_EQUALS( pObject1->GetParam(), 0x12345678 );
}
};
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS( CObject );
REGISTER_SAVELOAD_CLASS( SimplePointerHolder );
BASIC_REGISTER_CLASS( IObject1 );
BASIC_REGISTER_CLASS( IObject2 );

