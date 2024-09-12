#ifndef __R_LobbyClientInterface_H__
#define __R_LobbyClientInterface_H__

#include <RPC/RPC.h>
#include "Server/LobbyPvx/CommonTypes.h"
#include "Server/Roll/RollTypes.h"
#include "HybridServer/RPeered.auto.h"




namespace lobby
{


class RILobbyUser : public rpc::IRemoteEntity, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2(RILobbyUser, rpc::IRemoteEntity, BaseObjectMT);
public:
  RPC_INFO("lobby::ILobbyUser", 0x62dac159);
  
  RILobbyUser() : handler(0) {}
  RILobbyUser( rpc::EntityHandler* _handler, rpc::IRemoteEntity* _parent )
  :  handler(_handler)
  ,  parent(_parent)

  {

  }

  ~RILobbyUser()
  {
    if( handler )
    {
      handler->OnDestruct(*this);
      handler = 0;
    }
  }
  virtual rpc::RemoteEntityInfo GetInfo() const { rpc::RemoteEntityInfo info = { handler->GetId(), { RILobbyUser::ID(), RILobbyUser::CRC32}, handler->GetGUID() }; return info; }
  inline bool IsUpdated() const { return handler->IsUpdated(); }
  rpc::EntityHandler* GetHandler() { return handler; }

  void AddGameInfo(  const SDevGameInfo & info )
  {
    handler->Go(handler->Call( 0, info ));
  }
  void JoinCustomSession(  const SGameParameters & params )
  {
    handler->Go(handler->Call( 1, params ));
  }
  void UpdateClientStatus(  int status )
  {
    handler->Go(handler->Call( 2, status ));
  }
  void AddCustomGameMember(  const SGameMember & member )
  {
    handler->Go(handler->Call( 3, member ));
  }
  void RemoveCustomGameMember(  int userId )
  {
    handler->Go(handler->Call( 4, userId ));
  }
  void UpdateCustomGameMember(  int userId, const SPlayerGameContext & params )
  {
    handler->Go(handler->Call( 5, userId, params ));
  }
  void UpdateCustomGameMemberReadiness(  int userId, bool ready )
  {
    handler->Go(handler->Call( 6, userId, ready ));
  }
  void StartSession(  TGameId sessionId, const SGameParameters & params, const TGameLineUp & gameLineUp, Peered::RIGameServer * gameServerInstance, const Peered::SInstanceId & _gsInstId, unsigned timestamp32 )
  {
    handler->Go(handler->Call( 7, sessionId, params, gameLineUp, gameServerInstance, _gsInstId, timestamp32 ));
  }
  void Award(  const vector<roll::SAwardInfo> & _awards )
  {
    handler->Go(handler->Call( 8, _awards ));
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

  static uint GetClassCrcStatic() { return 0x62dac159; }
protected:
  friend class rpc::Gate;




private:
  StrongMT<rpc::EntityHandler> handler;
  WeakMT<rpc::IRemoteEntity> parent;


};

}



#endif // __R_LobbyClientInterface_H__
