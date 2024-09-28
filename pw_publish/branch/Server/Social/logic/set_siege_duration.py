# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetSiegeDurationRequest import *
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
from modeldata.change_applicator import ModelChangeApplicator

class Set_siege_duration( SubAction, SetSiegeDurationRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "set_siege_duration"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        self.I.GS.setSiegeDuration(self.acc, self.arguments.targetAuid, self.arguments.duration, self.onSetDuration)


    @model_callback
    @action_timing
    def onSetDuration(self, response):
        if response:
            info("onSetDuration response: %s" % self.I.MD.pretty(response))
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

            self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
            self.acc.pending_events.append({"SiegeData": {"SiegeData": SiegeData_changes}})
            if self.acc.pending_handler:
                self.acc.pending_handler()

        self.response["ok"] = 1
        self.fin()