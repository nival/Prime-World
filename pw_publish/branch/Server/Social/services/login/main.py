# -*- coding: utf-8 -*-
import sys
sys.path.append('../common/py')
sys.path.append('../..')
sys.path.append('../../cfg')
sys.path.append('../../thrift_pw/statistics/gen-py')
sys.path.append('../../libs')

from handlers import loadMultiConfig
import System.logs
import System.fsm
import System.config

import os.path, json, functools, time, hashlib, random

from tornado.options import options
import tornado.escape
import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import tornado.httpclient
import tornadoredis

import Network
import Network.HttpClient
from Network.SOA import Service

from base.helpers import ClassDict, toint, catch, IncDict, debug, info, warn
from ifactory import IfaceFactory
from handlers import SOCAGG_VERSION

import EC
import CC
import ext_main.who
import ext_main.l_ping
import ext_main.qlogin
import ext_main.l_statistic
import ext_main.join 
import ext_main.l_login

import handlers
from subaction import SubAction, action_timing

from geolocation import GeoLocator
from geo_cfg import DEFAULT_GEO_LOCATION

import cfg, coord_cfg

class WhoAction(ext_main.who.WhoAction): # PF-91757

    def onStart(self):
        self.zul_cb = self.getParam("callback", None)
        super(WhoAction, self).onStart()

    def fin(self):
        if self.zul_cb:
            self.response['jsonp_cb'] = self.zul_cb
        super(WhoAction, self).fin()


actionClasses = {
    'l_who' : WhoAction,
    'l_set_gender': ext_main.who.SetSteamGenderAction,
    'l_ping': ext_main.l_ping.LauncherPingAction,
    'qlogin': ext_main.qlogin.QueueLoginAction,
    'qpoll': ext_main.qlogin.QueuePollAction,
    'qcancel': ext_main.qlogin.QueueCancelAction,
    'l_start': ext_main.l_statistic.LauncherStartAction,
    'l_events': ext_main.l_statistic.LauncherEventsAction,
    'l_stat': ext_main.l_statistic.LauncherDActions,
    'l_join': ext_main.join.JoinAction,
    'l_merge': ext_main.qlogin.QueueMergeAction,
    'l_login' : ext_main.l_login.LauncherLoginAction,
}

class ExternalHandler(tornado.web.RequestHandler):

    def initialize(self, config, http_client, service):
        self.http_client = http_client
        self.config = config
        self.service = service

    @tornado.web.asynchronous
    def get(self):
        if not self.service.isStarted:
            raise tornado.web.HTTPError(503)

        method = self.get_argument('action')

        actionClass = actionClasses.get(method, None)

        action = None
        if actionClass:
            action = actionClass(self.request.arguments, self.onFinishWrapped, self.request)    

        if action:
            action.I = self.service
            action.onStart()
        else:
            raise tornado.web.HTTPError(501)

    def onFinishWrapped(self, data):
        if 'ModelData' in data:
            del data['ModelData']
        cb = data.pop('jsonp_cb', None)  # PF-91757
        data['server'] = 'login%s' % self.config.service.external_id 
        data = { 'response' : data }
        if cb: # сериализуем сами, self.finish это скушает нормально
            data = '%s(%s);' % (cb, tornado.escape.json_encode(data))
            self.set_header("Content-Type", "application/javascript; charset=UTF-8")
            self.set_header("Expires", "on, 01 Jan 1970 00:00:00 GMT")
            self.set_header("Cache-Control", "no-store, no-cache, must-revalidate")
            self.set_header("Pragma", "no-cache")
        self.finish(data)
            
    @tornado.web.asynchronous
    def post(self):
        if not self.service.isStarted:
            raise tornado.web.HTTPError(503)

        muid = 'mailru'
        if '<OnlineInfoIn/>' in self.request.body:
            self.service.GetCurrentCCU(muid, self.onCCU)
        elif '<OverallRegistrationInfoIn/>' in self.request.body:
            self.service.GetOverallRegistrations(muid, self.onRegs)

    def onRegs(self, data):
        self.write('<?xml version="1.0" encoding="UTF-8"?><OverallRegistrationInfoOut OverallCount="%s"/>' % data)
        self.finish()

    def onCCU(self, data):
        self.write('<?xml version="1.0" encoding="UTF-8"?><OnlineInfoOut Count="%s" />' % data)
        self.finish()

class FIFOQueue:  # is not used anywhere!

    def __init__(self, lst=[]):
        self.q = []
        self.out = 0

    def push(self, seq):
        self.q.append(seq)

    def pop(self):
        k = self.q[self.out]
        self.out += 1
        return k

    def remove(self, seq):
        pass        

    def __len__(self):
        return len(self.q)

import collections

class IncAverageCalculator:

    def __init__(self):
        self.count = 0
        self.average = 0.0

    def push(self, value):
        self.count += 1
        if self.count == 1:
            self.average = value
        else:
            self.average += (value - self.average) / float(self.count)

USER_AWAITING = 0
USER_IN_QUEUE = 1
USER_PENDING_LOGIN = 2
USER_LOGGED_IN = 3
USER_CANCELED = 4

