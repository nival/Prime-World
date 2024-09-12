# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# Mock Social Aggregator web-server
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json, logging

sys.path.append('tornado')
import tornado.options
from tornado.options import define, options

sys.path.append('base')
from helpers import *

sys.path.append('cfg')
from coord_cfg import *

from iwebserver import *
from ifactory import IfaceFactory
from iuserdata import IDataManager

##----------------------------------------------------------------------------------------------------------------------
## базовые web request handlers 
from handlers import * # JsonHandler, SubAction, IfaceFactory
from mock_agg_handlers import MockAggregatorHandler, LocalAggregatorHandler

    
##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class MockAggregatorServer( ITornadoServer ):
    """ mock social aggregator веб-сервер (с периодическим таймером) """
    
    ## _Interfaces = dict( HTTP=None, WS=None, ZZ=None )
    
    # -----------------------------------------------
    def tick(self):
        # social aggregator tick
        pass
        
    # -----------------------------------------------
    def initHandlers(self, application):
        info( "MockAggregatorServer initHandlers: WS=%s, HTTP=%s, ZZ=%s" \
            % ( str(getattr(self, "WS", None)), str(getattr(self, "HTTP", None)), str(getattr(self, "ZZ", None)) ) )
            
        application.add_handlers( r"(.*)", [ 
            ( r"/", MockAggregatorHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I) ),
        ] )

    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = DUMMY_SOCAGG_ID
            options.server_name = DUMMY_SOCAGG_NAME
        else:
            options["server_id"].set(DUMMY_SOCAGG_ID)
            options["server_name"].set(DUMMY_SOCAGG_NAME)
        
    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf=None ):
        iDict = ClassDict()

        # http-клиент, потенциально -- для запросов к facebook и zzima api
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient( max_clients=32 ) 
        iDict.WS = IWebServer() # чисто для генерации GUID-ов

        # сейчас AsyncZZima норовит брать ZZima-опции из cfg.*
        cfg.ZZIMA_SERVICE_NAME = COORDINATOR_ZZIMA_SERVICE_NAME
        cfg.ZZIMA_SERVICE_PASSWORD = COORDINATOR_ZZIMA_SERVICE_PASSWORD
        cfg.ZZIMA_API_KEY = COORDINATOR_ZZIMA_API_KEY
        cfg.ZZIMA_API_SECRET = COORDINATOR_ZZIMA_API_SECRET
        cfg.ZZIMA_API_URL = COORDINATOR_ZZIMA_API_URL
        
        iDict.ZZ = IfaceFactory.makeZZimaInterface( options.zzima, COORDINATOR_ZZIMA_WSDL, HTTP=iDict.HTTP )
        info( "ZZ interface: " + str(iDict.ZZ) )
        
        # обычным веб-серверам требуется только оболочка DataManager для заворачивания JSON-данных
        iDict.MD = IDataManager() 
        info( "MD interface: " + str(iDict.MD) )
        
        return iDict

    
## ------------------------------------------------------------

def main():
    ITornadoServer.main( MockAggregatorServer )

if __name__ == "__main__":
    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = 8703
    else:
        options["port"].set(8703)
    main()
