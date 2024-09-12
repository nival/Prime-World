# -*- coding: utf-8 -*-

#!/usr/bin/env python
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

class JoinAction( BaseCheckVersionAction ):
    action = "l_join"
    

    """ Cлужебный handler, поддерживает 'action=who'. """
    @action_timing
    def onStart(self):
        info( "JoinAction.onStart: AGG=%s" % self.I.AGG )
        self.auid = self.getParam("auid0")
        self.token = self.getParam("token0")
        self.sn_id = self.getParam("snid1")
        self.sn_uid = self.getParam("snuid1")
        self.sn_token = self.getParam("sntoken1")
        self.snrefresh_token = self.getParam("snrefresh_token1")
        
        self.client_ver = self.getParam("ver", self._DEFAULT_VERSION)
        self._dont_log = options._dont_log
        
        self.registering = False

        self.response["ver"] = PWSOC_VERSION
        self.response["_depth"] = DEPTH_WS

        if not self.checkClientVersion( hi_med_only=True ):
            self.fin() # error codes are already set in checkClientVersion
            return

        if self.sn_id == 'st':
            self.sn_token = self.RecodeSteamToken(self.sn_token)
        
        self.user0 = self.I.WS.checkLoginToken(str(self.auid), self.token)
        if not self.user0:
            return self.markLoginFailed("auid token fail (auid=%s token=%r)" % (self.auid, self.token), EC.TOKEN_NOT_FOUND)

        # проверим цифровую подпись:
        self.secret = md5(self.user0.original_snuid) + md5(self.sn_uid)
        params = self.getParam('_params',{}) or self.getFlatParams()
        info("%s params: %s" % (self.action, params))

        if not checkParamsSignature( params, secret=self.secret ):
            return self.markLoginFailed("bad signature", EC.PWC_BAD_SIGNATURE)

        if (not self.sn_uid) or re.search(CC.SOCAGG_LOGIN_CHECK_EX, self.sn_uid):
            return self.markLoginFailed("bad snuid (snuid=%s)" % self.sn_uid, EC.AGGREGATOR_LOGIN_FAIL)

        # ок, похоже на логин.
        if self.checkSnToken(self.sn_id, self.sn_token):
            if self.checkPossibleValue( self.sn_id, CC.LOGIN_SOCIAL_NETWORK_NAMES, error="bad snid" ):
                ## логинимся через SocialAggregator (sntoken нам дали в открытом виде)
                self.I.AGG.join(self.auid, self.sn_uid, self.sn_token, self.sn_id, self.snrefresh_token, callback=self.onAggregatorJoin)
                return
            else:
                return self.markLoginFailed("bad sn (snid=%s)" % self.sn_id, EC.AGGREGATOR_LOGIN_FAIL)
        else:
            info("bad sntoken %r for sn %s", self.sn_token, self.sn_id)
            return self.markLoginFailed("bad sntoken (sntoken=%r)" % self.sn_token, EC.AGGREGATOR_LOGIN_FAIL)
    
    #------------------------------------------------------------------------------------
    # Social Aggregator ответил на авторизацию
    @action_timing
    def onAggregatorJoin(self, reply): # reply теперь приходит сразу распарсенный до dict-содержимого
        if not reply:
            return self.markLoginFailed('no aggregator reply', EC.AGGREGATOR_LOGIN_FAIL)
        try:
            info( "onAggregatorJoin: %s" % str(reply) )
            reason = reply.get("message", '')
            ecode = reply.get("error", 0)
            if ecode > 0 or reason:
                lcode = EC.AGGREGATOR_LOGIN_FAIL
                if ecode == 9:
                    lcode = EC.AGGREGATOR_JOIN_USER_EXISTS                    
                return self.markLoginFailed("aggregator join fail (code=%d reason=%r)" % (ecode, reason), lcode)
            else:
                auid = reply.get("auid", None)
                if auid != None and str(auid) == self.auid:
                    self.I.STATS.addSocialJoin( str(auid), str(self.sn_id), str(self.sn_uid) ) 
                    self.response["ok"] = 1
                    return self.updateSocialNetworkCount( auid )
        except:
            message = catch()
            agg_error = reply.get("error", 0)
            if agg_error:
                self.response['agg_error'] = agg_error 
            return self.markLoginFailed(message, EC.AGGREGATOR_LOGIN_FAIL)
        return self.markLoginFailed("aggregator join fail", EC.AGGREGATOR_LOGIN_FAIL)

