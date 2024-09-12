# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network
import sys, os, time, logging, json

os.chdir('..')
sys.path.append( os.path.abspath('.') )
sys.path.append( os.path.abspath('cfg') )

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

from fake_guid import FakeWSGuidGenerator
#from person_server import *

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

from party_test_base import PartyTestBase

from logic.all import Mm_ready, Set_guard, Set_wins

class GuardsTest( PartyTestBase ):
    """ Этот тест будет создавать локальные копии WS и PS, и завязывать взаимодействие их SubAction-ов напрямую друг на друга 
        (через подмену их интерфейсов I.PS и I.WSX фейками) """

    def testGuardsStart(self):
        logLevel( )

        self.createGuestUsers( 5 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        SLAVE3 = 4
        SLAVE4 = 5
        
        ALL = [1,2,3,4,5]
        
        # пусть наш карманный PartyServer сразу удаляет тамбур-контексты (при первом же вызове tick)
        self.iDictPTS.WS.TAMBUR_DELETE_PERIOD = 0

        # logLevel( logging.INFO ) # ############################
        
        info("--- testGuardsStart ---")

        self.buyHero(MASTER, "rockman")
        
        for index in ALL:
            self.accs[index].model.LordInfo.GuardInfo.OnlyGuard = True # требуем гвардейский режим (для mock matchmaker должно прокатить)
            hero_id_index = self.accs[index].model.HeroesKeeper.keys()[0]
            self.accs[index].model.LordInfo.Ratings.LastRecalcPlayerRatingTime = int(time.time()) - 60 * 60 * 24 * 5
            test = self.makeGuestAction( MatchmakingAddAction, index, game_type="/Maps/Multiplayer/MOBA/_.ADMPDSCR", with_bots = 0, fraction="A", src_hero_id=hero_id_index ) 
            test.OnStart()
            self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
            info("MatchmakingAddAction reply: %s" % test.reply)
            self.assert_( test.reply and test.reply.get("ok") ) 

        #-----
        # отсылаем mm_add и делаем "matchmaking степ": должно быть достаточно для формирования mock "гвардейского тамбура"
        self.I.WS.pingMatchmaking()
        self.I.PVX.stepSessions()
        self.I.WS.pingMatchmaking()
        #-----
        
        # logLevel( logging.INFO ) # ##########################
        
        test = self.makeGuestAction( MatchmakingPingAction, MASTER, mmid=0 ) 
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("MatchmakingPingAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") ) 
        
        MASTER_MMID = test.reply.get("mmid", "")
        
        # для первого создается новый тамбур:
        test, event = self.checkNextPendingFriendEvent(test, MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingFriendEvent(test, MASTER, "change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingFriendEvent(test, MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "join_init_tambur", "TamburData", join_auid=MASTER)
        
        ## надо захачить лимиты по рейтингу (иначе устанавливалка диапазона рейтингов будет ждать, пока не заполнится "тамбур противника")
        #tambur_id = toint( event.get("tambur_id") )
        #tambur = self.iDictPTS.WS.tamburs.get( tambur_id )
        #tambur.PartyData.RatingLimits.MaxRating = 3000
        #tambur.PartyData.RatingLimits.MinRating = 0
        
        # и еще четверо присоединяются:
        self.checkNextPendingEvent(test, MASTER, "join", "TamburData")
        self.checkNextPendingEvent(test, MASTER, "join", "TamburData")
        self.checkNextPendingEvent(test, MASTER, "join", "TamburData")
        self.checkNextPendingEvent(test, MASTER, "join", "TamburData")
        
        ## logLevel( logging.INFO ) 
        
        test, event = self.checkPendingFriendsEvent(SLAVE1, "status_change", "FriendsData", friend_auid=SLAVE1)
        test, event = self.checkNextPendingFriendEvent(test, SLAVE1, "status_change", "FriendsData", friend_auid=SLAVE1)
        test, event = self.checkNextPendingEvent(test, SLAVE1, "join_init_tambur", "TamburData", join_auid=SLAVE1)
        
        # еще один контрольный пинг: ничего не должно поменяться на person_server
        info("- control ping -")
        self.I.WS.pingMatchmaking()
        
        test = self.sendGuestAction( MatchmakingPingAction, MASTER, mmid=0 ) 
        
        # --- присылаем party_hero (ПОВТОРЯЮЩЕГОСЯ -- FAIL)
        hero_id = self.accs[MASTER].model.HeroesKeeper.keys()[0]
        hero = self.accs[MASTER].model.HeroesKeeper.get(hero_id)
        hero_crc = hero.PersistentId
        
        self.accs[MASTER].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли party_hero
        # и теми же грязными руками нахачиваем гвардейский статус:
        self.accs[MASTER].model.LordInfo.GuardInfo.NumberOfWins = 1000.0
        hero.Master = True
        info("== old hero force: %5.3f" % hero.TalentSets[hero.ActiveTalentSet].Force)
        hero.TalentSets[hero.ActiveTalentSet].Force = 160.0

        # logLevel( logging.INFO ) #
        
        self.sendHero( MASTER, 0, hero_id=hero_id, hero_crc=hero_crc )
        
        # Тут теперь не ошибка, а в тихую меняем героя обратно!
        #test, event = self.checkPendingEvent(MASTER, "error", message="too many similar heroes chosen")
        
        # --- присылаем party_hero (НЕПОВТОРЯЮЩЕГОСЯ -- OK)
        hero_id = self.accs[MASTER].model.HeroesKeeper.keys()[1]
        hero = self.accs[MASTER].model.HeroesKeeper.get(hero_id)
        hero_crc = hero.PersistentId
        
        self.accs[MASTER].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли party_hero
        # и теми же грязными руками нахачиваем гвардейский статус:
        self.accs[MASTER].model.LordInfo.GuardInfo.NumberOfWins = 1000.0
        hero.Master = True
        info("== old hero force: %5.3f" % hero.TalentSets[hero.ActiveTalentSet].Force)
        hero.TalentSets[hero.ActiveTalentSet].Force = 160.0

        # logLevel( logging.INFO ) #
        
        self.sendHero( MASTER, 0, hero_id=hero_id, hero_crc=hero_crc )
        
        test, event = self.checkPendingEvent(MASTER, "hero", "TamburData")
        test, event = self.checkPendingEvent(SLAVE1, "hero", "TamburData")
        
        # --- теперь присылаем mm_ready
        self.accs[MASTER].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли mm_ready
        test = self.makeGuestAction( Mm_ready, MASTER, mmid=MASTER_MMID ) 
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("Mm_ready action reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") ) 
        
        self.I.WS.pingMatchmaking()
        
        test, event = self.checkPendingEvent(MASTER, "tambur_ready", "TamburData", ready_auid=MASTER)
        test, event = self.checkPendingEvent(SLAVE1, "tambur_ready", "TamburData", ready_auid=MASTER)
                
        # теперь делаем cancel (по идее, тамбур должен развалиться)
        test = self.makeGuestAction( MatchmakingCancelAction, MASTER, mmid=MASTER_MMID )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("MatchmakingCancelAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") ) 

        # проверяем что развалилось..
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "deleted", "TamburData", "tambur_id")
        
        test, event = self.checkPendingEvent(SLAVE1, "deleted", "TamburData", "tambur_id")
        
        # тикнем карманный PersonServer (чтобы удалил тамбур-контекст)
        self.iDictPTS.WS.tick()
        
        # --------------
        info("- after-cancel ping -")
        self.I.WS.pingMatchmaking()
        
        test = self.makeGuestAction( MatchmakingPingAction, MASTER, mmid=0 ) 
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("MatchmakingPingAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok")==0 ) 
        
        # --------------
        logLevel( )

    # -----------------------------------------------------------------
    # гвардейская игра из 2 партий по 2 игрока + 1 игрок соло
    def xxx__testGuardParties(self):
        logLevel( )

        self.createGuestUsers( 5 )

        MASTER = 1
        SLAVE = 2
        MASTER2 = 3
        SLAVE2 = 4
        SOLO = 5
        
        SLAVE1 = SLAVE
        
        ALL = [1,2,3,4,5]
        
        PARTY_LIST = [MASTER,SLAVE,MASTER2,SLAVE2]
        MASTER_LIST = [MASTER,MASTER2]
        SLAVE_LIST = [SLAVE,SLAVE2]
        SOLO_LIST = [SOLO]
        
        # пусть наш карманный PartyServer сразу удаляет тамбур-контексты (при первом же вызове tick)
        self.iDictPTS.WS.TAMBUR_DELETE_PERIOD = 0
        
        # шлем инвайты
        self.sendInvite(MASTER, SLAVE)
        self.sendInvite(MASTER2, SLAVE2)
        self.sendAccept(SLAVE, MASTER)
        self.sendAccept(SLAVE2, MASTER2)
        
        self.buyHero(MASTER, "rockman")
        
        # пропускаем все ответы
        self.skipPendingEvents(MASTER)
        self.skipPendingEvents(SLAVE)
        self.skipPendingEvents(MASTER2)
        self.skipPendingEvents(SLAVE2)
        
        # у всех должен появиться party_id != 0
        PARTY_ID = self.accs[MASTER].party_id
        self.assert_( PARTY_ID )
        
        PARTY_ID2 = self.accs[MASTER2].party_id
        self.assert_( PARTY_ID2 )
        
        self.assertEqual( PARTY_ID, self.accs[SLAVE].party_id )
        self.assertEqual( PARTY_ID2, self.accs[SLAVE2].party_id )
        
        info("--- testGuardParties ---")
        
        # запоминаем гвард. героя MASTER[0]
        md = self.accs[MASTER].model
        hero_id = md.HeroesKeeper.keys()[0]
        MASTER_HERO_ID = hero_id
        
        for index in SLAVE_LIST:
            party_id = self.accs[index].party_id
            md = self.accs[index].model
            md.LordInfo.GuardInfo.OnlyGuard = True # требуем гвардейский режим (для mock matchmaker должно прокатить)
            hero_id = md.HeroesKeeper.keys()[1]
            hero_crc = md.HeroesKeeper.get(hero_id).PersistentId
            # нахачиваем гвард.статус:
            test = self.sendGuestAction( Set_wins, index, wins=20 ) 
            test = self.sendGuestAction( Set_guard, index, hero_id=hero_id, guard=True ) 
            # выбираем героя:
            self.sendHero( index, party_id, hero_id=hero_id, hero_crc=hero_crc )
            self.skipPendingEvents( index ) # пропускаем все ответы
            
        for index in MASTER_LIST:
            party_id = self.accs[index].party_id
            md = self.accs[index].model
            md.LordInfo.GuardInfo.OnlyGuard = True # требуем гвардейский режим (для mock matchmaker должно прокатить)
            hero_id = md.HeroesKeeper.keys()[0]
            hero_crc = md.HeroesKeeper.get(hero_id).PersistentId
            # нахачиваем гвард.статус:
            test = self.sendGuestAction( Set_wins, index, wins=20 ) 
            test = self.sendGuestAction( Set_guard, index, hero_id=hero_id, guard=True ) 
            # выбираем героя:
            self.sendHero( index, party_id, hero_id=hero_id, hero_crc=hero_crc )
            self.sendGo( index, party_id ) # GO!
            self.skipPendingEvents( index ) # пропускаем все ответы
            
        for index in SOLO_LIST:
            self.accs[index].model.LordInfo.GuardInfo.OnlyGuard = True # требуем гвардейский режим (для mock matchmaker должно прокатить)
            md = self.accs[index].model
            md.LordInfo.OnlyGuard = True # требуем гвардейский режим (для mock matchmaker должно прокатить)
            hero_id = md.HeroesKeeper.keys()[0]
            hero_crc = md.HeroesKeeper.get(hero_id).PersistentId
            # нахачиваем гвард.статус:
            test = self.sendGuestAction( Set_wins, index, wins=20 ) 
            test = self.sendGuestAction( Set_guard, index, hero_id=hero_id, guard=True ) 
            # стартуем соло мм:
            test = self.makeGuestAction( MatchmakingAddAction, index, game_type="/Maps/Multiplayer/MOBA/_.ADMPDSCR", with_bots = 0, fraction="A", src_hero_id=hero_id ) 
            test.OnStart()
            self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
            info("MatchmakingAddAction reply: %s" % test.reply)
            self.assert_( test.reply and test.reply.get("ok") ) 
            self.skipPendingEvents( index ) # пропускаем все ответы

        #-----
        # отсылаем mm_add и делаем "matchmaking степ": должно быть достаточно для формирования mock "гвардейского тамбура"
        self.I.WS.pingMatchmaking()
        self.I.PVX.stepSessions()

        for index in ALL:
            self.skipPendingEvents( index ) # пропускаем все ответы (про партии и старт матчмейкинга)

        self.I.WS.pingMatchmaking()
        #-----
        
        test = self.makeGuestAction( MatchmakingPingAction, MASTER, mmid=0 ) 
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("MatchmakingPingAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") ) 
        MASTER_MMID = test.reply.get("mmid", "")
        
        test = self.makeGuestAction( MatchmakingPingAction, SLAVE, mmid=0 ) 
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("MatchmakingPingAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") ) 
        SLAVE_MMID = test.reply.get("mmid", "")
        
        test = self.makeGuestAction( MatchmakingPingAction, SOLO, mmid=0 ) 
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("MatchmakingPingAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") ) 
        SOLO_MMID = test.reply.get("mmid", "")
        
        logLevel( logging.INFO ) 
        
        self.I.WS.pingMatchmaking()
        self.I.PVX.stepSessions()
        self.I.WS.pingMatchmaking()
        #-----

        # logLevel( logging.INFO ) # ##########################

        test = self.makeGuestAction( MatchmakingPingAction, MASTER, mmid=0 )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("MatchmakingPingAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") )

        MASTER_MMID = test.reply.get("mmid", "")

        # для первого создается новый тамбур:
        test, event = self.checkNextPendingFriendEvent(test, MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingFriendEvent(test, MASTER, "change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingFriendEvent(test, MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "join_init_tambur", "TamburData", join_auid=MASTER)
        
        # и еще четверо присоединяются:
        self.checkNextPendingEvent(test, MASTER, "join", "TamburData")
        self.checkNextPendingEvent(test, MASTER, "join", "TamburData")
        self.checkNextPendingEvent(test, MASTER, "join", "TamburData")
        self.checkNextPendingEvent(test, MASTER, "join", "TamburData")
        
        test, event = self.checkPendingEvent(SLAVE1, "join_init_tambur", "TamburData", join_auid=SLAVE1)
        
        # еще один контрольный пинг: ничего не должно поменяться на person_server
        info("- control ping -")
        self.I.WS.pingMatchmaking()
        
        test = self.makeGuestAction( MatchmakingPingAction, MASTER, mmid=0 ) 
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("MatchmakingPingAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") ) 
        
        # --- присылаем party_hero (ПОВТОРЯЮЩЕГОСЯ -- FAIL)
        hero_id = sorted(self.accs[MASTER].model.HeroesKeeper.keys())[0]
        hero = self.accs[MASTER].model.HeroesKeeper.get(hero_id)
        hero_crc = hero.PersistentId
        info("repeat hero_id=%s, crc=%s" % (hero_id, hero_crc))
        
        self.accs[MASTER].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли party_hero
        
        self.sendHero( MASTER, 0, hero_id=hero_id, hero_crc=hero_crc )
        
        # Тут теперь не ошибка, а в тихую меняем героя обратно!
        #test, event = self.checkPendingEvent(MASTER, "error", message="too many similar heroes chosen")
        #self.assert_( self.accs[MASTER].data.mm.hero_id == MASTER_HERO_ID )
        
        # --- присылаем party_hero (НЕПОВТОРЯЮЩЕГОСЯ -- OK)
        hero_id = sorted(self.accs[MASTER].model.HeroesKeeper.keys())[2]
        hero = self.accs[MASTER].model.HeroesKeeper.get(hero_id)
        hero_crc = hero.PersistentId
        info("non-repeat hero_id=%s, crc=%s" % (hero_id, hero_crc))
        
        MASTER_HERO_ID2 = hero_id
        
        self.accs[MASTER].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли party_hero
        # и теми же грязными руками нахачиваем гвардейский статус:
        test = self.sendGuestAction( Set_wins, MASTER, wins=100 ) 
        test = self.sendGuestAction( Set_guard, MASTER, hero_id=hero_id, guard=True )

        self.skipPendingEvents( SLAVE2 ) # пропускаем все ответы (про партии и старт матчмейкинга)
        
        #logLevel( logging.INFO ) # #################
        info("non-repeat hero_id=%s, crc=%s" % (hero_id, hero_crc))
        
        self.sendHero( MASTER, 0, hero_id=hero_id, hero_crc=hero_crc )
        
        test, event = self.checkPendingEvent(MASTER, "hero", "TamburData")
        self.checkNextPendingEvent(test, MASTER, "hero", "PartyData")

        test, event = self.checkPendingEvent(SLAVE1, "hero", "TamburData")
        self.checkNextPendingEvent(test, SLAVE1, "hero", "PartyData")
        
        test, event = self.checkPendingEvent(SLAVE2, "hero", "TamburData")
        
        self.assert_( self.accs[MASTER].data.mm.hero_id == MASTER_HERO_ID2 )
        self.assert_( self.accs[MASTER].data.mm.hero_crc == hero_crc )
        
        ############# DEBUG ################
        # восстановим "стартового героя" для мастера
        master_acc = self.accs[MASTER]
        self.I.WS.restoreSrcHero( master_acc.data.mm, master_acc )
        test, event = self.checkPendingEvent(MASTER, "hero" )
        self.skipPendingEvents(SLAVE1)
        self.skipPendingEvents(SLAVE2)
        logLevel() 
        #############
                
        # --- теперь присылаем mm_ready
        self.accs[MASTER].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли mm_ready
        test = self.makeGuestAction( Mm_ready, MASTER, mmid=MASTER_MMID ) 
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("Mm_ready action reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") ) 
        
        self.I.WS.pingMatchmaking()
        
        test, event = self.checkPendingEvent(MASTER, "tambur_ready", "TamburData", ready_auid=MASTER)
        test, event = self.checkPendingEvent(SLAVE1, "tambur_ready", "TamburData", ready_auid=MASTER)
        test, event = self.checkPendingEvent(SLAVE2, "tambur_ready", "TamburData", ready_auid=MASTER)
                       
        # теперь делаем cancel (по идее, тамбур должен развалиться)
        CANCEL_INDEX = SLAVE
        ## test = self.makeGuestAction( MatchmakingTamburLeaveAction, MASTER, mmid=MASTER_MMID )
        test = self.makeGuestAction( MatchmakingTamburLeaveAction, SLAVE, mmid=SLAVE_MMID )
        ## test = self.makeGuestAction( MatchmakingTamburLeaveAction, SOLO, mmid=SOLO_MMID ) -- НЕТ. в этом случае партии вывалятся только после развала сессии через lobby/gateway
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("MatchmakingTamburLeaveAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") ) 

        # проверяем что развалилось..
        test, event = self.checkPendingEvent(MASTER, "progress", "party_id") # партия вываливается из ММ
        self.checkNextPendingEvent(test, MASTER, "deleted", "TamburData", "tambur_id")
        
        test, event = self.checkPendingEvent(SLAVE, "progress", "party_id") # партия вываливается из ММ
        self.checkNextPendingEvent(test, SLAVE, "deleted", "TamburData", "tambur_id")
        
        test, event = self.checkPendingEvent(SLAVE2, "deleted", "TamburData", "tambur_id")
        
        # тикнем карманный PersonServer (чтобы удалил тамбур-контекст)
        self.iDictPTS.WS.tick()
        
        # --------------
        info("- after-cancel ping -")
        self.I.WS.pingMatchmaking()
        
        test = self.makeGuestAction( MatchmakingPingAction, CANCEL_INDEX, mmid=0 ) 
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("MatchmakingPingAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok")==0 ) 
        
        # --------------
        logLevel( )

    def test_ForbidentHeroes(self):
        logLevel( )

        self.createGuestUsers( 5 )

        MASTER = 1
        SLAVE1 = 2
        SLAVE2 = 3
        SLAVE3 = 4
        SLAVE4 = 5

        self.accs[MASTER].db.fraction = 'A'
        self.accs[SLAVE1].db.fraction = 'A'
        self.accs[SLAVE2].db.fraction = 'B'
        self.accs[SLAVE3].db.fraction = 'A'
        self.accs[SLAVE4].db.fraction = 'A'


        ALL = [1,2,3,4,5]

        # пусть наш карманный PartyServer сразу удаляет тамбур-контексты (при первом же вызове tick)
        self.iDictPTS.WS.TAMBUR_DELETE_PERIOD = 0
        self.iDictPTS.Config.getMainConfig().FORBIDDEN_FOR_PARTY_HERO_PAIRS = []
        self.iDictPTS.Config.getMainConfig().blockHeroesPairForParty("crusader_A","crusader_B")

        # logLevel( logging.INFO ) # ############################

        info("--- testGuardsStart ---")

        self.buyHero(MASTER, "rockman")
        self.buyHero(SLAVE1, "crusader_A")
        self.buyHero(SLAVE2, "crusader_B")

        self.accs[MASTER].db.fraction = 'A'
        self.accs[SLAVE1].db.fraction = 'A'
        self.accs[SLAVE2].db.fraction = 'A'
        self.accs[SLAVE3].db.fraction = 'A'
        self.accs[SLAVE4].db.fraction = 'A'

        skeys2 = sorted(self.accs[SLAVE1].model.HeroesKeeper.keys())
        hero_id_3 = skeys2[5]
        hero = self.accs[SLAVE1].model.HeroesKeeper.get(hero_id_3)
        hero.Rating = 1600
        hero_crc_3 = hero.PersistentId

        skeys3 = sorted(self.accs[SLAVE2].model.HeroesKeeper.keys())
        hero_id_4 = skeys3[5]
        hero = self.accs[SLAVE2].model.HeroesKeeper.get(hero_id_4)
        hero.Rating = 1600
        hero_crc_4 = hero.PersistentId

        for index in ALL:
            self.accs[index].model.LordInfo.GuardInfo.OnlyGuard = True # требуем гвардейский режим (для mock matchmaker должно прокатить)
            hero_id_index = self.accs[index].model.HeroesKeeper.keys()[0]
            test = self.makeGuestAction( MatchmakingAddAction, index, game_type="/Maps/Multiplayer/MOBA/_.ADMPDSCR", with_bots = 0, fraction="A", src_hero_id=hero_id_index )
            test.OnStart()
            self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
            info("MatchmakingAddAction reply: %s" % test.reply)
            self.assert_( test.reply and test.reply.get("ok") )

            if index == SLAVE1:
                SLAVE1_MMID = test.reply.get("mmid", "")
            elif index == SLAVE2:
                SLAVE2_MMID = test.reply.get("mmid", "")
                hero = self.accs[SLAVE2].model.HeroesKeeper.get(hero_id_index)
                old_hero_crc_4 = hero.PersistentId
        #-----
        # отсылаем mm_add и делаем "matchmaking степ": должно быть достаточно для формирования mock "гвардейского тамбура"
        self.I.WS.pingMatchmaking()
        self.I.PVX.stepSessions()
        self.I.WS.pingMatchmaking()

        #-----

        ##### logLevel( logging.INFO ) # ##########################

        test = self.makeGuestAction( MatchmakingPingAction, MASTER, mmid=0 )
        test.OnStart()
        self.waitAsyncReply( test, 1 ) # ждем асинк-ответа
        info("MatchmakingPingAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") )
        MASTER_MMID = test.reply.get("mmid", "")


        # для первого создается новый тамбур:
        test, event = self.checkNextPendingFriendEvent(test, MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingFriendEvent(test, MASTER, "change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingFriendEvent(test, MASTER, "status_change", "FriendsData", friend_auid=MASTER)

        test, event = self.checkNextPendingEvent(test, MASTER, "join_init_tambur", "TamburData", join_auid=MASTER)

        ## надо захачить лимиты по рейтингу (иначе устанавливалка диапазона рейтингов будет ждать, пока не заполнится "тамбур противника")
        tambur_id = toint( event.get("tambur_id") )
        tambur = self.iDictPTS.WS.tamburs.get( tambur_id )
        tambur.PartyData.RatingLimits.MaxRating = 3000
        tambur.PartyData.RatingLimits.MinRating = 0

        # и еще четверо присоединяются:
        self.checkNextPendingEvent(test, MASTER, "join", "TamburData")
        self.checkNextPendingEvent(test, MASTER, "join", "TamburData")
        self.checkNextPendingEvent(test, MASTER, "join", "TamburData")
        self.checkNextPendingEvent(test, MASTER, "join", "TamburData")

        ## logLevel( logging.INFO )

        test, event = self.checkPendingFriendsEvent(SLAVE1, "status_change", "FriendsData", friend_auid=SLAVE1)
        test, event = self.checkNextPendingFriendEvent(test, SLAVE1, "change", "FriendsData", friend_auid=SLAVE1)
        test, event = self.checkNextPendingFriendEvent(test, SLAVE1, "status_change", "FriendsData", friend_auid=SLAVE1)
        test, event = self.checkNextPendingEvent(test, SLAVE1, "join_init_tambur", "TamburData", join_auid=SLAVE1)
        self.checkNextPendingEvent(test, SLAVE1, "join", "TamburData")
        self.checkNextPendingEvent(test, SLAVE1, "join", "TamburData")

        # еще один контрольный пинг: ничего не должно поменяться на person_server
        info("- control ping -")
        self.I.WS.pingMatchmaking()

        test = self.sendGuestAction( MatchmakingPingAction, MASTER, mmid=0 )

        # --- присылаем party_hero (ПОВТОРЯЮЩЕГОСЯ -- FAIL)
        hero_id = self.accs[MASTER].model.HeroesKeeper.keys()[0]
        hero = self.accs[MASTER].model.HeroesKeeper.get(hero_id)
        hero_crc = hero.PersistentId

        self.accs[MASTER].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли party_hero
        # и теми же грязными руками нахачиваем гвардейский статус:
        self.accs[MASTER].model.LordInfo.GuardInfo.NumberOfWins = 1000.0
        hero.Master = True
        info("== old hero force: %5.3f" % hero.TalentSets[hero.ActiveTalentSet].Force)
        hero.TalentSets[hero.ActiveTalentSet].Force = 160.0

        # logLevel( logging.INFO ) #

        self.sendHero( MASTER, 0, hero_id=hero_id, hero_crc=hero_crc )

        # Тут теперь не ошибка, а в тихую меняем героя обратно!
        #test, event = self.checkPendingEvent(MASTER, "error", message="too many similar heroes chosen")

        # --- присылаем party_hero (НЕПОВТОРЯЮЩЕГОСЯ -- OK)
        hero_id = self.accs[MASTER].model.HeroesKeeper.keys()[1]
        hero = self.accs[MASTER].model.HeroesKeeper.get(hero_id)
        hero_crc = hero.PersistentId

        self.accs[MASTER].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли party_hero
        # и теми же грязными руками нахачиваем гвардейский статус:
        self.accs[MASTER].model.LordInfo.GuardInfo.NumberOfWins = 1000.0
        hero.Master = True
        info("== old hero force: %5.3f" % hero.TalentSets[hero.ActiveTalentSet].Force)
        hero.TalentSets[hero.ActiveTalentSet].Force = 160.0

        # logLevel( logging.INFO ) #

        self.sendHero( MASTER, 0, hero_id=hero_id, hero_crc=hero_crc )
        self.accs[SLAVE1].partydata.RatingLimits.MinRating = 1500
        self.accs[SLAVE1].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли party_hero
        # и теми же грязными руками нахачиваем гвардейский статус:
        self.accs[SLAVE1].model.LordInfo.GuardInfo.NumberOfWins = 1000.0
        hero.Master = True
        info("== old hero force: %5.3f" % hero.TalentSets[hero.ActiveTalentSet].Force)
        hero.TalentSets[hero.ActiveTalentSet].Force = 160.0
        self.accs[SLAVE2].partydata.RatingLimits.MinRating = 1500
        self.accs[SLAVE2].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли party_hero
        # и теми же грязными руками нахачиваем гвардейский статус:
        self.accs[SLAVE2].model.LordInfo.GuardInfo.NumberOfWins = 1000.0
        hero.Master = True
        info("== old hero force: %5.3f" % hero.TalentSets[hero.ActiveTalentSet].Force)
        hero.TalentSets[hero.ActiveTalentSet].Force = 160.0

        self.sendHero( SLAVE1, 0, hero_id=hero_id_3, hero_crc=hero_crc_3)

        self.sendHero( SLAVE2, 0, hero_id=hero_id_4, hero_crc=hero_crc_4)

        test, event = self.checkPendingEvent(MASTER, "hero", "TamburData")
        test, event = self.checkNextPendingEvent(test, MASTER, "hero", "TamburData")
        test, event = self.checkNextPendingEvent(test, SLAVE1, "hero", "TamburData")
        test, event = self.checkNextPendingEvent(test, SLAVE2, "hero", "TamburData")
        # проверим подменился ли герой, если он в спсике запрещенных то не должен
        self.assert_( event.hero_crc == old_hero_crc_4)

        # --- теперь присылаем mm_ready
        self.accs[MASTER].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли mm_ready
        test = self.makeGuestAction( Mm_ready, MASTER, mmid=MASTER_MMID )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("Mm_ready action reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") )

        self.accs[SLAVE1].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли mm_ready
        test = self.makeGuestAction( Mm_ready, SLAVE1, mmid=SLAVE1_MMID )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("Mm_ready action reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") )

        self.accs[SLAVE2].data.mm.progress = MM.STATUS_GUARDS_LOBBY # грязными руками хакаем прогресс, чтобы приняли mm_ready
        test = self.makeGuestAction( Mm_ready, SLAVE2, mmid=SLAVE2_MMID )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("Mm_ready action reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") )


        self.I.WS.pingMatchmaking()

        test, event = self.checkPendingEvent(MASTER, "tambur_ready", "TamburData", ready_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, SLAVE1, "tambur_ready", "TamburData")
        test, event = self.checkNextPendingEvent(test, SLAVE2, "tambur_ready", "TamburData")

        # теперь делаем cancel (по идее, тамбур должен развалиться)
        test = self.makeGuestAction( MatchmakingCancelAction, MASTER, mmid=MASTER_MMID )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("MatchmakingCancelAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") )

        # проверяем что развалилось..
        test, event = self.checkPendingFriendsEvent(MASTER, "status_change", "FriendsData", friend_auid=MASTER)
        test, event = self.checkNextPendingEvent(test, MASTER, "deleted", "TamburData", "tambur_id")

        # тикнем карманный PersonServer (чтобы удалил тамбур-контекст)
        self.iDictPTS.WS.tick()

        # --------------
        info("- after-cancel ping -")
        self.I.WS.pingMatchmaking()

        test = self.makeGuestAction( MatchmakingPingAction, MASTER, mmid=0 )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("MatchmakingPingAction reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok")==0 )

        # --------------
        logLevel( )

