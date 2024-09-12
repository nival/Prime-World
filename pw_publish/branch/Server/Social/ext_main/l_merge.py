# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# Social Aggregator Merge

import sys, os, time, logging, base64

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

_addPath('..')
from handlers import * 
from subaction import SubAction, action_timing
from base.helpers import md5

import iaggregator

from instr import * 
from login import BaseCheckVersionAction
from logic.building_remove import *

import EC
import CC

import ibilling

##-------------------------------------------------------------------------------------
class LauncherMergeBaseAction( BaseCheckVersionAction ):
    
    @action_timing
    def onProcess(self, auid0, auid1, email_md5, pwc_snuid):
        self.auid0 = auid0
        self.auid1 = auid1
        self.email_md5 = email_md5
        self.pwc_snuid = pwc_snuid
        # сначала нужно посмотреть, есть ли в биллинге золото для объединяемых аккаунтов (если на auid1 есть золото, нужно перенести на auid0)
        self.billingResponse = { self.auid0:None, self.auid1:None }
        self.I.BILL.getBalanceEx( self.auid0, callback=self.onCheckBilling0 )
        self.I.BILL.getBalanceEx( self.auid1, callback=self.onCheckBilling1 )
    
    @action_timing
    def onCheckBilling0(self, billing_response):
        info("l_merge.onCheckBilling0 (auid %s) response: %s" % (self.auid0, billing_response))
        self.billingResponse[self.auid0] = billing_response or {}
        self.checkBillingReplies()
        
    @action_timing
    def onCheckBilling1(self, billing_response):
        info("l_merge.onCheckBilling1 (auid %s) response: %s" % (self.auid1, billing_response))
        self.billingResponse[self.auid1] = billing_response or {}
        self.checkBillingReplies()
        
    def checkBillingReplies(self):
        if (self.billingResponse.get(self.auid0) is not None) and (self.billingResponse.get(self.auid1) is not None):
            # обе проверки баланса завершились (результаты разберем позже, в doBillingTransfer)
            # подтянем второй аккаунт
            self.I.AGG.getInfo( self.auid1, None, include_secure_data=1, callback=self.onGetAggProperties )
            
    def onGetAggProperties(self, agg_response):
        info("l_merge.onGetAggProperties (auid %s) agg_response: %s" % (self.auid1, agg_response))
        agg_info = agg_response.get('get_info')
        if agg_info:
            agg_properties = agg_info.get('props') or {}
            fsn = agg_properties.get('fsn')
            if fsn:
                sn_info = agg_info.get(fsn)
                if sn_info:
                    fsn_snid = fsn
                    fsn_snuid = sn_info.get('snuid', '')
                    if fsn_snid and fsn_snuid:
                        login = str("%s#%s" % ( fsn_snid, fsn_snuid ))
                        self.I.WS.serverSubLogin( login, persistent_callback=self.checkAccLoaded, auid=self.auid1 )
                        return
        
        #С аккаунтом не сдюжила )=. Пошли мержить дальше
        self.checkAccLoaded(None)            
            
    def checkAccLoaded(self, acc):
        info( "l_merge.checkAccLoaded (auid %s), acc is None: %s" % (self.auid1, (acc is None)) )
        # посчитаем сколько золота было потрачено на домики
        self.gold = 0
        if acc and acc.model:
            self.gold = acc.model.getSpentGold(self.I, acc)
            
            # а если аккаунт приговорен к удалению, то удалимся-ка мы, заодно, и из гильдии, что-бы всем хорошо было
            if acc.db.guildAuid:
                self.I.GS.removeGuildMember( acc, acc.db.guildAuid, acc.auid, None )
                acc.model.write( acc.pending )
                acc.db.guildAuid = 0
                acc.model.resetGuild(self.I, acc)
                guildbuilding = acc.model.getGuildBuilding(acc.SD)
                if guildbuilding:
                    # PF-98072
                    #acc.model.Buildings.remove(guildbuilding)
                    #acc.model.Pocket.remove(guildbuilding)
                    subParams = ClassDict( building_id=[guildbuilding.PersistentId], rid=[1] )
                    accountAction = Building_remove( subParams, partial(self.callbackFnAuid, auid=acc.auid), I=self.handler.I, acc=acc, uid=acc.uid )
                    accountAction.onStart()

        # можно выполнять собственно merge (в аггрегаторе):            
        self.I.AGG.merge( self.auid0, self.auid1, callback=self.onAggregatorMerge)
            
    #------------------------------------------------------------------------------------
    @action_timing
    def onAggregatorMerge(self, reply): 
        if not reply:
            return self.markLoginFailed('no aggregator reply', EC.AGGREGATOR_MERGE_FAIL)
        reason = reply.get("message", '')
        ecode = reply.get("error", 0)
        try:
            info( "onAggregatorMerge: %s", str(reply) )
            if ecode > 0 or reason:
                lcode = EC.AGGREGATOR_MERGE_FAIL
                return self.markLoginFailed("aggregator merge fail (code=%d reason=%r)" % (ecode, reason), lcode)
            else:
                self.I.STATS.addSocialMerge( str(self.auid0), str(self.auid1) )
                
                if reply.get("pwc_snuid"):
                    if self.email_md5:
                        # для PW Connect дешевле сразу перепилить auid в mysql-базе, чем потом гонять лишние запросы через аггрегатор (спрашивать auid по pwc_snuid, потом get_info по auid...)
                        return self.I.SQL.pwcMerge( self.email_md5, self.auid0, self.auid1, callback=self.onPwcUpdateDone )
                    elif self.pwc_snuid:
                        # при логине через связанную соц.сеть может быть fsn=pwc, в этом случае есть только snuid==str(pwc_snuid), и email_md5 надо выкапывать отдельно
                        return self.I.SQL.pwcGetByPwcSnuid( self.pwc_snuid, callback=self.onPwcGetEmailMd5 )
                elif reply.get("pwc_unused"):
                    pass # TODO как-то пометить в tbl_pwconnect неиспользуемость аккаунта
                return self.doBillingTransfer()

        except:
            message = catch()
            if ecode:
                self.response['agg_error'] = ecode 
            return self.markLoginFailed(message, EC.AGGREGATOR_MERGE_FAIL)
        return self.markLoginFailed("aggregator merge fail", EC.AGGREGATOR_MERGE_FAIL)
        
    #------------------------------------------------------------------------------------
    @action_timing
    def onPwcGetEmailMd5(self, sql_reply):
        info( "onPwcGetEmailMd5: %s", str(sql_reply) )
        try:
            # достаем данные аккаунта
            result = sql_reply["r"][0]
            email_md5 = result.email_md5
            self.I.SQL.pwcMerge( email_md5, self.auid0, self.auid1, callback=self.onPwcUpdateDone )
        except:
            self.response["ec"] = EC.MERGE_PWC_UPDATE_FAILED
            self.response["error"] = catch()
            self.fin()
        
    #------------------------------------------------------------------------------------
    @action_timing
    def onPwcUpdateDone(self, sql_reply):
        info( "onPwcUpdateDone: %s", str(sql_reply) )
        # теперь разбираемся с биллингом
        if cfg.MERGE_TRANSFER_GOLD_ALLOWED:
            self.doBillingTransfer()
        else:
            msg = "[MERGE_BILLING] transfer and refund for merging accounts was disabled"
            debug(msg)
            self.doReply()

    #------------------------------------------------------------------------------------
    def doBillingTransfer(self):
        code0 = self.billingResponse[self.auid0].get("code",-1)
        code1 = self.billingResponse[self.auid1].get("code",-1)
        if code0 == ibilling.ERROR_CODE_OK and code1 == ibilling.ERROR_CODE_OK:
            # причем удачно                
            dead_balance = 0
            dead_dbalance = self.billingResponse[self.auid1].get("dbalance", {})
            for ps, balance in dead_dbalance.items():
                if ps not in cfg.BILLING_MERGE_DISABLED_PS:
                    dead_balance += balance
            info("l_merge.checkBillingReplies: auid1=%s balance=%s" % (self.auid1, dead_balance))
            if dead_balance > 0:
                # попробуем перевести золото с "умирающего" аккаунта на новый основной
                self.I.BILL.transferGold( self.auid1, self.auid0, dead_balance, "l_merge(auid0:%s,auid1:%s)" % (self.auid0, self.auid1), self.onBillingTransfer)
                return
                
            self.doGoldRefund()
        else:
            msg = "[MERGE_BILLING] bad billing check results for merging accounts (auid %s: code %s, auid %s: code %s)" % (self.auid0, code0, self.auid1, code1)
            warn( msg )
            self.response["ec"] = EC.MERGE_BILLING_TRANSFER_BAD_RESPONSE
            self.response["error"] = msg
            self.doReply()
                
    #------------------------------------------------------------------------------------
    @action_timing
    def onBillingTransfer(self, billing_response):
        info("l_merge.onBillingTransfer (auid0=%s, auid1=%s) billing_response: %s" % (self.auid0, self.auid1, billing_response))
        response = billing_response or {}
        code = response.get("code",-1)
        if code != ibilling.ERROR_CODE_OK:
            err("[MERGE_BILLING] l_merge.onBillingTransfer (auid0=%s, auid1=%s) billing_response: %s" % (self.auid0, self.auid1, billing_response))
            self.response["ec"] = EC.MERGE_BILLING_TRANSFER_FAILED
            self.response["error"] = "bad billing transfer response: code %s" % (code)
            self.doReply()
        else:
            self.doGoldRefund()
    
    #------------------------------------------------------------------------------------
    def doGoldRefund(self):
        if cfg.MERGE_REFUND_GOLD_ALLOWED and self.gold > 0:
            self.I.BILL.replenish( self.auid0, self.gold, "Gold spent on buildings refund while account merge", self.onGoldRefund )
            return
        self.doReply()
                
    #------------------------------------------------------------------------------------
    @action_timing
    def onGoldRefund(self, billing_response):
        info("l_merge.onGoldRefund (auid0=%s, auid1=%s) amount=%s billing_response: %s" % (self.auid0, self.auid1, self.gold, billing_response))
        response = billing_response or {}
        code = response.get("code",-1)
        if code != ibilling.ERROR_CODE_OK:
            err("[MERGE_BILLING] l_merge.onGoldRefund (auid0=%s, auid1=%s) billing_response: %s" % (self.auid0, self.auid1, billing_response))
            self.response["ec"] = EC.MERGE_BILLING_TRANSFER_FAILED
            self.response["error"] = "bad gold refund response: code %s" % (code)
        self.doReply()
        
    #------------------------------------------------------------------------------------
    def doReply(self):
        self.I.WS.deleteLoginToken(self.auid1)
        self.response["ok"] = 1
        self.updateSocialNetworkCount( self.auid0 ) # там после обращения к аггрегатору делается self.fin()

