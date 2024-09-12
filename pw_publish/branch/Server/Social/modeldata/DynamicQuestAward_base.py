# -*- coding: utf-8 -*-
from binascii import crc32

import CC
from enums import DynamicQuestAwardType, ETalentRarity
from base.helpers import *
from modeldata.collects import *
import traceback, sys

class DynamicQuestAward_base(object):
    def serializeToFile( self, file, name ):
        pass

    def fillFromSD(self, awardDict, quest, model, SD):
        # convert logic
        self.fill(awardDict, quest, model, SD)

    def fill(self, award, quest, model, SD):
        self.QuestAwardType = award["AwardType"]
        self.AwardConditionType = award["AwardConditionType"]
        if self.QuestAwardType in [DynamicQuestAwardType.Experience, DynamicQuestAwardType.Gold, DynamicQuestAwardType.Perl,
            DynamicQuestAwardType.RedPerl, DynamicQuestAwardType.PremiumAcc, DynamicQuestAwardType.Resource1,
            DynamicQuestAwardType.Resource2, DynamicQuestAwardType.Resource3, DynamicQuestAwardType.Shard, DynamicQuestAwardType.Silver, DynamicQuestAwardType.UpgradeHeroTalentsEvent]:
            self.Value = toint(award["Value"])
        elif self.QuestAwardType == DynamicQuestAwardType.CustomCurrency:
            self.Value = toint(award["Value"])
            self.CustomCurrencyId = str(award["TextData"])
        elif self.QuestAwardType == DynamicQuestAwardType.RandomTalent:
            talentPack = ""
            talentRariry = award["TextData"]
            if ":" in award["TextData"]:
                talInfo = [ str(x).strip() for x in award["TextData"].split(":")]
                talentRariry = talInfo[0]
                talentPack = talInfo[1]
            persistentId = SD.getRandomTalent(talentRariry, talentPack, model.LordInfo.RandomSeed >> 8)
            if not persistentId:
                warn("Can't add random talent reward with rarity %s", award["TextData"])
                return
            self.PersistentId = persistentId

            additDataToAwards = self.get_talent_refine_from_addit_data(award)
            self.AdditionalData = additDataToAwards

            if toint(award["Value"]) > 1:
                talentsCount = len(SD.TALENTS_FOR_ROLL[talentRariry])
                for i in xrange(1, toint(award["Value"])):
                    talId = SD.getValueInRange(random.randint(0, talentsCount-1), 0, talentsCount-1)
                    talentAwardId = model.addNewDynamicQuestAward()
                    talentAward = model.getDynamicQuestAwardByID(talentAwardId)
                    persistentId = SD.getRandomTalent(talentRariry, talentPack, talId)
                    if not persistentId:
                        warn("Can't add random talent reward with rarity %s", award["TextData"])
                        continue
                    talentAward.PersistentId = persistentId
                    if award["AdditionalData2"]:
                        talentAward.AdditionalData = additDataToAwards
                    talentAward.QuestAwardType = award["AwardType"]
                    quest.Awards.add(talentAward)
        elif self.QuestAwardType in [DynamicQuestAwardType.Construction,
            DynamicQuestAwardType.Hero, DynamicQuestAwardType.Skin, DynamicQuestAwardType.HeroStatsReset]:
            self.PersistentId = crc32(award["Value"])
        elif self.QuestAwardType == DynamicQuestAwardType.Talent:
            self.PersistentId = crc32(award["TextData"])
            self.AdditionalData = self.get_talent_refine_from_addit_data(award)
            if toint(award["Value"]) > 1:
                for i in xrange(1, toint(award["Value"])):
                  talentAwardId = model.addNewDynamicQuestAward()
                  talentAward = model.getDynamicQuestAwardByID(talentAwardId)
                  talentAward.PersistentId = crc32(award["TextData"])
                  talentAward.QuestAwardType = award["AwardType"]
                  talentAward.AdditionalData = self.get_talent_refine_from_addit_data(award)
                  quest.Awards.add(talentAward)
        elif self.QuestAwardType == DynamicQuestAwardType.HeroExperience:
            self.Value = toint(award["Value"])
            self.PersistentId = crc32(award["TextData"])
        elif self.QuestAwardType == DynamicQuestAwardType.Lamp:
            try:
                lampInfo = [ str(x).strip() for x in award["TextData"].split(":")]
                self.Lamp.DbId = lampInfo[0]
                self.Lamp.Bonus = toint(lampInfo[1])
                self.Lamp.Transactions = toint(lampInfo[2])
                self.Lamp.Duration = toint(lampInfo[3])
            except Exception:
                catch()
                err("Wrong award value format for dynamic quest award!")
        elif self.QuestAwardType == DynamicQuestAwardType.CustomFlag:
            self.DbId = award["Value"]
        elif self.QuestAwardType == DynamicQuestAwardType.Quest:
            self.PersistentId = toint(award["Value"])
        elif self.QuestAwardType == DynamicQuestAwardType.RandomHero:
            persistentIds = [ str(x).strip() for x in award["TextData"].split(",")]
            availableHeroes = persistentIds[:]
            for persistentId in persistentIds:
                for hero_id, hero in model.Heroes.iteritems():
                    if hero.PersistentId == crc32(persistentId):
                        availableHeroes.remove(persistentId)
            if len(availableHeroes):
                randInt = model.getRandom(model.LordInfo.RandomSeed)
                hero_id = availableHeroes[randInt % len(availableHeroes)]
                self.PersistentId = crc32(hero_id)
            else:
                warn("Player already has all awarded heroes")
        elif self.QuestAwardType == DynamicQuestAwardType.RandomSkin:
            persistentIds =  [ str(x).strip() for x in award["TextData"].split(",")]
            availableSkins = persistentIds[:]
            for persistentId in persistentIds:
                if model.isSkinOwned(persistentId, SD):
                    availableSkins.remove(persistentId)
            if len(availableSkins):
                randInt = model.getRandom(model.LordInfo.RandomSeed)
                hero_id = availableSkins[randInt % len(availableSkins)]
                self.PersistentId = crc32(hero_id)
            else:
                warn("Player already has all awarded skins")
        elif self.QuestAwardType == DynamicQuestAwardType.RandomTalentFromPool:
            persistentIds = [ str(x).strip() for x in award["TextData"].split(",")]
            talentsCount = len(persistentIds)
            talId = SD.getValueInRange(random.randint(0, talentsCount - 1), 0, talentsCount - 1)
            self.AdditionalData = self.get_talent_refine_from_addit_data(award)

            self.PersistentId = crc32(persistentIds[talId])
            if toint(award["Value"]) > 1:
                for i in xrange(1, toint(award["Value"])):
                    talId = SD.getValueInRange(random.randint(0, talentsCount-1), 0, talentsCount-1)
                    talentAwardId = model.addNewDynamicQuestAward()
                    talentAward = model.getDynamicQuestAwardByID(talentAwardId)
                    talentAward.PersistentId = crc32(persistentIds[talId])
                    talentAward.QuestAwardType = award["AwardType"]
                    talentAward.AdditionalData = self.get_talent_refine_from_addit_data(award)
                    quest.Awards.add(talentAward)
        elif self.QuestAwardType == DynamicQuestAwardType.AlreadyCompletedQuest:
            self.PersistentId = toint(award["Value"])
            self.DbId = award["TextData"]
        elif self.QuestAwardType == DynamicQuestAwardType.Lootbox:
            self.DbId = award["TextData"]
            self.Value = toint(award["Value"])

    def get_talent_refine_from_addit_data(self, award):
        additDataToAwards = '0'

        if 'AdditionalData2' not in award:
            return additDataToAwards

        if not award["AdditionalData2"]:
            return additDataToAwards

        max = CC.max_talent_refine_rate
        additDataInt = toint(award["AdditionalData2"])
        additDataToAwards = award["AdditionalData2"] if 0 < additDataInt <= max else '0'
        return additDataToAwards
