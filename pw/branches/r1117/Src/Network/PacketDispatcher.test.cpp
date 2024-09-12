//!Component( "Network/PacketDispatcher" )

#include <cxxtest/TestSuite.h>
#include "PacketDispatcher.h"
#include "RPC/RPC.h"


struct PacketDispatcherTestData : public rpc::Data
{
  SERIALIZE_ID();

  ZDATA
  ZNOPARENT(rpc::Data)
  int i;
  string s;
  ZEND int operator&( IBinSaver &f ) { f.Add(2,&i); f.Add(3,&s); return 0; }

  bool operator == (const PacketDispatcherTestData & other ) const { return ( i == other.i ) && ( s == other.s ); }

  PacketDispatcherTestData() : i( 0 ) {}
  PacketDispatcherTestData( int _i, const char * _s ) : i( _i ), s( _s ) {}
};


SERIALIZE_FACTORY( PacketDispatcherTestData );

struct PacketDispatcherTest : public CxxTest::TestSuite 
{
  virtual void setUp()
  {
  }
  
  virtual void tearDown()
  {
  }

  struct RawHandler : public Network::IPacketHandler, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_2( RawHandler, Network::IPacketHandler, BaseObjectMT );

  public:
    RawHandler() {}

    virtual bool Handle( const void * _data, size_t _size )
    {
      bytes.resize( _size );
      if ( _size )
        memcpy( &bytes[0], _data, _size );
      return true;
    }

    virtual bool Valid()
    {
      return true;
    }

    std::vector<byte> bytes;
  };



  struct TypedHandler : public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( TypedHandler, BaseObjectMT );
  public:
    TypedHandler( const PacketDispatcherTestData & _expectedData ) : expectedData( _expectedData ){}
    void OnTestData( const PacketDispatcherTestData & _data )
    {
      TS_ASSERT( expectedData == _data );
    }
    const PacketDispatcherTestData expectedData;
  };

  struct ControlSizeTypedHandler : public Network::IControlSizePacketHandler, public BaseObjectMT
  {
    NI_DECLARE_REFCOUNT_CLASS_1( TypedHandler, BaseObjectMT );
  public:
    ControlSizeTypedHandler( const PacketDispatcherTestData & _expectedData ) : expectedData( _expectedData ) 
    {
      containerSizeLimit = 256;
      totalSizeLimit = 256;
    }
    void OnTestData( const PacketDispatcherTestData & _data )
    {
      TS_ASSERT( expectedData == _data );
    }


    const PacketDispatcherTestData expectedData;

  };


  void test_serialize()
  {
    Network::PacketDispatcher d;
    PacketDispatcherTestData data( 5, "25" );
    StrongMT<RawHandler> rawHandler = new RawHandler;
    TS_ASSERT( d.SerializePacket( rawHandler, data ) );
    TS_ASSERT_EQUALS( rawHandler->bytes.size(), 14 );
  }



  void test_dispatch()
  {
    Network::PacketDispatcher d;
    PacketDispatcherTestData data( 5, "25" );

    StrongMT<TypedHandler> typedHandler = new TypedHandler( data );

    d.AddHandler( typedHandler.Get(), &TypedHandler::OnTestData );

    StrongMT<RawHandler> serialzd = new RawHandler;
    TS_ASSERT( Network::PacketDispatcher::SerializePacket( serialzd, data ) );

    TS_ASSERT( d.Dispatch( &serialzd->bytes[0], serialzd->bytes.size() ) );

    TS_ASSERT( d.Dispatch( &serialzd->bytes[0], serialzd->bytes.size() ) );

    typedHandler = 0;

    TS_ASSERT( !d.Dispatch( &serialzd->bytes[0], serialzd->bytes.size() ) );

    d.Cleanup();
  }

  void test_dispatch_big_packet()
  {
    Network::PacketDispatcher d;
    std::string s = "";
    unsigned int big_size = 257;
    while (s.size() <= big_size)
        s += "1234567890";
    PacketDispatcherTestData data( s.size(), s.c_str() );

    StrongMT<ControlSizeTypedHandler> typedHandler = new ControlSizeTypedHandler( data );


    d.AddHandler( typedHandler.Get(), &ControlSizeTypedHandler::OnTestData );

    StrongMT<RawHandler> serialzd = new RawHandler;
    TS_ASSERT( Network::PacketDispatcher::SerializePacket( serialzd, data ) );

    TS_ASSERT( !d.Dispatch( &serialzd->bytes[0], serialzd->bytes.size() ) );

    TS_ASSERT( !d.Dispatch( &serialzd->bytes[0], serialzd->bytes.size() ) );

    typedHandler = 0;

    TS_ASSERT( !d.Dispatch( &serialzd->bytes[0], serialzd->bytes.size() ) );

    d.Cleanup();
  }

};
