#!/usr/bin/env python
# -"- coding: utf8 -"-
# (C) Dmitry Kolb 2014, Nival Network
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
import izzimacom

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
            headers = request.headers
            url = request.url
        self.requests[url] = (body, callback, headers)

    def push(self, url, result, error=None):
        data, callback = self.requests[url]
        class Response:
            def __init__(self, body, error):
                self.body = body
                self.error = error
        del self.requests[url]
        callback(Response(result, error))

    def clear(self):
        logging.info("DummyHttp  clear: [%r]" % self.requests)
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
        logging.info("Handler reply: [%r] " % reply)
        print reply


class DummySA:

    def __init__(self):
        self.billing_url = coord_cfg.COORDINATOR_ARCGAMES_URL
        self.user = 'shtest100'
        self.pwd = 'test123'

    def getInfo(self, auid, snid, include_secure_data, callback=None):

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
                    "fsn": "zzma",
                    "guildshortname": "-",
                    "locale": "RU",
                    "nick": "test",
                    "referral": "RU/RU0",
                    "reg": "1",
                    "snbonus": "1"
                },
                "zzma": {
                    "userName": "destroyer2014",
                    "sntoken": "c5fe7c48b941cde107900431e4840d21",
                    "snuid":  545302

                }
            }
        }

        # action=l_who&sntoken=&snuid=109886800&snid=arc&primary=1
        if callback:
            logging.info("DummySA getInfo")
            callback(result)

