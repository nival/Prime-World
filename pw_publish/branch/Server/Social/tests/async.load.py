# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, random, json, hashlib, urllib, httplib, thread, logging

########################
import asyncore, socket
import urllib2
from binascii import crc32 # zlib version is not cross-platform

sys.path.append('..')
sys.path.append('../base')
from helpers import * 
from http_dumb import *

sys.path.append('../tornado')
import tornado.options
from tornado.options import define,options

import tornado.ioloop

define("server", default="127.0.0.1:88", help="connect to given ip:port")
define("num_threads", default=2, help="http client thread count", type=int)
define("log_level", default="info", help="logging level")
define("scenario", default="async", help="test scenario: async|aggregator")

def randomUserId(i):
    ## return random.randint(1,500)
    return 1+i # 1..num_threads

def randomFraction(i):
    return "A" if (i%2) == 0 else "B"

##--------------------------------------------------------------------------------
httpAsyncClient = None
handlers = []

SUCCESS_COUNT = 0

##--------------------------------------------------------------------------------
##--------------------------------------------------------------------------------

class BaseAsyncFetcher:
    """ базовый класс, умеет только получать интерфейсы, делать http fetch, стартовать и сваливать """
    def __init__(self, id, uid, fraction, HTTP, HANDLERS):
        self.id = id
        self.uid = uid
        self.fraction = fraction
        self.HTTP = HTTP
        self.HANDLERS = HANDLERS
        self.t0 = time.time()

        # добавляем себя в глобальное множество handler-ов
        HANDLERS.append( self )    
        
    # ---------------------------------------------
    def fin(self):
        # удаляем себя из глобального множества handler-ов
        self.HANDLERS.remove(self)
        #~ log("fin: handlers left %d" % len(handlers))
        if not self.HANDLERS:
            tornado.ioloop.IOLoop.instance().stop()
            
    # ---------------------------------------------
    # OVERRIDABLE
    def start(self, scenario="default"):
        self.fin()
        
    # ---------------------------------------------
    def fetch(self, request, callback):
        self.request = request
        self.callback = callback
        self.HTTP.fetch( request, self.onFetch, connect_timeout=5.0, request_timeout=5.0 )
        
    # ---------------------------------------------
    def onFetch(self, response):
        if response.error:
            print "Error:", response.error
        else:
            try:
                self.t1 = time.time()
                info( "onFetch[%d] '%s' t%0.3f: %s" % ( self.id, str(self.request), self.t1-self.t0, str(response.body) ) )
            
                res = json_loads(response.body)
                ret = res["response"]
            except:
                catch()
            if ret:
                try:
                    return self.callback( ret )
                except:
                    catch()
        
        self.fin()

    # ---------------------------------------------
    # вешаем вызов callback через указанное кол-во секунд 
    # (аргументы, видимо, передавать неявно, через поля self.xxx)
    def setRetry(self, retry_seconds, callback):
        loop = tornado.ioloop.IOLoop.instance()
        t0 = time.time()
        loop.add_timeout(t0 + 1, callback)
        
        
##--------------------------------------------------------------------------------
##--------------------------------------------------------------------------------

class LoginAsyncFetcher( BaseAsyncFetcher ):
    """ умеем делать login + keepalive """
    # ---------------------------------------------
    def start(self, scenario="default"):
        if scenario=="default":
            self.login = "user%d" % self.uid
            pwd = "pwd%d" % self.uid
            auth = hashlib.md5(pwd).hexdigest()
            self.fetch( options.server + "/?action=login&user=%s&auth=%s&testkey=1" % (self.login, auth), self.handle_login )
        
    # ---------------------------------------------
    def handle_login(self, ret):
        self.uid = ret.get("uid", 0)
        self.server = ret.get("server", "")
        self.authTries = 0
        self.onLogin()
        return
        
    # ---------------------------------------------
    # OVERRIDABLE
    def onLogin(self):
        self.fetch( options.server + "/%s?action=auth&uid=%d&key=12345" % (self.server, self.uid), self.handle_auth )
        
    # ---------------------------------------------
    def handle_auth(self, ret):
        if ret.get("ok") and ret.get("loaded"):
            info( "AUTH_OK" )
            #~ self.data =
        else:
            warn( "AUTH: not loaded [%d]!" % self.id )
            
            #--- RETRY until valid persistent data:
            self.authTries += 1
            if self.authTries < 5:
                return self.setRetry(1, self.onLogin) # повесить retry через 1 сек.
            warn( "AUTH: 5 times FAIL: forcing NEW set_fraction" )
            
        return self.onAuth()
        
    # ---------------------------------------------
    # OVERRIDABLE
    def onAuth(self):
        self.fetch( options.server + "/%s?action=keepalive&uid=%d&key=12345" % (self.server, self.uid), self.handle_ka )
    
    # ---------------------------------------------
    def handle_ka(self, ret):
        #finish anyway:
        warn( "AUTH_FAIL!" )
        self.fin()

        

