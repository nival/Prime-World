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
import tornado.httpclient
import urllib
import json
import hashlib
import base64
import time
import threading
import imp
import datetime

import Network
import Network.HttpClient
from Network.SOA import Service

import logging
from logging import debug, info, error, warning

NO_USER = 1
BAD_PARAM = 2
NO_PARTNER = 3
USER_CREATION_FAIL = 4
ALREADY_LINKED = 5
NO_MUID = 6

sides = {
    '-1' : 'unknown',
    '0' : 'docts',
    '1' : 'adornians',
}

start_mode = {
    '0' : 'session_start_training',
    '1' : 'session_start_pvp',
}

class Callback:

    def __init__(self, rid, callback, url,data=None):
        self.rid = rid
        self.callback = callback
        self.url = url
        self.data = data

    def __call__(self, data, error):
        self.callback(self.rid, error == None)

class Data:
    
    def __init__(self):
        self.rid = 0
        self.requests = []

    def Allocate(self):
        rid = self.rid
        self.rid += 1
        self.requests.append(rid)
        return rid

    def Complete(self, rid):
        self.Remove(rid)

    def Remove(self, rid):
        self.requests.remove(rid)

import ShelveDb
class RequestDatabase:

    def __init__(self, path, flushPeriod):
        self.db = ShelveDb.ShelveDatabase(path, flushPeriod)
        if not self.db.has_key('data'):
            self.data = Data()
        else:
            rid, requests = self.db['data']
            self.data = Data()
            self.data.rid = rid
            self.data.requests = requests
            info('Pending queue length: %d' % len(self.data.requests))
        self.sent = {}
        self.sentTotal = 0
        self.sentSuccessTotal = 0

    def Update(self):
        self.db.Update()

    def __del__(self):
        self.Flush(True)

    def GetCount(self):
        return len(self.sent)

    def GetPendingCount(self):
        return len(self.data.requests)

    def AddRequest(self, url, callback=None,data=None):                        
        rid = self.data.Allocate()        
        self.db[str(rid)] = (url,data)
        if callback:
            self.sentTotal += 1
            self.sent[rid] = True
            cb = Callback(rid, callback, url,data)            
            return cb
        return None

    def ResetSuccessRate(self):
        if self.sentTotal > 0:
            result = self.sentSuccessTotal/float(self.sentTotal)
        else:
            result = -1.0
        self.sentSuccessTotal = 0
        self.sentTotal = 0
        return result

    def FinishRequest(self, rid, succeded):
        del self.sent[rid]
        if succeded:
            self.sentSuccessTotal += 1
            self.data.Complete(rid)
            del self.db[str(rid)]

    def PopRequests(self, sim_count, callback):
        callbacks = []
        count = sim_count-len(self.sent)
        if count <= 0:
            return callbacks

        i = 0
        removed = []        
        while len(callbacks) < count:            
            if i < len(self.data.requests):
                rid = self.data.requests[i]
                if rid not in self.sent:
                    url, data = self.FetchData(rid)                    
                    if url:
                        self.sent[rid] = True                        
                        cb = Callback(rid, callback, url,data)                        
                        callbacks.append(cb)
                    else:
                        removed.append(rid)
                i += 1
            else:
                break
        for rid in removed:
            warning('Request not found in db, skipping (rid=%d)' % rid)
            self.data.Remove(rid)
        self.sentTotal += len(callbacks)
        return callbacks

    def FetchData(self, rid):
        key = str(rid)
        try:
            if self.db.has_key(key):
                return self.db[key]
        except:
            pass
        return None

    def Flush(self, close=False):
        if self.db.IsClosed():
            return
        info('Flushing db, pending queue length: %d' % len(self.data.requests))
        self.db['data'] = (self.data.rid, self.data.requests)
        self.db.Flush(close)

    def Stop(self):
        self.Flush(True)

class PersistentQueue:

    ACTIVE = 0
    STOPPING = 1
    STOPPED = 2

    def __init__(self, http_client, config, db_path):
        self.http_client = http_client
        self.config = config
        self.db = RequestDatabase(db_path, self.config.flush_period)
        self.status = PersistentQueue.ACTIVE
        self.requestRate = self.config.start_request_rate
        self.requestRateTime = time.time() + self.config.rate_period

    def GetData(self):
        result = {
            'pending' : self.db.GetPendingCount(),
            'rate' : self.requestRate,
        }
        return result

    def Push(self, url, _data=None):        
        _url = url.replace(' ', '%20')
        if _url == url:
            if self.db.GetCount() < self.requestRate:            
                callback = self.db.AddRequest(_url, self.FinishRequest,_data)            
                self.Start(callback)
            else:                        
                self.db.AddRequest(_url, None,_data)        
            return True
        error("Pushed url is not valid, skipped (value=%r)" % _url)
        return False

    def FinishRequest(self, rid, succeeded):
        self.db.FinishRequest(rid, succeeded)        
        if succeeded and self.db.GetCount() < self.requestRate and self.requestRate > 1 and self.status == PersistentQueue.ACTIVE:
            self.FetchRequests(self.requestRate-1)            

    def Start(self, callback,data=None):                   
        self.http_client.fetch(callback.url, callback, data=callback.data,accept_json=False)

    def AdjustRequestRate(self):
        coeff = self.db.ResetSuccessRate()
        requestRate = self.requestRate    
        if coeff >= 0:
            if coeff > 0.99 and coeff < 1.05:
                requestRate += self.config.request_rate_delta
                if requestRate > self.config.max_request_rate:
                    requestRate = self.config.max_request_rate
            else:
                requestRate = int(requestRate*coeff)
                if requestRate < 1:
                    requestRate = 1
        if self.requestRate != requestRate:
            self.requestRate = requestRate
            info("Request rate adjusted (coeff=%2.1f value=%d)" % (coeff, self.requestRate))

    def FetchRequests(self, requestRate):
        callbacks = self.db.PopRequests(requestRate, self.FinishRequest)
        for callback in callbacks:
            self.Start(callback)
        return len(callbacks)

    def Update(self):
        self.db.Update()
        curTime = time.time()
        if curTime > self.requestRateTime:
            self.AdjustRequestRate()
            self.requestRateTime = curTime + self.config.rate_period

        if self.status == PersistentQueue.ACTIVE:
            fetchedCount = self.FetchRequests(self.requestRate)
            if fetchedCount > 0:
                debug('Requests added (count=%d left=%d)' % (fetchedCount, self.db.GetCount()))
        elif self.status == PersistentQueue.STOPPING and self.db.GetCount() == 0:
            self.db.Stop()
            self.status = PersistentQueue.STOPPED
        
    def Shutdown(self):
        info('Disabling immediate send (left=%d)' % self.db.GetCount())
        self.status = PersistentQueue.STOPPING

    def IsStopped(self):
        return self.status == PersistentQueue.STOPPED

