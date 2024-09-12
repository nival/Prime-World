#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys, time
from subaction import *
from tornado.options import options
sys.path.append('..')
sys.path.append('../cfg')
import cfg
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildWarEventData import GuildWarEventData
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from logic.requests.GuildCreateRequest import GuildCreateRequest
from ext_main.nickname import SetNicknameAction

class Guild_create( SubAction, GuildCreateRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "guild_create"

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if self.acc.db.guildAuid:
            self.response["callback"] = ["guild_create"]
            self.errorResponse(EC.IN_GUILD,  "Can not create guild, you already in guild, leave it first")
            return

        ( r, self.textFullName, encoding ) = SetNicknameAction.checkNickname( self.arguments.fullname,
                self.acc.getConfigValue("NICKNAME_REGEXES").keys(), self.acc.getConfigValue("ADMIN_NICKS").keys())
        if r != SetNicknameAction.CHECK_OK:
            warn( "Cannot rename guild for acc %r to %r" % ( self.acc.db.guildAuid, self.arguments.fullname ) )
            self.response["callback"] = ["guild_create"]
            self.errorResponse( EC.BAD_GUILD_FULL_NAME, self.textFullName )
            return

        ( r, self.textShortName, encoding ) = SetNicknameAction.checkNickname( self.arguments.shortname,
                self.acc.getConfigValue("NICKNAME_REGEXES").keys(), self.acc.getConfigValue("ADMIN_NICKS").keys(),
                2, 5 )
        if r != SetNicknameAction.CHECK_OK:
            warn( "Cannot rename guild for acc %r to %r" % ( self.acc.auid, self.arguments.shortname ) )
            self.response["callback"] = ["guild_create"]
            self.errorResponse( EC.BAD_GUILD_SHORT_NAME, self.textShortName)
            return

        self.textFullName = self.textFullName.encode( 'utf8' )
        self.textShortName = self.textShortName.encode( 'utf8' )
        self.I.GS.checkGuildName( self.acc, self.textFullName, self.textShortName, self.OnNameChecked )

    @action_timing
    def OnNameChecked(self, response):
        info("OnNameChecked response: %s", self.I.MD.pretty(response))
        code = response.get("unique", False)
        if code and code != "Short" and code != "Full":
            silver = int(self.acc.getConfigValue("GUILD_CREATE_PRICE_SILVER"))
            self.price = self.acc.model.createResourcesTable(Silver=silver)
            self.needGold = int(0)
            if self.price >= 0:
                reason = "PW!CREATE_GUILD:" + str(self.textFullName)
                self.buy( self.price, self.onBuy, self.onBuyFunc, reason)
                return None
            else:
                self.response["callback"] = ["guild_create"]
                self.errorResponse("Price is negative")
        elif code == "Short" or code == "Full":
            self.response["callback"] = ["guild_create"]
            if code == "Short":
                self.errorResponse(EC.GUILD_SHORTNAME_NOT_UNIQUE, "Guild shortname is not unique")
            elif code == "Full":
                self.errorResponse(EC.GUILD_FULLNAME_NOT_UNIQUE, "Guild fullname is not unique")
        else:
            err('OnNameChecked warn response [%r]', response)

    @model_callback
    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff( response )
            bestHero = 0
            bestHeroRating = 0.0
            for heroId in self.acc.model.HeroesKeeper:
                hero = self.acc.model.getHeroByID( heroId )
                if hero.Rating > bestHeroRating:
                    bestHero = hero.PersistentId
                    bestHeroRating = hero.Rating

            self.acc.db.guildAuid = self.I.WS.nextInt64GUID("guild_service")

            self.I.GS.createGuild( self.acc, self.acc.snid, self.acc.snuid, self.acc.uid, options.server_id, self.acc.locale or cfg.MATCHMAKER_DEFAULT_LOCALE,
                                   self.textFullName, self.textShortName, bestHero, bestHeroRating, self.onCreateGuild)

            self.response["ok"] = 1 # success
            self.fin()
        else:
          self.response["callback"] = ["guild_create"]
          self.onBuyError( response, self.needGold )

    @action_timing
    def onBuy( self, response ):
        self.onBuyFunc( response )

    def onNotifyGuildWarEventChangedReply(self, response):
        debug("onCreateGuild: notifyGuildWarEventChanged response %r", response)

    @model_callback
    @action_timing
    def onCreateGuild(self, response):
        if response and response["ok"] == 1:
            info("onCreateGuild response: %s" % self.I.MD.pretty(response))
            GuildData_response = response.get("GuildData")
            if GuildData_response is not None:
                self.acc.model.write( self.acc.pending )
                self.acc.pending.setPrefix( "guildCreate:" )
                self.acc.model.setComment( "auto" )
                for giId in self.acc.model.IncomingGuildInvites.keys():
                    guildInvite = self.acc.model.getGuildInviteByID( giId )
                    self.acc.model.IncomingGuildInvites.remove( guildInvite )

                self.I.WS.removeRecruitApplications(self.acc)

            GuildWarEventData_changes = self.I.WS.getGuildWarEventDataChanges()
            self.I.GS.notifyGuildWarEventChanged(guild_auids=[self.acc.db.guildAuid], event_id=self.I.WS.getGuildWarEventId(),
                                                 callback=self.onNotifyGuildWarEventChangedReply)

            GuildData_changes = GuildData_response or []
            if GuildData_changes:
              try:
                ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, GuildData_changes )
              except:
                catch()
            SiegeData_changes = response.get("SiegeData") or []
            if SiegeData_changes:
                try:
                    ModelChangeApplicator.apply(self.acc, "siegedata", SiegeData, SiegeData_changes)
                except:
                    catch()

            if GuildWarEventData_changes:
                try:
                    ModelChangeApplicator.apply(self.acc, "GuildWarEventData", GuildWarEventData, GuildWarEventData_changes)
                except:
                    catch()

            self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
            self.acc.pending_events.append({"SiegeData": {"SiegeData": SiegeData_changes}})
            self.acc.pending_events.append({"GuildWarEventData": {"GuildWarEventData": GuildWarEventData_changes}})
            self.acc.pending_events.append({"callback": {"callback": ["guild_create"]}})
            self.I.STATS.addGuildCreated( self.acc.auid, self.acc.db.guildAuid, self.acc.db.fraction, self.textShortName, self.textFullName, self.price, self.acc.model.Resources, 1 )
            if self.acc.pending_handler:
                self.acc.pending_handler()
        else:
            self.acc.model.sell( self.price, self.acc, False )
            self.acc.pending_events.append( { "ec": EC.DOUBLE_CREATE_GUILD } )
            self.acc.pending_events.append( { "error": "Double create guild" } )
            self.acc.pending_events.append( {"callback": { "callback": ["guild_create"] }} )
            if self.acc.pending_handler:
                self.acc.pending_handler()
