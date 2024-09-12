# -*- coding: utf-8 -*-
#!/usr/bin/env python

from base.helpers import *
import functools
import tornado.httpclient

import cfg

import EC
import CC

STEAM_ORDER_STATUS_BUY = 0
STEAM_ORDER_STATUS_CONFIRM = 1
STEAM_ORDER_STATUS_WAIT_FOR_REPLENISH = 2
STEAM_ORDER_STATUS_WAIT_FOR_STEAMCONFIRM = 3

STEAM_REPLENISH_TIMEOUT = 180 # seconds
STEAM_ORDER_TIMEOUT = 60*60*2 # seconds

##---------------------------------------------------------------------------------------------

class ISteam:
        
    def startTransaction(self, steamId, remoteIp, langCode, currencyCode, items, callback=None):
        # this method generating server unique 64bit orderId
        # than pass orderId to Steam 
        # returns result (or timeout)
        # method params:
        #   'steamId' should be <STRING> from social aggregator snuid
        #   'items' should be list of tuples (itemId <INT32>, quantity <INT>, amount <INT>, desc <utf8 STRING>, category <utf8 STRING>)
        #   'langCode' should be <STRING> in ISO 639-1 language code
        #   'currencyCode' should be <STRING> in ISO 4217 currency code
        # returns dict
        # {
        #     'orderCode' : <STRING>, // order code that should be passe to retrieveTransaction and confirmTransaction methods
        #     'ec'        : <INT>,    // error code (0 - if all ok, >0 otherwise)
        #     'ok'        : <INT>,    // boolean flag if request was successful
        #     'em'        : <STRING>, // optional error description
        # }
        raise NotImplementedError()

    def retrieveTransaction(self, steamId, orderId, orderCode):
        # method params:
        #   'steamId' should be <STRING> from social aggregator snuid
        #   'orderId' should be <INT64> 
        #   'orderCode' should be <STRING8> 
        # return items // returns 'items' passed to startTransaction method if transaction (steamId, orderId, orderCode) exists, None otherwise
        raise NotImplementedError()
        
    def confirmTransaction(self, steamId, orderId, orderCode, callback=None):
        # checking if transaction exists before calling Steam
        # call Steam to confirm transaction
        # returns result (or timeout)
        #
        # returns dict
        # {
        #     'ec'        : <INT>,    // error code (0 - if all ok, >0 otherwise)
        #     'ok'        : <INT>,    // boolean flag if request was successful
        #     'em'        : <STRING>, // optional error description
        # }
        raise NotImplementedError()

    def retrieveUserInfo(self, steamId, remoteIp, callback=None):
        raise NotImplementedError()

    def retrieveOwnershipInfo(self, steamId, callback=None):
        raise NotImplementedError()

    def checkOwnershipInfo(self, steamId, appId, callback=None):
        raise NotImplementedError()

    def attachTo(self, steamId, remoteIp, auid, callback=None):
        raise NotImplementedError()

class IUserSteam:

    def startTransaction(self, langCode, currencyCode, items, callback=None):
        raise NotImplementedError()

    def retrieveTransaction(self, orderId, orderCode):
        raise NotImplementedError()

    def confirmTransaction(self, orderId, orderCode, callback=None):
        raise NotImplementedError()

    def checkOwnershipInfo(self, appId, callback=None):
        raise NotImplementedError()

