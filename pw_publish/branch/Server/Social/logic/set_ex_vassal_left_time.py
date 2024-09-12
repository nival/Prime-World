# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetExVassalEndTimeRequest import *
from guild.GuildData import GuildData
from modeldata.change_applicator import ModelChangeApplicator

class Set_ex_vassal_left_time( SubAction, SetExVassalEndTimeRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "set_ex_vassal_left_time"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.I.GS.setExVassalLeftTime(self.acc, str(self.arguments.guildAuid), self.arguments.duration, self.onLeftTimeChanged)

    def onLeftTimeChanged(self, response):
        info("onLeftTimeChanged response: %r", response)
        if response:
            isOk = response.get("ok") or 0
            if isOk:
                GuildData_changes = response.get("GuildData") or []
                if GuildData_changes:
                    try:
                        ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                    except Exception:
                        catch()

                self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
                if self.acc.pending_handler:
                    self.acc.pending_handler()
                self.sendPendingEvents()
                self.response["ok"] = 1
                self.fin()
                return

        else:
            self.errorResponse("Can't set left time")