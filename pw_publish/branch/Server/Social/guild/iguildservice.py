# -*- coding: utf-8 -*-

from base.helpers import *
import urllib
from binascii import crc32
from enums import *
from numbers import Integral

import collections, functools, CC, EC, ihttp
from subaction import SubAction

class IGuildService:
    def __init__(self, addresses=None, HTTP=None):
        pass

    def subscribe(self, *args):
        pass

    def unsubscribe(self, acc, server, callback):
        pass

    def createGuild(self, *args):
        pass

    def renameGuild(self, acc, fullname, shortname, callback):
        pass

    def checkGuildName(self, *args):
        pass

    def isGuildMember( self, *args ):
        pass

    def leaveGuild( self, *args ):
        pass

    def destroyGuild( self, *args ):
        pass

    def inviteToGuild( self, *args ):
        pass

    def acceptGuild( self, *args ):
        pass

    def promoteGuild( self, *args ):
        pass

    def demoteGuild( self, *args ):
        pass

    def changeGuildOwner( self, *args ):
        pass

    def kickGuild( self, *args ):
        pass

    def messageGuild( self, *args ):
        pass

    def changeHeroRating( self, *args ):
        pass

    def recalcRating( self, *args ):
        pass

    def recalcRank( self, *args ):
        pass

    def investInGiuld( self, *args ):
        pass

    def checkGuildExists( self, *args ):
        pass

    def addGuildTalent( self, *args ):
        pass

    def takeGuildTalent( self, *args ):
        pass

    def returnGuildTalent( self, *args ):
        pass

    def guildBankLimitsReset( self, *args ):
        pass

    def guildTalentInfoUpdate( self, *args ):
        pass

    def giveBackGuildTalent( self, *args ):
        pass

    def buyGuildShopItem(self, *args):
        pass

    def acceptVassal(self, *args):
        pass

    def inviteSuzerain(self, *args):
        pass

    def declineVassal(self, *args):
        pass

    def removeVassal(self, *args):
        pass
        
    def startSiege(self, *args):
        pass

    def leaveSiege(self, *args):
        pass

    def getGuildDataForMap(self, *args):
        pass

    def addSuzerain(self, *args):
        pass

    def getGuilDataFordMap(self, *args):
        pass

    def sendTribute(self, *args):
        pass

    def newSuzerainNotify(self, *args):
        pass

    def guildCwpointsSell(self, *args):
        pass

    def setGuildExperience(self, *args):
        pass

    def winSiege(self, *args):
        pass

    def hideRecommendedVassal(self, *args):
        pass

    def changeMemberRating(self, *args):
        pass

    def setSiegeDuration(self, *args):
        pass

    def setSiegeScore(self, *args):
        pass

    def updateVassalsAndSuzerainInfo(self, *args):
        pass

    def tryAcceptVassalApplication(self, *args):
        pass

    def clearSuzerainInvites(self, *args):
        pass

    def checkGuildSize(self, *args):
        pass

    def newRecruitNotification(self, *args):
        pass

    def acceptRecruit(self, *args):
        pass
    
    def rmRecruitNotification(self, *args):
        pass

    def renameRecruitNotification(self, *args):
        pass

    def addActiveBuff(self, *args):
        pass

    def updateGuildsRating(self, *args):
        pass

    def notifyGuildWarEventChanged(self, *args):
        pass


class GuildDataCollector(AllResponseCollector):
    """Collects guilds data responses from all guild_services
     and join them into a single list."""
    def addResponse(self, response, peer):
        self.data.extend({peer : response})