CHECK_ALIVE_MAX_IDLE = 7
CHECK_ALIVE_RECONNECT_FENCE = 2 

LOGIN_EXPIRE_TIME_BEFORE_LOGIN = 60*60*3

from iwebserver import ICSVActionTimingWriter

class LoginContext:

    def __init__(self, user, token, expirePeriod, loginOffset, primary):
        self.user = user
        self.inToken = token
        self.outToken = None
        self.outInstanceId = None
        self.outInstanceName = None
        self.expirePeriod = expirePeriod
        self.expireTime = time.time()+LOGIN_EXPIRE_TIME_BEFORE_LOGIN
        self.status = USER_AWAITING
        self.callback = None
        self.loginOffsetTime = loginOffset
        self.startWaitTime = time.time()
        self.loginTime = time.time()
        self.startTime = time.time()
        self.secondary = {}
        self.isPrimary = primary
        self.startLoginTime = time.time()

    def addUser(self, user):
        self.secondary[user.snid] = user

    def getCurrentWaitTime(self):
        return time.time()-self.startWaitTime 

    def getWaitTime(self):
        return self.startLoginTime-self.startWaitTime 

    def getLoginTime(self):
        return time.time()-self.startLoginTime 

    def startWait(self):
        self.startWaitTime = time.time()
        self.loginTime = self.startWaitTime+self.loginOffsetTime
        self.refresh()

    def startLogin(self):
        self.startLoginTime = time.time()

    def match(self, token):
        return (self.inToken == token)

    def isFresh(self, currentTime):
        return currentTime < self.expireTime                    

    def refresh(self):
        self.expireTime = time.time() + self.expirePeriod

    def checkReply(self, force, qlength=0, qtime=0):
        if self.callback:
            if self.status == USER_LOGGED_IN:
                self.callback(True, self.outInstanceName, self.outToken, 0, 0, EC.OK)
                self.callback = None
            elif force:
                self.callback(False, None, None, qlength, qtime, EC.OK)
                self.callback = None

