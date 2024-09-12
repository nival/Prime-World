# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging
import functools

import tornado.httpclient

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

_addPath('cfg')
import cfg

from base.helpers import *
import EC

# некоторые коды ошибок от настоящей ZZIMA (для тестовой заглушки)
BILLING_ZZIMA_BAD_PARAMS = -1000
BILLING_ZZIMA_ERROR_CRC = -1001               # E_CRC Incorrect CRC/unable to authorize request source
BILLING_ZZIMA_EMAIL_EXISTS = -1002            # User with such email already exists
BILLING_ZZIMA_USER_ALREADY_REGISTERED = -1003 # бывает, что аггрегатор не может понять, что юзер уже создан, и пытается его создать заново; в этом случае можно обращаться к биллингу
BILLING_ZZIMA_UNKNOWN_USER = -1004            # E_INVALID_USER No such user
BILLING_ZZIMA_INVALID_PASSWORD = -1005        # Invalid user name or password
BILLING_ZZIMA_UNKNOWN_PAYMENT_SYSTEM = -1006  # Unknown payments system
BILLING_ZZIMA_INVALID_ACCOUNT = -1007         # Cannot find account or this account id conflicts with other parameters
BILLING_ZZIMA_OVERDRAFT = -1008               # E_ OVERDRAFT Insufficient funds
BILLING_ZZIMA_ALREADY_SUBSCRIBED = -1009      # Service already subscribed
BILLING_ZZIMA_UNSUBSCRIBED = -1010            # Service unsubscribed
BILLING_ZZIMA_INVALID_SERVICE = -1011         # No service with such name
BILLING_ZZIMA_ACCESS = -1012                  # Access denied/Fraud detected
BILLING_ZZIMA_RECORD_NOT_FOUND = -1013        # Requested record not found
BILLING_ZZIMA_UNKNOWN_ERROR = -2000           # Something really bad happends

BILLING_SA_ERROR = 19 # бывает, что аггрегатор не может понять, что юзер уже создан, и пытается его создать заново; в этом случае можно обращаться к биллингу

# свои коды ошибок
BILLING_RUNNING = -100
BILLING_FAIL = -1
BILLING_RETRY = -2
BILLING_SUBSCRIBE = -3
BILLING_GET_BALANCE = -4
BILLING_BALANCE_FAIL = -5
BILLING_NOT_IMPLEMENTED = -6
BILLING_NOT_INITIALIZED = 0
BILLING_OK = 1

ERROR_CODE_UNKNOWN = -1
ERROR_CODE_OK = 0

PAYMENTS_OK = 0
PAYMENTS_BAD_PARAMS = 1
PAYMENTS_BAD_SIGNATURE = 2
PAYMENTS_UNKNOWN_USER = 3
PAYMENTS_BAD_AMOUNT = 4
PAYMENTS_TXN_IN_QUEUE = 5
PAYMENTS_TXN_QUEUE_FAIL = 6
PAYMENTS_NOT_IMPLEMENTED = 1000
PAYMENTS_FETCH_ERROR = 1001

# ------------------------------------------------------
class IBilling(object):
    
    RESPONSE_OK = dict(code=ERROR_CODE_OK)
    RESPONSE_FAIL = dict(code=ERROR_CODE_UNKNOWN)
    
    def __init__(self, I):
        pass
        
    # заводим биллинг для данного auid (в т.ч. обращаемся к аггрегатору с get_billing_status или retry_billing_registration; и запрашиваем у биллинга баланс)
    #
    # для асинхронного возврата результата вызываем callback с единственным параметром = словарь response: {
    #    "code":<int код ошибки>, // 0 если ок -- ЭТО ГЛАВНОЕ ПОЛЕ, КОТОРОЕ ПЕРВЫМ ДЕЛОМ НУЖНО ПРОВЕРИТЬ В ОТВЕТЕ (если там ошибка, balance может отсутствовать или не иметь смысла)
    #    "auid":<исходный auid>, 
    #    "balance":<float>, // баланс счета (голда), если code==0
    # }
    def initBilling(self, _auid, callback=None):
        if callback:
            callback( dict(code=BILLING_NOT_IMPLEMENTED, auid=toint(_auid)) )
            
    # пытаемся списать сумму sum (обязательно указать строчку reason с "назначением платежа"); если необходимо, делает также initBilling)
    #
    # для асинхронного возврата результата вызываем callback с единственным параметром = словарь response: {
    #    "code":<int код ошибки>, // 0 если ок -- ЭТО ГЛАВНОЕ ПОЛЕ, КОТОРОЕ ПЕРВЫМ ДЕЛОМ НУЖНО ПРОВЕРИТЬ В ОТВЕТЕ
    #    "auid":<исходный auid>, 
    #    "sum":<исходная сумма>, 
    #    "balance":<float>, // новый баланс счета (голда)
    # }
    def writeoff(self, _auid, sum, callback=None):
        if callback:
            callback( dict(code=BILLING_NOT_IMPLEMENTED, auid=toint(_auid)) )

    def replenish(self, _auid, sum, reason="dummy", callback=None, payment_system=None):
        if callback:
            callback( dict(code=BILLING_NOT_IMPLEMENTED, auid=toint(_auid)) )
    
    # возвращаем текущий статус и баланс (текущие локальные данные, без дополнительных запросов к биллингу); нормальный рабочий статус это BILLING_OK
    def getStatusBalance(self, _auid, force_balance_check=False):
        return BILLING_NOT_INITIALIZED, 0.0
                
    # вызывается при логауте/уничтожении аккаунта, когда биллинг для этого auid больше не понадобится
    def releaseBilling(self, auid):
        pass

    def reserveAmount( self, _auid, sum, reason, callback ):
        if callback:
            callback( dict(code=BILLING_NOT_IMPLEMENTED, auid=toint(_auid)) )

    def confirmWriteOff( self, _auid, reserveId, callback ):
        if callback:
            callback( dict(code=BILLING_NOT_IMPLEMENTED, auid=toint(_auid)) )

    def getBalanceEx(self, _auid, callback=None):
        if callback:
            callback( dict(code=BILLING_NOT_IMPLEMENTED, auid=toint(_auid)) )
        
