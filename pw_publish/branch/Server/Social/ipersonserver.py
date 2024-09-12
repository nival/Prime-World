# -*- coding: utf-8 -*-
#
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, json, urllib

from base.helpers import *

import collections
import functools

import CC

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IPersonServer:
    """ Болванка для интерфейса """
    def __init__(self, address=None, HTTP=None):
        pass
        
    def subscribe(self, *args):
        pass
        
    def updateGameData(self, *args):
        pass

    def updatePartyDodge(self, auid, server, banEndTime, party_id, callback):
        pass
        
    def unsubscribe(self, auid, server, callback):
        pass
        
    def sendPartyCmd(self, auid, server, command, callback, **kwargs):
        pass

    def sendTamburCmd(self, auid, server, command, callback, **kwargs):
        pass
        
    def addFriend(self, auid, friend_auid, callback, **kwargs):
        pass

    def deleteFriend(self, auid, friend_auid, callback, **kwargs):
        pass
        
    def inCastle(self, auid, on):
        pass

    def afk(self, auid):
        pass

    def mute(self, auid, status, callback, **kwargs):
        pass

##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IFakePersonServer( IPersonServer ):
    """ Перехватываем запросы к тестируемому PersonServer, направляем их в некую функцию 'HTTP-handler' """
    def __init__(self, address=None, HTTP=None):
        assert isinstance( HTTP, collections.Callable )
        self.HTTP = HTTP 
        
    # ----------------------------------------------------------------------------------
    def subscribe(self, auid, snid, snuid, uid, nick, photo, fame, fraction, sex, server, locale, callback):
        quoted_photo = urlQuote( photo ) # от всяких служебных символов http-шечке будет худо, так что quote
        quoted_nick = urlQuote( nick )
        args = dict(
            auid=auid, snid=snid, snuid=snuid, uid=uid, nick=quoted_nick, photo=quoted_photo, server=server,
            fame=fame, fraction=fraction, sex=sex, locale=locale,
            action="subscribe"
        )
        self.fetch(args, callback)
        
    def updateGameData(self, auid, nick, fame, fraction, locale, hero_id, hero_lvl, hero_force, hero_rating, sex, callback):
        quoted_nick = urlQuote( nick )
        args = dict(
            auid=auid, nick=quoted_nick, fame=fame, fraction=fraction, locale=locale, sex=sex,
            hero_id=hero_id, hero_lvl=hero_lvl, hero_force=hero_force, hero_rating=hero_rating,
            action="update_game_data"
        )
        self.fetch(args, callback)

    def updatePartyDodge(self, auid, server, banEndTime, party_id, callback):
        args = dict(
            auid=auid, banEndTime=banEndTime, party_id=party_id,
            action="party", cmd="party_dodge", server=server
        )
        self.fetch(args, callback)

        
    def unsubscribe(self, auid, server, callback):
        args = dict(
            auid=auid, server=server,
            action="unsubscribe"
        )
        self.fetch(args, callback)
        
    def sendPartyCmd(self, auid, server, command, callback, **kwargs):
        args = dict(
            auid=auid, server=server, cmd=command, 
            action="party",
            **kwargs
        )
        self.fetch(args, callback)

    def sendTamburCmd(self, auid, server, command, callback, **kwargs):
        args = dict(
            auid=auid, server=server, cmd=command, 
            action="tambur",
            **kwargs
        )
        self.fetch(args, callback)
        
    def inCastle(self, auid, on, callback=None):
        args = dict(
            auid=auid, on=toint(on),
            action="in_castle",
        )
        self.fetch(args, callback)

    def afk(self, auid, callback=None):
        args = dict(
            auid=auid, action="afk",
        )
        self.fetch(args, callback)

    def mute(self, auid, status, callback=None):
        args = dict(
            auid=auid, isMuted=status, action="mute",
        )
        self.fetch(args, callback)

    # ----------------------------------------------------------------------------------
    # для удобства сразу распарсим HTTP-ответ до response:{}
    def fetch( self, args_dict, callback, subrequest="x" ):
        response = self.HTTP( args_dict )
        if callback:
            callback( response )
            


##---------------------------------------------------------------------------------------------
##---------------------------------------------------------------------------------------------