class Entity:

    def Save(self):
        result = {}
        for name, value in self.__class__.names:
            result[name] = self.__dict__.get(name, value)
        return result    
        
    def Load(self, data):  
        for name, value in self.__class__.names:
            self.__dict__[name] = data.get(name, value)

    def FillDefaults(self):
        for name, value in self.__class__.names:
            if type(value) == dict:
                self.__dict__[name] = dict(value)  
            else:
                self.__dict__[name] = value  
                 
class User(Entity):
    # data legend
    # fs - session types played 
    # fc - first login
    # ka - was registered
    # fr - first resource spent

    prefix = 'u'
    names =[ ('su', None), ('partner', None), ('program', None), ('fc', False), ('fs', {}), ('fr', False), ('ka', False), ('puid', None), ('auid', None),  ('subid', None), ('regc', 0.0), ('regl', 0.0), ('clogins', 0), ('cregs', 0), ('ctutorial', 0), ('clinstall', 0)]

    def __init__(self, muid, auid=None):
        self.muid = muid
        self.FillDefaults()
        self.auid = auid
        self.pdata = None
                
    def GetKey(self):
        return self.muid

class Partner(Entity):

    prefix = 'p'
    names = [('su', 0), ('code', None)]

    def __init__(self, partner):
        self.partner = partner
        self.FillDefaults()

    def GetKey(self):
        return self.partner

    def GenerateSu(self):
        su = self.su
        self.su +=1
        return self.code+'%06x' % su
        
class CachedStorage:

    def __init__(self, db, sclass):
        self.db = db
        self.items = {}
        self.sclass = sclass
    
    def Get(self, key):
        item = self.items.get(key, None)   # trying find in cache
        if item:
            return item
        else:
            dbKey = self.sclass.prefix+str(key)
            try:
                data = self.db[dbKey]
            except:
                data = None
            if data:
                #debug('Loaded data (key=%s data=%r)' % (dbKey, data))
                item = self.sclass(key)
                item.Load(data)
                self.items[key] = item  # save item in cache
                return item
        return None            
        
    def Save(self, item):    
        key = item.GetKey()
        data = item.Save()
        dbKey = item.prefix+str(key)
        self.db[dbKey] = data
        self.items[key] = item
        #debug('Saving data (key=%s data=%r)' % (dbKey, data))

class UserDatabase:

    def __init__(self, path, pdata, flushPeriod): 
        self.db = ShelveDb.ShelveDatabase(path, flushPeriod)
        self.pdata = pdata
        self.users = CachedStorage(self.db, User)
        self.partners = CachedStorage(self.db, Partner)
        info('Database loaded (max_muid=%s)', self.db['muid'])

    def Flush(self, close=False):
        self.db.Flush(close)

    def Stop(self):
        self.Flush(True)
        
    def FlushUser(self, user):  # no callbacks
        self.users.Save(user)
        
    def LinkUserToAuid(self, callback, user, _auid):
        auid = str(_auid)
        self.db['l'+auid] = user.muid
        user.auid = _auid 
        user.regl = time.time()
        self.users.Save(user)
        callback(user)

    def _LoadUser(self, muid):
        user = self.users.Get(muid)
        if user:
            user.pdata = self.pdata.get(user.partner, None)
        return user

    def GetUserByAuid(self, _auid, callback):
        auid = str(_auid)
        try:
            muid = self.db['l'+auid]
        except KeyError:
            muid = None
        if muid != None:
            user = self._LoadUser(muid)
            if user and user.auid == None:
                user.auid = _auid   
                self.users.Save(user)
            callback(user)
        else:    
            callback(None)
        
    def GetUser(self, muid, callback):
        user = self._LoadUser(muid)
        callback(user)

    def GetCurrentMuid(self):
        try:
            muid = self.db['muid']
        except KeyError:
            muid = 1
        return muid
        
    def Update(self):
        self.db.Update()

    def GenerateMuid(self):
        muid = self.db.get('muid', 0)+1
        self.db['muid'] = muid
        return muid    

    def LinkPartner(self, callback, user, _partner, program=None, puid=None, subid=None):
        if self._LinkPartner(user, _partner, program, puid, subid):
            callback(user)
        else:
            callback(None)

    def _LinkPartner(self, user, _partner, program=None, puid=None, subid=None):
        info('Linking partner (muid=%r partner=%r puid=%r subid=%r)' % (user.muid,  _partner, puid, subid))
        partner = self.partners.Get(_partner)
        if not partner:
            if _partner == None:
                _partner = 'pw'
            pdata = self.pdata.get(_partner, None)
            if not pdata:
                warning('Partner info not found, using default (partner=%r)' % _partner)
                pdata = self.pdata.get('pw', None)
            if not pdata:
                return False 
            else:
                partner = Partner(_partner)
                partner.code = pdata.code
        else:
            pdata = self.pdata.get(_partner, None)
        user.su = partner.GenerateSu()
        user.partner = _partner
        user.program = program      
        user.subid = subid
        user.puid = puid
        user.pdata = pdata
        self.partners.Save(partner)
        self.users.Save(user)
        return True

    def CreateUser(self, callback, default_partner, auid=None):
        muid = self.GenerateMuid()
        info('Creating user (muid=%r partner=%r auid=%s)' % (muid, default_partner, auid))
        user = User(muid, auid)
        user.regc = time.time()
        self.users.Save(user)        
        if auid != None:
            self.db['l'+str(auid)] = user.muid
        self._LinkPartner(user, default_partner)
        callback(user)
        
