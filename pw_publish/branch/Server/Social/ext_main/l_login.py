# -*- coding: utf-8 -*-
#
# Social Aggregator Login

import sys, os, time, logging, base64

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

_addPath('..')
from handlers import * 
from subaction import SubAction, action_timing

import iaggregator

from login import BaseCheckVersionAction
from instr import * 

import EC
import CC

##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------

class LauncherLoginAction( BaseCheckVersionAction ):
    action = 'l_login'
    """ Cлужебный handler, поддерживает 'action=l_login'. """
    @action_timing
    def onStart(self):
        info( "LauncherLoginAction.onStart" )
        self.auid = self.getParam("auid")

        self.sns = []
        for index in xrange( len(CC.LOGIN_SOCIAL_NETWORK_NAMES) ):
            snid = self.getParam("snid"+str(index))
            snuid = self.getParam("snuid"+str(index))
            sn_token = self.getParam("sntoken"+str(index))
            snrefresh_token = self.getParam("snrefresh_token"+str(index))
            if snid and snuid and sn_token:
                self.sns.append( (snid, snuid, sn_token, snrefresh_token) )
        
        self.client_ver = self.getParam("ver", self._DEFAULT_VERSION)
        self._dont_log = options._dont_log
        
        self.response["ver"] = PWSOC_VERSION
        self.response["_depth"] = DEPTH_WS

        isFailed = False
        if len(self.sns) == 0:
            self.response["error"] = "no social networks defined";
            self.response["ec"] = EC.AGGREGATOR_LOGIN_FAIL
            isFailed = True
        elif self.checkClientVersion( hi_med_only=True ): 
            for snid, snuid, sntoken, snrefresh_token in self.sns:
                if not self.checkLoginSymbols(snid, snuid, sntoken):
                    message = "bad login (snid=%s snuid=%s sntoken=%r" % (snid, snuid, sntoken)
                    info(message)
                    self.response["error"] = message
                    self.response["ec"] = EC.AGGREGATOR_LOGIN_FAIL
                    isFailed = True
                    break

        self.index = 0
        if isFailed:
            #-- FAIL: отвечаем юзеру если хотя бы одна сеть не прошла проверку
            self.fin()
        else:
            # логинимся на первую по списку соц.сеть
            snid, snuid, sntoken, snrefresh_token = self.sns[self.index]
            self.I.AGG.login( snuid, sntoken, snid, False, snrefresh_token, callback=self.onAggregatorLogin)
            return

    #------------------------------------------------------------------------------------
    # Social Aggregator ответил на авторизацию
    @action_timing
    def onAggregatorLogin(self, reply): # reply теперь приходит сразу распарсенный до dict-содержимого
        try:
            if reply:
                info( "onAggregatorLogin: %s" % str(reply) )
                if reply.get("message"):
                    return self.markLoginFailed('aggregator login fail (reason=%r)' % reply.get("message"), EC.AGGREGATOR_LOGIN_FAIL)

                auid = reply.get("auid", None)
                if str(auid) == self.auid:
                    # aggregator login по реквизитам очередной соц.сети прошел успешно.
                    self.index += 1
                    if self.index < len(self.sns):
                        snid, snuid, sntoken, snrefresh_token = self.sns[self.index]
                        return self.I.AGG.login( snuid, sntoken, snid, False, snrefresh_token, callback=self.onAggregatorLogin)
                    else:
                        self.response["ok"] = 1
                        self.fin()
                        return 
                else:
                    return self.markLoginFailed('auid differs', EC.AGGREGATOR_LOGIN_FAIL)
        except:
            return self.markLoginFailed(catch(), EC.AGGREGATOR_LOGIN_FAIL)
        return self.markLoginFailed('aggregator login fail', EC.AGGREGATOR_LOGIN_FAIL)
