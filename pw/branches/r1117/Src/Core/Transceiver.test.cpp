//!Component("Core/World")
//!Component("Core/Transceiver")
//!Component("System/FileSystem/FileSystem")
//!Component("System/MainFrame")
#include "stdafx.h"
#include "WorldBase.h"
#include "Transceiver.h"
#include "WorldCommand.h"
#include "GameCommand.h"
#include "System/ChunklessSaver.h"
#include "Scheduler.h"
#include <CxxTest.h>
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static const int checkInterval = 20; // g_catchUpFactor * GAME_STEP_LENGTH
static const int stepsDelay = 2; // g_stepsDelay
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// mock objects
class MockWorld : public NCore::IWorldBase
{
  OBJECT_METHODS( 0x49763D00, MockWorld );
public:
  MockWorld() : steps( -1 ), worldTime( 0.0f ), localTime( 0.0f ) {}

  virtual void ExecuteCommand( NCore::WorldCommand* pCommand ) { commands.push_back( pCommand ); }
  virtual IPointerHolder *GetPointerSerialization() { return 0; }
  virtual bool Step(float dtInSeconds, float dtLocal)
  { 
    if ( dtInSeconds > 0 )
      ++steps;
    worldTime += dtInSeconds;
    localTime += dtLocal;
    return true;
  }

  virtual void SetAccounting( lobby::AccountingGadget* accounting ) {}
  virtual void UpdatePlayerStatuses(const NCore::TStatuses & statuses) {}
  virtual void ExecuteCommands(const NCore::TPackedCommands & commands) {}

  virtual void CreateCRCPoint(char const *) {;}  //do nothing by default
  
  virtual void DumpObjectsNames(char const * fileName) const {}

  virtual void SetSlowdownHint( float hintValue ) {}
  virtual float GetSlowdownHint() const { return 0.0f; }

  virtual void SetPause( bool paused, int playerId ) {}
  virtual bool IsPaused() const { return false; }
  virtual int GetStepNumber() const { return steps; }
  virtual void Save(void) const {}
  virtual void Load(void) {}
  virtual void CalcCRC( IBinSaver& f, bool fast ) {}

  const vector<CObj<NCore::WorldCommand>>& GetCommands() const { return commands; }
  template<typename T>
  const T* GetCommand( int index ) const
  {
    if ( index < 0 || index >= commands.size() )
      return 0;

    CDynamicCast<T> result = commands[index];
    return result;
  }
private:
  vector<CObj<NCore::WorldCommand>> commands;
  int steps;
  float worldTime;
  float localTime;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MockCommandScheduler : public NCore::ICommandScheduler, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( MockCommandScheduler, ICommandScheduler, BaseObjectMT );

public:
  MockCommandScheduler() : infiniteSegments( false ), step( 0 ) { }
  MockCommandScheduler( bool _infiniteSegments ) : infiniteSegments( _infiniteSegments ), step( 0 )
  {
    if ( infiniteSegments )
      PushSegment( 0 );
  }

  virtual void SendMessage( CObjectBase *pMsg ) { }

  virtual CObj<NCore::SyncSegment> GetSyncSegment()
  {
    CObj<NCore::SyncSegment> result = segments.front();
    segments.pop_front();
    if ( infiniteSegments && segments.empty() )
      PushSegment( 0 );
    return result;
  }
  virtual int GetNextStep( bool warnIfNoSegments ) const { return segments.empty() ? -1 : segments.back()->step; }

  virtual void SendCRC( int step, DWORD crcValue ) { }
  virtual int GetAsyncStep() const { return  -1; }

  virtual bool IsAllClientsReady() { return true; }

  virtual void Step( float dt ) { }

  virtual int GetMyClientID() const { return 0; }

  virtual void Reinit( NCore::IServerNode * _server, NCore::ISessionRunner * _asyncProcessor ) {}
  virtual void SendCrcData( int step, unsigned char * data, int size) {}
  virtual int GetAsyncStep() { return -1; }
  virtual int GetLastConfirmedStep() { return step; }
  virtual int PopCrcRequestStep() { return step; }
  virtual const NCore::StepsDelaySettings& GetStepsDelaySettings() 
  { 
    static NCore::StepsDelaySettings s;
    return s; 
  }
  virtual bool IsCrcDataEnabled() { return true; }

