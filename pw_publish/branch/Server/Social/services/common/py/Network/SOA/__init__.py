# -*- coding: utf-8 -*-
import Network
import Network.Web
import Network.HttpClient
import System.fsm
import System.exc_handle
import tornado.ioloop
from logging import info, error, critical
import urllib
import json

import sys
import logging

class Service(object):
    """
    Конечный автомат, который умеет вызывать обработчки при смене сотояний.
    Состояния: STOPPED (оно же начальное), STARTING, STARTED, STOPPING
    Обработчики по дефолту просто пишут в лог INFO о смене состояния.
    А ещё у него есть HttpLoggerInit() и HttpLoggerTick(), но сам он ихне вызывает.
    """

    STOPPED = 0
    STARTING = 1
    STARTED = 3
    STOPPING = 4

    STOP_NONE = 0
    STOP_TERMINATE = 1
    STOP_SOFT = 2
    STOP_GRACEFULL = 3

    def __init__(self, sid=None):    
        self.sid = sid
        self.fsm = System.fsm.FSM(
            [ 
                (Service.STOPPED, Service.STARTING, self.OnStart), 
                (Service.STARTING, Service.STOPPED, self.OnStartFailure), 
                (Service.STARTING, Service.STOPPING, self.OnStartFailure), 
                (Service.STARTING, Service.STARTED, self.OnStartSuccess), 
                (Service.STARTED, Service.STOPPING, self.OnStop), 
                (Service.STOPPING, Service.STOPPED, self.OnStopSuccess),
                (Service.STARTED, Service.STOPPED, self.OnStopFailure), 
                (Service.STOPPED, Service.STOPPING, self.OnAlreadyStopped), 
            ], Service.STOPPED)

    def OnStart(self, data):
        if self.sid:
            info('Service starting (sid=%r)' % self.sid)

    def OnStartFailure(self, data):
        if self.sid:
            info('Service failed to start (sid=%r)' % self.sid)

    def OnStopFailure(self, data):
        if self.sid:
            info('Service stopped unexpectedly (sid=%r)' % self.sid)

    def OnStartSuccess(self, data):
        if self.sid:
            info('Service started (sid=%r)' % self.sid)

    def OnStop(self, data):
        if self.sid:
            info('Service stopping (sid=%r)' % self.sid)

    def OnStopSuccess(self, data):
        if self.sid:
            info('Service stopped (sid=%r)' % self.sid)

    def OnAlreadyStopped(self, data):
        if self.sid:
            info('Service already stopped (sid=%r)' % self.sid)

    def GetStatus(self):
        return self.fsm.state

    def Stop(self, how):
        raise NotImplementedError()

    def HttpLoggerInit(self, args, config):
        if args.log_http:
            logging.info( "init log_http, severity=%s" % (args.log_http_level) )
            severity_level = System.logs.getLoggingLevel( args.log_http_level )
            import severe_logger
            handler = severe_logger.PacketedJsonHttpLogHandler( level=severity_level, max_queue_size=args.log_http_max_count, 
                channel_name=args.sid, service_id=args.sid, process_id=args.pid )
            handler.setFormatter( logging.Formatter("%(message)s") )
            # settings from our own config, no coord_cfg in sight
            max_clients = config.HTTP_CURL_WORKERS or 32
            urls = config.EVENT_SERVICES or [""]
            iHTTP = tornado.httpclient.AsyncHTTPClient( max_clients=max_clients ) 
            handler.setHTTP( urls, iHTTP )
            logging.getLogger().addHandler( handler )
            self.http_log = handler
            
    def HttpLoggerTick(self):
        handler = getattr(self, "http_log", None)
        if handler:
            handler.send()           

class ClusterLink(object):
    DEFAULT_MAX_CLIENTS = 50

    def __init__(self, gate, config, url=None):
        self.url = url
        self.config = config
        self.gate = gate
        self.client = Network.HttpClient.AsyncHttpClient(max_clients=ClusterLink.DEFAULT_MAX_CLIENTS)

    def GetGate(self):
        return self.gate

    def fetch(self, args, callback, data=None, page='', url=None):
        if url:
            request = url
        else:
            request = self.url
        if page:
            request += '/'+page
        request += '?'+urllib.urlencode(args)
        self.client.fetch(
            request, 
            callback,
            data)

import signal

class ServiceGate(Service):

    def __init__(self, url=None):
        super(ServiceGate, self).__init__()
        self.url = url
        signal.signal(signal.SIGINT, self.OnBreak)
        # TODO нам бы ещё и SIGTERM обрабатывать, вероятно, так же,как SIGINT
        self.services = []
        self.fsm.Move(Service.STARTING)
        self.pending = []

    def AddService(self, service, config):
        info(('Service config (sid=%r)\n' % service.sid) + json.dumps(config.GetRaw(), indent=4))
        self.pending.append( (service, config) )
        service.fsm.Move(Service.STARTING)

    def OnBreak(self, signum, frame):
        info( 'SIGNAL %d caught: initiating shutdown' % signum )
        for service, link in self.services:
            service.fsm.Move(Service.STOPPING)
            service.Stop(Service.STOP_SOFT)
        self.fsm.Move(Service.STOPPING)
        self.updater.SetTimeout(0.05)
        self.updater.Reset()
    
    def Update(self):
        for service, link in self.services:
            try:
                service.Update()
            except:
                info( 'Exception caught: initiating service stop (sid=%r)' % service.sid )
                error(System.exc_handle.getException())
                service.fsm.Move(Service.STOPPING)
                service.Stop(Service.STOP_SOFT)
        
        if self.fsm.state == Service.STOPPING:
            if self._IsAllStopped():
                self.loop.stop()

    def _IsAllStopped(self):
        for service, link in self.services:
            if service.GetStatus() != Service.STOPPED:
                return False
        return True
                
    def Run(self):
        self.loop = tornado.ioloop.IOLoop.instance()
        self.updater = Network.Web.Updater(self, self.loop, 2.0)
        for service, config in self.pending:
            link = ClusterLink(self, config, self.url)
            try:
                service.Start(link, config)
            except:
                critical(System.exc_handle.getException())
                service.fsm.Move(Service.STOPPING)
            self.services.append( (service, link) )

        self.fsm.Move(Service.STARTED)
        try:
            self.loop.start()
        finally:
            pass
