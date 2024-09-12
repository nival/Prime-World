#include "StdAfx.h"
#include "RemoteCommandScheduler.h"
#include "SessionRunner.h"
#include "GameCommand.h"
#include "System/ChunklessSaver.h"
#include "CommandSerializer.h"
#include "GameTypes.h"

namespace
{
  NDebug::DebugVar<int> stepsDelayed( "StepsDelayed", "" );
  NDebug::DebugVar<int> stepsRecieved( "StepsRecieved", "", false, 200, 2.0f );
}

namespace NCore
{

RemoteCommandScheduler::RemoteCommandScheduler( IServerNode * _server, ISessionRunner * _asyncProcessor, int _clientId, bool _isSpectator ) :
server( _server ),
asyncProcessor( _asyncProcessor ),
clientId( _clientId ),
isSpectator( _isSpectator )
{
}



void RemoteCommandScheduler::Reinit( IServerNode * _server, ISessionRunner * _asyncProcessor )
{
  MessageTrace( "Re-initializing CommandScheduler, node=%08x", (void*)_server );

  segments.clear();
}


void RemoteCommandScheduler::SendMessage( CObjectBase *pMsg, bool isPlayerCommand )
{
  if ( isSpectator )
    return;

  MessageQueue & selectedMessageQueue = (isPlayerCommand) ? (messageQueue) : (messageQueueAI);
  if (selectedMessageQueue.messageSent)
  {
    selectedMessageQueue.messages.push_back(pMsg);
  }
  else
  {
    SendMessageImpl(pMsg, isPlayerCommand);
    selectedMessageQueue.messageSent = true;
  }
}

void RemoteCommandScheduler::SendMessageImpl( CObjectBase *pMsg, bool isPlayerCommand )
{
  if ( isSpectator )
    return;

  CObj<CObjectBase> message = pMsg;
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return;

  MemoryStream ms;
  WriteCommandToStream( message, &ms, 0 );
  lserver->SendMessage( &ms, isPlayerCommand );
}


CObj<SyncSegment> RemoteCommandScheduler::GetSyncSegment()
{
  if ( segments.empty() )
    return 0;

  CObj<SyncSegment> result = segments.front();
  segments.pop_front();

  stepsDelayed.SetValue( segments.size() );

  return result;
}



int RemoteCommandScheduler::GetNextStep( bool warnIfNoSegments ) const
{
  if ( warnIfNoSegments )
    stepsDelayed.SetValue( stepsDelayed.GetValue(), segments.empty() && warnIfNoSegments );
  return segments.empty() ? INVALID_STEP : segments.back()->step;
}



void RemoteCommandScheduler::SendCRC( int step, DWORD crcValue )
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return;
  lserver->SendCRC( step, crcValue );
}


void RemoteCommandScheduler::SendCrcData( int step, unsigned char * data, int size)
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return;
  lserver->SendCrcData( step, data, size );
}


int RemoteCommandScheduler::GetStartedStep()
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return INVALID_STEP;
  return lserver->GetStartedStep();
}


int RemoteCommandScheduler::GetAsyncStep() 
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return INVALID_STEP;
  return lserver->GetAsyncStep();
}


int RemoteCommandScheduler::GetProtectionAsyncStep()
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return INVALID_STEP;
  return lserver->GetProtectionAsyncStep();
}


int RemoteCommandScheduler::GetLastConfirmedStep() 
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return INVALID_STEP;
  return lserver->GetLastConfirmedStep();
}


int RemoteCommandScheduler::PopCrcRequestStep() 
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return INVALID_STEP;
  return lserver->PopCrcRequestStep();
}


bool RemoteCommandScheduler::IsAllClientsReady() 
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return false;
  return lserver->GetStartedStep() >= 0;
}



void RemoteCommandScheduler::Step( float dt )
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return;
  IServerNode::TMessageList serverSegment;
  IServerNode::TStatusList statuses;

  int step;
  int steps = 0;
  while ( ( step = lserver->GetServerSegment( serverSegment, statuses ) ) != -1 )
  {
    CObj<SyncSegment> newSyncSegment;

    if ( step >= lserver->GetStartedStep() && IsAllClientsReady() || lserver->IsReconnecting())
      newSyncSegment = new SyncSegment( step );

    for ( IServerNode::TMessageList::iterator it = serverSegment.begin(); it != serverSegment.end(); ++it )
    {
      CPtr<CObjectBase> pMsg = ReadCommandFromStream( *it, 0 );
      CDynamicCast<PackedWorldCommand> pwcmd( pMsg );
      if ( pwcmd )
      {
        if ( newSyncSegment )
          newSyncSegment->commands.push_back( pwcmd );
      }
      else
      {
        StrongMT<ISessionRunner> runner = asyncProcessor.Lock();
        if (runner)
        {
          runner->ProcessAsyncMessage( pMsg );
        }
      }
    }

    if ( newSyncSegment )
    {
      newSyncSegment->statuses = statuses;
      segments.push_back( newSyncSegment );
      stepsDelayed.SetValue( segments.size() );
      ++steps;
    }
    else
    {
      StrongMT<ISessionRunner> runner = asyncProcessor.Lock();
      if (runner)
      {
        for (int i = 0; i < statuses.size(); ++i)
        {
          runner->ProcessAsyncStatus( statuses[i] );
        }
      }
    }

    serverSegment.clear();
  }
  stepsRecieved.SetValue( steps );

  StepMessageQueue(true);
  StepMessageQueue(false);
}


void RemoteCommandScheduler::StepMessageQueue( bool playerMessages )
{
  MessageQueue & selectedMessageQueue = (playerMessages) ? (messageQueue) : (messageQueueAI);
  if (selectedMessageQueue.messages.size() > 0)
  {
    SendMessageImpl(selectedMessageQueue.messages.front(), playerMessages);
    selectedMessageQueue.messages.pop_front();
    selectedMessageQueue.messageSent = true;
  }
  else
  {
    selectedMessageQueue.messageSent = false;
  }
}


int RemoteCommandScheduler::GetMyClientID() const
{
  return clientId;
}

const StepsDelaySettings & RemoteCommandScheduler::GetStepsDelaySettings()
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return defaultStepsDelaySettings;
  return lserver->GetStepsDelaySettings();
}

bool RemoteCommandScheduler::IsCrcDataEnabled()
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return false;
  return lserver->IsCrcDataEnabled();
}

void RemoteCommandScheduler::SendProtectionMagic(int step, uint magic)
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return;
  return lserver->SendProtectionMagic(step, magic);
}


int RemoteCommandScheduler::GetProtectionMagicConfirmFrequency()
{
  StrongMT<IServerNode> lserver = server.Lock();
  if ( !lserver)
    return 0;
  return lserver->GetProtectionMagicConfirmFrequency();
}

} //namespace NCore

NI_DEFINE_REFCOUNT( NCore::IServerNode );
NI_DEFINE_REFCOUNT( NCore::RemoteCommandScheduler )
NI_DEFINE_REFCOUNT( NCore::ISessionRunner );
