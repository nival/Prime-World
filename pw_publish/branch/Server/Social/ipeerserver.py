# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json, urllib

sys.path.append('base')
from helpers import *

import collections
import functools

from tornado.httpclient import HTTPRequest

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IPeerWebServer:
    """ Болванка для интерфейса внешних запросов к WS (для тестирования нужно уметь перехватывать внешние запросы к тестируемому WorkServer) """
    def __init__(self, HTTP=None):
        pass

    def fetch( self, peer_addr, args_dict, callback, subrequest="x" ):
        pass
        
    def post( self, peer_addr, args_dict, post_body, callback, subrequest="x" ):
        pass

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IFakePeerWebServer( IPeerWebServer ):
    """ Перехватываем внешние запросы к тестируемому WorkServer, направляем их в некую функцию 'HTTP-handler' """
    def __init__(self, HTTP):
        assert isinstance( HTTP, collections.Callable )
        self.HTTP = HTTP 

    # для удобства сразу распарсим HTTP-ответ до response:{}
    def fetch( self, peer_addr, args_dict, callback, subrequest="x" ):
        response = self.HTTP( args_dict )
        if callback:
            callback( response )
            
    # для удобства сразу распарсим HTTP-ответ до response:{}
    def post( self, peer_addr, args_dict, post_body, callback, subrequest="x" ):
        # для фейка передаем body просто как один из параметров
        args = args_dict.copy()
        args["_post_body"] = post_body
        response = self.HTTP( args )
        if callback:
            callback( response )
            
##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

#~ class IHttp2PeerWebServer: --- OBSOLETE, replaced by generic ihttp.IAsyncHttpFetcher
