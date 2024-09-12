# -*- coding: utf-8 -*-

import sys
sys.path.append('../common/py')
sys.path.append('../..')

import System.logs
import System.fsm
import System.config
import Network
from Network.SOA import Service
import argparse
import os
import time
import json

import EC

from logging import debug, info, error, warning

import tornado.web
import tornado.httpserver

class SocialExchangeHandler(tornado.web.RequestHandler):

    def initialize(self, entity):
        self.entity = entity

    @tornado.web.asynchronous
    def post(self):
        method = self.get_argument('method')
        pretty = int(self.get_argument('pretty', '0'))
        request = Network.Web.Request(self, method, pretty)
        if method == 'send':
            sid = self.get_argument('sid')
            auid = int(self.get_argument('recipient'))
            project = self.get_argument('project')
            try:        
                messages = json.loads(self.request.body)
            except Exception, details:
                return request.Fail(EC.MESSAGE_BAD_FORMAT, 'Message bad format %r' % str(details))
            if type(messages) == list:
                self.entity.Send(request, sid, auid, project, messages)
            else:
                raise TypeError("'messages' should have 'list' type")
        if method == 'send_nl':
            sender = self.get_argument('sender')
            auid = int(self.get_argument('recipient'))
            project = self.get_argument('project')
            try:        
                messages = json.loads(self.request.body)
            except Exception, details:
                print 'Message bad format %r\nBody: %r' % ( str(details), self.request.body )
                return request.Fail(EC.MESSAGE_BAD_FORMAT, 'Message bad format %r' % str(details))
            if type(messages) == list:
                self.entity.SendNoLogin(request, sender, auid, project, messages)
            else:
                raise TypeError("'messages' should have 'list' type")
        elif method == 'purge':
            sid = self.get_argument('sid')
            try:        
                messages = json.loads(self.request.body)
                if type(messages) == list:
                    self.entity.Purge(request, sid, messages)
                else:
                    raise TypeError("'messages' should have 'list' type")
            except Exception, details:
                request.Fail(EC.MESSAGE_BAD_FORMAT, 'Message bad format %r' % str(details))
        else:
            request.Fail(EC.UNSUPPORTED_METHOD, 'Unsupported method %r' % method)

    @tornado.web.asynchronous
    def get(self):
        method = self.get_argument('method')
        pretty = int(self.get_argument('pretty', '0'))
        request = Network.Web.Request(self, method, pretty)
        if method == 'login':
            project = self.get_argument('project')
            auid = int(self.get_argument('auid'))
            period = int(self.get_argument('period', '5'))
            force = int(self.get_argument('force', '0'))
            url = self.get_argument('url', None)
            self.entity.Login(request, project, auid, period, url, force)
        elif method == 'logout':
            sid = self.get_argument('sid')
            self.entity.Logout(request, sid)
        elif method == 'retrieve':
            sid = self.get_argument('sid')
            self.entity.Retrieve(request, sid)
        elif method == 'getdata':
            self.entity.GetData(request)
        else:
            request.Fail(EC.UNSUPPORTED_METHOD, 'Unsupported method %r' % method)

class M:

    def __init__(self, body, expirePeriod=None):
        self.body = body
        self.timeExpire = None
        self.timeAccess = None
        if expirePeriod > 0:
            self.timeExpire = time.time()+expirePeriod
            
    def Block(self, nextTime):
        self.timeAccess = nextTime

class MS:

    def __init__(self):
        self.msgId = 0
        self.messages = {}

    def Send(self, sender, messages, block=False, blockPeriod=0):
        result = {}
        for message in messages:
            message['dt_rcv'] = int(time.time())
            message['sender'] = sender
            message = M(message, message.get('tm_expire', 0))
            msgId = self.msgId
            self.msgId += 1
            self.messages[msgId] = message
            if block:
                message.Block(blockPeriod)
                result[msgId] = message.body
        return result

    def Count(self):
        return len(self.messages)

    def Retrieve(self, blockPeriod):
        result = {}
        removed = []
        curTime = time.time()
        for msgId, message in self.messages.items():
            if message.timeExpire != None and curTime >= message.timeExpire:
                removed.append(msgId)
            elif message.timeAccess == None or curTime >= message.timeAccess:
                message.Block(curTime+blockPeriod)
                result[msgId] = message.body
        for msgId in removed:
            del self.messages[msgId]
        return (result, len(removed) > 0 or len(result) > 0)

    def Purge(self, messages):
        success = []
        failure = []
        for msgId in messages:
            if msgId in self.messages:
                success.append(msgId)
            else:
                failure.append(msgId)
        for msgId in success:
            del self.messages[msgId]
        return success, failure

