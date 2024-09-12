# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# Thrift Agent web-server: принимает внешние запросы по thrift, мапит их на внутрикластерные http-запросы
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json, logging
import functools

os.chdir('..')
sys.path.append('.')

sys.path.append('tornado')
import tornado.options
from tornado.options import define, options

sys.path.append('base')
from helpers import *

sys.path.append('cfg')
import coord_cfg

from iwebserver import *
from ifactory import IfaceFactory
from iuserdata import IDataManager

from ext_main.chat import MessageAction

##----------------------------------------------------------------------------------------------------------------------
## базовые web request handlers 
from handlers import * # JsonHandler, SubAction, IfaceFactory
from thrift_handler import ThriftHandler, AsyncThriftException

from thrift import Thrift
from thrift.transport import TTransport
from thrift.transport import THttpClient
from thrift.protocol import TBinaryProtocol

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

sys.path.append('thrift_pw/statistics/gen-py')
import StatisticCore.StatisticService
import StatisticCore.ttypes
       

class DumpStatsHandler( StatisticCore.StatisticService.Iface ):
    """ ------------------------------ """
    def __init__( self, handler ):
        self.handler = handler
        self.service = handler.service
        self.I = handler.I
        
    @staticmethod
    def getProcessorClass():
        return StatisticCore.StatisticService.Processor   
        
    def LoginUsers(self, logins):
        info("DumpStatsHandler.LoginUsers: %s" % logins)

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

class ThriftAgentInternalHandler( JsonHandler ):
    """ обрабатываем только служебные команды от координатора """
    internalActionMap = {
        # внутрикластерные команды; закрыты для внешних клиентов
        # --- служебное ----
        'check_alive': 'onCheckWebServerAlive', # base JsonHandler: умеем отвечать, что мы живы
        'peer': PeerServerStatusAction, # base JsonHandler: апдейтим статус peer WS-ок
    }
    
class ThriftStatsServer( ITornadoServer ):
    """ Thrift Statistics веб-сервер (принимает внешние запросы по thrift, логает, больше ничего не делает) """
    
    _SERVICES = { 
        "stats": DumpStatsHandler, # этот сервис сначала исполняет кастомную кластерную логику (лезет в memcache/sql), а потом отправляет суб-запросы на WS
    }
        
    ##---------------------------------------------------------------------------------------------------
    def __init__(self, **kwargs):
        super(ThriftStatsServer, self).__init__( **kwargs )
        
    # -----------------------------------------------
    def initHandlers(self, application):
        info( "ThriftStatsServer initHandlers" )
            
        application.add_handlers( r"(.*)", [ 
            ( r"/thrift", ThriftHandler, dict(I=self.I, SERVICES=ThriftStatsServer._SERVICES ) ),
        ] )
        
    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = THRIFT_AGENT_ID
            options.server_name = THRIFT_AGENT_NAME
        else:
            options["server_id"].set(THRIFT_AGENT_ID)
            options["server_name"].set(THRIFT_AGENT_NAME)
        
    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf=None ):
        iDict = ClassDict()
        return iDict

    
## ------------------------------------------------------------

def main():
    ITornadoServer.main( ThriftStatsServer )

if __name__ == "__main__":
    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = 8766
    else:
        options["port"].set(8766)
    main()
