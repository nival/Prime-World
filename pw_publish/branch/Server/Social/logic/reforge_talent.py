# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ReforgeTalentRequest import *
from StatisticCore.ttypes import TalentInfo
from StatisticCore.ttypes import TalentChangeOperation
from binascii import crc32
from modeldata.StaticData import StaticData


class Reforge_talent(SubAction, ReforgeTalentRequest):
    """action, который будет обрабатывать данный класс"""
    action = "reforge_talent"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.talents = []
        self.newTalIds = {}
        # Убедимся, что мы всё делаем правильно
        transmutationBuilding = self.acc.model.getTransmutationBuilding(self.acc.SD)

        if not self.acc.getConfig().IS_REFORGE_ACTIVE:
            self.errorResponse("Reforge is not permitted")
            return

        for talentId in self.arguments.talents:
            talent = self.acc.model.getTalentByID(talentId)
            staticTalent = self.acc.SD.getStaticTalent(talent)
            if not talent or not staticTalent:
                self.response["callback"] = ["reforge_talent"]
                self.errorResponse("Talent with Id " + str(talentId) + " wasn't found")
                return

            if staticTalent["rarity"] not in ["exclusive", "excellent", "magnificent", "outstanding"]:
                self.response["callback"] = ["reforge_talent"]
                self.errorResponse(EC.REFORGE_WRONG_TALENT_RARITY, "Wrong talent rarity for reforging")
                return

            if not self.acc.model.canReforge(self.acc.SD, staticTalent, transmutationBuilding):
                self.response["callback"] = ["reforge_talent"]
                self.errorResponse(EC.REFORGE_WRONG_TRANSMUTATION_LEVEL_FOR_REROLL,
                                   "The level of the Transmutation building is too small")
                return

            if talent.GuildBankInfo.get() and talent.GuildBankInfo.OwnerId != self.acc.auid and talent.GuildBankInfo.OwnerId != 0:
                self.response["callback"] = ["reforge_talent"]
                self.errorResponse(EC.GUILD_BANK_TALENT_IMPROPER_USE,
                                   "Guild talent can't be reforged! TalentOwnerId=%d" % talent.GuildBankInfo.OwnerId)
                return

            # ролить заточенные таланты из сета можно только с ALLOW_REROLL_FROM_SET_FOR_UPGRADED_TALENTS_ON_REFORGE
            is_set_selected = staticTalent['rarity'] == 'exclusive' and bool(self.arguments.selectedOrangeSet) \
                              or staticTalent['rarity'] == 'outstanding' and bool(self.arguments.selectedRedSet)
            if talent.Points > 0 \
                    and self.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE \
                    and is_set_selected \
                    and not self.acc.getConfig().ALLOW_REROLL_FROM_SET_FOR_UPGRADED_TALENTS_ON_REFORGE:
                continue

            if staticTalent["rarity"] == "exclusive":
                newPersistentId = self.acc.model.reforgeTalent(self.acc.SD, talent, self.arguments.selectedOrangeSet,
                                                               staticTalent["rarity"])
            elif staticTalent["rarity"] == "outstanding":
                newPersistentId = self.acc.model.reforgeTalent(self.acc.SD, talent, self.arguments.selectedRedSet,
                                                               staticTalent["rarity"])
            else:
                newPersistentId = self.acc.model.reforgeTalent(self.acc.SD, talent, "", staticTalent["rarity"])

            if not newPersistentId:
                self.response["callback"] = ["reforge_talent"]
                self.errorResponse("StaticData error. Can't reforge talent")
                return
            self.newTalIds[talent.getID()] = newPersistentId
            self.talents.append(talent)

        self.price, self.pricesByRarity = self.__getRerollPrice(self.talents,
                                                                self.arguments.selectedOrangeSet,
                                                                self.arguments.selectedRedSet)
        if self.price is None or self.pricesByRarity is None:
            self.response["callback"] = ["reforge_talent"]
            self.errorResponse("Can't calc reforge price")
            return

        if not self.acc.model.canBuy(self.price):
            self.response["callback"] = ["reforge_talent"]
            self.errorResponse(EC.NOT_ENOUGH_RESOURCES, "Not enough perl for reforge")
            return

        reason = "PW!REFORGE"
        self.buy(self.price, self.onBuy, self.onBuyFunc, reason)

    @model_callback
    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            for talent in self.talents:
                oldPersistentId = talent.PersistentId
                talent.PersistentId = self.newTalIds[talent.getID()]
                talent.IsNew = True
                if not self.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE:
                    talent.Points = 0
                talent.defaultForHero = None
                talent.Soulbound = None
                self.I.STATS.addTalentChange(self.acc.db.auid, TalentInfo(talent.PersistentId, talent.getID(), 0),
                                             TalentChangeOperation.GetFromTransmutation, 'reforge %s' % oldPersistentId)
            self.acc.model.addStatisticEvent(StatisticEventType.TALENT_REFORGE, "", len(self.talents))

            for rar in self.pricesByRarity:
                self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.Transmutation,
                                                "reforge %s" % rar, self.pricesByRarity[rar], self.acc.model.Resources,
                                                self.arguments.aftercontext)

            self.response["callback"] = ["reforge_talent"]
            self.response["ok"] = 1  # success
        else:
            self.response["callback"] = ["reforge_talent"]
            self.onBuyError(response, self.needGold)
            return

        self.fin()

    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)

    def __getRerollPrice(self, talents, orange_set, red_set):
        price = self.acc.SD.emptyPrice()
        pricesByRarity = {}

        for talent in talents:
            staticTalent = self.acc.SD.getStaticTalent(talent)
            rarityPrices = self.acc.SD.data['ReforgeTalentPrices'].get(staticTalent['rarity'], None)
            if not rarityPrices:
                return None, None
            talentLevel = 1
            if self.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE:
                talentLevel = self.acc.SD.getTalentLevelByPoints(talent.Points, staticTalent) + 1
            levelPrice = next((pr for pr in reversed(rarityPrices['rerollPrices']['Item']) if pr['stars'] <= talentLevel), None)
            if not levelPrice:
                return None, None
            is_set_selected = staticTalent['rarity'] == 'exclusive' and bool(orange_set) \
                              or staticTalent['rarity'] == 'outstanding' and bool(red_set)
            set_price = levelPrice['priceWithoutSetFilter']
            if is_set_selected:
                set_price = levelPrice['priceWithSetFilter']

            StaticData.getAddPrice(price, set_price)
            if not staticTalent["rarity"] in pricesByRarity:
                pricesByRarity[staticTalent["rarity"]] = self.acc.SD.emptyPrice()
            StaticData.getAddPrice(pricesByRarity[staticTalent["rarity"]], set_price)

        return price, pricesByRarity
