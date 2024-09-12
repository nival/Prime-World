# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
sys.path.append(os.path.abspath('cfg'))
import zlib, bz2
import gc
from base.wstools import AddLoopCallback, RemoveLoopCallback
import tornado.options
from tornado.options import define, options

import imemcache # saveUserData использует CasS/AddS

from base.http_dumb import *

from isql import main_sql_callback
from imemcache import main_memc_callback

##----------------------------------------------------------------------------------------------------------------------
## затаскиваем все web request handlers (основные и "расширенные")
from handlers import * # JsonHandler, IfaceFactory
from ifactory import IfaceFactory
from whandler import WebJsonHandler
from iwebserver import ITornadoServer, WS_MAX_TICK_TIME, ICSVActionTimingWriter
from iuserdata import IDataManager #from iuserdata import IUserDataManager

##----------------------------------------------------------------------------------------------------------------------
## служебные web handlers типа Login импортируем отдельно
sys.path.append('ext_main')
from ext_main.ccu import CCUAction
from ext_main.x_login import XLoginAction, XLogoutAction
from ext_main.x_actions import XSendAction, XSendNoLoginAction, XReceiveAction, XPurgeAction, XSendToFriendsAction
from ext_main.touch import TouchAction

import EC
import CC

MARKER_FILENAME = ''

# можно вынести в отдельный x_version.py
XS_VERSION_HIGH = 0
XS_VERSION_MED = 0
XS_VERSION_LOW = 0
XS_VERSION_REVISION = 0
XS_BRANCH_NAME = "trunk"

XS_SERVER_VERSION = "%s.%s.%s.%s.%s" % (XS_VERSION_HIGH, XS_VERSION_MED, XS_VERSION_LOW, XS_VERSION_REVISION, XS_BRANCH_NAME)

XSERVER_ACCOUNT_EXPIRE_SECONDS = 2*60*60 # 2 часа после login/receive

# -------------------------------------------------------------------------------------------------------
# -------------------------------------------------------------------------------------------------------

class XWebJsonHandler( WebJsonHandler ):
    """ пока всё чем мы отличаемся -- это параметром запроса method=<action> (ну и приемом сообщений через HTTP POST наряду с GET) """

    ## main http request mapper (раскидываем запросы по handler methods/classes, в зависимости от "/subaddr" и "action=")
    @tornado.web.asynchronous
    def get(self):
        method = self.getParam("method")
        if method:
            self.addArguments( action=method )
        return WebJsonHandler.get( self )

    ## main http request mapper (раскидываем запросы по handler methods/classes, в зависимости от "/subaddr" и "action=")
    @tornado.web.asynchronous
    def post(self):
        method = self.getParam("method")
        if method:
            self.addArguments( action=method )
        return WebJsonHandler.get( self )


    def fail(self, message, code):
        warn("%s action fail: ec=%s, message=%s", getattr(self, "action", ""), code, message)
        self.response["error"] = message
        self.response["ec"] = code
        self.fin()

    def onCoordinatorCheck(self):
        log("onCoordinatorCheck")
        self.response["session_awards"] = self.I.WS.CCU.session_awards
        self.response["s_guild_awards"] = self.I.WS.CCU.s_guild_awards
        super(XWebJsonHandler, self).onCoordinatorCheck()

    ##-------------------------------------------------------------------------------------
    ## общая обертка для пользовательских команд (требующих наличия активной сессии)
    ##   со стандартными проверками "залоганности юзера" (uid, key)
    def onLoggedAction(self):
        self.sid = self.getIntParam("sid", 0)
        if self.sid:
            info("onLoggedAction sid: %r", self.sid)
            self.acc = users.get(self.sid)
            if self.acc:
                self.auid = self.getIntParam("auid", 0)
                if self.auid:
                    if self.auid == self.acc.auid:
                        ## if not acc.failed: if not acc.locked: if not acc.db.banned:
                        touch( self.acc ) # продлеваем активную жизнь юзера на сервере

                        try:
                            ## method_name = loggedActionMap[self.action]
                            ActionClass = self.loggedActionMap[self.action]
                            actionHandler = ActionClass( self.request.arguments, self.async_callback( self.scheduleFinalize ), self )
                            return actionHandler.onStart()
                        except Exception:
                            catch()
                            self.response["error"] = printException(sys.exc_info())
                            return self.fin()

                    else:
                        return self.fail("wrong session auid, relogin", EC.XS_BAD_SESSION_AUID)
                else:
                    return self.fail("bad auid", EC.XS_BAD_AUID)
            else:
                return self.fail("no such session", EC.XS_NO_SESSION)
        else:
            return self.fail("bad session id", EC.XS_BAD_SESSION_ID)


