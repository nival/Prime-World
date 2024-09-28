#ifndef GAMESTATCLIENT_H_INCLUDED
#define GAMESTATCLIENT_H_INCLUDED

//
// A T T E N T I O N
//
// This class is used both in server and client
//

#include "System/JobThread.h"
#include "System/ChunklessSaver.h"


namespace StatisticService
{

typedef vector<byte> TMessageData;


class IStatDataDispatcher : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IStatDataDispatcher, IBaseInterfaceMT );
public:
  virtual bool DispatchChunk( const TMessageData & _data, unsigned _msgNumber ) = 0;
  virtual bool GetPermittedEventsChunk( TMessageData & _data ) = 0;
};


class GameStatClientImplementation;

class GameStatClient : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( GameStatClient, BaseObjectMT );
public:
  GameStatClient( IStatDataDispatcher * _dispatcher, int _filtrationListMaxTries = -1 );

  bool Ready() const;

  template <class TMsg>
  bool Message( const TMsg & msg )
  {
    if ( Ready() )
    {
      if ( IsMethodInabled( TMsg::NI_SERIALIZE_ID() ) )
      {
        TMessageData buffer;
        Serialize( buffer, msg );
        PostRawMessage( TMsg::NI_SERIALIZE_ID(), buffer );
      }
      return true;
    }

    return false;
  }

  void PostRawMessage( unsigned msgid, const TMessageData & data );

  bool IsSessionEventEnabled( int evtId ) const;

private:
  bool                                    filtrationEnabled;
  StrongMT<GameStatClientImplementation>  implementation;
  StrongMT<threading::JobThread>          thread;


  template <class TMsg>
  void Serialize( TMessageData & buffer, const TMsg & msg )
  {
    const size_t defaultBufferSize = 1024;

    CObj<Stream> stream = new MemoryStream( defaultBufferSize );
    CObj<IBinSaver> saver = CreateChunklessSaver( stream, 0, false );

    TMsg & nonConstMsg = const_cast<TMsg & >( msg );
    nonConstMsg & (*saver);
    saver = 0;

    size_t size = stream->GetPosition();

    buffer.resize( size, 0 );
    if ( size )
      memcpy( &buffer[0], stream->GetBuffer(), size );
  }

  bool IsMethodInabled( int id ) const;
};

} //namespace StatisticService

#endif //GAMESTATCLIENT_H_INCLUDED
