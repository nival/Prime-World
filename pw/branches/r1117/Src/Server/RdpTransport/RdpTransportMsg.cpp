#include "stdafx.h"
#include "RdpTransportMsg.h"

NI_DEFINE_REFCOUNT( rdp_transport::IMessageAllocator );

namespace rdp_transport
{

Message::Message( IMessageAllocator * _allctr, size_t _reserve ) :
allocator( _allctr )
{
  data.reserve( _reserve );
}



Message::~Message()
{
}



void Message::Setup( size_t _size )
{
  data.resize( _size );
}



void Message::FillUp( const void * _data, size_t _size, const Transport::MessageMiscInfo & _miscInfo )
{
  NI_VERIFY( data.size() == _size, "", return );
  if ( _size )
    memcpy( &data[0], _data, _size );

  miscInfo = _miscInfo;
}





Message * HeapAllocator::AllocateMsg( size_t _size )
{
  Message * msg = new Message( this, _size );
  msg->Setup( _size );
  return msg;
}

} //namesapce rdp_transport
