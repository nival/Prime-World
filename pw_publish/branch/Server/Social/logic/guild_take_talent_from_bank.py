#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from StatisticCore.ttypes import TalentInfo, TalentChangeOperation
from logic.requests.GuildTakeTalentFromBankRequest import GuildTakeTalentFromBankRequest


class Guild_take_talent_from_bank(SubAction, GuildTakeTalentFromBankRequest):
    """action, который будет обрабатывать данный класс"""
    action = "guild_take_talent_from_bank"

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

        self.I.GS.takeGuildTalent(self.acc, self.arguments.talentid, self.onTakeTalent)

    @model_callback
    @action_timing
    def onTakeTalent(self, response):
        if response:
            info("onTakeTalent response: %s" % self.I.MD.pretty(response))
            isOk = response.get("ok") or 0
            if isOk:
                GuildData_changes = response.get("GuildData") or []
                if GuildData_changes:
                    try:
                        ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                    except:
                        catch()

                if response.get("PersistentId"):
                    staticTalent = self.acc.SD.getStaticTalentByTalentId(response.get("PersistentId"))
                    if staticTalent:
                        if staticTalent['rarity'] != "Class":
                            talent = self.acc.model.addTalent(response.get("PersistentId"))
                            talent.Points = response.get("Points")

                            # Сначала проверим, не потеряем ли мы привязку гильдийского таланта
                            soulboundFixed = True
                            if response.get("GuildBankInfo.HeroClassId"):
                                soulboundFixed = False
                                for heroId in self.acc.model.Heroes:
                                    hero = self.acc.model.getHeroByID(heroId)
                                    if hero.PersistentId == response.get("GuildBankInfo.HeroClassId"):
                                        talent.Soulbound = hero
                                        soulboundFixed = True
                                        break

                            if (response.get("OwnerId") != self.acc.db.auid) or not soulboundFixed:
                                gbi, gbi_id = self.acc.model.newGuildBankInfo()
                                gbi.GuildAuid = int(response.get("GuildBankInfo.GuildAuid"))
                                gbi.GuildTalentId = int(response.get("GuildBankInfo.GuildTalentId"))
                                gbi.OwnerId = int(response.get("OwnerId"))
                                gbi.HeroClassId = int(response.get("GuildBankInfo.HeroClassId"))
                                talent.GuildBankInfo = gbi_id
                                self.I.STATS.addTalentChange(self.acc.db.auid,
                                                             TalentInfo(talent.PersistentId, talent.getID(),
                                                                        getBoundHeroClassId(talent)),
                                                             TalentChangeOperation.TakeFromBank)
                            else:
                                self.I.STATS.addTalentChange(self.acc.db.auid,
                                                             TalentInfo(talent.PersistentId, talent.getID(),
                                                                        getBoundHeroClassId(talent)),
                                                             TalentChangeOperation.TakeBackFromBank)

                        else:
                            self.errorResponse("Class talents are not allowed to be added")
                            return
                    else:
                        self.errorResponse("Static talent not found")
                        return

                self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
                if self.acc.pending_handler:
                    self.acc.pending_handler()

                self.sendPendingEvents()
                self.response["ok"] = 1
                self.fin()
            else:
                self.response["callback"] = ["guild_take_talent_from_bank"]
                self.errorResponse(response["ec"], "Can't take talent, bad response from server")
