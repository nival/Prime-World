#pragma once

#include "TransportPipe.h"
#include "Base.h"
#include <System/noncopyable.h>
namespace rpc
{ 
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct TransportEndpoint : public IPacketPipe, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( TransportEndpoint, IPacketPipe, BaseObjectMT );
  public:
    TransportEndpoint( Transport::IChannel* channel )
      : channel(channel)
    {
      char buffer[32];
/*      if ( channel->GetAddress().IsClientConnection() )
        sprintf_s(buffer, 32, "%s:%d", channel->GetAddress().target.c_str(), channel->GetAddress().client );
      else
*/
      NStr::Printf(buffer, 32, "%s", channel->GetAddress().target.c_str() );
      name = buffer;
    }

    ~TransportEndpoint()
    {
      Reset();
      channel = 0;
    }

    virtual const char* GetName() const 
    { 
      return name.c_str(); 
    }
    
    virtual Transport::IChannel * GetPipeChannel() const { return channel; }

    virtual IPacketPipe::PipeInfo GetInfo() const 
    { 
      rpc::IPacketPipe::PipeInfo info = {ConvertStatus(channel), channel?channel->GetInternalClientId():-1}; 
      return info; 
    }


    virtual void Send( const byte* data, int size, bool force )
    {
      channel->SendRaw( data, size );
    }

    virtual bool Recieve(int index, byte** data, int* size, Transport::MessageMiscInfo & miscInfo )
    {
//      nstl::vector<byte> buf;
      bool result = channel->ReceiveRaw( &dataCache );

      if( result ) // !!!!!
      {
        *data = dataCache.begin(); *size = dataCache.size(); // TODO: remove allocation
//        swap( buf, dataCache.push_back() );
      }
      return result;
    }

    virtual void Reset() 
    {
      dataCache.clear();
    }

//    nstl::list<nstl::vector<byte>> dataCache;
    nstl::vector<byte> dataCache;
    StrongMT<Transport::IChannel> channel;
    nstl::string name;
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct TransportCorruptedPacketProcessor : public rpc::IPipeProcessor
  {
    virtual void OnCorruptData(rpc::IPacketPipe * pipe)
    {
      TransportEndpoint* pEndpoint = checked_cast<TransportEndpoint*>( pipe );

      NI_VERIFY( pEndpoint->channel != NULL, "Corrupted endpoint", return );

      const Transport::Address& addr = pEndpoint->channel->GetAddress();
      systemLog( NLogg::LEVEL_WARNING ) << "Corrupted RPC packet received from channel (" << addr.target.c_str() << ":" << addr.sender << "->" << addr.client << ")" << endl;
      pEndpoint->channel->Close();
    }
  };
  ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  struct P2PNode : public NonCopyable
  {
    StrongMT<rpc::Node> node;
    WeakMT<rpc::Gate> gate;
    StrongMT<TransportEndpoint> endpoint;
  public:
    P2PNode( Transport::IChannel* channel, rpc::Gate* gate )
      : endpoint( new TransportEndpoint( channel ) ), gate( gate )
    {
      node = gate->AddPipe( endpoint, 0 );
    }

    void Poll()
    {
      StrongMT<rpc::Gate> sGate = gate.Lock();
      if (sGate)
      {
        sGate->Poll();
      }
    }

    ~P2PNode()
    {
      StrongMT<rpc::Gate> sGate = gate.Lock();
      if ( sGate )
      {
        sGate->RemovePipe( node );
        node = 0;
      }
    }
  };
} // rpc
