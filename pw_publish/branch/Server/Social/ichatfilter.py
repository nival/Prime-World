# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2013, Nival Network

import sys, os, time, json, urllib
import functools
import re

from base.helpers import *

import CC
import EC
import ihttp

import coord_cfg

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IChatFilter:
    """ Болванка для интерфейса """
    def __init__(self, address=None, HTTP=None):
        pass
        
    def filterText(self, *args, **kwargs):
        pass
        
##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class ICleanSpeakChatFilter( IChatFilter ):
    """  """
    def __init__(self, address="", HTTP=None, request_limit=1000):
        self.address = http_prefix(address)
        self.HTTP = ihttp.ILimitedAsyncHttpFetcher( HTTP, request_limit )
        
    def do(self, args, text, callback):
        _callback = functools.partial( self.onPost, args=args, text=text, callback=callback )
        self.post( args, _callback )
            
    # единственная точка, реально вызывающая HTTP.post (OVERRIDE point для фейк-интерфейсов)
    def post(self, args, callback):
        headers = { "Content-Type": "application/x-www-form-urlencoded" }
        body = urllib.urlencode( args )
        info("ichatfilter post body: %s" % body)
        _timeout = coord_cfg.COORDINATOR_CHAT_FILTER_TIMEOUT
        # у нас нестандартный формат ответа (никаких {"response"}, да еще и встречаются кривые числа "с запятыми" в json, так что unwrap=False, развернем сами)
        self.HTTP.post( self.address, {}, body, callback, headers=headers, subrequest="content/item.js", unwrap=False, timeout=_timeout )
        
    def onPost(self, reply, args={}, text="", callback=None):
        ##info("ICleanSpeakChatFilter reply (args=%s):\n%s" % (args, reply))
        response = text
        if reply:
            try:
                if reply:
                    reply = re.sub( r'"quality": (\d),', r'"quality": \1.', reply )
                unjson_reply = json_loads(reply)
                filter_response = unjson_reply.get("filter", {})
                response = filter_response.get("replacement", "") 
                info("filtered: %r" % response)
            except:
                catch("ICleanSpeakChatFilter.onPost: Error processing reply string '%r'", reply)
        if callback:
            callback(response)
        
    # ----------------------------------------------------------------------------------
    def filterText(self, text, locales, callback):
        encoded_text = utf8convert(text)
        args = [
            ("contentItem.content", encoded_text),
            ("contentItem.type", "text"),
            ("filter.operation", "replace"),
            ("filter.blacklist.enabled", "true"),
            ("filter.blacklist.severity", "high"),
        ]
        for locale in locales:
            args.append( ("filter.blacklist.locale", locale.lower()) )
        self.do( args, text, callback )
    
##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IFakeChatFilter( ICleanSpeakChatFilter ):
    """ тупо возвращаем тот же текст, без изменений """
    def do(self, args, text, callback):
        if callback:
            callback( text )