##---------------------------------------------------------------------------------------------
class IRealSteam(ISteam):

    def __init__(self, appId, appKey, steamUrl, isSandbox, http, data, steamOrderBase=0L, steamOrderOffset=0L):
        self.appId = appId
        self.appKey = appKey
        self.steamBaseUrl = steamUrl
        if self.steamBaseUrl[-1] != '/':
            self.steamBaseUrl += '/'
        self.steamUrl = self.steamBaseUrl
        if isSandbox:
            self.steamUrl += 'ISteamMicroTxnSandbox/'
        else:
            self.steamUrl += 'ISteamMicroTxn/'
        self.requests = {}
        self.http = http
        self.data = data
        self.steamOrderBase = steamOrderBase << 56
        self.steamOrderOffset = steamOrderOffset
    
    def _generateCode(self):
        s = ''
        for i in range(8):
            s += chr(random.randint(65, 90))
        return s

    def startTransaction(self, steamId, remoteIp, langCode, currencyCode, items, callback):
        def cb(response):
            _callback = functools.partial( self._startTransaction, data = (steamId, remoteIp, langCode, currencyCode, items, callback) )
            self.data.find_one("counters", "counters", {"name": "steamOrder"}, callback=_callback)
        self.data.increment("counters", "counters", {"name": "steamOrder"}, {"ammount": 1}, callback=cb)

        
    def _startTransaction(self, result, data):
        steamId, remoteIp, langCode, currencyCode, items, callback = data    

        if not result or not result.get("r") or result["r"].get("err"):
            data = {'ok' : 0, 'ec' : EC.STEAM_LOCAL_MONGO_FAILURE}
            callback(data)
            return

        steamUrl = self.steamUrl + 'InitTxn/V0002/'
        steamUrl += '?format=json&key='+self.appKey
        orderId = (self.steamOrderBase | int(result['r'].get('ammount',0) or 0)) + self.steamOrderOffset
        args = {
            'orderid' : orderId,
            'steamid' : steamId,
            'appId': self.appId,
            'itemcount' : len(items),
            'language' : langCode,
            'currency' : currencyCode,
            'ipaddress' : remoteIp,
        }

        for index, (itemId, quantity, amount, desc, category) in enumerate(items):
            args['itemid[%d]' % index] = itemId            
            args['qty[%d]' % index] = quantity            
            args['amount[%d]' % index] = amount            
            args['description[%d]' % index] = desc            
            args['category[%d]' % index] = category            

        info('Start Steam transaction (steamId=%s orderId=%s ip=%s args=%r)' % (steamId, orderId, remoteIp, args))
        _callback = functools.partial( self._onStart, callback=callback, data = (orderId, steamId, items) )
        self.fetch(steamUrl, urllib.urlencode(args), _callback, 'response')

    def parseError(self, http_reply, message):
       e = http_reply.get('error', {})
       message = e.get('errordesc', message)
       ecode = e.get('errorcode', 0)
       return message, ecode

    def _onStart(self, http_reply, message, callback, data):
        ecode = 0
        if http_reply is not None: # all ok
            if http_reply['result'] == 'OK':
                orderCode = self._generateCode()
                orderId, steamId, items = data
                self.requests[orderCode] = (orderId, steamId, items, time.time())
                data = {'orderCode' : orderCode, 'orderId' : orderId, 'ok' : 1, 'ec' : 0}
            else:
                data = {'ok' : 0, 'ec' : EC.STEAM_BILLING_PROCESSING_ERROR}
                message, ecode = self.parseError(http_reply, message)
        else:
            data = {'ok' : 0, 'ec' : EC.STEAM_BILLING_ERROR}
        if message is not None:
            if ecode != 0:
                message += ' (steam_error_code=%s)' % ecode
            data['em'] = message
            
        callback(data)

    def _onConfirm(self, http_reply, message, callback):
        ecode = 0
        if http_reply is not None: # all ok
            if http_reply['result'] == 'OK':
                data = {'ok' : 1, 'ec' : 0}
            else:
                data = {'ok' : 0, 'ec' : EC.STEAM_BILLING_PROCESSING_ERROR}
                message, ecode = self.parseError(http_reply, message)
        else:
            data = {'ok' : 0, 'ec' : EC.STEAM_BILLING_ERROR}
        if message is not None:
            if ecode != 0:
                message += ' (steam_error_code=%s)' % ecode
            data['em'] = message
        callback(data)

    def cancelTransaction(self, steamId, orderId, orderCode):
        items = self.retrieveTransaction(steamId, orderId, orderCode)
        if items is not None:
            del self.requests[orderCode]
    
    def retrieveTransaction(self, steamId, orderId, orderCode):
        data = self.requests.get(orderCode, None)
        if data is not None:
            _orderId, _steamId, _items, _start = data
            if _orderId == orderId and _steamId == steamId:
                return _items
        return None
        
    def confirmTransaction(self, steamId, orderId, orderCode, callback):
        items = self.retrieveTransaction(steamId, orderId, orderCode)
        if items is not None:
            del self.requests[orderCode]
            steamUrl = self.steamUrl + 'FinalizeTxn/V0001/'
            steamUrl += '?format=json&key='+self.appKey
            args = {
                'orderid' : orderId,
                'appId': self.appId,
            }
            info('Confirm Steam transaction (steamId=%s orderId=%s args=%r)' % (steamId, orderId, args))
            _callback = functools.partial( self._onConfirm, callback=callback )
            self.fetch(steamUrl, urllib.urlencode(args), _callback, 'response')
        else:
            data = {'ok' : 0, 'ec' : EC.STEAM_TRANSACTION_NOT_FOUND}
            callback(data)

    def _onRetrieveUser(self, http_reply, message, callback):
        ecode = 0
        if http_reply is not None: # all ok
            if http_reply['result'] == 'OK':
                data = {'user' : http_reply.get('params', {}), 'ok' : 1, 'ec' : 0}
            else:
                data = {'ok' : 0, 'ec' : EC.STEAM_BILLING_PROCESSING_ERROR}
                message, ecode = self.parseError(http_reply, message)
        else:
            data = {'ok' : 0, 'ec' : EC.STEAM_BILLING_ERROR}
        if message is not None:
            if ecode != 0:
                message += ' (steam_error_code=%s)' % ecode
            data['em'] = message
        callback(data)

    def retrieveUserInfo(self, steamId, remoteIp, callback=None):
        steamUrl = self.steamUrl + 'GetUserInfo/V0001/'
        steamUrl += '?format=json&key='+self.appKey
        args = {
            'steamid' : steamId,
            'ipaddress' : remoteIp,
        }
        steamUrl += '&'+urllib.urlencode(args)
        _callback = functools.partial( self._onRetrieveUser, callback=callback )
        self.fetch(steamUrl, None, _callback, 'response')

    def _onRetrieveOwnership(self, http_reply, message, callback):
        ecode = 0
        if http_reply is not None: # all ok
            data = {'apps' : http_reply.get('apps', []), 'ok' : 1, 'ec' : 0}
        else:
            data = {'ok' : 0, 'ec' : EC.STEAM_BILLING_ERROR}
        if message is not None:
            data['em'] = message
        callback(data)

    def retrieveOwnershipInfo(self, steamId, callback=None):
        steamUrl = self.steamBaseUrl + 'ISteamUser/GetPublisherAppOwnership/V0002/'
        steamUrl += '?format=json&key='+self.appKey
        args = {
            'appid' : self.appId,
            'steamid' : steamId,
        }
        steamUrl += '&'+urllib.urlencode(args)
        _callback = functools.partial( self._onRetrieveOwnership, callback=callback )
        self.fetch(steamUrl, None, _callback, 'appownership')

    def _onCheckOwnership(self, http_reply, message, callback):
        ecode = 0
        if http_reply is not None: # all ok
            data = {'app' : http_reply, 'ok' : 1, 'ec' : 0}
        else:
            data = {'ok' : 0, 'ec' : EC.STEAM_BILLING_ERROR}
        if message is not None:
            data['em'] = message
        callback(data)

    def checkOwnershipInfo(self, steamId, appId, callback=None):
        steamUrl = self.steamBaseUrl + 'ISteamUser/CheckAppOwnership/V0001/'
        steamUrl += '?format=json&key='+self.appKey
        args = {
            'appid' : appId,
            'steamid' : steamId,
        }
        steamUrl += '&'+urllib.urlencode(args)
        _callback = functools.partial( self._onCheckOwnership, callback=callback )
        self.fetch(steamUrl, None, _callback, 'appownership')

    def _onFetch(self, http_reply, keyword, callback):
        try:
            if http_reply and (not http_reply.error):   
                info('Steam responded (value=%r)' % http_reply.body)
                unquote_body = urllib.unquote( http_reply.body )
                data = json.loads(unquote_body)
                callback(data.get(keyword, None), None)
                return
        except Exception, details:
            catch()
        callback(None, str(http_reply))

    def fetch(self, url, data, callback, keyword):
        _callback = functools.partial( self._onFetch, keyword=keyword, callback=callback )
        try:
            headers = {"Accept-Encoding":"gzip", "Content-Type": "application/x-www-form-urlencoded"}
            if data is not None:
                request = tornado.httpclient.HTTPRequest(url, headers=headers, request_timeout=120.0, method='POST', body=data, validate_cert=False)
            else:
                request = tornado.httpclient.HTTPRequest(url, headers=headers, request_timeout=120.0, method='GET', validate_cert=False) 
            self.http.fetch( request, _callback )
            return
        except:
            catch()
            _callback( None )

    def attachTo(self, steamId, remoteIp, auid, callback=None):
        return IRealUserSteam(self, steamId, remoteIp, auid, callback)

