#pragma once

#include "RPCMixin.h"

#include "SimpleRPCRabbitTypes.h"
#include "SimpleRPCRabbitAck.h"

struct RabbitData : rpc::Data
{
  SERIALIZE_ID();
  
  int i;
  float f;
  int operator&( IBinSaver &_f ) { _f.Add(2,&i); _f.Add(3,&f); return 0; }
};


namespace test
{

REMOTE struct SimpleRPCRabbit : public BaseObjectMT
{
  RPC_ID();
  NI_DECLARE_REFCOUNT_CLASS_1(SimpleRPCRabbit, BaseObjectMT);
public:
  bool is_processed;
  int id;
  nstl::string sS;
  nstl::string cS;
  nstl::vector<int> vI;
  RabbitData data;
  test::InitialSnapshot msg;
  bool isSnapshotRecieved;
  nstl::wstring sW;
  FixedVector<float, 20> ff;
    
  SimpleRPCRabbit()
    :   is_processed(false),
  isSnapshotRecieved(false),
  id(0xFFFFFFFF)
    {
  }

  SimpleRPCRabbit(const char* _cS, const nstl::string& _sS, const nstl::vector<int>& _vI, const RabbitData& _data)
    :   is_processed(false),
  isSnapshotRecieved(false),
  id(0xFFFFFFFF),
  cS(_cS),
  sS(_sS),
  vI(_vI),
  data(_data)
    {
  }

  SimpleRPCRabbit(int _id)
    :   id(_id) 
    {
  }

  SimpleRPCRabbit(const nstl::wstring& _sW):  
    sW(_sW)
  {
  }

  SimpleRPCRabbit(const FixedVector<float, 20>& _ff, int dummy):  
    ff(_ff)
  {
  }

  REMOTE void process()
  {
    is_processed = true;
  }

  REMOTE int processIntWithReturnValueIntAsync(int value) 
  {
      return 3*value;
  }
  
  REMOTE void processSnapshot(const test::InitialSnapshot& _msg)
  {
    msg = _msg;
    isSnapshotRecieved = true;
  }
  
  REMOTE const InitialSnapshot& GetServerDef() 
  {
    return msg;
  }

  REMOTE void Roll(const test::SPreGameData& _preGame, const test::SPostGameData& _postGame, NI_LPTR test::ISimpleRPCRabbitAck* _ack)
  {
    test::SPreGameData preGame = _preGame;   // just copy to be sure that structs are ok
    test::SPostGameData postGame = _postGame;
    is_processed = true;
    if (_ack)
    {
      _ack->Ack(456);
    }
  }
};

REMOTE struct SimpleRefCountedRPCRabbit : BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1(SimpleRefCountedRPCRabbit, BaseObjectMT);
  RPC_ID();
  bool is_processed;

  SimpleRefCountedRPCRabbit()
    :is_processed( false ) 
  {}
  ~SimpleRefCountedRPCRabbit()
  {
  }

  REMOTE void process()
  {
    is_processed = true;
  }

  REMOTE void processWithRecieveTime(const NHPTimer::STime& __recieveTime__)
  {
    is_processed = true;
  }
};

} // test
     