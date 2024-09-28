#include "stdafx.h"
#include "GameStatClient.h"
#include "SpecialStatisticTypes.h"
#include "System/AddressOf.h"
#include "System/sleep.h"


namespace StatisticService
{

static float      s_retry_timeout_limit = 240.0f;
static unsigned   s_chunk_size_limit = 64 * 1024;
static unsigned   s_chunk_number_limit = 1024;
static float      s_chunk_timeout = 600.0f;
static unsigned   s_queue_limit = 256;

REGISTER_VAR( "stat_retry_timeout_limit", s_retry_timeout_limit, STORAGE_NONE );
REGISTER_VAR( "stat_chunk_limit", s_chunk_size_limit, STORAGE_NONE );
REGISTER_VAR( "stat_chunk_msg_limit", s_chunk_number_limit, STORAGE_NONE );
REGISTER_VAR( "stat_chunk_timeout", s_chunk_timeout, STORAGE_NONE );


static ni_detail::UInt32 DATA_MARKER = 0xc001face;




class GameStatClientImplementation : public BaseObjectMT, public threading::IThreadJob
{
  NI_DECLARE_REFCOUNT_CLASS_2( GameStatClientImplementation, BaseObjectMT, threading::IThreadJob );

public:
  typedef set<int> Filter;

  GameStatClientImplementation( IStatDataDispatcher * _dispatcher, int _filtrationListMaxTries ) :
  dispatcher( _dispatcher ),
  filtrationListMaxTries( _filtrationListMaxTries ),
  ready( false )
  {}

  volatile const bool & Ready() const { return ready; }
  const Filter & MethodsFilter() const { return methodsFilter; }
  const Filter & SessionEventsFilter() const { return sessionEventsFilter; }

  void PostRawMessage( unsigned msgid, const TMessageData & data )
  {
    time_t timestamp = 0;
    time( &timestamp );

    threading::MutexLock lock( inputMutex );

    size_t sizeAdd = data.size() + 4 * sizeof( ni_detail::UInt32 );

    if ( currentChunk && !currentChunk->bytes.empty() )
      if ( ( currentChunk->bytes.size() + sizeAdd >= s_chunk_size_limit ) || ( currentChunk->messagesNumber >= s_chunk_number_limit ) )
      {
        PutChunkInQueue( currentChunk );
        currentChunk = 0;
      }

    if ( !currentChunk )
      currentChunk = new Chunk( timer::Now(), s_chunk_size_limit );

    size_t start = currentChunk->bytes.size();
    currentChunk->bytes.resize( start + sizeAdd );
    ni_detail::UInt32 * dest = (ni_detail::UInt32 *)&currentChunk->bytes[start];

    *dest = DATA_MARKER;
    ++dest;

    *dest = msgid;
    ++dest;

    *dest = (ni_detail::UInt32)timestamp;
    ++dest;

    *dest = (ni_detail::UInt32)data.size();
    ++dest;

    if ( data.size() )
      memcpy( dest, &data[0], data.size() );

    ++currentChunk->messagesNumber;
  }



  void Flush()
  {
    {
      threading::MutexLock lock( inputMutex );
      if ( currentChunk && !currentChunk->bytes.empty() )
        PutChunkInQueue( currentChunk );
      currentChunk = 0;
    }

    while ( true )
    {
      StrongMT<Chunk> chunk;
      {
        threading::MutexLock lock( queueMutex );
        if ( queue.empty() )
          return;
        chunk = queue.front();
        queue.pop_front();
      }
      dispatcher->DispatchChunk( chunk->bytes, chunk->messagesNumber );
    }
  }

protected:
  //threading::IThreadJob
  virtual void Work( volatile bool & isRunning )
  {
    RetrieveFiltrationList( isRunning );
    DispatchChunks( isRunning );

    Flush();
  }

private:
  struct Chunk : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( Chunk, BaseObjectMT );
    timer::Time   creationTime;
    unsigned      messagesNumber;
    TMessageData  bytes;
    Chunk( timer::Time _now, size_t _reserve ) :
    creationTime( _now ),
    messagesNumber( 0 )
    {
      bytes.reserve( _reserve );
    }
  };

  typedef list<StrongMT<Chunk> > ChunkQueue;

  StrongMT<IStatDataDispatcher>   dispatcher;

  const int                       filtrationListMaxTries;
  volatile bool                   ready;
  Filter                          methodsFilter, sessionEventsFilter;

  threading::Mutex                inputMutex, queueMutex;
  StrongMT<Chunk>                 currentChunk;
  ChunkQueue                      queue;