# -------------------------------------------------------------------------------------------------------
# -------------------------------------------------------------------------------------------------------

class XchangeWorkServer( ICSVActionTimingWriter, ITornadoServer ):
    server_type_name = "xs"

    MAX_USER_SAVE_TIME = 30.0
    SAVE_USER_CACHE_RETRY_TIMEOUT = 3.0
    SAVE_USER_DATA_RETRY_TIMEOUT = 5.0
    SAVE_USER_RETRY_TIMEOUT = 3.0
    MAX_COUNT_TRY_PUSH = 100
    TIMEOUT_TRY_PUSH = 20

    # -------------------------------------------------------------------------------------------------------
    _SPECIFIC_CONFIG_PARAMS = {
        "curl_wrk":  "HTTP_CURL_WORKERS",
        "curl_conn": "HTTP_CURL_CONNECTIONS",
        "curl_wrk":  "HTTP_CURL_WORKERS",
        "sql_trd":   "SQL_THREADS",
        "events":    "EVENT_SERVICES",
        "friends_svc": "FRIEND_SERVICES",
        "guild_svc": "GUILD_SERVICES",
    }

    # -----------------------------------------------
    @staticmethod
    def initOptions():
        #tornado 3.4 fix
        if options.__class__.__name__ == "OptionParser":
            options.port = 8811
            options.coordinator = "127.0.0.1:8701"
            options.server_name ="ein"
            options.server_class = "xs"
        else:
            options["port"].set(8811)
            options["coordinator"].set("127.0.0.1:8701")
            options["server_name"].set("ein")
            options["server_class"].set("xs")

    # -----------------------------------------------
    # return True if startup enviroment is bad
    @staticmethod
    def checkStartupFail():
        ## gc.set_threshold( 500000, 5, 5 ) # пореже, но помощнее плз
        gc.disable() # если совсем отключить, и потом не вызывать gc.collect() -- очевидно, будет накапливаться лишняя память; можно пробовать только "для чистого эксперимента"
        info("gc enabled:%s, thresholds:%s", gc.isenabled(), str(gc.get_threshold()))
        ## gc.set_debug( gc.DEBUG_STATS ) # печатайте статистику garbage collector

        if not options.coordinator:
            fatal( "NO COORDINATOR OPTION: either use --coordinator=none to run solo WebServer, or --coordinator=ip:port to run in cluster")
            return True

        coord_res = {}
        if options.coordinator != "none":
            # коннектимся к координатору: сообщаем, что мы запустились, просим разрешения начать работу
            coord_res = httpClientRequest( addr=options.coordinator, server="x", params="action=ws_start&name=%s" % options.server_name )
            if coord_res and coord_res.get("ok"):
                info("Connected to coordinator: %s", coord_res)

                server_id = coord_res.get("sid", 0)

                #tornado 3.4 fix
                if options.__class__.__name__ == "OptionParser":
                    options.server_id = server_id
                else:
                    options["server_id"].set(server_id)

                info("set server_id=%d", server_id)
            else:
                fatal( "Cannot connect to coordinator (addr:%s)\ncoordinator reply was:%s" % ( str(options.coordinator), str(coord_res) ) )
                return True
        else:
            bad_warn( "RUNNING WITHOUT COORDINATOR: no cluster config available." )


    # -----------------------------------------------
    @staticmethod
    def initInterfaces( classOf ):
        # заводим файл-маркер того, что мы живы
        curDir = os.getcwd()
        global MARKER_FILENAME
        MARKER_FILENAME = curDir + "/logs/xs.running.%s" % options.server_name
        success("creating marker file %r" % MARKER_FILENAME)
        f = open( MARKER_FILENAME, "w" )
        f.close()

        # --- надо связаться с координатором и получить от него актуальные кластерные настройки для cfg
        coord_res = {}
        if options.coordinator != "none":
            # начали слушать; сообщаем координатору, что готовы принимать http-send'ы на своем порту
            coord_res = httpClientRequest( addr=options.coordinator, server="x", params="action=ws_ready&name=%s" % options.server_name )
            if coord_res and coord_res.get("ok"):
                info("Reported 'ready' state to coordinator: reply %s", coord_res)
            else:
                return fatal( "Cannot report to coordinator (addr:%s)\ncoordinator reply was:%s" % ( str(options.coordinator), str(coord_res) ) )

            #~ ws_peers = coord_res.get("peers") or {}
            #~ while ws_peers: # координатор индексирует по имени, нам удобнее по server_id; перепакуем..
                #~ name, peer = ws_peers.popitem()
                #~ sid = toint( peer.get("server_id") )
                #~ peer["name"] = name
                #~ self.I.WS.peers[sid] = peer
            #~ info( "updated peers:" + str(self.I.WS.peers) )

            internal_addr = coord_res.get("int_addr")
            if internal_addr:
                #tornado 3.4 fix
                if options.__class__.__name__ == "OptionParser":
                    options.server_addr = str(internal_addr)
                else:
                    options["server_addr"].set(str(internal_addr))

        if options.coordinator != "none":
            classOf.updateSpecificParamList( coord_res, getattr(classOf, "_SPECIFIC_CONFIG_PARAMS", {}), classOf.server_type_name )

        # --- теперь заводим интерфейсы для общения с внешними компонентами (MC, SQL, HTTP)
        iDict = ClassDict()
        iDict.coord_res = coord_res

        cfg.resetSqlServers()
        iDict.SQL = IfaceFactory.makeSqlInterface( options.sql, coord_res.get("sql_list"), num_threads=cfg.SQL_THREADS )
        info("SQL interface: %s", iDict.SQL)

        # http-клиент для связи с peer-серверами
        iDict.HTTP = tornado.httpclient.AsyncHTTPClient( max_clients=cfg.HTTP_CURL_WORKERS )

        # обычным веб-серверам требуется только оболочка DataManager для заворачивания JSON-данных
        iDict.MD = IDataManager()
        info("MD interface: %s", iDict.MD)

        iDict.WSX = IfaceFactory.makeIPeerWebServerInterface( options.wsx, HTTP=iDict.HTTP )
        info("WSX interface: %s", iDict.WSX)

        iDict.GS = IfaceFactory.makeGuildServiceInterface(options.guilds, cfg.GUILD_SERVICES, HTTP=iDict.HTTP)
        info("GuildService interface: %s", iDict.GS)

        iDict.FS = IfaceFactory.makeFriendServiceInterface(options.friends, cfg.FRIEND_SERVICES, HTTP=iDict.HTTP)
        info("FriendServiceInterface interface: %s", iDict.FS)

        return iDict


    # -----------------------------------------------
    def __init__(self, **kwargs):
        # inherited
        ITornadoServer.__init__(self, **kwargs)
        info("WS __init__")

        self.timeSqlKeepAlive = self.startTickTime
        self.ACCOUNT_EXPIRE_SECONDS = XSERVER_ACCOUNT_EXPIRE_SECONDS
        self.GUEST_ACCOUNT_EXPIRE_SECONDS = GUEST_ACCOUNT_EXPIRE_SECONDS
        self.SERVER_VERSION = XS_SERVER_VERSION
        self.SHUTDOWN_ACCOUNT_EXPIRE_SECONDS = 1

        self.CCU = ClassDict()
        self.CCU.session_awards = 0
        self.CCU.s_guild_awards = 0


    # -----------------------------------------------
    def initHandlers(self, application):
        # добавляем handlers для реальных запросов (через load balancer, через внутри-кластерный порт, или по прямому имени сервера)
        application.add_handlers( r"(.*)", [
            ( r"/", XWebJsonHandler, dict(SUBADDR=SUBADDR_BALANCED, I=self.I) ),
            ( r"/x", XWebJsonHandler, dict(SUBADDR=SUBADDR_INTERNAL, I=self.I) ),
            ( r"/%s" % options.server_name, XWebJsonHandler, dict(SUBADDR=SUBADDR_SELF, I=self.I) ),
        ] )

        # служебные хэндлеры, типа login/logout
        self.initServiceActions()

        # готовы слушать; рапортуем координатору (и получаем в ответ список WS peers)
        self.getPeersFromCoordinator()

    # служебные хэндлеры, типа login/logout
    def initServiceActions(self):
        XWebJsonHandler.unloggedActionMap['login'] = XLoginAction
        XWebJsonHandler.loggedActionMap['logout'] = XLogoutAction

        XWebJsonHandler.loggedActionMap['send'] = XSendAction
        XWebJsonHandler.internalActionMap['send'] = XSendAction # redirect
        XWebJsonHandler.unloggedActionMap['send_nl'] = XSendNoLoginAction # no-login version
        XWebJsonHandler.loggedActionMap['retrieve'] = XReceiveAction
        XWebJsonHandler.loggedActionMap['purge'] = XPurgeAction
        XWebJsonHandler.loggedActionMap['touch'] = TouchAction
        XWebJsonHandler.unloggedActionMap['send_to_friends'] = XSendToFriendsAction

        # admin commands:
        XWebJsonHandler.loggedActionMap['ccu'] = CCUAction



    # ----------------------------------------------------------------------------------------------
    # закончен ли рабочий процесс (по wsShutdown сначала ждем выхода юзеров, завершения обработки incoming requests..)
    def isDoneServer(self):
        return ( len(users) <= 0 )

    # ----------------------------------------------------------------------------------------------
    # выполняем действия по финализации состояния (доразбор очередей sql и т.п.);
    # когда совсем готовы умереть, возвращаем True
    def shutdownServerTick(self):
        if self.wsShutdown == self.SHUTDOWN_START:
            bad_warn( "wsShutdown (SHUTDOWN_START): logout active users" )
            # даем юзерам N секунд чтобы свалить
            self.ACCOUNT_EXPIRE_SECONDS = min(self.ACCOUNT_EXPIRE_SECONDS, self.SHUTDOWN_ACCOUNT_EXPIRE_SECONDS)
            self.GUEST_ACCOUNT_EXPIRE_SECONDS = min(self.GUEST_ACCOUNT_EXPIRE_SECONDS, SHUTDOWN_ACCOUNT_EXPIRE_SECONDS) # включая и guest юзеров тоже
            self.tsUsersShutdownStarted = time.time()
            self.wsShutdown = self.SHUTDOWN_USERS

        elif self.wsShutdown == self.SHUTDOWN_USERS:
            if self.tsUsersShutdownStarted + self.SHUTDOWN_ACCOUNT_EXPIRE_SECONDS + 1 < time.time():
                bad_warn( "wsShutdown (SHUTDOWN_USERS): fadeout databases" )
                # постепенно закрываем лавочку (ждем когда очередь запросов полностью разберут, и тогда прибиваем thread pool)
                self.I.SQL.fadeout()
                self.tsDatabaseShutdownStarted = time.time()
                self.wsShutdown = self.SHUTDOWN_SQL
            else:
                bad_warn( "wsShutdown (SHUTDOWN_USERS): waiting for users logout (%d)..." % (toint(time.time() - self.tsUsersShutdownStarted) ))

        elif self.wsShutdown == self.SHUTDOWN_SQL:
            if self.I.SQL.isDone():
                bad_warn( "wsShutdown: sql done, stopping io loop" )
                return True
            else:
                bad_warn( "wsShutdown (SHUTDOWN_BILLING): waiting for sql fadeout (%d)..." % (toint(time.time() - self.tsDatabaseShutdownStarted) ))

    # ----------------------------------------------------------------------------------------------
    def fadeoutServer(self, **kwargs):
        ITornadoServer.fadeoutServer(self, **kwargs)


    # ----------------------------------------------------------------------------------------------
    # служебная фигня типа замеров времени, перевешивания таймеров, проверки shutdownServer -- делается в родительском _tick
    # здесь только полезная нагрузка:
    def tick(self):
        # ---- (1) выкинем протухшие аккаунты (keep alive более чем N минут назад)
        try:
            t0 = time.time()
            keys = users.keys()

            # заодно посчитаем кол-во юзеров (и отдельно guest-ов)
            self.CCU.userCount = 0
            self.CCU.guestCount = 0

            # посчитаем кол-во юзеров (и отдельно guest-ов)
            for id in keys:
                acc = users.get(id)
                if acc:
                    if acc.login.startswith("guest:"):
                        self.CCU.guestCount += 1
                    else:
                        self.CCU.userCount += 1

            for id in keys:
                acc = users.get(id)
                if acc:
                    last_keep_alive = acc.get("ka")

                    acc_timeout = self.ACCOUNT_EXPIRE_SECONDS
                    if acc.guest:
                        acc_timeout = self.GUEST_ACCOUNT_EXPIRE_SECONDS

                    if last_keep_alive + acc_timeout < t0:
                        # выкидываем
                        login = acc.login
                        info("DELETING EXPIRED acc[%d], login=%r: ka %0.2f, now %0.2f", id, login, last_keep_alive, t0)

                        # освобождаем лок в SQL
                        # (sp_logout проверяет ws == server_id, не позволит чужому серверу очистить server_id)
                        self.I.SQL.logout( login, options.server_id, main_sql_callback )

                        self.I.WS.onUserLogout( acc ) # OVERRIDE чтобы обработать кастомную логику logoff

                        try: # с заглушками (--mc=none, --sql=none) бывают дубликаты логинов
                            l = login.lower()
                            if l in logins:
                                logins.pop(l)
                            else:
                                warn("unknonw login %r", l)
                        except:
                            catch()

                        if id in users:
                            users.pop(id)
                        del acc

        except:
            warn( printException( sys.exc_info() ) )

        # ---------------------------------------------------------------------------
        # статистика: посчитаем кол-во юзеров (и отдельно guest-ов)
        self.CCU.peakUserCount = max( self.CCU.userCount, toint(self.CCU.peakUserCount) )
        self.CCU.peakGuestCount = max( self.CCU.guestCount, toint(self.CCU.peakGuestCount) )

        SEC = toint(t0)

        if SEC % 10 == 0:
            # раз в 10 секунд: дампим статистику юзеров
            info("CCU: %s", self.CCU)

        if SEC % 60 == 0:
            # раз в N секунд: прогоняем полный garbage collection pass
            t10 = time.time()
            gc.collect()
            t11 = time.time()
            info("gc counts: %s, garbage size: %d, gc time: %.3f", gc.get_count(), len(gc.garbage), t11-t10)
        else: # elif SEC % 1 == 0:
            info("gc counts: %s, garbage size: %d", gc.get_count(), len(gc.garbage))

        if SEC % 60 == 0:
            self.updateInstrumentedActions()

        # ---------------------------------------------------------------------------
        # (2) время от времени надо делать keepalive для всех sql-коннектов
        t1 = time.time()
        if options.sql == "async":
            if t1 - self.timeSqlKeepAlive > options.sql_keep_alive_seconds:
                info("sql keepalive: %5.3f", t1)
                self.I.SQL.keepAlive()
                self.timeSqlKeepAlive = t1


    # VIRTUAL: OVERRIDE чтобы отработать кастомную логику logoff
    def onUserLogout(self, acc):
        pass

    # ----------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------

    def getUserAcc(self, login):
        uid = logins.get( login.lower(), 0 )
        if uid:
            return users.get( uid )

    def getIOLoop(self):
        return tornado.ioloop.IOLoop.instance()

    # ----------------------------------------------------------------------------------------------
    # ----------------------------------------------------------------------------------------------

    def pushAccountMessages(self, acc, unlock=False):
        if acc:
            if acc.push_url:
                if not acc.push_lock or unlock:
                    if acc.messages:
                        acc.push_lock = 1 # на время исполнения push-запроса запрещаем повторные push (чтобы у принимающей стороны не перепутался порядок исполнения вызовов)
                        try:
                            callback = functools.partial( self.onPushMessagesReply, acc=acc )
                            body_dict = dict( count=len(acc.messages), messages=acc.messages )
                            json_body = json_dumps( body_dict )
                            debug("pushAccountMessages json body: %s", json_body)
                            args = dict( action="sex_send", method="send", project=acc.project, auid=acc.auid )
                            acc.pending_push = 0
                            self.I.WSX.post( acc.push_url, args, json_body, callback, subrequest="sex" )
                        except Exception:
                            catch()
                    else:
                        warn("pushAccountMessages (acc login=%s): no messages to push", acc.login)
                else:
                    warn("pushAccountMessages (acc login=%s): push locked (already executing a push)", acc.login)
                    acc.pending_push = 1
            else:
                warn("pushAccountMessages (acc login=%s): no push url", acc.login)

    def onPushMessagesReply(self, response, acc=None):
        info("onPushMessagesReply response: %s, \n acc login: %s", response, acc.login if acc else None)
        if acc and response:
            # ок, что-то пришло в ответ, сбрасываем лок
            acc.push_lock = 0
            if response.get("ok", 0):
                purge_msg_id_list = response.get("purge_ids")
                if purge_msg_id_list and isinstance(purge_msg_id_list, list):
                    delete_list = []
                    # собираем список msg_id "на удаление"
                    for str_msg_id in purge_msg_id_list:
                        msg_id = toint(str_msg_id)
                        msg = acc.messages.get(msg_id)
                        if msg:
                            info("onPushMessagesReply: schedule delete msg_id=%s for acc login=%s", msg_id, acc.login)
                            delete_list.append( msg_id )
                    if delete_list:
                        callback = functools.partial( self.onSqlDeleteMessages, acc=acc, delete_list=delete_list )
                        # удаляем весь список msg_id в mysql
                        return self.I.SQL.seDeleteMessages( acc.login, delete_list, callback=callback )
        elif acc and response is None:
            warn("onPushMessagesReply response is None, acc login: %s. Try to push message again count=%r", acc.login, getattr(acc, "push_lock_count", 0))
            if acc.push_lock == 1:
                acc.push_lock_count = getattr(acc, "push_lock_count", 0) + 1 # будем пытаться протолкнуть
                if acc.push_lock_count <= self.MAX_COUNT_TRY_PUSH:
                    #  разблокируем лок, видимо  не смогли достучатьcя и попытаемся еще раз
                    cb = functools.partial(self.pushAccountMessages, acc, True)
                    warn("pushAccountMessages %r seconds...", self.TIMEOUT_TRY_PUSH )
                    AddLoopCallback(cb, self.TIMEOUT_TRY_PUSH)
                    #self.pushAccountMessages( acc, True )
                else:
                    err("onPushMessagesReply response is None, acc login: %s. Amount of the try is maximum. Need to reload xs-server", acc.login)

    def onSqlDeleteMessages(self, sql_reply, acc=None, delete_list=[]):
        info("onSqlDeleteMessages sql_reply: %s, \n acc login: %s, delete_list: %s", sql_reply, acc.login, delete_list)
        r = sql_reply["r"]
        if r:
            if acc and delete_list:
                for msg_id in delete_list:
                    info("onPushMessagesReply: pop msg_id=%s for acc login=%s", msg_id, acc.login)
                    acc.messages.pop( msg_id, None )
        else:
            warn( "sql failed to delete messages %s for acc login=%s", delete_list, acc.login)

        # Если есть не отправленные, то еще раз отправляем PF-78175
        if acc.pending_push:
            self.pushAccountMessages( acc )

    # ------------------------------------------------------------------------------------------------------------------
    # ------------------------------------------------------------------------------------------------------------------


## -------------------------------------------------------------------------------------------------------
## -------------------------------------------------------------------------------------------------------
if __name__ == "__main__":
    try:
        ITornadoServer.main( XchangeWorkServer )
    except:
        msg = catch()
        print msg
    if MARKER_FILENAME:
        success("removing marker file %r" % MARKER_FILENAME)
        os.remove( MARKER_FILENAME )

