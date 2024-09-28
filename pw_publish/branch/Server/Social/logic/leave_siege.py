# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.LeaveSiegeRequest import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData

class Leave_siege( SubAction, LeaveSiegeRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "leave_siege"

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

        self.I.GS.leaveSiege(self.acc, self.arguments.guildAuid, self.onLeaveSiege)

    def onLeaveSiege(self, response):
        if response:
            isOk = response.get("ok") or 0
            if isOk:
                info("onLeaveSiege: ok")
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
                self.acc.model.write(self.acc.pending)

                self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
                self.acc.pending_events.append({"SiegeData": {"SiegeData": SiegeData_changes}})
                if self.acc.pending_handler:
                    self.acc.pending_handler()

                self.sendPendingEvents()
                self.response["ok"] = 1
                self.fin()
                return
            else:
                if "ec" and "error" in response:
                    self.errorResponse(response["ec"],  response["error"])
                    return
        self.errorResponse("Can't leave siege, bad response from server")