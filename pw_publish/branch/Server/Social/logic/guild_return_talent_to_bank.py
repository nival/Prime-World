#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from StatisticCore.ttypes import TalentInfo, TalentChangeOperation
from logic.requests.GuildReturnTalentToBankRequest import GuildReturnTalentToBankRequest


class Guild_return_talent_to_bank(SubAction, GuildReturnTalentToBankRequest):
    """action, который будет обрабатывать данный класс"""
    action = "guild_return_talent_to_bank"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if not self.acc.db.guildAuid:
            self.errorResponse(EC.NOT_IN_GUILD, "You're not in guild")
            return

        self.guildTalent = self.arguments.talent
        if self.guildTalent.Owner and self.guildTalent.Owner.get():
            self.errorResponse(EC.GUILD_BANK_CANNOT_ADD_TALENT, "Can't add talent from active hero set")
            return

        if not self.guildTalent.GuildBankInfo.get():
            self.errorResponse(EC.GUILD_BANK_CANNOT_ADD_TALENT, "Can't add talent - not guild talent")
            return

        self.I.GS.returnGuildTalent(self.acc, self.guildTalent.GuildBankInfo.GuildTalentId, self.onReturnTalent)

    @model_callback
    @action_timing
    def onReturnTalent(self, response):
        if response:
            info("onReturnTalent response: %s", self.I.MD.pretty(response))
            isOk = response.get("ok") or 0
            if isOk:
                GuildData_changes = response.get("GuildData") or []
                if GuildData_changes:
                    try:
                        ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                    except:
                        catch()
                if self.guildTalent.Owner and self.guildTalent.Owner.get():
                    self.guildTalent.Owner.moveTalentFromTalentSetToLibrary(self.guildTalent, self.guildTalent.id)

                    for tsId in self.guildTalent.Owner.TalentSets.keys():
                        self.guildTalent.Owner.CalcForce(self.acc.model, self.I.WS, self.acc, tsId, skipStatisticEvent=True)

                self.acc.model.UserInventory.remove(self.guildTalent)
                self.I.STATS.addTalentChange(self.acc.db.auid,
                                             TalentInfo(self.guildTalent.PersistentId, self.guildTalent.getID(),
                                                        getBoundHeroClassId(self.guildTalent)),
                                             TalentChangeOperation.ReturnToBank)

                self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
                if self.acc.pending_handler:
                    self.acc.pending_handler()

                self.sendPendingEvents()
                self.response["ok"] = 1
                self.fin()
            else:
                self.errorResponse(response["ec"], "Can't return talent, bad response from server")