class IRealUserSteam(IUserSteam):

    def __init__(self, isteam, steamId, remoteIp, auid, callback=None):
        self.isteam = isteam
        self.steamId = steamId 
        self.remoteIp = remoteIp
        self.auid = auid 
        self.user = None
        self.isUserResponded = False
        self.ownership = []
        self.isOwnershipResponded = False
        self.callback = callback
        self.isteam.retrieveUserInfo(self.steamId, self.remoteIp, self._onRetrieveUser)
        self.isteam.retrieveOwnershipInfo(self.steamId, self._onRetrieveOwnership)

    def getUser(self):
        return self.user

    def getOwnership(self):
        return self.ownership

    def _onRetrieveOwnership(self, data):
        if data:        
            ownership = data.get('apps', [])
            for app in ownership:
                if app.get('permanent', False) and app.get('ownsapp', False):
                    self.ownership.append(app.get('appid'))
        if self.ownership:
            info('Steam ownership data retrieved (auid=%s steamId=%s data=%r)' % (self.auid, self.steamId, self.ownership))
        else:
            warn('No Steam ownership data retrieved (auid=%s steamId=%s)' % (self.auid, self.steamId) )
        self.isOwnershipResponded = True
        if self.isUserResponded:
            if self.callback:
                self.callback(self.user, self.ownership)

    def _onRetrieveUser(self, data):
        if data:
            self.user = data.get('user', None)
        if self.user:
            info('Steam user data retrieved (auid=%s steamId=%s data=%r)' % (self.auid, self.steamId, self.user))
        else:
            warn('No Steam user data retrieved (auid=%s steamId=%s)' % (self.auid, self.steamId) )
        self.isUserResponded = True
        if self.isOwnershipResponded:
            if self.callback:
                self.callback(self.user, self.ownership)
        
    def startTransaction(self, langCode, currencyCode, items, callback):
        return self.isteam.startTransaction(self.steamId, self.remoteIp, langCode, currencyCode, items, callback)

    def retrieveTransaction(self, orderId, orderCode):
        return self.isteam.retrieveTransaction(self.steamId, orderId, orderCode)

    def confirmTransaction(self, orderId, orderCode, callback):
        return self.isteam.confirmTransaction(self.steamId, orderId, orderCode, callback)

    def cancelTransaction(self, orderId, orderCode):
        return self.isteam.cancelTransaction(self.steamId, orderId, orderCode)

    def _onCheck(self, data, callback):
        if data:
            app = data.get('app', {})
            if app.get('permanent', False) and app.get('ownsapp', False):
                callback(True)
                return    
        callback(False)

    def checkOwnershipInfo(self, appId, callback=None):
        _callback = functools.partial( self._onCheck, callback=callback )
        return self.isteam.checkOwnershipInfo(self.steamId, appId, _callback)

