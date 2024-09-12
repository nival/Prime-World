#include "Server/Roll/RollLog.h"
#include "Server/Roll/RollLogic.h"
#include "Server/Roll/RollConfig.h"
#include "Server/Roll/RollBuff.h"
#include "PF_GameLogic/PFResourcesCollection.h"
#include "System/FileSystem/WinFileSystem.h"
#include "System/FileSystem/FilePath.h"
#include "System/CmdLineLite.h"
#include "System/ConfigFiles.h"
#include "System/FileSystem/FileUtils.h"
#include "System/LogFileName.h"
#include "System/TextFileDumper.h"
#include "System/BinChunkSerializer.h"
#include "Server/Roll/TalentRollDataCache.h"

#include "Version.h"
#include <iostream>

#include "RollTestToolStorage.h"
#include "RollTestTool.h"

struct BuffApplyParam
{
  BuffApplyParam() : repeatCount(-1) {}
  BuffApplyParam(int rc, int pid) : repeatCount(rc), playerId (pid) {}
  int repeatCount;
  int playerId;
};

typedef vector<BuffApplyParam> BuffApplyParamCollection;

typedef map<string, BuffApplyParamCollection> PlayersBuffs;
const string BUFFS_PARAM_GROUP_DELEMITER = ";";
const string BUFFS_PARAM_VALUE_DELEMITER = ":";
const string USE_THIS_BUFFS_DEFAULT = "empty";
const string USE_THIS_BUFFS_ENABLE = "all";

inline void FillUserBuffs(const NCore::TAwardsBuffs& awardBuff, vector<roll::SPreGamePerUserData> & preUsers)
{
  for (int i = 0; i < preUsers.size(); ++i)
  {
      roll::SPreGamePerUserData &userData = preUsers[i];
      userData.playerInfo.aBuffs = awardBuff;
  }
}

inline void FillUserBuffs(const PlayersBuffs& awardBuff, vector<roll::SPreGamePerUserData> & preUsers)
{
  PlayersBuffs::const_iterator buffsIterator = awardBuff.begin();

  for (;buffsIterator != awardBuff.end(); ++buffsIterator)
  {
    string buffId = buffsIterator->first;
    BuffApplyParamCollection& buffsApplyParams = buffsIterator->second;

    BuffApplyParamCollection::const_iterator paramIter = buffsApplyParams.begin();
    for(; paramIter != buffsApplyParams.end(); ++paramIter)
    {
      int playerId = paramIter->playerId;
      if(playerId > 0 && playerId < preUsers.size())
      {
        preUsers[playerId].playerInfo.aBuffs.push_back(buffId);
      }
      else if (playerId == 0) // if playerId == 0 => buff for all players
      {
        for(int i = 0; i < preUsers.size(); ++i)
        {
          preUsers[i].playerInfo.aBuffs.push_back(buffId);
        }
      }
    }
  }
}

string GetBuffByCode(const string BuffCode, const NCore::TAwardsBuffs& awardBuff)
{
  string ret;
  NCore::TAwardsBuffs::const_iterator abIterator = awardBuff.begin();
  for(;abIterator != awardBuff.end();++abIterator)
  {

    vector<string> values;
    NStr::SplitString((*abIterator), &values, BUFFS_PARAM_VALUE_DELEMITER);

    if(values.empty()) continue;

    if(values[0].find(BuffCode) != string::npos)
    {
      ret = *abIterator;
      break;
    }
  }

  return ret;
}

void AddBuff(PlayersBuffs& buffs, BuffApplyParam buffData, const string& buffId)
{
  vector<BuffApplyParam>& pb = buffs[buffId];
  pb.push_back(buffData);
}


inline void InitPlayersBuffs(const string& useThisBuffs, const NCore::TAwardsBuffs& awardBuff,  PlayersBuffs& buffs)
{
  if( useThisBuffs.empty() || awardBuff.empty() ) return;

  vector<string> groups;
  NStr::SplitString(useThisBuffs, &groups, BUFFS_PARAM_GROUP_DELEMITER);

  if(groups.empty()) return;

  vector<string>::const_iterator groupIter = groups.begin();

  for(;groupIter != groups.end();++groupIter)
  {
    if(groupIter->empty()) continue;

    vector<string> values;
    NStr::SplitString((*groupIter), &values, BUFFS_PARAM_VALUE_DELEMITER);

    int valuesCount = values.size();

    if(values.empty() || valuesCount < 2) continue;

    string buffId;
    BuffApplyParam buffData;
    buffData.playerId = atoi(values[0].c_str());

    switch(valuesCount)
    {
    case 2:
      buffId = GetBuffByCode(values[1], awardBuff);
      break;
    case 3:
      buffId = GetBuffByCode(values[1], awardBuff);
      buffData.repeatCount = atoi(values[2].c_str());
      break;
    }

    if(!buffId.empty())
    {
      AddBuff(buffs, buffData, buffId);
    }
  }
}

