# -*- coding: utf-8 -*-
import sys, os, time, logging, json
import unittest
import urlparse

os.chdir('..')
sys.path.append( os.path.abspath('.') )
sys.path.append( os.path.abspath('cfg') )

import isteam

class DummyHttp:

    def __init__(self):
        self.requests = {}

    def fetch(self, request, callback):
        if type(request) == str:
            body = None
            url = request
        else:
            body = request.body
            url = request.url
        self.requests[url] = (body, callback)

    def push(self, url, result, error=None):
        data, callback = self.requests[url]
        class Response:
            def __init__(self, body, error):
                self.body = body
                self.error = error
        del self.requests[url] 
        callback(Response(result, error))

    def clear(self):
        self.requests.clear()

class Mongo:

    def __init__(self):
        self.items = {}

    def increment(self, shard_key, collection, query, ammount, callback=None, params=None):
        name = query['name']

        if name not in self.items:
            self.items[name] = {'r': {'ammount': 1}}
        else: 
            self.items[name]['r']['ammount'] += 1
        callback(self.items[name])

    def find_one(self, shard_key, collection, query, callback=None, params=None):
        name = query['name']

        if name not in self.items:
            callback()
        else:
            callback(self.items[name])

    def set(self, name, value, callback=None):
        self.items[name] = {'r': {'ammount': value}}
        if callback:
            callback(value)

class Callback:
    def __call__(self, *args, **kvargs):
        self.args = args
        self.kvargs = kvargs