# ------------------------------------------------------
class IPayments(object):
    
    def __init__(self):
        pass
        
    def replenish(self, _auid, amount, ramount, currency, txnid, callback=None):
        callback( dict(result=PAYMENTS_NOT_IMPLEMENTED) )
    
# ------------------------------------------------------
class DummyBillingHelper(object):
    def __init__(self, default_amount):
        self.status = BILLING_OK
        self._balance = {
            None : default_amount,
        }
        self.reasons = {}
        self.reserves = {}

    def setGold( self, gold, ps=None):
        self._balance[ps] = gold

    def writeoff(self, sum):
        s = sum
        while s > 0:
            items = [ (name, amount) for name, amount in self._balance.items() if amount > 0]
            for name, amount in self._balance.items():
                if amount > s:
                    amount = s
                self._balance[name] = self._balance[name]-amount
                s -= amount

    def replenish(self, sum, ps=None):
        self._balance[ps] = self._balance.get(ps, 0)+sum

    def getBalance(self):
        return sum(self._balance.values())

    def getBalanceEx(self):
        return self._balance

    def addReason( self, reason ):
        if reason in self.reasons:
            return False
        self.reasons[reason] = 1
        return True

    def delReason( self, reason ):
        if reason in self.reasons:
            del self.reasons[reason]

    def reserve( self, sum, reason ):
        if not self.addReason( reason ):
            return 0
        else:
            nextId = len(self.reserves)+1
            self.reserves[nextId] = ( sum, int( time.time() ) )
            self.writeoff(sum)
            self.delReason( reason )
            return len(self.reserves)

    def updateReserves( self ):
        for key in self.reserves.keys():
            sum, uptime = self.reserves[key]
            if uptime + 5 < int( time.time() ):
                self.reserves.pop( key, None )
                self.replenish(sum)

    def confirmReserve( self, reserveId ):
        if reserveId in self.reserves:
            self.reserves.pop( reserveId, None )
            return True
        return False

