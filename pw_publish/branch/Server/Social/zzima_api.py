# -*- coding: utf-8 -*-

#!/usr/bin/env python

import urllib, urllib2, hashlib, json, sys, time
from base64 import b64encode

#---------------------------------------------------------------------
sys.path.append('tornado')
import tornado.httpclient
import tornado.ioloop

#---------------------------------------------------------------------
def getInfoParams( api_key, api_secret, user_id, get_extended_info=0, get_pic=0 ):
    params = {
        'api_key' : api_key,
        'game_user' : str(user_id),
        'method' : 'users.getInfo,%s,%d,%d' % (str(user_id), get_extended_info, get_pic),
        'format' : 'json'
    }
    
    md5_string = ''
    out_params = []
    for key in sorted( params.keys() ):
        val = b64encode( params[key] )
        md5_string += '%s=%s' % (key, val)
        out_params.append( (key,val) )

    # 'sig' should be last parameter, and unencoded
    md5_string += api_secret
    sig = hashlib.md5(md5_string).hexdigest()
    out_params.append( ('sig',sig) )

    body = urllib.urlencode( out_params )
    headers = { "Accept-Encoding": "text/plain" }

    return body, headers
    

#---------------------------------------------------------------------
def invokeUrllib2( url, body, headers ):
    request = urllib2.Request(url, body, headers)
    reply_body = urllib2.urlopen(request).read()
    return reply_body
    
#---------------------------------------------------------------------
def invokeTornado( client, url, body, headers, callback=None ):
    request = tornado.httpclient.HTTPRequest( url, method="POST", headers=headers, body=body )
    client.fetch( request, callback=callback  )
    
    
##---------------------------------------------------------------------
def dummy_on_http_reply(response):
    tornado.ioloop.IOLoop.instance().stop()
    
    
#== TEST ===========================
if __name__ == "__main__":
    
    ITERATIONS = 1
    for i in range(ITERATIONS):
        URL = 'http://SITE.com/zzimaApi'
        API_KEY = '123'
        API_SECRET = '123'

        #body, headers = getInfoParams( API_KEY, API_SECRET, 200384, 1, 1 ) # quetz
        body, headers = getInfoParams( API_KEY, API_SECRET, 4838, 1, 1 ) # redjack
        
        json_body = invokeUrllib2( URL,  body, headers )
        client = tornado.httpclient.AsyncHTTPClient() 
        invokeTornado( client, URL, body, headers, dummy_on_http_reply )
        tornado.ioloop.IOLoop.instance().start()

        # левый тест: просто делаем POST на соотв. handler координатора
        COORD_URL = 'http://127.0.0.1:8700/th'
        body = '\x80\x01\x00\x01\x00\x00\x00\x04ping\x00\x00\x00\x00\x00'
        invokeUrllib2( COORD_URL, body, headers )
