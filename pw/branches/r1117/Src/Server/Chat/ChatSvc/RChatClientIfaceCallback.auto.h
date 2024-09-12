#ifndef __R_ChatClientIfaceCallback_H__
#define __R_ChatClientIfaceCallback_H__

#include <RPC/RPC.h>


#include "ChatClientIfaceCallback.h"

namespace chat
{


class RIChatClientCallback : public IChatClientCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIChatClientCallback, IChatClientCallback, BaseObjectMT);
public:
  RPC_INFO("chat::IChatClientCallback", 0xfddadb45);
  
  RIChatClientCallback() : handler(0) {}
  RIChatClientCallback( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIChatClientCallback()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIChatClientCallback::ID(), RIChatClientCallback::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void OnRegisterUser(  SessionId _sid, UserId _userid, int _rc )
  {
    handler->Go(handler->Call( 0, _sid, _userid, _rc ));
  }
  void OnJoinChannel(  SessionId _sid, const ChannelName& _chnlname )
  {
    handler->Go(handler->Call( 1, _sid, _chnlname ));
  }
  void OnNewMessage(  SessionId _sid, const ChannelName& _chnlname, const NickName& _nickname, CustomId _useridGlobal, const wstring& _sourceMsg, const wstring& _fiteredMsg )
  {
    handler->Go(handler->Call( 2, _sid, _chnlname, _nickname, _useridGlobal, _sourceMsg, _fiteredMsg ));
  }



  bool Update(rpc::IUpdateCallback* callback=0)
  {
    return handler->Update(this, callback);
  }

  bool SetUpdateCallback(rpc::IUpdateCallback* callback=0)
  {
    return handler->SetUpdateCallback(callback);
  }

  void ReadOnly( bool val )
  {
    handler->ReadOnly( val );
  }

  void Publish()
  {
    handler->Publish();
  }
 
  StrongMT<rpc::INode> GetNode(int index) { return GetHandler()->GetNode(index); }
  StrongMT<rpc::INode> GetNode(const char* name) { return GetHandler()->GetNode(name); }
  virtual rpc::IUpdateCallback* GetUpdateCallback() { StrongMT<rpc::IRemoteEntity> _parent = parent.Lock(); return handler->GetUpdateCallback(_parent); }
  virtual void SetParent(rpc::IRemoteEntity* _parent) { parent = _parent; }
  virtual rpc::Status GetStatus() { return handler->GetStatus(); }

  static uint GetClassCrcStatic() { return 0xfddadb45; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ChatClientIfaceCallback_H__
