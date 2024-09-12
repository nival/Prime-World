#!/usr/bin/env python
# -*- coding: utf-8 -*-
__author__ = 'danil.lavrentyuk'
"""<Сервис осад> - обслуживает процессы осад в клановых войнах,
т.е. захват и перезахват вассалов и освобждение вассала отсюзерена.
Осада инициируется кланом с уплатой некоторого кол-ва очков клана.
По сути своей осада -- это 'меряние понтами', где мерилом выступает количество
очков, заработанных членами клана в сражениях за время осады.

Для хранения информации используется отдельная коллекция (sieges) в MongoDB.

На старте каждый сервис осад загружает все "свои" осады в память.
"Свои" определяются по GuildAuid цели осады и номеру сервиса среди подобных ему
(сообщается координатором в запросе action=youare). Все изменения осад сразу же
сохраняются в БД, но до рестарта сервиса они не потребуются (всё в памяти).
Потребности памяти на одну осаду невелики, общее количество одновременных осад
на всех сервисах не превосходит общее количество кланов помноженное на максимальное
количество пересекающихся по времени инициированных кланом осад (сейчас это 1, т.е.
пока не закончишь/покинешь инициированную осаду, новую начинать нельзя).

Структура осады:
"_id"  -- id осады, автогенерируется каждым сервисом
"target" -- GuildAuid цели
"target_rating" -- рейтнг цели на момент старта соады
'status':  --  состояние осады, возможные значения: 'active', 'gap', 'locked', 'done'
'start_tm' -- момент начала (unixtime)
'end_time' -- планируемый момент окончания (unixtime)
'suzerain' -- GuildAuid сюзерена цели
'suzerain_raiting' -- рейтинг сюзерена цели на момент старта осады
'winner' -- GuildAuid победителя (добавляется по окончании осады)
'rev' -- номер последних техработ, заставших осаду, используется для приостановки времени на техработы
'participants' -- список всех участников, структура каждого:
    'id' -- GuildAuid участника осады
    'score' -- текущие набранные очки осады
    'rating' -- рейтинг участника на момент старта осады
    'start' -- момент присоединения к осаде (для инициатора и защищаюшегося равен моменту начала осады)
    'price' -- сколько заплатил за присоединение к осаде
    'leave' -- время сбегания из осады (добавляется сбежавшему, по окончании добавляется всем, кто не победитель)
    'finished' -- признак того, что участвовал до конца, не сбежал (для проверки совместно с  'leave')

Некоторые сочетания значений:
1. Присутствие target'а в числе участников означает, то либо это свободый клан, который захватывают
(в этом случае у него, нет сюзерена) либо, напротив, клан освобождается от своего текущего сюзерена
(и тогда этот сюзерен также есть вчисле участников).
Попытка освобождения может совмещаться (в одной осаде) с попыткой другим кланом захватить
освобождающегося.
2. Участники, чьё время присоединения к осаде совпадает с временем начала осады -- это
защищающийся (target либо suzerain) и инициатор осады, у всех остальных время присоединения
к осаде будет больше.

Осада, в которой остался только один участник, автоматически завершается его победой.

Если у победителя-захватчика нет места на ещё одного вассала, ему даётся время на принятие
решения (осада переходит в статус 'lock'). В случае его отказа осада не меняет текущего
вассалитета цели. Исключение: если сама цель осады боролась за освобождение и заняла второе
место по количеству очков осады, то при отказе победителя освобождение цели засчитывается.

В случае удаления клана он автоматически покидает все осады, в которых участвует.
Если он сам является целью осады -- такая осада прекращается с возвращением участником
очков стратегии, потраченных на инициацию/присоединение к осаде.

=======
Сервис рассчитан на получение запросов, как правило, от сервиса кланов, не напрямую.
Сервис кланов будет сам кешировать информацию и агрегировать её в ответы на запросы
про кланы.
Корректность параметров запроса (например, ограничение на одну осаду-захват в один
момент для одного клана) ложится, по возможности, на сервис кланов.

Сервис рассчитан на запуск нескольких независимых экземпляров, распределение нагрузки
делается аналогично клан-сервису, по _id осады.
(_id используется как стандартный идентификатор монги)
"""

from base.helpers import *
import tornado.options
from tornado.options import define, options
from base.wstools import AddLoopCallback
from itertools import takewhile, dropwhile, groupby

addModPath('cfg')
import cfg

from base.service_lock import ServiceLock
from iwebserver import *
from ifactory import IfaceFactory
from iuserdata import IDataManager

from handlers import * # JsonHandler, IfaceFactory
from subaction import SubAction, action_timing, separate_timing  # also addRelPath('thrift_pw/statistics/gen-py') is here!
from siege.handlers import *
from functools import partial
from StatisticCore.ttypes import GuildInteractionType

addModPath("../thrift_pw/account_management/gen-py")
from AccountManagementAPI.ttypes import ConfigEventType

import CC
import EC

DEFAULT_PORT=8741

#DEFAULT_SIEGE_DURATION=24*60*60 # 1 day   - moved ro Сonfig, PF-92274
#DEFAULT_SIEGE_LOCK=4*60*60 # 4 hours      - moved ro Сonfig, PF-92274
# DEFAULT_NOTIFY_PERIOD = 60 - unused

DAYS_TR = 30 # на сколько дней назад нас интересуют техработы
TR_LEN = DAYS_TR * 60 * 60 * 24

#
#### Логика уведомления кланов об измененииях осад:
#
# action = update_siege, в данных список изменений, в каждом изменении
#
# cmd == "start"
#   начало осады
# cmd == "lock"
#   переход осады в состояние блокировки после окончания
# cmd == "remove"
#   убрать осаду из списков осад клана
# cmd == "destroy"
#   убрать осаду из списков, вернув её стоимость, если клан платил за участие в осаде
# cmd == "leave"
#   клан выбывает из осады - уведомление для остающихся
# cmd == "score"
#   изменение очков осады
# cmd == "join"
#   присоединение к осаде нового участника
# cmd == "time"
#   изменение времени окончания осады
#
# Все изменения сохраняются на каждого получателя отдельно.
# Параметры события каждый раз разные, и пока их можно посмотреть в UpdateSiegeAction в GuildRequests.py
# Изменения, перечисленные в IMMEDIATE_EVENTS, отправляются немедленно (и забирают с собой все накопленные).
# Изменения, перечисленные в FORCED_EVENTS, отправляются даже неподписанным кланам (гильдсервис
# подгрузит их и обновит).

