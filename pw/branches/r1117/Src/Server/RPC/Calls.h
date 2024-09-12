#pragma once

#include <Network/Message.h>
#include "ArgWriter.h"
#include "Parser.h"
#include "System/types.h"

namespace rpc 
{ 

class ArgReader;

  struct MethodCallInfo 
  {
    MethodCallInfo():writer(0) {}

    void SetEntityInfo(uint entityId, nival::uint32_t _classCrc)
    {
      header.entityId = entityId;
      classCrc = _classCrc;
    }
    void Reset(uint entityId, ArgWriter* _writer, nival::uint32_t classCrc)
    {
      SetEntityInfo(entityId, classCrc);
      writer = _writer;
      writer->Reset(&data);
    }
    inline const byte* Get() const { return &data[0]; }
    inline uint GetParamsCount() const { return header.GetParamsCount(); }
    inline uint GetPreAllocatedSize() const { return header.GetPreAllocatedSize(); }
    void SerializeCall(Stream& s, const nstl::vector<byte>* setData);
    uint Go(IPacketPipe * pipe, Stream& stream, const nstl::vector<byte>* setData, bool force=false);
    void Apply();

    MethodCallHeader header;
    nstl::vector<byte> data;
    ArgWriter* writer;
    nival::uint32_t classCrc;
  };

} // rpc

namespace rpc
{
  class MethodCall {
  public:
    MethodCallInfo info;
    MemoryStream stream;

    MethodCall(uint entityId, uint classCrc, IEntityMap* _entityMap=0):
    args(0)
    {
      args.SetEntityMap(_entityMap);
      Reset(entityId, classCrc);
    }

    ~MethodCall()
    {
    }

    void Reset(uint entityId, uint classCrc) { info.Reset(entityId, &args, classCrc); }
    ArgWriter& Prepare( uint methodId );

    uint GetParamsCount() const { return args.GetParamsCount(); }

    uint Go(IPacketPipe * pipe, bool force=false)
    {
      info.Apply();
      return info.Go(pipe, stream, 0, force);
    }

    void ReturnValue(uint methodId, uint transactionId)
    {
      info.header.transactionId = transactionId;
      info.header.isReturnValue = true;
      info.header.id = methodId;
    }
    EntityId GetEntityId() const { return info.header.entityId; }

    ArgWriter args;
    enum FailReason
    {
      OK,
      FailedEntitySize,
      FailedEntityHeader,
      FailedTransactionId,
      FailedRemainingDataSize,
      FailedDataSize,
      FailedPreallocatedSize,
    };
    static const byte* DeserializeCall(ArgReader& r, MethodCallHeader& targetCall, FailReason& reason);
    static const char* GetReason(FailReason reason);
  };

} // rpc
