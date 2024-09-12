# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from logic.requests.RemoveVassalRequest import *
from StatisticCore.ttypes import GuildInteractionType

class Remove_vassal( SubAction, RemoveVassalRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "remove_vassal"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if not self.acc.db.guildAuid:
            self.errorResponse( EC.NOT_IN_GUILD,  "You're not in guild" )
            return

        self.I.GS.removeVassal(self.acc, self.arguments.guildAuid, self.onRemoveVassal)

    @model_callback
    @action_timing
    def onRemoveVassal(self, response):
        if response:
            info("onRemoveVassal response: %s" % self.I.MD.pretty(response))
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
            self.I.STATS.addGuildInteraction(self.acc.db.guildAuid, self.arguments.guildAuid,
                GuildInteractionType.Revolt, 0, 0)
            self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
            if self.acc.pending_handler:
                self.acc.pending_handler()

            self.sendPendingEvents()
            self.response["ok"] = 1
        self.fin()