# В данные гильдии надо что-то писать, только если "выиграл и получил вассала" или "проиграл и потерял".
# Если "выиграл и отстоял своего" - ничего вроде писать не надо. Если проиграл и не получил - тоже.
#

IMMEDIATE_EVENTS = set(('start', 'remove', 'time', 'destroy', 'lock'))
FORSED_EVENTS = set(('start', 'remove', 'time', 'destroy')) # send this events for target (only for target) even if it's not subscribed

# Length (in seconds) of a gap after a siege end that gives time for batlle results to come from PvX to SS
GAP_LENGTH = 2 * 60
# During a gap period scores are accepted, but joins and leaves are not acepted

# TODO описать поля дикта siege!

def is_participant(guild, siege):
    return any( part for part in siege["participants"] if part["id"] == guild )

def is_actual_participant(guild, siege):
    return any( part for part in siege["participants"] if part["id"] == guild and "leave" not in part)

def check_participant(guild, siege):
    return siege and siege["end_time"] > time.time() and siege['status'] in ('active', 'gap') and is_actual_participant(guild, siege)



class SiegeServiceHandler(JsonHandler):
    """Обработчик запросов - обрабатываем только внутренние запросы от рабочих серверов"""
    internalActionMap = {
        # --- служебное ----
        'check_alive'          : 'onCheckWebServerAlive', # base JsonHandler: умеем отвечать, что мы живы
        'reload_multi_config'  : 'onReloadMultiConfigWithMainSD', # base JsonHandler: умеем перегружать logic_cfg+StaticData со всеми внутренностями
        'clear_addr_info'      : 'onClearAddrInfoCache', # base JsonHandler: умеем чистить кэш addrinfo (чтобы заново резолвить адреса после перестройки DNS)
        'youare'               : 'onWhoAmIReply',  # координатор сообщает сервису его номер среди таких же
        'add_techs'            : 'onAddTechs',  # Координатор добавляет данные о тех-работах
        'get_stat'             : 'onGetStat',

        # --- guild service actions ---
        'subscribe'            : SubscribeAction,
        'unsubscribe'          : UnsubscribeAction,
        'start'                : StartSiegeAction,   # начать осаду данной цели, если цель под осадой - присоединииться к осаде
        'join'                 : JoinSiegeAction,    # присоединиться к осаде
        'leave'                : LeaveSiegeAction,   # сбежать (признать поражение и выйти) из осады
        'score'                : ScoreAction,        # здобавить в счёт осады полученные игроками очки стратегии
        'get_sieges'           : GetSieges,          # все осады для данного клана
        'choice'               : WinnerChoiceAction, # победитель принимает нового вассала или отказывается
        'destroy'              : DestroySiegeAction, # прервать осаду и вернуть очки всем участникам
        'check'                : CheckSiegeAction,   # есть ли такая осада?

        # --- debug actions ---
        'set_duration'         : SetDurationAction,
        'set_score'            : SetScoreAction,
    }

    def onGetStat(self):
        info("onGetStat")
        self.response["ok"] = 1
        self.response["active_siege"] = len(self.I.WS.active)
        self.response["gapped_siege"] = len(self.I.WS.gapped)
        self.response["activeGuilds"] = len(self.I.WS.activeGuilds)
        self.fin()

    def onCheckWebServerAlive(self):
        if self.I.WS.shardingPos is None:
            self.response["whoami"] = 1 # request to send our position among other siege services
        super(SiegeServiceHandler, self).onCheckWebServerAlive()


    def onWhoAmIReply(self):
        if self.I.WS.shardingPos is None:
            pos = self.getIntParam("pos") # valid value >= 0
            total = self.getIntParam("total") # valid value > 0
            info("onWhoAmIReply: I am %s of %s", pos, total)
            if total and pos is not None:
                self.I.WS._setShardingParams(pos, total)
        else:
            info("onWhoAmIReply: duplicate call, ignored")
        self.response["ok"] = 1
        self.fin()


    def onReloadMultiConfigWithMainSD(self):
        rc = super(SiegeServiceHandler, self).onReloadMultiConfigWithMainSD()
        self.I.WS.onReloadMultiConfig()
        return rc

    def onAddTechs(self):
        persistentId = self.getIntParam("persistentId")
        techType = self.getParam("techType").split(',')
        compensation = self.getIntParam("compensation")
        startTime = self.getIntParam("startTime", 0)

        if persistentId and "sieges" in techType:
            self.I.WS.addTechs(persistentId, startTime, compensation)


