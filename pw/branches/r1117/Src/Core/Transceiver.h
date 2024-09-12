#pragma once
#include "Scheduler.h"
#include "../System/Crc32Calculator.h"
#include "GameCommand.h"
#include "BinStatsCollector.h"
#include "System/AsyncInvoker.h"
#include "Core/WorldBase.h"
#include "GameTypes.h"

_interface IPointerHolder;

namespace NCore
{
class ReplayStorage;

class CrcStatsCollector : public BinStatsCollector
{
public:
  struct TypeStats
  {
    int size;
    int objects;

    TypeStats() : size( 0 ), objects( 0 ) { }

    void Add( int _size, bool increaseObjectsCounter = false )
    {
      size += _size;
      if ( increaseObjectsCounter )
        ++objects;
    }
  };
  typedef hash_map<string, vector<TypeStats> > TTypeStatsMap;
private:
  TTypeStatsMap stats;
  vector<CObjectBase*> curObjects;
  CObjectBase* curObject;
  CObjectBase* newObject;
  int slices;

  TypeStats& GetSliceData( const char* key );

public:
  CrcStatsCollector() : BinStatsCollector(), curObject(0), newObject(0), slices(0) {}

  int GetSliceCount() const { return slices; }

  void OnReset() { slices++; }

  void OnStartObject();

  void OnFinishObject( CObjectBase* object );

  void OnStorePointer( const IBinSaver::chunk_id idChunk, CObjectBase* object );

  void OnDataChunk( const IBinSaver::chunk_id idChunk, const void* pData, int nSize );

  void OnDataChunk( const string& data ) {}

  void OnDataChunk( const wstring& data ) {}

  bool OnStartChunk( const IBinSaver::chunk_id idChunk, int chunkType );

  void OnFinishChunk();

  const TTypeStatsMap& GetStatsData() const;

  virtual void DumpStats() const {}
};


//TODO: move it to a separate file
class TransceiverCrcCalculator
{
public:
  struct CRCResult
  {
    CRCResult() : step(INVALID_STEP), crc(0) {}

    bool IsValid() const { return step != INVALID_STEP; }

    int step;
    unsigned long crc;
  };

  struct Buffer
  {
    unsigned char* buffer;
    size_t size;
    size_t length;

    Buffer() : buffer( 0 ), size( 0 ), length( 0 ) { }
    ~Buffer() { if ( buffer ) { delete buffer; buffer = 0; } }

    void Allocate( size_t _size )
    {
      if ( buffer )
        delete buffer;

      buffer = new unsigned char[_size];
      size = _size;
      length = 0;
    }
  };

  TransceiverCrcCalculator();
  ~TransceiverCrcCalculator();

  void CreateCalculator(bool _crcDataEnabled);
  void StartCalcCRCAsync( int step, CObj<IWorldBase> world );
  void StartCalcCRCSync( int step, CObj<IWorldBase> world );
  CRCResult WaitForCrcResult() { return threadWithTask.EndInvoke(); }
  void DumpCrc( int step );
  void UpdateBuffers(int lastConfirmedStep);
  Buffer * GetBuffer(int step, Stream & stream);

  bool IsBusy() const { return threadWithTask.IsBusy(); }
  void Sync() { threadWithTask.Sync(); }

private:
  struct CalcCRCTask
  {
    TransceiverCrcCalculator *pThis;
    int step;
    CObj<IWorldBase> world; 
    
    CRCResult operator()() const 
    {
      CRCResult res;
      
      res.crc = pThis->CalcCRCImpl( step, world );
      res.step = step;
    
      return res; 
    };
  };
  
  unsigned long CalcCRCImpl( int step, CObj<IWorldBase> world );
  
  nstl::list<Buffer*> crcBuffers;
  nstl::list<Buffer*> crcBuffersCache;
  int bufferSize;
  bool crcDataEnabled;
  
  CObj<ICrcCalculator> crcCalculator;
#ifndef _SHIPPING
  threading::AsyncInvoker<CalcCRCTask, CRCResult> threadWithTask;
#else
  threading::FakeAsyncInvoker<CalcCRCTask, CRCResult> threadWithTask;
#endif // _SHIPPING
};

class StepsBufferLimit
{
public:
  class LagsHistory
  {
    int stepOfLastLag;
    int minValidLagDistance;
    int maxEntries;

    list<int> lagsHistory;

