# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddVassalRequest import *
from guild.GuildData import GuildData
from modeldata.change_applicator import ModelChangeApplicator

class Add_vassal( SubAction, AddVassalRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "add_vassal"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if len(self.acc.guilddata.GuildVassals) >= self.acc.getConfig().GUILD_MAX_VASSAL_SIZE:
            self.errorResponse("Can't add more vassals")
            return

        for vassalId, vassal in self.acc.guilddata.GuildVassals.iteritems():
            if vassal.ShortInfo.GuildFullName == self.arguments.guildFullName:
                self.errorResponse("You already have this vassal")
                return

        self.I.DATA.find_one("guilds", "guilds", {"FullName": self.arguments.guildFullName}, callback=self.onGuildAuidFound)


    def onGuildAuidFound(self, response):
        info("onGuildAuidFound response: %r", response)
        if response and response["r"]:
            try:
                guildAuid = response["r"]["GuildAuid"]
                self.I.GS.addVassal(self.acc, guildAuid, self.onVassalAdded)
                return
            except Exception:
                catch()

        self.errorResponse(EC.FIND_NICK_NO_AUID, "Can't find this guild")

    def onVassalAdded(self, response):
        info("onVassalAdded response: %r", response)
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
            self.errorResponse("Can't add vassal")