#ifndef __R_ChatManagementIface_H__
#define __R_ChatManagementIface_H__

#include <RPC/RPC.h>
#include "ClusterTypes/ClusterTypes.h"
#include "ChatManagementIface.h"


#include "ChatManagementIface.h"

namespace chat
{


class RIOpenSessionCallback : public IOpenSessionCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIOpenSessionCallback, IOpenSessionCallback, BaseObjectMT);
public:
  RPC_INFO("chat::IOpenSessionCallback", 0xf9cb56ad);
  
  RIOpenSessionCallback() : handler(0) {}
  RIOpenSessionCallback( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIOpenSessionCallback()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIOpenSessionCallback::ID(), RIOpenSessionCallback::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void OnOpenSession(  Result::Enum _rc, SessionId _sid )
  {
    handler->Go(handler->Call( 0, _rc, _sid ));
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

  static uint GetClassCrcStatic() { return 0xf9cb56ad; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}

#include "ChatManagementIface.h"

namespace chat
{


class RIOpenChannelCallback : public IOpenChannelCallback, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIOpenChannelCallback, IOpenChannelCallback, BaseObjectMT);
public:
  RPC_INFO("chat::IOpenChannelCallback", 0x2d10ce14);
  
  RIOpenChannelCallback() : handler(0) {}
  RIOpenChannelCallback( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIOpenChannelCallback()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIOpenChannelCallback::ID(), RIOpenChannelCallback::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void OnOpenChannel(  Result::Enum _rc, SessionId _sid, ChannelId chnlid, CustomId _ctmid )
  {
    handler->Go(handler->Call( 0, _rc, _sid, chnlid, _ctmid ));
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

  static uint GetClassCrcStatic() { return 0x2d10ce14; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



namespace chat
{


class RIChatManagement : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIChatManagement, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("chat::IChatManagement", 0x76a6e04a);
  
  RIChatManagement() : handler(0) {}
  RIChatManagement( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIChatManagement()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIChatManagement::ID(), RIChatManagement::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void OpenSession(  chat::SessionInfo const & _si, NI_LPTR chat::IOpenSessionCallback* _cb )
  {
    handler->Go(handler->Call( 0, _si, RemotePtr<chat::RIOpenSessionCallback>(_cb) ));
  }
  void CloseSession(  chat::SessionId _sid )
  {
    handler->Go(handler->Call( 1, _sid ));
  }
  void OpenChannel(  ChannelInfo const & _chinfo, chat::SessionId _sid, CustomId _ctmid, NI_LPTR chat::IOpenChannelCallback* _cb )
  {
    handler->Go(handler->Call( 2, _chinfo, _sid, _ctmid, RemotePtr<chat::RIOpenChannelCallback>(_cb) ));
  }
  void CloseChannel(  ChannelId _chnlid, chat::SessionId _sid )
  {
    handler->Go(handler->Call( 3, _chnlid, _sid ));
  }

  template <typename T>
  rpc::ECallResult::Enum AddUser2Channel( chat::CustomId _useridGlobal, chat::SessionId _sid, bool channelMuted, chat::ChannelName const & _chnlname, T* object, void (T::*func)(Result::Enum result) )
  {           
    rpc::Transaction* transaction = handler->Call( 4, _useridGlobal, _sid, channelMuted, _chnlname );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, Result::Enum>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum AddUser2Channel( chat::CustomId _useridGlobal, chat::SessionId _sid, bool channelMuted, chat::ChannelName const & _chnlname, T* object, void (T::*func)(Result::Enum result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 4, _useridGlobal, _sid, channelMuted, _chnlname );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, Result::Enum, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum RemoveUser( chat::CustomId _useridGlobal, chat::SessionId _sid, chat::ChannelName const & _chnlname, T* object, void (T::*func)(Result::Enum result) )
  {           
    rpc::Transaction* transaction = handler->Call( 5, _useridGlobal, _sid, _chnlname );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, Result::Enum>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum RemoveUser( chat::CustomId _useridGlobal, chat::SessionId _sid, chat::ChannelName const & _chnlname, T* object, void (T::*func)(Result::Enum result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 5, _useridGlobal, _sid, _chnlname );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, Result::Enum, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
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

  static uint GetClassCrcStatic() { return 0x76a6e04a; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_ChatManagementIface_H__
