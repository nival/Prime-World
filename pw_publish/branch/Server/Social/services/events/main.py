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
import random
import threading
import datetime
import urlparse

import tornadoredis

from base.helpers import catch

class Counter:

    def __init__(self, freqs, start):
        self.freqs = {}
        self.amounts = {}
        for freq in freqs:
            self.freqs[freq] = 0
            self.amounts[freq] = 0
        self.start = start

    def Add(self, when):
        delta = when-self.start
        for freq, index in self.freqs.items():
            nindex = int(delta/freq)
            if nindex > index:
                self.freqs[freq] = nindex
                self.amounts[freq] = 1
            else:            
                self.amounts[freq] += 1

    def Update(self, when):
        delta = when-self.start
        for freq, index in self.freqs.items():
            nindex = int(delta/freq)
            if nindex > index:
                self.freqs[freq] = nindex
                self.amounts[freq] = 0

    def Get(self):
        return self.amounts


class LogsProcessor:

    def __init__(self, root):
        self.root = root 

    def Process(self, _data, callback):
        try:
            data = json.loads(_data)
        except:
            callback(False)
            return
        _body = base64.b64decode(data.get('body', ''))
        if not _body:
            callback(False)    
            return 
        try:
            body = json.loads(_body)
        except:
            callback(False)
            return
        
        try:
            info('processing log (uri=%r count=%d)', data.get('uri'), len(body))
            url = urlparse.urlparse(data.get('uri'))
            qs = urlparse.parse_qs(url.query)
            format = "%Y.%m.%d"
            pid = qs['pid'][0]
            sid = qs['sid'][0]
            host = qs['host'][0]
            files = {}

            for msg in body:
                try:
                    dt = datetime.datetime.fromtimestamp(msg['tm']).strftime(format)

                    fkey = dt+'/%s(%s)' % (sid, pid)
                    path = '/'.join([self.root, host, fkey+'.log'])

                    f = files.get(fkey, None)
                    if f is None:
                        head, tail = os.path.split(path)
                        if not os.path.isdir(head):
                            os.makedirs(head)
                        writeHeader = not os.path.isfile(path)

                        f = open(path, 'ab+')
                        files[fkey] = f
                        if writeHeader:
                            f.write('Process: %s\n' % pid)
                            f.write('ServiceId: %s\n' % sid)
                            f.write('\n')
                            
                    timestamp = msg.get('datetime', '?')
                    severity = msg.get('type', '?')
                    unicode_message = msg.get('msg')
                    f.write("[%s %8s] " % ( timestamp, severity ))
                    f.write( unicode_message.encode("utf8") )
                    f.write("\n") 
                except:
                    catch()
                    warning('failed processing message')
        except:
            catch()
            warning('failed processing message queue')
            callback(False)
            
        callback(True)

EXPIRE_TIME = 60*60*24*30

class ReliableRedisQueueGuard:

    def __init__(self, rclient, ioloop):
        self.rclient = rclient
        self.ioloop = ioloop
        self.keys = []
        self.expired = []
        self.itemsCount = 0
        self._Refresh()

    def _Refresh(self):
        self.rclient.keys('g|tq*', self._OnKeys)

    def _OnKeys(self, keys):
        self.keys = keys
        if len(self.keys) > 0:   
            pipe = self.rclient.pipeline()
            for name in self.keys:
                pipe.ttl(name)
            pipe.execute(self._OnTime)
        else:
            self.ioloop.add_timeout(time.time()+60.0, self._Refresh)

    def _OnTime(self, result):
        for name, ttl in zip(self.keys, result):
            if EXPIRE_TIME-ttl > 120:
                self.expired.append(name)
        if len(self.expired) > 0:
            info('Expired queues: %r', self.expired)
        self._Clear()

    def _Clear(self):
        if len(self.expired) > 0:
            name = self.expired[0]
            index = name.rfind('|')
            self.rclient.rpoplpush(name[2:], name[3:index], self._OnClear)
        else:
            self.ioloop.add_timeout(time.time()+60.0, self._Refresh)
        
    def _OnClear(self, result):
        if result is None:
            name = self.expired.pop(0)
            info('Deleting expired queue (name=%r items=%d)', name, self.itemsCount)
            self.rclient.delete(name, callback=self._OnDelete) 
        else:
            self.itemsCount += 1
            self._Clear()   

    def _OnDelete(self, result):
        self.itemsCount = 0
        self._Clear()

class ConsumerCallback:

    def __init__(self, root, uid):
        self.root = root
        self.uid = uid

    def _OnData(self, args):
        if args:
            self.root.processor.Process(args, self._OnProcess)
        self.root.OnProcess(False)

    def _OnProcess(self, result):
        self.root.counter.Add(time.time())
        if not result:
            error('Processing failed (item=%r)', self.uid)
        self.root.RemoveItem(self.uid)

