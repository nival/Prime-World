#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, json, base64, hashlib
import random

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

os.chdir('..')
_addPath('.')
_addPath('cfg')
_addPath('libs')
##print "os.cwd:", os.getcwd()
##print "sys.path:", sys.path

import unittest
from base.helpers import *
#from ifactory import IfaceFactory
import thread
import tornado.httpclient
import tornado.ioloop # для тестов, требующих асинхронной обработки
import cfg, coord_cfg # настройки WSDL (будем надеяться, актуальные) возьмем из локального конфига координатора


#~ from ext_main.login import LoginAction
#~ from ext_main.auth import AuthAction
#~ from ext_pw import *

#~ ## --------- for sync tests --------------
#~ from helpers import *
#~ from test_action import TestAction, TestDictAction
#~ from handlers import resetGlobals, users, peers, SOCAGG_VERSION # между наборами тестов чистим глобальные серверные синглтоны (logins, users, peers)
#~ from ifactory import IfaceFactory
#~ import imemcache, isql, ihttp, idata

#~ import cfg, coord_cfg # настройки MC/SQL (будем надеяться, актуальные) возьмем из локального конфига координатора
#~ ## --------- for Async (real MC/SQL/HTTP) test --------------
#~ import thread, tornado.ioloop # для тестов, требующих асинхронной обработки
#~ from tornado.options import options, define
#~ from iwebserver import IWebServer
#~ from pwserver import PwWorkServer
#~ from modeldata.ModelData import ModelData
#~ from modeldata.datamanager import PwNewModelManager
#~ import MM # matchmaking const

#~ from fake_guid import FakeWSGuidGenerator

#~ # ---------------------------------
#~ from binascii import crc32   # zlib version is not cross-platform
#~ import xdbload
#~ # ---------------------------------
#~ import unittest
#~ import iaggregator

#~ from logic import KeepaliveAction
#~ from base_cluster_test import *

#~ from base_dummy_test import BaseDummyTest

##------------------------------------------------------------------------------------------------------------------

def ioloopThreadFunc( ioloop ):
    threadId = thread.get_ident()
    info( "starting -- ioloop %s -- (thread %d).." % (ioloop, threadId) )
    ioloop.start()
    info( "ioloop exit (thread %d)" % threadId )
    

STATS = ClassDict( maxWait=-1, maxExec=-1, replyCount=0, minWait=100000, minExec=100000, totalWait=0, totalExec=0)

def onBillingReply( reply ):
    info("onBillingReply: %s" % reply)
    tStart = reply.get("ts",0)
    tWait = tStart - reply.get("tq",0)
    tExec = reply.get("tr",0) - tStart
    
    global STATS
    STATS.replyCount += 1
    STATS.maxWait = max(STATS.maxWait, tWait)
    STATS.maxExec = max(STATS.maxExec, tExec)
    STATS.minWait = min(STATS.minWait, tWait)
    STATS.minExec = min(STATS.minExec, tExec)
    STATS.totalWait += tWait
    STATS.totalExec += tExec

##------------------------------------------------------------------------------------------------------------------
##------------------------------------------------------------------------------------------------------------------

import izzima
    