##--------------------------------------------------------------------------------
##--------------------------------------------------------------------------------

class MmAsyncFetcher( LoginAsyncFetcher ):
    """ умеем делать matchmaking-запросы """
    # ---------------------------------------------
    def onAuth(self):
        # на всякий случай, каждый раз делаем reset пользовательской ModelData (мало ли какая хрень там была сохранена в БД..) на свежий model с 1 героем (faceless)
        self.fetch( options.server + "/%s?action=set_fraction&uid=%d&key=12345&fraction=%s&create_heroes=1&force_new=1"
            % (self.server, self.uid, self.fraction), self.onSetFraction )

    def onSetFraction(self, ret):
        if ret.get("ok"):
            info( "fresh SET_FRACTION(fraction %s, 1 hero) OK, uid=%s" % (self.fraction, self.uid) )
            return self.addMmSession() # ломимся сразу, не ждем; должно правильно обработать mm_cancel + mm_add
            ##return self.setRetry(3, self.addMmSession) # сессию добавим через 3 секунды, чтобы успели пройти mm-cancel, "зачищающие MM-статус после логина"
            ## return self.cancelMmSessionsAll() # делаем mm_cancel ALL (проверим, что это не сломает одновременный mm_add)
            
        #fail
        warn( "fresh SET_FRACTION FAIL!" )
        self.fin()

    # ---------------------------------------------
    def addMmSession(self, game_type="pvp1x1", hero=crc32("faceless")):
        self.fetch( options.server + "/%s?action=mm_add&uid=%d&key=12345&game_type=%s&fraction=%s&hero=%s&snuid=%s" 
            % (self.server, self.uid, str(game_type), self.fraction, str(hero), self.login ),
            self.handle_mm_add )
        
    # ---------------------------------------------
    def handle_mm_add(self, ret):
        if ret.get("ok"):
            self.mmid = ret.get("mmid")
            return self.pingMmSessions()
            
        #fail
        warn( "MM_PING FAIL!" )
        self.fin()
        
    # ---------------------------------------------
    def pingMmSessions(self):
        self.fetch( options.server + "/%s?action=mm_ping&uid=%d&key=12345&mmid=0" 
            % (self.server, self.uid),
            self.handle_mm_ping )
        
    # ---------------------------------------------
    def handle_mm_ping(self, ret):
        if ret.get("ok"):
            sessions = ret.get("ModelData")[0][2] # model = [ [op, path, value] ]
            if sessions.get(self.mmid) and sessions[self.mmid].get("progress") >= MM.STATUS_WAITING_ACCEPT:
                ## return self.cancelMmSessions()
                return self.acceptMmSession( self.mmid )
            else:
                return self.setRetry(1, self.pingMmSessions) # повесить retry через 1 сек

        #finish
        warn( "MM_PING FAIL!" )
        self.fin()
        
    # ---------------------------------------------
    def cancelMmSessionsAll(self):
        self.fetch( options.server + "/%s?action=mm_cancel&uid=%d&key=12345&mmid=0" 
            % (self.server, self.uid),
            self.handle_mm_cancel_all )
        
    # ---------------------------------------------
    def handle_mm_cancel_all(self, response):
        if response.get("ok"):
            info( "MM_CANCEL_ALL ok" )
            return self.addMmSession()
        elif response.get("error", "").startswith("no active"):
            info( "MM_CANCEL_ALL: no sessions" )
            return self.addMmSession()

        warn( "MM_CANCEL FAIL!" )
        #finish anyway
        self.fin()
        
    # ---------------------------------------------
    def acceptMmSession(self, mmid):
        self.fetch( options.server + "/%s?action=mm_accept&uid=%d&key=12345&mmid=%s" 
            % (self.server, self.uid, str(mmid)),
            self.handle_mm_accept )
        
    # ---------------------------------------------
    def handle_mm_accept(self, response):
        if response.get("ok"):
            info( "MM_ACCEPT OK mmid=%s, uid=%s" % (self.mmid, self.uid) )
            return self.pingMmSessionsForSessionKey()
                        
        #finish anyway
        warn( "MM_ACCEPT FAIL!" )
        self.fin()
        
    # ---------------------------------------------
    def pingMmSessionsForSessionKey(self):
        self.fetch( options.server + "/%s?action=mm_ping&uid=%d&key=12345&mmid=0" 
            % (self.server, self.uid),
            self.handle_mm_ping_session_key )
        
    # ---------------------------------------------
    def handle_mm_ping_session_key(self, ret):
        if ret.get("ok"):
            sessions = ret.get("ModelData")[0][2] # model = [ [op, path, value] ]
            if sessions.get(self.mmid) and sessions[self.mmid].get("session_id"):
                global SUCCESS_COUNT
                SUCCESS_COUNT += 1
            
                info( "GOT SESSION_KEY [%d] mmid=%s, uid=%s" % (SUCCESS_COUNT, self.mmid, self.uid) )
                
                return self.logout()
            else:
                return self.setRetry(1, self.pingMmSessionsForSessionKey) # повесить retry через 1 сек

        #finish
        self.fin()

    # ---------------------------------------------
    def logout(self):
        self.fetch( options.server + "/%s?action=logout&uid=%d&key=12345" 
            % (self.server, self.uid), self.handle_logout )
            
    # ---------------------------------------------
    def handle_logout(self, ret):
        info( "handle_logout, uid=%s, ret=%s" % (self.uid, str(ret)) )
        #finish
        self.fin()


