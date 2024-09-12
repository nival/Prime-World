#pragma once
#include "Scheduler.h"

namespace NCore
{

class RemoteCommandScheduler : public ICommandScheduler, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( RemoteCommandScheduler, ICommandScheduler, BaseObjectMT );

public:
  RemoteCommandScheduler( IServerNode * _server, ISessionRunner * _asyncProcessor, int _clientId, bool _isSpectator );

  virtual void Reinit( IServerNode * _server, ISessionRunner * _asyncProcessor );

  virtual void SendMessage( CObjectBase *pMsg, bool isPlayerCommand );

  virtual CObj<SyncSegment> GetSyncSegment();
  virtual int GetNextStep( bool warnIfNoSegments ) const;

  virtual void SendCRC( int step, DWORD crcValue );
  virtual void SendCrcData( int step, unsigned char * data, int size);
  virtual int GetStartedStep();
  virtual int GetAsyncStep();
  virtual int GetProtectionAsyncStep();
  virtual int GetLastConfirmedStep();
  virtual int PopCrcRequestStep();

  virtual bool IsAllClientsReady();

  virtual void Step( float dt );

  virtual int GetMyClientID() const;

  virtual const StepsDelaySettings & GetStepsDelaySettings();
  virtual bool IsCrcDataEnabled();

  virtual void SendProtectionMagic(int step, uint magic);
  virtual int GetProtectionMagicConfirmFrequency();
private:
  void SendMessageImpl( CObjectBase *pMsg, bool isPlayerCommand );
  void StepMessageQueue( bool playerMessages );

  WeakMT<IServerNode> server;
  WeakMT<ISessionRunner> asyncProcessor;
  int clientId;
  StepsDelaySettings defaultStepsDelaySettings;

  bool isSpectator;

  list<CObj<SyncSegment> > segments;

  struct MessageQueue
  {
    MessageQueue() : messageSent(false) {}

    nstl::list<CObj<CObjectBase> > messages;
    bool messageSent;
  };

  MessageQueue messageQueue;
  MessageQueue messageQueueAI;
};

} //namespace NCore
