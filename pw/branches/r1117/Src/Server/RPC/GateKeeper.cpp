#include "stdafx.h"
#include "GateKeeper.h"
#include "Network/ClientTransportSystemIntf.h"
#include "Network/AddressTranslator.h"
#include "Network/TransportUtils.h"
#include "System/InlineProfiler.h"
#if defined( NV_LINUX_PLATFORM )
#include <unistd.h>
#endif // defined( NV_LINUX_PLATFORM )
#include "System/SafeTextFormatNstl.h"

namespace rpc
{

rpc::IPacketPipe::PipeInfo::Status ConvertStatus(Transport::IChannel* channel) 
{
  if (channel)
  {
    switch (channel->GetStatus())
    {
    case Network::ConnectionState::Connected: return rpc::IPacketPipe::PipeInfo::Connected;
    case Network::ConnectionState::Closed: return rpc::IPacketPipe::PipeInfo::Closed;
    default:
      return rpc::IPacketPipe::PipeInfo::Connecting;
    }

  }
  return IPacketPipe::PipeInfo::Closed;
}



GateKeeperBase::GateKeeperBase( const Transport::TServiceId& _serviceId, Transport::TClientId _clientId, 
                               IGateKeeperCallback* _callback, unsigned int nthreads )  :
serviceId( _serviceId ), clientId( _clientId ), pipeCount(0)
{
  if (_callback)
    attachNotificationCallback_(_callback);

  unsigned int n = nthreads;
  if (0 == n)
  {
#if defined( NV_WIN_PLATFORM )
    SYSTEM_INFO si;
    ::GetSystemInfo(&si);
    n = si.dwNumberOfProcessors;
#elif defined( NV_LINUX_PLATFORM )
    sysconf(_SC_NPROCESSORS_CONF);
#endif
  }

  if (n > 1)
    tp_.Open(n);
}



void GateKeeperBase::setGateKeeperCallback( IGateKeeperCallback* _callback )
{
  attachNotificationCallback(_callback);
}



void GateKeeperBase::attachNotificationCallback_(IGateKeeperCallback* _callback)
{
  NI_ASSERT(_callback, "");

  CallbacksT::iterator it = callbacks.begin();
  for (; it != callbacks.end(); ++it)
  {
    StrongMT<IGateKeeperCallback> const cb = (*it).Lock();
    if (cb && _callback == cb.Get())
      break;
  }
  if (it == callbacks.end())
    callbacks.push_back(_callback);
}



void GateKeeperBase::attachNotificationCallback( IGateKeeperCallback * _callback )
{
  attachNotificationCallback_( _callback );
}



void GateKeeperBase::detachNotificationCallback( IGateKeeperCallback * _callback )
{
  for (CallbacksT::iterator it = callbacks.begin(); it != callbacks.end(); ++it)
  {
    StrongMT<IGateKeeperCallback> const cb = (*it).Lock();
    if (cb && _callback == cb.Get())
    {
      callbacks.erase(it);
      break;
    }
  }
}



void GateKeeperBase::setTransportPipeTrackerFactory( TransportPipeTrafficTrackerFactory * _tpttf )
{
  tpttf = _tpttf;
}



void GateKeeperBase::Poll()
{
  NI_PROFILE_FUNCTION;

  {
    NI_PROFILE_BLOCK( "OnPrePoll call" );
    OnPrePoll();
  }

  gate->Poll();

  TPipeList pipes2close;

  {
    NI_PROFILE_BLOCK( "Closing pipes" );
    for ( TPipes::iterator it = pipes.begin(); it != pipes.end();)
    {
      if ( it->second->IsClosed() )
      {
        pipes2close.push_back(it->second);

        TPipes::iterator itOld = it;
        ++it;
        pipes.erase( itOld );
      }
      else
        ++it;
    }

    for ( TPipeList::iterator it = closingPipes.begin(); it != closingPipes.end();)
    {
      StrongMT<TransportPipe> pipe = *it;
      if ( pipe->IsClosed() )
      {
        pipes2close.push_back(pipe);

        TPipeList::iterator itOld = it;
        ++it;
        closingPipes.erase( itOld );
      }
      else
        ++it;
    }
  }

  {
    NI_PROFILE_BLOCK( "Processing close callbacks" );

    for ( TPipeList::iterator it = pipes2close.begin(); it != pipes2close.end(); ++it)
    {
      StrongMT<TransportPipe> pipe = *it;

      MessageTrace( "GateKeeper: Close pipe(name=%s)", pipe->GetName() );

      StrongMT<Node> lockedNode = pipe->LockNode();
      NI_VERIFY( lockedNode, "Pipe node is null!", continue );

      for(CallbacksT::iterator it = callbacks.begin(); it != callbacks.end();)
      {
        StrongMT<IGateKeeperCallback> _callback = (*it).Lock();
        if (_callback)
        {
          if (tp_.IsOpened())
          {
            CloseChannelJob * j = ccjobFactory_.create();
            j->Init( _callback, pipe->GetPipeChannel(), lockedNode );
            tp_.pushJob(j);
          }
          else
          {
            _callback->OnChannelClosed( pipe->GetPipeChannel(), lockedNode );
          }
          _callback = 0;
          ++it;
        }
        else
        {
          it = callbacks.erase(it);
        }
      }
    }
    if (pipes2close.size() && tp_.IsOpened())
      tp_.WaitJobs();
  }

  {
    NI_PROFILE_BLOCK( "Removing pipes" );

    for ( TPipeList::iterator it = pipes2close.begin(); it != pipes2close.end(); ++it)
    {
      TransportPipe * pipe = *it;

      DebugTrace("GateKeeper: Close pipe(gkn=%s p=%s)", GetName(), pipe->GetName() );

      StrongMT<Node> lockedNode = pipe->LockNode();
      NI_VERIFY( lockedNode, "Pipe node is null!", continue );

      gate->RemovePipe( lockedNode );
      *it = 0;
    }
  }

  {
    NI_PROFILE_BLOCK( "OnPostPoll call" );
    OnPostPoll();
  }
}



StrongMT<rpc::Node> GateKeeperBase::RequestNode( Transport::TServiceId const & destination )
{
  TPipes::iterator it = pipes.find( destination );

  if ( it != pipes.end() )
    return it->second->LockNode();

  StrongMT<Transport::IChannel> chan = OpenChannel( Transport::Address( serviceId, destination, clientId ));
  if ( chan )
  {
    StrongMT<TransportPipe> pipe = CreatePipe( chan );
    if ( pipe )
      return pipe->LockNode();
    else
      return 0;
  }

  return NULL;
}



void GateKeeperBase::RemoveNode( const Transport::TServiceId& destination )
{
  TPipes::iterator it = pipes.find( destination );

  if ( it == pipes.end() )
    return;

  StrongMT<TransportPipe> pipe = it->second;

  if ( StrongMT<Node> lockedNode = pipe->LockNode() )
    gate->RemovePipe( lockedNode );
  else
    NI_ALWAYS_ASSERT( "Pipe node is null!" );

  pipes.erase( it );
}



StrongMT<rpc::Node> GateKeeperBase::GetNode( const Transport::TServiceId& destination ) const
{
  TPipes::const_iterator it = pipes.find( destination );

  if ( it != pipes.end() )
    return it->second->LockNode();
  return 0;
}



void GateKeeperBase::Init()
{
  gate = new Gate( this );
}



void GateKeeperBase::Destroy()
{
  for ( TPipes::iterator it = pipes.begin(); it != pipes.end(); ++it )
  {
    if ( StrongMT<Node> lockedNode = it->second->LockNode() )
      gate->RemovePipe( lockedNode );
    it->second = 0;
  }

  gate = 0;
}



void GateKeeperBase::GenerateServiceId( Transport::IChannel* channel, Transport::TServiceId *serviceId )
{
  if ( !channel || !serviceId )
    return;

  Transport::TServiceId const & target = channel->GetAddress().target;
  Transport::TServiceId const & source = channel->GetAddress().source;

  Transport::TServiceId svcid;
  if (Transport::autoAssignClientId == channel->GetInternalClientId())
  { //  services haven't clientid
    if (channel->IsIncomingConnection())
      svcid = source;
    else
      svcid = target;

    if ( !svcid.empty() && ( '_' == svcid.At( 0 ) ) )
      svcid.clear();
  }
  else
  {
    //  client side support
    if (!channel->IsIncomingConnection())
    {
      svcid = target;
    }
  }

  if ( svcid.empty() )
    svcid.Printf( "%d_%d", channel->GetInternalClientId(), ++pipeCount);

  *serviceId = svcid;
}



StrongMT<TransportPipe> GateKeeperBase::CreatePipe( Transport::IChannel * chan, const GUID * id )
{
  Transport::TServiceId pipeId;
  GenerateServiceId( chan, &pipeId );

  DebugTrace( "GateKeeper: Generated pipeid(s=%d t=%s c=%d p=%s)", 
    chan->GetAddress().source.c_str(), chan->GetAddress().target.c_str(), chan->GetInternalClientId(), pipeId.c_str() );

  StrongMT<TransportPipe> pipe;

  TPipes::iterator it = pipes.find( pipeId );
  if (it != pipes.end() && it->second->IsClosed())
  {
    DebugTrace( "GateKeeper: Pipeid already exists but closed(p=%s)", pipeId.c_str());

    pipes.erase(it);
    it = pipes.end();
  }

  StrongMT<TransportPipeTrafficTracker> pipeTracker;
  StrongMT<TransportPipeTrafficTrackerFactory> pipeTrackerFactory;
  if (tpttf)
  {
    TPipeTrackers::iterator it = trackers.find(chan->GetAddress().source);
    if (it != trackers.end())
      pipeTrackerFactory = it->second;
    else
    {
      pipeTrackerFactory = tpttf->CloneFactory(chan->GetAddress().source);
      if (pipeTrackerFactory)
      {
        MessageTrace( "GateKeeper: Pipe tracker factory is registered. src=%s", chan->GetAddress().source.c_str());
      }
      trackers[chan->GetAddress().source] = pipeTrackerFactory;
    }

    if (pipeTrackerFactory)
      pipeTracker = pipeTrackerFactory->CreateTrafficTracker();
  }

  if ( it == pipes.end() )
  { 
    pipe = new TransportPipe( chan, pipeId, pipeTracker );
    pipes[ pipeId ] = pipe;
    pipe->SetNode(gate->AddPipe( pipe, id ));

    MessageTrace("GateKeeper: Pipe created for service. name=%s", pipeId.c_str() );
  }
  else
  { //  creation another pipe with the same name is requested
    //  здесь считаем текущий pipe закрывается и чтобы по нему завершить операции - 
    //  просто храним его до тех пор пока он не станет closed

    WarningTrace("GateKeeper: Race pipe detected. name=%s", Transport::AddressToString(chan->GetAddress()));

    TransportPipe* prevpipe = it->second;
    closingPipes.push_back(prevpipe);

    pipe = new TransportPipe( chan, pipeId, pipeTracker );
    it->second = pipe;
    pipe->SetNode(gate->AddPipe( pipe, id ));

    WarningTrace("GateKeeper: Pipe replaced for service. name=%s", pipeId.c_str() );
  }

  return pipe;
}



void GateKeeperBase::AddReceivedPipe( Transport::IChannel * channel )
{
  StrongMT<TransportPipe> pipe = CreatePipe( channel );

  DebugTrace( "GateKeeper: New pipe accepted. c=%d, s=%s, t=%s, p=%s", 
    channel->GetInternalClientId(),
    channel->GetAddress().source.c_str(),
    channel->GetAddress().target.c_str(),
    pipe->GetName());

  for(CallbacksT::iterator it = callbacks.begin(); it != callbacks.end();)
  {
    StrongMT<IGateKeeperCallback> _callback = (*it).Lock();
    if (_callback)
    {
      _callback->OnNewNode( pipe->GetPipeChannel(), pipe->LockNode() );
      ++it;
    }
    else
    {
      it = callbacks.erase(it);
    }
  }
}



void GateKeeperBase::OnCorruptData( rpc::IPacketPipe * _pipe )
{
  TransportPipe * pipe = nival_cast<TransportPipe>(_pipe);
  NI_VERIFY( pipe, "", return );

  for(CallbacksT::iterator it = callbacks.begin(); it != callbacks.end();)
  {
    StrongMT<IGateKeeperCallback> _callback = (*it).Lock();
    if (_callback)
    {
      _callback->OnCorruptData( pipe->GetPipeChannel(), pipe->LockNode() );
      ++it;
    }
    else
      it = callbacks.erase(it);
  }

  TPipes::iterator it = pipes.find( Transport::TServiceId( pipe->GetName() ) );
  NI_VERIFY( it != pipes.end(), "OnCorruptData received for unknown node", return );

  pipes.erase( it );
}



StrongMT<rpc::IPacketPipe> GateKeeperBase::ConnectToPipe( const char* name, const GUID& id )
{
  MessageTrace( "GateKeeper: ConnectToPipe. name=%s, svcid=%s c=%d", name, serviceId.c_str(), clientId );

  StrongMT<Transport::IChannel> channel = OpenChannel( Transport::Address( serviceId, Transport::TServiceId( name ), clientId ) );
  if (channel)
  {
    return CreatePipe( channel, &id ).Get();
  } 
  return 0;
}



GateKeeper::GateKeeper( Transport::ITransportSystem* _transport, const Transport::TServiceId& _serviceId, 
                       Transport::TClientId _clientId /*= Transport::autoAssignClientId*/, IGateKeeperCallback* callback /*= 0 */,
                       Network::NetAddress const & listenAddress)
:GateKeeperBase( _serviceId, _clientId, callback, 1),
transport( _transport )
{
  if (!listenAddress.empty())
  {
    listener = transport->CreateChannelListenerDirect( _serviceId, listenAddress );
    DebugTrace( "GateKeeper: Created direct service listener. svcid=%s, ptr=%d, ip=%s", _serviceId.c_str(), (void*)listener.Get(), listenAddress );
  }
  else
  if (!_serviceId.empty() && _serviceId.At(0) != '_') // имена, начинающиеся с "_", будем считать служебными (просто для сообщения адресату, кто к нему пришёл)
  {
    serviceId = transport->GetAddressTranslator()->GetLastServiceInstance( _serviceId );
    listener = transport->CreateChannelListener( serviceId );
    DebugTrace( "GateKeeper: Created service listener. svcid=%s, ptr=%d", _serviceId.c_str(), (void*)listener.Get() );
  }

  Init();
}



StrongMT<Transport::IChannel> GateKeeper::OpenChannel( const Transport::Address& address )
{
  return  transport->OpenChannel( address, "" );
}



void GateKeeper::OnPostPoll()
{
  if ( listener )
  {
    Transport::TChannels connections;
    listener->GetNewConnections( &connections );

    for ( Transport::TChannels::iterator it = connections.begin(); it != connections.end(); ++it )
    {
      AddReceivedPipe( *it );
    }
  }
}



GateKeeperClient::GateKeeperClient( Transport::IClientTransportSystem* _transport, const Transport::TServiceId& _serviceId, IGateKeeperCallback* callback /*= 0 */ ) :
GateKeeperBase( _serviceId, _transport->GetUserId(), callback ),
transport( _transport )
{
  Init();
}



StrongMT<Transport::IChannel> GateKeeperClient::OpenChannel( const Transport::Address& address )
{
  return transport->OpenChannel( address.target );
}

Transport::TClientId GateKeeperClient::GetClientId() const
{
  return transport->GetUserId();
}










TransportPipe::TransportPipe( Transport::IChannel * channel, Transport::TServiceId _serviceId, TransportPipeTrafficTracker * _tptt ) :
serviceId( _serviceId ),
channel( channel ),
tptt(_tptt)
{
  NI_ASSERT(channel, "Channel can't be 0");
}



TransportPipe::~TransportPipe()
{
  Reset();
  if ( channel )
    channel->Close();
  channel = 0;
}



bool TransportPipe::IsClosed() const
{
  if (!channel)
    return true;

  if (channel->GetStatus() == Network::ConnectionState::Closed)
    return true;

  return false;
}



IPacketPipe::PipeInfo TransportPipe::GetInfo() const 
{ 
  rpc::IPacketPipe::PipeInfo info = {ConvertStatus(channel), channel?channel->GetInternalClientId():-1}; 
  return info; 
}



void TransportPipe::Send( const byte* data, int size, bool force )
{
  //DebugTrace( "Sending message to %s ", serviceId.c_str() );
  if (tptt)
  {
    Transport::ChannelAddr chaddr(Transport::EKnownPipeId::Invalid, channel->GetInternalClientId());
    tptt->HandlePacket(chaddr, (const char*)data, size);
  }

  channel->SendRaw( data, size );
}



bool TransportPipe::Recieve( int index, byte ** data, int * size, Transport::MessageMiscInfo & _miscInfo )
{
  bool result = false;

  if (channel)
    result = channel->ReceiveRaw( &dataCache, _miscInfo );

  if( result ) 
  {
    *data = dataCache.begin(); *size = dataCache.size();
  }
  return result;
}



bool TransportPipe::Recieve(int index, byte** data, int* size )
{
  Transport::MessageMiscInfo miscInfo;
  return Recieve( index, data, size, miscInfo );
}



void TransportPipe::Reset() 
{
  dataCache.clear();
}

} //namespace rpc

NI_DEFINE_REFCOUNT( rpc::IGateKeeperCallback )
NI_DEFINE_REFCOUNT( rpc::IPipeProcessor )