class SiegeService(ICSVActionTimingWriter, ITornadoServer):
    # не надо ли в предки ещё и ISocialExchangeUser - для уведомлений?
    server_type_name = "ss"

    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = SIEGE_SERVER_ID
            options.server_name = SIEGE_SERVER_NAME
            options.server_class = "siege"
        else:
            options["server_id"].set(SIEGE_SERVER_ID)
            options["server_name"].set(SIEGE_SERVER_NAME)
            options["server_class"].set("siege")


    def __init__(self, **kwargs):
        super(SiegeService, self).__init__(**kwargs)
        self.guilds = {}
        self.sieges = {}
        self.active = [] # sieges ordered by end time (suppose, end time never changes!)
        self.gapped = [] # sieges on a gap, ordered by end time
        self.locked = [] # sieges ordered by update end_time
        self.byTarget = {} # sieges by target, refer to the same object as from self.sieges
        self.byPartyicipants = {}
        self.suspendedEvents = {} # sieges modifications waiting to be sent: guildAuid => [events]
        self.activeGuilds = set() # guildAuid
        self.guids["siege_service"] = int((time.time()-1400000000)*10) # init guid counter
        self.cached = False # will set True after caching all it's sieges
        self.shardingPos = None
        self.shardingTotal = None
        self._last_minute = 0
        self.ready = False
        self.enabled = True
        self.techs = {}
        self.lastRev = None # use None as a 'not ready' flag here

        self.I.DATA.find(CC.EVENTS_DATA, CC.EVENTS_DATA, {"type": ConfigEventType.Techs},
                         params=None, callback=self.onGetTechsInfos)
        #self.techsLock = ServiceLock(self.I.DATA, 'siege_techs', self.onSemaphoreReady
        #self.I.DATA.find("vars", "vars", {}, self.onVarsLoaded, params=None)
        self.defencePointsPercent = CC.DEFAULT_DEFENCE_POINTS_PRSENT


    # OVERRIDE
    def onGetPeerServer(self, peer, peer_name, peer_id, status):
        pass # do nothing - we have no interests in WSes


    def initHandlers(self, application):
        application.add_handlers( r"(.*)", [
            (r"/x", SiegeServiceHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I)),
        ])
        self.onReloadMultiConfig()


    # return True if startup enviroment is bad
    @staticmethod
    def checkStartupFail():
        # проверяем, не слушает ли на нашем порту кто-то еще (защита от повторного запуска координатора)
        self_addr = "127.0.0.1:" + str(options.port)
        res = httpClientRequest(addr=self_addr, server="x", params="action=check_alive&name=_siege_service_") # SYNC ok
        if res and res.get("ok") != None:
            fatal("DUPLICATE SIEGE SERVER: already listening on " + self_addr + "\n(reply was %s)", str(res))
            return True # обламываемся, уже запущена копия веб-сервера на этом порту

        print("check startup environment: ok, port free (" + self_addr + ")")

    # -----------------------------------------------
    _SPECIFIC_CONFIG_PARAMS = {
        "guilds_svc": "GUILD_SERVICES",
        "siege_svc": "SIEGE_SERVICES",
        "curl_wrk": "HTTP_CURL_WORKERS",
        "stats_agent": "STATS_AGENT_URL",
    }

    @staticmethod
    def initInterfaces(classOf=None):
        # --- для начала надо связаться с координатором и получить от него актуальные кластерные настройки для cfg
        coord_res = {}
        if options.coordinator != "none":
            # начали слушать; сообщаем координатору, что готовы принимать http-send'ы на своем порту
            for t in timeouts_iterator((10, 20, 30, 45, 60)):
                coord_res = httpClientRequest( addr=options.coordinator, server="x", params="action=ws_ready&name=%s" % options.server_name )
                if coord_res and coord_res.get("ok"):
                    info( "Reported 'ready' state to coordinator: reply " + str(coord_res) )
                    classOf.updateSpecificParamList( coord_res, getattr(classOf, "_SPECIFIC_CONFIG_PARAMS", {}), classOf.server_type_name )
                    break
                else:
                    # raise Exception("Cannot report to coordinator (addr:%s)\ncoordinator reply was:%s" % ( str(options.coordinator), str(coord_res)))
                    err("Cannot report to coordinator (addr:%s)\ncoordinator reply was:%s\nSuspending for %d seconds" % ( str(options.coordinator), str(coord_res), t))
                    time.sleep(t)
                    #FIXME Хорошо бы научить их ждать прихода координатора

        #FIXME Все параметры получать от координатора, а не из файла!
        iDict = ClassDict(
            HTTP   = tornado.httpclient.AsyncHTTPClient(max_clients=cfg.HTTP_CURL_WORKERS),
            WS     = IWebServer(), # чисто для генерации GUID-ов
            MD     = IDataManager(), # обычным веб-серверам требуется только оболочка DataManager для заворачивания JSON-данных. TODO выпилить по PF-92199
            Config = MultiConfig(),
        )
        info( "MD interface: " + str(iDict.MD) )

        iDict.MSD = MultiStaticData("xdb/ExportedSocialData.xml", iDict.Config.getMainConfig(), loadLocales=False)
        iDict.SD = iDict.MSD.getMainSD()
        if iDict.SD:
            # конфиг logic_overrides может содержать переопределения полей StaticData; их тоже нужно применить к перегруженной SD
            iDict.Config.mainConfig.applyOverrides(iDict.SD)
            # Заполним статические поля, которые можно перезаписыать из GMTools
            iDict.Config.mainConfig.fillStaticDataDependendValues(iDict.SD)
        iDict.GUILD = IfaceFactory.makeGuildServiceInterface(options.guilds, cfg.GUILD_SERVICES, HTTP=iDict.HTTP)
        iDict.SIEGE = IfaceFactory.makeSiegeServiceInterface(options.sieges, cfg.SIEGE_SERVICES, HTTP=iDict.HTTP)

        info( "GuildService interface: " + str(iDict.GUILD ) )
        iDict.DATA = IfaceFactory.makeIDataInterface("mongo", coord_cfg.COORDINATOR_MONGO_CONFIG, None)
        #iDict.MIRROR = IfaceFactory.makeMirrorInterface(options.mirror, coord_cfg.COORDINATOR_MIRROR_QUEUE_CONFIG,
        #                                                num_threads=coord_cfg.COORDINATOR_MIRROR_QUEUE_THREADS)
        #info("Mirror interface: " + str(iDict.MIRROR))
        iDict.STATS = IfaceFactory.makeIStatsInterface(options.stats, cfg.STATS_AGENT_URL, iDict, cfg.STATS_RESEND_POOL_LIMIT)
        info("Statistics interface: " + str(iDict.STATS))
        return iDict


    def tick(self):
        try:
            if self.enabled:
                self.checkSieges()
        except Exception:
            catch("checkSieges on tick failed: ")
        min = int(time.time()) / 60
        if min > self._last_minute:
            self._last_minute = min
            try:
                if self.enabled:
                    self.sendBufferedNotificatons()
            except Exception:
                catch("sendBufferedNotificatons on tick: ")
            self.updateInstrumentedActions()
            if self.I.STATS:
                ts0 = time.clock()
                try:
                    self.I.STATS.Send()
                except:
                    catch()
                info("STATS.Send time: %.3f" % (time.clock()-ts0))
            self.gcTick()



    def onVarsLoaded(self, response):
        info("onVarsLoaded: %s", response)
        if response and 'r' in response:
            found = False
            if 'e' in response:
                warn("SiegeService.onVarsLoaded: %s", response['e'])
            else:
                #FIXME сделать это, а также установку значений, каким-то общим механизмом
                for v in response['r']:
                    name = v['_id']
                    if name == 'sieges_disabled':
                        found = True
                        info("VARS: sieges_disabled = %r", v['value'])
                        if not v['value']:
                            self.enabled = False
            if not found:
                if self.enabled:
                    self.clearDisabled() # FIXME!!! UPDATE SIEGE TIMES!!!
                else:
                    self.saveDisabled(upsert=True)
        else:
            warn("SiegeService.onVarsLoaded: EMPTY response")
        #Next to load:


    def saveDisabled(self, upsert=False):
        self.I.DATA.find_and_modify("vars", "vars", {'_id': 'sieges_disabled', 'value': 0}, callback=self.dummyMongoCallback,
                                    update={'_id': 'sieges_disabled', 'value': int(time.time())}, upsert=upsert)


    def clearDisabled(self):
        self.I.DATA.update("vars", "vars", {'_id': 'sieges_disabled'}, {'value': 0},  callback=self.dummyMongoCallback)


    def dummyMongoCallback(self, response):
        if not response:
            err("Mongo call returns empty response!")
        elif 'e' in response:
            err("Mongo call returns error: %s", response)
        else:
            debug("Mongo call returns: %s", response)


    def onGetTechsInfos(self, response):
        if response and "r" in response:
            info("SiegeService: onGetTechsInfos")
            debug("SiegeService: onGetTechsInfos %r", response)
            for techEvent in response["r"]:
                compensationTypes = techEvent["customData"]["techType"].split(',')
                if "sieges" in compensationTypes:
                    self.techs[techEvent["_id"]] = {"startTime": techEvent["startTime"],
                                                    "duration": techEvent["customData"]["compensation"]}

            if self.techs:
                self.lastRev = max(self.techs.keys())
        else:
            err("Failed to load techs info")
        info("updateTechsInfo: lastRev %s, techs %s", self.lastRev, self.techs)

    def updateSiegeEnds(self):
        info("updateSiegeEnds")
        updated = {'active': 0, 'locked': 0}
        for siege in self.sieges.itervalues():
            # note, we don't correct gapped list - the gap time is just and internal implementation feature
            # really this sieges are already finished, but results aren't checked
            if siege['status'] in ('active', 'locked', 'gap') and siege['rev'] < self.lastRev:
                if siege['status'] != 'gap': # for gapped sieges just set 'rev'
                    old_time = siege['end_time']
                    for revision in self.techs:
                        tech = self.techs[revision]
                        if siege['end_time'] <= tech['startTime']:
                            break # self.techs is ordered by start DESC, so stop iteration here
                        if siege.get('rev', 0) < revision:  # but order by 'rev' is not guaranteed
                            siege['end_time'] += tech['duration']
                    if old_time < siege['end_time']:
                        updated[siege['status']] += 1
                        self.notifyParticipants(siege,
                            {'cmd': 'time', '_id': siege['_id'], 'end_time': siege['end_time'], 'status': siege['status']})
                siege['rev'] = self.lastRev
                self.I.DATA.update("sieges", "sieges", {"_id": siege["_id"]},
                                   {"end_time": siege["end_time"], 'rev': siege['rev']},
                                   callback=self.dummyMongoCallback)
        if updated['active']:
            self.active.sort(key=lambda s: s['end_time'])
        if updated['locked']:
            self.locked.sort(key=lambda s: s['end_time'])
        info("Updated siege end times: %s", updated)


    def getByTarget(self, target):
        try:
            return self.byTarget[target]
        except KeyError:
            self.error_response = {'ec': EC.NO_SIEGE_FOR_TARGET, 'error': "Siege with this target not found"}
            return None


    def popError(self):
        try:
            res = self.error_response
            del self.error_response
        except AttributeError:
            return None
        return res

    def onAddTechs(self, persistentId, startTime, duration):
        self.techs[persistentId] = {"startTime": startTime, "duration": duration}
        lastId = max(self.techs.keys())
        if lastId != self.lastRev:
            self.lastRev = lastId
            self.updateSiegeEnds()

    def onReloadMultiConfig(self):
        self.settings = self.I.Config.getMainConfig().SiegeSettings
        enabled = self.I.Config.getMainConfig().GUILD_WARS_ENABLED
        info("onReloadMultiConfig: GUILD_WARS_ENABLED: %s", enabled)
        if self.enabled != enabled:
            info("Switching sieges %s", "ON" if enabled else "OFF")
            self.enabled = enabled
