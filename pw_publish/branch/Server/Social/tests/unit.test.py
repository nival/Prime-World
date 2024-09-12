#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, json

os.chdir('..')
sys.path.append( os.path.abspath('.') )
sys.path.append( os.path.abspath('cfg') )
from base.helpers import *

from ext_main.login import LoginAction
from ext_main.auth import AuthAction
from ext_main.nickname import SetNicknameAction
from ext_pw import *

## --------- for sync tests --------------
from test_action import TestAction, TestDictAction
from handlers import resetGlobals, users # между наборами тестов чистим глобальные серверные синглтоны (logins, users, peers)
from ifactory import IfaceFactory 
import imemcache, isql, ihttp

## --------- for Async (real MC/SQL/HTTP) test --------------
import thread, tornado.ioloop # для тестов, требующих асинхронной обработки
import cfg, coord_cfg # настройки MC/SQL (будем надеяться, актуальные) возьмем из локального конфига координатора
from tornado.options import options, define
from iwebserver import IWebServer
from pwserver import PwWorkServer
from geolocation import GeoLocator
from modeldata.ModelData import *
from modeldata.datamanager import PwNewModelManager
import MM # matchmaking const
from logic.keepalive import Keepalive
import ichatserver

from fake_guid import FakeWSGuidGenerator

# ---------------------------------
from binascii import crc32   # zlib version is not cross-platform
import xdbload
from modeldata.MultiStaticData import MultiStaticData
from config.MultiConfig import *
# ---------------------------------

from base_dummy_test import *
import unittest

from ext_main.l_statistic import LauncherStartAction, LauncherEventsAction, LauncherDActions 

##------------------------------------------------------------------------------------------------------------------
##------------------------------------------------------------------------------------------------------------------