  void RetrieveFiltrationList( volatile bool & isRunning )
  {
    if ( filtrationListMaxTries <= 0 )
    {
      ready = true;
      return;
    }

    int tryIndex = 0;
    timer::Time nextTry = 0, nextPause = 1.0;
    while ( isRunning )
    {
      if ( tryIndex >= filtrationListMaxTries )
        break;

      timer::Time now = timer::Now();

      if ( now > nextTry )
      {
        if ( TryRetrieveFiltrationList() )
          break;
        ++tryIndex;
        nextTry = now + nextPause;
        nextPause = Min( nextPause * 2.0, (timer::Time)s_retry_timeout_limit );
      }
      nival::sleep( 100 );
    }
  }


  void DispatchChunks( volatile bool & isRunning )
  {
    timer::Time nextTry = 0, nextPause = 1.0;
    while ( isRunning )
    {
      CheckCurrentChunkTimeout();

      timer::Time now = timer::Now();

      if ( now > nextTry )
      {
        if ( DispatchSingleChunk() )
        {
          nextTry = 0;
          nextPause = 1.0;
        }
        else
        {
          nextTry = now + nextPause;
          nextPause = Min( nextPause * 2.0, (timer::Time)s_retry_timeout_limit );
        }
      }
      nival::sleep( 100 );
    }
  }


  bool TryRetrieveFiltrationList()
  {
    TMessageData data;
    if ( !dispatcher->GetPermittedEventsChunk( data ) )
      return false;

    MessageTrace( "Got permitted events data. size=%d", data.size() );

    if ( data.empty() )
    {
      methodsFilter.clear();
      sessionEventsFilter.clear();
      ready = true;
      return true;
    }

    FixedMemoryStream stream( &data[0], data.size() );
    CObj<IBinSaver> saver = CreateChunklessSaver( nival::getaddressof( stream ), 0, true );

    RPC::PermittedStatisticsMethods events;

    events.operator &( *saver );

    MessageTrace( "Got permitted events. methods=%d, sessionEvents=%d", events.methods.size(), events.sessionEvents.size() );

    methodsFilter.clear();
    sessionEventsFilter.clear();

    for ( int i = 0; i < events.methods.size(); ++i )
      methodsFilter.insert( events.methods[i] );

    for ( int i = 0; i < events.sessionEvents.size(); ++i )
      sessionEventsFilter.insert( events.sessionEvents[i] );

    ready = true;
    return true;
  }


  void CheckCurrentChunkTimeout()
  {
    threading::MutexLock lock( inputMutex );

    if ( currentChunk && !currentChunk->bytes.empty() )
    {
      timer::Time t = timer::Now();
      if ( t > ( currentChunk->creationTime + s_chunk_timeout ) )
      {
        PutChunkInQueue( currentChunk );
        currentChunk = 0;
      }
    }
  }


  void PutChunkInQueue( Chunk * chunk )
  {
    MessageTrace( "New statistics data chunk. size=%u, msg_num=%u, lifetime=%.1f", chunk->bytes.size(), chunk->messagesNumber, timer::Now() - chunk->creationTime );

    threading::MutexLock lock( queueMutex );
    if ( (size_t)queue.size() < s_queue_limit )
      queue.push_back( chunk );
    else
      ErrorTrace( "Statistics queue overflow. size=%d", queue.size() );
  }


  bool DispatchSingleChunk()
  {
    StrongMT<Chunk> chunk;

    {
      threading::MutexLock lock( queueMutex );
      if ( queue.empty() )
        return true;

      chunk = queue.front();
      queue.pop_front();
    }

    NI_VERIFY( !chunk->bytes.empty(), "", return true );
    
    MessageTrace( "Dispatching statistics data chunk. size=%u, msg_num=%u", chunk->bytes.size(), chunk->messagesNumber );

    if ( !dispatcher->DispatchChunk( chunk->bytes, chunk->messagesNumber ) )
    {
      threading::MutexLock lock( queueMutex );
      queue.push_front( chunk );
      return false;
    }
    return true;
  }
};










GameStatClient::GameStatClient( IStatDataDispatcher * _dispatcher, int _filtrationListMaxTries ) :
filtrationEnabled( _filtrationListMaxTries != 0 )
{
  implementation = new GameStatClientImplementation( _dispatcher, _filtrationListMaxTries );
  thread = new threading::JobThread( implementation, "GameStat", 30000 );
}



bool GameStatClient::Ready() const
{
  return implementation->Ready();
}



void GameStatClient::PostRawMessage( unsigned msgid, const TMessageData & data )
{
  implementation->PostRawMessage( msgid, data );
}



bool GameStatClient::IsSessionEventEnabled( int evtId ) const
{
  if ( !filtrationEnabled )
    return true;
  if ( !implementation->Ready() )
    return false;
  return implementation->SessionEventsFilter().find( evtId ) != implementation->SessionEventsFilter().end();
}



bool GameStatClient::IsMethodInabled( int id ) const
{
  if ( !filtrationEnabled )
    return true;
  if ( !implementation->Ready() )
    return false;
  return implementation->MethodsFilter().find( id ) != implementation->MethodsFilter().end();
}

} //namespace StatisticService
