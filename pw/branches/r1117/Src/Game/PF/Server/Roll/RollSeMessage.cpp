#include "stdafx.h"
#include "RollSeMessage.h"
#include <json/reader.h>
#include <json/writer.h>
#include "RollConfig.h"
#include "RollLog.h"


namespace roll
{

SeMessageBase::SeMessageBase( IConfigProvider * _cfg, TRollId _rollId ) :
rollId( _rollId ),
config( _cfg ),
status( ESeMsgStatus::Init ),
nextRetry( 0 ),
retryCooldown( _cfg->Cfg()->seFirstRetryDelay * 0.5f ) //HACK to display correct cooldown value in log
{
  AppendLogId( NI_STRFMT( "roll_id=%016x", rollId ) );
}



StrongMT<RollConfig> SeMessageBase::Config() const
{
  return config->Cfg();
}



void SeMessageBase::AppendLogId( const char * txt )
{
  if ( !logId.empty() )
    logId += ", ";
  logId += txt;
}



void SeMessageBase::AppendLogExtInfo( const char * txt )
{
  if ( !logExtInfo.empty() )
    logExtInfo += ", ";
  logExtInfo += txt;
}


void SeMessageBase::SetStatus( ESeMsgStatus::Enum st )
{
  threading::SpinLockGuard guard( statusMutex );
  status = st;
}



ESeMsgStatus::Enum SeMessageBase::DeliveryStatus() const
{
  threading::SpinLockGuard guard( statusMutex );
  return status;
}


void SeMessageBase::DelayRetry( timer::Time now )
{
  retryCooldown *= 2.0f;

  retryCooldown = Min( retryCooldown, (timer::Time)Config()->seMaxRetryDelay );
  nextRetry = now + retryCooldown;
}

void SeMessageBase::AwardsIntoJson( Json::Value & value, const char * fieldId, const vector<SAwardInfo> & awards )
{
  Json::Value json( Json::arrayValue );
  for ( int i = 0; i < awards.size(); ++i )
  {
    const SAwardInfo & item = awards[i];

    if ( item.isOwnedByPlayer )
    {
      Json::Value rec( Json::objectValue );
      rec["type"] = item.type;
      rec["id"] = item.id;
      rec["count"] = item.count;
      rec["customCurrencyId"] = item.customCurrencyId.c_str();
      json.append( rec );
    }
  }

  value[fieldId] = json;
}

void SeMessageBase::AwardsBuffStatIntoJson( Json::Value & value, const char * fieldId, const SUserAward & award )
{
  Json::Value json( Json::arrayValue );

  set<string>::iterator it = award.appliedRollBuffs.begin();
  for ( ; it != award.appliedRollBuffs.end(); ++it )
  {
    Json::Value rec( it->c_str() );
    json.append( rec );
  }

  value[fieldId] = json;
}

void SeMessageBase::FormJson( Json::Value & msg ) const
{
  msg["type"] = SeMessageType();
  msg["tm_expire"] = (int)Config()->seMessageExpirePeriod;
  msg["count"] = 1;
  msg["roll_id"] = NI_STRFMT( "%d", rollId );
}

SeUserMessage::SeUserMessage( IConfigProvider * _cfg, TRollId _rollId, const SUserAward & _award ) :
SeMessageBase( _cfg, _rollId ),
award( _award )
{
  AppendLogId( NI_STRFMT( "uid=%d", award.userId ) );
  AppendLogExtInfo( NI_STRFMT( "award_count=%d, awards=[%s]", award.awards.size(), DbgDumpAwards( award.awards ) ) );
}


static Json::Value RollItems2Json( const vector<NCore::TalentRollItem>& rollItems )
{
  Json::Value jsonRollList( Json::arrayValue );
  for ( int i = 0; i < rollItems.size(); ++i )
  {
    Json::Value item( Json::objectValue );
    const NCore::TalentRollItem& talentRollItem = rollItems[i];
    item["dbid"] = talentRollItem.dbid;
    item["probability"] = talentRollItem.probability;
    jsonRollList.append( item );
  }
  return jsonRollList;
}


static Json::Value RollTable2JsonConverter( const NCore::TalentRollData & rollData )
{
  Json::Value jsonRollData( Json::objectValue );

  jsonRollData["gen_index"] = (int)rollData.generationIndex;

  const NCore::TTalentRollTable& rollTable = rollData.rollTable;

  for ( NCore::TTalentRollTable::const_iterator it = rollTable.begin(); it != rollTable.end(); ++it )
  {
    const NCore::TalentRollItems & talentRollItems = it->second;

    Json::Value jsonRollTableObj( Json::objectValue );
    jsonRollTableObj["version"] = talentRollItems.version;
    jsonRollTableObj["db_version"] = talentRollItems.dbVersion;

    Json::Value itemsListObj( Json::objectValue );
    itemsListObj["items"] = RollItems2Json( talentRollItems.defaultItems );
    jsonRollTableObj["default"] = itemsListObj;
    itemsListObj["items"] = RollItems2Json( talentRollItems.premiumItems );
    jsonRollTableObj["premium"] = itemsListObj;

    jsonRollData[(it->first).c_str()] = jsonRollTableObj;
  }
  return jsonRollData;
}


void SeUserMessage::FormUrl( string & url ) const
{
  url += NI_STRFMT( "&recipient=%d&project=%s", award.userId, Config()->seProjectForUsers );
}

void SeUserMessage::FormUrlForPacket( Json::Value & msg ) const
{
  msg["recipient"] = NI_STRFMT( "%d", award.userId);
  msg["project"] = NI_STRFMT( "%s",Config()->seProjectForUsers );
}


void SeUserMessage::FormJson( Json::Value & msg ) const
{
  SeMessageBase::FormJson( msg );

  AwardsIntoJson( msg, "awards", award.awards );
  AwardsBuffStatIntoJson(msg, "applied_roll_buffs", award);

  // convert talent roll data
  // Process only if rollTable is not empty. Otherwise empty string should signalize social server not to update "session_roll" data.
  if ( !award.talentRollData.rollTable.empty() )
  {
    Json::Value talentRollData;
    talentRollData = RollTable2JsonConverter( award.talentRollData );
    std::string strTalentRollData = (Json::FastWriter()).write( talentRollData );
    msg["session_roll"] = strTalentRollData;
  }

}

static Json::Value Extra2JsonConverter( const StatisticService::SessionPlayerExtra& _extra )
{
  Json::Value jsonExtra( Json::objectValue );
  //ROLL_LOG_DBG("Extra2JsonConverter: partySize %d, enemyPartySize %d", _extra.partySize, _extra.enemyPartySize );
  jsonExtra["tutorialSkipped"] = _extra.tutorialSkipped;
  jsonExtra["partySize"] = _extra.partySize;
  jsonExtra["enemyPartySize"] = _extra.enemyPartySize;
  jsonExtra["badBehaviourDetected"] = _extra.badBehaviourDetected;
  jsonExtra["badBehaviourReported"] = _extra.badBehaviourReported;
  jsonExtra["isGuildFight"] = _extra.isGuildFight;


  return jsonExtra;
}


static Json::Value Scoring2JsonConverter( const StatisticService::SessionPlayerScoring& _scoring )
{
  Json::Value jsonScore( Json::objectValue );

  jsonScore["score"] = _scoring.score;
  jsonScore["specialPoints"] = _scoring.specialPoints;
  jsonScore["finalLevel"] = _scoring.finalLevel;
  jsonScore["kills"] = _scoring.kills;
  jsonScore["deaths"] = _scoring.deaths;
  jsonScore["assists"] = _scoring.assists;
  jsonScore["enemyCreepsKilled"] = _scoring.enemyCreepsKilled;
  jsonScore["neutralCreepsKilled"] = _scoring.neutralCreepsKilled;
  jsonScore["totalNumTowersKilled"] = _scoring.totalNumTowersKilled;
  jsonScore["totalNumTowersAssisted"] = _scoring.totalNumTowersAssisted;
  jsonScore["flagsRaised"] = _scoring.flagsRaised;
  jsonScore["flagsDestroyed"] = _scoring.flagsDestroyed;
  jsonScore["totalMedalsCountFailed"] = _scoring.totalMedalsCountFailed;
  jsonScore["totalMedalsCountDone"] = _scoring.totalMedalsCountDone;
  jsonScore["totalMedalsCountSilver"] = _scoring.totalMedalsCountSilver;
  jsonScore["totalMedalsCountGold"] = _scoring.totalMedalsCountGold;
  jsonScore["timeInDeath"] = _scoring.timeInDeath;
  jsonScore["damageDealedMagic"] = _scoring.damageDealedMagic;
  jsonScore["damageDealedMaterial"] = _scoring.damageDealedMaterial;
  jsonScore["damageDealedPure"] = _scoring.damageDealedPure;
  jsonScore["damageDealedTotal"] = _scoring.damageDealedTotal;
  jsonScore["damageReceivedMagic"] = _scoring.damageReceivedMagic;
  jsonScore["damageReceivedMaterial"] = _scoring.damageReceivedMaterial;
  jsonScore["damageReceivedPure"] = _scoring.damageReceivedPure;
  jsonScore["damageReceivedTotal"] = _scoring.damageReceivedTotal;
  jsonScore["sexHelp"] = _scoring.sexHelp;
  jsonScore["healedAmount"] = _scoring.healedAmount;
  jsonScore["totalNumQuartersDestroyed"] = _scoring.totalNumQuartersDestroyed;
  jsonScore["numBossKillsAssist"] = _scoring.numBossKillsAssist;
  jsonScore["numCatKillAssist"] = _scoring.numCatKillAssist;
  jsonScore["numDragonKillAssist"] = _scoring.numDragonKillAssist;
  jsonScore["numKillsTotal"] = _scoring.numKillsTotal;
  jsonScore["money"] = _scoring.money;
  jsonScore["currentKillSpree"] = _scoring.currentKillSpree;
  jsonScore["currentDeathSpree"] = _scoring.currentDeathSpree;
  jsonScore["saviourTime"] = _scoring.saviourTime;
  jsonScore["timeInIdle"] = _scoring.timeInIdle;
  jsonScore["killedByNeutrals"] = _scoring.killedByNeutrals;
  jsonScore["usedPotions"] = _scoring.usedPotions;
  jsonScore["timeAtHome"] = _scoring.timeAtHome;
  jsonScore["teleportsByAbility"] = _scoring.teleportsByAbility;
  jsonScore["glyphsPickuped"] = _scoring.glyphsPickuped;
  jsonScore["achievScore"] = _scoring.achievScore;
  jsonScore["damageReceivedFromHeroesMagic"] = _scoring.damageReceivedFromHeroesMagic;
  jsonScore["damageReceivedFromHeroesMaterial"] = _scoring.damageReceivedFromHeroesMaterial;
  jsonScore["damageReceivedFromHeroesPure"] = _scoring.damageReceivedFromHeroesPure;
  jsonScore["damageReceivedFromHeroesTotal"] = _scoring.damageReceivedFromHeroesTotal;
  jsonScore["damageDealedToHeroesMagic"] = _scoring.damageDealedToHeroesMagic;
  jsonScore["damageDealedToHeroesMaterial"] = _scoring.damageDealedToHeroesMaterial;
  jsonScore["damageDealedToHeroesPure"] = _scoring.damageDealedToHeroesPure;
  jsonScore["damageDealedToHeroesTotal"] = _scoring.damageDealedToHeroesTotal;
  jsonScore["grandScore"] = _scoring.grandScore;
  jsonScore["timeElapsed"] = _scoring.timeElapsed;


  return jsonScore;
}

SeUserMessageFromGame::SeUserMessageFromGame( IConfigProvider * _cfg, 
                                              TRollId _rollId,
                                              const SUserAward & _award,
                                              const nstl::string & _gameType,
                                              bool _customGame,
                                              const StatisticService::SessionPlayerScoring& _scoring,
                                              const StatisticService::SessionPlayerExtra& _extra ) :
SeUserMessage( _cfg, _rollId, _award ),
gameType( _gameType ),
customGame( _customGame ),
scoring( _scoring ),
extra( _extra )
{
  // dump scoring? !!!!!!!!!!!!
}

void SeUserMessageFromGame::FormJson( Json::Value & msg ) const
{
  SeUserMessage::FormJson( msg );

  // Hack. See NUM_TASK comments. Adding slash before DBID string and removing trailing ".xdb"
  nstl::string key = '/' + gameType;
  if ( !key.empty() && key[0] != '/' )
    key.insert( 0, "/" );

  if ( ( key.length() > 4 ) && ( key.substr( key.length() - 4 ) == ".xdb" ) )
    key.erase( key.length() - 4 );

  msg["game_type"] = key.c_str();
  msg["playerWin"] = award.playerWin;
  msg["playerLeaver"] = award.playerLeaver;
  msg["tambur_fight"] = award.hadPreGameLobby;
  msg["customGame"] = customGame;
  msg["scoring"] = Scoring2JsonConverter( scoring );
  msg["extra"] = Extra2JsonConverter(extra);
}

SeGuildMessage::SeGuildMessage( IConfigProvider * _cfg, TRollId _rollId, const SGuildAward & _award ) :
SeMessageBase( _cfg, _rollId ),
guildAward( _award )
{
  AppendLogId( NI_STRFMT( "guildid=%d", guildAward.guildId ) );
  AppendLogExtInfo( NI_STRFMT( "award_count=%d, awards=[%s]", guildAward.awards.size(), DbgDumpAwards( guildAward.awards ) ) );
}

void SeGuildMessage::FormUrl( string & url ) const
{
  url += NI_STRFMT( "&recipient=%d&project=%s", guildAward.guildId, Config()->seProjectForGuilds );
}

void SeGuildMessage::FormUrlForPacket( Json::Value & msg ) const
{
    msg["recipient"] = NI_STRFMT( "%Ld", guildAward.guildId);
    msg["project"] = NI_STRFMT( "%s", Config()->seProjectForGuilds);
}

void SeGuildMessage::FormJson( Json::Value & msg ) const
{
  SeMessageBase::FormJson( msg );

  AwardsIntoJson( msg, "awards", guildAward.awards );
}

} //namespace roll
