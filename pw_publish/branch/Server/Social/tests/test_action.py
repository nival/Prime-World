#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, json, base64, hashlib

sys.path.append('../base')

from helpers import *

##------------------------------------------------------------------------------------------------------------------
class TestAction:
    """ test-обертка для наследников SubAction (имя класса передается в параметре classOf) """
    
    def __init__(self, params, classOf, **kwargs):
        self.handler = classOf( params, self.callback1, **kwargs )
        
    def OnStart(self):
        self.handler.onStart()
    
    def callback1(self, reply):
        self.reply = reply
        ##log( "callback1 reply:" + str(reply) )

##------------------------------------------------------------------------------------------------------------------
class TestDictRequest:
    def __init__( self, paramsDict ):
        self.flatParams = paramsDict
    def getFlatParams( self ):
        ##info("TestDictRequest getFlatParams")
        return self.flatParams

class TestDictAction( TestAction ):
    """ Отличается тем, что параметры запроса задаются простым словарем, без вложенности.
        По умолчанию значение каждого параметра задается списком значений: "params:[value, ...]",
        данная обертка сама "запаковывает" несписочные параметры, вызывать ее можно, например, так:
        
        TestDictAction( dict(user2="user4"), SomeAction, acc=accTest, MC=imemcache.MemcacheMockYes() )
    """
        
    # перепаковываем paramsDict..
    def __init__(self, paramsDict, classOf, **kwargs):
        params = {}
        if isinstance(paramsDict, dict):
            for key,value in paramsDict.iteritems():
                if not isinstance(value, list):
                    params[key] = [ value ]
                else:
                    params[key] = value # и так список
                    
        request = kwargs.get("request")
        if request:
            try:
                args = request.arguments
            except:
                request.arguments = params
        else:
            kwargs["request"] = TestDictRequest( paramsDict )
        
        ##log( "TestDictAction kwargs:" + str(kwargs) )
        self.handler = classOf( params, self.callback1, **kwargs )
