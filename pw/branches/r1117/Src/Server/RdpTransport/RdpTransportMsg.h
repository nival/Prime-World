#ifndef RDPTRANSPORTMSG_H_INCLUDED
#define RDPTRANSPORTMSG_H_INCLUDED

#include <vector>
#include "Network/Transport.h"

namespace rdp_transport
{

class Message;

class IMessageAllocator : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IMessageAllocator, IBaseInterfaceMT );
public:
  virtual Message * AllocateMsg( size_t _size ) = 0;
};



class Message : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( Message, BaseObjectMT );
public:
  Message( IMessageAllocator * _allctr, size_t _reserve );
  ~Message();

  void Setup( size_t _size );

  void FillUp( const void * _data, size_t _size, const Transport::MessageMiscInfo & _miscInfo );

  const byte * Data() const { return data.empty() ? 0 : &data[0]; }
  size_t Size() const { return data.size(); }
  size_t Capacity() const { return data.capacity(); }

  Transport::MessageMiscInfo MiscInfo() const { return miscInfo; }

private:
  std::vector<byte>   data;
  Transport::MessageMiscInfo miscInfo;
  WeakMT<IMessageAllocator> allocator;
};



class HeapAllocator : public IMessageAllocator, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( HeapAllocator, IMessageAllocator, BaseObjectMT );
public:
  HeapAllocator() {}

  virtual Message * AllocateMsg( size_t _size );

private:
};

} //namesapce rdp_transport

#endif //RDPTRANSPORTMSG_H_INCLUDED