class _CustomCallback:

    def __init__(self, _callback, request, args):
        self.__callback = _callback
        self.__args = args
        self.__request = request
        self.__error = None

    def GetArgs(self):
        return self.__args
        
    def SetError(self, error):
        self.__error = error

    def SetRequest(self, request):
        self.__request = request
    
    def __call__(self, result):   
        if not result and self.__error != None:
            self.__request.Fail(*self.__error)
            return 
        self.__callback(self.__request, result, **self.__args)

class UserCallback(_CustomCallback):

    def __init__(self, _callback, request, **args):
        _CustomCallback.__init__(self, _callback, request, args)
        self.SetError( (NO_USER, 'User not found') )
        
class CustomCallback(_CustomCallback):

    def __init__(self, _callback, request, **args):
        _CustomCallback.__init__(self, _callback, request, args)

class EventCollection:

    def __init__(self):
        self.callbacks = []
        self.partner = None

    def SetPartner(self, value):
        self.partner = value            

    def Bind(self, callback):
        self.callbacks.append( (callback, self.partner) )

    def __call__(self, user, *args):
        for callback, partner in self.callbacks:
            if not partner or user.partner == partner:
                callback(user, *args)

class Events:

    def __init__(self):
        self.events = []
        events = [
          "OnLandingRegister",
          "OnLandingLogin",
          "OnRegister",
          "OnBeginInstall",
          "OnCancelInstall",
          "OnLaunchInstall",          
          "OnBeginDownload",
          "OnEndInstall",
          "OnReInstall",
          "OnUnInstall",
          "OnDownloadClientBegin",
          "OnDownloadClientEnd",
          "OnSelectFaction",
          "OnCastleLogin",
          "OnFirstLogin",
          "OnSessionStart",
          "OnFirstSessionStart",
          "OnFirstSpentResource",
          "OnSpentResource",
          "OnPayment",
          "OnFirstCastleLogin",
          "OnPageView",
          "OnCreateMuid",
          "OnLinkPartner",
          "OnQuest",
          "OnHeroLevel",
          "OnHeroRank",
          "OnCastleLevel",
        ]
        for name in events:
            self._RegisterEvent(name)

    def _RegisterEvent(self, name):
        collection = EventCollection()
        self.__dict__[name] = collection
        self.events.append(collection)

    def SetModule(self, name, partner):
        self.name = name
        for event in self.events:
            event.SetPartner(partner)

def GetInt(value):
    try:
        return int(value)
    except:
        return None

def GetBool(value):
    if value in ['false', '0', 'False']:
        return False
    if value in ['true', '1', 'True']:
        return True
    return False

def GetFloat(value):
    try:
        return float(value)
    except:
        return None

class DummyRequest:

    def Finish(self, data=None):
        if data:     
            self.data = data
        else:
            self.data = {}

def ApplyEvents(user, queue, processor):
    events = queue.Retrieve(user.auid)
    request = DummyRequest()
    if len(events) > 0:
        for event in events:
            etype = event.get('etype', None)
            if etype != None:
                if etype == 'CastleLogin':
                    processor._CastleLogin(request, user, **event)
                elif etype == 'SessionStart':
                    processor._SessionStart(request, user, **event)
                elif etype == 'SelectFaction':
                    processor._SelectFaction(request, user, **event)
                elif etype == 'DownloadClientBegin':
                    processor._DownloadClientBegin(request, user, **event)
                elif etype == 'DownloadClientEnd':
                    processor._DownloadClientEnd(request, user, **event)
                elif etype == 'ChangeResource':
                    processor._ChangeResource(request, user, **event)
                elif etype == 'MakePayment':
                    processor._MakePayment(request, user, **event)
                elif etype == 'ProcessQuest':
                    processor._ProcessQuest(request, user, **event)
                elif etype == 'ProcessHeroLevel':
                    processor._ProcessHeroLevel(request, user, **event)
                elif etype == 'ProcessHeroRank':
                    processor._ProcessHeroRank(request, user, **event)
                elif etype == 'ProcessCastleLevel':
                    processor._ProcessCastleLevel(request, user, **event)
                else:
                    error('Unsupported event type %r' % event)
            else:
                error('Event type not defined')
        queue.Clear(user.auid)
        info('Delayed events processed (auid=%r ecount=%d)' % (user.auid, len(events)))
    return len(events)

class LinkProxyRequest:

    def __init__(self, user, request, queue, processor):
        self.user = user
        self.request = request
        self.queue = queue
        self.processor = processor

    def Finish(self, data=None):
        if data is None:            
            data = {}
        n = ApplyEvents(self.user, self.queue, self.processor)
        self.request.Finish(data)

