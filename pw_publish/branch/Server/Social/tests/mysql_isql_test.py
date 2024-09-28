#!/usr/bin/env python
# -*- coding: utf-8 -*-

import sys
import os

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

_addPath(r'..')
_addPath(r'../../')
_addPath(r'../base')
_addPath(r'../tornado')

sys.path.append(os.path.abspath('../cfg'))

from helpers import *
import cfg
import coord_cfg  # настройки MC/SQL (будем надеяться, актуальные) возьмем из локального конфига координатора
import tornado.database  # sql query result as iterator
import isql
from ifactory import IfaceFactory

from subaction import *

from ext_main.login import LoginAction
from ext_main.auth import AuthAction
from ext_pw import *

## --------- for sync tests --------------
from test_action import TestAction, TestDictAction
from handlers import resetGlobals, users, PWSOC_VERSION, SOCAGG_VERSION
from ifactory import IfaceFactory
import imemcache, ihttp
import ixchange

## --------- for Async (real MC/SQL/HTTP) test --------------
import thread, tornado.ioloop # для тестов, требующих асинхронной обработки
from config.MultiConfig import *
from tornado.options import options, define
from iwebserver import IWebServer
import iwebserver
from modeldata.ModelData import *
from modeldata.datamanager import PwNewModelManager
from modeldata.persistent_data import PersistentDataManager
import MM # matchmaking const

from fake_guid import FakeWSGuidGenerator

# ---------------------------------
from binascii import crc32   # zlib version is not cross-platform
import xdbload

import unittest

DEFAULT_LOG_LEVEL = logging.INFO

def setDefaultLogLevel(level):
    global DEFAULT_LOG_LEVEL
    DEFAULT_LOG_LEVEL = level

def logLevel(level=None):
    if not level:
        level = DEFAULT_LOG_LEVEL
    logger = logging.getLogger()
    logger.setLevel(level)

def resetUserSessionsDummy(acc):
    pass

def ioloopThreadFunc(ioloop):
    threadId = thread.get_ident()
    info("starting -- ioloop %s -- (thread %d).." % (ioloop, threadId))
    ioloop.start()
    info("ioloop exit (thread %d)" % threadId)

# @action_timing
def printSqlRez(sql_reply):
    #print "???", type(sql_reply)
    #info("printSqlRez: ********* : %s" % sql_reply)
    try:
        result = sql_reply["r"] if sql_reply.has_key("r") else '-None-'
        sql = sql_reply["s"] if sql_reply.has_key("s") else '-None-'
        sql = sql_reply["x"] if sql_reply.has_key("x") else sql
        args = sql_reply["a"] if sql_reply.has_key("a") else '-None-'
        print "********* printSqlRez: rez [[ %s ]] SQL [ %s ] args [ %s ]" % (result, sql, args)
    except Exception as e:
        print "error: ", e


