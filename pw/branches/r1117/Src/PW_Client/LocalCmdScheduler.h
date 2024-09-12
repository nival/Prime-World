#ifndef LOCALCMDSCHEDULER_H_INCLUDED
#define LOCALCMDSCHEDULER_H_INCLUDED

#include "Core/Scheduler.h"
#include "Core/GameTypes.h"
#include "PW_Client/GameStatistics.h"
#include "PF_GameLogic/ReplayInfo.h"

namespace NCore
{
  class ReplayWriter;
}

namespace Game
{

class LocalCmdScheduler : public NCore::ICommandScheduler, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( LocalCmdScheduler, ICommandScheduler, BaseObjectMT );

public:
  LocalCmdScheduler( int _clientId );

  virtual void    Reinit( NCore::IServerNode * _server, NCore::ISessionRunner * _asyncProcessor ) {}
  virtual void    SendMessage( CObjectBase * pMsg, bool isPlayerCommand );
  virtual CObj<NCore::SyncSegment> GetSyncSegment();
  virtual int     GetNextStep( bool warnIfNoSegments ) const;
  virtual void    SendCRC( int step, DWORD crcValue ) {}
  virtual void    SendCrcData( int step, unsigned char * data, int size) {};
  virtual int     GetStartedStep() { return NCore::INVALID_STEP; }
  virtual int     GetAsyncStep() { return NCore::INVALID_STEP; }
  virtual int     GetProtectionAsyncStep() { return NCore::INVALID_STEP; }
  virtual int     GetLastConfirmedStep() { return NCore::INVALID_STEP; }
  virtual int     PopCrcRequestStep() { return NCore::INVALID_STEP; }
  virtual bool    IsAllClientsReady() { return gameReady; }
  virtual void    Step( float dt );
  virtual int     GetMyClientID() const { return clientId; }
  virtual const NCore::StepsDelaySettings & GetStepsDelaySettings() { return defaultStepsDelaySettings; }
  virtual bool    IsCrcDataEnabled() { return false; }
  virtual void    SendProtectionMagic(int step, uint magic) {}
  virtual int     GetProtectionMagicConfirmFrequency() { return 1; }

  void StartGame() { gameReady = true; }
  void SetReplayWriter(NCore::ReplayWriter * _replayWriter) { replayWriter = _replayWriter; }
  void OnVictory(const StatisticService::RPC::SessionClientResults & _sessionResults, const NGameX::ReplayInfo & _replayInfo);
  void OnCombatScreenStarted( const NGameX::ReplayInfo & _replayInfo );

private:
  const int                 clientId;
  timer::Time               localTime;
  bool                      gameReady;
  CObj<NCore::SyncSegment>  currentSegment;
  CObj<NCore::SyncSegment>  nextSegment;
  int                       stepIndex;
  timer::Time               nextStepTime;
  NCore::StepsDelaySettings defaultStepsDelaySettings;
  WeakMT<NCore::ReplayWriter> replayWriter;
};

} //namespace Game

#endif //LOCALCMDSCHEDULER_H_INCLUDED
