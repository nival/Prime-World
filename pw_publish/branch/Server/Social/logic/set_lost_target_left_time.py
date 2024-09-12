# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetLostTargetLeftTimeRequest import *
from guild.GuildData import GuildData
from modeldata.change_applicator import ModelChangeApplicator


class Set_lost_target_left_time( SubAction, SetLostTargetLeftTimeRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "set_lost_target_left_time"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        self.I.DATA.find_one("guilds", "guilds", {"FullName": self.arguments.guildFullName}, callback=self.onGuildAuidFound)

    def onGuildAuidFound(self, response):
        info("onGuildAuidFound response: %r", response)
        if response and response["r"]:
            try:
                guildAuid = response["r"]["GuildAuid"]
                self.I.GS.setLostTargetLeftTime(self.acc, str(guildAuid), self.arguments.duration, self.onLeftTimeChanged)
                return
            except Exception:
                catch()

        self.errorResponse(EC.FIND_NICK_NO_AUID, "Can't find this guild")

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