import pickle
class Database:

    def __init__(self, project, config):
        self.project = project
        self.config = config
        if not os.path.isdir(config.db_path):
            os.makedirs(config.db_path)
        self.db = shelve.open(os.path.join(config.db_path, project+'.dat'), protocol=pickle.HIGHEST_PROTOCOL)
        self.isDirty = False
        self.isOpen = True
    
    def __del__(self):
        if self.isOpen:
            self.db.close()

    def Save(self, key, value):
        if self.isOpen: 
            self.db[key] = value
            self.isDirty = True
        
    def Load(self, key):
        if self.isOpen and self.db.has_key(key):
            return self.db[key]
    
    def Update(self):
        if self.isOpen and self.isDirty:
            self.db.sync()
            self.isDirty = False

    def Close(self):
        self.db.close()
        self.isOpen = False

class Context:

    def __init__(self, auid, db):
        self.auid = auid 
        self.sid = None
        self.db = db
        self.url = None
        self.key = 'r'+str(self.auid)
        self.messages = self.db.Load(self.key)
        if not self.messages:
            self.messages = MS()
            self.db.Save(self.key, self.messages)

    def OnPush(self, data, message):
        if not message and data:
            self.Purge(data)

    def Online(self, sid, url, period):
        self.sid = sid
        self.url = url
        self.period = period
    
    def IsOnline(self):            
        return self.sid != None

    def Offline(self):
        self.sid = None
        self.url = None

    def Purge(self, messages):
        success, failure = self.messages.Purge(messages)
        if len(success) > 0:
            self.db.Save(self.key, self.messages)
        return success, failure

    def SendMessages(self, sender, messages):
        if self.url:
            result = self.messages.Send(sender, messages, True, self.period)
        else:
            result = self.messages.Send(sender, messages)
        self.db.Save(self.key, self.messages)
        return result, self.messages.Count()

    def Count(self):
        return self.messages.Count()

    def RetrieveMessages(self):
        result, changed = self.messages.Retrieve(self.period)
        if changed:
            self.db.Save(self.key, self.messages)
        return result, self.messages.Count()

import shelve

class Sessions:

    def __init__(self):
        self.sessions = {}
        self.sid = 0

    def Get(self, sid):
        return self.sessions.get(sid, None)

    def Register(self, context, project, url, period):
        if context.IsOnline():
            self.Unregister(context)
        sid = project+str(self.sid)
        self.sid += 1
        context.Online(sid, url, period)
        self.sessions[sid] = context
        return sid

    def Unregister(self, context):
        sid = context.sid
        context.Offline()
        del self.sessions[sid]

    def Count(self):
        return len(self.sessions)

class Contexts:

    def __init__(self, db, sessions):
        self.sessions = sessions
        self.auids = {}
        self.db = db
        self.online = 0

    def GetByAuid(self, auid):
        context0 = self.auids.get(auid, None)
        if context0:
            if context0.sid != None:
                context1 = self.sessions.Get(context0.sid)
                if context1 == context0:
                    return context0
                raise Exception('Violation detected')
            else:
                return context0
        return None
            
    def Create(self, auid):
        context = Context(auid, self.db)
        self.auids[auid] = context
        return context

    def Online(self, context, url, period):
        if not context.IsOnline():
            self.online += 1
        self.sessions.Register(context, self.db.project, url, period)

    def Offline(self, context):
        self.sessions.Unregister(context)
        self.online -= 1

    def Count(self):
        return (self.online, len(self.auids))

class ProjectProcessor:

    def __init__(self, config, project, sessions, link):
        self.config = config
        self.db = Database(project, config)
        self.contexts = Contexts(self.db, sessions)
        self.link = link

    def GetData(self):
        result = {}
        online, loaded = self.contexts.Count()
        result['online'] = online
        result['loaded'] = loaded
        return result

    def Login(self, request, auid, period, url=None, force=0):
        context = self.contexts.GetByAuid(auid)
        if not context:
            context = self.contexts.Create(auid)
        if context.IsOnline():
            if not force:
                context = None
        if context:
            self.contexts.Online(context, url, period)
            result = {
                'sid' : context.sid
            }
            messages, count = context.RetrieveMessages()
            if len(messages) > 0:
                result['messages'] = messages
            if count > 0:
                result['count'] = count
            request.Finish(result)
        else:
            request.Fail(EC.USER_ALREADY_LOGGEDIN, 'User %r already logged in' % auid)

    def Send(self, request, context, recipient, messages):
        context1 = self.contexts.GetByAuid(recipient)
        if not context1:
            context1 = self.contexts.Create(recipient)
        messages, count = context1.SendMessages(context.auid, messages)
        if len(messages) > 0:
            result = {'messages' : messages, 'count' : count }
            self.link.fetch({'method':'send', 'auid' : context1.auid, 'project' : context1.db.project},  context1.OnPush, result, url=context1.url)
        count = context.Count()
        if count > 0:
            request.Finish({'count': count})
        else:
            request.Finish()

    def SendNoLogin(self, request, sender, recipient, messages):
        context1 = self.contexts.GetByAuid(recipient)
        if not context1:
            context1 = self.contexts.Create(recipient)
        messages, count = context1.SendMessages(sender, messages)
        if len(messages) > 0:
            result = {'messages' : messages, 'count' : count }
            self.link.fetch({'method':'send', 'auid' : context1.auid, 'project' : context1.db.project},  context1.OnPush, result, url=context1.url)
        count = context1.Count()
        if count > 0:
            request.Finish({'count': count})
        else:
            request.Finish()

    def Logout(self, request, context):
        self.contexts.Offline(context)
        request.Finish()

