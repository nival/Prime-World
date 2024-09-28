# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import ssl

repeated_requests = {"sn_login": {},
                     "auth": {},
                     "collect_production_results": {}
                     }

#~ # -- serialization tests --
#~ import bson
import ujson
#~ import cjson

#~ import cgi, import urlparse
import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import tornado.httpclient
import functools

from tornado.options import define, options

import isql
import idata
#import imemcache
import ihttp
#import iwebserver

from base.http_dumb import *
from instr import *

from isql import main_sql_callback
from imemcache import main_memc_callback
#from iwebserver import IWebServer

from version import *

from subaction import SubAction, RESPONSE_TIMING_KEY, MAINTENANCE_NORMAL, MAINTENANCE_PENDING, MAINTENANCE_ONGOING

import EC # error codes


##----------------------------------------------------------------------------------------------------------------------
## social client/server protocol version
## при логине сообщаем версию сервера (даже в случае неуспеха)
PWSOC_VERSION = "%d.%d.%d.%d.%s" % (PWSOC_VERSION_HIGH, PWSOC_VERSION_MED, PWSOC_VERSION_LOW, PWSOC_VERSION_REVISION, PWSOC_BRANCH_NAME)

##----------------------------------------------------------------------------------------------------------------------
## social server/MATCHMAKING protocol version
MMSOC_VERSION_HIGH = 1
MMSOC_VERSION_MED = 8
MMSOC_VERSION_LOW = 116

## при логине сообщаем версию сервера (даже в случае неуспеха)
MMSOC_VERSION = "%d.%d.%d.%s" % (MMSOC_VERSION_HIGH, MMSOC_VERSION_MED, MMSOC_VERSION_LOW, PWSOC_BRANCH_NAME)

##----------------------------------------------------------------------------------------------------------------------
## social server/SOCIAL AGGREGATOR protocol version
SOCAGG_VERSION_HIGH = 0
SOCAGG_VERSION_MED = 3
SOCAGG_VERSION_LOW = 93

## всегда сообщаем версию соц.аггрегатора
SOCAGG_VERSION = "%d.%d.%d" % (SOCAGG_VERSION_HIGH, SOCAGG_VERSION_MED, SOCAGG_VERSION_LOW)

##----------------------------------------------------------------------------------------------------------------------
## глобальные настройки (в т.ч. для syncSqlQuery)

SUBADDR_NONE = 0
SUBADDR_BALANCED = 1
SUBADDR_INTERNAL = 2
SUBADDR_SELF = 3

define("port", default=8801, help="run on the given port", type=int)
define('nump', default=1, help="num processes to fork", type=int)
define("server_id", default=1, help="server index in cluster", type=int)
define("server_name", default="one", help="server name in cluster")
define("server_addr", default="127.0.0.1", help="self address for internal http calls")
define("server_class", default="unknown", help="cluster service class")

## SOLO CONFIG:
#define("coordinator", default="none", help="connect to coordinator at given ip:port")
#~ define("mc", default="none", help="which memcache version to use: none|mocky|async")
#~ define("sql", default="none", help="which sql realization to use: none|async")

## CLUSTER CONFIG:
define("coordinator", default="127.0.0.1:8700", help="connect to coordinator at given ip:port")

define("mc", default="none", help="which memcache realization to use: none|mocky|async")
define("sql", default="async", help="which sql realization to use: none|async")
define("zzima", default="http", help="which zzima realization to use: none|async|http")
define("billing", default="zzima", help="which billing realization to use: none|dummy|zzima")
define("data", default="mongo", help="which persistent data realization to use: none|sql|mongo")
define("pvx", default="http", help="which pvx mm realization to use: none|dummy|http")
##define("soc_agg", default="dummy", help="social aggregator interface: dummy|http")
define("soc_agg", default="http", help="social aggregator interface: dummy|http")
define("smodel", default="async", help="serial model interface: sync|async")

define("stats", default="thrift", help="statistics interface: thrift|none")
define("pers", default="scaled", help="person server interface: scaled|http|none")
define("wsx", default="http", help="peer web server server interface: http|fake|none")
define("sex", default="dummy", help="social exchange interface: async|dummy")
define("guilds", default="http", help="guilds service interface: http|none")
define("sieges", default="none", help="sieges service interface: http|none")  # отключаем в PF-106419
define("friends", default="http", help="friends service interface: http|none")

define("chat", default="http", help="chat server interface: http|fake|none")
define("filter", default="fake", help="chat filter interface: cleanspeak|fake")  # не используется

define("mirror", default="async", help="data mirroring request interface: async|none")
define("export", default="async", help="data mirroring export interface: async|none")

define("sql_keep_alive_seconds", default=15*60, help="set period (seconds) for sql keepalive (dummy) command execution", type=int)

define("log_level", default="info", help="logging level: none|debug|warning|error")
##define("log_level", default="debug", help="logging level: none|debug|warning|error")
##define("log_rotation", default="external", help="log rotation mechanism: timed|external, linux systems can use 'external' with logrotate utility")
define("log_rotation", default="timed", help="log rotation mechanism: timed|external, linux systems can use 'external' with logrotate utility")
define("log_rotation_interval", default=60.0, type=float, help="log rotation interval (minutes)")

