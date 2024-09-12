#ifndef ROLLSEMESSAGE_H_INCLUDED
#define ROLLSEMESSAGE_H_INCLUDED

#include "RollTypes.h"
#include "RollConfig.h"
#include "system/SpinLock.h"


namespace Json
{
  class Value;
}


namespace roll
{


namespace ESeMsgStatus
{
  enum Enum { Init, Waiting, Delivered, Failed };
}


class ISeMessageHandle : public IBaseInterfaceMT
{
  NI_DECLARE_CLASS_1( ISeMessageHandle, IBaseInterfaceMT );

public:
  virtual ESeMsgStatus::Enum DeliveryStatus() const = 0;
};



class SeMessageBase : public ISeMessageHandle, public BaseObjectMT
{
  NI_DECLARE_REFCOUNT_CLASS_2( SeMessageBase, ISeMessageHandle, BaseObjectMT );

public:
  SeMessageBase( IConfigProvider * _cfg, TRollId _rollId );

  const char * GetLogId() const { return logId.c_str(); }
  const char * GetLogExtInfo() const { return logExtInfo.c_str(); }

  void SetStatus( ESeMsgStatus::Enum st );

  //ISeMessageHandle
  virtual ESeMsgStatus::Enum DeliveryStatus() const;

  //overridable
  virtual void FormUrl( string & url ) const = 0;
  virtual void FormUrlForPacket( Json::Value & msg ) const = 0;

  virtual void FormJson( Json::Value & msg ) const;
  virtual const char * SeMessageType() const = 0;

  timer::Time NextRetry() const { return nextRetry; }
  void DelayRetry( timer::Time now );
  timer::Time RetryCooldown() const { return retryCooldown; }
  StrongMT<RollConfig> Config() const;

protected:
  void AppendLogId( const char * txt );
  void AppendLogExtInfo( const char * txt );
  const lobby::TSocialGameId RollId() const { return rollId; }
  static void AwardsIntoJson( Json::Value & value, const char * fieldId, const vector<SAwardInfo> & awards );
  static void AwardsBuffStatIntoJson( Json::Value & value, const char * fieldId, const SUserAward & awards );

private:
  const TRollId       rollId;
  string              logId, logExtInfo;
  StrongMT<IConfigProvider> config;

  threading::SpinLock statusMutex;
  ESeMsgStatus::Enum  status;
  timer::Time         nextRetry;
  timer::Time         retryCooldown;
};



class SeUserMessage : public SeMessageBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( SeUserMessage, SeMessageBase );

public:
  SeUserMessage( IConfigProvider * _cfg, TRollId _rollId, const SUserAward & _award );

  virtual void FormUrl( string & url ) const;
  virtual void FormUrlForPacket( Json::Value & msg ) const;

  virtual void FormJson( Json::Value & msg ) const;
  virtual const char * SeMessageType() const { return "forge_roll"; }

protected:
  const SUserAward    award;
};



class SeUserMessageFromGame : public SeUserMessage
{
  NI_DECLARE_REFCOUNT_CLASS_1( SeUserMessageFromGame, SeUserMessage );

public:
  SeUserMessageFromGame( IConfigProvider * _cfg, 
                         TRollId _rollId,
                         const SUserAward & _award,
                         const nstl::string & _gameType,
                         bool _customGame,
                         const StatisticService::SessionPlayerScoring& _scoring,
                         const StatisticService::SessionPlayerExtra& _extra
                         );

  virtual void FormJson( Json::Value & msg ) const;
  virtual const char * SeMessageType() const { return "session_awards"; }

protected:
  const nstl::string      gameType;
  bool                    customGame;
  const StatisticService::SessionPlayerScoring scoring;
  const StatisticService::SessionPlayerExtra extra;
};



class SeGuildMessage : public SeMessageBase
{
  NI_DECLARE_REFCOUNT_CLASS_1( SeGuildMessage, SeMessageBase );

public:
  SeGuildMessage( IConfigProvider * _cfg, TRollId _rollId, const SGuildAward & _award );

  virtual void FormUrl( string & url ) const;
  virtual void FormUrlForPacket( Json::Value & msg ) const;
  virtual void FormJson( Json::Value & msg ) const;
  virtual const char * SeMessageType() const { return "s_guild_awards"; }

private:
  SGuildAward   guildAward;
};

} //namespace roll

#endif //ROLLSEMESSAGE_H_INCLUDED
