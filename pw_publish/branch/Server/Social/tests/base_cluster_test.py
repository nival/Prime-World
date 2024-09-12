# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, json

## --------- for sync tests --------------
import sys
sys.path.append("../cfg")

from base.helpers import *
from test_action import TestAction, TestDictAction
from handlers import resetGlobals, users, PWSOC_VERSION, SOCAGG_VERSION 
import imemcache, isql, ihttp, idata

import cfg, coord_cfg # настройки MC/SQL (будем надеяться, актуальные) возьмем из локального конфига координатора
## --------- for Async (real MC/SQL/HTTP) test --------------
import thread, tornado.ioloop # для тестов, требующих асинхронной обработки
from tornado.options import options, define
from iwebserver import IWebServer
from ifactory import IfaceFactory
from pwserver import PwWorkServer
from config.MultiConfig import *
from modeldata.ModelData import ModelData
from modeldata.datamanager import PwNewModelManager
from modeldata.changes import CHANGE_OP_CODES 
from modeldata.persistent_data import PersistentDataManager

# ---------------------------------
from binascii import crc32   # zlib version is not cross-platform
# ---------------------------------
import unittest
from itertools import repeat, starmap
import iaggregator
import ipersonserver


##------------------------------------------------------------------------------------------------------------------
#DEFAULT_LOG_LEVEL = logging.ERROR
DEFAULT_LOG_LEVEL = logging.WARNING

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
def resetUserSessionsDummy( acc ):
    acc.data.mm = {}


##------------------------------------------------------------------------------------------------------------------
##------------------------------------------------------------------------------------------------------------------