  public:
    LagsHistory() : 
        minValidLagDistance(100)
          , stepOfLastLag(-1)
          , maxEntries(5)
        {}
        void RegisterLag( int level, int step );
        float GetAvgLagsLevel();
        void SetMinLagDistance( int distance );
        void Update( int trascieverStep );
  };


private:
  int currentBufferLimit;
  int bufferLimitTimer;
  vector<int> bufferLimitsTimes;
  StepsDelaySettings bufferLimitSettings;
  LagsHistory lagsHistory;
  int stepLength;

  int GetBufferLimitTime( int bufferLimit );
  int CalcBaseTimeForBufferLimit( int bufferLimit );

public:
  StepsBufferLimit() :
      currentBufferLimit(1),
        bufferLimitTimer(0),
        stepLength(DEFAULT_GAME_STEP_LENGTH)
      { }

  void Init( const StepsDelaySettings& settings, int _stepLength );
  void Update( int trascieverStep );
  void AdjustByLag( int newLagTime, int trascieverStep );
  int GetValue() const { return currentBufferLimit; }

};

namespace
{
  struct ProtectionMagicStepCalculator : NonCopyable
  {
    ProtectionMagicStepCalculator()
      : serverStep(NCore::INVALID_STEP)
      , worldStep(NCore::INVALID_STEP)
    {

    }

    bool NeedUpdate() const
    {
      if (serverStep < 0)
        return true;
      if (worldStep < 0)
        return true;

      return false;
    }

    bool Update(const int _serverStep, const int _worldStep)
    {
      if (_serverStep < 0)
        return false;
      if (_worldStep < 0)
        return false;

      bool updated = false;

      if (serverStep < 0)
      {
        serverStep = _serverStep;
        updated = true;
      }

      if (worldStep < 0)
      {
        worldStep = _worldStep;
        updated = true;
      }

      return updated;
    }

    int Calculate(const int step)
    {
      if (serverStep < 0)
        return NCore::INVALID_STEP;
      if (worldStep < 0)
        return NCore::INVALID_STEP;

      if (step < 0)
        return NCore::INVALID_STEP;

      return (step + serverStep - worldStep);
    }

    int serverStep;
    int worldStep;
  };
}

class Transceiver : public ITransceiver, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( Transceiver, ITransceiver, BaseObjectST )
public:
  Transceiver( ICommandScheduler * scheduler, int _stepLength = DEFAULT_GAME_STEP_LENGTH, bool writeReplay = true );

  ~Transceiver();
  //ITransceiver
  virtual void Reinit( ICommandScheduler * scheduler );
  virtual void Step( float dt );
  virtual int GetWorldStep() const;
  virtual void SendCommand( WorldCommand *command, bool isPlayerCommand );
  virtual void SetWorld( IWorldBase * world );
  virtual IWorldBase * GetWorld() { return world; }
  virtual void RecordMapStart( const MapStartInfo & info );
  virtual bool IsPaused() const;
  virtual bool IsAsynced() const { return asyncState; }
  virtual int GetNextStep() const { return nextStep; }
  virtual void SetNextStep( int _nextStep ) { nextStep = _nextStep; }
  virtual void SetPrecalcCrcOnce( bool _precalcCrcOnce ) { precalcCrcOnce = _precalcCrcOnce; }
  virtual bool GetNoData() const { return noData; }
  virtual int GetBufferLimit() const;

private:
  StrongMT<ICommandScheduler> scheduler;

#ifndef _SHIPPING
  Crc32Calculator<CrcStatsCollector> crcStatCalc;
#endif

  CObj<IWorldBase> world;
  CPtr<IPointerHolder> ptrHolder;

  CObj<ReplayStorage> replay;

  bool asyncState;

  float localTimeElapsed;
  float worldTimeElapsed;
  float checkTime;
  int nextStep;
  bool delaySteps;
  TransceiverCrcCalculator crcCalc;
  bool precalcCrcOnce;
  float slowDownFactor;
  bool noData;
  //TODO: Add base class for transceivers and move there all common functionality
  int stepLength;
  float stepLengthInSeconds;
  
  StepsBufferLimit stepsBufferLimit;

  ProtectionMagicStepCalculator pmsc;

  int lastProtectionMagicAsyncStep;

  void ProcessSegment( float localTime );
  bool CanProcessStep();
  void SkipDelayedStepd();
  void ProcessProtectionMagic();
};
}
