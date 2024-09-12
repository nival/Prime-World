# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

from base.helpers import *
import functools
from tornado.httpclient import HTTPRequest

# request handling
import mock_agg_handlers

import cfg

import EC
import CC

##---------------------------------------------------------------------------------------------

class ISocialAggregator:
    """ Болванка для интерфейса SocialAggregator; настоящий интерфейс поддерживает запросы по HTTP, а мы просто вызываем методы локального LocalAggregatorHandler """
    def __init__(self, version="0.0", HTTP=None):
        self.version = version
        self.handler = mock_agg_handlers.LocalAggregatorHandler()
        
    def login(self, snuid, sntoken, snid, auto, snrefresh_token, callback=None, **kwargs):
        self.handler.setArguments(snid=snid, snuid=snuid, sntoken=sntoken, version=self.version, auto=auto, snrefresh_token=snrefresh_token, **kwargs)
        self.handler.onLogin()
        self.fin( callback )
        
    def logout(self, auid, callback=None):
        pass ##self.handler.onLogout() -- not implemented
        self.fin( callback )
        
    def register(self, snuid, sntoken, snid, snrefresh_token, use_billing=1, callback=None, **kwargs):
        self.handler.setArguments( snid=snid, snuid=snuid, sntoken=sntoken, version=self.version, use_billing=use_billing, snrefresh_token=snrefresh_token, **kwargs)
        self.handler.onRegister()
        self.fin( callback )

    def join(self, auid, snuid, sntoken, snid, snrefresh_token, callback=None):
        self.handler.setArguments( auid=auid, snid=snid, snuid=snuid, sntoken=sntoken, version=self.version, snrefresh_token=snrefresh_token )
        self.handler.onJoin()
        self.fin( callback )

    def merge(self, auid0, auid1, callback=None):
        self.handler.setArguments( auid1=auid0, auid2=auid0 )
        self.handler.onMerge()
        self.fin( callback )

    def deleteSn(self, auid, snid, callback=None):
        self.handler.setArguments(auid=auid, snid=snid)
        self.handler.onDeleteSn()
        self.fin( callback )

    def deleteSnNewState(self, auid, snid, callback=None):
        self.handler.setArguments(auid=auid, snid=snid)
        self.handler.onDeleteSn()
        self.fin( callback )

    def deleteAccount(self, auid, callback=None):
        self.handler.setArguments(auid=auid)
        self.handler.onDeleteAccount()
        self.fin(callback)

    def getInfo(self, auid, snid, include_secure_data, callback=None):
        if snid:
            self.handler.setArguments( snid=snid, auid=auid, include_secure_data=include_secure_data, version=self.version )
        else:
            self.handler.setArguments( auid=auid, include_secure_data=include_secure_data, version=self.version )
        self.handler.onGetInfo()
        self.fin( callback )

    def findUser(self, snid, snuid, callback=None):
        pass
        
    def getFriendsInfo(self, auid, include_secure_data=0, skip=0, limit=0, callback=None):
        self.handler.setArguments( auid=auid, include_secure_data=include_secure_data, version=self.version )
        self.handler.onGetInfo()
        self.fin( callback )
        
    def setProperty(self, auid, property_name, property_value, callback=None):
        self.handler.setArguments( auid=auid, property_name=property_name, property_value=property_value, version=self.version )
        self.handler.onSetProperty()
        self.fin( callback )
        
    def getBillingStatus(self, auid, callback=None):
        self.handler.setArguments( auid=auid, version=self.version )
        self.handler.onGetBillingStatus()  
        self.fin( callback )
        
    def retryBillingRegistration(self, auid, callback=None):
        self.handler.setArguments( auid=auid, version=self.version )
        pass ##self.handler.onRetryBillingRegistration() -- not implemented
        self.fin( callback )
        
    def fin(self, callback):
        if callback:
            callback( self.handler.reply )

    def pwcAggRegister(self, pwc_uid, use_billing=0, callback=None, referral=None, ruid=None):
        # register(self, snuid, sntoken, snid, snrefresh_token, use_billing=1, callback=None):
        kwargs ={}
        if ruid:
            kwargs['ruid'] = ruid
        else:
            kwargs['ruid'] = ""
        self.register( pwc_uid, '1', CC.PWCONNECT_AGGREGATOR_SNID, '1', use_billing=use_billing, callback=callback, referral=referral, **kwargs)

    def addFriend(self, auid, friend_auid, callback=None):
        pass

    def deleteFriend(self, auid, friend_auid, callback=None):
        pass

    def deleteGuildFriens(self, auid, callback=None):
        pass

    def listSn(self, callback=None):
        pass
        
