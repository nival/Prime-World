#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys, os, time, json, logging, functools, datetime

sys.path.append('..')

sys.path.append('../tornado')
sys.path.append('tornado')
import tornado.options
from tornado.options import define, options

sys.path.append('cfg')
sys.path.append('../cfg')
# import cfg
import coord_cfg
from config.MultiConfig import *
from handlers import *  # JsonHandler, IfaceFactory
from subaction import SubAction, action_timing, separate_timing

from iwebserver import *
from iuserdata import IDataManager
from modeldata.datamanager import PwNewModelManager
from modeldata.MultiStaticData import MultiStaticData
from ifactory import IfaceFactory

import iguildservice
import ifriendservice
import isiegeservice
import urllib

from imirror import MirrorDataType

from GuildInvestStatistics import GuildInvestStatistics
from guild.GuildData import GuildData
from guild.RecruitsData import RecruitsData
from modeldata.collects import *
from modeldata.changes import PendingChangeWriter, GroupPendingChangeWriter, MakeModelChangeString
from guild.GuildRequests import *
from guild.SiegesRequests import *

## Thrift
from thrift_handler import ThriftHandler
from thrift_pw.account_management.acc_management_gs_handler import GuildManagementServerHandler

## Social Exchange
import CC
import MM
from MM import EAwardType
from pwhandler import SocialExchangeJsonHandler
from intaction import InternalMailAction
from enums.TalentEventType import *

from bson import ObjectId

thriftypespath = os.path.join(realpath, "../thrift_pw/account_management/gen-py")
sys.path.append(thriftypespath)
from AccountManagementAPI.ttypes import ConfigEventType
from StatisticCore.ttypes import TalentInfo, TalentChangeOperation

GUILD_EXPIRE_CHECK_PERIOD = 180  # раз в N секунд проверяем, не пора ли удалять протухшие гильдии из памяти
GUILD_WAR_EVENT_CHECK_PERIOD = 5

class GuildServiceHandler(JsonHandler):
    """ обрабатываем только внутренние запросы от рабочих серверов """

    internalActionMap = {
        # внутрикластерные команды; закрыты для внешних клиентов
        # --- служебное ----
        'check_alive': 'onCheckWebServerAlive',  # base JsonHandler: умеем отвечать, что мы живы
        'get_stat': 'onGetWebServerStat',  # base JsonHandler: умеем отвечать, что мы живы
        'reload_multi_config': 'onReloadMultiConfigWithMainSD',
        # base JsonHandler: умеем перегружать logic_cfg+StaticData со всеми внутренностями
        'peer': PeerServerStatusAction,  # base JsonHandler: апдейтим статус peer WS-ок
        'clear_addr_info': 'onClearAddrInfoCache',
        # base JsonHandler: умеем чистить кэш addrinfo (чтобы заново резолвить адреса после перестройки DNS)
        'add_techs': AddTechsAction,  # добавляем информацию о новых тех-работах

        # --- user actions ---
        'subscribe': SubscribeGSAction,
        'unsubscribe': UnsubscribeGSAction,
        'create_guild': CreateGuildAction,
        'rename_guild': RenameGuildAction,
        'leave_guild': LeaveGuildAction,
        'destroy_guild': DestroyGuildAction,
        'invite_guild': InviteToGuildAction,
        'accept_guild': AcceptGuildAction,
        'check_guild_name': CheckGuildNameAction,
        'promote_guild': PromoteGuildAction,
        'demote_guild': DemoteGuildAction,
        'kick_guild': KickGuildAction,
        'msg_guild': MessageGuildAction,
        'hero_rating': HeroRatingAction,
        'recalc_rating': RecalcRatingAction,
        'recalc_rank': RecalcRankAction,
        'change_guild_owner': ChangeGuildOwnerAction,
        'is_guild_member': IsGuildMemberAction,
        'invest_in_guild': InvestInGuildAction,
        'check_guild_exists': CheckGuildExistsAction,
        'remove_guild_member': RemoveGuildMemberAction,
        'add_guild_talent': AddGuildTalentAction,
        'take_guild_talent': TakeGuildTalentAction,
        'return_guild_talent': ReturnGuildTalentAction,
        'guild_talent_info_update': UpdateBankTalentInfo,
        'give_back_guild_talent': GiveBackGuildTalentAction,
        'buy_guild_shop_item': BuyGuildShopItemAction,
        'get_guilddata_for_map': GetGuildDataForMapAction,
        'change_member_rating': ChangeMemberRatingAction,
        'check_guild_size': CheckGuildSizeAction,
        'recruitment_locale': RecruitmentLocaleAction,
        'recruitment_message': RecruitmentMessageAction,
        'recruitment_rating': RecruitmentRatingAction,
        'get_recruits_list': GetRecruitsListAction,
        'new_recruit': NewRecruitAction,
        'rm_recruit': RemoveRecruitAction,
        'accept_recruit': AcceptRecruitAction,
        'decline_recruit': DeclineRecruitAction,
        'rename_recruit': RenameRecruitAction,
        'update_guilds_rating': UpdateGuildsRatingAction,
        'on_guild_war_event_changed': OnGuildWarEventChangedAction,

        # PF-106691
        # --- actions for vassals and suzerens
        # --- actions to pass to siedge service
        # 'start_siege'             : StartSiegeAction,
        # 'leave_siege'             : LeaveSiegeAction,
        # 'update_siege'            : UpdateSiegeAction,
        # видимо стоит их убрать  из internalActionMap
        # 'send_tribute': SendTributeAction,
        # 'new_recommended_vassal_notify': NewRecommendedVassalNotify,
        # 'clear_suzerain_invites': ClearSuzerainInvitesAction,
        # 'update_vassals_and_suzerain_info' : UpdateVassalsAndSuzerainInfoAction,
        # 'win_siege' : WinSiegeAction,
        # 'add_vassal': AddVassalAction,
        # 'hide_recommended_vassal': HideRecommendedVassalAction,
        # 'reset_sieges_counter': ResetSiegesCounterAction,
        # 'invite_suzerain': InviteSuzerainAction,
        # 'check_vassal_application': CheckVassalApplicationAction,
        # 'accept_vassal' : AcceptVassalAction,
        # 'decline_vassal': DeclineVassalAction,
        # 'remove_vassal': RemoveVassalAction,

        # --- debug actions ---
        'debug_update_siege'      : DebugUpdateSiegeAction,
        'reset_guild_shop_limits': ResetGuildShopLimits,
        'guild_bank_limits_reset': GuildBankLimitsResetAction,
        'guild_cwpoints_sell' : GuildCWPointsSellAction,
        'set_guild_experience' : SetGuildExperience,
        'set_guild_today_rating' : SetGuildTodayRating,
        # PF-106691
        #'set_siege_duration': SetSiegeDurationAction,
        #'set_siege_score': SetSiegeScoreAction,
        #'set_lost_target_left_time': SetLostTargetLeftTimeAction,
        #'set_ex_vassal_left_time': SetExVassalLeftTimeAction,
        'update_recruit_application': UpdateRecruitApplicationAction,
        'add_active_buff': AddActiveBuffAction,
        # ...
  }

    def onGetWebServerStat(self):
        info("onGetWebServerStat")
        self.response['ok'] = 1
        self.response["awards"] = self.I.WS.awards
        resp = {}
        resp["totalGuildsCount"] = len(self.I.WS.guildAuids)
        totalUsers = 0
        for gauid in self.I.WS.guildAuids:
             data = self.I.WS.activeGuildUsers.get(gauid, None)
             if data:
                 count = len(data)
                 #resp[str(gauid)] = count
                 totalUsers += count
        resp["totalGuildUserCount"] = totalUsers
        resp["failRequests"] = self.I.WS.fail_requests
        self.response["guilds"] = resp
        self.fin()

    ## main http request mapper (раскидываем запросы по handler methods/classes, в зависимости от "/subaddr" и "action=")
    @tornado.web.asynchronous
    def get(self):
        method = self.getParam("method")
        if method:
            self.addArguments( action=method )
        return JsonHandler.get( self )

    ## main http request mapper (раскидываем запросы по handler methods/classes, в зависимости от "/subaddr" и "action=")
    @tornado.web.asynchronous
    def post(self):
        method = self.getParam("method")
        if method:
            self.addArguments( action=method )
        return JsonHandler.get( self )

# ---------------------------------------------------------------------------------------------------------------------------------------------
class SendToGuildAction(InternalMailAction):
    action = "send_to_guild"

    @action_timing
    def onStart(self):
        info("SendToGuildAction.onStart")
        if self.acc.auid:
            guildInfo = self.I.WS.guildAuids.get(self.acc.auid)
            if guildInfo and "guild" in guildInfo and guildInfo["guild"]:
                guildData = guildInfo["guild"]
                info("SendToGuildAction.: GuildData.GuildAuid=%s [acc.auid=%s], msg_id=%s, msg=%r" % ( guildData.GuildAuid, self.acc.auid, self.msg_id, self.msg))
                if self.msg:
                    self.messages = self.msg["messages"]
                    self.fromGuildAuid = self.messages["fGuildAuid"]
                    method = self.messages.get("method")
                    if method == "send_tribute":
                        args = ClassDict(auid=[CC.GUILD_NEUTRAL_AUID],
                                         toGuildAuid=[guildData.GuildAuid],
                                         fromGuildAuid=[self.fromGuildAuid],
                                         tribute=[self.messages["message"].get("tribute")])
                        action = SendTributeAction(args, self.onSend, I=self.I)
                        action.onStart()
                        return
                    elif method == "new_suzerain_notify":
                        args = ClassDict(auid=[CC.GUILD_NEUTRAL_AUID], toGuildAuid=[guildData.GuildAuid], fromGuildAuid=[self.fromGuildAuid])
                        action = NewSuzerainNotify(args, self.onSend, I=self.I)
                        action.onStart()
                        return
                    elif method == "new_recommended_vassal_notify":
                        args = ClassDict(auid=[CC.GUILD_NEUTRAL_AUID], toGuildAuid=[guildData.GuildAuid],
                                         fromGuildAuid=[self.fromGuildAuid],
                                         dontUpdateTime=[self.messages["message"].get("dontUpdateTime")] or False)
                        action = NewRecommendedVassalNotify(args, self.onSend, I=self.I)
                        action.onStart()
                        return
                    elif method == "remove_vassal":
                        args = ClassDict(auid=[CC.GUILD_NEUTRAL_AUID], toGuildAuid=[guildData.GuildAuid],
                                         targetAuid=[self.messages["message"].get("targetAuid")],
                                         notifyVassal=[self.messages["message"].get("notifyVassal")])
                        action = RemoveVassalAction(args, self.onSend, I=self.I)
                        action.onStart()
                    elif method == "update_vassal_info":
                        args = ClassDict(auid=[CC.GUILD_NEUTRAL_AUID], toGuildAuid=[guildData.GuildAuid], targetAuid=[self.messages["message"].get("targetAuid")])
                        action = UpdateVassalInfoAction(args, self.onSend, I=self.I)
                        action.onStart()
                    elif method == "add_vassal":
                        args = ClassDict(auid=[CC.GUILD_NEUTRAL_AUID],
                                         toGuildAuid=[self.messages["message"].get("toGuildAuid")],
                                         targetAuid=[self.messages["message"].get("targetAuid")])
                        accountAction = AddVassalAction(args, self.onSend, I=self.I)
                        accountAction.onStart()
                    else:
                        warn("BAD  action %s skipped" % method)
                else:
                    warn("Request body is empty!")

        self.response["ok"] = 1
        self.fin()

    def onSend(self, response):
        info("SendToGuildAction: onSend %r" % response)
        self.response["ok"] = 1
        self.fin()


class CCUAction(SubAction):
    action = "ccu"

    @action_timing
    def onStart(self):
        info("CCUAction.onStart")
        info("CCU: %r", self.I.WS.awards)
        self.response["ccu"] = self.I.WS.awards

        self.response["ok"] = 1
        self.fin()