# ------------------------------------------------------
class DummyBilling:
    """ создает на каждый auid новый "биллинг акканунт" с дефолтной суммой на счету. Нормально исполняет writeoff-ы. """
    RESPONSE_OK = dict(code=ERROR_CODE_OK)
    RESPONSE_FAIL = dict(code=ERROR_CODE_UNKNOWN)
    
    def __init__(self, I, default_amount=1000.0):
        self.helpers = {}
        if cfg.TOURNAMENT_SERVER:
            self.default_amount = 0.0
        else:
            self.default_amount = 1000.0 # столько выдаем каждому "новому юзеру"
        
    def _fin(self, response, callback):
        info("DummyBilling response: %s" % response)
        if callback:
            callback( response )
    

    def checkHelper(self, _auid):
        auid = toint(_auid)
        helper = self.helpers.get(auid)
        info( "DummyBilling: auid=%s, helper=%s" % (auid, helper) )
        if not helper:
            warn("DummyBilling: no helper found for auid=%s, creating new.." % auid)
            helper = DummyBillingHelper( self.default_amount )
            self.helpers[auid] = helper
        return auid, helper
    
    def setGold( self, _auid, gold, ps=None):
        self.default_amount = gold
        auid = toint(_auid)
        helper = self.helpers.get(auid)
        if helper:
            helper.setGold(gold, ps)
        
    # ------------------------------------------------------
    def initBilling(self, _auid, callback=None):
        auid, helper = self.checkHelper(_auid)
        info( "DummyBilling initBilling: auid=%s, helper=%s" % (auid, helper) )            

        # фейлов не бывает; можно сразу сказать, что у нас OK
        response = dict(code=ERROR_CODE_OK, auid=auid, balance=helper.getBalance())
        self._fin(response, callback)
        return helper
            
    # ------------------------------------------------------
    def writeoff(self, _auid, sum, reason="dummy", callback=None):
        auid, helper = self.checkHelper(_auid)
        info( "DummyBilling  writeoff: auid=%s, sum=%s, reason=%s, helper=%s" % (auid, sum, reason, helper) )
            
        # writeoff
        if sum and isinstance(sum, (int, long, float)) and (sum > 0):
            if helper.getBalance() >= sum:
                if not helper.addReason( reason ):
                    response = dict(code=BILLING_ZZIMA_BAD_PARAMS, auid=auid, sum=sum, reason=reason, balance=helper.getBalance(), response=dict(message="Bad sum"))
                else:
                    helper.writeoff(sum)
                    helper.delReason( reason )
                    response = dict(code=ERROR_CODE_OK, auid=auid, sum=sum, reason=reason, balance=helper.getBalance())
            else:
                # не хватило бабла
                response = dict(code=BILLING_ZZIMA_OVERDRAFT, auid=auid, sum=sum, reason=reason, balance=helper.getBalance(), response=dict(message="Malovato babla"))
        else:
            # запрошена плохая сумма
            response = dict(code=BILLING_ZZIMA_BAD_PARAMS, auid=auid, sum=sum, reason=reason, balance=helper.getBalance(), response=dict(message="Bad sum"))
        
        self._fin(response, callback)

    # ------------------------------------------------------
    def replenish(self, _auid, sum, reason="dummy", callback=None, payment_system=None):
        auid, helper = self.checkHelper(_auid)
        info( "DummyBilling  replenish: auid=%s, sum=%s, reason=%s, helper=%s" % (auid, sum, reason, helper) )
            
        # replenish
        if sum and isinstance(sum, (int, long, float)) and (sum > 0):
            helper.replenish(sum, payment_system)
            response = dict(code=ERROR_CODE_OK, auid=auid, sum=sum, reason=reason, balance=helper.getBalance(), payment_system=payment_system)
        else:
            # запрошена плохая сумма
            response = dict(code=BILLING_ZZIMA_BAD_PARAMS, auid=auid, sum=sum, reason=reason, payment_system=payment_system, balance=helper.getBalance(), response=dict(message="Bad sum"))
        
        self._fin(response, callback)

            
    # ------------------------------------------------------
    def getStatusBalance(self, _auid, force_balance_check=False):
        auid = toint(_auid)
        helper = self.helpers.get(auid) 
        if helper:
            helper.updateReserves()
            return helper.status, helper.getBalance()
        else:
            return BILLING_NOT_INITIALIZED, 0.0
            
    # ------------------------------------------------------
    def releaseBilling(self, _auid):
        auid = toint(_auid)
        self.helpers.pop(auid, None) 
        
    # ------------------------------------------------------
    def transferGold(self, src_auid, dest_auid, sum, reason, callback=None):
        src_helper = self.initBilling(src_auid)
        dest_helper = self.initBilling(dest_auid)
        
        if sum and isinstance(sum, (int, long, float)) and (sum > 0):
            if src_helper.getBalance() >= sum:
                src_helper.writeoff(sum)
                dest_helper.replenish(sum)
                response = dict(code=ERROR_CODE_OK, auid=src_auid, sum=sum, reason=reason, balance=dest_helper.getBalance())
            else:
                # не хватило бабла
                response = dict(code=BILLING_ZZIMA_OVERDRAFT, auid=src_auid, sum=sum, reason=reason, balance=src_helper.getBalance(), response=dict(message="Malovato babla"))
        else:
            # запрошена плохая сумма
            response = dict(code=BILLING_ZZIMA_BAD_PARAMS, auid=src_auid, sum=sum, reason=reason, balance=src_helper.getBalance(), response=dict(message="Bad sum"))
        
        self._fin(response, callback)

    # ------------------------------------------------------
    def getBalanceEx(self, _auid, callback=None):
        auid, helper = self.checkHelper(_auid)
        info( "DummyBilling getBalanceEx: auid=%s, helper=%s" % (auid, helper) )
        dbalance = helper.getBalanceEx()
        if callback:
            callback( dict(code=ERROR_CODE_OK, dbalance=dbalance) )
        
    # ------------------------------------------------------
    def reserveAmount( self, _auid, sum, reason, callback ):
        auid, helper = self.checkHelper(_auid)
        info( "DummyBilling reserveAmount: auid=%s, sum=%s, reason=%s, helper=%s" % (auid, sum, reason, helper) )
            
        # reserve
        if sum and isinstance(sum, (int, long, float)) and (sum > 0):
            if helper.getBalance() >= sum:
                resId = helper.reserve( sum, reason )
                if resId:
                    response = dict(code=ERROR_CODE_OK, auid=auid, sum=sum, reason=reason, balance=helper.getBalance(), reserveId = resId)
                else:
                    response = dict(code=BILLING_ZZIMA_BAD_PARAMS, auid=auid, sum=sum, reason=reason, balance=helper.getBalance(), response=dict(message="Bad sum"))
            else:
                # не хватило бабла
                response = dict(code=BILLING_ZZIMA_OVERDRAFT, auid=auid, sum=sum, reason=reason, balance=helper.getBalance(), response=dict(message="Malovato babla"))
        else:
            # запрошена плохая сумма
            response = dict(code=BILLING_ZZIMA_BAD_PARAMS, auid=auid, sum=sum, reason=reason, balance=helper.getBalance(), response=dict(message="Bad sum"))
        
        self._fin( response, callback )


    def confirmWriteOff( self, _auid, reserveId, callback ):
        auid, helper = self.checkHelper(_auid)
        info( "DummyBilling confirmWriteOff: auid=%s, reserveId=%s, helper=%s" % (auid, reserveId, helper) )
        helper.updateReserves()
        if helper.confirmReserve( reserveId ):
            response = dict( code=ERROR_CODE_OK, auid=auid, balance=helper.getBalance(), reserveId=reserveId )
        else:
            response = dict( code=ERROR_CODE_UNKNOWN, auid=auid, balance=helper.getBalance(), reserveId=reserveId )
        self._fin( response, callback )

        
# ------------------------------------------------------
# ------------------------------------------------------

