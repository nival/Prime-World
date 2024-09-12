#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from guild_leave import *
from logic.requests.ChangeFractionRequest import ChangeFractionRequest


class Change_fraction(SubAction, ChangeFractionRequest):
    """action, который будет обрабатывать данный класс"""
    action = "change_fraction"

    @model_callback  # АВТОМАТИЧЕСКИ НЕ(!) АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if (self.acc.db.fraction == 'A' and self.acc.getConfigValue("CHANGE_FRACTION_TO_ADORNIA")) \
                or (self.acc.db.fraction == 'B' and self.acc.getConfigValue("CHANGE_FRACTION_TO_DOCT")):
            inMatchmaking = False
            for heroId in self.acc.model.Heroes:
                hero = self.acc.model.getHeroByID(heroId)
                if hero.InMatchmaking:
                    inMatchmaking = True
                    self.errorResponse(EC.HERO_IN_MATCHMAKING, "Hero " + hero.class_name + " is in matchmaking",
                                       {"hero": hero.class_name})
                    return

            self.price = self.acc.model.createResourcesTable(Gold=self.acc.getConfigValue("COST_FRACTION_CHANGE"))
            if self.acc.db.fraction != self.arguments.fraction and self.acc.db.fraction != 'N':
                if (self.acc.db.fractionChanged >= self.acc.getConfigValue(
                        "FREE_FRACTION_CHANGES") and self.acc.model.canBuy(self.price)) \
                        or self.acc.db.fractionChanged < self.acc.getConfigValue("FREE_FRACTION_CHANGES"):
                    if self.acc.db.fractionChanged >= self.acc.getConfigValue("FREE_FRACTION_CHANGES"):
                        self.needGold = int(self.price.Gold)
                        reason = "PW!CHANGE_FRACTION:" + str(self.acc.db.fractionChanged + 1) + ":" + str(
                            self.arguments.fraction)
                        self.buy(self.price, self.onBuy, self.onBuyFunc, reason)
                    else:
                        self.needGold = None
                        self.onBuyFunc({"code": ibilling.ERROR_CODE_OK})
                    return None
                else:
                    freeChanges = self.acc.getConfigValue("FREE_FRACTION_CHANGES") - self.acc.db.fractionChanged
                    if freeChanges < 0:
                        freeChanges = 0
                    self.errorResponse(EC.NOT_ENOUGH_RESOURCES, "Not enough gold", \
                                       {"cost": self.acc.getConfigValue("COST_FRACTION_CHANGE"),
                                        "gold": self.acc.model.Resources.Gold})
                    return
            else:
                self.errorResponse(
                    "can't change fraction from %r to %r" % (self.acc.db.fraction, self.arguments.fraction))
                return
        else:
            self.errorResponse(EC.FRACTION_CHANGE_DISABLED)
            return

        self.fin()

    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            oldFraction = self.acc.db.fraction
            newFraction = self.arguments.fraction
            self.changeFraction()
            self.acc.db.fractionChanged += 1
            if self.needGold:
                self.I.STATS.addFactionSelect(self.acc.auid, oldFraction, newFraction, self.price,
                                              self.acc.model.Resources)
            else:
                self.I.STATS.addFactionSelect(self.acc.auid, oldFraction, newFraction,
                                              self.acc.model.createResourcesTable(), self.acc.model.Resources)
            self.response["ok"] = 1  # success
        else:
            self.onBuyError(response, self.needGold)
            return

        self.fin()

    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)

    def changeFraction(self):
        oldFraction = self.acc.db.fraction
        newFraction = self.arguments.fraction
        info("changeFraction: %s -> %s (auid %s)" % (oldFraction, newFraction, self.acc.auid))

        # Здания - декорации удаляем, но даем за них ресурсы
        if self.acc.model.LordInfo.LevelOfExpansion != 0:
            for buildingId in self.acc.model.Buildings.keys():
                building = self.acc.model.getConstructionByID(buildingId)
                staticBuilding = self.acc.SD.getStaticConstruction(building)
                if staticBuilding:
                    # продавать нельзя конвертить
                    if staticBuilding['classType'] == "Decoration" and (
                        (staticBuilding['fraction'] == '1' and oldFraction == 'A') or (
                            staticBuilding['fraction'] == '2' and oldFraction == 'B')):
                        building.sellConstruction(building, staticBuilding, building.Level, self.acc.model, self.acc.SD,
                                                  False, self.I.STATS, self.acc, False)
                        self.acc.model.Buildings.remove(building)
            self.acc.model.calcResourcesLimit(self.acc.SD, self.acc.guest)
            self.acc.model.recalcPopulation(self.acc.SD, self.acc.guest)

        # Конвертим антагонистов и выдаем денег за скины
        goldForSkin = 0
        config = self.acc.getConfig()
        for heroId in self.acc.model.HeroesKeeper.keys():
            hero = self.acc.model.getHeroByID(heroId)
            staticHero = self.acc.SD.getStaticHero(hero)
            for skinId in hero.HeroSkins.Skins.keys():
                skin = self.acc.model.getSkinByID(skinId)
                if skin:
                    static_skin = self.acc.SD.getStaticSkinByPersistentId(skin.PersistentId)
                    if int(static_skin['heroRace']) == 3:
                        pass  # скин не оригинальный - оставляем
                    else:
                        # А есть ли на что этот скин заменить?
                        if static_skin['antagonistSkinId'] != "":
                            antagonist_skin = self.acc.SD.getStaticSkinByPersistentId(
                                crc32(static_skin['antagonistSkinId']))
                            if antagonist_skin and ((antagonist_skin['heroRace'] == '1' and newFraction == 'A') or (
                                    antagonist_skin['heroRace'] == '2' and newFraction == 'B')):
                                skin.PersistentId = crc32(antagonist_skin['persistentId'])
                                continue
                        # Если не на что менять, то просто возвращаем деньги
                        price = self.acc.model.createResourcesTable(Gold=static_skin['cost'])
                        if static_skin['persistentId'] in config.EventToolsChangeFields.SKIN_GOLD_PRICES:
                            price.Gold = config.EventToolsChangeFields.SKIN_GOLD_PRICES[static_skin['persistentId']]
                        # а был ли скин куплен или получен из event'ов?
                        if skin.WasBought:
                            goldForSkin += int(price.Gold)
                            skinName = static_skin['persistentId'] + "_" + self.acc.db.fraction
                            self.I.STATS.addResourcesChange(self.acc.auid, True, ResourceChangeItem.BuySkin,
                                                            "%r (id=%r)" % (skinName, hero.id), price,
                                                            self.acc.model.Resources)

                        self.acc.model.deleteByID(skinId)

            if staticHero and staticHero['heroSkins'] and staticHero['heroSkins']['Item'] and len(
                    staticHero['heroSkins']['Item']) > 0:
                for sk in staticHero['heroSkins']['Item']:
                    skFr = self.acc.SD.getFractions(sk['heroRace'])
                    # скин валидный и дефолтовый для новой фракции
                    if sk['persistentId'] in config.DEFAULT_SKINS and sk['legal'] and sk[
                        'persistentId'] not in config.INVALID_SKINS and newFraction in skFr and oldFraction not in skFr:
                        isDefault = not hero.HeroSkins.CurrentSkin.get()
                        if not self.acc.model.isSkinOwned(crc32(sk['persistentId']), self.acc.SD):
                            self.acc.model.addSkinForHero(crc32(sk['persistentId']), hero, isDefault=isDefault,IsAnimatedAvatar=sk['persistentId'] not in config.SKIN_AVATAR_BLOCK)

            heroRace = self.acc.SD.getFractions(staticHero['heroRace'])
            if oldFraction in heroRace and not newFraction in heroRace:

                staticAntagonist = self.acc.SD.getStaticHeroByClassId(crc32(staticHero['antagonistId']))
                # ну а вдруг кто-то забыл включить антогонистов
                if not staticAntagonist:
                    info("converting hero failed: classname %s -> %s (auid %s). no static antagonist found!" % (
                    hero.class_name, staticHero['antagonistId'], self.acc.auid))
                    # вообще, удаление конечно неправильное, зато не падаем
                    self.acc.model.deleteByID(hero.id)
                    continue

                info("converting hero: classname %s -> %s (auid %s)" % (
                hero.class_name, staticHero['antagonistId'], self.acc.auid))
                for tsId in hero.TalentSets.keys():
                    for key in hero.TalentSets[tsId].Talents.keys():
                        talent = self.acc.model.getTalentByID(hero.TalentSets[tsId].Talents.get(key))
                        if talent:
                            staticTalent = self.acc.SD.getStaticTalent(talent)
                            if staticTalent['rarity'] != "Class":
                                talent.Soulbound = IGuidGenerator.InvalidUID
                                if talent.GuildBankInfo.get():
                                    if talent.GuildBankInfo.OwnerId != self.acc.db.auid:
                                        talent.GuildBankInfo.HeroClassId = 0
                                    else:
                                        talent.GuildBankInfo = None
                                # self.acc.model.UserInventory.add( talent )
                                hero.removeTalentFromTalentSet(tsId, talent, key)

                for talentId in self.acc.model.UserInventory:
                    talent = self.acc.model.getTalentByID(talentId)
                    if talent.Soulbound != IGuidGenerator.InvalidUID and talent.Soulbound.PersistentId == hero.PersistentId:
                        talent.Soulbound = IGuidGenerator.InvalidUID
                        if talent.GuildBankInfo.get():
                            if talent.GuildBankInfo.OwnerId != self.acc.db.auid:
                                talent.GuildBankInfo.HeroClassId = 0
                            else:
                                talent.GuildBankInfo = None

                # Перераспределяем statpoints
                curLvl = self.acc.SD.getHeroExpLevel(0)
                earnedLvl = self.acc.SD.getHeroExpLevel(hero.Experience)
                for tsId in hero.TalentSets.keys():
                    if earnedLvl > curLvl:
                        statPoints = 0
                        for lvl in xrange(self.acc.SD.getHeroExpLevel(0),
                                          self.acc.SD.getHeroExpLevel(hero.Experience) + 1):
                            statPoints += self.acc.SD.getHeroStatPoints(lvl)
                        if statPoints > 0:
                            hero.TalentSets[tsId].Stats.__init__(self.acc.model, None, "")
                            hero.changeStatPoints(statPoints, tsId)

                hero.deleteDefaultTalentSet(self.acc.model)
                hero.class_name = staticHero['antagonistId']
                hero.PersistentId = crc32(hero.class_name)
                staticHeroNew = self.acc.SD.getStaticHero(hero)

                hero.createDefaultTalentSet(self.acc.getConfig(), self.acc.model, self.acc.SD, staticHeroNew, 0)
                hero.TalentSets[0].Force = self.acc.SD.getDefaultHeroForce(self.acc.getConfig(), hero.PersistentId, 0,
                                                                           self.acc.model.getStatPointsFromBuilding(
                                                                               self.acc.SD))

                for tsId in xrange(1, self.acc.getConfig().MAX_USER_TALENTSETS_COUNT):
                    #hero.createOtherTalentSets(self.acc.model, tsId, hero.TalentSets[0], staticHeroNew)
                    hero.createTalentSetFromDefault(self.acc.model, staticHeroNew, self.acc.SD, tsId, self.acc.getConfig())
                    hero.TalentSets[tsId].Force = self.acc.SD.getDefaultHeroForce(self.acc.getConfig(), hero.PersistentId, tsId,
                                                                                  self.acc.model.getStatPointsFromBuilding(
                                                                                      self.acc.SD))

                    # распечатаем первые 2 таланта в получившемся TS
                    for slot in [1, 2]:
                        talent = self.acc.model.getTalentByID(hero.TalentSets[tsId].Talents.get(slot))
                        info("converted talents(auid %s, heroId %s): TalentSet[%s] => TalentSlot[%s] = PersistentId %s",
                             self.acc.auid, heroId, tsId, slot, talent.PersistentId)
        if goldForSkin:
            self.I.BILL.replenish(self.acc.db.auid, goldForSkin, "ChangeFraction", None)

        # Меняем ActiveQuests, CompletedQuests и PendingQuests.
        for questId in self.acc.model.ActiveQuests.keys():
            quest = self.acc.model.getQuestByID(questId)
            staticQuest = self.acc.SD.getStaticQuestById(quest.persistentId)
            if staticQuest:
                # Если альтернативный квест пустой, то ничего менять не надо
                if staticQuest['alternativeQuestId'] != "":
                    quest.persistentId = crc32(staticQuest['alternativeQuestId'])
            else:
                self.acc.model.ActiveQuests.remove(questId)
        for questId in self.acc.model.CompletedQuests.keys():
            quest = self.acc.model.getQuestByID(questId)
            staticQuest = self.acc.SD.getStaticQuestById(quest.persistentId)
            if staticQuest:
                # Если альтернативный квест пустой, то ничего менять не надо
                if staticQuest['alternativeQuestId'] != "":
                    quest.persistentId = crc32(staticQuest['alternativeQuestId'])
            else:
                self.acc.model.CompletedQuests.remove(questId)
        pendingQuests = []
        while (len(self.acc.model.PendingQuests)):
            pendingQuests.append(self.acc.model.PendingQuests.pop(0))
        for persistentId in pendingQuests:
            staticQuest = self.acc.SD.getStaticQuestById(persistentId)
            if staticQuest:
                # Если альтернативный квест пустой, то ничего менять не надо
                if staticQuest['alternativeQuestId'] != "":
                    self.acc.model.PendingQuests.append(crc32(staticQuest['alternativeQuestId']))
                else:
                    self.acc.model.PendingQuests.append(persistentId)
        # Карты больше не сбрасываем, потому что квесты всё равно меняются на противоположные (не перевыдаются)
        # self.acc.model.createDefaultMaps(self.acc.SD, True)

        # Собственно меняем фракцию
        self.acc.db.fraction = self.arguments.fraction

        # self.acc.model.GiveStartQuest(self.acc.SD.data['StartQuestsForFractionChange'], self.acc, self.I)
        self.I.WS.updateGameDataToPersonServer(self.acc)
