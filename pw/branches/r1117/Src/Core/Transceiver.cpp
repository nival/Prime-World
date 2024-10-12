#include "stdafx.h"
#include "Transceiver.h"

#include "System/LogFileName.h"
#include "System/FileSystem/FileUtils.h"
#include "System/InlineProfiler.h"
#include "System/MainFrame.h"

#include "WorldBase.h"
#include "GameCommand.h"
#include "WorldCommand.h"
#include "Replay.h"
#include "System/FileSystem/TinyFileWriteStream.h"
#include "RemoteCommandScheduler.h"
#include "System/SyncProcessorState.h"


namespace CrcMode
{
  enum Enum
  {
    Disabled = 0,
    Fast = 1,
    Full = 2,
  };
};


namespace
{
  const float g_catchUpFactor = 0.2f;
  const float g_slowDownFactor = 1.1f;
  const int g_buffersCount = 10;
  int g_bufferSize = 20 * 1024 * 1024;
#ifdef _SHIPPING
  DEV_VAR_STATIC int g_crcMode = CrcMode::Fast;
  DEV_VAR_STATIC int g_processCrcRequests = true;
#else
  DEV_VAR_STATIC int g_crcMode = CrcMode::Full;
  DEV_VAR_STATIC int g_processCrcRequests = false;
#endif
  bool g_disableWorld = false;
  bool g_dumpCrc = false;
  bool g_skipDelyaedSteps = false;
  bool g_logTransceiverSteps = false;
  int g_logSegmentsInterval = 300;
  static bool g_calcCrcInSeparateThread = true;
  static bool g_saveWorldRequested = false;
  static bool g_loadWorldRequested = false;
  static bool g_saveLoadWorldDumpCRC = false;

  static bool g_dumpCrcTimerEnabled = false;
  static int  g_dumpCrcTimer = 0;

  static bool g_fillBufferAfterLag = false;
  static bool g_enableAdaptiveBuffer = true;

  static int g_needCrcStats = 0;
  REGISTER_DEV_VAR( "need_crc_stats", g_needCrcStats, STORAGE_NONE );

  bool DumpCrc( const char *name, const vector<wstring> &params )
  {
    g_dumpCrc = true;
    return true;
  }

  bool SkipDelayedSteps( const char *name, const vector<wstring> &params )
  {
    g_skipDelyaedSteps = true;
    return true;
  }
}


