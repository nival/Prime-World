#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from logic.requests.GuildAcceptRequest import GuildAcceptRequest

class Guild_accept( SubAction, GuildAcceptRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "guild_accept"

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        # existing user's guild check
        if not self.acc.db.guildAuid:
            self.acc.db.guildAuid = self.arguments.guild_auid

            for giId in self.acc.model.IncomingGuildInvites.keys():
                guildInvite = self.acc.model.getGuildInviteByID( giId )
                if guildInvite.guildAuid == self.arguments.guild_auid:
                    self.acc.model.IncomingGuildInvites.remove( guildInvite )

            bestHero = 0
            bestHeroRating = 0.0
            for heroId in self.acc.model.HeroesKeeper:
                hero = self.acc.model.getHeroByID( heroId )
                if hero.Rating > bestHeroRating:
                    bestHero = hero.PersistentId
                    bestHeroRating = hero.Rating

            self.I.GS.acceptGuild( self.acc, self.acc.snid, self.acc.snuid, self.acc.uid, options.server_id, self.acc.locale or cfg.MATCHMAKER_DEFAULT_LOCALE,
                                   bestHero, bestHeroRating, self.onAcceptGuild )
            self.response["ok"] = 1
            self.fin()
        else:
            self.response["callback"] = ["guild_accept"]
            self.errorResponse( EC.IN_GUILD,  "Can not accept invite, you already in guild, leave it first" )

    @model_callback
    @action_timing
    def onAcceptGuild(self, response):
        ec = EC.OK
        if response:
            isOk = response.get("ok") or 0
            if isOk:
                info("onAcceptGuild: ok, response: %s" % self.I.MD.pretty(response))
                SiegeData_changes = response.get("SiegeData") or []
                if SiegeData_changes:
                    try:
                        ModelChangeApplicator.apply(self.acc, "siegedata", SiegeData, SiegeData_changes)
                    except:
                        catch()
                GuildData_changes = response.get("GuildData") or []
                if GuildData_changes:
                    try:
                        ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                    except:
                        catch()

                    self.acc.model.write( self.acc.pending )
                    self.acc.pending.setPrefix( "guildAccept:" )
                    self.acc.model.setComment( "auto" )
                    for giId in self.acc.model.IncomingGuildInvites.keys():
                        guildInvite = self.acc.model.getGuildInviteByID(giId)
                        self.acc.model.IncomingGuildInvites.remove(guildInvite)

                self.I.WS.removeRecruitApplications(self.acc)

                self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
                self.acc.pending_events.append({"SiegeData": {"SiegeData": SiegeData_changes}})
                self.I.STATS.addGuildJoined(self.acc.auid, self.acc.db.guildAuid, self.acc.db.fraction,
                                            len(self.acc.guilddata.Members))
            else:
                ec = response.get("ec") or EC.OK
                info( "onAcceptGuild: failed, ec=%d" % ec )
                self.I.GS.unsubscribe( self.acc, options.server_id, None )
                self.acc.db.guildAuid = 0
        else:
            self.I.GS.unsubscribe( self.acc, options.server_id, None )
            self.acc.db.guildAuid = 0
        if self.acc.pending_handler:
            self.acc.pending_handler()

        self.acc.pending_events.append( {"callback": { "callback_ec": [ec], "callback": ["guild_accept"] }} )