class DummyWS(ICSVActionTimingWriter):

    def __init__(self, ioloop, config, apis, test_mode=False):
        self.TEST_MODE = test_mode
        self.loginCache = {}
        self.loginCacheExpireTime = time.time()
        self.apis = apis
        self.peers = {}
        self.activePeers = 0
        self.recalcPeersTime = time.time()
        self.queue = collections.deque()
        self.pending = {}
        self.ioloop = ioloop
        self.config = config
        self.averageWaitTime = IncAverageCalculator()
        self.averageLoginTime = IncAverageCalculator()
        self.lastShiftTime = time.time()
        self.lastLogTime = time.time()
        self.server_id = None
        self.lastAliveCheckTime = time.time()
        self.isCoordinatorDead = 0
        self.disabledInstances = {}
        self.timing_file = None
        self.pwc = {} # TEMP: временно (для теста) заводим еще один набор токенов (специально для pwc_login)    
        self.guids = IncDict()

    def getInfo(self):
        return {
            'queue' : len(self.queue),
            'pending' : len(self.pending),
            'logins' : len(self.loginCache),
            'peers' : {
                'disabled' : self.disabledInstances.keys(),
                'total' : len(self.peers),
                'active' : self.activePeers,
            },
            'coordinator_dead' : self.isCoordinatorDead,
            'login_avg_tm' : self.averageLoginTime.average,
            'wait_avg_tm' : self.averageWaitTime.average,
        }

    def nextUid(self, key):
        return self.guids.inc(key)
    
    def nextStringGUID(self, key):
        uid = self.nextUid(key)
        return "%d_%d" % (self.config.service.external_id, uid)

    def onStart(self):
        self.createActionsCSV( 'login', 'login', self.server_id, test_mode=self.TEST_MODE )

    def Stop(self):
        self.closeActionsCSV()

    def setServerId(self, value):
        self.server_id = value

    def onCheckAlive(self):
        self.lastAliveCheckTime = time.time()
        self.isCoordinatorDead = 0

    def onPeersRecieved(self, peers):
        self.peers = {}
        for name, _peer in peers.items():
            sid = _peer.get('server_id', None)
            if sid is not None:
                peer = ClassDict()
                peer.name = name
                peer.on = _peer['on']
                peer.rdy = _peer['rdy']
                peer.addr = _peer['addr']
                peer.max_users = _peer.get('max_users', 0)
                peer.cur_users = _peer['cur_users']
                self.peers[sid] = peer 
        self.recalcPeersTime = time.time()
        info('Peers recieved (peers=%r count=%d)', peers, len(self.peers))

    def onGetPeerServer(self, peer, peer_name, _peer_id, status):
        if status == handlers.PEER_DELETED:
            peer_id = int(_peer_id)
            if peer_id in self.disabledInstances:
                del self.disabledInstances[peer_id]

        if status == handlers.PEER_DELETED or status == handlers.PEER_ADDED:
            self.recalcWaitTimes()
        self.recalcPeersTime = time.time()
    
    def Update(self):
        t = time.time()
        if t-self.lastAliveCheckTime > CHECK_ALIVE_MAX_IDLE:
            self.isCoordinatorDead += 1
            self.lastAliveCheckTime = t
            info('Coordinator is inactive (time=%2.1f)', self.isCoordinatorDead*CHECK_ALIVE_MAX_IDLE)

            if self.isCoordinatorDead > CHECK_ALIVE_RECONNECT_FENCE:
                self.reconnectToCoordinator()
                self.isCoordinatorDead = 0
            
        if t > self.loginCacheExpireTime:
            self.updateLoginTokens(t)
            self.loginCacheExpireTime = t + self.config.service.login_token_check_time

        it = toint(t)
        if it % 60 == 0:
            self.updateInstrumentedActions()

        self.pollQueue()

    def getShiftTime(self):
        return time.time() - self.lastShiftTime

    def generateToken(self, auid):
        m = hashlib.md5()
        m.update(auid)
        m.update(str(time.time()))
        m.update(str(random.random()))
        return m.hexdigest()

    def registerLogin(self, _auid, user, token=None, primary=0, registering=False):
        debug('Creating context for user %r', user.toJson())

        auid = str(_auid)
        context = self.loginCache.get(auid, None)
        create_new = False
        if primary == 0:
            if context is not None:
                context.addUser(user)
                info('User added to primary context (auid=%s snid=%r)', auid, user.snid)
            else:
                create_new = True
        else:
            create_new = True
        if create_new:
            if context:
                info('Previous context found, discarding (auid=%s snid=%r)', auid, context.user.snid)
            if not token:
                token = self.generateToken(auid)
            context = LoginContext(user, token, self.config.service.login_token_expire_time, self.config.service.login_offset_time, bool(primary))
            self.loginCache[auid] = context
            info('New context created (auid=%s token=%r snid=%r primary=%d register=%r)', auid, token, user.snid, primary, registering)
        if registering:
            pipe = self.apis.REDIS.pipeline()
            muid = user.muid
            ruid = user.ruid
            if not muid or cfg.META_MUIDS is None or muid not in cfg.META_MUIDS:
                muid = CC.OTHER_MUID
            pipe.hincrby('regs/muid', muid, 1)
            pipe.hincrby('regs/ruid', ruid, 1)
            pipe.hincrby('regs/snid', user.snid, 1)
            pipe.execute(self.onReg)
        return context.inToken

    def onReg(self, data):
        pass

    def checkLoginContext(self, _auid, token):
        auid = str(_auid)
        context = self.loginCache.get(auid, None)
        if context:
            if context.match(token):
                return context

    def enqueueContext(self, auid, context, toLeft=False):
        if auid in self.pending:
            del self.pending[auid]
        context.status = USER_IN_QUEUE
        if toLeft:
            self.queue.appendleft( (auid, context.inToken) )
        else:
            self.queue.append( (auid, context.inToken) )
        return len(self.queue)

    def pollQueue(self):
        tm = time.time()
        if tm >= self.recalcPeersTime:
            self.chooseInstance()    
            self.recalcPeersTime = tm+5.0

        if tm > self.lastLogTime:
            info('Polling queue (length=%d pending=%d peers=%d apeers=%d)', len(self.queue), len(self.pending), len(self.peers), self.activePeers)
            self.lastLogTime = tm + 5.0

        if len(self.pending) < self.config.service.max_pending and self.activePeers > 0:
            kept = False
            while self.queue:
                auid, token = self.queue.popleft()
                context = self.loginCache.get(auid, None)
                if context and context.match(token):
                    if context.status == USER_CANCELED:
                        info('Found canceled request (auid=%s)', auid)
                        del self.loginCache[auid]
                        continue
                    self.lastShiftTime = time.time()
                    targetInstance = None        
                    if time.time() >= context.loginTime:
                        debug('Found candidate (auid=%s token=%r context=%d)', auid, token, context is not None)
                        targetInstance = self.chooseInstance()

                    if targetInstance is not None:
                        debug('Start login (auid=%s token=%r instance=%r)', auid, token, targetInstance)
                        self.startContext(auid, context, targetInstance)                                                            
                    else:
                        debug('Enqueue to queue head (auid=%s token=%r)', auid, token)
                        self.enqueueContext(auid, context, True)
                        kept = True
                    break
                else:
                    reason = 'Second login attempt' if context else 'Context expired'
                    info('Found expired request (auid=%s token=%r reason=%r)', auid, token, reason)
            if self.queue:
                self.ioloop.add_timeout(time.time() + (0.005 if kept else 0), self.pollQueue)

    def chooseInstance(self):
        min_sid = None
        min_users = 0
        tm = time.time()
        self.activePeers = 0   
        for sid, peer in self.peers.items():
            if peer.on == 1 and peer.rdy == 1:
                enableTime = self.disabledInstances.get(sid, None)
                if enableTime is not None:
                    if tm < enableTime:
                        continue
                    else:
                        info('Enabling instance for login (instance=%r)', peer.name)
                        del self.disabledInstances[sid]
                self.activePeers += 1
                cur_users = peer.cur_users
                if cur_users < peer.max_users or peer.max_users == 0:
                    if min_sid is None or cur_users < min_users:          
                        min_sid = sid
                        min_users = cur_users
        return min_sid

    def startContext(self, auid, context, targetInstanceId):
        context.refresh()
        context.startLogin()
        peer = self.peers.get(targetInstanceId, None)
        context.status = USER_PENDING_LOGIN
        context.outToken = self.generateToken(auid)
        context.outInstanceId = targetInstanceId
        context.outInstanceName = peer.name
        self.pending[auid] = time.time()
        body = context.user.toJson()
        info('Logging user (auid=%s instance=%r data_size=%d)', auid, peer.name, len(body))
        self.incrUserCount(targetInstanceId, 1)

        _callback = functools.partial( self.onAddUser, auid=auid, lcontext=context )
        self.apis.WSX.post(peer.addr, { 'auid' : auid, 'action' : 'add_user', 'token' : context.outToken, 'primary' : 1 }, body, _callback, subrequest="x", unwrap=True, timeout=20.0 )

    def finishContext(self, auid, context):
        if auid in self.pending:
            del self.pending[auid]
        context.status = USER_LOGGED_IN
        context.checkReply(False)

    def getEstimatedWaitTime(self, auid, context, qlength, addon):
        if len(self.peers) == 0:
            return 0
        tm = time.time()
        if tm < context.loginTime:
            mainTime = context.loginTime-tm 
        else:
            mainTime = self.averageWaitTime.average-context.getCurrentWaitTime()
            if mainTime < 0:
                mainTime = self.getEstimatedQueueProcessTime(context, qlength)
        loginTime = self.averageLoginTime.average*(qlength+1)
        info('Wait time estimation (auid=%s main=%2.1f login=%2.1f addon=%2.1f comm=%2.1f)', auid, mainTime, loginTime, addon, 1.0)    
        return int(mainTime+loginTime+addon+1) # always add 1 for communication

    def getEstimatedQueueProcessTime(self, context, place):
        if len(self.peers) == 0:
            return 0
        value = min(self.averageWaitTime.average/len(self.peers), 60.0*5.0)
        info("getEstimatedQueueProcessTime: %0.3f", value)
        return value

    def getExactPlace(self, auid):
        for index, (item, token) in enumerate(self.queue):
            if item == auid:
                return (index+1)
        return 0

    def recalcWaitTimes(self):
        if len(self.queue) == 0:
            return
        info('Recalculating wait times for all queue')
        index = 0 
        for auid, token in self.queue:
            context = self.loginCache.get(auid, None)
            if context and context.status != USER_CANCELED:
                place = index + 1
                waitTime = self.getEstimatedWaitTime(auid, context, place, self.getEstimatedQueueProcessTime(context, place))
                context.checkReply(True, place, waitTime) 
            index += 1

    def pollUser(self, auid, context, callback):
        place = self.getExactPlace(context)
        waitTime = self.getEstimatedWaitTime(auid, context, place, self.getEstimatedQueueProcessTime(context, place))
        context.checkReply(True, place, waitTime) 
        context.callback = callback
        context.refresh()
        context.checkReply(False, place, waitTime)  

    def loginUser(self, auid, context, callback):
        if context.status != USER_AWAITING:
            callback(False, None, None, len(self.queue), 0, EC.QLOGIN_CONTEXT_ALREADY_PENDING)
            return 
        if not context.isPrimary:
            callback(False, None, None, len(self.queue), 0, EC.QLOGIN_CONTEXT_IS_NOT_PRIMARY)
            return 

        context.startWait()
        info("LoginContext.startWait called auid=%s: startWaitTime %0.3f, loginTime %0.3f, expireTime %0.3f",
             auid, context.startWaitTime, context.loginTime, context.expireTime)

        targetInstance = None    
        if time.time() >= context.loginTime and len(self.queue) == 0 and len(self.pending) < self.config.service.max_immediate_pending: 
            targetInstance = self.chooseInstance()
            info("Instance choosen: %s", targetInstance)

        if targetInstance is None:
            qlength = self.enqueueContext(auid, context)
            info("User context enqueued. qlength = %s", qlength)
            waitTime = self.getEstimatedWaitTime(auid, context, qlength, self.getEstimatedQueueProcessTime(context, qlength))
            callback(False, None, None, qlength, waitTime, EC.OK)
            self.ioloop.add_timeout(time.time()+0.005, self.pollQueue)
            return
        else:
            if callback:
                context.callback = callback
            self.startContext(auid, context, targetInstance)

    def cancelContext(self, auid, context):
        info('Canceling context (auid=%s)', auid)
        context.checkReply(True)
        if context.status == USER_PENDING_LOGIN:
            del self.pending[auid]
            del self.loginCache[auid]
        else:
            context.status = USER_CANCELED
    
    def cancelUser(self, auid, context, callback):
        self.cancelContext(auid, context)
        callback(False, None, None, 0, 0, EC.OK)

    def disableInstance(self, instanceId):
        peer = self.peers.get(instanceId, None)
        if peer is not None:
            disableTime = 30.0
            info('Disabling instance for login (instance=%r time=%2.1f)', peer.name, disableTime)
            self.disabledInstances[instanceId] = time.time()+disableTime
        
    def incrUserCount(self, instanceId, incr):
        peer = self.peers.get(instanceId, None)
        if peer is not None:
            count = peer.cur_users
            count += incr
            if count < 0:
                count = 0
            peer.cur_users = count
            return peer.name
        
    def onAddUser(self, response, auid, lcontext):
        context = self.loginCache.get(auid, None)
        if not context or context.status != USER_PENDING_LOGIN or context != lcontext:
            if auid in self.pending:
                del self.pending[auid]
            if lcontext.callback:
                lcontext.callback(False, None, None, 0, 0, EC.QLOGIN_CONTEXT_EXPIRED)
            status = lcontext.status
            info('User context failed (auid=%s status=%d)', auid, status)
            return

        if response:
            info("onAddUser response %r", response )
            waitTime = context.getWaitTime()
            self.averageWaitTime.push(waitTime)

            loginTime = context.getLoginTime()
            self.averageLoginTime.push(loginTime)
            info('User logged in (auid=%s instance=%r wait_time=%2.2f avg_wait_time=%2.2f login_time=%2.2f avg_login_time=%2.2f)', auid, context.outInstanceName, waitTime, self.averageWaitTime.average, loginTime, self.averageLoginTime.average)
            self.finishContext(auid, context)
            return
        else:
            self.incrUserCount(context.outInstanceId, -1)
            self.disableInstance(context.outInstanceId)
            info('User login failed, returning to queue (auid=%s instance=%r)', auid, context.outInstanceName)
            self.enqueueContext(auid, context, True)
            waitTime = self.getEstimatedWaitTime(auid, context, 1, self.getEstimatedQueueProcessTime(context, 1))
            context.checkReply(True, len(self.queue), waitTime) 
            return

    def checkLoginToken(self, _auid, token):
        auid = str(_auid)
        context = self.loginCache.get(auid, None)
        if context:
            if context.match(token):
                return context.user

    def refreshLoginToken(self, _auid):
        auid = str(_auid)
        context = self.loginCache.get(auid, None)
        if context:
            context.refresh()

    def updateLoginTokens(self, currentTime):
        expired = []
        for auid, token in self.loginCache.items():
            if not token.isFresh(currentTime):
                info('Token expired (auid=%s token=%r)', auid, token.inToken)
                expired.append(auid)
        for auid in expired:    
            del self.loginCache[auid]

    def deleteLoginToken(self, _auid):
        auid = str(_auid)
        context = self.loginCache.get(auid, None)
        if context:
            info('Token removed (auid=%s token=%r)', auid, context.inToken)
            del self.loginCache[auid]
            
    def setLoginNick(self, _auid, nick_utf8):
        auid = str(_auid)
        context = self.loginCache.get(auid, None)
        if context:
            info('setLoginNick(%s) user token ok for auid=%s', nick_utf8, auid)
            context.user.nick = nick_utf8
        else:
            info('setLoginNick(%s) user token failed: no user token for auid=%s', nick_utf8, auid)

    def setLoginGender(self, _auid, gender):
        auid = str(_auid)
        context = self.loginCache.get(auid, None)
        if context:
            info('setLoginGender(%s) user token ok for auid=%s', gender, auid)
            context.user.sex = gender
        else:
            info('setLoginGender(%s) user token failed: no user token for auid=%s', gender, auid)
        
    def setSnBonusCount(self, _auid, _sn_count, _sn_count_prev, _new_networks):
        auid = str(_auid)
        sn_count = toint(_sn_count)
        sn_count_prev = toint(_sn_count_prev)
        context = self.loginCache.get(auid, None)
        if context:
            info('setSnBonusCount(cur=%s, prev=%s new netw %s) user token ok for auid=%s', sn_count, sn_count_prev, _new_networks, auid)
            context.user.sn_count = sn_count
            context.user.sn_count_prev = sn_count_prev
            context.user.new_networks = _new_networks
        else:
            info('setSnBonusCount(cur=%s, prev=%s new netw %s) user token failed: no user token for auid=%s', sn_count, sn_count_prev, _new_networks, auid)
            
    def markRestrictionOk(self, _auid):
        auid = str(_auid)
        context = self.loginCache.get(auid, None)
        if context:
            context.user.restriction_ok = 1

    def mergeAccounts(self, auid0, auid1, callback):
        targetInstance = self.chooseInstance()
        peer = None
        context = self.loginCache.get(auid1, None)
        if targetInstance:
            peer = self.peers.get(targetInstance, None)
        if peer and context:
            info('Merging account using WS (peer=%r)', peer.name)
            _callback = functools.partial( self.onMerge, auid0=auid0, auid1=auid1, callback=callback )
            user1 = context.user
            wsargs = {'action' : 'l_merge_internal', 'auid0': auid0, 'auid1': auid1, 'pwc_snuid' : user1.pwc_snuid }
            if user1.email_md5 is not None:
                wsargs['email_md5'] = user1.email_md5
                # else: it is defaulted to None on a WS side,
            self.apis.WSX.fetch(peer.addr, wsargs, _callback, subrequest="x", unwrap=True, timeout=120.0 )
        else:
            args = {
                'ok' : 0,
                'ec' : EC.AGGREGATOR_MERGE_FAIL,
                'error' : "Could't find peer for merge"
            }
            callback(args)

    def onMerge(self, response, auid0, auid1, callback):
        context0 = self.loginCache.get(auid0, None)
        context1 = self.loginCache.get(auid1, None)
        if context0 is not None and context1 is not None:
            if not context0.isPrimary:
                # copying snid from primary context
                context0.user.original_snid = context1.user.original_snid
                context0.user.original_snuid = context1.user.original_snuid
                context0.user.muid = context1.user.muid
                context0.user.ruid = context1.user.ruid
                context0.isPrimary = True
                info('Merged main context is not primary, copying credentials (original_snid=%r original_snuid=%s)', context0.user.original_snid, context0.user.original_snuid)
        else:
            if context0 is not None and not context0.isPrimary:
                # context is not primary, so cancel it, launcher should relogin
                info('Merged main context missed primary information, canceling (snid=%r snuid=%s)', context0.user.snid, context0.user.snuid)
                self.cancelContext(auid0, context0)
        if context1 is not None:
            self.cancelContext(auid1, context1)
        
        update_auid = response.get('update_auid', None)
        sn_count = response.get('sn_count', None)
        sn_count_prev = response.get('sn_count_prev', None)
        new_networks = response.get('new_networks', [])
        if update_auid and sn_count and sn_count_prev:
            self.setSnBonusCount( update_auid, sn_count, sn_count_prev, new_networks )
        callback(response)

    def reconnectToCoordinator(self, callback=None):
        info('Connecting to coordinator (url=%r)', self.config.coordinator.url)
        addr = '127.0.0.1:%d' % self.config.port
        args = {'action' : 'aux_ready', 'name' : 'login', 'addr' : addr, 'subscribe_ws' : 1, 'subscribe_ca' : 1}
        if self.server_id:
            args['sid'] = self.server_id
        _callback = functools.partial( self.onCoordinatorConnect, callback=callback )
        self.apis.WSX.fetch(self.config.coordinator.url, args, _callback, subrequest="x", unwrap=True, timeout=20.0 )

    def onCoordinatorConnect(self, data, callback):
        debug("onCoordinatorConnect data: %r", data)
        if data:
            self.clusterConfig = data.get('config', {})
            configMatch = {
                "pvx_def_loc": "MATCHMAKER_DEFAULT_LOCALE",
                "fb_restrict": "RESTRICT_FACEBOOK_USERS",
                "loc_restrict": "RESTRICT_LOCATIONS",
                "loc_allowed": "RESTRICT_LOCATIONS_ALLOWED",
                "soc_agg": "SOCIAL_AGGREGATOR_ADDRESS",
                "stats_agent" : "STATS_AGENT_URL",
                "events" : "EVENTS_SERVICES",
                "sql_trd": "SQL_THREADS", 
                "pwc_info_url" : "PWC_INFO_URL",
                "geo_data_path" : "GEO_DATA_PATH",
                "redis_config" : "REDIS_CONFIG",
                "meta_muids" : "META_MUIDS",
            }
            for name, value in configMatch.items():
                setattr(cfg, value, self.clusterConfig.get(name, None))
                debug("Set config %r = %r", name, self.clusterConfig.get(name, None))
            self.clusterConfig['sql_list'] = data['sql_list']
            self.clusterConfig['mongo_list'] = data['mongo_list']

            self.onPeersRecieved(data.get('peers', {}))                    
            self.setServerId(data['sid'])     
            self.onStart()
            if callback:
                callback(True)          
        else:
            if callback:
                callback(False)               