class BaseClusterTest(unittest.TestCase):
    """ Базовый класс для тестов, требующих асинхронной обработки, с участием настоящих async-thread-pool & IOLoop. """
    
    @staticmethod
    def setXDB( _sdb ):
        global SDB
        SDB = _sdb
        
    ## заводим всю машинерию (ioloop, memcache/sql thread pools)
    def setUp(self):
        info( "--------------- LoopTest setUp start ---------------" )
        #self.loop = tornado.ioloop.IOLoop.instance()
        self.loop = tornado.ioloop.IOLoop.instance()
        
        # запускаем в отдельном thread tornado IOLoop
        self.ioThreadId = thread.start_new_thread(ioloopThreadFunc, (self.loop, )) 
        log( "startUp: thread %d" % self.ioThreadId )
        
        self.I = ClassDict()
        
        self.I.Config = MultiConfig()
        
        # запускаем реальный async memcache thread pool
        self.I.MC = IfaceFactory.makeMcInterface( "async", coord_cfg.COORDINATOR_MC_SERVER_LIST )
        
        # запускаем реальный async sql thread pool
        self.I.SQL = IfaceFactory.makeSqlInterface( "async", coord_cfg.COORDINATOR_SQL_CONFIG )

        # заглушка
        #self.I.DATA = IfaceFactory.makeIDataInterface( "sql", coord_cfg.COORDINATOR_MONGO_CONFIG, self.I.SQL )
        self.I.DATA = IfaceFactory.makeIDataInterface( "mongo", coord_cfg.COORDINATOR_MONGO_CONFIG, self.I.SQL )
        
        # заводим заглушку для PvX matchmaking
        self.I.PVX = IfaceFactory.makePvxMmInterface( "dummy" )

        '''
        self.I.SD = {}

        self.I.MD = PwNewModelManager( ifaceDict=self.I, load_events=False )
        '''

        self.I.HTTP = tornado.httpclient.AsyncHTTPClient( max_clients=32 ) # может понадобиться для запросов к внешнему соц.аггрегатору
        self.I.PS = ipersonserver.IPersonServer() # пустая болванка 
        #self.I.GS = IfaceFactory.makeGuildServiceInterface("none", None, self.I.HTTP)
        ## self.I.PS = IfaceFactory.makePersonServerInterface(options.pers, coord_cfg.COORDINATOR_PERSON_SERVER_ADDRESS, HTTP=self.I.HTTP)

        # еще придется пометить наш "якобы web-сервер" как "якобы активный":
        #options["server_id"].set(imemcache.DUMMY_TEST_WS_ID)
        #options["server_name"].set(imemcache.DUMMY_TEST_WS_NAME)
        self.I.SQL.addServer( options.server_id, options.server_name )
        
        self.I.WS = IWebServer() # fake обертка WS, умеет только guid-ы делать
        
        self.I.SMODEL = IfaceFactory.makeSerialModelInterface("sync", self.I, PWSOC_VERSION, load_conversion_xml=False)
        self.I.PDM = PersistentDataManager( self.I )
        self.I.BILL = IfaceFactory.makeBillingInterface( "dummy", self.I )
        self.I.STATS = IfaceFactory.makeIStatsInterface( "none", "", self.I ) # пустая болванка

        info( "--------------- LoopTest setUp done ---------------" )


    ## ждем пока у test_obj не появится атрибут (поле, ключ) "reply", или пока не истекут max_sleep секунд
    def waitAsyncReply(self, test_obj, max_sleep=0.3):
        start = time.time()
        while not getattr(test_obj, "reply", None):
            time.sleep(0.001)
            if time.time() - start > max_sleep:
                log( "waitAsyncReply TIMEOUT [%.3f sec]" % max_sleep)
                raise Exception("%s: waitAsyncReply TIMEOUT [%.3f sec]" % (test_obj,max_sleep))

    def makeAction(self, classOf, **kwargs):
        return TestDictAction( dict(**kwargs), classOf, request=self ) # MC, SQL и прочие интерфейсы забирайте прямо у нашего класса

    def test_count(self):
        self.count = 1000000000
        while self.count:
            print self.count
            self.I.DATA.find_one("guilds", "guilds", {"key": {"$exists": True}})
            self.I.DATA.find_one("guilds", "guilds", {"key": {"$exists": False}})
            self.count -= 1


    ## аккуратно прибиваем всю машинерию (ioloop, memcache/sql thread pools)
    def tearDown(self):
        logLevel() # отдельные тесты могут ставить свой уровень logging; возвращаем дефолтный...
        
        info( "--------------- LoopTest tearDown start ---------------" )
        # пометить наш "якобы web-сервер" как "якобы offline":
        self.I.SQL.removeServer( options.server_name )
        # time.sleep( 0.1 ) # пусть команда уйдет в sql, и даже ответ разберется ioloop-ом
        
        resetGlobals() # между наборами тестов чистим глобальные серверные синглтоны (logins, users, peers)
        #~ log( "tearDown: thread %d" % self.ioThreadId )
        self.I.SQL.fadeout() # мягко завершаем рабочий thread pool (дожидаемся, пока очистятся очереди)
        self.I.MC.destroy() # убиваем рабочий thread pool, чистим очереди
        self.I.DATA.fadeoutData() # мягко завершаем рабочий thread pool (дожидаемся, пока очистятся очереди)
        #~ log( "SQL.fadeout called" )
        
        # SQL.fadeout делаем асинхронно (syncWait=0), а здесь (синхронно) подождем, проследим как SQL мягко закроется и ioloop заберет его pending ответы
        self.I.SQL.fadeout( syncWait=2.0 )
        #~ while not self.I.SQL.isDone():
            #~ time.sleep(0.001)
        warn( "self.I.SQL.isDone" )
            
        self.loop.stop() # прибиваем IOLoop, после этого должна закрыться и ioloopThread tornado IOLoop
        
        t0 = time.time()
        while self.loop._stopped: # ждем пока IOLoop закончит текущую итерацию и действительно остановится
            time.sleep(0.001)
            if time.time() - t0 > 1:
                raise Exception
        
        info( "--------------- LoopTest tearDown done ---------------" )

    # ------------ 
    # helper
    def assertModelChangeFormat( self, model_changes ):
        for event in model_changes:
            self.assert_(event and isinstance(event, dict))
            for comment,change_list in event.iteritems():
                self.assert_(comment and isinstance(comment, basestring))
                self.assert_(change_list and isinstance(change_list, list))
                for change_line in change_list:
                    self.assert_( change_line and isinstance(change_line, list) and len(change_line)==3 )
                    path, op, values = change_line
                    assert( path and isinstance(path, basestring) )
                    assert( op and isinstance(op, basestring) and (op in CHANGE_OP_CODES) )
                    
                    if op in ['init', 'add', 'upd']:
                        assert( values and (isinstance(values, dict)) )
                    elif op == "del":
                        assert( values and (isinstance(values, int) or isinstance(values, basestring)) )
                    elif op == "swap":
                        assert( values and isinstance(values, list) and len(values)==2 )