class UserLoader:

    def __init__(self, db, eventsQueue, processor):
        self.db = db 
        self.eventsQueue = eventsQueue
        self.processor = processor

    def _EnsureUser4(self, request, user, callback):
        #debug("UserLoader._EnsureUser5(%r, %r, %r) " % request, user, callback)
        callback(user)
        
    def _EnsureUser5(self, request, user, callback):
        #debug("UserLoader._EnsureUser5(%r, %r, %r) " % (request, user, callback))
        if user:
            proxyRequest = LinkProxyRequest(user, request, self.eventsQueue, self.processor)
            callback.SetRequest(proxyRequest)
        callback(user)

    def _EnsureUser3(self, request, user, auid, callback, partner):
        #debug("UserLoader._EnsureUser3(%r, %r, %r, %r, %r) " % (request, user, auid, callback, partner))
        if not user:  # user wasn't found
            cb = UserCallback(self._EnsureUser5, request, callback=callback)
            callback.SetError( (USER_CREATION_FAIL, "Muid creation fail" ) )
            self.db.CreateUser(cb, partner, auid=auid)  # create user and attach him to auid
        else:
            proxyRequest = LinkProxyRequest(user, request, self.eventsQueue, self.processor)
            callback.SetRequest(proxyRequest)
            cb = UserCallback(self._EnsureUser4, proxyRequest, callback=callback)
            self.db.LinkUserToAuid(cb, user, auid)
    
    def _EnsureUser2(self, request, user, auid, muid, callback, partner, create_new):
        #debug("UserLoader._EnsureUser2(%r, %r, %r, %r, %r, %r, %r) " % (request, user, auid, muid, callback, partner, create_new))
        if user:
            callback(user)
        elif muid != None:  # no attached to auid user found
            cb = CustomCallback(self._EnsureUser3, request, auid=auid, callback=callback, partner=partner)
            cb.SetError(None)
            self.db.GetUser(muid, cb)    # trying to find user
        else:   # no muid defined, need to create new user    
            if create_new:
                self._EnsureUser3(request, None, auid, callback, partner) 
            else:
                ecount = self.eventsQueue.Push(auid, callback.GetArgs())
                info('Pushed delayed event (auid=%r ecount=%d)' % (auid, ecount))
                callback.SetError( (NO_MUID, 'Muid not found, event queued') )
                callback(None)

    def Process(self, callback, request, auid, muid=None, partner=None, create_new=False):
        # check auid validity
        #debug("UserLoader.Process(%r, %r, %r, %r, %r, %r) " % (callback, request, auid, muid, partner, create_new))
        iauid = GetInt(auid)        
        if iauid == None:
            request.Fail(BAD_PARAM, 'Bad param auid')
            return None

        # if muid defined check muid validity
        imuid = None
        if muid != None:
            imuid = GetInt(muid)        
        cb = CustomCallback(self._EnsureUser2, request, auid=iauid, muid=imuid, callback=callback, partner=partner, create_new=create_new)   
        cb.SetError(None)
        self.db.GetUserByAuid(iauid, cb)  # trying to find link between auid and muid

    def GetUser(self, _muid, callback):
        muid = GetInt(_muid)
        if muid == None:
            callback(None)
        self.db.GetUser(muid, callback)

def ParseAuidFromUser(user):
    i = len(user)-1
    while str(user[i]).isdigit() and i >= 0:
        i -= 1
    auid = user[i+1:] 
    return (auid or None)