##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IRealSocialAggregator ( ISocialAggregator ):
    """ настоящий интерфейс: поддерживает запросы по HTTP """
    def __init__(self, address, version, HTTP=None):
        self.address = http_prefix( address )
        self.version = version
        self.HTTP = HTTP
        
    def login(self, snuid, sntoken, snid, auto, snrefresh_token, use_billing=1, callback=None, **kwargs):
        req = self.address + "/?action=login&snid=%s&snuid=%s&sntoken=%s&version=%s&auto=%d&snrefresh_token=%s&use_billing=%s" \
            % (snid, snuid, sntoken, self.version, auto, snrefresh_token, use_billing)
        if kwargs.get('referral') is not None:
            req += '&referral='+str(kwargs['referral'])
        if kwargs.get('zul', None):
            req += '&zul=1'
        self.fetch( req, callback )

    def logout(self, auid, callback=None):
        req = self.address + "/?action=logout&auid=%s&version=%s" \
            % (auid, self.version)
        self.fetch( req, callback )
        
    def register(self, snuid, sntoken, snid, snrefresh_token, use_billing=1, callback=None, **kwargs):
        req = self.address + "/?action=register&snid=%s&snuid=%s&sntoken=%s&version=%s&snrefresh_token=%s&use_billing=%s" \
            % (snid, snuid, sntoken, self.version, snrefresh_token, use_billing)
        if kwargs.get('referral') is not None:
            req += '&referral='+str(kwargs['referral'])
        if kwargs.get('zul', None):
            req += '&zul=1'
        if kwargs.get('ruid', None) is not None:
            req += '&ruid='+str(kwargs['ruid'])
        self.fetch(HTTPRequest(url=req, request_timeout=60.0), callback)
        
    def join(self, auid, snuid, sntoken, snid, snrefresh_token, callback=None):
        req = self.address + "/?action=join&auid=%s&snid=%s&snuid=%s&sntoken=%s&version=%s&snrefresh_token=%s" \
            % (auid, snid, snuid, sntoken, self.version, snrefresh_token)
        self.fetch( req, callback )

    def merge(self, auid0, auid1, callback=None):
        req = self.address + "/?action=merge&auid1=%s&auid2=%s&version=%s" \
            % (auid0, auid1, self.version)
        self.fetch( req, callback )

    def deleteSn(self, auid, snid, callback=None):
        req = self.address + '/?action=delete_sn&auid=%s&snid=%s&version=%s' % (auid, snid, self.version)
        self.fetch(req, callback)

    def deleteSnNewState(self, auid, snid, callback=None):
        req = self.address + '/?action=delete_sn_new_state&auid=%s&snid=%s&version=%s' % (auid, snid, self.version)
        self.fetch(req, callback)

    def deleteAccount(self, auid, callback=None):
        req = self.address + '/?action=delete_account&auid=%s&version=%s' % (auid, self.version)
        self.fetch(req, callback)

    def getInfo(self, auid, snid, include_secure_data, callback=None):
        req = self.address + "/?action=get_info&auid=%s&version=%s&include_secure_data=%s" \
            % (auid, self.version, include_secure_data)
        if snid:
            req += '&snid=%s' % snid
        self.fetch( req, callback )

    def getInfos(self, auids, snid, callback=None):
        req = self.address + "/?action=get_infos&auids=%s&version=%s" % (auids, self.version)
        if snid:
            req += '&snid=%s' % snid
        self.fetch(req, callback)
        
    def findUser(self, snid, snuid, callback=None):
        req = self.address + "/?action=find_user&snid=%s&snuid=%s&version=%s" \
            % (snid, snuid, self.version)
        self.fetch( req, callback )

    def getUserSnList(self, snid, snuid, callback=None):
        req = self.address + "/?action=get_user_sn_list&snid=%s&snuid=%s&version=%s" \
            % (snid, snuid, self.version)
        self.fetch( req, callback )

    def getFriendsInfo(self, auid, include_secure_data=0, skip=0, limit=0, callback=None):
        req = self.address + "/?action=get_friends_info_all&auid=%s&version=%s&include_secure_data=%d&skip=%s&limit=%s" % (auid, self.version, include_secure_data, skip, limit)
        self.fetch( req, callback )

    def setProperty(self, auid, property_name, property_value, callback=None):
        req = self.address + "/?action=set_property&auid=%s&version=%s&property_name=%s&property_value=%s" \
            % (auid, self.version, property_name, property_value)
        if cfg.TOURNAMENT_SERVER:
            if callback:
                callback( {'ok':1} )
            return
        self.fetch( req, callback )
        
    def getBillingStatus(self, auid, callback=None):
        req = self.address + "/?action=get_billing_status&auid=%s&version=%s" \
            % (auid, self.version)
        self.fetch( req, callback )
        
    def retryBillingRegistration(self, auid, callback=None):
        req = self.address + "/?action=retry_billing_registration&auid=%s&version=%s" \
            % (auid, self.version)
        self.fetch( req, callback )
        
    def addFriend(self, auid, friend_auid, callback=None):
        req = self.address + "/?action=add_friend&auid=%s&friend_auid=%s&version=%s" \
            % (auid, friend_auid, self.version)
        self.fetch( req, callback )

    def addSnFriend(self, auid, friend_auid, snid, callback=None):
        req = self.address + "/?action=add_friend&auid=%s&friend_auid=%s&snid=%s&version=%s" \
            % (auid, friend_auid, snid, self.version)
        self.fetch( req, callback )

    def deleteFriend(self, auid, friend_auid, callback=None):
        req = self.address + "/?action=delete_friend&auid=%s&friend_auid=%s&version=%s" \
            % (auid, friend_auid, self.version)
        self.fetch( req, callback )

    def deleteSnFriends(self, auid, snid, callback=None):
        req = self.address + "/?action=delete_friend&auid=%s&snid=%s&version=%s" \
            % (auid, snid, self.version)
        self.fetch( req, callback )

    def setGender(self, auid, snid, gender, callback=None):
        req = self.address + "/?action=set_gender&auid=%s&snid=%s&gender=%s&version=%s" \
            % (auid, snid, gender, self.version)
        self.fetch( req, callback )

    def getAeriaToken(self, auid, callback=None):
        req = self.address + "/?action=get_aeria_token&auid=%s&version=%s" % (auid, self.version)
        self.fetch(req, callback)



    def refreshAeriaToken(self, auid, callback=None):
        req = self.address + "/?action=refresh_aeria_token&auid=%s&version=%s" % (auid, self.version)
        self.fetch(req, callback)

    def markLastLogin(self, auid, callback=None):
        req = self.address + "/?action=mark_login&auid=%s&version=%s" % (auid, self.version)
        self.fetch(req, callback)

    def listSn(self, callback=None):
        req = self.address + "/?action=list_sn&version=%s" % (self.version,)
        self.fetch(req, callback)

    # ----------------------------------------------------------------------------------
    def fetch(self, request, callback):
        # HTTP-результат пусть падает в _onFetch, там мы его распарсим до response:{} 
        # (достало писать однотипные http_reply-обработчики)
        _callback = functools.partial( self._onFetch, callback=callback )
        try:
            debug("setAggProperty request: %s", request)
            self.HTTP.fetch( request, _callback )
        except:
            catch()
            _callback( None )
        
    # ----------------------------------------------------------------------------------
    def _onFetch(self, http_reply, callback=None):
        response = {}
        try:
            if http_reply and (not http_reply.error):   
                unquote_body = urllib.unquote( http_reply.body )
                
                # отрезаем лишнюю хню в конце ответа (нам нужен чистый json, а аггрегатор дописывает какие-то самодеятельные сообщения)
                warning_suffixes = ["}\nWarning:", "}\nNotice:", "}\Error:"]
                for suffix in warning_suffixes:
                    extra_warnings_pos = unquote_body.find( suffix )
                    if extra_warnings_pos > 0:
                        break
                if extra_warnings_pos > 0:
                    warn( "skipping extra aggregator warnings: %s" % unquote_body[ (extra_warnings_pos+1): ])
                    unquote_body = unquote_body[ :(extra_warnings_pos+1) ] 

                try:
                    json_reply = json_load_transform( unquote_body )
                except ValueError:
                    warn("ValueError parsing SA reply. Reply body: \"%s\"", unquote_body)
                    raise
            else:
                warn( "BAD aggregator http reply: %s" % http_reply )
                json_reply = dict( error=EC.AGGREGATOR_HTTP_ERROR, http_error=http_reply.error )
        except:
            catch()
            msg = "EXCEPTION on aggregator http reply: %s" % http_reply
            warn( msg )
            json_reply = dict( error=EC.AGGREGATOR_HTTP_ERROR, http_error=msg )
            
        if callback:
            callback( json_reply )