class CheckAliveAction(SubAction):

    action = "check_alive"
    
    @action_timing
    def onStart(self):
        """ всем кому угодно умеем отвечать, что живы """ 
        self.response['ok'] = 1
        if self.I.HTTP:
            self.response["httpActive"] = len(self.I.HTTP.active)
            self.response["httpQueued"] = len(self.I.HTTP.queue)
        self.response["sid"] = self.I.WS.server_id
        self.I.WS.onCheckAlive()
        self.fin()        

class GetStatsAction(SubAction):

    action = "get_stat"

    def aggregate(self, aname, data):
        result = {}
        for sdata in data:
            for name, count in sdata.items():
                result[name] = result.get(name, 0)+int(count)
        self.response[aname.replace("/","_")] = result

    def query(self, cname, callback):
        pipe = self.I.REDIS.pipeline()
        for name in self.svcs:
            svc_name = 'svc/' + name + '/'+cname
            pipe.hgetall(svc_name)
        pipe.execute(callback)    
        
    @action_timing
    def onStart(self):
        if self.I.HTTP:
            self.response["http"] = {
                'active' : len(self.I.HTTP.active),
                'queue' : len(self.I.HTTP.queue),
            }
        self.response["sid"] = self.I.WS.server_id
        self.response['login'] = self.I.WS.getInfo()
        if self.I.REDIS:
            pipe = self.I.REDIS.pipeline()
            pipe.hgetall('regs/muid')
            pipe.hgetall('regs/ruid')
            pipe.hgetall('regs/snid')
            pipe.zrangebyscore('svcs/ttls', time.time(), time.time()+24*3600)
            pipe.execute(self.onFinish)    
            return
        else:
            self.fin()

    def onFinish(self, data):
        self.response['regs_muid'] = data[0]
        self.response['regs_ruid'] = data[1]
        self.response['regs_snid'] = data[2]

        if len(data[2]) > 0:
            self.svcs = data[3]

            self.query('ccu/muid', self.onFinish2)
        else:   
            self.response['ok'] = 1
            self.fin()        

    def onFinish2(self, data):
        self.aggregate('ccu/muid', data)
        self.query('ccu/ruid', self.onFinish3)

    def onFinish3(self, data):
        self.aggregate('ccu/ruid', data)
        self.query('ccu/locale', self.onFinish4)

    def onFinish4(self, data):
        self.aggregate('ccu/locale', data)
        self.query('ccu/total', self.onFinish5)

    def onFinish5(self, data):
        self.aggregate('ccu/total', data)

        self.response['ok'] = 1
        self.fin()        