class TestZZimacom(unittest.TestCase):

    def test_getBalance(self):
        http = DummyHttp()
        SA = DummySA()
        zz = izzimacom.IRealIZZimacom(coord_cfg.COORDINATOR_ZZIMACOM_SERVICE_NAME,
                                      coord_cfg.COORDINATOR_ZZIMACOM_PAYMENT_SYSTEM,
                                      coord_cfg.COORDINATOR_ZZIMACOM_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_IS_TEST, http, SA)
        user = izzimacom.IRealUserZZimacom(zz, 2, 'zzma')
        zz.original_snid = 'zzma'
        http.clear()

        handler = Handler()
        user.getBalance(handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))
        '''
        POST DATA:
        reply = ClassDict({'body': """<?xml version="1.0" encoding="utf-8"?>
<soap:Envelope xmlns:soap="http://schemas.xmlsoap.org/soap/envelope/" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xmlns:xsd="http://www.w3.org/2001/XMLSchema">
    <soap:Body>
        <GetUserBalanceResponse xmlns="http://zzima.com/">
            <GetUserBalanceResult>
                <code>0</code>
                <amount>250.00</amount>
            </GetUserBalanceResult>
        </GetUserBalanceResponse>
    </soap:Body>
</soap:Envelope>
""", 'error': 0 })

        reply = ClassDict({'body': http.requests.values()[0][0]})
        '''
        surl = http.requests.keys()[0]
        c = httpclient.HTTPClient()
        print 'URL: ', surl
        print 'POST DATA: ', str(http.requests[surl][0])

        req = httpclient.HTTPRequest(surl,
                                    method="POST",
                                    body=http.requests[surl][0],
                                    validate_cert= False,
                                    headers=http.requests[surl][2],
                                    #request_timeout=90,
                                    #connect_timeout=90,
                                    )


        resp = c.fetch(req)
        print "RESPONSE: ", resp.body


        http.requests.values()[0][1](resp)
        # баланс может быть другой
        self.assertEquals({'balance': 50080.0, 'ok': 1, 'ec': 0}, handler.reply)


    def test_purchaseItem(self):
        http = DummyHttp()
        SA = DummySA()
        zz = izzimacom.IRealIZZimacom(coord_cfg.COORDINATOR_ZZIMACOM_SERVICE_NAME,
                                      coord_cfg.COORDINATOR_ZZIMACOM_PAYMENT_SYSTEM,
                                      coord_cfg.COORDINATOR_ZZIMACOM_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_IS_TEST, http, SA)
        user = izzimacom.IRealUserZZimacom(zz, 2, 'zzma')
        zz.original_snid = 'zzma'
        http.clear()

        handler = Handler()

        #startTransaction(self, transactionId, itemId, itemPrice, count, callback=None):
        # self.izz.startTransaction(self.auid, self.snid, transactionId, itemId, itemPrice, count, callback)
        user.startTransaction(transactionId="123", itemId=1, itemPrice=1, count=1, callback=handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))

        # ----------------------------------------------------------------------
        surl = http.requests.keys()[0]
        c = httpclient.HTTPClient()
        print 'URL: ', surl
        print 'POST DATA: ', str(http.requests[surl][0])

        req = httpclient.HTTPRequest(surl,
                                    method="POST",
                                    body=http.requests[surl][0],
                                    validate_cert= False,
                                    headers=http.requests[surl][2],
                                    #request_timeout=90,
                                    #connect_timeout=90,
                                    )

        resp = c.fetch(req)
        print "RESPONSE: ", resp.body

        http.requests.values()[0][1](resp)
        print "handler.reply: ", handler
        self.assertEquals({'ok': 1 }, handler.reply)

        # ----------------------------------------------------------------------
        # ReserveAmount
        surl = http.requests.keys()[0]

        print 'URL: ', surl
        print 'POST DATA: ', str(http.requests[surl][0])

        req = httpclient.HTTPRequest(surl,
                                    method="POST",
                                    body=http.requests[surl][0],
                                    validate_cert= False,
                                    headers=http.requests[surl][2],
                                    #request_timeout=90,
                                    #connect_timeout=90,
                                    )

        resp = c.fetch(req)
        print "RESPONSE: ", resp.body
        """

        http.requests.values()[0][1](resp)
        print "handler.reply: ", handler
        """
        self.assertEquals({'ok': 1 }, handler.reply)

    def test_purchaseItemNotEnoughMany(self):
        http = DummyHttp()
        SA = DummySA()
        zz = izzimacom.IRealIZZimacom(coord_cfg.COORDINATOR_ZZIMACOM_SERVICE_NAME,
                                      coord_cfg.COORDINATOR_ZZIMACOM_PAYMENT_SYSTEM,
                                      coord_cfg.COORDINATOR_ZZIMACOM_URL,
                                      coord_cfg.COORDINATOR_ARCGAMES_IS_TEST, http, SA)
        user = izzimacom.IRealUserZZimacom(zz, 2, 'zzma')
        zz.original_snid = 'zzma'
        http.clear()

        handler = Handler()
        user.startTransaction("123", 1, 10000000000, 1, handler.callback)
        self.assertEquals(None, handler.reply)

        self.assertEquals(1, len(http.requests))

        surl = http.requests.keys()[0]
        c = httpclient.HTTPClient()
        print 'URL: ', surl
        print 'POST DATA: ', str(http.requests[surl][0])

        req = httpclient.HTTPRequest(surl,
                                    method="POST",
                                    body=http.requests[surl][0],
                                    validate_cert= False,
                                    headers=http.requests[surl][2],
                                    #request_timeout=90,
                                    #connect_timeout=90,
                                    )


        resp = c.fetch(req)
        print "RESPONSE: ", resp.body
        #reply = ClassDict({'body': http.requests.values()[0][0]})
        values = http.requests.popitem()
        values[1][1](resp)

        self.assertEquals(None, handler.reply)
        surl = http.requests.keys()[0]

        print 'URL: ', surl
        print 'POST DATA: ', str(http.requests[surl][0])

        req = httpclient.HTTPRequest(surl,
                                    method="POST",
                                    body=http.requests[surl][0],
                                    validate_cert= False,
                                    headers=http.requests[surl][2],
                                    #request_timeout=90,
                                    #connect_timeout=90,
                                    )


        resp = c.fetch(req)
        print "RESPONSE: ", resp.body


        http.requests.values()[0][1](resp)

        self.assertEquals({'balance': {'balance': 120.0, 'ok': 1, 'ec': 0}, 'ok': 0, 'ec': 425}, handler.reply)


if __name__ == '__main__':
    import logging
    logging.getLogger().setLevel(logging.INFO)
    #suite = unittest.TestSuite()
    #suite.addTest(TestZZimacom('test_getBalance'))
    #suite.addTest(TestZZimacom('test_purchaseItem'))
    #suite.addTest(TestZZimacom('test_getBalance'))
    #suite.addTest(TestZZimacom('test_purchaseItemNotEnoughMany'))
    #runner = unittest.TextTestRunner()
    #runner.run(suite)

    unittest.main()
