#pragma once

namespace test
{

REMOTE class ISimpleRPCRabbitAck : public rpc::IRemoteEntity
{
  NI_DECLARE_CLASS_1( ISimpleRPCRabbitAck, rpc::IRemoteEntity );

public:
  RPC_ID();

  REMOTE virtual void Ack( int _value ) 
  {
    value = _value;
  }
  int value;
};


}


     