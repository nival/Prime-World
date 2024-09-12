#ifndef ROLL_CONFIG_H_INCLUDED
#define ROLL_CONFIG_H_INCLUDED

#include "ServerAppBase/ConfigProvider.h"


namespace roll
{


struct SRollConfig
{
  float     loadNotifyPeriod;
  float     instanceUpdateTimeout;
  float     instanceConnectionTimeout;
  int       balancerSoftLimit;
  int       balancerHardLimit;
  string    seUrl;
  string    seProjectForUsers;
  string    seProjectForGuilds;
  string    seSender;
  int       seMessageExpirePeriod;
  bool      seDumpJson, sePrettyJson;
  float     seFirstRetryDelay;
  float     seMaxRetryDelay;
  string    forbiddenTalentsList;
  string    dropAllClientIds;
  float     resourcesAmountModifier;
  float     cristalsAmountModifier;
  float     redCristalsAmountModifier;
  float     defaultContCCAmountModifier;
  float     scoreContCCAmountModifier;
  float     specialContCCAmountModifier;
  float     customCurrencyLoseCoeff;
  float     pvpTalentsAmountModifier;
  float     expAmountModifier;
  int       rollApplyPremiumTalentsForWinning;
  int       rollApplyPremiumTalentsForLosing;
  float     pveTalentsAmountModifier;
  float     pveFWODTalentsByRankMultiplier;
  float     pvpFWODTalentsByRankMultiplier;
  string    fwodTalentsByRankList;
  bool      sendPacketAwards;
  int       packetAwardsSize;
  float     pvpFWODResourcesAmountModifier;
  float     pvpFWODCristalsAmountModifier;
  float     pvpFWODRedCristalsAmountModifier;
  float     pvpFWODCustomCurrencyAmountModifier;
  int       eventContainersIndex;
  int       premiumEventContainersIndex;

SRollConfig();
};

///////////////////////////////////////////////////////////////////////////////

struct FWODTalentsByRankList
{
  FWODTalentsByRankList(){
    init();
  }
  
  FWODTalentsByRankList(string values){
    init();

    if (values.empty())
      return;

    size_t found = nstl::string::npos;
    size_t found_prev = 0;
    while (nstl::string::npos != (found = values.find(";", found_prev)))
    {
      string cur_val = values.substr(found_prev, found - found_prev);
      parseIdxValue(cur_val);

      found_prev = found + 1;
    }

    if (found_prev < static_cast<size_t>(values.length()))
    { 
      nstl::string cur_val = values.substr(found_prev);
      parseIdxValue(cur_val);
    }
  }

  void parseIdxValue(string& idx_value)
  {
    if (idx_value.empty())
      return;

    size_t delem_pos = idx_value.find(":");

    if (nstl::string::npos != delem_pos)
    {
      int idx = atoi(idx_value.substr(0, delem_pos).c_str());
      int val = atoi(idx_value.substr(delem_pos + 1, idx_value.length()).c_str());

      talents[idx] = val;
    }
  }

  void init()
  {
    for(int i = 0; i < RANK_SIZE; ++i)
    {
      talents[i] = FWODTalentsByRankList::UNKNOWN_VALUE;
    }
  }

  int getValue(int idx) const
  {
    if (isIdxValid(idx))
    {
      return talents[idx];
    }
    return FWODTalentsByRankList::UNKNOWN_VALUE;
  }

  bool setValue(int idx, int value)
  {
    if (isIdxValid(idx))
    {
      talents[idx] = value;
      return true;
    }
    return false;
  }

  bool isIdxValid(int idx) const
  {
    return (idx >= 0 && idx < RANK_SIZE);
  }

  static const int RANK_SIZE = 12;
  static const int UNKNOWN_VALUE = -1;
  int talents[RANK_SIZE];
};

///////////////////////////////////////////////////////////////////////////////


typedef Transport::IConfigProvider<SRollConfig> IConfigProvider;
typedef IConfigProvider::TConfig RollConfig;

StrongMT<IConfigProvider> CreateConfigFromStatics();

} //namespace roll

#endif ROLL_CONFIG_H_INCLUDED
