#ifndef ROLLJOB_H_INCLUDED
#define ROLLJOB_H_INCLUDED

#include "RollLogic.h"
#include "RollClient.h"

namespace timer 
{
  class Timer;
}

namespace roll
{

class ISeMessageHandle;
class SeMessageBase;
class SeClientWorker;
class Instance;


class BaseJob : public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_1( BaseJob, BaseObjectMT );

public:
  BaseJob( DropNRoll * _logic, IClient * _client, SeClientWorker * _seClient );

  bool Poll();

protected:
  DropNRoll * Logic() const { return logic; }
  IClient * Client() const { return client; }
  SeClientWorker * SeClient() const { return seClient; }
  void ImplAddNewMessage( SeMessageBase * msg );

  virtual void Roll() = 0;
  virtual void NotifyClient() = 0;
  virtual void BeginDelivery() = 0;
  virtual void DeliveryFinished( int delivered, int failed ) = 0;

private:
  struct EState { enum Enum { Rolling, ClientNotification, Delivery, Done }; };

  Strong<DropNRoll>   logic;
  StrongMT<IClient>   client;
  StrongMT<SeClientWorker> seClient;

  vector<StrongMT<ISeMessageHandle>> seMessages;
  EState::Enum        state;

  void SwitchTo( EState::Enum st ) { state = st; }
  bool CheckDelivery();
};




class SessionRollJob : public BaseJob
{
  NI_DECLARE_REFCOUNT_CLASS_1( SessionRollJob, BaseJob );

public:
  SessionRollJob( DropNRoll * _logic, IClient * _client, SeClientWorker * _seClient, const SPreGameData & _preGame, const SPostGameData & _postGame, Instance* _instance );

private:
  const SPreGameData  preGame;
  const SPostGameData postGame;

  vector<SUserAward>  result;
  map<NCore::TGuildAuid, SGuildAward> guildResult;
  Instance*  instance;
  timer::Time begin_delivery_time;
  virtual void Roll();
  virtual void NotifyClient();
  virtual void BeginDelivery();
  virtual void DeliveryFinished( int delivered, int failed );
};




class ForgeRollJob : public BaseJob
{
  NI_DECLARE_REFCOUNT_CLASS_1( ForgeRollJob, BaseJob );

public:
  ForgeRollJob( DropNRoll * _logic, IClient * _client, SeClientWorker * _seClient, const SForgeRollData & _data );

private:
  const SForgeRollData  data;
  SUserAward  result;

  virtual void Roll();
  virtual void NotifyClient();
  virtual void BeginDelivery();
  virtual void DeliveryFinished( int delivered, int failed );
};

} //namespace roll

#endif //ROLLJOB_H_INCLUDED
