# -*- coding: utf-8 -*-

from base.helpers import *
import functools

import CC

addRelPath("logic")  # it's for `from requests import *` since we can't import it as logic.requests

from instr import *

from modeldata.changes import MakeModelChangeString
from tornado.options import options
import tornado.ioloop

import ibilling
import EC
from baserequest import BaseRequest

# from requests import *
from enums import *

from modeldata.validator import Validator
from binascii import crc32

from modeldata.changes import IGuidGenerator
from UserDict import DictMixin

from geo_cfg import DEFAULT_GEO_LOCATION

# we need this because of 'gen-py' subdirectory
addRelPath('thrift_pw/statistics/gen-py')
from StatisticCore.ttypes import ResourceChangeItem

import iaeria
import iarcgames


def parse(method):
    @functools.wraps(method)
    def wrapper(self, *args, **kwargs):
        self.parse()
        if not self.acc.getConfigValue("TESTS_ENABLED"):
            self.acc.model.setTime()
        return method(self, *args, **kwargs)

    return wrapper


##----------------------------------------------------------------------------------------------------------------------
## декоратор для методов RequestHandler, работающих с новой Model Data
## прописывает, чтобы автоматические modelChange добавлялись в наш self.response[]
def model_callback(method):
    @functools.wraps(method)
    def wrapper(self, *args, **kwargs):
        # изменения Model Data пусть автоматически направляются в наш self.modelChangeOp:
        rid = self.getIntParam("rid")
        if self.arguments != None and rid != None and rid != BaseRequest.UnindexedRequestIndex:
            self.acc.model.setComment(rid)
        else:
            self.acc.model.setComment("auto")
        self.acc.model.write(self)
        return method(self, *args, **kwargs)

    return wrapper


##----------------------------------------------------------------------------------------------------------------------
## декоратор для RequestHandler, работающих с новой Model Data
## прописывает, чтобы автоматические modelChange добавлялись в self.acc.pending_changes
def model_pending(method):
    @functools.wraps(method)
    def wrapper(self, *args, **kwargs):
        self.acc.model.write(self.acc.pending)
        return method(self, *args, **kwargs)

    return wrapper


##----------------------------------------------------------------------------------------------------------------------
## декоратор для callback-ов SubAction, вида onSubAction(self, response)
## переносит model changes, накопленные в response["ModelXxx"] в acc.pending_changes
def response2pending(method):
    @functools.wraps(method)
    def wrapper(self, response):
        self.postponeResponseChanges(response=response)
        return method(self, response)

    return wrapper


##----------------------------------------------------------------------------------------------------------------------
## декоратор для методов RequestHandler, которым нужен точный тайминг времени исполнения собственно запроса,
## исключающий время ожидания асинхронных операций (т.е. не учитываем время, когда ждем ответов БД, биллинга, аггрегатора..)
RESPONSE_TIMING_KEY = "tmg"


def action_timing(method):
    @functools.wraps(method)
    def wrapper(self, *args, **kwargs):
        t0 = time.clock()
        ##action_name = getattr(self, "action", "")
        ##info("action_timing START %s(%r) t0=%5.5f" % (action_name, method, t0)) #!!!!!!!!!!!!!!!!!!!!!!!!
        # -----
        method(self, *args, **kwargs)
        # -----
        t1 = time.clock()
        timing = self.response.get(RESPONSE_TIMING_KEY, 0.0)
        ##info("action_timing fin %s(%r) t1=%5.5f, prev timing=%5.5f" % (action_name, method, t1, timing)) #!!!!!!!!!!!!!!!!!!!!!!!!
        timing += t1 - t0
        self.response[RESPONSE_TIMING_KEY] = timing
        ##info("action_timing FIN %s(%r) t1-t0=%5.5f, new timing=%5.5f" % (action_name, method, t1-t0, timing)) #!!!!!!!!!!!!!!!!!!!!!!!!

    return wrapper


##----------------------------------------------------------------------------------------------------------------------
## декоратор для методов любых классов, которым доступен self.I.WS;
## замеряет время операции и добавляет его отдельной категорией в словарь instrumented actions
def separate_timing(method):
    @functools.wraps(method)
    def wrapper(self, *args, **kwargs):
        t0 = time.clock()
        # -----
        method(self, *args, **kwargs)
        # -----
        t1 = time.clock()
        event_name = "%s.%s" % (self.__class__.__name__, method.__name__)
        self.I.WS.instrumentAction(event_name, t1 - t0)

    return wrapper


