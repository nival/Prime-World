#pragma once

#include "Types.h"

namespace rpc
{
  enum ReservedMethodIds
  {
    Constructor = 0x3F,
    Destructor = Constructor-1,
    ReplicatedConstructor = Constructor-2,
    NoMethod = Constructor-3,
    LinkConstructor = Constructor-4,
    UpdateRequest = Constructor-5,
    UpdateData = Constructor-6,
    QueryRequest = Constructor-7,
    Ping = Constructor-8,
    SetGateInfo = Constructor-9,
    SharePtr = Constructor-10,
    Publish = Constructor-11,
    ForceLink = Constructor-12,
    __TheLastOne__ = Constructor-13,
  };


#pragma warning( disable: 4201 ) // warning C4201: nonstandard extension used : nameless struct/union

  struct MethodCallHeader 
  {
    union
    {
      byte data[2];
      struct  
      {
        byte isReturnValue: 1; // 1 - if call returns value, 0 - if not
        byte isDataMembersIncluded: 1; // 1 - if data members included to call data
        byte id: 6; // maximum 32 methods in entity
        byte paramsCount : 3;  // maximum 7 params
        byte entitySizeFlag : 2; // 0 - 1 byte, 1 - 2 bytes, 2-3 bytes, 3-4 bytes
        byte preAllocatedSizeFlag : 2; // 0 - 0 bytes, 1 - 1 bytes, 2 - 2 bytes
        byte dataSizeFlag: 1; // 0 - 2 bytes for data size, 1 - 4 bytes for data size
      };
    };
    EntityId entityId;
    nival::uint32_t dataSize;
    nival::uint16_t preAllocatedSize;     // filled from ArgWriter
    TransactionId transactionId;
    nival::uint32_t membersSize;
    union
    {
      byte dataFlags;
      struct  
      {
        byte isPublishOnCommit: 1;
        byte reserved: 7; 
      };
    };
    Transport::MessageMiscInfo miscInfo;

    void Optimize()
    {
      if (entityId <= 0xFF)
      {
        entitySizeFlag = 0;
      } else if (entityId <= 0xFFFF)
      {
        entitySizeFlag = 1;
      } else if (entityId <= 0xFFFFFF)
      {
        entitySizeFlag = 2;
      } else
      {
        entitySizeFlag = 3;
      }
      if (dataSize <= 0xFFFF)
      {
        dataSizeFlag = 0;
      } else
      {
        dataSizeFlag = 1;
      }
      if (preAllocatedSize == 0)
      {
        preAllocatedSizeFlag = 0;
      } else if (preAllocatedSize <= 0xFF)
      {
        preAllocatedSizeFlag = 1;
      } else 
      {
        preAllocatedSizeFlag = 2;
      }
    }

    inline uint GetParamsCount() const { return paramsCount; }
    inline uint GetPreAllocatedSize() const { return preAllocatedSize; }

    void Prepare( uint methodId)
    {
      crt::memset(data, 0, sizeof(data));
      id = methodId;
      Reset();
    }

    void Reset()
    {
      paramsCount = 0;
      dataFlags = 0;
      preAllocatedSize = 0;
      isReturnValue = false;
      dataSize = 0;
    }
  };

  struct PacketHeader
  {
    PacketHeader(nival::uint32_t _classCrc = 0xFFFFFFFF, uint _methodId = 0xFFFFFFFF)
      :classCrc(_classCrc),
      methodId(_methodId)
    {}

    uint classCrc;
    uint methodId;
  };

  bool ParsePacketHeader(const void*, uint, PacketHeader&);
}