##----------------------------------------------------------------
##----------------------------------------------------------------

def main():
    DEFAULT_LOG_LEVEL = logging.INFO
    #DEFAULT_LOG_LEVEL = logging.ERROR
    #print "DEFAULT_LOG_LEVEL: %s" % DEFAULT_LOG_LEVEL
    setDefaultLogLevel( DEFAULT_LOG_LEVEL )
    logging.basicConfig( level=DEFAULT_LOG_LEVEL, format='[%(asctime)s %(levelname)8s] %(message)s' )
    
    info( "Loading XDB..." )
    config = MultiConfig()
    _SD = MultiStaticData( options.xdb_path + "/ExportedSocialData.xml", config.getMainConfig() )
    config.fillStaticDataDependendValues(_SD)
    BaseDummyTest.setXDB( _SD )
    
    #~ #########################
    #~ map = _SD.getObjectByDbid( "/Maps/Tutorial/_1.ADMPDSCR" )
    #~ err( "map.matchmaking:%s" % str(map.matchmaking) )
    
    #~ exit(0)
    #~ #########################
    
    info( "-- START tests.." )
    
    ITERATIONS = 1
    for i in range(ITERATIONS):
        try:
            unittest.main()
        except SystemExit:
            if str( exc() ) == "True":
                sys.exit(1)
        except:
            catch()
            sys.exit(1)
            
    info( "-- Finish tests (x %d)." % ITERATIONS )
    

if __name__ == "__main__":
    main()