namespace NCore
{

CrcStatsCollector::TypeStats& CrcStatsCollector::GetSliceData( const char* key )
{
  vector<TypeStats>& vecStats = stats[key];

  if ( vecStats.empty() )
    vecStats.reserve( 1000 );

  if ( vecStats.size() < slices )
    vecStats.resize( slices );

  return vecStats.back();
}

void CrcStatsCollector::OnStartObject()
{
  curObjects.push_back( curObject );
  curObject = newObject;

  GetSliceData(curObject->GetObjectTypeName()).Add( sizeof(Record<StartObject>), true );
}

void CrcStatsCollector::OnFinishObject( CObjectBase* object )
{
  GetSliceData(curObject->GetObjectTypeName()).Add( sizeof(Record<FinishObject>) );

  curObject = curObjects.back();
  curObjects.pop_back();
}

void CrcStatsCollector::OnStorePointer( const IBinSaver::chunk_id idChunk, CObjectBase* object )
{
  newObject = object;

  if ( curObject == 0 )
    curObject = object;

  GetSliceData(curObject->GetObjectTypeName()).Add( sizeof(Record<Pointer>) );
}

void CrcStatsCollector::OnDataChunk( const IBinSaver::chunk_id idChunk, const void* pData, int nSize )
{
  GetSliceData(curObject->GetObjectTypeName()).Add( sizeof(Record<Data>) );
}

bool CrcStatsCollector::OnStartChunk( const IBinSaver::chunk_id idChunk, int chunkType )
{
  GetSliceData(curObject->GetObjectTypeName()).Add( sizeof(Record<StartChunk>) );

  return true;
}

void CrcStatsCollector::OnFinishChunk()
{
  GetSliceData(curObject->GetObjectTypeName()).Add( sizeof(Record<FinishChunk>) );
}

const CrcStatsCollector::TTypeStatsMap& CrcStatsCollector::GetStatsData() const { return stats; }


Transceiver::Transceiver(ICommandScheduler *_scheduler, 
                         int _stepLength /*= DEFAULT_GAME_STEP_LENGTH*/, 
                         bool writeReplay /*= true*/ ) :
  scheduler( _scheduler), 
  asyncState( false ), 
  localTimeElapsed( 0 ), 
  worldTimeElapsed( 0 ), 
  delaySteps( true ),
  checkTime( g_catchUpFactor * _stepLength ),
  nextStep( 0 ),
  precalcCrcOnce( false ),
  slowDownFactor(1.0f),
  noData(false),
  stepLength(_stepLength),
  pmsc(),
  lastProtectionMagicAsyncStep(INVALID_STEP)
{
  NI_SYNC_FPU_START;
  stepLengthInSeconds = _stepLength/1000.0f;
  NI_SYNC_FPU_END;

  stepsBufferLimit.Init(scheduler->GetStepsDelaySettings(), stepLength);

  bool crcDataEnabled;
#ifndef _SHIPPING
  if (writeReplay)
  {
    string fileName = NDebug::GenerateDebugFileName( "replay", "rpl" );
    replay = new ReplayStorage( REPLAY_BUFFER_WRITE, fileName.c_str() );
  }
  crcDataEnabled = true;
#else
  crcDataEnabled = scheduler->IsCrcDataEnabled();
#endif

  crcCalc.CreateCalculator(crcDataEnabled);
}



void Transceiver::Reinit( ICommandScheduler * scheduler )
{
  MessageTrace( "Re-initializing Transceiver, scheduler=%08x", (void*)scheduler );

  //TODO
}



TransceiverCrcCalculator::TransceiverCrcCalculator():
  bufferSize( 16*1024 ),
  crcDataEnabled(false)
{
#ifndef _SHIPPING
  for (int i = 0; i < g_buffersCount; ++i)
  {
    crcBuffersCache.push_back(new Buffer())->Allocate( g_bufferSize );
  }
#endif // _SHIPPING

  threadWithTask.FakeInvoke();
}



TransceiverCrcCalculator::~TransceiverCrcCalculator()
{
  while (crcBuffers.size() > 0)
  {
    delete crcBuffers.back();
    crcBuffers.pop_back();
  }
  while (crcBuffersCache.size() > 0)
  {
    delete crcBuffersCache.back();
    crcBuffersCache.pop_back();
  }
}



void TransceiverCrcCalculator::CreateCalculator(bool _crcDataEnabled)
{
  crcDataEnabled = _crcDataEnabled;
  if (crcDataEnabled)
  {
    crcCalculator = new Crc32Calculator<BinStatsCollector>();
  }
  else
  {
    crcCalculator = new Crc32Calculator<NullStatsCollector>();
  }
}


Transceiver::~Transceiver()
{
  if ( crcCalc.IsBusy() )
  {
    crcCalc.Sync();
    NI_ASSERT( !crcCalc.IsBusy(), "Thread not dead" );
  }

#ifndef _SHIPPING
  if ( g_needCrcStats )
  {
    string outputFileName = NDebug::GenerateDebugFileName( NStr::StrFmt( "crc-objects-size" ), "csv" );

    CObj<Stream> crcStatsFile = new FileWriteStream( outputFileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
    NI_ASSERT( crcStatsFile->IsOk(), "Failed to open output file!" );

    if ( crcStatsFile->IsOk() )
    {
      CrcStatsCollector& statsCollector = static_cast<CrcStatsCollector&>(crcStatCalc.GetStatsCollector());

      const CrcStatsCollector::TTypeStatsMap& statsData = statsCollector.GetStatsData();

      crcStatsFile->WriteString( "objects count;" );

      for( CrcStatsCollector::TTypeStatsMap::const_iterator it = statsData.begin(); it != statsData.end(); ++it )
      {
        string header( NI_STRFMT( "%s;", it->first.c_str() ) );
        crcStatsFile->WriteString( header );
      }
      crcStatsFile->WriteString( "\n" );

      for ( int i = 0; i < statsCollector.GetSliceCount(); ++i )
      {
        string header( NI_STRFMT( "%d;", i * g_needCrcStats ) );
        crcStatsFile->WriteString( header );

        for( CrcStatsCollector::TTypeStatsMap::const_iterator it = statsData.begin(); it != statsData.end(); ++it )
        {
          const vector<CrcStatsCollector::TypeStats>& vecStats = it->second;

          string val( NI_STRFMT( "%d;", i < vecStats.size() ? vecStats[i].objects : 0 ) );
          crcStatsFile->WriteString( val );
        }
        crcStatsFile->WriteString( "\n" );
      }

      crcStatsFile->WriteString( "sizes\n" );

      for ( int i = 0; i < statsCollector.GetSliceCount(); ++i )
      {
        string header( NI_STRFMT( "%d;", i * g_needCrcStats ) );
        crcStatsFile->WriteString( header );

        for( CrcStatsCollector::TTypeStatsMap::const_iterator it = statsData.begin(); it != statsData.end(); ++it )
        {
          const vector<CrcStatsCollector::TypeStats>& vecStats = it->second;

          string val( NI_STRFMT( "%d;", i < vecStats.size() ? vecStats[i].size : 0 ) );
          crcStatsFile->WriteString( val );
        }
        crcStatsFile->WriteString( "\n" );
      }
    }
  }
#endif

}


void Transceiver::ProcessSegment( float localTime )
{
  NI_PROFILE_FUNCTION

  ReplaySegment replaySegment;
  replaySegment.deltaTime = stepLengthInSeconds;
  CObj<SyncSegment> segment = scheduler->GetSyncSegment();

  if (g_loadWorldRequested)
  {
    DebugTrace( "Load world was requested" );
    if (!g_saveLoadWorldDumpCRC || !g_dumpCrcTimerEnabled)
    {
      DebugTrace( "Start CRC calculation after world loading..." );
      crcCalc.StartCalcCRCSync( 0, world );
    }
    if (g_saveLoadWorldDumpCRC && !g_dumpCrcTimerEnabled)
    {
      DebugTrace( "Start CRC dump timer after world loading..." );
      g_dumpCrcTimerEnabled = true;
      g_dumpCrcTimer = 1;
    }
    g_loadWorldRequested = false;
  }

  nextStep = segment->step;

  if (g_logSegmentsInterval && !(nextStep % g_logSegmentsInterval))
  {
    DebugTrace( "Segment step: %d (%d commands)", nextStep, segment->commands.size() );
  }

  TransceiverCrcCalculator::CRCResult crcResult;

  {
    NI_PROFILE_BLOCK( "Wait for crc calc thread" );
    crcResult = crcCalc.WaitForCrcResult();
  }

  if (crcResult.IsValid())
  {
    scheduler->SendCRC( crcResult.step, crcResult.crc );
  }
  else
  {
    DebugTrace( "Start segment step: %d (%d commands)", nextStep, segment->commands.size() );
  }

  if ( !g_disableWorld )
  {
    if (g_dumpCrcTimerEnabled)
    {
      // Ignore commands for clean timered CRC dump if needed and set step number to 
      // timer's value, so we will get dump of 0 to N step, where N is a number of CRC buffers
      segment->step = g_dumpCrcTimer;
    }
    else
    {
      world->ExecuteCommands(segment->commands);

      replaySegment.seg = segment->commands;
    }

    world->UpdatePlayerStatuses(segment->statuses);

    world->Step( stepLengthInSeconds, localTime );

#ifndef _SHIPPING
    if ( g_needCrcStats > 0 && ( world->GetStepNumber() % g_needCrcStats == 0 ) )
    {
      CPtr<IWorldBase> pTmp(world);
      crcStatCalc.Calculate( &pTmp, true );
    }
#endif
  }

  if (g_saveWorldRequested)
  {
    DebugTrace( "Save world was requested" );
    if (!g_saveLoadWorldDumpCRC || !g_dumpCrcTimerEnabled)
    {
      DebugTrace( "Start world saving to file..." );
      world->Save();
    }
    if (g_saveLoadWorldDumpCRC && !g_dumpCrcTimerEnabled)
    {
      DebugTrace( "Start CRC dump timer after world saving..." );
      g_dumpCrcTimerEnabled = true;
      g_dumpCrcTimer = 0;
      segment->step = 0;
    }
    g_saveWorldRequested = false;
  }

  if( g_calcCrcInSeparateThread )
    crcCalc.StartCalcCRCAsync( segment->step, world );
  else
    crcCalc.StartCalcCRCSync( segment->step, world );
 
  replaySegment.crc = crcResult.crc;
  
  if (replay)
    replay->WriteSegment( replaySegment );
}



static int g_showCrcSize;
REGISTER_DEV_VAR( "show_crc_size", g_showCrcSize, STORAGE_NONE );


static int g_dumpCrcStats = 0;
REGISTER_DEV_VAR( "dump_full_crc_stats", g_dumpCrcStats, STORAGE_NONE );



struct CalcCrcTimeDebugVar: public NDebug::BaseDebugVar
{
public:  
  explicit CalcCrcTimeDebugVar( const char *name ): 
    BaseDebugVar( name, false ), time(), tickCounts(), dataLength() {}
     
  virtual bool IsWarning() const { return false; }
  
  virtual int FormatValue( wchar_t *pBuffer, const int bufferLen ) const 
  {
    return NStr::SWPrintf( pBuffer, bufferLen, L"%.2f, %d; %d", time, tickCounts, dataLength ); 
  }
  
  void Set( float _time, int _tickCounts, int _dataLength )
  {
    time = _time;
    tickCounts = _tickCounts;
    dataLength = _dataLength;
  }

private:
  float time;
  int tickCounts;
  int dataLength;
};



static CalcCrcTimeDebugVar g_calcCrcTimeDebugVar( "calc_crc_time" );

class CrcTimeUpdater
{
public:
  CrcTimeUpdater() 
  {
    NHPTimer::GetTime(startTime);
  }
  
  ~CrcTimeUpdater()
  {
    NHPTimer::STime curTime;
    NHPTimer::GetTime(curTime);
    
    deltaTime += curTime - startTime;
    ++tickCount;
    
    const int writePeriod = 15;
    
    if( tickCount % writePeriod == 0 )
    {
      g_calcCrcTimeDebugVar.Set( 
        float(deltaTime) * 1000 / writePeriod / NHPTimer::GetTimerFrequency(),
        tickCount,
        dataLength
      );
      deltaTime = 0;
    }
  }

private:
  NHPTimer::STime startTime;
  static NHPTimer::STime deltaTime;
  static int tickCount;

public:
  static int dataLength; 
};

NHPTimer::STime CrcTimeUpdater::deltaTime = 0;
int CrcTimeUpdater::tickCount = 0;
int CrcTimeUpdater::dataLength = 0;



void TransceiverCrcCalculator::StartCalcCRCAsync( int step, CObj<IWorldBase> world )
{
  CalcCRCTask task;
  
  task.pThis = this;
  task.step = step;
  task.world = world;
  
  threadWithTask.BeginInvoke( task );
}



void TransceiverCrcCalculator::StartCalcCRCSync( int step, CObj<IWorldBase> world )
{
  CalcCRCTask task;
  
  task.pThis = this;
  task.step = step;
  task.world = world;
  
  threadWithTask.SyncInvoke( task );
}



unsigned long TransceiverCrcCalculator::CalcCRCImpl( int step, CObj<IWorldBase> world )
{ 
  NI_PROFILE_FUNCTION;
  
  CrcTimeUpdater crcTimeUpdater;

  if ( g_crcMode == CrcMode::Disabled || g_disableWorld )
    return 0;

  if (crcDataEnabled)
  {
    if (crcBuffersCache.size() > 0)
    {
      crcBuffers.push_front(crcBuffersCache.front());
      crcBuffersCache.pop_front();
    }
    else
    {
      crcBuffers.push_front(new Buffer())->Allocate(bufferSize);
    }
    Buffer * currentBuffer = crcBuffers.front();
    crcCalculator->GetStatsCollector().Init( currentBuffer->buffer, currentBuffer->size, step );
  }
  
  crcCalculator->BeginCalculate( true );
  
  if( g_dumpCrcStats )
    crcCalculator->StartStatisticsGathering();
  
  world->CalcCRC( *crcCalculator.GetPtr(), g_crcMode == CrcMode::Fast );
  const unsigned int curCrcValue =  crcCalculator->EndCalculate();

  if (crcDataEnabled)
  {
    Buffer * currentBuffer = crcBuffers.front();
    BinStatsCollector::setCrcToBuffer( currentBuffer->buffer, curCrcValue );
    currentBuffer->length = crcCalculator->GetStatsCollector().GetLength();
    bufferSize = currentBuffer->length;
    CrcTimeUpdater::dataLength = crcCalculator->GetStatsCollector().GetLength();
  }

  if( g_showCrcSize )
  {
    DebugTrace( "Total bytes used for crc calc: %u", crcCalculator->GetBytesHashed() );
    g_showCrcSize = 0;
  }

  if( g_dumpCrcStats )
  {
    crcCalculator->DumpStatistics();
    g_dumpCrcStats = 0;
  }

  return curCrcValue;
}



void TransceiverCrcCalculator::DumpCrc( int step )
{
  threadWithTask.Sync();

  int crc = 0;

  for (nstl::list<Buffer*>::iterator it = crcBuffers.begin(); it != crcBuffers.end(); ++it)
  {
    if ( BinStatsCollector::getStepFromBuffer( (*it)->buffer ) == step )
      crc = BinStatsCollector::getCrcFromBuffer( (*it)->buffer );
  }

  CObj<Stream> file = new TinyFileWriteStream( NDebug::GenerateDebugFileName( NStr::StrFmt( "crc-%d-0x%08X", step, crc ), "bin" ) );

  for (nstl::list<Buffer*>::iterator it = crcBuffers.begin(); it != crcBuffers.end(); ++it)
  {
    BinStatsCollector::writeToFile( (*it)->buffer, (*it)->length, *file );
  }
}



void TransceiverCrcCalculator::UpdateBuffers(int lastConfirmedStep)
{
  if (crcDataEnabled)
  {
    if (g_processCrcRequests)
    {
      while (crcBuffers.size() > 0 && BinStatsCollector::getStepFromBuffer( crcBuffers.back()->buffer ) <= lastConfirmedStep)
      {
        crcBuffersCache.push_back(crcBuffers.back());
        crcBuffers.pop_back();
      }
    }
    else
    {
      if (crcBuffersCache.size() == 0 && crcBuffers.size() > 0)
      {
        crcBuffersCache.push_back(crcBuffers.back());
        crcBuffers.pop_back();
      }
    }
  }
}



TransceiverCrcCalculator::Buffer * TransceiverCrcCalculator::GetBuffer(int step, Stream & stream)
{
  for (nstl::list<Buffer*>::iterator it = crcBuffers.begin(); it != crcBuffers.end(); ++it)
  {
    if ( BinStatsCollector::getStepFromBuffer( (*it)->buffer ) == step )
    {
      BinStatsCollector::writeToFile( (*it)->buffer, (*it)->length, stream );
      return *it;
    }
  }
  return 0;
}

bool Transceiver::CanProcessStep()
{
  const int schedulerStep = scheduler->GetNextStep( worldTimeElapsed >= stepLength );
  // no steps to preceed
  if ( schedulerStep < 0 )
  {
    if ( worldTimeElapsed >= stepLength )
    {
      noData = true;
      worldTimeElapsed = stepLength;
      delaySteps = g_fillBufferAfterLag;
    }
    if (localTimeElapsed >= stepLength)
    {
      stepsBufferLimit.AdjustByLag(localTimeElapsed, nextStep);
    }
    return false;
  }
  else
  {
    noData = false;
  }

  const int stepsDelayed = schedulerStep - nextStep;
  bool canProcessStep = false;
  const int currentBufferLimit = stepsBufferLimit.GetValue();

  slowDownFactor = 1.0f;
  if ( stepsDelayed > currentBufferLimit )
  {
    delaySteps = false;
    if ( checkTime == 0 || worldTimeElapsed >= stepLength )
      canProcessStep = true;
  }
  else if ( stepsDelayed <= currentBufferLimit )
  {
    slowDownFactor = g_slowDownFactor;
  }

  // stepLength passed 
  if ( worldTimeElapsed >= slowDownFactor * stepLength && ( stepsDelayed == currentBufferLimit || !delaySteps ) )
    canProcessStep = true;

  if (canProcessStep)
  {
    stepsBufferLimit.Update( nextStep );
  }

  return canProcessStep;
}



void Transceiver::SkipDelayedStepd()
{
  while ( scheduler->GetNextStep( false ) - nextStep > stepsBufferLimit.GetValue() )
  {
    CObj<SyncSegment> segment = scheduler->GetSyncSegment();
    scheduler->SendCRC( segment->step, 0 );
    nextStep = segment->step;
  }
}



void Transceiver::ProcessProtectionMagic()
{
  NI_VERIFY(!!world, "World must be set!", return);

  if (pmsc.NeedUpdate())
  {
    const int startedStep = scheduler->GetStartedStep();

    if (startedStep < 0)
      return;

    const int serverStep = nextStep;
    const int worldStep = world->GetStepNumber();

    if (!pmsc.Update(serverStep, worldStep))
      return;

    NI_ASSERT(nextStep == startedStep, "Invariant");

    {
      int offset = 0;
      int frequency = scheduler->GetProtectionMagicConfirmFrequency();

      if (frequency > 0)
      {
        if (int r = pmsc.Calculate(0) % frequency)
          offset = frequency - r;
      }

      world->SetProtectionUpdateFrequency(offset, frequency);
    }

    DevTrace("P: step number calculator updated (serverStep=%d, worldStep=%d)", pmsc.serverStep, pmsc.worldStep);
  }

#ifndef _SHIPPING
  if (!world->HasProtection())
  {
    const int step = pmsc.Calculate(world->GetStepNumber());

    if (step < 0)
    {
    }
    else
    {
      scheduler->SendProtectionMagic(step, 0U);
    }

    return;
  }
#endif

  NCore::ProtectionResult pr;

  if (world->PollProtectionResult(pr))
  {
    const int step = pmsc.Calculate(pr.step);

    if (step < 0)
    {
      WarningTrace("P: invalid step number");
    }
    else
    {
      scheduler->SendProtectionMagic(step, pr.magic);
    }
  }
}



void Transceiver::Step( float dt )
{
  NI_PROFILE_FUNCTION

  if ( !delaySteps )
    worldTimeElapsed += dt;
  localTimeElapsed += dt;
  if ( checkTime > dt )
    checkTime -= dt;
  else if ( checkTime > 0 )
    checkTime = 0;

  if ( g_skipDelyaedSteps )
  {
    SkipDelayedStepd();
    g_skipDelyaedSteps = false;
  }

  if (g_processCrcRequests)
  {
    const int crcRequestStep = scheduler->PopCrcRequestStep();
    if (crcRequestStep != INVALID_STEP)
    {
      CObj<Stream> stream = new MemoryStream();
      if (TransceiverCrcCalculator::Buffer * buffer = crcCalc.GetBuffer(crcRequestStep, *stream))
      {
        scheduler->SendCrcData( crcRequestStep, (unsigned char*)stream->GetBuffer(), stream->GetPosition() );
      }
    }
  }

  crcCalc.UpdateBuffers( scheduler->GetLastConfirmedStep() );

  const bool canProcessStep = CanProcessStep();
  if ( g_logTransceiverSteps )
  {
    const int schedulerStep = scheduler->GetNextStep( worldTimeElapsed >= stepLength );
    const int stepsDelayed = schedulerStep - nextStep;
    systemLog(NLogg::LEVEL_MESSAGE) << 
      "transceiver: Start (time = "<< NHPTimer::GetScalarTime() << 
      " canProcessStep = " << canProcessStep << ( worldTimeElapsed >= stepLength && !canProcessStep ? "LAGS" : "" ) <<
      " worldTimeElapsed = " << worldTimeElapsed << 
      " checkTime = " << checkTime << 
      " delaySteps = " << delaySteps << 
      " stepsDelayed = " << schedulerStep << " - " << nextStep << " = " << stepsDelayed <<
      ")" << endl;
  }

  if (world)
  {
    ProcessProtectionMagic();
  }

  if ( canProcessStep )
  {
    if (precalcCrcOnce)
    {
      crcCalc.StartCalcCRCSync( nextStep, world );
      precalcCrcOnce = false;
    }

    float localTime = 0;
    if ( localTimeElapsed >= stepLength )
    {
      localTime = stepLengthInSeconds;
      localTimeElapsed -= stepLength;
    }

    ProcessSegment( localTime );
    worldTimeElapsed = Max( worldTimeElapsed - slowDownFactor * stepLength, 0.0f );
    checkTime = g_catchUpFactor * stepLength;

    if (g_dumpCrcTimerEnabled)
    {
      ++g_dumpCrcTimer;
      if (g_dumpCrcTimer == g_buffersCount)
        g_dumpCrc = true;
    }
  }

  /* Seems to be obsolete. Used for local world.
  if ( localTimeElapsed > stepLength * ( 1 + g_catchUpFactor ) )
  {
    world->Step( 0.0f, stepLengthInSeconds );
    localTimeElapsed -= stepLength;
  }*/

  const int asyncStep = scheduler->GetAsyncStep();
  if ( !asyncState && asyncStep >= 10 )
  {
    crcCalc.DumpCrc( asyncStep );
#if 0
    throw "Async detected";
#else
    NI_ALWAYS_ASSERT( NStr::StrFmt( "Async detected at step %d", asyncStep ) );
#endif
  }

  const int protectionMagicAsyncStep = scheduler->GetProtectionAsyncStep();
  if (lastProtectionMagicAsyncStep < protectionMagicAsyncStep)
  {
    lastProtectionMagicAsyncStep = protectionMagicAsyncStep;

    ErrorTrace("P: Async detected at step %d", protectionMagicAsyncStep);

#ifndef _SHIPPING
    NI_ALWAYS_ASSERT(NStr::StrFmt("Protection magic async detected at step %d", protectionMagicAsyncStep));
#endif
  }

  if ( asyncState && NGlobal::GetVar( "exit_on_finish", 0 ).GetFloat() != 0 )
    NMainFrame::Exit();
  asyncState = asyncStep >= 0;

  if ( g_dumpCrc )
  {
    DebugTrace( "Start CRC dump to file..." );

    if (g_dumpCrcTimerEnabled)
      crcCalc.DumpCrc( g_buffersCount - 1 );
    else
      crcCalc.DumpCrc( nextStep - 1 );

    g_dumpCrcTimerEnabled = false;
    g_dumpCrc = false;
  }
}



int Transceiver::GetWorldStep() const
{
  return world ? world->GetStepNumber() : 0;
}



void Transceiver::SendCommand( WorldCommand *_command, bool isPlayerCommand )
{
  CObj<WorldCommand> command = _command;
  if ( asyncState || !scheduler->IsAllClientsReady() )
    return;
  PackedWorldCommand * packedCommand = new PackedWorldCommand( command, ptrHolder, scheduler->GetMyClientID(), GetTickCount() );
  scheduler->SendMessage( packedCommand, isPlayerCommand );
}



void Transceiver::SetWorld( IWorldBase * _world )
{
  //FIXME: Мы исполняем первую команду в ручном режиме, так как она является своего рода хидером для реплея
  world = _world;
  ptrHolder = world->GetPointerSerialization();
}



void Transceiver::RecordMapStart( const MapStartInfo & info )
{
  if (replay)
    replay->WriteHeader( info );
}



bool Transceiver::IsPaused() const
{
  return world->IsPaused();
}

int Transceiver::GetBufferLimit() const
{
  return stepsBufferLimit.GetValue();
}
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

void StepsBufferLimit::Init( const StepsDelaySettings& settings, int _stepLength )
{
  bufferLimitSettings = settings;
  stepLength = _stepLength;

  int levels = bufferLimitSettings.stepsDelayMax - bufferLimitSettings.stepsDelayMin + 1;
  bufferLimitsTimes.resize(levels);


  int curLevel = bufferLimitSettings.stepsDelayMax;
  while ( curLevel >= bufferLimitSettings.stepsDelayMin )
  {
    int idx = curLevel - bufferLimitSettings.stepsDelayMin;
    NI_ASSERT( idx >= 0, "wrong buffer init index" );

    bufferLimitsTimes[idx] = CalcBaseTimeForBufferLimit(curLevel);
    --curLevel;
  }

  //будем регистрировать только те лаги, что приходят не более чем через время действия повышенного буфера (в степах, от последнего лага)
  lagsHistory.SetMinLagDistance( bufferLimitSettings.stepsDelayFrame * levels );
}

void StepsBufferLimit::AdjustByLag( int newLagTime, int trascieverStep )
{
  lagsHistory.Update(trascieverStep);

  // регистрируем новый лаг и в случае необходимости повышаем/обновляем время текущего лимита буфера  
  int newBufferLimit = min( (int)newLagTime / stepLength, 
    (g_enableAdaptiveBuffer)?(bufferLimitSettings.stepsDelayMax):(bufferLimitSettings.stepsDelayMin) );

  if (newBufferLimit >= currentBufferLimit)
  {
    currentBufferLimit = newBufferLimit;
    bufferLimitTimer = GetBufferLimitTime( currentBufferLimit );
  }

  if (newBufferLimit > bufferLimitSettings.stepsDelayMin)
    lagsHistory.RegisterLag(newBufferLimit, trascieverStep);

}

void StepsBufferLimit::Update( int trascieverStep )
{
  lagsHistory.Update( trascieverStep );

  //со временем понижаем лимит
  if (bufferLimitTimer > 0)
  {
    --bufferLimitTimer;

    if (bufferLimitTimer <= 0)
    {
      --currentBufferLimit;
      if (currentBufferLimit > bufferLimitSettings.stepsDelayMin)
        bufferLimitTimer = GetBufferLimitTime( currentBufferLimit );
    }
  }
}


int StepsBufferLimit::GetBufferLimitTime( int bufferLimit )
{
  //для текущего лимита вычисляем надо ли увеличивать его длительность, на основании того, 
  //какие лаги случались за последнее время
  int idx = bufferLimit - bufferLimitSettings.stepsDelayMin;
  NI_ASSERT( idx >=0 && idx < bufferLimitsTimes.size(), "invalid delay level" )
  int adaptiveTime = bufferLimitsTimes[idx];

  float avLagsLevel = lagsHistory.GetAvgLagsLevel();
  if (avLagsLevel >= bufferLimit)
    adaptiveTime = bufferLimitSettings.stepsDelayFrame;

  return adaptiveTime;
}

int StepsBufferLimit::CalcBaseTimeForBufferLimit(int bufferLimit )
{
  //вычисляем длительность каждого лимита в идеальных условиях - разовый лаг
  if (bufferLimit <= bufferLimitSettings.stepsDelayMin)
    return bufferLimitSettings.stepsDelayFrame;

  return  max( bufferLimitSettings.stepsDelayFrame / (bufferLimit - bufferLimitSettings.stepsDelayMin), 10);
}


void StepsBufferLimit::LagsHistory::RegisterLag( int level, int step )
{
  if (step == stepOfLastLag && !lagsHistory.empty())
  {
    lagsHistory.back() = level;
    return;
  }

  lagsHistory.push_back( level );
  stepOfLastLag = step;

  if (lagsHistory.size() > maxEntries) 
    lagsHistory.pop_front();
}

void StepsBufferLimit::LagsHistory::Update( int step )
{
  if ( stepOfLastLag < 0 )
  {
    stepOfLastLag = step;
    return;
  }

  if( step - stepOfLastLag > minValidLagDistance )
    lagsHistory.clear();
}


float StepsBufferLimit::LagsHistory::GetAvgLagsLevel()
{
  if (lagsHistory.size() < 3)
    return 0;

  float avgLevel = 0.0f;

  list<int>::iterator it = lagsHistory.begin();
  for ( ; it != lagsHistory.end(); ++it )
  {
    avgLevel += (*it);
  }

  avgLevel /= lagsHistory.size();

  return avgLevel;
}

void StepsBufferLimit::LagsHistory::SetMinLagDistance( int distance )
{
  minValidLagDistance = distance;
}

} // namespace NCore


NI_DEFINE_REFCOUNT( NCore::ITransceiver );
NI_DEFINE_REFCOUNT( NCore::Transceiver );
NI_DEFINE_REFCOUNT( NCore::ICommandScheduler );

REGISTER_DEV_VAR( "debug_crc_mode", g_crcMode, STORAGE_NONE );
REGISTER_DEV_VAR( "debug_disable_world", g_disableWorld, STORAGE_NONE );
REGISTER_DEV_VAR( "transceivert_log_step", g_logTransceiverSteps, STORAGE_NONE );
REGISTER_DEV_CMD( debug_dump_crc, DumpCrc );
REGISTER_DEV_CMD( debug_skip_delayed_steps, SkipDelayedSteps );
REGISTER_DEV_VAR( "calc_crc_in_separate_thread", g_calcCrcInSeparateThread, STORAGE_NONE );
REGISTER_DEV_VAR( "save_world", g_saveWorldRequested, STORAGE_NONE );
REGISTER_DEV_VAR( "load_world", g_loadWorldRequested, STORAGE_NONE );
REGISTER_DEV_VAR( "save_load_world_dump_crc", g_saveLoadWorldDumpCRC, STORAGE_NONE );
REGISTER_DEV_VAR( "log_segments_interval", g_logSegmentsInterval, STORAGE_NONE );
REGISTER_DEV_VAR( "process_crc_requests", g_processCrcRequests, STORAGE_NONE );
REGISTER_DEV_VAR( "debug_crc_buffer_size", g_bufferSize, STORAGE_NONE );

REGISTER_VAR( "fill_buffer_after_lag", g_fillBufferAfterLag, STORAGE_NONE );
REGISTER_VAR( "enable_adaptive_buffer", g_enableAdaptiveBuffer, STORAGE_NONE );