inline void InitBuffs(const vector<nstl::string>& buffs, NCore::TAwardsBuffs& awardBuff)
{
  awardBuff.clear();
  awardBuff.reserve(buffs.size() * 2);

  vector<nstl::string>::const_iterator buffInitIterator = buffs.begin();

  for(;buffInitIterator != buffs.end(); ++buffInitIterator)
  {
    NDb::Ptr<NDb::GuildBuff> buff = NDb::Get<NDb::GuildBuff>( NDb::DBID( *buffInitIterator ) );
    if(!buff) 
    {
      continue;
    }

    vector< NDb::Ptr< NDb::GuildShopItemBonus > >::const_iterator bonusIterator = buff->bonuses.begin();
    for(;bonusIterator != buff->bonuses.end(); ++bonusIterator)
    {
      awardBuff.push_back((*bonusIterator)->GetDBID().GetFormatted());
    }
  }

}

inline bool IsCountableAward( roll::EAwardType::Enum type )
{
  return type == roll::EAwardType::Silver 
      || type == roll::EAwardType::Resource1
      || type == roll::EAwardType::Resource2
      || type == roll::EAwardType::Resource3
      || type == roll::EAwardType::Pearl
      || type == roll::EAwardType::Experience
      || type == roll::EAwardType::Fame
      || type == roll::EAwardType::HeroRating
      || type == roll::EAwardType::ClanWarsClanRating
      || type == roll::EAwardType::ClanWarsPlayerRating
      || type == roll::EAwardType::RedPearl
	  || type == roll::EAwardType::CustomCurrency;
}


class AwardsCounter
{
  struct CounterData
  {
    CounterData() : cmin(1e8), cmax(-1e8), total(0), count(0), bonus(0) {}
    int cmin;
    int cmax;
    int total;
    int count;
    int bonus;
    int premium;
  };

  struct TalentsCount
  {
    TalentsCount(): count(0), bonus(0) {}

    int count;
    int bonus;
  };

  typedef vector<CounterData> TAwardCounters;
  typedef map<int, TAwardCounters> TAwardCounterData;
  typedef vector<TalentsCount> TByIdCounters;
  typedef map<uint, TByIdCounters > TByIdCounterData;

  TAwardCounterData data;
  TAwardCounterData premiumData;
  TByIdCounterData talentsData;
  TByIdCounterData premiumTalentsData;
  TByIdCounterData marketingEventsData;
  TByIdCounterData clanWarsRatingData;

  vector<string> counterNames;

  CObj<NWorld::PFResourcesCollection> resourcesCollection;

  int iterations;
  bool premium;

public:
  void Init(NWorld::PFResourcesCollection * _resourcesCollection, const vector<string> & _counterNames, const int _iterations, const bool _premium)
  {
    iterations = _iterations;
    counterNames = _counterNames;
    resourcesCollection = _resourcesCollection;
    premium = _premium;

    // Countable awards
    for (int awardType = roll::EAwardType::Talent; awardType < roll::EAwardType::NumOfAwardTypes; ++awardType) // !!!!!!!!
    {
      if ( !IsCountableAward( (roll::EAwardType::Enum)awardType ) )
        continue;

      TAwardCounters & awardsCounters = data[awardType];
      awardsCounters.resize( counterNames.size() );
      if (premium)
      {
        TAwardCounters & premiumAwardsCounters = premiumData[awardType];
        premiumAwardsCounters.resize( counterNames.size() );
      }
    }

    // Init talents
    const NWorld::PFResourcesCollection::TalentMap & talentMap = resourcesCollection->GetTalents();

    for (NWorld::PFResourcesCollection::TalentMap::const_iterator it = talentMap.begin(); it != talentMap.end(); ++it)
    {
      if (it->second->rarity != NDb::TALENTRARITY_CLASS)
      {
        TByIdCounters & talentCounters = talentsData[it->first];
        talentCounters.resize(counterNames.size());
        if ( premium )
        {
          TByIdCounters & premiumTalentCounters = premiumTalentsData[it->first];
          premiumTalentCounters.resize(counterNames.size());
        }
      }
    }

    // Init marketing events
    const NWorld::PFResourcesCollection::MarketingItemMap & marketingItemMap = resourcesCollection->GetMarketingItems();

    for (NWorld::PFResourcesCollection::MarketingItemMap::const_iterator it = marketingItemMap.begin(); it != marketingItemMap.end(); ++it)
    {
      TByIdCounters & eventCounters = marketingEventsData[it->first];
      eventCounters.resize(counterNames.size());
    }
  }