class ZZimaTest( unittest.TestCase ):
    
    ## заводим всю машинерию (ioloop, memcache/sql thread pools)
    def setUp(self):
        info( "--------------- LoopTest setUp start ---------------" )
        self.loop = tornado.ioloop.IOLoop.instance()
        
        # запускаем в отдельном thread tornado IOLoop
        self.ioThreadId = thread.start_new_thread(ioloopThreadFunc, (self.loop, )) 
        info( "startUp: thread %d" % self.ioThreadId )
        
        self.I = ClassDict()
        self.I.HTTP = tornado.httpclient.AsyncHTTPClient( max_clients=128 ) 
        
        info( "--------------- LoopTest setUp done ---------------" )
        
    def tearDown(self):
        self.loop.stop() # прибиваем IOLoop, после этого должна закрыться и ioloopThread tornado IOLoop
        
        t0 = time.time()
        while self.loop._stopped: # ждем пока IOLoop закончит текущую итерацию и действительно остановится
            time.sleep(0.001)
            if time.time() - t0 > 1:
                raise
        
        info( "--------------- LoopTest tearDown done ---------------" )        
        
    #~ ## ждем пока у test_obj не появится атрибут (поле, ключ) "reply", или пока не истекут max_sleep секунд
    #~ def waitAsyncReply(self, test_obj, max_sleep=0.3):
        #~ start = time.time()
        #~ while not getattr(test_obj, "reply", None):
            #~ time.sleep(0.001)
            #~ if time.time() - start > max_sleep:
                #~ log( "waitAsyncReply TIMEOUT [%.3f sec]" % max_sleep)
                #~ raise
                
    #~ #----------------------------------------------------------------
    #~ # zzima billing test
    #~ def createCallbackFunc(self, methodName):
        #~ def callbackFunc(reply):
            #~ info("on_%s: %s" % (methodName, str(reply)))
            #~ self.reply = reply
        #~ return callbackFunc

    #~ def makeZZimaTest(self, name, func, *params):
        #~ self.reply = None
        #~ func( *params, callback=self.createCallbackFunc(name) )
        #~ self.waitAsyncReply(self, 3)
        #~ return self.reply
        
    def onTick(self):
        info("---- TICK! -----")
        
    def testZZimaLoad(self):
        ##logLevel( logging.INFO ) -- стоит включить DEBUG, как туда начинают валиться километры логов от soap-клиента. /do not want
        info( "testZZimaLoad start" )
        
        self.loop.add_timeout( 0.5, self.onTick )

        # ТЕСТОВЫЙ
        cfg.ZZIMA_SERVICE_PASSWORD = coord_cfg.COORDINATOR_ZZIMA_SERVICE_PASSWORD
        SERVICE_NAME = coord_cfg.COORDINATOR_ZZIMA_SERVICE_NAME
        BILLING_PREFIX = coord_cfg.COORDINATOR_AGG_BILLING_PREFIX
        WSDL_URL = coord_cfg.COORDINATOR_ZZIMA_WSDL
        ZZIMA_THREADS = 10
        ZZIMA_SYNC_WAIT = 120.0

        #~ # БОЕВОЙ
        #cfg.ZZIMA_SERVICE_PASSWORD = coord_cfg.COORDINATOR_ZZIMA_SERVICE_PASSWORD
        #SERVICE_NAME = "pw"
        #BILLING_PREFIX = "ruopr_"
        #WSDL_URL = "http://b208.nivalnetwork.com:8080/API/PL/ZZServiceWeb.asmx?WSDL"

        #~ # чтобы не импортировать весь вагон исходников из ifactory
        #~ import cluster_zzima
        #~ self.I.ZZ = izzima.AsyncZZima( None, SERVICE_NAME )
        #~ self.loop.zz = cluster_zzima.AsyncZZimaManager( WSDL_URL, ZZIMA_THREADS, ZZIMA_SYNC_WAIT )
        
        import izzima
        self.I.ZZ = izzima.HttpZZima( self.I.HTTP, service_name=SERVICE_NAME, payment_system="CBT", billing_url=WSDL_URL )
        self.loop.zz = self.I.ZZ
        
        ##self.I.HTTP.fetch( "http://rbc.ru", onBillingReply )

        START_AUID = random.randint(50000,60000)

        GET_COUNT = 1
        TEST_RUNTIME = 10
        ASK_PERIOD = 10

        t0 = time.time()
        warn( "\n- starting test: %d x getUserBalance, now: %.3f" % (GET_COUNT, t0))
        
        # для каждого игрока заводим запись вида "auid->askTimestamp"
        records = {}
        MAX_DIV = 1000 # дробим общий период на N интервалов
        for auid in xrange(START_AUID, START_AUID+GET_COUNT):
            timestamp_offset = random.randint(0,MAX_DIV) * ASK_PERIOD / MAX_DIV
            timestamp = t0 + timestamp_offset
            records[auid] = timestamp # начиная с этого момента времени будем спрашивать баланс
            info( "start timestamp[%d] = %.3f" % (auid, timestamp) )
        
        now = time.time()
        while now < t0 + TEST_RUNTIME:
            ##info( "now: %.3f" % now )
            for auid,timestamp in records.iteritems():
                if now >= timestamp:
                    info( "get[%d]: timestamp %.3f, now %.3f" % (auid, timestamp, now) )
                    #BILLING_LOGIN = BILLING_PREFIX + str(auid)
                    BILLING_LOGIN = 'quetz'
                    self.I.ZZ.getBalance( BILLING_LOGIN, callback=onBillingReply )
                    self.I.ZZ.replenish( BILLING_LOGIN, 1.0, "_reason", callback=onBillingReply )
                    records[auid] = now + ASK_PERIOD
                    
            time.sleep( 0.01 )
            now = time.time()
            
        warn( "\n- finish test period: now %d" % now )
        
        # ---------------------------------------------------------------------------------------------------------------------
        tornado.ioloop.IOLoop.instance().zz.fadeout( 20.0 ) # синхронно ждем, пока thread pool отработает и убьется

        t1 = time.time()
        warn( "finish test: %d x users, %.3f msec" % (GET_COUNT, t1-t0) )
        
        warn( "TEST STATS: reply count: %d\n- execution time:  min=%.3f .. max=%.3f (avg=%.3f)" \
                          "\n- queue wait time: min=%.3f .. max=%.3f (avg=%.3f)" \
                % (STATS.replyCount, STATS.minExec, STATS.maxExec, STATS.totalExec/max(STATS.replyCount,1), \
                STATS.minWait, STATS.maxWait, STATS.totalWait/max(STATS.replyCount,1)) )


##------------------------------------------------------------------------------------------------------------------
##------------------------------------------------------------------------------------------------------------------

def main():
    DEFAULT_LOG_LEVEL = logging.INFO
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    
    info( "Starting tests..." )
    
    ITERATIONS = 1
    for i in range(ITERATIONS):
        try:
            unittest.main()
        except SystemExit:
            if str( exc() ) == "True":
                break
        except:
            catch()
            
    info( "-- Finish tests (x %d)." % ITERATIONS )
    

if __name__ == "__main__":
    main()
