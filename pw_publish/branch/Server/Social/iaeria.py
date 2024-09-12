# -*- coding: utf-8 -*-
#!/usr/bin/env python
#
# (C) Danil "Eleneldil" Lavrentyuk, 2013, Nival Network
#
# An interface to AeriaGames API

from base.helpers import *
from functools import partial
from tornado.httpclient import HTTPRequest
import tornado.curl_httpclient
from tornado.httpclient import AsyncHTTPClient
from tornado.httputil import HTTPHeaders

#sys.path.append('cfg')
#import cfg

import EC
import CC

# Was a user logged in through AeriaGames?
AERIA_AUTH_USED = 0
AERIA_AUTH_NO = 1
AERIA_AUTH_EXPIRED = 2

AERIA_ORDER_STATUS_OK = 0
AERIA_ORDER_STATUS_NOT_ENOUGH = 1
AERIA_ORDER_STATUS_EXPIRED = 2
AERIA_ORDER_STATUS_TIMEOUT = 3
AERIA_ORDER_STATUS_ERROR = 4

# codes from the AeriaGames API manual:
INVALID_ACCESS_TOKEN = 190
INVALID_REFRESH_TOKEN = 192
SA_INVALID_REFRESH_TOKEN = 28 # returned by SA if refresh token received 192 error from Aeria
NOT_ENOUGHT_AP = 251

AERIA_LG_START_TRANSACTION = 1
AERIA_LG_TRANSACTION_FASTTRY = 5
AERIA_LG_TRANSACTION_TIMEOUT = 20
AERIA_LG_TRANSACTION_MAXTRYS = 5
AERIA_LG_TRANSACTION_LONGTIMEOUT = 300

AERIA_LG_REPLENISH = 2
AERIA_LG_REPLENISH_FASTTRY = 5
AERIA_LG_REPLENISH_TIMEOUT = 20
AERIA_LG_REPLENISH_MAXTRYS = 5
AERIA_LG_REPLENISH_LONGTIMEOUT = 300


def SaveHTTPClientConfig():
    cls = AsyncHTTPClient
    if hasattr(cls, '_save_configuration'):
        return cls._save_configuration()
    return cls._impl_class, cls._impl_kwargs

def RestoreHTTPClientConfig(saved):
    cls = AsyncHTTPClient
    if hasattr(cls, '_restore_configuration'):
        cls._restore_configuration(saved)
    cls._impl_class, cls._impl_kwargs = saved

class IAeria(object):
    def startTransaction(self, auid, transactionId, remoteIp, itemId, itemName, itemPrice, callback):
        raise NotImplementedError()

    def getUserBalance(self, auid, callback=None):
        raise NotImplementedError()


class IUserAeria:
    def startTransaction(self, transactionId, itemId, itemName, itemPrice, callback=None):
        raise NotImplementedError()

    def getBalance(self, callback=None):
        raise NotImplementedError()


