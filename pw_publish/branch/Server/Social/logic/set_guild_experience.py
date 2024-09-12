# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetGuildExperienceRequest import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData

class Set_guild_experience( SubAction, SetGuildExperienceRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "set_guild_experience"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.I.GS.setGuildExperience(self.acc, self.arguments.value, self.onGuildExperienceSet)

    def onGuildExperienceSet( self, response ):
        if response:
            info( "setGuildExperience response: %s" % self.I.MD.pretty(response) )
            GuildData_changes = response.get("GuildData") or []
            if GuildData_changes:
                try:
                    ModelChangeApplicator.apply( self.acc, "guilddata", GuildData, GuildData_changes )
                except:
                    catch()

            self.acc.pending_events.append( {"GuildData": { "GuildData": GuildData_changes }} )
            if self.acc.pending_handler:
                self.acc.pending_handler()
            self.sendPendingEvents()

        self.response["ok"] = 1
        self.fin()