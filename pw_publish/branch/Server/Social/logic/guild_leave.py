#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from tornado.options import options
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from logic.requests.GuildLeaveRequest import GuildLeaveRequest

class Guild_leave( SubAction, GuildLeaveRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "guild_leave"

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if not self.acc.db.guildAuid:
            self.errorResponse( EC.NOT_IN_GUILD,  "You're not in guild" )
            return

        self.I.GS.leaveGuild( self.acc, self.onLeaveGuild )
        return

    @model_callback
    @action_timing
    def onLeaveGuild( self, response ):
        if response:
            info("onLeaveGuild response: %s" % self.I.MD.pretty(response))
            if len( self.acc.guilddata.GuildMemberKeeper ) == 1:
                self.I.STATS.addGuildDisbanded(self.acc.auid, self.acc.db.guildAuid, self.acc.db.fraction, 0)
            self.I.STATS.addGuildLeaved(self.acc.auid, self.acc.db.guildAuid, self.acc.db.fraction, False,
                                         len(self.acc.guilddata.Members))
            GuildData_changes = response.get("GuildData") or []
            if GuildData_changes:
                try:
                    ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                except:
                    catch()
            SiegeData_changes = response.get("SiegeData") or []
            if SiegeData_changes:
                try:
                    ModelChangeApplicator.apply(self.acc, "siegedata", SiegeData, SiegeData_changes)
                except:
                    catch()

            self.acc.db.guildAuid = 0
            self.acc.model.resetGuild(self.I, self.acc)
            #почему это не поместить в resetGuild?! пока оставляю так же как в guild_destroy.py
            self.acc.model.Resources.CWPoints_Player = 0

            self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
            self.acc.pending_events.append({"SiegeData": {"SiegeData": SiegeData_changes}})
            if self.acc.pending_handler:
                self.acc.pending_handler()

            self.response["ok"] = 1
            self.fin()
