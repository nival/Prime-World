# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json, re, hashlib, urllib, httplib, logging

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)
_addPath('tornado')

import tornado.options
#import tornado.web
#import tornado.httpclient

from tornado.options import define, options
from handlers import *
from ifactory import IfaceFactory

##----------------------------------------------------------------------------------------------------------------------
## служебные web handlers типа Login импортируем отдельно
from ext_main.login import LoginAction

## -------------------------------------------------------------------------------------------------------------------------------------
## -------------------------------------------------------------------------------------------------------------------------------------



class WebJsonHandler( JsonHandler ):
    """ реальный обработчик команд главного рабочего сервера (WebServer) """
    
    internalActionMap = {
        'peer':          PeerServerStatusAction,
        # внутрикластерные команды; закрыты для внешних клиентов
        'coord':         "onCoordinatorCheck",
        'get_stat':       "onCoordinatorCheck",  #добавил обработчик для того, чтобы был единый интерфейс получения статистики по сервисам
        ##'peer':          "onPeerServerStatus",
        'mc_list':       "onCoordinatorMcList",
        'sql_list':      "onCoordinatorSqlList",
        'mongo_list':    "onCoordinatorMongoList",
        'ip_list':       "onCoordinatorIpAddrList",
        'notify':        "onPeerNotify",
        'shutdown':      "onShutdown",
        'toggle_maintenance': "onMaintenance",
    }
    
    ## _Interfaces = dict( SUBADDR=None, MC=None, SQL=None, HTTP=None, WS=None )
    
    ##-------------------------------------------------------------------------------------
    def __init__(self, application, request, **kwargs):
        ## info( "WJH _Interfaces:" + str(self._Interfaces) )
        ## info( "internalActionMap:" + str(self.internalActionMap) )
        JsonHandler.__init__(self, application, request, **kwargs)


    ##-------------------------------------------------------------------------------------
    def onShutdown(self):
        bad_warn( 'action=shutdown received: initiating shutdown' )
        reloginUsers = self.getParam("relogin", 0) # "разгрузочный shutdown": по возможности перекинуть юзеров на соседние WS
        self.I.WS.fadeoutServer( reloginUsers=reloginUsers )
        self.response["ok"] = 1
        self.fin()

    ##-------------------------------------------------------------------------------------
    def onMaintenance(self):
        mode = self.getIntParam("mode") 
        tm = self.getIntParam("tm", None) 
        self.I.WS.toggleMaintenance(mode, tm)
        self.response["ok"] = 1
        self.fin()

    ##-------------------------------------------------------------------------------------
    ## извещение от peer-сервера: если в запросе есть имя user, отвечаем, есть ли у нас такой (-> uid)
    def onPeerNotify(self):
        ws = toint( self.getParam("ws") )
        info( "onPeerNotify( from ws %d )" % ws )
        
        user = self.getParam("user")
        uid = logins.get(user.lower(), 0)
        if uid:
            self.response["ok"] = 1 
            self.response["uid"] = uid
            
        self.fin()
        

    ##-------------------------------------------------------------------------------------
    ## COORDINATOR
    ##-------------------------------------------------------------------------------------
    ## периодически координатор спрашивает, живы ли мы
    def onCoordinatorCheck(self):
        log("onCoordinatorCheck")
        self.response["userCount"] = self.I.WS.CCU.userCount
        self.response["localeCounts"] = self.I.WS.CCU.localeCounts
        self.response["ok"] = 1 # живы, живы, не сумлевайтесь
        self.response["sid"] = options.server_id
        self.fin()


    ##-------------------------------------------------------------------------------------
    ## координатор сообщает об изменении набора memcache-серверов
    def onCoordinatorMcList(self):
        ## OBSOLETE
        self.response["ok"] = 1
        self.fin()
    

    ##-------------------------------------------------------------------------------------
    ## координатор сообщает об изменении набора sql-серверов (баз)
    def onCoordinatorSqlList(self):
        json_param = self.getParam("list")
        if json_param and len(json_param):
            sql_options_list = json_loads(json_param)
        else:
            sql_options_list = []
        count = toint( self.getParam("count") )
        
        info( "onCoordinatorSqlList( list=%s, count=%d )" % (str(sql_options_list), count) )
        
        if len(sql_options_list) == count:
            prev_crc = cfg.CLUSTER_SQL_SERVER_CRC32[0]
            cfg.resetSqlServers( sql_options_list )
            
            if prev_crc != cfg.CLUSTER_SQL_SERVER_CRC32[0]:
                info( "onCoordinatorSqlList: new sql base list!" )
                # набор серверов/баз поменялся; надо мягко завершить работу со старыми запросами, и заново инициализировать набор ioloop.sql[] для работы с новыми запросами
                self.I.WS.I.SQL.fadeout() # постепенно закрываем лавочку (ждем когда очередь запросов полностью разберут, и тогда прибиваем thread pool)
                self.I.WS.SQL = IfaceFactory.makeSqlInterface( options.sql, sql_options_list )
                self.response["reset"] = 1
            
            self.response["ok"] = 1
        else:
            err("bad sql_list count!")
            
        self.fin()


    ##-------------------------------------------------------------------------------------
    ## координатор сообщает об изменении набора mongo-серверов (баз)
    def onCoordinatorMongoList(self):
        json_param = self.getParam("list")
        if json_param and len(json_param):
            mongo_options_list = json_loads(json_param)
        else:
            mongo_options_list = []
        count = toint( self.getParam("count") )
        
        info( "onCoordinatorMongoList( list=%s, count=%d )" % (str(mongo_options_list), count) )
        
        if len(mongo_options_list) == count:
            prev_crc = cfg.CLUSTER_MONGO_SERVER_CRC32[0]
            cfg.resetMongoServers( mongo_options_list )
            
            if prev_crc != cfg.CLUSTER_MONGO_SERVER_CRC32[0]:
                info( "onCoordinatorMongoList: new mongo base list!" )
                # набор серверов/баз поменялся; надо мягко завершить работу со старыми запросами, и заново инициализировать набор ioloop.mongo[] для работы с новыми запросами
                self.I.WS.I.DATA.fadeoutData() # постепенно закрываем лавочку (ждем когда очередь запросов полностью разберут, и тогда прибиваем thread pool)
                self.I.WS.DATA = IfaceFactory.makeIDataInterface( options.data, mongo_options_list, self.I.WS.SQL )
                self.response["reset"] = 1
            
            self.response["ok"] = 1
        else:
            err("bad mongo_list count!")
            
        self.fin()

    ##-------------------------------------------------------------------------------------
    ## координатор сообщает (новый) адрес pvx-matchmaker
    def onCoordinatorIpAddrList(self):
        args = self.getFlatParams()
        info( "onCoordinatorIpAddrList args:" + str(args) )
        json_params = args.get("json_params")
        if json_params:
            config_params = json_loads(json_params)
            info( "onCoordinatorIpAddrList config_params:" + str(config_params) )
            self.I.WS.updateSpecificParamList( config_params, self.I.WS._SPECIFIC_CONFIG_PARAMS, self.I.WS.server_type_name )
        
        self.fin()            
        
        
    