""" Базовый класс для тестов, требующих асинхронной обработки, с участием настоящих async-thread-pool & IOLoop. """
class MysqlIsqlTest(unittest.TestCase):

    ## заводим всю машинерию (ioloop, memcache/sql thread pools)
    def setUp(self):

        info("--------------- LoopTest setUp start ---------------")
        #self.loop = tornado.ioloop.IOLoop.instance()
        self.loop = tornado.ioloop.IOLoop.instance()

        # запускаем в отдельном thread tornado IOLoop
        self.ioThreadId = thread.start_new_thread(ioloopThreadFunc, (self.loop,))
        info("startUp: ioloop thread %d" % self.ioThreadId)

        cfg.TOURNAMENT_SERVER = coord_cfg.COORDINATOR_TOURNAMENT_SERVER
        cfg.TOURNAMENT_SERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_SERVER_ADDR
        cfg.TOURNAMENT_XSERVER_ADDR = coord_cfg.COORDINATOR_TOURNAMENT_XSERVER_ADDR
        cfg.TOURNAMENT_SPECTATOR_AUIDS = coord_cfg.COORDINATOR_TOURNAMENT_SPECTATOR_AUIDS
        cfg.TOURNAMENT_APPLY_RESULTS = coord_cfg.COORDINATOR_TOURNAMENT_APPLY_RESULTS

        self.I = ClassDict()

        self.I.coord_res = {}
        self.I.coord_res["deploy_name"] = "RU"
        self.I.Config = MultiConfig()

        self.I.MC = IfaceFactory.makeMcInterface("none", None)
        self.I.SQL = IfaceFactory.makeSqlInterface("async", coord_cfg.COORDINATOR_SQL_CONFIG)

        self.I.DATA = IfaceFactory.makeIDataInterface("none", None, None)
        self.I.PVX = IfaceFactory.makePvxMmInterface("dummy")
        self.I.MD = PwNewModelManager(ifaceDict=self.I, load_events=False)
        self.I.HTTP = tornado.httpclient.AsyncHTTPClient(max_clients=32)  # может понадобиться для запросов к 

        # внешнему соц.аггрегатору
        self.I.AGG = IfaceFactory.makeSocAggInterface("dummy", "", SOCAGG_VERSION)  # пустая болванка
        self.I.STATS = IfaceFactory.makeIStatsInterface("none", "", self.I)  # пустая болванка

        # еще придется пометить наш "якобы web-сервер" как "якобы активный":
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.server_id = iwebserver.DUMMY_TEST_WS_ID
            options.server_name = iwebserver.DUMMY_TEST_WS_NAME
        else:
            options["server_id"].set(iwebserver.DUMMY_TEST_WS_ID)
            options["server_name"].set(iwebserver.DUMMY_TEST_WS_NAME)

        self.I.SQL.addServer(options.server_id, options.server_name,printSqlRez)

        self.I.WS = IWebServer() # fake обертка WS, умеет только guid-ы делать
        self.I.PS = IfaceFactory.makePersonServerInterface("none", None, self.I.HTTP)
        #self.I.GS = IfaceFactory.makeGuildServiceInterface("none", None, self.I.HTTP)
        self.I.SMODEL = IfaceFactory.makeSerialModelInterface("sync", self.I, PWSOC_VERSION, load_conversion_xml=False)
        self.I.PDM = PersistentDataManager(self.I)
        self.I.BILL = IfaceFactory.makeBillingInterface("dummy", self.I)
        self.I.SEX = ixchange.IFakeSocialExchange(HTTP=None)
        self.I.STATS = IfaceFactory.makeIStatsInterface( "none", "", self.I ) # пустая болванка


        logLevel()

        # NO {{{
        # print dir(self.I.SQL)
        # self.I.SQL.findLoginByUid(1, printSqlRez)
        # self.I.SQL.keepAlive(callback=printSqlRez)
        # print  #iSQL.isDone()
        # CALL sp_login("ok#160447163720",1)
        # }}}

        # Start 
        # self.I.SQL.logEventAll(uid=34359738370, server_id=1, timestamp=1405344966, event="dd'd")
        # self.I.SQL.login("fb#100002965326633", 0, printSqlRez)

        # self.I.SQL.login("fb#100002965326633", options.server_id, printSqlRez)
        # self.I.SQL.lazyLogin("fb#100002965326633", options.server_id, printSqlRez)
        # self.I.SQL.logout("fb#100002965326633", options.server_id, printSqlRez)
        # self.I.SQL.logEvent(login_name="fb#100002965326633",uid="34359738369",
        #                     server_id=options.server_id, timestamp=1405344966, event="d'dd")
        # self.I.SQL.logEventAll(uid=34359738370, server_id=options.server_id, timestamp=1405344966, event="d'dd")
        # self.I.SQL.addServer(options.server_id, options.server_name, printSqlRez)
        # self.I.SQL.removeServer(options.server_name, callback=printSqlRez)
        # self.I.SQL.checkNextServerId(callback=printSqlRez)

        # self.I.SQL.addNewLogin(id='11111', username="test_user", pwd_md5="aabb2408",
        #                        server_id=options.server_id,
        #                        callback=printSqlRez)
        # self.I.SQL.removeLogin(id='11111', username="test_user", callback=printSqlRez)

        # self.I.SQL.setNick(uid='137438953473', nick="test_'' Гламурь ЭЭЭ ``user", callback=printSqlRez)
        # self.I.SQL.setNick(uid='1234', nick="мамаё```ээвыв''dd", callback=printSqlRez)

        # self.I.SQL.removeNicknameById(id='11111', username="test_user", callback=printSqlRez)

        # INSERT INTO `tbl_brick` VALUES ('1', '1', '5', '3');
        # self.I.SQL.loadAndStampData(shard_key="11111", data_key=1, stamp=3, callback=printSqlRez)
        # self.I.SQL.stampData(shard_key="11111", data_key=1, stamp=3, callback=printSqlRez)
        # self.I.SQL.saveData(shard_key="11111", data_key=1, stamp=3, data=500, callback=printSqlRez)
        # self.I.SQL.findUidByNick('ssss', printSqlRez)
        # self.I.SQL.findLoginByUid(uid="137438953473", callback=printSqlRez)
        # self.I.SQL.addBroadcast(msgId=100, msgText="hi, i a`m ' ЪМамаЪ test)))", msgTitle="", tStart=0, tFin=0, interval=0, enabled=0, callback=printSqlRez)
        # self.I.SQL.editBroadcast(msgId=100, msgText="hi, i a`m ' + э ЛОмать ЪМамаЪ test)))", msgTitle="", tStart=0, tFin=0, interval=0, enabled=0, callback=printSqlRez)

        # self.I.SQL.pwcRegister(email_unicode="ss`s@sss.com", pwc_snuid=111, pwd_md5='fsd`;"f111', gender='1', remote_ip='127.0.0.1', birthdate=1111, callback=printSqlRez)
        # self.I.SQL.pwcGet(email_md5='08cacd41dcd8789b1721f33c6768815d', callback=printSqlRez)
        # self.I.SQL.pwcGetByPwcSnuid(pwc_snuid=111, callback=printSqlRez)
        # self.I.SQL.pwcPostRegister(email_md5='08cacd41dcd8789b1721f33c6768815d', auid=2, confirm_token='xxxxxxxxxxxxxxxxxxxxxxx', callback=printSqlRez)
        # self.I.SQL.pwcActivate(email_md5='08cacd41dcd8789b1721f33c6768815d', confirm_token='xxxxxxxxxxxxxxxxxxxxxxx', callback=printSqlRez)
        # self.I.SQL.pwcUpdatePwd(email_md5='08cacd41dcd8789b1721f33c6768815d', pwd_md5='fsd++f111', pwc_snuid=111, callback=printSqlRez)
        # self.I.SQL.pwcUpdateResendTimestamp(email_md5='08cacd41dcd8789b1721f33c6768815d', callback=printSqlRez)
        # self.I.SQL.pwcUpdateResetPwdTimestamp(email_md5='08cacd41dcd8789b1721f33c6768815d', callback=printSqlRez)
        
        #pwc.secret), str(pwc.ip), toint(pwc.gender), toint(pwc.birthdate
        # class pwcTest:
        #     def __init__(self):
        #         self.secret='dsddd'
        #         self.ip="127.0.0.1"
        #         self.gender='1'
        #         self.birthdate=toint(time.time())
        # pwc = pwcTest()
        # self.I.SQL.pwcChangeEmail(pwc_snuid=111, new_email="new2@com.com", old_email_md5="11", new_email_md5='0222241dcd8789b1721f33c67688111', pwc=pwc, callback=printSqlRez)
