#!/usr/bin/env python
# -*- coding: utf-8 -*-

#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import functools

addModPath('cfg')

import tornado.options
from tornado.options import define, options
import tornado.httpserver
import tornado.ioloop
import tornado.web

import coord_cfg, cfg

import imemcache
import isql

from handlers import JsonHandler, SUBADDR_INTERNAL
from iwebserver import * #ITornadoServer, IWebServer, COORDINATOR_WS_ID, COORDINATOR_WS_NAME
from ifactory import IfaceFactory

from base.http_dumb import *
import ihttp

from isql import main_sql_callback
from imemcache import main_memc_callback
from iuserdata import IDataManager

from thrift_pw.serverinfo.serverinfo_handler import ServerInfoHandler
from thrift_pw.account_management.acc_management_coord_handler import BroadcastHandler, BroadcastMessageData

addModPath('thrift_pw/account_management/gen-py/AccountManagementAPI')
from AccountManagement import BroadcastMessage, BroadcastInfo
from modeldata.MultiStaticData import MultiStaticData
from config.MultiConfig import MultiConfig
import EC
import CC

##----------------------------------------------------------------------------------------------------------------------
PWSOC_COORD_VERSION_HI = 1
PWSOC_COORD_VERSION_LO = 120

## при логине сообщаем версию сервера (даже в случае неуспеха)
PWSOC_COORD_VERSION = "%d.%d" % (PWSOC_COORD_VERSION_HI, PWSOC_COORD_VERSION_LO)

##----------------------------------------------------------------------------------------------------------------------
## глобальные настройки (в т.ч. для syncSqlQuery)

define("ws_warmup_seconds", default=2, help="give web-server this many seconds to warm up before pestering it with /coord_check", type=int)
#define("tick", default=3, help="tick period, seconds", type=int)

SQL_CHECK_PERIOD = 5.0
WS_CHECK_PERIOD = 3.0
WS_NOTIFY_MIN_INTERVAL = 5.0 # notify other WSes about WS status no more often than once per WS_NOTIFY_MIN_INTERVAL

## хэш "активных серверов" [name] -> server_id, port...
servers = {}

def on_dump_response(response):
    info("response: %s", response)
    
def on_dump_send_response(response, to="", params={}):
    info("send to %r (params %s) response: %s", to, params, response)
        