##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------
class ResponseObject(object):
    def __init__(self, key):
        self.key = key
        self.comments = [{}]

    # Возвращает true если пытаемся сделать "add" при наличии "del", или "del" при наличии "add"
    def opAddIfHaveDel(self, comment, path, op, params):
        if self.comments[0].has_key(comment):
            for i in range(0, len(self.comments[0][comment])):
                param = self.comments[0][comment][i]
                param_path = param[0]
                param_op = param[1]
                param_params = param[2]
                if param_path == path and param_op == "del" and op == "add":
                    return True
                if param_path == path and param_op == "add" and op == "del":
                    return True
        return False

    def addResponse(self, comment, path, op, params):
        if self.comments[0].has_key(comment):
            # Если больше 100 записей - не пытаемся объединять, затратное это дело....
            if len(self.comments[0][comment]) < 100:
                for i in range(0, len(self.comments[0][comment])):
                    param = self.comments[0][comment][i]
                    param_path = param[0]
                    param_op = param[1]
                    param_params = param[2]
                    if param_path == path and param_op == op and isinstance(param_params, dict) and isinstance(params,
                                                                                                               dict):
                        if not self.opAddIfHaveDel(comment, path, op, params):
                            param[2].update(params)
                            return
            self.comments[0][comment].append([path, op, params])
        else:
            self.comments[0][comment] = [[path, op, params]]

    def makeDict(self):
        if len(self.comments[0]) == 0:
            # check for sequence types is required since self.key could be an array of one item
            # see SubActiom.__init__() and classes like Ban_account and Mute_accaount usage in
            # thrift_pw/account_management/acc_management_ws_handler.py
            self.comments[0][self.key[0] if hasattr(self.key, '__iter__') else self.key] = []
        return self.comments


##----------------------------------------------------------------------------------------------------------------------
##----------------------------------------------------------------------------------------------------------------------

