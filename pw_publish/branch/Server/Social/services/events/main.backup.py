# -*- coding: utf-8 -*-
import sys
sys.path.append('../common/py')
sys.path.append('../..')

import System.logs
import System.fsm
import System.config

import os.path
import tornado.escape
import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web

import Network
from Network.SOA import Service

from logging import debug, info, error, warning

import json
import base64
import time
import threading

class LogsProcessor:

    def Process(self, data, callback):
        info('processing %r' % data)
        callback(True)

class ConsumerCallback:

    def __init__(self, root, uid):
        self.root = root
        self.uid = uid

    def _OnData(self, args):
        if args:
            self.root.processor.Process(args, self._OnProcess)

    def _OnProcess(self, result):
        if result:
            self.root.RemoveItem(self.uid)
        else:
            error('Processing failed (item=%r)' % self.uid)
            #TODO: trying to reprocess

class ReliableRedisQueueConsumer:

    def __init__(self, rclient, name, proxy, processor, ioloop):
        self.rclient = rclient
        self.name = name
        self.proxy = proxy
        self.processor = processor
        self.queueName = self.name+'_qt' 
        if self.proxy:
            self.proxy.Subscribe(self.name+'_c', self._OnMessage)
        self.ioloop = ioloop                
        self.ioloop.add_timeout(time.time(), self._Do)
        self.isExecuting = False
        self.length = 0

    def RemoveItem(self, uid):
        pipe = self.rclient.pipeline()
        pipe.lrem(self.queueName, uid, 1)
        pipe.hdel(self.name+'_d', str(uid))
        pipe.execute(self._OnRemove)

    def _OnRemove(self, data):
        info('remove %r' % data)
        #TODO: trying to remove
        self.OnFinish()

    def OnFinish(self):
        if self.length > 0:
            self.ioloop.add_timeout(time.time(), self._Do)
        else:
            self.ioloop.add_timeout(time.time()+10.0, self._Do)
        self.isExecuting = False

    def _OnMessage(self, msg):
        info('recieved pubsignal (length=%s)' % msg)
        self._Do()

    def _Do(self):
        if not self.isExecuting:
            self.isExecuting = True
            pipe = self.rclient.pipeline()
            pipe.rpoplpush(self.name+'_q', self.queueName)
            pipe.llen(self.name+'_q')
            pipe.execute(self._OnPoll)

    def _OnPoll(self, args):
        info('recieved poll (%s)' % args)
        if len(args) == 2:
            pushItem, self.length = args
        elif len(args) == 1:
            pushItem = args[0]
            self.length = 0
        if pushItem is not None:
            self.rclient.hget(self.name+'_d', str(pushItem), ConsumerCallback(self, pushItem)._OnData)
        else:
            self.OnFinish()


class LoopThread(threading.Thread):

    def __init__(self, ioloop):
        threading.Thread.__init__(self)
        self.ioloop = ioloop

    def run(self):
        self.ioloop.start()

    def Stop(self):        
        self.ioloop.stop()

class ReliableRedisQueueProxy:

    def __init__(self, rclient, ioloop):
        self.rclient = rclient
        self.subscribed = False
        self.pending = []
        self.channels = {}
        self.rclient.subscribe('<dummy>', self._OnSubscribe)
        self.thread = LoopThread(ioloop)
        self.thread.start()

    def Stop(self):
        self.thread.Stop()

    def _Subscribe(self, channel, processor):
        processors = self.channels.get(channel, None)
        if processors is None:
            processors = []
            self.channels[channel] = processors
        processors.append(processor)
        self.rclient.subscribe(channel)

    def Subscribe(self, channel, processor):
        if self.subscribed:
            self._Subscribe(channel, processor)
        else:
            self.pending.append( (channel, processor) )
        
    def _OnMessage(self, msg):
        if type(msg.body) == int:
            return
        processors = self.channels.get(msg.pattern, None)
        if processors is not None:
            for processor in processors:
                processor(msg.body)    

    def _OnSubscribe(self, msg):
        self.rclient.listen(self._OnMessage)
        for channel, processor in self.pending:
            self._Subscribe(channel, processor)
        self.pending = []
        self.subscribed = True    

class ReliableRedisQueueCallback:

    def __init__(self, root, callback, data):
        self.root = root
        self.callback = callback
        self.data = data

    def Push(self):
        self.root.GetId(self._OnId)

    def _OnId(self, uid):
        if uid is not None:
            self.root.PushData(uid, self.data, self._OnPush)
        else:
            self.callback(False)

    def _OnPush(self, result):
        if result is not None:
            dummy, count = result
            self.callback(True)
            self.root.rclient.publish(self.root.name+'_c', str(count))
        else:
            self.callback(False)

