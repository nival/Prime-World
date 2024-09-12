//!Component('libdb/Database')
//!Component('System/FileSystem/TestFileSystem')
//!Component('System/Texts')
#include "stdafx.h"
#include <CxxTest.h>

#include "System/FileSystem/TestFileSystem.h"
#include "libdb/XmlSaver.h"
#include "libdb/DbResourceCache.h"
#include "ClonedPtr.h"
#include "InheritableRes.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{

struct SimpleResource : public DbResource
{
	DBRESOURCE_METHODS( SimpleResource );

	int x;
	CVec2 v2;
	CVec3 v3;
	CTextRef text;

	SimpleResource() : x( 0 ), v2( 0, 0 ), v3( 0, 0, 0 ) {}

	virtual int GetTypeId() const { return 0; }
	virtual int operator&( IXmlSaver &saver )
	{
		saver.Add( "x", &x );
		saver.Add( "v2", &v2 );
		saver.Add( "v3", &v3 );
    saver.Add( "text", &text );

		return 0;
	}
	virtual DWORD CalcCheckSum() const { return 0; }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct RefResource : public DbResource
{
	DBRESOURCE_METHODS( RefResource );

	Ptr<SimpleResource> pSimpleResource;
  vector<NDb::Ptr<RefResource>> resourcesList;

	RefResource() {}

	virtual int GetTypeId() const { return 0; }
	virtual int operator&( IXmlSaver &saver )
	{
		saver.Add( "pSimpleResource", &pSimpleResource );
    saver.Add( "resourcesList", &resourcesList );
		return 0;
	}
	virtual DWORD CalcCheckSum() const { return 0; }
};
} //namespace NDb