##----------------------------------------------------------------------------------------------------------------------
# отвечать юзеру будем в JSON-формате, чтобы легко было парсить на стороне клиента
class CoordinatorHandler( JsonHandler ):

    ##_Interfaces = dict( SUBADDR=None, WS=None, MC=None, SQL=None )
    
    internalActionMap = {
        'ws_start':        "onWebServerStart",
        'ws_ready':        "onWebServerReady",
        'aux_ready':       "onAuxServerReady",
        'set_config':      "onSetConfigValues",  # динамически меняем одну из настроек конфига; по умолчанию апдейтится на все ws-ки
        'ws_dead':         "onWebServerDead",  # прибиваем активную запись WS, чтобы мы могли его перезапустить
        'get_stat':        "onGetClusterStat",  # отдаем общее число юзеров в кластере и т.п.
        'get_banned_ips':  "onGetBannedIp",  # отдаем общее число юзеров в кластере и т.п.

        'reload_multi_config': "onBroadcastReloadMultiConfig",  # рассылаем по всему кластеру команду reload_multi_config
        'update_multi_config': "onBroadcastUpdateMultiConfig",  # рассылаем по всему кластеру команду update_multi_config
        'clear_addr_info': "onBroadcastClearAddrInfo",  # рассылаем по всему кластеру команду clear_addr_info
        'toggle_maintenance': "onBroadcastMaintenance",  # рассылаем по всему кластеру команду toggle_maintenance
        'clear_dynamic_quests': "onClearDynamicQuests",  # удаляем динамические квесты из базы и с WS-ок, debug only
    }

    def onGetBannedIp(self):
        self.I.DATA.find(CC.BANNED_BY_IP, CC.BANNED_BY_IP, {}, callback=self.onGetBannedIpFromMongo)
        return

    def onGetBannedIpFromMongo(self, response):
        info("onGetBannedIpFromMongo reponse = %r", response)
        res = ""
        if response and response.get("r"):
            res = ";".join( str(ips["_id"]) for ips in response.get("r"))

        self.response["banned"] = res
        self.response["ok"] = 1
        self.fin()  # отправляем ответ

    ##------------------------------------------------------------------------------------------------------------------
    def onGetClusterStat(self):
        _byname = self.getParam("byname", None)
        _bytype = self.getParam("bytype", None)
        if _byname:
            fbyname = lambda d: {k: v for k, v in d.iteritems() if k == _byname}
            self.response["wsUserCounts"] = fbyname(self.I.WS.wsUserCounts)
            self.response["wsLocaleCounts"] = fbyname(self.I.WS.wsLocaleCounts)
            self.response["wsHttpActiveCounts"] = fbyname(self.I.WS.wsHttpActiveCounts)
            self.response["wsHttpQueuedCounts"] = fbyname(self.I.WS.wsHttpQueuedCounts)
            self.response["wsServicesCounts"] = fbyname(self.I.WS.wsServicesCounts)
        elif _bytype:
            types = ("thrift", "siege", "guild", "party", "friends", "login")
            fbytype = lambda d: {k: v for k, v in d.iteritems()}
            if _bytype in types:
                fbytype = lambda d: {k: v for k, v in d.iteritems() if _bytype in k}
            elif _bytype == "ws":
                fbytype = lambda d: {k: v for k, v in d.iteritems() if all(x not in k for x in types)}


            uc = fbytype(self.I.WS.wsUserCounts)
            self.response["wsUserCounts"] = uc
            self.response["wsLocaleCounts"] = fbytype(self.I.WS.wsLocaleCounts)
            self.response["wsHttpActiveCounts"] = fbytype(self.I.WS.wsHttpActiveCounts)
            self.response["wsHttpQueuedCounts"] = fbytype(self.I.WS.wsHttpQueuedCounts)
            self.response["wsType"] = _bytype
            self.response["wsTotalServersCount"] = len(filter(lambda k: self.I.WS.wsServicesCounts[k].get("on") > 0 , uc))
            self.response["wsServicesCounts"] = fbytype(self.I.WS.wsServicesCounts)
        else:
            self.response["totalUserCount"] = self.I.WS.totalUserCount
            self.response["wsUserCounts"] = self.I.WS.wsUserCounts
            self.response["wsLocaleCounts"] = self.I.WS.wsLocaleCounts

            # давайте посчитаем общее кол-во юзеров по локалям
            if self.I.WS.wsLocaleCounts:
                totalLocaleUsers = {}
                for server_id, localeCounts in self.I.WS.wsLocaleCounts.iteritems():
                    if localeCounts:
                        for locale, count in localeCounts.iteritems():
                            totalLocaleUsers[locale] = totalLocaleUsers.get(locale, 0) + count
                self.response["totalLocaleUsers"] = totalLocaleUsers
            self.response["wsHttpActiveCounts"] = self.I.WS.wsHttpActiveCounts
            self.response["wsHttpQueuedCounts"] = self.I.WS.wsHttpQueuedCounts
            self.response["wsTotalServersCount"] = len(filter(lambda k: self.I.WS.wsServicesCounts[k].get("on") > 0, self.I.WS.wsServicesCounts))
            self.response["wsServicesCounts"] = self.I.WS.wsServicesCounts
        self.response["ok"] = 1
        self.fin()  # отправляем ответ
        
    ##------------------------------------------------------------------------------------------------------------------
    def onBroadcastReloadMultiConfig(self):
        locale = self.getParam("locale", None)
        fromDisk = self.getParam("fromDisk", 0)
        self.I.WS.updateToPeerServices(
            dict(action='reload_locale_multi_config', locale=locale, fromDisk=fromDisk) if locale
            else dict(action='reload_multi_config', fromDisk=fromDisk)
        )
        self.response["ok"] = 1
        self.fin()  # отправляем ответ

    def onBroadcastUpdateMultiConfig(self):
        self.I.WS.updateToPeerServices(dict(action='reload_multi_config', update=1))
        self.response["ok"] = 1
        self.fin()  # отправляем ответ

    ##------------------------------------------------------------------------------------------------------------------
    def onBroadcastClearAddrInfo(self):
        self.I.WS.updateToPeerServices(dict(action="clear_addr_info"))
        self.response["ok"] = 1
        self.fin() # отправляем ответ

    ##------------------------------------------------------------------------------------------------------------------
    def onBroadcastMaintenance(self):
        _mode = self.getParam("mode")
        modes = {
            'normal' : 0,
            'pending' : 1,
            'ongoing' : 2,
        }
        mode = modes.get(_mode, None)
        if mode is not None:
            tm = self.getIntParam("tm")
            args = {
                'action' : 'toggle_maintenance',
                'mode' : mode,
            }
            if tm is not None:
                args['tm'] = tm
            self.I.WS.updateAllWebServers( args )
            self.response["ok"] = 1
        else:
            self.response["ok"] = 0
            self.response["em"] = 'Mode not defined (actual=%r)' % _mode
        self.fin() # отправляем ответ
        
    ##------------------------------------------------------------------------------------------------------------------
    def onSetConfigValues(self):
        json_values = self.getParam("json_values")
        info("onSetConfigValues: json %s" % (json_values))
        try:
            values = json_loads(json_values)
            info("onSetConfigValues: parsed %s" % values)
            
            # ставим значения локально
            for name, value in values.iteritems():
                if getattr(coord_cfg, name, None) is not None:
                    setattr(coord_cfg, name, value)
                else:
                    warn("no such name in coordinator config (%r)" % name)
                
            # разослать всем рабочим серверам
            args = {
                'action': 'set_config',
                'json_values': json_values,  # urlQuote больше не нужен, XHTTP.fetch и так делает
            }
            self.I.WS.updateAllWebServers(args)
            self.response["ok"] = 1
            
        except:
            catch()
            self.response["error"] = "can't parse json value (name %r)" % name
            warn("onSetConfigValue: can't parse json value for name %r" % name)
            
        self.fin()  # отправляем ответ
    
    ##------------------------------------------------------------------------------------------------------------------
    def onAuxServerReady(self):
        server_id = self.getIntParam("sid", None)
        _name = self.getParam("name")
        addr = self.getParam("addr", None)
        subscribe_ws = self.getIntParam("subscribe_ws", 0)
        subscribe_ca = self.getIntParam("subscribe_ca", 0)

        if server_id is None:
            server_id = self.I.WS.getNextServerId()

        name = '%s%d' % (_name, server_id)
        info("AuxServerReady (name=%s addr=%s subscribe_ws=%s subscribe_ca=%s)", name, addr, subscribe_ws, subscribe_ca)

        if subscribe_ws or subscribe_ca:        
            if not addr:
                self.response["error"] = "unknown server name";
                self.fin() # отправляем ответ
                return
            if subscribe_ws:
                self.I.WS.subscribeToWS(name, addr)
            if subscribe_ca:
                self.I.WS.subscribeToCheckActivity(name, addr)

        config = {}        
        self.response["sql_list"] = cfg.CLUSTER_SQL_CONFIG
        self.response["mongo_list"] = cfg.CLUSTER_MONGO_CONFIG

        self.I.WS.updateSpecificClusterParams( config )
        
        # отсылаем полный список peer-серверов
        self.response["config"] = config
        self.response["peers"] = servers
        self.response["sid"] = server_id
        self.response["ok"] = 1
        self.fin() # отправляем ответ
    
    ##-------------------------------------------------------------------------------------
    def onWebServerReady(self):
        info("onWebServerReady")
        name = self.getParam("name")
        
        if name and name.isalnum():
            if name in servers:
                acc = servers.get(name)
                acc["rdy"] = 1
                acc["new"] = 1
                acc["cur_users"] = 0
                
                # говорим, какой адрес прописан для этого "новичка" в нашем координаторском конфиге
                self.response["int_addr"] = acc["addr"]
                
                # апдейтим новенькому состояние кластера WS-серверов (с момента ready оно будет обновляться в периодических tick)
                _peers = servers.copy()
                _peers.pop(name, None) # кроме своей собственной инфы
                #_peer_keys = _peers.keys()
                for _name, _acc in _peers.items(): # также выкидываем всех кто не online
                    #acc = _peers.get(_name)
                    if _acc and not _acc.get("on"):
                        _peers.pop(_name)
                self.response["peers"] = _peers
                
                # апдейтим состояние компонентов PERSISTENCE-слоя (memcache, sql & mongo databases)
                self.response["mc_list"] = cfg.CLUSTER_MC_SERVER_LIST
                self.response["sql_list"] = cfg.CLUSTER_SQL_CONFIG
                self.response["mongo_list"] = cfg.CLUSTER_MONGO_CONFIG
            
                # override params here:
                self.I.WS.updateSpecificClusterParams( self.response )
                if not self.I.WS.coord_start:
                    self.I.WS.new_servers.append(str(acc["server_id"]))

                self.response["ok"] = 1
                return self.fin() # отправляем ответ
                
            elif (name[:7] == "friends") or (name[:5] == "party") or (name[:6] == "guilds") or (name[:5] == "siege"):
                # некоторым сервисам нужно отдавать список конфиг-параметров
                self.I.WS.updateSpecificClusterParams( self.response )
                
                self.response["ok"] = 1
                return self.fin() # отправляем ответ
                
            else:
                self.response["error"] = "unknown server name";
        else:
            self.response["error"] = "bad server name";
        #-- FAIL: отвечаем юзеру
        self.fin()            
                
                
    ##-------------------------------------------------------------------------------------
    def onWebServerStart(self):
        info("onWebServerStart")
        self.name = self.getParam("name")
        
        self.response["ver"] = PWSOC_COORD_VERSION
        
        if self.name and self.name.isalnum():
            if self.name in servers:
                self.acc = servers.get(self.name)
                
                if self.acc["on"]:
                    # и был живой? хмм
                    self.response["error"] = "this server name already up (duplicate web-server?)";
                else:
                    self.response["ok"] = 1
                    
                    server_id = self.I.WS.getNextServerId()
                    self.acc["server_id"] = server_id
                    self.response["sid"] = server_id
                    
                    self.I.WS.markWebServerOnline(self.name, self.acc)

                    # апдейт инфы о новом сервере лучше отложим до момента, когда новенький начнет слушать (будет готов принимать peer-сообщения)
            else:
                self.response["error"] = "unknown server name";
        else:
            self.response["error"] = "bad server name";
        #-- FAIL: отвечаем юзеру
        self.fin()            

    ##-------------------------------------------------------------------------------------
    def onWebServerDead(self):
        info("onWebServerDead")
        name = self.getParam("name")
        
        if name and name.isalnum():
            if name in servers:
                acc = servers.get( name )
                if acc and acc.on:
                    warn("onWebServerDead: Server %r DEAD: removing from databases" % name)
                    acc.on = 0
                    acc.rdy = 0
                    # надо удалить из всех известных БД
                    self.I.SQL.removeServer( name )
                    self.I.WS.updateWebServerState_One2All( name, acc ) # апдейтим всем инфу о состоянии peer-сервера
                    self.response["ok"] = 1
                else:
                    return self.fail("server not online", EC.BAD_PARAM)
            else:
                return self.fail("unknown server name", EC.BAD_PARAM)
        else:
            return self.fail("bad server name", EC.BAD_PARAM)
                
        self.fin()

    def onClearDynamicQuests(self):
        info("onClearDynamicQuests")
        args = {'action': 'clear_dynamic_quests'}
        self.I.WS.updateAllWebServers(args)
        self.response["ok"] = 1
        self.fin()

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------


