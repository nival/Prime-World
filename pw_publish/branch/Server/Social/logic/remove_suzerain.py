# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveSuzerainRequest import *
from guild.GuildData import GuildData
from modeldata.change_applicator import ModelChangeApplicator
import CC

class Remove_suzerain(SubAction, RemoveSuzerainRequest):
    """action, который будет обрабатывать данный класс"""
    action = "remove_suzerain"
    debug = True

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

        if self.acc.guilddata.GuildSuzerain.ShortInfo.GuildAuid == 0 or self.acc.guilddata.GuildSuzerain.ShortInfo.GuildAuid == CC.NPC_SUZERAIN_AUID:
            self.response["ok"] = 1
            self.fin()
        else:
            self.I.GS.removeSuzerain(self.acc, self.acc.guilddata.GuildSuzerain.ShortInfo.GuildAuid, self.onRemoveSuzerain)


    @model_callback
    @action_timing
    def onRemoveSuzerain(self, response):
        if response:
            info("onRemoveSuzerain response: %s" % self.I.MD.pretty(response))
            GuildData_changes = response.get("GuildData") or []
            if GuildData_changes:
                try:
                    ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                except:
                    catch()

            self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
            if self.acc.pending_handler:
              self.acc.pending_handler()
        self.response["ok"] = 1
        self.fin()