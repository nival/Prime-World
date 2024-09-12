#!/usr/bin/env python
# -"- coding: utf8 -"- 
# (C) Dmitry Kolb 2014, Nival Network 

import sys, os, time, logging, json
import unittest
import urlparse
import urllib2, urllib
import hmac
import binascii
import hashlib
from  functools import partial

os.chdir('..')
sys.path.append( os.path.abspath('.'))
sys.path.append( os.path.abspath('cfg'))
import cfg, coord_cfg
import iarcgames
from functools import partial
from base.helpers import *

from tornado import httpclient
from tornado.httputil import HTTPHeaders



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
            self.items[name] = {'r': {'amount': 1}}
        else:
            self.items[name]['r']['amount'] += 1
        callback(self.items[name])

    def find_one(self, shard_key, collection, query, callback=None, params=None):
        name = query['name']

        if name not in self.items:
            callback()
        else:
            callback(self.items[name])

    def set(self, name, value, callback=None):
        self.items[name] = {'r': {'amount': value}}
        if callback:
            callback(value)

class Callback:
    def __call__(self, *args, **kvargs):
        self.args = args
        self.kvargs = kvargs

class Handler:
    def __init__(self):
        self.reply = None

    def callback(self, reply):
        self.reply = reply
        print reply


class DummySA:

    def __init__(self):
        self.arcgames_app_abbr = coord_cfg.COORDINATOR_ARCGAMES_APPABBR
        self.arcgames_app_secret = coord_cfg.COORDINATOR_ARCGAMES_APP_SECRET
        self.arcgames_test_url = coord_cfg.COORDINATOR_ARCGAMES_URL
        self.user = 'shtest100'
        self.pwd = 'test123'

    def execute_request(self, data):
        sdata = json_dumps(data)
        random = 'abcdef'
        format = 'json'
        time1 = str(int(time.time()))
        hashstring = random + time1 + str(1) + self.arcgames_app_abbr + sdata
        sig = urllib.quote(hmac.new(self.arcgames_app_secret, hashstring, hashlib.sha1).hexdigest())
        params = {'r': random,
                  'f': format,
                  't': time1,
                  'v': str(1),
                  'g': self.arcgames_app_abbr,
                  'sig': sig}
        params_encodes = [k + '=' + urllib.quote_plus(v) for k, v in params.iteritems()]

        request = self.arcgames_test_url+'?' + '&'.join(params_encodes)

        #print 'Request', request
        #print request
        #print 'method : ', sdata
        s = urllib2.urlopen(request, sdata).read()
        #print 'response : ', s
        return json_loads(s)

    def hashClientPassword(self, token, salt):
        hash_stage1 = hashlib.md5(salt + self.pwd).digest()
        hash_stage2 = hashlib.md5(binascii.unhexlify(token) + hashlib.md5(hash_stage1).digest()).digest()
        #xor = lambda text, key: ''.join(chr(ord(x) ^ ord(k)) for x, k in zip(text, key))
        return binascii.hexlify(''.join(chr(ord(x) ^ ord(k)) for x, k in zip(hash_stage1, hash_stage2)))


    def get_access_token(self):
        dtoken ={ 'method': 'user.gettoken',
                'params': {'account': self.user,
                'password': self.pwd}
        }
        token = self.execute_request(dtoken)
        dlogin = {'method': 'user.tokenlogin',
                  'params':
                      {
                       'account': self.user,
                       'token': token['data']['token']
                      }
        }


        token = self.execute_request(dlogin)
        """
        #dlogin = {'method': 'user.login',
                  'params':
                      {
                       'account': self.user,
                       'password': self.hashClientPassword(token['data']['token'], token['data']['salt']),
                       'ip': socket.gethostbyname(socket.gethostname()),
                      }
        }

        id = self.execute_request(dlogin)
        rlog = { 'method': 'log.purchaseitem',
                  'params':
                      {
                    'userId': id['data']['id'],
                    'itemName': 'MonsterCard',
                    'itemQuantity' : '1',
                    'totalPrice' : '0.99',
                    'currency' : 'usd',
                    'transactionId' : 'WYSD1223KKS',
                    'transactionDate': '1372829445',
                    }
        }
        r = self.execute_request(rlog)
        """

    def getInfo(self, auid, snid, include_secure_data, callback=None):
        #self.get_access_token()
        result = {

            "tm": 52,
            "error": 0,
            "get_info": {
                "dt_register": 1404683162,
                "dt_login": 1404985001,
                "dt_logout": 1404985021,
                "props": {
                    "fame": "0",
                    "fraction": "1",
                    "fsn": "arc",
                    "guildshortname": "-",
                    "locale": "RU",
                    "nick": "test",
                    "referral": "RU/RU0",
                    "reg": "1",
                    "snbonus": "1"
                },
                "arc": {
                    "name": "test100",
                    "sntoken": "c5fe7c48b941cde107900431e4840d21",
                    "passportid": 43670530,
                    "snuid": "shtest100"
                }
            }
        }

        # action=l_who&sntoken=&snuid=109886800&snid=arc&primary=1
        if callback:
            callback(result)