##--------------------------------------------------------------------------------
##--------------------------------------------------------------------------------

class SocialAggregatorFetcher( BaseAsyncFetcher ):
    """ умеем делать запрос к соц.аггрегатору """
    # ---------------------------------------------
    def start(self):
        self.login = "user%d" % self.uid
        pwd = "pwd%d" % self.uid
        self.sntoken = hashlib.md5(pwd).hexdigest() # для предсказуемости/консистентности тестов всегда передаем один и тот же token для одного и того же логина
        self.fetch( options.server + "/x?action=login&snid=fb&snuid=%s&sntoken=%s&ver=0.0.1" % (self.login, self.sntoken), self.handle_login )
        
    # ---------------------------------------------
    def handle_login(self, ret):
        if ret and ret.get("error",1) == 0:
            self.auid = ret.get("auid", 0)
            return self.getInfo()
        self.fin()

    # ---------------------------------------------
    def getInfo(self):
        request_email = str(random.randint(0,1) == 0)
        self.fetch( options.server + "/x?action=get_info&snid=fb&auid=%s&include_secure_data=%s" % (self.auid, request_email), self.handle_get_info )
        
    # ---------------------------------------------
    def handle_get_info(self, ret):
        if ret and ret.get("error",1) == 0:
            global SUCCESS_COUNT
            SUCCESS_COUNT += 1
        self.fin()
        

##-------------------------------------------------------------------------------
## старт 
def main():
    tornado.options.parse_command_line()
    print "Test client start: scenario %r, %d threads" % (options.scenario, options.num_threads)
    
    logging.basicConfig( filename=options.log_file_prefix, level=loggingSeverity(options.log_level), format='[%(asctime)s %(levelname)8s] %(message)s' )
    log( 'This message should go to the log file' )
    
    #~ digest16 = hashlib.md5("12345").hexdigest()
    #~ int64 = md5_int64("12345")
    #~ print "md5[8] long: %d (0x%x)" % (int64, int64)
        
    global httpAsyncClient
    global handlers
    httpAsyncClient = tornado.httpclient.AsyncHTTPClient( max_clients=options.num_threads ) #, max_simultaneous_connections= )
    handlers = []

    t0 = time.time()
    
    for i in range(0, options.num_threads):
        uid = randomUserId(i)
        fraction = randomFraction(i)
        if options.scenario == "async":
            async = MmAsyncFetcher(i, uid, fraction, httpAsyncClient, handlers)
        elif options.scenario == "aggregator":
            async = SocialAggregatorFetcher(i, uid, fraction, httpAsyncClient, handlers)
        async.start()

    info("ASYNC ioloop start")
    tornado.ioloop.IOLoop.instance().start()
        
    t1 = time.time()
    print "%d threads done: %0.3f sec, SUCCESS: %d/%d" % (options.num_threads, t1-t0, SUCCESS_COUNT, options.num_threads)



if __name__ == "__main__":
    main()
