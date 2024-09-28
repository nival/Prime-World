#pragma once

#include "RPC/GateKeeper.h" 
#include "json/reader.h"
#include "json/writer.h"
#include "rpc/IfaceRequester.h"
#include "Server/LobbySocial/SocialLobbyTypes.h"
#include "system/SpinLock.h"
#include <list>
#include <map>


namespace socialLobby
{
  class RISocialInterface;
}


namespace roll
{
  class RIBalancer;
}


namespace HttpGateway
{

class PingContext;
class ForgeRollRequest;

namespace EContextState { enum Enum; }


// рабочий класс: парсит запросы, исполняет rpс-вызовы (через интерфейс ISocialLobby), кэширует данные и ответы
class GatewayJsonHandler : public BaseObjectMT
{
public:
  NI_DECLARE_REFCOUNT_CLASS_1( GatewayJsonHandler, BaseObjectMT );

  GatewayJsonHandler( rpc::GateKeeper * _gk );

  bool Ready();

  void Poll();
  void HandleJson( std::string & reply, const std::string & json_data );

private:
  typedef std::map<socialLobby::TUId, StrongMT<PingContext> >  TCacheMap;

  struct EGenericReqReply { enum Enum { ReplyZero, ReplyMmid, DoNothing, BadRequest }; };
  typedef EGenericReqReply::Enum (GatewayJsonHandler::*TGenericRequestHandler)( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData );

  typedef std::list<StrongMT<ForgeRollRequest> > ForgeRollRequests;

  StrongMT<rpc::GateKeeper>       gateKeeper;

  StrongMT<rpc::IfaceRequester<socialLobby::RISocialInterface> > socialLobby;
  StrongMT<rpc::IfaceRequester<roll::RIBalancer> > rollBalancer;

  threading::Mutex  mutex;
  TCacheMap         byUids;
  socialLobby::SServerStatus lastServerStatus;

  ForgeRollRequests forgeRollRequests;

  StrongMT<socialLobby::RISocialInterface> SocLobbyThreadSafe();

  void PollContexts();

  bool CheckVersion( const Json::Value & request );
  void HandleJsonThrow( std::string & reply, const std::string & json_data );

  StrongMT<PingContext> GetCtxByUid( socialLobby::TUId uid );
  StrongMT<PingContext> GetCtxSafe( socialLobby::TUId uid, const char * dbgText );
  StrongMT<PingContext> CreateContext( socialLobby::TUId uid, const char * sessionId, EContextState::Enum ctxState, socialLobby::ERequestStatus::Enum status );

  void HandleAddRequests( Json::Value & pvxReply, const Json::Value & request );
  void HandleSingleAddRequest( Json::Value & pvxReply, const std::string & uid, const Json::Value & requestData );

  void HandleSpectateRequests( Json::Value & pvxReply, const Json::Value & request );
  void HandleSingleSpectateRequest( Json::Value & pvxReply, const std::string & uid, const Json::Value & requestData );

  void HandleGenericRequest( Json::Value & pvxReply, const Json::Value & request, const char * key, TGenericRequestHandler handler );

  EGenericReqReply::Enum HandlePingReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData );
  EGenericReqReply::Enum HandleCancelReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData );
  EGenericReqReply::Enum HandleCancelPartyReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData );
  EGenericReqReply::Enum HandleLeaveReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData );
  EGenericReqReply::Enum HandleReconnectReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData );
  EGenericReqReply::Enum HandleAcceptReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData );
  EGenericReqReply::Enum HandleGuardChangeHeroReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData );
  EGenericReqReply::Enum HandleGuardReadyReq( Json::Value & pvxReply, const std::string & uidStr, PingContext * ctx, const Json::Value & requestData );

  void HandleServerStatus( Json::Value & pvxReply, const Json::Value & request );
  void OnServerStatus( socialLobby::SServerStatus result );

  void HandleForgeRoll( Json::Value & reply, const Json::Value & request );
  void PollForgeRollrequests();
};

} //namespace HttpGateway
