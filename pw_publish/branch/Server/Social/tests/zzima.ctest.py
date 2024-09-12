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
##print "os.cwd:", os.getcwd()
##print "sys.path:", sys.path

from ext_main.login import LoginAction
from ext_main.auth import AuthAction
from ext_pw import *

## --------- for sync tests --------------
from helpers import *
from test_action import TestAction, TestDictAction
from handlers import resetGlobals, users, SOCAGG_VERSION # между наборами тестов чистим глобальные серверные синглтоны (logins, users, peers)
from ifactory import IfaceFactory
import imemcache, isql, ihttp, idata

import cfg, coord_cfg # настройки MC/SQL (будем надеяться, актуальные) возьмем из локального конфига координатора
## --------- for Async (real MC/SQL/HTTP) test --------------
import thread, tornado.ioloop # для тестов, требующих асинхронной обработки
from tornado.options import options, define
from iwebserver import IWebServer
from pwserver import PwWorkServer
from modeldata.ModelData import ModelData
from modeldata.datamanager import PwNewModelManager
import MM # matchmaking const

from fake_guid import FakeWSGuidGenerator

# ---------------------------------
from binascii import crc32   # zlib version is not cross-platform
import xdbload
from config.MultiConfig import *
# ---------------------------------
import unittest
import iaggregator

from logic.keepalive import Keepalive
from base_cluster_test import *

from base_dummy_test import BaseDummyTest

##------------------------------------------------------------------------------------------------------------------

def ioloopThreadFunc( ioloop ):
    threadId = thread.get_ident()
    log( "starting -- ioloop %s -- (thread %d).." % (ioloop, threadId) )
    ioloop.start()
    log( "ioloop exit (thread %d)" % threadId )

##------------------------------------------------------------------------------------------------------------------
##------------------------------------------------------------------------------------------------------------------

    
#class LoopTest_Example( BaseClusterTest ):
class ZZima_Example( BaseDummyTest ):
    
    #----------------------------------------------------------------
    # zzima billing test
    def createCallbackFunc(self, methodName):
        def callbackFunc(reply):
            info("on_%s: %s" % (methodName, str(reply)))
            self.reply = reply
        return callbackFunc

    def makeZZimaTest(self, name, func, *params):
        self.reply = None
        func( *params, callback=self.createCallbackFunc(name) )
        self.waitAsyncReply(self, 20)
        return self.reply
        
    def test_GetBalanceEx(self):
        cfg.ZZIMA_SERVICE_PASSWORD = coord_cfg.COORDINATOR_ZZIMA_SERVICE_PASSWORD
        SERVICE_NAME = "pwdev"
        WSDL_URL = "http://b518.nivalnetwork.com:8080/API/PL/ZZServiceWeb.asmx?WSDL"
        
        import izzima
        izzima.WS_MAX_ZZIMA_THREADS = 1

        ZZ = IfaceFactory.makeZZimaInterface("http", WSDL_URL, HTTP=self.I.HTTP, service_name=SERVICE_NAME, syncWait=10.0)

        BILLING_LOGIN = 'devqa_1'
        reply = self.makeZZimaTest("getBalanceEx", ZZ.getBalanceEx, BILLING_LOGIN)
                
        tornado.ioloop.IOLoop.instance().zz.fadeout( 10.0 ) # синхронно ждем, пока thread pool отработает и убьется
        
    def testAZZima(self):
        ##logLevel( logging.INFO ) -- стоит включить DEBUG, как туда начинают валиться километры логов от soap-клиента. /do not want
        info( "testZZima start" )

        #~ cfg.ZZIMA_SERVICE_PASSWORD = coord_cfg.COORDINATOR_ZZIMA_SERVICE_PASSWORD
        #~ SERVICE_NAME = coord_cfg.COORDINATOR_ZZIMA_SERVICE_NAME
        #~ WSDL_URL = coord_cfg.COORDINATOR_ZZIMA_WSDL

        # БОЕВОЙ
        #~ cfg.ZZIMA_SERVICE_PASSWORD = coord_cfg.COORDINATOR_ZZIMA_SERVICE_PASSWORD
        #~ SERVICE_NAME = "pw"
        #~ WSDL_URL = "http://b208.nivalnetwork.com:8080/API/PL/ZZServiceWeb.asmx?WSDL"
        
        # ТЕСТОВЫЙ
        cfg.ZZIMA_SERVICE_PASSWORD = coord_cfg.COORDINATOR_ZZIMA_SERVICE_PASSWORD
        SERVICE_NAME = "pwdev"
        WSDL_URL = "http://b518.nivalnetwork.com:8080/API/PL/ZZServiceWeb.asmx?WSDL"
        
        import izzima
        izzima.WS_MAX_ZZIMA_THREADS = 1

        ZZ = IfaceFactory.makeZZimaInterface("http", WSDL_URL, HTTP=self.I.HTTP, service_name=SERVICE_NAME, syncWait=10.0)

        BILLING_LOGIN = 'test_dan1'
        #reply = self.makeZZimaTest("createUser", ZZ.createUser, BILLING_LOGIN, "dan12345432123@mail.ru", hashlib.md5("123454321").hexdigest() )
        reply = self.makeZZimaTest("subscribe", ZZ.subscribe, BILLING_LOGIN)
        reply = self.makeZZimaTest("getBalance", ZZ.getBalance, BILLING_LOGIN)
        reply = self.makeZZimaTest("replenish", ZZ.replenish, BILLING_LOGIN, 100.0, 'reason_test')
        reply = self.makeZZimaTest("writeOff", ZZ.writeOff, BILLING_LOGIN, 11.5, "pw_test")
        reply = self.makeZZimaTest("transfer", ZZ.transfer, BILLING_LOGIN, "quetz", 1.0, "pw_test_reason")
        warn("all passed")
        
        time.sleep(1.0)
        
        reply = self.makeZZimaTest("getBalance", ZZ.getBalance, BILLING_LOGIN)
        reply = self.makeZZimaTest("getBalance", ZZ.getBalance, "quetz")
                
        tornado.ioloop.IOLoop.instance().zz.fadeout( 10.0 ) # синхронно ждем, пока thread pool отработает и убьется


##------------------------------------------------------------------------------------------------------------------
##------------------------------------------------------------------------------------------------------------------

def main():
    DEFAULT_LOG_LEVEL = logging.INFO
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    
    BaseDummyTest.setXDB( None )
    
    info( "Starting tests..." )
    
    ## как исполнить отдельный test case:
    #~ suite = unittest.TestLoader().loadTestsFromTestCase(UnitTest_GiveHandler)
    #~ unittest.TextTestRunner(verbosity=2).run(suite)

    ITERATIONS = 1
    for i in range(ITERATIONS):
        try:
            unittest.main()
        except SystemExit:
            if str( exc() ) == "True":
                break
        except:
            catch()
            
        #time.sleep(0.01)

    info( "-- Finish tests (x %d)." % ITERATIONS )
    

if __name__ == "__main__":
    main()
