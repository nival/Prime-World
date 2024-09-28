#!/usr/bin/env python
# -"- coding: utf8 -"- 
# (C) Dmitry Kolb 2014, Nival Network 

# An interface for ZZima.com billing API


from functools import partial
from base.helpers import *
addRelPath('base')
from  izzima import HttpZZima

from tornado.httpclient import HTTPRequest
from tornado.httputil import HTTPHeaders

import EC
import CC
#недостаток средств на счету
E_ZZIMA_BILLING_OVERDRAFT = -1008

SA_INVALID_REFRESH_TOKEN = 28

ZZIMA_LG_START_TRANSACTION = 1
ZZIMA_LG_TRANSACTION_FASTTRY = 5
ZZIMA_LG_TRANSACTION_TIMEOUT = 20
ZZIMA_LG_TRANSACTION_MAXTRYS = 5
ZZIMA_LG_TRANSACTION_LONGTIMEOUT = 300

ZZIMA_LG_REPLENISH = 2
ZZIMA_LG_REPLENISH_FASTTRY = 5
ZZIMA_LG_REPLENISH_TIMEOUT = 20
ZZIMA_LG_REPLENISH_MAXTRYS = 5
ZZIMA_LG_REPLENISH_LONGTIMEOUT = 300

class IZZimacom(object):
    def startTransaction(self, auid, snid,  transactionId, itemId, itemPrice, count, callback):
        raise NotImplementedError()

    def getUserBalance(self, auid, snid, callback=None):
        raise NotImplementedError()


class IUserZZimacom:
    def startTransaction(self, transactionId, itemId, itemPrice, count,   callback=None):
        raise NotImplementedError()

    def getBalance(self, callback=None):
        raise NotImplementedError()

