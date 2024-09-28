#include "stdafx.h"
#include "libdb/DB.h"
#include "System/FilePath.h"
#include "System/FileSystem.h"
#include "System/WinFileSystem.h"

#include "System/AssertDumper.h"
#include "System/StdOutDumper.h"
#include "System/DebugTraceDumper.h"

#include "ResourceDesc.auto.h"
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float GetDps( const NDb::Hero* pHero )
{
  // Some formula getted from designers. Only they know about its magic.
  return pHero->stats.strength * pHero->stats.dexterity / 1000.f;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Perform fight between two heroes. Return 0 if heroes are equals, less that 0 if pHero2 is stronger than pHero1 and
// more than 0 overwise
int Fight( const NDb::Hero* pHero1, const NDb::Hero* pHero2 )
{
  // Verify that we have valid heroes and if no try to continue execution. No exceptions, no throws!
  NI_VERIFY( pHero1, "Invalid hero", return 0 );
  NI_VERIFY( pHero2, "Invalid hero", return 0 );

  const float dps1 = GetDps( pHero1 );
  const float dps2 = GetDps( pHero2 );

  const float timeToDie1 = pHero1->stats.health / dps2;
  const float timeToDie2 = pHero2->stats.health / dps1;

  if ( timeToDie1 < timeToDie2 )
    return 1;
  else if ( timeToDie2 < timeToDie1 )
    return -1;

  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ShowFightResults( const NDb::GameRoot* pGameRoot, const NDb::Heroes hero1, const NDb::Heroes hero2 )
{
  const NDb::Hero* pHero1 = pGameRoot->heroes[hero1];
  const NDb::Hero* pHero2 = pGameRoot->heroes[hero2];

  const int fightResult = Fight( pHero1, pHero2 );
  if ( fightResult < 0 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << pHero1->name << " is stronger than " << pHero2->name << endl;
  }
  else if ( fightResult > 0 )
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << pHero2->name << " is stronger than " << pHero1->name << endl;
  }
  else
  {
    systemLog( NLogg::LEVEL_MESSAGE ) << pHero1->name << " is equal to " << pHero2->name << endl;
  }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main( int argc, char *argv[], char *envp[] )
{
  // initialize logger with dumpers
  NLogg::CAssertDumper g_assertDumper( &GetSystemLog(), "Assert" );
  NLogg::CStdOutDumper g_stdOutDumper( &GetSystemLog(), "StdOut" );
  NLogg::CDebugTraceDumper g_debugTraceDumper( &GetSystemLog(), "DebugTrace" );

  // initialize root file system and actionDbidource system
  NFile::InitBaseDir();
	RootFileSystem::RegisterFileSystem( new WinFileSystem( NFile::GetBaseDir() + "Data", false ) );
  NDb::SetResourceCache( NDb::CreateGameResourceCache( RootFileSystem::GetRootFileSystem(), &RootFileSystem::GetChangesProcessor() ) );

  NDb::Ptr<NDb::GameRoot> pGameRoot = NDb::Get<NDb::GameRoot>( NDb::DBID( "/GameRoot" ) );
  ShowFightResults( pGameRoot, NDb::HEROES_SUPERHERO, NDb::HEROES_BATMAN ); 
  
  return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