class _MarketingService:

    ACTIVE = 0
    STOPPING = 1
    STOPPED = 2

    def __init__(self, config, loader=None):
        self.loader = loader
        self.config = config
        self.status = _MarketingService.ACTIVE
        self.db = UserDatabase(self.config.db, self.config.partners, self.config.flush_period)    

        self.events = Events()

        self.eventsDb = ShelveDb.ShelveDatabase(self.config.edb, self.config.flush_period)
        self.eventsQueue = ShelveDb.PersistentEventsQueue(self.eventsDb)

        self.users = UserLoader(self.db, self.eventsQueue, self)

        modules = []
        if config.modules:
            modules.extend(config.modules.keys())
        info('Loading modules (modules=%r)' % modules)

        for name in modules:
            module = self.loader.Load(name, config.modules.get(name, System.config.RawConfigWrapper()))
            if module:
                info('Module loaded successfully (name=%r)' % name)
                self.events.SetModule(name, module.GetPartner())
                module.Install(self.events)
            else:
                warning('Module not loaded, skipping (module=%r)' % name)

    def GetData(self):                                       
        result = {
            'muid' : self.db.GetCurrentMuid(),
            'events' : {
                'eid' : self.eventsDb.get('eid', 0),
                'ucount' : self.eventsDb.get('ucount', 0),
                'ecount' : self.eventsDb.get('ecount', 0),
            }
        }
        return result

    def _GetMuid(self, muid):
        if muid:
            muid = muid.strip()
            if muid == 'PrimeWorld_rutracker':
                return None, 'rut'
            muid = muid.replace('PWSetup_', '')
            if muid:
                if muid in self.config.muid_presets:
                    return None, muid
                return DecodeKey(muid), None
        return None, None

    def _CreateMuid(self, request, user):
        result = { 'muid' : EncodeKey(user.muid) }
        result['new'] = True
        request.Finish(result)
    
    def CreateMuid(self, request):
        callback = UserCallback(self._CreateMuid, request)
        callback.SetError( (USER_CREATION_FAIL, "Muid creation fail" ) )
        self.db.CreateUser(callback, 'pw')

    def _OnReturn(self, request, user):
        create_new = False
        if not user:
            create_new = True
        else:
            delta = datetime.datetime.fromtimestamp(time.time())-datetime.datetime.fromtimestamp(user.regc)
            period = delta.days*24*3600+delta.seconds
            create_new = (user.auid == None and period >= self.config.expire_muid_period)
        if create_new:
            callback = UserCallback(self._CreateMuid, request)
            callback.SetError( (USER_CREATION_FAIL, "Muid creation fail" ) )
            self.db.CreateUser(callback, 'pw')
            return 
        result = { 'muid' : EncodeKey(user.muid) }
        request.Finish(result)

    def _OnLinkPartner(self, request, user):
        self.events.OnCreateMuid(user)
        self.events.OnRegister(user)
        request.Finish()

    def _EnsureUserSent(self, user):
        if not user.ka:
            user.ka = True
            self.events.OnCreateMuid(user)
            self.events.OnRegister(user)
            self.db.FlushUser(user)
        
    def _LinkPartner(self, request, user, partner, program, puid, subid):
        if not user.ka:
            callback = UserCallback(self._OnLinkPartner, request)
            callback.SetError( (NO_PARTNER, "Partner %r not found" % partner ) )
            self.db.LinkPartner(callback, user, partner, program, puid, subid)
            user.ka = True
            self.db.FlushUser(user)
            self.events.OnLinkPartner(user)
        else:
            request.Fail(ALREADY_LINKED, 'Already linked')
        
    def _BeginDownload(self, request, user):
        self._EnsureUserSent(user)                    
        self.events.OnBeginDownload(user)
        request.Finish()
        
    def _BeginInstall(self, request, user):
        self._EnsureUserSent(user)
        self.events.OnBeginInstall(user)
        request.Finish()
    
    def _EndInstall(self, request, user):
        self._EnsureUserSent(user)                    
        self.events.OnEndInstall(user)
        request.Finish()

    def _LaunchInstall(self, request, user):
        self._EnsureUserSent(user)
        user.clinstall += 1
        self.db.FlushUser(user)
        self.events.OnLaunchInstall(user)
        request.Finish()
        
    def _CancelInstall(self, request, user):
        self._EnsureUserSent(user)                    
        self.events.OnCancelInstall(user)
        request.Finish()
        
    def _Reinstall(self, request, user):
        self._EnsureUserSent(user)                    
        self.events.OnReInstall(user)
        request.Finish()

    def _Uninstall(self, request, user):
        self._EnsureUserSent(user)                    
        self.events.OnUnInstall(user)
        request.Finish()    

    def _DownloadClientBegin(self, request, user, etype):
        self._EnsureUserSent(user)                    
        self.events.OnDownloadClientBegin(user)
        request.Finish()
            
    def _DownloadClientEnd(self, request, user, etype):
        self._EnsureUserSent(user)                    
        self.events.OnDownloadClientEnd(user)
        request.Finish()
        
    def _SelectFaction(self, request, user, etype, faction):
        self._EnsureUserSent(user)                    
        self.events.OnSelectFaction(user)
        request.Finish()     
        
    def _LandingRegister(self, request, user):  
        self._EnsureUserSent(user)    
        if user.muid > self.config.min_muid_to_send_postback:                
            self.events.OnLandingRegister(user)
        result = {
            'muid' : user.muid,
        }
        request.Finish(result)
        
    def _LandingLogin(self, request, user):  
        self._EnsureUserSent(user)                    
        self.events.OnLandingLogin(user)
        result = {
            'muid' : user.muid,
        }
        request.Finish(result)
        
    def _FirstLogin(self, request, user):
        self._EnsureUserSent(user)
        user.cregs += 1          
        self.db.FlushUser(user)
        if user.muid > self.config.min_muid_to_send_postback:                  
            self.events.OnFirstLogin(user)                
        result = {
            'muid' : user.muid,
        }
        request.Finish(result)
            
    def _CastleLogin(self, request, user, etype, faction, auid):
        self._EnsureUserSent(user)                    
        if user.fc == False:
            if user.muid > self.config.min_muid_to_send_postback:
                self.events.OnFirstCastleLogin(user, faction)
            user.fc = True
        user.clogins += 1
        self.db.FlushUser(user)
        if user.muid > self.config.min_muid_to_send_postback:
            self.events.OnCastleLogin(user, sides[faction], auid)
        request.Finish()
            
    def _SessionStart(self, request, user, etype, faction, session_type, hero):
        self._EnsureUserSent(user)                    
        if session_type not in user.fs:
            self.events.OnFirstSessionStart(user, faction, start_mode[session_type], hero)
            user.fs[session_type] = True
            self.db.FlushUser(user)
        self.events.OnSessionStart(user, sides[faction], start_mode[session_type], hero)
        request.Finish()

    def _ProcessQuest(self, request, user, etype, data):
        self._EnsureUserSent(user)                    
        quid, status, tm = data                
        if str(quid) in self.config.id_tutorial and str(status)=="2":                       
            user.ctutorial += 1
            self.db.FlushUser(user)        
        if user.muid > self.config.min_muid_to_send_postback:
            self.events.OnQuest(user, quid, status, tm)
        request.Finish()

    def _ProcessHeroLevel(self, request, user, etype, data):
        self._EnsureUserSent(user)
        if user.muid > self.config.min_muid_to_send_postback:
            # heroid, level, tm = data
            self.events.OnHeroLevel(user, *data)
        request.Finish()

    def _ProcessHeroRank(self, request, user, etype, data):
        self._EnsureUserSent(user)
        if user.muid > self.config.min_muid_to_send_postback:
            # heroid, level, rank, rank_up, tm = data
            self.events.OnHeroRank(user, *data)
        request.Finish()

    def _ProcessCastleLevel(self, request, user, etype, data):
        self._EnsureUserSent(user)
        if user.muid > self.config.min_muid_to_send_postback:
            #level, tm = data
            self.events.OnCastleLevel(user, *data)
        request.Finish()

    def _ChangeResource(self, request, user, etype, data):
        self._EnsureUserSent(user)                    
        source, _gain, _goldchange, _silverchange, _perlchange, _resource1change, _resource2change, _resource3change = data
        gain = GetBool(_gain)
        goldchange = GetInt(_goldchange)
        silverchange = GetInt(_silverchange)
        perlchange = GetInt(_perlchange)
        resource1change = GetInt(_resource1change)
        resource2change = GetInt(_resource2change)
        resource3change = GetInt(_resource3change)

        if not user.fr:
            self.events.OnFirstSpentResource(user)
            user.fr = True
            self.db.FlushUser(user)

        if silverchange != 0:
            self.events.OnSpentResource(user, source, 'silver', silverchange, -1, gain)
        if goldchange != 0:
            self.events.OnSpentResource(user, source, 'gold', goldchange, -1, gain)
        if perlchange != 0:
            self.events.OnSpentResource(user, source, 'perl', perlchange, -1, gain)
        if resource1change != 0:
            self.events.OnSpentResource(user, source, 'resource1', resource1change, -1, gain)
        if resource2change != 0:
            self.events.OnSpentResource(user, source, 'resource2', resource2change, -1, gain)
        if resource3change != 0:
            self.events.OnSpentResource(user, source, 'resource3', resource3change, -1, gain)
        request.Finish()

    def _MakePayment(self, request, user, etype, data):
        self._EnsureUserSent(user)                    
        self.events.OnPayment(user, *data)
        request.Finish()
    # ----------------------------------------------------------------------------------------------
    def OnReturn(self, request, _muid):
        muid, dummy = self._GetMuid(_muid)        
        if muid == None:
            request.Fail(NO_USER, 'No such user')
            return 
        callback = UserCallback(self._OnReturn, request)
        callback.SetError(None)
        self.users.GetUser(muid, callback)

    def OnPageView(self, _muid, ip=None):
        muid, dummy = self._GetMuid(_muid)        
        if muid == None:
            warning('User not found: %r' % _muid)
        else:
            self.events.OnPageView(muid, ip)

    def LinkPartner(self, request, _muid, _partner, program=None, puid=None, subid=None):
        muid, dummy = self._GetMuid(_muid)        
        if muid == None:
            request.Fail(NO_USER, 'No such user')
            return 
        self.users.GetUser(muid, UserCallback(self._LinkPartner, request, partner=_partner, program=program, puid=puid, subid=subid))

    def BeginDownload(self, request, _muid):                     
        muid, partner = self._GetMuid(_muid)        
        if muid == None:
            muid = 0
        self.users.GetUser(muid, UserCallback(self._BeginDownload, request))

    def LaunchInstall(self, request, _muid):
        muid, partner = self._GetMuid(_muid)        
        if muid == None:
            muid = 0
        self.users.GetUser(muid, UserCallback(self._LaunchInstall, request))
        
    def BeginInstall(self, request, _muid):
        muid, partner = self._GetMuid(_muid)        
        if muid == None:
            muid = 0
        self.users.GetUser(muid, UserCallback(self._BeginInstall, request))

    def CancelInstall(self, request, _muid):
        muid, partner = self._GetMuid(_muid)        
        if muid == None:
            muid = 0
        self.users.GetUser(muid, UserCallback(self._CancelInstall, request))        
        
    def EndInstall(self, request, _muid):
        muid, partner = self._GetMuid(_muid)        
        if muid == None:
            muid = 0
        self.users.GetUser(muid, UserCallback(self._EndInstall, request))

    def Reinstall(self, request, _muid):
        muid, partner = self._GetMuid(_muid)        
        if muid == None:
            muid = 0
        self.users.GetUser(muid, UserCallback(self._Reinstall, request))

    def Uninstall(self, request, _muid):
        muid, partner = self._GetMuid(_muid)        
        if muid == None:
            muid = 0
        self.users.GetUser(muid, UserCallback(self._Uninstall, request))

    def LandingRegister(self, request, _muid, auid):
        muid, partner = self._GetMuid(_muid)        
        self.users.Process(UserCallback(self._LandingRegister, request), request, auid, muid, create_new=True)      

    def LandingLogin(self, request, _muid, auid):
        muid, partner = self._GetMuid(_muid)
        self.users.Process(UserCallback(self._LandingLogin, request), request, auid, muid, partner, create_new=True)         
        
    def FirstLogin(self, request, _muid, auid):
        muid, partner = self._GetMuid(_muid)
        self.users.Process(UserCallback(self._FirstLogin, request), request, auid, muid, partner, create_new=True)
            
    def DownloadClientBegin(self, request, auid):
        self.users.Process(UserCallback(self._DownloadClientBegin, request, etype='DownloadClientBegin'), request, auid)

    def DownloadClientEnd(self, request, auid):
        self.users.Process(UserCallback(self._DownloadClientEnd, request, etype='DownloadClientEnd'), request, auid)

    def SelectFaction(self, request, auid, faction):
        if faction not in sides.keys():
            request.Fail(BAD_PARAM, 'Bad param faction')
            return
        self.users.Process(UserCallback(self._SelectFaction, request, etype='SelectFaction', faction=faction), request, auid)        
    
    def CastleLogin(self, request, auid, faction):
        if faction not in sides.keys():
            request.Fail(BAD_PARAM, 'Bad param "faction"')
            return
        self.users.Process(UserCallback(self._CastleLogin, request, etype='CastleLogin', faction=faction, auid=auid), request, auid)
            
    def SessionStart(self, request, auid, faction, session_type, heroId, heroName, _pvp):
        pvp = GetBool(_pvp)
        if pvp == None:         
            request.Fail(BAD_PARAM, 'Bad param "pvp"')
            return
        if pvp:
            session_type = '1'
        else:
            session_type = '0'
        if session_type not in start_mode.keys():
            request.Fail(BAD_PARAM, 'Bad param "session_type"')
            return
        self.users.Process(UserCallback(self._SessionStart, request, etype='SessionStart', faction=faction, session_type=session_type, hero=heroName), request, auid)

    def ChangeResource(self, request, auid, source, gain, goldchange, silverchange, perlchange, resource1change, resource2change, resource3change):
        if gain not in ['True', 'False', 'false', 'true', '0', '1']:
            request.Fail(BAD_PARAM, 'Bad param "gain"')
            return
        data = (source, gain, goldchange, silverchange, perlchange, resource1change, resource2change, resource3change)
        self.users.Process(UserCallback(self._ChangeResource, request, etype='ChangeResource', data=data), request, auid)

    def ProcessQuest(self, request, auid, quid, status, tm=None):
        data = (quid, status, tm)
        self.users.Process(UserCallback(self._ProcessQuest, request, etype='ProcessQuest', data=data), request, auid)

    def ProcessHeroLevel(self, request, auid, heroid, level, tm=None):
        self.users.Process(
            UserCallback(self._ProcessHeroLevel, request, etype='ProcessHeroLevel', data=(heroid, level, tm)),
            request, auid)

    def ProcessHeroRank(self, request, auid, heroid, level, rank, up, tm=None):
        rank_up = 1 if GetBool(up) else 0
        self.users.Process(
            UserCallback(self._ProcessHeroRank, request, etype='ProcessHeroRank', data=(heroid, level, rank, rank_up, tm)),
            request, auid)

    def ProcessCastleLevel(self, request, auid, level, tm=None):
        self.users.Process(
            UserCallback(self._ProcessCastleLevel, request, etype='ProcessCastleLevel', data=(level, tm)),
            request, auid)

    def MakePayment(self, request, user, _value, source):
        ivalue = GetInt(_value)
        if ivalue == None:
            request.Fail(BAD_PARAM, 'Bad param "value"')
            return
        cvalue = int(ivalue*self.config.exchange_rate)
        data = (cvalue, source, ivalue)
        auid = ParseAuidFromUser(user)
        if auid:          
            self.users.Process(UserCallback(self._MakePayment, request, etype='MakePayment', data=data), request, auid)
        else:
            request.Fail(BAD_PARAM, 'Bad param user')

    def Update(self):
        if self.status == _MarketingService.STOPPING:
            self.db.Stop()
            self.eventsDb.Stop()
            self.status = _MarketingService.STOPPED        
        self.db.Update()
        self.eventsDb.Update()

    def Shutdown(self):
        self.status = _MarketingService.STOPPING 
        
    def IsStopped(self):
        return self.status == _MarketingService.STOPPED
        
