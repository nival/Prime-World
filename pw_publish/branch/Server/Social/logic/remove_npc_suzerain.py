# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveNPCSuzerainRequest import *
from guild.GuildData import GuildData
from modeldata.change_applicator import ModelChangeApplicator
import CC

class Remove_npc_suzerain(SubAction, RemoveNPCSuzerainRequest):
    """action, который будет обрабатывать данный класс"""
    action = "remove_npc_suzerain"
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

        if self.acc.guilddata.GuildSuzerain.ShortInfo.GuildAuid == CC.NPC_SUZERAIN_AUID:
            args = dict(method="new_suzerain_notify", message={})
            self.I.SEX.sendToGuildService(0, self.acc.db.guildAuid, args, self.onRemoveSuzerain)
        else:
            self.response["ok"] = 1
            self.fin()


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