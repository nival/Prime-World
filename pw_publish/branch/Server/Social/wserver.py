# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import gc
from base.helpers import *
from tornado.options import define, options
import imemcache  # saveUserData использует CasS/AddS

#from base.http_dumb import httpClientRequest

from isql import main_sql_callback, info_sql_callback
from imemcache import main_memc_callback

# затаскиваем все web request handlers (основные и "расширенные")
from handlers import *  # JsonHandler, SubAction, IfaceFactory
from ifactory import IfaceFactory
from whandler import WebJsonHandler
from iwebserver import ITornadoServer, WS_MAX_TICK_TIME
from iuserdata import IUserDataManager

# служебные web handlers типа Login импортируем отдельно
from ext_main.login import LoginAction, LogoutAction, make_login_unlock
from ext_main.auth import AuthAction
from ext_main.ccu import CCUAction
from ext_main.test_guild import TestGuildAction
from ext_main.change_user_acc import ChangeUserAccAction
from ext_main.gender import SetGenderAction
from ext_main.nickname import SetNicknameAction
from ext_main.set_geolocation import SetGeoLocationAction
from ext_main.touch import TouchAction
from ext_main.inc_save import IncSaveAction
from ext_main.pseudo_delete_account import PseudoDeleteAccountAction

from sublogin import SubloginActionBase

from modeldata.persistent_data import PersistentDataManager, TAIL_MARKER, TAIL_MARKER_LEN, TAIL_MARKER_RECORD_LEN
from modeldata.ModelData import ModelData

import EC
import CC

import pwaccount
import pwaccount_data_manager