encode = ['b','q','7','z','j','0','m','s','v','d','2','k','h','5','c','f','9','4','x','3','t','p','l','6','r','g','w','1','n','8']
dim = 30
decode = [5, 27, 10, 19, 17, 13, 23, 2, 29, 16, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 9, 0, 15, 25, 12, 0, 4, 11, 22, 6, 28, 0, 21, 1, 24, 7, 20, 0, 8, 26, 18, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]

def GenerateDecodeTable():
    mi = None
    ma = None
    for c in encode:
        if mi == None:
            mi = ord(c)
        else:
            mi = min(ord(c), mi)
        if ma == None:
            ma = ord(c)
        else:
            ma = max(ord(c), ma)
    d = [0]*ma
    for i, c in enumerate(encode):
        d[ord(c)-mi] = i
    print 'decode = '+repr(d)
    
def EncodeKey(n):
    r = ''
    if n < dim:
        return encode[n]
    while n != 0:
        r += encode[n % dim]
        n /= dim
    return r

def DecodeKey(r):
    if len(r) <= 1:
        return decode[ord(r[0])-48]
    l = dim
    n = decode[ord(r[0])-48]
    for c in r[1:]:
        n += l*decode[ord(c)-48]
        l *= dim
    return n

import tracking

class CvtHandler(tornado.web.RequestHandler):

    def initialize(self, config, service):
        self.config = config
        self.service = service

    @tornado.web.asynchronous
    def get(self):
        if self.service.status != _MarketingService.ACTIVE:
            raise tornado.web.HTTPError(403)
        muid = self.get_argument('muid')
        if self.get_argument('encode', '') == '1':
            muid_n = EncodeKey(int(muid))
        else:
            muid_n = DecodeKey(muid)
        self.finish(str(muid_n))   
            
            