class ZzimaBilling(IBilling):
    
    def __init__(self, I):
        self.I = I
        self.helpers = {}

    # ------------------------------------------------------
    def initBilling(self, _auid, callback=None):
        auid, helper = self.checkHelper(_auid)
        
        if helper.status != BILLING_OK:
            helper.initBillingHelper( callback ) # вызовет пользовательский callback
        else:
            # можно сразу сказать, что у нас OK
            if callback:
                callback( dict(code=ERROR_CODE_OK, auid=auid, balance=helper.getBalanceCachedValue()) )
        
    # ------------------------------------------------------
    def checkHelper(self, _auid):
        auid = toint(_auid)
        helper = self.helpers.get(auid) 
        if not helper:
            warn("ZzimaBilling: no helper found for auid=%s, creating new.." % auid)
            helper = BillingHelper(self.I, auid)
            self.helpers[auid] = helper
        return auid,helper

    def reserveAmount( self, _auid, sum, reason, callback ):
        auid, helper = self.checkHelper(_auid)
        if helper.status == BILLING_OK:
            self._doReserveAmount( self.RESPONSE_OK, auid, sum, reason, callback )
        else:
            warn("ZzimaBilling reserveAmount: helper status for auid=%s not ok, calling init.." % auid)
            # helper свежесозданный, или пофейливший предыдущую попытку initBilling; придется retry
            _reserveAmount_callback = functools.partial( self._doReserveAmount, auid=auid, sum=sum, reason=reason, callback=callback )
            helper.initBillingHelper( _reserveAmount_callback ) # в конце работы вызовет _doReserveAmount со своим response{} и с нашими auid/sum/callback


    def _doReserveAmount( self, response, auid=0, sum=0.0, reason="", callback=None ):
        info("ZzimaBilling _doReserveAmount: response=%s, auid=%s, sum=%s, reason=%s" % (response, auid, sum, reason))
        if response and response.get("code", ERROR_CODE_UNKNOWN) == ERROR_CODE_OK:
            helper = self.helpers.get(auid)
            if helper:
                if not helper.addReason( reason ):
                    warn( "ZzimaBilling _doReserveAmount: reason=%r in progress for auid=%s" % ( reason, auid ) )
                    if callback:
                        callback( { "code" : EC.BILLING_BUSY } )
                else:
                    _on_reserveamount_callback = functools.partial( self._onFinishTransaction, auid=auid, callback=callback, reason=reason )
                    helper.reserveAmountHelper( sum, reason, _on_reserveamount_callback ) 
            else:
                warn("ZzimaBilling _doReserveAmount: no helper found for auid=%s" % auid)
        else:
            warn("ZzimaBilling _doReserveAmount: failed, response %s" % response)
            if callback:
                callback( response )


    def confirmWriteOff( self, _auid, reserveId, callback ):
        auid, helper = self.checkHelper(_auid)
        if helper.status == BILLING_OK:
            self._doConfirmWriteOff( self.RESPONSE_OK, auid, reserveId, callback )
        else:
            warn("ZzimaBilling confirmWriteOff: helper status for auid=%s not ok, calling init.." % auid)
            # helper свежесозданный, или пофейливший предыдущую попытку initBilling; придется retry
            _confirmWriteOff_callback = functools.partial( self._doConfirmWriteOff, auid=auid, reserveId=reserveId, callback=callback )
            helper.initBillingHelper( _confirmWriteOff_callback ) # в конце работы вызовет _doConfirmWriteOff со своим response{} и с нашими auid/reserveId/callback


    def _doConfirmWriteOff( self, response, auid=0, reserveId=0, callback=None ):
        info( "ZzimaBilling _doConfirmWriteOff: response=%s, auid=%s, reserveId=%s" % (response, auid, reserveId) )
        if response and response.get("code", ERROR_CODE_UNKNOWN) == ERROR_CODE_OK:
            helper = self.helpers.get(auid)
            if helper:
                _on_confirmwriteoff_callback = functools.partial( self._onFinishTransaction, auid=auid, callback=callback )
                helper.confirmWriteOffHelper( reserveId, _on_confirmwriteoff_callback ) 
            else:
                warn("ZzimaBilling _doConfirmWriteOff: no helper found for auid=%s" % auid)
        else:
            warn("ZzimaBilling _doConfirmWriteOff: failed, response %s" % response)
            if callback:
                callback( response )


    def getBalanceEx(self, _auid, callback=None):
        auid, helper = self.checkHelper(_auid)
        if helper.status == BILLING_OK:
            self._doGetBalanceEx( self.RESPONSE_OK, auid, callback )
        else:
            warn("ZzimaBilling getBalanceEx: helper status for auid=%s not ok, calling init.." % auid)
            # helper свежесозданный, или пофейливший предыдущую попытку initBilling; придется retry
            _writeoff_callback = functools.partial( self._doGetBalanceEx, auid=auid, callback=callback )
            helper.initBillingHelper( _writeoff_callback ) # в конце работы вызовет doGetBalanceEx со своим response{} и с нашими auid/sum/callback


    # ------------------------------------------------------
    def writeoff(self, _auid, sum, reason, callback=None):
        auid, helper = self.checkHelper(_auid)
        if helper.status == BILLING_OK:
            self._doWriteoff( self.RESPONSE_OK, auid, sum, reason, callback )
        else:
            warn("ZzimaBilling writeoff: helper status for auid=%s not ok, calling init.." % auid)
            # helper свежесозданный, или пофейливший предыдущую попытку initBilling; придется retry
            _writeoff_callback = functools.partial( self._doWriteoff, auid=auid, sum=sum, reason=reason, callback=callback )
            helper.initBillingHelper( _writeoff_callback ) # в конце работы вызовет doWriteoff со своим response{} и с нашими auid/sum/callback


    def _doWriteoff(self, response, auid=0, sum=0.0, reason="", callback=None):
        info("ZzimaBilling _doWriteoff: response=%s, auid=%s, sum=%s, reason=%s" % (response, auid, sum, reason))
        if response and response.get("code", ERROR_CODE_UNKNOWN) == ERROR_CODE_OK:
            helper = self.helpers.get(auid)
            if helper:
                if not helper.addReason( reason ):
                    warn( "ZzimaBilling _doWriteoff: reason=%r in progress for auid=%s" % ( reason, auid ) )
                    if callback:
                        callback( { "code" : EC.BILLING_BUSY } )
                else:
                    _on_writeoff_callback = functools.partial( self._onFinishTransaction, auid=auid, callback=callback, reason=reason )
                    helper.writeoffHelper( sum, reason, _on_writeoff_callback ) 
            else:
                warn("ZzimaBilling _doWriteoff: no helper found for auid=%s" % auid)
        else:
            warn("ZzimaBilling _doWriteoff: failed, response %s" % response)
            if callback:
                callback( response )


    def _doGetBalanceEx(self, response, auid=0, callback=None):
        info("ZzimaBilling _doGetBalanceEx: response=%s, auid=%s" % (response, auid))
        if response and response.get("code", ERROR_CODE_UNKNOWN) == ERROR_CODE_OK:
            helper = self.helpers.get(auid)
            if helper:
                _on_writeoff_callback = functools.partial( self._onProxyTransaction, auid=auid, callback=callback)
                helper.getBalanceEx( _on_writeoff_callback ) 
            else:
                warn("ZzimaBilling _doGetBalanceEx: no helper found for auid=%s" % auid)
        else:
            warn("ZzimaBilling _doGetBalanceEx: failed, response %s" % response)
            if callback:
                callback( response )

    def _onProxyTransaction(self, response, auid=0, callback=None):
        info("ZzimaBilling _onProxyTransaction: response %s" % response)
        if callback: # сообщаем ответ
            callback( response )

    def _onFinishTransaction(self, response, auid=0, callback=None, reason="", persistent_request_id=0, payment_system=None):
        info("ZzimaBilling _onFinishTransaction: response %s" % response)
        if callback: # сообщаем ответ
            callback( response )
        helper = self.helpers.get(auid)
        if helper:
            helper.delReason( reason )
            
        # и после отработки запроса еще раз перезапросим баланс у биллинга, чтобы иметь актуальное значение (мало ли, вдруг обновилось)
        # (но только если запрос успешный, иначе нет смысла обновлять баланс, да и можем ввалиться в бесконечную рекурсию)
        if response:
            error_code = response.get("code", ERROR_CODE_UNKNOWN)
            if error_code == ERROR_CODE_OK:
                helper = self.helpers.get(auid)
                if helper:
                    helper.initBillingHelper( callback=None ) 


    # ------------------------------------------------------
    def replenish(self, _auid, sum, reason="dummy", callback=None, persistent_request_id=0, payment_system=None):
        auid,helper = self.checkHelper(_auid)
        if helper.status == BILLING_OK:
            self._doReplenish( self.RESPONSE_OK, auid, sum, reason, callback, persistent_request_id, payment_system )
        else:
            warn("ZzimaBilling replenish: helper status for auid=%s not ok, calling init.." % auid)
            # helper свежесозданный, или пофейливший предыдущую попытку initBilling; придется retry
            _replenish_callback = functools.partial( self._doReplenish, auid=auid, sum=sum, reason=reason, callback=callback, \
                persistent_request_id=persistent_request_id, payment_system=payment_system )
            helper.initBillingHelper( _replenish_callback ) # в конце работы вызовет doReplenish со своим response{} и с нашими auid/sum/callback
        
        
    def _doReplenish(self, response, auid=0, sum=0.0, reason="", callback=None, persistent_request_id=0, payment_system=None):
        info("ZzimaBilling _doReplenish: response=%s, auid=%s, sum=%s, reason=%s" % (response, auid, sum, reason))
        if response and response.get("code", ERROR_CODE_UNKNOWN) == ERROR_CODE_OK:
            helper = self.helpers.get(auid)
            if helper:
                _on_replenish_callback = functools.partial( self._onFinishTransaction, auid=auid, callback=callback, reason=reason, \
                    persistent_request_id=persistent_request_id, payment_system=payment_system )
                helper.replenishHelper( sum, reason, _on_replenish_callback, payment_system ) 
            else:
                warn("ZzimaBilling _doReplenish: no helper found for auid=%s" % auid)
        else:
            warn("ZzimaBilling _doReplenish: failed, response %s" % response)
            if callback:
                callback( response )

    # ------------------------------------------------------
    def getStatusBalance(self, _auid, force_balance_check=False):
        auid = toint(_auid)
        helper = self.helpers.get(auid) 
        if helper:
            helper.checkBalance( callback=None, force_balance_check=force_balance_check )
            return helper.status, helper.balance
        else:
            return BILLING_NOT_INITIALIZED, 0.0
        
            
    # ------------------------------------------------------
    def releaseBilling(self, _auid):
        auid = toint(_auid)
        self.helpers.pop(auid, None) 
        
        
    # ------------------------------------------------------
    def transferGold(self, _src_auid, _dest_auid, sum, reason, callback=None):
        src_auid, src_helper = self.checkHelper(_src_auid) 
        dest_auid, dest_helper = self.checkHelper(_dest_auid) 
        _on_transfer_callback = functools.partial( self._onFinishTransaction, auid=dest_auid, callback=callback, reason=reason )
        dest_helper.transferHelper( src_auid, sum, reason, _on_transfer_callback )
        
        
                        
