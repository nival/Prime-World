//!Component('libdb/Database')
//!Component('System/FileSystem/TestFileSystem')
//!Component('System/Threading')
//!Component('UI/DBUI')
//!Component('Render/DBRender')


#include "stdafx.h"
#include <CxxTest.h>

#include "System/FileSystem/TestFileSystem.h"
#include "System/JobThread.h"
//#include "Render/HDRColor.h" //Required to compile "Render/DBRender.h"
#include "UI/DBUI.h" //We rely on PF.sln DB-codegen here


class DbAccessTestJob : public threading::IThreadJob, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( DbAccessTestJob, threading::IThreadJob, BaseObjectMT );

public:
  DbAccessTestJob( const string & _rootName, int _maxDepth ) : rootName( _rootName ), maxDepth( _maxDepth )
  {
  }

protected:
  virtual void Work( volatile bool & isRunning )
  {
    printf( "Running tests for '%s'...\n", rootName.c_str() );
    for ( int i = 0; i < 50; ++i )
      Check( NDb::DBID( rootName ), isRunning );
  }

  void Check( const NDb::DBID& dbid, volatile bool & isRunning )
  {
    NDb::Ptr<NDb::UILayout> ptr = NDb::Get<NDb::UILayout>( dbid );
    //Select random sublayout at specified depth
    for( int depth = maxDepth; isRunning && depth; --depth )
    {
      if ( !ptr->subLayouts.size() )
        break;
      int r = rand() % ptr->subLayouts.size();
      NDb::Ptr<NDb::UILayout> newPtr = ptr->subLayouts[r];
      ptr = 0;
      ptr = newPtr;
    }

    //Let's count layout area with some pervert method :-)
    const int runs = 1000000;
    int hits = 0;
    for ( int i = 0; isRunning && ( i < runs ); ++i )
    {
      int x = rand() % 1280;
      int y = rand() % 1024;

      if ( ( x < ptr->location.x ) || ( x >= ptr->location.x + ptr->size.x ) )
        continue;
      if ( ( y < ptr->location.y ) || ( y >= ptr->location.y + ptr->size.y ) )
        continue;
      ++hits;
    }

    float carloArea = (float)hits / (float)runs;
    float checkArea = (float)ptr->size.x * (float)ptr->size.y / ( 1280.0f * 1024.0f );

    printf( "Area of '%s' is %.3f (%.3f)\n", ptr->name.c_str(), carloArea, checkArea );
    return;
  }

private:
  DbAccessTestJob() {}

  string rootName;
  int maxDepth;
};



class MultithreadTest : public CxxTest::TestSuite
{
  CObj<TestFileSystem> fileSystem;
  vector<string> pseudoRoots;

public:
  void setUpSuite()
  {
    //We need UI resources to run on
    fileSystem = new TestFileSystem( "../../../Data/", true, true );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( fileSystem, 0 ) );

    //Setup our test entry points
    NDb::Ptr<NDb::UIRoot> root = NDb::Get<NDb::UIRoot>( NDb::DBID( "UI/UIRoot.xdb" ) );
    TS_ASSERT( !root->screens.empty() );

    const char *usedScreens[] = { "LoginScreen", "Combat", "LobbyScreen", 0 };
    for ( const char ** p = usedScreens; *p; ++p )
    {
      for ( int i = 0; i < root->screens.size(); ++i )
        if ( root->screens[i].screenId == *p )
        {
          pseudoRoots.push_back( root->screens[i].baseLayout->GetDBID().GetFileName() );
          break;
        }
    }
  }

  void tearDownSuite()
  {
    NDb::SetResourceCache( 0 );
  }
  
  void testMultipulti()
  {
    TS_ASSERT( !pseudoRoots.empty() );

    vector<StrongMT<threading::JobThread>> threads( pseudoRoots.size() );

    for ( int i = 0; i < threads.size(); ++i )
      threads[i] = new threading::JobThread( new DbAccessTestJob( pseudoRoots[0], 3 ), "DbAccessTest" );

    for ( int i = 0; i < threads.size(); ++i )
      threads[i]->Wait();
  }
};


//Linker mock
namespace Render
{
  class Texture2D : public CObjectBase 
  {
    OBJECT_BASIC_METHODS( Texture2D );
  };
  typedef CObj<Texture2D> Texture2DRef;

  Texture2DRef LoadTexture2D( NDb::Texture const & ) { return 0; }
  Texture2DRef LoadTexture2DIntoPool( NDb::Texture const &,bool,void *) { return 0; }
}

extern "C"
{
struct D3DXVECTOR3 {};
struct D3DXMATRIX {};

D3DXVECTOR3* WINAPI D3DXVec3TransformCoord( D3DXVECTOR3 *pOut, CONST D3DXVECTOR3 *pV, CONST D3DXMATRIX *pM )
{
  return 0;
}
}