# -*- coding: utf-8 -*-
#
# Social Aggregator Login
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, base64

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

_addPath('..')
from handlers import * # JsonHandler, globals: peers, users..
from subaction import SubAction, action_timing, separate_timing
#from instr import * 

import iaggregator

from login import BaseCheckVersionAction, LoginAction
from pwc_actions import PWConnectLoginAction

import time
import json

import EC
import CC


##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class AlienLoginAction( BaseCheckVersionAction ):
    action = "alien_login"
    """ Внешний логин, будет использоваться для server auth flow сторонних приложений (tower defence и проч.) после авторизации в нашем ланчере """
    @separate_timing
    @action_timing  
    def onStart(self):
        self.auid = self.getParam("snuid") # auid
        self.sntoken = self.getParam("sntoken") # pw token (challenge)
        self.client_ver = self.getParam("ver", self._DEFAULT_VERSION)
        
        self.response["ver"] = PWSOC_VERSION
            
        if self.checkClientVersion(): 
            if self.auid and (not re.search( CC.SOCAGG_LOGIN_CHECK_EX, self.auid )):
                #WARNING: self.checkSnToken is't used here since there is no snid here!
                #I'm not sure is it's correct to use snid = 'pwc' here. Anyway, checkSnToken has no special checks for pwc.
                if self.sntoken and (not re.search(CC.SOCAGG_TOKEN_CHECK_EX, self.sntoken)): # только hex символы?:
                    user = self.I.WS.checkLoginToken(self.auid, self.sntoken)
                    if user:
                        if getattr(user, "pwconnect", 0):
                            self.pwc_snuid = user.pwc_snuid
                            info("pwconnect alien login auid=%s: pwc_snuid=%s" % (self.auid, self.pwc_snuid))
                            return self.pwcLogin()
                        else:
                            info("pw alien login auid=%s" % (self.auid))
                            return self.subLogin()
                            
                    else:
                        return self.markLoginFailed("credentials failed, user not found (sn_uid=%s sntoken=%s)" % (self.auid, self.sntoken), EC.BAD_TOKEN)
                else:
                    return self.markLoginFailed("bad sntoken: %r" % self.sntoken, EC.AGGREGATOR_LOGIN_FAIL)
            else:
                return self.markLoginFailed("bad snuid", EC.AGGREGATOR_LOGIN_FAIL)

        #-- FAIL: отвечаем юзеру
        self.fin()            
    
    #------------------------------------------------------------------------------------
    @separate_timing
    def pwcLogin(self):
        # PW Connect 
        original_params = self.getFlatParams() # копия исходных параметров запроса, для проверки подписи
        info("original params: %s" % original_params) 
        subparams = ClassDict( snuid=[self.pwc_snuid], challenge=[self.sntoken], _params=[original_params] )
        subaction = PWConnectLoginAction( subparams, self.onPwcLogin, I=self.I )
        subaction.request = self.request
        subaction.onStart()
    
    #------------------------------------------------------------------------------------
    @separate_timing
    @action_timing  
    def onPwcLogin(self, pwc_response):
        # финальный ok должен зависеть от результата sublogin, так что в self.response pwc_response.ok попасть не должен
        pwc_ok = pwc_response.pop('ok',0) 
        # заливаем ответ Pwc Login поверх нашего собственного
        self.response.update( pwc_response )
        self.addResponseTiming( pwc_response )
        # ---------------
        if pwc_ok:
            return self.subLogin()
        # ---------------
        self.fin()
        
    def subLogin(self):
        # тривиально, ибо никакой дальнейшей судьбы у данного юзера в нашем кластере нет; только подтверждаем авторизацию для внешнего проекта, и прибиваем login token
        self.I.WS.deleteLoginToken( self.auid )
        self.response["ok"] = 1
        self.fin()
        
        