  void Add(const vector<roll::SAwardInfo> & awards, int counter)
  {
    for (int i = 0; i < awards.size(); ++i)
    {
      if ( !awards[i].isOwnedByPlayer )
        continue;

      const int awardCnt = awards[i].count;
      const int awardBonus = awards[i].bonus.count;
      nstl::string awardBonusId = awards[i].bonus.id;
      TAwardCounterData::iterator it;
      if (awards[i].isPremium)
      {
          it = premiumData.find( awards[i].type );
          // Process Countable awards
          if ( it != premiumData.end() )
          {
            TAwardCounters& awardCounters = it->second;

            CounterData& counterData = awardCounters[counter];
            counterData.total += awardCnt;
            counterData.bonus += awardBonus;

            if ( awardCnt < counterData.cmin )
              counterData.cmin = awardCnt;

            if ( awardCnt > counterData.cmax )
              counterData.cmax = awardCnt;
          }
      }
      else
      {
          it = data.find( awards[i].type );

          // Process Countable awards
          if ( it != data.end() )
          {
            TAwardCounters& awardCounters = it->second;

            CounterData& counterData = awardCounters[counter];
            counterData.total += awardCnt;
            counterData.bonus += awardBonus;

            if ( awardCnt < counterData.cmin )
              counterData.cmin = awardCnt;

            if ( awardCnt > counterData.cmax )
              counterData.cmax = awardCnt;
          }
      }

      // Process talents
      if (awards[i].type == roll::EAwardType::Talent)
      {
        if ( awards[i].isPremium )
        {
          TByIdCounterData::iterator talentCounters = premiumTalentsData.find( (uint)awards[i].id );
          NI_VERIFY( talentCounters != premiumTalentsData.end(), "Talent not found!", continue );

          talentCounters->second[ counter ].count += awardCnt;
          talentCounters->second[ counter ].bonus += awardBonus;
        }
        else
        {
          TByIdCounterData::iterator talentCounters = talentsData.find( (uint)awards[i].id );
          NI_VERIFY( talentCounters != talentsData.end(), "Talent not found!", continue );

          talentCounters->second[ counter ].count += awardCnt;
          talentCounters->second[ counter ].bonus += awardBonus;
        }
      }

      // Process marketing events
      if (awards[i].type == roll::EAwardType::MarketingEvent)
      {
        TByIdCounterData::iterator eventCounters = marketingEventsData.find( (uint)awards[i].id );
        NI_VERIFY( eventCounters != marketingEventsData.end(), "Markerting event not found!", continue );

        eventCounters->second[ counter ].count += awardCnt;
      }
    }
  }

  void Add(vector<roll::SUserAward> & awards, int counter)
  {
    for (int i = 0; i < awards.size(); ++i)
    {
      int wlcounter = counter;
      if (!awards[i].playerWin)
        wlcounter += 1;
      Add(awards[i].awards, wlcounter);
    }
  }

  void DumpTalents( const CObj<Stream>& file, TByIdCounterData& talentsData, bool isBuffsEnable )
  {
    for (TByIdCounterData::const_iterator it = talentsData.begin(); it != talentsData.end(); ++it)
    {
      NDb::Ptr<NDb::Talent> talent = resourcesCollection->FindTalentById(it->first);
      //NI_VERIFY( IsValid(talent), "Failed to find talent db!", continue );
      file->WriteString( NStr::StrFmt( "%s;%s;%s;", talent->persistentId.c_str(), talent->GetDBID().GetFileName().c_str(), NDb::EnumToString(talent->rarity) ) );
      const TByIdCounters & talentCounters = it->second;
      string frmStr;
      for (int tc = 0; tc < talentCounters.size(); ++tc)
      {
        frmStr = NStr::StrFmt( "%d;", talentCounters[tc].count );
        if(isBuffsEnable)
        {
          frmStr = NStr::StrFmt( "%d (%d);", talentCounters[tc].count, talentCounters[tc].bonus);
        }

        file->WriteString( frmStr );
      }
      file->WriteString( ";\n" );
    }
    file->WriteString( "\n" );
  }