# ------------------------------------------------------
# ------------------------------------------------------

# настоящий хелпер, для zzima
class BillingHelper(object):

    def __init__(self, I, auid):
        self.I = I
        self.auid = toint(auid)
        self.status = BILLING_NOT_INITIALIZED 
        self.balance_timestamp = 0 
        self.balance = 0.0
        self.reserveId = 0
        self.reasons = {}

    def addReason( self, reason ):
        if reason in self.reasons:
            return False
        self.reasons[reason] = 1
        return True

    def delReason( self, reason ):
        if reason in self.reasons:
            del self.reasons[reason]
        
    def fin(self, error_code=ERROR_CODE_OK, results={}, callback=None):
        results["code"] = error_code
        results["auid"] = self.auid
        info("BillingHelper fin results: %s" % results)
        if callback:
            callback( results )

    def getBalanceCachedValue(self):
        return self.balance

    # ------------------------------------------------------------
    def initBillingHelper(self, callback=None):
        info( "initBillingHelper: auid=%s, status=%s" % (self.auid, self.status) )
        if self.status != BILLING_OK:
            # похоже с биллингом не ок; перезапросим статус у аггрегатора
            info( "initBillingHelper: AGG.getBillingStatus for auid=%s" % (self.auid) )
            _on_callback = functools.partial( self.onUserBillingStatus, callback=callback )
            self.I.AGG.getBillingStatus( self.auid, callback=_on_callback )
        else:
            # просто перезапросим баланс
            ## info( "initBillingHelper: getBalance for auid=%s" % (self.auid) )
            self.getBalance( callback=callback )

    # ------------------------------------------------------------
    def checkBalance(self, callback=None, force_balance_check=False):
        now = toint( time.time() )
        if (self.balance_timestamp + cfg.BILLING_CHECK_BALANCE_PERIOD < now) or force_balance_check: # периодически запрашиваем новый баланс 
            if (not self.I.WS.wsShutdown): # но только если сервер еще не начал закрываться
                self.balance_timestamp = toint( time.time() ) # таймстэмп будем ставить перед запросом, чтобы не плодить частых лишних запросов в случае неответа
                self.initBillingHelper( callback=None )
            else:
                info("checkBalance: skipping because of wsShutdown(%s)" % self.I.WS.wsShutdown)

    
    def reserveAmountHelper( self, sum, reason, callback=None ):
        billing_login = cfg.AGG_BILLING_PREFIX + str(self.auid)
        if cfg.BILLING_RESERVE_ENABLED:
            info( "reserveAmountHelper: auid=%s, sum=%.2f, reason=%s" % (self.auid, sum, reason) )
            _on_callback = functools.partial( self.onBillingReserveAmount, sum=sum, callback=callback )
            self.I.ZZ.reserveAmount( billing_login, sum, reason, callback=_on_callback )
        else:
            info( "reserveAmountHelperFake: auid=%s, sum=%.2f, reason=%s" % (self.auid, sum, reason) )
            _on_callback = functools.partial( self.onBillingReserveAmountFake, sum=sum, callback=callback )
            self.I.ZZ.writeOff( billing_login, sum, reason, callback=_on_callback )


    def onBillingReserveAmount( self, response, sum=0, callback=None ):
        info( "onBillingReserveAmount: auid=%s, sum=%.2f, response=%s" % (self.auid, sum, response) )
        try:
            billing_response = response.get("r")
            error_code = billing_response.get("code", -1)
            reserveId = billing_response.get("reserveId", -1)
            if error_code == 0:
                self.balance -= sum # баланс пока пересчитаем руками; после завершения операции не забыть переспросить!
                self.fin( results=dict(sum=sum, balance=self.balance, reserveId=reserveId), callback=callback )
            else:
                self.fin( error_code, dict(sum=sum, response=billing_response, reserveId=reserveId), callback=callback )
        except:
            catch()
            self.fin( BILLING_FAIL, dict(response=response), callback=callback )

    def onBillingReserveAmountFake( self, response, sum=0, callback=None ):
        info( "onBillingReserveAmountFake: auid=%s, sum=%.2f, response=%s" % (self.auid, sum, response) )
        try:
            billing_response = response.get("r")
            error_code = billing_response.get("code", -1)
            self.reserveId += 1
            reserveId = self.reserveId
            if error_code == 0:
                self.balance -= sum # баланс пока пересчитаем руками; после завершения операции не забыть переспросить!
                self.fin( results=dict(sum=sum, balance=self.balance, reserveId=reserveId), callback=callback )
            else:
                self.fin( error_code, dict(sum=sum, response=billing_response, reserveId=reserveId), callback=callback )
        except:
            catch()
            self.fin( BILLING_FAIL, dict(response=response), callback=callback )

    def confirmWriteOffHelper( self, reserveId, callback=None ):
        if cfg.BILLING_RESERVE_ENABLED:        
            info( "confirmWriteOffHelper: auid=%s, reserveId=%r" % (self.auid, reserveId) )
            billing_login = cfg.AGG_BILLING_PREFIX + str(self.auid)
            _on_callback = functools.partial( self.onBillingConfirmWriteOff, reserveId=reserveId, callback=callback )
            self.I.ZZ.confirmWriteOff( billing_login, reserveId, callback=_on_callback )
        else:
            info( "confirmWriteOffHelperFake: auid=%s, reserveId=%r" % (self.auid, reserveId) )
            self.fin( results=dict(reserveId=reserveId, balance=self.balance), callback=callback )

    def onBillingConfirmWriteOff( self, response, reserveId=0, callback=None ):
        info( "onBillingConfirmWriteOff: auid=%s, reserveId=%r" % (self.auid, reserveId) )
        try:
            billing_response = response.get("r")
            error_code = billing_response.get("code", -1)
            if error_code == 0:
                self.fin( results=dict(reserveId=reserveId, balance=self.balance), callback=callback )
            else:
                self.fin( error_code, dict(reserveId=reserveId, response=billing_response), callback=callback )
        except:
            catch()
            self.fin( BILLING_FAIL, dict(response=response), callback=callback )


    def getBalanceEx(self, callback=None):
        billing_login = cfg.AGG_BILLING_PREFIX + str(self.auid)
        _on_callback = functools.partial( self.onBillingGetBalanceEx, callback=callback )
        self.I.ZZ.getBalanceEx( billing_login, callback=_on_callback )
            
    def onBillingGetBalanceEx(self, response, callback=None):
        info( "onBillingGetBalanceEx: auid=%s, response=%s" % (self.auid, response) )
        try:
            billing_response = response.get("r")
            error_code = billing_response.get("code", -1)
            if error_code == 0:
                self.fin( results=dict(dbalance=billing_response.get('dbalance', {})), callback=callback )
            else:
                self.fin( error_code, dict(response=billing_response), callback=callback )
        except:
            catch()
            self.fin( BILLING_FAIL, dict(response=response), callback=callback )

    # ------------------------------------------------------------
    def writeoffHelper(self, sum, reason, callback=None):
        info( "writeoffHelper: auid=%s, sum=%.2f" % (self.auid, sum) )
        billing_login = cfg.AGG_BILLING_PREFIX + str(self.auid)
        _on_callback = functools.partial( self.onBillingWriteoff, sum=sum, callback=callback )
        self.I.ZZ.writeOff( billing_login, sum, reason, callback=_on_callback )
            
    def onBillingWriteoff(self, response, sum=0, callback=None):
        info( "onBillingWriteoff: auid=%s, sum=%.2f, response=%s" % (self.auid, sum, response) )
        try:
            billing_response = response.get("r")
            error_code = billing_response.get("code", -1)
            if error_code == 0:
                self.fin( results=dict(sum=sum, balance=self.balance), callback=callback )
            else:
                self.fin( error_code, dict(sum=sum, response=billing_response), callback=callback )
        except:
            catch()
            self.fin( BILLING_FAIL, dict(response=response), callback=callback )

    # ------------------------------------------------------------
    def transferHelper(self, src_auid, sum, reason, callback=None ):
        info( "transferHelper: src_auid=%s, dest_auid=%s, sum=%.2f" % (src_auid, self.auid, sum) )
        src_billing_login = cfg.AGG_BILLING_PREFIX + str(src_auid)
        dest_billing_login = cfg.AGG_BILLING_PREFIX + str(self.auid)
        _on_callback = functools.partial( self.onBillingTransfer, sum=sum, callback=callback )
        self.I.ZZ.transfer( src_billing_login, dest_billing_login, sum, reason, callback=_on_callback )
            
    def onBillingTransfer(self, response, sum=0, callback=None):
        info( "onBillingTransfer: auid=%s, sum=%.2f, response=%s" % (self.auid, sum, response) )
        try:
            billing_response = response.get("r")
            error_code = billing_response.get("code", -1)
            if error_code == 0:
                self.balance += sum # баланс пока пересчитаем руками; после завершения операции не забыть переспросить!
                self.fin( results=dict(sum=sum, balance=self.balance), callback=callback )
            else:
                self.fin( error_code, dict(sum=sum, response=billing_response), callback=callback )
        except:
            catch()
            self.fin( BILLING_FAIL, dict(response=response), callback=callback )
        
    # ------------------------------------------------------------
    def replenishHelper(self, sum, reason, callback=None, payment_system=None):
        info( "replenishHelper: auid=%s, sum=%.2f" % (self.auid, sum) )
        billing_login = cfg.AGG_BILLING_PREFIX + str(self.auid)
        _on_callback = functools.partial( self.onBillingReplenish, sum=sum, callback=callback, payment_system=payment_system )
        self.I.ZZ.replenish( billing_login, sum, reason, callback=_on_callback, payment_system=payment_system )
            
    def onBillingReplenish(self, response, sum=0, callback=None, payment_system=None):
        info( "onBillingReplenish: auid=%s, sum=%.2f, response=%s" % (self.auid, sum, response) )
        try:
            billing_response = response.get("r")
            error_code = billing_response.get("code", -1)
            if error_code == 0:
                self.balance += sum # баланс пока пересчитаем руками; после завершения операции не забыть переспросить!
                self.fin( results=dict(sum=sum, balance=self.balance), callback=callback )
            else:
                self.fin( error_code, dict(sum=sum, response=billing_response), callback=callback )
        except:
            catch()
            self.fin( BILLING_FAIL, dict(response=response), callback=callback )
            
    # ------------------------------------------------------------
    def getBalance(self, callback=None):
        info( "getBalance: auid=%s" % (self.auid) )
        billing_login = cfg.AGG_BILLING_PREFIX + str(self.auid)
        _on_callback = functools.partial( self.onUserBillingBalance, callback=callback )
        self.balance_timestamp = toint( time.time() ) # таймстэмп будем ставить перед запросом, чтобы не плодить частых лишних запросов в случае неответа
        self.I.ZZ.getBalance( billing_login, callback=_on_callback )
        
    # ------------------------------------------------------------
    def subscribeBillingService(self, callback=None ):
        info( "subscribeBillingService: auid=%s" % (self.auid) )
        billing_login = cfg.AGG_BILLING_PREFIX + str(self.auid)
        _on_callback = functools.partial( self.onUserBillingSubscribe, callback=callback )
        self.I.ZZ.subscribe( billing_login, callback=_on_callback )
        
    # ------------------------------------------------------------
    def onUserBillingStatus(self, response, callback=None):
        info( "onUserBillingStatus: auid=%s, response=%s" % (self.auid, response) )
        try:
            if response and response.get("get_billing_status", BILLING_FAIL) == BILLING_OK:
                self.status = BILLING_OK
                # можно запрашивать баланс
                self.getBalance( callback=callback )
                
            else:
                self.status = BILLING_RETRY
                # попробуем retry
                _on_callback = functools.partial( self.onUserBillingRetry, callback=callback )
                self.I.AGG.retryBillingRegistration( self.auid, callback=_on_callback )
                
        except:
            catch()
            self.status = BILLING_FAIL
            self.fin( BILLING_FAIL, dict(response=response), callback=callback )
            
    # ------------------------------------------------------------
    def onUserBillingRetry(self, response, callback=None):
        info( "onUserBillingRetry: auid=%s, response=%s" % (self.auid, response) )
        try:
            if response:
                agg_billing_error = response.get("error", 0)
                if agg_billing_error == 0:
                    # retry прошел нормально 
                    self.status = BILLING_GET_BALANCE
                    # можно запрашивать баланс
                    self.getBalance( callback=callback )
                    return
                
        except:
            catch()
            
        # fail:
        self.status = BILLING_FAIL
        self.fin( BILLING_FAIL, dict(response=response), callback=callback )
        
    # ------------------------------------------------------------
    def onUserBillingBalance(self, response, callback=None):
        info( "onUserBillingBalance: auid=%s, response=%s" % (self.auid, response) )
        try:
            billing_response = response.get("r")
            error_code = billing_response.get("code", -1)
            if error_code == 0:
                self.balance = billing_response.get("amount", 0.0) or billing_response.get("balance", 0.0)
                self.status = BILLING_OK
                ##self.balance_timestamp = toint( time.time() )
                self.fin( results=dict(balance=self.balance), callback=callback )
                
            elif error_code == -1010:
                # юзер не подписан в билллинге на наш сервис; надо подписать..
                self.status = BILLING_SUBSCRIBE
                self.subscribeBillingService( callback=callback )
            
            else:
                self.status = BILLING_BALANCE_FAIL
                self.balance = 0.0
                self.fin( BILLING_BALANCE_FAIL, dict(response=billing_response), callback=callback )
        except:
            catch()
            self.status = BILLING_BALANCE_FAIL
            self.balance = 0.0
            self.fin( BILLING_BALANCE_FAIL, dict(response=response), callback=callback )
                
    # ------------------------------------------------------------
    def onUserBillingSubscribe(self, response, callback=None):
        info( "onUserBillingSubscribe: auid=%s, response=%s" % (self.auid, response) )
        try:
            error_code = response.get("code", 0)
            if error_code == 0:
                # подписались
                self.status = BILLING_GET_BALANCE
                self.getBalance( callback=callback )
            else:
                self.status = BILLING_FAIL
                self.fin( BILLING_BALANCE_FAIL, dict(response=response), callback=callback )
        except:
            catch()
            self.status = BILLING_FAIL
            self.fin( BILLING_BALANCE_FAIL, dict(response=response), callback=callback )