class BaseCoordinatorServer( ITornadoServer, IServerStatistic ):
    """ mock social aggregator веб-сервер (с периодическим таймером) """
    
    ##_Interfaces = dict( HTTP=None, WS=None, MC=None, SQL=None, ISS=None )

    MAX_WS_SERVER_FAILS = 100 # после стольки фейлов подряд удаляем из кластера
    MAX_SQL_SERVER_FAILS = 5 # после стольки фейлов подряд сильно ругаемся (? а что еще делать со статик базами)

    _next_sql_check = 0
    _next_ws_check = 0
    
    # ----------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------
    #
    # OVERRIDES для дополнительных (game-specific) параметров 
    #
    
    _SPECIFIC_CONFIG_PARAMS = {}
    def __init__(self, **kwargs):
        ITornadoServer.__init__(self, **kwargs)
        self.coord_start = True
        self.new_servers = []

    # апдейтим статические настройки (адреса смежных компонентов и т.п.), вписывая их в словарь response {}
    def updateSpecificClusterParams(self, response):
        if self._SPECIFIC_CONFIG_PARAMS:
            for key, val in self._SPECIFIC_CONFIG_PARAMS.iteritems():
                response[key] = val

    # апдейтим статические настройки (адреса смежных компонентов и т.п.), вписывая их в формат HTTP GET
    def makeSpecificParamList(self):
        param_dict = dict( action="ip_list" )
        if self._SPECIFIC_CONFIG_PARAMS:
            param_dict["json_params"] = json_dumps(self._SPECIFIC_CONFIG_PARAMS)
        return param_dict
        
    # ----------------------------------------------------------------------------------------------
    # -- IServerStatistic --- 
    def getServers(self):
        return servers
        
    # ----------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------
    def tick(self):
        now = time.time()

        if now > self._next_ws_check:
            self.checkWebServersPeriodic()
            self._next_ws_check = now + WS_CHECK_PERIOD
        
        if options.sql != "none" and now > self._next_sql_check:
            self.checkSqlServers()
            self._next_sql_check = now + SQL_CHECK_PERIOD
            
        if self.wsUserCounts:
            self.totalUserCount = sum( self.wsUserCounts.values() )
            info("totalUserCount=%s (self.wsUserCounts: %s)", self.totalUserCount, self.wsUserCounts)
        
        if self.wsHttpActiveCounts:
            info("wsHttpActiveCounts: %s", self.wsHttpActiveCounts)
        if self.wsHttpQueuedCounts:
            info("wsHttpQueuedCounts: %s", self.wsHttpQueuedCounts)

        self.checkTopBuild()

    # -----------------------------------------------
    def initCounters(self):
        # вытаскиваем из доступных БД максимальный номер nextServerId (AUTO-INC)
        self.nextServerId = 1
        self.I.SQL.checkNextServerId( callback=self.updateNextServerId )
        
        self.sqlFails = IncDict() # будем считать кол-во фейлов (подряд) для каждого sql-сервера
        self.wsFails = IncDict() # будем считать кол-во фейлов (подряд) для каждого ws-сервера
        self.totalUserCount = 0
        self.calcTopBuild = 1
        self.wsUserCounts = {}        
        self.wsLocaleCounts = {}        
        self.wsHttpActiveCounts = {}
        self.wsServicesCounts = {}
        self.wsHttpQueuedCounts = {}        
        
    # -----------------------------------------------
    def initHandlers(self, application):
        info( "BaseCoordinatorServer initHandlers: HTTP=%s, SQL=%s" \
            % ( str(getattr(self, "HTTP", None)), str(getattr(self, "SQL", None)) ) )
            
        application.add_handlers( r"(.*)", [ 
            ( r"/x", CoordinatorHandler, dict( SUBADDR=SUBADDR_INTERNAL, I=self.I ) ),
        ] )

        self.initCounters()

        # опрашиваем WS-сервера по стартовому списку (вдруг это мы, координатор, перезапускаемся, а они уже онлайн)
        self.checkWebServersInit()
        
        # раздаем всем живым WS-серверам актуальные конфиги MC/SQL/PVX (если изменений в конфиге нет, CRC от списка серверов все равно совпадут и никаких изменений у WS не будет)
        self.updateAllWebServers( self.makeSqlList() )
        
        # дырка для override:
        self.updateAllWebServers( self.makeSpecificParamList() )
        
        self.peer_update_services = {}
        self.check_alive_services = {}
        self.service_shard = {}


    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.port = 8700
            options.server_id = COORDINATOR_WS_ID
            options.server_name = COORDINATOR_WS_NAME
            options.server_class = "base_coord"
        else:
            options["port"].set(8700)
            options["server_id"].set(COORDINATOR_WS_ID)
            options["server_name"].set(COORDINATOR_WS_NAME)
            options["server_class"].set("base_coord")

    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf ):
        iDict = ClassDict()

        # собственный конфиг координатора
        for name,server in coord_cfg.COORDINATOR_WS_SERVERS.iteritems():
            if name and server:
                servers[name] = acc = ClassDict(server)
                acc.cur_users = 0
                acc.coording = False
                acc.last_sent2all = 0
                acc.need_send = False
        info( "servers config: %s" % pretty(servers) )
        
        # апдейтим в собственный cfg настройки из coord_cfg
        classOf.updateLocalConfig()
        cfg.resetSqlServers( coord_cfg.COORDINATOR_SQL_CONFIG )
        
        # http-клиент, потенциально -- для запросов к facebook и zzima api
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient( max_clients=coord_cfg.COORDINATOR_HTTP_CURL_WORKERS ) 
        
        info( "SQL instances: " + str(cfg.CLUSTER_SQL_CONFIG) )
        iDict.SQL = IfaceFactory.makeSqlInterface( options.sql, cfg.CLUSTER_SQL_CONFIG, num_threads=cfg.SQL_THREADS )
        info( "SQL interface: " + str(iDict.SQL) )

        iDict.DATA = IfaceFactory.makeIDataInterface(
            options.data, coord_cfg.COORDINATOR_MONGO_CONFIG, iDict.SQL, num_threads=coord_cfg.COORDINATOR_MONGO_THREADS)
        info("DATA interface: " + str(iDict.DATA))

        # обычным веб-серверам требуется только оболочка DataManager для заворачивания JSON-данных
        iDict.MD = IDataManager() 
        info( "MD interface: " + str(iDict.MD) )
        
        request_limit = getattr(coord_cfg, "COORDINATOR_HTTP_REQUEST_LIMIT", 1000)
        info("using http request_limit=%s" % request_limit)
        iDict.XHTTP = ihttp.ILimitedAsyncHttpFetcher( iDict.HTTP, request_limit=request_limit ) # более удобный HTTP fetcher
        
        iDict.CHAT = IfaceFactory.makeIChatServerInterface( options.chat, coord_cfg.COORDINATOR_CHAT_SERVICES, HTTP=iDict.HTTP, request_limit=request_limit)

        iDict.Config = MultiConfig()

        iDict.SD = MultiStaticData("xdb/ExportedSocialData.xml", iDict.Config.getMainConfig(), loadLocales=False)
        try:
            iDict.Config.mainConfig.applyOverrides(iDict.SD.getMainSD())
            iDict.Config.applyLocaleOverrides(iDict.SD)
            # Заполним статические поля, которые можно перезаписыать из GMTools
            iDict.Config.fillStaticDataDependendValues(iDict.SD)
        except:
            catch()
        
        return iDict
        
    #----------------------------------------------------------------------------------------------------------
    #----------------------------------------------------------------------------------------------------------
    # startup handlers

    # return True if startup enviroment is bad
    @staticmethod
    def checkStartupFail():
        # проверяем, не слушает ли на нашем порту кто-то еще (защита от повторного запуска координатора)
        self_addr = "127.0.0.1:" + str(options.port)
        res = httpClientRequest( addr=self_addr, server="x", params="action=ws_start&name=_coordinator_" ) # SYNC ok
        if res and res.get("ok") != None:
            fatal( "DUPLICATE COORDINATOR: already listening on " + self_addr + "\n(reply was %s)" % str(res) )
            return True # обламываемся, уже запущена копия веб-сервера на этом порту
            
        print( "check startup environment: ok, port free (" + self_addr + ")" )
    
    @staticmethod
    def updateLocalConfig():
        prefix = "COORDINATOR_"
        for k,v in coord_cfg.__dict__.iteritems():
            ln = len(prefix)
            if isinstance(k, basestring) and k[ :ln ] == prefix:
                local_name = k[ ln: ]
                setattr( cfg, local_name, v )
        
    #----------------------------------------------------------------------------------------------------------
    #----------------------------------------------------------------------------------------------------------
    # helpers для работы со свойствами Work-Servers
    
    ##-------------------------------------------------------------------------------------
    ## name = server_name, acc = servers.get(server_name)
    def markWebServerOnline(self, name, acc):
        info("Server %r ALIVE: adding to databases", name)
        # не было такого сервера; надо его зарегать во всех известных БД
        self.I.SQL.addServer( acc["server_id"], name )
        
        acc.on = 1
        acc.ka = time.time()
        
    ##-------------------------------------------------------------------------------------
    def getNextServerId(self):
        self.nextServerId += 1
        return self.nextServerId
            
    ##-------------------------------------------------------------------------------------
    def updateNextServerId(self, sql_reply):
        log( "updateNextServerId reply:" + str(sql_reply) )
        if sql_reply:
            r = sql_reply.get("r")
            if r and len(r):
                auto_inc = tolong( r[0].get("Auto_increment") )
                info( "sql[%d] tbl_servers auto_inc received: %s" % (sql_reply.get("i", 0), str(auto_inc)) )
                self.nextServerId = max( self.nextServerId, auto_inc )

    def checkTopBuild(self):
        debug("checkTopBuild %r, %r == %r", self.coord_start, len(coord_cfg.COORDINATOR_WS_SERVERS), len(filter(lambda t: t[1].on, servers.iteritems())))
        if self.coord_start:
            if len(coord_cfg.COORDINATOR_WS_SERVERS) == len(filter(lambda t: t[1].on, servers.iteritems())):
                name, server = getFirstSortedPair( coord_cfg.COORDINATOR_WS_SERVERS )
                if name and server:
                    self.coord_start = False
                    debug("checkTopBuild %r %r", name, server)
                    #res = httpClientRequest( addr=server.get("addr"), server="x", params="action=calc_top_build" ) # SYNC ok
                    #log( "Server %r coord check reply: %s" % (name, res) )
                    _callback = functools.partial(self.onCalcTopBuild, server, False )
                    self.I.XHTTP.fetch( server.get("addr"), {"action": "calc_top_build"}, _callback )
        elif self.new_servers:
            name, server = getFirstSortedPair( coord_cfg.COORDINATOR_WS_SERVERS )
            if name and server:
                _callback = functools.partial(self.onCalcTopBuild, server, True )
                self.I.XHTTP.fetch( server.get("addr"), {"action": "calc_top_build"}, _callback )


    def onCalcTopBuild(self, server, isResend, response):
        debug("onCalcTopBuild %r, response: %r", server, response )
        if response and response.get("calcTopBuildsData") and isResend:
            servers = self.new_servers[:]
            if servers:
                for x in servers:
                    if x in self.new_servers:
                        self.new_servers.remove(x)
                _callback = functools.partial(self.onResendTopBuild, servers)
                self.I.XHTTP.fetch( server.get("addr"), {"action": "resend_top_build", "servers_id": ",".join(servers) }, _callback )

    def onResendTopBuild(self, servers, response):
        debug("onResendTopBuild servers: %r; response: %r ",servers, response)

    #----------------------------------------------------------------------------------------------------------
    #----------------------------------------------------------------------------------------------------------

    # при старте: СИНХРОННО пробегаемся по списку Work-Servers, смотрим, какие живые, какие сдохли
    def checkWebServersInit( self ):
        try:
            # пробегаемся по списку WS-серверов, обращаемся к каждому по http
            for name, acc in servers.iteritems():
                if acc:
                    # на запуске координатора (do_init) надо проверить все WS-сервера по списку (вдруг какой-то жив);
                    # потом периодически проверяем только живые (ready)
                    if acc.on:
                        res = httpClientRequest( addr=acc.addr, server="x", params="action=coord" ) # SYNC ok
                        log( "Server %r coord check reply: %s" % (name, res) )
                        
                        if res:
                            # живой
                            server_id = res.get("sid", 0)
                            
                            info( "Server %r[%s] coord init reply: %s", name, server_id, res)
                            acc.server_id = server_id # если рестартится координатор, server_id спрашиваем у живого WS
                            if self.nextServerId <= server_id:
                                self.nextServerId = server_id + 1
                                info("updated nextServerId=%d" % self.nextServerId)
                            
                            self.markWebServerOnline(name, acc)
                            acc.rdy = 1
                            
                        else:
                            # неживой, похоже
                            warn("checkWebServersInit Server %r DEAD: removing from databases", name)
                            acc.on = 0
                            acc.rdy = 0
                            # надо удалить из всех известных БД
                            self.I.SQL.removeServer( name )

            # при первой проверке (на запуске) нужно апдейтнуть всем серверам список "других живых peer-ов"
            for name, acc in servers.iteritems():
                if acc and acc.get("rdy"): # живой WS
                    self.updateWebServerState_One2All( name, acc )

        except:
            warn( printException( sys.exc_info() ) )

    # --------------------------------------------------------------------------------------------------------------------------------------
    def onCheckAliveWS(self, response, server_name=""):
        acc = servers.get(server_name)
        if acc:
            acc.coording = False
        if response:
            # живой
            self.wsFails.reset( server_name ) # ответили нормально -> обнуляем счетчик фейлов
            server_id = response.get("sid", 0)
            userCount = toint( response.get("userCount", 0) )
            self.wsUserCounts[server_name] = userCount
            self.wsLocaleCounts[server_name] = response.get("localeCounts", {})
            self.wsHttpActiveCounts[server_name] = toint( response.get("httpActive", 0) )
            self.wsHttpQueuedCounts[server_name] = toint( response.get("httpQueued", 0) )
            self.wsServicesCounts[server_name] = {"on": 1, "rdy": 1, "fail_count":0}
            if acc and acc.cur_users != userCount:
                acc.cur_users = userCount
                acc.need_send = True

            if acc and not acc.rdy:
                acc.rdy = 1
                acc.need_send = True

            info( "onCheckAliveWS: Server is alive (suid=%r[%d] user_count=%d)", server_name, server_id, userCount)

            if acc and acc.need_send:
                if acc.last_sent2all + WS_NOTIFY_MIN_INTERVAL < time.time():
                    self.updateWebServerState_One2All(server_name, acc)
                    acc.last_sent2all = time.time()
                    acc.need_send = False
            if response.get("whoami") and server_name in self.service_shard:
                # notify server about it's place among other same servers
                i, n = self.service_shard[server_name]
                self.I.XHTTP.fetch(self.check_alive_services[server_name], dict(action="youare", pos=i, total=n), None)
        else:
            # неживой, похоже
            fail_count = self.wsFails.inc(server_name) # увеличиваем счетчик фейлов данного WS
            warn("onCheckAliveWS: Server %r not responding to check! fail_count=%s", server_name, fail_count)

            if fail_count >= self.MAX_WS_SERVER_FAILS:
                warn( "Server %r DEAD! fail_count=%s", server_name, fail_count)
                if acc and acc.rdy:
                    acc.rdy = 0
                    acc.on = 0
                    self.wsServicesCounts[server_name] = {"on": acc.on, "rdy": acc.rdy, "fail_count":fail_count}
                    self.updateWebServerState_One2All( server_name, acc )
                #TODO: стукнуть в заббикс, что серваку плохо
            else:
                if acc and acc.rdy:
                    #acc.rdy = 0
                    self.wsServicesCounts[server_name] = {"on": acc.on, "rdy": acc.rdy, "fail_count":fail_count}
                    self.updateWebServerState_One2All( server_name, acc )

            
    # --------------------------------------------------------------------------------------------------------------------------------------
    # периодически АСИНХРОННО опрашиваем все рабочие сервера: живые, али как. 
    # если неживые - всячески ругаемся в логи и заббикс, но больше ничего не предпринимаем
    def checkWebServersPeriodic( self ):
        try:
            # пробегаемся по списку WS-серверов, обращаемся к каждому по http
            debug("checkWebServersPeriodic servers: %r", servers)
            for name, srv in servers.iteritems():
                if srv and srv.rdy:
                    if srv.get("new"):
                        # рассылаем пачку начальных апдейтов
                        self.updateWebServerState_One2All(name, srv) # апдейтим всем инфу о новом peer-сервере
                        srv.pop("new")

                    if not srv.coording:
                        debug("checkWebServersPeriodic coord for : %r", name)
                        _callback = functools.partial( self.onCheckAliveWS, server_name=name )
                        self.I.XHTTP.fetch( srv.addr, dict(action="coord"), _callback )
                        srv.coording = True

            debug("checkWebServersPeriodic check_alive_services: %r", self.check_alive_services )
            if self.check_alive_services:
                for svc_name, svc_addr in self.check_alive_services.iteritems():
                    debug("checkWebServersPeriodic check_alive for : %r", svc_name)
                    _callback = functools.partial( self.onCheckAliveWS, server_name=svc_name )
                    self.I.XHTTP.fetch( svc_addr, dict(action="check_alive"), _callback )
                        
        except:
            catch()
            
    # --------------------------------------------------------------------------------------------------------------------------------------
    # --------------------------------------------------------------------------------------------------------------------------------------
    # сообщаем всем Work-Servers некие данные 

    ## делаем строчку для http-вызова "update peer state"
    def makeWsStateAction( self, name, acc=None ):
        acc = acc or servers.get(name)
        if acc:
            action_dict = dict( action="peer", name=name, sid=acc.server_id, on=acc.on, addr=acc.addr, max_users=acc.max_users, cur_users=acc.cur_users, rdy=acc.rdy )
            return action_dict

    ## разослать новое состояние сервера всем остальным серверам (а также специально подписанным службам)
    def updateWebServerState_One2All( self, name, acc ):
        param_dict = self.makeWsStateAction(name, acc)
        self.updateToPeerServices( param_dict )

    ## разослать указанный набор аргументов всем сервисам, подписанным на peer_update 
    def updateToPeerServices(self, param_dict, except_server_name=None):
        self.updateAllWebServers( param_dict, except_server=except_server_name)
        if self.peer_update_services:
            for svc_name, svc_addr in self.peer_update_services.iteritems():
                self.I.XHTTP.fetch( svc_addr, param_dict, functools.partial( on_dump_send_response, to=svc_addr, params=param_dict) )
        
    ## разослать всем живым WS одинаковый http-action (вариант: всем, кроме указанного except_server) 
    def updateAllWebServers( self, param_dict, except_server=None ):
        info( "updateAllWebServers( %s )" % param_dict )
        peer_keys = servers.keys() or []
        if except_server:
            peer_keys.remove(except_server) 
        for name_peer in peer_keys: # сообщить всем, кроме этого сервера
            self.updateWebServer( name_peer, param_dict )

    def updateOneWebServer(self, param_dict):
        info("updateFirstWebServer( %s )" % param_dict)
        if len(servers.keys()):
            self.updateWebServer(servers.keys()[0], param_dict)

    ## послать конкретному WS некий http-action
    def updateWebServer( self, name_peer, param_dict ):
        acc_peer = servers.get(name_peer)
        if acc_peer and acc_peer.get("rdy"):
            self.I.XHTTP.fetch( acc_peer["addr"], param_dict, on_dump_response )
            #info( "Server %r action %r reply: %s" % (name_peer, action_string, res) )
            

    # ---------------------------------------------------------------------------------------------------------------------
    #--------------------------------------------------------------------------------------------------------------------------------------------------
    # SQL checks

    ## список SQL-серверов пакуем через json
    def makeSqlList(self):
        return dict( action="sql_list", list=json_dumps(cfg.CLUSTER_SQL_CONFIG), count=cfg.CLUSTER_SQL_SERVER_COUNT )
            
    def onMainSqlCheck(self, reply):
        try:
            if reply:
                sql_database_id = reply["i"]
                if not reply["r"]:
                    fail_count = self.sqlFails.inc( sql_database_id ) # увеличиваем счетчик фейлов для данной БД
                    warn( "sql[%d] FAIL = %d" % (sql_database_id, fail_count ) ) #~ warn( "sql[%d] FAIL = %d (reply %s)" % (sql_database_id, fail_count, str(reply)) ) 
                else:
                    ##log( "sql[%d] check ok:" % sql_database_id + str(reply["r"]) )
                    self.sqlFails.reset( sql_database_id ) # ответили нормально -> обнуляем счетчик фейлов
        except:
            pass

    ## пробегаемся по всем sql-серверам, выполняем по одной тестовой операции; в случае fail - накапливаем fail-count для указанного SQL-сервера
    def checkSqlServers(self):
        loop = tornado.ioloop.IOLoop.instance()
        for i in range(cfg.CLUSTER_SQL_SERVER_COUNT):
            loop.sql[i].addQuery( "SELECT COUNT(*) as cnt FROM tbl_servers", self.onMainSqlCheck )
                
        
    ##--------------------------------------------------------------------------------------------------------------------------------------
    ## список MongoDB-серверов пакуем через json
    def makeMongoList(self):
        return dict( action="mongo_list", list=json_dumps(cfg.CLUSTER_MONGO_CONFIG), count=cfg.CLUSTER_MONGO_SERVER_COUNT )
        
        