#         self.I.SQL.pwcMerge(email_md5='0222241dcd8789b1721f33c67688111', main_auid='555', delete_auid='555', callback=printSqlRez)
    
        # Social Exchange
        # CREATE TABLE `tbl_message` (
        # `uid`  int(11) NULL DEFAULT NULL ,
        # `id`  int(11) NULL DEFAULT NULL ,
        # `type`  varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL ,
        # `msg`  varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL ,
        # `expire`  int(11) NULL DEFAULT NULL ,
        # `to`  varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci NULL DEFAULT NULL 
        # )
        # ENGINE=InnoDB
        # DEFAULT CHARACTER SET=utf8 COLLATE=utf8_general_ci
        # ROW_FORMAT=COMPACT;
        # (`uid`,`id`,`type`,`msg`,`expire`,`to`) VALUES(%d,%d,'%s','%s',%d,'%s')
        # self.I.SQL.seAddMessage(to_login='xx', msg_id=1, msg_type=1, message='hi !!!', to_uid=0, expire=0, callback=printSqlRez)
        # self.I.SQL.seGetMessages(x_login='xx', callback=printSqlRez)
        # self.I.SQL.seDeleteMessages(x_login='xx', msg_id_list=(1,2), callback=printSqlRez)
        # self.I.SQL.seFindLogin(x_login='xx', callback=printSqlRez)
        # self.I.SQL.seGetExpiredMessages(timestamp_now='3', callback=printSqlRez)

        # Access Restrictions
        # self.I.SQL.cbtAddRestrictedUser(login='test login', timestamp=0, access_key='', callback=printSqlRez)
        # self.I.SQL.cbtAddRestrictedUser(login='test login', timestamp=0, access_key='', callback=printSqlRez)
        # self.I.SQL.cbtCheckUserRestrictions(login_list=('test login','ddd',), callback=printSqlRez)
        self.I.SQL.cbtCheckIpAllowances(ip="127.0.0.1", callback=printSqlRez)

        info("--------------- LoopTest setUp done ---------------")


    ## ждем пока у test_obj не появится атрибут (поле, ключ) "reply", или пока не истекут max_sleep секунд
    def waitAsyncReply(self, test_obj, max_sleep=0.3):
        start = time.time()
        while not getattr(test_obj, "reply", None):
            time.sleep(0.001)
            if time.time() - start > max_sleep:
                log("waitAsyncReply TIMEOUT [%.3f sec]" % max_sleep)
                raise

    def makeAction(self, classOf, **kwargs):
        return TestDictAction(dict(**kwargs), classOf, request=self) # MC, SQL и прочие интерфейсы забирайте прямо у нашего класса

    ## аккуратно прибиваем всю машинерию (ioloop, memcache/sql thread pools)
    def tearDown(self):
        logLevel()  # отдельные тесты могут ставить свой уровень logging; возвращаем дефолтный...

        info("--------------- LoopTest tearDown start ---------------")
        # пометить наш "якобы web-сервер" как "якобы offline":
        self.I.SQL.removeServer(options.server_name)
        # time.sleep(0.1) # пусть команда уйдет в sql, и даже ответ разберется ioloop-ом

        resetGlobals() # между наборами тестов чистим глобальные серверные синглтоны (logins, users, peers)
        self.I.SQL.fadeout() # мягко завершаем рабочий thread pool (дожидаемся, пока очистятся очереди)
        self.I.MC.destroy() # убиваем рабочий thread pool, чистим очереди

        # SQL.fadeout делаем асинхронно (syncWait=0), а здесь (синхронно) подождем, проследим как SQL мягко закроется и ioloop заберет его pending ответы
        self.I.SQL.fadeout(syncWait=2.0)
        log("self.I.SQL.isDone")

        self.loop.stop() # прибиваем IOLoop, после этого должна закрыться и ioloopThread tornado IOLoop

        t0 = time.time()
        while self.loop._stopped: # ждем пока IOLoop закончит текущую итерацию и действительно остановится
            time.sleep(0.001)
            if time.time() - t0 > 1:
                raise

        info("--------------- LoopTest tearDown done ---------------")


    # ------------
    # helper
    def assertModelChangeFormat(self, model_changes):
        for event in model_changes:
            self.assert_(event and isinstance(event, dict))
            for comment, change_list in event.iteritems():
                self.assert_(comment and isinstance(comment, basestring))
                self.assert_(change_list and isinstance(change_list, list))
                for change_line in change_list:
                    self.assert_(change_line and isinstance(change_line, list) and len(change_line)==3)
                    path, op, values = change_line
                    assert(path and isinstance(path, basestring))
                    assert(op and isinstance(op, basestring) and (op in CHANGE_OP_CODES))

                    if op in ['init', 'add', 'upd']:
                        assert(values and (isinstance(values, dict)))
                    elif op == "del":
                        assert(values and (isinstance(values, int) or isinstance(values, basestring)))
                    elif op == "swap":
                        assert(values and isinstance(values, list) and len(values)==2)


def main():
    DEFAULT_LOG_LEVEL = logging.INFO
#     DEFAULT_LOG_LEVEL = logging.ERROR

    suite = unittest.TestSuite()
    suite.addTest(MysqlIsqlTest('setUp'))
    #suite.addTest(MysqlIsqlTest('tearDown'))
    runner = unittest.TextTestRunner()
    runner.run(suite)

if __name__ == "__main__":
    main()
    #unittest.main()