# ------------------------------------------------------
class RealPayments(object):
    
    def __init__(self, HTTP, url, secret, ps):
        self.HTTP = HTTP
        self.url = url
        self.secret = secret
        self.pending_count = 0
        self.ps = ps
        
    def replenish( self, _auid, amount, ramount, currency, txnid, callback=None ):
        args = {
            'auid' : _auid,
            'amount' : amount,
            'txnid' : txnid,
        }
        sign = makeParamsSignature(args, self.secret)
        args['sign'] = sign
        args['ps'] = self.ps
        args['ramount'] = ramount
        args['currency'] = currency

        url = self.url + "?" + urllib.urlencode(args)
        request = tornado.httpclient.HTTPRequest( url=url, method="GET" )
        self.pending_count += 1 
        info("Payments replenish (ps=%r pending_count=%s)" % (self.ps, self.pending_count))

        _callback = functools.partial( self.onPaymentReply, callback=callback )
        try:
            self.HTTP.fetch( request, _callback )
        except:
            catch()
            self.fail( callback )

    def onPaymentReply(self, http_reply, callback=None):
        self.pending_count -= 1 

        if http_reply and (not http_reply.error) and http_reply.body:           
            data = None
            try:
                data = json.loads(http_reply.body)
            except:
                catch()
                self.fail(callback)
                return
            info( "Payments replied (ps=%r pending_count=%s result=%r)" % (self.ps, self.pending_count, data) )
            
            if callback:
                callback( data )
        else:
            info( "Payments reply error (ps=%r pending_count=%s http_reply=%r)" % (self.ps, self.pending_count, http_reply) )
            self.fail( callback )

    def fail(self, callback):
        if callback:
            callback( {'result': PAYMENTS_FETCH_ERROR } )
