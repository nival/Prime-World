#ifndef FORGEROLLREQUEST_H_INCLUDED
#define FORGEROLLREQUEST_H_INCLUDED

#include "Server/LobbySocial/SocialLobbyTypes.h"
#include "Server/Roll/RollClient.h"
#include "rpc/IfaceRequester.h"

namespace roll
{
  struct SUserAward;
  class RIBalancer;
  class RIInstance;
}


namespace HttpGateway
{

namespace EForgeRollRequestState
{
  enum Enum { New, WaitingBalancer, WaitingRollInstance, WaitingRoll, Cooldown, Done, Failed };
}


class ForgeRollRequest : public BaseObjectMT, public roll::IClient
{
public:
  NI_DECLARE_REFCOUNT_CLASS_1( ForgeRollRequest, BaseObjectMT );

  ForgeRollRequest( const roll::SForgeRollData & _data, rpc::IfaceRequester<roll::RIBalancer> * _balancer );

  bool Poll( timer::Time _now );

  const roll::SForgeRollData & Data() const { return data; }

private:
  const roll::SForgeRollData    data;
  timer::Time                   now;
  StrongMT<rpc::IfaceRequester<roll::RIBalancer> > balancer;
  StrongMT<roll::RIInstance>    instance;
  EForgeRollRequestState::Enum  state;
  timer::Time                   stateExpires;
  timer::Time                   cooldownEnds;
  int                           retryIndex;

  void CheckStateExpire();
  void Switch( EForgeRollRequestState::Enum st );
  void SwitchWoExpire( EForgeRollRequestState::Enum st );

  void OnRollInstance( roll::RIInstance * _inst );

  //roll::IClient
  virtual void RollResults( const vector<roll::SUserAward> & _award );
  virtual void ForgeRollAck();
  virtual void RollFailed();

  void TryRetry();
};

} //namespace HttpGateway

#endif //FORGEROLLREQUEST_H_INCLUDED
