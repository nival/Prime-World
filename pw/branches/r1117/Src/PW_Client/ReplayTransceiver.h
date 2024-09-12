#pragma once

#include "Core/Scheduler.h"
#include "Core/Replay.h"


namespace Game
{
  namespace EReplayStatus { enum Enum; }
}

namespace NGameX
{
  class LoadingStatusHandler;
  _interface IAdventureScreen;
}

namespace NCore
{
  _interface IWorldBase;
}


namespace NWorld
{
  class IMapCollection;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ReplayStorage2: public NCore::IReplayStorage
{
  OBJECT_BASIC_METHODS(ReplayStorage2)

public:
  ReplayStorage2() {};
  ReplayStorage2( NCore::ReplayBufferMode mode, const char * fileName, NWorld::IMapCollection * _mapCollection, 
                  NGameX::LoadingStatusHandler * _loadingStatusHandler );

  virtual bool GetNextSegment( NCore::ReplaySegment& segOut ) { return false; }
  virtual bool GetNextSegment( NCore::SyncSegment & segOut );
  virtual bool GetHeader( NCore::MapStartInfo * info, int * clientId, int * stepLength, 
                          NCore::ClientSettings * clientSettings, lobby::SGameParameters* gameParams );

  virtual bool IsOk() { return (replayFile && replayFile->IsOk()); };

private:
  void SetLoadingStatus(Game::EReplayStatus::Enum status);

  CObj<FileStream> replayFile;
  StrongMT<NWorld::IMapCollection> mapCollection;
  Weak<NGameX::LoadingStatusHandler>  loadingStatusHandler;
  int startStep;
  int currentStep;
  int nextStep;
  bool isFinished;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class ReplayTransceiver : public NCore::ITransceiver, public BaseObjectST
{
  NI_DECLARE_REFCOUNT_CLASS_2( ReplayTransceiver, NCore::ITransceiver, BaseObjectST )

public:
  ReplayTransceiver() {}
  ReplayTransceiver( NCore::IReplayStorage* _replay, int _stepLength = DEFAULT_GAME_STEP_LENGTH );

  virtual void Reinit( NCore::ICommandScheduler * scheduler ) {}
  virtual void Step( float dt );
  virtual int GetWorldStep() const;
  virtual void SendCommand( NCore::WorldCommand *pCmd, bool ) {}
  virtual void SetWorld( NCore::IWorldBase * _world );
  virtual NCore::IWorldBase * GetWorld() { return world; }
  virtual void RecordMapStart( const NCore::MapStartInfo & info ) {}

  void SetAdventureScreenInterface( NGameX::IAdventureScreen * _adventureScreen ) { adventureScreen = _adventureScreen; }

  virtual bool IsPaused() const { return false; }
  virtual bool IsAsynced() const { return false; }

  virtual int GetNextStep() const { return 0; }
  virtual void SetNextStep( int _nextStep ) {};

  virtual void SetPrecalcCrcOnce( bool _precalcCrcOnce ) {};

  virtual bool GetNoData() const { return false; }
  virtual int  GetBufferLimit() const { return 1; }

  void SetUseServerReplay(bool _useServerReplay) { useServerReplay = _useServerReplay; };

protected:
  virtual void OnDestroyContent();

private:
  CObj<NCore::IReplayStorage> replay;
  CPtr<NCore::IWorldBase> world;
  CPtr<IPointerHolder> ptrHolder;
  Weak<NGameX::IAdventureScreen> adventureScreen;
  float time;
  bool useServerReplay;
  //TODO: Add base class for transceivers and move there all common functionality
  int stepLength;
  float stepLengthInSeconds;
  float replayMsgTimer;
  bool isPaused;

  bool SetTimeScale( const char *name, const vector<wstring> &args );
  bool ReplaySpeedInc( const char *name, const vector<wstring> &args );
  bool ReplaySpeedDec( const char *name, const vector<wstring> &args );
  bool ReplaySpeedRst( const char *name, const vector<wstring> &args );
  bool ReplayPause( const char *name, const vector<wstring> &args );

  void StepReplayMessage( float dt );

public:
  void SetTimeScale( float timeScale );

};

} //namespace NWorld