  void WriteToFile(const string & fileName, bool isBuffsEnable)
  {
    CObj<Stream> file = new FileWriteStream( fileName, FILEACCESS_WRITE, FILEOPEN_CREATE_NEW );
    NI_VERIFY( file->IsOk(), "Failed to open output file!", return );

    string counterNamesHeadLine;
    for (int i = 0; i < counterNames.size(); ++i)
    {
      counterNamesHeadLine.append( ";" + counterNames[i] );
    }
    counterNamesHeadLine.append( ";\n" );

    // Dump countable awards
    file->WriteString( "award type;;" );
    file->WriteString( counterNamesHeadLine );

    for (TAwardCounterData::const_iterator it = data.begin(); it != data.end(); ++it)
    {

      string frmStr = NI_STRFMT( "%s;;;", roll::EAwardType::ToString( roll::EAwardType::Enum(it->first) ) );
      file->WriteString( frmStr );
      const TAwardCounters & awardCounters = it->second;

      for (int tc = 0; tc < awardCounters.size(); ++tc)
      {
         

        const float average = (float)awardCounters[tc].total / iterations;
        const int cmin = awardCounters[tc].total != 0 ? awardCounters[tc].cmin : 0;
        const int cmax = awardCounters[tc].total != 0 ? awardCounters[tc].cmax : 0;
        
        frmStr = NStr::StrFmt( "%.1f ( %d, %d, %d);", average, cmin , cmax, awardCounters[tc].total );
        if(isBuffsEnable)
          frmStr = NStr::StrFmt( "%.1f ( %d, %d, %d)(%d);", average, cmin , cmax, awardCounters[tc].total, awardCounters[tc].bonus );

        file->WriteString( frmStr );
      }
      file->WriteString( ";\n" );
    }
    file->WriteString( "\n" );
    if (premium)
    {
      file->WriteString( "\n" );
      file->WriteString( "premium bonuses \n" );
      for (TAwardCounterData::const_iterator it = premiumData.begin(); it != premiumData.end(); ++it)
      {

        string frmStr = NI_STRFMT( "%s;;;", roll::EAwardType::ToString( roll::EAwardType::Enum(it->first) ) );
        file->WriteString( frmStr );
        const TAwardCounters & awardCounters = it->second;
        for (int tc = 0; tc < awardCounters.size(); ++tc)
        {
          const float average = (float)awardCounters[tc].total / iterations;
          const int cmin = awardCounters[tc].total != 0 ? awardCounters[tc].cmin : 0;
          const int cmax = awardCounters[tc].total != 0 ? awardCounters[tc].cmax : 0;
          frmStr = NStr::StrFmt( "%.1f ( %d, %d, %d);", average, cmin , cmax, awardCounters[tc].total );
          file->WriteString( frmStr );
        }
        file->WriteString( ";\n" );
      }
      file->WriteString( "\n" );
    }

    // Dump talents by persistentId
    file->WriteString( "talent;file;rarity;" );
    file->WriteString( counterNamesHeadLine );

    DumpTalents( file, talentsData, isBuffsEnable );
    if ( premium )
    {
      file->WriteString( "premium talents\n" );
      DumpTalents( file, premiumTalentsData, isBuffsEnable );
    }

    // Dump marketing events by persistentId
    file->WriteString( "lamp;file;" );
    file->WriteString( counterNamesHeadLine );

    for (TByIdCounterData::const_iterator it = marketingEventsData.begin(); it != marketingEventsData.end(); ++it)
    {
      NDb::Ptr<NDb::MarketingEventRollItem> marketingEvent = resourcesCollection->FindMarketingById(it->first);
      //NI_VERIFY( IsValid(talent), "Failed to find talent db!", continue );
      file->WriteString( NStr::StrFmt( "%s;%s;;", marketingEvent->persistentId.c_str(), marketingEvent->GetDBID().GetFileName().c_str() ) );
      const TByIdCounters & marketingEventCounters = it->second;
      for (int tc = 0; tc < marketingEventCounters.size(); ++tc)
      {
        file->WriteString( NStr::StrFmt( "%d;", marketingEventCounters[tc].count ) );
      }
      file->WriteString( ";\n" );
    }
  }
};


int times;
int energy;
int hlevel;
int rating;
int hrating;
int grating;
int prating;
bool premium;
float premiumDropRate;
bool fwod;
int wscore;
int lscore;
int forge;
int spoints;
string goldlamp;
string outputFileName;
bool customGame;
string debugLogFileName;
bool enableDebugLogging;
string inCacheFile;
string outCacheFile;
bool hasFullLibrary;
NCore::EBasket::Enum basket;
int cwGuildMemberCountWin; //-cw-gm-count-win
int cwPlayersWithGuildWarEventPassWin; //-cw-gme-pass-count
int cwPlayersWithGuildWarEventPassDef; //-cw-gme-pass-count
int cwGuildMemberCountDef; //-cw-gm-count-def
int cwDefetedGroupSize; //-cw-def-group-size
int sessionType;
bool isBuffsEnable = false;
bool hasOneGuildBothSide;
string useThisBuffs;