class InternalHandler(tornado.web.RequestHandler):

    def initialize(self, config, http_client, service):
        self.http_client = http_client
        self.config = config
        self.service = service

    @tornado.web.asynchronous
    def get(self):
        method = self.get_argument('action')
        pretty = int(self.get_argument('pretty', '0'))

        action = None
        if method == 'peer':
            action = handlers.PeerServerStatusAction(self.request.arguments, self.onFinish, self.request)    
        elif method == 'check_alive':
            action = CheckAliveAction(self.request.arguments, self.onFinishWrapped, self.request)
        elif method == 'get_stat':
            action = GetStatsAction(self.request.arguments, self.onFinishWrapped, self.request)

        if action:
            action.I = self.service
            action.onStart()
        else:
            raise tornado.web.HTTPError(501)
            
    def onFinish(self, data):
        self.finish(data)

    def onFinishWrapped(self, data):
        data['server'] = 'login%s' % self.config.service.external_id
        data = { 'response' : data }
        self.finish(data)

class _Service:

    def  __init__(self, ioloop, config, fsm):
        self.config = config
        self.fsm = fsm
        # http-клиент для связи с peer-серверами
        self.HTTP = tornado.httpclient.AsyncHTTPClient(max_clients=config.http.curl_workers)
        self.WSX = IfaceFactory.makeIPeerWebServerInterface( self.config.wsx.stype, HTTP=self.HTTP, request_limit=config.wsx.request_limit)
        self.WS = DummyWS(ioloop, self.config, self)
        self.GEO = None
        self.STATS = None
        self.REDIS = None
        self.AGG = None
        self.SQL = None
        self.isFirstStart = True
        self.isStarted = False
        ioloop.ws = self.WS
        self.cached_regs_values = {}
        self.Config = loadMultiConfig()
        if self.Config is not None:
            info('Config loaded')
        else:
            info("Config isn't loaded")
        #info("_Service config: %r", self.config.email if self.config.email else "empty config" )
        self.SMTP = IfaceFactory.makeSmtpInterface( self.config.email.smtp, self.config.email, num_threads=coord_cfg.COORDINATOR_PWC_SMTP_THREADS )
        info( "SMTP interface: " + str(self.SMTP) )

        self.WS.reconnectToCoordinator(self.onCoordinatorStart)


    def GetCurrentCCU(self, muid, ruid, callback):
        if muid not in cfg.META_MUIDS:
            callback(0)
            return

        _callback = functools.partial( self.onCCU0, muid=muid, ruid=ruid, callback=callback )
        try:
            self.REDIS.zrangebyscore('svcs/ttls', time.time(), time.time()+24*3600, callback=_callback)
        except tornadoredis.ConnectionError:
            callback(0)
        
    def onCCU0(self, data, muid, ruid, callback):
        if data:
            pipe = self.REDIS.pipeline()
            for name in data:
                pipe.hget('svc/' + name + '/ccu/muid', muid)
                pipe.hget('svc/' + name + '/ccu/ruid', ruid)

            _callback = functools.partial( self.onCCU1, svcs=data, callback=callback )
            pipe.execute(callback = _callback)
        else:
            callback(0)    

    def onCCU1(self, data, svcs, callback):
        total = 0
        for name, value in zip(svcs, data):
            count = 0
            if value:
                count = int(value)
            total += count
        callback(total)    

    def GetOverallRegistrations(self, muid, callback):         
        if muid not in cfg.META_MUIDS:
            callback(0)
            return

        _callback = functools.partial( self.onRegs, muid=muid, callback=callback )
        try:
            self.REDIS.hget('regs/muid', muid, _callback)
        except tornadoredis.ConnectionError:
            callback(self.cached_regs_values.get(muid, 0))
        
    def onRegs(self, data, muid, callback):
        count = 0
        if data:
            count = int(data)
            self.cached_regs_values[muid] = count
        callback(count)    

    def onCoordinatorStart(self, succeded):
        if self.isFirstStart:
            self.isFirstStart = False
            if succeded:
                try:    
                    url = cfg.SOCIAL_AGGREGATOR_ADDRESS
                    if url:
                        info('Created SA API (url=%r)', url)
                        self.AGG = IfaceFactory.makeSocAggInterface( 'http', url, SOCAGG_VERSION, self.HTTP )
                    cfg.resetSqlServers()
                    sql = self.WS.clusterConfig.get("sql_list")
                    if sql:
                        info('Created SQL API (urls=%r)', sql)
                        self.SQL = IfaceFactory.makeSqlInterface( 'async', sql, num_threads=cfg.SQL_THREADS )

                    mongo = self.WS.clusterConfig.get("mongo_list")
                    if mongo:
                        info("Created MongoDB API (urls=%r)", str(mongo))
                        self.DATA = IfaceFactory.makeIDataInterface( "mongo", mongo, self.SQL, num_threads=cfg.MONGO_THREADS)


                    url = cfg.STATS_AGENT_URL
                    if url:
                        info('Created StatsAgent API (url=%r)', url)
                        self.STATS = IfaceFactory.makeIStatsInterface('thrift', url, self, cfg.STATS_RESEND_POOL_LIMIT)
                    path = os.path.abspath(os.path.join('../..', cfg.GEO_DATA_PATH))
                    if path and os.path.isfile(path):
                        info('Created Geo API (path=%r)', path)
                        self.GEO = GeoLocator(path)
                    if cfg.REDIS_CONFIG is not None:
                        self.REDIS = tornadoredis.Client( io_loop=tornado.ioloop.IOLoop.instance(), host=cfg.REDIS_CONFIG["redis_addr"], port=cfg.REDIS_CONFIG["redis_port"], selected_db=cfg.REDIS_CONFIG["redis_base"])
                        self.REDIS.connect()
                        info('Created Redis API (config=%r)', cfg.REDIS_CONFIG)
    
                    if self.SQL and self.AGG and self.STATS and self.GEO:
                        self.isStarted = True
                        self.fsm.Move(Service.STARTED)
                        return

                except Exception:
                    catch()
            self.fsm.Move(Service.STOPPING)

    def Update(self):
        self.WS.Update()
        if self.STATS:
            ts0 = time.clock()
            try:
                self.STATS.Send()
            except:
                catch()
            info( "STATS.Send time: %.3f", time.clock()-ts0 )

        if self.fsm.state == Service.STOPPING:   
            self.fsm.Move(Service.STOPPED)

    def Stop(self):
        self.WS.Stop()