class IRealAeria(IAeria):

    def __init__(self, appId, appKey, aeriaUrl, isTest, http, sa, request_limit):
        self.appId = appId
        self.appKey = appKey
        self.baseUrl = aeriaUrl
        if self.baseUrl[-1] != '/':
            self.baseUrl += '/'
        self.url = self.baseUrl + 'services/v2/user/me/'
        self.isTest = isTest
        self.requests = {}

        saved = SaveHTTPClientConfig()
        #info("http: saved [%r] ",saved)
        AsyncHTTPClient.configure("tornado.curl_httpclient.CurlAsyncHTTPClient")
        AsyncHttpCurl = AsyncHTTPClient
        self.http = AsyncHttpCurl(max_clients=request_limit)
        RestoreHTTPClientConfig(saved)
        """ test:
        info("http: %r %r %r",self.http, dir(self.http), str(self.http))
        AsyncHttpSimple = AsyncHTTPClient
        test = AsyncHttpCurl(max_clients=request_limit)
        info("http: %r %r [%r]", request_limit, AsyncHttpSimple, test)
        """
        self.sa = sa

    def startTransaction(self, *args):
        # args: auid, transactionId, remoteIp, itemId, itemName, itemPrice, callback
        self.sa.getAeriaToken(args[0],
            partial(self._onGetAeriaToken, callback=partial(self._purchaseItem, data=args)))

    def getUserBalance(self, auid, callback=None):
        raise NotImplementedError()
        #TODO implement it!

    def _getBalance(self, sntoken, callback):
        self._fetch(''.join((self.url, 'ap?access_token=', sntoken)), None, partial(self._onGetAp, callback=callback))

    def _refreshToken(self, auid, args, callback):
        self.sa.refreshAeriaToken(auid, partial(self._onGetAeriaToken,
            callback=partial(self._onTokenRefreshed, auid=auid, args=args, callback=callback)))

    def _onGetAeriaToken(self, result, callback):
        "Callback for SA request for stored sntoken and for refresh sntoken."
        info("[DEBUG] _onGetAeriaToken: result: %r, callback %r", result, callback)
        if result is None:
            error = {'ok' : 0, 'ec': EC.AERIA_LOCAL_SA_FAILURE}
        elif result.get('error', 0):
            if result['error'] == SA_INVALID_REFRESH_TOKEN: # could be returned only for refresh sntoken request
                error = {'ok' : 0, 'ec': EC.AERIA_TOKEN_EXPIRED}
            else:
                error = {'ok': 0, 'ec': EC.AERIA_LOCAL_SA_FAILURE, 'em': str(result)}
        elif not result.get('sntoken', None):
            error = {'ok': 0, 'ec': EC.AERIA_LOCAL_SA_FAILURE, 'em': 'No sntoken returned'}
        else:
            error = None
        if error:
            info("IRealAeria._onGetAeriaToken error: %s", error)
            callback(None, error)
        else:
            callback(result['sntoken'], None)

    def _onGetAp(self, data, error, callback):
        if error is None:
            callback(data.get('balance', 0))
        else:
            info("IRealAeria._onGetAp error: %s", error)
            callback(0)

    def _purchaseItem(self, sntoken, error, data):
        if sntoken is None:
            # data[-1] is a callback
            data[-1](error)
            return
        auid, transactionId, remoteIp, itemId, itemName, itemPrice, callback = data
        args = {
            'txn_id': transactionId,
            'item_id': itemId,
            'price': itemPrice,
            'item_name': itemName,
            'user_ip': remoteIp
        }
        self._callPurchase(auid, sntoken, args, callback)

    def _onTokenRefreshed(self, sntoken, error, auid, args, callback):
        if sntoken is None:
            # data[-1] is a callback
            callback(error)
            return
        self._callPurchase(auid, sntoken, args, callback)

    def _callPurchase(self, auid, sntoken, args, callback):
        url = ''.join((self.url, 'item_purchase?access_token=', sntoken))
        _callback = partial(self._onAeriaPurchase, tr_data=(auid, args, sntoken, callback))
        self._fetch(url, urllib.urlencode(args), _callback)

    def _onAeriaPurchase(self, result, error, tr_data):
        auid, args, sntoken, callback = tr_data
        if error:
            data = {'ok': 0}
            code = error.get('code', None)
            if 'code' is not None:
                if code == INVALID_ACCESS_TOKEN:
                    self._refreshToken(auid, args, callback)
                    return
                elif code == NOT_ENOUGHT_AP:
                    self._getBalance(sntoken, partial(self._returnNotEnough, data=tr_data))
                    return
                else:
                    data['ec'] = EC.AERIA_OPERATION_FAILURE
                    data['em'] = 'AeriaGames error: %r' % error
            if 'fail' in error:
                data['ec'] = EC.AERIA_OPERATION_FAILURE
                data['em'] = error['fail']
        else:
            data = {'ok': 1, 'balance': result['balance']}
        callback(data)

    def _returnNotEnough(self, balance, data):
        auid, args, sntoken, callback = data
        info("User %s failed to buy %s (%s), not enough AP: %s of %s", auid, args['item_name'], args['item_id'], args['price'], balance)
        callback({'ok': 0, 'ec': EC.AERIA_NOT_ENOUGH_AP, 'balance': balance})

    def _onFetch(self, http_reply, callback):
        #info('Aeria responded (all=%r)', http_reply)
        try:
            if http_reply:
                if  http_reply.body:
                    info('Aeria responded (body=%r)', http_reply.body)
                    data = json.loads(urllib.unquote(http_reply.body))
                    if (not http_reply.error) or data.get('error', None):
                        # in case of expired access token Aeria return error 401 AND nonempty body with error.cope = 190
                        # keep the same logic for other cases when both HTTP error and nonempty body with error are provided
                        callback(data.get('data', None), data.get('error', None))
                        return
                else:
                    info('Aeria responded with empty body: %r', http_reply)
        except Exception, details:
            catch()
        callback(None, {'fail': str(http_reply)})

    def _fetch(self, url, data, callback):
        _callback = partial(self._onFetch, callback=callback)
        info('iaeria: _fetch %s, %s, validate_cert=%s', url, data, not self.isTest)
        try:
            self.http.fetch(
                HTTPRequest(
                    url=url,
                    method='POST' if data is not None else 'GET',
                    body=data,
                    validate_cert=not self.isTest,
                    headers=HTTPHeaders({'User-Agent':'PWServer'})),
                _callback)
            return
        except:
            catch()
            _callback( None )

    def attachTo(self, auid, remoteIp):
        return IRealUserAeria(self, auid, remoteIp)


class IRealUserAeria(IUserAeria):

    def __init__(self, iaeria, auid, remoteIp):
        self.iaeria = iaeria
        self.auid = auid
        self.remoteIp = remoteIp

    def startTransaction(self, transactionId, itemId, itemName, itemPrice, callback=None):
        return self.iaeria.startTransaction(self.auid, transactionId, self.remoteIp, itemId, itemName, itemPrice, callback)

    def getBalance(self, callback=None):
        return  self.iaeria.getUserAp(self.auid, callback)
