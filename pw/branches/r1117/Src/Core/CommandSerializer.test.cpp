#include "StdAfx.h"
#include "CommandSerializer.h"
#include <CxxTest.h>
#include "WorldCommand.h"

#pragma REMINDER("Move to PF_Core or implement here, when PF_Core will be merged into Core")

//using namespace NCore;
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class CTestObject : public NCore::WorldObjectBase
//{
//	OBJECT_METHODS( 0x1F4A8B05, CTestObject )
//	CTestObject() :WorldObjectBase (0), nParam1( 0 ) {}
//	ZDATA_(NCore::WorldObjectBase)
//	int nParam1;
//	string szParam2;
//	
//public:
//	ZEND int operator&( IBinSaver &f ) { f.Add(1,(NCore::WorldObjectBase*)this); f.Add(2,&nParam1); f.Add(3,&szParam2); return 0; }
//
//	CTestObject(IWorldObjectsHolder * _world):WorldObjectBase (_world) {}
//	
//	CTestObject(IWorldObjectsHolder * _world, const int _nParam1, const string &_szParam2 ) :WorldObjectBase (_world), nParam1( _nParam1 ), szParam2( _szParam2 ) {}
//
//	const int GetParam1() const { return nParam1; }
//	const string& GetParam2() const { return szParam2; }
//};
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class CTestCreateObjectCommand : public NCore::WorldCommand
//{
//	OBJECT_METHODS( 0x1F4A8B06, CTestCreateObjectCommand );
//	ZDATA
//	CPtr<CTestObject> pObject;
//	int nParam;
//	string szParam;
//public:
//	ZEND int operator&( IBinSaver &f ) { f.Add(2,&pObject); f.Add(3,&nParam); f.Add(4,&szParam); return 0; }
//	CTestCreateObjectCommand() {}
//	CTestCreateObjectCommand( const int _nParam, const string &_szParam ) 
//		: nParam( _nParam ), szParam( _szParam ) {}
//
//	bool CanExecute() const { return true; }
//	void Execute( NCore::IWorldBase *pWorld )
//	{ 
//		pObject = new CTestObject( dynamic_cast<NCore::IWorldObjectsHolder*>(pWorld), nParam, szParam ) ;
//	}
//
//	CTestObject *GetCreatedObject() const { return pObject; }
//};
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class CTestSavedCommand : public NCore::WorldCommand
//{
//	OBJECT_METHODS( 0x1F4A8B3A, CTestSavedCommand );
//
//	ZDATA
//	CPtr<CTestObject> pObject;
//	int nParam1;
//	string szParam2;
//public:
//	ZEND int operator&( IBinSaver &f ) { f.Add(2,&pObject); f.Add(3,&nParam1); f.Add(4,&szParam2); return 0; }
//
//	CTestSavedCommand() : nParam1( 0 ) {}
//	CTestSavedCommand( const int _nParam1, const string &_szParam2, CTestObject *_pObject ) 
//		: pObject( _pObject ) {}
//
//	bool CanExecute() const { return false; }
//	void Execute( NCore::IWorldBase * )
//	{ 
//	}
//
//	CTestObject *GetObject() const { return pObject; }
//	const int GetParam1() const { return nParam1; }
//	const string& GetParam2() const { return szParam2; }
//};
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//class CCommandSerializerTest : public CxxTest::TestSuite
//{
//public:
//	void TestSerialization();
//};
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void CCommandSerializerTest::TestSerialization()
//{
//	CObj<NCore::IWorldObjectsHolder> pWorld = NCore::CreateWorldObjectsHolder();
//	CObj<CTestCreateObjectCommand> pCreateTestObject1 = new CTestCreateObjectCommand( 1, "1" ); 
//	pWorld->ExecuteCommand( pCreateTestObject1 );
//}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//CXX_REGISTER_TEST_SUITE( CCommandSerializerTest, "Tests for UndoRedoCommand Serializer" )
//{
//	CXX_REGISTER_TEST_FUNCTION( TestSerialization, "Test serialization/deserialization of world commands" );
//}
//
//REGISTER_SAVELOAD_CLASS( CTestObject );