class IHttpGuildService( IGuildService ):
    def __init__(self, addresses=None, HTTP=None, request_limit=1000):
        self.addresses = addresses
        self.address_count = len(addresses)
        self.HTTP = ihttp.ILimitedAsyncHttpFetcher( HTTP, request_limit )

    def getPeer(self, acc):
        if self.address_count:
            if isinstance(acc, Integral):
                return self.addresses[ acc % self.address_count ]
            else:
                return self.addresses[ acc.db.guildAuid % self.address_count ]

    def do(self, acc, args, callback):
        peer_addr = self.getPeer( acc )
        _callback = functools.partial( self.onFetch, peer_addr=peer_addr, args=args, callback=callback )
        self.HTTP.fetch( peer_addr, args, _callback )

    def onFetchPeer(self, response, peer_addr, args, data,  collector):
        info("IGuildService.onFetchPeer response (peer_addr=%s, args=%s):\n%s", peer_addr, args, str(response)[:128])
        debug("IGuildService.onFetchPeer response: %r", data)
        collector.onResponse(response, peer_addr)

    def doPostAll(self, args, _data, _collector, logMsg=""):
        for peer in self.addresses:
            if logMsg:
                info(logMsg, peer, args)
            _callback = functools.partial( self.onFetchPeer, peer_addr=peer, args=args, data=_data, collector=_collector)
            self.HTTP.post( peer, args, json_dumps(_data), _callback )

    def doPost(self, acc, args, data, callback):
        peer_addr = self.getPeer( acc )
        _callback = functools.partial( self.onFetch, peer_addr=peer_addr, args=args, callback=callback )
        self.HTTP.post( peer_addr, args, json_dumps(data), _callback )

    def onFetch(self, response, peer_addr="", args={}, callback=None):
        info("IHttpGuildService response (peer_addr=%r, args=%r):\n%r", peer_addr, args, str(response)[:128])
        debug("IHttpGuildService response=%r", response)
        if callback:
            callback(response)

    def subscribe( self, acc, snid, snuid, uid, server, locale, callback ):
        if acc.db.guildAuid:
            args = dict( action="subscribe", auid=acc.auid, snid=snid, snuid=snuid, uid=uid, server=server, locale=locale, guildAuid=acc.db.guildAuid, oldAuid=acc.db.oldAuid )
            info("subscribeToGuildService: args=%r", args )
            self.do( acc, args, callback )

    def unsubscribe( self, acc, server, callback ):
        if acc.db.guildAuid:
            args = dict( action="unsubscribe", auid=acc.auid, server=server, guildAuid=acc.db.guildAuid )
            info("unsubscribeToGuildService: args=%r", args )
            self.do( acc, args, callback )

    def createGuild( self, acc, snid, snuid, uid, server, locale, fullname, shortname, bestHero, bestHeroRating, callback ):
        if acc.db.guildAuid:
            args = dict( action="create_guild", auid=acc.auid, snid=snid, snuid=snuid, uid=uid, server=server,
                         locale=locale, fullname=urllib.quote(fullname), shortname=urllib.quote(shortname),
                         bestHero=bestHero, bestHeroRating=bestHeroRating, guildAuid=acc.db.guildAuid, guildFraction=acc.db.fraction)
            info("createGuild: args=%r" % args )
            self.do( acc, args, callback )

    def renameGuild( self, acc, fullname, shortname, callback ):
        if acc.db.guildAuid:
            args = dict( action="rename_guild", auid=acc.auid, fullname=fullname, shortname=shortname )
            info("renameGuild: args=%r" % args )
            self.do( acc, args, callback )

    def checkGuildName( self, acc, fullname, shortname, callback ):
        args = dict( action="check_guild_name", auid=acc.auid, fullname=urllib.quote(fullname), shortname=urllib.quote(shortname) )
        info("checkGuildName: args=%r" % args )
        self.do( acc, args, callback )

    def isGuildMember( self, acc, personAuid, guildAuid, callback ):
        args = dict( action="is_guild_member", auid=acc.auid, personAuid=personAuid, guildAuid=guildAuid )
        info("isGuildMember: args=%r" % args )
        self.do( acc, args, callback )

    def leaveGuild( self, acc, callback ):
        if acc.db.guildAuid:
            args = dict( action="leave_guild", auid=acc.auid )
            info("leaveGuild: args=%r" % args )
            self.do( acc, args, callback )

    def destroyGuild( self, acc, callback ):
        if acc.db.guildAuid:
            args = dict( action="destroy_guild", auid=acc.auid )
            info("destroyGuild: args=%r" % args )
            self.do( acc, args, callback )

    def inviteToGuild( self, acc, callback ):
        if acc.db.guildAuid:
            args = dict( action="invite_guild", auid=acc.auid )
            info("inviteToGuild: args=%r" % args )
            self.do( acc, args, callback )

    def acceptGuild( self, acc, snid, snuid, uid, server, locale, bestHero, bestHeroRating, callback):
        if acc.db.guildAuid:
            args = dict( action="accept_guild", auid=acc.auid, snid=snid, snuid=snuid, uid=uid, server=server, locale=locale,
                         bestHero=bestHero, bestHeroRating=bestHeroRating, guildAuid=acc.db.guildAuid )
            info("acceptGuild: args=%r" % args )
            self.do( acc, args, callback )

    def promoteGuild( self, acc, personAuid, callback ):
        if acc.db.guildAuid:
            args = dict( action="promote_guild", auid=acc.auid, personAuid=personAuid )
            info("promoteGuild: args=%r" % args )
            self.do( acc, args, callback )

    def demoteGuild( self, acc, personAuid, callback ):
        if acc.db.guildAuid:
            args = dict( action="demote_guild", auid=acc.auid, personAuid=personAuid )
            info("demoteGuild: args=%r" % args )
            self.do( acc, args, callback )

    def changeGuildOwner( self, acc, personAuid, callback ):
        if acc.db.guildAuid:
            args = dict( action="change_guild_owner", auid=acc.auid, personAuid=personAuid )
            info("changeGuildOwner: args=%r" % args )
            self.do( acc, args, callback )

    def kickGuild( self, acc, personAuid, callback ):
        if acc.db.guildAuid:
            args = dict( action="kick_guild", auid=acc.auid, personAuid=personAuid )
            info("kickGuild: args=%r" % args )
            self.do( acc, args, callback )

    def removeGuildMember( self, acc, guildAuid, memberAuid, callback ):
        args = dict( action="remove_guild_member", auid=acc.auid, guildAuid=guildAuid, memberAuid=memberAuid )
        info("removeGuildMember: args=%r" % args )
        self.do( acc, args, callback )

    def messageGuild( self, acc, message, callback ):
        if acc.db.guildAuid:
            args = dict( action="msg_guild", auid=acc.auid, message=urllib.quote(message) )
            info("messageGuild: args=%r" % args )
            self.do( acc, args, callback )

    def changeHeroRating( self, acc, rating, bestHero, bestHeroRating, callback ):
        if acc.db.guildAuid:
            args = dict( action="hero_rating", auid=acc.auid, rating=rating, bestHero=bestHero, bestHeroRating=bestHeroRating )
            info("changeHeroRating: args=%r" % args )
            self.do( acc, args, callback )

    def changeMemberRating(self, acc, rating, callback):
        if acc.db.guildAuid:
            args = dict(action="change_member_rating", auid=acc.auid, rating=rating)
            info("changeMemberRating: args=%r" % args)
            self.do(acc, args, callback)

    def recalcRating( self, guildAuid, gw_event_id, callback ):
        args = dict( action="recalc_rating", guildAuid=guildAuid, gw_event_id=gw_event_id )
        info("recalcRating: args=%r" % args )
        self.do( guildAuid, args, callback )

    def recalcRank( self, guildData, callback ):
        guildRank, guildAuid, guildRating = guildData
        args = dict( action="recalc_rank", guildAuid=guildAuid, guildRank=guildRank )
        info("recalcRank: args=%r" % args )
        self.do( guildAuid, args, callback )

    def clearSuzerainInvites( self, guildAuid, callback ):
        args = dict( action="clear_suzerain_invites", guildAuid=guildAuid )
        info("clearSuzerainInvites: args=%r" % args )
        self.do( guildAuid, args, callback )

    def investInGuild( self, acc, amount, callback ):
        args = dict( action="invest_in_guild", auid=acc.auid, amount=amount )
        info("investInGuild: args=%r" % args )
        self.do( acc, args, callback )

    def checkGuildExists( self, acc, guildAuid, inviteId, callback ):
        args = dict( action="check_guild_exists", auid=acc.auid, guildAuid = guildAuid, inviteId = inviteId )
        info("checkGuildExists: args=%r" % args )
        self.do( acc, args, callback )

    def addGuildTalent( self, acc, heroClassId, points, persistentId, callback ):
        if acc.db.guildAuid:
            args = dict( action="add_guild_talent", auid=acc.auid, heroClassId=heroClassId, points=points, persistentId=persistentId )
            info("addGuildTalent: args=%r" % args )
            self.do( acc, args, callback )

    def takeGuildTalent( self, acc, talId, callback ):
        if acc.db.guildAuid:
            args = dict( action="take_guild_talent", auid=acc.auid, talId=talId )
            info("takeGuildTalent: args=%r" % args )
            self.do( acc, args, callback )

    def returnGuildTalent( self, acc, talId, callback ):
        if acc.db.guildAuid:
            args = dict( action="return_guild_talent", auid=acc.auid, talId=talId )
            info("returnGuildTalent: args=%r" % args )
            self.do( acc, args, callback )

    def guildTalentInfoUpdate( self, acc, guildTalId, points, heroClassId, callback ):
        if acc.db.guildAuid:
            args = dict( action="guild_talent_info_update", auid=acc.auid, guildTalId=guildTalId, points=points, heroClassId=heroClassId )
            info("guildBankLimitsReset: args=%r" % args )
            self.do( acc, args, callback )

    def giveBackGuildTalent( self, acc, talId, callback ):
        if acc.db.guildAuid:
            args = dict( action="give_back_guild_talent", auid=acc.auid, talId=talId )
            info("giveBackGuildTalent: args=%r" % args )
            self.do( acc, args, callback )

    def buyGuildShopItem( self, acc, guildShopItemId, callback ):
        if acc.db.guildAuid:
            args = dict( action="buy_guild_shop_item", auid=acc.auid, guildShopItemId=guildShopItemId )
            info("buyGuildShopItem: args=%r" % args )
            self.do( acc, args, callback )

    def tryAcceptVassalApplication(self, acc, candidateGuildAuid,  callback):
        if acc.db.guildAuid:
            args = dict( action="accept_vassal", auid=acc.auid, candidateGuildAuid=candidateGuildAuid)
            info("tryAcceptVassalApplication: args=%r" % args )
            self.do( acc, args, callback )

    def inviteSuzerain(self, acc, gId,  callback):
        if acc.db.guildAuid:
            args = dict( action="invite_suzerain", auid=acc.auid, guildId=gId)
            info("inviteSuzerain: args=%r" % args )
            self.do( acc, args, callback )

    def declineVassal(self, acc, gId,  callback):
        if acc.db.guildAuid:
            args = dict( action="decline_vassal", auid=acc.auid, guildId=gId)
            info("declineVassal: args=%r" % args )
            self.do( acc, args, callback )

    def startSiege(self, acc, guildAuid, join, callback):
        if acc.db.guildAuid:
            args = dict(action="start_siege", auid=acc.auid, join=join, targetAuid=guildAuid)
            info("startSiege: args=%r" % args)
            self.do(acc, args, callback)

    def leaveSiege(self, acc, guildAuid, callback):
        if acc.db.guildAuid:
            args = dict(action="leave_siege", auid=acc.auid, targetAuid=guildAuid)
            info("leaveSiege: args=%r" % args)
            self.do(acc, args, callback)

    def getGuildDataForMap(self, acc, guildAuid, callback):
        if acc.db.guildAuid:
            args = dict(action="get_guilddata_for_map", auid=acc.auid, guildAuid=guildAuid)
            info("getGuildDataForMap: args=%r" % args)
            self.do(acc, args, callback)

    def removeVassal(self, acc, guildAuid, callback):
        if acc.db.guildAuid:
            args = dict(action="remove_vassal", auid=acc.auid, targetAuid=guildAuid, notifyVassal=True)
            info("removeVassal: args=%r" % args )
            self.do( acc, args, callback )

    def updateSiege(self, guildAuid, siegeInfo, callback):
        info("updateSiege: guildAuid=%s, siegeInfo=%s" % (guildAuid, siegeInfo) )
        self.doPost(guildAuid, dict(action="update_siege", guildAuid=guildAuid), dict(siegeInfo=siegeInfo), callback)

    def sendTribute(self, vGuildAuid, sGuildAuid, mess, callback ):
        args = dict( action="send_tribute", vassalGuildAuid=vGuildAuid, suzerainGuildAuid=sGuildAuid, message=mess)
        info("sendTribute: args=%r" % args )
        self.do( sGuildAuid, args, callback )

    def newSuzerainNotify(self, fGuildAuid, tGuildAuid, mess, callback):
        args = dict( action="new_suzerain_notify", fromGuildAuid=fGuildAuid, toGuildAuid=tGuildAuid, message=mess)
        info("newSuzerainNotify: args=%r" % args )
        self.do( tGuildAuid, args, callback )

    def newRecommendedVassalNotify(self, fGuildAuid, tGuildAuid, mess, callback):
        args = dict( action="new_recommended_vassal_notify", fromGuildAuid=fGuildAuid, toGuildAuid=tGuildAuid, message=mess)
        info("newRecommendedVassalNotify: args=%r" % args )
        self.do( tGuildAuid, args, callback )

    def getGuilDataFordMap(self, acc, guildAuid, callback):
        if acc.db.guildAuid:
            args = dict( action="get_guilddata_for_map", auid=acc.auid, guildAuid=guildAuid )
            info("getGuilDataFordMap: args=%r" % args )
            self.do( acc, args, callback )

    def winSiege(self, guildAuid, siegeId, callback):
        args = dict(action="win_siege", guildAuid=guildAuid, siegeId=siegeId)
        info("siegeWin: args=%r" % args )
        self.do(guildAuid, args, callback)

    def hideRecommendedVassal(self, acc, guildAuid, callback):
        if acc.db.guildAuid:
            args = dict( action="hide_recommended_vassal", auid=acc.auid, guildAuid=guildAuid)
            info("hideRecommendedVassal: args=%r" % args )
            self.do(acc, args, callback)

    def resetSiegesCounter(self, acc, callback):
        if acc.db.guildAuid:
            args = dict( action="reset_sieges_counter", auid=acc.auid)
            info("resetSiegesCounter: args=%r" % args)
            self.do(acc, args, callback)

    def removeSuzerain(self, acc, suzerainAuid, callback):
        if acc.db.guildAuid:
            args = dict(action="remove_vassal", auid=CC.GUILD_NEUTRAL_AUID, targetAuid=acc.db.guildAuid, toGuildAuid=suzerainAuid, notifyVassal=True)
            info("removeSuzerain: args=%r" % args )
            self.do(suzerainAuid, args, callback)

    def addVassal(self, acc, targetAuid, callback):
        args = dict( action="add_vassal", auid=acc.auid, targetAuid=targetAuid)
        info("addVassal: args=%r" % args)
        self.do(acc, args, callback)

    def updateVassalsAndSuzerainInfo(self, targetAuid, callback):
        args = dict( action="update_vassals_and_suzerain_info", guildAuid=targetAuid)
        info("updateVassalsAndSuzerainInfo: args=%r" % args)
        self.do(targetAuid, args, callback)

    def recruitmentLocale(self, acc, locale, callback):
        if acc.db.guildAuid:
            args = dict(action="recruitment_locale", auid=acc.auid, locale=urllib.quote(locale))
            info("recruitmentLocale: args=%r" % args)
            self.do(acc, args, callback)

    def recruitmentMessage(self, acc, message, callback):
        if acc.db.guildAuid:
            args = dict(action="recruitment_message", auid=acc.auid, message=urllib.quote(message))
            info("recruitmentMessage: args=%r" % args)
            self.do(acc, args, callback)

    def recruitmentRating(self, acc, rating, callback):
        if acc.db.guildAuid:
            args = dict(action="recruitment_rating", auid=acc.auid, rating=rating)
            info("recruitmentRating: args=%r" % args)
            self.do(acc, args, callback)

    def getRecruitsList(self, acc, position, sortCriteria, order, callback):
        if acc.db.guildAuid:
            args = dict(action="get_recruits_list", auid=acc.auid, position=position, sortCriteria=sortCriteria, order=order)
            info("getRecruitsList: args=%r" % args)
            self.do(acc, args, callback)

    def checkGuildSize(self, guildAuid, callback):
        info("checkGuildSize: guildAuid=%s", guildAuid)
        self.do(guildAuid, dict(action="check_guild_size", guildAuid=guildAuid), callback)

    def newRecruitNotification(self, auid, guildAuid, callback=None):
        info("newRecruitNotification: auid=%s, guildAuid=%s", auid, guildAuid)
        self.do(guildAuid, dict(action="new_recruit", auid=auid, guildAuid=guildAuid), callback)

    def rmRecruitNotification(self, auid, guildAuid, callback=None):
        info("rmRecruitNotification: auid=%s, guildAuid=%s", auid, guildAuid)
        self.do(guildAuid, dict(action="rm_recruit", auid=auid, guildAuid=guildAuid), callback)

    def renameRecruitNotification(self, auid, nick, guildAuid, callback=None):
        info("renameRecruitNotification: %s(%s) -> %s", auid, nick, guildAuid)
        self.do(guildAuid, dict(action="rename_recruit", auid=auid, nick=nick, guildAuid=guildAuid), callback)

    def declineRecruit(self, acc, recruitAuid, callback=None):
        if acc.db.guildAuid:
            args = dict(action="decline_recruit", auid=acc.auid, recruitAuid=recruitAuid)
            info("declineRecruit: args=%r" % args)
            self.do(acc, args, callback)

    def acceptRecruit(self, auid, guildAuid, target_auid, callback):
        info("acceptRecruit: auid=%s, guildAuid=%s, target_auid=%s", auid, guildAuid, target_auid)
        self.do(guildAuid, dict(action="accept_recruit", auid=auid, guildAuid=guildAuid, recruit_auid=target_auid), callback)

    def updateGuildsRating(self, data, callback):
        info("updateGuildsRating: data=%s", data )
        self.doPostAll(dict(action="update_guilds_rating"), data, GuildDataCollector(self.address_count, callback),"Send guild ratings dict to GuildService  %s: args=%r")

    def notifyGuildWarEventChanged(self, guild_auids, event_id, callback):
        data = []
        if guild_auids:
            data.extend(guild_auids)
        args = dict(action="on_guild_war_event_changed", event_id=event_id)
        info("notifyGuildWarEventChanged: args=%r" % args )
        self.doPostAll(args, data, GuildDataCollector(self.address_count, callback),
                       "Send guild ratings dict to GuildService  %s: args=%r")