class ReliableRedisQueueProvider:

    def __init__(self, rclient, name):
        self.rclient = rclient
        self.name = name
        self.connected = True
        self.connectTime = time.time()

    def GetId(self, callback):
        if not self.connected and time.time() < self.connectTime:
            callback(None)
            return
        try:
            self.rclient.hincrby(self.name+'_d', 'id', 1, callback)
            self.connected = True
        except tornadoredis.ConnectionError:
            self.connected = False
            self.connectTime = time.time() + 3.0
            callback(None)

    def Push(self, callback, data):
        pcallback = ReliableRedisQueueCallback(self, callback, data)
        pcallback.Push()

    def PushData(self, uid, data, callback):
        if not self.connected and time.time() < self.connectTime:
            callback(None)
            return
        pipe = self.rclient.pipeline()
        pipe.hset(self.name+'_d', str(uid), data)
        pipe.lpush(self.name+'_q', uid)
        try:
            pipe.execute(callback)
            self.connected = True
        except tornadoredis.ConnectionError:
            self.connected = False
            self.connectTime = time.time() + 3.0
            callback(None)

class PlainHTTPHandler(tornado.web.RequestHandler):
    
    def initialize(self, queue):
        self.queue = queue

    @tornado.web.asynchronous
    def get(self):
        data = {
            'uri' : self.request.uri,
        }
        self.queue.Push(self.OnFinish, json.dumps(data))

    @tornado.web.asynchronous
    def post(self):
        data = {
            'uri' : self.request.uri,
            'body' : base64.b64encode(self.request.body),
        }
        self.queue.Push(self.OnFinish, json.dumps(data))

    def OnFinish(self, result):    
        if result:
            self.finish()
        else:
            raise tornado.web.HTTPError(503)


import tornadoredis

class EventsService(Service):

    def __init__(self, sid):
        super(EventsService, self).__init__(sid)
        self.entity = None

    def Start(self, link, config):
        self.config = config
        self.link = link

        self.application = tornado.web.Application( 
            [],
            debug=self.config.debug,
            autoescape=None )   

        self.httpServers = {}
        self.rclients0 = {}

        for _lconfig in self.config.listeners:
            lconfig = System.config.RawConfig(_lconfig)
            httpServer = self.httpServers.get(lconfig.port, None)
            if httpServer is None:
                httpServer = tornado.httpserver.HTTPServer(self.application, xheaders=self.config.xheaders)
                httpServer.listen(lconfig.port)
                self.httpServers[lconfig.port] = httpServer
            rclient = self.rclients0.get( ( lconfig.redis_host, lconfig.redis_port), None)
            if rclient is None:
                rclient = tornadoredis.Client(host=lconfig.redis_host, port=lconfig.redis_port)
                self.rclients0[ ( lconfig.redis_host, lconfig.redis_port) ] = rclient
            self.application.add_handlers(".*$", [ (lconfig.path, PlainHTTPHandler, { 'queue' : ReliableRedisQueueProvider(rclient, lconfig.queue)}) ])

    #    ioloop = tornado.ioloop.IOLoop()
    #    rclient = tornadoredis.Client(host=self.config.processors.redis_host, port=self.config.processors.redis_port, io_loop=ioloop)
    #    self.proxy = ReliableRedisQueueProxy(rclient, ioloop)

        crclient = tornadoredis.Client(host=self.config.processors.redis_host, port=self.config.processors.redis_port)
        for _pconfig in self.config.processors.instances:
            pconfig = System.config.RawConfig(_pconfig)
            processor = LogsProcessor()
            consumer = ReliableRedisQueueConsumer(crclient, pconfig.queue, None, processor, tornado.ioloop.IOLoop.instance())
                                                                                                            
        self.fsm.Move(Service.STARTED)

    def Update(self):
        pass
                
    def Stop(self, how):
#        self.proxy.Stop()
        self.fsm.Move(Service.STOPPED)


def main(args, gate):
    if args.config:
        config = System.config.RawConfig(args.config)
    else:
        data = {
            'debug' : True,
            'xheaders' : True,
            'processors' : {
                'redis_host' : 'localhost',
                'redis_port' : 6379,
                'instances' : [        
                    {
                        'type' : 'Logs',
                        'queue' : 'logs',
                    },         
                ], 
            },
            'listeners' : [
                {
                    'path' : '/pw/logs',
                    'port' : 10007,
                    'queue' : 'logs',
                    'redis_host' : 'localhost',
                    'redis_port' : 6379,
                },
            ],
        }
        config = System.config.RawConfig(data)
    svn = EventsService(args.sid)
    gate.AddService(svn, config)

if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--config', default=None, help='Config path') 
    parser.add_argument('--sid', default='Events', help='Service id')
    parser.add_argument('--log', default=None, help='Log file name')
    parser.add_argument('--loglevel', choices=['debug', 'info','warning','error', 'critical'], default='info', help='Logging severity level')
    parser.add_argument('--logrotate', type=int, default=0, help='Logging rotation')
    args = parser.parse_args()

    System.logs.setup(args.log, args.loglevel, args.logrotate)

    gate = Network.SOA.ServiceGate()

    main(args, gate)
    gate.Run() 
                
    