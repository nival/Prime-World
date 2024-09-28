# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.HideRecommendedVassalRequest import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData

class Hide_recommended_vassal(SubAction, HideRecommendedVassalRequest):
    """action, который будет обрабатывать данный класс"""
    action = "hide_recommended_vassal"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        # ACTION LOGIC
        if not self.acc.db.guildAuid:
            self.errorResponse(EC.NOT_IN_GUILD, "You're not in guild")
            return

        self.I.GS.hideRecommendedVassal(self.acc, self.arguments.guildAuid, self.onHideRecommendedVassal)

    def onHideRecommendedVassal(self, response):
        info("Hide_recommended_vassal.onHideRecommendedVassal response %r" % response)
        if response and response.get("ok"):
            info( "onRemoveVassal response: %s" % self.I.MD.pretty(response) )
            GuildData_changes = response.get("GuildData") or []
            if GuildData_changes:
                try:
                    ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, GuildData_changes )
                except:
                    catch()
            self.acc.pending_events.append( {"GuildData": { "GuildData": GuildData_changes }} )
            if self.acc.pending_handler:
                self.acc.pending_handler()

            self.response["ok"] = 1
        else:
            err("onHideRecommendedVassal: bad response")
            self.response["ok"] = 0
        self.fin()