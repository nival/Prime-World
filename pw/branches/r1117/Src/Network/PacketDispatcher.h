#ifndef NETWORK_PACKETDISPATCHER_H_INCLUDED
#define NETWORK_PACKETDISPATCHER_H_INCLUDED

#include "System/ChunklessSaver.h"
#include "System/AddressOf.h"
#include <map>

namespace Network
{

  class IControlSizePacketHandler
  {
  public: 
    virtual uint GetContainerSizeLimit() const {return containerSizeLimit;}
    virtual uint GetTotalSizeLimit() const {return totalSizeLimit;}

  protected: 
    uint containerSizeLimit;
    uint totalSizeLimit; 
  };

class IPacketHandler : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IPacketHandler, IBaseInterfaceMT );

public:
  virtual bool Handle( const void * _data, size_t _size ) = 0;
  virtual bool Valid() = 0;
};



class PacketDispatcher : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( PacketDispatcher, BaseObjectMT );

private:
  const static size_t DefaultBufferSize = 4096;

public:
  typedef int PktId;

  PacketDispatcher();

  void AddHandler( PktId _msgid, IPacketHandler * _handler );

  template <class THostClass, class TPkt>
  void AddHandler( THostClass * _host, void (THostClass::*_func)( const TPkt & ) )
  {
    AddHandler( (PktId)TPkt::NI_SERIALIZE_ID(), new TypedHandler<THostClass, TPkt>( _host, _func ) );
  }

  bool Dispatch( const void * _data, size_t _size );

  void Cleanup();

  template <class TPkt>
  static bool SerializePacket( IPacketHandler * _handler, const TPkt & pkt )
  {
    CObj<Stream> stream = new MemoryStream( DefaultBufferSize );
    CObj<IBinSaver> saver = CreateChunklessSaver( stream, 0, false );

    (*stream) << (PktId)TPkt::NI_SERIALIZE_ID();

    TPkt & nonConstPkt = const_cast<TPkt & >( pkt );
    nonConstPkt & (*saver);

    size_t size = stream->GetPosition();

    if ( saver->GetError() != IBinSaver::BINSAVER_ERR_OK )
      return false;

    return _handler->Handle( size ? stream->GetBuffer() : 0, size );
  }

private:
  template <class THostClass, class TPkt>
  class TypedHandler : public IPacketHandler, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( TypedHandler, IPacketHandler, BaseObjectMT );
  public:
    TypedHandler( THostClass * _host, void (THostClass::*_func)( const TPkt & ) ) :
    host( _host ), func( _func ) {}

    virtual bool Handle( const void * _data, size_t _size )
    {
      StrongMT<THostClass> locked = host.Lock();
      if ( !locked )
        return false;

      FixedMemoryStream stream( _data, _size );
      IControlSizePacketHandler* p = dynamic_cast<IControlSizePacketHandler*>(locked.Get());
      CObj<IBinSaver> saver;
      if (p)
        saver = CreateChunklessSaver( nival::getaddressof( stream ), 0, true, p->GetContainerSizeLimit(), p->GetTotalSizeLimit());
      else 
        saver = CreateChunklessSaver( nival::getaddressof( stream ), 0, true);
      TPkt pkt;
      pkt & *saver;

      if ( saver->GetError() != IBinSaver::BINSAVER_ERR_OK )
        return false;

      (locked.Get()->*func)( pkt );
      return true;
    }

    virtual bool Valid() { return host.Lock().Valid(); }

  private:
    WeakMT<THostClass>  host;
    void (THostClass::*func)( const TPkt & );
  };

  typedef std::map<PktId, StrongMT<IPacketHandler> > Handlers;

  Handlers  handlers;
};

} //namespace Network

#endif //NETWORK_PACKETDISPATCHER_H_INCLUDED