  void PushSegment( NCore::WorldCommand* _command )
  {
    CObj<NCore::WorldCommand> command = _command;
    CObj<NCore::SyncSegment> segment = new NCore::SyncSegment( step );
    if ( IsValid( command ) )
      segment->commands.push_back( new NCore::PackedWorldCommand( command, 0, 0, 0 ) );
    segments.push_back( segment );
    ++step;
  }

private:
  list<CObj<NCore::SyncSegment>> segments;
  bool infiniteSegments;
  int step;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
DEFINE_1_PARAM_CMD( 0x49763D02, MockCommand1, int, index );
void MockCommand1::Execute( NCore::IWorldBase* world )
{
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct TransceiverTest : public CxxTest::TestSuite
{
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void TestTransciverCreation()
  {
    StrongMT<MockCommandScheduler> scheduler = new MockCommandScheduler();
    CObj<MockWorld> world = new MockWorld();
    
    Strong<NCore::Transceiver> transceiver = new NCore::Transceiver( scheduler );
    transceiver->SetWorld( world /*, new MockCommand1( 123 )*/ );
    TS_ASSERT_EQUALS( 0, world->GetCommands().size() );

    scheduler->PushSegment( new MockCommand1( 123 ) );
    transceiver->Step( 100 );
    transceiver->Step( 100 );
    transceiver->Step( 100 );

    TS_ASSERT_EQUALS( 0, world->GetCommands().size() );
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transciver has enougt segments to process, so first it delayes for two segments that process every segments in 100ms
  void TestInitialDelay()
  {
    StrongMT<MockCommandScheduler> scheduler = new MockCommandScheduler( false );
    CObj<MockWorld> world = new MockWorld();
    
    Strong<NCore::Transceiver> transceiver = new NCore::Transceiver( scheduler );
    transceiver->SetWorld( world /*, new MockCommand1( 1 )*/ );

    for( int i = 0; i < stepsDelay; ++i )
      scheduler->PushSegment( new MockCommand1( 1 ) );

    for( int i = 0; i < 10; ++i )  
    {
      scheduler->PushSegment( new MockCommand1( 1 ) );
      transceiver->Step( 100 );
      TS_ASSERT_EQUALS( i, world->GetStepNumber() );
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// transciver should get steps form queue
  void TestGettingDelayed()
  {
    StrongMT<MockCommandScheduler> scheduler = new MockCommandScheduler( false );
    CObj<MockWorld> world = new MockWorld();
    
    Strong<NCore::Transceiver> transceiver = new NCore::Transceiver( scheduler );
    transceiver->SetWorld( world /*, new MockCommand1( 1 )*/ );

    for( int i = 0; i < stepsDelay; ++i )
      scheduler->PushSegment( new MockCommand1( 1 ) );

    for( int i = 0; i < 10; ++i )  
    {
      scheduler->PushSegment( new MockCommand1( 1 ) );
      transceiver->Step( 100 );
      TS_ASSERT_EQUALS( i, world->GetStepNumber() );
    }

    for( int i = 0; i < stepsDelay; ++i )
    {
      transceiver->Step( 100 );
      TS_ASSERT_EQUALS( 10, world->GetStepNumber() );
    }
    transceiver->Step( 100 );
    TS_ASSERT_EQUALS( 10 + stepsDelay - 1, world->GetStepNumber() );
    
    for( int i = 0; i < stepsDelay - 1; ++i )
    {
      scheduler->PushSegment( new MockCommand1( 1 ) );
      transceiver->Step( checkInterval );
      TS_ASSERT_EQUALS( 10 + stepsDelay - 1, world->GetStepNumber() );
    }

    for( int i = 0; i < 10; ++i )
    {
      scheduler->PushSegment( new MockCommand1( 1 ) );
      transceiver->Step( 100 );
      TS_ASSERT_EQUALS( 10 + stepsDelay + i, world->GetStepNumber() );
    }
  }
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  void TestComplexFastComputer()
  {
    StrongMT<MockCommandScheduler> scheduler = new MockCommandScheduler( false );
    CObj<MockWorld> world = new MockWorld();
    Strong<NCore::Transceiver> transceiver = new NCore::Transceiver( scheduler );
    transceiver->SetWorld( world /*, new MockCommand1( 1 )*/ );

    //scheduler->PushSegment();
    //transceiver->Step( 100 );

  }
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
REGISTER_SAVELOAD_CLASS( MockWorld );
NI_DEFINE_REFCOUNT( MockCommandScheduler )
REGISTER_SAVELOAD_CLASS( MockCommand1 );