# -*- coding: utf-8 -*-
# Automatically generated file. do not modify it!!!

from base.helpers import *
from modeldata.jsonserialize import JSONSerialization
from modeldata.baseclasses import *
from modeldata.changes import *
from modeldata.collects import *
from modeldata.ref import *

addRelPath("../modeldata", "../modeldata/SharedTypes")

import ActiveGroup
import BeginnersPackEventInfo
import BeginnersPackItem
import BruteForceDefenderSettings
import BuyAeriaGoldEventInfo
import BuyAeriaItem
import BuyArcGamesGoldEventInfo
import BuyArcGamesItem
import BuyGamigoGoldEventInfo
import BuyGamigoItem
import BuyGoldHeroInfo
import BuySpecialHeroEventInfo
import BuySteamGoldEventInfo
import BuySteamItem
import BuyZZimaGoldEventInfo
import BuyZZimaItem
import ComplaintsSettings
import CustomFlag
import DonateEvent
import DonateEventRange
import DonateEventReward
import EventToolsChangeFields
import ExperienceRewardRelation
import GuildBankSettings
import HonorSettings
import LampEventSettings
import MonetizationDisablers
import MuteSettings
import NewsInfo
import PingInfo
import ProductionDiscount
import QuestEvent
import QuestEventStage
import QuestEventStageStep
import QuestEventStageStepVariant
import ReforgeTalentPrices
import RerollShopBanner
import RerollShopGroupUpgradeLevels
import RerollShopWeightsToTimes
import ResourceTable
import RollEvent
import RollEventItem
import RollEventRule
import SeasonEvent
import SeasonEventShopGroup
import SeasonEventShopItem
import SeasonProgressRewardRelation
import SiegeSettings
import TalentsCollectionSettings
import TamburInfo
import TournamentSettings
import TradeEvent
import TradeEventGroup
import TradeGroupMember
import WorldRatingRewardRelation

import pwconst # специфические константы PW (кол-во талантов в строке TalentSet и т.п.)
from iuserdata import IAbstractModelData
from modeldata.validator import *
from ConfigDataCustom import ConfigDataCustom

