#pragma once

#include "PFState.h"

namespace NWorld
{

class PFHFSM
{
public:
  explicit PFHFSM();
  virtual ~PFHFSM();

  void DumpAllStates(int depths=0);

  void FSMStep(float dt);

  void             PushState(CObj<IPFState> const& pState);
  CObj<IPFState>   PopState();
  IPFState*        GetCurrentState();
  IPFState const * GetCurrentState() const;
  int              GetStackSize() const { return stateStack.size(); }
  virtual void Cleanup( bool bForced = true );
  void             RemoveState( IPFState* pState );
  virtual const char* GetCurrentStateName();
protected:
  bool CanClearStack() const;
private:
  ZDATA
  vector< CObj<IPFState> > stateStack;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&stateStack); return 0; }
};

class PFFsm : public PFHFSM
{
public:
  void EnqueueState(CObj<IPFState> pState, bool flushQueue);
	bool IsIdle() const ;
  bool HasQueuedStates() const { return !stateQueue.empty(); }

  void PauseFSM( bool pause );
  bool IsPaused() const { return paused; }

  virtual void Cleanup( bool bForced = true );
  virtual ~PFFsm();

protected:
  PFFsm() : paused(false) {}
  void FsmStep(float dtInSeconds);
 
  void FlushStateQueue();
  void FlushStateQueue2();

  virtual void OnBecameIdle() {}
private:
  typedef nstl::list< CObj<IPFState> > TStateQueue;
  typedef nstl::list< pair<CObj<IPFState>, bool> > TDelayedStates;
  ZDATA_(PFHFSM)
  TStateQueue    stateQueue;
  TDelayedStates delayedStates;
  bool           paused;
public:
  ZEND int operator&( IBinSaver &f ) { f.Add(1,(PFHFSM*)this); f.Add(2,&stateQueue); f.Add(3,&delayedStates); f.Add(4,&paused); return 0; }
};

}
