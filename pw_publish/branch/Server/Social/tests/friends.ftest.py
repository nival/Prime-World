# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, json

os.chdir('..')
sys.path.append( os.path.abspath('.') )

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
from pwhandler import PwJsonHandler
from modeldata.ModelData import ModelData
from modeldata.datamanager import PwNewModelManager
import MM # matchmaking const
from MM import FriendStatus

from fake_guid import FakeWSGuidGenerator
from person_server import *

# ---------------------------------
from binascii import crc32   # zlib version is not cross-platform
import xdbload
from modeldata.MultiStaticData import MultiStaticData
from config.MultiConfig import *
# ---------------------------------
import unittest
import iaggregator

from base_dummy_test import *
#from base_cluster_test import *

from logic.keepalive import Keepalive
from ext_main.login import LoginAction, LogoutAction

from ipeerserver import *
from ipersonserver import *
from iaggregator import ISocialAggregator

## DEFAULT_LOG_LEVEL = logging.DEBUG

from party_test_base import PartyTestBase

class FriendsTest( PartyTestBase ):
    """ Воспользуемся тем фактом, что аггрегатор преспокойно исполняет команды get_friends и т.п. по голым auid-ам, без всякой авторизации.
        Соотв. заведем guest-юзеров с auid-ами известных нам юзеров (DAN, OLGA, MARY_LEE) и посмотрим, что приходит от PS и аггрегатора.
    """
        
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def test_Friends(self):
        AGG = IfaceFactory.makeSocAggInterface( options.soc_agg, coord_cfg.COORDINATOR_SOCIAL_AGGREGATOR_ADDRESS, SOCAGG_VERSION, HTTP=self.I.HTTP )
        
        DAN = 97
        OLGA = 78
        OTHER = 106 # его не создаем, на нем проверим FriendsData для offline-юзеров
        
        ## logLevel( logging.DEBUG )
        
        self.createGuestUsers( 1, AGG=AGG, start_auid=DAN, roll_fraction=1)
        self.createGuestUsersCount( 1, start_auid=OLGA, roll_fraction=1)
        
        # пропускаем ответы
        for index in [DAN,OLGA]:
            self.skipPendingEvents(index)
        
        # теперь VADIM выходит онлайн
        self.createGuestUsersCount( 1, roll_fraction=1, start_auid=OTHER )
        
        for index in [OLGA]:
            test, event = self.checkPendingFriendEvent(index, "change", "FriendsData")
        
        #test, event = self.checkPendingFriendEvent(VADIM, "change", "FriendsData")
        
        
        
    def test_FriendStatus(self):
        AGG = IfaceFactory.makeSocAggInterface( "http", coord_cfg.COORDINATOR_SOCIAL_AGGREGATOR_ADDRESS, SOCAGG_VERSION, HTTP=self.I.HTTP )
        
        DAN = 97
        OLGA = 78
        MARY_LEE = 106 # Mary Lee (не создаем, на нем проверим FriendsData для offline-юзеров)
        
        ## logLevel( logging.DEBUG )
        
        ## ------------------------------------------------------------------------------
        ## приходит DAN
        test = self.createGuestUsers( 1, AGG=AGG, start_auid=DAN, roll_fraction=1 )
        
        keeper = test.reply['FriendsData'][0]['init_friends'][0][2]['FriendsData']['FriendsKeeper']['Keeper']
        assert keeper
        warn("createGuestUsers [auid %s] test reply keeper: %s" % (DAN, json_pretty(keeper)) )
        assert keeper[DAN]['Friend']['Status'] == FriendStatus.INCASTLE # self: уже в замке
        assert keeper[OLGA]['Friend']['Status'] == FriendStatus.NONE # friend: еще нету онлайн
        
        ## ------------------------------------------------------------------------------
        ## приходит OLGA
        test = self.createGuestUsersCount( 1, start_auid=OLGA, roll_fraction=1 )
        
        keeper = test.reply['FriendsData'][0]['init_friends'][0][2]['FriendsData']['FriendsKeeper']['Keeper']
        assert keeper
        warn("createGuestUsers [auid %s] test reply keeper: %s" % (OLGA, json_pretty(keeper)) )
        assert keeper[OLGA]['Friend']['Status'] == FriendStatus.INCASTLE # self: уже в замке
        assert keeper[DAN]['Friend']['Status'] == FriendStatus.INCASTLE # friend: уже в замке
        
        test, event = self.checkPendingFriendEvent(DAN, "change", "FriendsData")
        warn("[auid %s], friend of [auid %s], coming ONLINE event: %s" % (OLGA, DAN, json_pretty(event)) )
        assert event['FriendsData'][0]['auto'][0][0] == "FriendsKeeper/%s" % OLGA 
        assert event['FriendsData'][0]['auto'][0][2]['Status'] == FriendStatus.INCASTLE # уже в замке

        ## ------------------------------------------------------------------------------
        ## OLGA идет в матчмейкинг
        self.checkSoloMM_START(OLGA)

        test, event = self.checkPendingFriendEvent(DAN, "status_change", "FriendsData")
        warn("[auid %s], friend of [auid %s], gone into MM TRAINING event: %s" % (OLGA, DAN, json_pretty(event)) )
        assert event['FriendsData'][0]['auto'][0][0] == "FriendsKeeper/%s" % OLGA 
        assert event['FriendsData'][0]['auto'][0][2]['Status'] == FriendStatus.INTRAINING # в тренировке
        
        ## ------------------------------------------------------------------------------
        ## приходит MARY_LEE
        test = self.createGuestUsersCount( 1, start_auid=MARY_LEE, roll_fraction=1 )
        
        keeper = test.reply['FriendsData'][0]['init_friends'][0][2]['FriendsData']['FriendsKeeper']['Keeper']
        assert keeper
        warn("createGuestUsers [auid %s] test reply keeper: %s" % (MARY_LEE, json_pretty(keeper)) )
        assert keeper[MARY_LEE]['Friend']['Status'] == FriendStatus.INCASTLE # self: уже в замке
        assert keeper[OLGA]['Friend']['Status'] == FriendStatus.INTRAINING # friend: в тренировке
        
        ## ------------------------------------------------------------------------------
        ## OLGA уходит в оффлайн 
        test = self.sendLogout( OLGA )
        t0 = time.time()
        while users.get( OLGA ): 
            self.I.WS.tick()
            # подождем, пока уйдет оффлайн
            time.sleep(0.1)
            self.assert_( time.time() - t0 < 1.5 ) # не ждем больше 1.5 секунд
            
        test, event = self.checkPendingFriendEvent(DAN, "change", "FriendsData")
        warn("[auid %s], friend of [auid %s], coming OFFLINE event: %s" % (OLGA, DAN, json_pretty(event)) )
        assert event['FriendsData'][0]['auto'][0][0] == "FriendsKeeper/%s" % OLGA 
        assert event['FriendsData'][0]['auto'][0][2]['Status'] == FriendStatus.NOTINGAME # friend: вышел из игры
        
        
##----------------------------------------------------------------
##----------------------------------------------------------------

def main():
    ## print "DEFAULT_LOG_LEVEL: %s" % DEFAULT_LOG_LEVEL
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    
    info( "Loading XDB..." )
    config = MultiConfig()
    _SD = MultiStaticData( options.xdb_path + "/ExportedSocialData.xml", config.getMainConfig() )
    config.fillStaticDataDependendValues(_SD)
    BaseDummyTest.setXDB( _SD )
    
    info( "-- START tests.." )
    
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