vector<string> registeredArgs;

int RegisterCmdLineParam( const char* name, int defaultValue )
{
  registeredArgs.push_back( name );
  return CmdLineLite::Instance().GetIntKey( name, defaultValue );
}

string RegisterCmdLineParam( const char* name, const char* defaultValue )
{
  registeredArgs.push_back( name );
  return CmdLineLite::Instance().GetStringKey( name, defaultValue );
}

bool RegisterCmdLineParam( const char* name )
{
  registeredArgs.push_back( name );
  return CmdLineLite::Instance().IsKeyDefined( name );
}

void ReadArgs()
{
  times = RegisterCmdLineParam( "-times", 1000 );
  energy = RegisterCmdLineParam( "-energy", 100 );
  hlevel = RegisterCmdLineParam( "-hlevel", 1 );
  rating = RegisterCmdLineParam( "-rating", 1500 );
  hrating = RegisterCmdLineParam( "-hrating", rating );
  grating = RegisterCmdLineParam( "-grating", rating );
  prating = RegisterCmdLineParam( "-prating", rating );
  premium = RegisterCmdLineParam( "-premium" );
  premiumDropRate = RegisterCmdLineParam( "-premiumDropRate", 2 );
  fwod = RegisterCmdLineParam( "-fwod" );
  wscore = RegisterCmdLineParam( "-wscore", 150 );
  lscore = RegisterCmdLineParam( "-lscore", 50 );
  forge = RegisterCmdLineParam( "-forge", 0 );
  goldlamp = RegisterCmdLineParam( "-lamp", "" );
  spoints = RegisterCmdLineParam( "-spoints", 0 );
  outputFileName = RegisterCmdLineParam( "-output", "" );
  customGame = RegisterCmdLineParam( "-cgame" );
  debugLogFileName = RegisterCmdLineParam( "-logfile", "" );
  enableDebugLogging = RegisterCmdLineParam( "-log" );
  inCacheFile = RegisterCmdLineParam( "-cache-file-in", "" );
  outCacheFile = RegisterCmdLineParam( "-cache-file-out", "" );
  hasFullLibrary = RegisterCmdLineParam( "-fullLibrary" );
  basket = (NCore::EBasket::Enum)RegisterCmdLineParam( "-basket", 1 );
  cwGuildMemberCountWin = RegisterCmdLineParam( "-cw-guild-member-count-win", 2 );
  cwGuildMemberCountDef = RegisterCmdLineParam( "-cw-guild-member-count-def", 2 );
  cwDefetedGroupSize = RegisterCmdLineParam( "-cw-defeted-group-size", 0 );
  useThisBuffs = RegisterCmdLineParam( "-enable-buffs", "" );
  hasOneGuildBothSide = RegisterCmdLineParam( "-one-guild-both-side" );
  sessionType = RegisterCmdLineParam( "-session-type", 1 );
  
  cwPlayersWithGuildWarEventPassWin = RegisterCmdLineParam( "-cw-gme-pass-count-win", 1);
  cwPlayersWithGuildWarEventPassDef = RegisterCmdLineParam( "-cw-gme-pass-count-def", 1 );
}

int CheckArgs()
{
  int argsCnt = CmdLineLite::Instance().ArgsCount();

  for ( int i = 1; i < argsCnt; ++i )
  {
    const char* arg = CmdLineLite::Instance().Argument( i );

    // skip param value
    if ( arg[0] != '-' )
      continue;

    // search within registered arg names
    bool found = false;
    for ( int regCounter = 0, regTotal = registeredArgs.size(); regCounter < regTotal; ++regCounter )
    {
      if ( !_stricmp( arg, registeredArgs[regCounter].c_str() ) )
      {
        found = true;
        break;
      }
    }

    if ( !found )
      return i;
  }

  return 0;
}


roll::SUserAward GetUserAwardsFromCache(int userId, const vector<roll::SUserAward>& rollResultBasket)
{
  vector<roll::SUserAward>::const_iterator iter = rollResultBasket.begin();
  for(; iter != rollResultBasket.end(); ++ iter)
  {
    if(iter->userId == userId)
      return *iter;
  }

  return roll::SUserAward();
}

