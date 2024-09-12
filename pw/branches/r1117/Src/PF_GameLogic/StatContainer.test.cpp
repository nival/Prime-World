//!Component("PF_GameLogic/StatContainer")

#include "stdafx.h"
#include "cxxtest/TestSuite.h"
#include "System/TestAssertDumper.h"
#include "Stat.hpp"
#include "System/SyncProcessorState.h"

#include "Mockup.test.h"


struct StatContainerTest : public CxxTest::TestSuite
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void TestValueWithModifiersBaseValueModifications()
  {
    NWorld::ValueWithModifiers value( 10.0f );
    TS_ASSERT_EQUALS( 10.0f, value.GetValue() );

    value.SetBaseValue( 11.0f );
    TS_ASSERT_EQUALS( 11.0f, value.GetValue() );
  }

  void TestValueWithModifiersAddModifier()
  {
    NWorld::ValueWithModifiers value( 10.0f );

    value.AddModifier( 1.0f, 2.0f, 1 );
    TS_ASSERT_EQUALS( 12.0f, value.GetValue() );

    value.AddModifier( 2.0f, 0.0f, 1 );
    TS_ASSERT_EQUALS( 22.0f, value.GetValue() ); // we use non user friendly formula for modifiers
  }

  void TestValueWithModifiersRemoveModifier()
  {
    NWorld::ValueWithModifiers value( 10.0f );
    value.AddModifier( 1.0f, 2.0f, 1 );
    value.AddModifier( 2.0f, 0.0f, 1 );
    int i = value.AddModifier( 3.0f, 2.0f, 2 );
    TS_ASSERT_EQUALS( 64.0f, value.GetValue() );
    
    value.RemoveModifier( i );
    TS_ASSERT_EQUALS( 22.0f, value.GetValue() );
    
    value.RemoveModifiers( 1 );
    TS_ASSERT_EQUALS( 10.0f, value.GetValue() );
  }

  void TestValueWithModifiersEnableModifier()
  {
    NWorld::ValueWithModifiers value( 10.0f );
    value.AddModifier( 1.0f, 2.0f, 1 );
    value.AddModifier( 2.0f, 0.0f, 1 );
    int i = value.AddModifier( 3.0f, 2.0f, 2 );
    
    value.EnableModifier( i, false );
    TS_ASSERT_EQUALS( 22.0f, value.GetValue() );
    value.EnableModifier( i, true );
    TS_ASSERT_EQUALS( 64.0f, value.GetValue() );
    
    value.EnableModifiers( 1, false );
    TS_ASSERT_EQUALS( 32.0f, value.GetValue() );
    value.EnableModifiers( 1, true );
    TS_ASSERT_EQUALS( 64.0f, value.GetValue() );
  }
  
  void TestValueWithModifiersUpdate()
  {
    NWorld::ValueWithModifiers value( 10.0f );

    int i = value.AddModifier( 3.0f, 2.0f, 2 );
    TS_ASSERT_EQUALS( 32.0f, value.GetValue() );

    value.UpdateModifier( i, 4.0f, 3.0f );
    TS_ASSERT_EQUALS( 43.0f, value.GetValue() );

    value.UpdateModifierAdd( i, 4.0f );
    TS_ASSERT_EQUALS( 44.0f, value.GetValue() );
  }

  void TestValueWithModifiersCache()
  {

    //Set processor state for UI
    SetProcessorState(UI_PROCESSOR_STATE);

    NWorld::ValueWithModifiers value( 10.0f );
    
    TS_ASSERT_EQUALS( 10.0f, value.GetValue() );
    TS_ASSERT_DIFFERS( true, value.IsCacheValid() );

    WORD nFPUStatus = GetProcessorState();
    SyncProcessorState();

    value.SetBaseValue(10.f);
    TS_ASSERT_EQUALS( 10.0f, value.GetValue() );
    TS_ASSERT_EQUALS( true, value.IsCacheValid() );

    SetProcessorState( nFPUStatus );

    value.SetBaseValue(11.f);
    TS_ASSERT_EQUALS( 11.0f, value.GetValue() );
    TS_ASSERT_DIFFERS( true, value.IsCacheValid() );
  }

  void TestStatValueWithModifiersCache()
  {
    //Set processor state for UI
    SetProcessorState(UI_PROCESSOR_STATE);

    NWorld::StatValueWithModifiers value( 10.0f );
    
    TS_ASSERT_EQUALS( 10.0f, value.GetValue() );
    TS_ASSERT_DIFFERS( true, value.IsCacheValid() );

    WORD nFPUStatus = GetProcessorState();
    SyncProcessorState();

    TS_ASSERT_EQUALS( 10.0f, value.GetValue() );
    TS_ASSERT_EQUALS( true, value.IsCacheValid() );

    SetProcessorState( nFPUStatus );

    value.SetValue( 11.0f );
    TS_ASSERT_DIFFERS( true, value.IsCacheValid() );

    TS_ASSERT_EQUALS( 11.0f, value.GetValue() );
    TS_ASSERT_DIFFERS( true, value.IsCacheValid() );
  }

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  NDb::UnitStat CreateStat( NDb::EStat statId, float value, float increment )
  {
    NDb::UnitStat stat;
    stat.statId = statId;
    //stat.value = value;
    //stat.increment = increment;

    return stat;
  }

  NDb::UnitStat CreateStat( NDb::EStat statId, float value, float increment, int level0, float increment0 )
  {
    NDb::UnitStat stat;
    stat.statId = statId;
    //stat.value = value;
    //stat.increment = increment;

    NDb::StatUpgrade upgrade;
    upgrade.level = level0;
    upgrade.increment = increment0;
    stat.levelUpgrades.push_back( upgrade );

    return stat;
  }

  NDb::UnitStat CreateStat( NDb::EStat statId, float value, float increment, int level0, float increment0, int level1, float increment1 )
  {
    NDb::UnitStat stat;
    stat.statId = statId;
    //stat.value = value;
    //stat.increment = increment;

    NDb::StatUpgrade upgrade;
    upgrade.level = level0;
    upgrade.increment = increment0;
    stat.levelUpgrades.push_back( upgrade );

    upgrade.level = level1;
    upgrade.increment = increment1;
    stat.levelUpgrades.push_back( upgrade );

    return stat;
  }

  CObj<TestFileSystem> fileSystem;

  Strong<NGameX::MockAdventureScreen2> mockAdventureScreen;
  CObj<NWorld::PFWorld> world;

  int stepLength;

  void setUp()
  {
    fileSystem = new TestFileSystem( "../../../Data/", true, true );
    NDb::SetResourceCache( NDb::CreateGameResourceCache( fileSystem, 0 ) );
    UI::SetUIRoot( NDb::Get<NDb::UIRoot>( NDb::DBID( "UI/UIRoot" ) ) );
    NDb::SessionRoot::InitRoot(NDb::DBID( "Session.ROOT" ));
    NDb::SoundRoot::InitRoot( NDb::DBID( "Audio/SoundRoot" ) );
    
    stepLength = DEFAULT_GAME_STEP_LENGTH;

  }

  void tearDown()
  {
    UI::SetUIRoot( 0 );
    NDb::SessionRoot::InitRoot( 0 );
    NDb::SoundRoot::InitRoot( 0 );
    NDb::SetResourceCache( 0 );
    fileSystem = 0;
  }

  void TestStatsContainerLoading()
  {
    NCore::MapStartInfo info;
		CObj<NWorld::PFWorld> world = new NWorld::PFWorld( info, 0, 0, 0, stepLength );
    CObj<NWorld::PFStatContainer> container = new NWorld::PFStatContainer( world );
    
    NDb::StatsContainer unit;
    unit.stats.push_back( CreateStat( NDb::STAT_LIFE, 1.0f, 1.0f ) );
    unit.stats.push_back( CreateStat( NDb::STAT_DEXTERITY, 2.0f, 1.0f ) );

    container->Load( &unit, &unit, 0 );
    //TS_ASSERT_EQUALS( 1.0f, container->GetValue( NDb::STAT_LIFE ) );
    //TS_ASSERT_EQUALS( 2.0f, container->GetValue( NDb::STAT_DEXTERITY ) );
    TS_ASSERT_EQUALS( 0.0f, container->GetValue( NDb::STAT_ENERGY ) );
  }

  void TestStatsContainerLoadingDefaults()
  {
    NCore::MapStartInfo info;
		CObj<NWorld::PFWorld> world = new NWorld::PFWorld( info, 0, 0, 0, stepLength );
    CObj<NWorld::PFStatContainer> container = new NWorld::PFStatContainer( world );
    
    NDb::StatsContainer unit;
    unit.stats.push_back( CreateStat( NDb::STAT_LIFE, 1.0f, 1.0f ) );
    unit.stats.push_back( CreateStat( NDb::STAT_DEXTERITY, 2.0f, 1.0f ) );
    
    NDb::StatsContainer defaults;
    defaults.stats.push_back( CreateStat( NDb::STAT_LIFE, 100.0f, 1.0f ) );
    defaults.stats.push_back( CreateStat( NDb::STAT_ENERGY, 3.0f, 1.0f ) );
    defaults.stats.push_back( CreateStat( NDb::STAT_RANGE, 4.0f, 1.0f ) );

    container->Load( &unit, &defaults, 0 );
    //TS_ASSERT_EQUALS( 1.0f, container->GetValue( NDb::STAT_LIFE ) );
    //TS_ASSERT_EQUALS( 2.0f, container->GetValue( NDb::STAT_DEXTERITY ) );
    //TS_ASSERT_EQUALS( 3.0f, container->GetValue( NDb::STAT_ENERGY ) );
    //TS_ASSERT_EQUALS( 4.0f, container->GetValue( NDb::STAT_RANGE ) );
  }

  void TestStatsContainerUpgrade()
  {
    NCore::MapStartInfo info;
		CObj<NWorld::PFWorld> world = new NWorld::PFWorld( info, 0, 0, 0, stepLength );
    CObj<NWorld::PFStatContainer> container = new NWorld::PFStatContainer( world );
    
    NDb::StatsContainer unit;
    unit.stats.push_back( CreateStat( NDb::STAT_LIFE, 1.0f, 1.0f, 5, 5.0f, 3, 2.0f ) );
    container->Load( &unit, &unit, 0 );
    
    container->Upgrade( 0, 1 ); // 0 -> 1: +0.0f
    //TS_ASSERT_EQUALS( 1.0f, container->GetValue( NDb::STAT_LIFE ) );
    
    container->Upgrade( 1, 2 ); // 1 -> 2: +0.0f; 2 -> 3: +2.0f
    //TS_ASSERT_EQUALS( 3.0f, container->GetValue( NDb::STAT_LIFE ) );
    
    container->Upgrade( 3, 3 ); // 3 -> 4: +2.0f; 4 -> 5: +5.0f; 5 -> 6: +5.0f
    //TS_ASSERT_EQUALS( 15.0f, container->GetValue( NDb::STAT_LIFE ) );
  }

  void TestStatsContainerUpgrade2()
  {
    NCore::MapStartInfo info;
		CObj<NWorld::PFWorld> world = new NWorld::PFWorld( info, 0, 0, 0, stepLength );
    CObj<NWorld::PFStatContainer> container = new NWorld::PFStatContainer( world );
    CObj<NWorld::PFStatContainer> container2 = new NWorld::PFStatContainer( world );
    
    NDb::StatsContainer unit;
    unit.stats.push_back( CreateStat( NDb::STAT_LIFE, 1.0f, 1.0f, 2, 2.0f ) );
    container->Load( &unit, &unit, 0 );
    container2->Load( &unit, &unit, 0 );
    
    container->Upgrade( 0, 1 ); // 0 -> 1: +0.0f
    container->Upgrade( 1, 1 ); // 1 -> 2: +2.0f
    //TS_ASSERT_EQUALS( 3.0f, container->GetValue( NDb::STAT_LIFE ) );

    container2->Upgrade( 0, 2 ); // 0 -> 1: +0.0f; 1 -> 2: +1.0f
    //TS_ASSERT_EQUALS( 3.0f, container->GetValue( NDb::STAT_LIFE ) );
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

};
