# -*- coding: utf-8 -*-
import sys, os, time, logging, json
import urllib2


os.chdir('..')
sys.path.append( os.path.abspath('.') )

import isteam

class Response:

    def __init__(self, body, error=None):
        self.body = body
        self.error = error

class RealHttp:

    def __init__(self):
        self.requests = {}
        self.data = []

    def fetch(self, request, callback):
        print request
        if type(request) == str:
            url = request
            data = None
        else:
            url = request.url
            data = request.body    
        
        print url, data
        if data:
            self.data.append(data)
        urlRequest = urllib2.Request( url, data )
        try:
            response = urllib2.urlopen( urlRequest, None, timeout=20.0 )
            headers = response.info()
            responseData = response.read()
            print headers, responseData
            callback(Response(responseData))
            return 
        except urllib2.URLError, e:
            print str(e)
            callback(Response(None, e))


class Redis:

    def __init__(self, host, port):
        self.redis = redis.Redis( host=host, port=port)

    def connect(self):
        self.redis.dbsize()

    def incr(self, name, callback):
        result = self.redis.incr(name)
        callback(result)

class Callback:

    def __call__(self, *args, **kwargs):
        print args, kwargs
#
#import redis

http = RealHttp()
#redis = Redis(host='127.0.0.1', port=8379)
#redis.connect()

steamId = '76561198002895105'
steam = isteam.IRealSteam('235340', 'DF2AB4D40CC294D9482628DBAF3085B6', 'https://api.steampowered.com/', True, http, None)
user = steam.attachTo(steamId, '127.0.0.1', '555', Callback())

class Handler:

    def __init__(self):
        self.start = None
        self.confirm = None

    def onStart(self, reply):
        self.start = reply
        print reply

    def onConfirm(self, reply):
        self.confirm = reply
        print reply

#handler = Handler()
#user.startTransaction('RU', 'RUB', [ (123, 1, 1, 'Описание', 'Cat')], handler.onStart)
#while handler.start is None:
#    time.sleep(0.5)

#if handler.start['ec'] == 0:
#    order = http.data[1].split('&')[0].split('=')
#    assert order[0] == 'orderid'
#    items = user.retrieveTransaction(int(order[1]), handler.start['orderCode'])
#    if items is not None:
#        user.confirmTransaction(int(order[1]), handler.start['orderCode'], handler.onConfirm)
#        while handler.confirm is None:
#            time.sleep(0.5)
#    else:
#        print 'Error'
#else:
#    print 'Error'
    
user.checkOwnershipInfo(235340, Callback())            
                    



