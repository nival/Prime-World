#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, json, base64, hashlib

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

os.chdir('..')
_addPath('.')
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
from modeldata.MultiStaticData import MultiStaticData
from config.MultiConfig import *
# ---------------------------------
import unittest
import iaggregator

from logic.keepalive import Keepalive
from base_cluster_test import *


##------------------------------------------------------------------------------------------------------------------
def ioloopThreadFunc( ioloop ):
    threadId = thread.get_ident()
    log( "starting -- ioloop %s -- (thread %d).." % (ioloop, threadId) )
    ioloop.start()
    log( "ioloop exit (thread %d)" % threadId )

##------------------------------------------------------------------------------------------------------------------
##------------------------------------------------------------------------------------------------------------------

    
""" Пример конкретного "асинхронного теста"  """
class LoopTest_Example( BaseClusterTest ):
    ## -------------------------------------------------------------------------------------------------------------------------------------
    ## helper: логиним юзера, ждем пока загрузятся persistent данные
    def loginAndLoad(self, login_name=""):
        self.I.GG = FakeWSGuidGenerator()
        self.I.WS = PwWorkServer( I=self.I, test_mode=True )
        
        self.I.WS.MM_PING_PERIOD = -1 # чтобы генерация пакетов для matchmaking не делала задержек между пингами статуса сессий юзера
        self.I.WS.MM_MIN_ADD_PERIOD = 0
        self.I.WS.resetUserSessions = resetUserSessionsDummy # заменяем настоящий "принудительный mm_cancel" заглушкой
        self.I.WS.nextInt64GUID = self.I.GG.nextInt64GUID # подменяем GUID Generator на фейк, раздающий ID-шки для ModelData с единицы
        self.HERO_ID = 1
        
        # ---------
        # login 
        self.allow_login_underscores = 1
        test = self.makeAction( LoginAction, guest=1 )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        ##err( "test.reply:" + str(test.reply) )
        self.assert_( test.reply and test.reply.get("ok") ) # первый раз берем из MC или SQL
        
        #~ ## # ---------
        #~ ##test = self.makeAction( LoginAction, user=login_name, auth="12345" )
        #~ ##test.OnStart()

        #~ ##self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ ##self.assert_( test.reply and test.reply.get("ok") and test.reply["_depth"] == 1 ) # второй раз берем из кэша сервера

        self.assert_( test.reply and test.reply.get("uid") ) 
        
        self.uid = test.reply.get("uid")
        self.acc = users.get( self.uid )
                
        self.assert_( self.uid and self.acc ) 
        
        # ---------------------------
        # auth / get persistent data
        loaded = None
        t0 = time.time()
        while not loaded:
            test = self.makeAction( AuthAction )
            test.OnStart()

            self.waitAsyncReply( test, 1.0 ) # ждем асинк-ответа
            self.assert_( test.reply and test.reply.get("loaded") != None ) 
            
            loaded = test.reply.get("loaded")
            if time.time() - t0 > 3.0: # даем полсекунды на загрузку persistent data
                raise "persistent data not loaded"
            
            time.sleep(0.05)

        # ок, загрузили persistent data
        self.assert_( loaded and self.acc.data ) 


    def newDataModel( self ):
        # ---------------------------
        # create new DataModel (1 hero)
        test = self.makeAction( SetFractionAction, fraction="A", create_heroes=2, force_new=1 )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") and test.reply.get("init") ) 
        
    
    ## первый набор: создать пару сессий, пингануть, cancel
    def testKeepalive(self):
        self.loginAndLoad()
        self.newDataModel()
        
        ##logLevel( logging.DEBUG )
        info( "---------- testKeepalive ----------" )
        
        session_results = pickRandom( MM.TEST_SESSION_RESULTS )
        self.I.WS.applyGameSessionResults( self.acc, "mmid_TEST_", 1234567890, session_results, "pvp", None ) 
                
        test = self.makeAction( Keepalive )
        test.OnStart()
        
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 

        model_changes = test.reply.get("ModelData")
        info( "Keepalive reply: %s, pending changes count: %d" % (test.reply, len(model_changes)) )
        self.assert_( model_changes ) 
        self.assert_( isinstance(model_changes, list) and len(model_changes) == 65 )
        
        self.assertModelChangeFormat( model_changes )
        
        
    #~ ## первый набор: создать пару сессий, пингануть, cancel
    #~ def testMatchmake1(self):
        #~ self.loginAndLoad()
        #~ self.newDataModel()
        
        #~ ##logLevel( logging.DEBUG )
        #~ log( "---------- testMatchmake1 ----------" )
                
        #~ # ---------------------------
        #~ # add mm session 1
        #~ test = self.makeAction( MatchmakingAddAction, game_type="pvp", fraction="A", src_hero_id=self.HERO_ID )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") ) 
        
        #~ self.mmid = test.reply.get("mmid")
    
        #~ # ---------------------------
        #~ # cancel 1
        #~ test = self.makeAction( MatchmakingCancelAction, mmid=self.mmid )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") == self.mmid and test.reply.get("mm") == None ) 
        
        #~ # ---------------------------
        #~ # add mm session 2
        #~ test = self.makeAction( MatchmakingAddAction, game_type="pvb", fraction="B", src_hero_id=self.HERO_ID )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") ) 
        
        #~ self.mmid2 = test.reply.get("mmid")
        
        #~ # ---------------------------
        #~ # add BAD session 3
        #~ test = self.makeAction( MatchmakingAddAction, game_type="xxx", fraction="X", src_hero_id=0 )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and not test.reply.get("ok") ) 

        #~ # ---------------------------
        #~ # ping session
        #~ test = self.makeAction( MatchmakingPingAction, mmid=self.mmid2 )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") != None ) 
        #~ sessions = test.reply.get("mm")
        #~ self.assert_( sessions.get("progress") ) # должен быть словарь конкретной сессии, без вложенных { mmid: {session data}, mmid2: {...}
        
        #~ # ---------------------------
        #~ # ping BAD session
        #~ test = self.makeAction( MatchmakingPingAction, mmid="mm_xxx_x" )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") == 0 and test.reply.get("error") ) 
        
        #~ # ---------------------------
        #~ # ping all
        #~ test = self.makeAction( MatchmakingPingAction, mmid="0" )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") != None ) 
        #~ ####sessions = test.reply.get("ModelData")[0][2] # model = [ [op, path, value] ]
        #~ ####self.assert_( len(sessions) == 1 )
        
        ## ---------------------------
        ## cancel BAD session -> сейчас все равно делается CANCEL ALL
        ## test = self.makeAction( MatchmakingCancelAction, mmid="mm_xxx_x" )
        ## test.OnStart()

        ## self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        ## self.assert_( test.reply and test.reply.get("ok") == 0 and test.reply.get("error") ) 
        
        #~ # ---------------------------
        #~ # accept BAD session
        #~ test = self.makeAction( MatchmakingAcceptAction, mmid="mm_xxx_x" )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") == 0 and test.reply.get("error") ) 
        
        #~ # ---------------------------
        #~ # cancel all
        #~ test = self.makeAction( MatchmakingCancelAction, mmid="0" )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") == None ) 
        
        
    #~ ## -------------------------------------------------------------------------------------------------------------------------------------
    #~ ## второй набор: создать сессию, дождаться progress=MM.STATUS_WAITING_ACCEPT, сделать accept, дождаться pvx_accepted
    #~ def testMatchmake2(self):
        #~ self.loginAndLoad()
        #~ self.newDataModel()
        
        #~ ##logLevel( logging.DEBUG )
        #~ log( "---------- testMatchmake2 ----------" )
                
        #~ # ---------------------------
        #~ # add mm session 1
        #~ test = self.makeAction( MatchmakingAddAction, game_type="pvp", fraction="A", src_hero_id=self.HERO_ID )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") ) 
        
        #~ self.mmid = test.reply.get("mmid")
        
        #~ # ---------------------------
        #~ # делаем ping: должен появиться progress==1
        #~ self.I.WS.pingMatchmaking()
        
        #~ # ---------------------------
        #~ # ping session
        #~ test = self.makeAction( MatchmakingPingAction, mmid=self.mmid )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") != None ) 
        #~ sessions = test.reply.get("mm")
        #~ self.assert_( sessions.get("progress") == 1 ) # должен быть словарь конкретной сессии, без вложенных { mmid: {session data}, mmid2: {...}
        
        #~ # ---------------------------
        #~ # BAD accept (рано, сессия еще только создана)
        #~ test = self.makeAction( MatchmakingAcceptAction, mmid=self.mmid )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") == 0 and test.reply.get("error") ) 
        
        #~ # ---------------------------
        #~ # делаем пару "matchmaking степов": должно быть достаточно для progress==ACCEPT
        
        #~ self.I.PVX.stepSessions()
        #~ self.I.PVX.stepSessions()
        #~ self.I.WS.pingMatchmaking()
        
        #~ # ---------------------------
        #~ # ping session
        #~ test = self.makeAction( MatchmakingPingAction, mmid=self.mmid )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") != None ) 
        #~ sessions = test.reply.get("mm")
        #~ self.assert_( sessions.get("progress") == MM.STATUS_WAITING_ACCEPT ) # должен быть словарь конкретной сессии, без вложенных { mmid: {session data}, mmid2: {...}
        
        #~ # ---------------------------
        #~ # accept session
        #~ test = self.makeAction( MatchmakingAcceptAction, mmid=self.mmid )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") != None ) 
        #~ mmid = test.reply.get("mmid")
        #~ session = test.reply.get("mm")
        
        #~ # ---------------------------
        #~ # делаем mm ping: должно быть достаточно для progress==101
        #~ self.I.WS.pingMatchmaking()

        #~ # ---------------------------
        #~ # ping session
        #~ test = self.makeAction( MatchmakingPingAction, mmid=self.mmid )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") != None ) 
        #~ sessions = test.reply.get("mm")
        #~ self.assert_( sessions.get("progress") == 101 ) # должен быть словарь конкретной сессии, без вложенных { mmid: {session data}, mmid2: {...}

        
        
    #----------------------------------------------------------------
    # social aggregator test (требует запущенной заглушки) 
    def onSocialAggregatorCallback(self, reply):
        self.reply = json_loads( reply.body ) #.get("response")
        info( "onSocialAggregatorCallback reply: " + str(self.reply) )

    #~ def testISocialAggregator(self):
        #~ ##logLevel( logging.DEBUG )
        #~ log( "---------- testISocialAggregator ----------" )
        
        #~ SA = iaggregator.ISocialAggregator( SOCAGG_VERSION )
        #~ SA.login( "uid12345", "token12345", "fb", callback=self.onSocialAggregatorCallback)
        #~ self.assert_( self.reply.get("error") == 0 )
        
        #~ SA.getInfo( "12345", "fb", 1, callback=self.onSocialAggregatorCallback )
        #~ self.assert_( self.reply.get("error") == 0 )
        #~ self.assert_( self.reply["get_info"]["fb"] )
        #~ self.assert_( self.reply["get_info"]["fb"].get("email") )
        

def main():
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    
    info( "Loading XDB..." )
    config = MultiConfig()
    _SD = MultiStaticData( options.xdb_path + "/ExportedSocialData.xml", config.getMainConfig() )
    config.fillStaticDataDependendValues(_SD)
    BaseClusterTest.setXDB( _SD )
    
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
