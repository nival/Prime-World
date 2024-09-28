#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from binascii import crc32
from modeldata.change_applicator import ModelChangeApplicator
from guild.GuildData import GuildData
from logic.requests.ItemMoveInvToTsRequest import ItemMoveInvToTsRequest
from StatisticCore.ttypes import TalentInfo, TalentChangeOperation


class Item_move_inv2ts(SubAction, ItemMoveInvToTsRequest):
    """action, который будет обрабатывать данный класс"""
    action = "item_move_inv2ts"

    # клиент просит переместить вещь из инвентаря в талантсет
    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        hero = self.arguments.src_hero
        self.tsId = self.arguments.talent_set_id
        if not hero or not hero.Hired:
            self.errorResponse("hero not hired")
            return

        if hero.InMatchmaking:
            self.errorResponse("hero is in matchmaking")
            return
        src_item = self.acc.model.UserInventory.get(self.arguments.src_item_id)
        if not src_item:
            self.errorResponse("bad source path or item_id")
            return

        destTalId = hero.TalentSets[self.tsId].Talents.get(self.arguments.dest_slot_id)
        if destTalId is not None and destTalId != self.arguments.dest_item_id:
            self.errorResponse("bad dest path or item_id")
            return

        hero_talents = self.acc.model.getHeroClassTalents(self.acc.getConfig(), hero.PersistentId, self.acc.SD)
        if src_item.GuildBankInfo.get() and src_item.GuildBankInfo.OwnerId != self.acc.auid and src_item.GuildBankInfo.OwnerId != 0:
            guildTalentCounter = 0
            for slot, at in hero.TalentSets[self.tsId].Talents.iteritems():
                activeTalent = self.acc.model.getTalentByID(at)
                if activeTalent.GuildBankInfo.get() and activeTalent.GuildBankInfo.OwnerId != self.acc.auid and activeTalent.GuildBankInfo.OwnerId != 0:
                    guildTalentCounter += 1

            if guildTalentCounter >= self.acc.getConfig().GuildBankSettings.MAX_GUILD_TALENTS_IN_SET:
                dstTalent = self.acc.model.getTalentByID(hero.TalentSets[self.tsId].Talents.get(self.arguments.dest_slot_id))
                if dstTalent:
                    if not dstTalent.GuildBankInfo.get() or dstTalent.GuildBankInfo.OwnerId == self.acc.auid or dstTalent.GuildBankInfo.OwnerId == 0:
                        self.errorResponse(EC.GUILD_BANK_GUILD_TALENTS_LIMIT_IN_TS_EXCEEDED,
                                           "Guild talents limit in TalantSet exceeded")
                        return
                else:
                    self.errorResponse(EC.GUILD_BANK_GUILD_TALENTS_LIMIT_IN_TS_EXCEEDED,
                                       "Guild talents limit in TalantSet exceeded")
                    return

        talent_id, response_error = Validator.checkItemFit(self.acc, hero, src_item, self.arguments.dest_slot_id,
                                                           self.acc.SD, check_duplicates=1, hero_talents=hero_talents,
                                                           tsId=self.tsId)
        if response_error:
            self.errorResponse(response_error)
            return

        if not talent_id:
            self.errorResponse("bad src slot filter (cant place dest item)")
            return

        dest_item = self.acc.model.getTalentByID(hero.TalentSets[self.tsId].Talents.get(self.arguments.dest_slot_id))

        self.hero = hero
        self.src_item = src_item
        self.dest_item = dest_item

        self.staticTalent = self.acc.SD.getStaticTalent(src_item)
        if src_item.isSoulboundedToHero(hero) or not src_item.isSoulbounded() \
                or not self.acc.getConfigValue("SOULBOUND_ENABLED") or not src_item.canBeSoulbound(self.acc.SD):
            self.moveItem(self.tsId)
        else:
            useLamp = self.arguments.useLamp
            if useLamp:
                if self.acc.model.canUnsoulboundWithLamp(self.staticTalent, self.acc.SD):
                    self.moveItem(self.tsId)
                    self.I.STATS.addRuneUnsoulbound(self.acc.auid, self.acc.model.getGoldLampType(self.acc.SD),
                                                    crc32(self.staticTalent['persistentId']))
                    self.acc.model.useLampTransaction()
                else:
                    self.errorResponse("Lamp cannot be used for this talent")
            else:
                talent_level = self.acc.SD.getTalentLevelByPoints(src_item.Points, self.staticTalent)
                self.price = self.acc.SD.getTalentUnsoulboundPrice(self.staticTalent, talent_level, self.acc.getConfig())
                self.needGold = int(self.price.Gold)
                if (src_item.Soulbound.get()):
                    reason = "PW!UNSOULBOUND:" + str(src_item.PersistentId) + ":" + str(src_item.Soulbound.class_name)
                elif src_item.GuildBankInfo.get():
                    reason = "PW!UNSOULBOUND:" + str(src_item.PersistentId) + ":" + str(
                        src_item.GuildBankInfo.HeroClassId)
                else:
                    self.errorResponse("Can not move strange talent %r", src_item.getID())
                self.buy(self.price, self.onBuy, self.onBuyFunc, reason)
                return None

        self.response["ok"] = 1  # success
        self.fin()

    def moveItem(self, tsId):
        ts = self.hero.TalentSets[tsId]
        if self.dest_item:
            self.hero.removeTalentFromTalentSet(tsId, self.dest_item, self.dest_item.id)

        src_item = self.src_item
        staticTalent = self.acc.SD.getStaticTalent(src_item)
        ts.Talents.add(self.arguments.dest_slot_id, src_item.id)
        if (not src_item.isSoulbounded() or not src_item.isSoulboundedToHero(self.hero)) and src_item.canBeSoulbound(
                self.acc.SD):
            if src_item.isSoulbounded():
                self.acc.model.addStatisticEvent(StatisticEventType.TALENT_UNSOULBOUND, staticTalent['persistentId'], 1)

            src_item.Soulbound = self.hero
            if src_item.GuildBankInfo.get():
                src_item.GuildBankInfo.HeroClassId = self.hero.PersistentId
                # Если информация о таланте ещё хранится в гильдии, обновим её
                if src_item.GuildBankInfo.OwnerId != self.acc.auid and src_item.GuildBankInfo.OwnerId != 0:
                    self.I.GS.guildTalentInfoUpdate(self.acc, src_item.GuildBankInfo.GuildTalentId,
                                                    src_item.Points, src_item.GuildBankInfo.HeroClassId,
                                                    self.onUpdateGuildData)
            else:
                src_item.GuildBankInfo = None

            self.acc.model.addStatisticEvent(StatisticEventType.TALENT_SOULBOUND, staticTalent['persistentId'], 1)
            self.I.STATS.addTalentChange(self.acc.auid,
                                         TalentInfo(src_item.PersistentId, self.arguments.src_item_id,
                                                    self.hero.PersistentId),
                                         TalentChangeOperation.Soulbound)

        if src_item.IsNew:
            src_item.IsNew = False

        if not staticTalent['type'] == "Passive" and not staticTalent['type'] == "Simple":
            actionBarIdx = self.hero.GetFreeActionBarSlot(tsId)
            if actionBarIdx != -1:
                ts.ActionBar[actionBarIdx] = src_item.getID()
                ts.InstaCast.set(actionBarIdx, False)

        src_item.ParentTalentSets.add(tsId, ts.id)
        self.hero.CalcForce(self.acc.model, self.I.WS, self.acc, tsId)
        src_item.Owner = self.hero
        self.I.STATS.addMoveTalentToSet(self.acc.auid, self.acc.nick, src_item.PersistentId, self.hero.PersistentId,
                                        self.arguments.dest_slot_id)

    @model_callback
    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            self.moveItem(self.tsId)
            self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.Unsoulbound,
                                            "%r (id=%r)" % (self.src_item.PersistentId, self.src_item.id), self.price,
                                            self.acc.model.Resources)
            self.response["ok"] = 1  # success
        else:
            self.onBuyError(response, self.needGold)
            return

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