#            if enabled:
#                self.clearDisabled() # FIXME!!! UPDATE SIEGE TIMES!!!
#            else:
#                self.saveDisabled()
        debug("Siege Duration setting = %s", self.settings.SIEGE_DURATION)
        try:
            self.defencePointsPercent =  self.I.SD.data["ClanWarsData"]["defencePointsPercent"]
            debug("Siege start defencePointsPercent: %s", self.defencePointsPercent)
        except:
            catch("onReloadMultiConfig: no StaticData ClanWarsData->defencePointsPercent value found. Keep old value %s", self.defencePointsPercent)

    def _setShardingParams(self, pos, total):
        if self.cached:
            err("_setShardingParams called when self.cached id True!")
            return
        self.shardingPos = pos
        self.shardingTotal = total
        self.preloadSieges()


    def _checkMySiege(self, key):
        return key % self.shardingTotal == self.shardingPos


    def preloadSieges(self):
        # Кешируем в памяти все осады (предназначенные для нашего сервера)
        self.I.DATA.find("sieges", "sieges", {}, params=None, callback=self.onPreloadSieges)


    def _setParticipantRef(self, part_id, siege):
        self.byPartyicipants.setdefault(part_id, []).append(siege) # FIXME может, тут set(), заполненный id осад?


    def _rmParticipantRef(self, part_id, siege):
        try:
            if part_id != CC.NPC_SUZERAIN_AUID:
                self.byPartyicipants[part_id].remove(siege)
        except KeyError:
            warn("_rmParticipantRef: Guild %s isn't a participant in any of my sieges!", part_id)
        except ValueError:
            warn("Guild %s isn't a participant of siege %s", part_id, siege["_id"])


    def _setSiegeRefs(self, siege):
        self.sieges[siege["_id"]] = siege
        self.byTarget[siege["target"]] = siege
        for part in siege["participants"]: # Вопрос, надо ли тут ссылаться на тех, кто уже ливнул? Видимо, нет.
            if "leave" not in part and part['id'] != CC.NPC_SUZERAIN_AUID:
                self._setParticipantRef(part["id"], siege)


    def _releaseSiegeRefs(self, siege):
        try:
            del self.sieges[siege["_id"]]
        except KeyError:
            catchFull()
            err("Siege %s not found in self.sieges. Full siege data: %s", siege["_id"], siege)
        try:
            del self.byTarget[siege["target"]]
        except KeyError:
            catchFull()
            err("Siege %s not found in self.byTarget. Full siege data: %s", siege["_id"], siege)
        for part in siege["participants"]: # Вопрос, надо ли тут ссылаться на тех, кто уже ливнуд? Видимо, нет.
            if "leave" not in part:
                self._rmParticipantRef(part["id"], siege)


    def _cleanLosers(self, siege):
        "Remove participants except of winner, target and suzerain"
        losers = []
        keep = []
        for part in siege["participants"]:
            if "leave" not in part:
                if part['id'] not in (siege['target'], siege['suzerain'], siege['winner']):
                    part['leave'] = int(time.time())
                    part['finished'] = True # means it didn't leave in the middle but stays until the end, but lost
                    losers.append(part['id'])
                    self.addNotification(part['id'], {'cmd': 'remove', '_id': siege['_id']})
                    self._rmParticipantRef(part['id'], siege)
        return (keep, losers)


    _REQUIED_FIELDS = ('status', 'target', 'suzerain', 'end_time', 'participants')

    def _checkSiegeFields(self, siege):
        absent = [k for k in self._REQUIED_FIELDS if k not in siege]
        if absent:
            err("Some fields lost from siege %s: %s. Siege IGNORED!\nSiege data: %s", siege['_id'], ', '.join(absent), siege)
            return True
        return False


    def onPreloadSieges(self, response):
        info("onPreloadSieges: Response = %r", response)
        if response and response.get("r") is not None:
            for siege in response["r"]:
                debug("onPreloadSieges: siege: %s", siege)
                if self._checkSiegeFields(siege):
                    continue
                if self._checkMySiege(siege["target"]):
                    self._setSiegeRefs(siege)
            for s in sorted(self.sieges.itervalues(), key=lambda s: s['end_time']):
                if s['status'] == 'active':
                    self.active.append(s)
                elif s['status'] == 'gap':
                    self.gapped.append(s)
                elif s['status'] == 'locked':
                    self.locked.append(s)
                else:
                    err("onPreloadSieges: Wrong status %s of the siege %s: %s", s['status'], s['_id'], s)
            self.cached = True
            info("onPreloadSieges: %s sieges cached", len(self.sieges))
            debug("onPreloadSieges: cached sieges: %s", self.sieges)
            if self.lastRev is not None:
                self.updateSiegeEnds()
        else:
            err("onGetDynamicQuestList: error loading active sieges")


    def _appendScoreNotification(self, events, newEvent):
        for e in events:
            if e['cmd'] == 'score' and e['_id'] == newEvent['_id'] and e['guildAuid'] == newEvent['guildAuid']:
                e['score'] = newEvent['score']
                return
        # if no score for this guild in this siege found - append the event
        events.append(newEvent)


    def addNotification(self, guild, event, force=False):
        if guild in self.activeGuilds or (force and event['cmd'] in FORSED_EVENTS):
            info("addNotification for %s,%s event %s", guild, ' (FORCED)' if force else '', event)
            if guild in self.suspendedEvents:
                if event['cmd'] == 'score':
                    self._appendScoreNotification(self.suspendedEvents[guild], event)
                else:
                    self.suspendedEvents[guild].append(event)
            else:
                self.suspendedEvents[guild] = [event]
            if event['cmd'] in IMMEDIATE_EVENTS:
                self._notifyGuild(guild)


    def _notifyGuild(self, guild):
        events = self.suspendedEvents.pop(guild)
        self.I.GUILD.updateSiege(guild, events, partial(self.onGuildNotified, guild=guild, events=events))


    def notifyParticipants(self, siege, event, exclusion=None):
        "Notify all participants, except leaved ones, and the target."
        info("notifyParticipants: siege %s,\nevent %s", siege, event)
        sent = []
        target = siege['target'] if (event['cmd'] in FORSED_EVENTS) else None
        for part in siege["participants"]:
            if "leave" not in part and part['id'] != exclusion:
                self.addNotification(part["id"], event, part["id"] == target)
                sent.append(part["id"])
        if siege['target'] != exclusion and siege['target'] not in sent:
            self.addNotification(siege['target'], event, target)


    def onGuildNotified(self, response, guild, events):
        info("onGuildNotified %s: %s", guild, response)
        if not (response and response.get("ok")):
            if guild in self.activeGuilds:
                if guild in self.suspendedEvents:
                    self.suspendedEvents[guild][:0] = events # Restore events in the queue front
                else:
                    self.suspendedEvents[guild] = events
            err("updateSiege request failed for guild %s at server '%s'\nevents: %s",
                guild, response.get('server') if response else '', events)


    def sendBufferedNotificatons(self):
        # Это может получиться не мгновенно, потому снимаем копию списка
        for guild in self.suspendedEvents.keys():
            self._notifyGuild(guild)


    def subscribeAction(self, guildAuid, callback=None):
        info("subscribeAction: guild %s", guildAuid)
        self.activeGuilds.add(guildAuid)
        # now find all it's sieges
        callback(self.findGuildSieges(guildAuid))


    def findGuildSieges(self, guild):
        res = self.byPartyicipants.get(guild, [])
        siege = self.byTarget.get(guild)
        if siege and not siege in res:
            res = res[:] + [siege]
        #debug("findGuildSieges for %s, found: %s", guild, map(lambda s: s["_id"], res))
        return res


    def unsubscribeAction(self, guildAuid):
        self.activeGuilds.discard(guildAuid)
        self.suspendedEvents.pop(guildAuid)


    def checkTargetAndSieger(self, target, sieger):
        return check_participant(sieger, self.byTarget.get(target))


    def checkReverseSiege(self, invider, target, callback):
        """Check if the target already sieges the invider.
        Returns True if the siege found on this service, else calls the callback and returns False"""
        if self._checkMySiege(invider):
            if self.checkTargetAndSieger(target=invider, sieger=target):
                return True
            # it's ok, no reverse siege, can proceed
            callback(True)
        else:
            ## need to check through db
            #cb = partial(self.reverseSiegeChecDb, target=target, callback=callback)
            #self.I.DATA.find_one("sieges", "sieges", {'target': invider}, cb, params=None)
            # need to ask another siege service
            self.I.SIEGE.checkSiege(invider, target, partial(self.reverseSiegeCheckSiege, callback=callback))
        return False


    def reverseSiegeCheckSiege(self, response, callback):
        if response and response.get('ok'):
            callback(not response.get('found'))
        else:
            err("reverseSiegeCheckContinue: error in mongo response: %s", response)
            callback(False)


    def reverseSiegeChecDb(self, response, target, callback):
        if response:
            try:
                if check_participant(target, response.get('r')):
                    return callback(False)
            except Exception:
                catch()
                callback(None)
            callback(True)
        else:
            err("reverseSiegeCheckContinue: error in mongo response: %s", response)
            callback(True)


    def getNewSiegeId(self):
        "Paranoidly checking. It looks impossible, but we've got duplicate key errors by this ids!"
        while True:
            sid = self.I.WS.nextInt64GUID("siege_service")
            if sid not in self.sieges:
                info("getNewSiegeId: %s - ok, desn't exist in self.sieges", sid)
                return sid
            err("getNewSiegeId: Generated siege id %s already exists in self.sieges!", sid)

    def startSiegeAction(self, (target, targetRating), (invider, inviderRating), (suzerain, suzerainRating), price, callback):
        siege = self.byTarget.get(target)
        if siege is None:
            now = int(time.time())
            # второй участник осады:
            # - сюзерен таргета, если таргет - чей-то вассал
            # - сам таргет, если он не имеет сюзерена
            # - сам таргет, если он является сюзереном инициатора (это случай осады-за-освобождение)
            defender_rating = suzerainRating if suzerain else targetRating
            siege = {
                "_id": self.getNewSiegeId(),
                "target": target,
                "target_rating": targetRating,
                'status': 'active', # other possible values: 'gap', 'locked', 'done'
                'start_tm': now,
                'end_time': now + self.settings.SIEGE_DURATION,
                'suzerain': suzerain,
                'suzerain_raiting': suzerainRating,
                'participants': [
                    {'id': invider, 'score': 0, 'rating': inviderRating, 'start': now, 'price': price},
                    {'id': (suzerain if suzerain else target),
                     'score': defender_rating if suzerain == CC.NPC_SUZERAIN_AUID else int(defender_rating * self.defencePointsPercent),
                     'rating': defender_rating,
                     'start': now, 'price': 0}
                ],
                'rev': 0 if self.lastRev is None else self.lastRev, # for techs check
            }
            self._setSiegeRefs(siege)
            self.active.append(siege)
            info("startSiegeAction: new siege: %r", siege)
            self.I.DATA.insert("sieges", "sieges", siege.copy(), callback=partial(self.onSiegeSave, siege=siege, callback=callback))
            self.notifyParticipants(siege, {'cmd': 'start', 'siege': siege}, exclusion=invider)
        else:
            self._performJoin(siege, invider, inviderRating, price, callback)


    def joinSiegeAction(self, target, invider, inviderRating, price, callback):
        siege = self.getByTarget(target)
        if siege is None:
            return callback(self.popError())
        self._performJoin(siege, invider, inviderRating, price, callback)


    def _performJoin(self, siege, invider, inviderRating, price, callback):
        now = int(time.time())
        if is_participant(invider, siege):
            warn("_performJoin: guild %s already takes part in the siege %s", invider, siege["_id"])
            callback({"ec": EC.ALREADY_SIEGE_PARTICIPANT, "error": "already takes part in this siege"})
        elif siege["status"] != "active":
            callback({"ec": EC.SIEGE_FINISHED, "error": "The siege is finished already"})
        else:
            siege["participants"].append({"id": invider, "score": 0, 'rating': inviderRating, 'start': now, 'price': price})
            self._setParticipantRef(invider, siege)
            info("_performJoin: join to siege: %r", siege)
            self.I.DATA.update("sieges", "sieges", {"_id": siege["_id"]}, {"participants": siege["participants"]},
                               callback=partial(self.onSiegeSave, siege=siege, callback=callback))
            self.notifyParticipants(siege, {'cmd': 'join', 'guildAuid': invider, '_id': siege['_id']}, exclusion=invider)


    def onSiegeSave(self, response, siege, callback):
        info("onSiegeSave: response %r, siege %r", response, siege)
        if not response or response.get("r") is None:
            msg = response.get("ex")
            err("onSiegeSave: error saving/updating siege: %s\nSiege: %s", msg, siege)
            if 'DuplicateKeyError' in msg: # BUT HOW?! Let's check in mongo
                self.I.DATA.find_one("sieges", "sieges", {"_id": siege["_id"]}, partial(self.onGetDuplicatedSiege, siege=siege))
            # we don't return an error since it really can go on with this siege processing unless we stop this siege-service
            #TODO: make this error processing smarter!
        if callback:
            callback({"siege" : siege, "ok": 1})


    def onGetDuplicatedSiege(self, response, siege):
        err("onGetDuplicatedSiege: Fail condition check response: %s\nFailed-on-insert siege:%s", response, siege)


    def leaveSiegeAction(self, target, guild, callback):
        siege = self.getByTarget(target)
        if siege is None:
            return callback(self.popError())
        if siege["status"] != "active":
            return callback({'ec': EC.SIEGE_FINISHED, 'error': ("The siege is '%s' already" % ("finished" if siege.get("gap") else siege['status']))})
        for part in siege["participants"]:
            if part["id"] == guild:
                if not part.get("leave"):
                    part["leave"] = int(time.time())
                    self.I.DATA.update("sieges", "sieges", {"_id": siege["_id"]}, {"participants": siege["participants"]},
                                       callback=partial(self.onSiegeLeaveSave, siege=siege, leaver=guild, callback=callback))
                    self._rmParticipantRef(guild, siege)
                    return
                else: # it's already left, so let's return OK, it's not a problem
                    warn("Siege %s. Already left participant %s tries to leave gain.", siege['_id'], guild)
                    callback({"ok": 1, "siege": siege['_id']})
                    return
        callback({"ok": 0, "ec": EC.PARTICIPANT_NOT_FOUND, "error": "No such participant in this siege"})


    def onSiegeLeaveSave(self, response, siege, leaver, callback):
        info("onSiegeLeaveSave: Response = %r", response)
        if not response or response.get("r") is None:
            err("onSiegeLeaveSave: siege update (leaver %s) not saved into mongo, error: %s\rSiege: %s", leaver, response.get("ex"), siege)
        self.notifyParticipants(siege, {'cmd': 'leave', 'guildAuid': leaver, '_id': siege['_id']})
        callback({"ok": 1, "siege": siege['_id']})
        if sum(not p.get("leave") for p in siege["participants"]) < 2:
            # no more opponents - end the siege
            self.processSiegeResult(siege, untimely=True)


    def checkSieges(self):
        "Is any siege ready for status change?"
        while self.locked:
            siege = self.locked[0]
            if siege['status'] == 'done':
                del self.locked[0]
            elif siege['end_time'] <= int(time.time()):
                self.processTimeOver(siege) # it performs del self.locked[0]
            else:
                break
        while self.gapped:
            siege = self.gapped[0]
            if siege['status'] == 'done':
                del self.gapped[0]
            elif siege['end_time'] <= int(time.time()):
                self.processSiegeResult(siege) # it performs del self.gapped[0]
            else:
                break
        while self.active:
            siege = self.active[0]
            if siege['status'] == 'done':
                del self.active[0]
            elif siege['end_time'] <= int(time.time()):
                self.setGap(siege) # it performs del self.active[0]
            else:
                break


    def siegeEndTimeUpdate(self, siege, newtime):
        """Modify the active siege end_time and move it to the right place in self.active.
        Also call self.notifyParticipants().
        Don't save the siege into DB, since only the caller knows what callback to use with it.
        """
        info("siegeEndTimeUpdate: siege %s: %s -> %s", siege['_id'], siege['end_time'], newtime)
        delta = newtime - siege['end_time']
        siege['end_time'] = newtime
        # and now move it to it's new position according to the 'end_time'
        if len(self.active) > 1:
            try:
                i = self.active.index(siege)
            except ValueError:
                warn("Siege %s is not in self.active list!", siege)
                return False
            #debug("siegeEndTimeUpdate: old siege position %s, time delta %s", i, delta)
            if delta > 0:
                block = [v for v in takewhile(lambda s: s["end_time"] < newtime, self.active[i+1:])]
                if block:
                    self.active[i:i + len(block) + 1] = block + [siege]
            else:
                block = [v for v in dropwhile(lambda s: s["end_time"] < newtime, self.active[0:i])]
                if block:
                    self.active[i-len(block):i+1] = [siege] + block
            #debug("siegeEndTimeUpdate: %s", map(lambda s: {'_id': s['_id'], 'end_time': s['end_time']}, self.active))
        self.notifyParticipants(siege, {'cmd': 'time', '_id': siege['_id'], 'end_time': newtime, 'status': siege['status']})


    def setGap(self, siege):
        info("Siege %s finished. Setting %s seconds gap.", siege["_id"], GAP_LENGTH)
        del self.active[0]
        now = int(time.time())
        siege['gap_tm'] = now
        siege['end_time'] = now + GAP_LENGTH
        siege['status'] = 'gap'
        self.gapped.append(siege)
        self.I.DATA.update("sieges", "sieges", {"_id": siege["_id"]},
                           dict((k, siege[k]) for k in ("gap_tm", "end_time", "status")),
                          callback=partial(self.onGapSaved, siege=siege))
        self.notifyParticipants(siege, {'cmd': 'time', '_id': siege['_id'], 'end_time': siege['end_time'], 'status': 'gap'})


    def onGapSaved(self, response, siege):
        info("onGapSaved: Response = %r", response)
        if not response or response.get("r") is None:
            err("Error saving siege gap: %s\nSiege data: %s", response.get("ex"), siege)


    def scoreAction(self, guild, points, callback):
        for siege in self.byPartyicipants.get(guild, []):
            if siege['status'] in ('active', 'gap'): # accept scores during a gap -- this is a gap's purpose
                for part in siege["participants"]:
                    if part['id'] == guild:
                        part["score"] += points
                        self.I.DATA.update("sieges", "sieges", {"_id": siege["_id"]}, {"participants": siege["participants"]},
                                   callback=partial(self.onScoreSaved, guild=guild, score=part["score"], siege=siege))
                        self.notifyParticipants(siege, {'cmd': 'score', 'guildAuid': guild, 'score': part["score"], '_id': siege['_id']})
                        break
        callback({"ok": 1})


    def onScoreSaved(self, response, guild, score, siege):
        info("onScoreSaved: Response = %r", response)
        if not response or response.get("r") is None:
            err("Error saving siege score: %s\nGuild %s, score %s, siege data: %s", response.get("ex"), guild, score, siege)


    def _chooseWinner(self, siege):
        'What if 2+ guilds have equal top score.'
        #NOTE: the same logic is also implemented in checkVassalWin
        participants = [p for p in siege['participants'] if not p.get('leave') or p.get('finished')]
        winner = max(participants, key=lambda p: p['score'])
        all_winners = [p for p in participants if p['score'] == winner['score']]
        if len(all_winners) > 1:
            winner = min(all_winners, key=lambda p: p['start'])
            same_start = [winner]
            for p in all_winners:
                if p is not winner and p['start'] == winner['start']:
                    same_start.append(p)
            if len(same_start) > 1: # same time (it means, one of them is the defender), equal points => no winner!
                return None
            return winner
        else:
            return all_winners[0]


    def processSiegeResult(self, siege, untimely=False):
        "Check the winner, change status to done or lock, send events"
        info("processSiegeResult(untimely=%s): siege: %s", untimely, siege)
        if untimely:
            try:
                self.active.remove(siege)
            except:
                warn("Untimely siege finishing: siege was not in self.active!")
        else:
            del self.gapped[0]
        winner = self._chooseWinner(siege)
        if not winner:
            info("No winner (dead heat), just removing the siege.")
            self._removeSiege(siege)
        else:
            siege['winner'] = winner['id']
            win = False
            siege['status'] = 'done'
            if winner['id'] != siege['suzerain']: # if winner == suzerain -- it defended, so no changes! CC.NPC_SUZERAIN_AUID case is also skiiped here
                if winner['id'] == siege['target']:
                    if siege['suzerain']: # winner breaks free
                        win = True
                    # else: # it was free and stays free
                else:
                    # it conqueres the target
                    win = True
                    now = int(time.time())
                    siege['status'] = 'locked'
                    siege['finish_tm'] = now
                    siege['end_time'] = now + self.settings.SIEGE_LOCK
            if win:
                if siege['status'] == 'locked':
                    self.locked.append(siege)
                    keep, losers = self._cleanLosers(siege)
                    if losers:
                        for guild in keep: # notify the winner, the target and it's suzerain about losers to remove them from lists on GS
                            for loser in losers:
                                self.addNotification(guild, {'cmd': 'leave', 'guildAuid': loser, '_id': siege['_id']})
                # not saving siege here - if it fails the service perform all processing after restart
                self.I.GUILD.winSiege(winner['id'], siege['_id'], callback=partial(self.onWinSent, siege=siege, winner_id=winner['id']))
            else: # current suzerain wins
                self.onWinSent({"skip": True, "ok": True}, siege, winner['id'])
        self.sendSiegeStats(siege)



    def onWinSent(self, response, siege, winner_id):
        if not response:
            err("onWinSent: EMPTY RESPONSE. Siege: %s", siege)
        else:
            if not response.get('skip'):
                info("onWinSent: response %s", response)
            if not response.get('ok'):
                err("Failed to send siege win result. Server %s. Error: %s: %s\nSiege: %s",
                    response.get('server', 'UNKNOWN'), response['ec'], response['error'], siege)
        # TODO продолжать пытаться посылать результаты! PF-92443

        if siege['status'] == 'locked' and response.get('lock_siege'):
            # the winner has enough vassals, wait him to free space or send 'refuse'
            sent = []
            rm_event = {'cmd': 'remove', '_id': siege['_id']}
            lock_event = {'cmd': 'lock', '_id': siege['_id'], 'end_time': siege['end_time']}
            # lock for the winner, the target and the target's suzerain, remove for others
            for part in siege["participants"]:
                if 'finished' in part:
                    self.addNotification(part["id"], rm_event)
                elif not 'leave' in part:
                    sent.append(part['id'])
                    self.addNotification(part["id"], lock_event)
            if siege['target'] not in sent:
                self.addNotification(siege['target'], lock_event)
            data = dict((k, siege[k]) for k in ('status', 'end_time', 'winner', 'finish_tm') if k in siege)
            self.I.DATA.update("sieges", "sieges", {"_id": siege["_id"]}, data, callback=partial(self.onLockSaved, siege=siege))
        else:
            info("onWinSent: removing a finished siege: %s", siege)
            self._removeSiege(siege, notNotify=(None if response.get('skip') else winner_id))
            siege['status'] = 'done'


    def processTimeOver(self, siege):
        "Notify the target, the suzerain and the winner. Send statistics and remove all siege data."
        info("processTimeOver: removing %s", siege)
        if siege['status'] != 'done':
            siege['status'] = 'done'
            if not self.checkVassalWin(siege):
                self._removeSiege(siege)
        del self.locked[0]


    def _removeSiege(self, siege, notNotify=None):
        "Notify the target, the suzerain and the winner. Send statistics and remove all siege data."
        self.notifyParticipants(siege, {'cmd': 'remove', '_id': siege['_id']}, exclusion=notNotify)
        self.I.DATA.remove("sieges", "sieges", {"_id": siege["_id"]}, partial(self.onSiegeRemoved, siege=siege))
        self._releaseSiegeRefs(siege)


    def onLockSaved(self, response, siege):
        info("onLockSaved: Siege remove response = %r", response)
        if not(response and response.get("r") is not None):
            err("Can't save siege lock. Error: %s:%s,%s\nSiege: %s", response.get('ex'), response.get('error'), response.get('ex'), siege)
            #TODO add retries PF-92445


    def onSiegeRemoved(self, response, siege):
        info("onSiegeRemoved: Siege remove response = %r", response)
        if not(response and response.get("r") is not None):
            err("Can't remove completely siege into mongo. Error: %s:%s,%s\nSiege: %s", response.get('ex'), response.get('error'), response.get('ex'), siege)
            #TODO add retries PF-92445


    def winnerChoice(self, target, choice, callback):
        info("winnerChoice: siege target %s, choice %s", target, choice)
        siege = self.getByTarget(target)
        if siege is None:
            return callback(self.popError())
        siege['status'] = 'done'
        if choice == 'refuse':
            self.I.STATS.addGuildInteraction(siege['winner'], target, GuildInteractionType.Decline, siege['_id'], int(time.time() - siege['end_time']))
        if not(choice == 'refuse' and self.checkVassalWin(siege)):
            rm_event = {'cmd': 'remove', '_id': siege['_id']}
            self.addNotification(siege['target'], rm_event, True)
            if siege['suzerain']:
                self.addNotification(siege['suzerain'], rm_event)
            self.I.DATA.remove("sieges", "sieges", {"_id": siege["_id"]}, partial(self.onSiegeRemoved, siege=siege))
            self._releaseSiegeRefs(siege)
        callback({"ok": 1})


    def checkVassalWin(self, siege):
        """Check if the target was a participant also and has the second score, after the winner.
        Used on winner's choice 'refuse' and in  processTimeOver."""
        max_score = 0
        max_score_id = None
        multiple = False
        participants = [p for p in siege['participants'] if not p.get('leave') or p.get('finished')]
        winner = siege.get('winner', 0) # no winneer if it's called from processTimeOver
        for p in participants:
            if p['id'] != winner:
                if p['score'] > max_score:
                    max_score = p['score']
                    max_score_id = p['id']
                    multiple = False
                elif p['score'] == max_score:
                    multiple = True
        if max_score_id == siege['target'] and siege['suzerain']:
            if multiple and min((p for p in participants if p['score'] == max_score), key=lambda p: p['start'])['id'] != siege['target']:
                #NOTE: the same logic is also implemented in _chooseWinner
                return False
            info("Vassal %s becomes free being the second in the siege %s after the winner who refused to accept this vassal", max_score_id, siege['_id'])
            self.I.GUILD.winSiege(max_score_id, siege['_id'], callback=partial(self.onWinSent, siege=siege, winner_id=max_score_id))
            return True
        return False


    def performDestroy(self, siege):
        "Destroy siege. Possible cases: target clan deletion or GM-Tool call."
        info("performDestroy: removing %s", siege)
        self.sendSiegeStats(siege)
        siege['status'] = 'done' # so it will be removed from it's current queue
        self.notifyParticipants(siege, {'cmd': 'destroy', '_id': siege['_id']})
        self.I.DATA.remove("sieges", "sieges", {"_id": siege["_id"]}, partial(self.onSiegeRemoved, siege=siege))
        self._releaseSiegeRefs(siege)


    def sendSiegeStats(self, siege):
        # find who've started the siege
        start_tm = siege['start_tm']
        guild = 0
        for part in siege['participants']:
            if part['start'] == start_tm:
                # it could be: the invider, the targets's suzerain or the target itself
                # possible cases:
                # ... part['id'] not in (siege['suzerain'], siege['target']) - the invider, the initiator
                # ... part['id'] == siege['target'] and siege['suzerain'] != 0 - a revolt! the initiator
                # ... part['id'] == siege['target'] and siege['suzerain'] == 0 - it has beed defending himself, so the initiator is another guild
                if part['id'] == siege['target']:
                    if siege['suzerain']:
                        guild = part
                        break
                elif part['id'] != siege['suzerain']:
                    guild = part
        if not guild:
            err("sendSiegeStats: Can't figure the siege initiator! Siege: %s", siege)
            guild = {"id": 0, "score": 0, 'rating': 0, 'start': 0, 'price': 0}
        siege_end = siege.get('finish_tm') or siege.get('end_time') or int(time.time())
        self.I.STATS.addGuildSiege(siege['_id'], guild['id'], guild['rating'], siege['target'], siege['target_rating'],
            siege['suzerain'], siege['suzerain_raiting'], guild['price'], siege['start_tm'], siege_end,
            participants=siege['participants'], winnerGuildId=siege.get('winner',0))


#TODO
#2. ? А не сделать ли список участников -- словарём?


def main():
    ITornadoServer.main(SiegeService)

if __name__ == "__main__":
    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = DEFAULT_PORT
    else:
        options["port"].set(DEFAULT_PORT)
    main()
