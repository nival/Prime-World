# -*- coding: utf-8 -*-
#
# Queue Login

import sys, os, time, logging

from handlers import *
from subaction import SubAction, action_timing

import cfg

from login import BaseCheckVersionAction
from instr import * 

import EC
import CC

class QueueAction( BaseCheckVersionAction ):

    def OnLogin(self, authorized, gserver, token, qlength, etime, errorCode):
        if errorCode == 0:
            if authorized:
                if gserver:
                    self.response["gserver"] = gserver
                if token:
                    self.response["token"] = token
            if qlength > 0:
                self.response["length"] = qlength
            if etime > 0:
                self.response["time"] = etime
            self.successReply()
        else:
            self.errorReply('Error queue login', errorCode)

    def successReply(self):
        self.response["ok"] = 1
        self.fin()

    def errorReply(self, message, code):
        info( "errorReply: ec=%s, message=%s" % (code, message) )
        self.response["error"] = message
        self.response["ec"] = code
        self.fin()


class QueueLoginAction( QueueAction ):
    action = "qlogin"

    """ Cлужебный handler, поддерживает 'action=qlogin'. """
    @action_timing
    def onStart(self):
        self.sn_uid = self.getParam("snuid")
        self.sn_token = self.getParam("sntoken")
        
        self.client_ver = self.getParam("ver", self._DEFAULT_VERSION)
        self._dont_log = options._dont_log
        
        if self.checkClientVersion( hi_med_only=True ): 
            if self.sn_uid and (not re.search( CC.SOCAGG_LOGIN_CHECK_EX, self.sn_uid )):
                context = self.I.WS.checkLoginContext(self.sn_uid, self.sn_token)
                if context:
                    self.I.WS.loginUser(self.sn_uid, context, self.OnLogin)
                    return 
                else:
                    warn("QueueLoginAction: no user found (%s, %s)", self.sn_uid, self.sn_token)
                    return self.errorReply("no user found", EC.AGGREGATOR_LOGIN_FAIL)
            else:
                return self.errorReply("bad snuid", EC.AGGREGATOR_LOGIN_FAIL)
        #-- FAIL: отвечаем юзеру
        self.fin()


class QueuePollAction( QueueAction ):
    action = "qpoll"

    """ Cлужебный handler, поддерживает 'action=qpoll'. """
    @action_timing
    def onStart(self):
        self.sn_uid = self.getParam("snuid")
        self.sn_token = self.getParam("sntoken")
        
        self.client_ver = self.getParam("ver", self._DEFAULT_VERSION)
        self._dont_log = options._dont_log
        
        if self.checkClientVersion( hi_med_only=True ): 
            if self.sn_uid and (not re.search( CC.SOCAGG_LOGIN_CHECK_EX, self.sn_uid )):
                context = self.I.WS.checkLoginContext(self.sn_uid, self.sn_token)
                if context:
                    self.I.WS.pollUser(self.sn_uid, context, self.OnLogin)
                    return 
                else:
                    warn("QueuePollAction: no user found (%s, %s)", self.sn_uid, self.sn_token)
                    return self.errorReply("no user found", EC.AGGREGATOR_LOGIN_FAIL)
            else:
                return self.errorReply("bad snuid", EC.AGGREGATOR_LOGIN_FAIL)
        #-- FAIL: отвечаем юзеру
        self.fin()


class QueueCancelAction( QueueAction ):
    action = "qcancel"

    """ Cлужебный handler, поддерживает 'action=qpoll'. """
    @action_timing
    def onStart(self):
        self.sn_uid = self.getParam("snuid")
        self.sn_token = self.getParam("sntoken")
        
        self.client_ver = self.getParam("ver", self._DEFAULT_VERSION)
        self._dont_log = options._dont_log
        
        if self.checkClientVersion( hi_med_only=True ): 
            if self.sn_uid and (not re.search( CC.SOCAGG_LOGIN_CHECK_EX, self.sn_uid )):
                context = self.I.WS.checkLoginContext(self.sn_uid, self.sn_token)
                if context:
                    self.I.WS.cancelUser(self.sn_uid, context, self.OnLogin)
                    return 
                else:
                    warn("QueueCancelAction: no user found (%s, %s)", self.sn_uid, self.sn_token)
                    return self.errorReply("no user found", EC.AGGREGATOR_LOGIN_FAIL)
            else:
                return self.errorReply("bad snuid", EC.AGGREGATOR_LOGIN_FAIL)
        #-- FAIL: отвечаем юзеру
        self.fin()


class QueueMergeAction( BaseCheckVersionAction ):
    action = "l_merge"
    
    @action_timing
    def onStart(self):
        self.auid0 = self.getParam("auid0")
        self.auid1 = self.getParam("auid1")
        self.token0 = self.getParam("token0")
        self.token1 = self.getParam("token1")

        self.user0 = self.I.WS.checkLoginToken(str(self.auid0), self.token0)
        self.user1 = self.I.WS.checkLoginToken(str(self.auid1), self.token1)
        if self.user0:
            if self.user1:
                # проверим цифровую подпись:
                info("l_merge user0 %s:%s, user1 %s:%s" % (self.user0.snid, self.user0.snuid, self.user1.snid, self.user1.snuid))
                self.secret = md5(self.user0.snuid) + md5(self.user1.snuid)
                params = self.getParam('_params',{}) or self.getFlatParams()
                info("%s params: %s" % (self.action, params))
                if True or checkParamsSignature( params, secret=self.secret ):
                    self.I.WS.mergeAccounts(self.auid0, self.auid1, self.onReply)
                    return
                else:
                    return self.markLoginFailed("bad signature", EC.PWC_BAD_SIGNATURE)
            else:
                return self.markLoginFailed("auid token fail (auid=%s token=%r)" % (self.auid1, self.token1), EC.TOKEN_NOT_FOUND)
        else:
            return self.markLoginFailed("auid token fail (auid=%s token=%r)" % (self.auid0, self.token0), EC.TOKEN_NOT_FOUND)
        
    #------------------------------------------------------------------------------------
    def onReply(self, response):
        if response:
            self.response.update(response)
            if response['ok'] == 1:
                self.I.WS.deleteLoginToken(self.auid1)
        self.fin()


