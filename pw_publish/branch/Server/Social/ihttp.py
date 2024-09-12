# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json # , re, hashlib, urllib, httplib, logging
import functools
import gzip

from base.helpers import *

from tornado.httpclient import HTTPClient
from tornado.httpclient import HTTPRequest

##---------------------------------------------------------------------------------------------

class IHttp:
    """ Болванка для HTTP-интерфейса; поддерживаем единственный пустой метод fetch(). """
    def fetch(self, request, callback):
        if callback:
            callback( None )
        
##---------------------------------------------------------------------------------------------
    
class IHttpDummyPeerNotify( IHttp ):
    """ Этот вариант на все fetch соглашается, что 'да, на моем peer-server есть такой юзер, его uid==1'. """
    def fetch(self, request, callback):
        reply = { "ok":1, "uid":1, "server":"dummy" }
        json_response = '{"response":%s}' % json_dumps( reply )
        http_response = ClassDict( error=0, body=json_response, code=200 )
        if callback:
            callback( http_response )
        
        
##---------------------------------------------------------------------------------------------
class ISyncHttp():
    """ синхронный торнадовский HTTP-клиент (на базе curl) """
    def __init__(self):
        self.client = HTTPClient()
    
    def fetch(self, request, callback=None):
        print "ISyncHttp fetch request: %r, callback: %r" % (request, callback)
        try:
            http_reply = self.client.fetch( request )
        except:
            catch()
            http_reply = None
        ## print "ISyncHttp fetch reply: %r" % http_reply
        
        if callback:
            callback( http_reply )
        else:
            # возврат можно получить и через callback (синхронно), и просто через response = HTTP.fetch()
            # в последнем случае сразу распарсим ответ до JSON:
            response = {}
            try:
                if http_reply and (not http_reply.error):
                    print "http_reply.body: ", http_reply.body
                    unquote_body = urllib.unquote( http_reply.body )
                    json_reply = json_load_transform( unquote_body )
                    if json_reply:
                        response = json_reply.get("response", {})
                else:
                    warn( "BAD http reply: %s" % http_reply )
            except:
                print "catch: ", catch()
                warn( "EXCEPTION on http reply: %s" % http_reply )
                
            return response