class TestArcGames(unittest.TestCase):

    def test_getBalance(self):
        http = DummyHttp()
        SA = DummySA()
        arc = iarcgames.IRealArcGames(coord_cfg.COORDINATOR_ARCGAMES_APPID,
                                      coord_cfg.COORDINATOR_ARCGAMES_APPABBR,
                                      coord_cfg.COORDINATOR_ARCGAMES_APP_SECRET,
                                      coord_cfg.COORDINATOR_ARCGAMES_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_BILLING_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_ZONEID,
                                      coord_cfg.COORDINATOR_ARCGAMES_IS_TEST, http, SA)
        user = iarcgames.IRealUserArcGames(arc, 123, 'arc')
        arc.original_snid = 'arc'
        http.clear()

        handler = Handler()
        user.getBalance(handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))

        reply = ClassDict({'body': json_dumps({"status": "success", "data":{"userid": 109886800, "server": coord_cfg.COORDINATOR_ARCGAMES_APPID, "balance": 99999}})})
        http.requests.values()[0][1](reply)
        self.assertEquals({'balance': 99999, 'ok': 1, 'ec': 0}, handler.reply)

        '''
        surl = http.requests.keys()[0]

        c = httpclient.HTTPClient()

        print 'URL: ',surl
        print 'POST DATA: ', str(http.requests[surl][0])
        req = httpclient.HTTPRequest(surl,
                                    method="POST",
                                    body=str(http.requests[surl][0]),
                                    headers=HTTPHeaders({'User-Agent': 'PWServer'}),
                                    #validate_cert=False,
                                    #request_timeout=90,
                                    #connect_timeout=90,
                                    )


        resp = c.fetch(req)
        r =  json_loads(resp.body)
        print 'RESPONSE: ', r

        self.assertEquals(True, 'status' in r)
        '''

    def test_getBalanceFail(self):
        http = DummyHttp()
        SA = DummySA()
        arc = iarcgames.IRealArcGames(coord_cfg.COORDINATOR_ARCGAMES_APPID,
                                      coord_cfg.COORDINATOR_ARCGAMES_APPABBR,
                                      coord_cfg.COORDINATOR_ARCGAMES_APP_SECRET,
                                      coord_cfg.COORDINATOR_ARCGAMES_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_BILLING_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_ZONEID,
                                      coord_cfg.COORDINATOR_ARCGAMES_IS_TEST, http, SA)
        user = iarcgames.IRealUserArcGames(arc, 123, 'arc')
        arc.original_snid = 'arc'
        http.clear()

        handler = Handler()
        user.getBalance(handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))

        reply = ClassDict({'body': json_dumps({"status":"failure","error":{"code":402,"message":"Internal Database Error"}})})

        http.requests.values()[0][1](reply)

        self.assertEquals({'em': "ArcGames error: {u'message': u'Internal Database Error', u'code': 402}", 'ok': 0, 'ec': 416}, handler.reply)



    def test_purchaseItem(self):
        http = DummyHttp()
        SA = DummySA()
        arc = iarcgames.IRealArcGames(coord_cfg.COORDINATOR_ARCGAMES_APPID,
                                      coord_cfg.COORDINATOR_ARCGAMES_APPABBR,
                                      coord_cfg.COORDINATOR_ARCGAMES_APP_SECRET,
                                      coord_cfg.COORDINATOR_ARCGAMES_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_BILLING_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_ZONEID,
                                      coord_cfg.COORDINATOR_ARCGAMES_IS_TEST, http, SA)

        user = iarcgames.IRealUserArcGames(arc, 123, 'arc')
        arc.original_snid = 'arc'
        http.clear()

        handler = Handler()
        params = [ #"zoneid": 0,
                   #"uniqueid":
                   "abc-def_hij1234",
                   #"amount":
                    1,
                   #"itemid":
                    35,
                   #"count":
                   1,
                   #"callback":
                   handler.callback
        ]

        user.startTransaction(*params)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))

        response  = {"status": "success", "data":{"userid": 109886800, "server": coord_cfg.COORDINATOR_ARCGAMES_APPID, "balance": 99999}}
        reply = ClassDict({'body': json_dumps(response)})

        http.requests.values()[0][1](reply)

        self.assertEquals({'balance': 99999, 'ok': 1}, handler.reply)

        '''
        surl = http.requests.keys()[0]
        c = httpclient.HTTPClient()
        print 'URL: ', surl
        print 'POST DATA: ', str(http.requests[surl][0])

        req = httpclient.HTTPRequest(surl,
                                    method="POST",
                                    body=http.requests[surl][0],
                                    headers=HTTPHeaders({'User-Agent': 'PWServer'}),
                                    validate_cert= False,
                                    #request_timeout=90,
                                    #connect_timeout=90,
                                    )


        resp = c.fetch(req)
        r =  json_loads(resp.body)
        print "RESPONSE: ", r
        self.assertEquals(True, 'status' in r)
        '''

    def test_purchaseItemFail(self):
        http = DummyHttp()
        SA = DummySA()
        arc = iarcgames.IRealArcGames(coord_cfg.COORDINATOR_ARCGAMES_APPID,
                                      coord_cfg.COORDINATOR_ARCGAMES_APPABBR,
                                      coord_cfg.COORDINATOR_ARCGAMES_APP_SECRET,
                                      coord_cfg.COORDINATOR_ARCGAMES_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_BILLING_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_ZONEID,
                                      coord_cfg.COORDINATOR_ARCGAMES_IS_TEST, http, SA)

        user = iarcgames.IRealUserArcGames(arc, 123, 'arc')
        arc.original_snid = 'arc'
        http.clear()

        handler = Handler()
        params = [ #"zoneid": 0,
                   #"uniqueid":
                   "abc-def_hij1234",
                   #"amount":
                    1,
                   #"itemid":
                    35,
                   #"count":
                   1,
                   #"callback":
                   handler.callback
        ]


        user.startTransaction(*params)
        self.assertEquals(None, handler.reply)

        response = {"status":"failure", "error":{"code":402,"message":"Internal Database Error"}}
        reply = ClassDict({'body': json_dumps(response)})

        surl, val = http.requests.popitem()
        val[1](reply)

        self.assertEquals({'em': "ArcGames error: {u'message': u'Internal Database Error', u'code': 402}", 'ok': 0, 'ec': 416}, handler.reply)

    def test_purchaseItemNotEnoughZZen (self):
        http = DummyHttp()
        SA = DummySA()
        arc = iarcgames.IRealArcGames(coord_cfg.COORDINATOR_ARCGAMES_APPID,
                                      coord_cfg.COORDINATOR_ARCGAMES_APPABBR,
                                      coord_cfg.COORDINATOR_ARCGAMES_APP_SECRET,
                                      coord_cfg.COORDINATOR_ARCGAMES_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_BILLING_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_ZONEID,
                                      coord_cfg.COORDINATOR_ARCGAMES_IS_TEST, http, SA)

        user = iarcgames.IRealUserArcGames(arc, 123, 'arc')
        arc.original_snid = 'arc'
        http.clear()

        handler = Handler()
        params = [ #"zoneid": 0,
                   #"uniqueid":
                   "abc-def_hij1234",
                   #"amount":
                    1,
                   #"itemid":
                    35,
                   #"count":
                   1,
                   #"callback":
                   handler.callback
        ]


        user.startTransaction(*params)
        self.assertEquals(None, handler.reply)

        response = {"status":"failure", "error": {"code":1502,"message":"not enough currency"}}
        reply = ClassDict({'body': json_dumps(response)})

        surl, val = http.requests.popitem()
        val[1](reply)

        self.assertEquals(1, len(http.requests.values()))

        reply = ClassDict({'body': json_dumps({"status": "success", "data":{"userid": 109886800, "server": coord_cfg.COORDINATOR_ARCGAMES_APPID, "balance":99999}})})
        surl, val = http.requests.popitem()
        val[1](reply)

        self.assertEquals({'balance': {'balance': 99999, 'ok': 1, 'ec': 0 }, 'ok': 0, 'ec': 420}, handler.reply)


    def test_logPurchaseItem(self):
        http = DummyHttp()
        SA = DummySA()
        arc = iarcgames.IRealArcGames(coord_cfg.COORDINATOR_ARCGAMES_APPID,
                                      coord_cfg.COORDINATOR_ARCGAMES_APPABBR,
                                      coord_cfg.COORDINATOR_ARCGAMES_APP_SECRET,
                                      coord_cfg.COORDINATOR_ARCGAMES_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_BILLING_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_ZONEID,
                                      coord_cfg.COORDINATOR_ARCGAMES_IS_TEST, http, SA)

        user = iarcgames.IRealUserArcGames(arc, 123, 'arc')
        arc.original_snid = 'arc'
        http.clear()
        #from geo_cfg import DEFAULT_GEO_LOCATION


        handler = Handler()
        params = [#"itemName":
                      "MonsterCard",
                  #"itemQuantity":
                      "1",
                  #"totalPrice":
                      "0.99",
                  #"currency":
                      "usd",
                  #"transactionId":
                      "WYSD1223KKS",
                  #"transactionDate":
                      "1372829445",
                  #"callback":
                      handler.callback
        ]

        user.logPurchaseitem(*params)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))
        response = {"status":"success", "data": {"result": "success"}}
        reply = ClassDict({'body': json_dumps(response)})

        surl, val = http.requests.popitem()
        val[1](reply)

        self.assertEquals({'status': u'success', 'ok': 1},handler.reply)

        '''
        surl = http.requests.keys()[0]
        c = httpclient.HTTPClient()

        req = httpclient.HTTPRequest(surl,
                                    method="POST",
                                    body=http.requests[surl][0],
                                    headers=HTTPHeaders({'User-Agent': 'PWServer'}),
                                    validate_cert= False
                                    )


        resp = c.fetch(req)
        r = json_loads(resp.body)
        print r
        self.assertEquals(True, 'status' in r)
        '''

    def test_logPurchaseItemFail(self):
        http = DummyHttp()
        SA = DummySA()
        arc = iarcgames.IRealArcGames(coord_cfg.COORDINATOR_ARCGAMES_APPID,
                                      coord_cfg.COORDINATOR_ARCGAMES_APPABBR,
                                      coord_cfg.COORDINATOR_ARCGAMES_APP_SECRET,
                                      coord_cfg.COORDINATOR_ARCGAMES_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_BILLING_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_ZONEID,
                                      coord_cfg.COORDINATOR_ARCGAMES_IS_TEST, http, SA)

        user = iarcgames.IRealUserArcGames(arc, 123, 'arc')
        arc.original_snid = 'arc'
        http.clear()
        #from geo_cfg import DEFAULT_GEO_LOCATION

        handler = Handler()
        params = [#"itemName":
                      "MonsterCard",
                  #"itemQuantity":
                      "1",
                  #"totalPrice":
                      "0.99",
                  #"currency":
                      "usd",
                  #"transactionId":
                      "WYSD1223KKS",
                  #"transactionDate":
                      "1372829445",
                  #"callback":
                      handler.callback
        ]

        user.logPurchaseitem(*params)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))
        response = {"status":"failure","error":{"code":14,"message":"invalid param","detail":"param currency should not be empty"}}
        reply = ClassDict({'body': json_dumps(response)})

        surl, val = http.requests.popitem()
        val[1](reply)

        self.assertEquals({'em': "ArcGames error: {u'message': u'invalid param', u'code': 14, u'detail': u'param currency should not be empty'}", 'ok': 0, 'ec': 416}, handler.reply)

if __name__ == '__main__':
    import logging
    logging.getLogger().setLevel(logging.ERROR)
    #suite = unittest.TestSuite()
    #suite.addTest(TestArcGames('test_getBalance'))
    #suite.addTest(TestArcGames('test_getBalanceFail'))
    #suite.addTest(TestArcGames('test_purchaseItem'))
    #suite.addTest(TestArcGames('test_purchaseItemFail'))
    #suite.addTest(TestArcGames('test_purchaseItemEnoughZZen'))
    #suite.addTest(TestArcGames('test_logPurchaseItem'))
    #runner = unittest.TextTestRunner()
    #runner.run(suite)

    unittest.main()
