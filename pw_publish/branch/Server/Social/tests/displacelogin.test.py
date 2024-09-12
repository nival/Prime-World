#!/usr/bin/env python
# -"- coding: utf8 -"- 
# (C) Dmitry Kolb 2014, Nival Network 
import sys, os, time, logging, json

os.chdir('..')
sys.path.append( os.path.abspath('.') )
sys.path.append( os.path.abspath('cfg') )
from base.helpers import *

from ext_main.login import LoginAction, LogoutOldUserAction
from ext_main.sn_login import SocAggLoginAction

import handlers
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

class MockWSX:

    class Request:
        def __init__(self, addr, args, body, post, callback):
            self.addr = addr
            self.args = args
            self.body = body
            self.post = post
            self.callback = callback

    def __init__(self):
        self.requests = {}

    def fetch(self, addr, args, callback, subrequest, unwrap=None, timeout=0):
        self.post(addr, args, None, callback, subrequest, unwrap, timeout)

    def post(self, _addr, args, body, callback, subrequest, unwrap, timeout):
        addr = _addr+'/?' + urllib.urlencode(args)
        if addr not in self.requests:
            self.requests[addr] = []
        self.requests[addr].append(MockWSX.Request(addr, args, body, body!=None, callback ))

    def push(self, addr, index, response):
        requests = self.requests[addr]
        request = requests[index]
        request.callback(response)
        del requests[index]
        if len(requests) == 0:
            del self.requests[addr]
        return request.addr

    def check(self, addr, index):
        requests = self.requests.get(addr, [])
        if index < len(requests):
            return True
        return False