class TestSteam(unittest.TestCase):

    def test_Simple(self):
        http = DummyHttp()
        mongo = Mongo()
        mongo.set('steamOrder', 54)
        steam = isteam.IRealSteam('2345', 'key', 'https://api.steampowered.com/', True, http, mongo)
        user = isteam.IRealUserSteam(steam, '666', '127.0.0.1', 123)
        http.clear()

        class Handler:
            def __init__(self):
                self.reply = None

            def callback(self, reply):
                self.reply = reply

        handler = Handler()
        user.startTransaction('EN', 'USD', [ (123, 1, 1, 'Desc', 'Cat')], handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))
        self.assertEquals(True, 'https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key' in http.requests)        
        reply = '''
{
    "response" : 
    { 
        "result" : "OK",
        "params" : {
            "orderid" : 55,
            "transid" : 374839
        }
    }
}
'''
        http.push('https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key', reply) 
        self.assertEquals(0, handler.reply['ec'])
        self.assertEquals(1, handler.reply['ok'])
        self.assertEquals(True, handler.reply['orderCode'] != None)
        self.assertEquals(55, handler.reply.get('orderId', None))

    def test_Failure(self):
        http = DummyHttp()
        mongo = Mongo()
        mongo.set('steamOrder', 54)
        steam = isteam.IRealSteam('2345', 'key', 'https://api.steampowered.com/', True, http, mongo)
        user = isteam.IRealUserSteam(steam, '666', '127.0.0.1', 123)
        http.clear()

        class Handler:
            def __init__(self):
                self.reply = None

            def callback(self, reply):
                self.reply = reply

        handler = Handler()
        user.startTransaction('EN', 'USD', [ (123, 1, 1, 'Desc', 'Cat')], handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))
        self.assertEquals(True, 'https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key' in http.requests)        
        reply = '''
{
    "response" : 
    { 
        "result" : "Failure",
        "params" : {
            "orderid" : 55
        },
        "error" : {
            "orderid" : 1001,
            "transid" : "Action not allowed",
            "errorcode" : 115,
            "errordesc" : "Hmm"
        }
    }
}
'''
        http.push('https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key', reply) 
        self.assertEquals(0, handler.reply['ok'])
        self.assertEquals(0, handler.reply['ok'])
        self.assertEquals(None, handler.reply.get('orderCode', None))        
        self.assertEquals('Hmm (steam_error_code=115)', handler.reply['em'])
        

    def test_Timeout(self):
        http = DummyHttp()
        mongo = Mongo()
        mongo.set('steamOrder', 54)
        steam = isteam.IRealSteam('2345', 'key', 'https://api.steampowered.com/', True, http, mongo)
        user = isteam.IRealUserSteam(steam, '666', '127.0.0.1', 123)
        http.clear()

        class Handler:
            def __init__(self):
                self.reply = None

            def callback(self, reply):
                self.reply = reply

        handler = Handler()
        user.startTransaction('EN', 'USD', [ (123, 1, 1, 'Desc', 'Cat')], handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))
        self.assertEquals(True, 'https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key' in http.requests)        
        http.push('https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key', '', Exception()) 
        self.assertEquals(401, handler.reply['ec'])
        self.assertEquals(0, handler.reply['ok'])
        self.assertEquals(None, handler.reply.get('orderCode', None))

    def test_RetrieveAndConfirm(self):
        http = DummyHttp()
        mongo = Mongo()
        mongo.set('steamOrder', 54)
        steam = isteam.IRealSteam('2345', 'key', 'https://api.steampowered.com/', True, http, mongo)
        user = isteam.IRealUserSteam(steam, '666', '127.0.0.1', 123)
        http.clear()

        class Handler:
            def __init__(self):
                self.reply = None

            def callback(self, reply):
                self.reply = reply

        handler = Handler()
        user.startTransaction('EN', 'USD', [ (123, 1, 1, 'Desc', 'Cat')], handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))
        self.assertEquals(True, 'https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key' in http.requests)        
        reply = '''
{
    "response" : 
    { 
        "result" : "OK",
        "params" : {
            "orderid" : 55,
            "transid" : 374839
        }
    }
}
'''
        http.push('https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key', reply) 
        self.assertEquals(0, handler.reply['ec'])
        self.assertEquals(1, handler.reply['ok'])
        self.assertEquals(True, handler.reply['orderCode'] != None)

        items = user.retrieveTransaction(55, handler.reply['orderCode'])
        self.assertEquals(1, len(items))
        self.assertEquals((123, 1, 1, 'Desc', 'Cat'), items[0])

        self.assertEquals(0, len(http.requests))
        items = user.confirmTransaction(55, handler.reply['orderCode'], handler.callback)

        self.assertEquals(1, len(http.requests))
        self.assertEquals(True, 'https://api.steampowered.com/ISteamMicroTxnSandbox/FinalizeTxn/V0001/?format=json&key=key' in http.requests)        
        reply = '''
{
    "response" : 
    { 
        "result" : "OK",
        "params" : {
            "orderid" : 55,
            "transid" : 374839
        }
    }
}
'''
        http.push('https://api.steampowered.com/ISteamMicroTxnSandbox/FinalizeTxn/V0001/?format=json&key=key', reply) 
        self.assertEquals(0, handler.reply['ec'])
        self.assertEquals(1, handler.reply['ok'])

        
    def test_ConfirmTransactionFailure(self):
        http = DummyHttp()
        mongo = Mongo()
        mongo.set('steamOrder', 54)
        steam = isteam.IRealSteam('2345', 'key', 'https://api.steampowered.com/', True, http, mongo)
        user = isteam.IRealUserSteam(steam, '666', '127.0.0.1', 123)
        http.clear()

        class Handler:
            def __init__(self):
                self.reply = None

            def callback(self, reply):
                self.reply = reply

        handler = Handler()
        user.startTransaction('EN', 'USD', [ (123, 1, 1, 'Desc', 'Cat')], handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))
        self.assertEquals(True, 'https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key' in http.requests)        
        reply = '''
{
    "response" : 
    { 
        "result" : "OK",
        "params" : {
            "orderid" : 55,
            "transid" : 374839
        }
    }
}
'''
        http.push('https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key', reply) 
        self.assertEquals(0, handler.reply['ec'])
        self.assertEquals(1, handler.reply['ok'])
        self.assertEquals(True, handler.reply['orderCode'] != None)

        items = user.retrieveTransaction(55, handler.reply['orderCode'])
        self.assertEquals(1, len(items))
        self.assertEquals((123, 1, 1, 'Desc', 'Cat'), items[0])

        self.assertEquals(0, len(http.requests))
        items = user.confirmTransaction(55, handler.reply['orderCode'], handler.callback)

        self.assertEquals(1, len(http.requests))
        self.assertEquals(True, 'https://api.steampowered.com/ISteamMicroTxnSandbox/FinalizeTxn/V0001/?format=json&key=key' in http.requests)        
        reply = '''
{
    "response" : 
    { 
        "result" : "Failure",
        "params" : {
            "orderid" : 55,
            "transid" : 374839
        },
        "error" : {
            "errordesc" : "Ups.",
            "errorcode" : 23
        }
    }
}
'''
        http.push('https://api.steampowered.com/ISteamMicroTxnSandbox/FinalizeTxn/V0001/?format=json&key=key', reply) 
        self.assertEquals(402, handler.reply['ec'])
        self.assertEquals(0, handler.reply['ok'])
        self.assertEquals('Ups. (steam_error_code=23)', handler.reply['em'])

    def test_ConfirmTransactionNotFound(self):
        http = DummyHttp()
        mongo = Mongo()
        mongo.set('steamOrder', 54)
        steam = isteam.IRealSteam('2345', 'key', 'https://api.steampowered.com/', True, http, mongo)
        user = isteam.IRealUserSteam(steam, '666', '127.0.0.1', 123)
        http.clear()

        class Handler:
            def __init__(self):
                self.reply = None

            def callback(self, reply):
                self.reply = reply

        handler = Handler()
        user.startTransaction('EN', 'USD', [ (123, 1, 1, 'Desc', 'Cat')], handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))
        self.assertEquals(True, 'https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key' in http.requests)        
        reply = '''
{
    "response" : 
    { 
        "result" : "OK",
        "params" : {
            "orderid" : 55,
            "transid" : 374839
        }
    }
}
'''
        http.push('https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key', reply) 
        self.assertEquals(0, handler.reply['ec'])
        self.assertEquals(1, handler.reply['ok'])
        self.assertEquals(True, handler.reply['orderCode'] != None)

        items = user.retrieveTransaction(55, handler.reply['orderCode'])
        self.assertEquals(1, len(items))
        self.assertEquals((123, 1, 1, 'Desc', 'Cat'), items[0])

        self.assertEquals(0, len(http.requests))
        items = user.confirmTransaction(55, 'XXX', handler.callback)

        self.assertEquals(0, len(http.requests))
        self.assertEquals(403, handler.reply['ec'])
        self.assertEquals(0, handler.reply['ok'])

    def test_LargeBase(self):
        http = DummyHttp()
        mongo = Mongo()
        mongo.set('steamOrder', 54)
        steam = isteam.IRealSteam('2345', 'key', 'https://api.steampowered.com/', True, http, mongo, 16)
        user = isteam.IRealUserSteam(steam, '666', '127.0.0.1', 123)
        http.clear()

        class Handler:
            def __init__(self):
                self.reply = None

            def callback(self, reply):
                self.reply = reply

        handler = Handler()
        user.startTransaction('EN', 'USD', [ (123, 1, 1, 'Desc', 'Cat')], handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))
        data = http.requests['https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key'][0]
        expected = {
            'orderid' : 1152921504606847031,
            'steamid' : 666,
            'amount[0]' : 1,
            'language' : 'EN',
            'currency': 'USD',
            'itemid[0]' : 123,
            'appId': 2345,
            'ipaddress' : '127.0.0.1',
            'description[0]' : 'Desc',
            'itemcount': 1,
            'qty[0]' : 1,
            'category[0]' : 'Cat',
        }
        self.checkUrl(data, expected)
        
        reply = '''
{
    "response" : 
    { 
        "result" : "OK",
        "params" : {
            "orderid" : 55,
            "transid" : 374839
        }
    }
}
'''
        http.push('https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key', reply) 
        self.assertEquals(0, handler.reply['ec'])
        self.assertEquals(1, handler.reply['ok'])
        self.assertEquals(True, handler.reply['orderCode'] != None)

    def checkUrl(self, url, expected):
        data = urlparse.parse_qs(url)
        self.assertEquals(len(expected), len(data))
        for name, value in expected.items():
            actual = data.get(name, [])
            self.assertEquals([str(value)], actual)

    def test_LargeOffset(self):
        http = DummyHttp()
        mongo = Mongo()
        mongo.set('steamOrder', 54)
        steam = isteam.IRealSteam('2345', 'key', 'https://api.steampowered.com/', True, http, mongo, 16, 10)
        user = isteam.IRealUserSteam(steam, '666', '127.0.0.1', 123)
        http.clear()

        class Handler:
            def __init__(self):
                self.reply = None

            def callback(self, reply):
                self.reply = reply

        handler = Handler()
        user.startTransaction('EN', 'USD', [ (123, 1, 1, 'Desc', 'Cat')], handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))
        data = http.requests['https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key'][0]
        expected = {
            'orderid' : 1152921504606847041,
            'steamid' : 666,
            'amount[0]' : 1,
            'language' : 'EN',
            'currency': 'USD',
            'itemid[0]' : 123,
            'appId': 2345,
            'ipaddress' : '127.0.0.1',
            'description[0]' : 'Desc',
            'itemcount': 1,
            'qty[0]' : 1,
            'category[0]' : 'Cat',
        }
        self.checkUrl(data, expected)
        
        reply = '''
{
    "response" : 
    { 
        "result" : "OK",
        "params" : {
            "orderid" : 55,
            "transid" : 374839
        }
    }
}
'''
        http.push('https://api.steampowered.com/ISteamMicroTxnSandbox/InitTxn/V0002/?format=json&key=key', reply) 
        self.assertEquals(0, handler.reply['ec'])
        self.assertEquals(1, handler.reply['ok'])
        self.assertEquals(True, handler.reply['orderCode'] != None)

    def _onLogin(self, user, ownership):
        self.user = user
        self.ownership = ownership

    def test_NoUserInfo(self):
        http = DummyHttp()
        mongo = Mongo()
        mongo.set('steamOrder', 54)
        steam = isteam.IRealSteam('2345', 'key', 'https://api.steampowered.com/', True, http, mongo)
        callback = Callback()
        user = isteam.IRealUserSteam(steam, '666', '127.0.0.1', 123, callback)

        self.assertEquals(2, len(http.requests))
        user_reply = '''
{
        "response": {
                "result": "Failure",
                "error": {
                        "errorcode": 3,
                        "errordesc": "Both the SteamID and the ipaddress parameters were missing or invalid. At least one must be present and valid."
                }
        }
}
'''
        http.push('https://api.steampowered.com/ISteamMicroTxnSandbox/GetUserInfo/V0001/?format=json&key=key&steamid=666&ipaddress=127.0.0.1', user_reply) 
        self.assertEquals(None, user.getUser())

        ownership_reply = '''
{
        "appownership": {
                "apps": [
                        {
                                "appid": 235340,
                                "ownsapp": true,
                                "permanent": true
                        },
                        {
                                "appid": 235360,
                                "ownsapp": true,
                                "permanent": false
                        },
                        {
                                "appid": 235380,
                                "ownsapp": true,
                                "permanent": false
                        },
                        {
                                "appid": 235400,
                                "ownsapp": true,
                                "permanent": false
                        },
                        {
                                "appid": 240240,
                                "ownsapp": true,
                                "permanent": true
                        }
                ]

        }
}
'''
        http.push('https://api.steampowered.com/ISteamUser/GetPublisherAppOwnership/V0002/?format=json&key=key&steamid=666&appid=2345', ownership_reply) 
        info, ownership = callback.args
        self.assertEquals(None, info)
        self.assertEquals(ownership, user.getOwnership())
        self.assertEquals(2, len(ownership))
        self.assertEquals(240240, ownership[1])
        self.assertEquals(235340, ownership[0])


    def test_GoodUserInfo(self):
        http = DummyHttp()
        mongo = Mongo()
        mongo.set('steamOrder', 54)
        steam = isteam.IRealSteam('2345', 'key', 'https://api.steampowered.com/', True, http, mongo)
        callback = Callback()
        user = isteam.IRealUserSteam(steam, '666', '127.0.0.1', 123, callback)

        self.assertEquals(2, len(http.requests))
        user_reply = '''
{
        "response": {
                "result": "OK",
                "params": {
                        "state": "",
                        "country": "RU",
                        "currency": "RUB",
                        "status": "Trusted"
                }
        }
}
'''
        http.push('https://api.steampowered.com/ISteamMicroTxnSandbox/GetUserInfo/V0001/?format=json&key=key&steamid=666&ipaddress=127.0.0.1', user_reply) 
        self.assertEquals('RU', user.getUser()['country'])
        self.assertEquals('RUB', user.getUser()['currency'])
        http.push('https://api.steampowered.com/ISteamUser/GetPublisherAppOwnership/V0002/?format=json&key=key&steamid=666&appid=2345', '{}')

        info, ownership = callback.args
        self.assertEquals([], user.getOwnership())
        self.assertEquals([], ownership)


if __name__ == '__main__':
    import logging
    logging.getLogger().setLevel(logging.ERROR)
    unittest.main()
