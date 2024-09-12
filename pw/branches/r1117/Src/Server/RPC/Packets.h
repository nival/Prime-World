#pragma once

#include "System/HPTimer.h"
#include "Network/Transport.h"
#include "System/Pointers/Pointers.h"

#pragma warning(disable:4100)

namespace Transport
{
  _interface IChannel;
}

namespace threading
{
class Event;
class Mutex;
}// threading

namespace rpc 
{

enum CallStatus
{
  CallPending,
  CallSuccessful,
  CallTimedOut,
  PipeDisconnected,
};

const char * CallStatusToString( CallStatus _st );

_interface IPacketPipe : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IPacketPipe, IBaseInterfaceMT );

public:
  struct PipeInfo
  {
    enum Status
    {
      Connecting,
      Connected,
      Closed,
    };
    Status status;
    int pipeId;
  };
  virtual void Send( const byte* data, int size, bool force )=0;
  virtual bool Recieve(int index, byte** data, int* size, Transport::MessageMiscInfo & _miscInfo)=0;
  virtual void Reset()=0;
  virtual const char* GetName() const { return 0; }
  virtual PipeInfo GetInfo() const=0;
  virtual Transport::IChannel * GetPipeChannel() const { return 0; }; //For diagnostics mainly
};

_interface IPipeProcessor : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IPipeProcessor, IBaseInterfaceMT );

  virtual ~IPipeProcessor() = 0;
  virtual void OnCorruptData(IPacketPipe * pipe)=0;
  virtual StrongMT<IPacketPipe> ConnectToPipe(const char* name, const GUID& id)=0;
  virtual const char* GetName() const { return 0; }
};

inline IPipeProcessor::~IPipeProcessor() {}

} // rpc
