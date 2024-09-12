#ifndef ROLLSECLIENT_H_INCLUDED
#define ROLLSECLIENT_H_INCLUDED

#include "System/JobThread.h"
#include "RollSeMessage.h"
#include "RollConfig.h"

namespace webClient
{
  class IJsonClient;
}


namespace roll
{

class SeClientWorker : public BaseObjectMT, public threading::IThreadJob
{
  NI_DECLARE_REFCOUNT_CLASS_1( SeClientWorker, BaseObjectMT );

public:
  SeClientWorker( IConfigProvider * _cfg );

  void AddMessage( SeMessageBase * _msg );

  StrongMT<IConfigProvider> Config() { return config; }
  const int LineSize() const {return line.size(); } ;
private:
  typedef list<StrongMT<SeMessageBase>> Messages;

  StrongMT<IConfigProvider> config;
  StrongMT<webClient::IJsonClient>  httpClient;
  int packetAwardsSize;
  bool sendPacketAwards;

  Messages  line;
  threading::Mutex  lineMutex;

  //threading::IThreadJob
  virtual void Work( volatile bool & isRunning );
  void SingleWorker();
  void PacketWorker();

  ISeMessageHandle * AddMsgImpl( ISeMessageHandle * msg );
  StrongMT<SeMessageBase> Pop();
  
  bool Deliver( SeMessageBase * msg );
  void RollBack( SeMessageBase * msg );
  
  bool DeliverPacket( const Messages& pack );
  void RollBackPacket(const Messages& pack );

  void SetStatusForPack(ESeMsgStatus::Enum stat, Messages & pack);


};


} //namespace roll

#endif //ROLLSECLIENT_H_INCLUDED