class GuildExchangeAction(SubAction):
    """ нам присылают список сообщений игровой почты, из Social EXchange """
    action = "sex_send"

    @action_timing
    def onStart(self):
        info("GuildExchangeAction.onStart")
        """ стартовый метод для обработки action """
        if self.checkValidParam("project"):
            if self.checkValidIntParam("auid"):
                try:
                    json_body = json_loads(self.request.request.body)
                    info("GuildExchangeAction: project=%s, auid=%s, json messages=%s" % (
                    self.project, self.auid, json_body))
                    if self.project == CC.SEX_PW_GUILD_PROJECT:
                        self.guild_data = self.I.WS.getGuildData(self.auid)
                        if self.guild_data:
                            if json_body and isinstance(json_body, dict):
                                messages = json_body.get("messages", {})
                                if messages and isinstance(messages, dict):
                                    self.purge_msg_ids = self.I.WS.handleSocialExchangeMessages(messages,
                                                                                                self.guild_data.mail)
                                    if self.purge_msg_ids:
                                        info("GuildExchangeAction done: project=%s, auid=%s, purge msg_id list=%s" % (
                                        self.project, self.auid, self.purge_msg_ids))
                                        self.response["purge_ids"] = self.purge_msg_ids
                                    self.response["ok"] = 1
                                else:
                                    return self.fail("bad or empty message dict", EC.XS_NO_MESSAGES)
                            else:
                                return self.fail("can't parse message body", EC.XS_BAD_SEND_MESSAGE_BODY)
                        else:
                            return self.fail("no GuildData for auid", EC.XS_BAD_DEST_AUID)
                    else:
                        return self.fail("bad mail project", EC.XS_BAD_DEST_PROJECT)
                except:
                    catch()
                    return self.fail("can't parse message body", EC.XS_BAD_SEND_MESSAGE_BODY)

        self.fin()


class GuildMailAction(InternalMailAction):
    """ по умолчанию просто достаем GuildData и логируем сообщение """

    @action_timing
    def onStart(self):
        debug("GuildMailAction.onStart")
        if self.acc.auid:
            guildInfo = self.I.WS.guildAuids.get(self.acc.auid)

            if guildInfo and "guild" in guildInfo and guildInfo["guild"]:
                guildData = guildInfo["guild"]
                # self.acc.auid - this is guildAuid !!!
                info("GuildMailAction: GuildData.GuildAuid=%s [acc.auid=%s], msg_id=%s, msg=%r" % (
                    guildData.GuildAuid, self.acc.auid, self.msg_id, self.msg))

                self.fakeAcc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=guildData, guildAuid=guildData.GuildAuid)
                self.I.WS.loadGuildData(self.fakeAcc, self.onLoad)
                return
            else:
                warn("GuildMailAction: no GuildData for acc.auid=%s, msg_id=%s, msg=%r" % (
                    self.acc.auid, self.msg_id, self.msg))

        self.response["ok"] = 1
        self.fin()

    def onLoad(self, acc, errMessage=None):
        if acc and errMessage is None:
            self.I.WS.resetPendingChanges(acc)
            acc.GuildData.write(acc.pending)

            awards = self.msg.get("awards", {})
            if not awards:
                awards = None

            if getattr(self.I.WS, "awards"):
                self.I.WS.awards.s_guild_awards = self.I.WS.awards.get("s_guild_awards", 0) + 1

            info("applyGuildAwards( GuildData.GuildAuid=%s, awards=%s )", acc.GuildData.GuildAuid, awards)
            self.resAmount = 0
            self.points = 0.0
            self.clanwarsPlayerRating = 0.0
            self.clanwarsClanRating = 0.0
            if isinstance(awards, list):
                for award in awards:
                    if isinstance(award, dict):
                        award_type = toint(award.get("type"))
                        award_id = toint(award.get("id"))
                        award_count = toint(award.get("count"))
                        if award_type and award_count:
                            try:
                                if award_type == EAwardType.GUILD_RESOURCE:
                                    self.resAmount += award_count
                                elif award_type == EAwardType.GUILD_WAR_EVENT_POINTS:
                                    self.points += award_count
                                elif award_type == EAwardType.CWPOINTS_CLAN:
                                    self.clanwarsClanRating += award_count

                                    # PF-106419
                                    # if self.I.Config.getMainConfig().GUILD_WARS_ENABLED:
                                    #     # храним дань, которую мы собираемся отдавать вассалу
                                    #     acc.GuildData.GuildSuzerain.DonationToday += round(self.I.SD.getGuildVassalsTributeCoef() * award_count)
                            except Exception:
                                catch()
                                err("exception in award (GuildData.GuildAuid=%s, award_type=%s), skipped" % (
                                    acc.GuildData.GuildAuid, str(award_type)))
                    else:
                        err("applyGuildAwards (GuildData.GuildAuid=%s): bad awards" % acc.GuildData.GuildAuid)
            else:
                err("applyGuildAwards (GuildData.GuildAuid=%s): bad awards" % acc.GuildDataGuildAuid)

            info("applyGuildAwards( GuildData.GuildAuid=%s, resInvested=%s, points=%s, clanwarsClanRating=%s )" % (
                acc.GuildData.GuildAuid, self.resAmount, self.points, self.clanwarsClanRating))

            # изменено в соответствии с PF-106419
            changed = False
            if self.resAmount != 0:
                changed = True
                acc.GuildData.GuildLevelInfo.Experience += self.resAmount  # влили в гильдию ресурсы

            if self.points > 0.0:
                self.I.WS.addPointsToGuildWarEventPool(acc.GuildData.GuildAuid, self.points)

            if self.clanwarsClanRating != 0:
                # для отключения кланваров по PF-93306
                if self.I.Config.getMainConfig().GUILD_WARS_ENABLED:
                    changed = True
                    acc.GuildData.GuildInfo.CWPoints_Clan += self.clanwarsClanRating

                    # cwPointsWithBuff = self.clanwarsClanRating
                    # debug("applyGuildAwards  pre buffBonus %r", cwPointsWithBuff)
                    # cwPointsWithBuff = self.getBuffBonus(self.clanwarsClanRating, acc.GuildData)
                    # debug("applyGuildAwards  post buffBonus %r", cwPointsWithBuff)

            if changed:
                self.sendUpdates()
        else:
            warn(errMessage)
            self.response["ok"] = 1

        self.fin()

    def onScoreSiegeAction(self, response):
        info("GuildMailAction.onScoreSiegeAction response %r", response)
        if response:
            for x in response:
                if not x.get("ok"):
                    warn("Response from siege service: %r", x)

    def sendUpdates(self):
        info("GuildMailAction.sendUpdates for GuildAuid=%r", self.fakeAcc.GuildData.GuildAuid)
        changes = self.I.WS.pickPendingChanges(self.fakeAcc)
        self.I.WS.sendBroadCast(self.fakeAcc, changes, [], '')
        self.I.WS.saveGuildData(self.fakeAcc, None)
        self.response["ok"] = 1

    def getBuffBonus(self, clanwarsClanRating, GD):
        bonusPrice = clanwarsClanRating
        debug("ActiveHoldGuild buffs %r", GD.ActiveHoldGuildBuffs.generateJsonDict())
        for bufId, duration in GD.ActiveHoldGuildBuffs.iteritems():
            if int(time.time()) < duration:
                staticBonus = self.I.SD.getGuildBufById(toint(bufId))
                if staticBonus:
                    for bonus in staticBonus['bonuses']['Item']:
                        if bonus['classType'] == 'SiegePointsBonus':
                            bonusPrice += self.I.SD.roundFloatToInt(clanwarsClanRating * float(bonus['modifiers']['multiplicativeValue']))
                            bonusPrice += self.I.SD.roundFloatToInt(float(bonus['modifiers']['additiveValue']))
        return bonusPrice


# ---------------------------------------------------------------------------------------------------------------------------------------------