class LoginService(Service):

    def __init__(self, sid):
        super(LoginService, self).__init__(sid)
        self.entity = None

    def Start(self, link, config):
        self.config = config
        self.link = link
        
        self.http_client = Network.HttpClient.AsyncHttpClient(validate_cert=False)
        self.service = _Service(tornado.ioloop.IOLoop.instance(), self.config, self.fsm)
        
        handlers = [
            ('/', ExternalHandler, dict(config=config, http_client=self.http_client, service=self.service)),
            ('/login', ExternalHandler, dict(config=config, http_client=self.http_client, service=self.service)),
            ('/x', InternalHandler, dict(config=config, http_client=self.http_client, service=self.service)),
        ]

        self.application = tornado.web.Application( 
            handlers,
            debug=self.config.debug,
            autoescape=None )
        self.http_server = tornado.httpserver.HTTPServer(self.application)
        self.http_server.bind(self.config.port)
        self.http_server.start(self.config.nump)

    def Update(self):
        self.service.Update()
        self.HttpLoggerTick()
        if self.fsm.state == Service.STOPPING:   
            self.fsm.Move(Service.STOPPED)
            
    def Stop(self, how):
        self.service.Stop()

def main(args, gate):
    if args.config:
        config = System.config.RawConfig(args.config)
    else:
        data = {
            'port' : 8724,
            'nump' : 1,
            'debug' : True,
            'http': {
                'curl_workers' : 2,
            },
            'wsx': {
                'stype' : 'http',
                'request_limit' : 1000,
            },
            'coordinator' : {
                'stype' : 'http',
                'url' : '127.0.0.1:8700',
            },
            'service' : {
                'max_pending' : 200,
                'max_immediate_pending' : 50,
                'login_token_check_time' : 30,
                'login_token_expire_time' : 180,
                'login_offset_time' : 15,
                'external_id' : 0,
            },
            "email":
            {
                "smtp" : "async",
                "smtp_host": "minsk-mail.nivalnetwork.com",
                "smtp_port": 25,
                "smtp_ssl": 0,
                "smtp_fromaddr": "pwconnect@zzima.com",
                "smtp_username": "pwconnect",
                "smtp_pwd": "teewnv2rZJ",

            }
        }
        config = System.config.RawConfig(data)
    svn = LoginService(args.sid)
    gate.AddService(svn, config)
#   svn.HttpLoggerInit(args, config)


if __name__ == "__main__":
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--config', default=None, help='Config path') 
    parser.add_argument('--sid', default='Login', help='Service id')
    parser.add_argument('--pid', default='login', help='Service process (instance) id')
    System.logs.setupParserArgs( parser )
    args = parser.parse_args()

    System.logs.setup(args.log, args.loglevel, args.logrotate)

    gate = Network.SOA.ServiceGate()

    main(args, gate)
    gate.Run()