# --------------------------------------------------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------------------------------------------------
def dump_sql_reply( r, header="" ):
    info("%s: %s" % (header,r))
        
class CoordinatorServer( BaseCoordinatorServer ):
    """ mock social aggregator веб-сервер (с периодическим таймером) """
    
    ##_Interfaces = dict( HTTP=None, WS=None, MC=None, SQL=None, ISS=None )
    _THRIFT_SERVICES = { 
        "serverinfo": ServerInfoHandler, 
        "account_management": BroadcastHandler,
    }

    MAX_MC_SERVER_FAILS = 20 # после стольки фейлов подряд удаляем из кластера
    MAX_WS_SERVER_FAILS = 100 # после стольки фейлов подряд удаляем из кластера
    MAX_SQL_SERVER_FAILS = 5 # после стольки фейлов подряд сильно ругаемся (? а что еще делать со статик базами)
    
    # ----------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------
    def tick(self):
        super(CoordinatorServer, self).tick()
        self.tickBroadcasts()
                
        
    # -----------------------------------------------
    def initHandlers(self, application):
        info( "CoordinatorServer initHandlers: HTTP=%s, MC=%s, SQL=%s" \
            % ( str(getattr(self, "HTTP", None)), str(getattr(self, "MC", None)), str(getattr(self, "SQL", None)) ) )
            
        from thrift_handler import ThriftHandler
        application.add_handlers( r"(.*)", [ 
            ( r"/x", CoordinatorHandler, dict( SUBADDR=SUBADDR_INTERNAL, I=self.I ) ),
            ( r"/thrift", ThriftHandler, dict( I=self.I, SERVICES=self._THRIFT_SERVICES ) ),
        ] )

        # список дополнительных сервисов, которые тоже будем пинговать насчет check_alive
        self.check_alive_services = {}
        self.service_shard = {}
        self.peer_update_services = {} # список дополнительных сервисов, которым будем рассылать изменения в составе peers

        self.subscribeToWS("thrift", getattr(coord_cfg, "COORDINATOR_THRIFT_AGENT_URL", ""))
        for i,addr in enumerate(coord_cfg.COORDINATOR_FRIEND_SERVICES):
            sname = "friends%d" % (i+1)
            self.subscribeToCheckActivity(sname, addr)
            self.subscribeToWS(sname, addr)
        for i,addr in enumerate(coord_cfg.COORDINATOR_PARTY_SERVICES):
            sname = "party%d" % (i+1)
            self.subscribeToCheckActivity(sname, addr)
            self.subscribeToWS(sname, addr)
        for i,addr in enumerate(coord_cfg.COORDINATOR_GUILD_SERVICES):
            sname = "guilds%d" % (i+1)
            self.subscribeToCheckActivity(sname, addr)
            self.subscribeToWS(sname, addr)
        for i,addr in enumerate(coord_cfg.COORDINATOR_SIEGE_SERVICES):
            sname = "siege%d" % (i+1)
            self.subscribeToCheckActivity(sname, addr)
            self.subscribeToWS(sname, addr)
            self.service_shard[sname] = (i, len(coord_cfg.COORDINATOR_SIEGE_SERVICES))
            
        self.initCounters()
        
        #TODO: вытаскиваем из БД список бродкастов
        self.broadcasts = {}
        self.I.SQL.getBroadcastList( callback=self.onGetBroadcastList )
        
        self.mcFails = IncDict() # будем считать кол-во фейлов (подряд) для каждого mc-сервера, и при превышении MAX_MC_SERVER_FAILS удалять сервер из CLUSTER_MC_SERVER_LIST[]
        
        # опрашиваем WS-сервера по стартовому списку (вдруг это мы, координатор, перезапускаемся, а они уже онлайн)
        self.checkWebServersInit()
        
        # раздаем всем живым WS-серверам актуальные конфиги MC/SQL/PVX (если изменений в конфиге нет, CRC от списка серверов все равно совпадут и никаких изменений у WS не будет)
        self.updateAllWebServers( self.makeMcList() )
        self.updateAllWebServers( self.makeSqlList() )
        self.updateAllWebServers( self.makeMongoList() )
        
        # дырка для override:
        self.updateAllWebServers( self.makeSpecificParamList() )

        # -----------------------------------------------
    def subscribeToWS(self, name, addr):
        info('Subscribed to ws notification (name=%r addr=%r)' % (name, addr))
        self._subscribe(self.peer_update_services, name, addr)

    def _subscribe(self, lst, name, addr):
        to_delete = []
        for pname, paddr in lst.items():
            if paddr == addr:
                info('Found old instance on the same address, removing (name=%s)' % pname)
                to_delete.append(pname)
        for pname in to_delete:
            del lst[pname]
        lst[name] = addr

    def subscribeToCheckActivity(self, name, addr):
        info('Subscribed to check activity (name=%r addr=%r)' % (name, addr))
        self._subscribe(self.check_alive_services, name, addr)

    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.port = 8700
            options.server_id = COORDINATOR_WS_ID
            options.server_name = COORDINATOR_WS_NAME
            options.server_class = "coord"
        else:
            options["port"].set(8700)
            options["server_id"].set(COORDINATOR_WS_ID)
            options["server_name"].set(COORDINATOR_WS_NAME)
            options["server_class"].set("coord")

    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf ):
        iDict = BaseCoordinatorServer.initInterfaces( classOf )
        
        cfg.resetMcServers( coord_cfg.COORDINATOR_MC_SERVER_LIST )
        cfg.resetMongoServers( coord_cfg.COORDINATOR_MONGO_CONFIG )       

        iDict.MC = IfaceFactory.makeMcInterface( options.mc, cfg.CLUSTER_MC_SERVER_LIST, num_threads=cfg.MEMCACHE_THREADS )
        info( "MC interface: " + str(iDict.MC) )
        
        return iDict
        
    #----------------------------------------------------------------------------------------------------------
    #----------------------------------------------------------------------------------------------------------
    # BROADCASTS

    def editBroadcast(self, editInfo):
        if editInfo.Id in self.broadcasts:
            msgData = self.broadcasts[ editInfo.Id ]
            #editInfo.EnabledNow = False # при любом редактировании сбрасываем статус "активно рассылается"
            msgData.message = editInfo
            self.updatePersistentBroadcast( msgData )
            return True
        return False

    def deleteBroadcast(self, msgId):
        if msgId in self.broadcasts:
            self.broadcasts.pop( msgId )
            self.I.SQL.deleteBroadcast( msgId, callback=functools.partial(dump_sql_reply, header="DeleteBroadcast") )
            return True
        return False    

    def addBroadcast(self, createInfo):
        msgId = self.I.WS.nextUid("broadcast")
        createInfo.Id = msgId 
        msgData = BroadcastMessageData( msgId, createInfo )
        self.broadcasts[ msgId ] = msgData
        msgText = msgData.toJson()
        self.I.SQL.addBroadcast( msgId, msgText, createInfo.Title, 
            createInfo.TimeStart, createInfo.TimeFinish, createInfo.Interval, 
            createInfo.EnabledNow, callback=functools.partial(dump_sql_reply, header="CreateBroadcast") )
        return msgData

    # --------------------------------------------------------
    # получаем из mysql список broadcast message defs, наполняем self.broadcasts = {} объектами BroadcastMessage
    def onGetBroadcastList( self, sql_reply ):
        info("onGetBroadcastList sql_reply: %s" % sql_reply)
        if sql_reply and sql_reply.get("r"):
            for line in sql_reply.get("r", []):
                if line.id:
                    broad = BroadcastInfo( Id=line.id, Title=utf8convert(line.title), Messages=[], 
                        TimeStart=line.tstart, TimeFinish=line.tfin, Interval=line.interval, 
                        EnabledNow=False ) # флаг enabled принудительно сбрасываем, рассылку начинаем только по команде StartRotation от GM-а

                    data = BroadcastMessageData( line.id, broad, line.tlastsent )
                    data.fromJson(utf8convert(line.message))
                    self.broadcasts[ broad.Id ] = data
                    self.guids._upd_max( "broadcast", broad.Id )
                    info( "onGetBroadcastList: added persistent broadcast: %s, new nextUid:%s",broad, self.guids.pick("broadcast"))
                
                
    # --------------------------------------------------------
    def tickBroadcasts(self):
        sorted_keys = sorted( self.broadcasts.keys() )
        if sorted_keys:
            now = time.time()
            info( "tickBroadcasts: now %d, broadcasts count %d" % (toint(now), len(sorted_keys)) )
            for msgId in sorted_keys:
                data = self.broadcasts[msgId]
                message = data.message
                if getattr(coord_cfg, "DUMP_BROADCAST_CHECKS", 0):
                    debug( "- check broadcast: now=%d, tLastSent=%d, message=%s", now, data.tLastSent, message )
                if message.EnabledNow:
                    # проверяем граничные условия
                    if (message.TimeStart <= 0) or (now > message.TimeStart):
                        if (message.Interval <= 0) or (now > data.tLastSent + message.Interval):
                            # случайно не закончился период рассылки?
                            _callback = functools.partial( dump_sql_reply, header="updatePersistentBroadcast" )
                            if (now > message.TimeFinish) and (data.tLastSent):
                                info( "tickBroadcasts: message expired (%s), now: %d" % (message, toint(now)) )
                                message.EnabledNow = False
                                self.updatePersistentBroadcast( data, _callback )
                            else:
                                info( "tickBroadcasts: sending message (%s)" % (message) )
                                data.tLastSent = toint(now)
                                
                                # urlQuote больше не нужен, XHTTP.fetch и так делает 
                                for loc in message.Messages:
                                    self.I.CHAT.broadcast( loc.Text, loc.Locale, on_dump_response )
                                
                                if message.Interval <= 0: # одноразовое
                                    message.EnabledNow = False
                                self.updatePersistentBroadcast( data, _callback )
                                    
                            
    # --------------------------------------------------------
    def updatePersistentBroadcast( self, msgData, callback=None ):
        editMessage = msgData.message
        self.I.SQL.editBroadcast( editMessage.Id, msgData.toJson(), editMessage.Title, 
            editMessage.TimeStart, editMessage.TimeFinish, editMessage.Interval, 
            editMessage.EnabledNow, msgData.tLastSent, 
            callback=callback )
    
    #----------------------------------------------------------------------------------------------------------
    #----------------------------------------------------------------------------------------------------------


    #------------------------------------------------------------------------------------------------------------------
    #------------------------------------------------------------------------------------------------------------------
    # Memcache checks
            
    def main_mc_check( self, reply ):
        try:
            if reply:
                key, mc_server = reply["a"]
                if not reply["r"]:
                    fail_count = self.mcFails.inc( mc_server ) # увеличиваем счетчик фейлов для данного mc-сервера
                    warn( "mc FAIL [%s] = %d (reply %s)" % (mc_server, fail_count, str(reply)) ) 
                else:
                    ##log( "mc [%s] check ok" % mc_server )
                    self.mcFails.reset( mc_server ) # ответили нормально -> обнуляем счетчик фейлов
        except:
            pass
            
    ## строчка со списком живых MC-серверов
    def makeMcList(self):
        return dict( action="mc_list", list=json_dumps(cfg.CLUSTER_MC_SERVER_LIST), count=cfg.CLUSTER_MC_SERVER_COUNT )
        
    ## пробегаемся по всем MC-серверам, выполняем по одной set-операции; в случае fail - накапливаем fail-count для указанного MC-сервера
    def checkMcServers(self):
        pass
        #~ i = 0
        #~ while i < cfg.CLUSTER_MC_SERVER_COUNT:
            #~ mc_server = cfg.CLUSTER_MC_SERVER_LIST[i]
            
            #~ if self.mcFails.pick(mc_server) >= self.MAX_MC_SERVER_FAILS:
                #~ # все, пора на свалку
                #~ warn( "DELETING MC SERVER %s" % mc_server)
                
                #~ del cfg.CLUSTER_MC_SERVER_LIST[i]
                #~ cfg.CLUSTER_MC_SERVER_COUNT -= 1
                #~ cfg.resetMcServers() # crc32(CLUSTER_MC_SERVER_LIST)
                
                #~ # теперь нужно раздать всем WS-серверам новый список MC-шек
                #~ self.updateAllWebServers( self.makeMcList() )
                
            #~ else:
                #~ server_key = (i, "__coord__")
                #~ ## пока проще оставить прямой вызов?
                #~ self.I.MC.addQuery( "set", (server_key, mc_server), self.main_mc_check )
                #~ i += 1


