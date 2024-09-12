#include "stdafx.h"

#include "RollConfig.h"

NI_DEFINE_REFCOUNT( roll::IConfigProvider );

namespace roll
{

SRollConfig::SRollConfig() :
loadNotifyPeriod( 5.0f ),
instanceUpdateTimeout( 30.0f ),
instanceConnectionTimeout( 180.0f ),
balancerSoftLimit( 500 ), balancerHardLimit( 1000 ),
seUrl( "http://localhost:80/" ),
seProjectForUsers( "pw" ),
seProjectForGuilds( "pwguild" ),
seSender( "pw_pvx" ),
seMessageExpirePeriod( 3600 * 24 ),
seDumpJson( false ), sePrettyJson( false ),
seFirstRetryDelay( 10.0f ), seMaxRetryDelay( 640.0f ),
resourcesAmountModifier(1.0f),
cristalsAmountModifier(1.0f),
redCristalsAmountModifier(1.0f),
defaultContCCAmountModifier(1.0f),
scoreContCCAmountModifier(1.0f),
specialContCCAmountModifier(1.0f),
customCurrencyLoseCoeff(1.0f),
pvpTalentsAmountModifier(1.0f),
expAmountModifier(1.0f),
rollApplyPremiumTalentsForWinning(-1),
rollApplyPremiumTalentsForLosing(-1),
pveTalentsAmountModifier(1.0f),
pveFWODTalentsByRankMultiplier(1.f),
pvpFWODTalentsByRankMultiplier(1.f),
sendPacketAwards(false),
packetAwardsSize(30),
pvpFWODResourcesAmountModifier(1.f),
pvpFWODCristalsAmountModifier(1.f),
pvpFWODRedCristalsAmountModifier(1.f),
pvpFWODCustomCurrencyAmountModifier(1.f),
eventContainersIndex(-1),
premiumEventContainersIndex(-1)
{}


static SRollConfig s_config;

REGISTER_VAR( "roll_load_notify_period",                  s_config.loadNotifyPeriod, STORAGE_NONE );
REGISTER_VAR( "roll_instance_update_timeout",             s_config.instanceUpdateTimeout, STORAGE_NONE );
REGISTER_VAR( "roll_instance_connection_timeout",         s_config.instanceConnectionTimeout, STORAGE_NONE );
REGISTER_VAR( "roll_balancer_soft_limit",                 s_config.balancerSoftLimit, STORAGE_NONE );
REGISTER_VAR( "roll_balancer_hard_limit",                 s_config.balancerHardLimit, STORAGE_NONE );
REGISTER_VAR( "roll_se_url",                              s_config.seUrl, STORAGE_NONE );
REGISTER_VAR( "roll_se_project",                          s_config.seProjectForUsers, STORAGE_NONE );
REGISTER_VAR( "roll_se_guild_project",                    s_config.seProjectForGuilds, STORAGE_NONE );
REGISTER_VAR( "roll_se_sender",                           s_config.seSender, STORAGE_NONE );
REGISTER_VAR( "roll_se_expire_period",                    s_config.seMessageExpirePeriod, STORAGE_NONE );
REGISTER_VAR( "roll_se_first_retry_delay",                s_config.seFirstRetryDelay, STORAGE_NONE );
REGISTER_VAR( "roll_se_max_retry_delay",                  s_config.seMaxRetryDelay, STORAGE_NONE );
REGISTER_VAR( "roll_se_dump_json",                        s_config.seDumpJson, STORAGE_NONE );
REGISTER_VAR( "roll_se_pretty_json",                      s_config.sePrettyJson, STORAGE_NONE );
REGISTER_VAR( "roll_forbidden_talents_list",              s_config.forbiddenTalentsList, STORAGE_NONE );
REGISTER_VAR( "roll_drop_all",                            s_config.dropAllClientIds, STORAGE_NONE );
REGISTER_VAR( "roll_amount_resources",                    s_config.resourcesAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_amount_cristal",                      s_config.cristalsAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_amount_red_cristal",                  s_config.redCristalsAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_amount_cc_default",                   s_config.defaultContCCAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_amount_cc_score",                     s_config.scoreContCCAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_amount_cc_special",                   s_config.specialContCCAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_mult_cc_for_losing",                  s_config.customCurrencyLoseCoeff, STORAGE_NONE );
REGISTER_VAR( "roll_pve_amount_talents",                  s_config.pveTalentsAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_amount_exp",                          s_config.expAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_apply_premium_talents_for_winning",   s_config.rollApplyPremiumTalentsForWinning, STORAGE_NONE );
REGISTER_VAR( "roll_apply_premium_talents_for_losing",    s_config.rollApplyPremiumTalentsForLosing, STORAGE_NONE );
REGISTER_VAR( "roll_pvp_amount_talents",                  s_config.pvpTalentsAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_pvp_fwod_talents_multiplier",         s_config.pvpFWODTalentsByRankMultiplier, STORAGE_NONE );
REGISTER_VAR( "roll_pve_fwod_talents_multiplier",         s_config.pveFWODTalentsByRankMultiplier, STORAGE_NONE );
REGISTER_VAR( "roll_pvp_fwod_talents_by_rank_list",       s_config.fwodTalentsByRankList, STORAGE_NONE );
REGISTER_VAR( "roll_send_packet_awards",                  s_config.sendPacketAwards, STORAGE_NONE );
REGISTER_VAR( "roll_packet_awards_size",                  s_config.packetAwardsSize, STORAGE_NONE );
REGISTER_VAR( "roll_pvp_fwod_amount_resource_mul",        s_config.pvpFWODResourcesAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_pvp_fwod_amount_cristal_mul",         s_config.pvpFWODCristalsAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_pvp_fwod_amount_red_cristal_mul",     s_config.pvpFWODRedCristalsAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_pvp_fwod_custom_currency_mul",        s_config.pvpFWODCustomCurrencyAmountModifier, STORAGE_NONE );
REGISTER_VAR( "roll_event_containers_index",              s_config.eventContainersIndex, STORAGE_NONE );
REGISTER_VAR( "roll_premium_event_containers_index",      s_config.premiumEventContainersIndex, STORAGE_NONE );





class ConfigProviderPolicy
{
public:
  ConfigProviderPolicy() {}
  IConfigProvider::TConfig * CreateNewConfig() { return new IConfigProvider::TConfig( s_config ); }
};


StrongMT<IConfigProvider> CreateConfigFromStatics()
{
  return new Transport::ConfigProvider<SRollConfig, ConfigProviderPolicy>;
}

} //roll
