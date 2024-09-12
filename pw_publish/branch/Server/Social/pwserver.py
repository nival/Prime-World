#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
from base.exceptions import BadModelDataError
import datetime, signal, copy
import functools
from base.wstools import AddLoopCallback, RemoveLoopCallback
addModPath('cfg')

from enums import *

import tornado.options
from tornado.options import define, options
import isteam
import iaeria
import iarcgames
import izzimacom
import tornadoredis

#SPECIFIC # matchmaking const
import CC
import MM
from MM import EAwardType

import party_const

from binascii import crc32

MARKER_FILENAME = ''

##----------------------------------------------------------------------------------------------------------------------
## затаскиваем все web request handlers (основные и "расширенные")
from handlers import * # JsonHandler, SubAction, IfaceFactory
from ifactory import IfaceFactory
import izzima
from pwhandler import PwJsonHandler, SocialExchangeJsonHandler, PersonServerFriendsCmdAction # SPECIFIC
from whandler import WebJsonHandler # SPECIFIC
from intaction import InternalAction, InternalMailAction

from iwebserver import ITornadoServer, ICSVActionTimingWriter, ISocialExchangeUser
from wserver import WorkServer

import ixchange
import imirror
import ipersonserver
import ifriendservice
import ipartyservice

##----------------------------------------------------------------------------------------------------------------------
## служебные web handlers типа Login импортируем отдельно
from ext_main.login import LoginAction, LogoutAction
from ext_main.sn_login import SocAggLoginAction
from ext_main.login import LogoutOldUserAction
from ext_main.create_account import CreateAccountAction
from ext_main.alien_login import AlienLoginAction
from ext_main.pguest_login import PersistentGuestLoginAction
from ext_main.auth import AuthAction
from ext_main.who import WhoAction, SetSteamGenderAction
from ext_main.join import JoinAction
from ext_main.l_login import LauncherLoginAction
from ext_main.l_ping import LauncherPingAction
from ext_main.l_merge import LauncherMergeAction
from ext_main.l_statistic import LauncherStartAction, LauncherEventsAction, LauncherDActions
from ext_main.nickname import NicknameRemoveSquareBrackets
from ext_pw.matchmake import CheckForSpectatorAction
from ext_main.get_full_user_account import GetFullUserAccountAction, GetAccountDataAction
from ext_main.accept_recruit import AcceptRecruitAction


from ext_main.pwc_actions import PWConnectWhoAction, PWConnectLoginAction, PWConfirmAction, PWConfirmRedirectAction, PWGetInfoAction, PWConnectLoadAction, \
    PWChangePasswordLinkAction, PWChangePasswordLinkActionExt

from ext_pw.sexchange import ExchangeSendAction, DefaultMailAction, AsyncMailAction, SessionAwardsMailAction, ForgeRollMailAction,\
  InviteFriendMailAction, InviteGuildMailAction, DeleteAllGuildTalentsMailAction, AddGuildTalentMailAction, DeleteGuildTalentMailAction,\
  TicketInfoMailAction, DestroyGuildMailAction, AddGuildBufMailAction, DeleteAllGuildBufsMailAction, RemoveGuildApplicationMailAction,\
  RecruitApplicationRejectedMailAction, AddMuteAction


import ext_main.l_login
import ext_pw
import logic.all
import cfg
import coord_cfg
import pymongo
import gc

from ext_pw.matchmake import MatchmakingAcceptAction
from logic.requests.PartyHeroRequest import PartyHeroRequest
from logic.party_hero import Party_hero

##----------------------------------------------------------------------------------------------------------------------
from modeldata.datamanager import PwNewModelManager
from modeldata.change_applicator import ModelChangeApplicator
from friendsdata.FriendsData import FriendsData
from modeldata.ModelData import ModelData
from modeldata.DynamicQuest import DynamicQuest
from party.PartyData import PartyData
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from modeldata.TopBuildsData import TopBuildsData
from guild.GuildWarEventData import GuildWarEventData
from modeldata.changes import MakeModelChangeString,PendingChangeWriter, GroupPendingChangeWriter
from modeldata.MultiStaticData import MultiStaticData
from guild.guild_bonuses_helper import GuildBonusProcessor
from enums.DetectedBadBehaviour import DetectedBadBehaviour
from enums.LeavePointReason import LeavePointReason

import xdbload
define("xdb", default=1, help="load xdb tables: heroes, talents etc.", type=int)

from party_const import FRACTION, FRACTION_LIST

##----------------------------------------------------------------------------------------------------------------------
from geolocation import GeoLocator
from geo_cfg import DEFAULT_GEO_LOCATION

##----------------------------------------------------------------------------------------------------------------------
## Thrift
from thrift_handler import ThriftHandler
#print "os.cwd:", os.getcwd()
from thrift_pw.account_management.acc_management_ws_handler import AccountManagementServerHandler
addModPath('thrift_pw/statistics/gen-py')
from StatisticCore.ttypes import RatingType
from StatisticCore.ttypes import TalentInfo
from StatisticCore.ttypes import RuneRollSource
from StatisticCore.ttypes import ResourceChangeItem


LOGIN_TOKEN_CHECK_TIME = 60
LOGIN_TOKEN_EXPIRE_TIME = 60*60*3
PEERS_LOG_PERIOD = 10  # seconds

IN_CASTLE_TIMEOUT = 30  # если клиент порядка минуты не присылал keepalive, считается "не очень-то живым"

MAX_WS_USERS = 1500  # по умолчанию разрешаем не более 1.5K юзеров на WS (конфиг координатора может оверрайдить это значение)
USERS_UPDATE_PER_TICK = 32  # скольки пользователям за 1 тик рассылать апдейт конфига
GUILD_WAR_EVENT_CHECK_PERIOD = 5  # каждые N секунд читаем из монги данные по ивенту
# -------------------------------------------------------------------------------------------------------
# -------------------------------------------------------------------------------------------------------
# -------------------------------------------------------------------------------------------------------

