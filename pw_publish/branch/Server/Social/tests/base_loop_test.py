# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, json

## --------- for sync tests --------------
from base.helpers import *
from handlers import resetGlobals, users, SOCAGG_VERSION # между наборами тестов чистим глобальные серверные синглтоны (logins, users, peers)
import imemcache, isql, ihttp, idata

import cfg, coord_cfg # настройки MC/SQL (будем надеяться, актуальные) возьмем из локального конфига координатора
## --------- for Async (real MC/SQL/HTTP) test --------------
import thread, tornado.ioloop # для тестов, требующих асинхронной обработки
from tornado.options import options, define
from iwebserver import IWebServer
from ifactory import IfaceFactory

# ---------------------------------
from binascii import crc32   # zlib version is not cross-platform
# ---------------------------------
import unittest
import iaggregator


DEFAULT_LOG_LEVEL = logging.ERROR

def setDefaultLogLevel( level ):
    global DEFAULT_LOG_LEVEL
    DEFAULT_LOG_LEVEL = level
    
def logLevel( level=None ):
    if not level:
        level = DEFAULT_LOG_LEVEL
    logger = logging.getLogger()
    logger.setLevel( level )
    

##------------------------------------------------------------------------------------------------------------------
def ioloopThreadFunc( ioloop ):
    threadId = thread.get_ident()
    log( "starting -- ioloop %s -- (thread %d).." % (ioloop, threadId) )
    ioloop.start()
    log( "ioloop exit (thread %d)" % threadId )

##------------------------------------------------------------------------------------------------------------------
##------------------------------------------------------------------------------------------------------------------

""" Базовый класс для тестов, требующих асинхронной обработки, с участием настоящих async-thread-pool & IOLoop. """
class BaseLoopTest(unittest.TestCase):

    ##----------------------------------------------------------------
    ## заводим всю машинерию (ioloop, memcache/sql thread pools)
    def setUp(self):
        info( "--------------- LoopTest setUp start ---------------" )
        
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = imemcache.DUMMY_TEST_WS_ID
            options.server_name = imemcache.DUMMY_TEST_WS_NAME
        else:
            options["server_id"].set(imemcache.DUMMY_TEST_WS_ID)
            options["server_name"].set(imemcache.DUMMY_TEST_WS_NAME)

        self.loop = tornado.ioloop.IOLoop.instance()
        
        # запускаем в отдельном thread tornado IOLoop
        self.ioThreadId = thread.start_new_thread(ioloopThreadFunc, (self.loop, )) 
        info( "startUp: ioloop thread %d" % self.ioThreadId )
        
        info( "--------------- LoopTest setUp done ---------------" )


    ##----------------------------------------------------------------
    ## аккуратно прибиваем всю машинерию (ioloop, memcache/sql thread pools)
    def tearDown(self):
        logLevel() # отдельные тесты могут ставить свой уровень logging; возвращаем дефолтный...
        
        info( "--------------- LoopTest tearDown start ---------------" )
        
        resetGlobals() # между наборами тестов чистим глобальные серверные синглтоны (logins, users, peers)
            
        self.loop.stop() # прибиваем IOLoop, после этого должна закрыться и ioloopThread tornado IOLoop
        
        t0 = time.time()
        while self.loop._stopped: # ждем пока IOLoop закончит текущую итерацию и действительно остановится
            time.sleep(0.001)
            if time.time() - t0 > 1:
                raise
        
        info( "--------------- LoopTest tearDown done ---------------" )
        
        
    ##----------------------------------------------------------------
    ## ждем пока у test_obj не появится атрибут (поле, ключ) "reply", или пока не истекут max_sleep секунд
    def waitAsyncReply(self, test_obj, max_sleep=0.3):
        start = time.time()
        while not getattr(test_obj, "reply", None):
            time.sleep(0.001)
            if time.time() - start > max_sleep:
                log( "waitAsyncReply TIMEOUT [%.3f sec]" % max_sleep)
                raise "waitAsyncReply TIMEOUT"