class LoopTest_Example( BaseDummyTest ):
    """ Пример конкретного "асинхронного теста" на базе BaseLoopTest. """
    def createGuestInfrastructure(self):
        self.I.GG = FakeWSGuidGenerator()
        self.I.WS = PwWorkServer( I=self.I, test_mode=True )
        self.I.GEO = GeoLocator()
        self.I.WSX = MockWSX()
        #cfg.resetSqlServers()
        #self.I.SQL = IfaceFactory.makeSqlInterface( options.sql, coord_cfg.COORDINATOR_SQL_CONFIG, num_threads=cfg.SQL_THREADS)
        #info("SQL interface: " + str(self.I.SQL))
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
        self.I.WS.peers[1] = {"name":"one", "addr": "dummy"}
        self.I.WS.peers[2] = {"name":"two", "addr": "dummy"}
        self.I.SQL.addServer(1, "one")
        self.I.SQL.addServer(2, "two")

        # Заглушки для логики
        self.I.SQL.login = self.__Login
        self.I.SQL.logout = self.__Logout
        self.I.WS.onAccActive = self.__onAccActive
        self.I.WS.onAccSaved = self.__onAccSaved

    def __onAccSaved(self, acc, uid):
        info("Mock onAccSaved acc=%r, uid=%r", acc, uid)

    def __onAccActive(self, acc, uid, callback):
        info("Mock onAccActive start acc=%r, uid=%r", acc, uid )
        callback()

    def __Logout(self, login_name, server_id, callback):
        info("Mock sql logout %r %r", login_name, server_id)
        reply = ClassDict( {"ws":0, "login":login_name, "id":self.I.SQL._next_uid} )
        if callback is not None:
            try:
                callback( reply )
            except Exception:
                callback()

    def __Login(self, login_name, server_id, callback, isFirst=False):
        info("Mock sql login %r %r", login_name, server_id)
        self.I.SQL._next_uid += 1
        if isFirst:
            reply = ClassDict( {"ws":1, "login":login_name, "pwd":"123", "id":self.I.SQL._next_uid} )
            return callback( { "r": [reply] } )
        else:
            reply = ClassDict( {"ws": 2, "login":login_name, "pwd":"123", "id":self.I.SQL._next_uid} )
            return callback( { "r": [reply] } )

    def onDisplaceWithSQLKickLogin(self, reply):
        info("--------------- onRepeatingDisplaceWithSQLKickLogin %r", reply)
        testLoginAction = self.makeAction( LoginAction, user='fb_730742963',auth="12345", isGM=False)
        # мы сча на первой ws-ке
        options.server_id = 1
        testLoginAction.OnStart()
        assert self.I.WSX.requests

        testLogoutOldUserAction = self.makeAction(LogoutOldUserAction, login='fb_730742963')
        testLogoutOldUserAction.OnStart()

        info("onRepeatingDisplaceWithSQLKickLogin %r", testLogoutOldUserAction.reply)
        assert testLogoutOldUserAction.reply.get("ok") == 1

        # а сча на второй ws-ке
        options.server_id = 2
        callback = self.I.WSX.requests.values()[0][0].callback
        callback({"ok":1})

        info("onRepeatingDisplaceWithSQLKickLogin %r", testLoginAction.reply)
        assert testLoginAction.reply.get("ok") == 1

    def onRepeatingDisplaceLogin(self, reply):
        info("--------------- onRepeatingDisplaceLogin %r", reply)
        testLoginAction = self.makeAction( LoginAction, user='fb_730742963',auth="12345", isGM=False)

        # мы сча на первой ws-ке
        options.server_id = 1
        testLoginAction.OnStart()
        assert self.I.WSX.requests

        testLogoutOldUserAction = self.makeAction(LogoutOldUserAction, login='fb_730742963')
        handlers.logins['fb_730742963'] = 12345
        handlers.users[12345] = ClassDict({"failed": False, "data": ClassDict({"mm": None}), "uid":12345})
        testLogoutOldUserAction.OnStart()

        info("onRepeatingDisplaceLogin %r", testLogoutOldUserAction.reply)
        assert testLogoutOldUserAction.reply.get("ok") == 1

        # а сча на второй ws-ке
        options.server_id = 2
        callback = self.I.WSX.requests.values()[0][0].callback
        callback({"ok":1})

        info("onRepeatingDisplaceLogin %r", testLoginAction.reply)
        assert testLoginAction.reply.get("ok") == 1

    def onDisplaceLogin(self, reply):
        info("--------------- onDisplaceLogin %r", reply)
        testLoginAction= self.makeAction( LoginAction, user='fb_730742963',auth="12345", isGM=False)
        testLoginAction.OnStart()
        assert self.I.WSX.requests
        callback = self.I.WSX.requests.values()[0][0].callback
        options.server_id = 2
        callback({"ok":1})
        #self.waitAsyncReply(test.reply, 10)
        info("onDisplaceLogin reply %r", testLoginAction.reply)
        assert testLoginAction.reply.get("ok") == 1

    def onDisplaceLoginWithBadWS(self, reply):
        info("--------------- onDisplaceLoginWithBadWS %r", reply)
        testLoginAction = self.makeAction( LoginAction, user='fb_730742963',auth="12345", isGM=False)
        testLoginAction.OnStart()
        assert self.I.WSX.requests
        callback = self.I.WSX.requests.values()[0][0].callback
        options.server_id = 2
        callback({})

        info("onDisplaceLoginWithBadWS reply %r", testLoginAction.reply)
        assert testLoginAction.reply.get("ok") == 0
        assert testLoginAction.reply.get("ec") == 6

    def onDisplaceLoginWithBadWS1(self, reply):
        info("--------------- onDisplaceLoginWithBadWS1 %r", reply)
        testLoginAction = self.makeAction( LoginAction, user='fb_730742963', auth="12345", isGM=False)
        testLoginAction.OnStart()
        assert self.I.WSX.requests
        callback = self.I.WSX.requests.values()[0][0].callback
        options.server_id = 2
        callback({"ok": 0, "ec": 12345, "error": "test error"})

        info("onDisplaceLoginWithBadWS1 reply %r", testLoginAction.reply)
        assert testLoginAction.reply.get("ok") == 0
        assert testLoginAction.reply.get("ec") == 12345

    def onDisplaceLoginWithGM(self, reply):
        info("--------------- onDisplaceLoginWithGM %r", reply)
        testLoginAction = self.makeAction( LoginAction, user='fb_730742963', auth="12345", isGM=True)
        testLoginAction.OnStart()
        info("onDisplaceLoginWithGM reply %r", testLoginAction.reply)
        assert testLoginAction.reply.get("ok") == 0
        testLoginAction1 = self.makeAction( LoginAction, user='fb_730742963', auth="12345", isGM=True)
        options.server_id = 2
        testLoginAction1.OnStart()
        info("onDisplaceLoginWithGM reply %r", testLoginAction1.reply)
        assert testLoginAction1.reply.get("ok") == 1

    def testDisplaceLogin(self):

        self.createGuestInfrastructure()
        #{'ver': ['0.12.0.37742'], 'user': ['fb#730742963'], 'key': ['757143950'], 'testkeypass': [None], 'geo_info': ['{}'], 'testkey': [0], 'userlocale': ['RU'], 'auth': ['12345']}

        options.server_id = 1
        #попытка вытеснения когда у нас образовался неизвестный игрок на ws-ке
        self.I.SQL.login("fb_730742963", 1, self.onDisplaceWithSQLKickLogin, True)

    def testDisplaceLogin1(self):
        self.createGuestInfrastructure()
        options.server_id = 1
        #если вдруг было подвисанеи игрока и мы не смогли его вытеснить
        self.I.SQL.login("fb_730742963", 1, self.onRepeatingDisplaceLogin, True)

    def testDisplaceLogin2(self):
        self.createGuestInfrastructure()
        options.server_id = 1
        #обычное вытеснение
        self.I.SQL.login("fb_730742963", 1, self.onDisplaceLogin, True)

    def testDisplaceLogin3(self):
        self.createGuestInfrastructure()
        options.server_id = 1
        #если вдруг упала ws-ка и игрок подвис
        self.I.SQL.login("fb_730742963", 1, self.onDisplaceLoginWithBadWS, True)

    def testDisplaceLogin4(self):
        self.createGuestInfrastructure()
        options.server_id = 1
        #если вдруг ws-ка отправила плохой ответ
        self.I.SQL.login("fb_730742963", 1, self.onDisplaceLoginWithBadWS1, True)

    def testDisplaceLoginforGM(self):
        self.createGuestInfrastructure()
        #если в друг было подвисанеи игрока и мы не смогли его вытеснить
        self.I.SQL.login("fb_730742963", 1, self.onDisplaceLoginWithGM, True)

    def _testDisplaceLoginforSpectator(self):
        pass

## --------------------------------------------------------------------------------------------------------------------
## --------------------------------------------------------------------------------------------------------------------


def main():
    DEFAULT_LOG_LEVEL = logging.INFO
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