class ReliableRedisQueueConsumer:

    def __init__(self, rclient, name, processor, ioloop, freqs):
        self.rclient = rclient
        self.name = name
        self.processor = processor
        self.ioloop = ioloop                
        self.rclient.hincrby('d|'+self.name, 'qid', 1, self._OnConnect)
        self.execCount = 0
        self.length = 0
        self.isStopped = False
        self.counter = Counter(freqs, time.time())
        self._Update()

    def GetQueueName(self):
        return self.name

    def _Update(self):
        self.counter.Update(time.time())
        self.ioloop.add_timeout(time.time() + 2.5, self._Update)

    def GetData(self):
        data = {
            'bw' :  self.counter.Get(),
            'length' : self.length,
        }
        return data
        
    def Stop(self):
        self.isStopped = True

    def IsExecuting(self):
        return self.execCount > 0

    def _OnConnect(self, qid):
        self.queueName = 'tq|'+self.name+'|%s' % qid 
        info('Queue consumer started (name=%r)', self.queueName)
        self.ioloop.add_timeout(time.time()+random.random()*3.0, self._Do)
        self._Refresh()

    def _Refresh(self):
        if self.length > 0: 
            info('Pending queue (name=%r size=%d)', self.name, self.length)
        self.rclient.setex('g|'+self.queueName, EXPIRE_TIME, 0)
        self.ioloop.add_timeout(time.time()+60.0, self._Refresh)

    def RemoveItem(self, uid):
        pipe = self.rclient.pipeline()
        pipe.lrem(self.queueName, uid, 1)
        pipe.hdel('d|'+self.name, str(uid))
        pipe.execute(self._OnRemove)

    def _OnRemove(self, data):
        #info('remove %r' % data)
        #TODO: trying to remove
        self._OnFinish()

    def OnProcess(self, isFinished):
        if self.length > 0:
            self.ioloop.add_timeout(time.time(), self._Do)
        else:
            self.ioloop.add_timeout(time.time()+3.0, self._Do)
        if isFinished:
            self._OnFinish()

    def _OnFinish(self):
        self.execCount -= 1

    def _Do(self):
        if not self.isStopped:
            self.execCount += 1
            pipe = self.rclient.pipeline()
            pipe.rpoplpush('q|'+self.name, self.queueName)
            pipe.llen('q|'+self.name)
            pipe.execute(self._OnPoll)

    def _OnPoll(self, args):
        #info('recieved poll (%s)' % args)
        if len(args) == 2:
            pushItem, self.length = args
        elif len(args) == 1:
            pushItem = args[0]
            self.length = 0
        if pushItem is not None:
            self.rclient.hget('d|'+self.name, str(pushItem), ConsumerCallback(self, pushItem)._OnData)
        else:
            self.OnProcess(True)

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
        else:
            self.callback(False)

class ReliableRedisQueueProvider:

    def __init__(self, rclient, name, ioloop, freqs):
        self.rclient = rclient
        self.name = name
        self.connected = True
        self.connectTime = time.time()
        self.counter = Counter(freqs, time.time())
        self.ioloop = ioloop
        self._Update()

    def _Update(self):
        self.counter.Update(time.time())
        self.ioloop.add_timeout(time.time()+2.5, self._Update)

    def GetQueueName(self):
        return self.name

    def GetData(self):
        return self.counter.Get()

    def GetId(self, callback):
        if not self.connected and time.time() < self.connectTime:
            callback(None)
            return
        try:
            self.rclient.hincrby('d|'+self.name, 'id', 1, callback)
            self.connected = True
        except tornadoredis.ConnectionError:
            self.connected = False
            self.connectTime = time.time() + 3.0
            callback(None)

    def Push(self, callback, data):
        self.counter.Add(time.time())
        pcallback = ReliableRedisQueueCallback(self, callback, data)
        pcallback.Push()

    def PushData(self, uid, data, callback):
        if not self.connected and time.time() < self.connectTime:
            callback(None)
            return
        pipe = self.rclient.pipeline()
        pipe.hset('d|'+self.name, str(uid), data)
        pipe.lpush('q|'+self.name, uid)
        try:
            pipe.execute(callback)
            self.connected = True
        except tornadoredis.ConnectionError:
            self.connected = False
            self.connectTime = time.time() + 3.0
            callback(None)

class HTTPHandler(tornado.web.RequestHandler):

    def CheckParams(self):
        for name, required in self.scheme.items():
            if required:
                self.get_argument(name)
            else:
                self.get_argument(name, None)

class PlainHTTPHandler(HTTPHandler):
    
    def initialize(self, scheme, queue):
        self.queue = queue
        self.scheme = scheme

    @tornado.web.asynchronous
    def get(self):
        data = {
            'uri' : self.request.uri,
        }
        self.queue.Push(self.OnFinish, json.dumps(data))

    @tornado.web.asynchronous
    def post(self):
        self.CheckParams()
        data = {
            'uri' : self.request.uri,
            'body' : base64.b64encode(self.request.body),
        }
        self.queue.Push(self.OnFinish, json.dumps(data))

    def OnFinish(self, result):    
        if result:
            self.write('{"response":{"ok":1}}')
            self.finish()
        else:
            raise tornado.web.HTTPError(503)

