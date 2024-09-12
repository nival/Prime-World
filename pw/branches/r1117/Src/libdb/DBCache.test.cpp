//!Component('libdb/Database')
//!Component('System/FileSystem/TestFileSystem')
#include "stdafx.h"
#include <CxxTest.h>

#include "System/FileSystem/TestFileSystem.h"
#include "libdb/XmlSaver.h"
#include "libdb/DBResourceCache.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace NDb
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TestResource : public DbResource
{
	DBRESOURCE_METHODS( TestResource );
	vector<int> ints;
  NDb::Ptr<TestResource> ref;

	TestResource() {}

	virtual int GetTypeId() const { return 0; }
	virtual int operator&( IXmlSaver &saver )
	{
		saver.Add( "ints", &ints );
    saver.Add( "ref", &ref );

		return 0;
	}
	virtual DWORD CalcCheckSum() const { return 0; }
};
} //namespace NDb
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DBCacheTest : public CxxTest::TestSuite
{
  CPtr<TestFileSystem> pFileSystem;
  CPtr<NDb::DbResourceCache> pCache;
public:
  void setUpSuite()
  {
    pFileSystem = new TestFileSystem( "", true, false );
    pCache = new NDb::DbResourceCache( pFileSystem );
    NDb::SetResourceCache( pCache );
  }

  void tearDownSuite()
  {
    NDb::SetResourceCache( 0 );
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestClearOnReload()
{
  string res0 = "ï>¿<?xml version=\"1.0\" encoding=\"utf-8\"?>"
    "<TestResource>"
    "<ints>"
    "<Item>1</Item>"
    "<Item>2</Item>"
    "<Item>3</Item>"
    "</ints>"
    "</TestResource>";
  pFileSystem->SetFileWithContents( "a.xdb", res0 );
  NDb::Ptr<NDb::TestResource> pRes = NDb::Get<NDb::TestResource>( NDb::DBID( "/a.xdb" ) );
  NDb::Ptr<NDb::TestResource> pRes2 = pRes;
  TS_ASSERT( IsValid( pRes ) );
  TS_ASSERT_EQUALS( 3, pRes->ints.size() );

  string res1 = "ï>¿<?xml version=\"1.0\" encoding=\"utf-8\"?>"
    "<TestResource>"
    "<ints>"
    "<Item>1</Item>"
    "<Item>2</Item>"
    "</ints>"
    "</TestResource>";
  pFileSystem->SetFileWithContents( "a.xdb", res1 );
  pCache->Reset( NDb::DBID( "/a.xdb" ) );
  TS_ASSERT( IsValid( pRes ) );
  TS_ASSERT_EQUALS( 2, pRes->ints.size() );

  pFileSystem->SetFileWithContents( "a.xdb", string() );
  TS_ASSERT_EQUALS( 2, pRes2->ints.size() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestRemoveFromCache()
{
  string res0 = "ï>¿<?xml version=\"1.0\" encoding=\"utf-8\"?>"
    "<TestResource>"
    "<ints>"
    "<Item>1</Item>"
    "<Item>2</Item>"
    "<Item>3</Item>"
    "</ints>"
    "</TestResource>";
  pFileSystem->SetFileWithContents( "a.xdb", res0 );
  NDb::Ptr<NDb::TestResource> pRes = NDb::Get<NDb::TestResource>( NDb::DBID( "/a.xdb" ) );
  TS_ASSERT( IsValid( pRes ) );
  TS_ASSERT_EQUALS( 3, pRes->ints.size() );

  string res1 = "ï>¿<?xml version=\"1.0\" encoding=\"utf-8\"?>"
    "<TestResource>"
    "<ints>"
    "<Item>1</Item>"
    "<Item>2</Item>"
    "</ints>"
    "</TestResource>";
  pFileSystem->SetFileWithContents( "a.xdb", res1 );
  pCache->Reset( NDb::DBID( "/a.xdb" ) );
  TS_ASSERT_EQUALS( 2, pRes->ints.size() );

  pFileSystem->SetFileWithContents( "a.xdb", res0 ); // no reset
  TS_ASSERT_EQUALS( 2, pRes->ints.size() );
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void TestResetInlined()
{
  string res0 = "ï>¿<?xml version=\"1.0\" encoding=\"utf-8\"?>"
    "<TestResource>"
    "<ints>"
    "<Item>1</Item>"
    "<Item>2</Item>"
    "<Item>3</Item>"
    "</ints>"
    "<ref href=\"/a.xdb\" id=\"D47CA338-4A05-4106-A41A-6EF7215E0281\">"
      "<TestResource>"
        "<ints>"
        "<Item>4</Item>"
        "<Item>5</Item>"
        "</ints>"
      "</TestResource>"
    "</ref>"
    "</TestResource>";
  pFileSystem->SetFileWithContents( "a.xdb", res0 );
  NDb::Ptr<NDb::TestResource> pRes = NDb::Get<NDb::TestResource>( NDb::DBID( "/a.xdb" ) );
  TS_ASSERT( IsValid( pRes ) );
  TS_ASSERT_EQUALS( 3, pRes->ints.size() );
  TS_ASSERT_EQUALS(2, pRes->ref->ints.size() );


  string res1 = "ï>¿<?xml version=\"1.0\" encoding=\"utf-8\"?>"
    "<TestResource>"
    "<ints>"
    "<Item>1</Item>"
    "<Item>2</Item>"
    "<Item>3</Item>"
    "</ints>"
    "<ref href=\"/a.xdb\" id=\"D47CA338-4A05-4106-A41A-6EF7215E0281\">"
    "<TestResource>"
    "<ints>"
    "<Item>6</Item>"
    "</ints>"
    "</TestResource>"
    "</ref>"
    "</TestResource>";

  pFileSystem->SetFileWithContents( "a.xdb", res1 );
  pCache->ResetFile( "/a.xdb" );
  TS_ASSERT( IsValid( pRes ) );

  TS_ASSERT_EQUALS( 3, pRes->ints.size() );
  TS_ASSERT( IsValid( pRes->ref ) );
  TS_ASSERT_EQUALS( 1, pRes->ref->ints.size() );
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_DBRESOURCE( TestResource );
