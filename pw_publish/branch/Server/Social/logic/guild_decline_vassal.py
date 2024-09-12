# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GuildDeclineVassalRequest import *
from StatisticCore.ttypes import GuildInteractionType

class Guild_decline_vassal(SubAction, GuildDeclineVassalRequest):
    """action, который будет обрабатывать данный класс"""
    action = "guild_decline_vassal"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        # ACTION LOGIC
        if not self.acc.db.guildAuid:
            self.errorResponse(EC.NOT_IN_GUILD, "You're not in guild")
            return

        if self.acc.db.guildAuid == self.getIntParam('guildAuid'):
            self.errorResponse(EC.DEBUG_MESSAGE, "It is your guild")
            return


        self.I.GS.declineVassal(self.acc, self.getIntParam('guildAuid'), self.onDeclineVassal)


    @model_callback
    @action_timing
    def onDeclineVassal(self, response):
        info("Guild_decline_vassal.onDeclineVassal response %r" % response)
        if response:
            isOk = response.get("ok") or 0
            self.response["error"] = response.get("error") or ""
            self.response["ec"] = response.get("ec") or 0
            if isOk:
                self.I.STATS.addGuildInteraction(self.acc.db.guildAuid, self.arguments.guildAuid,
                                                 GuildInteractionType.Decline, 0, 0)
                self.response["ok"] = 1
            else:
                err("Can not decline: %r" % self.response["error"] )
                self.response["ok"] = 0

        self.fin()