class SocialExchange:

    def __init__(self, config, link):
        self.projects = {}
        self.sessions = Sessions()
        self.config = config
        self.link = link
    
    def GetData(self, request):
        projects = {}
        for project, processor in self.projects.items():
            projects[project] = processor.GetData()
        result = {
            'sessions' : self.sessions.Count(),
            'projects' : projects,
        }
        request.Finish(result)

    def Login(self, request, project, auid, period=5, url=None, force=0):
        if period < 0 or period > 30:
            return request.Fail(EC.PARAM_INVALID, 'Invalid param %r' % 'period')
        if project not in self.config.allowed_projects:
            return request.Fail(EC.PROJECT_NOT_ALLOWED, 'Project %r is not in list' % project)
            
        processor = self.projects.get(project, None)
        if not processor:
            processor = ProjectProcessor(self.config, project, self.sessions, self.link)
            self.projects[project] = processor
        processor.Login(request, auid, period, url, force)

    def Logout(self, request, sid):
        context = self.sessions.Get(sid)
        if context:
            processor = self.projects.get(context.db.project, None)
            if processor:
                processor.Logout(request, context)
            else:   
                request.Fail(EC.PROJECT_NOT_FOUND, 'Project %r not found' % context0.db.project)
        else:
            request.Fail(EC.SESSION_ALREADY_CLOSED, 'Session %r already closed' % sid)

    def Send(self, request, sid, recipient, project, messages):
        context0 = self.sessions.Get(sid)
        if context0:
            processor = self.projects.get(context0.db.project, None)
            if processor:
                processor.Send(request, context0, recipient, messages)
            else:   
                request.Fail(EC.PROJECT_NOT_FOUND, 'Project %r not found' % context0.db.project)
        else:
            request.Fail(EC.SESSION_NOT_FOUND, 'Session %r not found' % sid)

    def SendNoLogin(self, request, sender, recipient, project, messages):
        if project not in self.config.allowed_projects:
            return request.Fail(EC.PROJECT_NOT_ALLOWED, 'Project %r is not in list' % project)
        processor = self.projects.get(project, None)
        if not processor:
            processor = ProjectProcessor(self.config, project, self.sessions, self.link)
            self.projects[project] = processor
        processor.SendNoLogin(request, sender, recipient, messages)

    def Retrieve(self, request, sid):
        context = self.sessions.Get(sid)
        if context:
            processor = self.projects.get(context.db.project, None)
            if processor:
                result = {
                }
                messages, count = context.RetrieveMessages()
                if len(messages) > 0:
                    result['messages'] = messages   
                if count > 0:
                    result['count'] = count
                request.Finish(result)
            else:   
                request.Fail(EC.PROJECT_NOT_FOUND, 'Project %r not found' % context0.db.project)
        else:
            request.Fail(EC.SESSION_NOT_FOUND, 'Session %r not found' % sid)

    def Update(self):
        for processor in self.projects.values():
            processor.db.Update()

    def Stop(self):
        for processor in self.projects.values():
            processor.db.Close()

    def Purge(self, request, sid, messages):
        context = self.sessions.Get(sid)
        if context:
            success, failure = context.Purge(messages)
            result = {}
            if len(success) > 0:
                result['success'] = success
            if len(failure) > 0:
                result['failure'] = failure
            request.Finish(result)
        else:
            request.Fail(EC.SESSION_NOT_FOUND, 'Session %r not found' % sid)

class SocialExchangeService(Service):

    def __init__(self, sid):
        super(SocialExchangeService, self).__init__(sid)

    def Start(self, link, config):
        self.config = config
        self.link = link
        self.entity = SocialExchange(config, link)
        self.application = tornado.web.Application( [
            (r"/", SocialExchangeHandler, dict(entity=self.entity)),
        ] ) 
        self.http_server = tornado.httpserver.HTTPServer(self.application)
        self.http_server.listen(self.config.port)

        self.fsm.Move(Service.STARTED)
    
    def Update(self):
        self.entity.Update()
    
    def Stop(self, how):
        self.entity.Stop()
        self.fsm.Move(Service.STOPPED)
            
def main(args, gate):
    if args.config:
        config = System.config.RawConfig(args.config)
    else:
        config = System.config.RawConfig({'port' : 10000, 'db_path' : os.path.expanduser('~/se'), 'allowed_projects' : ['pw', 'em']})

    svn = SocialExchangeService(args.sid)

    gate.AddService(svn, config)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--config', default=None, help='Config path')
    parser.add_argument('--sid', default='Service', help='Service id')
    parser.add_argument('--log', default=None, help='Log file name')
    parser.add_argument('--loglevel', choices=['debug', 'info','warning','error', 'critical'], default='info', help='Logging severity level')
    args = parser.parse_args()

    System.logs.setup(args.log, args.loglevel)
    gate = Network.SOA.ServiceGate()

    main(args, gate)
    gate.Run()