define("_dont_log", default=0, type=int, help="don't use statistic event logging")
define("strict_login_check", default=0, type=int, help="strict login check: 0|1, 0=allow ver 0.0.0 clients")
define("shipping", default=0, type=int, help="shipping mode: 1=turn off development-mode commands, mm_messages etc.")

##define('log_scribe_host', default='ec2-50-17-32-187.compute-1.amazonaws.com', help="scribe host to send logs")
##define('log_scribe_host', default='localhost', help="scribe host to send logs")
define('log_scribe_host', default='', help="scribe host to send logs") # OFF
define('log_scribe_port', default=1463, type=int, help="scribe port to send logs")
define('log_scribe_level', default='warning', help="logging level for scribe: none|debug|info|warning|error|critical")
define('log_scribe_transport', default='framed', help="logging transport for scribe: framed|unframed|http|none")
define('log_scribe_uri', default=None, help="logging uri for http transport")
##define('log_file_prefix', default='logs/scribe', help="scribe log file prefix")

define('log_http', default=1, type=int, help="use remote logging interface: 0|1")
#~ define('log_http', default=0, type=int, help="use remote logging interface: 0|1")
define('log_http_level', default='warning', help="logging level for http: none|debug|info|warning|error|critical")
define('log_http_max_count', default=1000, type=int, help="max messages count in to-send queue")
define('log_http_retry_pause', default=10.0, type=float, help="after a failed send, pause X seconds before trying to send again")

define('ssl', default=0, type=int, help="use ssl for incoming HTTPS traffic")
define('ssl_key', default='tests/ssl_ca/ca.key', help="ssl key file for incoming HTTPS traffic")
define('ssl_cert', default='tests/ssl_ca/ca.crt', help="ssl certificate for incoming HTTPS traffic")
define('ssl_reqs', default=ssl.CERT_REQUIRED, help="ssl requirement mode (CERT_NONE|CERT_OPTIONAL|CERT_REQUIRED)")
#define('ssl_reqs', default=ssl.CERT_OPTIONAL, help="ssl requirement mode (CERT_NONE|CERT_OPTIONAL|CERT_REQUIRED)")

#define('smtp', default="async", help="use real or dummy(file log) smtp for sending mail: dummy|async")
define('smtp', default="dummy", help="use real or dummy(file log) smtp for sending mail: dummy|async")
define('smtp_ssl', default=0, type=int, help="0|1, use ssl encoding for smtp connect")
define('smtp_host', default='minsk-mail.nivalnetwork.com', help="smtp host address")
define('smtp_port', default=2525, type=int, help="smtp port")
define('smtp_timeout', default=20, type=int, help="smtp operations timeout (seconds)")
define('smtp_fromaddr', default='pwconnect@zzima.com', help="smtp 'from' address")
define('smtp_fromname', default='Prime World', help="smtp 'from' symbolic name")
define('smtp_username', default='pwconnect', help="smtp username for sending mail")
define('smtp_pwd', default='', help="smtp password for sending mail")

define('blocking_threshold', default=26.0, help="tornado ioloop blocking threshold (log stack trace when exceeded)")

# for local debug mostly -- lightens logging flood
define("tick_period", default=1.0, help="tick period, seconds", type=float)

sys.path.append('cfg')
import cfg # конфиг кластера

##----------------------------------------------------------------------------------------------------------------------
## глобальный хэш "юзеров нашего сервера", [id] -> { ..context.. }
users = {}

# игроки выброшенные вытесняющим логином
old_users = []

## глобальный хэш "логинов нашего сервера" [login] -> id, md5
logins = {}

## глобальный 2-уровневый хэш "social-network логинов", [<sn>][<sn_login>] -> { login, sn_md5 }


## (default) столько живут активные юзеры на сервере
ACCOUNT_EXPIRE_SECONDS = 60*2 # standard: 2 minutes
GUEST_ACCOUNT_EXPIRE_SECONDS = 60*60*4 # AP5: 4 HOURS ###########################FIXME
SHUTDOWN_ACCOUNT_EXPIRE_SECONDS = 10 # столько секунд даем юзерам чтобы свалить при активированно shutdown

POLLING_PING_TIMEOUT = 15 # если за 15 секунд ничо не случилось, сервер так и отвечает на PingAction

USER_RELIABILITY_INITIAL = 1000

## отладочное: насколько "глубоко" проходит запрос по кластеру
DEPTH_WS = 1 # ответил сразу рабочий сервер, без обращений куда-то еще
DEPTH_MC = 2 # поднадобилось обращение в MEMCACHE
DEPTH_SQL = 3 # поднадобилось обращение в базу данных

from modeldata.MultiStaticData import MultiStaticData
import modeldata.GenerateSeeds

## helper
def makePersKey( uid ):
    return "data_%d" % uid


##----------------------------------------------------------------------------------------------------------------------
def resetGlobals():
    logins.clear()
    users.clear()
    old_users = []


def addErrorArg(response, name, value):
    response["error_args"] = response.get("error_args") or {}
    response["error_args"][name] = value

##----------------------------------------------------------------------------------------------------------------------
from config.MultiConfig import MultiConfig

def loadMultiConfig():
    config = MultiConfig()
    #info( "mainConfig: %s" % pretty(config.mainConfig.generateJsonDict()) )
    #for locale, locale_config in config.configs.iteritems():
        #info( "localeConfig[%s]: %s" % (locale, pretty(locale_config.generateJsonDict())) )
    return config