class GuildService(ICSVActionTimingWriter, ISocialExchangeUser, ITornadoServer):
    server_type_name = "gs"

    _SPECIFIC_CONFIG_PARAMS = {
        "guilds_svc": "GUILD_SERVICES",
        "siege_svc" : "SIEGE_SERVICES",
        "chat_serv": "CHAT_SERVER_ADDRESS",
        "stats_agent": "STATS_AGENT_URL",
        "balancer_int": "BALANCER_INTERNAL",
        "curl_wrk": "HTTP_CURL_WORKERS",
        "req_limit": "HTTP_REQUEST_LIMIT",
        "soc_agg": "SOCIAL_AGGREGATOR_ADDRESS",
        "export_cfg": "MIRROR_EXPORT_CONFIG",
        "export_trd": "MIRROR_EXPORT_THREADS",
        "events": "EVENT_SERVICES",
        "guild_icons_upload_url": "GUILD_ICONS_UPLOAD_URL_PATTERN",
        "tournament_server": "TOURNAMENT_SERVER",
        "stats": "STATS_SERVER_URL",
    }

    mailActions = {
        # тип почтового сообщения - строка не более 15 символов!
        #TODO: добавить обработчики для событий из гильдовой почты
        "s_guild_awards": GuildMailAction,
        "send_to_guild": SendToGuildAction,
    }

    def __init__(self, **kwargs):
        super(GuildService, self).__init__(**kwargs)

        self.users = {}  # здесь будем хранить записи юзеров (со списками френдов) [auid] -> user info
        self.guildAuids = {}  # [guildAuid]["guild"] -> [GuildData], [guildAuid]["siege"] -> [SiegeData], [guildAuid]['requests'] -> RequestsData

        self.activeGuildUsers = {}  # [guildAuid] -> [auids] хранится auid'ы пользователей, которые сейчас в онлайне в этой гильдии

        self.peers = {}  # [server_id] -> peer server info
        self.aggregatorProperties = {}  # [auid] -> aggregatorProperties acc

        self.ts_guild_expire = 0
        self.ts_mail_touch = 0

        self.awards = ClassDict()
        self.awards.s_guild_awards = 0
        self.fail_requests = ClassDict()

        self.techs = {}
        self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA, {"type": ConfigEventType.Techs}, params=None,
                         callback=self.onGetTechsInfos)
        self.recruits_changes = self.generateRecruitsDataChangeStr()

        self.check_gr_queue_touch = 0
        self.guildsRatingQueue = []
        self.guildsRatings = []

        self.guildsToUpdateOnChangeGuildWarEvent = []
        self.check_guild_war_event = 0

    def onGetTechsInfos(self, response):
        if response and "r" in response:
            info("GuildService: onGetTechsInfos")
            for techEvent in response["r"]:
                compensationTypes = techEvent["customData"]["techType"].split(',')
                if "rating" in compensationTypes:
                    self.techs[techEvent["_id"]] = {"startTime": techEvent["startTime"],
                                                    "duration": techEvent["customData"]["compensation"]}
        else:
            err("Failed to load techs info")

    # -----------------------------------------------
    def tick(self):
        now = toint(time.time())
        if now % 60 == 0 and self.lastInstrumentedAction + 10 < now:
            self.updateInstrumentedActions()
            self.lastInstrumentedAction = now
            if self.I.STATS:
                ts0 = time.clock()
                try:
                    self.I.STATS.Send()
                except:
                    catch()
                info("STATS.Send time: %.3f" % (time.clock() - ts0))

        if now > self.ts_guild_expire + GUILD_EXPIRE_CHECK_PERIOD:
            self.ts_guild_expire = now
            for guildAuid in self.activeGuildUsers.keys():
                self.tryUnloadGuild(guildAuid)

        self.mailTick()
        self.guildsRatingQueueTick()
        self.guildWarEventTick()
        self.gcTick()

    # OVERRIDE
    def onGetPeerServer(self, peer, peer_name, peer_id, status):
        if status == PEER_DELETED:
            return

        if peer["on"] and peer_id:
            # просим каждый online WS выслать нам полный список юзеров для подписки (а то мы тут только что перезапустились)
            self.peers[toint(peer_id)] = peer
            if status == PEER_ADDED:
                res = httpClientRequest(addr=peer["addr"], server="x",
                                        params="action=gs_resubscribe&name=%s" % options.server_name)

    _THRIFT_SERVICES = {
        "account_management": GuildManagementServerHandler,
    }

    # -----------------------------------------------
    def initHandlers(self, application):
        application.add_handlers(r"(.*)", [
            ( r"/x", GuildServiceHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I) ),
            ( r"/thrift", ThriftHandler, dict(I=self.I, SERVICES=self._THRIFT_SERVICES) ),
            ( r"/sex", SocialExchangeJsonHandler, dict(SUBADDR=SUBADDR_BALANCED, I=self.I) ),
        ])

        SocialExchangeJsonHandler.unloggedActionMap['sex_send'] = GuildExchangeAction
        SocialExchangeJsonHandler.unloggedActionMap['ccu'] = CCUAction

        # готовы слушать; рапортуем координатору (и получаем в ответ список WS peers)
        self.getPeersFromCoordinator()

    # return True if startup enviroment is bad
    @staticmethod
    def checkStartupFail():
        # проверяем, не слушает ли на нашем порту кто-то еще (защита от повторного запуска координатора)
        self_addr = "127.0.0.1:" + str(options.port)
        res = httpClientRequest(addr=self_addr, server="x", params="action=check_alive&name=_guild_server_")
        if res and res.get("ok") != None:
            fatal("DUPLICATE GUILD SERVER: already listening on " + self_addr + "\n(reply was %s)" % str(res))
            return True  # обламываемся, уже запущена копия веб-сервера на этом порту

        print("check startup environment: ok, port free (" + self_addr + ")")

    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = GUILD_SERVER_ID
            options.server_name = GUILD_SERVER_NAME
            options.server_class = "guilds"
        else:
            options["server_id"].set(GUILD_SERVER_ID)
            options["server_name"].set(GUILD_SERVER_NAME)
            options["server_class"].set("guilds")

    # -----------------------------------------------

    # -----------------------------------------------
    @staticmethod
    def initInterfaces(classOf=None):
        # --- для начала надо связаться с координатором и получить от него актуальные кластерные настройки для cfg
        coord_res = {}
        if options.coordinator != "none":
            # начали слушать; сообщаем координатору, что готовы принимать http-send'ы на своем порту
            coord_res = httpClientRequest(addr=options.coordinator, server="x",
                                          params="action=ws_ready&name=%s" % options.server_name)
            if coord_res and coord_res.get("ok"):
                info("Reported 'ready' state to coordinator: reply " + str(coord_res))
                classOf.updateSpecificParamList(coord_res, getattr(classOf, "_SPECIFIC_CONFIG_PARAMS", {}),
                                                classOf.server_type_name)
            else:
                return fatal("Cannot report to coordinator (addr:%s)\ncoordinator reply was:%s" % (
                str(options.coordinator), str(coord_res) ))

        iDict = ClassDict()

        # http-клиент, потенциально -- для запросов к facebook и zzima api
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient(max_clients=coord_cfg.COORDINATOR_HTTP_CURL_WORKERS)
        iDict.WS = IWebServer()  # чисто для генерации GUID-ов

        # обычным веб-серверам требуется только оболочка DataManager для заворачивания JSON-данных
        iDict.MD = IDataManager()
        info("MD interface: " + str(iDict.MD))

        iDict.Config = MultiConfig()
        iDict.MSD = MultiStaticData("../xdb/ExportedSocialData.xml", iDict.Config.getMainConfig(), loadLocales=False, applyOverrides=True)
        iDict.SD = iDict.MSD.getMainSD()

        iDict.AGG = IfaceFactory.makeSocAggInterface(options.soc_agg,
                                                     coord_cfg.COORDINATOR_SOCIAL_AGGREGATOR_ADDRESS, SOCAGG_VERSION,
                                                     HTTP=iDict.HTTP)

        iDict.WSX = IfaceFactory.makeIPeerWebServerInterface(options.wsx, HTTP=iDict.HTTP)
        iDict.CHAT = IfaceFactory.makeIChatServerInterface(options.chat, coord_cfg.COORDINATOR_CHAT_SERVICES,
                                                           HTTP=iDict.HTTP)

        iDict.GUILD = iguildservice.IHttpGuildService(addresses=cfg.GUILD_SERVICES, HTTP=iDict.HTTP)

        request_limit = getattr(cfg, "HTTP_REQUEST_LIMIT", 1000)
        info("using http request_limit=%s", request_limit)
        iDict.FRIENDS = ifriendservice.IHttpFriendService(addresses=coord_cfg.COORDINATOR_FRIEND_SERVICES,
                                                          HTTP=iDict.HTTP, request_limit=request_limit)

        iDict.SEX = IfaceFactory.makeSocialExchangeInterface(options.sex, iDict.HTTP,
                                                             coord_cfg.COORDINATOR_SOCIAL_EXCHANGE_URL,
                                                             options.server_addr, request_limit=request_limit)
        info("Social Exchange interface: " + str(iDict.SEX))

        iDict.DATA = IfaceFactory.makeIDataInterface("mongo", coord_cfg.COORDINATOR_MONGO_CONFIG, None)

        iDict.MIRROR = IfaceFactory.makeMirrorInterface(options.mirror, coord_cfg.COORDINATOR_MIRROR_QUEUE_CONFIG,
                                                        num_threads=coord_cfg.COORDINATOR_MIRROR_QUEUE_THREADS)
        info("Mirror interface: " + str(iDict.MIRROR))

        iDict.SIEGE = IfaceFactory.makeSiegeServiceInterface(options.sieges, cfg.SIEGE_SERVICES, HTTP=iDict.HTTP,
                                                             request_limit=request_limit)
        # Доступ к pw_stats для того, чтобы быстро подтягивать информацию о гильдиях
        iDict.EXPORT = IfaceFactory.makeExportInterface(options.export, coord_cfg.COORDINATOR_MIRROR_EXPORT_CONFIG,
                                                     num_threads=coord_cfg.COORDINATOR_MIRROR_EXPORT_THREADS)

        iDict.STATS = IfaceFactory.makeIStatsInterface(options.stats, coord_cfg.COORDINATOR_STATS_AGENT_URL, iDict, cfg.STATS_RESEND_POOL_LIMIT)
        info( "Statistics interface: " + str(iDict.STATS) )

        return iDict

    # Проверить, шардится ли конкретная гильдия на наш сервис
    def isMyUser(self, guildAuid):
        self_ws_addr = options.server_addr
        addresses = cfg.GUILD_SERVICES
        address_count = len(addresses)

        guildAdress = addresses[guildAuid % address_count]
        return guildAdress == self_ws_addr

    def getUserAcc(self, auid):
        return self.users.get(auid)

    def buildGuildsRatingQueue(self, guildsRatings):
        self.guildsRatingQueue = [x for x in self.users.iterkeys()]
        self.guildsRatings = dict(guildsRatings)

    def updateGuildsRatingsInSiegeData(self):
        if self.guildsRatingQueue and self.guildsRatings:
            i = CC.GULD_RATINGS_CHECK_USERS_COUNT
            while i and self.guildsRatingQueue:
                guildAuid = self.guildsRatingQueue.pop()
                acc = self.getUserAcc(guildAuid)
                if acc and acc.SiegeData and acc.GuildData:
                    self.resetPendingChanges(acc)
                    acc.SiegeData.write(acc.pending)
                    for siegeId, siege in  acc.SiegeData.SiegeGuildInfoKeeper.iteritems():
                        if siege.ShortInfo.GuildAuid in self.guildsRatings:
                            siege.ShortInfo.Rating = self.guildsRatings[siege.ShortInfo.GuildAuid]
                    changes = self.pickPendingChanges(acc)
                    self.sendBroadCast(acc, changes, acc.GuildData.getAllMembers(), '')
                    self.saveGuildData(acc, None)
                i -= 1

    def guildsRatingQueueTick(self):
        now_second = toint(time.time())
        if now_second > self.check_gr_queue_touch + CC.GULD_RATINGS_UPDATE_CHECK_PERIOD:
            self.updateGuildsRatingsInSiegeData()
            self.check_gr_queue_touch = toint(time.time())

    def tryUnloadGuild(self, guild_auid):
        membersOnline = self.activeGuildUsers.get(guild_auid, None)
        if not membersOnline:
            info("Unload guildAuid=%r" % guild_auid)
            self.unregisterGuild(guild_auid)

            if guild_auid in self.activeGuildUsers:
                del self.activeGuildUsers[guild_auid]

    def loadGuildData(self, acc, callback):
        GuildData = self.getGuildData(acc.guildAuid)
        if not GuildData:
            info("loadGuildData: auid=%r, guildAuid=%r NOT GuildData, CREATE" % (acc.auid, acc.guildAuid))
            acc.GuildData = None
            _callback = None
            if callback:
                _callback = functools.partial(self.loadGuildDataCallback, acc=acc, callback=callback)
            if not _callback:
                _callback = self.dummyCallback

            self.loadGuildDataByGuildAuid(acc.guildAuid, _callback)
        else:
            info("loadGuildData: auid=%r, guildAuid=%r exist GuildData" % (acc.auid, acc.guildAuid))

            SiegeData = self.getSiegeData(acc.guildAuid)
            acc.GuildData = GuildData
            acc.SiegeData = SiegeData
            acc.RecruitRequests = self.getRecruitData(acc.guildAuid)

            if callback:
                callback(acc)

    def loadGuildDataCallback(self, response, acc=None, callback=None):
        errMessage = None
        if response:
            try:
                data_json = response["r"]["data"] or '{"GuildData":{}}'
                acc.Requests = response["r"].get("requests")
                acc.currentGuildWarEvent = 0
                try:
                    acc.currentGuildWarEvent = long(response["r"].get("currentGuildWarEvent"))
                except:
                    warn("wrong currentGuildWarEvent, reset it to 0")

            except:
                info("Failed to load GuildData, mongo response: %r", response)
                data_json = '{"GuildData":{}}'
                acc.Requests = None

            self.resetPendingChanges(acc)
            acc.GuildData = self.getGuildData(acc.guildAuid)
            if not acc.GuildData:
                acc.GuildData = GuildData()
                acc.GuildData.load(data_json)
                acc.GuildData.GuildAuid = acc.guildAuid
                acc.GuildData.init(None)

            acc.SiegeData = self.getSiegeData(acc.guildAuid)
            if not acc.SiegeData:
                acc.SiegeData = SiegeData()
                acc.SiegeData.init(None)

            self.registerGuild(acc.GuildData.GuildAuid, acc.GuildData, acc.SiegeData,
                               acc.currentGuildWarEvent)  # !!! почему первый параметр не acc.guildAuid
            _recruitsCallback = functools.partial(self.onRecruitsInfoFound, acc=acc)
            self.I.DATA.find(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA,
                             {"guild_auid": acc.GuildData.GuildAuid, "created": {
                                 "$gt": int(time.time()) - self.I.SD.data['GuildRecruitment']['guildRequestLifetime']},
                                 "status": 1}, _recruitsCallback, params=None)

            self.validateSuzerain(acc.GuildData)  # !!! тут тоже используется acc.GuildData.GuildAuid

            if "e" in response and response["e"] is not None:
                errMessage = "Error in processing database request"
                if callback:
                    callback(acc, errMessage)
                return

            # PF-106691
            # self.I.SIEGE.subscribe(acc.guildAuid, functools.partial(self.onSiegeServiceLogin, acc=acc, callback=callback))
            # return

        if callback:
            callback(acc, errMessage)

    def loadGuildDataByGuildAuid(self, guilldAuid, _callback):
        if not _callback:
            _callback = self.dummyCallback
        self.I.DATA.find_one("guilds", "guilds", {"key": getMongoKeyAuid(guilldAuid)}, _callback, params=None)

    def validateSuzerain(self, guildData):
        if guildData.GuildSuzerain.get() is None:
            warn("GuildData with empty suzerain found for guild %d", guildData.GuildAuid)
            guildData.GuildSuzerain, _ = guildData.newGuildMapEntity()
            guildData.GuildSuzerain.ShortInfo, _ = guildData.newGuildShortInfo()

    def pickPendingChanges(self, acc):
        response = {}
        SubAction.wrapPendingMessages(acc, None, response)
        acc.pending_changes = []
        changes = {}

        guildChanges = response.get("GuildData") or []
        SubAction.convertResponseObjects(guildChanges)
        if len(guildChanges):
            changes["guild_data"] = guildChanges
        siegeChanges = response.get("SiegeData") or []
        SubAction.convertResponseObjects(siegeChanges)
        if len(siegeChanges):
            changes["siege_data"] = siegeChanges
        return changes

    def generateRecruitsDataChangeStr(self):
        acc = ClassDict()
        self.resetPendingChanges(acc)

        recruitsData = RecruitsData()
        recruitsData.init(None)
        recruitsData.write(acc.pending)
        recruitsData.HasChanges = True

        response = {}
        SubAction.wrapPendingMessages(acc, None, response)

        recruitsChanges = response.get("RecruitsData") or []
        SubAction.convertResponseObjects(recruitsChanges)
        return recruitsChanges

    def onSiegeServiceLogin(self, response, acc=None, callback=None):
        info("GuildService: onSiegeServiceLogin")
        guildAuids = []
        if response and acc:
            try:
                acc.SiegeData.write(acc.pending)
                guildAuids = acc.SiegeData.update(response)
            except:
                err("Bad data from Siege service received")
                if callback:
                    callback(acc, None)
                    return

        for k in acc.GuildData.ActiveSieges.keys():
            acc.GuildData.removeSiege(k)

        for k in acc.GuildData.InitiatedSieges.keys():
            siege = acc.GuildData.getInitiatedSiegeByID(k)
            if not acc.SiegeData.getSiegeById(siege.SiegeId):
                acc.GuildData.InitiatedSieges.remove(siege)

        if guildAuids:
            for siegeId, siege in acc.SiegeData.ActiveSieges.iteritems():
                acc.GuildData.addActiveSiege(siege.Uid)
            _callback = functools.partial(self.onSiegeDataFromSQL, acc=acc, callback=callback)
            self.I.EXPORT.getGuildsInfo(guildAuids, _callback)
            return
        else:
            # Если мы подписались, а список осад пустой надо бы проверить, а есть ли осады в GuildData
            # и разослать всем изменения
            if acc.GuildData.InitiatedSieges:
                acc.GuildData.write(acc.pending)
                for k in acc.GuildData.InitiatedSieges.keys():
                    siege = acc.GuildData.getInitiatedSiegeByID(k)
                    acc.GuildData.InitiatedSieges.remove(siege)
            acc.GuildData.SiegeForMyGuildEndTime = 0
            acc.GuildData.LockedByOtherGuild = False

            changes = self.pickPendingChanges(acc)
            self.sendBroadCast(acc, changes, [], '')
            self.saveGuildData(acc, None)

        if callback:
            callback(acc, None)

    def onSiegeDataFromSQL(self, reply, acc=None, callback=None):
        r = reply["r"]
        if r and len(r):
            # Обновим заодно и все старые записи, если у этих кланов что-то изменилось
            for guildInfo in r:
                acc.SiegeData.updateGuildInfoFromSQL(guildInfo)

        if callback:
            callback(acc, None)

    def saveGuildData(self, acc, callback, mirror=True):
        if not callback:
            callback = self.dummyCallback
        json_data = acc.GuildData.generateJsonDict()
        str_data = json_dumps(json_data)
        _callback = functools.partial(self.onSaveGuildData, acc, callback, mirror)
        self.I.DATA.update_data("guilds", "guilds", getMongoKey(acc), str_data, _callback, params=None)

    def onSaveGuildData(self, acc, callback, mirror, response):
        debug("onSaveGuildData response %r", response)
        if mirror:
            self.I.MIRROR.addRequest(MirrorDataType.GUILD_DATA, acc.guildAuid, self.dummyCallback)

        if callback:
            callback(response)

    def saveRequests(self, guildId, gAuid, data, _callback):
        if not _callback:
            _callback = self.dummyCallback

        self.I.DATA.update("guilds", "guilds", {"key": getMongoKeyAuid(guildId)},
                           {"requests.SuzerainInvites.%d" % gAuid: data}, _callback, params=None)

    def saveCurrentGuildWarEventId(self, guild_auid, event_id, _callback):
        if not _callback:
            _callback = self.dummyCallback

        self.I.DATA.update("guilds", "guilds", {"key": getMongoKeyAuid(guild_auid)}, {"currentGuildWarEvent": event_id},
                           _callback, params=None)

    def onRecruitsInfoFound(self, response, acc=None):
        recruitRequests = []
        if response:
            try:
                recruitCursor = response["r"]
                for recruitInfo in recruitCursor:
                    recruitRequests.append(recruitInfo)
            except Exception:
                catch()
        else:
            err("onRecruitsInfoFound: empty response from mongo for guild_auid %s, pers_auid %s",
                acc.GuildData.GuildAuid)
            return

        if recruitRequests:
            recruitRequests.sort(key=lambda x: x["created"])
            self.registerRecruitsData(acc.GuildData.GuildAuid, recruitRequests)
        else:
            info("onRecruitsInfoFound: empty recruit data: %r for guild %s", recruitRequests, acc.GuildData.GuildAuid)
        acc.RecruitRequests = self.getRecruitData(acc.GuildData.GuildAuid)

    def broadcastRecruitsChanges(self, guildData, auids=None):
        changes = {"recruits_data": self.recruits_changes}
        acc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID)
        if not auids:
            auids = [mem.Person for _id, mem in guildData.Members.iteritems() if mem.IsOfficer]
        debug("broadcastRecruitsChanges: changes %s, to auids %s", changes, auids)
        self.sendBroadCast(acc, changes, auids, '')

    def dummyCallback(self, data_reply):
        pass

    def dummyMongoCallback(self, response):
        if not response:
            err("Mongo call returns empty response!")
        elif 'e' in response:
            err("Mongo call returns error: %s", response)
        else:
            debug("Mongo call returns: %s", response)

    def checkFailCallback(self, sname, data_reply):
        if not data_reply:
            self.fail_requests[sname] = self.fail_requests.get(sname, 0) + 1
            warn("checkFailCallback fail_requests stats %r", self.fail_requests)
        else:
            if not self.fail_requests.get(sname, 0):
                self.fail_requests[sname] = 0

    # acc.auid == -CC.GUILD_NEUTRAL_AUID когда редактируем гильдию GMTools'ой
    def canInvite(self, acc):
        member = acc.GuildData.findMemberByAuid(acc.auid)
        if member:
            return member.IsOfficer
        return False or acc.auid == CC.GUILD_NEUTRAL_AUID

    # acc.auid == CC.GUILD_NEUTRAL_AUID когда редактируем гильдию GMTools'ой
    def isOwner(self, acc):
        return acc.GuildData.Owner.Person == acc.auid or acc.auid == CC.GUILD_NEUTRAL_AUID

    def registerGuild(self, guildAuid, GuildData, SiegeData, currentGuildWarEvent=0):
        if guildAuid:
            self.guildAuids[guildAuid] = {
                "guild": GuildData,
                "siege": SiegeData,
                "requests": ClassDict(),
                "recruits": list(),
                "currentGuildWarEvent": currentGuildWarEvent,
            }
            self.onGuildRegister(GuildData)

    def registerRecruitsData(self, guildAuid, recruitRequests):
        try:
            self.guildAuids[guildAuid]["recruits"] = recruitRequests
        except Exception:
            catchFull(stopAt='callback')

    def registerNewRecruitData(self, guildAuid, recruitInfo):
        debug("registerNewRecruitData: guild %s, recruit %s", guildAuid, recruitInfo)
        try:
            self.guildAuids[guildAuid]["recruits"].append(recruitInfo)
            debug("Guild %s updated recruit list: %s", guildAuid, self.guildAuids[guildAuid]["recruits"])
        except Exception:
            catchFull(stopAt='callback')

    def unregisterRecruitData(self, guildAuid, auid):
        if guildAuid:
            recruits = self.guildAuids[guildAuid]["recruits"]
            if recruits:
                pos = None
                for i, r in enumerate(recruits):
                    if r["pers_auid"] == auid:
                        pos = i
                        break
                if pos is not None:
                    debug("unregisterRecruitData: removing recruit %s from guild %s list", auid, guildAuid)
                    del recruits[pos]
                    return True
        return False

    def unregisterGuild(self, guildAuid):
        guildInfo = self.guildAuids.get(guildAuid)
        if guildInfo and "guild" in guildInfo:
            if guildInfo["guild"]:
                self.onGuildUnregister(guildInfo["guild"])
                self.guildAuids.pop(guildAuid, None)

    def getGuildData(self, guildAuid):
        if guildAuid in self.guildAuids:
            self.guildAuids[guildAuid]["guild"].init(None)
            return self.guildAuids[guildAuid]["guild"]
        return None

    def getGuildWarEventId(self, guildAuid):
        if guildAuid in self.guildAuids:
            return self.guildAuids[guildAuid]["currentGuildWarEvent"]
        return 0

    def setGuildWarEventId(self, guildAuid, eventId):
        if guildAuid in self.guildAuids:
            self.guildAuids[guildAuid]["currentGuildWarEvent"] = eventId

    def getGuildDataReadOnly(self, guildAuid):
        try:
            return self.guildAuids[guildAuid]["guild"]
        except KeyError:
            return None

    def getRecruitData(self, guildAuid):
        try:
            return self.guildAuids[guildAuid]["recruits"]
        except KeyError:
            return []

    def getSiegeData(self, guildAuid):
        if guildAuid in self.guildAuids:
            self.guildAuids[guildAuid]["siege"].init(None)
            return self.guildAuids[guildAuid]["siege"]
        return None

    def removeRequestsData(self, guildId, data, _callback=None):
        if not _callback:
            _callback = self.dummyCallback

        self.I.DATA.unset("guilds", "guilds", {"key": getMongoKeyAuid(guildId)}, data, _callback)

    def updateGuildShortName(self, auid, guildshortname):
        if guildshortname == "":
            self.I.AGG.setProperty(auid, "guildshortname", urlQuote("-"), callback=self.onDummyAggCallback)
        else:
            self.I.AGG.setProperty(auid, "guildshortname", urlQuote(guildshortname), callback=self.onDummyAggCallback)
        self.I.FRIENDS.updateGuildShortName(auid, guildshortname)
        self.resetChat(auid, guildshortname)

    def resetChat(self, auid, guildshortname):
        acc = self.users.get(auid)
        if acc:
            if acc.server:
                peer = self.peers.get(acc.server)
                if peer:
                    self.I.WSX.post(
                        peer["addr"],
                        dict(
                            action='guild_resubscribe_to_chat',
                            uid=acc.uid,
                            guildshortname=guildshortname,
                        ),
                        "none",
                        self.dummyCallback
                    )


    def resetPendingChanges(self, acc):
        acc.pending_changes = []
        acc.pending = GroupPendingChangeWriter(acc)

    def sendBroadCast(self, acc, changes, auids, cmd):
        info("sendBroadCast: from_auid=%r, changes=%r", acc.auid, changes)

        auid = acc.auid
        guild_auid = 0
        server_uid_groups = {}
        to_auids = auids[:]
        if not to_auids:
            for gmId in acc.GuildData.Members.keys():
                member = acc.GuildData.getGuildMemberByID(gmId)
                if member.Person != auid:
                    to_auids.append(member.Person)

        for to_auid in to_auids:
            to_acc = self.users.get(to_auid)
            if to_acc and to_acc.server:
                group = server_uid_groups.get(to_acc.server) or []
                group.append(to_acc.uid)
                server_uid_groups[to_acc.server] = group
        if acc.GuildData:
            guild_auid = acc.GuildData.GuildAuid
        if server_uid_groups:
            for action in changes:
                post_body = json_dumps(changes[action])

                for server_id, uid_list in server_uid_groups.iteritems():
                    peer = self.peers.get(server_id)
                    if peer:
                        Callback = functools.partial(self.checkFailCallback, peer.get("name", ""))
                        self.I.WSX.post(
                            peer["addr"],
                            dict(
                                action=action,
                                cmd=cmd,
                                to_uids=strList(uid_list),
                                guild_auid=guild_auid
                            ),
                            post_body,
                            Callback
                        )
                    else:
                        err("GuildService: bad peer id=%r", server_id)
        else:
            info("GuildService: empty server_uid_groups for auids=%r" % auids)

    def subscribeUserAccountOnGuildCreate(self, auid, guildAuid, server, uid):
        acc = self.getUserAcc(auid)  # auid should be already checked by a caller
        if acc:
            return acc, ("GuildService: acc already exist auid=%r, guildAuid=%r" % (auid, guildAuid))

        acc = ClassDict(auid=auid, online=True, guildAuid=guildAuid, server=server, uid=uid, GuildData=None,
                        SiegeData=None, lastLogin=toint(time.time()), currentGuildWarEvent=0)

        # Регистрируемся как активный участник гильдии
        if guildAuid in self.activeGuildUsers:
            return acc, ("GuildService: guildAuid already exist auid=%r, guildAuid=%r" % (auid, guildAuid))
        else:
            self.activeGuildUsers[guildAuid] = [auid]

        self.users[auid] = acc
        return acc, None

    # заводим аккаунт юзера и помечаем как активный, также высылаем GuildData
    def subscribeUserAccount(self, auid, guildAuid=0, server=None, uid=None, callback=None):
        if auid is not None:
            acc = self.getUserAcc(auid)
            if acc:
                acc.guildAuid = guildAuid
                info("GuildService: acc already exist auid=%r, guildAuid=%r", auid, guildAuid)
            else:
                acc = ClassDict(auid=auid, online=True, guildAuid=guildAuid, server=server, uid=uid, GuildData=None,
                                SiegeData=None, lastLogin=toint(time.time()), currentGuildWarEvent=0)

            # Регистрируемся как активный участник гильдии
            if guildAuid in self.activeGuildUsers:
                auids = self.activeGuildUsers[guildAuid]
                if auids:
                    if auid not in auids:
                        auids.append(auid)
                else:
                    self.activeGuildUsers[guildAuid] = [auid]
            else:
                self.activeGuildUsers[guildAuid] = [auid]

            self.users[auid] = acc
            self.loadGuildData(acc, callback)  # !!! нужно ли это, когда клан только создаётся?

            info("GuildService: subscribeUserAccount: auid=%r, guildAuid=%r", auid, guildAuid)
            return acc

        err("GuildService: subscribeUserAccount: bad auid=%r, guildAuid=%r", auid, guildAuid)
        return None

    def unsubscribeUserAccount(self, auid, guildAuid):
        if auid is not None:
            acc = self.users.get(auid)
            if acc:

                # Перестаем быть активным участником гильдии
                if guildAuid in self.activeGuildUsers:
                    auids = self.activeGuildUsers[guildAuid]
                    if auids:
                        if auid in auids:
                            auids.remove(auid)

                acc.online = False

                # оповещаем peer friend services, что юзер теперь не живет ни на какой WS-ке
                acc.server = 0

                # убиваем с концами
                self.users.pop(auid)

                info("GuildService: unsubscribeUserAccount: auid=%r, guildAuid=%r", auid, guildAuid)
            else:
                err(" GuildService: unsubscribeUserAccount: cannot find acc with auid=%r", auid)
        else:
            err("GuildService: unsubscribeUserAccount: bad auid=%r", auid)

    # -------------------------------------------------------------------
    # вызывается после создания или загрузки гильдии на сервис; сюда пишем всю типовую инициализацию (создание чатиков, подписку на peer сервисы и т.п.)
    def onGuildRegister(self, GuildData):
        info("onGuildRegister: guildAuid=%r" % GuildData.GuildAuid)
        GuildData.mail = ClassDict(auid=GuildData.GuildAuid,
                                   db=ClassDict())  # дефолтные механизмы ISocialExchangeUser принимают acc, и хотят чтобы там были acc.auid и acc.db
        _callback = functools.partial(self.onSocialExchangeLogin, acc=GuildData.mail)
        self.I.SEX.login(GuildData.GuildAuid, CC.SEX_PW_GUILD_PROJECT, _callback)

    # вызывается перед выгрузкой гильдии из памяти сервиса; сюда пишем всю типовую деинициализацию (удаление чатиков, отписывание от peer сервисов и т.п.)
    def onGuildUnregister(self, GuildData):
        info("onGuildUnregister: guildAuid=%r" % GuildData.GuildAuid)
        mail = getattr(GuildData, "mail", None)
        if mail:
            self.I.SEX.logout(mail.auid, mail.sex_sid, mail.sex_server)

        # PF-106691
        # siege = getattr(GuildData, "Siege", None)
        # if siege:
        #     self.I.SIEGE.unsibscribe(GuildData.GuildAuid)

    # -------------------------------------------------------------------
    def resetMailTickers(self, GuildData=None):
        if GuildData is not None:
            mail = getattr(GuildData, "mail", None)
            if mail is not None:
                mail.sex_touch = toint(time.time() - CC.SEX_KEEPALIVE_PERIOD + 1.0)
            self.ts_mail_touch = toint(time.time() - CC.SEX_KEEPALIVE_CHECK_PERIOD + 1.0)

    # -------------------------------------------------------------------
    def onNewGuildWarEvent(self, event_id, guilds):
        guildsToUpdate = guilds if guilds else [x for x in self.activeGuildUsers.iterkeys()]
        if not self.guildsToUpdateOnChangeGuildWarEvent or event_id != self.guildsToUpdateOnChangeGuildWarEvent[1]:
            self.guildsToUpdateOnChangeGuildWarEvent = (guildsToUpdate, event_id)
        else:
            self.guildsToUpdateOnChangeGuildWarEvent[0].extend(guildsToUpdate)

    def validateGuildWarEventIndex(self, guild_data, guild_auid, event_id, acc=None, mirror=True):
        currentGuildWarEvent = self.getGuildWarEventId(guild_auid)
        if currentGuildWarEvent != event_id:
            debug("gw event for guild %s has been changed", guild_auid)
            fakeAcc = acc
            if not fakeAcc:
                fakeAcc = ClassDict(auid=CC.GUILD_NEUTRAL_AUID, GuildData=guild_data, guildAuid=guild_auid)
            self.setGuildWarEventId(guild_auid, event_id)
            self.saveCurrentGuildWarEventId(guild_auid, event_id, self.dummyMongoCallback)
            self.updateGuildDataOnGWEventChanged(fakeAcc, mirror)

    def tickHandleOnNewGuildWarEvent(self):
        if self.guildsToUpdateOnChangeGuildWarEvent:
            debug("tickHandleOnNewGuildWarEvent tick: %r", self.guildsToUpdateOnChangeGuildWarEvent)
            guildsToUpdate, event_id = self.guildsToUpdateOnChangeGuildWarEvent

            i = CC.GULD_RATINGS_CHECK_USERS_COUNT
            while i and guildsToUpdate:
                guild_auid = guildsToUpdate.pop()
                debug("try change gw event for guild %s", guild_auid)
                guild_data = self.getGuildData(guild_auid)
                if guild_data:
                    self.validateGuildWarEventIndex(guild_data, guild_auid, event_id)
                i -= 1

            if not guildsToUpdate:
                self.guildsToUpdateOnChangeGuildWarEvent = None

    def guildWarEventTick(self):
        now_second = toint(time.time())
        if now_second > self.check_guild_war_event + GUILD_WAR_EVENT_CHECK_PERIOD:
            self.tickHandleOnNewGuildWarEvent()
            self.check_guild_war_event = now_second

    def addPointsToGuildWarEventPool(self, guild_auid, points):
        event_id = self.getGuildWarEventId(guild_auid)
        debug("trying to add %s points to event %s", points, event_id)

        self.I.DATA.increment(CC.GUILDWAR_EVENTS_DATA, CC.GUILDWAR_EVENTS_DATA,
                              {'_id': {'$exists': True},
                               'event_index': event_id,
                               'enabled': 1,
                               "end_time": {"$gt": int(time.time())}},
                              {'points': int(points)}, params=None, upsert=False, callback=self.dummyMongoCallback)

        # self.I.STATS.addGWScoreChange(event_id, guild_auid, 0, points)

    # -------------------------------------------------------------------
    def mailTick(self):
        now_second = toint(time.time())
        if now_second > self.ts_mail_touch + CC.SEX_KEEPALIVE_CHECK_PERIOD:
            self.ts_mail_touch = now_second
            for guild_auid, GuildInfo in self.guildAuids.iteritems():
                mail = getattr(GuildInfo["guild"], "mail", None)
                if mail:
                    last_touch = toint(mail.sex_touch)
                    if last_touch + CC.SEX_KEEPALIVE_PERIOD < now_second:
                        mail.sex_touch = now_second
                        if mail.sex_sid:
                            info("exhange self.I.SEX.touch mail=%s" % mail)
                            callback = functools.partial(self.onTouch, mail=mail)
                            self.I.SEX.touch(mail.auid, mail.sex_sid, mail.sex_server, callback=callback)
                        else:
                            # для случаев, когда на старте залогиниться в exchange не смогли, потом периодически делаем retry login
                            callback = functools.partial(self.onSocialExchangeLogin, acc=mail)
                            info("exhange login retry for mail=%s" % mail)
                            self.I.SEX.login(mail.auid, CC.SEX_PW_PROJECT, callback)

    def onTouch(self, response, mail=None):
        if response.get('ok', 0) != 1 and mail is not None:
            mail.sex_sid = None
            mail.sex_touch = toint(time.time() - CC.SEX_KEEPALIVE_PERIOD + 1.0)

    def resetAllTalentsLimits(self, GuildData):
        if not GuildData.GuildAuid:
            warn("resetAllTalentsLimits: wrong GuildData")
            return

        for gmId in GuildData.Members.keys():
            member = GuildData.getGuildMemberByID(gmId)
            if member:
                member.AddedTalentsDailyCount = 0
                member.TakenTalentsDailyCount = 0

    def resetAllShopItems(self, GuildData):
        if not GuildData.GuildAuid:
            warn("resetAllShopItems: wrong GuildData")
            return

        for shopItemId in GuildData.GuildShopItems.keys():
            GuildData.GuildShopItems.remove(shopItemId)

        # Проверим на уровень гильдии
        level = self.I.SD.getGuildShopLevel(GuildData.getShopOwnerRating(), GuildData.GuildInfo.HasUltimateShop)
        for shopItemId in self.I.Config.getMainConfig().GUILD_SHOP_ITEMS:
            staticItem = self.I.SD.getGuildShopItemById(shopItemId)
            if not staticItem:
                continue

            if level < staticItem['levelToUnlock']:
                continue
            amount = self.I.SD.getAmountByExperienceLevel(staticItem, level)
            # Если у нас бесконечное число айтемов, то и нечего грузить ими гилд-дату
            if amount > 0:
                GuildData.GuildShopItems[str(shopItemId)] = amount

    def checkGuildShopOnNewSuzerain(self, GuildData, newSuzerainRating, willHaveUltimateShop):
        oldLevel = self.I.SD.getGuildShopLevel(GuildData.getShopOwnerRating(), GuildData.GuildInfo.HasUltimateShop)
        newLevel = self.I.SD.getGuildShopLevel(newSuzerainRating, willHaveUltimateShop)

        if oldLevel == newLevel:
            return

        # Сначала посмотрим, что со старым ассортиментом
        for shopItemId in GuildData.GuildShopItems.keys():
            info("updating item %r", shopItemId)
            staticItem = self.I.SD.getGuildShopItemById(toint(shopItemId))
            if not staticItem:
                info("staticItem not found!")
                GuildData.GuildShopItems.remove(shopItemId)
                continue

            oldAmount = self.I.SD.getAmountByExperienceLevel(staticItem, oldLevel)
            newAmount = self.I.SD.getAmountByExperienceLevel(staticItem, newLevel)

            # У нового сюзерена доступное кол-во побольше, надо накинуть разницу
            if oldAmount < newAmount:
                GuildData.GuildShopItems[shopItemId] += newAmount - oldAmount

            # У нового сюзерена доступное кол-во поменьше, надо вычесть разницу
            if oldAmount > newAmount:
                GuildData.GuildShopItems[shopItemId] = max(GuildData.GuildShopItems[shopItemId] - (oldAmount - newAmount), 0)

        # Теперь пройдёмся по всему ассортименту, вдруг что надо добавить или убрать
        for shopItemId in self.I.Config.getMainConfig().GUILD_SHOP_ITEMS:
            staticItem = self.I.SD.getGuildShopItemById(shopItemId)
            if not staticItem or str(shopItemId) in GuildData.GuildShopItems or newLevel < staticItem['levelToUnlock']:
                continue

            amount = self.I.SD.getAmountByExperienceLevel(staticItem, newLevel)
            # Если у нас бесконечное число айтемов, то и нечего грузить ими гилд-дату
            if amount > 0:
                GuildData.GuildShopItems[str(shopItemId)] = amount

    def validateGuildTalents(self, GuildData):
        if not GuildData.GuildAuid:
            warn("validateGuildTalents: wrong GuildData")
            return

        for gTalId in GuildData.TakenTalents.keys():
            talent = GuildData.getGuildTalentByID(gTalId)
            if self.isBadRef(talent.Holder, GuildData):
                talent.Holder = 0
                talent.Owner = 0
                GuildData.TakenTalents.remove(talent)

        for gTalId in GuildData.FreeTalents.keys():
            talent = GuildData.getGuildTalentByID(gTalId)
            if self.isBadRef(talent.Owner, GuildData):
                talent.Holder = 0
                talent.Owner = 0
                GuildData.FreeTalents.remove(talent)

    def validateGuildBuffs(self, GuildData):
        # Проверяем, не истекли ли купленные общественные баффы.
        for buffId in GuildData.ActiveBuffs.keys():
            if GuildData.ActiveBuffs[buffId] < int(time.time()):
                del GuildData.ActiveBuffs[buffId]

        for buffId in GuildData.ActiveHoldGuildBuffs.keys():
            if GuildData.ActiveHoldGuildBuffs[buffId] < int(time.time()):
                del GuildData.ActiveHoldGuildBuffs[buffId]

    def updateExVassalsAndLostSieges(self, GuildData):
        for guildAuid in GuildData.ExVassals.keys():
            if (GuildData.ExVassals[guildAuid] + self.I.Config.getMainConfig().SiegeSettings.TIMEOUT_FOR_EX_VASSAL_CAPTURE +
                  self.I.Config.getMainConfig().SiegeSettings.SIEGE_DURATION) < int(time.time()):
                del GuildData.ExVassals[guildAuid]
        for guildAuid in GuildData.LostSiegesGuilds.keys():
            if (GuildData.LostSiegesGuilds[guildAuid] + self.I.Config.getMainConfig().SiegeSettings.SIEGE_DURATION) < int(time.time()):
                del GuildData.LostSiegesGuilds[guildAuid]

    def isBadRef(self, ref, GuildData):
        if not ref.get() or ref == 0:
            return True
        member = GuildData.findMemberByAuid(ref.Person)
        if not member:
            return True

        return False

    # -------------------------------------------------------------------
    def recalcGuildRating(self, GuildData, numGuilds):
        # ежедневный пересчет чего-то в гильдии
        if not GuildData.GuildAuid:
            warn("recalcGuildRating: wrong GuildData")
            return

        numOfDays = getNumberOfDays()

        defRating = self.I.Config.getMainConfig().GUILD_DEFAULT_RATING

        # GuildData.RatingInfo.DailyRating += GuildData.RatingInfo.ClanWarBonus
        # GuildData.RatingInfo.Rating += GuildData.RatingInfo.DailyRating

        GuildData.GuildInfo.TotalGuildsNumber = numGuilds

        # обновляем дневный рейтиинги мемберов
        for gmId, mem in GuildData.GuildMemberKeeper.iteritems():
            for idx in xrange(numOfDays - 2, -1, -1):
                if len(mem.HeroRatings) > idx + 1 and len(mem.HeroRatings) > idx:
                    mem.HeroRatings[idx + 1].Hero = mem.HeroRatings[idx].Hero
                    mem.HeroRatings[idx + 1].HeroRating = mem.HeroRatings[idx].HeroRating
                else:
                    err("recalcGuildRating Bad mem.HeroRatings %r" % str(mem.generateJsonDict()))

            mem.DailyRating = defRating

            if mem.HeroRatings:
                mem.HeroRatings[0].Hero = 0
                mem.HeroRatings[0].HeroRating = defRating
            else:
                err("recalcGuildRating Bad mem.HeroRatings[0] %r" % str(mem.generateJsonDict()))

            # убрал отдельный вызов resetAllTalentsLimits, чтобы не гонять повторно цикл по мемберам
            mem.AddedTalentsDailyCount = 0
            mem.TakenTalentsDailyCount = 0

        # сбрасываем дневной рейтиинг гильдии, но не трогаем ивентовый
        GuildData.RatingInfo.DailyRating = defRating
        GuildData.RatingInfo.ClanWarBonus = 0.0

        GuildData.checkUltimateShop(self.I.SD)

        # PF-106691
        # # Если у нас NPC сюзерен
        # if GuildData.GuildSuzerain.ShortInfo.GuildAuid == CC.NPC_SUZERAIN_AUID:
        #     GuildData.GuildSuzerain.DonationToday = round(self.I.SD.getGuildVassalsTributeCoef() * self.I.SD.data["ClanWarsData"]["npcVillage"]["everyDayProfit"])
        # elif GuildData.GuildSuzerain.ShortInfo.GuildAuid != 0:
        #     self.sendTributeToSuzerain(GuildData.GuildAuid, GuildData.GuildSuzerain.ShortInfo.GuildAuid,
        #                                GuildData.GuildSuzerain.DonationToday, self.onSendTribute)
        #     GuildData.GuildSuzerain.DonationYesterday = GuildData.GuildSuzerain.DonationToday
        #     GuildData.GuildSuzerain.DonationToday = 0 # обнуляем сегодняшнюю дань
        # else:
        #     GuildData.GuildSuzerain.DonationYesterday = 0
        #     GuildData.GuildSuzerain.DonationToday = 0 # Ну и на всякий пожарный, если у нас недавно свергли npc
        #
        #
        # # Соберем дань с NPC вассалов
        # for _id, vassal in GuildData.GuildVassals.iteritems():
        #     if vassal and vassal.ShortInfo.GuildAuid == CC.NPC_VASSAL_AUID:
        #         GuildData.GuildInfo.CWPoints_Clan += round(self.I.SD.getGuildVassalsTributeCoef() * self.I.SD.data["ClanWarsData"]["npcVillage"]["everyDayProfit"])
        #         vassal.DonationToday = round(self.I.SD.getGuildVassalsTributeCoef() * self.I.SD.data["ClanWarsData"]["npcVillage"]["everyDayProfit"])
        #         vassal.DonationYesterday = vassal.DonationToday

        self.I.DATA.update('guilds', 'guilds', {"key": GuildData.GuildAuid},
                           {"data.guildAllDaysRating": GuildData.RatingInfo.Rating}, callback=self.dummyCallback)

        return GuildData.RatingInfo.Rating

    # PF-106691
    # def sendTributeToSuzerain(self, fAuid, tAuid, tribute, callback):
    #     mess = dict(method="send_tribute", message={"tribute": tribute})
    #     self.I.SEX.sendToGuildService(fAuid, tAuid, mess, callback)
    #
    # def onSendTribute(self, response):
    #     info("GuildService: onSendTribute response: %r" % response)

    # PF-106691
    # def updateSuzerainInvites(self, guildAuid, requests):
    #     if not requests:
    #         debug("updateSuzerainInvitesLimits: requests")
    #         return
    #     # обнуляем дневной лимит инвайтов
    #     if not (requests and requests["SuzerainInvites"]):
    #         debug("updateSuzerainInvitesLimits: wrong GuildData.Requests")
    #         return
    #
    #     # если время автоудаления просрочено, то удаляем просроченые прошения
    #     #self.I.DATA.group_unset("guilds", "guilds",{"key": getMongoKeyAuid(gData.GuildAuid)},
    #     #                     {"requests.SuzerainInvites.$.timeToAutoDecline": {"$lte": int(time.time())}}, self.onDummyGuildCallback())
    #
    #     for k, v in requests["SuzerainInvites"].items():
    #         if v and (v.get("timeToAutoDecline") <= int(time.time())):
    #             del requests["SuzerainInvites"][k]
    #             self.removeRequestsData(guildAuid, {"requests.SuzerainInvites.%s" % k : str(k)})
    #
    #
    # def updateRatingForSiegeData(self, fakeAcc, GuildData):
    #     if fakeAcc.SiegeData:
    #         for siegeId, siege in fakeAcc.SiegeData.ActiveSieges.iteritems():
    #             if siege.Target.ShortInfo.GuildAuid == GuildData.GuildAuid:
    #                 siege.Target.ShortInfo.Rating = GuildData.RatingInfo.Rating
    #                 siege.Target.ShortInfo.Place = GuildData.GuildInfo.Place
    #                 siege.Target.ShortInfo.RatingPositionChange = GuildData.GuildInfo.PlaceChange
    #
    # def updateRecommendedVassalsList(self, acc, gData, callback):
    #     if not gData.GuildAuid:
    #         warn("updateRecommendedVassalsList: wrong GuildData")
    #         return
    #
    #     minRating = gData.getRatingForRecommendedVassals()
    #     vauids = [v.ShortInfo.GuildAuid for _id, v in gData.GuildVassals.iteritems()] + [gData.GuildAuid]
    #
    #     _callback = functools.partial(self.onRecommendedVassalFromSQL, fakeAcc=acc, guildData=gData, callback=callback)
    #
    #     self.I.EXPORT.exportRecommendedVassalsData(vauids, minRating,
    #                                                round(gData.RatingInfo.Rating - 1), # пока 1 до тех пор пока не внесем параметр в Social
    #                                                 self.I.Config.getMainConfig().GUILD_MAX_RECOMMENDED_VASSAL_SIZE,
    #                                                _callback )
    #     return
    #
    # def removeGuildFromRecommendedVassal(self, acc, potentialVassalAuid):
    #     for k in acc.GuildData.RecommendedForMapVassals.keys():
    #         vass = acc.GuildData.getRecommendedVassalByID(k)
    #         if vass and vass.ShortInfo and vass.ShortInfo.GuildAuid == potentialVassalAuid:
    #             _id = vass.ShortInfo.getID()
    #             acc.GuildData.RecommendedForMapVassals.remove(vass)
    #             acc.GuildData.deleteByID(_id)
    #             return
    #
    # def onRecommendedVassalFromSQL(self, reply, fakeAcc, guildData, callback=None):
    #     info("onRecommendedVassalFromSQL reply: %r " % reply)
    #     r = reply["r"]
    #     for k in guildData.RecommendedForMapVassals.keys():
    #         vass = guildData.getRecommendedVassalByID(k)
    #         if vass and vass.ShortInfo:
    #             _id = vass.ShortInfo.getID()
    #             guildData.RecommendedForMapVassals.remove(vass)
    #             guildData.deleteByID(_id)
    #
    #     for k in guildData.GuildsRemovedFromSearch.keys():
    #         del guildData.GuildsRemovedFromSearch[k]
    #
    #     if r and len(r):
    #         for guildInfo in r:
    #             rv, _ = guildData.newRecommendedVassal()
    #             rv.ShortInfo.GuildAuid = guildInfo.guild_id
    #             rv.ShortInfo.GuildShortName = guildInfo.guild_short_name
    #             rv.ShortInfo.GuildFullName = guildInfo.guild_name
    #             rv.ShortInfo.Level = guildInfo.guild_level
    #             rv.ShortInfo.Rating = guildInfo.rating
    #             rv.ShortInfo.Place = guildInfo.position
    #             rv.ShortInfo.RatingPositionChange = GuildWarsData.GetRatingPositionChange(guildInfo.position_change)
    #             rv.ShortInfo.ShopLevel = guildInfo.shop_level
    #             rv.ShortInfo.MembersCount = guildInfo.num_members
    #             rv.ShortInfo.IconChangesCount = guildInfo.icon_revision
    #             rv.IsInSiege = (guildInfo.siege_end_time != 0)
    #             rv.HasSuzerain = (guildInfo.suzerain != 0) # -1 NPC 0-сюзерена нет
    #             rv.ApplicationSent = False
    #
    #             if (fakeAcc.Requests and fakeAcc.Requests["SuzerainInvites"]):
    #                 warn("onRecommendedVassalFromSQL: wrong GuildData.Requests")
    #                 rv.ApplicationSent = guildInfo.guild_id in fakeAcc.Requests["SuzerainInvites"]
    #
    #             guildData.RecommendedForMapVassals.add(rv)
    #     if callback:
    #         callback()

    def updateTechs(self, ):
        mark = int(time.time()) - getNumberOfDays() * 24 * 60 * 60
        for revision, tech in self.techs.items():
            # запись протухла, не учитываем её
            if tech["startTime"] + tech["duration"] < mark:
                del self.techs[revision]

    def getTechsForThisWeek(self, ):
        self.updateTechs()
        techsTime = 0
        for revision, tech in self.techs.iteritems():
            if tech["startTime"] < int(time.time()) - getNumberOfDays() * 24 * 60 * 60:
                # Эти тех-работы попали в учёт только частично.
                techsTime += tech["startTime"] + tech["duration"] - (
                        int(time.time()) - getNumberOfDays() * 24 * 60 * 60)
            else:
                techsTime += tech["duration"]
        return techsTime

    def calcGuildDayRating(self, GuildData):
        defRating = self.I.Config.getMainConfig().GUILD_DEFAULT_RATING
        dayRatingsMembers = []
        for gmId in GuildData.Members.keys():
            mem = GuildData.getGuildMemberByID(gmId)
            dayRatingsMembers.append(mem.DailyRating)

        bestPlayersCount = self.I.Config.getMainConfig().GUILD_BEST_PLAYERS
        dayRatingsMembersCount = len(dayRatingsMembers)

        if dayRatingsMembersCount < bestPlayersCount:
            for idx in xrange(dayRatingsMembersCount, bestPlayersCount):
                dayRatingsMembers.append(defRating)
        elif dayRatingsMembersCount > bestPlayersCount:
            dayRatingsMembers.sort(reverse=True)
            dayRatingsMembers = dayRatingsMembers[:bestPlayersCount]

        guildDayRating = sum(dayRatingsMembers) / float(bestPlayersCount)

        # Не сохраняем бонус от гильдбоя в текущий дневной рейтинг, храним отдельно
        # guildDayRating += GuildData.RatingInfo.ClanWarBonus

        return guildDayRating

    def renameGuild(self, acc, shortname, fullname):
        self.resetPendingChanges(acc)
        acc.GuildData.write(acc.pending)

        acc.GuildData.GuildInfo.FullName = fullname
        acc.GuildData.GuildInfo.ShortName = shortname

        args = {"FullName": acc.GuildData.GuildInfo.FullName, "ShortName": acc.GuildData.GuildInfo.ShortName,
                "GuildAuid": acc.GuildData.GuildAuid}
        self.I.DATA.update("guilds", "guilds", {"GuildAuid": acc.GuildData.GuildAuid}, args, callback=None, params=None)

        for gmId in acc.GuildData.Members.keys():
            mem = acc.GuildData.getGuildMemberByID(gmId)
            self.updateGuildShortName(mem.Person, acc.GuildData.GuildInfo.ShortName)

        changes = self.pickPendingChanges(acc)
        self.sendBroadCast(acc, changes, [], '')
        self.saveGuildData(acc, None)
        # PF-106691
        # self.notifyVassalsAndSuzerain(acc.GuildData)
        return changes["guild_data"]

    # PF-106691
    # def notifyVassalsAndSuzerain(self, guildData):
    #     if guildData.GuildSuzerain.ShortInfo.GuildAuid and guildData.GuildSuzerain.ShortInfo.GuildAuid != CC.NPC_SUZERAIN_AUID:
    #         args = dict(method="update_vassal_info", message={"targetAuid": guildData.GuildAuid})
    #         self.I.SEX.sendToGuildService(guildData.GuildAuid, guildData.GuildSuzerain.ShortInfo.GuildAuid, args, self.onDummyGuildCallback)
    #     for vassalId, vassal in guildData.GuildVassals.iteritems():
    #         if vassal.ShortInfo.GuildAuid != CC.NPC_VASSAL_AUID:
    #             args = dict(method="new_suzerain_notify", message={"dontUpdateTime" : True})
    #             self.I.SEX.sendToGuildService(guildData.GuildAuid, vassal.ShortInfo.GuildAuid, args, self.onDummyGuildCallback)

    # def addRecommendedVassal(self, fakeAcc, vassalAuid, rv, vass):
    #     gi = pathFind(vass, "GuildData/GuildInfo")
    #     rv.ShortInfo, _id = fakeAcc.GuildData.newGuildShortInfo()
    #     self.fillShortInfo(rv.ShortInfo, pathFind(vass, "GuildData/GuildAuid"), gi.get("ShortName", ""), gi.get("FullName", ""),
    #                        self.I.SD.getGuildLevel(pathFind(vass, "GuildData/GuildLevelInfo/GuildLevelInfo/Experience")),
    #                        pathFind(vass, "GuildData/RatingInfo/RatingInfo/Rating"), gi.get("Place", 0),
    #                        GuildWarsData.GetRatingPositionChange(gi.get("PlaceChange", 0)), 0,
    #                        len(pathFind(vass, "GuildData/Members/Set")), gi.get("IconChangesCount", 0))
    #     suzerainId = pathFind(vass, "GuildData/GuildSuzerain")
    #     shortInfoId = pathFind(vass, "GuildData/GuildMapEntityKeeper/Keeper/%s/GuildMapEntity/ShortInfo" % suzerainId, force_int_keys=False)
    #     suzerain = pathFind(vass, "GuildData/GuildShortInfoKeeper/Keeper/%s/GuildShortInfo" % shortInfoId, force_int_keys=False)
    #     rv.HasSuzerain = suzerain is not None and (suzerain.get("GuildAuid", -1) != 0) # -1 NPC 0-сюзерена нет
    #     shopRating = rv.ShortInfo.Rating
    #     if rv.HasSuzerain:
    #         shopRating = suzerain.get("Rating", 0)
    #     rv.ShortInfo.ShopLevel = self.I.SD.getGuildShopLevel(shopRating, gi.get("HasUltimateShop", False))
    #     rv.IsInSiege = pathFind(vass, "GuildData/SiegeForMyGuildEndTime") > int(time.time())
    #     rv.ApplicationSent = False
    #
    #     if (fakeAcc.Requests and fakeAcc.Requests["SuzerainInvites"]):
    #         warn("onAddRecomendedVassal: wrong GuildData.Requests")
    #         rv.ApplicationSent = vassalAuid in fakeAcc.Requests["SuzerainInvites"]

    def removeGuildMember(self, guildData, siegeData, member_auid):
        member = guildData.findMemberByAuid(member_auid)
        if not member:
            warn("removeGuildMember failed: cannot find member %d in guild %d" % (member_auid, guildData.GuildAuid))
            return False

        # пшел вон
        memberID = member.getID()
        for heroInfo_id, heroInfo in member.HeroRatings.items():
            member.HeroRatings.remove(heroInfo_id)
        guildData.Members.remove(member)
        guildAuid = guildData.GuildAuid

        needDeleteGuild = False
        if guildData.Owner.Person == member_auid:
            # не командир ты нам больше
            guildData.Owner = None
            newOwner = None
            maxRating = 0.0
            # вакансия открыта, ищем нового повелителя
            for gmId in guildData.Members.keys():
                mem = guildData.getGuildMemberByID(gmId)

                avrRating = mem.DailyRating

                if not newOwner or (mem.IsOfficer and not newOwner.IsOfficer) or (
                        mem.IsOfficer == newOwner.IsOfficer and maxRating < avrRating):
                    newOwner = mem
                    maxRating = avrRating

            if newOwner:
                # да здравствует новый король
                newOwner.IsOfficer = True
                guildData.Owner = newOwner
            else:
                # если, уходя, вы оказались последним, гасите свет
                args = {"FullName": guildData.GuildInfo.FullName, "ShortName": guildData.GuildInfo.ShortName,
                        "GuildAuid": guildAuid}
                self.I.DATA.remove("guilds", "guilds", args)
                self.processDestroyGuild(guildData, siegeData)

                guildData = GuildData()
                guildData.init(None)
                needDeleteGuild = True

        guildData.GuildMemberKeeper.remove(memberID)

        # Возвращаем таланты, которые мы взяли
        for gTalId in guildData.TakenTalents.keys():
            talent = guildData.getGuildTalentByID(gTalId)
            if talent.Holder == member:
                self.logTalentEvent(guildData, TalentEventType.LeaveReturn, member_auid, talent.Owner.Person,
                                    talent.PersistentId)
                talent.Holder = 0
                guildData.FreeTalents.add(talent)
                guildData.TakenTalents.remove(talent)
        # Удаляем их из своей ModelData
        self.createMailDeleteAllGuildTalents(member_auid, guildData)

        # Забираем наши таланты, которые уже взяли
        for gTalId in guildData.TakenTalents.keys():
            talent = guildData.getGuildTalentByID(gTalId)
            if talent.Owner == member:
                # Удаляем из ModelData у того, кто взял наш талант
                self.createMailDeleteGuildTalent(talent.Holder.Person, gTalId, guildData)
                # Добавляем в ModelData наш талант
                self.createMailAddGuildTalent(talent.Owner.Person, talent.PersistentId, talent.HeroClassId,
                                              talent.Points, guildData)
                self.I.STATS.addTalentChange(talent.Owner.Person,
                                             TalentInfo(talent.PersistentId, gTalId, talent.HeroClassId),
                                             TalentChangeOperation.ReturnToUserOnLeave)
                # Удялем из гильдии
                talent.Holder = 0
                talent.Owner = 0
                guildData.TakenTalents.remove(talent)

        # Забираем наши таланты, которые еще не взяли и они лежат в гильдбанке
        for gTalId in guildData.FreeTalents.keys():
            talent = guildData.getGuildTalentByID(gTalId)
            if talent.Owner == member:
                self.logTalentEvent(guildData, TalentEventType.LeaveTake, member_auid, 0, talent.PersistentId)
                # Добавляем в ModelData наш талант
                self.createMailAddGuildTalent(talent.Owner.Person, talent.PersistentId, talent.HeroClassId,
                                              talent.Points, guildData)
                self.I.STATS.addTalentChange(talent.Owner.Person,
                                             TalentInfo(talent.PersistentId, gTalId, talent.HeroClassId),
                                             TalentChangeOperation.ReturnToUserOnLeave)
                # Удялем из гильдии
                talent.Owner = 0
                guildData.FreeTalents.remove(talent)

        # Забираем гильдийские бафы, раз уж такой казус
        self.createMailDeleteAllGuildBufs(member_auid, guildData)

        if needDeleteGuild:
            self.I.DATA.remove("guilds", "guilds", {"key": getMongoKeyAuid(guildAuid)}, self.onDummyGuildCallback)

        return needDeleteGuild

    def createMailDestroyGuild(self, auid, guildData, callback=None):
        ourInfo = [{"type": "destr_guild"}]
        mail = getattr(guildData, "mail", None)
        if mail:
            self.I.SEX.sendMail("pw", auid, ourInfo, from_auid=mail.auid, from_sid=mail.sex_sid,
                                from_server=mail.sex_server, callback=callback)

    def createMailDeleteAllGuildTalents(self, auid, guildData, callback=None):
        ourInfo = [{"type": "del_all_gltals"}]
        mail = getattr(guildData, "mail", None)
        if mail:
            self.I.SEX.sendMail("pw", auid, ourInfo, from_auid=mail.auid, from_sid=mail.sex_sid,
                                from_server=mail.sex_server, callback=callback)

    def createMailAddGuildTalent(self, auid, persistentId, heroClassId, points, guildData, callback=None):
        ourInfo = [{"type": "add_gltal", "persistentId": persistentId, "heroClassId": heroClassId, "points": points}]
        mail = getattr(guildData, "mail", None)
        if mail:
            self.I.SEX.sendMail("pw", auid, ourInfo, from_auid=mail.auid, from_sid=mail.sex_sid,
                                from_server=mail.sex_server, callback=callback)

    def createMailDeleteGuildTalent(self, auid, guildTalId, guildData, callback=None):
        ourInfo = [{"type": "del_gltal", "guildTalId": guildTalId}]
        mail = getattr(guildData, "mail", None)
        if mail:
            self.I.SEX.sendMail("pw", auid, ourInfo, from_auid=mail.auid, from_sid=mail.sex_sid,
                                from_server=mail.sex_server, callback=callback)

    def createMailAddGuildBuf(self, auid, persistentId, expireTime, guildData, callback=None):
        ourInfo = [{"type": "add_glbuf", "persistentId": persistentId, "expireTime": expireTime}]
        mail = getattr(guildData, "mail", None)
        if mail:
            self.I.SEX.sendMail("pw", auid, ourInfo, from_auid=mail.auid, from_sid=mail.sex_sid,
                                from_server=mail.sex_server, callback=callback)

    def createMailDeleteAllGuildBufs(self, auid, guildData, callback=None):
        ourInfo = [{"type": "del_all_glbufs"}]
        mail = getattr(guildData, "mail", None)
        if mail:
            self.I.SEX.sendMail("pw", auid, ourInfo, from_auid=mail.auid, from_sid=mail.sex_sid,
                                from_server=mail.sex_server, callback=callback)

    def createMailRemoveSuzeren(self, guildAuid, guildData, callback=None):
        ourInfo = [{"type": "s_suzerain_lost"}]
        mail = getattr(guildData, "mail", None)
        if mail:
            self.I.SEX.sendMail("pw", guildAuid, ourInfo, from_auid=mail.auid, from_sid=mail.sex_sid,
                                from_server=mail.sex_server, callback=callback)

    def createMailsDestroyApplication(self, guildAuid, auids, response):
        if auids:
            msg = [{"type": "drop_guildapp", "guildAuid": guildAuid}]
            cb = functools.partial(self.createMailsDestroyApplication, guildAuid, auids[1:]) if len(auids) > 1 else None
            debug("createMailsDestroyApplication to %s: %s", auids[0], msg)
            self.I.SEX.sendMail("pw", auids[0], msg, callback=cb)
        if not (response and response["ok"]):
            err("Falied to send an applicant player notifiction about the guild %s destruction. Response: %r",
                guildAuid, response)

    def createMailRejectedApplication(self, guildAuid, guildData, auid, callback=None):
        ourInfo = [{"type": "recruit_rejected", "guildAuid": guildAuid}]
        info("createMailRejectedApplication to %s", auid)
        mail = getattr(guildData, "mail", None)
        if mail:
            self.I.SEX.sendMail("pw", auid, ourInfo, from_auid=mail.auid, from_sid=mail.sex_sid,
                                from_server=mail.sex_server, callback=callback)

    def logTalentEvent(self, guildData, type, auid1, auid2, persistentId):
        logEvent = guildData.newTalentEvent()[0]
        logEvent.Type = type
        logEvent.Auid1 = auid1
        logEvent.Auid2 = auid2
        logEvent.PersistentId = persistentId
        logEvent.timestamp = int(time.time())

        guildData.TalentLog.add(logEvent)

        logTimeToDel = self.I.Config.getMainConfig().GuildBankSettings.GUILD_BANK_HISTORY_TIME

        for tlId in guildData.TalentLog.keys():
            talentLog = guildData.getTalentEventByID(tlId)
            if talentLog.timestamp + logTimeToDel < int(time.time()):
                guildData.TalentLog.remove(talentLog)

    def setMessageOfTheDay(self, acc, message):
        self.resetPendingChanges(acc)
        acc.GuildData.write(acc.pending)

        acc.GuildData.GuildInfo.MessageOfTheDay = urllib.unquote(message)

        changes = self.pickPendingChanges(acc)
        self.sendBroadCast(acc, changes, [], '')
        self.saveGuildData(acc, None)
        return changes

    def setExperience(self, acc, exp):
        self.resetPendingChanges(acc)
        acc.GuildData.write(acc.pending)

        acc.GuildData.GuildLevelInfo.Experience = exp

        changes = self.pickPendingChanges(acc)
        self.sendBroadCast(acc, changes, [], '')
        self.saveGuildData(acc, None)
        return changes

    def setLeader(self, acc, leader):
        self.resetPendingChanges(acc)
        acc.GuildData.write(acc.pending)

        new_owner = acc.GuildData.findMemberByAuid(leader)
        if new_owner:
            old_owner = acc.GuildData.findMemberByAuid(acc.GuildData.Owner.Person)
            if old_owner:
                old_owner.IsOfficer = False

            new_owner.IsOfficer = True
            acc.GuildData.Owner = new_owner

        changes = self.pickPendingChanges(acc)
        self.sendBroadCast(acc, changes, [], '')
        self.saveGuildData(acc, None)
        return changes

    def setGuildCWPoints(self, acc, cwPoints):
        self.resetPendingChanges(acc)
        acc.GuildData.write(acc.pending)

        acc.GuildData.GuildInfo.CWPoints_Clan = cwPoints

        changes = self.pickPendingChanges(acc)
        self.sendBroadCast(acc, changes, [], '')
        self.saveGuildData(acc, None)
        return changes

    def updateGuildDataOnGWEventChanged(self, acc, mirror=True):
        self.resetPendingChanges(acc)
        acc.GuildData.write(acc.pending)

        defRating = self.I.Config.getMainConfig().GUILD_DEFAULT_RATING
        acc.GuildData.GuildInfo.CWPoints_Clan = 0
        acc.GuildData.GuildInfo.PrevPlace = acc.GuildData.GuildInfo.Place

        acc.GuildData.GuildInfo.CurrentEventId = self.getGuildWarEventId(acc.GuildData.GuildAuid)
        acc.GuildData.RatingInfo.PrevRating = acc.GuildData.RatingInfo.Rating
        acc.GuildData.RatingInfo.ClanWarBonus = 0.0

        sorted_members = [(gmId, mem.EventRating) for gmId, mem in acc.GuildData.GuildMemberKeeper.iteritems()]
        sorted_members.sort(key=lambda p: p[1], reverse=True)
        members_places = dict()
        for i, p in enumerate(sorted_members):
            members_places[p[0]] = i + 1

        for gmId, mem in acc.GuildData.GuildMemberKeeper.iteritems():
            mem.DailyRating = 0
            if mem.EventRating > 0:
                mem.PrevEventPlace = members_places[gmId]
            else:
                mem.PrevEventPlace = 0
            mem.EventRating = 0

        self.setGuildRating(acc, 0)

        self.resetAllShopItems(acc.GuildData)

        changes = self.pickPendingChanges(acc)
        self.sendBroadCast(acc, changes, [], '')
        self.saveGuildData(acc, None, mirror=mirror)
        return changes

    # PF-106691
    def createVassal(self, GuildData, vassalGuildDict):
        vassal, _id = GuildData.newGuildMapEntity()
        vassal.ShortInfo, _id = GuildData.newGuildShortInfo()
        self.fillVassal(vassal, vassalGuildDict, self.I.SD.getGuildShopLevel(GuildData.RatingInfo.Rating, False))
        vassal.JoinTime = int(time.time())
        vassal.DonationYesterday = 0
        vassal.DonationToday = 0  # вассал нам ничего не присылал, типа новая тушка
        GuildData.GuildVassals.add(vassal)

    def fillVassal(self, vassal, vGuildDict, shopLevel):
        gi = pathFind(vGuildDict, "GuildData/GuildInfo/GuildInfo")
        self.fillShortInfo(vassal.ShortInfo, pathFind(vGuildDict, "GuildData/GuildAuid"),
                           gi.get("ShortName", ""), gi.get("FullName", ""),
                           self.I.SD.getGuildLevel(pathFind(vGuildDict, "GuildData/GuildLevelInfo/GuildLevelInfo/Experience")),
                           pathFind(vGuildDict, "GuildData/RatingInfo/RatingInfo/Rating"), gi.get("Place", 0),
                           GuildWarsData.GetRatingPositionChange(gi.get("PlaceChange", 0)), shopLevel,
                           len(pathFind(vGuildDict, "GuildData/Members/Set")),
                           gi.get("IconChangesCount", 0))

    def updateSuzerainFromDict(self, guildData, gDict):
        gi = pathFind(gDict, "GuildData/GuildInfo/GuildInfo")
        self.fillSuzerain(guildData,
                          pathFind(gDict, "GuildData/GuildAuid"),
                          gi.get("ShortName", ""),
                          gi.get("FullName", ""),
                          self.I.SD.getGuildLevel(gi.get("GuildData/LevelInfo/Experience", 0)),
                          pathFind(gDict, "GuildData/RatingInfo/RatingInfo/Rating"),
                          gi.get("Place", 0),
                          gi.get("PlaceChange", 0),
                          self.I.SD.getGuildShopLevel(pathFind(gDict, "GuildData/RatingInfo/RatingInfo/Rating"), False),
                          len(pathFind(gDict, "GuildData/Members/Set")),
                          gi.get("IconChangesCount", 0))

    def fillSuzerain(self, GuildData, suzerainAuid, shortName, fullName, level, rating, place, placeChange, shopLevel,
                     membersCount, iconChanges):
        debug("fillSuzerain: %s", (suzerainAuid, rating, shortName, fullName, place, placeChange, iconChanges))
        # Почистим  старую структуру

        si = GuildData.GuildSuzerain.ShortInfo
        debug("fillSuzerain ShortInfo: %r", si)
        debug("fillSuzerain ShortInfo.object: %r", si.object)
        debug("fillSuzerain ShortInfo.id: %r", si.id)
        # GuildData.GuildSuzerain.ShortInfo = 0
        # GuildData.GuildSuzerain = 0
        if not (GuildData.GuildSuzerain and GuildData.GuildSuzerain.get()):
            GuildData.GuildSuzerain, _id = GuildData.newGuildMapEntity()

        suzerain = GuildData.GuildSuzerain
        if not (suzerain.ShortInfo and suzerain.ShortInfo.get()):
            suzerain.ShortInfo, _id = GuildData.newGuildShortInfo()

        # suzerain.ShortInfo, _id = GuildData.newGuildShortInfo()
        self.fillShortInfo(suzerain.ShortInfo, suzerainAuid, shortName, fullName, level, rating, place, placeChange,
                           shopLevel, membersCount, iconChanges)
        # Проверим, не надо ли дать нашей гильдии доступ к убермагазину
        GuildData.checkUltimateShop(self.I.SD)

    def fillShortInfo(self, shortInfo, GuildAuid, shortName, fullName, level, rating, place, placeChange, shopLevel,
                      membersCount, iconChanges):
        shortInfo.GuildAuid = GuildAuid
        shortInfo.GuildShortName = utf8convert(shortName)
        shortInfo.GuildFullName = utf8convert(fullName)
        shortInfo.Level = level
        shortInfo.Rating = rating
        shortInfo.Place = place
        shortInfo.RatingPositionChange = GuildWarsData.GetRatingPositionChange(placeChange)
        shortInfo.ShopLevel = shopLevel
        shortInfo.MembersCount = membersCount
        shortInfo.IconChangesCount = iconChanges

    def setGuildRating(self, acc, rating):
        acc.GuildData.RatingInfo.DailyRating = rating
        acc.GuildData.RatingInfo.Rating = rating
        # Проверим, не надо ли дать нашей гильдии доступ к убермагазину
        acc.GuildData.checkUltimateShop(self.I.SD)

    def processDestroyGuild(self, GuildData, SiegeData):
        if GuildData.GuildSuzerain.ShortInfo.GuildAuid != 0 and GuildData.GuildSuzerain.ShortInfo.GuildAuid != CC.NPC_SUZERAIN_AUID:

            args = dict(method="remove_vassal", message={"auid": CC.GUILD_NEUTRAL_AUID,
                                                         "targetAuid": GuildData.GuildAuid, "notifyVassal": False})
            self.I.SEX.sendToGuildService(GuildData.GuildAuid, GuildData.GuildSuzerain.ShortInfo.GuildAuid, args, self.onDummyGuildCallback)
        for vassalId, vassal in GuildData.GuildVassals.iteritems():
            if vassal.ShortInfo.GuildAuid != CC.NPC_VASSAL_AUID:
                args = dict(method="new_suzerain_notify", message={})
                self.I.SEX.sendToGuildService(0, vassal.ShortInfo.GuildAuid, args, self.onDummyGuildCallback)
        self.I.EXPORT.removeGuildInfoOnGuildDelete(GuildData.GuildAuid, self.onDummyGuildCallback)
        for siegeId, siege in SiegeData.ActiveSieges.iteritems():
            # Если боролись за нашу гильдию, то надо развалить осаду и вернуть деньги
            if siege.Target.ShortInfo.GuildAuid == GuildData.GuildAuid:
                self.I.SIEGE.destroySiege(GuildData.GuildAuid, safe=True, callback=self.onDummyGuildCallback)
            else:
                self.I.SIEGE.leaveSiege(GuildData.GuildAuid, siege.Target.ShortInfo.GuildAuid,
                                        self.onDummyGuildCallback)

        self.removeGuildRecruitApplications(GuildData.GuildAuid)

    def removeGuildRecruitApplications(self, guildAuid):
        data_key = {"guild_auid": guildAuid}
        info("removeGuildRecruitApplications: %s", data_key)
        self.I.DATA.remove(CC.PLAYER_GUILD_REQUESTS_DATA, CC.PLAYER_GUILD_REQUESTS_DATA, data_key)
        self.createMailsDestroyApplication(guildAuid, [
            recruitInfo["pers_auid"] for recruitInfo in self.getRecruitData(guildAuid)
        ], response={"ok": 1}) # it's chain-callback, so let's emulate an ok-response
        self.registerRecruitsData(guildAuid, list())
        #TODO когда будет хороший механизм определения, кто онлайн и на какой WS, переделать:
        # Цикл по recruitInfo:
        # 1. найти, есть ли юзер где-то на ws
        # 2. если есть - оповестить


    def checkGMLock(self, targetAuid, callback):
        args = ClassDict(targetAuid=[targetAuid])
        action = CheckGMLockAction(args, callback, I=self.I)
        action.onStart()

    def findReq(self, recruitRequests, recruit_auid):
        debug("GuildService: findReq (acc.RecruitRequests=%r)", recruitRequests)
        if recruitRequests:
            for req in recruitRequests:
                if req.get('pers_auid') == recruit_auid:
                    return req

    def onZADD(self, response):
        info("GuildService: onZADD=%r" % response)

    def onGuildChatRegister(self, response):
        if response and response.get('ok'):
            info("onGuildChatRegister response: %s" % pretty(response))

    def onGuildChatUnregister(self, response):
        if response and response.get('ok'):
            info("onGuildChatUnregister response: %s" % pretty(response))

    def onDummyAggCallback(self, result_dict):
        info("onDummyAggCallback: result %s" % result_dict)

    def onDummyGuildCallback(self, response):
        info("onDummyGuildCallback: result %s" % response)


def main():
    ITornadoServer.main(GuildService)


if __name__ == "__main__":
    # tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = 8717
    else:
        options["port"].set(8717)
    main()