class WorkServer(ITornadoServer):

    # _Interfaces = dict( SUBADDR=None, WS=None, MC=None, SQL=None, HTTP=None,
    # DATA=None, MD=None ) #  AGG=None,

    MAX_USER_SAVE_TIME = 600.0  # если за 10 минут так и не удалось сохранить юзера в монго, признаем поражение и дампим в файл
    SAVE_USER_DATA_RETRY_TIMEOUT = 5.0
    PENDING_SAVE_RETRY_TIMEOUT = 5.0

    # return True if startup enviroment is bad
    @staticmethod
    def checkStartupFail():
        # gc.set_threshold( 500000, 5, 5 ) # пореже, но помощнее плз
        gc.disable()
                   # если совсем отключить, и потом не вызывать gc.collect() -- очевидно, будет накапливаться лишняя память; можно пробовать только "для чистого эксперимента"
        info("gc enabled:%s, thresholds:%s" %
             (gc.isenabled(), str(gc.get_threshold())))
        # gc.set_debug( gc.DEBUG_STATS ) # печатайте статистику garbage
        # collector

        if not options.coordinator:
            fatal(
                "NO COORDINATOR OPTION: either use --coordinator=none to run solo WebServer, or --coordinator=ip:port to run in cluster")
            return True

        if options.coordinator != "none":
            # коннектимся к координатору: сообщаем, что мы запустились, просим разрешения начать работу
            coord_res = httpClientRequest(
                addr=options.coordinator, server="x", params="action=ws_start&name=%s" % options.server_name)
            if coord_res and coord_res.get("ok"):
                info("Connected to coordinator: " + str(coord_res))

                server_id = coord_res.get("sid", 0)

                #tornado 3.4 fix
                if options.__class__.__name__ == "OptionParser":
                    options.server_id = server_id
                else:
                    options["server_id"].set(server_id)

                info("set server_id=%d" % server_id)
            else:
                fatal(
                    "Cannot connect to coordinator (addr:%s)\ncoordinator reply was:%s" %
                    (str(options.coordinator), str(coord_res)))
                return True
        else:
            bad_warn(
                "RUNNING WITHOUT COORDINATOR: no cluster config available.")

    @staticmethod
    def initInterfaces(classOf):
        # --- для начала надо связаться с координатором и получить от него актуальные кластерные настройки для cfg
        coord_res = {}
        if options.coordinator != "none":
            # начали слушать; сообщаем координатору, что готовы принимать http-send'ы на своем порту
            coord_res = httpClientRequest(
                addr=options.coordinator, server="x", params="action=ws_ready&name=%s" % options.server_name)
            if coord_res and coord_res.get("ok"):
                info(
                    "Reported 'ready' state to coordinator: reply " + str(coord_res))
            else:
                return fatal("Cannot report to coordinator (addr:%s)\ncoordinator reply was:%s" % (str(options.coordinator), str(coord_res)))

            #~ ws_peers = coord_res.get("peers") or {}
            # ~ while ws_peers: # координатор индексирует по имени, нам удобнее по server_id; перепакуем..
                #~ name, peer = ws_peers.popitem()
                #~ sid = toint( peer.get("server_id") )
                #~ peer["name"] = name
                #~ self.peers[sid] = ClassDict( peer )
            #~ info( "updated peers:" + str(peers) )

            internal_addr = coord_res.get("int_addr")
            if internal_addr:
                #tornado 3.4 fix
                if options.__class__.__name__ == "OptionParser":
                    options.server_addr = str(internal_addr)
                else:
                    options["server_addr"].set(str(internal_addr))


        if options.coordinator != "none":
            classOf.updateSpecificParamList(
                coord_res, getattr(classOf, "_SPECIFIC_CONFIG_PARAMS", {}), classOf.server_type_name)

        # --- теперь заводим интерфейсы для общения с внешними компонентами (MC, SQL, HTTP)
        iDict = ClassDict()
        iDict.coord_res = coord_res

        cfg.resetMcServers()
        iDict.MC = IfaceFactory.makeMcInterface(
            options.mc, coord_res.get("mc_list"), num_threads=cfg.MEMCACHE_THREADS)
        info("MC interface: " + str(iDict.MC))

        cfg.resetSqlServers()
        iDict.SQL = IfaceFactory.makeSqlInterface(
            options.sql, coord_res.get("sql_list"), num_threads=cfg.SQL_THREADS)
        info("SQL interface: " + str(iDict.SQL))

        iDict.DATA = IfaceFactory.makeIDataInterface(
            options.data, coord_res.get("mongo_list"), iDict.SQL, num_threads=cfg.MONGO_THREADS)
        info("DATA interface: " + str(iDict.DATA))

        # http-клиент для связи с peer-серверами
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient(max_clients=cfg.HTTP_CURL_WORKERS)

        iDict.MD = IUserDataManager()
        info("MD interface: " + str(iDict.MD))

        iDict.PDM = PersistentDataManager(iDict)
        info("PDM interface: " + str(iDict.PDM))

        return iDict

    def __init__(self, **kwargs):
        # inherited
        ITornadoServer.__init__(self, **kwargs)
        info("WS __init__")

        self.timeSqlKeepAlive = self.startTickTime
        self.ACCOUNT_EXPIRE_SECONDS = ACCOUNT_EXPIRE_SECONDS
        self.GUEST_ACCOUNT_EXPIRE_SECONDS = GUEST_ACCOUNT_EXPIRE_SECONDS
        self.PWSOC_VERSION = PWSOC_VERSION

        self.CCU = ClassDict()

        self.auid2uid = {}
        self.pwc = {}
            # TEMP: временно (для теста) заводим еще один набор токенов
            # (специально для pwc_login)

        self.serviceCheckTime = time.time()

        def stub(x, y):
            pass

        self.states = {
            pwaccount.ACC_STATUS_SAVED: self.onAccSaved,
            pwaccount.ACC_STATUS_ACTIVE: self.onAccActive,
            pwaccount.ACC_STATUS_PROCESS_SAVE: stub,
        }



    def initHandlers(self, application):
        # добавляем handlers для реальных запросов (через load balancer, через внутри-кластерный порт, или по прямому имени сервера)
        application.add_handlers(r"(.*)", [
            (r"/", WebJsonHandler, dict(SUBADDR=SUBADDR_BALANCED, I=self.I)),
            (r"/x", WebJsonHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I)),
            (r"/%s" % options.server_name, WebJsonHandler,
             dict(SUBADDR=SUBADDR_SELF, I=self.I)),
            #~ ( r"/", WebJsonHandler, dict(SUBADDR=SUBADDR_BALANCED, WS=self, HTTP=self.HTTP, MC=self.MC, SQL=self.SQL, DATA=self.DATA) ),
            #~ ( r"/x", WebJsonHandler, dict(SUBADDR=SUBADDR_INTERNAL, WS=self, HTTP=self.HTTP, MC=self.MC, SQL=self.SQL, DATA=self.DATA) ),
            #~ ( r"/%s" % options.server_name, WebJsonHandler, dict(SUBADDR=SUBADDR_SELF, WS=self, HTTP=self.HTTP, MC=self.MC, SQL=self.SQL, DATA=self.DATA, MD=self.MD) ),
        ])

        # служебные хэндлеры, типа login/logout
        self.initServiceActions()

    # служебные хэндлеры, типа login/logout
    def initServiceActions(self):
        WebJsonHandler.unloggedActionMap['login'] = LoginAction
        WebJsonHandler.loggedActionMap['auth'] = AuthAction
        WebJsonHandler.loggedActionMap['logout'] = LogoutAction
        WebJsonHandler.loggedActionMap['touch'] = TouchAction
        WebJsonHandler.loggedActionMap['set_nickname'] = SetNicknameAction
        WebJsonHandler.loggedActionMap['set_gender'] = SetGenderAction
        WebJsonHandler.loggedActionMap[
            'set_geolocation'] = SetGeoLocationAction

        WebJsonHandler.loggedActionMap['pseudo_delete_account'] = PseudoDeleteAccountAction

        # admin commands:
        WebJsonHandler.loggedActionMap['ccu'] = CCUAction
        WebJsonHandler.loggedActionMap['change_user_acc'] = ChangeUserAccAction
        WebJsonHandler.loggedActionMap['inc_save'] = IncSaveAction
        WebJsonHandler.unloggedActionMap['test_guild'] = TestGuildAction

    # закончен ли рабочий процесс (по wsShutdown сначала ждем выхода юзеров, завершения обработки incoming requests..)
    def isDoneServer(self):
        return (len(users) <= 0)

    # выполняем действия по финализации состояния (доразбор очередей sql и т.п.);
    # когда совсем готовы умереть, возвращаем True
    def shutdownServerTick(self):
        if self.wsShutdown == self.SHUTDOWN_START:
            info("wsShutdown (SHUTDOWN_START): start billing fadeout")
            self.I.ZZ.fadeout()  # ждем, пока завершатся все запросы к биллингу
            self.tsBillingShutdownStarted = time.time()
            self.wsShutdown = self.SHUTDOWN_BILLING

        elif self.wsShutdown == self.SHUTDOWN_BILLING:
            if self.I.ZZ.isDone():
                info("wsShutdown (SHUTDOWN_BILLING): logout active users")
                # даем юзерам N секунд чтобы свалить
                self.ACCOUNT_EXPIRE_SECONDS = min(
                    self.ACCOUNT_EXPIRE_SECONDS, SHUTDOWN_ACCOUNT_EXPIRE_SECONDS)
                self.GUEST_ACCOUNT_EXPIRE_SECONDS = min(
                    self.GUEST_ACCOUNT_EXPIRE_SECONDS, SHUTDOWN_ACCOUNT_EXPIRE_SECONDS)  # включая и guest юзеров тоже
                self.tsUsersShutdownStarted = time.time()

                # есть нюанс: некоторые юзеры (например, возвращающиеся из pvx) могут ставить себе acc.ka в будущее, чтобы их не трогали определенное время; нужно зачистить такие ka
                if users:
                    corrected_ka = self.tsUsersShutdownStarted - SHUTDOWN_ACCOUNT_EXPIRE_SECONDS + 1
                    for id, acc in users.iteritems():
                        if acc:
                            last_keep_alive = acc.get("ka", 0)
                            if last_keep_alive > self.tsUsersShutdownStarted:
                                info("wsShutdown user(SHUTDOWN_BILLING) user id=%s, auid=%s: last_keep_alive in future (%s), setting corrected_ka (%s)", id,
                                     acc.auid, last_keep_alive, corrected_ka)
                                acc.ka = corrected_ka

                self.wsShutdown = self.SHUTDOWN_USERS
            else:
                info("wsShutdown (SHUTDOWN_BILLING): waiting for billing fadeout (%d)...", toint(time.time() - self.tsBillingShutdownStarted))

        elif self.wsShutdown == self.SHUTDOWN_USERS:
            # if self.tsUsersShutdownStarted + SHUTDOWN_ACCOUNT_EXPIRE_SECONDS
            # + 1 < time.time():

            self.shutdownUsers(users.keys())

            if len(users) <= 0:
                info("wsShutdown (SHUTDOWN_USERS): fadeout databases")
                # постепенно закрываем лавочку (ждем когда очередь запросов полностью разберут, и тогда прибиваем thread pool)
                self.I.SQL.fadeout()
                self.I.DATA.fadeoutData()
                self.tsDatabaseShutdownStarted = time.time()
                self.wsShutdown = self.SHUTDOWN_SQL
            else:
                info("wsShutdown (SHUTDOWN_USERS): waiting for users logout (%d)...",toint(time.time() - self.tsUsersShutdownStarted))

        elif self.wsShutdown == self.SHUTDOWN_SQL:
            if self.I.SQL.isDone() and self.I.DATA.isDoneData():
                info("wsShutdown: sql & mongo done, stopping io loop")
                return True
            else:
                info("wsShutdown (SHUTDOWN_BILLING): waiting for sql/mongo fadeout (%d)...", toint(time.time() - self.tsDatabaseShutdownStarted))

    def shutdownUsers(self, keys):

        if not self.shutdown_process:
           self.shutdown_process = self.SHUTDOWN_USERS_PROCESS
        else:
            return

        info("shutdownUsers.wsShutdown (SHUTDOWN_USERS_PROCESS): %r", keys)

        for id in keys:
            acc = users.get(id)
            debug("shutdownUsers.wsShutdown user id=%r status=%r", id, acc.acc_status)
            if acc.acc_status == pwaccount.ACC_STATUS_SAVED: # на случай, если в кипэлайве чего то не сохранили, но статус поменяли
                self.onAccSaved(acc, id)
            elif acc.acc_status == pwaccount.ACC_STATUS_ACTIVE:
                if not getattr(acc,"isTutorialAccount", False):
                    _callback = functools.partial(self.onAccActiveCallback, id, acc)
                    self.onAccActive(acc, id,  _callback)
                else:
                    self.throwOutTutorialAcc(acc, id)

    def onAccActiveCallback(self, id, acc):
        info("onAccActiveCallback for acc[%d]", id)
        if acc.acc_status == pwaccount.ACC_STATUS_SAVED:
            self.onAccSaved(acc, id)
            info("onAccActiveCallback FINAL-SAVE for acc[%d] is completed!", id)

    def saveUserData(self, *args, **kwargs):
        kwargs['server_instance'] = self
        args = list(args)

        if 'uid' in kwargs:
            return pwaccount_data_manager.UserAccountDataManager.save_by_uid(*args, **kwargs)
        elif type(args[0]) == pwaccount.UserAccount:
            acc = args.pop(0)
            return pwaccount_data_manager.UserAccountDataManager(acc).save(*args, **kwargs)
        else:
            warn('saveUserData: first param of type {0}'.format(str(type(args[0]))))

    def fadeoutServer(self, **kwargs):
        ITornadoServer.fadeoutServer(self, **kwargs)

    def onTTL(self, data):
        pass

    # служебная фигня типа замеров времени, перевешивания таймеров, проверки shutdownServer -- делается в родительском _tick
    # здесь только полезная нагрузка:
    def tick(self):
        # ---- (1) выкинем протухшие аккаунты (keep alive более чем N минут назад)
        try:
            t0 = time.time()

            keys = users.keys()

            if t0 > self.serviceCheckTime:
                self.serviceCheckTime = t0 + CC.SERVICE_ALIVE_SET_PERIOD

                # заодно посчитаем общее кол-во юзеров (и отдельно guest-ов), и кол-ва юзеров по отдельным локалям
                self.CCU.userCount = 0
                self.CCU.guestCount = 0
                self.CCU.localeCounts = {}
                self.CCU.muidCounts = {}
                self.CCU.ruidCounts = {}
                # посчитаем кол-во юзеров (и отдельно guest-ов)
                for id in keys:
                    acc = users.get(id)
                    if acc:
                        if acc.login.startswith("guest:"):
                            self.CCU.guestCount += 1
                        else:
                            self.CCU.userCount += 1
                            if acc.locale:
                                self.CCU.localeCounts[acc.locale] = self.CCU.localeCounts.get(acc.locale, 0) + 1
                        muid = acc.db.muid
                        ruid = acc.db.ruid
                        if not muid or muid not in cfg.META_MUIDS:
                            muid = CC.OTHER_MUID
                        self.CCU.muidCounts[muid] = self.CCU.muidCounts.get(muid, 0) + 1
                        self.CCU.ruidCounts[ruid] = self.CCU.ruidCounts.get(ruid, 0) + 1
                        # обновляем статус "юзер живой, клиент запущен"
                        self.updateKeepaliveState(acc, online=False, now=t0)

                svc_name = '%s.%s' % (options.server_name, options.server_id)

                pipe = self.I.REDIS.pipeline()

                pipe.zadd('svcs/ttls', time.time()+CC.SERVICE_ALIVE_TTL, svc_name)

                key_name = 'svc/' + svc_name + '/ccu/total'
                pipe.delete(key_name)
                pipe.hset(key_name, 'guest', self.CCU.guestCount)
                pipe.hset(key_name, 'user', self.CCU.userCount)
                pipe.expire(key_name, CC.SERVICE_ALIVE_TTL*2)

                key_name = 'svc/' + svc_name + '/ccu/locale'
                pipe.delete(key_name)
                for locale, count in self.CCU.localeCounts.items():
                    pipe.hset(key_name, locale, count)
                pipe.expire(key_name, CC.SERVICE_ALIVE_TTL*2)

                key_name = 'svc/' + svc_name + '/ccu/muid'
                pipe.delete(key_name)
                for muid, count in self.CCU.muidCounts.items():
                    pipe.hset(key_name, muid, count)

                pipe.expire(key_name, CC.SERVICE_ALIVE_TTL*2)

                key_name = 'svc/' + svc_name + '/ccu/ruid'
                pipe.delete(key_name)
                for ruid, count in self.CCU.ruidCounts.items():
                    pipe.hset(key_name, ruid, count)

                pipe.expire(key_name, CC.SERVICE_ALIVE_TTL*2)

                pipe.execute(self.onTTL)

            debug("self.wsShutdown=%r, self.checkExpireAccount(%r, %r) ", self.wsShutdown, keys, t0)
            if not self.wsShutdown:
                self.checkExpireAccount(keys, t0)

        except:
            catch()

        # статистика: посчитаем кол-во юзеров (и отдельно guest-ов)
        self.CCU.peakUserCount = max(self.CCU.userCount, toint(self.CCU.peakUserCount))
        self.CCU.peakGuestCount = max(self.CCU.guestCount, toint(self.CCU.peakGuestCount))

        SEC = toint(t0)

        if SEC % 10 == 0:
            # раз в 10 секунд: дампим статистику юзеров
            info("CCU: %s" % str(self.CCU))

        # garbage collection
        self.gcTick()

        #Чтобы не писать тайминги по несколько раз, если tick успевает
        if SEC % 60 == 0 and self.lastInstrumentedAction + 10 < SEC:
            # раз в минуту: дампим средние времена исполнения всех action и апдейтим общую статистику
            self.updateInstrumentedActions()
            self.lastInstrumentedAction = SEC

        # (2) время от времени надо делать keepalive для всех sql-коннектов
        t1 = time.time()
        if options.sql == "async":
            if t1 - self.timeSqlKeepAlive > options.sql_keep_alive_seconds:
                info("sql keepalive: %5.3f" % t1)
                self.I.SQL.keepAlive()
                self.timeSqlKeepAlive = t1

    def throwOutTutorialAcc(self, acc, uid, callback=None):
        login = acc.login.lower()
        info("throwOutTutorialAcc , auid=%r uid=%r login=%r", acc.auid, uid, login)
        self.I.WS.removeUserAccount(acc, uid)
        if not callback:
            callback = info_sql_callback
        self.I.SQL.logout( login, toint(options.server_id), callback)

    def checkExpireAccount(self, keys, t0):
        for id in keys:
            acc = users.get(id)
            if acc:
                last_keep_alive = acc.get("ka")

                acc_timeout = self.ACCOUNT_EXPIRE_SECONDS
                if acc.guest:
                    acc_timeout = self.GUEST_ACCOUNT_EXPIRE_SECONDS

                debug("acc.wait_inform_user == %r", acc.wait_inform_user)
                if acc.wait_inform_user == False:
                    self.removeUserAccount(acc, id)
                    continue

                debug("%r + %r < %r", last_keep_alive, acc_timeout, t0 )
                if last_keep_alive + acc_timeout < t0:
                    debug("acc.acc_status == %r", acc.acc_status )
                    try:
                        # выкидываем
                        if acc.acc_status == pwaccount.ACC_STATUS_SAVED:
                            if acc.finalize_data and (not acc.pend_data_load) and (not acc.pend_data_save):
                                # сохранение подтверждено, pending-операций нет, можно удалять
                                info("DELETING EXPIRED acc[%d], login=%r: ka %0.2f, now %0.2f", id, acc.login, last_keep_alive, t0)
                                self.onAccSaved(acc, id)
                            else:
                                err("WTF? acc.acc_status == pwaccount.ACC_STATUS_SAVED but not really saved! finalize[%s]: auid=%s, finalize_tm=%s, finalize_data=%s, pend_data_load=%s, pend_data_save=%s",
                                     id, acc.auid, acc.finalize_tm, acc.finalize_data, acc.pend_data_load, acc.pend_data_save )

                        elif acc.acc_status == pwaccount.ACC_STATUS_ACTIVE:
                            debug("checkExpireAccount: acc.model %r", type(acc.model))
                            if not getattr(acc, "isTutorialAccount", False) and isinstance(acc.model, ModelData) and acc.model.isTutorialComplete():
                                self.onAccActive(acc, id)
                                t1 = time.time()
                                if t1 > t0 + WS_MAX_TICK_TIME:
                                    # хватит, многовато времени уже потратили на "финальные сохранения" в процессе этого тика
                                    info("skipping the rest of tick (%.3f spent)", t1 - t0)
                                    break
                            else:
                                self.throwOutTutorialAcc(acc, id)
                                break
                        else:
                            info("waiting for acc_status == ACC_STATUS_SAVED, finalize[%s]: auid=%s, finalize_tm=%s, finalize_data=%s, pend_data_load=%s, pend_data_save=%s",
                                  id, acc.auid, acc.finalize_tm, acc.finalize_data, acc.pend_data_load, acc.pend_data_save)
                    except:
                        catch()


    def onAccActive(self, acc, id, _callback=None):
        info("FINAL-SAVE for acc[%d]", id)
        try:
            # Обработка перед сохранением
            self.I.WS.onBeforeFinalDataSave(acc)
            # запускаем финальное сохранение
            acc.setAccStatusProcessSave()
            self.saveUserData(acc, final=True, callback=_callback)
        except:
            catch()

    def onAccSaved(self, acc, id):
        debug("onAccSaved for acc[%d]", id)
        # сохранение подтверждено, pending-операций нет, можно удалять
        login = acc.login
        # освобождаем лок в SQL
        _logout_callback = info_sql_callback
        if self.wsShutdown and self.wsShutdownReloginUsers:
            #  в процессе "разгрузочного shutdown" пытаемся перелогинить всех активных юзеров на соседние WS
            _logout_callback = functools.partial(self.onShutdownSqlLogout, snid=acc.db.snid, snuid=acc.db.snuid)

        self.I.SQL.logout( login, toint(options.server_id), _logout_callback)

        if not options._dont_log:
            nick = acc.getNickname()
            self.I.STATS.addLogout(acc.auid, nick, options.server_name)

        self.I.WS.onUserLogout(acc)  # OVERRIDE чтобы обработать кастомную логику logoff

        if not acc.wait_inform_user or self.wsShutdown:
            try:  # с заглушками (--mc=none, --sql=none) бывают дубликаты логинов
                l = login.lower()
                if l in logins:
                    logins.pop(l)
                for action in repeated_requests:
                    if l in repeated_requests[action]:
                        repeated_requests[action].pop(l)
            except:
                catch()

            self.I.AGG.logout(acc.auid)

            self.unregisterAuid(acc.auid)
            if id in users:
                users.pop(id)
            del acc

    def removeUserAccount(self, acc, id):
        try:  # с заглушками (--mc=none, --sql=none) бывают дубликаты логинов
            l = acc.login.lower()
            logins.pop(l)
            for action in repeated_requests:
                if l in repeated_requests[action]:
                    repeated_requests[action].pop(l)
        except:
            catch()

        self.I.AGG.logout(acc.auid)

        self.unregisterAuid(acc.auid)
        if id in users:
            users.pop(id)
        del acc


    def onShutdownSqlLogout(self, sql_response, snid="", snuid=""):
        info("onShutdownSqlLogout(snid=%s, snuid=%s) sql_response: %s" %
             (snid, snuid, sql_response))
        # для начала кинем через балансер обычный пинг; если какая-нибудь peer WS на него ответит, попробуем перелогинить туда нашего юзера
        args = dict(action="l_ping", auid=0)
        _callback = functools.partial(
            self.onShutdownPingResponse, snid=snid, snuid=snuid)
        self.I.WSX.fetch(
            cfg.BALANCER_EXTERNAL, args, _callback, subrequest="")

    def onShutdownPingResponse(self, peer_response, snid="", snuid=""):
        if peer_response:
            info(
                "onShutdownPingResponse(snid=%s, snuid=%s) peer_response: %s" %
                (snid, snuid, peer_response))
            peer_name = peer_response.get("server")
            if peer_name:
                # ага, кто-то из соседей нам ответил; пробуем залогинить к нему нашего юзера
                peer = self.getPeerServerByName(peer_name)
                if peer:
                    args = dict(action="sublogin_fsn", snid=snid, snuid=snuid)
                    _callback = functools.partial(
                        self.onShutdownSubloginResponse, snid=snid, snuid=snuid, peer_name=peer_name)
                    self.I.WSX.fetch(
                        peer.addr, args, _callback, subrequest="x")
                else:
                    warn("onShutdownPingResponse: can't find peer by name=%r" %
                         peer_name)
            else:
                warn("onShutdownPingResponse: no server name in response")
        else:
            warn(
                "BAD onShutdownPingResponse(snid=%s, snuid=%s) peer_response: %s" %
                (snid, snuid, peer_response))

    def onShutdownSubloginResponse(self, response, **kwargs):
        info("onShutdownSubloginResponse(%s): response %s" %
             (kwargs, response))

    # VIRTUAL: OVERRIDE чтобы отработать кастомную логику logoff
    def onUserLogout(self, acc):
        pass

    def onBeforeFinalDataSave(self, acc):
        pass


    # после того как нам пришли "persistent данные юзера" (все равно каким путем), надо их разобрать (из json-формата) и вписать юзеру на аккаунт
    def onUserData(self, acc, data_string):
        try:
            # добавим callback, который сохранит данные аккаунта обратно в persistent
            acc.on_loaded_callbacks = acc.on_loaded_callbacks or []
            acc.on_loaded_callbacks.append(self.onUserDataLoadedCallback)

            self.I.PDM.loadAccountData(acc, data_string)
        except Exception:
            catch()
            warn("onUserData acc failed (uid=%s)" % acc.uid)
            acc.failed = 1

    def checkGiveBonusTalents(self, acc):
        info("checkGiveBonusTalents: auid=%s, sn_count=%s, sn_count_prev=%s" %
             (acc.auid, acc.sn_count, acc.sn_count_prev))
        # если за отчетный период на аккаунте прибавилось соц.сетей (зарегистрированных в аггрегаторе), нужно выдать бонусные таланты
        if acc.auid and acc.sn_count and (acc.sn_count > acc.sn_count_prev) and not acc.getConfig().TournamentSettings.IS_TOURNAMENT_SERVER:
            info("give bonus talents to auid=%s" % acc.auid)
            bonus_networks = []
            if isinstance(acc.new_networks, list):
                for networkId in acc.new_networks:
                    if networkId in CC.BONUS_SOCIAL_NETWORK_NAMES:
                        bonus_networks.append(networkId)
            for i in xrange(acc.sn_count_prev, acc.sn_count):
                acc.model.giveBonusTalent( i+1, bonus_networks, acc.getConfig(), acc, self.I )
            self.I.AGG.setProperty( acc.auid, CC.SN_BONUS_PROPERTY, acc.sn_count )
            acc.sn_count_prev = acc.sn_count
            # еще нужно достать login token, и там тоже поправить
            user = self.I.WS.setSnBonusCount(
                acc.auid, acc.sn_count, acc.sn_count, acc.new_networks)
            if isinstance(acc.new_networks, list):
                for networkId in acc.new_networks:
                    self.I.AGG.deleteSnNewState( acc.auid, networkId )

    def onUserDataLoadedCallback(self, acc):
        # self.saveUserData( acc ) -- можно не сохранять сразу после загрузки;
        # при нынешнем механизме все равно пофейлится на acc.locked==1
        self.onUserLoadFinished(acc)

    # всякие нужные пост-действия, которые обычно выполняются после загрузки ModelData
    def onUserLoadFinished(self, acc):
        pass

    # DATA-хранилище присылает "persistent данные юзера" (видимо, только что
    # залоганного к нам на сервер)
    def onUserPersistentData(self, data_reply):
        if data_reply:
            uid, retry_count = data_reply.get("p")
        else:
            uid, retry_count = 0, 0

        acc = users.get(uid)
        info("onUserPersistentData[%d]: %s\n user acc: %s" %
             (uid, str(data_reply)[:1024], str(acc)[:256]))
        if acc:
            if acc.pend_data_load > 0:
                acc.pend_data_load -= 1
            else:
                warn("Trying to load data, but acc.pend_data_load will be < 0 for uid=%d", uid)
            try:
                data_json = data_reply["r"]["data"] or "{}"
            except Exception:
                data_json = "{}"

            mongo_error = data_reply.get("e")
            if not mongo_error:
                try:
                    self.onUserData(acc, data_json)
                except Exception:
                    log("bad onUserPersistentData reply")
            else:
                warn(
                    "mongo auto-reconnect acc failed: mongo error for uid=%s, retry_count=%s, pend_data_load=%s" %
                    (uid, retry_count, acc.pend_data_load))
                if (retry_count < CC.MONGO_READ_RETRY_COUNT):
                    retry_count += 1
                    acc.pend_data_load += 1
                    info("retrying mongo read for uid=%s, retry_count=%s" %
                         (uid, retry_count))
                    self.I.DATA.loadAndStampData(
                        acc.login, acc.pers_key, options.server_id, self.onUserPersistentData, params=(uid, retry_count))
                else:
                    acc.failed = 1

    #~ def onUserBillingStatus(self, response, auid=-1):
        #~ info( "onUserBillingStatus: auid=%s, response=%s" % (auid, response) )
    def initBilling(self, auid):
        pass

    def getUserAccSN(self, snid, snuid):
        login = "%s#%s" % (snid, snuid.lower())
        return self.getUserAcc(login)

    def getUserAcc(self, login):
        uid = logins.get(login.lower(), 0)
        if uid:
            return users.get(uid)

    def getIOLoop(self):
        return tornado.ioloop.IOLoop.instance()

    def registerAuid(self, auid, uid):
        self.auid2uid[auid] = uid

    def unregisterAuid(self, auid):
        self.auid2uid.pop(auid, None)

    def getUserAccByAuid(self, auid):
        if auid:
            uid = self.auid2uid.get(auid)
            if uid:
                return users.get(uid)

    def serverSubLogin(self, login, sublogin_callback=None, persistent_callback=None, auid=0):
        login = login.lower()
                            # safeguard на случай получения кривых upcase
                            # логинов
        info("serverSubLogin: login=%s, sublogin_callback=%s, persistent_callback=%s", str(login), str(sublogin_callback), str(persistent_callback))
        subloginAction = SubloginActionBase({}, None, self)
        subloginAction.subLogin( login, login_callback=sublogin_callback, persistent_callback=persistent_callback, auid=auid)


if __name__ == "__main__":
    ITornadoServer.main(WorkServer)