class DoHandler(tornado.web.RequestHandler):

    def initialize(self, config, http_client, service, loader):
        self.http_client = http_client
        self.config = config
        self.service = service
        self.loader = loader

    @tornado.web.asynchronous
    def get(self):
        if self.service.status != _MarketingService.ACTIVE:
            raise tornado.web.HTTPError(403)
            
        method = self.get_argument('method')
        pretty = int(self.get_argument('pretty', '0'))
        request = Network.Web.Request(self, method, pretty, False)
        if method == 'resource_change':
            auid = self.get_argument('auid')
            source = self.get_argument('source')
            gain = self.get_argument('gain')
            goldchange  = self.get_argument('goldchange', 0)
            silverchange  = self.get_argument('silverchange', 0)
            perlchange = self.get_argument('perlchange', 0)
            resource1change = self.get_argument('resource1change', 0)
            resource2change = self.get_argument('resource2change', 0)
            resource3change = self.get_argument('resource3change', 0)
            self.service.ChangeResource(request, auid, source, gain, goldchange, silverchange, perlchange, resource1change, resource2change, resource3change)
        elif method == 'session_start':
            auid = self.get_argument('auid')
            faction = self.get_argument('faction')
            heroId = self.get_argument('heroid', None)
            heroName = self.get_argument('heroname', None)
            pvp = self.get_argument('pvp', 'True')
            sessiontype = self.get_argument('sessiontype', '1')
            self.service.SessionStart(request, auid, faction, sessiontype, heroId, heroName, pvp)
        elif method == 'castle_login':
            auid = self.get_argument('auid')
            faction = self.get_argument('faction')
            self.service.CastleLogin(request, auid, faction)
        elif method == 'create_muid':
            self.service.CreateMuid(request)
        elif method == 'launcher_start':
            request.Finish()
        elif method == 'launcher_dstart':
            request.Finish()
        elif method == 'launcher_dend':
            request.Finish()
        elif method == 'launcher_events':
            request.Finish()
        elif method == 'payment':
            user = self.get_argument('user')
            value = self.get_argument('value')
            source = self.get_argument('source')
            self.service.MakePayment(request, user, value, source)
        elif method == 'quest':
            auid = self.get_argument('auid')
            quid = self.get_argument('quid')
            status = self.get_argument('status')
            tm = self.get_argument('tm', None)
            self.service.ProcessQuest(request, auid, quid, status, tm)
        elif method == "hero_level":
            auid = self.get_argument('auid')
            heroid = self.get_argument('heroid')
            level = self.get_argument('level')
            tm = self.get_argument('tm', None)
            self.service.ProcessHeroLevel(request, auid, heroid, level, tm)
        elif method == "hero_rank":
            auid = self.get_argument('auid')
            heroid = self.get_argument('heroid')
            level = self.get_argument('level')
            rank = self.get_argument('rank')
            up = self.get_argument('up')
            tm = self.get_argument('tm', None)
            self.service.ProcessHeroRank(request, auid, heroid, level, rank, up, tm)
        elif method == "castle_level":
            auid = self.get_argument('auid')
            level = self.get_argument('level')
            tm = self.get_argument('tm', None)
            self.service.ProcessCastleLevel(request, auid, level, tm)
        elif method == 'begin_download':
            muid = self.get_argument('muid')
            self.service.BeginDownload(request, muid)
        elif method == 'begin_install':
            muid = self.get_argument('muid')
            self.service.BeginInstall(request, muid)
        elif method == 'cancel_install':
            muid = self.get_argument('muid')
            self.service.CancelInstall(request, muid) 
        elif method == 'launch_install':
            muid = self.get_argument('muid')
            self.service.LaunchInstall(request, muid)             
        elif method == 'end_install':
            muid = self.get_argument('muid')
            self.service.EndInstall(request, muid)
        elif method == 'landing_register': 
            muid = self.get_argument('muid', None)        
            auid = self.get_argument('auid')
            self.service.LandingRegister(request, muid, auid) 
        elif method == 'landing_login': 
            muid = self.get_argument('muid', None)        
            auid = self.get_argument('auid')
            self.service.LandingLogin(request, muid, auid)             
        elif method == 'first_login':
            muid = self.get_argument('muid', None)
            auid = self.get_argument('auid')
            self.service.FirstLogin(request, muid, auid)
        elif method == 'download_client_begin':
            auid = self.get_argument('auid')
            self.service.DownloadClientBegin(request, auid)
        elif method == 'download_client_end':
            auid = self.get_argument('auid')
            self.service.DownloadClientEnd(request, auid)
        elif method == 'faction_selected':
            auid = self.get_argument('auid')
            faction = self.get_argument('faction')
            self.service.SelectFaction(request, auid, faction)
        elif method == 'uninstall':
            muid = self.get_argument('muid')
            self.service.Uninstall(request, muid)
        elif method == 'reinstall':
            muid = self.get_argument('muid')
            self.service.Reinstall(request, muid)
        elif method == 'getdata':
            result = {
                'frontend' : self.service.GetData(),
                'queue' : self.loader.GetData(),
            }
            request.Finish(result)
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