##----------------------------------------------------------------------------------------------------------------------
# отвечать юзеру будем в JSON-формате, чтобы легко было парсить на стороне клиента
class JsonHandler( tornado.web.RequestHandler ):
    """ базовый класс: обработчик команд веб-сервера """
    unloggedActionMap = {
        # команды, всегда открытые для любого внешнего клиента
    }

    loggedActionMap = {
        # команды, открытые только для залоганных внешних клиентов
    }

    internalActionMap = {
        # внутрикластерные команды; закрыты для внешних клиентов
    }

    _Interfaces = dict( SUBADDR=None, I=None )

    ACTION_PARAM_NAME = "action"

    ##-------------------------------------------------------------------------------------
    def __init__(self, application, request, **kwargs):
        tornado.web.RequestHandler.__init__(self, application, request)
        ##log( "JH _Interfaces:" + str(self._Interfaces) )

        # мапим интерфейсы по списку _interfaces (если для одного из интерфейсов есть оверрайд в списке параметров, подставляем)
        for key, iBase in self._Interfaces.iteritems():
            if kwargs:
                # интерфейсы типа HTTP, MC, SQL можно оверрайдить через дополнительный словарик
                iface = kwargs.get(key)
                if iface is not None:
                    setattr(self, key, iface)
                    continue

            # по умолчанию -- берем default-ные заглушки
            setattr(self, key, iBase)


    ##-------------------------------------------------------------------------------------
    ## достаем первый параметр из списка значений 'name=' (в строчном виде)
    def getParam(self, name, default=None):
        param_list = self.request.arguments.get(name)
        if param_list:
            return param_list[0] #tornado.escape.xhtml_escape(param_list[0])
        else:
            return default


    ##-------------------------------------------------------------------------------------
    ## достаем первый параметр из списка значений 'name=' (обязательно числовой)
    def getDigitParam(self, name, converter, default=None):
        param_list = self.request.arguments.get(name)
        result = default
        if param_list:
            value = param_list[0] #tornado.escape.xhtml_escape(param_list[0])
            try:
                result = converter(value)
            except:
                pass
        #fail:
        return result

    ##-------------------------------------------------------------------------------------
    ## достаем первый параметр из списка значений 'name=' (обязательно числовой)
    def getIntParam(self, name, default=None):
        return self.getDigitParam(name, int, default)

    ##-------------------------------------------------------------------------------------
    ## достаем первый параметр из списка значений 'name=' (обязательно числовой)
    def getFloatParam(self, name, default=None):
        return self.getDigitParam(name, float, default)

    ##-------------------------------------------------------------------------------------
    ## достаем первый параметр из списка значений 'name=' (в строчном виде)
    def getJsonParam(self, name, default=None, error="bad json data: "):
        param_list = self.request.arguments.get(name)
        if param_list and len(param_list) and param_list[0]:
            json_data = param_list[0] #tornado.escape.xhtml_escape(param_list[0])
            try:
                data = json_loads( json_data )
                return data
            except:
                self.response["error"] = error + "%s=%s" % (str(name), str(json_data))
                self.response["error_json"] = printException( sys.exc_info() )
        return default


    ##-------------------------------------------------------------------------------------
    ## вытаскиваем все простые аргументы (x:[y]) в виде словаря
    def getFlatParams(self, except_list=[]):
        arg_dict = {}
        if self.request.arguments:
            for key,arg in self.request.arguments.iteritems():
                if key and arg and isinstance(arg, list) and len(arg)==1 and (key not in except_list):
                    arg_dict[key] = arg[0]
        return arg_dict

    ##-------------------------------------------------------------------------------------
    def addArguments(self, **kwargs):
        info( "JsonHandler addArguments: %s" % kwargs )
        if kwargs:
            for k,v in kwargs.iteritems():
                self.request.arguments[k] = [v]

    ##-------------------------------------------------------------------------------------
    # проверяем, что значение есть в некотором "списке допустимых значений"
    def checkPossibleValue(self, val, possible, error="bad value"):
        if val in possible:
            return True
        else:
            self.response["error"] = error + " (possible values: %s)" % str(possible)


    ##-------------------------------------------------------------------------------------
    # проверяем, что есть непустой параметр "name" (если есть, ставим self.name)
    def checkValidParam(self, name, error="bad or missing param: "):
        val = self.getParam(name)
        setattr(self, name, val)
        if val:
            return True
        else:
            self.response["error"] = str(error) + str(name)

    ##-------------------------------------------------------------------------------------
    # проверяем, что есть непустой и ненулевой параметр "name"
    def checkValidIntParam(self, name, error="bad or null param: "):
        val = self.getIntParam(name, 0)
        setattr(self, name, val)
        if val:
            return True
        else:
            self.response["error"] = str(error) + str(name)

    ##-------------------------------------------------------------------------------------
    def fail(self, message, code):
        info("%s action fail: ec=%s, message=%s", getattr(self, "action", ""), code, message)
        self.response["ec"] = code
        self.response["error"] = message
        self.fin()

    ##-------------------------------------------------------------------------------------
    ## schedule request finalization
    def fin(self):
        self.scheduleFinalize( self.response )

    def scheduleFinalize(self, response):
        if not self.I.WS.TEST_MODE:
            loop = tornado.ioloop.IOLoop.instance()
            fin_callback = functools.partial( self.finJson, response )
            loop.add_callback( fin_callback )
        else:
            # в тестах вызываем callback напрямую
            self.finJson( response )

    ##-------------------------------------------------------------------------------------
    ## finalize response of SubAction() into JSON, send over
    def finJson(self, response):
        redirectURL = response.get("__redirect__")
        if not redirectURL:
            ##log( "finJson response: %s" % str(response) )

            # посмотрим время  паковки ModelData в json:
            t0 = time.time()

            if getattr(self, "pretty", 0):
                # красиво отформатировать, с отступами и переносами строки
                json_response = '{\n"response":%s\n}' % self.I.MD.pretty( response )
            else:
                json_response = '{"response":%s}' % self.I.MD.toJson( response )

            t1 = time.time()

            self.finJsonResponse(json_response, response, t1-t0)

        else:
            self.redirect( redirectURL )

    ##-------------------------------------------------------------------------------------
    def finJsonResponse(self, json_response, response, json_timing=0):
        t9 = time.time()

        self.write(json_response)
        self.finish()

        t10 = time.time()

        total_wrap_time = t10-t9 + json_timing

        action_name = getattr(self, "action", "")
        if action_name:
            executionTime = response.get(RESPONSE_TIMING_KEY, -1)
            if executionTime >= 0:
                self.I.WS.instrumentAction(action_name, executionTime + total_wrap_time) # добавим к instrumentation и время заворачивания ответа

        if total_wrap_time > 0.001:
            info( "%s response .toJson write: %.4f, http write: %.4f" % (action_name, json_timing, t10-t9) )

    ##-------------------------------------------------------------------------------------
    def on_connection_close(self):
        if getattr(self, 'actionMethod', None):
            # Action is handled by self's method
            try:
                onConnectionClose = self.onConnectionClose
            except AttributeError:
                return
        else:
            # Action is handled by SubAction's subclass
            try:
                onConnectionClose = self.actionHandler.onConnectionClose
            except AttributeError:
                if getattr(self, 'actionHandler', None) is None:
                    msg = 'no actionHandler'
                else:
                    msg = 'no onConnectionClose method for actionHandler'
                warn("%s.on_connection_close: %s! reqest time: %s, request = %s",
                     self.__class__, msg, self.request.request_time(), self.request)
                return
        onConnectionClose()

    ##-------------------------------------------------------------------------------------
    ## main http request mapper (раскидываем запросы по handler methods, в зависимости от "/subaddr" и "action=")
    @tornado.web.asynchronous
    def get(self):
        info( "Query: %s", str(self.request.query) )
        info( "Query params: %s",  str(self.request.arguments) )

        params = self.request.arguments
        ## info( "Params: %s" % str(params) )
        #~ warn( "cgi.parse_qs: %s" % str(cgi.parse_qs(self.request.query)) )
        #~ warn( "urlparse.parse_qs: %s" % str(urlparse.parse_qs(self.request.query)) )

        if getattr(self.I.WS, "wsShutdown", None):
            raise tornado.web.HTTPError(410) # сервак выключается, всем пора спать, о чем и извещаем пользователей.

        if self.SUBADDR in [SUBADDR_BALANCED, SUBADDR_INTERNAL, SUBADDR_SELF]:
            #self.set_header("Content-Type", "application/json") ## SHIPPING: отвечаем в json
            self.set_header("Content-Type", "text/plain") ## DEBUG: показываем текст в браузере
            self.set_header("charset", "UTF-8")

            self.response = { "ok":0, "ec":0, "server":options.server_name }

            self.pretty = self.getIntParam("pretty", 0)

            ## handle commands
            try:
                self.action = self.getParam( self.ACTION_PARAM_NAME )
                if self.action:
                    if self.SUBADDR == SUBADDR_BALANCED:
                        if self.unloggedActionMap.has_key(self.action):
                            # случайный load balancing разрешаем только для логина
                            ActionClass = self.unloggedActionMap[self.action]
                            actionHandler = ActionClass( params, self.async_callback( self.scheduleFinalize ), self )
                            self.actionHandler = actionHandler
                            actionHandler.onStart()
                            return
                        else:
                            self.response["error"] = "Bad unlogged action from client: %r" % str(self.action)

                    elif self.SUBADDR == SUBADDR_INTERNAL:
                        ## info( "internalActionMap:" + str(self.internalActionMap) )
                        if self.internalActionMap.has_key(self.action):
                            # внутрикластерные события
                            MethodHandler = self.internalActionMap[self.action]
                            ##info( 'MethodHandler=%r' % MethodHandler )
                            if isinstance( MethodHandler, basestring ):
                                # можно задавать имя метода в своем JsonHandler ('sys_req': 'onSomeSystemRequest')
                                method = getattr(self, MethodHandler, None)
                                if method is None:
                                    err("GET: %s doesn't support %s method", self.__class__, MethodHandler)
                                    self.response["error"] = 'Unknown method %s.%s' % (self.__class__, MethodHandler)
                                elif not callable(method):
                                    err("GET: %s.%s isn't callable", self.__class__, MethodHandler)
                                    self.response["error"] = "%s.%s isn't callable" % (self.__class__, MethodHandler)
                                else:
                                    self.actionMethod = MethodHandler
                                    method()
                                    return

                            elif issubclass( MethodHandler, SubAction ):
                                # можно также задавать отдельный SubAction ( 'some_subaction': SomeSubAction ), from ext_xxx import SomeSubAction;
                                actionHandler = MethodHandler( params, self.async_callback( self.scheduleFinalize ), self )
                                self.actionHandler = actionHandler
                                actionHandler.onStart()
                                return

                            else:
                                self.response["error"] = "Unknown handler type for internal action: %r" % str(self.action)
                        else:
                            self.response["error"] = "Bad internal action: %r" % str(self.action)

                    elif self.loggedActionMap.has_key(self.action):
                        # общий обработчик для всех команд со "стандартной проверкой залоганности"
                        ##log( "loggedActionMap has_key " + str(self.action) )
                        self.onLoggedAction()
                        return
                    elif self.unloggedActionMap.has_key(self.action):
                        ActionClass = self.unloggedActionMap[self.action]
                        actionHandler = ActionClass( params, self.async_callback( self.scheduleFinalize ), self )
                        self.actionHandler = actionHandler
                        actionHandler.onStart()
                        return
                    else:
                        self.response["error"] = "Bad logged action from client: %r" % str(self.action)
                else:
                    self.response["error"] = "Bad action: %r" % str(self.action)

                self.response["ec"] = EC.BAD_ACTION_NAME
                addErrorArg( self.response, "action", str(self.action) )

            except:
                # объединяем и распечатываем exception info
                excInfo = printException( sys.exc_info() )
                warn(excInfo)
                self.response["error"] = excInfo

                self.response["ec"] = EC.ACTION_HANDLER_EXCEPTION
                addErrorArg( self.response, "action", str(self.action) )

            self.fin()
            return

        #FAIL
        raise tornado.web.HTTPError(403)


    ##-------------------------------------------------------------------------------------
    ## общая обертка для пользовательских команд (требующих наличия активной сессии)
    ##   со стандартными проверками "залоганности юзера" (uid, key)
    def onLoggedAction(self):
        uid = self.getParam("uid")
        try:
            self.uid = int(uid)
        except TypeError:
            self.fail("bad uid", EC.BAD_SESSION)
            return
        except ValueError:
            self.fail("bad uid", EC.BAD_SESSION)
            return
        acc = users.get(self.uid)
        if not acc:
            if self.uid in old_users:
                self.fail("old user", EC.OLD_USER )
                old_users.remove(self.uid)
                return
            else:
                self.fail("bad session", EC.BAD_SESSION )
                return
        self.acc = acc
        key = self.getParam("key", "X")
        if not digit(key):
            self.fail("bad key", EC.BAD_SESSION)
            return

        if key != acc["key"]:
            if self.uid in old_users:
                self.fail("old user", EC.OLD_USER )
                old_users.remove(self.uid)
                return
            else:
                self.fail("wrong key, relogin", EC.BAD_SESSION)
                return

        if acc.failed:
            if self.pretty:
                self.response["failed_traceback"] = acc.failed_traceback
            self.fail("account failed, please report to customer service", EC.ACCOUNT_FAILED)
            return
        if acc.locked:
            self.fail("account locked, please retry your request later", EC.ACCOUNT_LOCKED)
            return
        if acc.wait_inform_user:
            acc.wait_inform_user = False
            self.fail("account kicked, please retry your request later", EC.CLIENT_KICKED)
            return

        if (not acc.db.banned) and (not acc.banned):
            touch( self.acc ) # продлеваем активную жизнь юзера на сервере
            params = self.getFlatParams()
            signCheckResult = checkParamsSignature( params, secret=acc.secret )
            ## info("signature check:%s (acc.secret=%s, params=%s)" % ( signCheckResult, acc.secret, str(params) ))
            strictSignCheck = getattr(cfg, "STRICT_SIGN_CHECK", 0) # нужно ли отказывать при несовпадении подписи?
            if (not strictSignCheck) or (signCheckResult):
                try:
                    ## method_name = loggedActionMap[self.action]
                    ActionClass = self.loggedActionMap[self.action]
                    actionHandler = ActionClass( self.request.arguments, self.async_callback( self.scheduleFinalize ), self )
                    self.actionHandler = actionHandler
                    actionHandler.response["sign_ok"] = signCheckResult
                    if not ActionClass.debug or (self.acc.admin or self.acc.getConfigValue("DEBUG_ENABLED")):
                        return actionHandler.onStart()
                    else:
                        self.response["error"] = "Debug requests are not allowed"
                        self.response["ec"] = EC.DEBUG_REQUEST
                except:
                    catch()
                    self.response["error"] = printException(sys.exc_info())
            else:
                self.response["error"] = "bad request signature"
                self.response["ec"] = EC.BAD_SIGNATURE
        else:
            addErrorArg( self.response, "banreason", acc.db.banreason )
            if acc.db.bantime == 0:
                self.response["ec"] = EC.ACCOUNT_BANNED_FOREVER
            else:
                addErrorArg( self.response, "bantime", acc.db.bantime )
                self.response["ec"] = EC.ACCOUNT_BANNED
        # fail, return error
        self.fin()


    # -----------------------------------------
    def onCheckWebServerAlive(self):
        """ всем кому угодно умеем отвечать, что живы """
        self.response['ok'] = 1
        if self.I.HTTP:
            self.response["httpActive"] = len(self.I.HTTP.active)
            self.response["httpQueued"] = len(self.I.HTTP.queue)
            if len(self.I.HTTP.active):
                logging.info("active HTTP queue dump (%s requests):" % len(self.I.HTTP.active))
                try:
                    for k, v in self.I.HTTP.active.iteritems():
                        request, callback = v
                        logging.info( "[%s] request url=%s" % (k, request.url))
                except:
                    logging.warning( "dump_active_queue exception", exc_info=True)
        self.response['sid'] = options.server_id
        self.fin()

    # -----------------------------------------
    def onReloadMultiConfig(self):
        time1 = time.time()
        info( "onReloadMultiConfig..." )
        # старая копия конфига будет жить, пока на нее будут валидные ссылки (у пользовательских аккаунтов и т.п.)
        self.I.Config = loadMultiConfig()
        # аналогично перегружаем StaticData:
        debug("backupDynamicQuests...")
        dynamicQuests, dynamicQuestPulls = self.I.SD.backupDynamicQuests()
        debug("reloadStaticData...")
        self.I.SD.reloadStaticData(self.I.Config.mainConfig)
        # update config-dependant static data collections:
        if self.I.SD:
            # конфиг logic_overrides может содержать переопределения полей StaticData; их тоже нужно применить к перегруженной SD
            self.I.Config.mainConfig.applyOverrides(self.I.SD.getMainSD())
            self.I.Config.applyLocaleOverrides(self.I.SD)
            self.I.Config.fillStaticDataDependendValues(self.I.SD)
            self.I.SD.loadDynamicQuests(dynamicQuests, dynamicQuestPulls)
            for _id, event in self.I.WS.operatorEvents["activeEvents"].items():
                self.I.Config.applyEvent(self.I.SD, event)
        if self.I.MD:
            self.I.MD.reloadAllEvents()

        info( "onReloadMultiConfig all done, time: %.3f sec", time.time() - time1 )
        self.response['ok'] = 1
        self.fin()

    # -----------------------------------------
    def onReloadLocaleMultiConfig(self):
        info( "onReloadLocaleMultiConfig..." )
        time1 = time.time()
        locale = self.getParam("locale", None)
        if locale:
            locale = locale.lower()
            # если такой локали в конфигах нет, то всё остальное бессмысленно
            if not self.I.Config.reloadLocaleConfig(locale):
                return

            # аналогично перегружаем StaticData:
            dynamicQuests, dynamicQuestPulls = self.I.SD.backupDynamicQuests()
            if self.I.SD.hasSDForLocale(locale):
                self.I.SD.reloadLocaleStaticData(locale)
                self.I.SD.getSD(locale).reloadConfigDependendFields(self.I.Config.getConfig(locale))
                time2 = time.time()
                info( "onReloadMultiConfig MultiStaticData done, time: %.3f sec", time2 - time1 )
                # конфиг logic_overrides может содержать переопределения полей StaticData; их тоже нужно применить к перегруженной SD
                self.I.Config.getConfig(locale).applyOverrides(self.I.SD.getSD(locale))
                self.I.Config.getConfig(locale).fillStaticDataDependendValues(self.I.SD.getSD(locale))
                for _id, event in self.I.WS.operatorEvents["activeEvents"].items():
                    if event["locale"].lower() == locale.lower():
                        self.I.Config.applyEvent(self.I.SD, event)
            self.I.SD.loadDynamicQuests(dynamicQuests, dynamicQuestPulls)
            if self.I.MD:
                self.I.MD.reloadAllEvents()
        info( "onReloadMultiConfig all done, time: %.3f sec", time.time() - time1 )
        self.response['ok'] = 1
        self.fin()

    # -----------------------------------------
    # Вызывается для сервисов, которые работают с единой основной SD
    # (guild, party, friend, siege)
    def onReloadMultiConfigWithMainSD(self):
        info("onReloadMultiConfigWithMainSD...")

        self.I.Config = loadMultiConfig()
        # аналогично перегружаем StaticData:
        if self.getIntParam("fromDisk", 0):
            self.I.MSD = MultiStaticData(os.path.join(os.path.dirname(os.path.realpath(__file__)),
                                                      options.xdb_path + "/ExportedSocialData.xml"),
                                         self.I.Config.mainConfig, loadLocales=False)
        else:
            self.I.MSD.reloadStaticData(self.I.Config.mainConfig)
        self.I.SD = self.I.MSD.getMainSD()
        # update config-dependent static data collections:
        if self.I.SD:
            # конфиг logic_overrides может содержать переопределения полей StaticData; их тоже нужно применить к перегруженной SD
            self.I.Config.mainConfig.applyOverrides(self.I.SD)
            self.I.Config.mainConfig.fillStaticDataDependendValues(self.I.SD)
        if self.I.MD:
            self.I.MD.reloadAllEvents()
        info("onReloadMultiConfigWithMainSD done.")
        self.response['ok'] = 1
        self.fin()


    # -----------------------------------------
    def onAddNewDynamicQuest(self):
        info("onAddNewDynamicQuest")
        locale = self.getParam("locale", None)
        jsonQuestData = self.getParam("jsonQuestData", None)
        persistentId = self.getIntParam("persistentId", None)
        pullId = self.getIntParam("pullId", None)
        if locale and jsonQuestData and persistentId is not None:
            # Находим соответствующую StaticData:
            localSD = self.I.SD.getSD(locale)
            # Посмотрим, правильный ли у нас json
            try:
                questDict = json_loads(jsonQuestData)
                if localSD:
                    localSD.DynamicQuests[persistentId] = {"questData": questDict, "version": 0, "pullId": pullId}
                    # Квест, возможно, добавляется в ротацию
                    if pullId and pullId in localSD.DynamicQuestPulls:
                        localSD.DynamicQuestPulls[pullId]["quests"].append(persistentId)
                    self.I.WS.updateDynamicQuests()
            except Exception:
                catch()
                info("onAddNewDynamicQuest failed for %r", jsonQuestData)
        info("onAddNewDynamicQuest done.")
        self.response['ok'] = 1
        self.fin()

    # -----------------------------------------
    def onSendGWEventEditToStats(self, ):
        info("onSendGWEventEditToStats")

        gwEvent = ClassDict(persistentId=self.getParam('persistentId', ''),
                            event_index=self.getIntParam('event_index', 0),
                            enabled=bool(self.getIntParam('enabled', 0)),
                            points=self.getIntParam('points', 0),
                            endTime=self.getIntParam('endTime', 0),
                            limit=self.getIntParam('limit', 0))

        self.I.STATS.addGWEvent(gwEvent.persistentId, gwEvent.event_index, gwEvent.enabled, gwEvent.points,
                                gwEvent.endTime,
                                gwEvent.limit)

        self.response['ok'] = 1
        self.fin()

    def onRemoveDynamicQuest(self, ):
        info("onRemoveDynamicQuest")
        locale = self.getParam("locale", None)
        questId = self.getIntParam("questId", None)
        # Находим соответствующую StaticData:
        localSD = self.I.SD.getSD(locale)
        if localSD and questId in localSD.DynamicQuests:
            pullId = localSD.DynamicQuests[questId]["pullId"]
            if pullId and pullId in localSD.DynamicQuestPulls:
                localSD.DynamicQuestPulls[pullId]["quests"].remove(questId)
            del localSD.DynamicQuests[questId]
        self.response['ok'] = 1
        self.fin()

    def onEditDynamicQuest(self,):
        info("onEditDynamicQuest")
        locale = self.getParam("locale", None)
        jsonQuestData = self.getParam("jsonQuestData", None)
        questId = self.getIntParam("persistentId", None)
        pullId = self.getIntParam("pullId", None)
        localSD = self.I.SD.getSD(locale)
        if localSD and questId in localSD.DynamicQuests:
            try:
                questDict = json_loads(jsonQuestData)
                localSD.DynamicQuests[questId]['questData'] = questDict
                localSD.DynamicQuests[questId]['version'] += 1
                # изменился или убрался пулл
                if pullId != localSD.DynamicQuests[questId]['pullId']:
                    oldPullId = localSD.DynamicQuests[questId]['pullId']
                    localSD.DynamicQuests[questId]['pullId'] = pullId
                    if oldPullId and oldPullId in localSD.DynamicQuestPulls:
                        localSD.DynamicQuestPulls[pullId]["quests"].remove(questId)
                    if pullId and pullId in localSD.DynamicQuestPulls:
                        localSD.DynamicQuestPulls[pullId]["quests"].append(questId)
            except Exception:
                catch()
                info("onEditDynamicQuest failed for %r", jsonQuestData)
            self.I.WS.updateDynamicQuests()
        self.response['ok'] = 1
        self.fin()

    def onEditAuidsListForQuest(self):
        info("onEditAuidsListForQuest")
        auids = self.getJsonParam("auids")
        listId = self.getIntParam("listId", -1)

        for locale in self.I.SD.staticDatas:
            localeSD = self.I.SD.staticDatas[locale]
            for questId in localeSD.DynamicQuests:
                if questId == "isMainSD":
                    continue
                dynQuest = localeSD.DynamicQuests[questId]["questData"]
                if "AuidList" in dynQuest["AcceptFilter"] and int(dynQuest["AcceptFilter"]["AuidList"]) == listId:
                    dynQuest["AcceptFilter"]["ForAuids"] = auids
        self.response['ok'] = 1
        self.fin()

    # -----------------------------------------
    def onRemoveDynamicQuestPull(self, ):
        info("onRemoveDynamicQuestPull")
        locale = self.getParam("locale", None)
        pullId = self.getIntParam("persistentId", None)
        # Находим соответствующую StaticData:
        localSD = self.I.SD.getSD(locale)
        if localSD and pullId in localSD.DynamicQuestPulls:
            for questId in localSD.DynamicQuestPulls[pullId]["quests"]:
                if questId in localSD.DynamicQuests:
                    del localSD.DynamicQuests[questId]
            del localSD.DynamicQuestPulls[pullId]
        self.response['ok'] = 1
        self.fin()

    # -----------------------------------------
    def onClearAllDynamicQuests(self, ):
        info("onClearAllDynamicQuests")
        if self.I.Config.getMainConfig().DEBUG_ENABLED:
            for localeSD in self.I.SD.staticDatas:
                self.I.SD.staticDatas[localeSD].DynamicQuests = {}
                self.I.SD.staticDatas[localeSD].DynamicQuestPulls = {}
            self.response['ok'] = 1
            self.fin()


    # -----------------------------------------
    def onAddNewDynamicQuestPull(self):
        info("onAddNewDynamicQuestPull")
        locale = self.getParam("locale", None)
        startTime = self.getIntParam("startTime", 0)
        endTime = self.getIntParam("endTime", 0)
        persistentId = self.getIntParam("persistentId", None)
        hasRotation = self.getParam("hasRotation", None)
        active = str2bool(self.getParam("active", None))
        if locale and persistentId is not None:
            # Находим соответствующую StaticData:
            localSD = self.I.SD.getSD(locale)
            try:
                if localSD:
                    localSD.DynamicQuestPulls[persistentId] = {"startTime": startTime, "endTime": endTime,
                                                               "hasRotation": hasRotation, "isActive": active,
                                                               "quests": []}
            except Exception:
                catch()
                info("onAddNewDynamicQuestPull failed for persistentId %r", persistentId)
        info("onAddNewDynamicQuestPull done.")
        self.response['ok'] = 1
        self.fin()

    # -----------------------------------------
    def onAddDynamicQuestToPull(self):
        info("onAddDynamicQuestToPull")
        locale = self.getParam("locale", None)
        pullId = self.getIntParam("pullId", None)
        questId = self.getIntParam("questId", None)
        if locale and pullId is not None and questId is not None:
            # Находим соответствующую StaticData:
            localSD = self.I.SD.getSD(locale)
            try:
                if localSD and pullId in localSD.DynamicQuestPulls:
                    localSD.DynamicQuestPulls[pullId]["quests"].append(questId)
                    # Надо проставить id квесту, который был добавлен в пулл
                    if questId in localSD.DynamicQuests:
                        localSD.DynamicQuests[questId]["pullId"] = pullId
            except Exception:
                catch()
                info("onAddDynamicQuestToPull failed for pullId %r and questId %r", pullId, questId)
        info("onAddDynamicQuestToPull done.")
        self.response['ok'] = 1
        self.fin()

    # -----------------------------------------
    def onRemoveDynamicQuestFromPull(self):
        info("onRemoveDynamicQuestFromPull")
        locale = self.getParam("locale", None)
        pullId = self.getIntParam("pullId", None)
        questId = self.getIntParam("questId", None)
        if locale and pullId is not None and questId is not None:
            # Находим соответствующую StaticData:
            localSD = self.I.SD.getSD(locale)
            try:
                if localSD and pullId in localSD.DynamicQuestPulls:
                    localSD.DynamicQuestPulls[pullId]["quests"].remove(questId)
                    # Надо убрать id квесту, который был добавлен в пулл
                    if questId in localSD.DynamicQuests:
                        localSD.DynamicQuests[questId]["pullId"] = 0
            except Exception:
                catch()
                info("onRemoveDynamicQuestFromPull failed for pullId %r and questId %r", pullId, questId)
        info("onRemoveDynamicQuestFromPull done.")
        self.response['ok'] = 1
        self.fin()

    # -----------------------------------------
    def onClearAddrInfoCache(self):
        info( "onClearAddrInfoCache" )
        if self.I.HTTP:
            self.I.HTTP.clear_addr_info_cache()
        self.response['ok'] = 1
        self.fin()

