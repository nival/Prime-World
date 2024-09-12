# -*- coding: utf-8 -*-

#!/usr/bin/env python
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json, urllib

sys.path.append('base')
from helpers import *

import collections
import functools

import CC
import EC
import ihttp

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IFriendService:
    """ Болванка для интерфейса """
    def __init__(self, addresses=None, HTTP=None):
        pass
        
    def removePartyId(self, *args, **kwargs):
        pass
        
    def removePartyInvite(self, *args, **kwargs):
        pass
        
    def updateWsAcc(self, *args, **kwargs):
        pass
        
    def sendPartyCmd(self, *args, **kwargs):
        pass
    def removeRecentAlly(self, *args, **kwargs):
        pass
##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IHttpFriendService( IFriendService ):
    """  """
    def __init__(self, addresses=[""], HTTP=None, request_limit=1000):
        self.addresses = addresses
        self.address_count = len(addresses) or 1
        self.HTTP = ihttp.ILimitedAsyncHttpFetcher( HTTP, request_limit )
        
    def getPeer(self, auid):
        if self.address_count:
            return self.addresses[ auid % self.address_count ] 
            #~ return self.addresses[ toint(auid/1000) % self.address_count ] # тестовый шардинг, при котором все тестовые auid (в пределах первой тысячи) попадут на один FS
            
    def do(self, auid, args, callback):
        peer_addr = self.getPeer( toint(auid) )
        _callback = functools.partial( self.onFetch, peer_addr=peer_addr, args=args, callback=callback )
        self.fetch( peer_addr, args, _callback )
            
    # единственная точка, реально вызывающая HTTP.fetch (OVERRIDE point для фейк-интерфейсов)
    def fetch(self, peer_addr, args, callback):
        self.HTTP.fetch( peer_addr, args, callback )
        
    def onFetch(self, response, peer_addr="", args={}, callback=None):
        info("IHttpFriendService response (peer_addr=%s, args=%s):\n%s" % (peer_addr, args, str(response)[:128]))
        if callback:
            callback(response)
        
    # ----------------------------------------------------------------------------------
    # LEGACY (PersonServer) requests
    def subscribe(self, auid, snid, snuid, uid, nick, photo, fame, fraction, sex, server, locale, callback):
        quoted_photo = photo or ""  #urlQuote( photo or "" ) # от всяких пробелов http-шечке будет худо, так что quote
        quoted_nick = nick or "" #urlQuote( nick or CC.NICK_EMPTY )
        args = dict( action="subscribe", auid=auid, snid=snid, snuid=snuid, uid=uid, nick=quoted_nick, photo=quoted_photo, sex=sex, server=server, locale=locale, fame=fame )
        self.do( auid, args, callback )
    
    def unsubscribe(self, auid, server, callback):
        args = dict( action="unsubscribe", auid=auid, server=server )
        self.do( auid, args, callback )
        
    def updateGameData(self, auid, nick, fame, fraction, locale, hero_id, hero_lvl, hero_force, hero_rating, sex, callback):
        quoted_nick = nick or "" # urllib.quote( nick or CC.NICK_EMPTY ) # пустой ник посылать бессмысленно, аггрегатор не поставит property
        args = dict( action="update_game_data", auid=auid, nick=quoted_nick, fame=toint(fame), fraction=fraction, locale=locale, \
            hero_id=hero_id, hero_lvl=hero_lvl, hero_force=hero_force, hero_rating=hero_rating, sex=sex )
        self.do( auid, args, callback )
    
    def inCastle(self, auid, on, callback=None):
        args = dict( action="in_castle", auid=auid, on=toint(on) )
        self.do( auid, args, callback )

    def afk(self, auid, callback=None):
        args = dict( action="afk", auid=auid )
        self.do( auid, args, callback )

    def mute(self, auid, status, callback=None):
        info("mute: auid %r status %r", auid, status)
        args = dict(action="mute", auid=auid, isMuted=status)
        self.do(auid, args, callback)


    def addFriend(self, auid, friend_auid, callback, no_aggregator_up=None):
        args = dict( action="add_friend", auid=auid, friend_auid=friend_auid)
        if no_aggregator_up is not None:
            args['no_aggregator_up'] = no_aggregator_up
        self.do( auid, args, callback )

    def addSnFriend(self, auid, friend_auid, snid, callback):
        #info("addSnFriend: auid %s, friend_auid %s, snid %s" % (auid, friend_auid, snid))
        args = dict( action="add_friend", auid=auid, friend_auid=friend_auid, snid=snid)
        self.do( auid, args, callback )

    def deleteFriend(self, auid, friend_auid, callback):
        args = dict( action="delete_friend", auid=auid, friend_auid=friend_auid ) 
        self.do( auid, args, callback )
        
    def deleteSnFriends(self, auid, snid, callback):
        args = dict( action="delete_friend", auid=auid, snid=snid )
        self.do( auid, args, callback )

    # ----------------------------------------------------------------------------------
    def removePartyId(self, auid, party_id, master_auid, callback=None):
        args = dict( action="fs_remove_party_id", auid=auid, party_id=party_id, master_auid=master_auid )
        self.do( auid, args, callback )
        
    def removePartyInvite(self, auid, party_id, master_auid, reason="", callback=None):
        args = dict( action="fs_remove_party_invite", auid=auid, party_id=party_id, master_auid=master_auid, reason=reason )
        self.do( auid, args, callback )

    def updateWsAcc(self, auid, uid, server):
        args = dict( action="fs_update_ws_acc", auid=auid, uid=uid, server=server )
        self_addr = self.getPeer( auid )
        # оповещаем всех кроме своего "родного" friend_service
        for peer_addr in self.addresses:
            if peer_addr != self_addr:
                self.fetch( peer_addr, args, None )
                
    def updateFriendList(self, auid, friend_auids, callback=None):
        args = dict( action="fs_update_friend_list", auid=auid, friend_auids=json_dumps(friend_auids) )
        self_addr = self.getPeer( auid )
        # рассылаем всем кроме своего "родного" friend_service
        for peer_addr in self.addresses:
            if peer_addr != self_addr:
                self.fetch( peer_addr, args, callback )

    def refreshFriendList(self, auid, callback=None):
        args = dict( action="refresh_friend", auid=auid)
        # шлем "нужному" friend_service`у
        self.fetch(self.getPeer(auid), args, callback)

    def updateDeleteFriend(self, auid, friend_auid, callback=None):
        args = dict( action="fs_update_delete_friend", auid=auid, friend_auid=friend_auid )
        self.do( auid, args, callback )
        
    def updateAddFriend(self, auid, friend_auid, friend_acc=None, send_personal_info=0, callback=None):
        if friend_acc:
            args = dict( 
                action="fs_update_add_friend", 
                auid=auid, 
                friend_auid=friend_auid, 
                friend_acc_on=1,
                send_personal_info=send_personal_info,
                #---------------------------------------------
                # our personal info:
                nickName = friend_acc.nick, #urllib.quote(friend_acc.nick),
                gender = friend_acc.sex,
                fraction = friend_acc.fraction,
                photoUrl = friend_acc.photoUrl, #urllib.quote(friend_acc.photoUrl)
                fame = friend_acc.fame,
                online = friend_acc.online,
                Status = friend_acc.friend_status,
                lastLoginTime = friend_acc.lastlogin,
                lastLogoutTime = friend_acc.lastlogout,
                guildshortname = friend_acc.guildshortname,
                isMuted = friend_acc.IsMuted
                #---------------------------------------------
            )
        else:
            info("updateAddFriend witg empty friend_acc; auid=%s, friend_auid=%s", auid, friend_auid)
            args = dict(action="fs_update_add_friend", auid=auid, friend_auid=friend_auid, friend_acc_on=0)
        self.do(auid, args, callback)
            
    def sendPartyCmd(self, auid, server, command, callback, **kwargs):
        if command in ["party_invite", "party_accept", "party_decline", "party_progress", "party_choose_again",
                       "party_set_id"]:
            args = dict( action="fs_"+command, auid=auid, server=server, **kwargs )
            self.do( auid, args, callback )
        else:
            err("bad party cmd for friends server (command %s)" % command)
            if callback:
                callback( dict(ec=EC.FRIENDS_BAD_PARTY_CMD, error="bad party cmd for friends server: %s" % command) )

    def partyInviteFromMaster(self, invite_auid, callback, **kwargs):
        args = dict( action="fs_party_invite_from_master", invite_auid=invite_auid, **kwargs )
        self.do( invite_auid, args, callback )

    def sendTamburCmd(self, auid, command, callback=None, **kwargs):
        if command in ["tambur_add"]:
            args = dict( action="fs_"+command, auid=auid, **kwargs )
            self.do( auid, args, callback )
        else:
            err("bad party cmd for friends server (command %s)" % command)
            if callback:
                callback( dict(ec=EC.FRIENDS_BAD_PARTY_CMD, error="bad party cmd for friends server: %s" % command) )
                
    def removeTamburId(self, tambur_id, auids=[]):
        args = dict( action="fs_remove_tambur_id", json_auids=json_dumps(auids), tambur_id=tambur_id)
        # оповещаем всех 
        for peer_addr in self.addresses:
            self.fetch( peer_addr, args, None )

    def updateGuildShortName( self, auid, guildshortname ):
        info( "updateGuildShortName: %r" % guildshortname )
        args = dict( action="update_guildshortname", auid=auid, guildshortname=guildshortname )
        self.do( auid, args, None )

    def addRecentAllies(self, auid, allies_auids):
        info("addRecentAllies: %r" % allies_auids)
        args = dict(action="add_recent_allies", auid=auid, allies_auids=allies_auids)
        self.do(auid, args, None)

    def updateRecentAllies(self, auid, callback=None):
        info("updateRecentAllies: %r" % auid)
        args = dict(action="update_recent_allies", auid=auid)
        self.do(auid, args, callback)

    def removeRecentAlly(self, auid, ally_auid, callback):
        info("removeRecentAlly: %r, %r", auid, ally_auid)
        args = dict(action="remove_recent_ally", auid=auid, ally_auid=ally_auid)
        self.do(auid, args, callback)

    def updateRecentAllyInfo(self, auid, callback=None):
        info("updateRecentAllyInfo: %r" % auid)
        args = dict(action="update_recent_ally_info", auid=auid)
        self.do(auid, args, callback)

    def getFriendInfo(self, auid, callback=None):
        info("getFriendInfo: %r" % auid)
        args = dict(action="fs_get_friend_info", auid=auid)
        self.do(auid, args, callback)




##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IFakeFriendService( IHttpFriendService ):
    """ вместо HTTP у нас функция, которую мы тупо вызываем """
    def __init__(self, addresses=[""], HTTP=None):
        self.addresses = addresses
        self.address_count = len(addresses) or 1
        assert isinstance( HTTP, collections.Callable )
        self.HTTP = HTTP
        
    def fetch(self, peer_addr, args_dict, callback):
        response = self.HTTP( args_dict )
        if callback:
            callback( response )
