# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ResetSiegesCounterRequest import *
from guild.GuildData import GuildData
from modeldata.change_applicator import ModelChangeApplicator

class Reset_sieges_counter( SubAction, ResetSiegesCounterRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "reset_sieges_counter"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.I.GS.resetSiegesCounter(self.acc, self.onResetLimits)
        self.response["ok"] = 1
        self.fin()


    @model_callback
    @action_timing
    def onResetLimits(self, response):
        if response:
            info("onResetLimits response: %s" % self.I.MD.pretty(response))
            GuildData_changes = response.get("GuildData") or []
            if GuildData_changes:
                try:
                    ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                except:
                    catch()

            self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
            if self.acc.pending_handler:
                self.acc.pending_handler()