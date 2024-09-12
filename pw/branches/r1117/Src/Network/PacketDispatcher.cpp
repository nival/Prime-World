#include "stdafx.h"
#include "PacketDispatcher.h"

namespace Network
{

PacketDispatcher::PacketDispatcher()
{
}



void PacketDispatcher::AddHandler( PktId _pktid, IPacketHandler * _handler )
{
  StrongMT<IPacketHandler> & slot = handlers[_pktid];
  NI_ASSERT( !slot.Valid(), "" );

  slot = _handler;
}



bool PacketDispatcher::Dispatch( const void * _data, size_t _size )
{
  NI_VERIFY( _size >= sizeof( PktId ), "", return false );

  PktId & pktid = *(PktId *)(_data);

  Handlers::iterator it = handlers.find( pktid );
  if ( it == handlers.end() )
  {
    ErrorTrace( "Unknown packet id. pktid=%d, size=%d", pktid, _size );
    return false;
  }

  return it->second->Handle( (const byte *)_data + sizeof( PktId ), _size - sizeof( PktId ) );
}



void PacketDispatcher::Cleanup()
{
  for ( Handlers::iterator it = handlers.begin(); it != handlers.end(); )
    if ( it->second->Valid() )
      ++it;
    else
#if defined( NV_WIN_PLATFORM )
      it = handlers.erase( it );
#elif defined( NV_LINUX_PLATFORM )
    {
      Handlers::iterator toDel = it;
      ++it;
      handlers.erase( toDel );
    }
#endif
}

} //namespace Network