void FillUserDataPlayers(vector<roll::SPreGamePerUserData> & preUsers, vector<roll::SPostGamePerUserData> & postUsers, int usersPerTeam, const vector<roll::SUserAward>& userAwards)
{
  preUsers.clear();
  postUsers.clear();

  lobby::ETeam::Enum team = lobby::ETeam::Team1;
  int playerID = 100;
  for (int i = 0; i < 2; ++i)
  {
    for (int u = 0; u < usersPerTeam; ++u, ++playerID)
    {
      roll::SPreGamePerUserData & preUserData = preUsers.push_back();
      preUserData.clientId = playerID;
      preUserData.faction = team;
      preUserData.playerInfo.auid = playerID;
      preUserData.playerInfo.heroEnergy = energy;
      preUserData.playerInfo.heroLevel = hlevel;
      preUserData.playerInfo.guardRating = grating;
      preUserData.playerInfo.playerRating = prating;
      preUserData.playerInfo.heroRating = hrating;
      preUserData.playerInfo.hasPremium = premium;
      preUserData.playerInfo.fwod = fwod;
      preUserData.playerInfo.goldLampRollContainer = goldlamp;
      preUserData.playerInfo.customGame = customGame;
      preUserData.playerInfo.hasFullLibrary = hasFullLibrary;
      preUserData.playerInfo.basket = basket;
      preUserData.playerInfo.dropRate = premiumDropRate;
      
      

      if(userAwards.size())
      {
        roll::SUserAward prevAwards = GetUserAwardsFromCache(playerID, userAwards);

        NCore::TalentRollData rollData;
        rollData.rollTable = prevAwards.talentRollData.rollTable;
        rollData.generationIndex = prevAwards.talentRollData.generationIndex;

        preUserData.playerInfo.talentRollData = rollData;
      }

      roll::SPostGamePerUserData & postUserData = postUsers.push_back();
      postUserData.clientId = playerID;
      postUserData.statistics.clientId = playerID;
      postUserData.statistics.clientState = Peered::EGameFinishClientState::FinishedGame;
    }
    team = lobby::ETeam::Team2;
  }
}


void FillPlayersScore(vector<roll::SPreGamePerUserData> & preUsers, vector<roll::SPostGamePerUserData> & postUsers, lobby::ETeam::Enum victoriousFaction)
{
  int defetedPartyId = 100;
  int defetedParyPlayerCount = cwDefetedGroupSize;

  int winnersGuildId = 100;
  int guildMemberCountWin = cwGuildMemberCountWin;
  int guildMemberCountDef = cwGuildMemberCountDef;
  int playerWithGWEPassWin = cwPlayersWithGuildWarEventPassWin;
  int playerWithGWEPassDef = cwPlayersWithGuildWarEventPassDef;


  for (int i = 0; i < postUsers.size(); ++i)
  {
    postUsers[i].scoring.score = (preUsers[i].faction == victoriousFaction) ? (wscore) : (lscore);
    postUsers[i].scoring.specialPoints = (preUsers[i].faction != victoriousFaction) ? (spoints) : (0);

    if(defetedParyPlayerCount != 0 && preUsers[i].faction != victoriousFaction)
    {
      preUsers[i].playerInfo.partyId = defetedPartyId;
      --defetedParyPlayerCount;
    }

    if(guildMemberCountWin != 0 && preUsers[i].faction == victoriousFaction)
    {
      preUsers[i].playerInfo.guildData.id = winnersGuildId;
      --guildMemberCountWin;
    }

    if(playerWithGWEPassWin != 0 && preUsers[i].faction == victoriousFaction)
    {
      preUsers[i].playerInfo.guildData.guidWarEventPass = true;
      --playerWithGWEPassWin;
    }

    if(guildMemberCountDef != 0 && preUsers[i].faction != victoriousFaction)
    {
      preUsers[i].playerInfo.guildData.id = hasOneGuildBothSide ? winnersGuildId : winnersGuildId - 1;
      --guildMemberCountDef;
    }

    if(playerWithGWEPassDef != 0 && preUsers[i].faction != victoriousFaction)
    {
      preUsers[i].playerInfo.guildData.guidWarEventPass = true;
      --playerWithGWEPassDef;
    }
  }
}


void CopyTalentsData(vector<roll::SPreGamePerUserData> & preUsers, const vector<roll::SUserAward> & rollResults)
{
  NI_VERIFY( preUsers.size() == rollResults.size(), "Users count mismatch!", return; );

  for (int i = 0; i < preUsers.size(); ++i)
  {
    NI_VERIFY( preUsers[i].clientId == rollResults[i].userId, "User Id mismatch!", continue; );
    preUsers[i].playerInfo.talentRollData = rollResults[i].talentRollData;
  }
}


