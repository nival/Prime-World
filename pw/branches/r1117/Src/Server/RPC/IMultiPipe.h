#ifndef RPC_I_MULTI_PIPE_H__
#define RPC_I_MULTI_PIPE_H__

namespace rpc
{

struct INode;

_interface IMultiPipe : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( IMultiPipe, IBaseInterfaceMT );

public:
  virtual int GetCount() =0;
  virtual StrongMT<INode> GetNode(int index)=0;
};                                                                                  

}

#endif // RPC_I_MULTI_PIPE_H__
