#!/usr/bin/env python
# -*- coding: utf-8 -*-

# (C) Dmitry Kolb 2014, Nival Network 
# An interface for ArcGames API

from base.helpers import *
from functools import partial
from tornado.httpclient import HTTPRequest
from tornado.httputil import HTTPHeaders, url_concat

import hmac
import hashlib
import urllib
#sys.path.append('cfg')
#import cfg

import EC
import CC

# ArcGames API Error
ARCGAMES_INTERNAL_DATABASE_ERROR = 402
#Invalid method call
ARCGAMES_METHOD_NOT_FOUND = 6
ARCGAMES_USER_NOT_EXIST = 11
# Requested same account too many times in short amount time
ARCGAMES_MANY_REQUEST = 12
#Some of the provided parameter values are invalid
ARCGAMES_INVALID_PARAM = 14
#Not enough currency in the balance to process a purchase transaction
ARCGAMES_NOT_ENOUGH_CURRENCY = 1502

SA_INVALID_REFRESH_TOKEN = 28

ARCGAMES_LG_START_TRANSACTION = 1
ARCGAMES_LG_TRANSACTION_FASTTRY = 5
ARCGAMES_LG_TRANSACTION_TIMEOUT = 20
ARCGAMES_LG_TRANSACTION_MAXTRYS = 5
ARCGAMES_LG_TRANSACTION_LONGTIMEOUT = 300

ARCGAMES_LG_REPLENISH = 2
ARCGAMES_LG_REPLENISH_FASTTRY = 5
ARCGAMES_LG_REPLENISH_TIMEOUT = 20
ARCGAMES_LG_REPLENISH_MAXTRYS = 5
ARCGAMES_LG_REPLENISH_LONGTIMEOUT = 300

class IArcGames(object):
    def startTransaction(self, transactionId, itemId, itemPrice, count, callback):
        raise NotImplementedError()

    def getUserBalance(self, auid, snid, callback=None):
        raise NotImplementedError()

    def logPurchaseitem(self, auid, snid, itemName, itemQuantity, totalPrice, currency,
                                             transactionId, transactionDate, callback):
        raise NotImplementedError()


class IUserArcGames:
    def startTransaction(self, transactionId, itemId, itemPrice, count,   callback=None):
        raise NotImplementedError()

    def getBalance(self, callback=None):
        raise NotImplementedError()

    def logPurchaseitem(self, itemName, itemQuantity, totalPrice, currency,
                              transactionId,transactionDate, callback):
        raise NotImplementedError()

