# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import os, sys, time, functools

sys.path.append("base")
sys.path.append("cfg")

from modeldata.changes import MakeModelChangeString
from tornado.options import options
import tornado
import EC

from base.helpers import *
from subaction import ResponseObject

def internalDummyCallback(response):
    #msg_id = getattr(intaction, "msg_id", 0)
    #info("InternalMailAction (action %s, acc auid=%s, msg_id=%s) response: %s" % (intaction.action, intaction.acc.auid, msg_id, response))
    info("InternalMailAction response: %s" % (response))

## ----------------------------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------------------------

class InternalAction( object ):
    """ аналог SubAction для внутренних запросов, где не нужно передавать и парсить http-параметры """
    action = "intbase"
    
    # список ключей, которые нужно найти в **kwargs (если там нету -- берем указанные здесь значения-заглушки)
    _Interfaces = dict( 
        acc=ClassDict(), # user account (acc.model = пользовательская Model Data)
        I=None,          # "all server interfaces" dictionary
    )
    
    def __init__(self, fin_callback=internalDummyCallback, **kwargs): # ?
        self.arguments = kwargs
        
        # возможно, понадобится и callback(response)
        self.fin_callback = fin_callback
        self.response = { "ok":0, "ec":0, "server":options.server_name }

        for key, iBase in self._Interfaces.iteritems():
            if kwargs:
                iface = kwargs.get(key)
                if iface:
                    setattr(self, key, iface)
                    continue
                
            # по умолчанию -- берем default-ные заглушки
            setattr(self, key, iBase)

    def addArguments(self, **kwargs):
        if kwargs:
            for k,v in kwargs.iteritems():
                self.arguments[k] = [v]

    # вернуть ответ (аналогично JsonHandler)
    def fin(self):
        if self.fin_callback:
            if not self.I.WS.TEST_MODE:
                # поручаем tornado IOLoop вызвать указанный callback после того как мы вернем управление (и корректно отработают все декораторы)
                loop = tornado.ioloop.IOLoop.instance()
                _callback = functools.partial( self.fin_callback, self.response )
                loop.add_callback( _callback )
            else:
                # в тестах вызываем callback напрямую
                self.fin_callback( self.response )

    def fail(self, message, code):
        info( "%s action fail: ec=%s, message=%s" % ( getattr(self, "action", ""), code, message ))
        self.response["error"] = message
        self.response["ec"] = code
        self.fin()

    def getParam(self, name, default=None):
        value = self.arguments.get(name, default)
        return value
        
    def getIntParam(self, name, default=None):
        value = toint( self.arguments.get(name, default) )
        return value

    def getBoolParam(self, name, default=None):
        value = str2bool( self.arguments.get(name, default) )
        return value
    ##-------------------------------------------------------------------------------------
    ## добавляем к списку response.model[] новую "строчку изменений": [comment, path, op, change]
    def writeStringToResponse(self, key, comment, path, op, params):
        if not self.response.has_key(key):
            self.response[key] = ResponseObject( key )
        if isinstance( self.response[key], ResponseObject ):
            self.response[key].addResponse( comment, path, op, params )
        else:
            self.response[key].append( MakeModelChangeString(comment, path, op, params) )

## ----------------------------------------------------------------------------------------------------
## ----------------------------------------------------------------------------------------------------

class InternalMailAction( InternalAction ):
    """ реагируем на события из внутренней почты (social exchange);
        сразу парсим ключевые поля msg: msg_id, msg_type, date_received, from_project, from_auid """
    action = "intmail"
    
    # список ключей, которые нужно найти в **kwargs (если там нету -- берем указанные здесь значения-заглушки)
    _Interfaces = mergeDicts( InternalAction._Interfaces, dict( 
        msg_id = 0,
        msg = {},
    ))
    
    def __init__(self, fin_callback=internalDummyCallback, **kwargs): # ?
        super(InternalMailAction, self).__init__(fin_callback, **kwargs)
        
        ## info( "InternalMailAction: message[%s]=%r" % (self.msg_id, self.msg) )

        self.msg_type = ""
        self.date_received = 0
        self.from_project = ""
        self.from_auid = 0
        
        # сразу парсим ключевые поля msg
        try:
            self.msg_type = self.msg.get("type")
            self.date_received = toint( self.msg.get("dt_rcv") )
            sender = self.msg.get("sender", "")

            split_sender = sender.split(":")
            if len(split_sender) == 2:
                self.from_project, str_auid = split_sender
                self.from_auid = toint(str_auid)
            else:
                self.from_project = sender
        except:
            catchFull()
      
        info( "InternalMailAction: parsed message[msg_id=%s] msg_type=%s, date_received=%s, sender(project=%s, auid=%s)", self.msg_id, self.msg_type, time.ctime(self.date_received), self.from_project, self.from_auid)
          
    ## debug
    #~ def __del__(self):
        #~ info("__del__ InternalMailAction(msg_id=%s)" % self.msg_id)
