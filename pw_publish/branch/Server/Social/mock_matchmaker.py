# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# Mock MatchMaker web-server
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json, re, hashlib, urllib, httplib, logging, signal

sys.path.append('tornado')
import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import torndb # sql
from tornado.options import define, options

sys.path.append('base')
from helpers import *

from iwebserver import *
from iuserdata import IDataManager
from imatchmaker import MockMatchmaker

##----------------------------------------------------------------------------------------------------------------------
## базовые web request handlers 
from handlers import * # JsonHandler, SubAction, IfaceFactory

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class MockMmHandler( JsonHandler ):
    """ обрабатываем только внутренний запрос 'mm' от рабочих серверов """
    
    internalActionMap = {
        # внутрикластерные команды; закрыты для внешних клиентов
        'mm': 'onMmPacket',
    }
    
    ## SUBADDR и WS обязательны при работе c JsonHandler
    ## _Interfaces = dict( SUBADDR=None, WS=None, MM=None )

    # -----------------------------------------
    def onMmPacket(self):
        json_data = self.getParam( "data", "{}" )
        mm_packet = json_loads(json_data)
        ##log( "onMmPacket data: " + pretty(mm_packet) )
        
        # parse version
        ver_ok = False
        try:
            soc_server_ver = mm_packet.get("ver", "0.0.0")
            hi,med = soc_server_ver.split(".")[:2]
            if toint(hi) == MMSOC_VERSION_HIGH and toint(med) == MMSOC_VERSION_MED:
                ver_ok = True
            else:
                self.response["error"] = "matchmaking protocol version mismatch (%s)" % soc_server_ver;
        except:
            self.response["error"] = "bad version format"
            
        if ver_ok:
            reply = self.I.MM.handlePacket( mm_packet )
            
            self.response["ok"] = 1
            self.response["pvx"] = reply
            self.response["ver"] = MMSOC_VERSION
            
        self.fin()
        

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class MockMatchmakingServer( ITornadoServer ):
    """ pvx matchmaking веб-сервер (с периодическим таймером) """
    
    ## _Interfaces = dict( MM=None, HTTP=None )
    
    # -----------------------------------------------
    def tick(self):
        # pvx matchmaker tick
        self.I.MM.stepSessions()
        
    # -----------------------------------------------
    def initHandlers(self, application):
        application.add_handlers( r"(.*)", [ 
            ( r"/x", MockMmHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I) ),
            ##( r"/x", MockMmHandler, dict(SUBADDR=SUBADDR_INTERNAL, MM=self.MM, WS=self) ),
        ] )

    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = DUMMY_MM_ID
            options.server_name = DUMMY_MM_NAME
        else:
            options["server_id"].set(DUMMY_MM_ID)
            options["server_name"].set(DUMMY_MM_NAME)
        
    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf=None ):
        iDict = ClassDict()

        # http-клиент для отсылки сообщений Work-серверами (о завершении игровых сессий)
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient( max_clients=32 ) 
        
        # mock pvx-matchmaking server
        iDict.MM = MockMatchmaker( iDict.HTTP )
    
        # обычным веб-серверам требуется только оболочка DataManager для заворачивания JSON-данных
        iDict.MD = IDataManager() 
        info( "MD interface: " + str(iDict.MD) )
        
        return iDict

    
## ------------------------------------------------------------

def main():
    ITornadoServer.main( MockMatchmakingServer )

if __name__ == "__main__":
    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = 8702
    else:
        options["port"].set(8702)
    main()