class IRealArcGames(IArcGames):

    def __init__(self, appId, appAbbr, appKey, arcUrl, arcBillUrl, zoneId, isTest, http, sa):
        self.appAbbr = appAbbr
        self.appId = appId
        self.appKey = appKey
        self.zoneId = zoneId
        proc_url = lambda u: u + '/' if u[-1] != '/' else u
        assert arcUrl
        self.baseUrl = proc_url(arcUrl)
        self.url = self.baseUrl + '?'
        assert arcBillUrl
        self.urlbil = proc_url(arcBillUrl) + '?'
        self.isTest = isTest
        self.requests = {}
        self.http = http
        self.sa = sa

    def startTransaction(self, *args):
        # args: auid, snid, amount, itemid, count, uniqueid, callback
        self.sa.getInfo(args[0], args[1], 1,
            partial(self.onGetArcGamesUserId, callback=partial(self._purchaseItem, data=args[2:])))

    def getUserBalance(self, *args):
        self.sa.getInfo(args[0], args[1], 1,
            partial(self.onGetArcGamesUserId, callback=partial(self._getBalance, callback=args[2])))

    def logPurchaseitem(self, *args):
        # args: auid, snid, itemName, itemQuantity, totalPrice, currency, transactionId, transactionDate, callback
        self.sa.getInfo(args[0], args[1], 1,
                        partial(self.onGetArcGamesUserId, callback=partial(self._getLogPurchaseItem, data=args[2:])))


    def _getLogPurchaseItem(self, info, error,  data):
        itemName, itemQuantity, totalPrice, currency, transactionId, transactionDate, callback = data

        args = {"method": "log.purchaseitem",
            'params':{
                "userId": info.get('snuid', ''),
                "itemName": itemName,
                "itemQuantity": itemQuantity,
                "totalPrice": totalPrice,
                "currency": currency,
                "transactionId": transactionId,
                "transactionDate": transactionDate
            }
        }
        self._callLogPurchaseItem(info.get('snuid', ''), args, callback)

        #self._fetch(self.url, args, partial(self._onGetAp, callback=callback))

    def _callLogPurchaseItem(self, info, args, callback):
        _callback = partial(self._onArcGamesLogPurchaseItem, tr_data=(info, args, callback))
        self._fetch(self.url, args, _callback)

    def _onArcGamesLogPurchaseItem(self, result, error, tr_data):
        inf, args, callback = tr_data
        if error:
            data = {'ok': 0}
            data['ec'] = EC.ARCGAMES_OPERATION_FAILURE
            data['em'] = 'ArcGames error: %r' % error
        else:
            info("IRealArcGames.ArcGamesLogPurchaseItem : %s", result)
            data = {'ok': 1, "status": result['result']}
        callback(data)

    def onGetArcGamesUserId(self, result, callback):
        "Callback for SA request for stored sntoken and for refresh sntoken."
        info("IRealArcGames.onGetArcGamesUserId: result: %r, callback %r", result, callback)
        if result is None:
            error = {'ok' : 0, 'ec': EC.ARCGAMES_LOCAL_SA_FAILURE}
        elif result.get('error', 0):
            if result['error'] == SA_INVALID_REFRESH_TOKEN: # could be returned only for refresh sntoken request
                error = {'ok' : 0, 'ec': EC.ARCGAMES_TOKEN_EXPIRED}
            else:
                error = {'ok': 0, 'ec': EC.ARCGAMES_LOCAL_SA_FAILURE, 'em': str(result)}
        else:
            props = result['get_info'].get('props')
            if not props:
                error = {'ok': 0, 'ec': EC.ARCGAMES_LOCAL_SA_FAILURE, 'em': 'No props returned'}

            else:
                error = None

        if error:
            info("IRealArcGames._onGetArcGamesUserId error: %s", error)
            callback(None, error)
        else:
            callback(result['get_info'][self.original_snid], None)

    def _onGetAp(self, data, error, callback):
        if error is None:
            callback(data.get('balance', 0), None)
        else:
            info("IRealArcGames._onGetAp error: %s", str(error))
            callback(0)

    def _purchaseItem(self, inf, error,  data):

        if inf is None:
            # data[-1] is a callback
            data[-1](error)
            return
        #charid, amount, itemid, count, uniqueid, callback
        uniqueid,  itemid, amount, count, callback = data
        print itemid
        args = {"method": "currency.purchaseitem",
            'params':{
                'userid': inf.get('snuid', ''),
                'zoneid': self.zoneId,
                'charid': inf.get('passportid', 0),
                'id': inf.get('passportid', 0),
                'amount': amount,
                'itemid':  itemid,
                'count': count,
                'uniqueid': uniqueid
            }
        }
        self._callPurchase(inf, args, callback)

    def _getBalance(self, inf, error, callback):
        args = {"method": "currency.getbalance",
            'params':{
                'userid': inf.get('snuid'),
                'id': inf.get('passportid'),
                'zoneid': self.zoneId,
            }
        }
        self._callBalance(inf, args, callback)

    def _callBalance(self, inf, args, callback):
        _callback = partial(self._onArcGamesBalance, tr_data=(inf, args, callback))
        self._fetch(self.urlbil, args, _callback)


    def _onArcGamesBalance(self, result, error, tr_data):
        info, args, callback = tr_data
        if error:
            data = {'ok': 0}
            data['ec'] = EC.ARCGAMES_OPERATION_FAILURE
            data['em'] = 'ArcGames error: %r' % error
        else:
            data = {'ok': 1, 'ec': 0, 'balance': result['balance']}
        callback(data)

    def _callPurchase(self, inf, args, callback):
        _callback = partial(self._onArcGamesPurchase, tr_data=(inf, args, callback))
        self._fetch(self.urlbil, args, _callback)

    def _onArcGamesPurchase(self, result, error, tr_data):
        inf, args, callback = tr_data
        info("IRealArcGames._onArcGamesPurchase info: %r", inf)
        if error:
            data = {'ok': 0}
            code = error.get('code', None)
            if code is not None:
                if code == ARCGAMES_NOT_ENOUGH_CURRENCY:
                    self._getBalance(inf, None, partial(self._returnNotEnough, tr_data=tr_data))
                    return
                else:
                    data['ec'] = EC.ARCGAMES_OPERATION_FAILURE
                    data['em'] = 'ArcGames error: %r' % error
            if 'fail' in error:
                data['ec'] = EC.ARCGAMES_OPERATION_FAILURE
                data['em'] = error['fail']
        else:
            data = {'ok': 1, 'balance': result['balance']}
        callback(data)

    def _returnNotEnough(self, balance, tr_data):
        account, args, callback = tr_data
        info("IRealArcGames._returnNotEnough User %s failed to buy %s (%s), not enough ZEN: %s of %s", args['params']['charid'], args['params']['itemid'], args['params']['amount'], balance)
        callback({'ok': 0, 'ec': EC.ARCGAMES_NOT_ENOUGH_ZEN, 'balance': balance})

    def _onFetch(self, http_reply, callback):
        try:
            if http_reply:
                if  http_reply.body:
                    info('ArcGames responded (body=%r)', http_reply.body)
                    data = json.loads(urllib.unquote(http_reply.body))
                    if data.get('status', None) == 'failure':
                        # in case of expired access token ArcGames return error 401 AND nonempty body with error.cope = 190
                        # keep the same logic for other cases when both HTTP error and nonempty body with error are provided
                        callback(None, data.get('error', None))
                        return
                    else:
                        callback(data.get('data', None), None)
                        return
                else:
                    info('ArcGames responded with empty body: %r', http_reply)
        except Exception, details:
            catch()
        callback(None, {'fail': str(http_reply)})

    def _fetch(self, url, data, callback):
        _callback = partial(self._onFetch, callback=callback)
        info('IRealArcGames._fetch %s, %s, validate_cert=%s', url, data, not self.isTest)
        sdata = json_dumps(data)
        random = 'abcdef'
        format = 'json'
        time1 = str(int(time.time()))
        hashstring = random + time1 + str(1) + self.appAbbr + sdata
        sig = urllib.quote(hmac.new(self.appKey.encode('cp1251'), hashstring, hashlib.sha1).hexdigest())
        params = {'r': random,
                  'f': format,
                  't': time1,
                  'v': str(1),
                  'g': self.appAbbr,
                  'sig': sig}
        params_encodes = [k + '=' + urllib.quote_plus(v) for k, v in params.iteritems()]

        request = url + '&'.join(params_encodes)
        try:
            self.http.fetch(
                HTTPRequest(
                    url=request,
                    method='POST',
                    body=sdata,
                    validate_cert= False,
                    headers=HTTPHeaders({'User-Agent': 'PWServer'})),
                _callback)
            return
        except:
            catch()
            _callback(None)

    def attachTo(self, auid, snid):
        self.original_snid = snid
        return IRealUserArcGames(self, auid, snid)


class IRealUserArcGames(IUserArcGames):

    def __init__(self, iarcgames, auid, snid):
        self.iarcgames = iarcgames
        self.auid = auid
        self.snid = snid

    def startTransaction(self, transactionId, itemId, itemPrice, count, callback=None):
        return self.iarcgames.startTransaction(self.auid, self.snid, transactionId, itemId, itemPrice, count, callback)

    def getBalance(self, callback=None):
        return self.iarcgames.getUserBalance(self.auid, self.snid, callback)

    def logPurchaseitem(self, itemName, itemQuantity, totalPrice, currency, transactionId, transactionDate, callback):
        return self.iarcgames.logPurchaseitem(self.auid, self.snid, itemName, itemQuantity, totalPrice, currency,
                                             transactionId, transactionDate, callback)

