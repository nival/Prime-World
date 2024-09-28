# -*- coding: utf-8 -*-

#!/usr/bin/env python

import sys, os, time, json, logging

sys.path.append(os.path.abspath('.'))

from tornado.options import define, options

sys.path.append('base')
from helpers import *

sys.path.append('cfg')
import coord_cfg

import status_cfg

from iwebserver import *
from iuserdata import IDataManager

from handlers import * # JsonHandler, IfaceFactory

import functools
import random

class StatusServiceHandler( JsonHandler ):
    
    internalActionMap = {
        'status': 'onStatus', 
    }
    
    # -----------------------------------------
    def onStatus(self):
        who = self.getParam("who")
        self.response['ok'] = 1
        self.response['info'] = self.I.WS.getInfo(who)
        self.fin()        

import time        
CONNECTED = 0 
UNKNOWN = 1 
DISCONNECTED = 2

class ServerInfo:

    def __init__(self, name, host, http, updateTime):
        self.host = host
        self.status = UNKNOWN
        self.info = {
            'status' : self.status, 
            'message' : '', 
            'last_update' : int(updateTime),
            'name' : name,
        }
        self.http = http
        self.started = False

    def getLastUpdateTime(self):
        return time.time()-self.info['last_update']

    def update(self):
        self.info['last_update'] = int(time.time())
        if not self.started:
            self.fetch(self.host, self.onReply )

    def fetch(self, request, callback):
        _callback = functools.partial( self._onReply, callback=callback )
        self.started = True
        try:
            self.http.fetch( request, _callback )
        except:
            catch()
            _callback( None )

    def onReply(self, response, error):
        old_status = self.status
        if not error:
            self.status = CONNECTED
        else:
            if self.status == CONNECTED:
                self.status = DISCONNECTED
        if old_status != self.status:
            self.info['status'] = self.status
        self.started = False
        
    def _onReply(self, http_reply, callback):
        response, error = parseResponse(http_reply)

        if error:    
            warn( error )

        if callback:
            callback( response, error )

class StatusService( ITornadoServer ):

    def __init__(self, **kwargs):
        super(StatusService, self).__init__( **kwargs )

        self.servers = { 
        }

        for name, host in status_cfg.hosts.items():
            self.servers[name] = ServerInfo(name, host, self.I.HTTP, time.time()+random.random()*status_cfg.updatePeriod)

    def getInfo(self, server):
        info = self.servers.get(server, None)
        if info:
            return info.info
        
    # -----------------------------------------------
    def tick(self):
        for name, server in self.servers.items():
            if server.getLastUpdateTime() > status_cfg.updatePeriod:
                server.update()

    # -----------------------------------------------
    def initHandlers(self, application):
        application.add_handlers( r"(.*)", [ 
            ( r"/", StatusServiceHandler, dict(SUBADDR=SUBADDR_BALANCED, I=self.I) ),
            ( r"/x", StatusServiceHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I) ),
        ] )
        
    # return True if startup enviroment is bad
    @staticmethod
    def checkStartupFail():
        pass
        
    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = 0
            options.server_name = 'status'
        else:
            options["server_id"].set(0)
            options["server_name"].set('status')

    # -----------------------------------------------
        
    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf=None ):
        iDict = ClassDict()

        iDict.MD = IDataManager( ) 

        iDict.HTTP = tornado.httpclient.AsyncHTTPClient( max_clients=32 ) 
        return iDict
        
## ---------------------------------------------------------------------------------------------
def main():
    ITornadoServer.main( StatusService )

if __name__ == "__main__":
    #tornado 3.4 fix
    if options.__class__.__name__ == "OptionParser":
        options.port = 8707
    else:
        options["port"].set(8707)
    main()
