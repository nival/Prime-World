import sys
sys.path.append('../../services/common/py')

import System.logs

import tornado.ioloop
import tornado.httpclient

import signal
import time
import json
import base64

from logging import debug, info

from tornado import gen
import urllib

class PingScenario:

    def __init__(self, root):
        self.root = root
        self.status = 0
        self.url = 'http://localhost:8705' #'http://b307.nivalnetwork.com:8705'
        self.auid = id(self)
        self.hclient = tornado.httpclient.AsyncHTTPClient()

    def GetUrl(self, page, action, **kwargs):
        kwargs['action'] = action
        url = self.url
        if page:
            if url[-1] != '/':
                url += '/'
            url += page
        result = url+'?'+urllib.urlencode(kwargs)
        debug(result)
        return result

    @gen.engine
    def Start(self):
        self.status = 1

        url = self.GetUrl('x', 'add_user', auid=self.auid, key='aabbccddee', locale='RU', fraction=0, mutetime=0, muted=0, nickname='TestUser'+str(self.auid))

        response = yield gen.Task(self.hclient.fetch, url)
        debug(response.body)

        self.status = 2

    @gen.engine
    def Execute(self):
        self.status = 3
        yield gen.Task(self.root.loop.add_timeout, time.time() + 5.0)

        for i in range(10):
            if i % 10 == 0:
                chat = base64.urlsafe_b64encode('PRIVMSG #globalRU0 : Hello %d!' % i)
            else:
                chat = None
            if chat:
                url = self.GetUrl('chat0', 'ping', auid=self.auid, key='aabbccddee', chat=chat)
            else:
                url = self.GetUrl('chat0', 'ping', auid=self.auid, key='aabbccddee')
            response = yield gen.Task(self.hclient.fetch, url)
            debug(response.body)
            if not response.error:
                data = json.loads(response.body)
                chat = data.get('response', {}).get('chat', None)
                if chat:
                    debug('-------------------------------------')
                    debug(base64.b64decode(chat))
                    debug('-------------------------------------')
            yield gen.Task(self.root.loop.add_timeout, time.time() + 0.75)

        url = self.GetUrl('x', 'add_user', auid=self.auid, key='aabbccddee', locale='RU', fraction=0, mutetime=0, muted=0, nickname='TestUser'+str(self.auid))
        response = yield gen.Task(self.hclient.fetch, url)
        debug(response.body)

        for i in range(10):
            if i % 10 == 0:
                chat = base64.urlsafe_b64encode('PRIVMSG #globalRU0 : Hello %d!' % i)
            else:
                chat = None
            if chat:
                url = self.GetUrl('chat0', 'ping', auid=self.auid, key='aabbccddee', chat=chat)
            else:
                url = self.GetUrl('chat0', 'ping', auid=self.auid, key='aabbccddee')
            response = yield gen.Task(self.hclient.fetch, url)
            debug(response.body)
            if not response.error:
                data = json.loads(response.body)
                chat = data.get('response', {}).get('chat', None)
                if chat:
                    debug('-------------------------------------')
                    debug(base64.b64decode(chat))
                    debug('-------------------------------------')
            yield gen.Task(self.root.loop.add_timeout, time.time() + 0.75)

        yield gen.Task(self.root.loop.add_timeout, time.time() + 10.0)

        url = self.GetUrl('x', 'add_user', auid=self.auid, key='aabbccddee', locale='RU', fraction=0, mutetime=0, muted=0, nickname='TestUser'+str(self.auid))
        response = yield gen.Task(self.hclient.fetch, url)
        debug(response.body)

        for i in range(10):
            if i % 10 == 0:
                chat = base64.urlsafe_b64encode('PRIVMSG #globalRU0 : Hello %d!' % i)
            else:
                chat = None
            if chat:
                url = self.GetUrl('chat0', 'ping', auid=self.auid, key='aabbccddee', chat=chat)
            else:
                url = self.GetUrl('chat0', 'ping', auid=self.auid, key='aabbccddee')
            response = yield gen.Task(self.hclient.fetch, url)
            debug(response.body)
            if not response.error:
                data = json.loads(response.body)
                chat = data.get('response', {}).get('chat', None)
                if chat:
                    debug('-------------------------------------')
                    debug(base64.b64decode(chat))
                    debug('-------------------------------------')
            yield gen.Task(self.root.loop.add_timeout, time.time() + 0.75)
        self.status = 4

    @gen.engine
    def Stop(self):
        self.status = 5

        url = self.GetUrl('x', 'remove_user', auid=self.auid)
        response = yield gen.Task(self.hclient.fetch, url)
        debug(response.body)

        self.status = 6