PEER_UPDATED = 0
PEER_DELETED = 1
PEER_ADDED = 2

# -----------------------------------------
class PeerServerStatusAction(SubAction):
    action = "peer"
    def onStart(self):
        """ координатор сообщает об изменении статуса одного из peer-серверов """
        name = self.getParam("name")
        on = toint( self.getParam("on") )
        sid = toint( self.getParam("sid") )
        rdy = toint( self.getParam("rdy") )
        max_users = toint( self.getParam("max_users") )
        cur_users = toint( self.getParam("cur_users", 0) )
        info( "onPeerServerStatus( sid=%d, name=%s, on=%d, rdy=%d, max_users=%d cur_users=%d)", sid, str(name), on, rdy, max_users, cur_users  )

        if on:
            # добавляем
            peer = self.I.WS.peers.get(sid)
            action = 'Updated'
            status = PEER_UPDATED
            if not peer:
                peer = ClassDict()
                self.I.WS.peers[sid] = peer
                action = 'Added'
                status = PEER_ADDED

            peer["on"] = 1
            peer["addr"] = self.getParam("addr")
            peer["name"] = name
            peer["max_users"] = max_users
            peer["cur_users"] = cur_users
            peer["rdy"] = rdy
            info("%s peer server [%d]: %s", action, sid, str(peer))

            self.I.WS.onGetPeerServer( peer, name, sid, status )
        else:
            peer = self.I.WS.peers.pop(sid, None)
            if peer is not None:
                peer["on"] = 0
                peer["rdy"] = 0
            self.I.WS.onGetPeerServer( peer, name, sid, PEER_DELETED )
            # сдох, удаляем
            info("remove peer server [%d]: %s", sid, str(peer))

        self.response["ok"] = 1 # ну так, что вообще живы
        self.fin()


