#ifndef __R_ChatClientIface_H__
#define __R_ChatClientIface_H__

#include <RPC/RPC.h>
#include "Chat/ChatTypes.h"
#include "ChatSvc/ChatClientIfaceCallback.h"




namespace chat
{


class RIChatClient : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIChatClient, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("chat::IChatClient", 0xa130333a);
  
  RIChatClient() : handler(0) {}
  RIChatClient( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIChatClient()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIChatClient::ID(), RIChatClient::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }


  template <typename T>
  rpc::ECallResult::Enum RegisterUser( chat::CustomId _sidGlobal, chat::CustomId _useridGlobal, chat::NickName const & _nickname, NI_LPTR IChatClientCallback* _cb, T* object, void (T::*func)(int result) )
  {           
    rpc::Transaction* transaction = handler->Call( 0, _sidGlobal, _useridGlobal, _nickname, RemotePtr<RIChatClientCallback>(_cb) );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, int>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum RegisterUser( chat::CustomId _sidGlobal, chat::CustomId _useridGlobal, chat::NickName const & _nickname, NI_LPTR IChatClientCallback* _cb, T* object, void (T::*func)(int result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 0, _sidGlobal, _useridGlobal, _nickname, RemotePtr<RIChatClientCallback>(_cb) );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, int, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  
  void SendMsg(  chat::SessionId _sid, chat::ChannelName const & _chnlname, chat::UserId _from, wstring const & _msg )
  {
    handler->Go(handler->Call( 1, _sid, _chnlname, _from, _msg ));
  }
  void UnregisterUser(  chat::CustomId _sidGlobal, chat::UserId _useridLocal )
  {
    handler->Go(handler->Call( 2, _sidGlobal, _useridLocal ));
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

  static uint GetClassCrcStatic() { return 0xa130333a; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ChatClientIface_H__