# ---------------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------------


# отличается от базового координатора только набором "специфических конфиг-параметров", передаваемых work-серверам
class PwCoordinatorServer( CoordinatorServer ):
    
    _SPECIFIC_CONFIG_PARAMS = {
        "pvx_login": coord_cfg.COORDINATOR_PVX_LOGIN_ADDRESS,
        "zz_addr": coord_cfg.COORDINATOR_ZZIMA_WSDL,
        "zz_svc_name": coord_cfg.COORDINATOR_ZZIMA_SERVICE_NAME,
        "zz_pay_sys": coord_cfg.COORDINATOR_ZZIMA_PAYMENT_SYSTEM,
        "zz_steam_pay_sys": coord_cfg.COORDINATOR_ZZIMA_STEAM_PAYMENT_SYSTEM,
        "zz_aeria_pay_sys": coord_cfg.COORDINATOR_ZZIMA_AERIA_PAYMENT_SYSTEM,
        "zz_arcgames_pay_sys": coord_cfg.COORDINATOR_ZZIMA_ARCGAMES_PAYMENT_SYSTEM,
        "zz_zzima_pay_sys": coord_cfg.COORDINATOR_ZZIMA_ZZIMACOM_PAYMENT_SYSTEM,
        "agg_bill_prefix": coord_cfg.COORDINATOR_AGG_BILLING_PREFIX,
        "zz_api": coord_cfg.COORDINATOR_ZZIMA_API_URL,
        "zz_key": coord_cfg.COORDINATOR_ZZIMA_API_KEY,
        "zz_sec": coord_cfg.COORDINATOR_ZZIMA_API_SECRET,
        "soc_agg": coord_cfg.COORDINATOR_SOCIAL_AGGREGATOR_ADDRESS,
        "pers_serv": coord_cfg.COORDINATOR_PERSON_SERVER_ADDRESS,
        "friends_svc": coord_cfg.COORDINATOR_FRIEND_SERVICES,
        "party_svc": coord_cfg.COORDINATOR_PARTY_SERVICES,
        "guilds_svc": coord_cfg.COORDINATOR_GUILD_SERVICES,
        "siege_svc" : coord_cfg.COORDINATOR_SIEGE_SERVICES,
        "chat_serv": coord_cfg.COORDINATOR_CHAT_SERVICES,
        "stats_agent": coord_cfg.COORDINATOR_STATS_AGENT_URL,
        "stats": coord_cfg.COORDINATOR_STATS_URL,
        "fb_restrict": coord_cfg.COORDINATOR_RESTRICT_FACEBOOK_USERS,
        "loc_restrict": coord_cfg.COORDINATOR_RESTRICT_LOCATIONS,
        "loc_allowed": coord_cfg.COORDINATOR_RESTRICT_LOCATIONS_ALLOWED,
        "can_reconnect": coord_cfg.COORDINATOR_PVX_CAN_RECONNECT,
        "balancer_ext": coord_cfg.COORDINATOR_BALANCER_EXTERNAL,
        "balancer_int": coord_cfg.COORDINATOR_BALANCER_INTERNAL,
        "bill_chk_period": coord_cfg.COORDINATOR_BILLING_CHECK_BALANCE_PERIOD,
        "pwc_activ_term": coord_cfg.COORDINATOR_PWC_ACTIVATION_TERM,
        "pwc_retry_term": coord_cfg.COORDINATOR_PWC_RETRY_CONFIRM_PERIOD,
        "pwc_reset_term": coord_cfg.COORDINATOR_PWC_RESET_PWD_PERIOD,
        "pwc_info_url": coord_cfg.COORDINATOR_PWC_INFO_URL,
        "curl_wrk": coord_cfg.COORDINATOR_HTTP_CURL_WORKERS, 
        "curl_conn": coord_cfg.COORDINATOR_HTTP_CURL_CONNECTIONS, 
        "req_limit": coord_cfg.COORDINATOR_HTTP_REQUEST_LIMIT,
        "bill_trd": coord_cfg.COORDINATOR_ZZIMA_BILLING_THREADS, 
        "sql_trd": coord_cfg.COORDINATOR_SQL_THREADS, 
        "mc_trd": coord_cfg.COORDINATOR_MEMCACHE_THREADS, 
        "mongo_trd": coord_cfg.COORDINATOR_MONGO_THREADS,
        "smtp_trd": coord_cfg.COORDINATOR_PWC_SMTP_THREADS, 
        "serial_trd": coord_cfg.COORDINATOR_SERIAL_MODEL_DATA_THREADS, 
        "pvx_locs": coord_cfg.COORDINATOR_MATCHMAKER_LOCALES,
        "pvx_def_loc": coord_cfg.COORDINATOR_MATCHMAKER_DEFAULT_LOCALE,
        "mm_valid_sec": coord_cfg.COORDINATOR_MM_VALIDATION_SECONDS,
        "mm_gateway_fails": coord_cfg.COORDINATOR_MM_MAX_INDIVIDUAL_GATEWAY_FAILS,
        "sex_url": coord_cfg.COORDINATOR_SOCIAL_EXCHANGE_URL,
        "mirror_cfg": coord_cfg.COORDINATOR_MIRROR_QUEUE_CONFIG,
        "mirror_trd": coord_cfg.COORDINATOR_MIRROR_QUEUE_THREADS,
        "export_cfg": coord_cfg.COORDINATOR_MIRROR_EXPORT_CONFIG,
        "export_trd": coord_cfg.COORDINATOR_MIRROR_EXPORT_THREADS,
        "mongo_cfg": coord_cfg.COORDINATOR_MONGO_CONFIG,
        "events": coord_cfg.COORDINATOR_EVENT_SERVICES,
        "guild_icons_upload_url": coord_cfg.GUILD_ICONS_UPLOAD_URL_PATTERN,
        "sign_check": coord_cfg.COORDINATOR_STRICT_SIGN_CHECK,
        "client_revs": coord_cfg.COORDINATOR_CLIENT_REVISIONS,
        "steam_appid": coord_cfg.COORDINATOR_STEAM_APPID,
        "steam_appkey": coord_cfg.COORDINATOR_STEAM_APPKEY,
        "steam_url": coord_cfg.COORDINATOR_STEAM_URL,
        "steam_sandbox_mode": coord_cfg.COORDINATOR_STEAM_SANDBOX_MODE,
        "steam_billing_base": coord_cfg.COORDINATOR_STEAM_BILLING_BASE,
        "steam_billing_offset": coord_cfg.COORDINATOR_STEAM_BILLING_OFFSET,
        "steam_payments_url": coord_cfg.COORDINATOR_STEAM_PAYMENTS_URL,
        "steam_payments_secret": coord_cfg.COORDINATOR_STEAM_PAYMENTS_SECRET,
        "aeria_payments_url": coord_cfg.COORDINATOR_AERIA_PAYMENTS_URL,
        "aeria_payments_secret": coord_cfg.COORDINATOR_AERIA_PAYMENTS_SECRET,
        "arcgames_payments_url": coord_cfg.COORDINATOR_ARCGAMES_PAYMENTS_URL,
        "arcgames_payments_secret": coord_cfg.COORDINATOR_ARCGAMES_PAYMENTS_SECRET,
        "zzima_payments_url": coord_cfg.COORDINATOR_ZZIMACOM_PAYMENTS_URL,
        "zzima_payments_secret": coord_cfg.COORDINATOR_ZZIMACOM_PAYMENTS_SECRET,

        "skip_limit_check": coord_cfg.COORDINATOR_SKIP_LIMIT_CHECK,
        "dlcs_info": coord_cfg.COORDINATOR_DLCS,
        "muid_to_dlcs": coord_cfg.COORDINATOR_MUID_TO_DLCS,
        "deploy_name": coord_cfg.COORDINATOR_DEPLOY_NAME,

        # aeria dependent params:
        "aeria_is_test": coord_cfg.COORDINATOR_AERIA_IS_TEST,
        "aeria_url": coord_cfg.COORDINATOR_AERIA_URL,
        "aeria_appid": coord_cfg.COORDINATOR_AERIA_APPID,
        "aeria_appkey": coord_cfg.COORDINATOR_AERIA_KEY,

        # arcgames dependent params:
        "arcgames_is_test": coord_cfg.COORDINATOR_ARCGAMES_IS_TEST,
        "arcgames_url": coord_cfg.COORDINATOR_ARCGAMES_URL,
        "arcgames_appid": coord_cfg.COORDINATOR_ARCGAMES_APPID,
        "arcgames_appabbr": coord_cfg.COORDINATOR_ARCGAMES_APPABBR,
        "arcgames_appkey": coord_cfg.COORDINATOR_ARCGAMES_APP_SECRET,
        "arcgames_billing_url": coord_cfg.COORDINATOR_ARCGAMES_BILLING_URL,
        "arcgames_zoneid": coord_cfg.COORDINATOR_ARCGAMES_ZONEID,

        # zzima dependent params:
        "zzimacom_is_test": coord_cfg.COORDINATOR_ZZIMACOM_IS_TEST,
        "zzimacom_url": coord_cfg.COORDINATOR_ZZIMACOM_URL,
        "zzimacom_service_name": coord_cfg.COORDINATOR_ZZIMACOM_SERVICE_NAME,
        "zzimacom_payment_system": coord_cfg.COORDINATOR_ZZIMACOM_PAYMENT_SYSTEM,

        "tournament_server": coord_cfg.COORDINATOR_TOURNAMENT_SERVER,
        "tournament_server_addr": coord_cfg.COORDINATOR_TOURNAMENT_SERVER_ADDR,
        "tournament_xserver_addr": coord_cfg.COORDINATOR_TOURNAMENT_XSERVER_ADDR,
        "billing_reserve_enabled": coord_cfg.COORDINATOR_BILLING_RESERVE_ENABLED,
        "tournament_spectator_auids": coord_cfg.COORDINATOR_TOURNAMENT_SPECTATOR_AUIDS,
        "tournament_apply_results": coord_cfg.COORDINATOR_TOURNAMENT_APPLY_RESULTS,
        "geo_data_path": coord_cfg.COORDINATOR_GEO_DATA_PATH,
        "billing_merge_disable_ps": coord_cfg.COORDINATOR_BILLING_MERGE_DISABLED_PS,
        "redis_config" : coord_cfg.COORDINATOR_REDIS_CONFIG,
        "meta_muids" : coord_cfg.COORDINATOR_META_MUIDS,
        "mm_msv_locale": coord_cfg.COORDINATOR_MATCHMAKER_MSV_LOCALE,
        "mm_msv_geolocation": coord_cfg.COORDINATOR_MATCHMAKER_MSV_GEOLOCATION,
    }


if __name__ == "__main__":
    ITornadoServer.main( PwCoordinatorServer )
