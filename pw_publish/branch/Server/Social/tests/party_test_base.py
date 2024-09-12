# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, json

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
from iwebserver import IWebServer, DUMMY_TEST_WS_ID, DUMMY_TEST_WS_NAME
from pwserver import PwWorkServer
from pwhandler import PwJsonHandler
from modeldata.ModelData import ModelData
from modeldata.datamanager import PwNewModelManager
from enums import FlagType
import MM # matchmaking const

from subaction import SubAction 

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

from logic.all import Keepalive, Hire_hero, Party_invite, Party_accept, Party_decline, Party_disband, Party_kick
from logic.all import Party_hero, Party_go, Party_dodge, Party_map, Party_flag, Party_inventory_is_full, Choose_party_again
from ext_main.login import LoginAction, LogoutAction

from ipeerserver import *
from ipersonserver import *
import ichatserver
from iaggregator import ISocialAggregator
import ixchange

import ifriendservice
import ipartyservice
from friend_service import FriendService, FriendServiceHandler
from party_service import PartyService, PartyServiceHandler

class PartyTestBase( BaseDummyTest ):
    """ Этот тест будет создавать локальные копии WS и PS, и завязывать взаимодействие их SubAction-ов напрямую друг на друга 
        (через подмену их интерфейсов I.PS и I.WSX фейками) """

    ## -------------------------------------------------------------------------------------------------------------------------------------
    def makeGuestAction(self, classOf, guestIndex, **kwargs):
        acc = self.accs[ guestIndex ]
        uid = acc.uid
        self.flatParams = kwargs
        self.testAction = TestDictAction( dict(**kwargs), classOf, acc=acc, uid=uid, request=self ) # MC, SQL и прочие интерфейсы забирайте прямо у нашего класса
        return self.testAction

    def sendGuestAction(self, classOf, guestIndex, ok=1, **kwargs):
        test = self.makeGuestAction( classOf, guestIndex, **kwargs ) 
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("%s reply: %s" % (classOf.action, test.reply))
        self.assert_( test.reply and test.reply.get("ok")==ok ) 
        return test
        
    ## -------------------------------------------------------------------------------------------------------------------------------------
    def getFlatParams(self, except_list=[]):
        ##info( "party.test getFlatParams" )
        if except_list:
            copyDict = {}
            for key,val in self.flatParams.iteritems():
                if key not in except_list:
                    copyDict[key] = val
            return copyDict
        else:
            return self.flatParams
            
    ## -------------------------------------------------------------------------------------------------------------------------------------
    def addArguments(self, **kwargs):
        ##info( "party.test addArguments: %s" % kwargs )
        if kwargs:
            for k,v in kwargs.iteritems():
                self.flatParams[k] = v
                self.arguments[k] = [v]
        
    # -------------------------------------------------------------------------------------------------------------------------------------
    def fakeSend2PersonServer(self, args):
        info("fakeSend2PersonServer args: %r" % args)
        
        # args -- это тупо словарь аргументов, которые мы подпихиваем напрямую соответствующему SubAction-у из PersonServer
        action = args.get('action')
        self.assert_( action )
        
        ActionClass = PersonServerHandler.internalActionMap.get(action)
        self.assert_( ActionClass )
        
        test = TestDictAction( args, ActionClass, request=ClassDict(I=self.iDictPS) )
        test.OnStart()
        # ответы от SubAction теперь идут через IOLoop, так что надо ждать
        self.waitAsyncReply( test, 2.0 ) # ждем асинк-ответа
        info("fakeSend2PersonServer reply: %r" % test.reply)
        self.assert_( test.reply ) 
        
        return test.reply
        
    # -------------------------------------------------------------------------------------------------------------------------------------
    def fakeSend2PartyService(self, args):
        info("fakeSend2PartyService args: %r" % args)
        
        # args -- это тупо словарь аргументов, которые мы подпихиваем напрямую соответствующему SubAction-у из PersonServer
        action = args.get('action')
        self.assert_( action )
        
        ActionClass = PartyServiceHandler.internalActionMap.get(action)
        self.assert_( ActionClass )
        
        test = TestDictAction( args, ActionClass, request=ClassDict(I=self.iDictPTS) )
        test.OnStart()
        # ответы от SubAction теперь идут через IOLoop, так что надо ждать
        self.waitAsyncReply( test, 2.0 ) # ждем асинк-ответа
        info("fakeSend2PartyService reply: %r" % test.reply)
        self.assert_( test.reply ) 
        
        return test.reply
        
    # -------------------------------------------------------------------------------------------------------------------------------------
    def fakeSend2FriendService(self, args):
        info("fakeSend2FriendService args: %r" % args)
        
        # args -- это тупо словарь аргументов, которые мы подпихиваем напрямую соответствующему SubAction-у из PersonServer
        action = args.get('action')
        self.assert_( action )
        
        ActionClass = FriendServiceHandler.internalActionMap.get(action)
        self.assert_( ActionClass )
        
        test = TestDictAction( args, ActionClass, request=ClassDict(I=self.iDictFS) )
        test.OnStart()
        # ответы от SubAction теперь идут через IOLoop, так что надо ждать
        self.waitAsyncReply( test, 2.0 ) # ждем асинк-ответа
        info("fakeSend2FriendService reply: %r" % test.reply)
        self.assert_( test.reply ) 
        
        return test.reply
        
    # -------------------------------------------------------------------------------------------------------------------------------------
    def fakeSend2WorkServer(self, args):
        info("fakeSend2WorkServer args: %r" % args)
        
        # args -- это тупо словарь аргументов, которые мы подпихиваем напрямую соответствующему SubAction-у из PersonServer
        action = args.get('action')
        self.assert_( action )
        
        post_body = args.get('_post_body')
        if post_body:
            self.request.body = post_body
        
        ActionClass = PwJsonHandler.internalActionMap.get(action)
        self.assert_( ActionClass )
        
        test = TestDictAction( args, ActionClass, request=self )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("fakeSend2PersonServer reply: %r" % test.reply)
        self.assert_( test.reply ) 
        
        return test.reply
                
    # -------------------------------------------------------------------------------------------------------------------------------------
    def fakeSend2ChatServer(self, args):
        info("fakeSend2ChatServer args: %r" % args)
        return dict( ok=1 )
        
        #~ class Response:
            #~ def __init__(self):
                #~ self.error = 0
                #~ self.body = '{"ok" : 1}'
                
        #~ return Response()

    ## -------------------------------------------------------------------------------------------------------------------------------------
    ## helper
    def createGuestInfrastructure(self, AGG=None, start_auid=1):
        self.I.GG = FakeWSGuidGenerator(start_auid-1)
        self.I.WS = PwWorkServer( I=self.I, test_mode=True )

        class ChatHTTP(object):
            def __call__(self, args):
                return {'ok' : 1, 'host' : 'chat0', 'key' : '1234'}
        self.I.CHAT = ichatserver.IFakeChatServer( ChatHTTP() )
        
        self.I.WS.MM_PING_PERIOD = -1 # чтобы генерация пакетов для matchmaking не делала задержек между пингами статуса сессий юзера
        self.I.WS.MM_MIN_ADD_PERIOD = 0
        self.I.WS.resetUserSessions = resetUserSessionsDummy # заменяем настоящий "принудительный mm_cancel" заглушкой
        self.I.WS.nextInt64GUID = self.I.GG.nextInt64GUID # подменяем GUID Generator на фейк, раздающий ID-шки для ModelData с единицы
        self.HERO_ID = 1        
        cfg.TOURNAMENT_SERVER = coord_cfg.COORDINATOR_TOURNAMENT_SERVER
        cfg.TOURNAMENT_SERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_SERVER_ADDR
        cfg.TOURNAMENT_XSERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_XSERVER_ADDR
        cfg.MUID_TO_DLCS = coord_cfg.COORDINATOR_MUID_TO_DLCS

        if not AGG:
            AGG = ISocialAggregator() # пустая болванка
            self.isAsyncAgg = 0 
        else:
            self.isAsyncAgg = 1
            
        #--------------------------------------------------
        # создаем отдельный словарь интерфейсов для PartyService
        self.iDictPTS = ClassDict( self.I )
        self.iDictPTS.WS = PartyService( I=self.iDictPTS, test_mode=True )
        self.iDictPTS.AGG = AGG
        self.iDictPTS.WSX = IFakePeerWebServer( HTTP=self.fakeSend2WorkServer )
        self.iDictPTS.CHAT = ichatserver.IFakeChatServer( HTTP=self.fakeSend2ChatServer )
        self.iDictPTS.SD = self.I.SD.getMainSD()
        
        #--------------------------------------------------
        # создаем отдельный словарь интерфейсов для PartyService
        self.iDictFS = ClassDict( self.I )
        self.iDictFS.WS = FriendService( I=self.iDictFS, test_mode=True )
        self.iDictFS.AGG = AGG
        self.iDictFS.WSX = IFakePeerWebServer( HTTP=self.fakeSend2WorkServer )
        self.iDictFS.CHAT = ichatserver.IFakeChatServer( HTTP=self.fakeSend2ChatServer )
        
        ## self.I.PS = IFakePersonServer( HTTP=self.fakeSend2PersonServer )
        self.I.FRIENDS = ifriendservice.IFakeFriendService( HTTP=self.fakeSend2FriendService )
        self.I.PARTY = ipartyservice.IFakePartyService( HTTP=self.fakeSend2PartyService )
        self.I.PS = IScaledPersonServer( PARTY=self.I.PARTY, FRIENDS=self.I.FRIENDS )
        self.I.SEX = ixchange.IFakeSocialExchange( HTTP=None )
        
        self.iDictPTS.FRIENDS = self.I.FRIENDS
        self.iDictPTS.PARTY = self.I.PARTY
        self.iDictFS.FRIENDS = self.I.FRIENDS
        self.iDictFS.PARTY = self.I.PARTY
        
        # -------------------------------------------------
        # сообщаем PersonServer-у, что есть такой peer WS:
        self.fakeSend2FriendService( dict(action="peer", sid=DUMMY_TEST_WS_ID, on=1, name=DUMMY_TEST_WS_NAME, addr="0.0.0.0") )
        self.fakeSend2PartyService( dict(action="peer", sid=DUMMY_TEST_WS_ID, on=1, name=DUMMY_TEST_WS_NAME, addr="0.0.0.0") )
        
        # -------------------------------------------------
        # login guest users
        self.allow_login_underscores = 1
        
        self.accs = {}
        
    ## -------------------------------------------------------------------------------------------------------------------------------------
    ## основной вызываемый для инициализации guest-теста метод (объединяет createGuestInfrastructure + createGuestUsersCount)
    def createGuestUsers(self, user_count=2, AGG=None, start_auid=1, roll_fraction=0):
        self.createGuestInfrastructure(AGG, start_auid)
        return self.createGuestUsersCount(user_count, roll_fraction)
        
    ## -------------------------------------------------------------------------------------------------------------------------------------
    ## helper: логиним юзера, ждем пока загрузятся persistent данные
    def createGuestUsersCount(self, user_count=2, roll_fraction=0, start_auid=0):
        if start_auid:
            self.I.GG.inc = start_auid-1
            
        for i in xrange(user_count):
            test = self.makeAction( LoginAction, guest=1, geo_info='{}' )
            test.OnStart()
            self.waitAsyncReply( test, 1.0 ) # ждем асинк-ответа
            self.assert_( test.reply and test.reply.get("ok") ) # первый раз берем из MC или SQL
        
            uid = test.reply.get("uid")
            ##info("new guest uid = %d (start_auid=%d)" % (uid, start_auid))
            
            self.assert_( uid ) 
            acc = users.get( uid )
            self.accs[uid] = acc 
            self.assert_( uid and acc )
            self.assert_( self.accs[uid] == acc )
        
            # якобы загрузили persistent data
            self.assert_( acc.loaded )

            # create new DataModel (1 hero)
            if roll_fraction:
                err("roll_fraction")
                fraction = "B" if (uid%2) else "A"
            else:
                fraction = "B"
            test = self.makeGuestAction( SetFractionAction, uid, fraction=fraction, create_heroes=1, force_new=1 )
            test.OnStart()
            self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
            self.assert_( test.reply and test.reply.get("ok") and test.reply.get("init") ) 
            
            # забираем (пустые?) списки друзей от fake-агрегатора (чтобы потом не мешались)
            test = self.makeGuestAction( PingAction, uid )
            test.OnStart()
            self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
            self.assert_( test.reply and test.reply.get("ok") ) 
            
            # кроме того, обязательно прислать keepalive, чтобы юзер считался "в замке" на person_server
            test = self.makeGuestAction( Keepalive, uid )
            test.OnStart()
            self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
            self.assert_( test.reply and test.reply.get("ok") ) 
            
        return test # для желающих - вернем последний список друзей (в test.reply)
            
            

    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    #    BRIEF-style helpers
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    
    def _assertPendingFriendsEvent(self, event, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs):
        self.assert_( event )
        self.assert_( event.action == "server_friends" and event.cmd == eventCmd ) 
        
        for key in checkEventArgs:
            info( "checking that event key present: key=%r, event[key]=%r" % (key, event.get(key)) )
            self.assert_( event.get(key) is not None )
            
        # and event.message == "ok" and event.invite_auid == SLAVE
        for key,value in kwEventArgs.iteritems():
            val = event.get(key)
            info( "key %s, event.get(key) %s [type %s] =%s= value %s [type %s]" % (key, val, type(val), "EQ" if (val == value) else "NE", value, type(value)) )
            self.assert_( event.get(key) == value )
            
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def checkPendingFriendsEvent(self, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs):
        test = self.makeGuestAction( PingAction, guestIndex )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        
        event = ClassDict( test.reply["pending_events"][0]["friends"] )
        ## warn("event: %s" % event)
        self._assertPendingFriendsEvent( event, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs )
        
        for model_key in SubAction.MODEL_CHANGE_KEYS:
            model_changes = test.reply.get(model_key)
            if model_changes:
                info( "%s model_changes: %s" % (model_key, model_changes) )
                self.assertModelChangeFormat( model_changes )
        
        test.reply["pending_events"].pop(0) # выкидываем разобранный евент (на случай дальнейших checkNextPendingEvent)
        return test, event
        
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    #   CHECKs
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def _assertPendingEvent(self, event, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs):
        self.assert_( event )
        self.assert_( event.action == "server_party" and event.cmd == eventCmd ) 
        self.assert_( ((event.party_id is not None) or eventCmd=="error") and event.msg_id )
        
        for key in checkEventArgs:
            info( "checking that event key present: key=%r, event[key]=%r" % (key, event.get(key)) )
            self.assert_( event.get(key) is not None )
            
        # and event.message == "ok" and event.invite_auid == SLAVE
        for key,value in kwEventArgs.iteritems():
            val = event.get(key)
            info( "key %s, event.get(key) %s [type %s] =%s= value %s [type %s]" % (key, val, type(val), "EQ" if (val == value) else "NE", value, type(value)) )
            self.assert_( event.get(key) == value )
            
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def checkPendingEvent(self, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs):
        test = self.makeGuestAction( PingAction, guestIndex )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        pending_events = test.reply["pending_events"]

        event = ClassDict( pending_events[0]["party"] )
        ## warn("event: %s" % event)
        self._assertPendingEvent( event, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs )

        for model_key in SubAction.MODEL_CHANGE_KEYS:
            model_changes = test.reply.get(model_key)
            if model_changes:
                info( "%s model_changes: %s" % (model_key, model_changes) )
                self.assertModelChangeFormat( model_changes )

        test.reply["pending_events"].pop(0) # выкидываем разобранный евент (на случай дальнейших checkNextPendingEvent)
        return test, event

    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def checkNextPendingEvent(self, test, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs):
        event = ClassDict( test.reply["pending_events"][0]["party"] )
        self._assertPendingEvent( event, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs )
        test.reply["pending_events"].pop(0)
        return test, event
        
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def checkNoPendingEvents(self, guestIndex):
        test = self.makeGuestAction( PingAction, guestIndex )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        self.assert_( not test.reply.get("pending_events") )
        return test
    
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def skipPendingEvents(self, guestIndex):
        test = self.makeGuestAction( PingAction, guestIndex )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        info( "skipPendingEvents[%d]: %d pending events skipped" % (guestIndex, len(test.reply.get("pending_events"))) )
        return test
        
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def checkPendingEventCount(self, event_count, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs):
        test, event = self.checkPendingEvent(guestIndex, eventCmd, *checkEventArgs, **kwEventArgs)
        for i in xrange(event_count-1):
            self.checkNextPendingEvent(test, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs)

    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def checkPendingGoProgress(self, user_count, guestIndex, PARTY_ID, skipAfterEvents=0):
        test = self.makeGuestAction( PingAction, guestIndex  )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        self.assert_( len(test.reply["pending_events"]) == user_count+1+1 + skipAfterEvents) # 1*GO + 1*status_change + N*"PROGRESS 1"
        test.go = 0
        test.progress = 0
        test.status_change = 0
        go_events = test.reply["pending_events"][ :(user_count+1+1) ]
        for e in go_events:
            event = ClassDict( e.get("party") or e.get("friends") )
            self.assert_( event )
            self.assert_( (event.action == "server_party" and event.party_id == PARTY_ID) or (event.action == "server_friends" and event.friend_auid == guestIndex) )
            self.assert_( event.msg_id )
            self.assert_( event.cmd in ["go", "progress", "status_change"] )
            if event.cmd == "go":
                test.go += 1
                self.assert_( event.heroes and isinstance(event.heroes, dict) and len(event.heroes) == user_count )
                for auid, h in event.heroes.iteritems():
                    hero = ClassDict( h )
                    self.assert_( hero.hero_id and hero.hero_crc ) # and hero.uid 
            elif event.cmd == "status_change":
                test.status_change += 1
            elif event.cmd == "progress":
                test.progress += 1
                self.assert_( event.progress == 1 )
        self.assert_(test.go == 1 and test.progress == user_count and test.status_change == 1)
        return test
        
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def _assertPendingFriendEvent(self, event, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs):
        self.assert_( event )
        self.assert_( event.action == "server_friends" and event.cmd == eventCmd ) 
        self.assert_( event.msg_id )
        
        for key in checkEventArgs:
            self.assert_( event.get(key) is not None )
            
        # and event.message == "ok" and event.invite_auid == SLAVE
        for key,value in kwEventArgs.iteritems():
            val = event.get(key)
            info( "key %s, event.get(key) %s [type %s] =%s= value %s [type %s]" % (key, val, type(val), "EQ" if (val == value) else "NE", value, type(value)) )
            self.assert_( event.get(key) == value )
            
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def checkPendingFriendEvent(self, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs):
        test = self.makeGuestAction( PingAction, guestIndex )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        
        info( 'checkPendingFriendEvent test.reply["pending_events"] = %s' % test.reply["pending_events"] )
        
        event = ClassDict( test.reply["pending_events"][0]["friends"] )
        self._assertPendingFriendEvent( event, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs )
        
        for model_key in SubAction.MODEL_CHANGE_KEYS:
            model_changes = test.reply.get(model_key)
            if model_changes:
                info( "%s model_changes: %s" % (model_key, model_changes) )
                self.assertModelChangeFormat( model_changes )
        
        test.reply["pending_events"].pop(0) # выкидываем разобранный евент (на случай дальнейших checkNextPendingEvent)
        return test, event
    
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def checkNextPendingFriendEvent(self, test, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs):
        event = ClassDict( test.reply["pending_events"][0]["friends"] )
        self._assertPendingFriendEvent( event, guestIndex, eventCmd, *checkEventArgs, **kwEventArgs )
        
        for model_key in SubAction.MODEL_CHANGE_KEYS:
            model_changes = test.reply.get(model_key)
            if model_changes:
                info( "%s model_changes: %s" % (model_key, model_changes) )
                self.assertModelChangeFormat( model_changes )
        
        test.reply["pending_events"].pop(0) # выкидываем разобранный евент (на случай дальнейших checkNextPendingEvent)
        return test, event

    def checkChangeEventForAllMembers(self, members, cmd, party_id):
        for member in members:
            est, event = self.checkPendingEvent(member, cmd, party_id=party_id)
        
    # -----------------------------------------------------------------------------------------------------------------
    #   SENDs
    # -----------------------------------------------------------------------------------------------------------------
    def sendInvite(self, masterIndex, slaveIndex, invite_auid=0, game_type="/Maps/Multiplayer/MOBA/_.ADMPDSCR", with_bots = 0):
        if not invite_auid:
            invite_auid = self.accs[slaveIndex].auid
        test = self.makeGuestAction( Party_invite, masterIndex, invite_auid=invite_auid, game_type=game_type, with_bots = with_bots ) # после unjson вернется int
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("invite reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") ) 
        return test

    # -----------------------------------------------------------------------------------------------------------------
    def sendMap(self, masterIndex, game_type="/Maps/Multiplayer/MOBA/_.ADMPDSCR", with_bots = 0):
        test = self.makeGuestAction(Party_map, masterIndex, game_type=game_type, with_bots=with_bots)  # после unjson вернется int
        test.OnStart()
        self.waitAsyncReply(test, 0.5)  # ждем асинк-ответа
        info("map reply: %s" % test.reply)
        self.assert_(test.reply and test.reply.get("ok"))
        return test

    # -----------------------------------------------------------------------------------------------------------------
    def sendFlag(self, guestIndex, flag_type, flag_persistent_id):
        test = self.makeGuestAction(Party_flag, guestIndex, flag_type=flag_type, flag_persistent_id=flag_persistent_id)
        test.OnStart()
        self.waitAsyncReply(test, 0.5) # ждем асинк-ответа
        info("flag reply: %s" % test.reply)
        self.assert_(test.reply and test.reply.get("ok"))
        return test

    # -----------------------------------------------------------------------------------------------------------------
    def sendInventoryIsFull(self, guestIndex, is_full):
        test = self.makeGuestAction(Party_inventory_is_full, guestIndex, isFull=is_full)  # после unjson вернется int
        test.OnStart()
        self.waitAsyncReply(test, 0.5)  # ждем асинк-ответа
        info("inventory full reply: %s" % test.reply)
        self.assert_(test.reply and test.reply.get("ok"))
        return test
    
    # -----------------------------------------------------------------------------------------------------------------
    def sendAccept(self, slaveIndex, masterIndex, master_auid=0):
        if not master_auid:
            master_auid = self.accs[masterIndex].auid
        test = self.makeGuestAction( Party_accept, slaveIndex, master_auid=master_auid )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        return test
    
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def sendDecline(self, slaveIndex, masterIndex, master_auid=0):
        if not master_auid:
            master_auid = self.accs[masterIndex].auid
        test = self.makeGuestAction( Party_decline, slaveIndex, master_auid=master_auid )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        return test
    
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def sendDisband(self, slaveIndex, masterIndex, master_auid=0):
        if not master_auid:
            master_auid = self.accs[masterIndex].auid
        test = self.makeGuestAction( Party_disband, slaveIndex, master_auid=master_auid, party_id=self.accs[masterIndex].party_id )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        return test
        
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def sendKick(self, masterIndex, slaveIndex, kick_auid=0):
        if not kick_auid:
            kick_auid = self.accs[slaveIndex].auid
        master_auid = self.accs[masterIndex].auid
        test = self.makeGuestAction( Party_kick, masterIndex, master_auid=master_auid, kick_auid=kick_auid, party_id=self.accs[masterIndex].party_id )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 
        return test
        
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def sendHero(self, guestIndex, party_id, gParty=False, **kwargs):
        if party_id:
            test = self.makeGuestAction( Party_hero, guestIndex, party_id=party_id, guardParty=gParty, **kwargs )
        else:
            test = self.makeGuestAction( Party_hero, guestIndex, guardParty=gParty, **kwargs )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") ) 

    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def sendGo(self, guestIndex, party_id, expectedOk=1):
        test = self.makeGuestAction( Party_go, guestIndex, party_id=party_id )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") == expectedOk) 

    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def sendDodge(self, guestIndex, party_id):
        test = self.makeGuestAction( Party_dodge, guestIndex, party_id=party_id)
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") )
        
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def sendLogout(self, guestIndex):
        test = self.makeGuestAction( LogoutAction, guestIndex )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and (test.reply.get("ok") or test.reply.get("error") == "bad session") ) 
        return test

    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def sendChoosePartyAgain(self, masterIndex, alliesIndexes, agreed, finalize_time=20):
        post_data = {"lock_end_time": int(time.time()) + finalize_time, "agreed": agreed, "allies_keys": alliesIndexes}
        test = self.makeGuestAction( Choose_party_again, masterIndex, post_data=json_dumps(post_data), session_id=1) # после unjson вернется int
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        info("choose_party_again reply: %s" % test.reply)
        self.assert_( test.reply and test.reply.get("ok") )
        return test
        
    #~ # --------------------------------------------------------------------------------------------------------------
    #~ def sendStatus(self, guestIndex):
        #~ test = self.makeGuestAction( PartyStatusAction, guestIndex)
        #~ test.OnStart()
        #~ self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        #~ self.assert_( test.reply and test.reply.get("ok")) 
        #~ return test
        
    # -----------------------------------------------------------------------------------------------------------------
    def checkSoloMM_START(self, guestIndex):
        test = self.makeGuestAction( MatchmakingAddAction, guestIndex, game_type="/Maps/Multiplayer/MOBA/_.ADMPDSCR", with_bots = 1, fraction="B", src_hero_id=self.HERO_ID )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok")) 
        return test
        
    # ---------------------------------------------------------------------------------------------------------------------------------------------------
    def checkSoloMM_FAIL(self, guestIndex):
        test = self.makeGuestAction( MatchmakingAddAction, guestIndex, game_type="/Maps/Multiplayer/MOBA/_.ADMPDSCR", with_bots = 1, fraction="B", src_hero_id=self.HERO_ID )
        test.OnStart()
        self.waitAsyncReply( test, 0.5 ) # ждем асинк-ответа
        self.assert_( test.reply and test.reply.get("ok") == 0 ) 
        return test
        
    # -----------------------------------------------------------------------------------------------------------------
    def buyHero(self, index, hero_class_name):
        # нахачим юзеру еще одного героя (6 по счету)
        self.accs[index].model.LordInfo.Fame = 80000000
        self.accs[index].model.Resources.Silver = 5000000
        self.sendGuestAction( Hire_hero, index, PersistentId=crc32(hero_class_name), rid=1 )
        assert len( self.accs[index].model.HeroesKeeper ) == 6
        assert len( self.accs[index].model.Heroes ) == 6

    # -----------------------------------------------------------------------------------------------------------------
    def setLastPlayedMap(self, index, map_id):
        # Поставим новому игроку в данные карту (если сражений ещё не было, то этот слот в данных пустой)
        self.accs[index].model.LordInfo.LastStartedMap.MapId = map_id

    def addCustomFlag(self, index, persistentId):
        self.accs[index].model.Flags.append(persistentId)
        self.accs[index].model.FlagInfo.PersistentId = persistentId
        self.accs[index].model.FlagInfo.FlagType = FlagType.Special
