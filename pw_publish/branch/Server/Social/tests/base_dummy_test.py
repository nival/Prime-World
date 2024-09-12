#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, json

from ext_main.login import LoginAction
from ext_main.auth import AuthAction
from ext_pw import *

## --------- for sync tests --------------
from helpers import *
from test_action import TestAction, TestDictAction
from handlers import resetGlobals, users, PWSOC_VERSION, SOCAGG_VERSION 
from ifactory import IfaceFactory 
import imemcache, isql, ihttp
import ixchange

## --------- for Async (real MC/SQL/HTTP) test --------------
import thread, tornado.ioloop # для тестов, требующих асинхронной обработки
import cfg, coord_cfg # настройки MC/SQL (будем надеяться, актуальные) возьмем из локального конфига координатора
from config.MultiConfig import *
from tornado.options import options, define
from iwebserver import IWebServer
import iwebserver 
from pwserver import PwWorkServer
from modeldata.ModelData import *
from modeldata.datamanager import PwNewModelManager
from modeldata.persistent_data import PersistentDataManager
import MM # matchmaking const

from fake_guid import FakeWSGuidGenerator

# ---------------------------------
from binascii import crc32   # zlib version is not cross-platform
import xdbload
# ---------------------------------
import unittest

##------------------------------------------------------------------------------------------------------------------
##------------------------------------------------------------------------------------------------------------------

DEFAULT_LOG_LEVEL = logging.ERROR

def setDefaultLogLevel( level ):
    global DEFAULT_LOG_LEVEL
    DEFAULT_LOG_LEVEL = level

def logLevel( level=None ):
    if not level:
        level = DEFAULT_LOG_LEVEL
    logger = logging.getLogger()
    logger.setLevel( level )
    
def resetUserSessionsDummy( acc ):
    pass


##------------------------------------------------------------------------------------------------------------------
def ioloopThreadFunc( ioloop ):
    threadId = thread.get_ident()
    info( "starting -- ioloop %s -- (thread %d).." % (ioloop, threadId) )
    ioloop.start()
    info( "ioloop exit (thread %d)" % threadId )

##------------------------------------------------------------------------------------------------------------------
##------------------------------------------------------------------------------------------------------------------

""" Базовый класс для тестов, требующих асинхронной обработки, с участием настоящих async-thread-pool & IOLoop. """
class BaseDummyTest(unittest.TestCase):

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
        info( "startUp: ioloop thread %d" % self.ioThreadId )
        
        cfg.TOURNAMENT_SERVER = coord_cfg.COORDINATOR_TOURNAMENT_SERVER
        cfg.TOURNAMENT_SERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_SERVER_ADDR
        cfg.TOURNAMENT_XSERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_XSERVER_ADDR
        cfg.TOURNAMENT_SPECTATOR_AUIDS = coord_cfg.COORDINATOR_TOURNAMENT_SPECTATOR_AUIDS
        cfg.TOURNAMENT_APPLY_RESULTS = coord_cfg.COORDINATOR_TOURNAMENT_APPLY_RESULTS

        self.I = ClassDict()
        
        self.I.coord_res = {}
        self.I.coord_res["deploy_name"] = "RU"
        self.I.Config = MultiConfig()
        self.I.Config.fillStaticDataDependendValues(SDB)
        
        self.I.MC = IfaceFactory.makeMcInterface( "none", None )
        self.I.SQL = IfaceFactory.makeSqlInterface( "none", None)
        self.I.SSQL = IfaceFactory.makeSqlInterface( "sync", coord_cfg.COORDINATOR_SQL_CONFIG)
        self.I.DATA = IfaceFactory.makeIDataInterface( "none", None, None )
        self.I.PVX = IfaceFactory.makePvxMmInterface( "dummy" )
        self.I.SD = SDB
        self.I.MD = PwNewModelManager( ifaceDict=self.I, load_events=False )
        self.I.HTTP = tornado.httpclient.AsyncHTTPClient( max_clients=32 ) # может понадобиться для запросов к внешнему соц.аггрегатору
        self.I.AGG = IfaceFactory.makeSocAggInterface( "dummy", "", SOCAGG_VERSION) # пустая болванка
        self.I.STATS = IfaceFactory.makeIStatsInterface( "none", "", self.I ) # пустая болванка
        
        # еще придется пометить наш "якобы web-сервер" как "якобы активный":
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = iwebserver.DUMMY_TEST_WS_ID
            options.server_name = iwebserver.DUMMY_TEST_WS_NAME
        else:
            options["server_id"].set(iwebserver.DUMMY_TEST_WS_ID)
            options["server_name"].set(iwebserver.DUMMY_TEST_WS_NAME)
        
        self.I.SQL.addServer( options.server_id, options.server_name )
        self.I.WS = IWebServer() # fake обертка WS, умеет только guid-ы делать
        self.I.PS = IfaceFactory.makePersonServerInterface("none", None, self.I.HTTP)
        self.I.GS = IfaceFactory.makeGuildServiceInterface("none", None, self.I.HTTP)
        self.I.SMODEL = IfaceFactory.makeSerialModelInterface("sync", self.I, PWSOC_VERSION, load_conversion_xml=False)
        self.I.PDM = PersistentDataManager( self.I )
        self.I.BILL = IfaceFactory.makeBillingInterface( "dummy", self.I )
        self.I.SEX = ixchange.IFakeSocialExchange( HTTP=None )
        
        ## err( "self.I.PDM=%s" % self.I.PDM )

        info( "--------------- LoopTest setUp done ---------------" )


    ## ждем пока у test_obj не появится атрибут (поле, ключ) "reply", или пока не истекут max_sleep секунд
    def waitAsyncReply(self, test_obj, max_sleep=0.3):
        start = time.time()
        while not getattr(test_obj, "reply", None):
            time.sleep(0.001)
            if time.time() - start > max_sleep:
                log( "waitAsyncReply TIMEOUT [%.3f sec]" % max_sleep)
                raise Exception

    def makeAction(self, classOf, **kwargs):
        return TestDictAction( dict(**kwargs), classOf, request=self ) # MC, SQL и прочие интерфейсы забирайте прямо у нашего класса

    ## аккуратно прибиваем всю машинерию (ioloop, memcache/sql thread pools)
    def tearDown(self):
        ##logLevel() # отдельные тесты могут ставить свой уровень logging; возвращаем дефолтный...
        
        info( "--------------- LoopTest tearDown start ---------------" )
        # пометить наш "якобы web-сервер" как "якобы offline":
        self.I.SQL.removeServer( options.server_name )
        # time.sleep( 0.1 ) # пусть команда уйдет в sql, и даже ответ разберется ioloop-ом
        
        resetGlobals() # между наборами тестов чистим глобальные серверные синглтоны (logins, users, peers)
        self.I.SQL.fadeout() # мягко завершаем рабочий thread pool (дожидаемся, пока очистятся очереди)
        self.I.MC.destroy() # убиваем рабочий thread pool, чистим очереди
        
        # SQL.fadeout делаем асинхронно (syncWait=0), а здесь (синхронно) подождем, проследим как SQL мягко закроется и ioloop заберет его pending ответы
        self.I.SQL.fadeout( syncWait=2.0 )
        log( "self.I.SQL.isDone" )
            
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
                self.assert_(isinstance(change_list, list))
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