class IHttpPersonServer( IPersonServer ):
    """ настоящий интерфейс: поддерживает запросы по HTTP """
    def __init__(self, address, HTTP=None):
        self.address = http_prefix( address )
        self.HTTP = HTTP
        
    # ----------------------------------------------------------------------------------
    def subscribe(self, auid, snid, snuid, uid, nick, photo, fame, fraction, sex, server, locale, callback):
        quoted_photo = urlQuote( photo or "" ) # от всяких пробелов http-шечке будет худо, так что quote
        quoted_nick = urlQuote( nick or CC.NICK_EMPTY )
        cmd = "%s/x?action=subscribe&auid=%s&snid=%s&snuid=%s&uid=%s&nick=%s&photo=%s&fame=%d&fraction=%s&sex=%s&server=%s&locale=%s" \
            % (self.address, auid, snid, snuid, uid, quoted_nick, quoted_photo, fame, fraction, sex, server, locale)
        self.fetch(cmd, callback)

    def updateGameData(self, auid, nick, fame, fraction, locale, hero_id, hero_lvl, hero_force, hero_rating, sex, callback):
        quoted_nick = urllib.quote( nick or CC.NICK_EMPTY ) # пустой ник посылать бессмысленно, аггрегатор не поставит property
        cmd = "%s/x?action=update_game_data&auid=%s&nick=%s&fame=%d&fraction=%s&locale=%s&hero_id=%d&hero_lvl=%d&hero_force=%d&hero_rating=%d&sex=%d" \
            % (self.address, auid, quoted_nick, fame, fraction, locale, hero_id, hero_lvl, hero_force, hero_rating, sex)
        self.fetch(cmd, callback)

    def updatePartyDodge(self, auid, server, banEndTime, party_id, callback):
        cmd = "%s/x?action=party&cmd=party_dodge&auid=%s&server=%s&banEndTime=%r&party_id=%s" % (self.address, auid, server, banEndTime, party_id)
        self.fetch(cmd, callback)
        
    def unsubscribe(self, auid, server, callback):
        cmd = "%s/x?action=unsubscribe&auid=%s&server=%s" % (self.address, auid, server)
        self.fetch(cmd, callback)
        
    def sendPartyCmd(self, auid, server, command, callback, **kwargs):
        additional_param_string = makeParamString(kwargs)
        cmd = "%s/x?action=party&auid=%s&server=%s&cmd=%s%s" % (self.address, auid, server, command, additional_param_string)
        self.fetch(cmd, callback)

    def sendTamburCmd(self, auid, server, command, callback, **kwargs):
        additional_param_string = makeParamString(kwargs)
        cmd = "%s/x?action=tambur&auid=%s&server=%s&cmd=%s%s" % (self.address, auid, server, command, additional_param_string)
        self.fetch(cmd, callback)
        
    def addFriend(self, auid, friend_auid, callback, **kwargs):
        cmd = "%s/x?action=add_friend&auid=%s&friend_auid=%s" % (self.address, auid, friend_auid)
        self.fetch(cmd, callback)

    def deleteFriend(self, auid, friend_auid, callback, **kwargs):
        cmd = "%s/x?action=delete_friend&auid=%s&friend_auid=%s" % (self.address, auid, friend_auid)
        self.fetch(cmd, callback)

    def inCastle(self, auid, on, callback=None):
        cmd = "%s/x?action=in_castle&auid=%s&on=%s" % (self.address, auid, toint(on))
        self.fetch(cmd, callback)

    def afk(self, auid, callback=None):
        cmd = "%s/x?action=afk&auid=%s" % (self.address, auid)
        self.fetch(cmd, callback)

    def mute(self, auid, status, callback=None):
        cmd = "%s/x?action=mute&auid=%s&isMuted=%s" % (self.address, auid, toint(status))
        self.fetch(cmd, callback)

    def getAfterpartyId(self, auid, session_id, allies_keys, old_party_id, callback, **kwargs):
        cmd = "%s/x?action=get_afterparty_id&auid=%s&session_id=%s&allies_keys=%s&old_party_id=%s" % (self.address, auid, session_id, allies_keys,old_party_id)
        self.fetch(cmd, callback)

    def updatePartyLeaverInfo(self, auid, party_id, isLeaver, callback, **kwargs):
        cmd = "%s/x?action=update_party_leaver_info&auid=%s&party_id=%s&isLeaver=%s" % (self.address, auid, party_id, toint(isLeaver))
        self.fetch(cmd, callback)

    def updatePartyTournamentInfo(self, auid, party_id,  tournamentDynQuestId, dependedTournamentQuests, callback, **kwargs):
        cmd = "%s/x?action=update_party_tournament_info&auid=%s&party_id=%s&tournamentDynQuestId=%s&dependedTournamentQuests=%s" % (self.address, auid, party_id, tournamentDynQuestId, dependedTournamentQuests)
        self.fetch(cmd, callback)

    def updatePartyTalentSetInfo(self, auid, party_id,  activeTalentSet, callback, **kwargs):
        cmd = "%s/x?action=update_party_talentset_info&auid=%s&party_id=%s&activeTalentSet=%s" % (self.address, auid, party_id, activeTalentSet)
        self.fetch(cmd, callback)


    # ----------------------------------------------------------------------------------
    def fetch(self, request, callback):
        # HTTP-результат пусть падает в _onFetch, там мы его распарсим до response:{} 
        # (достало писать однотипные http_reply-обработчики)
        _callback = functools.partial( self._onFetch, callback=callback )
        try:
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
                json_reply = json_load_transform( unquote_body )
                if json_reply:
                    response = json_reply.get("response", {})
            else:
                warn( "BAD http reply: %s" % http_reply )
        except:
            catch()
            warn( "EXCEPTION on http reply: %s" % http_reply )
            
        if callback:
            callback( response )