##-------------------------------------------------------------------------------------
class LauncherMergeInternalAction( LauncherMergeBaseAction ):
    action = "l_merge_internal"
    
    @action_timing
    def onStart(self):
        auid0 = self.getParam("auid0")
        auid1 = self.getParam("auid1")
        email_md5 = self.getParam("email_md5", None)
        pwc_snuid = self.getParam("pwc_snuid", None)
        self.onProcess(auid0, auid1, email_md5, pwc_snuid)
        return

##-------------------------------------------------------------------------------------
class LauncherMergeAction( LauncherMergeBaseAction ):
    action = "l_merge"
    debug = True
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
                    email_md5 = getattr(self.user1, "email_md5", None)
                    pwc_snuid = getattr(self.user1, "pwc_snuid", None)
                    self.onProcess(self.auid0, self.auid1, email_md5, pwc_snuid)
                    return
                else:
                    return self.markLoginFailed("bad signature", EC.PWC_BAD_SIGNATURE)
            else:
                return self.markLoginFailed("auid token fail (auid=%s token=%r)" % (self.auid1, self.token1), EC.TOKEN_NOT_FOUND)
        else:
            return self.markLoginFailed("auid token fail (auid=%s token=%r)" % (self.auid0, self.token0), EC.TOKEN_NOT_FOUND)