#   DEBUG ACTIONS

    def setSiegeDuration(self, acc, targetAuid, duration, callback):
        if acc.db.guildAuid:
            args = dict(action="set_siege_duration", auid=acc.auid, targetAuid=targetAuid, duration=duration)
            info("setSiegeDuration: args=%r" % args)
            self.do(acc, args, callback)

    def setSiegeScore(self, acc, targetAuid, score, callback):
        if acc.db.guildAuid:
            args = dict(action="set_siege_score", auid=acc.auid, targetAuid=targetAuid, score=score)
            info("setSiegeScore: args=%r" % args)
            self.do(acc, args, callback)

    def debugUpdateSiege(self, guildAuid, siegeInfo, callback):
        info("debugUpdateSiege: guildAuid=%s, siegeInfo=%s" % (guildAuid, siegeInfo) )
        self.doPost(guildAuid, dict(action="debug_update_siege", guildAuid=guildAuid), dict(siegeInfo=siegeInfo), callback)

    def resetGuildShopItems(self, acc, callback):
        if acc.db.guildAuid:
            args = dict(action="reset_guild_shop_limits", auid=acc.auid)
            info("resetGuildShopItems: args=%r" % args)
            self.do(acc, args, callback)

    def guildBankLimitsReset( self, acc, callback ):
        if acc.db.guildAuid:
            args = dict(action="guild_bank_limits_reset", auid=acc.auid)
            info("guildBankLimitsReset: args=%r" % args)
            self.do(acc, args, callback)

    def guildCwpointsSell(self, acc, CWPoints_Clan,callback):
        if acc.db.guildAuid:
            args = dict(action="guild_cwpoints_sell", auid=acc.auid, cwPoints=CWPoints_Clan)
            info("guildCwpointsSell: args=%r " % args)
            self.do(acc, args, callback)

    def setGuildExperience(self, acc, value, callback):
        if acc.db.guildAuid:
            args = dict( action="set_guild_experience", auid=acc.auid, value=value )
            info("setGuildExperience: args=%r" % args )
            self.do( acc, args, callback )

    def setGuildTodayRating(self, acc, value, callback):
        if acc.db.guildAuid:
            args = dict( action="set_guild_today_rating", auid=acc.auid, value=value )
            info("setGuildTodayRating: args=%r" % args )
            self.do(acc, args, callback)

    def setExVassalLeftTime(self, acc, guildAuid, value, callback):
        if acc.db.guildAuid:
            args = dict( action="set_ex_vassal_left_time", auid=acc.auid, guildAuid=guildAuid, value=value )
            info("setExVassalLeftTime: args=%r" % args )
            self.do(acc, args, callback)

    def setLostTargetLeftTime(self, acc, guildAuid, value, callback):
        if acc.db.guildAuid:
            args = dict( action="set_lost_target_left_time", auid=acc.auid, guildAuid=guildAuid, value=value )
            info("setLostTargetLeftTime: args=%r" % args )
            self.do(acc, args, callback)

    def updateRecruitApplication(self, auid, guildAuid, created, callback=None):
        info("updateRecruitApplication: auid=%s, guildAuid=%s, created=%s", auid, guildAuid, created)
        self.do(guildAuid, dict(action="update_recruit_application", auid=auid, guildAuid=guildAuid, created=created,), callback)

    def addActiveBuff(self, acc, buffId, callback):
        if acc.db.guildAuid:
            args = dict( action="add_active_buff", auid=acc.auid, buffId=buffId )
            info("addActiveBuff: args=%r" % args )
            self.do(acc, args, callback)




