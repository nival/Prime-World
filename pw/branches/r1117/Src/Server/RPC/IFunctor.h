#ifndef RPC_I_FUNCTOR_H__
#define RPC_I_FUNCTOR_H__

#include "Types.h"

namespace rpc
{

_interface IFunctor
{
  virtual ~IFunctor() {}
  virtual bool Call(VArgList v)=0;
  virtual void OnFailure(rpc::CallStatus status)=0;
};

}

#endif // RPC_I_FUNCTOR_H__