/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class TestDBPrecache : public CxxTest::TestSuite
{
  CObj<TestFileSystem> pFileSystem;
public:
  void setUp()
  {
    pFileSystem = new TestFileSystem( "", true );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( pFileSystem, 0 ) );
  }
  void tearDown()
  {
    NDb::SetResourceCache( 0 );
    ReloadTexts();
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void MakeSampleFS()
  {
    //root - S1
    //     - A  - S2
    //          - C
    //              - S3 - 1.txt
    //              - D
    //              - >A
    //     - B
    string strRoot = "Рї>С—<?xml version=\"1.0\" encoding=\"utf-8\"?> <RefResource>"
      "<pSimpleResource href=\"S1.xdb\" />"
      "<resourcesList> <Item href=\"A.xdb\"/> <Item href=\"B.xdb\"/> </resourcesList>"
      "</RefResource>";
    string strS1 = "Рї>С—<?xml version=\"1.0\" encoding=\"utf-8\"?> <SimpleResource>"
      "<x>10</x>"
      "</SimpleResource>";
    string strS2 = "Рї>С—<?xml version=\"1.0\" encoding=\"utf-8\"?> <SimpleResource>"
      "<x>10</x>"
      "</SimpleResource>";
    string strS3 = "Рї>С—<?xml version=\"1.0\" encoding=\"utf-8\"?> <SimpleResource>"
      "<x>30</x>"
      "<text textref=\"/1.txt\" />"
      "</SimpleResource>";
    string strA = "Рї>С—<?xml version=\"1.0\" encoding=\"utf-8\"?> <RefResource>"
      "<pSimpleResource href=\"S2.xdb\" />"
      "<resourcesList> <Item href=\"C.xdb\"/> </resourcesList>"
      "</RefResource>";
    string strB = "Рї>С—<?xml version=\"1.0\" encoding=\"utf-8\"?> <RefResource>"
      "<pSimpleResource href=\"\" />"
      "<resourcesList/>"
      "</RefResource>";
    string strC = "Рї>С—<?xml version=\"1.0\" encoding=\"utf-8\"?> <RefResource>"
      "<pSimpleResource href=\"S3.xdb\" />"
      "<resourcesList> <Item href=\"D.xdb\"/> </resourcesList>"
      "<resourcesList/>"
      "</RefResource>";
    string strD = "Рї>С—<?xml version=\"1.0\" encoding=\"utf-8\"?> <RefResource>"
      "<pSimpleResource href=\"\" />"
      "<resourcesList/>"
      "</RefResource>";

    pFileSystem->SetFileWithContents( "root.xdb", strRoot );
    pFileSystem->SetFileWithContents( "A.xdb", strA );
    pFileSystem->SetFileWithContents( "B.xdb", strB );
    pFileSystem->SetFileWithContents( "C.xdb", strC );
    pFileSystem->SetFileWithContents( "D.xdb", strD );
    pFileSystem->SetFileWithContents( "S1.xdb", strS1 );
    pFileSystem->SetFileWithContents( "S2.xdb", strS2 );
    pFileSystem->SetFileWithContents( "S3.xdb", strS3 );

    pFileSystem->SetFileWithContents( "1.txt", "\xff\xfesome text" );
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void MakeEmptyFS()
  {
    string strRoot = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <RefResource> </RefResource>";
    string strS1 = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <SimpleResource></SimpleResource>";
    pFileSystem->SetFileWithContents( "root.xdb", strRoot );
    pFileSystem->SetFileWithContents( "S1.xdb", strS1 );
    pFileSystem->SetFileWithContents( "S2.xdb", strS1 );
    pFileSystem->SetFileWithContents( "S3.xdb", strS1 );
    pFileSystem->SetFileWithContents( "A.xdb", strRoot );
    pFileSystem->SetFileWithContents( "B.xdb", strRoot );
    pFileSystem->SetFileWithContents( "C.xdb", strRoot );
    pFileSystem->SetFileWithContents( "D.xdb", strRoot );
    pFileSystem->SetFileWithContents( "1.txt", "" );
  }

  void TestNoPrecache()
  {
    MakeSampleFS();
    NDb::Ptr<NDb::RefResource> pRes = NDb::Get<NDb::RefResource>( NDb::DBID( "root.xdb" ) );

    TS_ASSERT( pRes );

    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "root.xdb" ), 1 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "S1.xdb" ), 1 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "A.xdb" ), 1 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "B.xdb" ), 1 );

    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "C.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "D.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "S2.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "S3.xdb" ), 0 );

    TS_ASSERT( pRes->pSimpleResource );
    TS_ASSERT( pFileSystem->GetUsageCount( "S1.xdb" ) == 2 );

    MakeEmptyFS();
    TS_ASSERT( !pRes->resourcesList[0]->pSimpleResource );  // S2
    TS_ASSERT( pRes->resourcesList[0]->resourcesList.empty() );  // C
  }

  void TestFullPrecache()
  {
    MakeSampleFS();
    NDb::Ptr<NDb::RefResource> pRes = NDb::Precache<NDb::RefResource>( NDb::DBID( "root.xdb" ), 4 );

    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "root.xdb" ), 1 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "S1.xdb" ), 1 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "A.xdb" ), 1 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "B.xdb" ), 1 );

    MakeEmptyFS();
    pFileSystem->ResetUsageCounts();

    TS_ASSERT( pRes->resourcesList[0]->pSimpleResource );  // S2
    TS_ASSERT( pRes->resourcesList[0]->resourcesList[0] );  // C
    TS_ASSERT( pRes->resourcesList[0]->resourcesList[0]->pSimpleResource );  // S3
    TS_ASSERT( pRes->resourcesList[0]->resourcesList[0]->resourcesList[0] );  // D

    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "root.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "A.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "B.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "S3.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "C.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "D.xdb" ), 0 );
  }

  void TestPrecacheDepth()
  {
    MakeSampleFS();
    NDb::Ptr<NDb::RefResource> pRes = NDb::Precache<NDb::RefResource>( NDb::DBID( "root.xdb" ), 2 );

    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "root.xdb" ), 1 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "S1.xdb" ), 1 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "A.xdb" ), 1 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "B.xdb" ), 1 );

    MakeEmptyFS();
    pFileSystem->ResetUsageCounts();

    TS_ASSERT( pRes->resourcesList[0]->pSimpleResource );  // S2
    TS_ASSERT( pRes->resourcesList[0]->resourcesList[0] );  // C
    TS_ASSERT( !pRes->resourcesList[0]->resourcesList[0]->pSimpleResource );  // S3
    TS_ASSERT( pRes->resourcesList[0]->resourcesList[0]->resourcesList.empty() );  // D

    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "root.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "A.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "B.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "S2.xdb" ), 1 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "C.xdb" ), 1 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "D.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "S3.xdb" ), 0 );
  }

  struct MockTraverser : public NDb::IResourcesProcessor
  {
    int resCount;
    int sumX;
    bool stop;
    MockTraverser() : resCount(0), sumX(0), stop(false) {}
    virtual bool Call( const NDb::DBID& dbid, const NDb::DbResource* pRes )
    {
      if ( pRes->GetObjectTypeName() == NDb::SimpleResource::GetTypeName() )
      {
        const NDb::SimpleResource* pSRes = static_cast<const NDb::SimpleResource*>(pRes);  
        ++resCount;
        sumX += pSRes->x;
      }
      return !stop;
    }
    virtual bool LoadResources() { return true; }
  };

  void TestTraverse()
  {
    MakeSampleFS();

    NDb::Ptr<NDb::RefResource> pRes = NDb::Get<NDb::RefResource>( NDb::DBID( "root.xdb" ) );

    MockTraverser tr;

    /*pRes.Traverse( 2, &tr );

    TS_ASSERT_EQUALS( tr.resCount, 2 );
    TS_ASSERT_EQUALS( tr.sumX, 20 );
    tr.resCount = 0; tr.sumX = 0;

    pRes.Traverse( 3, &tr );
    TS_ASSERT_EQUALS( tr.resCount, 3 );
    TS_ASSERT_EQUALS( tr.sumX, 50 );
    tr.resCount = 0; tr.sumX = 0;*/

    pRes.Traverse( 20, &tr );
    TS_ASSERT_EQUALS( tr.resCount, 3 );
    TS_ASSERT_EQUALS( tr.sumX, 50 );
    tr.resCount = 0; tr.sumX = 0;

    tr.stop = true;
    pRes.Traverse( 20, &tr );
    TS_ASSERT_EQUALS( tr.resCount, 0 );
    TS_ASSERT_EQUALS( tr.sumX, 0 );
  }

  void TestTextPrecache()
  {
    RootFileSystem::RegisterFileSystem( pFileSystem );
    MakeSampleFS();

    NDb::Ptr<NDb::RefResource> pRes = NDb::Precache<NDb::RefResource>( NDb::DBID( "root.xdb" ), 4 );

    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "1.txt" ), 1 );
    TS_ASSERT( !pRes->resourcesList[0]->resourcesList[0]->pSimpleResource->text.GetText().empty() );  // 1.txt

    MakeEmptyFS();

    TS_ASSERT( !pRes->resourcesList[0]->resourcesList[0]->pSimpleResource->text.GetText().empty() );  // 1.txt

    RootFileSystem::UnregisterFileSystem( pFileSystem );
  }

  void TestPapaPrecache()
  {
    // A  - B
    //   -> C - D
    string strA = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild parent=\"C.xdb\">"
      "<twin href=\"B.xdb\" />"
      "<_data><x>1</x><y>0</y></_data>"
      "</LofSimpleChild>";
    string strB = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild>"
      "<_data><x>2</x><y>0</y></_data>"
      "</LofSimpleChild>";
    string strC = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild>"
      "<twin href=\"D.xdb\" />"
      "<_data><x>3</x><y>0</y></_data>"
      "</LofSimpleChild>";
    string strD = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild>"
      "<_data><x>4</x><y>0</y></_data>"
      "</LofSimpleChild>";
    pFileSystem->SetFileWithContents( "A.xdb", strA );
    pFileSystem->SetFileWithContents( "B.xdb", strB );
    pFileSystem->SetFileWithContents( "C.xdb", strC );
    pFileSystem->SetFileWithContents( "D.xdb", strD );


    NDb::Ptr<NDb::LofSimpleChild> pRes = NDb::Precache<NDb::LofSimpleChild>( NDb::DBID( "A.xdb" ), 4 );

    MakeEmptyFS();
    pFileSystem->ResetUsageCounts();

    TS_ASSERT( pRes->twin );

    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "A.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "B.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "C.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "D.xdb" ), 0 );
  }
  void TestPapaPrecache2()
  {
    // root 
    //      - A  - B
    //        -> C - D
    string strRoot = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild>"
      "<twin href=\"A.xdb\" />"
       "<_data><x>0</x><y>10</y></_data>"
      "</LofSimpleChild>";
    string strA = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild parent=\"C.xdb\">"
      "<twin href=\"B.xdb\" />"
      "<_data><x>1</x><y>0</y></_data>"
      "</LofSimpleChild>";
    string strB = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild>"
      "<_data><x>2</x><y>0</y></_data>"
      "</LofSimpleChild>";
    string strC = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild>"
      "<twin href=\"D.xdb\" />"
      "<_data><x>3</x><y>0</y></_data>"
      "</LofSimpleChild>";
    string strD = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild>"
      "<_data><x>4</x><y>0</y></_data>"
      "</LofSimpleChild>";
    pFileSystem->SetFileWithContents( "root.xdb", strRoot );
    pFileSystem->SetFileWithContents( "A.xdb", strA );
    pFileSystem->SetFileWithContents( "B.xdb", strB );
    pFileSystem->SetFileWithContents( "C.xdb", strC );
    pFileSystem->SetFileWithContents( "D.xdb", strD );


    NDb::Ptr<NDb::LofSimpleChild> pRes = NDb::Precache<NDb::LofSimpleChild>( NDb::DBID( "root.xdb" ), 4 );

    MakeEmptyFS();
    pFileSystem->ResetUsageCounts();

    TS_ASSERT( pRes->twin );
    TS_ASSERT( ((const NDb::LofSimpleChild*)pRes->twin.GetPtr())->twin );

    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "A.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "B.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "C.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "D.xdb" ), 0 );
  }


  void TestInlinedPrecache()
  {
    // A - {B} - C

    string strA = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofSimpleChild>"
      "<twin href=\"A.xdb\" id=\"7C593133-F336-4B00-8406-055DBDC04BE9\">"
      "  <LofSimpleChild>"
      "  <twin href=\"C.xdb\" />"
      "  <_int>10</_int>"
      "  </LofSimpleChild>"
      "</twin>"
      "<_int>1</_int>"
      "</LofSimpleChild>";
    string strC = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild>"
      "<_int>2</_int>"
      "</LofSimpleChild>";

    pFileSystem->SetFileWithContents( "A.xdb", strA );
    pFileSystem->SetFileWithContents( "C.xdb", strC );

    NDb::Ptr<NDb::LofSimpleChild> pRes = NDb::Precache<NDb::LofSimpleChild>( NDb::DBID( "A.xdb" ), 4 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "C.xdb" ), 1 );

    MakeEmptyFS();
    pFileSystem->ResetUsageCounts();

    TS_ASSERT( pRes->twin );
    TS_ASSERT_EQUALS( pRes->twin->_int, 10 );
    TS_ASSERT( ( (const NDb::LofSimpleChild*)pRes->twin.GetPtr())->twin );
    TS_ASSERT_EQUALS( ( (const NDb::LofSimpleChild*)pRes->twin.GetPtr())->twin->_int, 2 );

    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "A.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "C.xdb" ), 0 );
  }

  void TestPapaWithInlinedPrecache()
  {
    // root - {A} 
    //          -> C - {D}
    //                     - E
    string strRoot = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild>"
      "<twin href=\"root.xdb\" id=\"7C593133-F336-4B00-8406-055DBDC04BE9\" >"
      "  <LofSimpleChild parent=\"C.xdb\">"
      "  <_int>10</_int>"
      "  </LofSimpleChild>"
      "</twin>"
      "<_data><x>0</x><y>10</y></_data>"
      "</LofSimpleChild>";
    string strC = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild>"
      "<twin href=\"C.xdb\" id=\"7C593133-F336-4B00-8406-155DBDC04BEA\" >"
      "  <LofSimpleChild>"
      "  <twin href=\"E.xdb\" />"
      "  <_int>10</_int>"
      "  </LofSimpleChild>"
      "</twin>"
      "<_data><x>3</x><y>0</y></_data>"
      "</LofSimpleChild>";
    string strE = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?> <LofSimpleChild>"
      "<_int>2</_int>"
      "</LofSimpleChild>";

    pFileSystem->SetFileWithContents( "root.xdb", strRoot );
    pFileSystem->SetFileWithContents( "C.xdb", strC );
    pFileSystem->SetFileWithContents( "E.xdb", strE );


    NDb::Ptr<NDb::LofSimpleChild> pRes = NDb::Precache<NDb::LofSimpleChild>( NDb::DBID( "root.xdb" ), 4 );

    MakeEmptyFS();
    pFileSystem->ResetUsageCounts();

    TS_ASSERT( pRes->twin );
    NDb::Ptr<NDb::LofSimpleChild> pA = (const NDb::LofSimpleChild*)pRes->twin.GetPtr(); 
    NDb::Ptr<NDb::LofSimpleChild> pD = (const NDb::LofSimpleChild*)pA->twin.GetPtr(); 
    NDb::Ptr<NDb::LofSimpleChild> pE = (const NDb::LofSimpleChild*)pD->twin.GetPtr(); 

    TS_ASSERT( pD );
    TS_ASSERT( pE );

    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "root.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "C.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "E.xdb" ), 0 );
  }

  void TestStatesPrecache()
  {
    string strRoot = "<?xml version=\"1.0\" encoding=\"utf-8\"?> <TestStatedObject2>"
      "<_int>2</_int>"
      "<ref href=\"root.xdb\" id=\"7C593133-F336-4B00-8406-055DBDC04BE9\" >"
      "  <TestStatedObject2>"
      "  <ref href=\"A.xdb\" />"
      "  <_int>1</_int>"
      "  </TestStatedObject2>"
      "</ref>"
      "<__states>"
      "<state name=\"a\">"
      "   <ref href=\"root.xdb\" id=\"6724D851-896A-46FB-84D3-050D65AEA92D\" >"
      "   <TestStatedObject2 parent=\"root.xdb:7C593133-F336-4B00-8406-055DBDC04BE9\" />"
      "   </ref>"
      "</state>"
      "<state name=\"b\">"
      "   <ref href=\"root.xdb\" id=\"6724D851-896A-46FB-84D3-050D65AEA93D\" >"
      "   <TestStatedObject2 parent=\"root.xdb:7C593133-F336-4B00-8406-055DBDC04BE9\" >"
      "     <_int>3</_int>"
      "     <ref href=\"B.xdb\" />"
      "     </TestStatedObject2>";
      "   </ref>"
      "</state>"
      "</__states>"
      "</TestStatedObject2>";

    string strA = "<?xml version=\"1.0\" encoding=\"utf-8\"?> <TestStatedObject2>"
      " <_int>10</_int>"
      " </TestStatedObject2>";
    string strB = "<?xml version=\"1.0\" encoding=\"utf-8\"?> <TestStatedObject2>"
      " <_int>20</_int>"
      " </TestStatedObject2>";

    string strC = "<?xml version=\"1.0\" encoding=\"utf-8\"?> <TestStatedObject2>"
      "<ref href=\"root.xdb\" />"
      "</TestStatedObject2>";

    pFileSystem->SetFileWithContents( "root.xdb", strRoot );
    pFileSystem->SetFileWithContents( "A.xdb", strA );
    pFileSystem->SetFileWithContents( "B.xdb", strB );
    pFileSystem->SetFileWithContents( "C.xdb", strC );


    NDb::Ptr<NDb::TestStatedObject2> pC = NDb::Precache<NDb::TestStatedObject2>( NDb::DBID( "C.xdb" ), 4 );

    MakeEmptyFS();
    pFileSystem->ResetUsageCounts();

    NDb::Ptr<NDb::TestStatedObject2> pRes = pC->ref;

    TS_ASSERT( pRes->ref );
    TS_ASSERT_EQUALS( pRes->ref->_int, 1 ); 
    TS_ASSERT_EQUALS( pRes->ref->ref->_int, 10 ); 

    pRes.SetState( "a" );
    TS_ASSERT_EQUALS( pRes->ref->_int, 1 ); 
    TS_ASSERT_EQUALS( pRes->ref->ref->_int, 10 ); 

    pRes.SetState( "b" );
    TS_ASSERT_EQUALS( pRes->ref->_int, 3 ); 
    TS_ASSERT_EQUALS( pRes->ref->ref->_int, 20 ); 

    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "root.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "A.xdb" ), 0 );
    TS_ASSERT_EQUALS( pFileSystem->GetUsageCount( "B.xdb" ), 0 );
  }
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DBTest : public CxxTest::TestSuite
{
  CObj<TestFileSystem> pFileSystem;
public:
  void setUpSuite()
  {
    pFileSystem = new TestFileSystem( "", true );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( pFileSystem, 0 ) );
  }
  void tearDownSuite()
  {
    NDb::SetResourceCache( 0 );
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void TestSimpleSerialization()
  {
    NDb::SimpleResource* res = new NDb::SimpleResource();
    res->x = 666;
    res->v2.x = 10;
    res->v2.y = 11;
    res->v3.x = 12;
    res->v3.y = 13;
    res->v3.z = 14;

    {
      CPtr<Stream> pStream = new FileStream( "res.xdb", FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
      CPtr<IXmlSaver> pSaver = CreateXmlSaver( pStream, false );
      pSaver->AddPolymorphicBase( "SimpleResource", res );
    }

    NDb::SimpleResource* res2 = new NDb::SimpleResource();
    {
      CPtr<Stream> pStream = new FileStream( "res.xdb", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
      CPtr<IXmlSaver> pSaver = CreateXmlSaver( pStream, true );
      pSaver->AddPolymorphicBase( "SimpleResource", res2 );
    }
    delete res;
    delete res2;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void TestSimpleCache()
  {
    NDb::SimpleResource* res = new NDb::SimpleResource();

    res->x = 666;
    {
      CPtr<Stream> pStream = pFileSystem->OpenFile( "res2.xdb", FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
      CPtr<IXmlSaver> pSaver = CreateXmlSaver( pStream, false );
      pSaver->AddPolymorphicBase( "SimpleResource", res );
    }

    res->x = 0;
    {
      CPtr<Stream> pStream = pFileSystem->OpenFile( "res2.xdb", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
      CPtr<IXmlSaver> pSaver = CreateXmlSaver( pStream, true );
      pSaver->AddPolymorphicBase( "SimpleResource", res );
    }

    TS_ASSERT_EQUALS( res->x, 666 );
    delete res;

    NDb::Ptr<NDb::SimpleResource> pRes = NDb::Get<NDb::SimpleResource>( NDb::DBID( "res2.xdb" ) );
    TS_ASSERT_EQUALS( IsValid( pRes ), true );
    if ( pRes )
    {
      TS_ASSERT_EQUALS( pRes->x, 666 );
    }

    NDb::RefResource* refRes = new NDb::RefResource();
    refRes->pSimpleResource = pRes;
    {
      CPtr<Stream> pStream = pFileSystem->OpenFile( "refRes.xdb", FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
      CPtr<IXmlSaver> pSaver = CreateXmlSaver( pStream, false );
      pSaver->AddPolymorphicBase( refRes->GetObjectTypeName(), refRes );
    }
    delete refRes;
  }

  void TestSimpleInheritableRes()
  {
    string parent_str = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofSimpleInheritable>"
      "<BackLink DBID=\"test\" Count=\"1\" />"
      "<_bool>false</_bool>"
      "<_int>4</_int>"
      "<_float>65</_float>"
      "<_string>Vadim</_string>"
      "</LofSimpleInheritable>";
    string test_str = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofSimpleInheritable parent=\"parent\">"
      "<_int>3</_int>"
      "<_float>3</_float>"
      "</LofSimpleInheritable>";

    pFileSystem->SetFileWithContents( "parent.xdb", parent_str );
    pFileSystem->SetFileWithContents( "test.xdb", test_str );

    NDb::LofSimpleInheritable* parent_res = new NDb::LofSimpleInheritable();
    NDb::LofSimpleInheritable* test_res = new NDb::LofSimpleInheritable();
    {
      CPtr<Stream> pStream = pFileSystem->OpenFile( "parent.xdb", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
      CPtr<IXmlSaver> pSaver = CreateXmlSaver( pStream, true );
      pSaver->AddPolymorphicBase( "LofSimpleInheritable", parent_res );

      CPtr<Stream> pStream2 = pFileSystem->OpenFile( "test.xdb", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
      CPtr<IXmlSaver> pSaver2 = CreateXmlSaver( pStream2, true );
      pSaver2->AddPolymorphicBase( "LofSimpleInheritable", test_res );
    }

    TS_ASSERT_EQUALS( parent_res->_bool, false );
    TS_ASSERT_EQUALS( parent_res->_int, 4 );
    TS_ASSERT_EQUALS( parent_res->_float, 65.0f );
    TS_ASSERT_EQUALS( parent_res->_string, "Vadim" );

    TS_ASSERT_EQUALS( test_res->_bool, false );
    TS_ASSERT_EQUALS( test_res->_int, 3 );
    TS_ASSERT_EQUALS( test_res->_float, 3.0f );
    TS_ASSERT_EQUALS( test_res->_string, "Vadim" );

    delete parent_res;
    delete test_res;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void TestHardInheritableRes()
  {
    string parent_str = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofHardInheritable>"
      "<BackLink DBID=\"test\" Count=\"1\" />"
      "<_int>10</_int>"
      "<_list>"
      "<Item>2</Item>"
      "<Item>4</Item>"
      "<Item>8</Item>"
      "</_list>"
      "</LofHardInheritable>";
    string test_str = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofHardInheritable parent=\"parent\">"
      "<_int>20</_int>"
      "<_list>"
      "<Item>1</Item>"
      "<Item skip=\"1\" />"
      "<Item delete=\"1\" />"
      "</_list>"
      "</LofHardInheritable>";

    pFileSystem->SetFileWithContents( "parent.xdb", parent_str );
    pFileSystem->SetFileWithContents( "test.xdb", test_str );

    NDb::LofHardInheritable* parent_res = new NDb::LofHardInheritable();
    NDb::LofHardInheritable* test_res = new NDb::LofHardInheritable();
    {
      CPtr<Stream> pStream = pFileSystem->OpenFile( "parent.xdb", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
      CPtr<IXmlSaver> pSaver = CreateXmlSaver( pStream, true );
      pSaver->AddPolymorphicBase( "LofHardInheritable", parent_res );

      CPtr<Stream> pStream2 = pFileSystem->OpenFile( "test.xdb", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
      CPtr<IXmlSaver> pSaver2 = CreateXmlSaver( pStream2, true );
      pSaver2->AddPolymorphicBase( "LofHardInheritable", test_res );
    }

    TS_ASSERT_EQUALS( parent_res->_int, 10 );
    TS_ASSERT_EQUALS( parent_res->_list.size(), 3 );
    TS_ASSERT_EQUALS( parent_res->_list[0], 2 );
    TS_ASSERT_EQUALS( parent_res->_list[1], 4 );
    TS_ASSERT_EQUALS( parent_res->_list[2], 8 );

    TS_ASSERT_EQUALS( test_res->_int, 20 );
    TS_ASSERT_EQUALS( test_res->_list.size(), 2 );
    TS_ASSERT_EQUALS( test_res->_list[0], 1 );
    TS_ASSERT_EQUALS( test_res->_list[1], 4 );

    delete parent_res;
    delete test_res;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void TestComplexInheritableRes()
  {
    string parent_str = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofComplexInheritable>"
      "<BackLink DBID=\"test\" Count=\"1\" />"
      "<_int>33</_int>"
      "<_list>"
      "<Item>"
      "<x>2</x>"
      "<y>2</y>"
      "</Item>"
      "<Item>"
      "<x>4</x>"
      "<y>4</y>"
      "</Item>"
      "<Item>"
      "<x>8</x>"
      "<y>8</y>"
      "</Item>"
      "</_list>"
      "</LofComplexInheritable>";
    string test_str = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofComplexInheritable parent=\"parent\">"
      "<_int>66</_int>"
      "<_list>"
      "<Item>"
      "<x>1</x>"
      "<y>1</y>"
      "</Item>"
      "<Item skip=\"1\" />"
      "<Item delete=\"1\" />"
      "</_list>"
      "</LofComplexInheritable>";

    pFileSystem->SetFileWithContents( "parent.xdb", parent_str );
    pFileSystem->SetFileWithContents( "test.xdb", test_str );

    NDb::LofComplexInheritable* parent_res = new NDb::LofComplexInheritable();
    NDb::LofComplexInheritable* test_res = new NDb::LofComplexInheritable();
    {
      CPtr<Stream> pStream = pFileSystem->OpenFile( "parent.xdb", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
      CPtr<IXmlSaver> pSaver = CreateXmlSaver( pStream, true );
      pSaver->AddPolymorphicBase( "LofComplexInheritable", parent_res );

      CPtr<Stream> pStream2 = pFileSystem->OpenFile( "test.xdb", FILEACCESS_READ, FILEOPEN_OPEN_EXISTING );
      CPtr<IXmlSaver> pSaver2 = CreateXmlSaver( pStream2, true );
      pSaver2->AddPolymorphicBase( "LofComplexInheritable", test_res );
    }

    TS_ASSERT_EQUALS( parent_res->_int, 33 );
    TS_ASSERT_EQUALS( parent_res->_list.size(), 3 );
    TS_ASSERT_EQUALS( parent_res->_list[0].x, 2 );
    TS_ASSERT_EQUALS( parent_res->_list[0].y, 2 );
    TS_ASSERT_EQUALS( parent_res->_list[1].x, 4 );
    TS_ASSERT_EQUALS( parent_res->_list[1].y, 4 );
    TS_ASSERT_EQUALS( parent_res->_list[2].x, 8 );
    TS_ASSERT_EQUALS( parent_res->_list[2].y, 8 );

    TS_ASSERT_EQUALS( test_res->_int, 66 );
    TS_ASSERT_EQUALS( test_res->_list.size(), 2 );
    TS_ASSERT_EQUALS( test_res->_list[0].x, 1 );
    TS_ASSERT_EQUALS( test_res->_list[0].y, 1 );
    TS_ASSERT_EQUALS( test_res->_list[1].x, 4 );
    TS_ASSERT_EQUALS( test_res->_list[1].y, 4 );

    delete parent_res;
    delete test_res;
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void TestSimpleChildRes()
  {
    string parent_str = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofSimpleChild>"
      "<twin href=\"test_inh\" />"
      "<_data>"
      "<x>0</x>"
      "<y>0</y>"
      "</_data>"
      "<_bool>false</_bool>"
      "<_int>10</_int>"
      "<_float>10</_float>"
      "<_string>10</_string>"
      "</LofSimpleChild>";

    string test_str = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofSimpleChild parent=\"parent\">"
      "<twin href=\"parent\" />"
      "<_float>0</_float>"
      "<_string>mmm</_string>"
      "</LofSimpleChild>";

    string test_inh_str = "п>ї<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofSimpleInheritable>"
      "<_bool>false</_bool>"
      "<_int>5</_int>"
      "<_float>5</_float>"
      "<_string>5</_string>"
      "</LofSimpleInheritable>";

    pFileSystem->SetFileWithContents( "parent.xdb", parent_str );
    pFileSystem->SetFileWithContents( "test.xdb", test_str );
    pFileSystem->SetFileWithContents( "test_inh.xdb", test_inh_str );

    NDb::Ptr<NDb::LofSimpleInheritable> test_inh_res = NDb::Get<NDb::LofSimpleInheritable>( NDb::DBID::DBID("test_inh.xdb") );
    NDb::Ptr<NDb::LofSimpleChild> parent_res = NDb::Get<NDb::LofSimpleChild>( NDb::DBID::DBID("parent.xdb") );
    NDb::Ptr<NDb::LofSimpleChild> test_res = NDb::Get<NDb::LofSimpleChild>( NDb::DBID::DBID("test.xdb") );

    TS_ASSERT_EQUALS( test_inh_res->_bool, false );
    TS_ASSERT_EQUALS( test_inh_res->_int, 5 );
    TS_ASSERT_EQUALS( test_inh_res->_float, 5.0f );
    TS_ASSERT_EQUALS( test_inh_res->_string, "5" );

    TS_ASSERT_EQUALS( parent_res->twin->_bool, false );
    TS_ASSERT_EQUALS( parent_res->twin->_int, 5 );
    TS_ASSERT_EQUALS( parent_res->twin->_float, 5.0f );
    TS_ASSERT_EQUALS( parent_res->twin->_string, "5" );
    TS_ASSERT_EQUALS( parent_res->_bool, false );
    TS_ASSERT_EQUALS( parent_res->_int, 10 );
    TS_ASSERT_EQUALS( parent_res->_float, 10.0f );
    TS_ASSERT_EQUALS( parent_res->_string, "10" );

    TS_ASSERT_EQUALS( test_res->twin->_bool, false );
    TS_ASSERT_EQUALS( test_res->twin->_int, 10 );
    TS_ASSERT_EQUALS( test_res->twin->_float, 10.0f );
    TS_ASSERT_EQUALS( test_res->twin->_string, "10" );
    TS_ASSERT_EQUALS( test_res->_bool, false );
    TS_ASSERT_EQUALS( test_res->_int, 10 );
    TS_ASSERT_EQUALS( test_res->_float, 0.0f );
    TS_ASSERT_EQUALS( test_res->_string, "mmm" );
  }

  void TestStates()
  {
    string obj_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<TestStatedObject>"
      "<_int>10</_int>"
      "<_list>"
        "<Item>"
          "<x>1</x>"
          "<y>1</y>"
        "</Item>"
      "</_list> "
      "<states>"
        "<state name=\"A\">"
          "<_int>20</_int>"
        "</state>"
      "</states>"
      "</TestStatedObject>";

    pFileSystem->SetFileWithContents( "test.xdb", obj_str );

    NDb::Ptr<NDb::TestStatedObject> test_obj = NDb::Get<NDb::TestStatedObject>( NDb::DBID::DBID("test.xdb") );

    TS_ASSERT_EQUALS( test_obj->_int, 10 );
    test_obj.SetState( "A" );
    TS_ASSERT_EQUALS( test_obj->_int, 20 );
  }

  struct NotificationCallback
  {
    NDb::ChangeablePtr<NDb::TestStatedObject> a;
    NDb::ChangeablePtr<NDb::TestStatedObject> b;
    NDb::DBID res1, res2;

    void CallbackA( const NDb::DBID& param )
    {
      res1 = param;
    }
    void CallbackB( const NDb::DBID& param )
    {
      res2 = param;
    }

    NotificationCallback()
      : a( this, &NotificationCallback::CallbackA )
      , b( this, &NotificationCallback::CallbackB )
    {

    }
  };


  void TestChangeablePtrWithStates()
  {
    string obj_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<TestStatedObject>"
      "<_int>10</_int>"
      "<_list>"
      "<Item>"
      "<x>1</x>"
      "<y>1</y>"
      "</Item>"
      "</_list> "
      "<states>"
      "<state name=\"A\">"
      "<_int>20</_int>"
      "</state>"
      "</states>"
      "</TestStatedObject>";
    string obj2_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<TestStatedObject>"
      "<_int>20</_int>"
      "<_list>"
      "<Item>"
      "<x>1</x>"
      "<y>1</y>"
      "</Item>"
      "</_list> "
      "</TestStatedObject>";

    pFileSystem->SetFileWithContents( "test.xdb", obj_str );
    pFileSystem->SetFileWithContents( "test2.xdb", obj2_str );
    NDb::Ptr<NDb::TestStatedObject> test_obj = NDb::Get<NDb::TestStatedObject>( NDb::DBID::DBID("test.xdb") );
    NDb::Ptr<NDb::TestStatedObject> test_obj2 = NDb::Get<NDb::TestStatedObject>( NDb::DBID::DBID("test2.xdb") );

    NotificationCallback cb;
    cb.a = test_obj;
    cb.b = test_obj2;

    TS_ASSERT( cb.res1.IsEmpty() );
    TS_ASSERT( cb.res2.IsEmpty() );

    NDb::GetDbResourceCache().Reset( NDb::DBID::DBID("test2.xdb") );
    TS_ASSERT( cb.res2.GetFileName() == "test2.xdb" );

    cb.res1 = NDb::DBID();
    cb.a = test_obj2;
    NDb::GetDbResourceCache().Reset( NDb::DBID::DBID("test2.xdb") );
    TS_ASSERT( cb.res1.GetFileName() == "test2.xdb" );

    cb.res1 = NDb::DBID();
    cb.res2 = NDb::DBID();
    cb.a = 0;
    cb.b = 0;
    NDb::GetDbResourceCache().Reset( NDb::DBID::DBID("test2.xdb") );
    TS_ASSERT( cb.res1.GetFileName() == "" );
    TS_ASSERT( cb.res2.GetFileName() == "" );

    cb.a = test_obj2;
    NDb::GetDbResourceCache().Reset( NDb::DBID::DBID("test2.xdb") );
    TS_ASSERT( cb.res1.GetFileName() == "test2.xdb" );
  }

  void TestChangeablePtrWithParent()
  {
    string obj_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<TestStatedObject>"
      "<_int>10</_int>"
      "<_list>"
      "  <Item>"
      "    <x>1</x>"
      "    <y>1</y>"
      "  </Item>"
      "</_list> "
      "</TestStatedObject>";
    string obj_new_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<TestStatedObject>"
      "<_int>5</_int>"
      "<_list>"
      "  <Item>"
      "    <x>10</x>"
      "    <y>10</y>"
      "  </Item>"
      "</_list> "
      "</TestStatedObject>";
    string obj2_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<TestStatedObject parent=\"/test\">"
      "<_int>20</_int>"
      "<_list>"
      "  <Item skip=1 />"
      "  <Item>"
      "    <x>2</x>"
      "    <y>2</y>"
      "  </Item>"
      "</_list> "
      "</TestStatedObject>";

    pFileSystem->SetFileWithContents( "test.xdb", obj_str );
    pFileSystem->SetFileWithContents( "test2.xdb", obj2_str );
    NDb::Ptr<NDb::TestStatedObject> test_obj = NDb::Get<NDb::TestStatedObject>( NDb::DBID::DBID("test.xdb") );
    NDb::Ptr<NDb::TestStatedObject> test_obj2 = NDb::Get<NDb::TestStatedObject>( NDb::DBID::DBID("test2.xdb") );

    NotificationCallback cb;
    cb.a = test_obj;
    cb.b = test_obj2;

    TS_ASSERT( cb.res1.IsEmpty() );
    TS_ASSERT( cb.res2.IsEmpty() );

    NDb::GetDbResourceCache().Reset( NDb::DBID::DBID("test2.xdb") );
    TS_ASSERT( cb.res1.GetFileName() == "" );
    TS_ASSERT( cb.res2.GetFileName() == "test2.xdb" );
    TS_ASSERT_EQUALS( test_obj2->_int, 20 );
    TS_ASSERT_EQUALS( test_obj2->_list.size(), 2 );
    TS_ASSERT_EQUALS( test_obj2->_list[0].x, 1 );
    TS_ASSERT_EQUALS( test_obj2->_list[1].x, 2 );
    cb.res1 = NDb::DBID();
    cb.res2 = NDb::DBID();

    pFileSystem->SetFileWithContents( "test.xdb", obj_new_str );
    NDb::GetDbResourceCache().Reset( NDb::DBID::DBID("test.xdb") );

    TS_ASSERT( cb.res1.GetFileName() == "test.xdb" );
    TS_ASSERT( cb.res2.GetFileName() == "test2.xdb" );
    TS_ASSERT_EQUALS( test_obj->_int, 5 );
    TS_ASSERT_EQUALS( test_obj2->_int, 20 );
    TS_ASSERT_EQUALS( test_obj2->_list.size(), 2 );
    TS_ASSERT_EQUALS( test_obj2->_list[0].x, 10 );
    TS_ASSERT_EQUALS( test_obj2->_list[1].x, 2 );

    test_obj2 = 0;
    test_obj = 0;
  }

  struct NotificationCallback2
  {
    NDb::ChangeablePtr<NDb::LofSimpleChild> a;
    NDb::DBID res;

    void Callback( const NDb::DBID& param )
    {
      res = param;
    }

    NotificationCallback2()
      : a( this, &NotificationCallback2::Callback )
    {}
  };

  void TestClonedPtr()
  {

    string obj_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofSimpleChild>"
        "<twin href=\"/test\" id=\"7C593133-F336-4B00-8406-055DBDC04BE9\">"
          "<LofSimpleChild>"
           "<_int>10</_int>"
          "</LofSimpleChild>"
        "</twin>"
        "<_int>1</_int>"
      "</LofSimpleChild>";
    string obj2_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofSimpleChild parent=\"/test\">"
        "<twin href=\"/test2\" id=\"900C016D-E6DB-4B64-9F34-420B1AE09F08\">"
        "<LofSimpleChild parent=\"/test:7C593133-F336-4B00-8406-055DBDC04BE9\">"
            "<_int>20</_int>"
          "</LofSimpleChild>"
        "</twin>"
        "<_int>2</_int>"
      "</LofSimpleChild>";
   
    pFileSystem->SetFileWithContents( "test.xdb", obj_str );
    pFileSystem->SetFileWithContents( "test2.xdb", obj2_str );

    NDb::ClonedPtr<NDb::LofSimpleChild> test_obj; 
    NDb::ClonedPtr<NDb::LofSimpleChild> test_obj2;

    NotificationCallback2 cb;
    cb.a = NDb::Get<NDb::LofSimpleChild>( NDb::DBID::DBID("test2.xdb") ); 
    test_obj.Clone( NDb::Get<NDb::LofSimpleChild>( NDb::DBID::DBID("test.xdb") ) );
    test_obj2.Clone( NDb::Get<NDb::LofSimpleChild>( NDb::DBID::DBID("test2.xdb") ) );

    TS_ASSERT_EQUALS( test_obj->_int, 1 );
    TS_ASSERT_EQUALS( test_obj->twin->_int, 10 );
    TS_ASSERT_EQUALS( test_obj2->_int, 2 );
    TS_ASSERT_EQUALS( test_obj2->twin->_int, 20 );

     NDb::ClonedPtr<NDb::LofSimpleInheritable> pO;
     pO.Clone( test_obj2.GetSourcePtr() );

     NDb::ClonedPtr<NDb::LofSimpleInheritable> pO2 = pO;
  }

  void TestMultipleDeserialize()
  {
    string obj_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<TestMultipleDeserialize>"
      "<_int>10</_int>"
      "</TestMultipleDeserialize>";
    pFileSystem->SetFileWithContents( "test.xdb", obj_str );
    NDb::Ptr<NDb::TestMultipleDeserialize> test_obj = NDb::Get<NDb::TestMultipleDeserialize>( NDb::DBID::DBID( "test.xdb" ) );
    TS_ASSERT_EQUALS( test_obj->_int, 10 );
  }

  void TestInheritStates()
  {
    string obj_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<TestStatedObject>"
      "<_int>10</_int>"
      "<_list>"
      "<Item>"
      "<x>1</x>"
      "<y>1</y>"
      "</Item>"
      "</_list> "
      "<states>"
      "<state name=\"A\">"
      "<_int>20</_int>"
      "</state>"
      "</states>"
      "</TestStatedObject>";
    string obj2_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<TestStatedObject parent=\"/test\">"
      "<_list>"
      "  <Item>"
      "    <x>2</x>"
      "    <y>2</y>"
      "  </Item>"
      "</_list> "
      "</TestStatedObject>";

    pFileSystem->SetFileWithContents( "test.xdb", obj_str );
    pFileSystem->SetFileWithContents( "test2.xdb", obj2_str );
    NDb::Ptr<NDb::TestStatedObject> test_obj = NDb::Get<NDb::TestStatedObject>( NDb::DBID::DBID("test.xdb") );
    NDb::Ptr<NDb::TestStatedObject> test_obj2 = NDb::Get<NDb::TestStatedObject>( NDb::DBID::DBID("test2.xdb") );
    
    TS_ASSERT_EQUALS( test_obj2->_int, 10 );
    TS_ASSERT_EQUALS( test_obj2->_list.size(), 1 );
    TS_ASSERT_EQUALS( test_obj2->_list[0].x, 2 );
    TS_ASSERT_EQUALS( test_obj2->_list[0].y, 2 );

    test_obj2.SetState( "A" );
    TS_ASSERT_EQUALS( test_obj2->_int, 20 );
    TS_ASSERT_EQUALS( test_obj2->_list.size(), 1 );
    TS_ASSERT_EQUALS( test_obj2->_list[0].x, 2 );
    TS_ASSERT_EQUALS( test_obj2->_list[0].y, 2 );
  }

  void TestStatesInDBPtr()
  {
    string obj_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<TestStatedObject>"
      "<_int>10</_int>"
      "<_list>"
      "<Item>"
      "<x>1</x>"
      "<y>1</y>"
      "</Item>"
      "</_list> "
      "<states>"
      "<state name=\"A\">"
      "<_int>20</_int>"
      "</state>"
      "</states>"
      "</TestStatedObject>";

    pFileSystem->SetFileWithContents( "test.xdb", obj_str );

    NDb::Ptr<NDb::TestStatedObject> test_obj = NDb::Get<NDb::TestStatedObject>( NDb::DBID::DBID("test.xdb") );
    NDb::Ptr<NDb::TestStatedObject> test_obj2 = NDb::Get<NDb::TestStatedObject>( NDb::DBID::DBID("test.xdb") );

    TS_ASSERT_EQUALS( test_obj->_int, 10 );
    test_obj.SetState( "A" );
    TS_ASSERT_EQUALS( test_obj->_int, 20 );
    TS_ASSERT_EQUALS( test_obj2->_int, 10 );
  }

  void TestStatesInDBPtrAssignment()
  {
    string obj_str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<TestStatedObject>"
      "<_int>10</_int>"
      "<_list>"
      "<Item>"
      "<x>1</x>"
      "<y>1</y>"
      "</Item>"
      "</_list> "
      "<states>"
      "<state name=\"A\">"
      "<_int>20</_int>"
      "</state>"
      "</states>"
      "</TestStatedObject>";

    pFileSystem->SetFileWithContents( "test.xdb", obj_str );

    NDb::Ptr<NDb::TestStatedObject> test_obj = NDb::Get<NDb::TestStatedObject>( NDb::DBID::DBID("test.xdb") );

    TS_ASSERT_EQUALS( test_obj->_int, 10 );
    test_obj.SetState( "A" );

    TS_ASSERT_EQUALS( test_obj->_int, 20 );

    NDb::Ptr<NDb::TestStatedObject> test_obj2 = test_obj;
    TS_ASSERT_EQUALS( test_obj2->_int, 20 );

    const NDb::TestStatedObject *test_obj_ptr = test_obj;
    TS_ASSERT_EQUALS( test_obj_ptr->_int, 20 );

    NDb::Ptr<NDb::TestStatedObject> test_obj3( test_obj_ptr );
    TS_ASSERT_EQUALS( test_obj3->_int, 20 );
    test_obj3.SetState( "" );
    TS_ASSERT_EQUALS( test_obj3->_int, 10 );
    TS_ASSERT_EQUALS( test_obj->_int, 20 );
  }

  void TestLoadInlined()
  {
    string str = "<?xml version=\"1.0\" encoding=\"utf-8\"?>"
      "<LofSimpleChild>"
        "<twin href=\"test\" id=\"7eb0d147-8436-49a2-b7f5-3bae3fa94c2b\">"
          "<LofSimpleChild>"
            "<_int>11</_int>"
          "</LofSimpleChild>"
        "</twin>"
        "<_int>10</_int>"
      "</LofSimpleChild>";
  
    pFileSystem->SetFileWithContents( "test.xdb", str );

    //NDb::Ptr<NDb::LofSimpleChild> obj = NDb::Get<NDb::LofSimpleChild>( NDb::DBID( "test.xdb" ) );
    //TS_ASSERT_EQUALS( obj->_int, 10 );

    //Next line causes memory leaks
   // NDb::Ptr<NDb::LofSimpleChild> obj2 = NDb::Get<NDb::LofSimpleChild>( NDb::DBID( "test.xdb", "7eb0d147-8436-49a2-b7f5-3bae3fa94c2b" ) );
    //TS_ASSERT_EQUALS( obj2->_int, 11 );
  }

};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

REGISTER_DBRESOURCE( SimpleResource );
REGISTER_DBRESOURCE( RefResource );
REGISTER_DBRESOURCE( LofSimpleInheritable );
REGISTER_DBRESOURCE( LofHardInheritable );
REGISTER_DBRESOURCE( LofComplexInheritable );
REGISTER_DBRESOURCE( LofSimpleChild );
REGISTER_DBRESOURCE( TestMultipleDeserialize );
REGISTER_DBRESOURCE( TestStatedObject );
REGISTER_DBRESOURCE( TestStatedObject2 );