from modeldata.changes import PendingChangeWriter, GroupPendingChangeWriter, MakeModelChangeString
class IDummyGuildService( IGuildService ):

    def createGuild( self, acc, snid, snuid, uid, server, locale, fullname, shortname, bestHero, bestHeroRating, callback ):
        self._fin(callback)

    def checkGuildExists( self, acc, guildAuid, inviteId, callback ):
        response = {}
        response["inviteId"] = inviteId
        response["exists"] = False
        self._fin(callback, response)

    def checkGuildName( self, acc, fullname, shortname, callback ):
        response = {}
        response["unique"] = True
        self._fin(callback, response)

    def destroyGuild( self, acc, callback ):
        self._fin(callback)

    def renameGuild( self, acc, fullname, shortname, callback ):
        self._fin(callback)

    def leaveGuild( self, acc, callback  ):
        self._fin(callback)

    def investInGuild( self, acc, amount, callback  ):
        self._fin(callback)

    def changeHeroRating( self, acc, rating, bestHero, bestHeroRating, callback ):
        self._fin(callback)

    def addGuildTalent( self, acc, heroClassId, points, persistentId, callback ):
        self._fin(callback)

    def takeGuildTalent( self, acc, talId, callback ):
        acc.guilddata
        talent = acc.guilddata.getGuildTalentByID( talId )
        response = {}
        if talent:
            response["PersistentId"] = talent.PersistentId
            response["Points"] = talent.Points
            response["GuildBankInfo.HeroClassId"] = talent.HeroClassId
            response["GuildBankInfo.GuildAuid"] = acc.guilddata.GuildAuid
            response["GuildBankInfo.GuildTalentId"] = 1
            response["OwnerId"] = talId
        self._fin(callback, response)

    def returnGuildTalent( self, acc, talId, callback ):
        acc.guilddata
        talent = acc.guilddata.getGuildTalentByID( talId )
        response = {}
        if talent:
            acc.guilddata.FreeTalents.add( talent )
            acc.guilddata.TakenTalents.remove( talent )
        self._fin(callback, response)

    def guildBankLimitsReset( self, acc, callback ):
        self._fin(callback)

    def guildTalentInfoUpdate( self, acc, guildTalId, points, heroClassId, callback ):
        self._fin(callback)

    def giveBackGuildTalent( self, acc, talId, callback ):
        self._fin(callback)

    def guildCwpointsSell( self, acc, CWPoints_Clan,callback ):
        self._fin(callback)

    def buyGuildShopItem( self, acc, shopItemId, callback ):
        response = {}
        # А есть ли у нас вообще такой товар?
        member = acc.guilddata.findMemberByAuid(acc.auid)
        if str(shopItemId) in acc.guilddata.GuildShopItems:
            staticItem = acc.SD.getGuildShopItemById(shopItemId)
            if staticItem:
                if acc.guilddata.GuildShopItems[str(shopItemId)] > 0:
                    # Если покупаем только для гильдии - то за очки гильдии и только советником или главой
                    if (staticItem['price']['CWPoints_Clan'] != 0 and member.IsOfficer) or staticItem['price']['CWPoints_Clan'] == 0:
                        if staticItem['price']['CWPoints_Clan'] != 0 and member.IsOfficer:
                            # Хватает ли у гильдии денег на покупку?
                            if acc.guilddata.GuildInfo.CWPoints_Clan >= staticItem['price']['CWPoints_Clan']:
                                acc.guilddata.GuildInfo.CWPoints_Clan -= staticItem['price']['CWPoints_Clan']
                            else:
                                response["error"] = "BuyGuildShopItemAction: not enough CWPoints_Clan, item_id=%r, " \
                                                    "available cw_points = %s" % (shopItemId, acc.guilddata.GuildInfo.CWPoints_Clan)
                                response["ec"] = EC.NOT_ENOUGH_RESOURCES
                                response["ok"] = 0
                                callback( response )
                                return

                        acc.guilddata.GuildShopItems[str(shopItemId)] -= 1
                        # Если тип товара бонус, надо раздать людям
                        if staticItem['classType'] == "OneTimeGuildShopItem":
                            affectedMembers, _ = acc.guilddata.getAffectedMembersList(acc.auid, [acc.auid], staticItem)
                            expTime = int(time.time()) + int(staticItem['guildBuff']['duration'])
                            if not acc.model.AddOneTimeGuildShopItem(acc, acc.SD, expTime, staticItem):
                                response["error"] = "BuyGuildShopItemAction: failed while buying item, id=%r" % staticItem['persistentId']
                                response["ec"] = EC.BAD_PARAM
                                response["ok"] = 0
                                callback( response )
                                return

                        changes = self.pickPendingChanges(acc)
                        response["GuildData"] = changes
                        response["ok"] = 1
                        self._fin(callback, response)
                        return
                    else:
                        response["error"] = "BuyGuildShopItemAction: non-officer member can't buy guild only items, id=%r" % shopItemId
                        response["ec"] = EC.GUILD_SHOP_CANNOT_BUY_GUILD_POINTS_ONLY_ITEM
                else:
                    response["error"] = "BuyGuildShopItemAction: Can't buy item - day limit exceeded"
                    response["ec"] = EC.GUILD_SHOP_ITEM_DAY_LIMIT_EXCEEDED
            else:
                response["error"] = "BuyGuildShopItemAction: can not find static shop item with id=%r" % shopItemId
        else:
            response["error"] = "BuyGuildShopItemAction: can not find shop item with id=%r" % shopItemId

        response["ok"] = 0
        callback(response)

    def acceptVassal(self, gId, callback):
        self._fin(callback)

    def inviteSuzerain(self, acc, gId, callback):
        self._fin(callback)

    def declineVassal(self, gId, callback):
        self._fin(callback)

    def newSuzerainNotify(self, fGuildAuid, tGuildAuid, mess, callback):
        self._fin(callback)

    def updateVassalsAndSuzerainInfo(self,  acc, targetAuid, callback):
        self._fin(callback)

    def clearSuzerainInvites( self, guildAuid, callback ):
        self._fin(callback)

    def pickPendingChanges(self, acc):
        response = {}
        SubAction.wrapPendingMessages( acc, None, response )
        acc.pending_changes = []

        changes = response.get("GuildData") or []
        SubAction.convertResponseObjects( changes )
        return changes

    def startSiege(self, acc, guildAuid, join, callback):
       self._fin(callback)

    def startUprising(self, acc, callback):
        self._fin(callback)

    def getGuildDataForMap(self, acc, guildAuid, callback):
        self._fin(callback)

    def finishCapture(self, acc, guildAuid, accept, callback):
        self._fin(callback)

    def removeVassal(self, acc, guildAuid, callback):
        self._fin(callback)

    def getGuilDataFordMap(self, acc, guildAuid, callback):
        self._fin(callback)

    def sendTribute(self, fGuildAuid, tGuildAuid, mess, callback):
        self._fin(callback)

    def checkGuildSize(self, guildAuid, callback):
        self._fin(callback, {"current": 0, "max": 0})

    def newRecruitNotification(self, auid, guildAuid, callback=None):
        self._fin(callback)

    def rmRecruitNotification(self, auid, guildAuid, callback=None):
    	self._fin(callback)

    def renameRecruitNotification(self, auid, nick, guildAuid, callback=None):
    	self._fin(callback)

    def acceptRecruit(self, auid, guildAuid, callback):
        self._fin(callback)

    def updateGuildsRating(self, data, callback):
        self._fin(callback)

    def notifyGuildWarEventChanged(self, guild_auids, event_id, callback):
        self._fin(callback)

    def _fin(self, callback, response = None,):
        #info("DummyGuildService response: %s" % response)
        if not response:
            response = {}
        response["ok"] = 1
        if callback:
            callback( response )