class SubAction(object):
    debug = False
    # список ключей, которые нужно забрать у request или найти в **kwargs (если нет ни там, ни там - берем указанные здесь значения-заглушки)
    _Interfaces = dict(
            uid=0,  # user id
            acc=ClassDict(),  # user account (acc.model = пользовательская Model Data)
            I=None,  # "all server interfaces" dictionary
    )

    MODEL_CHANGE_KEYS = ['ModelData', 'FriendsData', 'PartyData', 'TamburData', 'GuildData', 'SiegeData',
                         'ConfigData', 'RecruitsData', 'callback', 'callback_ec']

    _DEFAULT_VERSION = "0.0.0.0"

    _DEFAULT_SUB_REQUEST = ClassDict(headers={"X-Real-IP": "127.0.0.1"})
    _DEFAULT_REQUEST = ClassDict(request=_DEFAULT_SUB_REQUEST)

    def __init__(self, arguments, fin_callback, request=None, **kwargs):
        # callback должен быть обязательно
        ## debug(" subAction[%s] arguments %s:", self.__class__.__name__, arguments )

        self.fin_callback = fin_callback

        self.arguments = arguments
        self.request = request

        rid = '-1'
        if self.arguments and hasattr(self.arguments, "rid"):
            rid = self.arguments.rid

        self.response = {"ok": 0, "ec": 0, "server": options.server_name}
        if rid != -1 and rid != "-1":
            self.response["ModelData"] = ResponseObject(rid)
        else:
            pass
        self.acc = None

        self.pending_save_data = 0  # можем попросить сохранить пользовательские данные по окончании обработки action

        ##log( "request: %r" % str(request) )
        ##log( "kwargs: %r" % str(kwargs) )
        ##log( "_Interfaces: %r" % str(SubAction._Interfaces) )

        for key, iBase in SubAction._Interfaces.iteritems():
            if kwargs:
                # интерфейсы типа HTTP, MC, SQL можно оверрайдить через дополнительный словарик; там же можно оверрайдить uid и acc (для тестов)
                iface = kwargs.get(key)
                if iface:
                    ##log( "kwargs set: %r=%r" % (str(key), str(iface)) )
                    setattr(self, key, iface)
                    continue

            if request:
                # если у request есть интересные нам интерфейсы, тоже заберем в свой объект -- чтобы не писать многоэтажное "self.request.I.MC.query(...)"
                iface = getattr(request, key, None)
                if iface != None:
                    ##log( "request set: %r=%r" % (str(key), str(iface)) )
                    setattr(self, key, iface)
                    continue

            # по умолчанию -- берем default-ные заглушки
            ##log( "default set: %r=%r" % (str(key), str(iBase)) )
            setattr(self, key, iBase)

        # в тестовые/фейковые запросы нужно засобачить поддельный заголовок, для случая когда нам хочется знать IP клиента
        request = request or self._DEFAULT_REQUEST
        if not getattr(request, "request", None):
            request.request = self._DEFAULT_SUB_REQUEST

    # принимаем параметры запроса в виде простого словаря (без вложенных списков на каждый параметр)
    def setArguments(self, **kwargs):
        # перепаковываем параметры в словарь..
        self.arguments = {}
        params = dict(**kwargs)
        if params:
            for key, value in params.iteritems():
                if not isinstance(value, list):
                    self.arguments[key] = [value]
                else:
                    self.arguments[key] = value  # и так уже список

    ##-------------------------------------------------------------------------------------
    # получаем аргументы (аналогично JsonHandler)
    def getParam(self, name, default=None):
        param_list = self.arguments.get(name)
        if param_list:
            value = param_list[0]
            if isinstance(value, basestring):
                value = urllib.unquote(value)
            return value  # tornado.escape.xhtml_escape(param_list[0])
        else:
            return default

    ##-------------------------------------------------------------------------------------
    # достаем первый параметр из списка значений 'name=' (обязательно числовой)
    def getIntParam(self, name, default=None):
        param_list = self.arguments.get(name)
        if param_list:
            value = param_list[0]
            if digit(value):
                return int(value)
        # fail:
        return default

        ##-------------------------------------------------------------------------------------

    # достаем первый параметр из списка значений 'name=' (обязательно числовой)
    def getFloatParam(self, name, default=None):
        param_list = self.arguments.get(name)
        if param_list:
            value = param_list[0]
            if testfloat(value):
                return float(value)
        # fail:
        return default

        ##-------------------------------------------------------------------------------------

    def getBoolParam(self, name, default=False):
        param_list = self.arguments.get(name)
        if param_list:
            value = param_list[0]
            return str2bool(value)
        # fail:
        return default

        ##-------------------------------------------------------------------------------------

    def getJsonParam(self, name, default=None, error="bad json data: "):
        param_list = self.arguments.get(name)
        if param_list and param_list[0]:
            value = param_list[0]
            if isinstance(value, basestring):
                value = urllib.unquote(value)
            try:
                data = json_loads(value)
                return data
            except:
                self.response["error"] = error + "%s=%s" % (str(name), str(value))
                self.response["error_json"] = printException(sys.exc_info())
        return default

    ##-------------------------------------------------------------------------------------
    ## вытаскиваем все простые аргументы (x:[y]) в виде словаря
    def getFlatParams(self, except_list=[]):
        ##info( "SubAction getFlatParams: %s" % self.arguments )
        arg_dict = {}
        if self.arguments:
            for key, arg in self.arguments.iteritems():
                if key and arg and isinstance(arg, list) and len(arg) == 1 and (key not in except_list):
                    arg_dict[key] = arg[0]
        ##info( "getFlatParams: arg_dict %s" % arg_dict )
        return arg_dict

    ##-------------------------------------------------------------------------------------
    def addArguments(self, **kwargs):
        ##info( "SubAction addArguments: %s" % kwargs )
        if kwargs:
            for k, v in kwargs.iteritems():
                self.arguments[k] = [v]

    def log(self):
        log(self.__class__.__name__ + ".onStart")

    ##-------------------------------------------------------------------------------------
    # проверяем, что значение есть в некотором "списке допустимых значений"
    def checkPossibleParam(self, name, possible, error="bad value", ec=EC.BAD_PARAM):
        val = self.getParam(name)
        setattr(self, name, val)
        if val in possible:
            return True
        else:
            self.response["error"] = error + " %r (possible values: %s)" % (val, possible)
            self.response["ec"] = ec

    ##-------------------------------------------------------------------------------------
    # проверяем, что значение есть в некотором "списке допустимых значений"
    def checkPossibleValue(self, val, possible, error="bad value", ec=EC.BAD_PARAM):
        if val in possible:
            return True
        else:
            self.response["error"] = error + " %r (possible values: %s)" % (val, possible)
            self.response["ec"] = ec

    ##-------------------------------------------------------------------------------------
    # проверяем, что есть непустой параметр "name" (если есть, ставим self.name)
    def checkValidParam(self, name, error="bad or missing param: ", ec=EC.BAD_PARAM):
        value = self.getParam(name)
        if isinstance(value, basestring):
            value = urllib.unquote(value)
        setattr(self, name, value)
        if value:
            return True
        else:
            self.response["error"] = str(error) + str(name)
            self.response["ec"] = ec

    # проверяем, что есть непустой и ненулевой параметр "name"
    def checkValidIntParam(self, name, error="bad or null int param: ", ec=EC.BAD_PARAM):
        val = self.getIntParam(name, None)
        setattr(self, name, val)
        if val is not None:
            return True
        else:
            self.response["error"] = str(error) + str(name)
            self.response["ec"] = ec

    # проверяем, что есть непустой и ненулевой параметр "name"
    def checkValidBoolParam(self, name, error="bad or null bool param: ", ec=EC.BAD_PARAM):
        val = self.getBoolParam(name, None)
        setattr(self, name, val)
        if val is not None:
            return True
        else:
            self.response["error"] = str(error) + str(name)
            self.response["ec"] = ec

    def checkIntParams(self, error="bad or null int params: ", ec=EC.BAD_PARAM):
        "Check and set a list of int params, list should be defined in self.intParams"
        errors = []
        for name in self.intParams:
            if not self.checkValidIntParam(name):
                errors.append(name)
        if errors:
            self.response["error"] = str(error) + ', '.join(str(name) for name in errors)
            self.response["ec"] = ec
        else:
            return True

    # проверяем, что есть непустой и ненулевой параметр "name"
    def checkValidFloatParam(self, name, error="bad or null float param: ", ec=EC.BAD_PARAM):
        val = self.getFloatParam(name, None)
        setattr(self, name, val)
        if val is not None:
            return True
        else:
            self.response["error"] = str(error) + str(name)
            self.response["ec"] = ec

    def checkFloatParams(self, error="bad or null float params: ", ec=EC.BAD_PARAM):
        "Check and set a list of float params, list should be defined in self.intParams"
        errors = []
        for name in self.floatParams:
            if not self.checkValidFloatParam(name):
                errors.append(name)
        if errors:
            self.response["error"] = str(error) + ', '.join(str(name) for name in errors)
            self.response["ec"] = ec
        else:
            return True

    # продлеваем время жизни юзера на сервере
    def touch(self):
        touch(self.acc)

    # вернуть ответ (аналогично JsonHandler)
    def fin(self):
        if self.acc and self.acc.model and not isinstance(self.acc.model, dict):
            self.acc.model.setComment("auto")
        if self.fin_callback:
            # поручаем tornado IOLoop вызвать указанный callback после того как мы вернем управление (и корректно отработают все декораторы)
            if not self.I.WS.TEST_MODE:
                loop = tornado.ioloop.IOLoop.instance()
                _callback = functools.partial(self.fin_callback, self.response)
                loop.add_callback(_callback)
            else:
                # в тестовом режиме вызываем callback напрямую
                self.fin_callback(self.response)
        if self.pending_save_data:
            self.I.WS.saveUserData(self.acc)

    def fail(self, message, code):
        warn("%s action fail: ec=%s, message=%s", getattr(self, "action", ""), code, message)
        self.errorResponse(code, message)

    def errorResponse(self, error, errorText=None, errorArgs=None):
        self.response["ok"] = 0

        if isinstance(error, int):
            self.response["ec"] = error
            self.response["error"] = errorText
        else:
            self.response["ec"] = EC.DEBUG_MESSAGE
            self.response["error"] = error

        if errorArgs != None:
            self.response["error_args"] = errorArgs

        self.fin()

    def onBuyError(self, response, needGold=0):
        code = response["code"]
        if code == EC.NOT_ENOUGH_RESOURCES:
            self.errorResponse(EC.NOT_ENOUGH_RESOURCES, "Not enough resources")
        elif code == EC.BILLING_BUSY:
            self.errorResponse(EC.BILLING_BUSY, "Billing is busy, please don't spam it")
        elif code == EC.NOT_ENOUGH_GOLD or code == ibilling.BILLING_ZZIMA_OVERDRAFT:
            self.errorResponse(EC.NOT_ENOUGH_GOLD, "Not enough gold",
                               {"cost": needGold, "gold": self.acc.model.Resources.Gold})
        elif code <= -1000 and str(code)[
                               :-1] == '-100':  # любая -100х ошибка кроме -1008(BILLING_ZZIMA_OVERDRAFT) означает что у нас проблема с аккаунтом
            self.acc.model.LordInfo.BillingStatus = Billing.UserProblem
            self.acc.model.Resources.Gold = 0
            self.errorResponse(EC.BILLING_ACCOUNT_PROBLEM, "Billing account problem")
        else:
            self.acc.model.LordInfo.BillingStatus = Billing.Fail
            self.acc.model.Resources.Gold = 0
            self.errorResponse(EC.BILLING_FAILED, "Billing fail")

    def buy(self, price, callbackBilling, callbackFunc, reason, check_for_hero = False):
        if not self.acc.model.canBuy(price, check_for_hero):
            if not self.acc.model.isEnoughGold(price, check_for_hero):
                if self.acc.model.LordInfo.BillingStatus == Billing.Fail:
                    self.onBuyError({"code": EC.BILLING_FAILED}, self.needGold)
                elif self.acc.model.LordInfo.BillingStatus == Billing.UserProblem:
                    self.onBuyError({"code": EC.BILLING_ACCOUNT_PROBLEM}, self.needGold)
                else:
                    self.onBuyError({"code": EC.NOT_ENOUGH_GOLD}, self.needGold)
            elif not self.acc.model.isEnoughResources(price):
                self.onBuyError({"code": EC.NOT_ENOUGH_RESOURCES}, self.needGold)
            return

        self._price = price

        if int(price.Gold) != 0:
            self._callback = callbackBilling
            self.I.BILL.reserveAmount(self.acc.auid, int(price.Gold), reason, self.onBuyConfirm)
        else:
            self._callback = callbackFunc
            self.onBuyConfirm({"code": ibilling.ERROR_CODE_OK})

    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    def onBuyConfirm(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            if int(self._price.Perl) != 0:
                if self.acc.model.Resources.Perl - int(self._price.Perl) < 0:
                    self.acc.model.Resources.Perl = 0
                else:
                    self.acc.model.Resources.Perl -= int(self._price.Perl)
            if int(self._price.RedPerl) != 0:
                if self.acc.model.Resources.RedPerl - int(self._price.RedPerl) < 0:
                    self.acc.model.Resources.RedPerl = 0
                else:
                    self.acc.model.Resources.RedPerl -= int(self._price.RedPerl)
            if int(self._price.Resource1) != 0:
                if self.acc.model.Resources.Resource1 - int(self._price.Resource1) < 0:
                    self.acc.model.Resources.Resource1 = 0
                else:
                    self.acc.model.Resources.Resource1 -= int(self._price.Resource1)
            if int(self._price.Resource2) != 0:
                if self.acc.model.Resources.Resource2 - int(self._price.Resource2) < 0:
                    self.acc.model.Resources.Resource2 = 0
                else:
                    self.acc.model.Resources.Resource2 -= int(self._price.Resource2)
            if int(self._price.Resource3) != 0:
                if self.acc.model.Resources.Resource3 - int(self._price.Resource3) < 0:
                    self.acc.model.Resources.Resource3 = 0
                else:
                    self.acc.model.Resources.Resource3 -= int(self._price.Resource3)
            if int(self._price.Silver) != 0:
                if self.acc.model.Resources.Silver - int(self._price.Silver) < 0:
                    self.acc.model.Resources.Silver = 0
                else:
                    self.acc.model.Resources.Silver -= int(self._price.Silver)
            if int(self._price.Population) != 0:
                if self.acc.model.Resources.Population - int(self._price.Population) < 0:
                    self.acc.model.Resources.Population = 0
                else:
                    self.acc.model.Resources.Population -= int(self._price.Population)
            if int(self._price.CWPoints_Player) != 0:
                if self.acc.model.Resources.CWPoints_Player - int(self._price.CWPoints_Player) < 0:
                    self.acc.model.Resources.CWPoints_Player = 0
                else:
                    self.acc.model.Resources.CWPoints_Player -= int(self._price.CWPoints_Player)
            if int(self._price.Resource1_Rare) != 0:
                if self.acc.model.Resources.Resource1_Rare - int(self._price.Resource1_Rare) < 0:
                    self.acc.model.Resources.Resource1_Rare = 0
                else:
                    self.acc.model.Resources.Resource1_Rare -= int(self._price.Resource1_Rare)
            if int(self._price.Resource2_Rare) != 0:
                if self.acc.model.Resources.Resource2_Rare - int(self._price.Resource2_Rare) < 0:
                    self.acc.model.Resources.Resource2_Rare = 0
                else:
                    self.acc.model.Resources.Resource2_Rare -= int(self._price.Resource2_Rare)
            if int(self._price.Resource3_Rare) != 0:
                if self.acc.model.Resources.Resource3_Rare - int(self._price.Resource3_Rare) < 0:
                    self.acc.model.Resources.Resource3_Rare = 0
                else:
                    self.acc.model.Resources.Resource3_Rare -= int(self._price.Resource3_Rare)
            if int(self._price.Shard) != 0:
                if self.acc.model.Resources.Shard - int(self._price.Shard) < 0:
                    self.acc.model.Resources.Shard = 0
                else:
                    self.acc.model.Resources.Shard -= int(self._price.Shard)

            for ck, cv in self._price.Currencies.iteritems():
                if self.acc.model.Resources.Currencies[ck] - int(cv) < 0:
                    self.acc.model.Resources.Currencies[ck] = 0
                else:
                    self.acc.model.Resources.Currencies[ck] -= int(cv)

            if int(self._price.Gold) != 0:
                self.acc.model.Resources.Gold -= int(self._price.Gold)
                if self.acc.model.Resources.Gold <= 0:
                    warn("WARNING! GOLD_ACHTUNG happened in subaction GOLD = %r for USER = %r",
                         self.acc.model.Resources.Gold, self.acc.uid)

            # заказываем сохранение пользовательского аккаунта в монго
            self.pending_save_data = 1

        self._callback(response)

    def doConfirmWriteOff(self, response):
        if not hasattr(self, "needGold"):
            return

        reserveId = response.get("reserveId", 0)
        if self.needGold and reserveId == 0:
            self.onBuyError(response, self.needGold)
            return

        if self.needGold and reserveId:
            self.I.BILL.confirmWriteOff(self.acc.db.auid, reserveId, self.onConfirmWriteOff)

    def onConfirmWriteOff(self, response):
        code = response["code"]
        if code != ibilling.ERROR_CODE_OK:
            err("Billing confirmWriteOff error! %r" % response)

    ##-------------------------------------------------------------------------------------
    ## добавляем к списку response.model[] новую "строчку изменений": [comment, path, op, change]
    def writeStringToResponse(self, key, comment, path, op, params):
        if not self.response.has_key(key):
            self.response[key] = ResponseObject(key)
        if isinstance(self.response[key], ResponseObject):
            self.response[key].addResponse(comment, path, op, params)
        else:
            self.response[key].append(MakeModelChangeString(comment, path, op, params))

    @staticmethod
    def wrapPendingMessages(acc, uid, response):
        # DAN: заворачиваем накопленные pending model changes (например, от операций выдачи game results) в соотв. абстрактный response
        if acc and acc.pending_changes:
            ## info( "------------- wrapPendingMessages (uid=%s): pending model changes: ----------\n%s" % (uid, str(acc.pending_changes)) )

            for obj in acc.pending_changes:
                ## key, val = obj.popitem() # "ModelData" : { model change } -- плохо, получается разрушающее чтение (не годится для промежуточных дампов в тестах)
                for key, val in obj.iteritems():
                    ## debug( "sendPendingMessages: %s : %s", key, val )
                    response[key] = response.get(key) or []
                    if isinstance(response[key], ResponseObject):
                        response[key] = response[key].makeDict()
                    response[key].append(val)

    # DAN: забираем накопившиеся pending model changes (например, от операций выдачи game results)
    def sendPendingMessages(self, destinationDict=None):
        if not destinationDict:
            destinationDict = self.response
        self.wrapPendingMessages(self.acc, self.acc.uid, destinationDict)
        self.acc.pending_changes = []

        # DAN: забираем накопившиеся long-polling events (например, от операций с френдами и партиями)

    def sendPendingEvents(self, destinationDict=None):
        # helper для сортировки
        def extractMsgId(event_dict):
            try:
                for comment_key, event_data in event_dict.iteritems():
                    return toint(event_data["msg_id"])
            except:
                pass

        if not destinationDict:
            destinationDict = self.response

        if self.acc.getConfigValue("SEND_PENDING_EVENTS"):
            # для отладки прикладываем полную копию исходных pending_events
            destinationDict["pending_events"] = self.acc.pending_events[:]

        for key in self.MODEL_CHANGE_KEYS:
            destinationDict[key] = destinationDict.get(key) or []

        # пакуем копию model changes на уровень response["XxxData"]
        if self.acc.pending_events:
            ##info("self.acc.pending_events before sort: %s" % self.I.MD.pretty(self.acc.pending_events) )
            # сначала предпримем попытку отсортировать массив changes по "msg_id" (не всегда поможет, но не повредит)
            self.acc.pending_events.sort(None, extractMsgId)
            ##info("self.acc.pending_events after sort: %s" % self.I.MD.pretty(self.acc.pending_events) )

            for event_dict in self.acc.pending_events:  # event_dict = { "party": ... }
                if event_dict and isinstance(event_dict, dict):
                    for comment_key, event_data in event_dict.iteritems():  # comment_key = "party", event_data = { "PartyData": ..., "msg_id": ... }
                        if event_data and isinstance(event_data, dict):
                            for key, data in event_data.iteritems():  # key="PartyData", data=[<model changes>] }
                                if data:
                                    if key in self.MODEL_CHANGE_KEYS:
                                        destinationDict[key].extend(data)
                                        # ~ elif key == "init":
                                        # ~ # отдельно надо выпихнуть на root-уровень response инициализационные пакеты (сейчас такое бывает для PartyData)
                                        # ~ if data and isinstance(data, dict):
                                        # ~ for key2,data2 in data.iteritems():
                                        # ~ destinationDict["init"] = destinationDict.get("init") or {}
                                        # ~ destinationDict["init"][key2] = data2

        self.acc.pending_events = []

    # переводим накопленные model changes из текущего response в acc.pending_changes
    @staticmethod
    def _postponeResponseChanges(response, acc):
        for ModelKey in SubAction.MODEL_CHANGE_KEYS:
            model_changes_generated = response.get(ModelKey)
            if model_changes_generated:
                if isinstance(model_changes_generated, ResponseObject):
                    model_changes_generated = model_changes_generated.makeDict()
                info("postponed model changes: %s", model_changes_generated)
                for change in model_changes_generated:
                    acc.pending_changes.append({ModelKey: change})

    # переводим накопленные model changes из текущего response в acc.pending_changes
    def postponeResponseChanges(self, response=None, acc=None):
        if response is None:
            response = self.response
        if acc is None:
            acc = self.acc
        SubAction._postponeResponseChanges(response, acc)

    # когда приходит HTTP POST, обычно нужно достать из тела поста аргументы и добавить их к аргументам GET-запроса
    def unpackJsonBodyArguments(self):
        if self.request.request and self.request.request.body:
            unquoted_body = urllib.unquote(self.request.request.body)
            ## info("unpackJsonBodyArguments unquoted_body: %s" % unquoted_body)
            body_dict = json_loads(unquoted_body)
            ## info("unpackJsonBodyArguments parsed body_dict: %s" % body_dict)
            ## info("unpackJsonBodyArguments request flat params: %s" % self.getFlatParams())
            args_dict = {}
            for k, v in body_dict.iteritems():
                key = str(k)
                if key[:5] == "json_" and (not isinstance(v, basestring)):
                    key = key[5:]  # json value уже все равно распаковали из строчки, так что убираем префикс
                args_dict[key] = v
            ## info("unpackJsonBodyArguments args_dict: %s" % args_dict)
            self.addArguments(**args_dict)
            ## info("unpackJsonBodyArguments updated flat params: %s" % self.getFlatParams())

    # добавить к собственному времени исполнения время исполнения вложенного SubAction (например, когда sn_login внутри себя вызывает login)
    def addResponseTiming(self, sub_response):
        timing = self.response.get(RESPONSE_TIMING_KEY, 0)
        if sub_response:
            sub_timing = sub_response.get(RESPONSE_TIMING_KEY, 0)
        else:
            sub_timing = 0
        info("addResponseTiming(%s): prev timing=%5.5f, sub_timing=%5.5f, new timing=%5.5f",
             getattr(self, "action", ""), timing, sub_timing, timing + sub_timing)
        timing += sub_timing
        self.response[RESPONSE_TIMING_KEY] = timing

    def onConnectionClose(self):
        pass

    def makeAccRandom(self, add=0):
        return self.acc.model.getRandom(self.acc.model.LordInfo.RandomSeed + int(self.arguments.rid or 0) + add)

    @staticmethod
    def convertResponseObjects(save_data):
        if isinstance(save_data, dict):
            for key in save_data:
                if isinstance(save_data[key], ResponseObject):
                    save_data[key] = save_data[key].makeDict()

    def checkRid(self, action=""):
        from handlers import repeated_requests
        actions = repeated_requests.get(action, {})
        debug("checkRid %s %r", action, actions)
        login = ""
        if hasattr(self, "sn_id") and hasattr(self.acc, "sn_login"):
            login = "%s#%s" % (str(self.sn_id), str(self.sn_login))
        else:
            if self.acc.login:
                login = self.acc.login.lower()
        if login:
            rid = self.getIntParam("rid", 0)
            actions = repeated_requests.get(action, {})
            check_rid = actions.get(login, None)
            if action != "collect_production_results":
                if check_rid and check_rid[0] == rid and check_rid[1] > toint(time.time()):
                    actions[login] = (rid, toint(time.time()) + CC.REPEATING_TIMEOUT)
                    warn("repeated rid param for %s login=%r rid=%r timeout=%r", action, login, rid, check_rid[1])
                    return True
                actions[login] = (rid, toint(time.time()) + CC.REPEATING_TIMEOUT)
                return False
            else:
                if check_rid:
                    if check_rid[0] >= rid:
                        actions[login] = (rid, toint(time.time()) + CC.REPEATING_TIMEOUT)
                        warn("collect_production_results: previous rid param for %s login=%r rid=%r timeout=%r", action, login, rid, check_rid[1])
                        return True
                    elif check_rid[1] >= toint(time.time()):
                        actions[login] = (rid, toint(time.time()) + CC.REPEATING_TIMEOUT)
                        warn("collect_production_results: repeated rid param for %s login=%r rid=%r timeout=%r", action, login, rid, check_rid[1])
                        return True

                    actions[login] = (rid, toint(time.time()) + CC.REPEATING_TIMEOUT)
        return False


MAINTENANCE_NORMAL = 0
MAINTENANCE_PENDING = 1
MAINTENANCE_ONGOING = 2


def getMaintenanceInfo(code):
    if code == MAINTENANCE_PENDING:
        return (EC.MAINTENANCE_STAGE_PENDING, 'Maintenance pending')
    elif code == MAINTENANCE_ONGOING:
        return (EC.MAINTENANCE_STAGE_ONGOING, 'Maintenance ongoing')
    return (EC.OK, None)


def parseGeoLocation(api, sn_uid, remote_ip):
    geolocation = DEFAULT_GEO_LOCATION
    geo_info = ''
    try:
        location, aux_info = api.getLocationInfoByIP(remote_ip)
        info("Parse geolocation success (snuid=%s remote_ip=%s geolocation=%r aux_info=%r", sn_uid, remote_ip, location,
             aux_info)
        geolocation = utf8convert(unicode(location, "latin1"))
        geo_info = str(aux_info)
    except Exception, details:
        info(
            "Parse geolocation error: can't get location by IP, set default (snuid=%s remote_ip=%s geolocation=%r details=%r)",
            sn_uid, remote_ip, DEFAULT_GEO_LOCATION, details)
    return geolocation, geo_info


def getBoundHeroClassId(talent):
    return 0 if (
    talent.Soulbound is None or talent.Soulbound == IGuidGenerator.InvalidUID) else talent.Soulbound.get().PersistentId
