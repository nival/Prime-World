#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from binascii import crc32
from modeldata.change_applicator import ModelChangeApplicator
from StatisticCore.ttypes import TalentInfo
from StatisticCore.ttypes import TalentChangeOperation
from guild.GuildData import GuildData
from logic.requests.ClearItemSoulboundRequest import ClearItemSoulboundRequest


class Clear_item_soulbound(SubAction, ClearItemSoulboundRequest):
    """action, который будет обрабатывать данный класс"""
    action = "clear_item_soulbound"

    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        talent = self.arguments.talent

        if talent:
            self.talent = talent

            if talent.Owner and talent.Owner.get() and talent.Owner.InMatchmaking:
                self.errorResponse(EC.HERO_IN_MATCHMAKING, "hero is in matchmaking")
                return

            staticTalent = self.acc.SD.getStaticTalent(talent)
            if staticTalent:
                if staticTalent['rarity'] != "Class":
                    if talent.isSoulbounded():
                        useLamp = self.arguments.useLamp
                        if useLamp:
                            if self.acc.model.canUnsoulboundWithLamp(staticTalent, self.acc.SD):
                                self.unsoulboundTalent()
                                self.I.STATS.addRuneUnsoulbound(self.acc.auid,
                                                                self.acc.model.getGoldLampType(self.acc.SD),
                                                                crc32(staticTalent['persistentId']))
                                self.acc.model.useLampTransaction()
                                self.response["ok"] = 1
                            else:
                                self.errorResponse("Lamp cannot be used for this talent")
                        else:
                            talent_level = self.acc.SD.getTalentLevelByPoints(talent.Points, staticTalent)
                            self.price = self.acc.SD.getTalentUnsoulboundPrice(staticTalent, talent_level, self.acc.getConfig())
                            if self.price:
                                self.needGold = int(self.price.Gold)
                                if (talent.Soulbound.get()):
                                    reason = "PW!UNSOULBOUND:" + str(talent.PersistentId) + ":" + str(talent.Soulbound.class_name)
                                elif talent.GuildBankInfo.get():
                                    reason = "PW!UNSOULBOUND:" + str(talent.PersistentId) + ":" + str(talent.GuildBankInfo.HeroClassId)
                                else:
                                    self.errorResponse("Talent not soulbound")
                                    return
                                self.buy(self.price, self.onBuy, self.onBuyFunc, reason)
                                return None
                    else:
                        self.errorResponse("Talent not soulbound")
                        return
                else:
                    self.errorResponse("Class talent can't be unsoulbound")
                    return
            else:
                self.errorResponse("Static talent not found")
                return
        else:
            self.errorResponse("Talent is null")
            return

        self.fin()

    def unsoulboundTalent(self):
        staticTalent = self.acc.SD.getStaticTalent(self.talent)
        if staticTalent:
            self.acc.model.addStatisticEvent(StatisticEventType.TALENT_UNSOULBOUND, staticTalent['persistentId'], 1)

        if self.talent.Owner and self.talent.Owner.get():
            hero = self.talent.Owner.get()
            for tsId in self.talent.ParentTalentSets.keys():
                hero.removeTalentFromTalentSet(tsId, self.talent, self.talent.getID())
                hero.CalcForce(self.acc.model, self.I.WS, self.acc, tsId)

        heroPersistentId = 0
        if ((self.talent.Soulbound and not self.talent.Soulbound.get()) or not self.talent.Soulbound) and self.talent.GuildBankInfo and self.talent.GuildBankInfo.get():
            heroPersistentId = self.talent.GuildBankInfo.HeroClassId
        else:
            heroPersistentId = self.talent.Soulbound.PersistentId

        talInfo = TalentInfo(self.talent.PersistentId, self.talent.getID(), heroPersistentId)
        self.I.STATS.addTalentChange(self.acc.db.auid, talInfo, TalentChangeOperation.Unsoulbound)

        self.talent.Soulbound = IGuidGenerator.InvalidUID
        if self.talent.GuildBankInfo.get():
            self.talent.GuildBankInfo.HeroClassId = 0
            # Если информация о таланте ещё хранится в гильдии, обновим её
            if self.talent.GuildBankInfo.OwnerId != self.acc.auid and self.talent.GuildBankInfo.OwnerId != 0:
                self.I.GS.guildTalentInfoUpdate(self.acc, self.talent.GuildBankInfo.GuildTalentId, self.talent.Points,
                                                self.talent.GuildBankInfo.HeroClassId, self.onUpdateGuildData)
            # Если талант наш, а GuildBankInfo был только ради Soulbound'a, уберём его
            else:
                self.talent.GuildBankInfo = None

    @model_callback
    def onBuyFunc(self, response):
        code = response["code"]
        if code != ibilling.ERROR_CODE_OK:
            self.onBuyError(response, self.needGold)
            return

        self.doConfirmWriteOff(response)
        self.unsoulboundTalent()
        self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.Unsoulbound, "", self.price,
                                        self.acc.model.Resources, self.arguments.aftercontext)

        self.response["ok"] = 1  # success
        self.fin()

    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)

    @model_callback
    @action_timing
    def onUpdateGuildData(self, response):
        if response:
            info("onUpdateGuildData response: %s" % self.I.MD.pretty(response))
            GuildData_changes = response.get("GuildData") or []
            if GuildData_changes:
                try:
                    ModelChangeApplicator.apply(self.acc, "guilddata", GuildData, GuildData_changes)
                except:
                    catch()
            self.acc.pending_events.append({"GuildData": {"GuildData": GuildData_changes}})
            if self.acc.pending_handler:
                self.acc.pending_handler()
