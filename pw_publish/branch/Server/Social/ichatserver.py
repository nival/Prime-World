# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json, urllib

sys.path.append('base')
from helpers import *

import collections
import functools

from ihttp import ILimitedAsyncHttpFetcher

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IChatServer:
    """ Болванка для интерфейса """
    def __init__(self):
        pass
        
    def addUser(self, *args, **kwargs):
        pass
        
    def removeUser(self, *args, **kwargs):
        pass
        
    def addUserGroup(self, *args, **kwargs):
        pass
        
    def removeUserGroup(self, *args, **kwargs):
        pass

    def addUserGlobalGroups(self, *args, **kwargs):
        pass

    def removeUserGlobalGroups(self, *args, **kwargs):
        pass

    def broadcast(self, *args, **kwargs):
        pass

    def muteUser(self, *args, **kwargs):
        pass

    def unmuteUser(self, *args, **kwargs):
        pass
    
    def systemMessage(self, *args, **kwargs):
        pass
        
##---------------------------------------------------------------------------------------------
class IFakeChatServer( IChatServer ):
    """ Перехватываем запросы к тестируемому PersonServer, направляем их в некую функцию 'HTTP-handler' """
    def __init__(self, HTTP=None):
        assert isinstance( HTTP, collections.Callable )
        self.HTTP = HTTP 
        
    # ----------------------------------------------------------------------------------
    def addUser(self, auid, key, nickname, fraction, muted, mutetime, locale, callback):
        args = dict(
            auid=auid, 
            key=key,
            nickname=nickname,
            fraction=fraction,
            muted=muted,
            mutetime=mutetime,
            locale=locale,
            action="add_user"
        )
        self.fetch(args, callback, 'x')

    def removeUser(self, host, auid, callback):
        args = dict(
            auid=auid, 
            action="remove_user"
        )
        self.fetch(args, callback, 'x')

    def addUserGroup(self, auid, group, callback, timestamp=0):
        if not timestamp:
            timestamp = time.time()
        args = dict(
            auid=auid, 
            group=group,
            timestamp=timestamp,
            action="add_user_group"
        )
        self.fetch(args, callback, 'x')
        
    def removeUserGroup(self, auid, group, callback, timestamp=0):
        if not timestamp:
            timestamp = time.time()
        args = dict(
            auid=auid, 
            group=group,
            timestamp=timestamp,
            action="remove_user_group"
        )
        self.fetch(args, callback, 'x')

    def addUserGlobalGroups(self, auid, callback, timestamp=0):
        self.fetch({'auid': auid, 'timestamp': timestamp or time.time(), 'action': 'add_user_global'}, callback, 'x')

    def removeUserGlobalGroups(self, auid, callback, timestamp=0):
        self.fetch({'auid': auid, 'timestamp': timestamp or time.time(), 'action': 'remove_user_global'}, callback, 'x')

    def broadcast(self, message, locale, callback):
        args = dict(
            message=message, 
            locale=locale,
            action="broadcast"
        )
        self.fetch(args, callback, 'x')

    def muteUser(self, host, auid, muted, mutetime, callback):
        args = dict(
            auid=auid, 
            mutetime=mutetime,
            muted=muted,
            action="mute_user"
        )
        self.fetch(args, callback, 'x')

    def unmuteUser(self, host, auid, callback):
        args = dict(
            auid=auid, 
            action="unmute_user"
        )
        self.fetch(args, callback, 'x')

    def systemMessage(self, auid, title, text, callback):
        args = dict(
            action="msg",
            auid=auid, 
            title=title,
            text=text,
        )
        self.fetch(args, callback, 'x')
    
    # ----------------------------------------------------------------------------------
    # для удобства сразу распарсим HTTP-ответ до response:{}
    def fetch( self, args_dict, callback, subrequest="x" ):
        # print 'FETCH', args_dict
        response = self.HTTP( args_dict )
        if callback:
            callback( response )


##---------------------------------------------------------------------------------------------
class IRealChatServer( IFakeChatServer ):
    """ настоящий интерфейс: поддерживает запросы по HTTP """
    def __init__(self, addresses, HTTP=None, request_limit=1000):
        self.addresses = addresses
        if self.addresses:
            for i, address in enumerate(self.addresses):
                self.addresses[i] = http_prefix( address )
        self.addr_count = len(self.addresses) or 1
        self.HTTP = ILimitedAsyncHttpFetcher( HTTP, request_limit )
        
    # ----------------------------------------------------------------------------------
    def fetch(self, args, callback, subrequest="x"):
        auid = args.get("auid", 0)
        if self.addresses:
            # кидаем на один из конкретных адресов (если в запросе нет auid-а, кинем на первый по списку чат-сервис)
            address = self.addresses[ auid % self.addr_count ]
            self.HTTP.fetch( address, args, callback, subrequest )
        else:
            warn("IRealChatServer.fetch: no valid chat service addresses, fail")
