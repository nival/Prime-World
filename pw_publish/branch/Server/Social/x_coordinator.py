#!/usr/bin/env python
# -*- coding: utf8 -*-
#
# (C) Dan Vorobiev 2012, Nival Network

from base.helpers import *

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

addModPath('cfg')
addModPath('memcache')

import tornado.options
from tornado.options import define, options
import tornado.httpclient
import tornado.httpserver
import tornado.ioloop
import tornado.web

from handlers import JsonHandler, SUBADDR_INTERNAL
from iwebserver import * 
from ifactory import IfaceFactory

from base.http_dumb import *
import ihttp

from isql import main_sql_callback
from iuserdata import IDataManager
import x_coord_cfg as coord_cfg
import cfg

##----------------------------------------------------------------------------------------------------------------------
X_COORD_VERSION_HI = 1
X_COORD_VERSION_LO = 100

## при логине сообщаем версию сервера (даже в случае неуспеха)
X_COORD_VERSION = "%d.%d" % (X_COORD_VERSION_HI, X_COORD_VERSION_LO)

##----------------------------------------------------------------------------------------------------------------------
from coordinator import CoordinatorHandler, BaseCoordinatorServer, servers

# раз в N секунд выгребаем протухшие сообщения, логаем и чистим
#~ CHECK_EXPIRED_MESSAGES_PERIOD = 10 ## DEBUG
CHECK_EXPIRED_MESSAGES_PERIOD = 10*60

# ---------------------------------------------------------------------------------------------------------------------
# ---------------------------------------------------------------------------------------------------------------------

# отличается от базового координатора только набором "специфических конфиг-параметров", передаваемых work-серверам
class XchangeCoordinatorServer( BaseCoordinatorServer ):
    
    _SPECIFIC_CONFIG_PARAMS = {
        "curl_wrk": coord_cfg.COORDINATOR_HTTP_CURL_WORKERS, 
        "curl_conn": coord_cfg.COORDINATOR_HTTP_CURL_CONNECTIONS, 
        "req_limit": coord_cfg.COORDINATOR_HTTP_REQUEST_LIMIT,
        "sql_trd": coord_cfg.COORDINATOR_SQL_THREADS, 
        "events": coord_cfg.COORDINATOR_EVENT_SERVICES,
        "friends_svc": coord_cfg.COORDINATOR_FRIEND_SERVICES,
        "guild_svc": coord_cfg.COORDINATOR_GUILD_SERVICES,
    }

    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.port = 8701
            options.server_id = XCOORDINATOR_WS_ID
            options.server_name = XCOORDINATOR_WS_NAME
            options.server_class = "xcoord"
        else:
            options["port"].set(8701)
            options["server_id"].set(XCOORDINATOR_WS_ID)
            options["server_name"].set(XCOORDINATOR_WS_NAME)
            options["server_class"].set("xcoord")
        
    # -----------------------------------------------
    # полностью аналогично методу BaseCoordinatorServer.initInterfaces, только используем свой, местный конфиг (x_coord_cfg as coord_cfg)
    @staticmethod
    def initInterfaces( classOf ):
        iDict = ClassDict()

        # собственный конфиг координатора
        # собственный конфиг координатора
        for name,server in coord_cfg.COORDINATOR_WS_SERVERS.iteritems():
            if name and server:
                servers[name] = acc = ClassDict(server)
                acc.coording = False
                acc.last_sent2all = 0
                acc.need_send = False
        info( "servers config: %s" % pretty(servers) )
        
        cfg.resetSqlServers( coord_cfg.COORDINATOR_SQL_CONFIG )
        
        # http-клиент, потенциально -- для запросов к facebook и zzima api
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient( max_clients=cfg.HTTP_CURL_WORKERS ) 
        #iDict.WS = IWebServer() # чисто для генерации GUID-ов
        
        iDict.SQL = IfaceFactory.makeSqlInterface( options.sql, cfg.CLUSTER_SQL_CONFIG, num_threads=cfg.SQL_THREADS )
        info( "SQL interface: " + str(iDict.SQL) )
        
        # обычным веб-серверам требуется только оболочка DataManager для заворачивания JSON-данных
        iDict.MD = IDataManager() 
        info( "MD interface: " + str(iDict.MD) )
        
        request_limit = getattr(coord_cfg, "COORDINATOR_HTTP_REQUEST_LIMIT", 1000)
        iDict.XHTTP = ihttp.ILimitedAsyncHttpFetcher( iDict.HTTP, request_limit=request_limit ) # более удобный HTTP fetcher
        
        return iDict

    # -----------------------------------------------
    def tick(self):
        super(XchangeCoordinatorServer, self).tick()
        
        # периодически нужно выгребать
        now = int( time.time() )
        ts_prev = getattr(self, "ts_check_expired_messages", 0)
        if now > ts_prev + CHECK_EXPIRED_MESSAGES_PERIOD:
            self.ts_check_expired_messages = now
            self.I.SQL.seGetExpiredMessages( now, self.onGetExpiredMessages )

    # -----------------------------------------------
    def onGetExpiredMessages(self, sql_reply):
        info( "onGetExpiredMessages: sql reply %s" % sql_reply)
        if sql_reply:
            lines = sql_reply.get("r")
            if lines:
                delete_messages_ids = []
                to = ""
                for l in lines:
                    info( "onGetExpiredMessages: id=%s, to=%s, type=%s, expire=%d" % (l.id, l.type, l.to, l.expire) )
                    delete_messages_ids.append( l.id )
                    to = l.to
                if delete_messages_ids:
                    self.I.SQL.seDeleteMessages( to, delete_messages_ids, self.onDeleteExpiredMessages )
        
    def onDeleteExpiredMessages(self, sql_reply):
        info( "onDeleteExpiredMessages: sql reply %s" % sql_reply), 

if __name__ == "__main__":
    ITornadoServer.main( XchangeCoordinatorServer )