class LongPingScenario:

    def __init__(self, root):
        self.root = root
        self.status = 0
        self.url = 'http://localhost:8705' #'http://b307.nivalnetwork.com:8705'
        self.auid = id(self)
        self.hclient = tornado.httpclient.AsyncHTTPClient()

    def GetUrl(self, page, action, **kwargs):
        kwargs['action'] = action
        url = self.url
        if page:
            if url[-1] != '/':
                url += '/'
            url += page
        result = url+'?'+urllib.urlencode(kwargs)
        debug(result)
        return result

    @gen.engine
    def Start(self):
        self.status = 1

        url = self.GetUrl('x', 'add_user', auid=self.auid, key='aabbccddee', locale='RU', fraction=0, mutetime=0, muted=0, nickname='TestUser'+str(self.auid))

        response = yield gen.Task(self.hclient.fetch, url)
        debug(response.body)

        self.status = 2

    @gen.engine
    def Execute(self):
        self.status = 3
        yield gen.Task(self.root.loop.add_timeout, time.time() + 5.0)

        for i in range(10):
            if i % 10 == 0:
                chat = base64.urlsafe_b64encode('PRIVMSG #globalRU0 : Hello %d!' % i)
            else:
                chat = None
            if chat:
                url = self.GetUrl('chat0', 'send', auid=self.auid, key='aabbccddee', chat=chat)
            else:
                url = self.GetUrl('chat0', 'lping', auid=self.auid, key='aabbccddee')
            response = yield gen.Task(self.hclient.fetch, url)
            debug(response.body)
            if not response.error:
                data = json.loads(response.body)
                chat = data.get('response', {}).get('chat', None)
                if chat:
                    debug('-------------------------------------')
                    debug(base64.b64decode(chat))
                    debug('-------------------------------------')
            yield gen.Task(self.root.loop.add_timeout, time.time() + 0.75)

        url = self.GetUrl('x', 'add_user', auid=self.auid, key='aabbccddee', locale='RU', fraction=0, mutetime=0, muted=0, nickname='TestUser'+str(self.auid))
        response = yield gen.Task(self.hclient.fetch, url)
        debug(response.body)

        for i in range(10):
            if i % 10 == 0:
                chat = base64.urlsafe_b64encode('PRIVMSG #globalRU0 : Hello %d!' % i)
            else:
                chat = None
            if chat:
                url = self.GetUrl('chat0', 'send', auid=self.auid, key='aabbccddee', chat=chat)
            else:
                url = self.GetUrl('chat0', 'lping', auid=self.auid, key='aabbccddee')
            response = yield gen.Task(self.hclient.fetch, url)
            debug(response.body)
            if not response.error:
                data = json.loads(response.body)
                chat = data.get('response', {}).get('chat', None)
                if chat:
                    debug('-------------------------------------')
                    debug(base64.b64decode(chat))
                    debug('-------------------------------------')
            yield gen.Task(self.root.loop.add_timeout, time.time() + 0.75)

        yield gen.Task(self.root.loop.add_timeout, time.time() + 10.0)

        url = self.GetUrl('x', 'add_user', auid=self.auid, key='aabbccddee', locale='RU', fraction=0, mutetime=0, muted=0, nickname='TestUser'+str(self.auid))
        response = yield gen.Task(self.hclient.fetch, url)
        debug(response.body)

        for i in range(10):
            if i % 10 == 0:
                chat = base64.urlsafe_b64encode('PRIVMSG #globalRU0 : Hello %d!' % i)
            else:
                chat = None
            if chat:
                url = self.GetUrl('chat0', 'send', auid=self.auid, key='aabbccddee', chat=chat)
            else:
                url = self.GetUrl('chat0', 'lping', auid=self.auid, key='aabbccddee')
            response = yield gen.Task(self.hclient.fetch, url)
            debug(response.body)
            if not response.error:
                data = json.loads(response.body)
                chat = data.get('response', {}).get('chat', None)
                if chat:
                    debug('-------------------------------------')
                    debug(base64.b64decode(chat))
                    debug('-------------------------------------')
            yield gen.Task(self.root.loop.add_timeout, time.time() + 0.75)
        self.status = 4

    @gen.engine
    def Stop(self):
        self.status = 5

        url = self.GetUrl('x', 'remove_user', auid=self.auid)
        response = yield gen.Task(self.hclient.fetch, url)
        debug(response.body)

        self.status = 6

class Service:

    def __init__(self):
        self.loop = tornado.ioloop.IOLoop.instance()
        signal.signal( signal.SIGINT, self.OnBreak )
        self.stopped = False
        self.loop.add_timeout(time.time(), self.OnUpdate)
        self.scenarios = []
        count = 1
        for i in range(count):
            self.scenarios.append(LongPingScenario(self))

    def Start(self):
        try:
            self.loop.start()
        finally:
            pass

    def OnBreak(self, signum, frame):
        info('SIGNAL %d caught: initiating shutdown' % signum)
        self.stopped = True
        self.loop.add_timeout(time.time(), self.OnUpdate)

    def OnUpdate(self):
        if self.stopped:
            self.loop.stop()

        for s in self.scenarios:
            if s.status == 0:
                s.Start()
            if s.status == 2:
                s.Execute()
            if s.status == 4:
                s.Stop()

        self.loop.add_timeout(time.time()+1.5, self.OnUpdate)

if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--log', default=None, help='Log file name')
    parser.add_argument('--loglevel', choices=['debug', 'info','warning','error', 'critical'], default='info', help='Logging severity level')
    args = parser.parse_args()
    System.logs.setup(args.log, args.loglevel)

    svc = Service()
    svc.Start()