# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2012, Nival Network

from base.helpers import *

import collections
import functools

from tornado.httpclient import HTTPRequest
from ihttp import ILimitedAsyncHttpFetcher
import CC

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class ISocialExchange:
    """ Болванка для интерфейса внешних запросов к SEX """
    def __init__(self, HTTP=None):
        pass

    # по дефолту сразу и забираем накопившиеся сообщения
    def login( self, *args, **kwargs ):
        pass 
        
    def logout( self, *args, **kwargs ):
        pass

    def sendMail( self, *args, **kwargs ):
        pass
        
    def receiveMail( self, *args, **kwargs ):
        pass
        
    def purgeMail( self, *args, **kwargs ):
        pass
        
    def touch( self, *args, **kwargs ):
        pass

    def sendToGuildService( self, *args, **kwargs ):
        pass


##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IFakeSocialExchange( ISocialExchange ):
    """ Перехватываем внешние запросы к тестируемому WorkServer, направляем их в некую функцию 'HTTP-handler' """
    def __init__(self, HTTP):
        self.HTTP = HTTP 

    # по дефолту сразу и забираем накопившиеся сообщения
    def login( self, *args, **kwargs ):
        info( "IFakeSocialExchange login(args: %r, kwargs: %r)" % (args, kwargs) )
        
    def logout( self, *args, **kwargs ):
        info( "IFakeSocialExchange logout(args: %r, kwargs: %r)" % (args, kwargs) )

    def sendMail( self, *args, **kwargs ):
        info( "IFakeSocialExchange sendMail(args: %r, kwargs: %r)" % (args, kwargs) )
        
    def receiveMail( self, *args, **kwargs ):
        info( "IFakeSocialExchange receiveMail(args: %r, kwargs: %r)" % (args, kwargs) )
        
    def purgeMail( self, *args, **kwargs ):
        info( "IFakeSocialExchange purgeMail(args: %r, kwargs: %r)" % (args, kwargs) )
            
    def touch( self, *args, **kwargs ):
        info( "IFakeSocialExchange touch(args: %r, kwargs: %r)" % (args, kwargs) )

    def sendToGuildService( self, *args, **kwargs ):
        info( "IFakeSocialExchange sendToGuildService(args: %r, kwargs: %r)" % (args, kwargs) )
##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IAsyncHttpSocialExchange( ISocialExchange ):
    """ Настоящий интерфейс, умеет исполнять запросы через HTTP GET/POST """
    def __init__(self, HTTP, sex_url, ws_url, request_limit=1000):
        self.HTTP = ILimitedAsyncHttpFetcher( HTTP, request_limit )
        self.url = http_prefix( sex_url )
        self.ws_addr = http_prefix( ws_url )

    def login( self, auid, project, callback=None ):
        ## callback должен сохранить sid (session id) и server (имя сервера) из ответа SocialExchange на аккаунте юзера auid
        args = dict( method="login", project=project, auid=auid, url=self.ws_addr )
        self.HTTP.fetch( self.url, args, callback, subrequest=CC.SEX_BALANCER_NAME )

    def logout( self, auid, sid, server, callback=None ):
        args = dict( method="logout", auid=auid, sid=sid )
        self.HTTP.fetch( self.url, args, callback, subrequest=server )
    
    def sendMail( self, project, auid, messages, from_auid=0, from_sid=0, from_server="", callback=None ):
        ## messages = [{msg},{msg},...], список сообщений (каждое сообщение -- некий словарь)
        if isinstance(messages, dict):
            # вообще-то хотим список сообщений, но если дают словарь (т.е. по идее одно сообщение), ок, завернем
            messages = [ messages ]
        post_body = json_dumps(messages)
        if from_auid:
            # от залогиненного exchange юзера, на его конкретный x-server
            args = dict( method="send", project=project, recipient=auid, sid=from_sid, auid=from_auid )
            if from_server:
                subrequest = from_server
            else:
                errStack("IAsyncHttpSocialExchange.sendMail: Empty from_server value (%r) for auid %s, from_auid %s, from_sid %s. "
                                 % (from_server, auid, from_auid, from_sid))
                if callback:
                    callback(None)
                return
        else:
            # от анонимного отправителя, на произвольный exchange server
            args = dict( method="send_nl", project=project, recipient=auid, sender=CC.SEX_PW_PROJECT )
            subrequest = CC.SEX_BALANCER_NAME
        self.HTTP.post( self.url, args, post_body, callback, subrequest=subrequest )
    
    def purgeMail( self, auid, sid, server, message_ids, callback=None ):
        if isinstance(message_ids, basestring):
            # вообще-то хотим список сообщений, но если дают строчку (т.е. один msg_id), ок, завернем в список
            message_ids = [ message_ids ]
        args = dict( method="purge", auid=auid, sid=sid, server=server)
        info("purgeMail(%s), message_ids=%s" % (args, message_ids))
        if isinstance(message_ids, list):
            post_body = json_dumps( message_ids )
            self.HTTP.post( self.url, args, post_body, callback, subrequest=server )
        else:
            warn("bad message id list for purgeMail(%s), message_ids=%s" % (args, message_ids))
            
    def touch( self, auid, sid, server, callback=None ):
        args = dict( method="touch", auid=auid, sid=sid )
        self.HTTP.fetch( self.url, args, callback, subrequest=server )

    def sendToGuildService(self, fGuildAuid, tGuildAuid, mess, callback):
        data= dict(type="send_to_guild")
        mess["fGuildAuid"] = fGuildAuid
        data["messages"] = mess
        self.sendMail(CC.SEX_PW_GUILD_PROJECT, tGuildAuid, data, 0, 0, "", callback)

