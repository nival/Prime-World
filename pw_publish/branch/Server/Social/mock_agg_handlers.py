# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# Mock Social Aggregator request handlers
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import httplib, signal, base64

import tornado.httpserver
import tornado.ioloop
import tornado.options
import tornado.web
import torndb # sql
from tornado.options import define, options

from instr import *

from iwebserver import *

##----------------------------------------------------------------------------------------------------------------------
## базовые web request handlers 
from handlers import * # JsonHandler, IfaceFactory
from subaction import SubAction

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

SA_ERROR_GENERIC = -1

class MockAggregatorHandler( JsonHandler ):
    """ обрабатываем внутренние 'аггрегаторские' запросы от рабочих серверов: login, register, get_info и т.п """
    
    internalActionMap = {
        # внутрикластерные команды; закрыты для внешних клиентов
        'login': 'onLogin',
        'register': 'onRegister',
        'join': 'onJoin',
        'merge': 'onMerge',
        'get_info': 'onGetInfo',
        'onSetProperty' : 'onSetProperty',
        'friends_info': 'onFriendsInfo',
    }
    
    ## SUBADDR и WS обязательны при работе c JsonHandler
    ## _Interfaces = dict( SUBADDR=None, WS=None, HTTP=None, ZZ=None )
    
    SOCIAL_NETWORKS = ['fb', 'zzima', 'ok', 'vk', 'st', 'arc', 'zzma']
    
    # -----------------------------------------
    # конвертируем наши уютные статусы и ошибки ("ok":1, "error":STRING) в те, что положены по протоколу ("error":0/<error_code_INT>, "message":STRING)
    def finConvert(self):
        if self.response.get("ok"):
            self.response.pop("ok")
            self.response["error"] = 0
        else:
            error_message = self.response.get("error")
            if error_message:
                self.response["message"] = error_message
            self.response["error"] = SA_ERROR_GENERIC

    # -----------------------------------------
    def fin(self):
        # конвертируем наши уютные статусы и ошибки ("ok":1, "error":STRING) в те, что положены по протоколу ("error":0/<error_code_INT>, "message":STRING)
        self.finConvert()
        # пишем результат в http response
        ##JsonHandler.fin(self)
        json_response = '%s' % self.I.MD.toJson( self.response, indent=4 )
        self.write(json_response)
        self.finish()


    # -----------------------------------------
    def onRegister(self):
        log( "onRegister" )
        # поведение register у заглушки ничем не отличается от login (так же возвращаем новый гестовый auid)
        return self.onLogin()
        
    def onGetBillingStatus(self):
        log( "onRegister" )
        self.response["get_billing_status"] = 1
        self.fin()
        
    def onSetProperty(self):
        log( "onSetProperty" )
        # SKIP
        self.response["ok"] = 1
        self.fin()
        
    # -----------------------------------------
    def onJoin(self):
        info( "onJoin" )
        self.fin()

    # -----------------------------------------
    def onMerge(self):
        info( "onMerge" )
        self.fin()

    # -----------------------------------------
    def onDeleteSn(self):
        info("onDeleteSn")
        self.fin()

    def onDeleteAccount(self):
        info("onDeleteAccount")
        self.fin()

    # -----------------------------------------
    def onGetInfo(self):
        info( "onGetInfo" )

        self.snid = self.getParam("snid", "fb")
        self.auid = tolong( self.getParam("auid") )
        self.include_secure_data = toint(self.getParam("include_secure_data", 0))
        
        if self.checkPossibleValue(self.snid, self.SOCIAL_NETWORKS, error="bad social network"):
            if self.auid:
                
                if self.snid == 'fb':
                    self.response["ok"] = 1
                    
                    auid = str(self.auid)
                    info_dict = { 
                        "name": "user_" + auid,                 # STRING
                        "gender": random.randint(0,3),           # 0 - not specified, 1 - male, 2 - female, 3 - other
                        "photo": "http://photo_" + auid + ".x", # link to photo
                        "age": random.randint(1,99),                
                    }
                    if self.include_secure_data:
                        info_dict["email"] = "user_" + auid + "@email.x" # email. Included if include_secure_data is true}
                        
                    self.response["get_info"] = { "fb": info_dict }
                elif self.snid == 'arc':
                    self.response["ok"] = 1

                    auid = str(self.auid)
                    info_dict = {
                        "name": "test999",
                        "account": "shtest999",
                        "sntoken": "c5fe7c48b941cde107900431e4840d21",
                        "snuid": "shtest999",
                        "id": 109886800
                    }
                    if self.include_secure_data:
                        info_dict["email"] = "user_" + auid + "@email.x" # email. Included if include_secure_data is true}

                    self.response["get_info"] = { "arc": info_dict, 'props':{'fsn': self.snid} }

                #~ elif self.snid == 'zzima':
                    #~ # обращаемся к ZZima API
                    #~ return self.I.ZZ.getInfo( self.auid, 1, 1, callback=self.onZZimaGetInfo )
                
            else:
                self.response["error"] = "bad auid"
        
        self.fin()
        
    # -----------------------------------------
    def onLogin(self):
        info( "onLogin" )
        info( "MockAggregatorHandler WS=%s, HTTP=%s, ZZ=%s" \
            % ( str(getattr(self, "WS", None)), str(getattr(self, "HTTP", None)), str(getattr(self, "ZZ", None))) )
        self.response["ver"] = SOCAGG_VERSION
        
        self.snid = self.getParam("snid", "fb")
        soc_server_ver = self.getParam("version", "0.0.0")
                
        # parse version
        ver_ok = False
        try:
            hi,med = soc_server_ver.split(".")[:2]
            if toint(hi) == SOCAGG_VERSION_HIGH and toint(med) == SOCAGG_VERSION_MED:
                ver_ok = True
            else:
                self.response["error"] = "soc.aggregator protocol version mismatch (%s)" % soc_server_ver;
        except:
            self.response["error"] = "bad version format"
        
        if ver_ok:
            if self.checkPossibleValue(self.snid, self.SOCIAL_NETWORKS, error="bad social network"):
                if self.checkValidParam("snuid"):
                    if self.checkValidParam("sntoken"):
                        
                        if self.snid == 'fb':
                            self.response["ok"] = 1
                            # выдаем на каждый логин некий crc64(sntoken) 
                            self.response["auid"] = md5_int64( self.sntoken ) #self.I.WS.nextInt64GUID( "auid" )
                        
                        elif self.snid == 'zzima':
                            # обращаемся к ZZima billing
                            res = md5_digest2binary( self.sntoken )
                            if res:
                                ## логинимся через ZZima (md5 от пароля нам дали в открытом виде)
                                try:
                                    self.I.ZZ.authorize( self.snuid, base64.b64encode(res), self.onZZimaAuthorize)
                                except:
                                    catch()
                                return
                                
                            else:
                                self.response["error"] = "can't convert auth string";

        self.fin()
        
    #------------------------------------------------------------------------------------
    def onFriendsInfo(self):
        self.fin()
        
    #------------------------------------------------------------------------------------
    # ZZima ответила на авторизацию
    def onZZimaAuthorize(self, query):
        reply = query.get("r")
        if reply:
            info( "onZZimaAuthorize: %s" % str(reply) )
            error_code = reply.get("code", -1)
            if error_code == 0:
                # ZZima нас пустила, теперь вопрос только в регистрации внутри нашей database и логине
                self.response["auid"] = reply.get("userId", 0)
                self.response["ok"] = 1
                
            else:
                self.response["error"] = "zzima authorization fail: error code %d" % error_code
        else:
            self.response["error"] = "zzima authorization fail"
            
        self.fin()
        
        
    #------------------------------------------------------------------------------------
    # ZZima ответила на getInfo (можем вытащить пол игрока)
    def onZZimaGetInfo(self, http_response):
        try:
            reply = json_loads( http_response.body ).get("response")
            info( "onZZimaGetInfo: response %s" % str(reply) )

            info_dict = { 
                "name":   reply.get("nick", ""),         # STRING
                "gender": toint( reply.get("sex") ),       # 0 - not specified, 1 - male, 2 - female, 3 - other
                "photo":  reply.get("picture_80", ""),  # link to photo
                "age":       0,                
            }
            
            if self.include_secure_data:
                info_dict["email"] = reply.get("email", "") # email. Included if include_secure_data is true}
            
            self.response["get_info"] = { "zzima": info_dict }
            self.response["ok"] = 1
            
        except:
            self.response["error"] = "zzima getinfo fail"
            self.response["zzima_response"] = str(http_response)
            
        # в любом случае (даже если с getinfo не выгорело) продолжаем sublogin
        self.fin()

##---------------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------------

# нахлобучиваем на http-шный RequestHandler интерфейс локального SubAction, причем reply не возвращается, а просто кладется в локальный self.reply
class LocalAggregatorHandler( SubAction, MockAggregatorHandler ):
    """ единственное, что мы всерьез оверрайдим, это fin (нужно преобразовать формат ответа, ok:1 -> error:0) """
    ## _Interfaces = {} # никакие особые интерфейсы нам не нужны
    
    def __init__(self):
        SubAction.__init__( self, dict(), self.callback )
        
    def callback(self, reply):
        self.reply = reply
        
    def fin(self):
        self.finConvert()
        #SubAction.fin(self) -- давайте синхронно вызовем, чтобы не ломать голову об IOLoop callbacks
        if self.fin_callback:
            self.fin_callback( self.response )
            
        
        
