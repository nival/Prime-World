#include "stdafx.h"
#include "PfFsm.h"
#include "System\InlineProfiler.h"
#include "PFHeroStates.h"

static int dontClearMomentary = 1;
static int maxStateQueueSize = 2;
REGISTER_DEV_VAR( "dont_clear_momentary", dontClearMomentary, STORAGE_NONE );
REGISTER_DEV_VAR( "orders_queue_size", maxStateQueueSize, STORAGE_NONE );

namespace NWorld
{

PFFsm::~PFFsm()
{
  Cleanup();
}

void PFFsm::EnqueueState( CObj<IPFState> pState, bool flushQueue )
{
  NI_VERIFY( pState, "Trying to enqueue invalid state!", return; );

  if( paused )
  {
    delayedStates.insert( delayedStates.end(), make_pair( pState, flushQueue ) );
    return;
  }

  if( flushQueue )
  {
    if (dontClearMomentary)
      FlushStateQueue2();
    else
      FlushStateQueue();
  }

  if ( stateQueue.size() < maxStateQueueSize )
    stateQueue.insert( stateQueue.end(), pState );
}

void PFFsm::FlushStateQueue()
{
  // Temp queue needed here for the case when DoLeave() of some state calls to PFFsm::Cleanup, 
  // which gets here again and we have infinit recursion with crash after some time
  TStateQueue  tempStateQueue(stateQueue);

  stateQueue.clear();

  for ( TStateQueue::iterator it = tempStateQueue.begin(); it != tempStateQueue.end(); it++ )
    (*it)->DoLeave(true);

  tempStateQueue.clear();
}

void PFFsm::FlushStateQueue2()
{
  // Temp queue needed here for the case when DoLeave() of some state calls to PFFsm::Cleanup, 
  // which gets here again and we have infinit recursion with crash after some time
  TStateQueue  tempStateQueue(stateQueue);

  stateQueue.clear();

  for ( TStateQueue::iterator it = tempStateQueue.begin(); it != tempStateQueue.end();)
  {
    TStateQueue::iterator itTmp = it;
    ++it;
    if ((*itTmp)->IsEjecting())
    {
      (*itTmp)->DoLeave(true);
      tempStateQueue.erase(itTmp);
    }
  }

  stateQueue = tempStateQueue;
  tempStateQueue.clear();
}

void PFFsm::FsmStep(float dtInSeconds)
{
  NI_PROFILE_FUNCTION
  
  if( paused )
  {
    return;
  }

  bool const wasIdle = IsIdle();

  FSMStep( dtInSeconds );

  if ( !stateQueue.empty() && ( IsIdle() || !GetCurrentState()->IsBlocking() ) )
  {
    CObj<IPFState> pState = stateQueue.front();
    stateQueue.pop_front();

    if( pState->IsEjecting() )
    {
     PFHFSM::Cleanup();
    }

    PushState( pState );
    FSMStep( 0.0f );

    if ( GetStackSize() > 1 && !pState->IsEjecting() && ( pState->GetNumSubStates() > 0 ) )
    {
      CObj<IPFState> pCmd = PopState();
      PFHFSM::Cleanup();
      if(IsValid(pCmd))
        PushState( pCmd );
      FSMStep( 0.0f );
    }
  }

  if( !wasIdle && IsIdle() )
  {
    OnBecameIdle();
  }
}

void PFFsm::Cleanup( bool bForced /*= true*/ )
{
  FlushStateQueue();
  PFHFSM::Cleanup( bForced );
}

void PFFsm::PauseFSM( bool pause )
{
  if( paused == pause )
  {
    return;
  }

  paused = pause;

  if( !pause )
  {
    for( TDelayedStates::iterator it = delayedStates.begin(), end = delayedStates.end();it != end; ++it )
    {
      EnqueueState( it->first.GetPtr(), it->second );
    }
  }
}

bool PFFsm::IsIdle() const {
  return GetCurrentState() == 0 
    || GetCurrentState()->GetTypeId() == NWorld::PFHeroHoldState::typeId; 
}


PFHFSM::PFHFSM()
{
  //DevTrace("%08x : PFHFSM::PFHFSM()", int(this));
}

PFHFSM::~PFHFSM()
{
  //DevTrace("%08x : PFHFSM::~PFHFSM()", int(this));
  Cleanup();
}

void PFHFSM::FSMStep(float dt)
{
  if ( CObj<IPFState> pCurrent = GetCurrentState() )
  {
    if ( pCurrent->DoStep(dt) )
    {
      CObj<IPFState> curState = PopState();
      if(IsValid(curState))
			  curState->DoLeave();
    }
  }
}

CObj<IPFState> PFHFSM::PopState()
{
  if( !stateStack.empty() )
  {
    CObj<IPFState> st = stateStack.back();
    stateStack.pop_back();

    //DevTrace("%08x : PFHFSM::PopState(%s)", int(this), st->GetObjectTypeName());
    return st;
  }
  return 0;
}

IPFState* PFHFSM::GetCurrentState()
{
  //if(!stateStack.empty())
  //  DevTrace("%08x : PFHFSM::GetCurrentState() = %s", int(this), stateStack.back()->GetObjectTypeName());

  return stateStack.empty() ? NULL : stateStack.back();
}

IPFState const* PFHFSM::GetCurrentState() const
{
  //if(!stateStack.empty())
  //  DevTrace("%08x : PFHFSM::GetCurrentState() = %s", int(this), stateStack.back()->GetObjectTypeName());
  
  return stateStack.empty() ? 0 : stateStack.back();
}

void PFHFSM::PushState( CObj<IPFState> const& pState )
{
  NI_VERIFY( pState, "Trying to push invalid state!", return; );
  if ( !GetCurrentState() || !GetCurrentState()->IsBlocking() )
  {
    // ”бираем стейт, который должен покинуть стек при пуше нового стейта. —ейчас пока что только PFHeroHoldState.
    if ( GetCurrentState() && GetCurrentState()->IsEscaping() )
    {
      CObj<IPFState> curState = PopState();
      if(IsValid(curState))
        curState->DoLeave( true ); // —читаем это очисткой
    }
    //DevTrace("%08x : PFHFSM::PushState(%s)", int(this), pState->GetObjectTypeName());
    stateStack.push_back( pState );
  }
  else
  {
    NI_VERIFY( GetCurrentState()->IsBlocking(), "State MUST be blocking!", stateStack.push_back( pState ); return; );

    //First state is blocking; adding new one under all blocking states.
    //Find last blocking state
    vector<CObj<IPFState>>::iterator iState;
    for( iState = stateStack.end() - 1; iState >= stateStack.begin(); iState-- )
    {
      if ( (*iState)->IsBlocking() )
      {
        (*iState)->InformStatePassingThrough();
      }
      else
      {
        iState++;
        break;
      }

      if ( iState == stateStack.begin() )
      {
        //All states are blocking!
        //We must insert new state to vector begin (i.e. stack bottom)
        break;
      }
    }

    NI_VERIFY( ( ( iState >= stateStack.begin() ) && ( iState < stateStack.end() ) ), "Invalid state iterator!", stateStack.push_back( pState ); return; );
    NI_VERIFY( (*iState)->IsBlocking(), "State MUST be blocking!", stateStack.push_back( pState ); return; );

    stateStack.insert( iState, pState );
  }
}

bool PFHFSM::CanClearStack() const
{
  for ( vector<CObj<IPFState>>::const_iterator iState = stateStack.begin(), iEnd = stateStack.end(); iState != iEnd; ++iState )
  {
    if ( *iState && !(*iState)->CanBeInterrupted() )
    {
      return false;
    }
  }
  return true;
}

void PFHFSM::Cleanup( bool bForced /*= true*/ )
{
  //DevTrace("%08x : PFHFSM::Cleanup()", int(this));
  // Check if current state can not be interrupted
  if ( !bForced && !CanClearStack() )
  {
    return;
  }

  while ( GetCurrentState() && ( bForced || !GetCurrentState()->IsBlocking() ) )
  {
	  CObj<IPFState> curState = PopState();
    if(IsValid(curState))
		  curState->DoLeave( true );
  }

  if ( GetCurrentState() && GetCurrentState()->IsBlocking() )
  {
    //If not forced we should clean non-blocking states only
    while( !stateStack.front()->IsBlocking() )
    {
      stateStack.erase( stateStack.begin() );
    }
  }
}

void PFHFSM::DumpAllStates(int depths)
{
  if (!depths)
    DebugTrace("Stack Dump");

  for (int i = stateStack.size()-1; i>=0;i-- )
  {
    stateStack[i]->DumpStateToConsole(depths);
  }
}

void PFHFSM::RemoveState( IPFState* pState )
{
  if ( !pState )
    return;

  if ( GetCurrentState() == pState )
  {
    CObj<IPFState> curState = PopState();
    if(IsValid(curState))
      curState->DoLeave();
    return;
  }

  stateStack.remove( pState );
}

const char* PFHFSM::GetCurrentStateName()
{
  return GetCurrentState() ? GetCurrentState()->GetObjectTypeName() : "None";
}

}