class ModuleLoader:
   
    def __init__(self, http_client, config):
        self.http_client = http_client
        self.config = config
        self.queues = []

    def Load(self, name, config):
        m = None
        try:
            f, pathname, description = imp.find_module(name, ['.']) 
            m = imp.load_module(name, f, pathname, description)
        except ImportError:
            return None

        if 'Module' in m.__dict__:
            queue = PersistentQueue(self.http_client, self.config, os.path.join(self.config.db_path, name+'.db'))
            module = m.Module(queue, config)
            self.queues.append ((name, queue) )
            return module

    def Shutdown(self):
        for name, queue in self.queues:
            queue.Shutdown()

    def Update(self):
        for name, queue in self.queues:
            queue.Update()

    def IsStopped(self):
        for name, queue in self.queues:
            if not queue.IsStopped():
                return False
        return True

    def GetData(self):
        result = []
        for name, queue in self.queues:
            result.append( (name, queue.GetData()) )
        return result

class MarketingService(Service):

    def __init__(self, sid):
        super(MarketingService, self).__init__(sid)
        self.entity = None

    def Start(self, link, config):
        self.config = config
        self.link = link
        self.http_client = Network.HttpClient.AsyncHttpClient(validate_cert=False)
        self.loader = ModuleLoader(self.http_client, self.config.queue)
        self.service = _MarketingService(self.config.frontend, self.loader)
        handlers = [
            (self.config.http_base_url, DoHandler, dict(config=config, http_client=self.http_client, service=self.service, loader=self.loader)),
            ('/key.js', tracking.KeyHandler, dict(config=config, service=self.service)),
            ('/event', tracking.EventHandler, dict(config=config, service=self.service)),
            ('/cvt', CvtHandler, dict(config=config, service=self.service)),
        ]
        if self.config.debug:
            handlers.append(('/static/(.*)', tornado.web.StaticFileHandler, {"path": './templates'}))

        self.application = tornado.web.Application( 
            handlers,
            debug=self.config.debug,
            autoescape=None )   
        self.http_server = tornado.httpserver.HTTPServer(self.application)
        self.http_server.bind(self.config.port)
        self.http_server.start(self.config.nump)
        self.fsm.Move(Service.STARTED)

    def Update(self):
        ## warning('MarketingService.Update') ##DEBUG
        self.HttpLoggerTick()
        self.service.Update()
        self.loader.Update()
        if self.fsm.state == Service.STOPPING and self.loader.IsStopped() and self.service.IsStopped():   
            self.fsm.Move(Service.STOPPED)
            
    def Stop(self, how):
        self.service.Shutdown()
        self.loader.Shutdown()


def main(args, gate):
    if args.config:
        config = System.config.RawConfig(args.config)
    else:
        data = {
            'port' : 10006,
            'nump' : 1,
            'debug' : True,
            'queue' : {
                'max_request_rate' : 20,
                'start_request_rate' : 5,
                'request_rate_delta' : 1,
                'flush_period' : 5,
                'db_path': '.',
                'rate_period' : 5,
            },
            'frontend' : {
                'muid_presets' : ['zzima', 'steam', 'aeria', 'amazon', 'arc'],
                'expire_muid_period' : 7*3600*24,
                'db' : 'users.db',
                'edb' : 'events.db',
                'flush_period' : 5,
                'min_muid_to_send_postback' : 0,
                'partners' : {
                    'rambler' : {
                        'code' : 'aa',
                        'source' : 'landing',
                    },
                    'pw' : {
                        'code' : 'ff',
                        'source' : 'copy',
                    },
                    'steam' : {
                        'code' : 'fe',
                        'source' : 'steam',
                    },
                    'pg' : {
                        'code' : 'ab',
                        'source' : 'landing',
                    },
                    'rut' : {
                        'code' : 'ac',
                        'source' : 'torrent',
                    },
                    'cityads' : {
                        'code' : 'ab',
                        'source' : 'torrent',
                    },
                },
                "exchange_rate" : 3.3898305084745762711864406779661,
                "modules" : {
                    "cityads" : {
                        "url" : "http://localhost:8080"
                    },
        #            "eventlogger" : {
        #              "url" : "test",
        #            },
#                    'kontagent' : {
#                        'url' : 'http://localhost:8080',
         #               'url' : 'http://test-server.kontagent.com/api/v1/ae17f59d7dab4dc39a28663647814ac0/',
        #                'url' : 'http://api.geo.kontagent.net/api/v1/ae17f59d7dab4dc39a28663647814ac0/',
#                    },
                },
            },
            'tracking' : {
                'host' : 'http://localhost:10006',
                'key_name' : 'nival_tracking_key'
            },
            'http_base_url' : '/push/',
        }
        config = System.config.RawConfig(data)
    svn = MarketingService(args.sid)
    gate.AddService(svn, config)
    svn.HttpLoggerInit(args, config)


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--config', default=None, help='Config path') 
    parser.add_argument('--sid', default='Marketing', help='Service id')
    parser.add_argument('--pid', default='market', help='Service process (instance) id')
    System.logs.setupParserArgs( parser )
    args = parser.parse_args()
    
    System.logs.setup(args.log, args.loglevel, args.logrotate)
    
    gate = Network.SOA.ServiceGate()

    main(args, gate)
    gate.Run() 