##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------
class IAsyncHttpFetcher:
    """ более удобный HTTP-интерфейс: поддерживает асинхронные запросы, парсит JSON-ответ, умеет справляться с проблемами gzip """
    def __init__(self, HTTP=None):
        self.HTTP = HTTP
            
    #---------------------------------------------------------------------------------------------
    # для удобства сразу распарсим HTTP-ответ до response:{}
    def fetch(self, peer_addr, args_dict, callback, subrequest="x", unwrap=True, timeout=20.0 ):
        #~ request = "%s/%s?" % ( http_prefix(peer_addr), subrequest)
        #~ for arg,value in args_dict.iteritems():
            #~ request += "&%s=%s" % (arg, value)
        if subrequest is None:
            errStack("Error: subrequest is None! '' used instead, but it could make WRONG request.") # to catch PF-85993 case
            subrequest = ''
        url = http_prefix(peer_addr) + '/' + subrequest + '?' + urllib.urlencode(args_dict)
        
        # HTTP-результат пусть падает в _onFetch, там мы его распарсим до response:{} 
        # (достало писать однотипные http_reply-обработчики)
        _callback = functools.partial( self._onFetch, callback=callback, unwrap=unwrap )
        try:
            self.HTTP.fetch( url, _callback, connect_timeout=timeout, request_timeout=timeout )
        except:
            catch()
            _callback( None )
    
    #---------------------------------------------------------------------------------------------
    # для удобства сразу распарсим HTTP-ответ до response:{}
    def post( self, peer_addr, args_dict, post_body, callback, subrequest="x", headers={}, unwrap=True, timeout=20.0 ):
        url = http_prefix(peer_addr) + '/' + subrequest + '?' + urllib.urlencode(args_dict)
        
        request = HTTPRequest( url=url, method="POST", headers=headers, body=post_body, connect_timeout=timeout, request_timeout=timeout )
        ##info("post request: url=%s, method=%s, headers=%s, body=%s" % (request.url, request.method, request.headers, request.body))
        
        # HTTP-результат пусть падает в _onFetch, там мы его распарсим до response:{} 
        # (достало писать однотипные http_reply-обработчики)
        _callback = functools.partial( self._onFetch, callback=callback, unwrap=unwrap )
        try:
            self.HTTP.fetch( request, _callback )
        except:
            catch()
            _callback( None )
            
    #---------------------------------------------------------------------------------------------
    def _onFetch(self, http_reply, callback=None, unwrap=True):
        response = {}
        try:
            if http_reply and (not http_reply.error):
                str_body = http_reply.body
                if str_body and str_body[0] != '{': # нормальный json должен начинаться с curly brace
                    encoding = http_reply.headers.get("Content-Encoding", "")
                    if encoding == "gzip":
                        warn("unzipping from http body (libcurl failed to deflate gzip?): %r" % str_body)
                        gzip_file = gzip.GzipFile(mode="rb", fileobj=http_reply.buffer) # в ответе уже есть StringIO буфер, не будем создавать новый
                        str_body = gzip_file.read()
                        info("unzipped http body: %r" % str_body)
                    
                unquote_body = urllib.unquote( str_body )
                if unwrap:
                    json_reply = json_load_transform( unquote_body )
                    if json_reply:
                        response = json_reply.get("response", {})
                else:
                    response = unquote_body
            else:
                warn( "BAD http reply: %s" % http_reply )
        except:
            catch()
            warn( "EXCEPTION on http reply: %r \n(http body: %r)" % (http_reply, http_reply.body) )
            
        if callback:
            callback( response )

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class ILimitedAsyncHttpFetcher( IAsyncHttpFetcher ):
    """ отслеживаем, сколько обращений идет к каждому конечному HTTP-адресу; по превышению лимита - сразу обламываем запросы к данному addr """
    def __init__(self, HTTP=None, request_limit=1000):
        self.request_limit = request_limit
        self.pending_counts = IncDict()
        IAsyncHttpFetcher.__init__( self, HTTP )
            
    #---------------------------------------------------------------------------------------------
    # для удобства сразу распарсим HTTP-ответ до response:{}
    def fetch(self, peer_addr, args_dict, callback, subrequest="x", unwrap=True, timeout=20.0):
        addr = http_prefix(peer_addr)
        if self.pending_counts.pick(addr) < self.request_limit:
            self.pending_counts.inc(addr)
            ## info("HttpLimit: get, pending[%s]=%s" % (addr, self.pending_counts.pick(addr)))
            
            # HTTP-результат пусть падает в _onFetch
            _callback = functools.partial( self._onLimitedFetch, callback=callback, addr=addr )
            try:
                IAsyncHttpFetcher.fetch( self, peer_addr, args_dict, _callback, subrequest, unwrap=unwrap, timeout=timeout )
            except:
                catch("ILimitedAsyncHttpFetcher.fectch fails with peer_addr=%s, subrequest=%s, args_dict=%s", peer_addr, subrequest, args_dict)
                _callback( None )
        else:
            self.fail(addr, args_dict, callback)
                
    #---------------------------------------------------------------------------------------------
    # для удобства сразу распарсим HTTP-ответ до response:{}
    def post( self, peer_addr, args_dict, post_body, callback, subrequest="x", headers={}, unwrap=True, timeout=20.0 ):
        addr = http_prefix(peer_addr)
        if self.pending_counts.pick(addr) < self.request_limit:
            self.pending_counts.inc(addr)
            ## info("HttpLimit: post, pending[%s]=%s" % (addr, self.pending_counts.pick(addr)))
            
            # HTTP-результат пусть падает в _onFetch
            _callback = functools.partial( self._onLimitedFetch, callback=callback, addr=addr )
            try:
                IAsyncHttpFetcher.post( self, peer_addr, args_dict, post_body, _callback, subrequest=subrequest, headers=headers, unwrap=unwrap, timeout=timeout )
            except:
                catch("ILimitedAsyncHttpFetcher.post fails with peer_addr=%s, args_dict=%s", peer_addr, args_dict)
                _callback( None )
            
    #---------------------------------------------------------------------------------------------
    def _onLimitedFetch(self, http_reply, callback=None, addr=""):
        self.pending_counts.add(addr, -1)
        ## info("HttpLimit: fetched, pending[%s]=%s" % (addr, self.pending_counts.pick(addr)))
        if callback:
            callback( http_reply )

    #---------------------------------------------------------------------------------------------
    def fail(self, addr, args_dict, callback):
        warn("HttpLimit REACHED (%s max) for addr=%r, failing (args=%s)" % (self.request_limit, addr, args_dict))
        if callback:
            callback({})
            
