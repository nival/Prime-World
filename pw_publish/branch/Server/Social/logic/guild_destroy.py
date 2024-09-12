#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from logic.requests.GuildDestroyRequest import GuildDestroyRequest

class Guild_destroy(SubAction, GuildDestroyRequest):
    """action, который будет обрабатывать данный класс"""
    action = "guild_destroy"

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.I.GS.destroyGuild(self.acc, self.onDestroyGuild)
        return


    @model_callback
    @action_timing
    def onDestroyGuild(self, response):
        if response:
            if response.get("ok") == 1:
                info("onDestroyGuild response: %s", self.I.MD.pretty(response))
                GuildData_changes = response.get("GuildData") or []
                SiegeData_changes = response.get("SiegeData") or []
                if GuildData_changes:
                    try:
                        ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                    except:
                        catch()
                if SiegeData_changes:
                    try:
                        ModelChangeApplicator.apply(self.acc, "siegedata", SiegeData, SiegeData_changes)
                    except:
                        catch()
                self.I.GS.unsubscribe(self.acc, options.server_id, self.onDummyResponseCallback)
                self.I.STATS.addGuildDisbanded(self.acc.auid, self.acc.db.guildAuid, self.acc.db.fraction, 0)
                self.acc.db.guildAuid = 0
                self.acc.model.resetGuild(self.I, self.acc)
                self.acc.model.Resources.CWPoints_Player = 0

                self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
                self.acc.pending_events.append({"SiegeData": {"SiegeData": SiegeData_changes}})
                if self.acc.pending_handler:
                    self.acc.pending_handler()
                self.response["ok"] = 1
            else:
                if "ec" in response:
                    self.errorResponse(response["ec"], "Can't destroy guild")
                    return

        self.fin()

    def onDummyResponseCallback(self, response):
        pass