roll::EMode::Enum GetRollMode(const NDb::Ptr<NDb::AdvMapDescription> advMapDescription)
{
  switch ( advMapDescription->mapType )
    {
    case NDb::MAPTYPE_PVP:
    case NDb::MAPTYPE_CTE:
      if ( customGame )
        return roll::EMode::CustomGame;
      else
        return roll::EMode::PvP;
      break;

    case NDb::MAPTYPE_TRAINING:
      return roll::EMode::Train;
      break;

    case NDb::MAPTYPE_TUTORIAL:
      return roll::EMode::Tutorial;
      break;

    case NDb::MAPTYPE_SERIES:
      return roll::EMode::Singleplayer;
      break;

    case NDb::MAPTYPE_COOPERATIVE:
      return roll::EMode::Coop;
      break;

    default:
      return roll::EMode::PvP;
    }
}


//=============================================================================

int main( int argc, char ** args )
{

  CmdLineLite::Instance().Init( argc, args );
  ReadArgs();
  registeredArgs.push_back("-map");
  int p = CheckArgs();
  if ( p != 0 )
  {
    std::cout << "Unknown argument " << CmdLineLite::Instance().Argument(p) << "\n";
    return EXIT_FAILURE;
  }

  NDebug::SetProductNameAndVersion( NFile::GetCurrDir(), "RollTestTool", VERSION_LINE, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_REVISION );

  //setup logging for roll logic
  nstl::string channelId = ROLL_SVC_CHNL;
  nstl::string channelFileSuffix = "roll-debug-log";
  nstl::string logFolderPath = NDebug::GetDebugLogDir();

  StrongMT<NLogg::BasicTextFileDumper> textLogDumper;

  if (enableDebugLogging)
  {
    textLogDumper = NLogg::BasicTextFileDumper::New( 0, channelFileSuffix.c_str(), logFolderPath.c_str() );
    GetSystemLog().AddChannel( channelId.c_str(), textLogDumper, NLogg::GetFromMinLevelMask( NLogg::LEVEL_DEBUG ) );
  }

  NFile::InitBaseDir();

  NProfile::Init(NDebug::GetProductName());
  NGlobal::ExecuteConfig( "pvx_srv_roll.cfg", NProfile::FOLDER_GLOBAL );

  RootFileSystem::RegisterFileSystem( new WinFileSystem( NFile::GetBaseDir() + "Data", false ) );
  NDb::SetResourceCache( NDb::CreateGameResourceCache( RootFileSystem::GetRootFileSystem(), &RootFileSystem::GetChangesProcessor() ) );
  NDb::SessionRoot::InitRoot( NDb::Get<NDb::SessionRoot>( NDb::DBID( "Session.ROOT" ) ) );

  vector<string> maps;
  CmdLineLite::Instance().GetStringKeys( maps, "-map" );
  NI_VERIFY( maps.size() > 0 || forge > 0, "No map selected for roll, nor forge!", return EXIT_FAILURE );

  vector<string> counters( maps.size()*2 + ((forge > 0)?(1):(0)) );
  for (int i = 0; i < maps.size(); ++i)
  {
    counters[i*2] = maps[i] + " (win)";
    counters[i*2+1] = maps[i] + " (lose)";
  }
  int forgeIdx = maps.size()*2;
  if (forge > 0)
  {
    counters[forgeIdx] = NStr::StrFmt( "Forge (%d)", forge );
  }

  CObj<NWorld::PFResourcesCollection> resourcesCollection = new NWorld::PFResourcesCollection();

  StrongMT<roll::IConfigProvider> config = roll::CreateConfigFromStatics();

  Strong<roll::DropNRoll> rollLogic = new roll::DropNRoll( config, roll::DropNRoll::DbRoot(), NDb::SessionRoot::GetRoot()->logicRoot->mapList, resourcesCollection );
  resourcesCollection->CollectMarketingItems();

  AwardsCounter ac;
  ac.Init(resourcesCollection, counters, times, premium);

  vector<roll::SUserAward> rollResult;
  roll::SPreGameData preGame;
  roll::SPostGameData postGame;

  preGame.sessionType = (lobby::ETypeOfSession::Enum)sessionType;

  postGame.gameResult = lobby::EGameResult::SyncResults;
  postGame.totalSeconds = 1800;

  RollTestToolStorage userAwardsCache;

  bool persistRollResult = outCacheFile.length() > 0;

  if(inCacheFile.length())
  {
    userAwardsCache.LoadFromFile(inCacheFile);
    if(userAwardsCache.IsOk())
      std::cout << "\n\rRollCache loaded from file: " << inCacheFile.c_str() << "\n";
    else
    {
      std::cout << "\n\rError in loading RollCache from file: " << inCacheFile.c_str() << "\n";
      return EXIT_FAILURE;
    }
  }

  NCore::TAwardsBuffs awardBuff;
  PlayersBuffs playersBuffs;
  InitBuffs(buffs, awardBuff);

  if(!useThisBuffs.empty() && 0 == useThisBuffs.compare(USE_THIS_BUFFS_ENABLE))
  {
    isBuffsEnable = true;
  }
  else if(!useThisBuffs.empty())
  {
    playersBuffs.clear();
    InitPlayersBuffs(useThisBuffs, awardBuff, playersBuffs);
    if(!playersBuffs.empty())
      isBuffsEnable = true;
  }

  int gameId = 0;
  for (int m = 0; m < maps.size(); ++m)
  {
    preGame.mapDesc = maps[m];

    const NDb::Ptr<NDb::AdvMapDescription> pDBMapDesc = NDb::Get<NDb::AdvMapDescription>( NDb::DBID( preGame.mapDesc ) );

    NI_ASSERT( pDBMapDesc, NI_STRFMT( "Map %s not found", preGame.mapDesc ) );
    
    preGame.mode = GetRollMode(pDBMapDesc);

    vector<roll::SUserAward> chachedRollResult;

    if(userAwardsCache.IsOk())
    {
      userAwardsCache.GetRollResultForMap(chachedRollResult, preGame.mapDesc);
      if(userAwardsCache.IsOk())
        std::cout << "\rUsing RollCache for map: " << preGame.mapDesc.c_str() << "\n";
      else if(userAwardsCache.IsDataError())
        std::cout << "\rNot found RollCache for map: " << preGame.mapDesc.c_str() << "\n";
    }

    FillUserDataPlayers(preGame.users, postGame.users, pDBMapDesc->teamSize, chachedRollResult );

    if(isBuffsEnable && playersBuffs.empty()) // roll all buffs
      FillUserBuffs(awardBuff, preGame.users);
    else 
      FillUserBuffs(playersBuffs, preGame.users);

    std::cout << "Roll for: " << maps[m].c_str() << "\n";

    for (int t = 0; t < times; ++t)
    {
      std::cout << "\r" << t*100/times << "%";

      preGame.socialLobbyGameId = gameId;
      postGame.victoriousFaction = (postGame.victoriousFaction == lobby::ETeam::Team1)?(lobby::ETeam::Team2):(lobby::ETeam::Team1);
      FillPlayersScore(preGame.users, postGame.users, postGame.victoriousFaction);

      map<NCore::TGuildAuid, roll::SGuildAward> guildAwards;
      rollLogic->RollAwards(rollResult, guildAwards, preGame, postGame);
      ac.Add(rollResult, m*2);

      CopyTalentsData(preGame.users, rollResult);
      ++gameId;
    }

    if(persistRollResult)
    {
      userAwardsCache.AddRollResultForMap(rollResult, preGame.mapDesc);
      if(userAwardsCache.IsOk())
        std::cout << "\rRoll results for map: " << preGame.mapDesc.c_str() << " added to RollCache." << "\n";
    }

    std::cout << "\rDone.\n";
  }

  if(persistRollResult)
  {
    userAwardsCache.SaveToFile(outCacheFile);
    if(userAwardsCache.IsOk())
      std::cout << "\n\rRollCache saved into file: " << outCacheFile.c_str() << "\n";
    else
    {
      std::cout << "\n\rError in saving RollCache into file: " << outCacheFile.c_str() << "\n";
      return EXIT_FAILURE;
    }
  }

  if (forge > 0)
  {
    std::cout << "Roll forge\n";

    roll::SUserAward award;
    roll::SForgeRollData data;
    data.uid = 101;
    data.count = 4;
    for (int t = 0; t < times; ++t)
    {
      std::cout << "\r" << t*100/times << "%";

      data.rollId = t;

      rollLogic->RollForge(award, data);
      ac.Add(award.awards, forgeIdx);

      data.talentRollData = award.talentRollData;
      award.awards.clear();
    }
    std::cout << "\rDone.\n";
  }

  if (outputFileName.empty())
    outputFileName = NDebug::GenerateDebugFileName( NStr::StrFmt( "roll-talents" ), "csv" );
  else
    outputFileName = NStr::StrFmt( "%s/%s", NDebug::GetDebugLogDir(), outputFileName);

  ac.WriteToFile(outputFileName, isBuffsEnable);

  GetSystemLog().ClearAllDumpers();

  NDb::SessionRoot::InitRoot( 0 );

  return EXIT_SUCCESS;
}