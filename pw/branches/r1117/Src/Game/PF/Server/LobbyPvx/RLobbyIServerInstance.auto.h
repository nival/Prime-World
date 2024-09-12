#ifndef __R_LobbyIServerInstance_H__
#define __R_LobbyIServerInstance_H__

#include <RPC/RPC.h>
#include "CommonTypes.h"




namespace lobby
{


class RIServerInstance : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RIServerInstance, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("lobby::IServerInstance", 0x94e70ebd);
  
  RIServerInstance() : handler(0) {}
  RIServerInstance( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RIServerInstance()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RIServerInstance::ID(), RIServerInstance::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void SetDeveloperSex(  int _sex )
  {
    handler->Go(handler->Call( 0, _sex ));
  }
  void RequestGamesList( )
  {
    handler->Go(handler->Call( 1 ));
  }

  template <typename T>
  rpc::ECallResult::Enum JoinGame( int gameId, T* object, void (T::*func)(EOperationResult::Enum result) )
  {           
    rpc::Transaction* transaction = handler->Call( 2, gameId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, EOperationResult::Enum>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum JoinGame( int gameId, T* object, void (T::*func)(EOperationResult::Enum result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 2, gameId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, EOperationResult::Enum, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum ReconnectToCustomGame( int gameId, int team, const string & heroId, T* object, void (T::*func)(EOperationResult::Enum result) )
  {           
    rpc::Transaction* transaction = handler->Call( 3, gameId, team, heroId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, EOperationResult::Enum>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum ReconnectToCustomGame( int gameId, int team, const string & heroId, T* object, void (T::*func)(EOperationResult::Enum result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 3, gameId, team, heroId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, EOperationResult::Enum, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum CreateCustomGame( int maxPlayers, int maxPlayersPerTeam, const string & mapId, int autostartPlayers, T* object, void (T::*func)(EOperationResult::Enum result) )
  {           
    rpc::Transaction* transaction = handler->Call( 4, maxPlayers, maxPlayersPerTeam, mapId, autostartPlayers );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, EOperationResult::Enum>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum CreateCustomGame( int maxPlayers, int maxPlayersPerTeam, const string & mapId, int autostartPlayers, T* object, void (T::*func)(EOperationResult::Enum result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 4, maxPlayers, maxPlayersPerTeam, mapId, autostartPlayers );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, EOperationResult::Enum, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T>
  rpc::ECallResult::Enum SpectateCustomGame( int gameId, T* object, void (T::*func)(EOperationResult::Enum result) )
  {           
    rpc::Transaction* transaction = handler->Call( 5, gameId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, EOperationResult::Enum>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum SpectateCustomGame( int gameId, T* object, void (T::*func)(EOperationResult::Enum result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 5, gameId );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, EOperationResult::Enum, C>(object, func, context), timeout );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  
  void ChangeCustomGameSettings(  int team, int faction, const string & heroId )
  {
    handler->Go(handler->Call( 6, team, faction, heroId ));
  }
  void SetReady(  int readiness )
  {
    handler->Go(handler->Call( 7, readiness ));
  }
  void SetDeveloperParty(  int party )
  {
    handler->Go(handler->Call( 8, party ));
  }

  template <typename T>
  rpc::ECallResult::Enum JoinSocialGame( T* object, void (T::*func)(EOperationResult::Enum result) )
  {           
    rpc::Transaction* transaction = handler->Call( 9 );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorNoContext<T, EOperationResult::Enum>(object, func) );
      return handler->Go(transaction);
    }
    return rpc::ECallResult::NoTransaction;
  }
  

  template <typename T, typename C>
  rpc::ECallResult::Enum JoinSocialGame( T* object, void (T::*func)(EOperationResult::Enum result, C context, rpc::CallStatus status), const C& context, float timeout=0.f)
  {           
    rpc::Transaction* transaction = handler->Call( 9 );
    if (transaction)
    {
      transaction->RegisterAsyncCall( transaction->GetInfo(), new rpc::FunctorContext<T, EOperationResult::Enum, C>(object, func, context), timeout );
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

  static uint GetClassCrcStatic() { return 0x94e70ebd; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_LobbyIServerInstance_H__