class IRealIZZimacom(IZZimacom):

    def __init__(self, service_name, payment_system, billing_url,isTest, http, sa):
        self.shutdown = 0
        self.pending_count = 0
        self.isTest = isTest
        self.requests = {}
        self.http = http
        self.sa = sa
        self.zzbill = HttpZZima(http, service_name, payment_system, billing_url)

    def startTransaction(self, *args):
        # args: auid, snid, amount, itemid, count, uniqueid, callback
        self.sa.getInfo(args[0], args[1], 1,
            partial(self.onGetZZimaUserId, callback=partial(self._purchaseItem, data=args)))

    def getUserBalance(self, *args):
        self.sa.getInfo(args[0], args[1], 1,
            partial(self.onGetZZimaUserId, callback=partial(self._getBalance, callback=args[2])))

    #callback - self._getBalance / _purchaseItem
    def onGetZZimaUserId(self, result, callback):
        "Callback for SA request for stored sntoken and for refresh sntoken."
        info("IRealZzima.onGetZzimaUserId: result: %r, callback %r", result, callback)
        if result is None:
            error = {'ok' : 0, 'ec': EC.ZZIMA_LOCAL_SA_FAILURE}
        elif result.get('error', 0):
            if result['error'] == SA_INVALID_REFRESH_TOKEN: # could be returned only for refresh sntoken request
                error = {'ok' : 0, 'ec': EC.ZZIMA_TOKEN_EXPIRED}
            else:
                error = {'ok': 0, 'ec': EC.ZZIMA_LOCAL_SA_FAILURE, 'em': str(result)}
        else:
            props = result['get_info'].get('props')
            if not props:
                error = {'ok': 0, 'ec': EC.ZZIMA_LOCAL_SA_FAILURE, 'em': 'No props returned'}

            else:
                error = None

        if error:
            info("IRealZzima._onGetZzimaUserId error: %s", error)
            callback(None, error)
        else:
            callback(result['get_info'][self.original_snid], None)

    # получить баланс перед началом резервирования
    def _onCheckBalance(self, response, inf, data):
        #info("IRealZzima._onCheckBalance response : [%r] type(%r) inf[%r] data[%r] " % (response, type(response), inf, data))
        balance = response.get('balance', 0)

        auid, snid, uniqueid,  itemid, amount, count, callback = data
        if amount > balance:
            response = {'ok': 0}
            response['ec'] = EC.ZZIMA_NOT_ENOUGH_ZZGOLD
            response['em'] = 'Zzima error: not enough zzgold'
            callback(response)
            warn("IRealZzima._onCheckBalance error: %s amount[%r], balance[%r]", error, amount, balance)
            return

        #_callback = partial(self._onZzimaPurchase, error=error, tr_data=(inf, data, callback))
        _callback = partial(self._onZzimaReserveAmount, error=None, tr_data=(inf, data, callback))
        reason  = "txn: %r , itemid: %r, count: %r" % (uniqueid,  itemid, count)
        #self.zzbill.writeOff(inf.get('userName'), amount, reason, _callback)
        #info("IRealZzima._onCheckBalance reserveAmount : [%r], amount:[%r] reason[%r] _callback[%r] " % (inf.get('userName'), amount, reason, _callback))
        self.zzbill.reserveAmount(inf.get('userName'), amount, reason, _callback)

    def _purchaseItem(self, inf, error, data):

        if inf is None:
            # data[-1] is a callback
            data[-1](error)
            return

        #info("IRealZzima._purchaseItem : [%r] ", data)
        _callback = partial(self._onZzimaBalance, error=error, callback=partial(self._onCheckBalance, inf=inf, data=data))
        self.zzbill.getBalance(inf.get('userName'), _callback)

    def _getBalance(self, inf, error, callback):
        _callback = partial(self._onZzimaBalance, error=error, callback=callback)
        self.zzbill.getBalance(inf.get('userName'), _callback)

    def _onZzimaBalance(self, result, error, callback):
        info("IRealZzima._onZzimaBalance info: %r", result)
        if error:
            data = {'ok': 0}
            data['ec'] = EC.ZZIMA_OPERATION_FAILURE
            data['em'] = 'Zzima error: %r' % error

        elif result and 'r' in result:
            code = result['r'].get('code', None)
            #info("IRealZzima._onZzimaBalance code: %r", code)
            if code and code is not None:
                data = {'ok': 0}
                data['ec'] = EC.ZZIMA_OPERATION_FAILURE
                data['em'] = 'Zzima error: %r' % result
            else:
                data = {'ok': 1, 'ec': 0, 'balance': result['r']['amount']}
            #info("IRealZzima._onZzimaBalance callback: %r data %r" % (callback,data))

        callback(data)

    def _onZzimaPurchase(self, result, error, tr_data):
        inf, args, callback = tr_data
        info("IRealZzima._onZzimaPurchase info: %r", result)

        if error:
            data = {'ok': 0}
            data['ec'] = EC.ZZIMA_OPERATION_FAILURE
            data['em'] = 'Zzima error: %r' % error

        elif result and 'r' in result:
            data = {'ok': 1}
            code = result['r'].get('code', None)
            if code and code is not None:
                data = {'ok': 0}
                if code == E_ZZIMA_BILLING_OVERDRAFT:
                    self._getBalance(inf, None, partial(self._returnNotEnough, tr_data=tr_data))
                    return
                else:
                    data['ec'] = EC.ZZIMA_OPERATION_FAILURE
                    data['em'] = 'Zzima error: %r' % result
            else:
                data['balance'] = True # Если всё плохо и баланса нет, то -1
        else:
            data = {'ok': 0, 'ec':EC.ZZIMA_OPERATION_FAILURE, 'em': "response result is empty" }
        callback(data)

    def _onZzimaReserveAmount(self, result, error, tr_data):
        info("IRealZzima._onZzimaReserveAmount info: %r", result)
        inf, args, callback = tr_data
        if error:
            data = {'ok': 0}
            data['ec'] = EC.ZZIMA_OPERATION_FAILURE
            data['em'] = 'Zzima error: %r' % error

        elif result and 'r' in result:
            data = {'ok': 1}
            code = result['r'].get('code', None)
            if code and code is not None:
                data = {'ok': 0}
                if code == E_ZZIMA_BILLING_OVERDRAFT:
                    self._getBalance(inf, None, partial(self._returnNotEnough, tr_data=tr_data))
                    return
                else:
                    data['ec'] = EC.ZZIMA_OPERATION_FAILURE
                    data['em'] = 'Zzima error: %r' % result
            else:
                reserveId = result['r'].get('reserveId', None)
                info("IRealZzima._onZzimaReserveAmount reserveId: %r", reserveId)
                if reserveId is not None:
                    _callback = partial(self._onZzimaPurchase, error=error, tr_data=(inf, data, callback))
                    self.zzbill.confirmWriteOff(inf.get('userName'), reserveId, _callback)
                    return
        else:
            data = {'ok': 0, 'ec':EC.ZZIMA_OPERATION_FAILURE, 'em': "response result is empty" }
        callback(data)

    def _returnNotEnough(self, balance, tr_data):
        inf, args, callback = tr_data
        auid, snid, uniqueid,  itemid, amount, count, callback = args
        info("IRealZzima._returnNotEnough User %s failed to buy %s, not enough ZZGold: %s of %s", auid, itemid, amount, balance)
        callback({'ok': 0, 'ec': EC.ZZIMA_NOT_ENOUGH_ZZGOLD, 'balance': balance})

    def attachTo(self, auid, snid):
        self.original_snid = snid
        return IRealUserZZimacom(self, auid, snid)


class IRealUserZZimacom(IUserZZimacom):

    def __init__(self, izz, auid, snid):
        self.izz = izz
        self.auid = auid
        self.snid = snid

    def startTransaction(self, transactionId, itemId, itemPrice, count, callback=None):
        return self.izz.startTransaction(self.auid, self.snid, transactionId, itemId, itemPrice, count, callback)

    def getBalance(self, callback=None):
        return self.izz.getUserBalance(self.auid, self.snid,  callback)