# ---------------------------------------------------------------------------------------

class IScaledPersonServer( IHttpPersonServer ):
    """ новый интерфейс: раскидывает legacy запросы I.PS.method(...) между новыми friends_service и party_service """
    def __init__(self, address="", HTTP=None, PARTY=None, FRIENDS=None):
        IHttpPersonServer.__init__(self, address, HTTP)
        self.PARTY = PARTY
        self.FRIENDS = FRIENDS
        
    # ----------------------------------------------------------------------------------
    def subscribe(self, auid, snid, snuid, uid, nick, photo, fame, fraction, sex, server, locale, callback):
        self.FRIENDS.subscribe(auid, snid, snuid, uid, nick, photo, fame, fraction, sex, server, locale, callback)

    def updateGameData(self, auid, nick, fame, fraction, locale, hero_id, hero_lvl, hero_force, hero_rating, sex, callback):
        self.FRIENDS.updateGameData(auid, nick, fame, fraction, locale, hero_id, hero_lvl, hero_force, hero_rating, sex, callback)

    def unsubscribe(self, auid, server, callback):
        self.FRIENDS.unsubscribe(auid, server, callback)
        
    def inCastle(self, auid, on, callback=None):
        self.FRIENDS.inCastle(auid, on, callback)

    def afk(self, auid, callback=None):
        self.FRIENDS.afk(auid, callback)

    def mute(self, auid, status, callback=None):
        self.FRIENDS.mute(auid, status, callback)

    def addFriend(self, auid, friend_auid, callback):
        self.FRIENDS.addFriend(auid, friend_auid, callback)

    def deleteFriend(self, auid, friend_auid, callback):
        self.FRIENDS.deleteFriend(auid, friend_auid, callback)

    def sendPartyCmd(self, auid, server, command, callback, **kwargs):
        if command in ["party_invite", "party_accept", "party_decline", "party_progress", "party_choose_again"]:
            # часть команд сначала должна проходить через FriendService (посмотреть person status, party_id, добавить person_info..)
            self.FRIENDS.sendPartyCmd(auid, server, command, callback, **kwargs)
        else: # часть команд идет сразу на PartyService
            self.PARTY.sendPartyCmd(auid, server, command, callback, **kwargs)

    def updatePartyDodge(self, auid, server, banEndTime, party_id, callback):
        self.sendPartyCmd(auid, server, "party_dodge", callback, banEndTime=banEndTime, party_id=party_id)

    def sendTamburCmd(self, auid, server, command, callback, **kwargs):
        if command in ["tambur_add"]: 
            # часть команд сначала должна проходить через FriendService (добавить person_info..)
            self.FRIENDS.sendTamburCmd(auid, command, callback, server=server, **kwargs)
        else: # часть команд пойдет сразу на PartyService
            self.PARTY.sendTamburCmd(auid, command, callback, server=server, **kwargs)

    def getAfterpartyId(self, auid, session_id, allies_keys, old_party_id, callback, **kwargs):
        self.PARTY.getAfterpartyId(auid, session_id, allies_keys, old_party_id, callback, **kwargs)

    def updatePartyLeaverInfo(self, auid, party_id, isLeaver, callback, **kwargs):
        self.PARTY.updatePartyLeaverInfo(auid, party_id, isLeaver, callback, **kwargs)

    def updatePartyTournamentInfo(self, auid, party_id, tournamentDynQuestId, dependedTournamentQuests, callback, **kwargs):
        self.PARTY.updatePartyTournamentInfo(auid, party_id, tournamentDynQuestId, dependedTournamentQuests, callback, **kwargs)

    def updatePartyTalentSetInfo(self, auid, party_id, talentSetId, callback, **kwargs):
        self.PARTY.updatePartyTalentSetInfo(auid, party_id, talentSetId, callback, **kwargs)