class PwWorkServer(ICSVActionTimingWriter, ISocialExchangeUser, WorkServer):

    ##_Interfaces = dict( SUBADDR=None, WS=None, MC=None, SQL=None, DATA=None, HTTP=None, PVX=None, AGG=None, ZZ=None, MD=None )

    _SPECIFIC_CONFIG_PARAMS = {
        "pvx_login": "PVX_LOGIN_ADDRESS",
        "zz_addr": "ZZIMA_WSDL",
        "zz_svc_name": "ZZIMA_SERVICE_NAME",
        "zz_pay_sys": "ZZIMA_PAYMENT_SYSTEM",
        "zz_steam_pay_sys": "ZZIMA_STEAM_PAYMENT_SYSTEM",
        "zz_aeria_pay_sys": "ZZIMA_AERIA_PAYMENT_SYSTEM",
        "zz_arcgames_pay_sys": "ZZIMA_ARCGAMES_PAYMENT_SYSTEM",
        "zz_zzima_pay_sys": "ZZIMA_ZZIMACOM_PAYMENT_SYSTEM",
        "agg_bill_prefix": "AGG_BILLING_PREFIX",
        "zz_api": "ZZIMA_API_URL",
        "zz_key": "ZZIMA_API_KEY",
        "zz_sec": "ZZIMA_API_SECRET",
        "soc_agg": "SOCIAL_AGGREGATOR_ADDRESS",
        "pers_serv": "PERSON_SERVER_ADDRESS",
        "friends_svc": "FRIEND_SERVICES",
        "party_svc": "PARTY_SERVICES",
        "guilds_svc": "GUILD_SERVICES",
        "chat_serv": "CHAT_SERVICES",
        "stats_agent": "STATS_AGENT_URL",
        "stats": "STATS_SERVER_URL",
        "fb_restrict": "RESTRICT_FACEBOOK_USERS",
        "loc_restrict": "RESTRICT_LOCATIONS",
        "loc_allowed": "RESTRICT_LOCATIONS_ALLOWED",
        "can_reconnect": "PVX_CAN_RECONNECT",
        "balancer_ext": "BALANCER_EXTERNAL",
        "balancer_int": "BALANCER_INTERNAL",
        "bill_chk_period": "BILLING_CHECK_BALANCE_PERIOD",
        "pwc_activ_term": "PWC_ACTIVATION_TERM",
        "pwc_retry_term": "PWC_RETRY_CONFIRM_PERIOD",
        "pwc_reset_term": "PWC_RESET_PWD_PERIOD",
        "pwc_info_url": "PWC_INFO_URL",
        "pvx_locs": "MATCHMAKER_LOCALES",
        "pvx_def_loc": "MATCHMAKER_DEFAULT_LOCALE",
        "curl_wrk": "HTTP_CURL_WORKERS",
        "curl_conn": "HTTP_CURL_CONNECTIONS",
        "bill_trd": "ZZIMA_BILLING_THREADS",
        "sql_trd": "SQL_THREADS",
        "mc_trd": "MEMCACHE_THREADS",
        "mongo_trd": "MONGO_THREADS",
        "smtp_trd": "PWC_SMTP_THREADS",
        "serial_trd": "SERIAL_MODEL_DATA_THREADS",
        "mm_valid_sec": "MM_VALIDATION_SECONDS",
        "mm_gateway_fails": "MM_MAX_INDIVIDUAL_GATEWAY_FAILS",
        "sex_url": "SOCIAL_EXCHANGE_URL",
        "mirror_cfg": "MIRROR_QUEUE_CONFIG",
        "mirror_trd": "MIRROR_QUEUE_THREADS",
        "export_cfg": "MIRROR_EXPORT_CONFIG",
        "export_trd": "MIRROR_EXPORT_THREADS",
        "events": "EVENT_SERVICES",
        "sign_check": "STRICT_SIGN_CHECK",
        "client_revs": "CLIENT_REVISIONS",
        "steam_appid": "STEAM_APPID",
        "steam_appkey": "STEAM_APPKEY",
        "steam_url": "STEAM_URL",
        "steam_sandbox_mode": "STEAM_SANDBOX_MODE",
        "steam_billing_base": "STEAM_BILLING_BASE",
        "steam_billing_offset": "STEAM_BILLING_OFFSET",
        "steam_payments_url": "STEAM_PAYMENTS_URL",
        "steam_payments_secret": "STEAM_PAYMENTS_SECRET",
        "aeria_payments_url": "AERIA_PAYMENTS_URL",
        "aeria_payments_secret": "AERIA_PAYMENTS_SECRET",
        "arcgames_payments_url": "ARCGAMES_PAYMENTS_URL",
        "arcgames_payments_secret": "ARCGAMES_PAYMENTS_SECRET",
        "zzima_payments_url": "ZZIMA_PAYMENTS_URL",
        "zzima_payments_secret": "ZZIMA_PAYMENTS_SECRET",

        "skip_limit_check" : "SKIP_LIMIT_CHECK",
        "dlcs_info": "DLCs_INFO",
        "muid_to_dlcs": "MUID_TO_DLCS",
        "deploy_name": "DEPLOY_NAME",
        "aeria_is_test": "AERIA_IS_TEST",
        "aeria_url": "AERIA_URL",
        "aeria_appid": "AERIA_APPID",
        "aeria_appkey": "AERIA_KEY",
        "arcgames_is_test": "ARCGAMES_IS_TEST",
        "arcgames_url": "ARCGAMES_URL",
        "arcgames_appid": "ARCGAMES_APPID",
        "arcgames_appabbr": "ARCGAMES_APPABBR",
        "arcgames_appkey": "ARCGAMES_KEY",
        "arcgames_billing_url": "ARCGAMES_BILLING_URL",
        "arcgames_zoneid": "ARCGAMES_ZONEID",
        "zzimacom_is_test": "ZZIMACOM_IS_TEST",
        "zzimacom_url": "ZZIMACOM_URL",
        "zzimacom_service_name": "ZZIMACOM_SERVICE_NAME",
        "zzimacom_payment_system": "ZZIMACOM_PAYMENT_SYSTEM",
        "tournament_server": "TOURNAMENT_SERVER",
        "tournament_server_addr": "TOURNAMENT_SERVER_ADDR",
        "tournament_xserver_addr": "TOURNAMENT_XSERVER_ADDR",
        "billing_reserve_enabled" : "BILLING_RESERVE_ENABLED",
        "tournament_spectator_auids": "TOURNAMENT_SPECTATOR_AUIDS",
        "tournament_apply_results": "TOURNAMENT_APPLY_RESULTS",
        "geo_data_path": "GEO_DATA_PATH",
        "billing_merge_disable_ps": "BILLING_MERGE_DISABLED_PS",
        "redis_config": "REDIS_CONFIG",
        "meta_muids": "META_MUIDS",
        "mm_msv_locale": "MATCHMAKER_MSV_LOCALE",
        "mm_msv_geolocation": "MATCHMAKER_MSV_GEOLOCATION",
    }

    # обработчики секций pvx matchmaking reply
    mmActions = {
        "add": "onMmSessionAdd",
        "spectate": "onMmSessionAdd",
        "ping": "onMmSessionProgress",
        "accept": "onMmSessionAccept",
        "cancel": "onMmSessionCancel",
        "server_status": "onMmServerStatus",
    }

    MM_SUBKEY_ORDER = [ "cancel", "close", "party_cancel", "leave", "reconnect", "add", "spectate", "accept", "ready", "change_hero", "ping", "server_status" ]

    mailActions = {
        # тип почтового сообщения - строка не более 15 символов!
        "async_mail_test" : AsyncMailAction,
        "session_awards"  : SessionAwardsMailAction,
        "forge_roll"      : ForgeRollMailAction,
        "invite_friend"   : InviteFriendMailAction,
        "invite_guild"    : InviteGuildMailAction,
        "del_all_gltals"  : DeleteAllGuildTalentsMailAction,
        "add_gltal"       : AddGuildTalentMailAction,
        "del_gltal"       : DeleteGuildTalentMailAction,
        "ticket_info"     : TicketInfoMailAction,
        "destr_guild"     : DestroyGuildMailAction,
        "add_glbuf"       : AddGuildBufMailAction,
        "del_all_glbufs"  : DeleteAllGuildBufsMailAction,
        "drop_guildapp"   : RemoveGuildApplicationMailAction,
        "recruit_rejected": RecruitApplicationRejectedMailAction,
        "add_mute"        : AddMuteAction,
    }

    # -----------------------------------------------
    def __init__(self, **kwargs):
        # inherited
        WorkServer.__init__(self, **kwargs)

        info( "PW __init__" )
        info( "mailActions: %s" % self.mailActions )


        curTime = datetime.datetime.utcnow()
        self.lastDay = curTime.day
        self.needRecalc = False

        self.MM_PING_PERIOD = MM.PING_PERIOD
        self.MM_MIN_ADD_PERIOD = MM.MIN_ADD_PERIOD
        self.MM_MAX_ADD_PERIOD = MM.MAX_ADD_PERIOD
        self.MM_VALID_TIMEOUT = MM.VALID_TIMEOUT

        self.MM_VALIDATION_SECONDS = cfg.MM_VALIDATION_SECONDS
        self.MM_MAX_INDIVIDUAL_GATEWAY_FAILS = cfg.MM_MAX_INDIVIDUAL_GATEWAY_FAILS

        # по этим счетчикам будем учитывать доставленные/недоставленные за период пакеты
        self.mmPassed = IncDict()
        self.mmFailed = IncDict()
        self.mmRetryPackets = {}

        self.mmFailedByGate = IncDict() # здесь будем держать счетчики фейлов по каждому уникальному gateway
        self.mmOfflineGateways = {} # здесь будем держать только адреса gateways, которые последнее время не отвечают на запросы (по превышению счетчика mmFailedByGate[gate_addr])

        self.MM_SERVER_STATUS_PERIOD = MM.SERVER_STATUS_PERIOD
        self.tsLastMmStatus = time.time()
        self.tsLastMmKeyStats = time.time()
        self.nextPeersLog = 0

        self.resetMatchmakingPackets()
        self.resetMmServerStatus()

        # по этим счетчикам будем учитывать объем и кол-во ключей в мм-пакетах (отдельно пинги, отдельно accept и т.п.)
        self.mmKeyStats = IncDict()

        self.POLLING_PING_TIMEOUT = POLLING_PING_TIMEOUT
        self.IN_CASTLE_TIMEOUT = IN_CASTLE_TIMEOUT

        self.MAX_USERS = MAX_WS_USERS  # по умолчанию разрешаем не более 1.5K юзеров на WS (конфиг координатора может оверрайдить это значение)

        self.loginCache = {}
        self.loginCacheExpireTime = time.time()

        self.xTouchStamp = time.time()

        self.debugTimings = {}

        self.guildBonusProcessor = GuildBonusProcessor(self)
        self.CCU["session_awards"] = 0

        self.accsToUpadte = {"config": set(), "quests": set()}

        self.tutorialGameAwards = {}
        # In "toRevert" store tuples: (False, event) if just revert, (True, event) if revert and store in finished
        self.operatorEvents = {"activeEvents": {}, "pendingEvents": {}, "toRevert": {}, "finishedEvents": {}, "disabledEvents": {}}
        self.needUpdateSeeds = False
        self.calcTopBuildsData = False
        self.calcTopBuildLock = False
        self.sendFriendsTime = int(time.time()) + self.I.Config.getMainConfig().KEEPALIVE_TIMEOUT

        self.nextGuildWarEventUpdateTime = int(time.time()) + GUILD_WAR_EVENT_CHECK_PERIOD + self.I.Config.getMainConfig().KEEPALIVE_TIMEOUT

    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf ):
        # заводим файл-маркер того, что мы живы
        curDir = os.getcwd()
        global MARKER_FILENAME
        MARKER_FILENAME = curDir + "/logs/ws.running.%s" % options.server_name
        success("creating marker file %r" % MARKER_FILENAME)
        f = open( MARKER_FILENAME, "w" )
        f.close()

        # связываемся с координатором и заводим базовые кластерные интерфейсы:
        iDict = WorkServer.initInterfaces( classOf )

        request_limit = getattr(cfg, "HTTP_REQUEST_LIMIT", 1000)
        info("using http request_limit=%s" % request_limit)

        # заводим game-specific интерфейсы:""
        iDict.PVX = IfaceFactory.makePvxMmInterface( options.pvx, HTTP=iDict.HTTP )
        info( "PVX interface: " + str(iDict.PVX) )

        iDict.AGG = IfaceFactory.makeSocAggInterface( options.soc_agg, cfg.SOCIAL_AGGREGATOR_ADDRESS, SOCAGG_VERSION, \
            HTTP=iDict.HTTP )
        info( "soc.AGG interface: " + str(iDict.AGG) )

        iDict.ZZ = IfaceFactory.makeZZimaInterface( options.zzima, cfg.ZZIMA_WSDL, HTTP=iDict.HTTP, \
            service_name=cfg.ZZIMA_SERVICE_NAME, payment_system=cfg.ZZIMA_PAYMENT_SYSTEM, num_threads=cfg.ZZIMA_BILLING_THREADS, syncWait=120.0 )
        info( "ZZ interface: " + str(iDict.ZZ) )

        iDict.MD = PwNewModelManager( ifaceDict=iDict )
        info( "MD interface: " + str(iDict.MD) )

        iDict.STATS = IfaceFactory.makeIStatsInterface(options.stats, cfg.STATS_AGENT_URL, iDict, cfg.STATS_RESEND_POOL_LIMIT)
        info( "Statistics interface: " + str(iDict.STATS) )

        iDict.EXPORT = IfaceFactory.makeExportInterface( options.export, cfg.MIRROR_EXPORT_CONFIG, num_threads=cfg.MIRROR_EXPORT_THREADS )
        info( "Mirrored data interface: " + str(iDict.EXPORT) )

        iDict.FRIENDS = ifriendservice.IHttpFriendService( addresses=cfg.FRIEND_SERVICES, HTTP=iDict.HTTP, request_limit=request_limit )
        iDict.PARTY = ipartyservice.IHttpPartyService( addresses=cfg.PARTY_SERVICES, HTTP=iDict.HTTP, request_limit=request_limit )
        iDict.PS = IfaceFactory.makePersonServerInterface( options.pers, cfg.PERSON_SERVER_ADDRESS, HTTP=iDict.HTTP, FRIENDS=iDict.FRIENDS, PARTY=iDict.PARTY )
        info( "PersonServer interface: " + str(iDict.PS) )

        iDict.GS = IfaceFactory.makeGuildServiceInterface(options.guilds, cfg.GUILD_SERVICES, HTTP=iDict.HTTP, request_limit=request_limit)
        info( "GuildService interface: " + str(iDict.PS) )

        iDict.WSX = IfaceFactory.makeIPeerWebServerInterface( options.wsx, HTTP=iDict.HTTP, request_limit=request_limit)
        info( "Peer WSX interface: " + str(iDict.WSX) )

        iDict.SEX = IfaceFactory.makeSocialExchangeInterface( options.sex, iDict.HTTP, cfg.SOCIAL_EXCHANGE_URL, options.server_addr, request_limit=request_limit )
        info( "Social Exchange interface: " + str(iDict.SEX) )

        iDict.Config = loadMultiConfig()

        iDict.BILL = IfaceFactory.makeBillingInterface( options.billing, iDict )
        info( "BILL interface: " + str(iDict.BILL) )

        iDict.CHAT = IfaceFactory.makeIChatServerInterface( options.chat, cfg.CHAT_SERVICES, HTTP=iDict.HTTP, request_limit=request_limit )
        info( "CHAT interface: " + str(iDict.CHAT) )

        iDict.MIRROR = IfaceFactory.makeMirrorInterface( options.mirror, cfg.MIRROR_QUEUE_CONFIG, num_threads=cfg.MIRROR_QUEUE_THREADS )
        info( "Mirror interface: " + str(iDict.MIRROR) )

        iDict.STEAM = isteam.IRealSteam(cfg.STEAM_APPID, cfg.STEAM_APPKEY, cfg.STEAM_URL, cfg.STEAM_SANDBOX_MODE, iDict.HTTP, iDict.DATA, cfg.STEAM_BILLING_BASE, cfg.STEAM_BILLING_OFFSET)
        iDict.STEAM_PS = IfaceFactory.makeSteamPaymentsInterface( 'real', iDict.HTTP, cfg.STEAM_PAYMENTS_URL, cfg.STEAM_PAYMENTS_SECRET )

        iDict.AERIA = iaeria.IRealAeria(cfg.AERIA_APPID, cfg.AERIA_KEY, cfg.AERIA_URL, cfg.AERIA_IS_TEST, iDict.HTTP, iDict.AGG, request_limit=request_limit)
        iDict.AERIA_PS = IfaceFactory.makeAeriaPaymentsInterface( 'real', iDict.HTTP, cfg.AERIA_PAYMENTS_URL, cfg.AERIA_PAYMENTS_SECRET )

        iDict.ARCGAMES = iarcgames.IRealArcGames(cfg.ARCGAMES_APPID, cfg.ARCGAMES_APPABBR, cfg.ARCGAMES_KEY, cfg.ARCGAMES_URL, cfg.ARCGAMES_BILLING_URL, cfg.ARCGAMES_ZONEID, cfg.ARCGAMES_IS_TEST, iDict.HTTP, iDict.AGG)
        iDict.ARCGAMES_PS = IfaceFactory.makeArcGamesPaymentsInterface( 'real', iDict.HTTP, cfg.ARCGAMES_PAYMENTS_URL, cfg.ARCGAMES_PAYMENTS_SECRET )

        iDict.ZZIMA = izzimacom.IRealIZZimacom(cfg.ZZIMACOM_SERVICE_NAME, cfg.ZZIMACOM_PAYMENT_SYSTEM, cfg.ZZIMACOM_URL, cfg.ZZIMACOM_IS_TEST, iDict.HTTP, iDict.AGG)
        iDict.ZZIMA_PS = IfaceFactory.makeZZimacomPaymentsInterface( 'real', iDict.HTTP, cfg.ZZIMA_PAYMENTS_URL, cfg.ZZIMA_PAYMENTS_SECRET )


        iDict.REDIS = tornadoredis.Client( io_loop=tornado.ioloop.IOLoop.instance(), host=cfg.REDIS_CONFIG["redis_addr"], port=cfg.REDIS_CONFIG["redis_port"], selected_db=cfg.REDIS_CONFIG["redis_base"])
        iDict.REDIS.connect()

        if options.xdb: #!!! а бывает ли это условие False ?
            info("Loading XML heroes/talents...")
            t1 = time.time()
            iDict.SD = MultiStaticData(options.xdb_path + "/ExportedSocialData.xml", iDict.Config.getMainConfig())
            t2 = time.time()
            info("main StaticData loaded(%.3f sec), sections count %d" % (t2-t1, len(iDict.SD.getMainSD().data)))

            try:
                iDict.Config.mainConfig.applyOverrides(iDict.SD.getMainSD())
                iDict.Config.applyLocaleOverrides(iDict.SD)
                # Заполним статические поля, которые можно перезаписыать из GMTools
                iDict.Config.fillStaticDataDependendValues(iDict.SD)
            except:
                catch()

        iDict.GEO = GeoLocator(cfg.GEO_DATA_PATH)

        iDict.SMODEL = IfaceFactory.makeSerialModelInterface(options.smodel, iDict, PWSOC_VERSION, load_conversion_xml=True, num_threads=cfg.SERIAL_MODEL_DATA_THREADS)

        return iDict

    # -----------------------------------------------
    def resetMmServerStatus(self):
        self.mmServerStatus = ClassDict(
            accept_timeout=MM.PVX_ACCEPT_TIMEOUT,
            average_mm_time=MM.PVX_AVERAGE_MM_TIME,
            average_mm_time_ext={},
            can_reconnect=cfg.PVX_CAN_RECONNECT,
            reconnect_timeout=MM.PVX_RECONNECT_TIMEOUT,
            network_delay=MM.PVX_NETWORK_DELAY,
            guard_lobby_timeout=MM.PVX_GUARD_LOBBY_TIMEOUT,
            party_accept_timeout=party_const.PARTY_INVITE_TIMEOUT,
        )
        self.mmDebugStatus = {}


    # -----------------------------------------------
    _THRIFT_SERVICES = {
        "account_management": AccountManagementServerHandler,
    }

    # -----------------------------------------------
    def initHandlers(self, application):
        ## ---------- base: --------------
        application.add_handlers( r"(.*)", [
            ( r"/", PwJsonHandler, dict(SUBADDR=SUBADDR_BALANCED, I=self.I) ),
            ( r"/x", PwJsonHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I) ),
            ( r"/%s" % options.server_name, PwJsonHandler, dict(SUBADDR=SUBADDR_SELF, I=self.I) ),
            ( r"/sex", SocialExchangeJsonHandler, dict(SUBADDR=SUBADDR_BALANCED, I=self.I) ),

            ( r"/thrift", ThriftHandler, dict(I=self.I, SERVICES=self._THRIFT_SERVICES ) ),
        ] )

        # после получения глобальных флагов от координатора, надо обновить mm-статус
        self.resetMmServerStatus()

        # служебные хэндлеры, типа login/logout
        self.initServiceActions()

        ## ---------- specific: --------------
        PwJsonHandler.unloggedActionMap['sn_login'] = SocAggLoginAction
        PwJsonHandler.unloggedActionMap['alien_login'] = AlienLoginAction
        PwJsonHandler.unloggedActionMap['pguest_login'] = PersistentGuestLoginAction
        PwJsonHandler.unloggedActionMap['l_who'] = WhoAction
        PwJsonHandler.unloggedActionMap['l_set_gender'] = SetSteamGenderAction
        PwJsonHandler.unloggedActionMap['l_login'] = LauncherLoginAction
        PwJsonHandler.unloggedActionMap['l_join'] = JoinAction
        PwJsonHandler.unloggedActionMap['l_ping'] = LauncherPingAction
        PwJsonHandler.unloggedActionMap['l_merge'] = LauncherMergeAction
        PwJsonHandler.unloggedActionMap['l_start'] = LauncherStartAction
        PwJsonHandler.unloggedActionMap['l_events'] = LauncherEventsAction
        PwJsonHandler.unloggedActionMap['l_stat'] = LauncherDActions
        PwJsonHandler.unloggedActionMap['check_for_spectator'] = CheckForSpectatorAction
        PwJsonHandler.unloggedActionMap['get_full_user_account'] = GetFullUserAccountAction
        PwJsonHandler.unloggedActionMap['get_account_data'] = GetAccountDataAction
        PwJsonHandler.unloggedActionMap['accept_recruit'] = AcceptRecruitAction
        PwJsonHandler.unloggedActionMap['logout_old_user'] = LogoutOldUserAction

        if cfg.TOURNAMENT_SERVER:
            PwJsonHandler.unloggedActionMap['create_account'] = CreateAccountAction

        #PwJsonHandler.unloggedActionMap['pwc_who'] = PWConnectWhoAction
        #PwJsonHandler.unloggedActionMap['pwc_login'] = PWConnectLoginAction
        PwJsonHandler.unloggedActionMap['pwc_confirm'] = PWConfirmAction
        PwJsonHandler.unloggedActionMap['pwc_confirm_pretty'] = PWConfirmRedirectAction
        PwJsonHandler.unloggedActionMap['pwc_get_info'] = PWGetInfoAction
        PwJsonHandler.unloggedActionMap['pwc_load_info'] = PWConnectLoadAction
        PwJsonHandler.unloggedActionMap['pwc_change_pwd_link'] = PWChangePasswordLinkActionExt

        SocialExchangeJsonHandler.unloggedActionMap['sex_send'] = ExchangeSendAction

        ## ---------- ext: --------------
        # грузим классы расширений для "пользовательских action" из модуля /ext_pw/
        self.loadExtActions(PwJsonHandler, ext_pw)
        # грузим логику
        self.loadExtActions(PwJsonHandler, logic.all)

        # Получаем список динамических квестов
        self.I.DATA.find(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA, {"key": {"$exists": True}}, params=None, callback=self.onGetDynamicQuestList)
        # Получаем список ивентов
        self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA, {"_id": {"$exists": True}}, params=None, callback=self.onGetEventsList)

        # Получаем данные последнего кланового ивента
        #if not self.get("GuildWarEventData"):
        #    self.updateGuildWarEventData()

        # Выцепим информацию о топовом билде, если нам его по какой-то причине не прислали
        if not self.get("TopBuildsData"):
            name, server = getFirstSortedPair( coord_cfg.COORDINATOR_WS_SERVERS )
            if name and server and options.server_name == name:
                self.updateTopBuilds()

        # готовы слушать; рапортуем координатору (и получаем в ответ список WS peers)
        self.getPeersFromCoordinator()

    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_class = "ws"
        else:
            options["server_class"].set("ws")

    # -------------------------------------------------------------------------
    def onGetDynamicQuestList(self, response):
        info("onGetDynamicQuestList: Response = %r", response)
        if response and response["r"] is not None:
            for obj in response["r"]:
                try:
                    # Если квест не активен, не загружаем его в StaticData.
                    if "removed" in obj and obj["removed"]:
                        continue

                    questInfo = json_loads(obj["data"])
                    if "QuestEndTime" in questInfo and (int(questInfo["QuestEndTime"]) == 0 or
                                                        int(questInfo["QuestEndTime"]) > int(time.time())):
                        if self.I.SD.hasSDForLocale(obj["locale"]) and DynamicQuest.validateJsonQuest(questInfo)[0]:
                            localSD = self.I.SD.getSD(obj["locale"])
                            localSD.DynamicQuests[obj["key"]] = {"questData": questInfo, "version": obj["version"],
                                                                 "pullId": 0}
                            # При старте сервера можем себе позволить проставить ауиды по ходу зазрузки
                            if "AuidList" in questInfo["AcceptFilter"] and int(questInfo["AcceptFilter"]["AuidList"]) != 0:
                                self.I.DATA.find_one(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA,
                                                     {"auidsKey": int(questInfo["AcceptFilter"]["AuidList"])},
                                                     params=None, callback=functools.partial(self.onGetAuidsListForQuest,
                                                     questId=obj["key"], locale=obj["locale"]))
                except Exception:
                    catch()
            # Квесты загружены, получаем список пулов динамических квестов
            self.I.DATA.find(CC.DYNAMIC_QUESTS_DATA, CC.DYNAMIC_QUESTS_DATA, {"pullKey": {"$exists": True}}, params=None, callback=self.onGetDynamicQuestPullsList)

    def onGetAuidsListForQuest(self, response, questId=0, locale=""):
        if response and "r" in response:
            localSD = self.I.SD.getSD(locale)
            if questId in localSD.DynamicQuests:
                try:
                    localSD.DynamicQuests[questId]["questData"]["AcceptFilter"]["ForAuids"] = response["r"]["auids"]
                except:
                    catch()

    def onGetDynamicQuestPullsList(self, response):
        info("onGetDynamicQuestPullsList: Response = %r", response)
        if response and response["r"] is not None:
            for obj in response["r"]:
                try:
                    questPull = obj["pullData"]
                    if self.I.SD.hasSDForLocale(questPull["locale"]):
                        localSD = self.I.SD.getSD(questPull["locale"])
                        localSD.DynamicQuestPulls[obj["pullKey"]] = {"startTime": questPull["startTime"],
                                                                     "endTime": questPull["endTime"],
                                                                     "hasRotation": questPull["hasRotation"],
                                                                     "quests": obj["quests"],
                                                                     "isActive": questPull["isActive"]}
                        # Надо проставить id квестам, которые были добавлены в пулл
                        for questId in obj["quests"]:
                            if questId in localSD.DynamicQuests:
                                localSD.DynamicQuests[questId]["pullId"] = obj["pullKey"]
                                debug("pullId %d was set for quest %d", obj["pullKey"], questId)
                except Exception:
                    catch()

    def onGetEventsList(self, response):
        info("onGetEventsList: response = %r", response)
        if response and response["r"] is not None:
            for obj in response["r"]:
                try:
                    event = {"endTime": obj["endTime"], "persistentId": obj["_id"],
                             "startTime": obj["startTime"],
                             "enabled": obj["enabled"], "type": obj["type"],
                             "newValue": obj["customData"], "defaultValue": {}}
                    self.I.Config.setEventDefalutValue(self.I.SD, event)
                    # Если событие выключено, используем disabled группу
                    if not event["enabled"]:
                        self.operatorEvents["disabledEvents"][obj["_id"]] = event
                    # Если событие ещё не активно, используем pending группу
                    elif event["startTime"] > int(time.time()):
                        self.operatorEvents["pendingEvents"][obj["_id"]] = event
                    elif event["startTime"] < int(time.time()) < event["endTime"]:
                        changes, self.needUpdateSeeds = self.I.Config.applyEvent(self.I.SD, event)
                        self.operatorEvents["activeEvents"][obj["_id"]] = event
                    else:
                        self.operatorEvents["finishedEvents"][obj["_id"]] = event
                except Exception:
                    catch()
            info("operatorEvents = %r", self.operatorEvents)

    # -------------------------------------------------------------------------
    # OVERRIDE
    def onGetPeerServer(self, peer, peer_name, peer_id, status):
        if status == PEER_DELETED:
            return
        if peer_id:
            self.peers[peer_id] = ClassDict(peer, name=peer_name)
        if peer.get("on") and (peer_name == options.server_name):
            # у координатора может поменяться настройка "максимального числа юзеров" для нашего сервера
            new_max = peer.get("max_users")
            if new_max and new_max != self.MAX_USERS:
                self.MAX_USERS = new_max
                info("onGetPeerServer: new MAX_USERS=%s", new_max)
        if time.time() > self.nextPeersLog:
            info("peers now: %s", self.peers)
            self.nextPeersLog = time.time() + PEERS_LOG_PERIOD

    # -------------------------------------------------------------------------
    def loadAction(self, RequestHandlerClassOf, ext_module, k):
        try:
            handlerClass = getattr(ext_module, k)
            action = handlerClass.action
            start = handlerClass.onStart
            info( "-- mapping from module %r: ext action[%r] = class %r (onStart = %s)" % ( str(ext_module.__name__), str(action), str(handlerClass), str(start) ) )
            RequestHandlerClassOf.loggedActionMap[ action ] = handlerClass
        except:
            catch()
            err( "FAILED to parse Action class %r" % k )
    # -------------------------------------------------------------------------
    def loadExtActions(self, RequestHandlerClassOf, ext_module):
        for k in ext_module.__all__:
            self.loadAction(RequestHandlerClassOf, ext_module, k)

    def toggleMaintenance(self, mode, tm):
        WorkServer.toggleMaintenance(self, mode, tm)

    # -----------------------------------------------
    def tick(self):
        info( "!pw tick" )
        t0 = time.time()
        # inherited
        WorkServer.tick(self)

        # --- game-specific: тик PVX-матчмейкера + отошлем периодический запрос для PvX-сервера
        if not self.wsShutdown:
            if self.accsToUpadte["config"] or self.accsToUpadte["quests"]:
                self.updateSomeAccs()

            if self.I.PVX:
                self.I.PVX.stepSessions()
            self.pingMatchmaking()

            if self.I.STATS:
                ts0 = time.clock()
                try:
                    self.I.STATS.Send()
                except:
                    catch()
                info( "STATS.Send time: %.3f" % (time.clock()-ts0) )
            try:
                self.tickEvents()
            except Exception:
                catch()

            if self.sendFriendsTime < time.time():
                self.tickFriends()
                self.sendFriendsTime += self.I.Config.getMainConfig().KEEPALIVE_TIMEOUT

            curTime = datetime.datetime.utcnow()
            if curTime.day != self.lastDay:
                self.lastDay = curTime.day
                self.needRecalc = True

            if self.needRecalc:
                self.I.SD.validateDynamicQuests()
                name, server = getFirstSortedPair( coord_cfg.COORDINATOR_WS_SERVERS )
                if name and server and options.server_name == name:
                    self.recalcAllGuilds()
                    # Топовый билд обновляем только на одном из серверов, потом разошлём остальным
                    self.updateTopBuilds()
                    self.updateGuildWarEventData()
                    self.removeOutOfDateRecruitApplications()
                self.needRecalc = False

            if self.calcTopBuildsData:
                self.calcTopBuildsData = False
                self.updateTopBuilds()

            if self.nextGuildWarEventUpdateTime < time.time():
                self.updateGuildWarEventData()
                self.nextGuildWarEventUpdateTime = time.time() + GUILD_WAR_EVENT_CHECK_PERIOD

            ########DEBUG: грохнуть сервер спустя N секунд после запуска
            #~ if (not self.wsShutdown) and (self.tickCount > 10):
                #~ self.sig_handler(-1, -1)
            ########DEBUG

            t1 = time.time()
            if t1-t0 > 0.001:
                info( "~pw tick: %.3f sec" % (t1-t0) )
            else:
                info( "~pw tick" )

            ########DEBUG: давайте навсегда зациклимся (посмотрим, сработает ли blocking alarm)
            #~ if t1 - self.startTickTime > 20:
                #~ info("Tesning alarm....")
                #~ if hasattr(signal, "getitimer"):
                    #~ info("getitimer: %s" % str(signal.getitimer(signal.ITIMER_REAL)) )
                #~ while True:
                    #~ pass
                #~ info( "~~pw tick" )
            ########DEBUG

            if t1 > self.loginCacheExpireTime:
                self.updateLoginTokens(t1)
                self.loginCacheExpireTime = t1 + LOGIN_TOKEN_CHECK_TIME
                # заодно давайте раз в минуту дампить debug-инфу по таймингам
                self.dumpDebugTimings()

            now_second = toint(t1)
            if now_second > self.xTouchStamp + CC.SEX_KEEPALIVE_CHECK_PERIOD:
                self.xTouchStamp = now_second
                for uid, acc in users.iteritems():
                    last_touch = toint(acc.sex_touch)
                    if last_touch + CC.SEX_KEEPALIVE_PERIOD < now_second:
                        acc.sex_touch = now_second
                        if acc.sex_sid:
                            self.I.SEX.touch( acc.auid, acc.sex_sid, acc.sex_server )
                        else:
                            # для случаев, когда на старте залогиниться в exchange не смогли, потом периодически делаем retry login
                            callback = functools.partial( self.onSocialExchangeLogin, acc=acc )
                            self.I.SEX.login( acc.auid, CC.SEX_PW_PROJECT, callback )



    # -----------------------------------------------
    # VIRTUAL: OVERRIDE чтобы отработать кастомную логику logoff
    def onUserLogout(self, acc):
        if acc.auid:
            self.I.PS.unsubscribe( acc.auid, options.server_id, self.onDummyResponseCallback )
            self.I.GS.unsubscribe( acc, options.server_id, self.onDummyResponseCallback )
            #DAN: в качестве эксперимента совсем убираю прибивание токена на логауте (чтобы ланчер не фейлил повторный sn_login:pw после выхода из клиента)
            # (альтернативное решение - ланчер должен ВСЕГДА делать l_who перед sn_login, в т.ч. после выхода из клиента в ланчер)
            ## if acc.ka == 0:  # intentional logout
                ## self.deleteLoginToken(acc.auid)
            self.I.BILL.releaseBilling(acc.auid)
            if acc.chat:
                self.I.CHAT.removeUser(acc.chat['host'], acc.auid, self.onDummyResponseCallback)
            if acc.sex_sid:
                callback = functools.partial( self.onSocialExchangeLogout, auid=acc.auid )
                self.I.SEX.logout( acc.auid, acc.sex_sid, acc.sex_server, callback )

    def onBeforeFinalDataSave( self, acc ):
        info("onBeforeFinalDataSave: auid=%s", acc.auid)
        if acc.model and isinstance(acc.model, ModelData):
            oldLastLogoutTime = acc.model.LordInfo.LastLogoutTime
            acc.model.LordInfo.LastLogoutTime = int( round( time.time() ) )
            if acc.model.AdminMessages:
                _id = sorted(acc.model.AdminMessages.iteritems(), key=lambda x: x[1].SentTime)[0][0]
                info("SendMessageToUser: id = %r", _id)
                if acc.model.LordInfo.LastLogoutTime > acc.model.AdminMessages[_id].SentTime >= oldLastLogoutTime:
                    acc.model.AdminMessages[_id].SentTime = acc.model.LordInfo.LastLogoutTime + CC.ADMINMESSAGE_TIMEOUT

    def onSocialExchangeLogout(self, response, auid=None):
        info("onSocialExchangeLogout: auid=%s, response %s", auid, response)

    # -----------------------------------------------
    def onDummyHttpCallback(self, http_reply):
        try:
            pass
            #info("onDummyHttpCallback http body: %r" % http_reply.body)
        except:
            warn("bad onDummyHttpCallback http reply: %r" % http_reply)

    def onDummyResponseCallback(self, response):
        debug("onDummyResponseCallback: response %r", response)
        pass


    def onGuildCallback(self, response, acc):
        if response:
            debug("onGuildCallback response: %s", PostponeStr(self.I.MD.pretty, response))
            if acc:
                GuildData_changes = response.get("GuildData") or []
                SiegeData_changes = response.get("SiegeData") or []
                if GuildData_changes:
                    try:
                        ModelChangeApplicator.apply( acc, "guilddata", GuildData, GuildData_changes )
                    except:
                        catch()
                if SiegeData_changes:
                    try:
                        ModelChangeApplicator.apply( acc, "siegedata", SiegeData, SiegeData_changes )
                    except:
                        catch()
                acc.pending_events.append( {"GuildData": { "GuildData": GuildData_changes }} )
                acc.pending_events.append( {"SiegeData": { "SiegeData": SiegeData_changes }} )
                if acc.pending_handler:
                    acc.pending_handler()
            else:
                warn("onGuildCallback: no acc found for guild data updates")


    def onPartyCmdCallback(self, response, uid=None, args={}):
        if response:
            ## info( "onPartyCmdCallback response: %s" % self.I.MD.pretty(response) )
            party_events = response.get("party_events")

            init = response.get("init")
            if party_events and isinstance(party_events, list):
                for party_event in party_events:
                    to_uid = party_event.pop("to_uid")
                    if to_uid:
                        acc = users.get(to_uid)
                        if acc:
                            info("party_event before unquote/unjson: %s", party_event)
                            recurse_unquote( party_event )
                            recurse_unjson( party_event )
                            info("party_event _after_ unquote/unjson: %s", party_event)
                            self.postPendingEvent( acc, { "party": party_event } )

                            party_model_changes = party_event.get("PartyData") or []
                            if party_model_changes:
                                try:
                                    ModelChangeApplicator.apply( acc, "partydata", PartyData, party_model_changes )
                                except:
                                    catch()

                        cmd = party_event.get("cmd")
                        if cmd:
                            if cmd == "join_init":
                                acc.party_id = toint( party_event.get("party_id") )
                                info( "join_init: set party_id=%d (auid=%d)" % (acc.party_id, acc.auid) )

                            elif cmd == "join_init_tambur":
                                acc.tambur_id = toint( party_event.get("tambur_id") )
                                info( "join_init_tambur: set tambur_id=%d (auid=%d)" % (acc.tambur_id, acc.auid) )

            else:
                # если нету party events, может, PS вернул ошибку?
                msg = response.get("error")
                if msg and uid:
                    msg = urllib.unquote( msg )
                    acc = users.get(uid)
                    party_event = {
                        "cmd": "error",
                        "failed_cmd": response.get("cmd"),
                        "party_id": response.get("party_id"),
                        "message": msg,
                    }
                    self.postPendingEvent( acc, { "party": party_event } )

        else:
            warn("bad onPartyCmdCallback response: %r" % response)
            # надо доставить юзеру ошибку (вероятно, PersonServer не смог ответить)
            acc = users.get( uid )
            if acc:
                party_event = {
                    "cmd": "error",
                    "message": "bad onPartyCmdCallback response: no party server?",
                    "ps_response": response
                }
                self.postPendingEvent( acc, { "party": party_event } )

        if (not response) or (not response.get("ok")):
            acc = users.get( uid )
            if acc:
                if toint(args.get("is_temp_party_id", 0)):
                    temp_party_id = toint(args.get("party_id", 0))
                    info("should clear temp party_id: party cmd args(%s), acc.party_id=%s" % (args, acc.party_id))
                    if acc.party_id == temp_party_id:
                        acc.party_id = 0
            else:
                warn("onPartyCmdCallback: no acc for uid=%s" % uid)


    def postFriendPendingEvent(self, acc, param_dict):
        ## info( "postPendingEvent for auid=%d, event:%r" % (acc.auid, event_object) )

        event_object = { "friends":param_dict }
        acc.pending_events.append( event_object )
        if acc.pending_handler:
            acc.pending_handler()




        return param_dict


    #----------------------------------------------------------------------------------------------
    def postPendingEvent(self, acc, event_object):
        ## info( "postPendingEvent for auid=%d, event:%r" % (acc.auid, event_object) )
        acc.pending_events.append( event_object )
        if acc.pending_handler:
            acc.pending_handler()


    ##-------------------------------------------------------------------------------------
    ##-------------------------------------------------------------------------------------
    ## IModelData candidates
    #-------------------------------------------------------------------------------------
    # OVERRIDE: приводим версию Model Data, отсылаемую клиенту, в ожидаемый клиентом вид
    # (возможно, фиктивно добавляем к model change какие-то данные, на сервере хранящиеся отдельно; или убираем служебные серверные данные, которые клиент увидеть не должен)
    def modelFullUpdateFix(self, action_handler):
        self.modelAddMatchmakingData(action_handler)

        # копируем в ответ и зачищаем у себя сообщения о валидации талантов в TalentSet
        if action_handler.acc.data.ts_validation_msgs:
            action_handler.response["ts_validation_msgs"] = action_handler.acc.data.ts_validation_msgs[:]
        action_handler.acc.data.ts_validation_msgs = []

        acc = action_handler.acc
        if acc and acc.db.fraction != FRACTION.NONE:
            acc.model.write( acc.pending )
            acc.pending.setPrefix( "modelFullUpdateFix:" )
            acc.model.setComment( "auto" )
            # trying to attach steam to acc
            acc.db.steamOrders = acc.db.steamOrders or {}
            acc.db.aeriaTransaction = acc.db.aeriaTransaction or 0
            acc.db.aeriaOrders = acc.db.aeriaOrders or {}
            acc.db.arcgamesTransaction = acc.db.arcgamesTransaction or 0
            acc.db.arcgamesOrders = acc.db.arcgamesOrders or {}
            acc.db.zzimacomTransaction = acc.db.zzimacomTransaction or 0
            acc.db.zzimacomOrders = acc.db.zzimacomOrders or {}

            if acc.original_snid == 'st':
                info( "Attaching Steam billing to account (auid=%s snuid=%s)", acc.auid, acc.snuid)
                callback = functools.partial( self.onSteamInfoLoaded, acc=acc, I=self.I )
                acc.steam = self.I.STEAM.attachTo(acc.original_snuid, acc.remote_ip, acc.auid, callback)  # загружаем информацию из Steam
            else:
                acc.steam = None
                acc.model.LordInfo.SteamBillingStatus = Billing.Fail

            # trying to attach aeria to acc
            if acc.original_snid == 'ae':
                # Выдаем dlc c id 'aeria_initial_dlc' для Aeria PF-76118
                dlc_id = 'aeria_initial_dlc'
                if dlc_id not in acc.db.dlcs:
                    self.tryApplyDLCs( [dlc_id], acc, self.I )

                info("Attaching AeriaGames billing to account (auid=%s snuid=%s)", acc.auid, acc.snuid)
                acc.aeria = self.I.AERIA.attachTo(acc.auid, acc.remote_ip)
                acc.model.LordInfo.AeriaBillingStatus = Billing.Ok
            else:
                acc.aeria = None
                acc.model.LordInfo.AeriaBillingStatus = Billing.Fail

            if acc.original_snid == 'msv':
                acc.model.LordInfo.MassiveBillingStatus = Billing.Ok
            else:
                acc.model.LordInfo.MassiveBillingStatus = Billing.Fail

            if acc.original_snid == 'mru':
                acc.model.LordInfo.MailruBillingStatus = Billing.Ok
            else:
                acc.model.LordInfo.MailruBillingStatus = Billing.Fail

            # trying to attach arcgames to acc
            if acc.original_snid == 'arc':
                info("Attaching ArcGames billing to account (auid=%s snuid=%s)", acc.auid, acc.snuid)
                acc.arcgames = self.I.ARCGAMES.attachTo(acc.auid, acc.original_snid)
                acc.model.LordInfo.ArcGamesBillingStatus = Billing.Ok
            else:
                acc.arcgames = None
                acc.model.LordInfo.ArcGamesBillingStatus = Billing.Fail

            if acc.original_snid == 'zzma':
                info("Attaching ZZima billing to account (auid=%s snuid=%s)", acc.auid, acc.snuid)
                acc.zzimacom = self.I.ZZIMA.attachTo(acc.auid, acc.original_snid)
                acc.model.LordInfo.ZZimaBillingStatus = Billing.Ok
            else:
                acc.zzimacom = None
                acc.model.LordInfo.ZZimaBillingStatus = Billing.Fail

            if acc.original_snid == 'gmg':
                info("Activate Gamigo billing state for  account (auid=%s snuid=%s)", acc.auid, acc.snuid)
                acc.model.LordInfo.GamigoBillingStatus = Billing.Ok
            else:
                acc.model.LordInfo.GamigoBillingStatus = Billing.Fail

            if acc.original_snid == 'dlt':
                info("Activate Draugas billing state for  account (auid=%s snuid=%s)", acc.auid, acc.snuid)
                acc.model.LordInfo.DraugasLtBillingStatus = Billing.Ok
            else:
                acc.model.LordInfo.DraugasLtBillingStatus = Billing.Fail


            # trying to apply dlcs by muid
            first_login = acc.model.LordInfo.LastLogoutTime == 0
            if first_login and hasattr( acc, 'muid' ):
                self.tryApplyDLCsForMuid( acc.muid, acc, self.I )

            if acc.userlocale:
                acc.model.LordInfo.UserLocale = acc.userlocale

            # Проверка на состояние туториала
            if acc.model.LordInfo.TutorialState >= TutorialState.SessionMMStarted and acc.model.LordInfo.TutorialState <= TutorialState.SessionStarted:

                acc.model.LordInfo.TutorialState = TutorialState.BattleQuestAdded
                debug("modelFullUpdateFix: change tutorial state to BattleQuestAdded")
                self.I.STATS.addTutorialStateChange( acc.auid, enum2String(TutorialState, acc.model.LordInfo.TutorialState) )

            info("modelFullUpdateFix: results (auid=%s SteamBillingStatus=%s AeriaBillingStatus=%s "
                 "ArcGamesBillingStatus=%s ZZimaBillingStatus=%s GamigoBillingStatus=%s DraugasLtBillingStatus=%s "
                 "original_snid=%r original_snuid=%s)",
                 acc.auid,
                 acc.model.LordInfo.SteamBillingStatus,
                 acc.model.LordInfo.AeriaBillingStatus,
                 acc.model.LordInfo.ArcGamesBillingStatus,
                 acc.model.LordInfo.ZZimaBillingStatus,
                 acc.model.LordInfo.GamigoBillingStatus,
                 acc.model.LordInfo.DraugasLtBillingStatus,
                 acc.original_snid, acc.original_snuid)


    # OVERRIDE wserver.onUserDataLoadedCallback
    def onUserDataLoadedCallback(self, acc):
        if acc.db.fraction != FRACTION.NONE:
            self.checkGiveBonusTalents( acc )
        ## self.saveUserData( acc ) -- можно не сохранять сразу после загрузки; при нынешнем механизме все равно пофейлится на acc.locked==1
        # и вызываем пост-действия
        self.onCheckUserComplaints(acc)
        self.onUserLoadFinished( acc )

    # Асинхронно подгрузим информацию о забаненных по нашим заявкам игроках
    def onCheckUserComplaints(self, acc):
        if acc.model.LordInfo.PunishedNextUpdateTime < int(time.time()):
            self.I.DATA.find_and_modify(CC.PUNISHED_BY_CLAIM, CC.PUNISHED_BY_CLAIM, {"_id": acc.auid},
                                        update={"punishedPlayers": 0}, new=False,
                                        callback=functools.partial(self.onPunishedUsersFound, acc=acc))
        else:
            acc.model.write(acc.pending)
            acc.pending.setPrefix( "onPunishedUsersFound:")
            acc.model.setComment("auto")
            acc.model.LordInfo.PunishedPlayers = 0

    def onPunishedUsersFound(self, response, acc):
        info("onPunishedUsersFound response: %r", response)
        if acc and response:
            acc.model.write(acc.pending)
            acc.pending.setPrefix( "onPunishedUsersFound:")
            acc.model.setComment("auto")
            if response and "r" in response and response["r"] is not None:
                acc.model.LordInfo.PunishedPlayers = response["r"]["punishedPlayers"]
                acc.model.LordInfo.PunishedNextUpdateTime = int(time.time()) + acc.getConfig().PUNISHED_PLAYERS_UPDATE_TIME

    # ----------------------------------------------------------------------------------------------
    # всякие нужные пост-действия, которые обычно выполняются после загрузки ModelData
    def onUserLoadFinished(self, acc):
        if acc:
            info( "onUserLoadFinished: uid=%s, auid=%s" % (acc.uid, acc.auid))
            _callback = functools.partial( self.onNicknameFinalized, acc=acc )
            iaction = NicknameRemoveSquareBrackets( _callback, I=self.I, acc=acc, uid=acc.uid )
            iaction.onStart()

        else:
            warn( "bad acc in onUserLoadFinished" )

    def onNicknameFinalized(self, response, acc=None):
        info( "onNicknameFinalized: uid=%s, auid=%s, response=%s, snid=%s, original_snid=%s original_snuid=%s" % (acc.uid, acc.auid, response, acc.snid, acc.original_snid, acc.original_snuid))

        acc.db.lord_level = acc.SD.getFameLevel( acc.model.LordInfo.Fame )

        # подпишемся на social exchange (callback пусть идет на уровень сервера, там будет служебная инфа типа sid + возможно, накопленные messages)
        callback = functools.partial( self.onSocialExchangeLogin, acc=acc )
        self.I.SEX.login( acc.auid, CC.SEX_PW_PROJECT, callback )

        self.onFinalize(acc)


    def tryApplyDLCs( self, dlcs, acc, I ):
      return acc.model.tryApplyDLCs( dlcs, acc, I )

    def tryApplyDLCsForMuid( self, muid, acc, I ):
      return acc.model.tryApplyDLCsForMuid( muid, acc, I )

    def onSteamInfoLoaded( self, data, dlcs, acc=None, I=None ):
        if not acc or not I:
            err( "onSteamInfoLoaded fail account or interface null" )

        acc.model.write( acc.pending )
        acc.pending.setPrefix( "onSteamInfoLoaded:" )
        acc.model.setComment( "auto" )

        if data:
            acc.model.LordInfo.SteamBillingStatus = Billing.Ok

        self.tryApplyDLCs( dlcs, acc, I )

        # self.onFinalize(acc) - излишне, уже вызывается из onNicknameFinalized в цепочке логина
        info( "onSteamInfoLoaded: SteamBillingStatus=%s, original_snid=%s, auid=%s, snuid=%s" % (acc.model.LordInfo.SteamBillingStatus, acc.original_snid, acc.auid, acc.snuid) )


    def onFinalize(self, acc):
        # и вот из этого места, после загрузки всех данных из persistent, можно отметить юзера как залогиненного
        if acc.online:
            self.I.STATS.addLogin(acc.auid, acc.getNickname(), options.server_name, (acc.remote_ip or ""), acc.fraction,
                                  False, acc.db.IsDeveloper, acc.locale, acc.db.guildAuid, acc.guilddata.GuildInfo.ShortName,
                                  acc.guilddata.GuildInfo.ShortName, acc.model.LordInfo.GuardInfo.LeavesPoint,
                                  acc.model.LordInfo.GuardInfo.isLeaver)  # CC.LOGIN
            if acc.db.muted:
                self.I.PS.mute(acc.auid, 1)
                if acc.chat:
                    self.I.CHAT.muteUser(acc.chat['host'], acc.auid, 1, acc.db.mutetime, None)
                else:
                    warn("MuteUser: no acc.chat for auid=%s", acc.auid)

    def getDeployName( self ):
        return cfg.DEPLOY_NAME

    #-------------------------------------------------------------------------------------
    # matchmaking info заворачиваем в ответ отдельно (т.к. оно не в пределах Model Data)
    def modelAddMatchmakingData(self, action_handler):
        self.validateMatchMakingSessions(action_handler) # пометим у всех сессий is_valid = 0|1 (в зависимости от тухлости timestamp)

        data = action_handler.acc.data

        # копируем в ответ и зачищаем у себя все mm-сообщения
        if data.mm_messages:
            action_handler.response["mm_messages"] = data.mm_messages[:]
        data.mm_messages = [] # зачищаем после отправки

        if data.mm:
            # new MD: желательно ответить в формате, аналогичном mm_ping
            action_handler.response["mmid"] = data.mm.mmid
            action_handler.response["mm"] = data.mm



    #-------------------------------------------------------------------------------------
    # сессии, для которых мы давно не получали ответа на mm_ping, помечаем как !is_valid
    def validateMatchMakingSessions(self, action_handler):
        session = action_handler.acc.data.mm
        if session:
            now = int( time.time() )
            ts = session.get( "ts_ping", 0 )
            if ts + self.MM_VALIDATION_SECONDS < now:
                session.is_valid = 0
            else:
                session.is_valid = 1

            ##log( "validateMatchMakingSessions: mmid %s, is_valid=%d" % (session.mmid, session.is_valid) )

    # ----------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------
    # GAME_SPECIFIC: Matchmaking methods

    def getMatchmakingPacket(self, acc):
        """ self.mmLocales[LOCALE][gateway_addr] -> mmPacket для соотв. pvx gateway """
        mmChain = self.mmLocales.get( acc.locale ) or self.mmLocales.get( MM.DEFAULT_LOCALE )
        session = acc.data.mm or ClassDict()
        if mmChain:
            gateway_addr = session.gateway_addr
            if gateway_addr:
                mmPacket = mmChain.get(gateway_addr)
                if mmPacket and (gateway_addr not in self.mmOfflineGateways):
                    return mmPacket
                else:
                    warn("stale/offline gateway_addr: %s for auid %s, removing from session data" % (gateway_addr, acc.auid))
                    session.pop("gateway_addr")

            if acc.auid:
                gateway_list = mmChain.keys()
                if type(acc.auid) not in (int, long): # for PF-86319
                    warn("getMatchmakingPacket: possible ERROR: type(acc.auid) = %s for auid %s", type(acc.auid), acc.auid)
                    try:
                        acc.auid = int(acc.auid)
                    except ValueError:
                        err("getMatchmakingPacket: acc.auid isn't a number: '%r'", acc.auid)
                        return None
                gateway_index = acc.auid % len(gateway_list)
                gateway_addr = gateway_list[ gateway_index ]

                if gateway_addr in self.mmOfflineGateways:
                    # увы, наш родной gateway сейчас оффлайн; давайте поймем, какие gateway из подходящих для нашей локали не оффлайн, и выберем из них
                    for addr in gateway_list[:]:
                        if addr in self.mmOfflineGateways:
                            gateway_list.remove(addr)
                    if gateway_list:
                        gateway_index = acc.auid % len(gateway_list)
                        gateway_addr = gateway_list[ gateway_index ]
                        info("picked gateway %s for auid=%s (locale=%s, online gateways: %s)" % (gateway_addr, acc.auid, acc.locale, gateway_list))
                    else:
                        warn("can't pick gateway for locale=%s, auid=%s: all gateways offline" % (acc.locale, acc.auid))
                        return

                mmPacket = mmChain.get(gateway_addr)
                if session:
                    session.gateway_addr = gateway_addr
                return mmPacket
        else:
            warn( "can't find mmLocale[%s], available locales: %r" % (acc.locale, self.mmLocales.keys()) )

    # ----------------------------------------------------------------------------------------------
    def resetMatchmakingPackets(self):
        self.mmLocales = {}
        for locale, addr_list in cfg.MATCHMAKER_LOCALES.iteritems():
            mmChain = {}
            for gateway_addr in addr_list:
                mmChain[gateway_addr] = self.newMmPacket(locale, gateway_addr)
            self.mmLocales[locale] = mmChain

    # ----------------------------------------------------------------------------------------------
    # юзер просит добавить к пакету команду на ролл талантов
    def requestForgeRoll(self, acc, session_roll="", roll_count=1):
        roll_id = 0
        mmPacket = self.getMatchmakingPacket(acc)
        if mmPacket:
            roll_id = self.I.WS.nextInt64GUID( "forge_roll" )
            mmPacket["forge_roll"] = mmPacket.get("forge_roll", [])
            mmPacket["forge_roll"].append( dict( uid=str(acc.auid), roll_id=str(roll_id), session_roll=session_roll, count=roll_count ) )
            info( "addRollForgeCmd: auid=%s, roll_id=%s" % (acc.auid, roll_id) )
        else:
            err("Can't find mmPacket for auid %s" % acc.auid)
        return roll_id

    # ----------------------------------------------------------------------------------------------
    # юзер просит добавить к пакету matchmaking-команду
    def doMatchmakingCmd(self, op, acc, mmid=0, args=None):
        info( "doMatchmakingCmd: op=%s, auid=%s, mmid=%s", op, acc.auid, mmid )
        session = acc.data.mm or ClassDict()
        mmPacket = self.getMatchmakingPacket(acc)
        if mmPacket:
            if op == "add":
                acc.data.mm = args
                subInsert(mmPacket, ("add", acc.auid), args)

                # ближайшую секунду точно не запрашиваем пинги свежедобавленной сессии (чтобы не сбить висящий mm_add)
                acc.data.mm_tReqd = time.time()
                return True

            elif op == "spectate":
                acc.data.mm = args
                subInsert(mmPacket, ("spectate", acc.auid), args)

                # ближайшую секунду точно не запрашиваем пинги свежедобавленной сессии (чтобы не сбить висящий mm_add)
                acc.data.mm_tReqd = time.time()
                return True

            elif op == "cancel":
                if mmid != MM.CANCEL_ALL:
                    subInsert(mmPacket, ("cancel", acc.auid), 1)

                    # выкидываем героя из матчмейкинга
                    if not getattr(acc,"isTutorialAccount", False):
                        hero = acc.model.getHeroByID( session.hero_id )
                        if hero:
                            hero.InMatchmaking = False

                    acc.data.mm = None
                    # удаляем pending команды "add" и "ping" для указанного юзера
                    subDelete(mmPacket, ("add", acc.auid) )
                    subDelete(mmPacket, ("ping", acc.auid) )

                else:
                    subInsert(mmPacket, ("cancel", acc.auid), 1)

                    # выкидываем героев из матчмейкинга
                    try:
                        if session and acc.model:
                            if not getattr(acc,"isTutorialAccount", False):
                                hero = acc.model.getHeroByID( session.hero_id )
                                if hero:
                                    hero.InMatchmaking = False

                        # удаляем вообще все pending команды/сессии указанного юзера
                        acc.data.mm = None
                        subDelete(mmPacket, ("add", acc.auid) )
                        subDelete(mmPacket, ("ping", acc.auid) )
                    except Exception:
                        catch()
                        warn("Bad modeldata for %r", acc.auid)
                        acc.data.mm = None
                        subDelete(mmPacket, ("add", acc.auid) )
                        subDelete(mmPacket, ("ping", acc.auid) )

                # извещаем PersonServer, что юзер закончил матчмейкаться
                if self.I.PS:
                    self.I.PS.sendPartyCmd(acc.auid, options.server_id, "party_progress", self.I.WS.onDummyResponseCallback, progress=0, reason="mm_cancel")

                return True

            elif op == "party_cancel":
                subInsert(mmPacket, ("party_cancel", acc.auid), 1)

                # выкидываем героев из матчмейкинга
                if session:
                    hero = acc.model.getHeroByID( session.hero_id )
                    if hero:
                        hero.InMatchmaking = False

                # удаляем вообще все pending команды/сессии указанного юзера
                acc.data.mm = None
                subDelete(mmPacket, ("add", acc.auid) )
                subDelete(mmPacket, ("ping", acc.auid) )

                # извещаем PersonServer, что юзер закончил матчмейкаться
                if self.I.PS:
                    self.I.PS.sendPartyCmd(acc.auid, options.server_id, "party_progress", self.I.WS.onDummyResponseCallback, progress=0, reason="party_cancel")

                return True

            elif op == "accept":
                subInsert(mmPacket, ("accept", acc.auid), args)
                return True

            elif op == "change_hero":
                subInsert(mmPacket, ("change_hero", acc.auid), args)
                return True

            elif op == "ready":
                subInsert(mmPacket, ("ready", acc.auid), 1)
                # извещаем PersonServer, что юзер поменял is_tambur_ready
                if self.I.PS:
                    callback = self.I.WS.onDummyResponseCallback # functools.partial( self.I.WS.onPartyCmdCallback, uid=acc.uid )
                    session = acc.data.mm
                    self.I.PS.sendTamburCmd( acc.auid, options.server_id, "tambur_ready", callback, \
                        game_id=session.game_id, allies_key=session.allies_key, allies_count=session.allies_count, \
                        ready=1, foes_ready=toint(session.foes_rdy) )
                return True

            elif op == "leave":
                # отправляем в сторону gateway/matchmaking
                subInsert(mmPacket, (op, acc.auid), 1)

                if acc.party_id:
                    # извещаем PersonServer, что юзер (leaver) должен покинуть партию
                    if self.I.PS:
                        self.I.PS.sendPartyCmd(acc.auid, options.server_id, "party_disband", self.I.WS.onDummyResponseCallback, party_id=acc.party_id, reason="mm_leave")

                return True

            elif op in ("reconnect", "close"):
                # просто отправляем в сторону gateway/matchmaking
                subInsert(mmPacket, (op, acc.auid), 1)
                return True

        else:
            err("Can't find mmPacket for auid %s" % acc.auid)

        return False

    def getMMSeasonData(self, hero, acc):
        cur_league_place = 0
        cur_league_arr_near_places = []
        best_league = hero.getBestLeagueFromPrevSeasons(acc, acc.SD)
        best_league_flash_idx = best_league['flashDataIndex'] if best_league else 0
        cur_season_md = hero.findCurrentSeasonInfo(acc)
        if cur_season_md:
            cur_league = acc.SD.getBestSeasonLeague(cur_season_md)
            if cur_league and cur_league['minLeaderPlace'] > 0:
                cur_league_place = cur_season_md.CurLeaguePlace
                cur_league_arr_near_places = cur_season_md.NearPlaces.keys()
        return best_league_flash_idx, cur_league_place, cur_league_arr_near_places

    def fillHeroMatchmakingValues(self, session, acc, hero_id, configdata, tsId):
        hero = acc.model.getHeroByID( hero_id )

        best_league_flash_idx, cur_league_place, arr_near_places = self.getMMSeasonData(hero, acc)

        if type(hero.PersistentId) is not int:
            error("ERROR! fillHeroMatchmakingValues: hero.PersistentId [{0}] must be int".format(hero.PersistentId))
        if type(hero.Rating) is str:
            error("ERROR! fillHeroMatchmakingValues: hero.Rating [{0}] must be number".format(hero.Rating))
        if type(cur_league_place) is not int:
            error("ERROR! fillHeroMatchmakingValues: cur_league_place [{0}] must be int".format(cur_league_place))

        # auid = tolong(acc.db.auid)
        # if auid == 0:
        #    error("ERROR! fillHeroMatchmakingValues: acc.db.auid [{0}] is {1}, must be number".format(acc.db.auid, type(acc.db.auid)))

        # debug_str = "fillHeroMatchmakingValues for auid = {0} hero = {1}, hero_rating = {2}, cur_league_place = {3}, " \
        #             "near_places = {4}".format(acc.db.auid,
        #                                        hero.PersistentId,
        #                                        hero.Rating,
        #                                        cur_league_place,
        #                                        str(arr_near_places))
        # debug(debug_str)

        session.update({
            "hero_id": hero_id,
            "force": hero.TalentSets[hero.ActiveTalentSet].Force,
            "hero": hero.class_name,
            "combat_rating": hero.Rating, # чтобы не сломался старый ММкинг, вырезать после ( PF-49528 )
            "hero_rating": hero.Rating,
            "hero_crc": hero.PersistentId,
            "hero_level": acc.SD.getHeroExpLevel( hero.Experience ) + 1,
            "lord_status": acc.model.getLordStatus( hero, configdata ),
            "hero_skin_id": acc.model.getCurrentSkinPersistentId( hero ),
            "animAvatar": acc.model.getCurrentSkinAnimateAvatar(hero),
            "talent_set_id": tsId,
            "LeagueIndex": best_league_flash_idx,   # лучшая лига!
            "ownLeaguePlace": cur_league_place,  # место в текущем сезоне!
            "leaguePlaces": arr_near_places  # соседние места в текущем сезон!
        })
        pRating = acc.model.getPlayerRating()
        session["lord_rating"] = pRating if hero.Rating < pRating else hero.Rating


    @staticmethod
    def fillStatsModifiers(acc, hero, buffs, tsId):
        stats_mod = {}

        converter = {
            "hsAgility" : "AttackSpeed",
            "hsCunning" : "Dexterity",
            "hsFortitude" : "Stamina",
            "hsHealth" : "Life",
            "hsIntellect" : "Intellect",
            "hsMana" : "Energy",
            "hsStrength" : "Strength",
            "hsWill" : "Will",
            "hsLifeRegen" : "LifeRegenerationAbsolute",
            "hsManaRegen" : "EnergyRegenerationAbsolute"
            }

        stats_mod["hsAgility"] = hero.TalentSets[tsId].Stats.Agility + hero.TalentSets[tsId].GuildStats.Agility
        stats_mod["hsCunning"] = hero.TalentSets[tsId].Stats.Cunning + hero.TalentSets[tsId].GuildStats.Cunning
        stats_mod["hsFortitude"] = hero.TalentSets[tsId].Stats.Fortitude + hero.TalentSets[tsId].GuildStats.Fortitude
        stats_mod["hsHealth"] = hero.TalentSets[tsId].Stats.Health + hero.TalentSets[tsId].GuildStats.Health
        stats_mod["hsIntellect"] = hero.TalentSets[tsId].Stats.Intellect + hero.TalentSets[tsId].GuildStats.Intellect
        stats_mod["hsMana"] = hero.TalentSets[tsId].Stats.Mana + hero.TalentSets[tsId].GuildStats.Mana
        stats_mod["hsStrength"] = hero.TalentSets[tsId].Stats.Strength + hero.TalentSets[tsId].GuildStats.Strength
        stats_mod["hsWill"] = hero.TalentSets[tsId].Stats.Will + hero.TalentSets[tsId].GuildStats.Will
        stats_mod["hsLifeRegen"] = 0
        stats_mod["hsManaRegen"] = 0

        for hs_stat in stats_mod:
            stat = converter[hs_stat]
            stats_mod[hs_stat] += acc.model.getBonusFromBuilding( stat, acc.SD )
            if buffs:
                for stat_id, stat_dat in buffs:
                    if stat == stat_id:
                        stats_mod[hs_stat] += GuildBonusProcessor.getModifiedValue(stats_mod[hs_stat], stat_dat)

        return stats_mod

    def getHeroAcceptParameters( self, acc, hero_id, map, map_name, tsId ):
        # нужно вытащить TalentSet нашего matchmaking-героя и завернуть его в accept, в неком определенном формате
        #  { slot: { id:<talent_crc32>, rr:<refine_rate> }, .... }
        mm_hero_talents = {}
        mm_hero_action_bar = {}
        hero_class_id = 0
        hero_rating = 0.0
        dropRate = 1.0
        try:
            hero = acc.model.getHeroByID( hero_id )
            if hero:
                hero_class_id = hero.PersistentId
                hero_rating = hero.Rating

                mdActionBar = hero.TalentSets[tsId].ActionBar
                actionBar = {}
                for actionBarIdx, talId in mdActionBar.iteritems():
                    actionBar[talId] = actionBarIdx

                instaCastParams = {}
                for indx, isInstaCast in hero.TalentSets[tsId].InstaCast.iteritems():
                    instaCastParams[mdActionBar[indx]] = isInstaCast

                # алло, мы ищем таланты,
                for slot, tal in hero.TalentSets[tsId].Talents.iteritems():
                    talent = acc.model.getTalentByID(tal)
                    if talent:
                        staticTalent = acc.SD.getStaticTalentByTalentId(talent.PersistentId)
                        refine_rate = acc.SD.getTalentLevel( talent ) + 1
                        talent_info = { "id":talent.PersistentId, "rr":refine_rate }
                        if talent.getID() in actionBar:
                            talent_info["ab"] = actionBar[talent.getID()]
                        if staticTalent['type'] != "Passive" and \
                                staticTalent['type'] != "Simple" and \
                                talent.getID() in instaCastParams:
                            talent_info["ic"] = instaCastParams[talent.getID()]
                        mm_hero_talents[slot] = talent_info

            if acc.model.IsPremiumAccount():
                dropRate = acc.getConfigValue("PREMIUM_ACCOUNT_SESSION_BONUS")

        except:
            catch()

        avatarLevel = acc.SD.getFameLevel( acc.getFame() )
        heroLevel = acc.SD.getHeroExpLevel( hero.Experience ) + 1 #X: 1
        lordRating = acc.model.getRating()
        lordPublicRating = acc.model.getPublicRating()
        lordStatus = acc.model.getLordStatus( hero, acc.getConfig() )
        hero_inventory = acc.model.getConsumablesForSession( acc.SD )
        friends = []
        # Грязный хак, проверка, что есть friendsdata для починки PF-49828. Все хорошо будет починено в PF-49238
        if acc.friendsdata:
            friends = acc.friendsdata.getOnlineFriendUids()

        guildRating = 0
        guildLevel = -1
        guildBuildingLevel = -1
        guildIconNumber = 0
        guild_icon_url = ""
        if acc.guilddata:
            guildRating = acc.guilddata.RatingInfo.Rating
            guildLevel = acc.SD.getGuildLevel( acc.guilddata.GuildLevelInfo.Experience )
            guildBuildingLevel = acc.model.getGuildBuildingLevel( acc.SD )
            guildIconNumber = acc.guilddata.GuildInfo.IconChangesCount
            guild_icon_url = acc.getConfigValue("GUILD_ICONS_URL_PATTERN").replace( "{guild_id}", str(acc.db.guildAuid) ).replace( "{changes_count}", str(guildIconNumber) )

        firstWin = acc.model.isFirstPlay( map, acc.getConfig() )

        complaintsMax =  acc.getConfig().ComplaintsSettings.MAX_COMPLAITS_PER_SESSION + acc.model.LordInfo.ExtraComplaintsSession
        complaintsToday = complaintsMax - acc.model.LordInfo.ComplaintsSessionLeft

        complaintsInfo = {}
        for key in acc.getConfig().ComplaintsSettings.COMPLAINTS_TYPES.keys():
            complaintsInfo[key] = acc.getConfig().ComplaintsSettings.COMPLAINTS_TYPES[key]

        # пока тут только купленные гильдийские бафы в виде { stat_id:{"add":<val>,"mul":<val>}, ... }
        buffs = self.guildBonusProcessor.getModifiersFromGuildBuffs(acc, hero.PersistentId, map_name)

        statModAt36Level = PwWorkServer.fillStatsModifiers(acc, hero, buffs['at36level'], hero.ActiveTalentSet)

        guild_war_event_pass = bool(self.canParticipateInGuildWarEvent() and buffs['pass'])
        debug("guild_war_event_pass is %s, buff id is %s", guild_war_event_pass, 0 if not buffs['pass'] else buffs['pass'][0])

        pRating = acc.model.getPlayerRating()
        lordRating = pRating if hero_rating < pRating else hero_rating

        best_league_flash_idx, cur_league_place, arr_near_places = self.getMMSeasonData(hero, acc)

        debug("getHeroAcceptParameters for auid = %d hero = %d, cur_league_place = %d, near_places = %s"%(acc.db.auid, hero.PersistentId, cur_league_place, str(arr_near_places)))

        acceptParamsDict = {"hid": hero_class_id,
                            "heroExp": hero.Experience,
                            "avatarLevel": avatarLevel,
                            "heroLevel": heroLevel,
                            "heroForce": hero.TalentSets[hero.ActiveTalentSet].Force,
                            "hsAgility": statModAt36Level["hsAgility"],
                            "hsCunning": statModAt36Level["hsCunning"],
                            "hsFortitude": statModAt36Level["hsFortitude"],
                            "hsHealth": statModAt36Level["hsHealth"],
                            "hsIntellect": statModAt36Level["hsIntellect"],
                            "hsMana": statModAt36Level["hsMana"],
                            "hsStrength": statModAt36Level["hsStrength"],
                            "hsWill": statModAt36Level["hsWill"],
                            "hsLifeRegen": statModAt36Level["hsLifeRegen"],
                            "hsManaRegen": statModAt36Level["hsManaRegen"],
                            "energy": 0,
                            "heroRating": hero_rating,
                            "lordRating": lordRating,
                            "guardRating": lordPublicRating,
                            "seed": acc.db.seed,
                            "session_roll": self.getMapSessionRollString(acc, map_name),
                            "dropRate": dropRate,
                            "ts": mm_hero_talents,
                            "inventory": hero_inventory,
                            "friends": friends,
                            "hasPremium": acc.model.IsPremiumAccount(),
                            "lord_status": lordStatus,
                            "firstWin": firstWin,
                            "heroSkin": acc.model.getCurrentSkinName( hero, acc.SD ),
                            "animAvatar": acc.model.getCurrentSkinAnimateAvatar(hero),
                            "locale": acc.get("locale", cfg.MATCHMAKER_DEFAULT_LOCALE),
                            "guild_auid": str(acc.db.guildAuid),
                            "guild_icon_number": guildIconNumber,
                            "guild_icon_url": guild_icon_url,
                            "guild_rating": tofloat(guildRating),
                            "guild_level": guildLevel,
                            "guild_building_level": guildBuildingLevel,
                            "guild_war_event_pass": bool(guild_war_event_pass),
                            "goldLamp": acc.model.getGoldLampRollContainer( acc.SD, acc.getConfig(), firstWin ),
                            "complaints_today": complaintsToday,
                            "complaints_max": complaintsMax,
                            "complaints_info": complaintsInfo,
                            "chat_muted": bool(acc.db.muted and (acc.db.mutetime == 0 or acc.db.mutetime > time.time())),
                            "developer": bool(acc.db.IsDeveloper),
                            "flag_id": acc.model.FlagInfo.PersistentId,
                            "hasFullLibrary": acc.model.isInventoryFull(),
                            "buffs2roll": buffs['roll'],
                            "partyLeader": False,
                            "LeagueIndex": best_league_flash_idx,
                            "ownLeaguePlace": cur_league_place,
                            "leaguePlaces": arr_near_places
                         #   "ps_modifiers": persistentModifiers
                         }

        return acceptParamsDict

    # ----------------------------------------------------------------------------------------------
    # подпорка: при релогине насиьлно сбрасываем текущие мм-запросы
    def resetUserSessions(self, acc):
        self.doMatchmakingCmd( "cancel", acc, MM.CANCEL_ALL )
        acc.data.mm_messages = []

    # ----------------------------------------------------------------------------------------------
    # OVERRIDE
    def dumpAccount(self, acc, title_string):
        copy_acc = ClassDict( acc ) # чисто для дампа acc
        copy_acc.model = None
        copy_acc.data = None
        copy_acc.pending = None
        copy_acc.friendsdata = None
        copy_acc.BufferFriendsData = None
        copy_acc.friendsdata = None
        copy_acc.partydata = None
        copy_acc.guilddata = None
        copy_acc.siegedata = None
        copy_acc.on_loaded_callbacks = []
        copy_acc.pending_changes = []
        copy_acc.pending_events = []
        try:
            info( "%s: acc %s" % (title_string, copy_acc) )
            ## info( "%s: pretty acc %s" % (title_string, pretty(copy_acc)) )
        except:
            catch()

    # ----------------------------------------------------------------------------------------------
    # собираем пакет для отправки pvx matchmaking
    # (должен включать периодические пинги для всех текущих mm-сессий наших юзеров)
    def addMatchmakingPings(self):
        now = time.time()

        # посчитаем, сколько юзеров сидят ждут матчмейкинга (за каждую сторону, для основного типа игры)
        self.CCU.mm_A = 0
        self.CCU.mm_B = 0

        for uid, acc in users.iteritems():
            can_ping = 0
            ping_period = self.MM_PING_PERIOD # по умолчанию пингуем часто (типа раз в секунду)
            if acc.data.mm:
                # давайте-ка посчитаем, сколько юзеров сидят ждут матчмейкинга (за каждую сторону, для основного типа игры)
                session = acc.data.mm
                if session:
                    is_valid = session.get("is_valid")
                    create_ts = session.get("create_ts", 0)
                    if (not is_valid) and create_ts + self.MM_VALID_TIMEOUT < now:
                        # протухла, надо удалить
                        warn( "stale mm session: %s (created %5.3f, now %5.3f), deleting..." % (session.mmid, create_ts, now) )
                        self.postMmMessage( acc, session.mmid, error="[pvx] stale mm session" )
                        self.doMatchmakingCmd( "cancel", acc, MM.CANCEL_ALL )
                        # NB: в этом случае acc.data.mm сейчас же погибнет, ping по ней отправлять уже не надо

                    else:
                        # пинговать свежесозданную сессию можно (1) не раньше чем истечет минимальный таймаут после создания
                        # и (2) после того как нам ответят что сессия создана на gateway (это прогресс!=1)
                        if (create_ts + self.MM_MIN_ADD_PERIOD < now):
                            if (session.progress != MM.STATUS_NEW):
                                can_ping = 1

                        if session.progress in [MM.STATUS_IN_GAME, MM.STATUS_WAITING_GAME_FINISH] \
                        or (session.progress == MM.STATUS_CLIENT_DROPPED and session.confirm not in [MM.CONFIRM_LEAVE, MM.CONFIRM_RECONNECT]):
                            # идущие pvx-сессии пингуем пореже (при типичной продолжительности игры полчаса пинговать каждую секунду как-то глупо)
                            if session.ts_client_ping + MM.INGAME_PING_PERIOD < now: # в последние N секунд клиент сессию не пинговал; можем и мы расслабиться
                                ping_period = MM.INGAME_PING_PERIOD

                        if session.get("game_type", "") == "pvp" and session.get("is_valid") and (session.get("progress", 0) < MM.STATUS_WAITING_ACCEPT):
                            if session.get("fraction"):
                                self.CCU.mm_B += 1
                            else:
                                self.CCU.mm_A += 1

            if acc.data.mm and can_ping:
                lastReqd = toint( acc.data.mm_tReqd )
                ##info( "lastReqd: %d, self.MM_PING_PERIOD: %d, now: %d" % (lastReqd, self.MM_PING_PERIOD, now) )
                if lastReqd + ping_period < now:
                    acc.data.mm_tReqd = now
                    mmPacket = self.getMatchmakingPacket(acc)
                    if mmPacket:
                        subInsert(mmPacket, ("ping", acc.auid), 1) # запрашиваем статус MM-сессии данного юзера (она может быть только одна)

        # периодически добавляем во все mm-пакеты запрос статистики сервера (среднее время матчмейкинга и т.п.)
        if self.tsLastMmStatus + self.MM_SERVER_STATUS_PERIOD < now:
            for locale, mmChain in self.mmLocales.iteritems():
                for gateway_addr, mmPacket in mmChain.iteritems():
                    mmPacket["server_status"] = 1
            self.tsLastMmStatus = now

    #-------------------------------
    LEN_EMPTY_MM_PACKET = 6
    #-------------------------------
    def newMmPacket(self, locale, gateway_addr):
        pid, server_num, packet_num = self.nextNamedGUIDTuple("pid")
        mmPacket = { "ver":MMSOC_VERSION, "pid":pid, "sn":server_num, "pn":packet_num, "loc":locale, "addr":gateway_addr }
        return mmPacket # version, packet id (string), server serial number, packet serial number

    # ----------------------------------------------------------------------------------------------
    # периодически шлем запрос в сторону pvx matchmaking
    def pingMatchmaking(self):
        self.recalcSummaryPacketState()
        self.addMatchmakingPings()

        now = toint( time.time() )
        if self.mmRetryPackets:
            for pid in self.mmRetryPackets.keys():
                retryDict = self.mmRetryPackets[pid]
                if retryDict["sched_time"] < now:
                    self.addRetryPacket( pid, retryDict["pack"] )
                    self.mmRetryPackets.pop( pid )

        # SEND (отсылаем в интерфейс PVX, который может быть внешним PvX matchmaker или нашей собственной заглушкой mock_matchmaker)
        for locale, mmChain in self.mmLocales.iteritems():
            for gateway_addr, mmPacket in mmChain.iteritems():
                if len(mmPacket) > self.LEN_EMPTY_MM_PACKET:
                    test_packet = json_dumps(mmPacket)
                    info( "pingMatchmaking WHOLE packet for %s [len %d, stamp %d]" % (gateway_addr, len(test_packet), now) )

                    self.sendMatchmakingPacket( mmPacket, now ) # NEW: отправляем через POST, поэтому размеры куска нас теперь не особо волнуют

                    # посчитаем статистику по объему ключей
                    for subkey in self.MM_SUBKEY_ORDER:
                        subdict = mmPacket.get(subkey)
                        if subdict:
                            json_value = json_dumps(subdict)
                            len_json_value = len(json_value)
                            if isinstance(subdict, dict):
                                len_subdict = len(subdict)
                            else:
                                len_subdict = 1
                            #info( "[mmKeyStats] subkey %s, len=%d, cnt=%d" % (subkey, len_json_value, len_subdict) )

                            self.mmKeyStats.add( subkey+".len", len_json_value ) # общий объем отправленных команд данного типа
                            self.mmKeyStats.inc( subkey+".sends" ) # количество пакетов, включавших хотя бы одну такую команду
                            self.mmKeyStats.add( subkey+".cnt", len_subdict ) # количество отправленных команд данного типа

                    if self.tsLastMmKeyStats + 360 < now:
                        self.tsLastMmKeyStats = now
                        info( "[mmKeyStats] TOTAL dict: \n" + pretty(self.mmKeyStats) )

        # создаем новый набор пустых mm-пакетов (взамен отправленных)
        self.resetMatchmakingPackets()

    # ----------------------------------------------------------------------------------------------
    def recalcSummaryPacketState(self):
        # по счетчикам failed/passed за последние N секунд составляем представление об общем уровне проблем в матчмейкинге
        now = toint( time.time() )
        failed = 0
        passed = 0
        for ts in range(now - MM.MATCHMAKING_STATUS_SUMMARY_PERIOD, now+1):
            failed += self.mmFailed.pick( ts )
            passed += self.mmPassed.pick( ts )

        if passed <= MM.SUMMARY_PASSED_THRESHOLD:
            # слишком мало прошедших пакетов: : КРАСНЫЙ СВЕТ
            self.mmSummaryState = MM.ESummaryState.RED
        elif failed > MM.SUMMARY_FAILED_THRESHOLD:
            # слишком много непрошедших пакетов: ЖЕЛТЫЙ СВЕТ
            self.mmSummaryState = MM.ESummaryState.YELLOW
        else:
            self.mmSummaryState = MM.ESummaryState.GREEN

        if failed+passed:
            self.mmFailedPercent = 100.0 * failed / (failed+passed)
        else:
            self.mmFailedPercent = 0.0

        info( "summary packet state for the period [%s..%s]: %s (failed %s, passed %s, total %s; fail percent: %2.2f)", now-MM.MATCHMAKING_STATUS_SUMMARY_PERIOD, now, self.mmSummaryState, failed, passed, failed+passed, self.mmFailedPercent)

        ## info( "[MM] offline gateways list: %s" % self.mmOfflineGateways.keys() )


    # ----------------------------------------------------------------------------------------------
    def sendMatchmakingPacket(self, pack, timestamp):
        # сохраним исходный вид пакета, чтобы failed запросы можно было заново ставить в очередь
        info( "sendMatchmakingPacket: pack %s, timestamp %s" % (pack, timestamp) )
        callback = functools.partial( self.onMatchmakingReply, pack=pack, timestamp=timestamp )
        gateway_addr = pack.get("addr")
        self.I.PVX.handlePacket( pack, send_addr=gateway_addr, callback=callback )


    # ----------------------------------------------------------------------------------------------
    # ловим ответ от PVX Matchmaking
    def onMatchmakingReply(self, http_reply, pack={}, timestamp=0):
        if http_reply:
            http_error = getattr(http_reply, "error", None)
            if not http_error:
                reply = getattr(http_reply, "body", None)
                if reply:
                    try:
                        mm = json_loads(reply)
                        pid = pack.get("pid")
                        info( "onMatchmakingReply: (pid %s) %s" % (pid, str(mm)) ) ## info( "onMatchmakingReply: (pid %s) %s" % (pid, pretty(mm)) )
                        pvx_error = mm["response"].get("error")
                        if not pvx_error:
                            sections = mm["response"]["pvx"]

                            # map reply sections (sub-keys) to handler methods
                            for cmd, action_handler in self.mmActions.iteritems():
                                subdict = sections.get(cmd)
                                if subdict:
                                    method = getattr(self, action_handler, None)
                                    if method:
                                        method(subdict)

                        else:
                            err( "onMatchmakingReply: pvx gateway returned error %r" % pvx_error )
                            self.mmFailed.inc( timestamp )
                            return
                    except:
                        catch()

                    # ОК, пришел более-менее нормальный ответ; не нужно делать retry pack
                    self.mmPassed.inc( timestamp )

                    gateway_addr = pack.get("addr")
                    self.clearFailedState( gateway_addr )
                    return

                else:
                    warn("onMatchmakingReply: no body, http_reply: %s" % str(http_reply))
            else:
                warn("onMatchmakingReply: http error %r, http_reply: %r" % (str(http_error), str(http_reply))  )
        else:
            warn("onMatchmakingReply: empty")

        # http send так или иначе пофейлился; ставим галочку "еще один fail", и добавляем содержимое пакета в очередь retry
        self.onFailedMatchmakingPacket(pack, timestamp)

    # --------------------------------------------------------------------------
    def onFailedMatchmakingPacket(self, pack, timestamp):
        if pack:
            pid = pack.get("pid")
            gateway_addr = pack.get("addr")
            self.mmFailed.inc( timestamp )
            if gateway_addr:
                counter_value = self.mmFailedByGate.inc( gateway_addr )
                info( "[MM] gateway %r fail count now: %s" % (gateway_addr, counter_value) )
                if counter_value >= self.MM_MAX_INDIVIDUAL_GATEWAY_FAILS:
                    if gateway_addr not in self.mmOfflineGateways:
                        self.mmOfflineGateways[gateway_addr] = 1
                        info( "[MM] failed gateway %s, offline gateways list now: %s" % (gateway_addr, self.mmOfflineGateways.keys()) )

            retry_timeout = MM.PACKET_RETRY_TIMEOUTS.get( self.mmSummaryState, 0 )
            sched_time = time.time() + retry_timeout
            self.mmRetryPackets[pid] = dict(pack=pack, sched_time=sched_time)

            info( "[MM] retry pack scheduled (pid %s, stamp %s, summary_state %s, sched.time: %s)" % (pid, timestamp, self.mmSummaryState, sched_time) )

    # --------------------------------------------------------------------------
    def clearFailedState(self, gateway_addr):
        self.mmFailedByGate.reset( gateway_addr )
        if gateway_addr in self.mmOfflineGateways:
            self.mmOfflineGateways.pop(gateway_addr)
            info( "[MM] clear fail state for gateway %s, offline gateways list now: %s" % (gateway_addr, self.mmOfflineGateways.keys()) )

    # --------------------------------------------------------------------------
    def addRetryPacket(self, pid, pack):
        info( "[MM] addRetryPacket start (pid %s): \n pack: %s " % (pid, pack) )

        locale = pack.get("loc")
        gateway_addr = pack.get("addr")
        try:
            mmChain = self.mmLocales.get( locale ) or self.mmLocales.get( MM.DEFAULT_LOCALE )
            mmPacket = mmChain[ gateway_addr ]
        except:
            warn("bad locale/gateway addr for retry mmPacket pid %s, skipping" % pid)
            return

        if gateway_addr in self.mmOfflineGateways:
            # если gateway, на который отправляли пакет, уже считается оффлайн -- придется пробежаться по всем [subkey][auid] и распихать их по еще живым гейтам
            # (для чего лучше сразу построить список "живых" mmPacket-ов и распихивать уже по нему)
            activePackets = []
            gateway_list = mmChain.keys()
            # увы, наш родной gateway сейчас оффлайн; давайте поймем, какие gateway из подходящих для нашей локали не оффлайн, и выберем из них
            for addr in gateway_list[:]:
                if addr in self.mmOfflineGateways:
                    gateway_list.remove(addr)
            info("[MM] online gateway list: %s" % gateway_list)

            if gateway_list:
                for addr in gateway_list:
                    activePackets.append( self.mmLocales[locale][addr] )
                activePacketsCount = len(activePackets)

                for subkey in self.MM_SUBKEY_ORDER:
                    subdict = pack.get(subkey)
                    if subdict:
                        if subdict and isinstance(subdict, dict):
                            for auid, val in subdict.iteritems():
                                index = toint(auid) % activePacketsCount
                                mmPacket = activePackets[ index ]
                                info( "[MM] retry from pid %s: subkey %s, auid %s -> to gateway bucket %s/%s (pid %s)" \
                                    % (pid, subkey, auid, index+1, activePacketsCount, mmPacket.get("pid", 0)) )
                                subInsert( mmPacket, (subkey, auid), val )

                return

            else:
                warn( "Can't retry packet %s: all gateways for locale %s offline" % (pid, locale) )

        # в случае, если gateway считается активным, или если вариантов все равно нет (все гейтвеи оффлайн)
        # выполняем простой retry: тупо перепихиваем все подряд ключи из старого mm-пакета в новый
        for subkey in self.MM_SUBKEY_ORDER:
            subdict = pack.get(subkey)
            if subdict:
                info( "[MM] retry subkey %s for pid %s" % (subkey, pid) )
                if subdict and isinstance(subdict, dict):
                    for key, val in subdict.iteritems():
                        subInsert( mmPacket, (subkey, key), val )

        info( "[MM] retry pack finish (pid %s): \n mmPacket now: %s" % (pid, mmPacket) )


    # ----------------------------------------------------------------------------------------------
    # на команды ping отвечает числом "прогресса сессии" (>0 если сессия идет, MM.STATUS_WAITING_ACCEPT: уже смейкалось, 0: нет такой сессии )
    def onMmSessionAdd(self, dct):
        ##info("onMmSessionAdd:" + pretty(dct))
        for auid, mm_session_progress in dct.iteritems():
            acc = self.getUserAccByAuid( toint(auid) )
            if acc:
                # ок, у pvx добавились какие-то наши сессии;
                ##info("onMmSessionAdd: acc.data.mm: " + pretty(acc.data.mm))
                session = acc.data.mm
                if session:
                    #############TODO: проверить, что совпадает mmid
                    info( "onMmSessionAdd: auid %s, progress %d" % (auid, mm_session_progress) )
                    session.progress = mm_session_progress


    # ----------------------------------------------------------------------------------------------
    def clearMmSession(self, session, acc, reason=""):
        if session:
            info( "%s: deleting mm session %s (auid=%s)" % (reason, session.mmid, acc.auid) )
            acc.model.write( acc.pending )
            hero = acc.model.getHeroByID( session.hero_id )
            if hero:
                info( "clearing hero.InMatchmaking (auid=%s, hero_id=%s)" % (acc.auid, session.hero_id) )
                hero.InMatchmaking = False

            # извещаем PersonServer, что юзер закончил матчмейкаться
            self.I.PS.sendPartyCmd(acc.auid, options.server_id, "party_progress", self.I.WS.onDummyResponseCallback, \
                progress=0, reason="mm_progress")

        acc.data.mm = None # чистим все сесии нафиг


    def addDodge(self, acc, reason=""):
        info( "%s: add dodge (auid=%s)" % (reason, acc.auid) )
        acc.model.write( acc.pending )
        acc.pending.setPrefix( "addDodge:" )
        acc.model.setComment( "auto" )
        acc.model.addDodge( self.I.WS, acc )



    # отсылаем в статистику сообщение о старте игровой сессии, со списком талантов выбранного героя
    def reportJoinSession(self, acc, session):
        # addJoinPvpSession(self, auid, gameid, heroid, talent_id_list):
        talent_id_list = []
        session_buffs = []
        hero = acc.model.getHeroByID( session.hero_id )
        buffs = None
        if hero:
            for slot,tal in hero.TalentSets[session.talent_set_id].Talents.iteritems():
                talent = acc.model.getTalentByID(tal)
                if talent:
                    talent_id_list.append( toint(talent.PersistentId) )


            buffs = self.guildBonusProcessor.getModifiersFromGuildBuffs(acc, hero.PersistentId, session.game_type)
            for stat, stat_data in buffs['at36level']:
                session_buffs.append( toint(crc32(stat_data['buffPersistentId'])) )

        guild_war_event_pass = -1 if not buffs or not buffs['pass'] else crc32(buffs['pass'][0])

        info("reportJoinSession: auid=%s, game_id=%s, hero_crc=%s, talent_id_list=%s, session_buffs=%s, guild_war_event_pass=%s, game_type=%s" %
             (acc.auid, session.game_id, session.hero_crc, talent_id_list, session_buffs, guild_war_event_pass, session.game_type))
        self.I.STATS.addJoinPvpSession(acc.auid, session.game_id, session.hero_crc,
                                        talent_id_list, session_buffs, guild_war_event_pass)


    # извещаем person_server, что у нас развалился (или стал не нужен) гвардейский тамбур
    def finishGuardsTambur(self, acc, session):
        info("Finish guards tambur for auid=%s (mmid=%s)" % (acc.auid, session.mmid))
        session.is_tambur_ready = 0
        if self.I.PS:
            callback = functools.partial( self.I.WS.onPartyCmdCallback, uid=acc.uid )
            self.I.PS.sendTamburCmd( acc.auid, options.server_id, "tambur_delete", callback,
                game_id=session.game_id, allies_key=session.allies_key, allies_count=session.allies_count )


    # ----------------------------------------------------------------------------------------------
    # на команды ping отвечает 1) list-ом, включающим "прогресс сессии" (если сессия идет) или 2) просто 0 если нет такой сессии
    def onMmSessionProgress(self, dct):
        ##info("onMmSessionProgress:" + pretty(dct))
        for auid, mm_session in dct.iteritems():
            try:
                acc = self.getUserAccByAuid( toint(auid) )
                if acc:
                    if not (acc.failed or acc.locked):
                        if mm_session:
                            # ок, у pvx есть какая-то наша сессия (по новым правилам - сессия бывает только одна)
                            ##info( "onMmSessionProgress: acc.data.mm: " + pretty(acc.data.mm) )
                            if acc.data.mm:
                                # сессия теперь одна, и лежит прямо в acc.data.mm
                                # mmid - всего лишь одно из полей сессии
                                session = acc.data.mm

                                # -------------------------------------------------------------------------------------------------------
                                # РАЗБИРАЕМ НОВЫЙ PROGRESS UPDATE
                                progress = 0
                                session_id = 0
                                accept_count = 0
                                total_count = 0
                                debug_info = 0
                                game_id = 0
                                session_results = 0
                                mmid = 0
                                guards_info = {}

                                progress_list = mm_session

                                if progress_list and isinstance(progress_list, list):
                                    debug("onMmSessionProgress progress_list: %r", progress_list)
                                    if len(progress_list) >= 8: # разбираем элементы [0]..[7]
                                        progress, session_id, accept_count, total_count, debug_info, session_results, game_id, mmid = progress_list[:8]
                                    else:
                                        warn("bad progress list from pvx gateway: %s" % progress_list)
                                    if len(progress_list) >= 9:
                                        guards_info = progress_list[8]

                                ##info("onMmSessionProgress: mmid %s, session %s, progress list: %s, accepted: %d/%d, guards_info: %s" \
                                ##    % (mmid, str(session), str(progress_list), accept_count, total_count))

                                # бывают случаи, когда с gateway еще приходит ответ на пинг старой сессии, а у нас на сервере уже создана новая; в таких случаях игнорим и ругаемся
                                prev_mmid = session.get('mmid',0)
                                if mmid and prev_mmid and mmid != prev_mmid:
                                    warn("onMmSessionProgress: stale ping reply, gateway mmid %s != local mmid %s, SKIPPING progress" % (mmid, prev_mmid))

                                else:
                                    # -------------------------------------------------------------------------------------------------------
                                    # СРАВНИВАЕМ СО СТАРЫМ СОСТОЯНИЕМ (НЕТ ЛИ КАКИХ ИНТЕРЕСНЫХ ИЗМЕНЕНИЙ)
                                    old_progress = session.get('progress', 0)
                                    old_game_id = session.get('game_id', 0)
                                    game_id = tolong(game_id)

                                    if debug_info and (game_id==0):
                                        # вытаскиваем из debug_info номер игры, вида "Game gXXX: ..."
                                        try:
                                            header_len = len("Game g")
                                            game_id = tolong( debug_info.split(":")[0][header_len:] )
                                        except:
                                            game_id = 0

                                    # если мы все еще в той же самой игре (сессия не распалася за промежуток пинга)
                                    tambur_was_deleted = False
                                    if old_game_id == game_id:
                                        # !! вот единственный случай, когда мы ОБМАНЫВАЕМ соц.клиент, подсовывая ему свой статус ("уже приняли твой accept") вместо матчмейкеровского
                                        if progress == MM.STATUS_WAITING_ACCEPT and old_progress == MM.STATUS_ACCEPTED_SOCSERVER:
                                            info( "enforcing status %d for mmid %s (mm progress %s)" % (old_progress, mmid, progress) )
                                            progress = old_progress
                                    elif session.guards_game:
                                        # сменился game_id; значит старый тамбур надо развалить
                                        tambur_was_deleted = True
                                        self.finishGuardsTambur( acc, session )

                                    if progress == MM.STATUS_ACCEPT_TIMED_OUT and old_progress == MM.STATUS_GUARDS_LOBBY:
                                        self.addDodge(acc, reason="accept timeout in tambur")

                                    session.debug_info = debug_info
                                    if game_id:
                                        session.game_id = game_id

                                    if progress != old_progress:
                                        # статус сменился, значит наше "серверное подтверждение" теряет смысл
                                        session.confirm = MM.CONFIRM_NONE

                                    # -------------------------------------------------------------------------------------------------------
                                    # ПРИМЕНЯЕМ НОВОЕ СОСТОЯНИЕ
                                    session.progress = progress

                                    # если уже идем в сессию, accept_count лучше не сбрасывать на 0/0, как это делает почему-то лобби
                                    if progress not in [MM.STATUS_WAITING_IN_LOBBY, MM.STATUS_WAITING_FOR_PARTY]:
                                        session.accept_count = accept_count
                                        session.accept_total = total_count

                                    # пометим специальным timestamp как "свежую"
                                    session.is_valid = 1
                                    session.ts_ping = toint( time.time() )

                                    if old_game_id != game_id and session.guards_game:
                                        # собралась новая игра; героя нужно выбрать заново, по src_hero_id (т.к. в тамбуре его могли сменить)
                                        self.restoreSrcHero( session, acc )

                                    # -------------------------------------------------------------------------------------------------------
                                    # РАЗБЕРЕМСЯ С ГВАРДЕЙСКИМИ ИГРАМИ
                                    if guards_info:
                                        guards_game = guards_info.get('guards_game', 0)
                                        foes_rdy = guards_info.get('foes_rdy', 0)
                                        allies = guards_info.get('allies', {})
                                    else:
                                        guards_game = 0
                                        foes_rdy = 0
                                        allies = {}

                                    if guards_game and allies and ((not session.allies) or (old_game_id != game_id)):
                                        # заводим список "соседей по тамбуру", он будет служить уникальным ключом для индексации тамбуров на PS
                                        allies_uids = []
                                        session.allies_key = ''
                                        session.allies_count = len( allies )
                                        for ally in allies:
                                            allies_uids.append(ally.get('uid', 0))
                                        for ally_uid in sorted(allies_uids):
                                            session.allies_key += '_' + str(ally_uid)
                                        # известить person_server, что у нас стартовал новый гвардейский тамбур
                                        info("Start guards tambur for auid=%s (mmid=%s): guards_info %s, allies_key %r" \
                                            % (acc.auid, mmid, guards_info, session.allies_key))
                                        callback = functools.partial( self.I.WS.onPartyCmdCallback, uid=acc.uid )
                                        self.I.PS.sendTamburCmd(acc.auid, options.server_id, "tambur_add", callback, \
                                                                game_id=session.game_id, allies_key=session.allies_key, allies_count=session.allies_count, foes_rdy=foes_rdy, \
                                                                hero_id=session.hero_id, hero_crc=session.hero_crc, hero_level=session.hero_level, hero_skin_id=session.hero_skin_id, \
                                                                hero_rating=session.hero_rating, hero_force=session.force, hero_status=session.lord_status, game_type=session.game_type, \
                                                                real_party_uid=session.party_id, flag_type=acc.model.FlagInfo.FlagType, flag_persistent_id=acc.model.FlagInfo.PersistentId,
                                                                IsAnimatedAvatar=toint(session.animAvatar), LeagueIndex = acc.model.getBestLeagueFlashIdxFromPrevSeasonsByHeroId(acc, session.hero_id))
                                    elif (not guards_game) and session.guards_game:
                                        if not tambur_was_deleted:
                                            self.finishGuardsTambur( acc, session )
                                    elif (session.foes_rdy != foes_rdy) and session.game_id: # при сброшенном game_id нет смысла отсылать tambur_ready (речь небось о foes_ready=0)
                                        callback = functools.partial( self.I.WS.onPartyCmdCallback, uid=acc.uid )
                                        self.I.PS.sendTamburCmd( acc.auid, options.server_id, "tambur_ready", callback, \
                                            game_id=session.game_id, allies_key=session.allies_key, allies_count=session.allies_count, ready=0, \
                                            foes_ready=toint(foes_rdy) )

                                    session.guards_game = guards_game
                                    session.foes_rdy = foes_rdy
                                    session.allies = allies

                                    # -------------------------------------------------------------------------------------------------------
                                    # если у нас идет активная pvx игра, поддержим существование пользовательской сессии у нас на соц.сервере
                                    # (чтобы результаты сессии обязательно были получены и применены)
                                    if progress in [ MM.STATUS_WAITING_IN_LOBBY, MM.STATUS_WAITING_FOR_PARTY, MM.STATUS_IN_GAME, MM.STATUS_CLIENT_DROPPED, \
                                    MM.STATUS_WAITING_GAME_FINISH ]:
                                        touch( acc )
                                    elif progress in [ MM.STATUS_GAME_FINISHED ]: # после окончания сессии разрешаем любоваться на окно pvx статистики подольше
                                        touch( acc, time.time() + MM.AFTER_PVX_TIMEOUT )
                                    elif progress == MM.STATUS_NONE:
                                        # если вдруг все клиенты упали и игра завершена,
                                        # уберем из keepalive, то что мы ставили на предыдущем шаге, поставим текущее время + MM.INGAME_PING_PERIOD
                                        # его достаточно, чтоб если замок жив он начал пинговать нас иначе будем выгружать чувака
                                        touch( acc)

                                    # -------------------------------------------------------------------------------------------------------
                                    # И РАЗБИРАЕМСЯ С ПОДРОБНОСТЯМИ НОВОГО СОСТОЯНИЯ

                                    # не пришел ли нам SessionKey?
                                    if session_id and progress in [MM.STATUS_WAITING_IN_LOBBY]:
                                        session.session_id = session_id
                                        # сейчас именно по статусу 102 будем отправлять отчет о старте игры в статистику
                                        if session.game_id and (not session.start_reported):
                                            self.reportJoinSession( acc, session )
                                            session.start_reported = 1
                                    else:
                                        session.pop("session_id", None) # подпорка: убираем совсем

                                    #-----------------------------------------------------------------------------------------
                                    # не пришли ли нам результаты сессии?
                                    if progress == MM.STATUS_GAME_FINISHED:
                                        if session_results:
                                            if not session.awards_applied:
                                                session.session_results = session_results
                                                hero = acc.model.getHeroByID( session.hero_id )
                                                apply_results_ok = self.applyGameSessionResults( acc, mmid, session.game_id, session_results, session.game_type, hero )
                                                if not apply_results_ok:
                                                    warn( "applyGameSessionResults FAILED for auid=%s, mmid=%s", acc.auid, mmid)
                                                session.awards_applied = 1
                                                session.confirm = MM.CONFIRM_RESULTS_APPLIED

                                        # отсылаем в сторону matchmaker подтверждение, что мы получили и применили результаты
                                        self.doMatchmakingCmd( "close", acc, mmid )

                                    #-----------------------------------------------------------------------------------------
                                    if progress in [MM.STATUS_WAITING_ACCEPT, MM.STATUS_ACCEPTED_PVX, MM.STATUS_WAITING_IN_LOBBY]:
                                        # смейкалось
                                        if progress == MM.STATUS_WAITING_ACCEPT and session.game_type:
                                            try:
                                                autoaccept = ""
                                                if session.game_type == "SPECTATE":
                                                    autoaccept = "SPECTATE"
                                                else:
                                                    map = acc.SD.getObjectByDbid( session.game_type )
                                                    if map and (not map['acceptNeeded']):
                                                        autoaccept = map['mapType']

                                                if autoaccept:
                                                    subParams = ClassDict( mmid=[mmid] )
                                                    mmAcceptAction = MatchmakingAcceptAction( subParams, self.onAutoAcceptTraining, I=self.I, acc=acc, uid=acc.uid )
                                                    mmAcceptAction.onStart() # ответ получаем в onPartyGoMMAddCallback; если кто-то из юзеров пофейлит mm_add, там поставят self.party_ok=0
                                                    info("session progress after auto-accept: %s (auid=%s, autoaccept reason=%s)",
                                                         session.progress, acc.auid, autoaccept)
                                            except:
                                                catch()

                                    elif progress == MM.STATUS_NONE:
                                        self.clearMmSession(session, acc, reason="session progress 0")

                                    # -------------------------------------------------------------------------------------------------------

                            elif mm_session:
                                # хм, в пакете есть сессия, а у нас нету.. это сюрприз.
                                # значит, у pvx есть наши mm-сессии, о которых нам (родному серверу юзера) ничего не известно.
                                # вероятно, какая-то фигня с persistence?.. в общем, грязно ругаемся
                                msg = "[pvx] extra mm session, unknown to Web Server: " + str(mm_session)
                                self.postMmMessage( acc, 0, error=msg )
                                err( msg )

                                # на всякий случай делаем со стороны соц.сервера mm_cancel перечисленных extra-сессий (все равно соц.серверу о них ничего не известно)
                                self.doMatchmakingCmd( "cancel", acc, MM.CANCEL_ALL )

                        else:
                            # !mm_session, какая-то фигня вместо сессии
                            self.clearMmSession(acc.data.mm, acc, reason="bad session ping reply")

                    else:
                        warn( "acc locked/failed: auid=%s, acc.locked=%s, acc.failed=%s" % (auid, acc.locked, acc.failed) )
                else:
                    warn( "no such acc: auid=%s" % auid )
                    ##log("/onMmSessionProgress: acc.data.mm now: " + pretty(acc.data.mm))
            except:
                catch()

    # ----------------------------------------------------------------------------------------------
    def restoreSrcHero(self, session, acc):
        #~ acc.model.write( acc.pending )
        #~ acc.pending.setPrefix( "restoreSrcHero:" )
        #~ acc.model.setComment( "auto" )
        hero_id = session.src_hero_id
        hero = acc.model.getHeroByID(hero_id)

        # Почему-то не дошёл id героя, изначально выбранного в замке
        if hero:
            tsId = hero.ActiveTalentSet
            info("restoreSrcHero(auid=%s, src_hero_id=%s, hero_crc=%s, talentset_id %r)", acc.auid, hero_id, hero.PersistentId, tsId)
            self.fillHeroMatchmakingValues( session, acc, hero_id, acc.getConfig(), tsId )
            acc.model.write( acc.pending )
            acc.model.validateHeroesInMatchmaking(acc)
            if acc.party_id and not acc.partydata.madeAfterBattle:
                # force_change: говорим, что героя надо сменить насильно (чтобы party service не кочевряжился с лишними проверками)
                subrequest = PartyHeroRequest( acc.model, dict( hero_id=[hero_id], hero_crc=[hero.PersistentId], force_change=[1], talent_set_id=[tsId] ), False )
                subaction = Party_hero( subrequest, dumpResponse, subrequest, I=self.I, acc=acc, uid=acc.uid )
                subaction.onStart()
        else:
            warn("Wrong information about src hero was found in session info: %r", hero_id)

    # ----------------------------------------------------------------------------------------------
    # callback, в который сразу получаем ответ на MatchmakingAcceptAction (автоматический accept тренировки)
    def onAutoAcceptTraining(self, response):
        if response and isinstance(response, dict):
            info( "onAutoAcceptTraining( mmid:%s, ok:%s )" % (response.get("mmid"), response.get("ok")) )
        self.autoAcceptResponse = response

    # ----------------------------------------------------------------------------------------------
    # результаты сессии: идут в статистику; по старой схеме в этих же результатах приходили награды
    def applyGameSessionResults(self, acc, mmid, gameid, results, game_type, hero):
        return 1

    def storeSessionRoll(self, acc, session_roll_string):
        try:
            # нужно взять разделы, приехавшие из pvx roll, и аккуратно (по отдельным ключам) вклеить их в хранимый acc.db.session_roll (при этом проставив текущую db_version)
            new_roll = json_loads(session_roll_string)
            for key,value in new_roll.iteritems():
                if isinstance(value, dict):
                    value["db_version"] = MM.ROLL_DB_VERSION
                acc.db.session_roll[key] = value
            debug("stored session roll string %r: acc.db.session_roll now: %s", session_roll_string, PostponePretty(acc.db.session_roll))
        except:
            catch()

    def getMapSessionRollString(self, acc, map_name):
        rollDict = {}
        rollDict["gen_index"] = acc.db.session_roll.get("gen_index", 0)

        # find corresponding roll subtable (mapid -> rollSettings -> modeName)
        modeName = "pvp"
        try:
            map = acc.SD.getObjectByDbid( map_name )
            # if training fwod then get modeName from common roll settings
            if map['mapType'] == "Training" and acc.model.isFirstPlay( map, acc.getConfig() ):
                trainingFWODSettings = acc.SD.getTrainingFwodSettings()
                if trainingFWODSettings:
                    modeName = trainingFWODSettings["modeName"]
            else:
                rollSettings = map["rollSettings"]
                if rollSettings:
                    modeName = rollSettings.get("modeName", modeName)
        except:
            catch()

        rollDict[modeName] = acc.db.session_roll.get(modeName, {})

        return json_dumps(rollDict)


    # разобрать и применить к пользовательской MD, сохранить в persistent
    def applyForgeRoll( self, acc, roll_id, awards, session_roll):
        info("applyForgeRoll( auid=%s, roll_id=%s, awards=%s )", acc.auid, roll_id, awards)
        awards_ok = 0
        awards_total = 0

        # направляем все изменения Model Data в pending changes
        acc.model.write( acc.pending )
        acc.pending.setPrefix( "forgeRoll:" )
        acc.model.setComment( "auto" )

        if isinstance( awards, list ):
            awards_total = len(awards)
            for award in awards:
                if isinstance( award, dict ):
                    award_type = toint( award.get("type") )
                    award_id = toint( award.get("id") )
                    award_count = toint( award.get("count") )

                    if award_type and award_count:
                        if award_type == EAwardType.TALENT:
                            if acc.SD.getStaticTalentByTalentId(award_id):
                                acc.model.addTalent(award_id)
                                awards_ok += 1
                                ## acc.model.addStatisticEvent( 2, str(item.PersistentId), 1 ) -- пока не логаем Forge Roll в статистику
                            else:
                                warn( "bad roll type (auid=%s) talentId=%s" % (acc.auid, award_id) )
                        else:
                            #TODO
                            warn( "roll type not supported! (auid=%s) award_type=%s" % (acc.auid, str(award_type)) )
                else:
                    err( "applyForgeRoll (auid=%s): bad roll (%s)" % (acc.auid, str(award)) )

            if session_roll:
                self.storeSessionRoll( acc, session_roll)

        else:
            err( "applyForgeRoll (auid=%s): bad awards" % acc.auid )

        info("applyForgeRoll (auid=%s): %d/%d awards ok", acc.auid, awards_ok, awards_total)

        if awards_ok:
            # если хоть что-то удалось применить, сохраняем данные юзера
            self.saveUserData( acc )

        return awards_ok or (awards_ok == awards_total) # если хоть что-то удалось применить, уже хорошо; если не было наград - тож ничего

    def unpackGameAwards(self, acc, msg, msg_id, msg_type):
        game_id = msg.get("roll_id", 0) or msg.get("gameid", 0)
        awards = msg.get("awards", [])
        session_roll = msg.get("session_roll", "")

        game_type = str(msg.get("game_type", ""))
        playerWin = toint(msg.get("playerWin", 0))
        playerLeaver = toint(msg.get("playerLeaver", 0))
        customGame = toint(msg.get("customGame", 0))
        scoring = msg.get("scoring",{})
        extra = msg.get("extra",{})
        tamburFight = toint(msg.get("tambur_fight",0))
        guildGame = bool(toint(extra.get("isGuildFight", 0)))

        appliedRollBuffs = msg.get("applied_roll_buffs", [])
        info("[SessionAwardsMailAction] applied buffs: %r", appliedRollBuffs)
        appliedRollBuffs = [ toint(crc32(buffId)) for buffId in appliedRollBuffs ]

        self.CCU["session_awards"] += 1

        acc.db.game_awards = acc.db.game_awards or {}
        str_game_id = str(game_id)
        prev_ts = acc.db.game_awards.get( str_game_id )
        if not prev_ts:
            acc.db.game_awards[ str_game_id ] = toint( time.time() )

            self.applyGameAwards(acc, game_id, awards, session_roll,
                                      game_type, playerWin, playerLeaver, customGame,
                                      scoring, tamburFight, appliedRollBuffs, guildGame, extra)

            # раз уж чего-то новое получили, давайте заодно повыкинем протухшие "ярлыки о получении наград"
            self.weedTimestamps(acc.db.game_awards, "game_awards", acc.auid, expire_period=24*60*60)
            acc.pending_changes.append( {"message":{ msg_id: dict(type=msg_type, game_id=game_id) }} )
        else:
            warn("unpackGameAwards (msg_id=%s, auid=%s): awards already received for game_id=%s (prev_ts %s), awards skipped" \
             % (msg_id, acc.auid, game_id, prev_ts))
    # ----------------------------------------------------------------------------------------------
    # разобрать и применить к пользовательской MD, сохранить в persistent
    def applyGameAwards(self, acc, gameid, awards, session_roll, game_type, playerWin, playerLeaver, customGame,
                        scoring, tamburFight, rollBuffs, guildFight, extra):
        info("applyGameAwards( auid=%s, gameid=%s, awards=%s, game_type=%s, playerWin=%s, playerLeaver=%s, "
             "customGame=%s, scoring=%r, tamburFight=%r, guildFight=%r, aplliedRollBufs=%r, extra=%r )",
              acc.auid, gameid, awards, game_type, playerWin, playerLeaver, customGame, scoring, tamburFight,
              guildFight, rollBuffs, extra)
        awards_ok = 0
        awards_total = 0
        session_tutorial_quest_added = False

        debug ("applyGameAwards: playerWin=%s(%s), if playerWin == %s", playerWin, type(playerWin), "true" if playerWin else "false" )

        # направляем все изменения Model Data в pending changes
        acc.model.write( acc.pending )
        acc.pending.setPrefix( "gameResults:" )
        acc.model.setComment( "auto")

        if not playerLeaver and not customGame:
            acc.model.addStatisticEvent( StatisticEventType.SESSION_FINISH, str(game_type), playerWin )
            if extra.get("tutorialSkipped"):
                #обратная совместимость для старого порядка запуска сессионного туториала (из замка):
                # если мы попали сюда из BattleQuestAdded (или его производных), то надо добавить квест
                debug("applyGameAwards: skip tutorial pressed - current tutorial state is %s -> TutorialState.Skipped ", enum2String(TutorialState, acc.model.LordInfo.TutorialState))
                if acc.model.LordInfo.TutorialState >= TutorialState.BattleQuestAdded and acc.model.LordInfo.TutorialState <= TutorialState.ClientReturnedFromSession:
                    self.onUserSkipTutorial(acc)
                    session_tutorial_quest_added = True

                acc.model.LordInfo.TutorialState = TutorialState.Skipped
            elif acc.model.LordInfo.TutorialState != TutorialState.Completed:
                #это странное условие означает, что мы успешно прошли сессионный туториал
                debug("applyGameAwards: acc.model.LordInfo.TutorialState != TutorialState.Completed %s -> TutorialState.RewardsReceived ", enum2String(TutorialState, acc.model.LordInfo.TutorialState))
                acc.model.LordInfo.TutorialState = TutorialState.RewardsReceived
                self.I.STATS.addTutorialStateChange( acc.auid, enum2String(TutorialState, acc.model.LordInfo.TutorialState) )
        elif not acc.model.isTutorialComplete():
                debug("applyGameAwards: not acc.model.isTutorialComplete() %s -> TutorialState.BattleQuestAdded", enum2String(TutorialState, acc.model.LordInfo.TutorialState))
                #а это - что сессионный туториал запущеный по старой схеме (из замка) не был завершен или проскипан
                acc.model.LordInfo.TutorialState = TutorialState.BattleQuestAdded
                self.I.STATS.addTutorialStateChange( acc.auid, enum2String(TutorialState, acc.model.LordInfo.TutorialState) )

        if acc.model.Statistics.StartSessionByGate and not playerLeaver:
            acc.model.Statistics.SessionsEndedByGate += 1
            acc.model.Statistics.StartSessionByGate = False

        # Проверим на ливерство, чтобы если что записать в статистику
        leaverStatusBefore = False
        leaverPointReason = ""
        leaverPointsChange = 0
        if not customGame:
            leaverStatusBefore = acc.model.LordInfo.GuardInfo.isLeaver
            leaverPointReason, leaverPointsChange = acc.model.changeLeaverStatus(acc, game_type, playerLeaver, extra, self.I )


        # HACK to fix PF-77858
        realComplaints = acc.model.LordInfo.ComplaintsLeft
        acc.model.LordInfo.ComplaintsLeft = realComplaints-42 # заранее не равное значение
        acc.model.LordInfo.ComplaintsLeft = realComplaints

        # запишем информацию о последнем бое, нужна динамическим квестам
        acc.model.Statistics.LastSessionInfo.GameType = str(game_type)
        acc.model.Statistics.LastSessionInfo.IsWinner = bool(playerWin)
        acc.model.Statistics.LastSessionInfo.PickedHero = 0
        acc.model.Statistics.LastSessionInfo.IsGuildGame = guildFight

        # прибавляем результаты сессии(число убийств, поддержки и пр.) к SummarySessionResults.
        if isinstance(scoring, dict):
            # увеличиваем счетчик полученных результатов
            acc.model.Statistics.TotalSessionResultsReceived += 1
            sumsr = acc.model.Statistics.SummarySessionResults
            lastsr = acc.model.Statistics.LastSessionResults
            maxsr = acc.model.Statistics.MaxSessionResults
            for attr in scoring:
                # пытаемся конвертировать полученное значение во float или int
                nval = scoring.get( attr, 0 )
                if digit(nval):
                    nval = toint( nval )
                elif testfloat(nval):
                    nval = tofloat( nval )
                else:
                    warn( "unable to detect scoring attribute's (%r) value as float or int. using 0 value" % attr )
                    nval = 0

                # ищем соответсвие по полям объектов MD/ключам присланного json

                # добавляем результаты к суммарной статистике
                if hasattr( sumsr, attr ):
                    sumval = getattr( sumsr, attr )
                    setattr( sumsr, attr, sumval + nval )

                # записываем результаты в поле последней игры
                if hasattr( lastsr, attr ):
                    setattr( lastsr, attr, nval )

                # проверяем не обновился ли максимум
                if hasattr( maxsr, attr ):
                    maxval = getattr( maxsr, attr )
                    setattr( maxsr, attr, max( maxval, nval ) )

        winhero = None

        if isinstance( awards, list ):
            awards_total = len(awards)

            stats = ClassDict( inc_silver=0, new_silver=0, inc_reliability=0, \
                     new_reliability=0, hero_id=0, talents=[], priceInc = acc.model.createResourcesTable(), force=0.0, rune = 0 )

            applyDodges = False
            guardFight = False
            count_award_talents = 0
            for award in awards:
                if isinstance( award, dict ):
                    award_type = toint( award.get("type") )
                    award_id = toint( award.get("id") )
                    award_count = toint( award.get("count") )
                    award_count_float = tofloat( award.get("count") )


                    ## info( "applying GameSessionResults (auid=%s): type %d, id %d, count %d" % (acc.auid, award_type, award_id, award_count) )

                    if award_type:
                        try:
                            if award_type in [EAwardType.SILVER, EAwardType.RELIABILITY,
                                                EAwardType.RESOURCE1, EAwardType.RESOURCE2, EAwardType.RESOURCE3,
                                                EAwardType.PEARL, EAwardType.CWPOINTS_PLAYER, EAwardType.RED_PEARL,
                                              EAwardType.SHARD, EAwardType.CUSTOM_CURRENCY]:
                                # изменения на уровне ModelData
                                if award_type == EAwardType.SILVER:
                                    stats.priceInc.Silver += award_count
                                elif award_type == EAwardType.RELIABILITY:
                                    acc.model.LordInfo.Reliability += award_count
                                    stats.inc_reliability += award_count
                                    stats.new_reliability = acc.model.LordInfo.Reliability
                                elif award_type == EAwardType.RESOURCE1:
                                    stats.priceInc.Resource1 += award_count
                                elif award_type == EAwardType.RESOURCE2:
                                    stats.priceInc.Resource2 += award_count
                                elif award_type == EAwardType.RESOURCE3:
                                    stats.priceInc.Resource3 += award_count
                                elif award_type == EAwardType.PEARL:
                                    stats.priceInc.Perl += award_count
                                elif award_type == EAwardType.RED_PEARL:
                                    stats.priceInc.RedPerl += award_count
                                elif award_type == EAwardType.CWPOINTS_PLAYER:
                                    stats.priceInc.CWPoints_Player += award_count
                                elif award_type == EAwardType.SHARD:
                                    stats.priceInc.Shard += award_count
                                elif award_type == EAwardType.CUSTOM_CURRENCY:
                                    currency_id = award.get("customCurrencyId", None)
                                    debug("got custom currency %s in awards", currency_id)
                                    if currency_id:
                                        if currency_id in stats.priceInc.Currencies:
                                            stats.priceInc.Currencies[currency_id] += award_count
                                        else:
                                            stats.priceInc.Currencies[currency_id] = award_count
                                awards_ok += 1

                            elif award_type == EAwardType.TALENT:
                                if acc.SD.getStaticTalentByTalentId(award_id):
                                    item = acc.model.addTalent(award_id)
                                    stats.talents.append( TalentInfo( item.PersistentId, item.getID(), 0 ) )
                                    awards_ok += 1
                                    count_award_talents += 1
                                    acc.model.addStatisticEvent( StatisticEventType.SESSION_TALENT, str(item.PersistentId), 1 )
                                else:
                                    warn( "bad award (auid=%s) talentId=%s" % (acc.auid, award_id) )

                            elif award_type in [EAwardType.EXPERIENCE, EAwardType.HERO_ENERGY, EAwardType.HERO_RATING]:
                                # изменения на уровне конкретного героя
                                if not winhero:
                                    winhero, winhero_id = acc.model.findHeroByCrc32( award_id )
                                hero, hero_id = acc.model.findHeroByCrc32( award_id )
                                if hero:
                                    if award_type == EAwardType.EXPERIENCE:
                                        hero.changeExperience( award_count, acc.model, self.I.WS, acc, self.I )
                                    elif award_type == EAwardType.HERO_RATING:
                                        hero_prev_rating = hero.Rating
                                        hero.changeRating( award_count_float, self.I, acc )
                                        start_league = acc.SD.getCurrentSeasonLegendLeague()
                                        if start_league and (hero.Rating >= start_league["minRating"] or hero_prev_rating >= start_league["minRating"]):
                                            self.I.EXPORT.updateLegendRatingInfo(acc.auid, hero.PersistentId, hero.Rating, acc.nick, acc.SD.getCurrentSeasonId())
                                        self.I.EXPORT.getLegendRatingInfo(hero.PersistentId, acc.db.auid, acc.SD.getCurrentSeasonId(), self.onReceiveLegendInfo)
                                        hero.lastPlayed = toint( time.time() ) # отметим, что играли этим героем (но только если изменился рейтинг, т.е. поучаствовали в pvp)
                                        stats.hero_id = hero.PersistentId
                                        stats.force = hero.TalentSets[hero.ActiveTalentSet].Force
                                        self.I.STATS.addRatingChange(acc.auid, RatingType.HeroRating, gameid, hero.PersistentId, award_count_float, hero.Rating)
                                        # Сбросим время последней игры, если последний раз пользователь играл недавно
                                        ratingLossLevel = acc.SD.getRatingToLooseLevel(acc.model.LordInfo.LastRankedGameTime)
                                        if not ratingLossLevel:
                                            acc.model.LordInfo.LastRankedGameTime = hero.lastPlayed

                                        if award_count_float != 0:
                                            info( "update guild rating with %d" % hero.Rating )
                                            callback = functools.partial( self.onGuildCallback, acc=acc )
                                            self.I.GS.changeHeroRating( acc, hero.Rating, hero.PersistentId, hero.Rating, callback )
                                        else:
                                            info( "skip update hero rating: win: %r, leaver: %r, rating: %r" % ( playerWin, playerLeaver, award_count_float ) )

                                    awards_ok += 1
                                else:
                                    warn( "bad award (auid=%s) hero_crc32=%s" % (acc.auid, award_id) )

                            elif award_type == EAwardType.FAME:
                                acc.model.addFame(award_count, acc, acc.SD, self.I.STATS)
                                awards_ok += 1

                            elif award_type == EAwardType.LORD_RATING:
                                acc.model.changeRating( award_count_float )
                                #self.I.STATS.addRatingChange( acc.auid, RatingType.LordRating, gameid, 0, award_count_float, acc.model.getRating() )
                                awards_ok += 1

                            elif award_type == EAwardType.GUARD_RATING:
                                guardFight = True # считаем, что бой гвардейский, если нам начисляют GUARD_RATING
                                acc.model.changePublicRating( award_count_float )
                                self.I.STATS.addRatingChange( acc.auid, RatingType.GuardRating, gameid, 0, award_count_float, acc.model.getPublicRating() )
                                awards_ok += 1

                            elif award_type == EAwardType.DODGE_POINTS:
                                applyDodges = True
                                if playerLeaver:
                                    acc.model.addDodges(0, self.I.WS, acc)
                                else:
                                    acc.model.addDodges(award_count, self.I.WS, acc)
                                awards_ok += 1

                            elif award_type == EAwardType.NEW_SEED:
                                acc.db.seed = award_count
                                awards_ok += 1

                            elif award_type == EAwardType.MARKETING_EVENT:
                                event_item = acc.SD.getMarketingEventRollItem(award_id)
                                if not event_item:
                                    warn("cannot resolve id %d as valid event" % award_id)
                                else:
                                    acc.model.applyMarketingEvent(event_item, acc.getConfig().LampEventSettings)
                                    stats.rune = acc.model.getGoldLampType(acc.SD)
                                    self.I.STATS.addLampRoll(acc.auid, stats.rune, RuneRollSource.SessionDrop, gameid)
                                awards_ok += 1
                            elif award_type == EAwardType.CWPOINTS_CLAN:
                                # обновляем данные по конкретному клану в GuildService
                                 stats.priceInc.CWPoints_Clan += award_count
                                 info( "update guild member rating with %d" % award_count)
                                 callback = functools.partial( self.onGuildCallback, acc=acc )
                                 self.I.GS.changeMemberRating( acc, award_count, callback )
                            else:
                                #TODO
                                warn("award type not supported! (auid=%s) award_type=%s" % (acc.auid, str(award_type)))

                        except:
                            catch()
                            err("exception in award (auid=%s, award_type=%s), skipped" % (acc.auid, str(award_type)))
                else:
                    err("applyGameAwards (auid=%s): bad award (%s)" % (acc.auid, str(award)))

            if session_roll:
                self.storeSessionRoll(acc, session_roll)

            if tamburFight and (not applyDodges):
                acc.model.clearDodges()

            # прибавим все полученные ресурсы:
            if not acc.getConfig().GUILD_WARS_ENABLED:
                cwp, stats.priceInc.CWPoints_Player = stats.priceInc.CWPoints_Player, 0
                acc.model.sell(stats.priceInc, acc)
                stats.priceInc.CWPoints_Player = cwp
            else:
                acc.model.sell(stats.priceInc, acc)

            # логируем в статистику
            acc.model.addStatisticEvent(StatisticEventType.SESSION_RESOURCE, "Resource1", stats.priceInc.Resource1)
            acc.model.addStatisticEvent(StatisticEventType.SESSION_RESOURCE, "Resource2", stats.priceInc.Resource2)
            acc.model.addStatisticEvent(StatisticEventType.SESSION_RESOURCE, "Resource3", stats.priceInc.Resource3)

            acc.model.addStatisticEvent(StatisticEventType.SESSION_RESOURCE, "Silver", stats.priceInc.Silver)
            acc.model.addStatisticEvent(StatisticEventType.SESSION_RESOURCE, "Perl", stats.priceInc.Perl)
            acc.model.addStatisticEvent(StatisticEventType.SESSION_RESOURCE, "RedPerl", stats.priceInc.RedPerl)
            acc.model.addStatisticEvent(StatisticEventType.SESSION_RESOURCE, "Shard", stats.priceInc.Shard)

            for k,v in stats.priceInc.Currencies.iteritems():
                debug("add statistic event for custom currency %s", k)
                acc.model.addStatisticEvent(StatisticEventType.SESSION_RESOURCE, "Currency:"+k, v)

            eventType = StatisticEventType.SESSION_RESOURCE
            if guildFight:
                eventType = StatisticEventType.GUILD_SESSION_RESOURCE
            acc.model.addStatisticEvent(eventType, "CWPoints_Player", stats.priceInc.CWPoints_Player)
            acc.model.addStatisticEvent(eventType, "CWPoints_Clan", stats.priceInc.CWPoints_Clan)


            if acc.guilddata and (stats.priceInc.CWPoints_Player != 0 or stats.priceInc.CWPoints_Clan != 0):
                self.I.STATS.addGuildPointsChange(acc.guilddata.GuildAuid, acc.auid, 'Session',
                                                  stats.priceInc.CWPoints_Player,
                                                  acc.model.Resources.CWPoints_Player + stats.priceInc.CWPoints_Player,
                                                  stats.priceInc.CWPoints_Clan,
                                                  acc.guilddata.GuildInfo.CWPoints_Clan + stats.priceInc.CWPoints_Clan)

            # зальем выжимку из результатов в статистику
            self.I.STATS.addGiveSessionAwards(acc.auid, gameid, acc.nick, stats.hero_id, stats.priceInc, acc.model.Resources,
                stats.inc_reliability, stats.new_reliability, stats.talents, stats.force, stats.priceInc.CWPoints_Clan,
                acc.guilddata.GuildInfo.CWPoints_Clan + stats.priceInc.CWPoints_Clan, rollBuffs, leaverPointsChange,
                acc.model.LordInfo.GuardInfo.LeavesPoint, acc.model.LordInfo.GuardInfo.isLeaver != leaverStatusBefore,
                acc.model.LordInfo.GuardInfo.isLeaver, leaverPointReason, acc.model.LordInfo.GuardInfo.isBadBehaviour
                )

            # зальём инфу по кастомной валюте
            self.I.STATS.addResourcesChange(acc.auid, True, ResourceChangeItem.Session,
                                            "", stats.priceInc,
                                            acc.model.Resources, customCurrenciesOnly=True)

        else:
            warn("applyGameAwards (auid=%s): bad awards" % acc.auid)

        debug("applyGameAwards winhero %r", winhero )
        if winhero:
            acc.model.Statistics.LastSessionInfo.PickedHero = winhero.PersistentId
            # Квесты проверяем только если игра была не на тренировочной карте и не договорная.
            acc.model.validateDynamicQuests(acc, self.I)
            if not customGame:
                # PF-102201 Добавляем поля для квеста на боссов
                extra["numBossKillsAssist"] = toint(scoring.get("numBossKillsAssist", 0))
                extra["numCatKillAssist"] = toint(scoring.get("numCatKillAssist", 0))
                extra["numDragonKillAssist"] = toint(scoring.get("numDragonKillAssist", 0))
                acc.model.tryCompleteAfterSessionObjectives(extra)

            isPvpSession = 0
            # проверяем, является ли указанный game_type "рейтинговой" pvp-картой
            map = acc.SD.getObjectByDbid( game_type )
            debug("applyGameAwards map %r", dict(map) )
            try:
                if map and (map['mapType'] in ("CTE", "PvP")):
                    info("applyGameAwards( auid=%s, game_type=%s ): mapType %r -> pvp map" % (acc.auid, game_type, map['mapType']))
                    isPvpSession = 1
                if playerWin and not playerLeaver and not customGame:
                    acc.model.setFirstWinIfNeed(map, acc.getConfig())
            except:
                catch()


            debug("applyGameAwards isPvpSession %r", isPvpSession )
            if isPvpSession:
                # добавляем результат партии в историю побед/поражений
                score = "0"
                if playerWin:
                    score = "1"
                hist_string = score + acc.db.win_lose_hist
                if len(hist_string) > MM.MAX_WIN_LOSE_LENGTH:
                    hist_string = hist_string[:MM.MAX_WIN_LOSE_LENGTH]
                acc.db.win_lose_hist = hist_string
                if not playerLeaver:
                    prevRating = acc.model.getPlayerRating()
                    if playerWin:
                        acc.model.addWin(winhero, map, acc.getConfig())
                    else:
                        acc.model.addLose(winhero, map, acc.getConfig())
                    pRating = acc.model.getPlayerRating()
                    change = pRating - prevRating
                    if change > 0:
                        self.I.STATS.addRatingChange( acc.auid, RatingType.LordRating, gameid, 0, change, pRating )
                else:
                    acc.model.breakEpicWinsStrike(winhero)
                debug("ApplyGameAwards acc.party_id: %r", acc.party_id)
                if acc.party_id:
                    self.I.PS.updatePartyLeaverInfo(acc.auid, acc.party_id, True if LordStatus.Leaver == acc.model.getInternalUserStatus(acc.getConfig()) else False, self.I.WS.onDummyResponseCallback)
                    tournamentDynQuestId, dependedTournamentQuests = acc.model.getActualTournamentQuestPersistentId()
                    self.I.PS.updatePartyTournamentInfo(acc.auid, acc.party_id, tournamentDynQuestId, dependedTournamentQuests, self.I.WS.onDummyResponseCallback)

            else:
                acc.model.breakEpicWinsStrike(winhero)

        buffs_to_update = rollBuffs
        hero_id = winhero.PersistentId if winhero else 0
        enabled_buffs = self.guildBonusProcessor.getModifiersFromGuildBuffs(acc, hero_id, game_type)
        if enabled_buffs['pass'] and guildFight:
            pass_persistent_id = crc32(enabled_buffs['pass'][0])
            buffs_to_update.append(pass_persistent_id)
        # Если клановые войны не включены, баффы не трогаем
        if acc.getConfig().GUILD_WARS_ENABLED:
            acc.model.checkGuildBufsAfterSession(playerWin, acc.SD, buffs_to_update)

        info("applyGameAwards (auid=%s): %d/%d awards ok" % (acc.auid, awards_ok, awards_total))
        ## info( "pending model changes (auid=%s): %s" % (acc.auid, str(acc.pending_changes)) )
        if cfg.TOURNAMENT_SERVER and cfg.TOURNAMENT_APPLY_RESULTS:
            isPvpSession = 0
            map = acc.SD.getObjectByDbid( game_type )
            try:
                if map and (map['mapType'] in ["CTE", "PvP"]):
                    isPvpSession = 1
            except:
                pass

            if isPvpSession:
                if playerWin:
                    acc.model.TournamentInfo.TournamentTicket.Wins += 1
                else:
                    acc.model.TournamentInfo.TournamentTicket.Losses += 1
                    if acc.model.TournamentInfo.TournamentTicket.Losses >= acc.getConfig().DEFEATS_COUNT_FOR_KICK_FROM_TOURNAMENT:
                        acc.model.TournamentInfo.TournamentTicket.State = TicketState.TournamentLost
                acc.model.TournamentInfo.TournamentTicket.GameDurations.append( acc.model.Statistics.LastSessionResults.timeElapsed )
                startTime = int( time.time() ) - acc.model.Statistics.LastSessionResults.timeElapsed
                acc.model.TournamentInfo.TournamentTicket.SessionInfo.append(str(startTime) + "#" + str(gameid))
                if (int(time.time()) - acc.model.TournamentInfo.TournamentTicket.LastGameTime) > acc.getConfig().TournamentSettings.HOURS_FOR_MISS*60*60:
                    acc.model.TournamentInfo.TournamentTicket.MissedGames += int((int(time.time()) - acc.model.TournamentInfo.TournamentTicket.LastGameTime)/(acc.getConfig().TournamentSettings.HOURS_FOR_MISS*60*60))
                acc.model.TournamentInfo.TournamentTicket.LastGameTime = int( time.time() )
                acc.model.TournamentInfo.TournamentTicket.IsSynchronized = False
                acc.model.TournamentInfo.sendTournamentTicket( acc, self.I.HTTP )

                awards_ok += 1

        if awards_ok > 0 or session_tutorial_quest_added:
            # если хоть что-то удалось применить, сохраняем данные юзера
            self.saveUserData(acc)

        return awards_ok or (awards_ok == awards_total) # если хоть что-то удалось применить, уже хорошо; если не было наград - тож ничего


    # helper
    def subscribeAccToPersonServer( self, acc, fame ):
        if acc.auid:
            fame = fame or acc.getFame()
            info( "subscribeAccToPersonServer: nick %r, nick type: %s, model Fame: %s, locale=%s" % (acc.nick, type(acc.nick), fame, acc.locale) )
            party_fraction = party_const.getPartyFraction( acc.db.fraction )
            callback = functools.partial( self.onFriendListCallback, uid=acc.uid )
            self.I.PS.subscribe( acc.auid, acc.snid, acc.snuid, acc.uid, acc.nick, acc.photoUrl, fame, party_fraction, acc.db.sex, options.server_id,  \
              acc.locale or cfg.MATCHMAKER_DEFAULT_LOCALE, callback )

    # helper
    def subscribeAccToGuildServer(self, acc):
        if acc.db.guildAuid:
            info( "subscribeAccToGuildServer: auid=%r locale=%s", acc.auid, acc.locale )
            callback = functools.partial( self.onGuildDataCallback, uid=acc.uid )
            self.I.GS.subscribe( acc, acc.snid, acc.snuid, acc.uid, options.server_id, acc.locale or cfg.MATCHMAKER_DEFAULT_LOCALE, callback )
            acc.db.oldAuid = 0
        else:
            self.I.AGG.setProperty( acc.auid, "guildshortname", urlQuote("-"), callback=self.onDummyResponseCallback )


    # helper
    #FIXME: no usages found!
    def addFriendToPersonServer(self, acc, friend_auid):
        if acc.auid:
            info( "addFriendToPersonServer: from %r to friend_auid %r " % (acc.nick, friend_auid) )
            self.I.PS.addFriend( acc.auid, friend_auid, self.onDummyResponseCallback )


    # helper
    def updateGameDataToPersonServer(self, acc, hero=None):
        if acc.auid:
            fame = acc.getFame()
            info( "updateGameDataToPersonServer: nick %r, nick type: %s, model Fame: %s" % (acc.nick, type(acc.nick), fame) )
            party_fraction = party_const.getPartyFraction( acc.db.fraction )
            hero_id = 0
            hero_lvl = 0
            hero_force = 0
            hero_rating = 0.0
            if hero:
              hero_id = hero.getID()
              hero_lvl = acc.SD.getHeroExpLevel( hero.Experience ) + 1
              hero_force = hero.TalentSets[hero.ActiveTalentSet].Force
              hero_rating = hero.Rating

            self.I.PS.updateGameData( acc.auid, acc.nick, fame, party_fraction, acc.locale or cfg.MATCHMAKER_DEFAULT_LOCALE, hero_id, hero_lvl,
                                      hero_force, hero_rating, acc.db.sex, self.onDummyResponseCallback )

    # helper
    def updatePartyDodge(self, acc):
        if acc.auid:
            banEndTime = acc.model.getBanEndTime()
            if banEndTime <= int( time.time() ):
                banEndTime = 0
            info( "updatePartyDodge: auid %r, model banEndTime: %s, acc.party_id %s", acc.auid, banEndTime, acc.party_id )
            if acc.party_id:
                self.I.PS.updatePartyDodge( acc.auid, options.server_id, banEndTime, acc.party_id, self.onDummyResponseCallback )


    def onGuildDataCallback(self, response, uid=0):
        if uid:
            acc = users.get(uid)
            acc.db.oldAuid = 0
        if response:
            guildAuid = response.get("guildAuid") or 0
            errMessage = response.get("error") or None

            if guildAuid and self.get("GuildWarEventData") and self.I.Config.getMainConfig().GUILD_WAR_EVENT_ENABLED:
                self.I.GS.notifyGuildWarEventChanged(guild_auids=[guildAuid],
                                                     event_id=self.GuildWarEventData.EventIndex,
                                                     callback=self.onNotifyGuildWarEventChangedReply)
            elif not guildAuid and errMessage is None:
                self.I.GS.unsubscribe( acc, options.server_id, self.onDummyResponseCallback )
                acc.db.guildAuid = 0

                #и плюшки от гильдии конфискуем!
                acc.model.write( acc.pending )
                acc.pending.setPrefix( "resetGuild:" )
                acc.model.setComment( "auto" )
                acc.model.resetGuild( self.I, acc)

            self.onGuildCallback( response, acc )
            acc.model.validateGuildTalentsAfterSnLogin(acc)
        else:
            warn("bad onGuildDataCallback response")


    # обработать возвращаемый список френдов, кинуть юзеру в pending_events
    def onFriendListCallback(self, response, uid=0):
        if uid:
            acc = users.get(uid)
        if response:
            friends_dict = pathFind(response, "get_friends")
            if isinstance(friends_dict, dict):
                friend_keys = friends_dict.keys()
            else:
                friend_keys = []
            info( "onFriendListCallback response (uid=%s, auid=%s): friend_keys %s", uid, getattr(acc, "auid", 0), friend_keys)

            friend_list = response.get("get_friends") or {}
            friends_model_changes = response.get("FriendsData") or []
            party_model_changes = response.get("PartyData") or []
            msg_id = toint( response.get("msg_id") )
            debug("onFriendListCallback before friend_list %s\nfriends_model_changes %s", friend_list, friends_model_changes)
            if acc:
                acc.db.CountOfAllFriends = len(friend_keys)
                acc.db.CurrBeginOfFriendsPage = 0
                f_l, f_m_c = friend_list, copy.deepcopy(friends_model_changes)
                if len(friend_list) > acc.getConfig().FRIENDS_PAGE_SIZE:
                    f_l, f_m_c = self.getPageFromFriendChanges(acc, friend_list, f_m_c )
                acc.sendedFriends = f_l.keys() or []
                acc.isSendedFriends = False
                self.postPendingEvent( acc, {"friends": { "get_friends": f_l, "msg_id": msg_id, "FriendsData": f_m_c }} )
                self.postPendingEvent( acc, {"party": { "msg_id": msg_id, "PartyData": party_model_changes }} )

                try:
                    debug( "onFriendListCallback after friend_list %s\nfriends_model_changes %s", friend_list, friends_model_changes)
                    ModelChangeApplicator.apply( acc, "BufferFriendsData", FriendsData, friends_model_changes )
                    ModelChangeApplicator.apply( acc, "friendsdata", FriendsData, f_m_c )
                    ModelChangeApplicator.apply( acc, "partydata", PartyData, party_model_changes )
                except:
                    catch()

        else:
            warn( "bad onFriendListCallback response (uid=%s): %r", uid, response )

    def getPageFromFriendChanges(self, acc, friend_list, friends_model_changes):
        res = friends_model_changes[:]
        f_m_c =  res[0]["init_friends"][0][2]
        f_l = dict(friend_list)
        debug("getPageFromFriendChanges %s", f_l)
        f_l_k = sorted(f_l.keys())[:acc.getConfig().FRIENDS_PAGE_SIZE]
        f_m_c1 = pathFind(f_m_c, "FriendsData/FriendsKeeper/Keeper")
        f_m_c2 = pathFind(f_m_c, "FriendsData/myFriends/Set")
        for key in f_m_c1.keys():
            #debug("getPageFromFriendChanges key=%s", key)
            if key not in f_l_k and acc.db.auid != key:
                if key in f_m_c1:
                    del f_m_c1[key]
                if key in f_m_c2:
                    del f_m_c2[key]
                if key in f_l:
                    del f_l[key]
                else:
                    warn("getPageFromFriendChanges unknown key: %r in friend_list", key)

        return f_l, res


    # ---------------------------------------------
    def getDecoratedNickname(self, acc):
        decorated = utf8convert( acc.nick )
        fd = getattr(acc, "friendsdata", None)
        if fd:
            me = fd.getFriendByID( acc.auid )
            if me:
                info("getDecoratedNickname(auid=%s): nick %r, guildshortname %r", acc.auid, acc.nick, me.guildshortname)
                if me.guildshortname:
                    decorated = "[" + utf8convert( me.guildshortname ) + "]" + utf8convert( acc.nick )
        return decorated

    #def getGlobalChatName(self, acc):
    #    intFraction = party_const.getPartyFraction(acc.db.fraction)
    #    return "global%s%d" % (acc.locale, intFraction)

    def getGuildChatName( self, guildAuid ):
        return 'guild_%s' % guildAuid

    def getGroupChatName( self, group_id):
        return 'group_%s' % group_id

    # ---------------------------------------------
    # обновляем статус "клиент живой и в замке" для person_server
    def updateKeepaliveState(self, acc, online=False, now=0):
        if acc:
            if online:
                if not acc.in_castle:
                    # до этого считался "не в замке"; извещаем PS
                    acc.in_castle = 1
                    self.I.PS.inCastle( acc.auid, acc.in_castle )
                    # добавляем в мировой чат
                    self.I.CHAT.addUserGlobalGroups(acc.auid, self.onDummyResponseCallback)
                    if acc.db.guildAuid:
                        self.I.CHAT.addUserGroup(acc.auid, self.getGuildChatName(acc.db.guildAuid), self.onDummyResponseCallback)
                acc.ts_incastle = now

            else:
                if acc.in_castle:
                    if acc.ts_incastle + self.IN_CASTLE_TIMEOUT < now:
                        # довольно давно уже не отмечался; сбрасываем статус и извещаем PS
                        acc.in_castle = 0
                        self.I.PS.inCastle( acc.auid, acc.in_castle )
                        # убираем из мирового чата
                        self.I.CHAT.removeUserGlobalGroups(acc.auid, self.onDummyResponseCallback)
                        if acc.db.guildAuid:
                            self.I.CHAT.removeUserGroup(acc.auid, self.getGuildChatName(acc.db.guildAuid), self.onDummyResponseCallback)

            if acc.db.muted and 0 < acc.db.mutetime <= int(time.time()):
                self.I.PS.mute( acc.auid, 0 )
                acc.db.muted = 0
                acc.db.mutetime = 0
                acc.db.mutereason = ""
    # ----------------------------------------------------------------------------------------------
    # оставляем юзеру matchmaking-соообщение (все дополнительные keyword arguments, напр. warning="xx...", error="yy..", добавятся в "словарик сообщения")
    def postMmMessage(self, acc, mmid, **kwargs):
        if not options.shipping: # mm_messages работают только при --shipping=0
            acc.data.mm_messages = acc.data.mm_messages or []
            dct = dict(kwargs)

            # проверим, нет ли уже дубликата
            if acc.data.mm_messages:
                for msg in acc.data.mm_messages:
                    if msg and ( msg.get("mmid", "x") == mmid ) and ( dct.get("error", "y") == msg.get("error", "n") ):
                        # одинаковые непустые сообщения с одинаковым mmid: skip
                        return

            dct["mmid"] = mmid
            dct["ts"] = "%.3f" % time.time()
            acc.data.mm_messages.append( dct )

    # ----------------------------------------------------------------------------------------------
    def onMmSessionAccept(self, dct):
        # вообще, надо бы донести до юзера, что pvx не принял его accept (и почему?..)
        for auid, session_result in dct.iteritems():
            acc = self.getUserAccByAuid( toint(auid) )
            if acc:
                if not session_result:
                    mmid = 0
                    if acc.mm:
                        mmid = acc.mm.mmid
                    self.postMmMessage( acc, mmid, error="[pvx] mm session not accepted" )
            else:
                warn( "onMmSessionAccept: no acc for auid=%s" % auid )


    # ----------------------------------------------------------------------------------------------
    def onMmSessionCancel(self, dct):
        # вообще, надо бы донести до юзера, что pvx не принял его cancel (и почему?..)
        for auid, session_result in dct.iteritems():
            acc = self.getUserAccByAuid( toint(auid) )
            if acc:
                if not session_result:
                    mmid = 0
                    if acc.mm:
                        mmid = acc.mm.mmid
                    self.postMmMessage( acc, mmid, error="[pvx] mm session could not be canceled" )
            else:
                warn( "onMmSessionCancel: no acc for auid=%s" % auid )


    # ----------------------------------------------------------------------------------------------
    def onMmServerStatus(self, dct):
        debug("onMmServerStatus %r", dct)
        self.mmServerStatus.accept_timeout = dct.get("accept_timeout", MM.PVX_ACCEPT_TIMEOUT)
        self.mmServerStatus.average_mm_time = dct.get("average_mm_time", MM.PVX_AVERAGE_MM_TIME)
        self.mmServerStatus.average_mm_time_ext = dct.get("average_mm_time_ext", {})
        self.mmServerStatus.reconnect_timeout = dct.get("reconnect_timeout", MM.PVX_RECONNECT_TIMEOUT)
        self.mmServerStatus.guard_lobby_timeout = dct.get("guard_lobby_timeout", MM.PVX_GUARD_LOBBY_TIMEOUT)
        self.mmDebugStatus = dct.get("mm_debug_status", self.mmDebugStatus)
        #TODO: network_delay?


    # ----------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------
    def registerLogin(self, _auid, user, token=None, primary=0, registering=False):
        auid = str(_auid)
        if not token:
            m = hashlib.md5()
            m.update(auid)
            m.update(str(time.time()))
            m.update(str(random.random()))
            token = m.hexdigest()

        class CachedToken:

            def __init__(self, user, token, expireTime):
                self.user = user
                self.token = token
                self.expireTime = expireTime
                self.startTime = time.time()
                self.refresh()

            def match(self, token):
                self.refresh()
                return (self.token == token)

            def isFresh(self, currentTime):
                return currentTime < self.expireTime

            def refresh(self):
                self.expireTime = time.time() + self.expireTime

        ptoken = self.loginCache.get(auid, None)
        ctoken = CachedToken(user, token, LOGIN_TOKEN_EXPIRE_TIME)
        self.loginCache[auid] = ctoken
        info('token created (auid=%s token=%s)' % (auid, token))
        if ptoken is not None:
            if ctoken.startTime-ptoken.startTime < 15:  # probably this is second login
                info('previous token found, copying data (snid=%r snuid=%r)', ptoken.user.original_snid, ptoken.user.original_snuid)
                ctoken.user.original_snid = ptoken.user.original_snid
                ctoken.user.original_snuid = ptoken.user.original_snuid
        return token

    def checkLoginToken(self, _auid, token):
        auid = str(_auid)
        cachedToken = self.loginCache.get(auid, None)
        if cachedToken:
            if cachedToken.match(token):
                return cachedToken.user

    def refreshLoginToken(self, _auid):
        auid = str(_auid)
        cachedToken = self.loginCache.get(auid, None)
        if cachedToken:
            cachedToken.refresh()

    def updateLoginTokens(self, currentTime):
        expired = []
        for auid, token in self.loginCache.items():
            if not token.isFresh(currentTime):
                info('token expired (auid=%s token=%s)' % (auid, token))
                expired.append(auid)
        for auid in expired:
            del self.loginCache[auid]

    def deleteLoginToken(self, _auid):
        auid = str(_auid)
        cachedToken = self.loginCache.get(auid, None)
        if cachedToken:
            info('token removed (auid=%s token=%s)' % (auid, cachedToken.token))
            del self.loginCache[auid]

    def setLoginNick(self, _auid, nick_utf8):
        auid = str(_auid)
        cachedToken = self.loginCache.get(auid, None)
        if cachedToken:
            info('setLoginNick(%s) user token ok for auid=%s' % (nick_utf8, auid))
            cachedToken.user.nick = nick_utf8
        else:
            info('setLoginNick(%s) user token failed: no user token for auid=%s' % (nick_utf8, auid))

    def setLoginGender(self, _auid, gender):
        auid = str(_auid)
        cachedToken = self.loginCache.get(auid, None)
        if cachedToken:
            info('setLoginGender(%s) user token ok for auid=%s' % (gender, auid))
            cachedToken.user.sex = gender
        else:
            info('setLoginGender(%s) user token failed: no user token for auid=%s' % (gender, auid))

    def setSnBonusCount(self, _auid, _sn_count, _sn_count_prev, _new_networks):
        auid = str(_auid)
        sn_count = toint(_sn_count)
        sn_count_prev = toint(_sn_count_prev)
        cachedToken = self.loginCache.get(auid, None)
        if cachedToken:
            info('setSnBonusCount(cur %s, prev %s, new netw %s) user token ok for auid=%s' % (sn_count, sn_count_prev, _new_networks, auid))
            cachedToken.user.sn_count = sn_count
            cachedToken.user.sn_count_prev = sn_count_prev
            cachedToken.user.new_networks = _new_networks
        else:
            info('setSnBonusCount(cur %s, prev %s, new netw %s) user token failed: no user token for auid=%s' % (sn_count, sn_count_prev, _new_networks, auid))

    def markRestrictionOk(self, _auid):
        auid = str(_auid)
        cachedToken = self.loginCache.get(auid, None)
        if cachedToken:
            cachedToken.user.restriction_ok = 1


    # добавлям набор замеров
    def addDebugTimings(self, action_key, timings_list):
        if timings_list and len(timings_list) > 1:
            timings = self.debugTimings.get(action_key, [])
            calc_timings = []
            tPrev = timings_list[0]
            for t in timings_list[1:]:
                calc_timings.append(t-tPrev)
                tPrev = t
            timings.append( calc_timings )
            self.debugTimings[action_key] = timings

    def dumpDebugTimings(self):
        if self.debugTimings:
            for action_key, timings in self.debugTimings.iteritems():
                #info( "dumpDebugTimings[%s]:\n%s" % (action_key, timings) )
                if timings:
                    sum_timings = [0.0] * len(timings[0])
                    for calc_timings in timings:
                        for i, t in enumerate(calc_timings):
                            sum_timings[i] += t

                    avg_timings = []
                    for sum in sum_timings:
                        avg_timings.append( sum / len(timings) )

                    for i, avg in enumerate(avg_timings):
                        info( "average dumpDebugTimings[%s] (%d): %5.4f" % (action_key, i, avg) )
        # полностью зачищаем замеры после каждого дампа
        self.debugTimings = {}

    '''
    методы для пересчета рейтинга и ранга гильдий
    '''
    def recalcAllGuilds( self ):
        info("Start recalcAllGuilds!")
        self.recalcStartTime = datetime.datetime.now()
        self.recalcStepTime = datetime.datetime.now()
        self.guilds = []
        self.guildsToSetRank = [] # В процессе будет заполняться id гильдии и ее текущим рейтингом

        # PF-106691
        # self.guildsUVassals = [] # Тут будем хранить списочек гильдий для апдейта информации вассалов
        # self.guildSuzerainIvites = [] # Тут будем хранить списочек гильдий для чистки протухших прошений на сюзеренство

        self.I.DATA.find("guilds", "guilds", {"GuildAuid": {"$exists" : True}}, self.onGuildsInfoFound)

    def onGuildsInfoFound(self, reply):
        info("onGuildsInfoFound: Fetching guilds...")
        ts = time.time()
        if reply and "r" in reply:
            for obj in reply["r"]:
                guildAuid = tolong(str(obj.get("GuildAuid", None)))

                #isGuildKey = str(obj.get("key", None))[:3] == "gs_"
                if guildAuid:
                    self.guilds.append(guildAuid)

                    # PF-106691
                    # self.guildsUVassals.append(guildAuid)
                    # self.guildSuzerainIvites.append(guildAuid)

        info("%d guilds to recalc. Time consumed for fetch: %0.3f",  len(self.guilds), time.time()-ts)

        if self.guilds:
            guildAuid = self.guilds.pop()
            self.I.GS.recalcRating(guildAuid, self.GuildWarEventData.EventIndex, functools.partial(self.nextRecalcGuild, guildAuid))


    def nextRecalcGuild(self, guildAuid, response):
        info("nextRecalcGuild response: %r" % response)

        if response and "guildRating" in response and response["guildRating"] is not None:
            self.guildsToSetRank.append((guildAuid, response["guildRating"]))
        else:
            err("Fail nextRecalcGuild %s", guildAuid)

        if self.guilds:
            nexGuildAuid = self.guilds.pop()
            info( "nextRecalcGuild guildAuid: %r" % nexGuildAuid )
            self.I.GS.recalcRating(nexGuildAuid, self.GuildWarEventData.EventIndex, functools.partial(self.nextRecalcGuild, nexGuildAuid))
        else:
            ratingTimedelta = datetime.datetime.now() - self.recalcStepTime
            self.recalcStepTime = datetime.datetime.now()
            info("recalcRating time: %sm %s sec", ratingTimedelta.seconds/60, ratingTimedelta.seconds % 60)

            self.I.GS.updateGuildsRating(self.guildsToSetRank, self.onUpdateGuildsRating)

            self.guildsToSetRank.sort(key=lambda x: x[1], reverse=True)
            self.guildsToSetRank = [(i, auid, rating) for i, (auid, rating) in enumerate(self.guildsToSetRank)]

            guild_data = self.guildsToSetRank.pop()
            info( "nextRankGuild guildAuid: %r",  guild_data[1])
            cb = functools.partial(self.I.GS.recalcRank, guild_data, self.nextRankGuild)
            info("delay recalcRank for 5 seconds...")
            AddLoopCallback(cb, 5)

    def onUpdateGuildsRating(self, response):
        info("onUpdateGuildsRating response: %r", response)

    def nextRankGuild( self, response):
        info("nextRankGuild response: %r", response)
        if not response:
            err("Fail nextRankGuild")

        if self.guildsToSetRank:
            guild_data = self.guildsToSetRank.pop()
            info( "nextRankGuild guildsToSetRank guildRank: {0}, guildAuid: {1}".format(guild_data[0], guild_data[1]))
            self.I.GS.recalcRank(guild_data, self.nextRankGuild)
        # PF-106691
        # elif self.guildsUVassals:
        #     rankTimedelta = datetime.datetime.now() - self.recalcStepTime
        #     self.recalcStepTime = datetime.datetime.now()
        #     info("recalcRank time: %sm %s sec", rankTimedelta.seconds/60, rankTimedelta.seconds % 60)
        #     guildAuid = self.guildsUVassals.pop()
        #     info( "nextUpdateVassals guildAuid: %r" % guildAuid)
        #     self.I.GS.updateVassalsAndSuzerainInfo(guildAuid, self.nextUpdateVassals)
        else:
            rankTimedelta = datetime.datetime.now() - self.recalcStepTime
            self.recalcStepTime = datetime.datetime.now()
            info("recalcRank time: %sm %s sec", rankTimedelta.seconds/60, rankTimedelta.seconds % 60)
            totalRecalcTime = datetime.datetime.now() - self.recalcStartTime
            info("Total recalc time: %sm %s sec", totalRecalcTime.seconds/60, totalRecalcTime.seconds % 60)

    # PF-106691
    # def nextUpdateVassals(self, response):
    #     info ( "nextUpdateVassals response: %r" % response )
    #     if not response:
    #         err("Fail nextUpdateVassals")
    #
    #     if self.guildsUVassals:
    #         guildAuid = self.guildsUVassals.pop()
    #         info( "nextUpdateVassals : guildAuid: {0}".format(guildAuid))
    #         self.I.GS.updateVassalsAndSuzerainInfo(guildAuid, self.nextUpdateVassals)
    #     else:
    #         updateVassalsTimedelta = datetime.datetime.now() - self.recalcStepTime
    #         info("updateVassalsAndSuzerainInfo time: %sm %s sec", updateVassalsTimedelta.seconds/60, updateVassalsTimedelta.seconds % 60)
    #         guildAuid = self.guildSuzerainIvites.pop()
    #         self.I.GS.clearSuzerainInvites(guildAuid, self.nextClearingSuzerainInvites)
    #
    # def nextClearingSuzerainInvites(self, response):
    #     info ( "nextClearingSuzerainInvites response: %r" % response )
    #     if not response:
    #         err("Fail nextClearingSuzerainInvites")
    #
    #     if self.guildSuzerainIvites:
    #         guildAuid = self.guildSuzerainIvites.pop()
    #         info( "nextClearingSuzerainInvites : guildAuid: {0}".format(guildAuid))
    #         self.I.GS.clearSuzerainInvites(guildAuid, self.nextClearingSuzerainInvites)
    #     else:
    #         clearingSuzerainInvitesTimedelta = datetime.datetime.now() - self.recalcStepTime
    #         totalRecalcTime = datetime.datetime.now() - self.recalcStartTime
    #         info("ClearingSuzerainInvites time: %sm %s sec", clearingSuzerainInvitesTimedelta.seconds/60, clearingSuzerainInvitesTimedelta.seconds % 60)
    #         info("Total recalc time: %sm %s sec", totalRecalcTime.seconds/60, totalRecalcTime.seconds % 60)
    '''
    tradeevent experience world ratings
    '''

    def updateTradeEventExperience(self, auid, event_id, experience, callback=None):
        self.I.EXPORT.updateTradeEventExperience(auid, event_id, experience, callback)

    def getTradeEventPlace(self, auid, event_id, callback=None, limit=5000):
        self.I.EXPORT.getTradeEventPlace(auid, event_id, limit, callback)

    '''
    season event progress world ratings
    '''

    def updateSeasonEventProgress(self, auid, event_id, progress, callback=None):
        self.I.EXPORT.updateSeasonEventProgress(auid, event_id, progress, callback)

    def getSeasonEventPlace(self, auid, event_id, callback=None, limit=5000):
        self.I.EXPORT.getSeasonEventPlace(auid, event_id, limit, callback)

    '''
    работа с данными текущего кланового ивента
    '''

    def getGuildWarEventId(self):
        if not self.get("GuildWarEventData"):
            return 0
        return self.GuildWarEventData.EventIndex

    def canParticipateInGuildWarEvent(self):
        if not self.get("GuildWarEventData") or not self.I.Config.getMainConfig().GUILD_WAR_EVENT_ENABLED:
            return False
        return self.GuildWarEventData.Points < self.GuildWarEventData.PointsCap

    def getGuildWarEventDataChanges(self):
        if not self.get("GuildWarEventData"):
            warn("No guild war event data on server!")
            self.GuildWarEventData = GuildWarEventData()
            self.GuildWarEventData.init(None)
        data = [MakeModelChangeString("init_guild_war_event_data", "/", "init", self.GuildWarEventData.generateJsonDict())]
        return data

    def updateGuildWarEventDataFromJson(self, gweData):
        if not self.get("GuildWarEventData"):
            warn("No guild war event data on server!")
            self.GuildWarEventData = GuildWarEventData()
            self.GuildWarEventData.init(None)
        try:
            self.GuildWarEventData.load(gweData)
        except Exception:
            catch()
            return 0
        return 1

    def updateGuildWarEventData(self):
        debug("Updating guild war event data")

        # лезем в монгу за данными
        if self.I.Config.getMainConfig().GUILD_WAR_EVENT_ENABLED:
            if not self.get("GuildWarEventData"):
                self.GuildWarEventData = GuildWarEventData()
                self.GuildWarEventData.init(None)

            self.I.DATA.find_one(CC.GUILDWAR_EVENTS_DATA, CC.GUILDWAR_EVENTS_DATA,
                                 {"$query": {"_id": {"$exists": True},
                                             "end_time": {"$gt": int(time.time())},
                                             "enabled": 1},
                                 # "$orderby": {"$natural": -1}}, говорят, что нельзя полагаться на этот порядок :(
                                  "$orderby": {"event_index": -1}},
                                 params=None, callback=self.onGetGuildWarEventData)


    def onGetGuildWarEventData(self, response):
        debug("onGetGuildwarEventsList: response = %r", response)
        if response and response["r"] is not None:
            prev_event_id = None if not self.get("GuildWarEventData") else self.GuildWarEventData.Id
            obj = response["r"]  # type: dict
            #debug("%r", obj)
            gwedata = self.GuildWarEventData
            try:
                gwedata.Enabled = int(obj["enabled"])
                gwedata.Points = long(obj["points"])
                gwedata.PointsCap = long(obj["limit"])
                gwedata.EndTime = int(obj["end_time"])
                gwedata.Id = str(obj["_id"])
                gwedata.EventIndex = long(obj.get("event_index", 0))
            except Exception:
                catch()

            # т.к. добавлять имеет право только одна спец. ws-ка, то нам при изменнении ивента
            # надо теперь разослать закешированные данные другим ws-кам и gs
            name, server = getFirstSortedPair(coord_cfg.COORDINATOR_WS_SERVERS)
            if name and server and options.server_name == name:
                if prev_event_id != self.GuildWarEventData.Id:
                    self.sendGuildWarEventData()
                    self.I.GS.notifyGuildWarEventChanged(guild_auids=None, event_id=gwedata.EventIndex,
                                                         callback=self.onNotifyGuildWarEventChangedReply)
            debug("GuildwarEventData = %r", self.GuildWarEventData)
        else:
            # добавлять может только спец. ws-ка
            name, server = getFirstSortedPair(coord_cfg.COORDINATOR_WS_SERVERS)
            if name and server and options.server_name == name:
                self.addNewGuildWarEvent()

    def addNewGuildWarEvent(self, response=None):
        next_event_index = self.GuildWarEventData.EventIndex + 1
        if not response:
            # перед тем как добавлять, надо получить event_index последнего оконченного
            self.I.DATA.find_and_modify(CC.HELPER_VARIABLES_DATA, CC.HELPER_VARIABLES_DATA, {"_id": "last_gw_event_index"},
                                        update={"$inc": {"val": int(1)}}, new=True, params=None, upsert=True,
                                        callback=self.addNewGuildWarEvent)
            return
        elif response["r"] is not None:
            debug("addNewGuildWarEvent: on increment event index response=%r", response)
            try:
                next_event_index = int(response["r"]["val"])
            except:
                pass
        else:
            err("Failed to increment guild war event index")
            next_event_index = 0

        cap = self.I.SD.getMainSD().getGuildWarEventPointsCap()
        duration = self.I.SD.getMainSD().getGuildWarEventDuration()
        endDateTime = (datetime.datetime.utcnow() + datetime.timedelta(days=duration)).replace(minute=0, second=0)
        endTimestamp = int(time.time()) + int((endDateTime - datetime.datetime.utcnow()).total_seconds()) - 2

        self.I.STATS.addGWEvent('new', next_event_index, True, 0, endTimestamp, cap)

        info("addNewGuildWarEvent: New guild war event data: duration=%s, end date=%s, end timestamp=%s index=%s", duration, endDateTime,
             endTimestamp, next_event_index)

        args = {'points': long(0), 'limit': long(cap),
                'end_time': endTimestamp, 'enabled': 1,
                'event_index': next_event_index}
        self.I.DATA.insert(CC.GUILDWAR_EVENTS_DATA, CC.GUILDWAR_EVENTS_DATA, args, params=None,
                           callback=self.onAddNewGuildWarEventData)

    def onAddNewGuildWarEventData(self, response):
        info("onAddNewClanWarEvent: response = %r", response)
        if response and response["r"] is not None:
            # успешно добавили новый клановый ивент в монгу
            self.updateGuildWarEventData()  # прочитаем его, чтобы обновить закешированные данные
            return

        warn("onAddNewGuildWarEventData: failed to add new guild war event data")

    def onNotifyGuildWarEventChangedReply(self, response):
        debug("notifyGuildWarEventChanged response %r", response)

    def sendGuildWarEventData(self, services=None):
        selfPeer = self.I.WS.peers.get(options.server_id)
        self_ws_addr = selfPeer["addr"]
        if not services:
            peers = self.I.WS.peers
            selfPeer = self.I.WS.peers.get(options.server_id)
            self_ws_addr = selfPeer["addr"]
        else:
            peers = {}
            for peer in self.I.WS.peers:
                if peer in services:
                    peers[peer] = self.I.WS.peers.get(peer)

        post_body = json_dumps(self.GuildWarEventData.generateJsonDict())
        # чтобы не слать запросов самому себе, достанем свой адрес

        if peers:
            for ws_id in peers.keys():
                peer = peers[ws_id]
                ws_addr = peer["addr"]

                # слать запросы самим себе - не комильфо
                if self_ws_addr == ws_addr:
                    continue

                args = dict(action="update_guild_war_event")
                _callback = functools.partial(self.onGuildWarEventDataUpdated, ws_addr=ws_addr)
                self.I.WSX.post(ws_addr, args, post_body, _callback, subrequest="x")

    def onGuildWarEventDataUpdated(self, response, ws_addr=""):
        debug("GS reply onGuildWarEventDataUpdated is %r", response)
        if response and response.get("ok"):
            info("GS %s, guild war event data updated successfully", ws_addr)
        else:
            warn("GS %s, guild war event data failed", ws_addr)

    def updateGuildWarEvent(self, acc):
        """
        при необходимости обновляет id клановго ивента в db юзера и сбрасывает личные клановые очки в 0
        :param acc: аккаунт пользователя
        :return:
        """
        if not self.I.Config.getMainConfig().GUILD_WAR_EVENT_ENABLED:
            return

        if not self.get("GuildWarEventData"):
            return

        if acc.db.currentGuildWarEvent != self.GuildWarEventData.EventIndex:
            # выдаем награды по завершению евента
            if acc.guilddata and acc.guilddata.GuildInfo:
                # проверяем, что GuildData уже обновилась (и пересчитала места). если не обновилась, ждем.
                if acc.guilddata.GuildInfo.CurrentEventId != self.GuildWarEventData.EventIndex:
                    return
                guild_place = acc.guilddata.GuildInfo.PrevPlace
                player = next((mem for _, mem in acc.guilddata.Members.iteritems() if mem.Person == acc.auid), None)
                if player:
                    player_place = player.PrevEventPlace
                    acc.model.awardForClanWarEvent(guild_place, player_place, acc)
            #
            acc.db.currentGuildWarEvent = self.GuildWarEventData.EventIndex
            acc.model.Resources.CWPoints_Player = 0
            acc.model.Resources.CWPoints_Clan = 0

    '''
    работа с TopBuildData
    '''
    def getTopBuildsData(self):
        if not self.get("TopBuildsData"):
            warn("No top builds on server!")
            self.TopBuildsData = TopBuildsData()
            self.TopBuildsData.init(None)
        topBuilds = [MakeModelChangeString("init_top_builds", "/", "init", self.TopBuildsData.generateJsonDict())]
        return topBuilds

    def updateTopBuildFromJson(self, topBuildJson):
        if not self.get("TopBuildsData"):
            warn("No top builds on server!")
            self.TopBuildsData = TopBuildsData()
            self.TopBuildsData.init(None)
        try:
            self.TopBuildsData.load(topBuildJson)
        except Exception:
            catch()
            return 0
        return 1

    def updateTopBuilds(self):
        #debug("updateTopBuilds self.calcTopBuildsData=%r", self.calcTopBuildsData )
        if not self.calcTopBuildLock:
            self.calcTopBuildLock = True
            info("Updating top builds")
            self.updatedBuilds = TopBuildsData()
            self.updatedBuilds.init(None)
            self.heroPersistents = [crc32(self.I.SD.getMainSD().data['Heroes'][hero_id]['persistentId']) for hero_id in self.I.SD.getMainSD().data['Heroes']]
            if self.heroPersistents:
                persistentId = self.heroPersistents.pop()
                self.invalidAuids = []
                self.I.EXPORT.getHeroWithMaxRating(persistentId, self.invalidAuids, self.checkHeroBuild)
        else:
            info("Lock updating top builds")

    def getTalentsetWithMaxForce(self, sqlRes):
        maxTs = max(sqlRes, key=lambda ts: ts.get("hero_force", 0))
        return min(filter(lambda ts: maxTs.get("hero_force", 0)==ts.get("hero_force", 0), sqlRes), key=lambda ts: ts.get("talentset_id",0))

    def checkHeroBuild(self, sqlReply):
        r = sqlReply["r"]
        if r and len(r):
            try:
                maxTs = self.getTalentsetWithMaxForce(r)
                talentSet = {}
                isTSValid = True

                for i in xrange(1, 37):
                    talentStr = maxTs.get("talent"+str(i))
                    crcAndRarity = talentStr.split(':')
                    # Нет ли у нас пустых позиций в талантсете
                    if len(crcAndRarity) == 2:
                        talentCrc = toint(crcAndRarity[0])
                        talentPoints = toint(crcAndRarity[1])
                        staticTalent = self.I.SD.getMainSD().getStaticTalentByTalentId(talentCrc)
                        # Проверим на допустимые рарности талантов
                        if staticTalent and staticTalent['rarity'] != 'ordinary' and staticTalent['rarity'] != 'good':
                            talentSet[i] = {"crc": talentCrc, "points": talentPoints}
                        else:
                            isTSValid = False
                            break
                    else:
                        isTSValid = False
                        break
                if isTSValid:
                    hero, heroId = self.updatedBuilds.newTopBuildHero()
                    hero.Auid = maxTs.auid
                    hero.Level = maxTs.hero_level
                    hero.Force = maxTs.hero_force
                    hero.Nickname = maxTs.nickname
                    hero.PersistentId = maxTs.hero_crc
                    hero.Rating = maxTs.hero_rating
                    hero.Skin = maxTs.hero_skin

                    hero.Stats.Health = maxTs.hero_health
                    hero.Stats.Mana = maxTs.hero_mana
                    hero.Stats.Strength = maxTs.hero_strength
                    hero.Stats.Intellect = maxTs.hero_intellect
                    hero.Stats.Agility = maxTs.hero_agility
                    hero.Stats.Cunning = maxTs.hero_cunning
                    hero.Stats.Fortitude = maxTs.hero_fortitude
                    hero.Stats.Will = maxTs.hero_will
                    for sqlTalentId in talentSet:
                        talent, talentId = self.updatedBuilds.newTopBuildTalent()
                        talent.PersistentId = talentSet[sqlTalentId]["crc"]
                        talent.Points = talentSet[sqlTalentId]["points"]
                        hero.TalentSet[sqlTalentId] = talent
                    self.updatedBuilds.Heroes.add(hero)
                else:
                    info("Not suitable data for build %r", r[0])
                    self.invalidAuids.append(r[0].auid)
                    self.I.EXPORT.getHeroWithMaxRating(r[0].hero_crc, self.invalidAuids, self.checkHeroBuild)
                    return
            except Exception:
                catch()

        self.updateNextTopBuild()

    def updateNextTopBuild(self):
        if self.heroPersistents:
            persistentId = self.heroPersistents.pop()
            self.invalidAuids = []
            self.I.EXPORT.getHeroWithMaxRating(persistentId, self.invalidAuids, self.checkHeroBuild)
        else:
            if not self.get("TopBuildsData"):
                self.TopBuildsData = TopBuildsData()
                self.TopBuildsData.init(None)
            self.TopBuildsData.load(self.updatedBuilds.generateJsonDict())
            self.sendTopBuildData()
            self.calcTopBuildLock = False

    def sendTopBuildData(self, services=None):
        selfPeer = self.I.WS.peers.get(options.server_id)
        self_ws_addr = selfPeer["addr"]
        if not services:
            peers = self.I.WS.peers
            selfPeer = self.I.WS.peers.get(options.server_id)
            self_ws_addr = selfPeer["addr"]
        else:
            peers = {}
            for peer in self.I.WS.peers:
                if peer in services:
                    peers[peer] = self.I.WS.peers.get(peer)

        post_body = json_dumps(self.TopBuildsData.generateJsonDict())
        # чтобы не слать запросов самому себе, достанем свой адрес

        if peers:
            for ws_id in peers.keys():
                peer = peers[ws_id]
                ws_addr = peer["addr"]

                # слать запросы самим себе - не комильфо
                if self_ws_addr == ws_addr:
                    continue

                args = dict(action="update_top_build")
                _callback = functools.partial(self.onTopBuildUpdated, ws_addr=ws_addr)
                self.I.WSX.post( ws_addr, args, post_body, _callback, subrequest="x")


    def onTopBuildUpdated(self, response, ws_addr=""):
        if response and response.get("ok"):
            info("WS %s, top build updated successfully", ws_addr)
        else:
            warn("WS %s, update top build failed", ws_addr)

    '''
    работа с сезонными лидербордами юзера
    '''
    def updateUserLeagueStat(self, acc):
        for heroId, cur_process_hero in acc.model.HeroesKeeper.iteritems():
            # TODO: used old functions
            # info("updateUserLeagueStat for auid %d, getLeagueIndexByRating = %d, BestLeagueRating = %d"%(acc.db.auid, acc.SD.getLeagueIndexByRating(cur_process_hero.Rating), cur_process_hero.getBestLeagueIndex(acc, acc.SD)))
            cur_season_md = cur_process_hero.findCurrentSeasonInfo(acc)
            if cur_season_md:
                cur_league = acc.SD.getBestSeasonLeague(cur_season_md)
                if cur_league['minLeaderPlace'] > 0:  # легендарная
                    self.I.EXPORT.getLegendRatingInfo(cur_process_hero.PersistentId, acc.db.auid, acc.SD.getCurrentSeasonId(), self.onReceiveLegendInfo)

    def onReceiveLeaguesPlaceInfo(self, sqlReply):
        list_ratings = []
        own_auid = -1
        r = sqlReply["r"]
        if r and len(r):
            try:
                for legendRatingInfo in r:
                    list_ratings.append(legendRatingInfo.rating)
                    own_auid = legendRatingInfo.own_auid
            except Exception:
                catch()

        for uid, acc in users.iteritems():
            if acc.db.auid == own_auid:
                info("onReceiveLeaguesPlaceInfo for auid %d, hero_id = %d, list_ratings = %s"%(own_auid, legendRatingInfo.hero_id, str(list_ratings)))
                acc.model.updateHeroLegendPlaces(acc, acc.SD, legendRatingInfo.hero_id, list_ratings)
                break

    def onReceiveLegendInfo(self, sqlReply):
        r = sqlReply["r"]
        if r and len(r):
            try:
                for legendRatingInfo in r:
                    for uid, acc in users.iteritems():
                        if acc.db.auid == legendRatingInfo.uid:
                            info("onReceiveLegendInfo for auid %d, hero_id = %d, league_place = %d"%(acc.db.auid, legendRatingInfo.hero_id, legendRatingInfo.league_place))
                            acc.model.updateHeroLegendLeagueInfo(acc, acc.SD, legendRatingInfo.hero_id, legendRatingInfo.league_place)
                            # TODO: used old functions
                            #info("onReceiveLegendInfo for auid %d, getLeagueIndexByRating = %d"%(acc.db.auid, acc.SD.getLeagueIndexByRating(legendRatingInfo.rating)))
                            if legendRatingInfo.league_place <= 10:
                                self.I.EXPORT.getLegendPlaces(legendRatingInfo.hero_id, acc.db.auid, 0, 21, acc.SD.getCurrentSeasonId(), self.onReceiveLeaguesPlaceInfo)
                            else:
                                self.I.EXPORT.getLegendPlaces(legendRatingInfo.hero_id, acc.db.auid, legendRatingInfo.league_place - 11, 21, acc.SD.getCurrentSeasonId(), self.onReceiveLeaguesPlaceInfo)
                            break
            except Exception:
                catch()


    '''
    прочее
    '''
    def updateMultiConfig(self):
        self.accsToUpadte["config"].update(users.iterkeys())
        info("updateMultiConfig...")
        time1 = time.time()

        # старая копия конфига должна быть заменена после этого у всех пользователей
        self.configChanges = self.I.Config.updateConfig()
        # update config-dependant static data collections:
        if self.I.SD:
            # конфиг logic_overrides может содержать переопределения полей StaticData; их тоже нужно применить к перегруженной SD
            self.I.Config.mainConfig.applyOverrides(self.I.SD.getMainSD())
            self.I.Config.applyLocaleOverrides(self.I.SD)
            # Заполним статические поля, которые можно перезаписыать из GMTools
            self.I.Config.fillStaticDataDependendValues(self.I.SD)

        info("updateMultiConfig all done, time: %.3f sec", time.time() - time1)


    def updateSomeAccs(self):
        try:
            for i in xrange(USERS_UPDATE_PER_TICK):
                if self.accsToUpadte["config"]:
                    uid = self.accsToUpadte["config"].pop()
                    acc = users.get(uid)
                    if getattr(acc, "isTutorialAccount", False):
                        continue
                    # Проверим, не ушёл ли пользователь
                    try:
                        if acc:
                            self.addConfigChanges(acc)
                    except Exception:
                        warn("Bad modeldata for uid %r", uid)
                        catch()
                elif self.accsToUpadte["quests"]:
                    uid = self.accsToUpadte["quests"].pop()
                    acc = users.get(uid)
                    if getattr(acc,"isTutorialAccount", False):
                        continue
                    # Проверим, не ушёл ли пользователь
                    try:
                        if acc:
                            self.checkDynamicQuests(acc)
                    except Exception:
                        warn("Bad modeldata for uid %r", uid)
                        catch()
                else:
                    break
            if not self.accsToUpadte["config"] and self.get("configChanges"):
                self.cleanupConfigUpdates()
        except Exception:
            warn("Bad modeldata")
            catch()

    def updateDynamicQuests(self):
        self.accsToUpadte["quests"].update(users.iterkeys())

    def checkDynamicQuests(self, acc):
        acc.model.write(acc.pending)
        acc.model.checkNewDynamicQuests(acc,self.I)
        acc.model.validateDynamicQuests(acc, self.I)

        if acc.pending_handler:
            acc.pending_handler()

    def addConfigChanges(self, acc):
        if not acc.userlocale:
            acc.userlocale = acc.model.LordInfo.UserLocale

        changes = self.configChanges.get(acc.userlocale.lower(), None)
        if changes:
            acc.pending_events.append({"ConfigData": {"ConfigData": changes}})
            if acc.pending_handler:
                acc.pending_handler()
            acc.Config = self.I.Config
            acc.SD = self.I.SD.getSD(acc.userlocale)

    def cleanupConfigUpdates(self):
        del self.configChanges


    def checkPlayerGuildApplications(self, acc):
        debug("checkPlayerGuildApplications for %s", acc.db.auid)
        to_remove = acc.model.checkGuildApplicationsAlive()
        if to_remove:
            self.removePlayerGuildApplications(acc, to_remove)
        return len(acc.model.GuildApplications)

    def removePlayerGuildApplications(self, acc, guildAuids):
        data_key = {"pers_auid": acc.db.auid, "guild_auid": {"$in": guildAuids}}
        debug("removePlayerGuildApplications: removing %s", data_key)
        self.I.DATA.remove(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA, data_key)

    def removeOutOfDateRecruitApplications(self):
        self.I.DATA.remove(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA,
                           {"created": {"$lt": int(time.time()) -
                                               self.I.SD.getMainSD().data['GuildRecruitment']['guildRequestLifetime']}},
                           self.onApplicationsRemoved)

    def removeRecruitApplications(self, acc):

        if acc and acc.model:
            for app_id, app in acc.model.GuildApplications.items():
                acc.model.GuildApplications.remove(app)

        debug("onRecruitApplicationsFind acc.model.GuildApplications= %r",  acc.model.GuildApplications.getJsonDict())

        _callback = functools.partial(self.onRecruitApplicationsFind, acc)
        self.I.DATA.find(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA,
                            {"pers_auid": acc.auid}, callback=_callback)


    def onRecruitApplicationsFind(self, acc, response):
        debug("onRecruitApplicationsFind acc=%r, \nresponse=%r", acc, response)

        if response and response.get('r'):
            for rq in response['r']:
                self.I.GS.rmRecruitNotification(acc.auid, rq.get('guild_auid'))

        self.I.DATA.remove(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA,
                            {"pers_auid": acc.auid})


    def onApplicationsRemoved(self, response):
        if response and "r" in response:
            info("Out of date recruit applications were successfully removed")
        else:
            warn("Failed to remove out of date recruitment applications")


    def onUserSkipTutorial(self, acc):
        debug("onUserSkipTutorial acc.fraction: %s:", acc.db.fraction)
        qId = acc.getConfigValue("SKIPPED_TUTORIAL_QUESTS")[
            acc.db.fraction if acc.db.fraction and acc.db.fraction == 'B' else 'A']
        debug("onUserSkipTutorial SKIPPED_TUTORIAL_QUESTS: %r", qId)
        if qId:
            staticQuest = acc.SD.getStaticQuestById(crc32(qId))
            if staticQuest:
                debug("onUserSkipTutorial pre addedQuest")
                if not acc.model.addQuest(staticQuest, None, acc.getConfigValue("ALTERNATIVE_QUESTS"), True, False, self.I.STATS, acc):
                    warn("onUserSkipTutorial: Must be unique quest")
                else:
                    info("onUserSkipTutorial addedQuest: %r", staticQuest)

            else:
                warn("onUserSkipTutorial: Static quest not found")
        else:
            err("onUserSkipTutorial: can't find SKIPPED_TUTORIAL_QUESTS")

    def tickEvents(self):
        debug("tickEvents")
        # Если какие-то изменения есть, подождём следующего тика, чтобы ничего не затереть
        if self.get("configChanges") and self.accsToUpadte["config"]:
            return

        configChanges = {}
        for _id, (store, event) in self.operatorEvents["toRevert"].items():
            eventChanges = self.I.Config.revertEvent(self.I.SD, event)
            for locale in eventChanges:
                if locale in configChanges:
                    configChanges[locale].extend(eventChanges[locale])
                else:
                    configChanges[locale] = eventChanges[locale]
            if store:
                self.operatorEvents["finishedEvents"][_id] = event
            del self.operatorEvents["toRevert"][_id]
        for _id, event in self.operatorEvents["activeEvents"].items():
            # Ивент закончился, откатим значение
            if event["endTime"] < int(time.time()):
                eventChanges = self.I.Config.revertEvent(self.I.SD, event)
                for locale in eventChanges:
                    if locale in configChanges:
                        configChanges[locale].extend(eventChanges[locale])
                    else:
                        configChanges[locale] = eventChanges[locale]
                self.operatorEvents["toRevert"][_id] = (True, event)
                del self.operatorEvents["activeEvents"][_id]
        for _id, event in self.operatorEvents["pendingEvents"].items():
            # Ивент начался, пора запускать
            if event["startTime"] < int(time.time()):
                self.I.Config.setEventDefalutValue(self.I.SD, event)
                eventChanges, self.needUpdateSeeds = self.I.Config.applyEvent(self.I.SD, event)
                for locale in eventChanges:
                    if locale in configChanges:
                        configChanges[locale].extend(eventChanges[locale])
                    else:
                        configChanges[locale] = eventChanges[locale]
                self.operatorEvents["activeEvents"][_id] = event
                del self.operatorEvents["pendingEvents"][_id]
        if len(configChanges):
            info("configChanges = %r", configChanges)
            self.configChanges = configChanges
            self.accsToUpadte["config"].update(users.iterkeys())
        if self.needUpdateSeeds:
            info("Reloading seeds")
            self.needUpdateSeeds = self.I.Config.reloadSeeds()
        #debug("tickEvents disabledEvents=%r\n pendingEvents=%r\n activeEvents=%r\n finishedEvents=%r", self.operatorEvents["disabledEvents"],
        #     self.operatorEvents["pendingEvents"], self.operatorEvents["activeEvents"], self.operatorEvents["finishedEvents"])

    def pickPendingChanges(self, acc):
        response = {}
        SubAction.wrapPendingMessages(acc, None, response)
        acc.pending_changes = []
        changes = {}

        friendChanges = response.get("FriendsData") or []
        SubAction.convertResponseObjects(friendChanges)
        if len(friendChanges):
            changes["FriendsData"] = friendChanges
        return changes

    def tickFriends(self):
        try:
            PAGE_SIZE = self.I.Config.getMainConfig().FRIENDS_PAGE_SIZE
            #  debug("TickFriends %r l=%r", users, len(users))
            for uid, acc in users.iteritems():
                #  debug("TickFriends  acc.db.CountOfAllFriends=%r", acc.db.CountOfAllFriends)
                #  debug("TickFriends  acc.sendedFriends=%r", acc.sendedFriends)
                if acc.sendedFriends and not acc.isSendedFriends and acc.db.CountOfAllFriends > len(acc.sendedFriends):
                    #  debug("TickFriends acc.db.auid = %r", acc.db.auid)
                    sorted_keys = sorted(acc.BufferFriendsData.myFriends.keys())
                    good_keys = sorted_keys[acc.db.CurrBeginOfFriendsPage + PAGE_SIZE : acc.db.CurrBeginOfFriendsPage + 2 * PAGE_SIZE]
                    #  debug("TickFriends good_keys = %r", good_keys)
                    if good_keys:

                        acc.pending_changes = []
                        acc.pending = GroupPendingChangeWriter( acc )
                        acc.friendsdata.write(acc.pending)
                        for _fid in good_keys:
                            acc.friendsdata.nextGUID = lambda : _fid
                            fi, fid = acc.friendsdata.newFriend()
                            fr = acc.BufferFriendsData.findPersonByUid(_fid)
                            acc.friendsdata.fillFriend(fr, fi)

                            if _fid in acc.BufferFriendsData.RecentAllies:
                                acc.friendsdata.RecentAllies.add(fi)

                            if _fid in acc.BufferFriendsData.ignores:
                                acc.friendsdata.igrnores.append(_fid)

                            if _fid in acc.BufferFriendsData.myFriends:
                                acc.friendsdata.myFriends.add(fi)

                        acc.db.CurrBeginOfFriendsPage += PAGE_SIZE
                        acc.sendedFriends.extend(good_keys)
                        changes = self.pickPendingChanges(acc)
                        #  debug("TickFriends changes = %r", changes)
                        """
                        args = ClassDict(friend_auid=[acc.db.auid], cmd=["change"],to_uids=[str(uid)], msg_id=[nextMsgID()], json_FriendsData=[changes])
                        _callback = functools.partial(self.onFriendsChanges, acc)
                        action = PersonServerFriendsCmdAction(args, _callback, I=self.I)
                        action.unpacked = True
                        action.onStart()
                        """
                        acc.pending_events.append( {"friends":  changes } )
                        if acc.pending_handler:
                            acc.pending_handler()
                        if len(acc.sendedFriends) >= acc.db.CountOfAllFriends:
                            debug("TickFriends friends was sended")
                            acc.isSendedFriends = True
                            acc.sendedFriends = []
                            acc.BufferFriendsData = FriendsData()
                            acc.BufferFriendsData.init(None)
        except Exception:
            catch()

    def onFriendsChanges(self, acc, action_response):
        debug("onFriendsChanges response %r", action_response)
# -------------------------------------------------------------------------------------------------------
# -------------------------------------------------------------------------------------------------------

if __name__ == "__main__":
    try:
        ITornadoServer.main( PwWorkServer )
    except:
        msg = catch()
        print msg
    if MARKER_FILENAME:
        success("removing marker file %r" % MARKER_FILENAME)
        os.remove( MARKER_FILENAME )
