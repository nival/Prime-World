# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ReforgeUpgradeTalentRequest import *
from StatisticCore.ttypes import TalentInfo
from StatisticCore.ttypes import TalentChangeOperation
from StatisticCore.ttypes import ResourceChangeItem
from modeldata.StaticData import StaticData


class Reforge_upgrade_talent(SubAction, ReforgeUpgradeTalentRequest):
    """action, который будет обрабатывать данный класс"""
    action = "reforge_upgrade_talent"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.talents = []
        self.talentsToRemove = []
        self.newTalIds = {}
        self.talentsByRarities = {"excellent": [], "magnificent": [], "exclusive": []}
        # Убедимся, что мы всё делаем правильно
        transmutationBuilding = self.acc.model.getTransmutationBuilding(self.acc.SD)

        if not self.acc.getConfig().IS_REFORGE_ACTIVE:
            self.errorResponse("Reforge is not permitted")
            return

        for talentId in self.arguments.talents:
            talent = self.acc.model.getTalentByID(talentId)
            staticTalent = self.acc.SD.getStaticTalent(talent)
            if not talent or not staticTalent:
                self.response["callback"] = ["reforge_upgrade_talent"]
                self.errorResponse(
                    "Talent with persistent Id " + str(talent.PersistentId) + " wasn't found in StaticData")
                return

            if staticTalent["rarity"] not in ["excellent", "magnificent", "exclusive"]:
                self.response["callback"] = ["reforge_upgrade_talent"]
                self.errorResponse(EC.REFORGE_UPGRADE_WRONG_TALENT_RARITY, "Wrong talent rarity for upgrading")
                return

            if not self.acc.model.canReforgeUpgrade(self.acc.SD, staticTalent, transmutationBuilding):
                self.response["callback"] = ["reforge_upgrade_talent"]
                self.errorResponse(EC.REFORGE_WRONG_TRANSMUTATION_LEVEL_FOR_REROLL,
                                   "The level of the Transmutation building is too small")
                return

            if talent.GuildBankInfo and talent.GuildBankInfo.get() and talent.GuildBankInfo.OwnerId != self.acc.auid and talent.GuildBankInfo.OwnerId != 0:
                self.response["callback"] = ["reforge_upgrade_talent"]
                self.errorResponse(EC.GUILD_BANK_TALENT_IMPROPER_USE,
                                   "Guild talent can't be reforged! TalentOwnerId=%d" % talent.GuildBankInfo.OwnerId)
                return

            if talent.Points > 0 and self.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE:
                continue

            # Все проверки прошли, сделаем фильтр по талантам
            self.talentsByRarities[staticTalent["rarity"]].append(talent)

        for rarity in self.talentsByRarities:
            counter = 0
            talentsForNewTalent = 1
            reforgeInfo = self.acc.SD.data['ReforgeTalentPrices'].get(rarity, None)
            if reforgeInfo:
                talentsForNewTalent = max(1, reforgeInfo['talentsToUpgrade'])
            # Если кол-во талантов не кратное, уберём остаток
            for i in xrange(0, len(self.talentsByRarities[rarity]) % talentsForNewTalent):
                self.talentsByRarities[rarity].pop(0)
            for talent in self.talentsByRarities[rarity]:
                # каждый кратный талант отправляем на перековку
                if counter % talentsForNewTalent == 0:
                    staticTalent = self.acc.SD.getStaticTalent(talent)
                    
                    if staticTalent["rarity"] == "magnificent":
                        newPersistentId = self.acc.model.reforgeUpgradeTalent(self.acc.SD, talent, self.arguments.selectedOrangeSet, staticTalent["rarity"])
                    elif staticTalent["rarity"] == "exclusive":
                        newPersistentId = self.acc.model.reforgeUpgradeTalent(self.acc.SD, talent, self.arguments.selectedRedSet, staticTalent["rarity"])
                    else:
                        newPersistentId = self.acc.model.reforgeUpgradeTalent(self.acc.SD, talent, "", staticTalent["rarity"])
                                                                          
                    if not newPersistentId:
                        self.response["callback"] = ["reforge_upgrade_talent"]
                        self.errorResponse("StaticData error. Can't upgrade talent")
                        return

                    self.newTalIds[talent.getID()] = newPersistentId
                    self.talents.append(talent)
                # каждый некратный талант отправляем на удаление
                else:
                    self.talentsToRemove.append(talent)
                counter += 1

        self.price, self.pricesByRarity = self.__getUpgradePrice(self.talents)
        if self.price is None or self.pricesByRarity is None:
            self.response["callback"] = ["reforge_upgrade_talent"]
            self.errorResponse("Can't calc reforge_upgrade price")
            return

        if not self.acc.model.canBuy(self.price):
            self.response["callback"] = ["reforge_upgrade_talent"]
            self.errorResponse(EC.NOT_ENOUGH_RESOURCES, "Not enough perl for upgrade")
            return
        reason = "PW!REFORGE_UPGRADE"
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
                talent.Points = 0
                talent.defaultForHero = None
                talent.Soulbound = None
                talent.GuildBankInfo = None
                self.I.STATS.addTalentChange(self.acc.db.auid, TalentInfo(talent.PersistentId, talent.getID(), 0),
                                             TalentChangeOperation.GetFromTransmutation,
                                             'reforgeupgrade %s' % oldPersistentId)
            self.acc.model.addStatisticEvent(StatisticEventType.TALENT_REFORGE, "", len(self.talents))

            for rar in self.pricesByRarity:
                self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.Transmutation,
                                                "reforgeupgrade %s" % rar,
                                                self.pricesByRarity[rar], self.acc.model.Resources,
                                                self.arguments.aftercontext)
                self.acc.model.addStatisticEvent(StatisticEventType.TALENT_REFORGE_UPGRADE, rar,
                                                 len(self.talentsByRarities[rar]))
            for talent in self.talentsToRemove:
                if talent.Owner and talent.Owner.get():
                    talent.Owner.moveTalentFromTalentSetToLibrary(self.talent, self.talent.id)
                self.acc.model.UserInventory.remove(talent)

            self.response["callback"] = ["reforge_upgrade_talent"]
            self.response["ok"] = 1  # success
        else:
            self.response["callback"] = ["reforge_upgrade_talent"]
            self.onBuyError(response, self.needGold)
            return

        self.fin()

    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)

    def __getUpgradePrice(self, talents):
        price = self.acc.SD.emptyPrice()
        pricesByRarity = {}

        for talent in talents:
            staticTalent = self.acc.SD.getStaticTalent(talent)
            rarityPrices = self.acc.SD.data['ReforgeTalentPrices'].get(staticTalent['rarity'], None)
            if not rarityPrices:
                return None, None
            StaticData.getAddPrice(price, rarityPrices['upgradePrice'])
            if not staticTalent["rarity"] in pricesByRarity:
                pricesByRarity[staticTalent["rarity"]] = self.acc.SD.emptyPrice()
            StaticData.getAddPrice(pricesByRarity[staticTalent["rarity"]], rarityPrices['upgradePrice'])

        return price, pricesByRarity