class LoopTest_Example( BaseDummyTest ):
    """ Пример конкретного "асинхронного теста" на базе BaseLoopTest. """
    def createGuestInfrastructure(self):
        self.I.GG = FakeWSGuidGenerator()
        self.I.WS = PwWorkServer( I=self.I, test_mode=True )
        self.I.GEO = GeoLocator()
        class ChatHTTP(object):
            def __call__(self, args):
                return {'ok' : 1, 'host' : 'chat0', 'key' : '1234'}
        self.I.CHAT = ichatserver.IFakeChatServer( ChatHTTP() )

        cfg.MUID_TO_DLCS = coord_cfg.COORDINATOR_MUID_TO_DLCS
        cfg.TOURNAMENT_SERVER = coord_cfg.COORDINATOR_TOURNAMENT_SERVER
        cfg.TOURNAMENT_SERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_SERVER_ADDR
        cfg.TOURNAMENT_XSERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_XSERVER_ADDR

        self.I.WS.MM_PING_PERIOD = -1 # чтобы генерация пакетов для matchmaking не делала задержек между пингами статуса сессий юзера
        self.I.WS.MM_MIN_ADD_PERIOD = 0 # чтобы генерация пакетов для matchmaking не делала задержек между пингами статуса сессий юзера
        self.I.WS.MM_MAX_ADD_PERIOD = 0 # чтобы генерация пакетов для matchmaking не делала задержек между пингами статуса сессий юзера
        self.I.WS.resetUserSessions = resetUserSessionsDummy # заменяем настоящий "принудительный mm_cancel" заглушкой
        self.I.WS.nextInt64GUID = self.I.GG.nextInt64GUID # подменяем GUID Generator на фейк, раздающий ID-шки для ModelData с единицы
        self.I.WS.mmSummaryState = 0
        
    # helper: логиним юзера, ждем пока загрузятся persistent данные
    def loginAndLoad(self):
        self.createGuestInfrastructure()
        
        # ---------
        # login 
        test = self.makeAction( LoginAction, guest=1, geo_info='{}' )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") and test.reply["_depth"] ) # первый раз берем из MC или SQL
        #log( "LoginAction reply: %s" % str(test.reply) )
        
        self.assert_( test.reply and test.reply.get("uid") ) 
        
        self.uid = test.reply.get("uid")
        self.acc = users.get( self.uid )
                
        self.assert_( self.uid and self.acc ) 
        
        #logLevel( logging.DEBUG )
        
        # ---------------------------
        # auth / get persistent data
        loaded = None
        t0 = time.time()
        while not loaded:
            test = self.makeAction( AuthAction )
            test.OnStart()

            self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
            self.assert_( test.reply and test.reply.get("loaded") != None ) 
            
            loaded = test.reply.get("loaded")
            if time.time() - t0 > 0.5: # даем полсекунды на загрузку persistent data
                return ### raise "persistent data not loaded" ### в юнит-тест варианте (без кластера) никогда не дождемся непустых persistent data
                
            #log( "auth reply: %s" % test.reply )
            
            time.sleep(0.05)

        # ок, загрузили persistent data
        self.assert_( loaded and self.acc.data ) 


    def newDataModel( self ):
        # ---------------------------
        # create new DataModel (1 hero)
        test = self.makeAction( SetFractionAction, fraction="A", create_heroes=2, force_new=1 )
        test.OnStart()
        ##err( "test.reply: %s" % test.reply )
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") and test.reply.get("init") ) 
        
        self.HERO_ID = 1
                
    
    ## первый набор: создать пару сессий, пингануть, cancel
    def testMatchmake1(self):
        info("TEST WAS IGNORED BY THE TASK https://devjira.nivalnetwork.com/browse/PF-103776")
        '''self.loginAndLoad()
        self.newDataModel()
        
        ##logLevel( logging.DEBUG )
        log( "---------- testMatchmake1 ----------" )
        
        # ---------------------------
        # add mm session 1
        test = self.makeAction( MatchmakingAddAction, game_type="/Maps/Multiplayer/MOBA/Training.ADMPDSCR", fraction="A", src_hero_id=self.HERO_ID )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") ) 
        
        self.mmid = test.reply.get("mmid")
    
        # ---------------------------
        # cancel 1
        test = self.makeAction( MatchmakingCancelAction, mmid=self.mmid )
        test.OnStart()

        self.waitAsyncReply( test, 1.0 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") == self.mmid and test.reply.get("mm") == None ) 
        
        # ---------------------------
        # add mm session 2
        test = self.makeAction( MatchmakingAddAction, game_type="/Maps/Multiplayer/MOBA/Training.ADMPDSCR", fraction="A", src_hero_id=self.HERO_ID )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") ) 
        
        self.mmid2 = test.reply.get("mmid")
        
        # ---------------------------
        # add BAD session 3
        test = self.makeAction( MatchmakingAddAction, game_type="xxx", fraction="X", src_hero_id=0 )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and not test.reply.get("ok") ) 

        # ---------------------------
        # ping session
        test = self.makeAction( MatchmakingPingAction, mmid=self.mmid2 )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") != None ) 
        sessions = test.reply.get("mm")
        self.assert_( sessions.get("progress") != None ) # должен быть словарь конкретной сессии, без вложенных { mmid: {session data}, mmid2: {...}
        
        #~ # ---------------------------
        #~ # ping BAD session -- сейчас просто возвращаем ту, которая есть
        #~ test = self.makeAction( MatchmakingPingAction, mmid="mm_xxx_x" )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") == 0 and test.reply.get("error") ) 
        
        # ---------------------------
        # ping all
        test = self.makeAction( MatchmakingPingAction, mmid="0" )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") != None ) 
        sessions = test.reply.get("mm")
        self.assert_( sessions )
        
        # ---------------------------
        # cancel BAD session
        #~ test = self.makeAction( MatchmakingCancelAction, mmid="mm_xxx_x" )
        #~ test.OnStart()

        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok") == 0 and test.reply.get("error") ) -> сейчас mm_cancel mmid работает как mm_cancel ALL, ошибки не будет
        
        # ---------------------------
        # accept BAD session
        test = self.makeAction( MatchmakingAcceptAction, mmid="mm_xxx_x" )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") == 0 and test.reply.get("error") ) 
        
        # ---------------------------
        # cancel all
        test = self.makeAction( MatchmakingCancelAction, mmid=sessions.get("mmid") )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") == None ) '''
        
        
    #~ ## -------------------------------------------------------------------------------------------------------------------------------------
    #~ ## второй набор: создать сессию, дождаться progress=MM.STATUS_WAITING_ACCEPT, сделать accept, дождаться pvx_accepted
    def testMatchmake2(self):
        info("TEST WAS IGNORED BY THE TASK https://devjira.nivalnetwork.com/browse/PF-103776")
        '''self.loginAndLoad()
        self.newDataModel()
        
        #logLevel( logging.INFO )
        info( "---------- testMatchmake2 ----------" )
                
        # ---------------------------
        # add mm session 1
        test = self.makeAction( MatchmakingAddAction, game_type="/Maps/Multiplayer/MOBA/_.ADMPDSCR", fraction="A", src_hero_id=self.HERO_ID )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") ) 
        
        self.mmid = test.reply.get("mmid")
        
        # ---------------------------
        # делаем ping: должен появиться progress==1
        self.I.WS.pingMatchmaking()
        
        # ---------------------------
        # ping session
        test = self.makeAction( MatchmakingPingAction, mmid=self.mmid )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") != None ) 
        sessions = test.reply.get("mm")
        ##err( "fresh sessions:" + str(sessions) )
        self.assert_( sessions.get("progress") ) # должен быть словарь конкретной сессии, без вложенных { mmid: {session data}, mmid2: {...}
        
        # ---------------------------
        # BAD accept (рано, сессия еще только создана)
        test = self.makeAction( MatchmakingAcceptAction, mmid=self.mmid )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") == 0 and test.reply.get("error") ) 
        
        # ---------------------------
        # делаем пару "matchmaking степов": должно быть достаточно для progress==MM.STATUS_WAITING_ACCEPT
        self.I.PVX.stepSessions()
        self.I.PVX.stepSessions()
        self.I.WS.pingMatchmaking()
        
        # ---------------------------
        # ping session
        test = self.makeAction( MatchmakingPingAction, mmid=self.mmid )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") != None ) 
        
        sessions = test.reply.get("mm")
        info( "sessions[%s]: %s" % (test.reply.get("mmid"), str(sessions)) )
        self.assert_( sessions.get("progress") == MM.STATUS_ACCEPTED_SOCSERVER )'''
        #self.assert_( sessions.get("progress") == MM.STATUS_WAITING_ACCEPT ) # должен быть словарь конкретной сессии, без вложенных { mmid: {session data}, mmid2: {...}
        
        ## ---------------------------
        ## accept session
        #test = self.makeAction( MatchmakingAcceptAction, mmid=self.mmid )
        #test.OnStart()

        #self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #log( "test.reply:" + str(test.reply) )
        
        #self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") != None ) 
        #mmid = test.reply.get("mmid")
        #session = test.reply.get("mm")
        #log( "accepted session:" + str(session) )
        
        ## ---------------------------
        ## делаем mm ping: должно быть достаточно для progress==101
        #self.I.WS.pingMatchmaking()

        ## ---------------------------
        ## ping session
        #test = self.makeAction( MatchmakingPingAction, mmid=self.mmid )
        #test.OnStart()

        #self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #self.assert_( test.reply and test.reply.get("ok") and test.reply.get("mmid") and test.reply.get("mm") != None ) 
        #sessions = test.reply.get("mm")
        #log( "after-accept sessions:" + str(sessions) )
        #self.assert_( sessions.get("progress") == 101 ) # должен быть словарь конкретной сессии, без вложенных { mmid: {session data}, mmid2: {...}
        
        
    ## -------------------------------------------------------------------------------------------------------------------------------------
    ## второй набор: создать сессию, дождаться progress=MM.STATUS_WAITING_ACCEPT, сделать accept, дождаться pvx_accepted
    def testLauncherStatistic(self):
        info("TEST WAS IGNORED BY THE TASK https://devjira.nivalnetwork.com/browse/PF-103776")
        '''self.loginAndLoad()
        self.newDataModel()
        
        from istats import StatsAgent
        class DumpStatsAgent(StatsAgent):
            # транспортная часть отправки сообщения (для тестов можно override именно эту часть; например, на прямой вызов StatisticAgentHandler.processRawData)
            def startSend(self, send_dict):
                info("Stats dict: \n%s" % pretty(send_dict) )
        self.I.STATS = DumpStatsAgent("", self.I)
        
        # logLevel( logging.INFO )
        
        # ---------------------------
        test = self.makeAction( LauncherStartAction, hostid="hostid1", version="version1", auid=1 )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") )
        self.assert_( self.I.STATS.LauncherStart and len(self.I.STATS.LauncherStart) == 1 )
        info("LauncherStartAction -- ok")
        
        # ---------------------------
        test = self.makeAction( LauncherEventsAction, muid="muid4", auid=4, bitmask=44, timestamp=444 )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        self.assert_( self.I.STATS.LauncherEvents and len(self.I.STATS.LauncherEvents) == 1 )
        info("LauncherEventsAction -- ok")
        
        # ---------------------------
        test = self.makeAction( LauncherDActions, cmd="dcancel", hostid="hostid5", muid="muid5", version="version5", auid="auid33", time=1234567890, speed=1.2345 )
        test.OnStart()

        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        self.assert_( self.I.STATS.LauncherDActions and len(self.I.STATS.LauncherDActions) == 1 )
        info("LauncherDActions -- ok")
        
        # ---------------------------
        self.I.WS.tick()
        
        # ---------------------------
        logLevel()'''


    ## --------------------------------------------------------------------------------------------------------------------
    def testFixedAwards(self):
        info("TEST WAS IGNORED BY THE TASK https://devjira.nivalnetwork.com/browse/PF-103776")
        '''self.loginAndLoad()
        self.newDataModel()
        
        info( "---------- testFixedAwards ----------" )
        
        hero = self.acc.model.getHeroByID(1)
        hero_rating, hero_energy = hero.Rating, 0
        info("BEFORE hero.PersistentId=%s, hero.Rating=%s" % (hero.PersistentId, hero.Rating))
        
        session_results = pickRandom( MM.TEST_SESSION_RESULTS )
        self.acc.model.setComment(123)
        self.I.WS.applyGameSessionResults( self.acc, "mmid_TEST_", 1234567890, session_results, "/Maps/Multiplayer/MOBA/Training.ADMPDSCR", hero )
                
        test = self.makeAction( Keepalive )
        test.OnStart()
        
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        
        #~ logLevel( logging.INFO )
        
        model_changes = test.reply.get("ModelData")
        #info( "Keepalive reply: %s, pending changes count: %d" % (test.reply, len(model_changes)) )
        #self.assert_( model_changes ) 
        #self.assert_( isinstance(model_changes, list) )
        #self.assert_( len(model_changes) == 66 )#stupid check...
        
        #self.assertModelChangeFormat( model_changes )
        
        #info("AFTER  hero.PersistentId=%s, hero.Rating=%s" % (hero.PersistentId, hero.Rating))
        
        ## self.assert_( hero.Rating == hero_rating + 33 )
        
        logLevel()'''
        
    ## --------------------------------------------------------------------------------------------------------------------
    def testAdminNicks(self):
        self.loginAndLoad()
        self.newDataModel()
        
        #~ logLevel( logging.INFO )
        
        test = self.makeAction( SetNicknameAction, nickname='Administrator' )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") == 0 ) 
        info( "SetNicknameAction reply: %s" % (test.reply) )
        
        test = self.makeAction( SetNicknameAction, nickname=utf8convert(u'Администратор ПВ') )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") == 0 ) 
        info( "SetNicknameAction reply: %s" % (test.reply) )
        
        logLevel()
        
    ## --------------------------------------------------------------------------------------------------------------------
    
    #~ def onPersistentSubloginCallback(self, response):
        #~ self.persistent_ok = 1
        #~ self.response = response
        
    #~ def testSublogin(self):
        #~ self.createGuestInfrastructure()
        #~ #logLevel( logging.INFO )
        
        #~ self.persistent_ok = 0
        #~ self.I.WS.serverSubLogin( "fb#100000234693443", sublogin_callback=self.onPersistentSubloginCallback )
        #~ self.assert_( self.persistent_ok ) 
        
        #~ info("testSublogin response: %s" % getattr(self, "response", None))
                
        #~ self.persistent_ok = 0
        #~ self.I.WS.serverSubLogin( "fb#100000234693443", persistent_callback=self.onPersistentSubloginCallback )
        #~ self.assert_( self.persistent_ok ) 
        
        #~ info("testSublogin (persistent) acc: %s" % getattr(self, "response", None))
        
        #~ logLevel()
        
        
## --------------------------------------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------------------------------------
       
        
def main():
    DEFAULT_LOG_LEVEL = logging.ERROR
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    
    ##err( "3 in (3,32): %s" % (3 in xrange(3,32)) )
    ##err( "32 in (3,32): %s" % (32 in xrange(3,32)) )
    
    info( "Loading XDB..." )
    config = MultiConfig()
    _SD = MultiStaticData( options.xdb_path + "/ExportedSocialData.xml", config.getMainConfig() )
    config.fillStaticDataDependendValues(_SD)
    BaseDummyTest.setXDB( _SD )
    
    info( "Starting tests..." )
    
    #~ suite = unittest.TestLoader().loadTestsFromTestCase(UnitTest_GiveHandler)
    #~ unittest.TextTestRunner(verbosity=2).run(suite)

    ITERATIONS = 1
    for i in range(ITERATIONS):
        try:
            unittest.main()
        except SystemExit:
            if str( exc() ) == "True":
                sys.exit(1)
        except:
            catch()
            
        #time.sleep(0.01)

    info( "-- Finish tests (x %d)." % ITERATIONS )
    

if __name__ == "__main__":
    main()