class ConfigData(ChangeHandler, ConfigDataCustom, IChangeWriter, IAbstractModelData, AutoIncGuidGenerator):
    _changeFields = {
        "ADD_FIRST_QUEST":1,
        "ADD_LEAVE_POINT":1,
        "ADDITIONAL_CONFIGS":1,
        "ADMIN_MESSAGES_TO_STORE":1,
        "ADMIN_NICKS":1,
        "AERIA_PAY_SERVER":1,
        "AFTERPARTY_TIMEOUT":1,
        "ALLOW_REROLL_FROM_SET_FOR_UPGRADED_TALENTS_ON_REFORGE":1,
        "ALTERNATIVE_QUESTS":1,
        "APPEARING_GOLDPRODUCTIONHOUSE_PRICE":1,
        "ARCGAMES_APPID":1,
        "ARCGAMES_PAY_SERVER":1,
        "ARCGAMES_USE_OVERLAY":1,
        "AUTOMUTE_DURATION":1,
        "BEHAVIOUR_DETECTED_ENABLE":1,
        "BUY_HERO_MAX_ORIGINAL_PRICE":1,
        "BUY_HERO_PRICE":1,
        "CAMERA_FLYBY_TIMEOUT_DURATION":1,
        "CHANGE_FRACTION_TO_ADORNIA":1,
        "CHANGE_FRACTION_TO_DOCT":1,
        "CHECK_REQUESTS_REPEATABILITY":1,
        "COST_FRACTION_CHANGE":1,
        "COST_NICK_CHANGE":1,
        "DEBUG_ENABLED":1,
        "DEFAULT_FRACTION":1,
        "DEFAULT_SKINS":1,
        "DEFEATS_COUNT_FOR_KICK_FROM_TOURNAMENT":1,
        "DELAYED_SESSION_START_TIME":1,
        "DISABLED_DEFAULT_TALENSETS":1,
        "DONT_VALIDATE_STEAM_DLC":1,
        "DRAUGASLT_PAY_SERVER":1,
        "DRAUGASLT_PAY_URL_PARAMS":1,
        "DRAUGASLT_PAY_URL_SALT":1,
        "ENABLE_AUTOACCEPT":1,
        "ENABLE_TAVERT_REROLL_ON_LEVELUP":1,
        "EPIC_HERO_FORCE":1,
        "EPIC_HERO_RETIRE_LIFETIME":1,
        "EPIC_HERO_RETIRED_CAP":1,
        "EPIC_HERO_RETIRED_TIME_BASE":1,
        "EPIC_HERO_RETIRED_TIME_INC":1,
        "EPIC_WINS_STRIKE":1,
        "FAVORITE_FRIENDS_LIMIT":1,
        "FORBIDDEN_FOR_PARTY_HERO_PAIRS":1,
        "FREE_FRACTION_CHANGES":1,
        "FREE_NICK_CHANGES":1,
        "FRIENDS_PAGE_SIZE":1,
        "FWOD_FOR_NEWBIES":1,
        "GAMIGO_PAY_SERVER":1,
        "GAMIGO_PAY_URL_SALT":1,
        "GIVE_ALL_HEROES":1,
        "GM_TOOL_UNBAN_COST":1,
        "GUILD_BEST_PLAYERS":1,
        "GUILD_CREATE_PRICE_SILVER":1,
        "GUILD_DEFAULT_RATING":1,
        "GUILD_ENABLED":1,
        "GUILD_FREE_ICON_CHANGES_COUNT":1,
        "GUILD_ICON_CHANGE_COST":1,
        "GUILD_ICONS_URL_PATTERN":1,
        "GUILD_INVITE_TIMEOUT":1,
        "GUILD_LIST_RECOMMENDED_VASSAL_SIZE":1,
        "GUILD_MAX_LOG_SIZE":1,
        "GUILD_MAX_RECOMMENDED_VASSAL_SIZE":1,
        "GUILD_MAX_SIZE":1,
        "GUILD_MAX_VASSAL_SIZE":1,
        "GUILD_MIN_LEVEL_FOR_ICON_CHANGE":1,
        "GUILD_RATE_TECHS_WEIGHT":1,
        "GUILD_RENAME_PRICE_GOLD":1,
        "GUILD_SHOP_ITEMS":1,
        "GUILD_SUZERAIN_INVITE_LIMIT":1,
        "GUILD_SUZERAIN_INVITE_TIMELIMIT":1,
        "GUILD_SUZERAIN_INVITE_TIMEOUT":1,
        "GUILD_WAR_EVENT_ENABLED":1,
        "GUILD_WARS_ENABLED":1,
        "GUILDS_IN_LIST_PER_REQUEST":1,
        "HERO_COEFF_RATING":1,
        "HERO_CUP_RATING":1,
        "HERO_DELTA_RATING":1,
        "HERO_START_RATING":1,
        "HIDE_BACK_SCREEN_TIMEOUT":1,
        "INIT_FAME":1,
        "INIT_SILVER":1,
        "INIT_TALENTS":1,
        "INVALID_HEROES":1,
        "INVALID_QUESTS":1,
        "INVALID_SKINS":1,
        "IS_REFORGE_ACTIVE":1,
        "K_FORCE_RATING":1,
        "KEEPALIVE_TIMEOUT":1,
        "KICK_FROM_TOURNAMENT_BY_TIMEOUT":1,
        "LAST_LOGIN_TIME_FOR_CASTLE_QUEST":1,
        "LEAVES_POINT":1,
        "LORD_LEVEL_FOR_ADVERTISING":1,
        "MAILRU_PAY_SERVER":1,
        "MAILRU_PAY_URL_PARAMS":1,
        "MAILRU_PAY_URL_SALT":1,
        "MAPS_FOR_PLAYER_RATING":1,
        "MARKETING_EVENTS":1,
        "MASSIVE_PAY_SERVER":1,
        "MASSIVE_PAY_URL_SALT":1,
        "MAX_GUILDS_IN_LIST":1,
        "MAX_IGNORED_PLAYERS":1,
        "MAX_LEAVES_POINT":1,
        "MAX_USER_TALENTSETS_COUNT":1,
        "MIN_LEAVES_POINT":1,
        "NEW_CHAT_PROTOCOL":1,
        "NEWBIE_WINS":1,
        "NICKNAME_REGEXES":1,
        "NUM_CHEAT_CYCLES":1,
        "ONE_TIME_QUESTS":1,
        "PARTY_FORCE_RANGE":1,
        "PARTY_RATING_RANGE":1,
        "PAY_SERVER":1,
        "PAY_URL_SALT":1,
        "PERCENT_TO_CYCLES_CHANGE":1,
        "PLAYER_RATING_PERIOD":1,
        "POINTS_PER_BAD_BEHAIVIOR_REPORTS":1,
        "PREMIUM_ACCOUNT_BONUS":1,
        "PREMIUM_ACCOUNT_DURATION":1,
        "PREMIUM_ACCOUNT_DURATION2":1,
        "PREMIUM_ACCOUNT_DURATION3":1,
        "PREMIUM_ACCOUNT_LORD_LEVEL":1,
        "PREMIUM_ACCOUNT_PRICE":1,
        "PREMIUM_ACCOUNT_PRICE2":1,
        "PREMIUM_ACCOUNT_PRICE3":1,
        "PREMIUM_ACCOUNT_SESSION_BONUS":1,
        "PREMIUM_ACCOUNT_SNOW_BANNER_TIMELEFT":1,
        "PREMIUM_ACCOUNT_TAVERN_BONUS":1,
        "PREMIUM_ACOUNT_LEFT_ALARM":1,
        "PREMIUM_ACOUNT_LEFT_ALARM_PERIOD":1,
        "PRODUCTION_BOOST_COEFF":1,
        "PUNISHED_PLAYERS_UPDATE_TIME":1,
        "RECENT_ALLIES_IN_LIST":1,
        "REQUIRED_LEVEL_FOR_EXCLUSIVE_TALENTS":1,
        "REQUIRED_LEVEL_FOR_OUTSTANDING_TALENTS":1,
        "RESET_ACCOUNT_TIME":1,
        "RETURN_FRIEND_ENABLED":1,
        "ROTATION_QUEST_LIFETIME":1,
        "SAVE_TALENTS_POINTS_ON_REFORGE":1,
        "SEASON_SKINS":1,
        "SEC_TO_CHEAT_CYCLE":1,
        "SECONDS_TO_AFK_STATE":1,
        "SEND_PENDING_EVENTS":1,
        "SESSION_TO_CASTLE_FIX_1":1,
        "SESSION_TO_CASTLE_FIX_2":1,
        "SHARING_WEBSITE_SALT":1,
        "SHARING_WEBSITE_URL":1,
        "SHIFT_MIN_RANK":1,
        "SHOW_BUY_CONFIRMATION_DIALOGS":1,
        "SILVER_TO_GUILD_RESOURCES_COEFF":1,
        "SKIN_AVATAR_BLOCK":1,
        "SKIPPED_TUTORIAL_QUESTS":1,
        "SOULBOUND_ENABLED":1,
        "START_HOUR_FOR_TAVERN_REROLL":1,
        "STATIC_DATA_OVERRIDES":1,
        "SUB_LEAVE_POINT":1,
        "TALENT_UPGRADE_LORD_LEVEL":1,
        "TALENTIDS_FOR_NEW_SN":1,
        "TALENTS_NOT_FOR_ROLL":1,
        "TESTS_ENABLED":1,
        "TIME_TO_STAY_PASSIVE":1,
        "TOTAL_BOOST_TIME":1,
        "UNLOAD_CASTLE_IN_TUTORIAL":1,
        "USE_LEVEL_SCALE_FOR_RESET_PRICE":1,
        "WEB_IM_ENABLED":1,
        "WEB_IM_WEBSITE_URL":1,
        "ZZIMA_PAY_SERVER":1,
    } 


    def __init__(self):
        ConfigDataCustom.__init__(self)
        ChangeHandler.__init__(self, u"/", self)
        AutoIncGuidGenerator.__init__(self)
        self._serializator = JSONSerialization(self)
        self.__dict__["ActiveGroups"] = Keeper(self)
        self.__dict__["BeginnersPackItemKeeper"] = Keeper(self)
        self.__dict__["BuyAeriaItemKeeper"] = Keeper(self)
        self.__dict__["BuyArcGamesItemKeeper"] = Keeper(self)
        self.__dict__["BuyGamigoItemKeeper"] = Keeper(self)
        self.__dict__["BuySteamItemKeeper"] = Keeper(self)
        self.__dict__["BuyZZimaItemKeeper"] = Keeper(self)
        self.__dict__["CustomFlagKeeper"] = Keeper(self)
        self.__dict__["DonateEventKeeper"] = Keeper(self)
        self.__dict__["DonateEventRangeKeeper"] = Keeper(self)
        self.__dict__["DonateEventRewardKeeper"] = Keeper(self)
        self.__dict__["NewsKeeper"] = Keeper(self)
        self.__dict__["QuestEventKeeper"] = Keeper(self)
        self.__dict__["QuestEventStageKeeper"] = Keeper(self)
        self.__dict__["QuestEventStageStepKeeper"] = Keeper(self)
        self.__dict__["QuestEventStageStepVariantKeeper"] = Keeper(self)
        self.__dict__["ReforgeTalentPricesKeeper"] = Keeper(self)
        self.__dict__["RerollShopGroupUpgradeLevelsKeeper"] = Keeper(self)
        self.__dict__["RerollShopWeightsToTimesKeeper"] = Keeper(self)
        self.__dict__["RollEventItemKeeper"] = Keeper(self)
        self.__dict__["RollEventKeeper"] = Keeper(self)
        self.__dict__["RollEventRuleKeeper"] = Keeper(self)
        self.__dict__["SeasonEventKeeper"] = Keeper(self)
        self.__dict__["SeasonEventShopGroupKeeper"] = Keeper(self)
        self.__dict__["SeasonEventShopItemKeeper"] = Keeper(self)
        self.__dict__["SeasonProgressRewardKeeper"] = Keeper(self)
        self.__dict__["TradeEventGroupKeeper"] = Keeper(self)
        self.__dict__["TradeEventKeeper"] = Keeper(self)
        self.__dict__["TradeExperienceRewardKeeper"] = Keeper(self)
        self.__dict__["TradeGroupMemberKeeper"] = Keeper(self)
        self.__dict__["TradeWorldRatingRewardKeeper"] = Keeper(self)
        self.__dict__["ADD_FIRST_QUEST"] = True
        self.__dict__["ADD_LEAVE_POINT"] = 6
        self.__dict__["ADDITIONAL_CONFIGS"] = SimpleList(self)
        self.__dict__["ADMIN_MESSAGES_TO_STORE"] = 30
        self.__dict__["ADMIN_NICKS"] = SimpleList(self)
        self.__dict__["AERIA_PAY_SERVER"] = "https://billing.aeriagames.com/"
        self.__dict__["AFTERPARTY_TIMEOUT"] = 40
        self.__dict__["ALLOW_REROLL_FROM_SET_FOR_UPGRADED_TALENTS_ON_REFORGE"] = True
        self.__dict__["ALTERNATIVE_QUESTS"] = SimpleDict(self)
        self.__dict__["APPEARING_GOLDPRODUCTIONHOUSE_PRICE"] = 9
        self.__dict__["ARCGAMES_APPID"] = 4600
        self.__dict__["ARCGAMES_PAY_SERVER"] = "http://billing.arcgames.com/"
        self.__dict__["ARCGAMES_USE_OVERLAY"] = False
        self.__dict__["AUTOMUTE_DURATION"] = 86400
        self.__dict__["BeginnersPackEventInfo"] = BeginnersPackEventInfo.BeginnersPackEventInfo(self)
        self.__dict__["BEHAVIOUR_DETECTED_ENABLE"] = True
        self.__dict__["BruteForceDefenderSettings"] = BruteForceDefenderSettings.BruteForceDefenderSettings(self)
        self.__dict__["BUY_HERO_MAX_ORIGINAL_PRICE"] = 125000
        self.__dict__["BUY_HERO_PRICE"] = 9
        self.__dict__["BuyAeriaGoldEventInfo"] = BuyAeriaGoldEventInfo.BuyAeriaGoldEventInfo(self)
        self.__dict__["BuyArcGamesGoldEventInfo"] = BuyArcGamesGoldEventInfo.BuyArcGamesGoldEventInfo(self)
        self.__dict__["BuyGamigoGoldEventInfo"] = BuyGamigoGoldEventInfo.BuyGamigoGoldEventInfo(self)
        self.__dict__["BuyGoldHeroInfo"] = BuyGoldHeroInfo.BuyGoldHeroInfo(self)
        self.__dict__["BuySpecialHeroEventInfo"] = BuySpecialHeroEventInfo.BuySpecialHeroEventInfo(self)
        self.__dict__["BuySteamGoldEventInfo"] = BuySteamGoldEventInfo.BuySteamGoldEventInfo(self)
        self.__dict__["BuyZZimaGoldEventInfo"] = BuyZZimaGoldEventInfo.BuyZZimaGoldEventInfo(self)
        self.__dict__["CAMERA_FLYBY_TIMEOUT_DURATION"] = 604800
        self.__dict__["CHANGE_FRACTION_TO_ADORNIA"] = True
        self.__dict__["CHANGE_FRACTION_TO_DOCT"] = True
        self.__dict__["CHECK_REQUESTS_REPEATABILITY"] = True
        self.__dict__["ComplaintsSettings"] = ComplaintsSettings.ComplaintsSettings(self)
        self.__dict__["COST_FRACTION_CHANGE"] = 0
        self.__dict__["COST_NICK_CHANGE"] = 0
        self.__dict__["CustomFlags"] = Set(self)
        self.__dict__["DEBUG_ENABLED"] = True
        self.__dict__["DEFAULT_FRACTION"] = "N"
        self.__dict__["DEFAULT_SKINS"] = SimpleList(self)
        self.__dict__["DEFEATS_COUNT_FOR_KICK_FROM_TOURNAMENT"] = 1
        self.__dict__["DELAYED_SESSION_START_TIME"] = 10
        self.__dict__["DISABLED_DEFAULT_TALENSETS"] = SimpleList(self)
        self.__dict__["DonateEvents"] = Collection(self)
        self.__dict__["DONT_VALIDATE_STEAM_DLC"] = False
        self.__dict__["DRAUGASLT_PAY_SERVER"] = ""
        self.__dict__["DRAUGASLT_PAY_URL_PARAMS"] = ""
        self.__dict__["DRAUGASLT_PAY_URL_SALT"] = ""
        self.__dict__["ENABLE_AUTOACCEPT"] = False
        self.__dict__["ENABLE_TAVERT_REROLL_ON_LEVELUP"] = False
        self.__dict__["EPIC_HERO_FORCE"] = 1500.0
        self.__dict__["EPIC_HERO_RETIRE_LIFETIME"] = 82800
        self.__dict__["EPIC_HERO_RETIRED_CAP"] = 21600
        self.__dict__["EPIC_HERO_RETIRED_TIME_BASE"] = 300
        self.__dict__["EPIC_HERO_RETIRED_TIME_INC"] = 3
        self.__dict__["EPIC_WINS_STRIKE"] = 2
        self.__dict__["EventToolsChangeFields"] = EventToolsChangeFields.EventToolsChangeFields(self)
        self.__dict__["FAVORITE_FRIENDS_LIMIT"] = 32
        self.__dict__["FORBIDDEN_FOR_PARTY_HERO_PAIRS"] = SimpleList(self)
        self.__dict__["FREE_FRACTION_CHANGES"] = 0
        self.__dict__["FREE_NICK_CHANGES"] = 0
        self.__dict__["FRIENDS_PAGE_SIZE"] = 15
        self.__dict__["FWOD_FOR_NEWBIES"] = True
        self.__dict__["GAMIGO_PAY_SERVER"] = "https://billing.gamigo.com/"
        self.__dict__["GAMIGO_PAY_URL_SALT"] = ""
        self.__dict__["GIVE_ALL_HEROES"] = False
        self.__dict__["GM_TOOL_UNBAN_COST"] = 99
        self.__dict__["GUILD_BEST_PLAYERS"] = 50
        self.__dict__["GUILD_CREATE_PRICE_SILVER"] = 150000
        self.__dict__["GUILD_DEFAULT_RATING"] = 0
        self.__dict__["GUILD_ENABLED"] = True
        self.__dict__["GUILD_FREE_ICON_CHANGES_COUNT"] = 1
        self.__dict__["GUILD_ICON_CHANGE_COST"] = 495
        self.__dict__["GUILD_ICONS_URL_PATTERN"] = "http://testcdn.playpw.com/guild_logo/{guild_id}_{changes_count}.png"
        self.__dict__["GUILD_INVITE_TIMEOUT"] = 259200
        self.__dict__["GUILD_LIST_RECOMMENDED_VASSAL_SIZE"] = 20
        self.__dict__["GUILD_MAX_LOG_SIZE"] = 50
        self.__dict__["GUILD_MAX_RECOMMENDED_VASSAL_SIZE"] = 3
        self.__dict__["GUILD_MAX_SIZE"] = 50
        self.__dict__["GUILD_MAX_VASSAL_SIZE"] = 8
        self.__dict__["GUILD_MIN_LEVEL_FOR_ICON_CHANGE"] = 10
        self.__dict__["GUILD_RATE_TECHS_WEIGHT"] = 1.0
        self.__dict__["GUILD_RENAME_PRICE_GOLD"] = 499
        self.__dict__["GUILD_SHOP_ITEMS"] = SimpleList(self)
        self.__dict__["GUILD_SUZERAIN_INVITE_LIMIT"] = 10
        self.__dict__["GUILD_SUZERAIN_INVITE_TIMELIMIT"] = 86400
        self.__dict__["GUILD_SUZERAIN_INVITE_TIMEOUT"] = 604800
        self.__dict__["GUILD_WAR_EVENT_ENABLED"] = True
        self.__dict__["GUILD_WARS_ENABLED"] = True
        self.__dict__["GuildBankSettings"] = GuildBankSettings.GuildBankSettings(self)
        self.__dict__["GUILDS_IN_LIST_PER_REQUEST"] = 100
        self.__dict__["HERO_COEFF_RATING"] = 1.0
        self.__dict__["HERO_CUP_RATING"] = 10000
        self.__dict__["HERO_DELTA_RATING"] = 0
        self.__dict__["HERO_START_RATING"] = 1290
        self.__dict__["HIDE_BACK_SCREEN_TIMEOUT"] = 60
        self.__dict__["HonorSettings"] = HonorSettings.HonorSettings(self)
        self.__dict__["INIT_FAME"] = 40500
        self.__dict__["INIT_SILVER"] = 325000
        self.__dict__["INIT_TALENTS"] = SimpleList(self)
        self.__dict__["INVALID_HEROES"] = SimpleList(self)
        self.__dict__["INVALID_QUESTS"] = SimpleList(self)
        self.__dict__["INVALID_SKINS"] = SimpleList(self)
        self.__dict__["IS_REFORGE_ACTIVE"] = False
        self.__dict__["K_FORCE_RATING"] = 1.0
        self.__dict__["KEEPALIVE_TIMEOUT"] = 5.0
        self.__dict__["KICK_FROM_TOURNAMENT_BY_TIMEOUT"] = True
        self.__dict__["LampEventSettings"] = LampEventSettings.LampEventSettings(self)
        self.__dict__["LAST_LOGIN_TIME_FOR_CASTLE_QUEST"] = 5184000
        self.__dict__["LEAVES_POINT"] = 12
        self.__dict__["LORD_LEVEL_FOR_ADVERTISING"] = 10
        self.__dict__["MAILRU_PAY_SERVER"] = ""
        self.__dict__["MAILRU_PAY_URL_PARAMS"] = ""
        self.__dict__["MAILRU_PAY_URL_SALT"] = ""
        self.__dict__["MAPS_FOR_PLAYER_RATING"] = SimpleList(self)
        self.__dict__["MARKETING_EVENTS"] = SimpleList(self)
        self.__dict__["MASSIVE_PAY_SERVER"] = "http://my.massive.ph/"
        self.__dict__["MASSIVE_PAY_URL_SALT"] = ""
        self.__dict__["MAX_GUILDS_IN_LIST"] = 400
        self.__dict__["MAX_IGNORED_PLAYERS"] = 99
        self.__dict__["MAX_LEAVES_POINT"] = 18
        self.__dict__["MAX_USER_TALENTSETS_COUNT"] = 3
        self.__dict__["MIN_LEAVES_POINT"] = 6
        self.__dict__["MonetizationDisablers"] = MonetizationDisablers.MonetizationDisablers(self)
        self.__dict__["MuteSettings"] = MuteSettings.MuteSettings(self)
        self.__dict__["NEW_CHAT_PROTOCOL"] = True
        self.__dict__["NEWBIE_WINS"] = 10
        self.__dict__["NEWS"] = Set(self)
        self.__dict__["NICKNAME_REGEXES"] = SimpleList(self)
        self.__dict__["NUM_CHEAT_CYCLES"] = 3
        self.__dict__["ONE_TIME_QUESTS"] = True
        self.__dict__["PARTY_FORCE_RANGE"] = 50.0
        self.__dict__["PARTY_RATING_RANGE"] = 100.0
        self.__dict__["PAY_SERVER"] = ""
        self.__dict__["PAY_URL_SALT"] = ""
        self.__dict__["PERCENT_TO_CYCLES_CHANGE"] = 50
        self.__dict__["PingInfo"] = PingInfo.PingInfo(self)
        self.__dict__["PLAYER_RATING_PERIOD"] = 30
        self.__dict__["POINTS_PER_BAD_BEHAIVIOR_REPORTS"] = 6
        self.__dict__["PREMIUM_ACCOUNT_BONUS"] = 2.0
        self.__dict__["PREMIUM_ACCOUNT_DURATION"] = 604800
        self.__dict__["PREMIUM_ACCOUNT_DURATION2"] = 2592000
        self.__dict__["PREMIUM_ACCOUNT_DURATION3"] = 172800
        self.__dict__["PREMIUM_ACCOUNT_LORD_LEVEL"] = 10
        self.__dict__["PREMIUM_ACCOUNT_PRICE"] = 99
        self.__dict__["PREMIUM_ACCOUNT_PRICE2"] = 299
        self.__dict__["PREMIUM_ACCOUNT_PRICE3"] = 50
        self.__dict__["PREMIUM_ACCOUNT_SESSION_BONUS"] = 2.0
        self.__dict__["PREMIUM_ACCOUNT_SNOW_BANNER_TIMELEFT"] = 259200
        self.__dict__["PREMIUM_ACCOUNT_TAVERN_BONUS"] = 2.0
        self.__dict__["PREMIUM_ACOUNT_LEFT_ALARM"] = 86400
        self.__dict__["PREMIUM_ACOUNT_LEFT_ALARM_PERIOD"] = 86400
        self.__dict__["PRODUCTION_BOOST_COEFF"] = 2.0
        self.__dict__["ProductionDiscount"] = ProductionDiscount.ProductionDiscount(self)
        self.__dict__["PUNISHED_PLAYERS_UPDATE_TIME"] = 604800
        self.__dict__["QuestEvents"] = Collection(self)
        self.__dict__["RECENT_ALLIES_IN_LIST"] = 20
        self.__dict__["REQUIRED_LEVEL_FOR_EXCLUSIVE_TALENTS"] = 15
        self.__dict__["REQUIRED_LEVEL_FOR_OUTSTANDING_TALENTS"] = 15
        self.__dict__["RESET_ACCOUNT_TIME"] = 604800
        self.__dict__["RETURN_FRIEND_ENABLED"] = True
        self.__dict__["RollEvents"] = Collection(self)
        self.__dict__["ROTATION_QUEST_LIFETIME"] = 86400
        self.__dict__["SAVE_TALENTS_POINTS_ON_REFORGE"] = True
        self.__dict__["SEASON_SKINS"] = SimpleList(self)
        self.__dict__["SeasonEvents"] = Collection(self)
        self.__dict__["SEC_TO_CHEAT_CYCLE"] = 60
        self.__dict__["SECONDS_TO_AFK_STATE"] = 900
        self.__dict__["SEND_PENDING_EVENTS"] = False
        self.__dict__["SESSION_TO_CASTLE_FIX_1"] = True
        self.__dict__["SESSION_TO_CASTLE_FIX_2"] = True
        self.__dict__["SHARING_WEBSITE_SALT"] = ""
        self.__dict__["SHARING_WEBSITE_URL"] = "http://share.qa.playpw.com/share.php"
        self.__dict__["SHIFT_MIN_RANK"] = 3
        self.__dict__["SHOW_BUY_CONFIRMATION_DIALOGS"] = False
        self.__dict__["SiegeSettings"] = SiegeSettings.SiegeSettings(self)
        self.__dict__["SILVER_TO_GUILD_RESOURCES_COEFF"] = 10.0
        self.__dict__["SKIN_AVATAR_BLOCK"] = SimpleList(self)
        self.__dict__["SKIPPED_TUTORIAL_QUESTS"] = SimpleDict(self)
        self.__dict__["SOULBOUND_ENABLED"] = True
        self.__dict__["START_HOUR_FOR_TAVERN_REROLL"] = 0
        self.__dict__["STATIC_DATA_OVERRIDES"] = SimpleDict(self)
        self.__dict__["SUB_LEAVE_POINT"] = 3
        self.__dict__["TALENT_UPGRADE_LORD_LEVEL"] = 10
        self.__dict__["TALENTIDS_FOR_NEW_SN"] = SimpleList(self)
        self.__dict__["TALENTS_NOT_FOR_ROLL"] = SimpleList(self)
        self.__dict__["TalentsCollectionSettings"] = TalentsCollectionSettings.TalentsCollectionSettings(self)
        self.__dict__["TamburInfo"] = TamburInfo.TamburInfo(self)
        self.__dict__["TESTS_ENABLED"] = False
        self.__dict__["TIME_TO_STAY_PASSIVE"] = 604800
        self.__dict__["TOTAL_BOOST_TIME"] = 82800
        self.__dict__["TournamentSettings"] = TournamentSettings.TournamentSettings(self)
        self.__dict__["TradeEvents"] = Collection(self)
        self.__dict__["UNLOAD_CASTLE_IN_TUTORIAL"] = True
        self.__dict__["USE_LEVEL_SCALE_FOR_RESET_PRICE"] = True
        self.__dict__["WEB_IM_ENABLED"] = False
        self.__dict__["WEB_IM_WEBSITE_URL"] = ""
        self.__dict__["ZZIMA_PAY_SERVER"] = "http://pay.zzima.com/"


    def init(self, changeWriter):
        self.write(changeWriter)
        self.ActiveGroups.init(u"ActiveGroups", self, "ActiveGroup")
        self.BeginnersPackItemKeeper.init(u"BeginnersPackItemKeeper", self, "BeginnersPackItem")
        self.BuyAeriaItemKeeper.init(u"BuyAeriaItemKeeper", self, "BuyAeriaItem")
        self.BuyArcGamesItemKeeper.init(u"BuyArcGamesItemKeeper", self, "BuyArcGamesItem")
        self.BuyGamigoItemKeeper.init(u"BuyGamigoItemKeeper", self, "BuyGamigoItem")
        self.BuySteamItemKeeper.init(u"BuySteamItemKeeper", self, "BuySteamItem")
        self.BuyZZimaItemKeeper.init(u"BuyZZimaItemKeeper", self, "BuyZZimaItem")
        self.CustomFlagKeeper.init(u"CustomFlagKeeper", self, "CustomFlag")
        self.DonateEventKeeper.init(u"DonateEventKeeper", self, "DonateEvent")
        self.DonateEventRangeKeeper.init(u"DonateEventRangeKeeper", self, "DonateEventRange")
        self.DonateEventRewardKeeper.init(u"DonateEventRewardKeeper", self, "DonateEventReward")
        self.NewsKeeper.init(u"NewsKeeper", self, "NewsInfo")
        self.QuestEventKeeper.init(u"QuestEventKeeper", self, "QuestEvent")
        self.QuestEventStageKeeper.init(u"QuestEventStageKeeper", self, "QuestEventStage")
        self.QuestEventStageStepKeeper.init(u"QuestEventStageStepKeeper", self, "QuestEventStageStep")
        self.QuestEventStageStepVariantKeeper.init(u"QuestEventStageStepVariantKeeper", self, "QuestEventStageStepVariant")
        self.ReforgeTalentPricesKeeper.init(u"ReforgeTalentPricesKeeper", self, "ReforgeTalentPrices")
        self.RerollShopGroupUpgradeLevelsKeeper.init(u"RerollShopGroupUpgradeLevelsKeeper", self, "RerollShopGroupUpgradeLevels")
        self.RerollShopWeightsToTimesKeeper.init(u"RerollShopWeightsToTimesKeeper", self, "RerollShopWeightsToTimes")
        self.RollEventItemKeeper.init(u"RollEventItemKeeper", self, "RollEventItem")
        self.RollEventKeeper.init(u"RollEventKeeper", self, "RollEvent")
        self.RollEventRuleKeeper.init(u"RollEventRuleKeeper", self, "RollEventRule")
        self.SeasonEventKeeper.init(u"SeasonEventKeeper", self, "SeasonEvent")
        self.SeasonEventShopGroupKeeper.init(u"SeasonEventShopGroupKeeper", self, "SeasonEventShopGroup")
        self.SeasonEventShopItemKeeper.init(u"SeasonEventShopItemKeeper", self, "SeasonEventShopItem")
        self.SeasonProgressRewardKeeper.init(u"SeasonProgressRewardKeeper", self, "SeasonProgressRewardRelation")
        self.TradeEventGroupKeeper.init(u"TradeEventGroupKeeper", self, "TradeEventGroup")
        self.TradeEventKeeper.init(u"TradeEventKeeper", self, "TradeEvent")
        self.TradeExperienceRewardKeeper.init(u"TradeExperienceRewardKeeper", self, "ExperienceRewardRelation")
        self.TradeGroupMemberKeeper.init(u"TradeGroupMemberKeeper", self, "TradeGroupMember")
        self.TradeWorldRatingRewardKeeper.init(u"TradeWorldRatingRewardKeeper", self, "WorldRatingRewardRelation")
        self.ADDITIONAL_CONFIGS.init(u"ADDITIONAL_CONFIGS", self)
        self.ADMIN_NICKS.init(u"ADMIN_NICKS", self)
        self.ALTERNATIVE_QUESTS.init(u"ALTERNATIVE_QUESTS", self)
        self.BeginnersPackEventInfo.setPath(u"BeginnersPackEventInfo")
        self.BruteForceDefenderSettings.setPath(u"BruteForceDefenderSettings")
        self.BuyAeriaGoldEventInfo.setPath(u"BuyAeriaGoldEventInfo")
        self.BuyArcGamesGoldEventInfo.setPath(u"BuyArcGamesGoldEventInfo")
        self.BuyGamigoGoldEventInfo.setPath(u"BuyGamigoGoldEventInfo")
        self.BuyGoldHeroInfo.setPath(u"BuyGoldHeroInfo")
        self.BuySpecialHeroEventInfo.setPath(u"BuySpecialHeroEventInfo")
        self.BuySteamGoldEventInfo.setPath(u"BuySteamGoldEventInfo")
        self.BuyZZimaGoldEventInfo.setPath(u"BuyZZimaGoldEventInfo")
        self.ComplaintsSettings.setPath(u"ComplaintsSettings")
        self.CustomFlags.init(self.CustomFlagKeeper, u"CustomFlags", self)
        self.DEFAULT_SKINS.init(u"DEFAULT_SKINS", self)
        self.DISABLED_DEFAULT_TALENSETS.init(u"DISABLED_DEFAULT_TALENSETS", self)
        self.DonateEvents.init(self.DonateEventKeeper, u"DonateEvents", self)
        self.EventToolsChangeFields.setPath(u"EventToolsChangeFields")
        self.FORBIDDEN_FOR_PARTY_HERO_PAIRS.init(u"FORBIDDEN_FOR_PARTY_HERO_PAIRS", self)
        self.GUILD_SHOP_ITEMS.init(u"GUILD_SHOP_ITEMS", self)
        self.GuildBankSettings.setPath(u"GuildBankSettings")
        self.HonorSettings.setPath(u"HonorSettings")
        self.INIT_TALENTS.init(u"INIT_TALENTS", self)
        self.INVALID_HEROES.init(u"INVALID_HEROES", self)
        self.INVALID_QUESTS.init(u"INVALID_QUESTS", self)
        self.INVALID_SKINS.init(u"INVALID_SKINS", self)
        self.LampEventSettings.setPath(u"LampEventSettings")
        self.MAPS_FOR_PLAYER_RATING.init(u"MAPS_FOR_PLAYER_RATING", self)
        self.MARKETING_EVENTS.init(u"MARKETING_EVENTS", self)
        self.MonetizationDisablers.setPath(u"MonetizationDisablers")
        self.MuteSettings.setPath(u"MuteSettings")
        self.NEWS.init(self.NewsKeeper, u"NEWS", self)
        self.NICKNAME_REGEXES.init(u"NICKNAME_REGEXES", self)
        self.PingInfo.setPath(u"PingInfo")
        self.ProductionDiscount.setPath(u"ProductionDiscount")
        self.QuestEvents.init(self.QuestEventKeeper, u"QuestEvents", self)
        self.RollEvents.init(self.RollEventKeeper, u"RollEvents", self)
        self.SEASON_SKINS.init(u"SEASON_SKINS", self)
        self.SeasonEvents.init(self.SeasonEventKeeper, u"SeasonEvents", self)
        self.SiegeSettings.setPath(u"SiegeSettings")
        self.SKIN_AVATAR_BLOCK.init(u"SKIN_AVATAR_BLOCK", self)
        self.SKIPPED_TUTORIAL_QUESTS.init(u"SKIPPED_TUTORIAL_QUESTS", self)
        self.STATIC_DATA_OVERRIDES.init(u"STATIC_DATA_OVERRIDES", self)
        self.TALENTIDS_FOR_NEW_SN.init(u"TALENTIDS_FOR_NEW_SN", self)
        self.TALENTS_NOT_FOR_ROLL.init(u"TALENTS_NOT_FOR_ROLL", self)
        self.TalentsCollectionSettings.setPath(u"TalentsCollectionSettings")
        self.TamburInfo.setPath(u"TamburInfo")
        self.TournamentSettings.setPath(u"TournamentSettings")
        self.TradeEvents.init(self.TradeEventKeeper, u"TradeEvents", self)


    @staticmethod
    def initJsonTypes(TCustomConfigData): # конечный класс CustomConfigData будет передавать снаружи, из datamanager
        if "ConfigData" not in JSONSerialization.SERIALIZABLE_CLASSES:
            JSONSerialization.updateOurTypes((TCustomConfigData,
            ActiveGroup.ActiveGroup,
            BeginnersPackEventInfo.BeginnersPackEventInfo,
            BeginnersPackItem.BeginnersPackItem,
            BruteForceDefenderSettings.BruteForceDefenderSettings,
            BuyAeriaGoldEventInfo.BuyAeriaGoldEventInfo,
            BuyAeriaItem.BuyAeriaItem,
            BuyArcGamesGoldEventInfo.BuyArcGamesGoldEventInfo,
            BuyArcGamesItem.BuyArcGamesItem,
            BuyGamigoGoldEventInfo.BuyGamigoGoldEventInfo,
            BuyGamigoItem.BuyGamigoItem,
            BuyGoldHeroInfo.BuyGoldHeroInfo,
            BuySpecialHeroEventInfo.BuySpecialHeroEventInfo,
            BuySteamGoldEventInfo.BuySteamGoldEventInfo,
            BuySteamItem.BuySteamItem,
            BuyZZimaGoldEventInfo.BuyZZimaGoldEventInfo,
            BuyZZimaItem.BuyZZimaItem,
            ComplaintsSettings.ComplaintsSettings,
            CustomFlag.CustomFlag,
            DonateEvent.DonateEvent,
            DonateEventRange.DonateEventRange,
            DonateEventReward.DonateEventReward,
            EventToolsChangeFields.EventToolsChangeFields,
            ExperienceRewardRelation.ExperienceRewardRelation,
            GuildBankSettings.GuildBankSettings,
            HonorSettings.HonorSettings,
            LampEventSettings.LampEventSettings,
            MonetizationDisablers.MonetizationDisablers,
            MuteSettings.MuteSettings,
            NewsInfo.NewsInfo,
            PingInfo.PingInfo,
            ProductionDiscount.ProductionDiscount,
            QuestEvent.QuestEvent,
            QuestEventStage.QuestEventStage,
            QuestEventStageStep.QuestEventStageStep,
            QuestEventStageStepVariant.QuestEventStageStepVariant,
            ReforgeTalentPrices.ReforgeTalentPrices,
            RerollShopBanner.RerollShopBanner,
            RerollShopGroupUpgradeLevels.RerollShopGroupUpgradeLevels,
            RerollShopWeightsToTimes.RerollShopWeightsToTimes,
            ResourceTable.ResourceTable,
            RollEvent.RollEvent,
            RollEventItem.RollEventItem,
            RollEventRule.RollEventRule,
            SeasonEvent.SeasonEvent,
            SeasonEventShopGroup.SeasonEventShopGroup,
            SeasonEventShopItem.SeasonEventShopItem,
            SeasonProgressRewardRelation.SeasonProgressRewardRelation,
            SiegeSettings.SiegeSettings,
            TalentsCollectionSettings.TalentsCollectionSettings,
            TamburInfo.TamburInfo,
            TournamentSettings.TournamentSettings,
            TradeEvent.TradeEvent,
            TradeEventGroup.TradeEventGroup,
            TradeGroupMember.TradeGroupMember,
            WorldRatingRewardRelation.WorldRatingRewardRelation,
            ))
            JSONSerialization.SERIALIZABLE_CLASSES.update(
            { "ConfigData" : TCustomConfigData
            , "Keeper" : Keeper
            , "Set" : Set
            , "SimpleList" : SimpleList
            , "SimpleDict" : SimpleDict
            , "Collection" : Collection
            , "Ref" : Ref
            , "ActiveGroup" : ActiveGroup.ActiveGroup
            , "BeginnersPackEventInfo" : BeginnersPackEventInfo.BeginnersPackEventInfo
            , "BeginnersPackItem" : BeginnersPackItem.BeginnersPackItem
            , "BruteForceDefenderSettings" : BruteForceDefenderSettings.BruteForceDefenderSettings
            , "BuyAeriaGoldEventInfo" : BuyAeriaGoldEventInfo.BuyAeriaGoldEventInfo
            , "BuyAeriaItem" : BuyAeriaItem.BuyAeriaItem
            , "BuyArcGamesGoldEventInfo" : BuyArcGamesGoldEventInfo.BuyArcGamesGoldEventInfo
            , "BuyArcGamesItem" : BuyArcGamesItem.BuyArcGamesItem
            , "BuyGamigoGoldEventInfo" : BuyGamigoGoldEventInfo.BuyGamigoGoldEventInfo
            , "BuyGamigoItem" : BuyGamigoItem.BuyGamigoItem
            , "BuyGoldHeroInfo" : BuyGoldHeroInfo.BuyGoldHeroInfo
            , "BuySpecialHeroEventInfo" : BuySpecialHeroEventInfo.BuySpecialHeroEventInfo
            , "BuySteamGoldEventInfo" : BuySteamGoldEventInfo.BuySteamGoldEventInfo
            , "BuySteamItem" : BuySteamItem.BuySteamItem
            , "BuyZZimaGoldEventInfo" : BuyZZimaGoldEventInfo.BuyZZimaGoldEventInfo
            , "BuyZZimaItem" : BuyZZimaItem.BuyZZimaItem
            , "ComplaintsSettings" : ComplaintsSettings.ComplaintsSettings
            , "CustomFlag" : CustomFlag.CustomFlag
            , "DonateEvent" : DonateEvent.DonateEvent
            , "DonateEventRange" : DonateEventRange.DonateEventRange
            , "DonateEventReward" : DonateEventReward.DonateEventReward
            , "EventToolsChangeFields" : EventToolsChangeFields.EventToolsChangeFields
            , "ExperienceRewardRelation" : ExperienceRewardRelation.ExperienceRewardRelation
            , "GuildBankSettings" : GuildBankSettings.GuildBankSettings
            , "HonorSettings" : HonorSettings.HonorSettings
            , "LampEventSettings" : LampEventSettings.LampEventSettings
            , "MonetizationDisablers" : MonetizationDisablers.MonetizationDisablers
            , "MuteSettings" : MuteSettings.MuteSettings
            , "NewsInfo" : NewsInfo.NewsInfo
            , "PingInfo" : PingInfo.PingInfo
            , "ProductionDiscount" : ProductionDiscount.ProductionDiscount
            , "QuestEvent" : QuestEvent.QuestEvent
            , "QuestEventStage" : QuestEventStage.QuestEventStage
            , "QuestEventStageStep" : QuestEventStageStep.QuestEventStageStep
            , "QuestEventStageStepVariant" : QuestEventStageStepVariant.QuestEventStageStepVariant
            , "ReforgeTalentPrices" : ReforgeTalentPrices.ReforgeTalentPrices
            , "RerollShopBanner" : RerollShopBanner.RerollShopBanner
            , "RerollShopGroupUpgradeLevels" : RerollShopGroupUpgradeLevels.RerollShopGroupUpgradeLevels
            , "RerollShopWeightsToTimes" : RerollShopWeightsToTimes.RerollShopWeightsToTimes
            , "ResourceTable" : ResourceTable.ResourceTable
            , "RollEvent" : RollEvent.RollEvent
            , "RollEventItem" : RollEventItem.RollEventItem
            , "RollEventRule" : RollEventRule.RollEventRule
            , "SeasonEvent" : SeasonEvent.SeasonEvent
            , "SeasonEventShopGroup" : SeasonEventShopGroup.SeasonEventShopGroup
            , "SeasonEventShopItem" : SeasonEventShopItem.SeasonEventShopItem
            , "SeasonProgressRewardRelation" : SeasonProgressRewardRelation.SeasonProgressRewardRelation
            , "SiegeSettings" : SiegeSettings.SiegeSettings
            , "TalentsCollectionSettings" : TalentsCollectionSettings.TalentsCollectionSettings
            , "TamburInfo" : TamburInfo.TamburInfo
            , "TournamentSettings" : TournamentSettings.TournamentSettings
            , "TradeEvent" : TradeEvent.TradeEvent
            , "TradeEventGroup" : TradeEventGroup.TradeEventGroup
            , "TradeGroupMember" : TradeGroupMember.TradeGroupMember
            , "WorldRatingRewardRelation" : WorldRatingRewardRelation.WorldRatingRewardRelation
            })  
        else:
            err("ConfigData.initJsonTypes called twice! The second call is:\n%s", errStack())

    def addNewActiveGroup(self):
        uid = self.nextGUID()
        var = ActiveGroup.ActiveGroup(self, uid, "ActiveGroups/"+str(uid))
        var.init_add()
        self.ActiveGroups.add(uid, var)
        return uid


    def getActiveGroupByID(self, id):
        return self.ActiveGroups.get(id)


    def newActiveGroup(self):
        _id = self.addNewActiveGroup()
        _data = self.getActiveGroupByID(_id)
        return _data, _id
    def addNewBeginnersPackItem(self):
        uid = self.nextGUID()
        var = BeginnersPackItem.BeginnersPackItem(self, uid, "BeginnersPackItemKeeper/"+str(uid))
        var.init_add()
        self.BeginnersPackItemKeeper.add(uid, var)
        return uid


    def getBeginnersPackItemByID(self, id):
        return self.BeginnersPackItemKeeper.get(id)


    def newBeginnersPackItem(self):
        _id = self.addNewBeginnersPackItem()
        _data = self.getBeginnersPackItemByID(_id)
        return _data, _id
    def addNewBuyAeriaItem(self):
        uid = self.nextGUID()
        var = BuyAeriaItem.BuyAeriaItem(self, uid, "BuyAeriaItemKeeper/"+str(uid))
        var.init_add()
        self.BuyAeriaItemKeeper.add(uid, var)
        return uid


    def getBuyAeriaItemByID(self, id):
        return self.BuyAeriaItemKeeper.get(id)


    def newBuyAeriaItem(self):
        _id = self.addNewBuyAeriaItem()
        _data = self.getBuyAeriaItemByID(_id)
        return _data, _id
    def addNewBuyArcGamesItem(self):
        uid = self.nextGUID()
        var = BuyArcGamesItem.BuyArcGamesItem(self, uid, "BuyArcGamesItemKeeper/"+str(uid))
        var.init_add()
        self.BuyArcGamesItemKeeper.add(uid, var)
        return uid


    def getBuyArcGamesItemByID(self, id):
        return self.BuyArcGamesItemKeeper.get(id)


    def newBuyArcGamesItem(self):
        _id = self.addNewBuyArcGamesItem()
        _data = self.getBuyArcGamesItemByID(_id)
        return _data, _id
    def addNewBuyGamigoItem(self):
        uid = self.nextGUID()
        var = BuyGamigoItem.BuyGamigoItem(self, uid, "BuyGamigoItemKeeper/"+str(uid))
        var.init_add()
        self.BuyGamigoItemKeeper.add(uid, var)
        return uid


    def getBuyGamigoItemByID(self, id):
        return self.BuyGamigoItemKeeper.get(id)


    def newBuyGamigoItem(self):
        _id = self.addNewBuyGamigoItem()
        _data = self.getBuyGamigoItemByID(_id)
        return _data, _id
    def addNewBuySteamItem(self):
        uid = self.nextGUID()
        var = BuySteamItem.BuySteamItem(self, uid, "BuySteamItemKeeper/"+str(uid))
        var.init_add()
        self.BuySteamItemKeeper.add(uid, var)
        return uid


    def getBuySteamItemByID(self, id):
        return self.BuySteamItemKeeper.get(id)


    def newBuySteamItem(self):
        _id = self.addNewBuySteamItem()
        _data = self.getBuySteamItemByID(_id)
        return _data, _id
    def addNewBuyZZimaItem(self):
        uid = self.nextGUID()
        var = BuyZZimaItem.BuyZZimaItem(self, uid, "BuyZZimaItemKeeper/"+str(uid))
        var.init_add()
        self.BuyZZimaItemKeeper.add(uid, var)
        return uid


    def getBuyZZimaItemByID(self, id):
        return self.BuyZZimaItemKeeper.get(id)


    def newBuyZZimaItem(self):
        _id = self.addNewBuyZZimaItem()
        _data = self.getBuyZZimaItemByID(_id)
        return _data, _id
    def addNewCustomFlag(self):
        uid = self.nextGUID()
        var = CustomFlag.CustomFlag(self, uid, "CustomFlagKeeper/"+str(uid))
        var.init_add()
        self.CustomFlagKeeper.add(uid, var)
        return uid


    def getCustomFlagByID(self, id):
        return self.CustomFlagKeeper.get(id)


    def newCustomFlag(self):
        _id = self.addNewCustomFlag()
        _data = self.getCustomFlagByID(_id)
        return _data, _id
    def addNewDonateEvent(self):
        uid = self.nextGUID()
        var = DonateEvent.DonateEvent(self, uid, "DonateEventKeeper/"+str(uid))
        var.init_add()
        self.DonateEventKeeper.add(uid, var)
        return uid


    def getDonateEventByID(self, id):
        return self.DonateEventKeeper.get(id)


    def newDonateEvent(self):
        _id = self.addNewDonateEvent()
        _data = self.getDonateEventByID(_id)
        return _data, _id
    def addNewDonateEventRange(self):
        uid = self.nextGUID()
        var = DonateEventRange.DonateEventRange(self, uid, "DonateEventRangeKeeper/"+str(uid))
        var.init_add()
        self.DonateEventRangeKeeper.add(uid, var)
        return uid


    def getDonateEventRangeByID(self, id):
        return self.DonateEventRangeKeeper.get(id)


    def newDonateEventRange(self):
        _id = self.addNewDonateEventRange()
        _data = self.getDonateEventRangeByID(_id)
        return _data, _id
    def addNewDonateEventReward(self):
        uid = self.nextGUID()
        var = DonateEventReward.DonateEventReward(self, uid, "DonateEventRewardKeeper/"+str(uid))
        var.init_add()
        self.DonateEventRewardKeeper.add(uid, var)
        return uid


    def getDonateEventRewardByID(self, id):
        return self.DonateEventRewardKeeper.get(id)


    def newDonateEventReward(self):
        _id = self.addNewDonateEventReward()
        _data = self.getDonateEventRewardByID(_id)
        return _data, _id
    def addNewNewsInfo(self):
        uid = self.nextGUID()
        var = NewsInfo.NewsInfo(self, uid, "NewsKeeper/"+str(uid))
        var.init_add()
        self.NewsKeeper.add(uid, var)
        return uid


    def getNewsInfoByID(self, id):
        return self.NewsKeeper.get(id)


    def newNewsInfo(self):
        _id = self.addNewNewsInfo()
        _data = self.getNewsInfoByID(_id)
        return _data, _id
    def addNewQuestEvent(self):
        uid = self.nextGUID()
        var = QuestEvent.QuestEvent(self, uid, "QuestEventKeeper/"+str(uid))
        var.init_add()
        self.QuestEventKeeper.add(uid, var)
        return uid


    def getQuestEventByID(self, id):
        return self.QuestEventKeeper.get(id)


    def newQuestEvent(self):
        _id = self.addNewQuestEvent()
        _data = self.getQuestEventByID(_id)
        return _data, _id
    def addNewQuestEventStage(self):
        uid = self.nextGUID()
        var = QuestEventStage.QuestEventStage(self, uid, "QuestEventStageKeeper/"+str(uid))
        var.init_add()
        self.QuestEventStageKeeper.add(uid, var)
        return uid


    def getQuestEventStageByID(self, id):
        return self.QuestEventStageKeeper.get(id)


    def newQuestEventStage(self):
        _id = self.addNewQuestEventStage()
        _data = self.getQuestEventStageByID(_id)
        return _data, _id
    def addNewQuestEventStageStep(self):
        uid = self.nextGUID()
        var = QuestEventStageStep.QuestEventStageStep(self, uid, "QuestEventStageStepKeeper/"+str(uid))
        var.init_add()
        self.QuestEventStageStepKeeper.add(uid, var)
        return uid


    def getQuestEventStageStepByID(self, id):
        return self.QuestEventStageStepKeeper.get(id)


    def newQuestEventStageStep(self):
        _id = self.addNewQuestEventStageStep()
        _data = self.getQuestEventStageStepByID(_id)
        return _data, _id
    def addNewQuestEventStageStepVariant(self):
        uid = self.nextGUID()
        var = QuestEventStageStepVariant.QuestEventStageStepVariant(self, uid, "QuestEventStageStepVariantKeeper/"+str(uid))
        var.init_add()
        self.QuestEventStageStepVariantKeeper.add(uid, var)
        return uid


    def getQuestEventStageStepVariantByID(self, id):
        return self.QuestEventStageStepVariantKeeper.get(id)


    def newQuestEventStageStepVariant(self):
        _id = self.addNewQuestEventStageStepVariant()
        _data = self.getQuestEventStageStepVariantByID(_id)
        return _data, _id
    def addNewReforgeTalentPrices(self):
        uid = self.nextGUID()
        var = ReforgeTalentPrices.ReforgeTalentPrices(self, uid, "ReforgeTalentPricesKeeper/"+str(uid))
        var.init_add()
        self.ReforgeTalentPricesKeeper.add(uid, var)
        return uid


    def getReforgeTalentPricesByID(self, id):
        return self.ReforgeTalentPricesKeeper.get(id)


    def newReforgeTalentPrices(self):
        _id = self.addNewReforgeTalentPrices()
        _data = self.getReforgeTalentPricesByID(_id)
        return _data, _id
    def addNewRerollShopGroupUpgradeLevels(self):
        uid = self.nextGUID()
        var = RerollShopGroupUpgradeLevels.RerollShopGroupUpgradeLevels(self, uid, "RerollShopGroupUpgradeLevelsKeeper/"+str(uid))
        var.init_add()
        self.RerollShopGroupUpgradeLevelsKeeper.add(uid, var)
        return uid


    def getRerollShopGroupUpgradeLevelsByID(self, id):
        return self.RerollShopGroupUpgradeLevelsKeeper.get(id)


    def newRerollShopGroupUpgradeLevels(self):
        _id = self.addNewRerollShopGroupUpgradeLevels()
        _data = self.getRerollShopGroupUpgradeLevelsByID(_id)
        return _data, _id
    def addNewRerollShopWeightsToTimes(self):
        uid = self.nextGUID()
        var = RerollShopWeightsToTimes.RerollShopWeightsToTimes(self, uid, "RerollShopWeightsToTimesKeeper/"+str(uid))
        var.init_add()
        self.RerollShopWeightsToTimesKeeper.add(uid, var)
        return uid


    def getRerollShopWeightsToTimesByID(self, id):
        return self.RerollShopWeightsToTimesKeeper.get(id)


    def newRerollShopWeightsToTimes(self):
        _id = self.addNewRerollShopWeightsToTimes()
        _data = self.getRerollShopWeightsToTimesByID(_id)
        return _data, _id
    def addNewRollEventItem(self):
        uid = self.nextGUID()
        var = RollEventItem.RollEventItem(self, uid, "RollEventItemKeeper/"+str(uid))
        var.init_add()
        self.RollEventItemKeeper.add(uid, var)
        return uid


    def getRollEventItemByID(self, id):
        return self.RollEventItemKeeper.get(id)


    def newRollEventItem(self):
        _id = self.addNewRollEventItem()
        _data = self.getRollEventItemByID(_id)
        return _data, _id
    def addNewRollEvent(self):
        uid = self.nextGUID()
        var = RollEvent.RollEvent(self, uid, "RollEventKeeper/"+str(uid))
        var.init_add()
        self.RollEventKeeper.add(uid, var)
        return uid


    def getRollEventByID(self, id):
        return self.RollEventKeeper.get(id)


    def newRollEvent(self):
        _id = self.addNewRollEvent()
        _data = self.getRollEventByID(_id)
        return _data, _id
    def addNewRollEventRule(self):
        uid = self.nextGUID()
        var = RollEventRule.RollEventRule(self, uid, "RollEventRuleKeeper/"+str(uid))
        var.init_add()
        self.RollEventRuleKeeper.add(uid, var)
        return uid


    def getRollEventRuleByID(self, id):
        return self.RollEventRuleKeeper.get(id)


    def newRollEventRule(self):
        _id = self.addNewRollEventRule()
        _data = self.getRollEventRuleByID(_id)
        return _data, _id
    def addNewSeasonEvent(self):
        uid = self.nextGUID()
        var = SeasonEvent.SeasonEvent(self, uid, "SeasonEventKeeper/"+str(uid))
        var.init_add()
        self.SeasonEventKeeper.add(uid, var)
        return uid


    def getSeasonEventByID(self, id):
        return self.SeasonEventKeeper.get(id)


    def newSeasonEvent(self):
        _id = self.addNewSeasonEvent()
        _data = self.getSeasonEventByID(_id)
        return _data, _id
    def addNewSeasonEventShopGroup(self):
        uid = self.nextGUID()
        var = SeasonEventShopGroup.SeasonEventShopGroup(self, uid, "SeasonEventShopGroupKeeper/"+str(uid))
        var.init_add()
        self.SeasonEventShopGroupKeeper.add(uid, var)
        return uid


    def getSeasonEventShopGroupByID(self, id):
        return self.SeasonEventShopGroupKeeper.get(id)


    def newSeasonEventShopGroup(self):
        _id = self.addNewSeasonEventShopGroup()
        _data = self.getSeasonEventShopGroupByID(_id)
        return _data, _id
    def addNewSeasonEventShopItem(self):
        uid = self.nextGUID()
        var = SeasonEventShopItem.SeasonEventShopItem(self, uid, "SeasonEventShopItemKeeper/"+str(uid))
        var.init_add()
        self.SeasonEventShopItemKeeper.add(uid, var)
        return uid


    def getSeasonEventShopItemByID(self, id):
        return self.SeasonEventShopItemKeeper.get(id)


    def newSeasonEventShopItem(self):
        _id = self.addNewSeasonEventShopItem()
        _data = self.getSeasonEventShopItemByID(_id)
        return _data, _id
    def addNewSeasonProgressRewardRelation(self):
        uid = self.nextGUID()
        var = SeasonProgressRewardRelation.SeasonProgressRewardRelation(self, uid, "SeasonProgressRewardKeeper/"+str(uid))
        var.init_add()
        self.SeasonProgressRewardKeeper.add(uid, var)
        return uid


    def getSeasonProgressRewardRelationByID(self, id):
        return self.SeasonProgressRewardKeeper.get(id)


    def newSeasonProgressRewardRelation(self):
        _id = self.addNewSeasonProgressRewardRelation()
        _data = self.getSeasonProgressRewardRelationByID(_id)
        return _data, _id
    def addNewTradeEventGroup(self):
        uid = self.nextGUID()
        var = TradeEventGroup.TradeEventGroup(self, uid, "TradeEventGroupKeeper/"+str(uid))
        var.init_add()
        self.TradeEventGroupKeeper.add(uid, var)
        return uid


    def getTradeEventGroupByID(self, id):
        return self.TradeEventGroupKeeper.get(id)


    def newTradeEventGroup(self):
        _id = self.addNewTradeEventGroup()
        _data = self.getTradeEventGroupByID(_id)
        return _data, _id
    def addNewTradeEvent(self):
        uid = self.nextGUID()
        var = TradeEvent.TradeEvent(self, uid, "TradeEventKeeper/"+str(uid))
        var.init_add()
        self.TradeEventKeeper.add(uid, var)
        return uid


    def getTradeEventByID(self, id):
        return self.TradeEventKeeper.get(id)


    def newTradeEvent(self):
        _id = self.addNewTradeEvent()
        _data = self.getTradeEventByID(_id)
        return _data, _id
    def addNewExperienceRewardRelation(self):
        uid = self.nextGUID()
        var = ExperienceRewardRelation.ExperienceRewardRelation(self, uid, "TradeExperienceRewardKeeper/"+str(uid))
        var.init_add()
        self.TradeExperienceRewardKeeper.add(uid, var)
        return uid


    def getExperienceRewardRelationByID(self, id):
        return self.TradeExperienceRewardKeeper.get(id)


    def newExperienceRewardRelation(self):
        _id = self.addNewExperienceRewardRelation()
        _data = self.getExperienceRewardRelationByID(_id)
        return _data, _id
    def addNewTradeGroupMember(self):
        uid = self.nextGUID()
        var = TradeGroupMember.TradeGroupMember(self, uid, "TradeGroupMemberKeeper/"+str(uid))
        var.init_add()
        self.TradeGroupMemberKeeper.add(uid, var)
        return uid


    def getTradeGroupMemberByID(self, id):
        return self.TradeGroupMemberKeeper.get(id)


    def newTradeGroupMember(self):
        _id = self.addNewTradeGroupMember()
        _data = self.getTradeGroupMemberByID(_id)
        return _data, _id
    def addNewWorldRatingRewardRelation(self):
        uid = self.nextGUID()
        var = WorldRatingRewardRelation.WorldRatingRewardRelation(self, uid, "TradeWorldRatingRewardKeeper/"+str(uid))
        var.init_add()
        self.TradeWorldRatingRewardKeeper.add(uid, var)
        return uid


    def getWorldRatingRewardRelationByID(self, id):
        return self.TradeWorldRatingRewardKeeper.get(id)


    def newWorldRatingRewardRelation(self):
        _id = self.addNewWorldRatingRewardRelation()
        _data = self.getWorldRatingRewardRelationByID(_id)
        return _data, _id
    

    def deleteByID(self, id):
        self.ADDITIONAL_CONFIGS.deleteByID(id)
        self.ADMIN_NICKS.deleteByID(id)
        self.ALTERNATIVE_QUESTS.deleteByID(id)
        self.BeginnersPackEventInfo.deleteByID(id)
        self.BruteForceDefenderSettings.deleteByID(id)
        self.BuyAeriaGoldEventInfo.deleteByID(id)
        self.BuyArcGamesGoldEventInfo.deleteByID(id)
        self.BuyGamigoGoldEventInfo.deleteByID(id)
        self.BuyGoldHeroInfo.deleteByID(id)
        self.BuySpecialHeroEventInfo.deleteByID(id)
        self.BuySteamGoldEventInfo.deleteByID(id)
        self.BuyZZimaGoldEventInfo.deleteByID(id)
        self.ComplaintsSettings.deleteByID(id)
        self.CustomFlags.deleteByID(id)
        self.DEFAULT_SKINS.deleteByID(id)
        self.DISABLED_DEFAULT_TALENSETS.deleteByID(id)
        self.DonateEvents.deleteByID(id)
        self.EventToolsChangeFields.deleteByID(id)
        self.FORBIDDEN_FOR_PARTY_HERO_PAIRS.deleteByID(id)
        self.GUILD_SHOP_ITEMS.deleteByID(id)
        self.GuildBankSettings.deleteByID(id)
        self.HonorSettings.deleteByID(id)
        self.INIT_TALENTS.deleteByID(id)
        self.INVALID_HEROES.deleteByID(id)
        self.INVALID_QUESTS.deleteByID(id)
        self.INVALID_SKINS.deleteByID(id)
        self.LampEventSettings.deleteByID(id)
        self.MAPS_FOR_PLAYER_RATING.deleteByID(id)
        self.MARKETING_EVENTS.deleteByID(id)
        self.MonetizationDisablers.deleteByID(id)
        self.MuteSettings.deleteByID(id)
        self.NEWS.deleteByID(id)
        self.NICKNAME_REGEXES.deleteByID(id)
        self.PingInfo.deleteByID(id)
        self.ProductionDiscount.deleteByID(id)
        self.QuestEvents.deleteByID(id)
        self.RollEvents.deleteByID(id)
        self.SEASON_SKINS.deleteByID(id)
        self.SeasonEvents.deleteByID(id)
        self.SiegeSettings.deleteByID(id)
        self.SKIN_AVATAR_BLOCK.deleteByID(id)
        self.SKIPPED_TUTORIAL_QUESTS.deleteByID(id)
        self.STATIC_DATA_OVERRIDES.deleteByID(id)
        self.TALENTIDS_FOR_NEW_SN.deleteByID(id)
        self.TALENTS_NOT_FOR_ROLL.deleteByID(id)
        self.TalentsCollectionSettings.deleteByID(id)
        self.TamburInfo.deleteByID(id)
        self.TournamentSettings.deleteByID(id)
        self.TradeEvents.deleteByID(id)

        #≈сли с RefCounter'ами все в пор€дке то объект к этому моменту уже должен быть удален из Keeper'ф
        obj = self.getObjectByID(id)
        if obj:
            #ј если не удален, значит RefCounter'ы глючат, и мы их обнул€ем что бы все нормально удал€лось
            obj.refCounter = 0

        self.ActiveGroups.deleteByID(id)
        self.BeginnersPackItemKeeper.deleteByID(id)
        self.BuyAeriaItemKeeper.deleteByID(id)
        self.BuyArcGamesItemKeeper.deleteByID(id)
        self.BuyGamigoItemKeeper.deleteByID(id)
        self.BuySteamItemKeeper.deleteByID(id)
        self.BuyZZimaItemKeeper.deleteByID(id)
        self.CustomFlagKeeper.deleteByID(id)
        self.DonateEventKeeper.deleteByID(id)
        self.DonateEventRangeKeeper.deleteByID(id)
        self.DonateEventRewardKeeper.deleteByID(id)
        self.NewsKeeper.deleteByID(id)
        self.QuestEventKeeper.deleteByID(id)
        self.QuestEventStageKeeper.deleteByID(id)
        self.QuestEventStageStepKeeper.deleteByID(id)
        self.QuestEventStageStepVariantKeeper.deleteByID(id)
        self.ReforgeTalentPricesKeeper.deleteByID(id)
        self.RerollShopGroupUpgradeLevelsKeeper.deleteByID(id)
        self.RerollShopWeightsToTimesKeeper.deleteByID(id)
        self.RollEventItemKeeper.deleteByID(id)
        self.RollEventKeeper.deleteByID(id)
        self.RollEventRuleKeeper.deleteByID(id)
        self.SeasonEventKeeper.deleteByID(id)
        self.SeasonEventShopGroupKeeper.deleteByID(id)
        self.SeasonEventShopItemKeeper.deleteByID(id)
        self.SeasonProgressRewardKeeper.deleteByID(id)
        self.TradeEventGroupKeeper.deleteByID(id)
        self.TradeEventKeeper.deleteByID(id)
        self.TradeExperienceRewardKeeper.deleteByID(id)
        self.TradeGroupMemberKeeper.deleteByID(id)
        self.TradeWorldRatingRewardKeeper.deleteByID(id)


    def getObjectByID(self, id):
        obj = None
        ActiveGroup = self.getActiveGroupByID(id)
        if ActiveGroup:
            obj = ActiveGroup
        BeginnersPackItem = self.getBeginnersPackItemByID(id)
        if BeginnersPackItem:
            obj = BeginnersPackItem
        BuyAeriaItem = self.getBuyAeriaItemByID(id)
        if BuyAeriaItem:
            obj = BuyAeriaItem
        BuyArcGamesItem = self.getBuyArcGamesItemByID(id)
        if BuyArcGamesItem:
            obj = BuyArcGamesItem
        BuyGamigoItem = self.getBuyGamigoItemByID(id)
        if BuyGamigoItem:
            obj = BuyGamigoItem
        BuySteamItem = self.getBuySteamItemByID(id)
        if BuySteamItem:
            obj = BuySteamItem
        BuyZZimaItem = self.getBuyZZimaItemByID(id)
        if BuyZZimaItem:
            obj = BuyZZimaItem
        CustomFlag = self.getCustomFlagByID(id)
        if CustomFlag:
            obj = CustomFlag
        DonateEvent = self.getDonateEventByID(id)
        if DonateEvent:
            obj = DonateEvent
        DonateEventRange = self.getDonateEventRangeByID(id)
        if DonateEventRange:
            obj = DonateEventRange
        DonateEventReward = self.getDonateEventRewardByID(id)
        if DonateEventReward:
            obj = DonateEventReward
        NewsInfo = self.getNewsInfoByID(id)
        if NewsInfo:
            obj = NewsInfo
        QuestEvent = self.getQuestEventByID(id)
        if QuestEvent:
            obj = QuestEvent
        QuestEventStage = self.getQuestEventStageByID(id)
        if QuestEventStage:
            obj = QuestEventStage
        QuestEventStageStep = self.getQuestEventStageStepByID(id)
        if QuestEventStageStep:
            obj = QuestEventStageStep
        QuestEventStageStepVariant = self.getQuestEventStageStepVariantByID(id)
        if QuestEventStageStepVariant:
            obj = QuestEventStageStepVariant
        ReforgeTalentPrices = self.getReforgeTalentPricesByID(id)
        if ReforgeTalentPrices:
            obj = ReforgeTalentPrices
        RerollShopGroupUpgradeLevels = self.getRerollShopGroupUpgradeLevelsByID(id)
        if RerollShopGroupUpgradeLevels:
            obj = RerollShopGroupUpgradeLevels
        RerollShopWeightsToTimes = self.getRerollShopWeightsToTimesByID(id)
        if RerollShopWeightsToTimes:
            obj = RerollShopWeightsToTimes
        RollEventItem = self.getRollEventItemByID(id)
        if RollEventItem:
            obj = RollEventItem
        RollEvent = self.getRollEventByID(id)
        if RollEvent:
            obj = RollEvent
        RollEventRule = self.getRollEventRuleByID(id)
        if RollEventRule:
            obj = RollEventRule
        SeasonEvent = self.getSeasonEventByID(id)
        if SeasonEvent:
            obj = SeasonEvent
        SeasonEventShopGroup = self.getSeasonEventShopGroupByID(id)
        if SeasonEventShopGroup:
            obj = SeasonEventShopGroup
        SeasonEventShopItem = self.getSeasonEventShopItemByID(id)
        if SeasonEventShopItem:
            obj = SeasonEventShopItem
        SeasonProgressRewardRelation = self.getSeasonProgressRewardRelationByID(id)
        if SeasonProgressRewardRelation:
            obj = SeasonProgressRewardRelation
        TradeEventGroup = self.getTradeEventGroupByID(id)
        if TradeEventGroup:
            obj = TradeEventGroup
        TradeEvent = self.getTradeEventByID(id)
        if TradeEvent:
            obj = TradeEvent
        ExperienceRewardRelation = self.getExperienceRewardRelationByID(id)
        if ExperienceRewardRelation:
            obj = ExperienceRewardRelation
        TradeGroupMember = self.getTradeGroupMemberByID(id)
        if TradeGroupMember:
            obj = TradeGroupMember
        WorldRatingRewardRelation = self.getWorldRatingRewardRelationByID(id)
        if WorldRatingRewardRelation:
            obj = WorldRatingRewardRelation
        return obj


    def __setattr__(self, name, val):
        ChangeHandler.__setattr__(self, name, val)
    

    
    def generateJsonDict(self):
        _dct = ConfigDataCustom.generateBaseDict(self)
        _dct.update(
            path=self.path,
            ActiveGroups=self.__dict__["ActiveGroups"].generateJsonDict(),
            ADD_FIRST_QUEST=self.__dict__["ADD_FIRST_QUEST"],
            ADD_LEAVE_POINT=self.__dict__["ADD_LEAVE_POINT"],
            ADDITIONAL_CONFIGS=self.__dict__["ADDITIONAL_CONFIGS"].getJsonDict(),
            ADMIN_MESSAGES_TO_STORE=self.__dict__["ADMIN_MESSAGES_TO_STORE"],
            ADMIN_NICKS=self.__dict__["ADMIN_NICKS"].getJsonDict(),
            AERIA_PAY_SERVER=self.__dict__["AERIA_PAY_SERVER"],
            AFTERPARTY_TIMEOUT=self.__dict__["AFTERPARTY_TIMEOUT"],
            ALLOW_REROLL_FROM_SET_FOR_UPGRADED_TALENTS_ON_REFORGE=self.__dict__["ALLOW_REROLL_FROM_SET_FOR_UPGRADED_TALENTS_ON_REFORGE"],
            ALTERNATIVE_QUESTS=self.__dict__["ALTERNATIVE_QUESTS"].getJsonDict(),
            APPEARING_GOLDPRODUCTIONHOUSE_PRICE=self.__dict__["APPEARING_GOLDPRODUCTIONHOUSE_PRICE"],
            ARCGAMES_APPID=self.__dict__["ARCGAMES_APPID"],
            ARCGAMES_PAY_SERVER=self.__dict__["ARCGAMES_PAY_SERVER"],
            ARCGAMES_USE_OVERLAY=self.__dict__["ARCGAMES_USE_OVERLAY"],
            AUTOMUTE_DURATION=self.__dict__["AUTOMUTE_DURATION"],
            BeginnersPackEventInfo = self.__dict__["BeginnersPackEventInfo"].generateJsonDict(),
            BeginnersPackItemKeeper=self.__dict__["BeginnersPackItemKeeper"].generateJsonDict(),
            BEHAVIOUR_DETECTED_ENABLE=self.__dict__["BEHAVIOUR_DETECTED_ENABLE"],
            BruteForceDefenderSettings = self.__dict__["BruteForceDefenderSettings"].generateJsonDict(),
            BUY_HERO_MAX_ORIGINAL_PRICE=self.__dict__["BUY_HERO_MAX_ORIGINAL_PRICE"],
            BUY_HERO_PRICE=self.__dict__["BUY_HERO_PRICE"],
            BuyAeriaGoldEventInfo = self.__dict__["BuyAeriaGoldEventInfo"].generateJsonDict(),
            BuyAeriaItemKeeper=self.__dict__["BuyAeriaItemKeeper"].generateJsonDict(),
            BuyArcGamesGoldEventInfo = self.__dict__["BuyArcGamesGoldEventInfo"].generateJsonDict(),
            BuyArcGamesItemKeeper=self.__dict__["BuyArcGamesItemKeeper"].generateJsonDict(),
            BuyGamigoGoldEventInfo = self.__dict__["BuyGamigoGoldEventInfo"].generateJsonDict(),
            BuyGamigoItemKeeper=self.__dict__["BuyGamigoItemKeeper"].generateJsonDict(),
            BuyGoldHeroInfo = self.__dict__["BuyGoldHeroInfo"].generateJsonDict(),
            BuySpecialHeroEventInfo = self.__dict__["BuySpecialHeroEventInfo"].generateJsonDict(),
            BuySteamGoldEventInfo = self.__dict__["BuySteamGoldEventInfo"].generateJsonDict(),
            BuySteamItemKeeper=self.__dict__["BuySteamItemKeeper"].generateJsonDict(),
            BuyZZimaGoldEventInfo = self.__dict__["BuyZZimaGoldEventInfo"].generateJsonDict(),
            BuyZZimaItemKeeper=self.__dict__["BuyZZimaItemKeeper"].generateJsonDict(),
            CAMERA_FLYBY_TIMEOUT_DURATION=self.__dict__["CAMERA_FLYBY_TIMEOUT_DURATION"],
            CHANGE_FRACTION_TO_ADORNIA=self.__dict__["CHANGE_FRACTION_TO_ADORNIA"],
            CHANGE_FRACTION_TO_DOCT=self.__dict__["CHANGE_FRACTION_TO_DOCT"],
            CHECK_REQUESTS_REPEATABILITY=self.__dict__["CHECK_REQUESTS_REPEATABILITY"],
            ComplaintsSettings = self.__dict__["ComplaintsSettings"].generateJsonDict(),
            COST_FRACTION_CHANGE=self.__dict__["COST_FRACTION_CHANGE"],
            COST_NICK_CHANGE=self.__dict__["COST_NICK_CHANGE"],
            CustomFlagKeeper=self.__dict__["CustomFlagKeeper"].generateJsonDict(),
            CustomFlags=self.__dict__["CustomFlags"].getJsonDict(),
            DEBUG_ENABLED=self.__dict__["DEBUG_ENABLED"],
            DEFAULT_FRACTION=self.__dict__["DEFAULT_FRACTION"],
            DEFAULT_SKINS=self.__dict__["DEFAULT_SKINS"].getJsonDict(),
            DEFEATS_COUNT_FOR_KICK_FROM_TOURNAMENT=self.__dict__["DEFEATS_COUNT_FOR_KICK_FROM_TOURNAMENT"],
            DELAYED_SESSION_START_TIME=self.__dict__["DELAYED_SESSION_START_TIME"],
            DISABLED_DEFAULT_TALENSETS=self.__dict__["DISABLED_DEFAULT_TALENSETS"].getJsonDict(),
            DonateEventKeeper=self.__dict__["DonateEventKeeper"].generateJsonDict(),
            DonateEventRangeKeeper=self.__dict__["DonateEventRangeKeeper"].generateJsonDict(),
            DonateEventRewardKeeper=self.__dict__["DonateEventRewardKeeper"].generateJsonDict(),
            DonateEvents=self.__dict__["DonateEvents"].getJsonDict(),
            DONT_VALIDATE_STEAM_DLC=self.__dict__["DONT_VALIDATE_STEAM_DLC"],
            DRAUGASLT_PAY_SERVER=self.__dict__["DRAUGASLT_PAY_SERVER"],
            DRAUGASLT_PAY_URL_PARAMS=self.__dict__["DRAUGASLT_PAY_URL_PARAMS"],
            DRAUGASLT_PAY_URL_SALT=self.__dict__["DRAUGASLT_PAY_URL_SALT"],
            ENABLE_AUTOACCEPT=self.__dict__["ENABLE_AUTOACCEPT"],
            ENABLE_TAVERT_REROLL_ON_LEVELUP=self.__dict__["ENABLE_TAVERT_REROLL_ON_LEVELUP"],
            EPIC_HERO_FORCE=self.__dict__["EPIC_HERO_FORCE"],
            EPIC_HERO_RETIRE_LIFETIME=self.__dict__["EPIC_HERO_RETIRE_LIFETIME"],
            EPIC_HERO_RETIRED_CAP=self.__dict__["EPIC_HERO_RETIRED_CAP"],
            EPIC_HERO_RETIRED_TIME_BASE=self.__dict__["EPIC_HERO_RETIRED_TIME_BASE"],
            EPIC_HERO_RETIRED_TIME_INC=self.__dict__["EPIC_HERO_RETIRED_TIME_INC"],
            EPIC_WINS_STRIKE=self.__dict__["EPIC_WINS_STRIKE"],
            EventToolsChangeFields = self.__dict__["EventToolsChangeFields"].generateJsonDict(),
            FAVORITE_FRIENDS_LIMIT=self.__dict__["FAVORITE_FRIENDS_LIMIT"],
            FORBIDDEN_FOR_PARTY_HERO_PAIRS=self.__dict__["FORBIDDEN_FOR_PARTY_HERO_PAIRS"].getJsonDict(),
            FREE_FRACTION_CHANGES=self.__dict__["FREE_FRACTION_CHANGES"],
            FREE_NICK_CHANGES=self.__dict__["FREE_NICK_CHANGES"],
            FRIENDS_PAGE_SIZE=self.__dict__["FRIENDS_PAGE_SIZE"],
            FWOD_FOR_NEWBIES=self.__dict__["FWOD_FOR_NEWBIES"],
            GAMIGO_PAY_SERVER=self.__dict__["GAMIGO_PAY_SERVER"],
            GAMIGO_PAY_URL_SALT=self.__dict__["GAMIGO_PAY_URL_SALT"],
            GIVE_ALL_HEROES=self.__dict__["GIVE_ALL_HEROES"],
            GM_TOOL_UNBAN_COST=self.__dict__["GM_TOOL_UNBAN_COST"],
            GUILD_BEST_PLAYERS=self.__dict__["GUILD_BEST_PLAYERS"],
            GUILD_CREATE_PRICE_SILVER=self.__dict__["GUILD_CREATE_PRICE_SILVER"],
            GUILD_DEFAULT_RATING=self.__dict__["GUILD_DEFAULT_RATING"],
            GUILD_ENABLED=self.__dict__["GUILD_ENABLED"],
            GUILD_FREE_ICON_CHANGES_COUNT=self.__dict__["GUILD_FREE_ICON_CHANGES_COUNT"],
            GUILD_ICON_CHANGE_COST=self.__dict__["GUILD_ICON_CHANGE_COST"],
            GUILD_ICONS_URL_PATTERN=self.__dict__["GUILD_ICONS_URL_PATTERN"],
            GUILD_INVITE_TIMEOUT=self.__dict__["GUILD_INVITE_TIMEOUT"],
            GUILD_LIST_RECOMMENDED_VASSAL_SIZE=self.__dict__["GUILD_LIST_RECOMMENDED_VASSAL_SIZE"],
            GUILD_MAX_LOG_SIZE=self.__dict__["GUILD_MAX_LOG_SIZE"],
            GUILD_MAX_RECOMMENDED_VASSAL_SIZE=self.__dict__["GUILD_MAX_RECOMMENDED_VASSAL_SIZE"],
            GUILD_MAX_SIZE=self.__dict__["GUILD_MAX_SIZE"],
            GUILD_MAX_VASSAL_SIZE=self.__dict__["GUILD_MAX_VASSAL_SIZE"],
            GUILD_MIN_LEVEL_FOR_ICON_CHANGE=self.__dict__["GUILD_MIN_LEVEL_FOR_ICON_CHANGE"],
            GUILD_RATE_TECHS_WEIGHT=self.__dict__["GUILD_RATE_TECHS_WEIGHT"],
            GUILD_RENAME_PRICE_GOLD=self.__dict__["GUILD_RENAME_PRICE_GOLD"],
            GUILD_SHOP_ITEMS=self.__dict__["GUILD_SHOP_ITEMS"].getJsonDict(),
            GUILD_SUZERAIN_INVITE_LIMIT=self.__dict__["GUILD_SUZERAIN_INVITE_LIMIT"],
            GUILD_SUZERAIN_INVITE_TIMELIMIT=self.__dict__["GUILD_SUZERAIN_INVITE_TIMELIMIT"],
            GUILD_SUZERAIN_INVITE_TIMEOUT=self.__dict__["GUILD_SUZERAIN_INVITE_TIMEOUT"],
            GUILD_WAR_EVENT_ENABLED=self.__dict__["GUILD_WAR_EVENT_ENABLED"],
            GUILD_WARS_ENABLED=self.__dict__["GUILD_WARS_ENABLED"],
            GuildBankSettings = self.__dict__["GuildBankSettings"].generateJsonDict(),
            GUILDS_IN_LIST_PER_REQUEST=self.__dict__["GUILDS_IN_LIST_PER_REQUEST"],
            HERO_COEFF_RATING=self.__dict__["HERO_COEFF_RATING"],
            HERO_CUP_RATING=self.__dict__["HERO_CUP_RATING"],
            HERO_DELTA_RATING=self.__dict__["HERO_DELTA_RATING"],
            HERO_START_RATING=self.__dict__["HERO_START_RATING"],
            HIDE_BACK_SCREEN_TIMEOUT=self.__dict__["HIDE_BACK_SCREEN_TIMEOUT"],
            HonorSettings = self.__dict__["HonorSettings"].generateJsonDict(),
            INIT_FAME=self.__dict__["INIT_FAME"],
            INIT_SILVER=self.__dict__["INIT_SILVER"],
            INIT_TALENTS=self.__dict__["INIT_TALENTS"].getJsonDict(),
            INVALID_HEROES=self.__dict__["INVALID_HEROES"].getJsonDict(),
            INVALID_QUESTS=self.__dict__["INVALID_QUESTS"].getJsonDict(),
            INVALID_SKINS=self.__dict__["INVALID_SKINS"].getJsonDict(),
            IS_REFORGE_ACTIVE=self.__dict__["IS_REFORGE_ACTIVE"],
            K_FORCE_RATING=self.__dict__["K_FORCE_RATING"],
            KEEPALIVE_TIMEOUT=self.__dict__["KEEPALIVE_TIMEOUT"],
            KICK_FROM_TOURNAMENT_BY_TIMEOUT=self.__dict__["KICK_FROM_TOURNAMENT_BY_TIMEOUT"],
            LampEventSettings = self.__dict__["LampEventSettings"].generateJsonDict(),
            LAST_LOGIN_TIME_FOR_CASTLE_QUEST=self.__dict__["LAST_LOGIN_TIME_FOR_CASTLE_QUEST"],
            LEAVES_POINT=self.__dict__["LEAVES_POINT"],
            LORD_LEVEL_FOR_ADVERTISING=self.__dict__["LORD_LEVEL_FOR_ADVERTISING"],
            MAILRU_PAY_SERVER=self.__dict__["MAILRU_PAY_SERVER"],
            MAILRU_PAY_URL_PARAMS=self.__dict__["MAILRU_PAY_URL_PARAMS"],
            MAILRU_PAY_URL_SALT=self.__dict__["MAILRU_PAY_URL_SALT"],
            MAPS_FOR_PLAYER_RATING=self.__dict__["MAPS_FOR_PLAYER_RATING"].getJsonDict(),
            MARKETING_EVENTS=self.__dict__["MARKETING_EVENTS"].getJsonDict(),
            MASSIVE_PAY_SERVER=self.__dict__["MASSIVE_PAY_SERVER"],
            MASSIVE_PAY_URL_SALT=self.__dict__["MASSIVE_PAY_URL_SALT"],
            MAX_GUILDS_IN_LIST=self.__dict__["MAX_GUILDS_IN_LIST"],
            MAX_IGNORED_PLAYERS=self.__dict__["MAX_IGNORED_PLAYERS"],
            MAX_LEAVES_POINT=self.__dict__["MAX_LEAVES_POINT"],
            MAX_USER_TALENTSETS_COUNT=self.__dict__["MAX_USER_TALENTSETS_COUNT"],
            MIN_LEAVES_POINT=self.__dict__["MIN_LEAVES_POINT"],
            MonetizationDisablers = self.__dict__["MonetizationDisablers"].generateJsonDict(),
            MuteSettings = self.__dict__["MuteSettings"].generateJsonDict(),
            NEW_CHAT_PROTOCOL=self.__dict__["NEW_CHAT_PROTOCOL"],
            NEWBIE_WINS=self.__dict__["NEWBIE_WINS"],
            NEWS=self.__dict__["NEWS"].getJsonDict(),
            NewsKeeper=self.__dict__["NewsKeeper"].generateJsonDict(),
            NICKNAME_REGEXES=self.__dict__["NICKNAME_REGEXES"].getJsonDict(),
            NUM_CHEAT_CYCLES=self.__dict__["NUM_CHEAT_CYCLES"],
            ONE_TIME_QUESTS=self.__dict__["ONE_TIME_QUESTS"],
            PARTY_FORCE_RANGE=self.__dict__["PARTY_FORCE_RANGE"],
            PARTY_RATING_RANGE=self.__dict__["PARTY_RATING_RANGE"],
            PAY_SERVER=self.__dict__["PAY_SERVER"],
            PAY_URL_SALT=self.__dict__["PAY_URL_SALT"],
            PERCENT_TO_CYCLES_CHANGE=self.__dict__["PERCENT_TO_CYCLES_CHANGE"],
            PingInfo = self.__dict__["PingInfo"].generateJsonDict(),
            PLAYER_RATING_PERIOD=self.__dict__["PLAYER_RATING_PERIOD"],
            POINTS_PER_BAD_BEHAIVIOR_REPORTS=self.__dict__["POINTS_PER_BAD_BEHAIVIOR_REPORTS"],
            PREMIUM_ACCOUNT_BONUS=self.__dict__["PREMIUM_ACCOUNT_BONUS"],
            PREMIUM_ACCOUNT_DURATION=self.__dict__["PREMIUM_ACCOUNT_DURATION"],
            PREMIUM_ACCOUNT_DURATION2=self.__dict__["PREMIUM_ACCOUNT_DURATION2"],
            PREMIUM_ACCOUNT_DURATION3=self.__dict__["PREMIUM_ACCOUNT_DURATION3"],
            PREMIUM_ACCOUNT_LORD_LEVEL=self.__dict__["PREMIUM_ACCOUNT_LORD_LEVEL"],
            PREMIUM_ACCOUNT_PRICE=self.__dict__["PREMIUM_ACCOUNT_PRICE"],
            PREMIUM_ACCOUNT_PRICE2=self.__dict__["PREMIUM_ACCOUNT_PRICE2"],
            PREMIUM_ACCOUNT_PRICE3=self.__dict__["PREMIUM_ACCOUNT_PRICE3"],
            PREMIUM_ACCOUNT_SESSION_BONUS=self.__dict__["PREMIUM_ACCOUNT_SESSION_BONUS"],
            PREMIUM_ACCOUNT_SNOW_BANNER_TIMELEFT=self.__dict__["PREMIUM_ACCOUNT_SNOW_BANNER_TIMELEFT"],
            PREMIUM_ACCOUNT_TAVERN_BONUS=self.__dict__["PREMIUM_ACCOUNT_TAVERN_BONUS"],
            PREMIUM_ACOUNT_LEFT_ALARM=self.__dict__["PREMIUM_ACOUNT_LEFT_ALARM"],
            PREMIUM_ACOUNT_LEFT_ALARM_PERIOD=self.__dict__["PREMIUM_ACOUNT_LEFT_ALARM_PERIOD"],
            PRODUCTION_BOOST_COEFF=self.__dict__["PRODUCTION_BOOST_COEFF"],
            ProductionDiscount = self.__dict__["ProductionDiscount"].generateJsonDict(),
            PUNISHED_PLAYERS_UPDATE_TIME=self.__dict__["PUNISHED_PLAYERS_UPDATE_TIME"],
            QuestEventKeeper=self.__dict__["QuestEventKeeper"].generateJsonDict(),
            QuestEvents=self.__dict__["QuestEvents"].getJsonDict(),
            QuestEventStageKeeper=self.__dict__["QuestEventStageKeeper"].generateJsonDict(),
            QuestEventStageStepKeeper=self.__dict__["QuestEventStageStepKeeper"].generateJsonDict(),
            QuestEventStageStepVariantKeeper=self.__dict__["QuestEventStageStepVariantKeeper"].generateJsonDict(),
            RECENT_ALLIES_IN_LIST=self.__dict__["RECENT_ALLIES_IN_LIST"],
            ReforgeTalentPricesKeeper=self.__dict__["ReforgeTalentPricesKeeper"].generateJsonDict(),
            REQUIRED_LEVEL_FOR_EXCLUSIVE_TALENTS=self.__dict__["REQUIRED_LEVEL_FOR_EXCLUSIVE_TALENTS"],
            REQUIRED_LEVEL_FOR_OUTSTANDING_TALENTS=self.__dict__["REQUIRED_LEVEL_FOR_OUTSTANDING_TALENTS"],
            RerollShopGroupUpgradeLevelsKeeper=self.__dict__["RerollShopGroupUpgradeLevelsKeeper"].generateJsonDict(),
            RerollShopWeightsToTimesKeeper=self.__dict__["RerollShopWeightsToTimesKeeper"].generateJsonDict(),
            RESET_ACCOUNT_TIME=self.__dict__["RESET_ACCOUNT_TIME"],
            RETURN_FRIEND_ENABLED=self.__dict__["RETURN_FRIEND_ENABLED"],
            RollEventItemKeeper=self.__dict__["RollEventItemKeeper"].generateJsonDict(),
            RollEventKeeper=self.__dict__["RollEventKeeper"].generateJsonDict(),
            RollEventRuleKeeper=self.__dict__["RollEventRuleKeeper"].generateJsonDict(),
            RollEvents=self.__dict__["RollEvents"].getJsonDict(),
            ROTATION_QUEST_LIFETIME=self.__dict__["ROTATION_QUEST_LIFETIME"],
            SAVE_TALENTS_POINTS_ON_REFORGE=self.__dict__["SAVE_TALENTS_POINTS_ON_REFORGE"],
            SEASON_SKINS=self.__dict__["SEASON_SKINS"].getJsonDict(),
            SeasonEventKeeper=self.__dict__["SeasonEventKeeper"].generateJsonDict(),
            SeasonEvents=self.__dict__["SeasonEvents"].getJsonDict(),
            SeasonEventShopGroupKeeper=self.__dict__["SeasonEventShopGroupKeeper"].generateJsonDict(),
            SeasonEventShopItemKeeper=self.__dict__["SeasonEventShopItemKeeper"].generateJsonDict(),
            SeasonProgressRewardKeeper=self.__dict__["SeasonProgressRewardKeeper"].generateJsonDict(),
            SEC_TO_CHEAT_CYCLE=self.__dict__["SEC_TO_CHEAT_CYCLE"],
            SECONDS_TO_AFK_STATE=self.__dict__["SECONDS_TO_AFK_STATE"],
            SEND_PENDING_EVENTS=self.__dict__["SEND_PENDING_EVENTS"],
            SESSION_TO_CASTLE_FIX_1=self.__dict__["SESSION_TO_CASTLE_FIX_1"],
            SESSION_TO_CASTLE_FIX_2=self.__dict__["SESSION_TO_CASTLE_FIX_2"],
            SHARING_WEBSITE_SALT=self.__dict__["SHARING_WEBSITE_SALT"],
            SHARING_WEBSITE_URL=self.__dict__["SHARING_WEBSITE_URL"],
            SHIFT_MIN_RANK=self.__dict__["SHIFT_MIN_RANK"],
            SHOW_BUY_CONFIRMATION_DIALOGS=self.__dict__["SHOW_BUY_CONFIRMATION_DIALOGS"],
            SiegeSettings = self.__dict__["SiegeSettings"].generateJsonDict(),
            SILVER_TO_GUILD_RESOURCES_COEFF=self.__dict__["SILVER_TO_GUILD_RESOURCES_COEFF"],
            SKIN_AVATAR_BLOCK=self.__dict__["SKIN_AVATAR_BLOCK"].getJsonDict(),
            SKIPPED_TUTORIAL_QUESTS=self.__dict__["SKIPPED_TUTORIAL_QUESTS"].getJsonDict(),
            SOULBOUND_ENABLED=self.__dict__["SOULBOUND_ENABLED"],
            START_HOUR_FOR_TAVERN_REROLL=self.__dict__["START_HOUR_FOR_TAVERN_REROLL"],
            STATIC_DATA_OVERRIDES=self.__dict__["STATIC_DATA_OVERRIDES"].getJsonDict(),
            SUB_LEAVE_POINT=self.__dict__["SUB_LEAVE_POINT"],
            TALENT_UPGRADE_LORD_LEVEL=self.__dict__["TALENT_UPGRADE_LORD_LEVEL"],
            TALENTIDS_FOR_NEW_SN=self.__dict__["TALENTIDS_FOR_NEW_SN"].getJsonDict(),
            TALENTS_NOT_FOR_ROLL=self.__dict__["TALENTS_NOT_FOR_ROLL"].getJsonDict(),
            TalentsCollectionSettings = self.__dict__["TalentsCollectionSettings"].generateJsonDict(),
            TamburInfo = self.__dict__["TamburInfo"].generateJsonDict(),
            TESTS_ENABLED=self.__dict__["TESTS_ENABLED"],
            TIME_TO_STAY_PASSIVE=self.__dict__["TIME_TO_STAY_PASSIVE"],
            TOTAL_BOOST_TIME=self.__dict__["TOTAL_BOOST_TIME"],
            TournamentSettings = self.__dict__["TournamentSettings"].generateJsonDict(),
            TradeEventGroupKeeper=self.__dict__["TradeEventGroupKeeper"].generateJsonDict(),
            TradeEventKeeper=self.__dict__["TradeEventKeeper"].generateJsonDict(),
            TradeEvents=self.__dict__["TradeEvents"].getJsonDict(),
            TradeExperienceRewardKeeper=self.__dict__["TradeExperienceRewardKeeper"].generateJsonDict(),
            TradeGroupMemberKeeper=self.__dict__["TradeGroupMemberKeeper"].generateJsonDict(),
            TradeWorldRatingRewardKeeper=self.__dict__["TradeWorldRatingRewardKeeper"].generateJsonDict(),
            UNLOAD_CASTLE_IN_TUTORIAL=self.__dict__["UNLOAD_CASTLE_IN_TUTORIAL"],
            USE_LEVEL_SCALE_FOR_RESET_PRICE=self.__dict__["USE_LEVEL_SCALE_FOR_RESET_PRICE"],
            WEB_IM_ENABLED=self.__dict__["WEB_IM_ENABLED"],
            WEB_IM_WEBSITE_URL=self.__dict__["WEB_IM_WEBSITE_URL"],
            ZZIMA_PAY_SERVER=self.__dict__["ZZIMA_PAY_SERVER"],
        )
        return { "ConfigData": _dct }
    

    def serializeToFile(self, file):
        pass
        file.write("self.ADD_FIRST_QUEST = " + repr(self.ADD_FIRST_QUEST) + "\n")
        file.write("self.ADD_LEAVE_POINT = " + repr(self.ADD_LEAVE_POINT) + "\n")
        self.ADDITIONAL_CONFIGS.serializeToFile(file, "ADDITIONAL_CONFIGS")
        file.write("self.ADMIN_MESSAGES_TO_STORE = " + repr(self.ADMIN_MESSAGES_TO_STORE) + "\n")
        self.ADMIN_NICKS.serializeToFile(file, "ADMIN_NICKS")
        file.write("self.AERIA_PAY_SERVER = " + repr(self.AERIA_PAY_SERVER) + "\n")
        file.write("self.AFTERPARTY_TIMEOUT = " + repr(self.AFTERPARTY_TIMEOUT) + "\n")
        file.write("self.ALLOW_REROLL_FROM_SET_FOR_UPGRADED_TALENTS_ON_REFORGE = " + repr(self.ALLOW_REROLL_FROM_SET_FOR_UPGRADED_TALENTS_ON_REFORGE) + "\n")
        self.ALTERNATIVE_QUESTS.serializeToFile(file, "ALTERNATIVE_QUESTS")
        file.write("self.APPEARING_GOLDPRODUCTIONHOUSE_PRICE = " + repr(self.APPEARING_GOLDPRODUCTIONHOUSE_PRICE) + "\n")
        file.write("self.ARCGAMES_APPID = " + repr(self.ARCGAMES_APPID) + "\n")
        file.write("self.ARCGAMES_PAY_SERVER = " + repr(self.ARCGAMES_PAY_SERVER) + "\n")
        file.write("self.ARCGAMES_USE_OVERLAY = " + repr(self.ARCGAMES_USE_OVERLAY) + "\n")
        file.write("self.AUTOMUTE_DURATION = " + repr(self.AUTOMUTE_DURATION) + "\n")
        self.BeginnersPackEventInfo.serializeToFile(file, "BeginnersPackEventInfo")
        file.write("self.BEHAVIOUR_DETECTED_ENABLE = " + repr(self.BEHAVIOUR_DETECTED_ENABLE) + "\n")
        self.BruteForceDefenderSettings.serializeToFile(file, "BruteForceDefenderSettings")
        file.write("self.BUY_HERO_MAX_ORIGINAL_PRICE = " + repr(self.BUY_HERO_MAX_ORIGINAL_PRICE) + "\n")
        file.write("self.BUY_HERO_PRICE = " + repr(self.BUY_HERO_PRICE) + "\n")
        self.BuyAeriaGoldEventInfo.serializeToFile(file, "BuyAeriaGoldEventInfo")
        self.BuyArcGamesGoldEventInfo.serializeToFile(file, "BuyArcGamesGoldEventInfo")
        self.BuyGamigoGoldEventInfo.serializeToFile(file, "BuyGamigoGoldEventInfo")
        self.BuyGoldHeroInfo.serializeToFile(file, "BuyGoldHeroInfo")
        self.BuySpecialHeroEventInfo.serializeToFile(file, "BuySpecialHeroEventInfo")
        self.BuySteamGoldEventInfo.serializeToFile(file, "BuySteamGoldEventInfo")
        self.BuyZZimaGoldEventInfo.serializeToFile(file, "BuyZZimaGoldEventInfo")
        file.write("self.CAMERA_FLYBY_TIMEOUT_DURATION = " + repr(self.CAMERA_FLYBY_TIMEOUT_DURATION) + "\n")
        file.write("self.CHANGE_FRACTION_TO_ADORNIA = " + repr(self.CHANGE_FRACTION_TO_ADORNIA) + "\n")
        file.write("self.CHANGE_FRACTION_TO_DOCT = " + repr(self.CHANGE_FRACTION_TO_DOCT) + "\n")
        file.write("self.CHECK_REQUESTS_REPEATABILITY = " + repr(self.CHECK_REQUESTS_REPEATABILITY) + "\n")
        self.ComplaintsSettings.serializeToFile(file, "ComplaintsSettings")
        file.write("self.COST_FRACTION_CHANGE = " + repr(self.COST_FRACTION_CHANGE) + "\n")
        file.write("self.COST_NICK_CHANGE = " + repr(self.COST_NICK_CHANGE) + "\n")
        file.write("self.DEBUG_ENABLED = " + repr(self.DEBUG_ENABLED) + "\n")
        file.write("self.DEFAULT_FRACTION = " + repr(self.DEFAULT_FRACTION) + "\n")
        self.DEFAULT_SKINS.serializeToFile(file, "DEFAULT_SKINS")
        file.write("self.DEFEATS_COUNT_FOR_KICK_FROM_TOURNAMENT = " + repr(self.DEFEATS_COUNT_FOR_KICK_FROM_TOURNAMENT) + "\n")
        file.write("self.DELAYED_SESSION_START_TIME = " + repr(self.DELAYED_SESSION_START_TIME) + "\n")
        self.DISABLED_DEFAULT_TALENSETS.serializeToFile(file, "DISABLED_DEFAULT_TALENSETS")
        file.write("self.DONT_VALIDATE_STEAM_DLC = " + repr(self.DONT_VALIDATE_STEAM_DLC) + "\n")
        file.write("self.DRAUGASLT_PAY_SERVER = " + repr(self.DRAUGASLT_PAY_SERVER) + "\n")
        file.write("self.DRAUGASLT_PAY_URL_PARAMS = " + repr(self.DRAUGASLT_PAY_URL_PARAMS) + "\n")
        file.write("self.DRAUGASLT_PAY_URL_SALT = " + repr(self.DRAUGASLT_PAY_URL_SALT) + "\n")
        file.write("self.ENABLE_AUTOACCEPT = " + repr(self.ENABLE_AUTOACCEPT) + "\n")
        file.write("self.ENABLE_TAVERT_REROLL_ON_LEVELUP = " + repr(self.ENABLE_TAVERT_REROLL_ON_LEVELUP) + "\n")
        file.write("self.EPIC_HERO_FORCE = " + repr(self.EPIC_HERO_FORCE) + "\n")
        file.write("self.EPIC_HERO_RETIRE_LIFETIME = " + repr(self.EPIC_HERO_RETIRE_LIFETIME) + "\n")
        file.write("self.EPIC_HERO_RETIRED_CAP = " + repr(self.EPIC_HERO_RETIRED_CAP) + "\n")
        file.write("self.EPIC_HERO_RETIRED_TIME_BASE = " + repr(self.EPIC_HERO_RETIRED_TIME_BASE) + "\n")
        file.write("self.EPIC_HERO_RETIRED_TIME_INC = " + repr(self.EPIC_HERO_RETIRED_TIME_INC) + "\n")
        file.write("self.EPIC_WINS_STRIKE = " + repr(self.EPIC_WINS_STRIKE) + "\n")
        self.EventToolsChangeFields.serializeToFile(file, "EventToolsChangeFields")
        file.write("self.FAVORITE_FRIENDS_LIMIT = " + repr(self.FAVORITE_FRIENDS_LIMIT) + "\n")
        self.FORBIDDEN_FOR_PARTY_HERO_PAIRS.serializeToFile(file, "FORBIDDEN_FOR_PARTY_HERO_PAIRS")
        file.write("self.FREE_FRACTION_CHANGES = " + repr(self.FREE_FRACTION_CHANGES) + "\n")
        file.write("self.FREE_NICK_CHANGES = " + repr(self.FREE_NICK_CHANGES) + "\n")
        file.write("self.FRIENDS_PAGE_SIZE = " + repr(self.FRIENDS_PAGE_SIZE) + "\n")
        file.write("self.FWOD_FOR_NEWBIES = " + repr(self.FWOD_FOR_NEWBIES) + "\n")
        file.write("self.GAMIGO_PAY_SERVER = " + repr(self.GAMIGO_PAY_SERVER) + "\n")
        file.write("self.GAMIGO_PAY_URL_SALT = " + repr(self.GAMIGO_PAY_URL_SALT) + "\n")
        file.write("self.GIVE_ALL_HEROES = " + repr(self.GIVE_ALL_HEROES) + "\n")
        file.write("self.GM_TOOL_UNBAN_COST = " + repr(self.GM_TOOL_UNBAN_COST) + "\n")
        file.write("self.GUILD_BEST_PLAYERS = " + repr(self.GUILD_BEST_PLAYERS) + "\n")
        file.write("self.GUILD_CREATE_PRICE_SILVER = " + repr(self.GUILD_CREATE_PRICE_SILVER) + "\n")
        file.write("self.GUILD_DEFAULT_RATING = " + repr(self.GUILD_DEFAULT_RATING) + "\n")
        file.write("self.GUILD_ENABLED = " + repr(self.GUILD_ENABLED) + "\n")
        file.write("self.GUILD_FREE_ICON_CHANGES_COUNT = " + repr(self.GUILD_FREE_ICON_CHANGES_COUNT) + "\n")
        file.write("self.GUILD_ICON_CHANGE_COST = " + repr(self.GUILD_ICON_CHANGE_COST) + "\n")
        file.write("self.GUILD_ICONS_URL_PATTERN = " + repr(self.GUILD_ICONS_URL_PATTERN) + "\n")
        file.write("self.GUILD_INVITE_TIMEOUT = " + repr(self.GUILD_INVITE_TIMEOUT) + "\n")
        file.write("self.GUILD_LIST_RECOMMENDED_VASSAL_SIZE = " + repr(self.GUILD_LIST_RECOMMENDED_VASSAL_SIZE) + "\n")
        file.write("self.GUILD_MAX_LOG_SIZE = " + repr(self.GUILD_MAX_LOG_SIZE) + "\n")
        file.write("self.GUILD_MAX_RECOMMENDED_VASSAL_SIZE = " + repr(self.GUILD_MAX_RECOMMENDED_VASSAL_SIZE) + "\n")
        file.write("self.GUILD_MAX_SIZE = " + repr(self.GUILD_MAX_SIZE) + "\n")
        file.write("self.GUILD_MAX_VASSAL_SIZE = " + repr(self.GUILD_MAX_VASSAL_SIZE) + "\n")
        file.write("self.GUILD_MIN_LEVEL_FOR_ICON_CHANGE = " + repr(self.GUILD_MIN_LEVEL_FOR_ICON_CHANGE) + "\n")
        file.write("self.GUILD_RATE_TECHS_WEIGHT = " + repr(self.GUILD_RATE_TECHS_WEIGHT) + "\n")
        file.write("self.GUILD_RENAME_PRICE_GOLD = " + repr(self.GUILD_RENAME_PRICE_GOLD) + "\n")
        self.GUILD_SHOP_ITEMS.serializeToFile(file, "GUILD_SHOP_ITEMS")
        file.write("self.GUILD_SUZERAIN_INVITE_LIMIT = " + repr(self.GUILD_SUZERAIN_INVITE_LIMIT) + "\n")
        file.write("self.GUILD_SUZERAIN_INVITE_TIMELIMIT = " + repr(self.GUILD_SUZERAIN_INVITE_TIMELIMIT) + "\n")
        file.write("self.GUILD_SUZERAIN_INVITE_TIMEOUT = " + repr(self.GUILD_SUZERAIN_INVITE_TIMEOUT) + "\n")
        file.write("self.GUILD_WAR_EVENT_ENABLED = " + repr(self.GUILD_WAR_EVENT_ENABLED) + "\n")
        file.write("self.GUILD_WARS_ENABLED = " + repr(self.GUILD_WARS_ENABLED) + "\n")
        self.GuildBankSettings.serializeToFile(file, "GuildBankSettings")
        file.write("self.GUILDS_IN_LIST_PER_REQUEST = " + repr(self.GUILDS_IN_LIST_PER_REQUEST) + "\n")
        file.write("self.HERO_COEFF_RATING = " + repr(self.HERO_COEFF_RATING) + "\n")
        file.write("self.HERO_CUP_RATING = " + repr(self.HERO_CUP_RATING) + "\n")
        file.write("self.HERO_DELTA_RATING = " + repr(self.HERO_DELTA_RATING) + "\n")
        file.write("self.HERO_START_RATING = " + repr(self.HERO_START_RATING) + "\n")
        file.write("self.HIDE_BACK_SCREEN_TIMEOUT = " + repr(self.HIDE_BACK_SCREEN_TIMEOUT) + "\n")
        self.HonorSettings.serializeToFile(file, "HonorSettings")
        file.write("self.INIT_FAME = " + repr(self.INIT_FAME) + "\n")
        file.write("self.INIT_SILVER = " + repr(self.INIT_SILVER) + "\n")
        self.INIT_TALENTS.serializeToFile(file, "INIT_TALENTS")
        self.INVALID_HEROES.serializeToFile(file, "INVALID_HEROES")
        self.INVALID_QUESTS.serializeToFile(file, "INVALID_QUESTS")
        self.INVALID_SKINS.serializeToFile(file, "INVALID_SKINS")
        file.write("self.IS_REFORGE_ACTIVE = " + repr(self.IS_REFORGE_ACTIVE) + "\n")
        file.write("self.K_FORCE_RATING = " + repr(self.K_FORCE_RATING) + "\n")
        file.write("self.KEEPALIVE_TIMEOUT = " + repr(self.KEEPALIVE_TIMEOUT) + "\n")
        file.write("self.KICK_FROM_TOURNAMENT_BY_TIMEOUT = " + repr(self.KICK_FROM_TOURNAMENT_BY_TIMEOUT) + "\n")
        self.LampEventSettings.serializeToFile(file, "LampEventSettings")
        file.write("self.LAST_LOGIN_TIME_FOR_CASTLE_QUEST = " + repr(self.LAST_LOGIN_TIME_FOR_CASTLE_QUEST) + "\n")
        file.write("self.LEAVES_POINT = " + repr(self.LEAVES_POINT) + "\n")
        file.write("self.LORD_LEVEL_FOR_ADVERTISING = " + repr(self.LORD_LEVEL_FOR_ADVERTISING) + "\n")
        file.write("self.MAILRU_PAY_SERVER = " + repr(self.MAILRU_PAY_SERVER) + "\n")
        file.write("self.MAILRU_PAY_URL_PARAMS = " + repr(self.MAILRU_PAY_URL_PARAMS) + "\n")
        file.write("self.MAILRU_PAY_URL_SALT = " + repr(self.MAILRU_PAY_URL_SALT) + "\n")
        self.MAPS_FOR_PLAYER_RATING.serializeToFile(file, "MAPS_FOR_PLAYER_RATING")
        self.MARKETING_EVENTS.serializeToFile(file, "MARKETING_EVENTS")
        file.write("self.MASSIVE_PAY_SERVER = " + repr(self.MASSIVE_PAY_SERVER) + "\n")
        file.write("self.MASSIVE_PAY_URL_SALT = " + repr(self.MASSIVE_PAY_URL_SALT) + "\n")
        file.write("self.MAX_GUILDS_IN_LIST = " + repr(self.MAX_GUILDS_IN_LIST) + "\n")
        file.write("self.MAX_IGNORED_PLAYERS = " + repr(self.MAX_IGNORED_PLAYERS) + "\n")
        file.write("self.MAX_LEAVES_POINT = " + repr(self.MAX_LEAVES_POINT) + "\n")
        file.write("self.MAX_USER_TALENTSETS_COUNT = " + repr(self.MAX_USER_TALENTSETS_COUNT) + "\n")
        file.write("self.MIN_LEAVES_POINT = " + repr(self.MIN_LEAVES_POINT) + "\n")
        self.MonetizationDisablers.serializeToFile(file, "MonetizationDisablers")
        self.MuteSettings.serializeToFile(file, "MuteSettings")
        file.write("self.NEW_CHAT_PROTOCOL = " + repr(self.NEW_CHAT_PROTOCOL) + "\n")
        file.write("self.NEWBIE_WINS = " + repr(self.NEWBIE_WINS) + "\n")
        self.NICKNAME_REGEXES.serializeToFile(file, "NICKNAME_REGEXES")
        file.write("self.NUM_CHEAT_CYCLES = " + repr(self.NUM_CHEAT_CYCLES) + "\n")
        file.write("self.ONE_TIME_QUESTS = " + repr(self.ONE_TIME_QUESTS) + "\n")
        file.write("self.PARTY_FORCE_RANGE = " + repr(self.PARTY_FORCE_RANGE) + "\n")
        file.write("self.PARTY_RATING_RANGE = " + repr(self.PARTY_RATING_RANGE) + "\n")
        file.write("self.PAY_SERVER = " + repr(self.PAY_SERVER) + "\n")
        file.write("self.PAY_URL_SALT = " + repr(self.PAY_URL_SALT) + "\n")
        file.write("self.PERCENT_TO_CYCLES_CHANGE = " + repr(self.PERCENT_TO_CYCLES_CHANGE) + "\n")
        self.PingInfo.serializeToFile(file, "PingInfo")
        file.write("self.PLAYER_RATING_PERIOD = " + repr(self.PLAYER_RATING_PERIOD) + "\n")
        file.write("self.POINTS_PER_BAD_BEHAIVIOR_REPORTS = " + repr(self.POINTS_PER_BAD_BEHAIVIOR_REPORTS) + "\n")
        file.write("self.PREMIUM_ACCOUNT_BONUS = " + repr(self.PREMIUM_ACCOUNT_BONUS) + "\n")
        file.write("self.PREMIUM_ACCOUNT_DURATION = " + repr(self.PREMIUM_ACCOUNT_DURATION) + "\n")
        file.write("self.PREMIUM_ACCOUNT_DURATION2 = " + repr(self.PREMIUM_ACCOUNT_DURATION2) + "\n")
        file.write("self.PREMIUM_ACCOUNT_DURATION3 = " + repr(self.PREMIUM_ACCOUNT_DURATION3) + "\n")
        file.write("self.PREMIUM_ACCOUNT_LORD_LEVEL = " + repr(self.PREMIUM_ACCOUNT_LORD_LEVEL) + "\n")
        file.write("self.PREMIUM_ACCOUNT_PRICE = " + repr(self.PREMIUM_ACCOUNT_PRICE) + "\n")
        file.write("self.PREMIUM_ACCOUNT_PRICE2 = " + repr(self.PREMIUM_ACCOUNT_PRICE2) + "\n")
        file.write("self.PREMIUM_ACCOUNT_PRICE3 = " + repr(self.PREMIUM_ACCOUNT_PRICE3) + "\n")
        file.write("self.PREMIUM_ACCOUNT_SESSION_BONUS = " + repr(self.PREMIUM_ACCOUNT_SESSION_BONUS) + "\n")
        file.write("self.PREMIUM_ACCOUNT_SNOW_BANNER_TIMELEFT = " + repr(self.PREMIUM_ACCOUNT_SNOW_BANNER_TIMELEFT) + "\n")
        file.write("self.PREMIUM_ACCOUNT_TAVERN_BONUS = " + repr(self.PREMIUM_ACCOUNT_TAVERN_BONUS) + "\n")
        file.write("self.PREMIUM_ACOUNT_LEFT_ALARM = " + repr(self.PREMIUM_ACOUNT_LEFT_ALARM) + "\n")
        file.write("self.PREMIUM_ACOUNT_LEFT_ALARM_PERIOD = " + repr(self.PREMIUM_ACOUNT_LEFT_ALARM_PERIOD) + "\n")
        file.write("self.PRODUCTION_BOOST_COEFF = " + repr(self.PRODUCTION_BOOST_COEFF) + "\n")
        self.ProductionDiscount.serializeToFile(file, "ProductionDiscount")
        file.write("self.PUNISHED_PLAYERS_UPDATE_TIME = " + repr(self.PUNISHED_PLAYERS_UPDATE_TIME) + "\n")
        file.write("self.RECENT_ALLIES_IN_LIST = " + repr(self.RECENT_ALLIES_IN_LIST) + "\n")
        file.write("self.REQUIRED_LEVEL_FOR_EXCLUSIVE_TALENTS = " + repr(self.REQUIRED_LEVEL_FOR_EXCLUSIVE_TALENTS) + "\n")
        file.write("self.REQUIRED_LEVEL_FOR_OUTSTANDING_TALENTS = " + repr(self.REQUIRED_LEVEL_FOR_OUTSTANDING_TALENTS) + "\n")
        file.write("self.RESET_ACCOUNT_TIME = " + repr(self.RESET_ACCOUNT_TIME) + "\n")
        file.write("self.RETURN_FRIEND_ENABLED = " + repr(self.RETURN_FRIEND_ENABLED) + "\n")
        file.write("self.ROTATION_QUEST_LIFETIME = " + repr(self.ROTATION_QUEST_LIFETIME) + "\n")
        file.write("self.SAVE_TALENTS_POINTS_ON_REFORGE = " + repr(self.SAVE_TALENTS_POINTS_ON_REFORGE) + "\n")
        self.SEASON_SKINS.serializeToFile(file, "SEASON_SKINS")
        file.write("self.SEC_TO_CHEAT_CYCLE = " + repr(self.SEC_TO_CHEAT_CYCLE) + "\n")
        file.write("self.SECONDS_TO_AFK_STATE = " + repr(self.SECONDS_TO_AFK_STATE) + "\n")
        file.write("self.SEND_PENDING_EVENTS = " + repr(self.SEND_PENDING_EVENTS) + "\n")
        file.write("self.SESSION_TO_CASTLE_FIX_1 = " + repr(self.SESSION_TO_CASTLE_FIX_1) + "\n")
        file.write("self.SESSION_TO_CASTLE_FIX_2 = " + repr(self.SESSION_TO_CASTLE_FIX_2) + "\n")
        file.write("self.SHARING_WEBSITE_SALT = " + repr(self.SHARING_WEBSITE_SALT) + "\n")
        file.write("self.SHARING_WEBSITE_URL = " + repr(self.SHARING_WEBSITE_URL) + "\n")
        file.write("self.SHIFT_MIN_RANK = " + repr(self.SHIFT_MIN_RANK) + "\n")
        file.write("self.SHOW_BUY_CONFIRMATION_DIALOGS = " + repr(self.SHOW_BUY_CONFIRMATION_DIALOGS) + "\n")
        self.SiegeSettings.serializeToFile(file, "SiegeSettings")
        file.write("self.SILVER_TO_GUILD_RESOURCES_COEFF = " + repr(self.SILVER_TO_GUILD_RESOURCES_COEFF) + "\n")
        self.SKIN_AVATAR_BLOCK.serializeToFile(file, "SKIN_AVATAR_BLOCK")
        self.SKIPPED_TUTORIAL_QUESTS.serializeToFile(file, "SKIPPED_TUTORIAL_QUESTS")
        file.write("self.SOULBOUND_ENABLED = " + repr(self.SOULBOUND_ENABLED) + "\n")
        file.write("self.START_HOUR_FOR_TAVERN_REROLL = " + repr(self.START_HOUR_FOR_TAVERN_REROLL) + "\n")
        self.STATIC_DATA_OVERRIDES.serializeToFile(file, "STATIC_DATA_OVERRIDES")
        file.write("self.SUB_LEAVE_POINT = " + repr(self.SUB_LEAVE_POINT) + "\n")
        file.write("self.TALENT_UPGRADE_LORD_LEVEL = " + repr(self.TALENT_UPGRADE_LORD_LEVEL) + "\n")
        self.TALENTIDS_FOR_NEW_SN.serializeToFile(file, "TALENTIDS_FOR_NEW_SN")
        self.TALENTS_NOT_FOR_ROLL.serializeToFile(file, "TALENTS_NOT_FOR_ROLL")
        self.TalentsCollectionSettings.serializeToFile(file, "TalentsCollectionSettings")
        self.TamburInfo.serializeToFile(file, "TamburInfo")
        file.write("self.TESTS_ENABLED = " + repr(self.TESTS_ENABLED) + "\n")
        file.write("self.TIME_TO_STAY_PASSIVE = " + repr(self.TIME_TO_STAY_PASSIVE) + "\n")
        file.write("self.TOTAL_BOOST_TIME = " + repr(self.TOTAL_BOOST_TIME) + "\n")
        self.TournamentSettings.serializeToFile(file, "TournamentSettings")
        file.write("self.UNLOAD_CASTLE_IN_TUTORIAL = " + repr(self.UNLOAD_CASTLE_IN_TUTORIAL) + "\n")
        file.write("self.USE_LEVEL_SCALE_FOR_RESET_PRICE = " + repr(self.USE_LEVEL_SCALE_FOR_RESET_PRICE) + "\n")
        file.write("self.WEB_IM_ENABLED = " + repr(self.WEB_IM_ENABLED) + "\n")
        file.write("self.WEB_IM_WEBSITE_URL = " + repr(self.WEB_IM_WEBSITE_URL) + "\n")
        file.write("self.ZZIMA_PAY_SERVER = " + repr(self.ZZIMA_PAY_SERVER) + "\n")

    
# инициализаци€ списка сериализуемых классов при импорте модул€
ConfigData.initJsonTypes(ConfigData)
