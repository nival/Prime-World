import tornado.httpclient
import json
from logging import debug, info, error
import asyncore, socket
import urllib2
import urllib
import time
import ssl
import os
import errno
import select
import threading
import collections

DEFAULT_MAX_CLIENTS = 50

class AsyncHttpClient:

    class Response:

        def __init__(self, requestId, callback, accept_json):
            self.callback = callback
            self.requestId = requestId
            self.accept_json = accept_json
        
        def __call__(self, response):
            data = None
            message = None
            if response.error:
                debug('r'+str(self.requestId)+': '+str(response.error))
                message = response.error
            else:
                debug('r'+str(self.requestId)+': '+response.body)
                if self.accept_json:
                    try:
                        data = json.loads(response.body)
                    except ValueError:
                        message = 'json error'
                else:
                    data = response.body

            if self.callback:
                self.callback(data, message)

    def __init__(self, validate_cert=True, max_clients=DEFAULT_MAX_CLIENTS):
        self.http_client = tornado.httpclient.AsyncHTTPClient(max_clients=max_clients)
        self.requestId = 0
        self.validate_cert = validate_cert

    def fetch(self, url, callback, data=None, accept_json=True):
        requestId = self.requestId
        self.requestId += 1
        debug('c'+str(requestId)+': ' +url)
        if data == None:
            request = tornado.httpclient.HTTPRequest(url, 'GET', validate_cert=self.validate_cert)
        else:
            request = tornado.httpclient.HTTPRequest(url, 'POST', body=data, validate_cert=self.validate_cert)
        self.http_client.fetch(request, AsyncHttpClient.Response(requestId, callback, accept_json))
