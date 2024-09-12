# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GuildInviteSuzerainRequest import *
from StatisticCore.ttypes import GuildInteractionType
import CC
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData

class Guild_invite_suzerain(SubAction, GuildInviteSuzerainRequest):
    """action, который будет обрабатывать данный класс"""
    action = "guild_invite_suzerain"

    @model_callback
    @parse
    @action_timing
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

        if self.getIntParam('guildAuid') in (CC.NPC_SUZERAIN_AUID, CC.NPC_VASSAL_AUID):
            self.errorResponse( EC.DEBUG_MESSAGE, "You can not send invite for NPC")
            return

        self.I.GS.inviteSuzerain(self.acc, self.getIntParam('guildAuid'), self.onInviteSuzerain)


    def ApplyUpdate(self, response):
        GuildData_changes = response.get("GuildData") or []
        if GuildData_changes:
            try:
                ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
            except:
                catch()
        self.acc.model.write(self.acc.pending)

        self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
        if self.acc.pending_handler:
            self.acc.pending_handler()

        self.sendPendingEvents()

    @model_callback
    @action_timing
    def onInviteSuzerain(self, response):
        info("Guild_invite_suzerain.onInviteSuzerain response %r" % response)
        if response:
            isOk = response.get("ok") or 0
            self.response["error"] = response.get("error") or ""
            self.response["ec"] = response.get("ec") or 0
            if isOk:
                self.I.STATS.addGuildInteraction(self.acc.db.guildAuid, self.arguments.guildAuid,
                                               GuildInteractionType.Apply, 0, 0)
                self.ApplyUpdate(response)
                self.response["ok"] = 1
            else:
                err("Can not invite: %r" % self.response["error"] )
                self.response["ok"] = 0

        self.fin()