class MetricsHandler(tornado.web.RequestHandler):
    def initialize(self, entity):
        self.entity = entity

    @tornado.web.asynchronous
    def get(self):
        method = self.get_argument('method')
        pretty = int(self.get_argument('pretty', '0'))
        request = Network.Web.Request(self, method, pretty, False)

        if method == 'getdata':
            allData = { 'uptime' : time.time()-self.entity.startTime}
            for provider in self.entity.providers:
                name = provider.GetQueueName()
                data = allData.get(name, None)
                if data is None:
                    data = { 'providers' : {}, 'consumers' : { 'bw' : {}, 'length' : 0} }
                    allData[name] = data
                presult = data['providers']
                
                lresult = provider.GetData()
                for freq, amount in lresult.items():
                    presult[freq] = presult.get(freq, 0) + amount

            for consumer in self.entity.consumers:
                name = consumer.GetQueueName()
                data = allData.get(name, None)
                if data is None:
                    data = { 'providers' : {}, 'consumers' : { 'bw' : {}, 'length' : 0} }
                    allData[name] = data
                cresult = data['consumers']

                lresult = consumer.GetData()
                bw = lresult['bw']
                dbw = cresult['bw']
                for freq, amount in bw.items():
                    dbw[freq] = cresult.get(freq, 0) + amount
                cresult['length'] =  cresult.get('length', 0)+lresult['length']
            request.Finish(allData)
        elif method == 'setparam':
            name = self.get_argument('name')
            value = self.get_argument('value')
            if name == 'loglevel':
                System.logs.setupLevel(value)
                request.Finish()
            else:
                request.Fail(1)
        else:
            request.Fail(1)
        
class EventsService(Service):

    def __init__(self, sid):
        super(EventsService, self).__init__(sid)
        self.entity = None

    def Start(self, link, config):
        self.config = config
        self.link = link

        self.startTime = time.time()

        self.application = tornado.web.Application( 
            [],
            debug=self.config.debug,
            autoescape=None )   

        self.httpServers = {}
        self.rclients0 = {}

        freqs = [10, 60, 300, 3600, 3600*24]

        self.providers = []
        self.consumers = []
        lrclient = tornadoredis.Client(host=self.config.listeners.redis_host, port=self.config.listeners.redis_port)
        handlers = []
        for _lconfig in self.config.listeners.instances:
            lconfig = System.config.RawConfig(_lconfig)
            httpServer = self.httpServers.get(lconfig.port, None)
            if httpServer is None:
                httpServer = tornado.httpserver.HTTPServer(self.application, xheaders=self.config.xheaders)
                httpServer.bind(lconfig.port)
                httpServer.start(lconfig.nump)
                self.httpServers[lconfig.port] = httpServer
            provider = ReliableRedisQueueProvider(lrclient, lconfig.queue, tornado.ioloop.IOLoop.instance(), freqs)
            handlers.append((lconfig.path, PlainHTTPHandler, { 'scheme' : lconfig.scheme, 'queue' : provider}))
            self.providers.append(provider)

        handlers.append(('/metrics', MetricsHandler, { 'entity' : self }))
        self.application.add_handlers(".*$", handlers)

        self.consumers = []
        prclient = tornadoredis.Client(host=self.config.processors.redis_host, port=self.config.processors.redis_port)
        for _pconfig in self.config.processors.instances:
            pconfig = System.config.RawConfig(_pconfig)
            processor = LogsProcessor(pconfig.root)
            consumer = ReliableRedisQueueConsumer(prclient, pconfig.queue, processor, tornado.ioloop.IOLoop.instance(), freqs)
            self.consumers.append(consumer)

        if self.config.guard:
            self.lquard = ReliableRedisQueueGuard(prclient, tornado.ioloop.IOLoop.instance())
                                                                                                            
        self.fsm.Move(Service.STARTED)

    def Update(self):   
        if self.fsm.state == Service.STOPPING:   
            executing = False
            for consumer in self.consumers:
                if consumer.IsExecuting():
                    executing = True
                    break
            if not executing:
                self.fsm.Move(Service.STOPPED)

                
    def Stop(self, how):
        for consumer in self.consumers:
            consumer.Stop()

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
                        'root'  : 'logs',
                    },         
                ], 
            },
            'listeners' : {
                'redis_host' : 'localhost',
                'redis_port' : 6379,
                'nump' : 1,
                'instances' : [
                    {
                        'path' : '/pw/logs',
                        'port' : 10007,
                        'nump' : 1,
                        'queue' : 'logs',
                        'scheme' : {
                            'host' : True,
                            'sid' : True,
                            'pid' : True,
                            'skipped' : False,
                        }
                    },
                ],
            },
            'guard' : True,
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

