# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.StartSiegeRequest import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from siege.SiegeData import SiegeData
import CC
from StatisticCore.ttypes import GuildInteractionType

class Start_siege( SubAction, StartSiegeRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "start_siege"

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

        if self.acc.db.guildAuid == self.arguments.guildAuid and self.acc.guilddata.GuildSuzerain.ShortInfo.GuildAuid == 0:
            self.errorResponse( EC.CANT_START_SIEGE_FOR_VASSAL_OR_SELF,  "Can't fight yourself" )
            return

        self.I.GS.tryAcceptVassalApplication(self.acc, self.arguments.guildAuid, self.onTryAcceptVassal)

    def onTryAcceptVassal(self, response):
        info("Start_siege.onTryAcceptVassal response %r" % response)
        if response:
            isOk = response.get("ok") or 0
            if isOk:
                self.I.STATS.addGuildInteraction(self.acc.db.guildAuid, self.arguments.guildAuid,
                                                 GuildInteractionType.Capture, 0, 0)
                self.ApplyUpdate(response)
                self.response["ok"] = 1
            else:
                self.response["error"] = response.get("error") or ""
                self.response["ec"] = response.get("ec") or 0
                if self.response["ec"] == EC.GUILD_YOU_MUST_START_SIEGE or self.response["ec"] == EC.GUILD_YOU_MUST_JOIN_SIEGE:
                    self.response["ec"] = 0
                    self.response["error"] = ""
                    self.I.GS.startSiege(self.acc, self.arguments.guildAuid, self.arguments.join, self.onStartSiege)
                    return
        self.fin()

    def ApplyUpdate(self, response):
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

    def onStartSiege(self, response):
        if response:
            isOk = response.get("ok") or 0
            if isOk:
                info("onStartSiege: ok")
                self.ApplyUpdate(response)
                self.response["ok"] = 1
                self.fin()
                return
            else:
                if "ec" and "error" in response:
                    self.errorResponse(response["ec"],  response["error"])
                else:
                    self.errorResponse("Can't start siege, bad response from server")
                return
        self.response["ok"] = 0
        self.fin()