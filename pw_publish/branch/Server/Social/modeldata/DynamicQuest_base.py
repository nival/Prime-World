# -*- coding: utf-8 -*-
import time

import CC
from base.helpers import *
from enums import DynamicQuestCheckType, DynamicQuestAwardType, CastleResources
from binascii import crc32

class DynamicQuest_base(object):
    def serializeToFile(self, file, name):
        pass

    def validateLifetime(self):
        if self.QuestEndTime and self.QuestEndTime < int(round(time.time())):
            return False
        return True

    def isComplete(self):
        mainComplete = True
        alternativeComplete = True
        for objectiveId, objective in self.Objectives.iteritems():
            if not objective.IsCompleted:
                mainComplete = False
                break
        for objectiveId, objective in self.AlternativeObjectives.iteritems():
            if not objective.IsCompleted:
                alternativeComplete = False
                break
        # Надо проверить, были ли вообще альтернативные задания
        return (mainComplete and len(self.Objectives)) or (alternativeComplete and len(self.AlternativeObjectives))

    def isMainComplete(self):
        return self.checkObjectives()

    def isAlternativeComplete(self):
        for objectiveId, objective in self.AlternativeObjectives.iteritems():
            if not objective.IsCompleted:
                return False
        return True

    def checkTalentsToPayObjectiveComplete(self, acc, talentsToDeletePersistentIds, objective, addToTalToRemove = False):

        if talentsToDeletePersistentIds is None:
            debug("checkTalentsToPayObjectiveComplete: talentsToDeletePersistentIds is None")
            return False

        debug("start!!! checkTalentsToPayObjectiveComplete")

        countTalentsInTToRemove = self.getCountTalentsInTToRemove(talentsToDeletePersistentIds)
        debug("checkTalentsToPayObjective countTalentsInTToRemove: {}".format(countTalentsInTToRemove))
        debug("checkTalentsToPayObjective sum countTalentsInTToRemove: {}".format(sum(countTalentsInTToRemove.values())))
        countTalentsInLib = self.getCountTalentsInLibAndAddToVerTalToRemove(acc, countTalentsInTToRemove.keys(), objective, countTalentsInTToRemove, addToTalToRemove)
        debug("checkTalentsToPayObjective countTalentsInLib: {}".format(countTalentsInLib))
        if sum(countTalentsInTToRemove.values()) > countTalentsInLib:
            debug("checkTalentsToPayObjective return invalid")
            return False



        debug("return valid checkTalentsToPayObjectiveComplete")
        return True

    def getCountTalentsInTToRemove(self, talentsToDeletePersistentIds):
        # talentsToDeletePersistentIds: [123, 345, 453, 123, 123, 123, 123];
        countTalentInTalentsToRemove = {}
        for persistentId in talentsToDeletePersistentIds:
            if not persistentId in countTalentInTalentsToRemove.keys():
                countTalentInTalentsToRemove[persistentId] = 1
            else:
                countTalentInTalentsToRemove[persistentId] += 1
        debug("checkTalentsToPayObjective countTalentInTalentsToRemove: {}".format(countTalentInTalentsToRemove))
        return countTalentInTalentsToRemove
        # countTalentInTalentsToRemove, countTalentsInTToRemove: {345: 1, 123: 5, 453: 1}

    def getCountTalentsInLibAndAddToVerTalToRemove(self, acc, persistentIds, objective, countTalentsInTToRemove, addToTalToRemove):
        countTalentsInLib = 0
        if addToTalToRemove:
            while len(objective.verifiedTalentsToRemove):
                objective.verifiedTalentsToRemove.pop()
        currentCountInTToRemove = {}
        for _id, talent in acc.model.UserInventory.items():
            if talent.PersistentId in persistentIds:
                if talent.isSoulbounded():  # if is soulbounded
                    continue
                if talent.Owner and talent.Owner.get():  # if in ts
                    continue
                if talent.GuildBankInfo.get():
                    if talent.GuildBankInfo.OwnerId != acc.auid and talent.GuildBankInfo.OwnerId != 0 and talent.GuildBankInfo.HeroClassId == 0:  # if guild talent
                        continue

                if addToTalToRemove:
                    if not talent.PersistentId in currentCountInTToRemove.keys():
                        currentCountInTToRemove[talent.PersistentId] = 1
                    else:
                        currentCountInTToRemove[talent.PersistentId] += 1
                    targetCount = countTalentsInTToRemove[talent.PersistentId]
                    currentCount = currentCountInTToRemove[talent.PersistentId]

                    if currentCount <= targetCount:
                        objective.verifiedTalentsToRemove.append(talent.id)
                        debug("checkTalentsToPayObjective getCountTalents method work... add talent To VerifiedTalentsToRemove")
                    else:
                        debug("checkTalentsToPayObjective getCountTalents method work... founded 1 or more talents... exit for")
                        break

                countTalentsInLib += 1

        return countTalentsInLib

    def checkObjectives(self):
        for objectiveId, objective in self.Objectives.iteritems():
            if not objective.IsCompleted:
                return False
        return True


    def fill(self, questData, timeDelta=0):
        debug("start fill in DynamicQuest_base")
        self.QuestStartTime = questData["QuestStartTime"]
        if timeDelta > 0:
            self.QuestEndTime = int(time.time()) + timeDelta
        else:
            self.QuestEndTime = questData["QuestEndTime"]
        self.QuestDescription = questData["QuestDescription"]
        self.QuestName = questData["QuestName"]
        self.NPCPortret = questData["NPCPortret"]
        self.CompletionText = questData["CompletionText"]
        self.DescriptionImage = questData["DescriptionImageUrl"]
        if questData["AutoAccept"] == "True":
            self.AutoAccept = True
        else:
            self.AutoAccept = False

        if "RepeatOnMiss" in questData and questData["RepeatOnMiss"] == "True":
            self.RepeatOnMiss = True

        if "DependedTournamentQuests" in questData["AcceptFilter"]:
            for questId in questData["AcceptFilter"]["DependedTournamentQuests"]:
                self.DependedTournamentQuests.append(questId)

    def update(self, version, questData, lastId, timeDelta=0):
        self.Version = version
        if not timeDelta:
            self.QuestStartTime = int(questData["QuestStartTime"])
            self.QuestEndTime = int(questData["QuestEndTime"])
        self.QuestDescription = questData["QuestDescription"]
        self.QuestName = questData["QuestName"]
        self.NPCPortret = questData["NPCPortret"]
        for staticObjective in questData["QuestData"]:
            for _id, questObjective in self.Objectives.iteritems():
                if questObjective.EditId == int(staticObjective["EditId"]):
                    questObjective.update(staticObjective, lastId, self)
        for staticObjective in questData["AlternativeQuestData"]:
            for _id, questObjective in self.AlternativeObjectives.iteritems():
                if questObjective.EditId == int(staticObjective["EditId"]):
                    questObjective.update(staticObjective, lastId, self)

    @staticmethod
    def validateJsonQuest(staticQuest):
        debug("start validateJsonQuest in DynamicQuest_base")
        try:
            if staticQuest["QuestEndTime"] != "":
                intVal = int(staticQuest["QuestEndTime"])
            if staticQuest["QuestStartTime"] != "":
                intVal = int(staticQuest["QuestStartTime"])

            acceptFilter = staticQuest["AcceptFilter"]
            if "LastLoginTime" in acceptFilter:
                intVal = int(acceptFilter["LastLoginTime"])
            if "CompletedQuests" in acceptFilter:
                arrVal = acceptFilter["CompletedQuests"][:]
            if "NotCompletedQuests" in acceptFilter:
                arrVal = acceptFilter["NotCompletedQuests"][:]
            if "MissedQuests" in acceptFilter:
                arrVal = acceptFilter["MissedQuests"][:]
            if "DependedTournamentQuests" in acceptFilter:
                arrVal = acceptFilter["DependedTournamentQuests"][:]
            if "NoHero" in acceptFilter and acceptFilter["NoHero"] != "":
                persistentIds = [crc32(h) for h in acceptFilter["NoHero"].split(",")]
            if "NoSkin" in acceptFilter and acceptFilter["NoSkin"] != "":
                persistentIds = [crc32(s) for s in acceptFilter["NoSkin"].split(",")]
            if "NoFlag" in acceptFilter and acceptFilter["NoFlag"] != "":
                persistentIds = acceptFilter["NoFlag"].split(",")
            if "HeroesOfRating" in acceptFilter:
                strVal = acceptFilter["HeroesOfRating"]["Items"]
                intVal = int(acceptFilter["HeroesOfRating"]["Value"])
            if "HeroesOfForce" in acceptFilter:
                strVal = acceptFilter["HeroesOfForce"]["Items"]
                intVal = int(acceptFilter["HeroesOfForce"]["Value"])
            if "HeroesOfLevel" in acceptFilter:
                strVal = acceptFilter["HeroesOfLevel"]["Items"]
                intVal = int(acceptFilter["HeroesOfLevel"]["Value"])
            if "LastPaymentTime" in acceptFilter:
                intVal = int(acceptFilter["LastPaymentTime"])
            if "BuildingOfLevel" in acceptFilter:
                strVal = acceptFilter["BuildingOfLevel"]["Items"]
                intVal = int(acceptFilter["BuildingOfLevel"]["Value"])



            intVal = acceptFilter["MinLordLevel"]
            intVal = acceptFilter["MaxLordLevel"]

            strVal = staticQuest["QuestDescription"]
            strVal = staticQuest["QuestName"]
            strVal = staticQuest["NPCPortret"]
            strVal = staticQuest["CompletionText"]
            strVal = staticQuest["DescriptionImageUrl"]

            objectives = staticQuest["QuestData"][:] + staticQuest["AlternativeQuestData"][:]
            for objective in objectives:
                intVal = objective["EditId"]
                questCheckType = objective["QuestCheckType"]
                if (questCheckType in [DynamicQuestCheckType.SessionInfo, DynamicQuestCheckType.SessionResult]
                    and "SessionCondition" in objective):
                    persistentIds = objective["SessionCondition"]["PickedHero"].split(",")
                    mapIds = objective["SessionCondition"]["GameType"].split(",")
                    intVal = objective["SessionCondition"]["CollectingType"]
                    intVal = objective["SessionCondition"]["TotalValue"]
                    intVal = objective["SessionCondition"]["IncrementPerBattle"]
                    intVal = objective["SessionCondition"]["SessionCheckType"]
                    if "IsGuildGame" in objective["SessionCondition"]:
                        boolVal = bool(objective["SessionCondition"]["IsGuildGame"])
                    if "PlayerPartySize" in objective["SessionCondition"] and "EnemyPartySize" in objective["SessionCondition"]:
                        intVal = objective["SessionCondition"]["PlayerPartySize"]
                        intVal = objective["SessionCondition"]["EnemyPartySize"]
                    if "IsPlayerPartySizeStrongCond" in objective["SessionCondition"] and "IsEnemyPartySizeStrongCond" in objective["SessionCondition"]:
                        intVal = objective["SessionCondition"]["IsPlayerPartySizeStrongCond"]
                        intVal = objective["SessionCondition"]["IsEnemyPartySizeStrongCond"]
                elif questCheckType == DynamicQuestCheckType.Instant and "InstantCondition" in objective:
                    intVal = objective["InstantCondition"]["ResourceType"]
                    strVal = objective["InstantCondition"]["TotalValue"] # TotalValue пришёл стринговым, но мы это исправим

                    # проверяем на правильную скобочную последовательность если ["InstantCondition"]["ResourceType"] == CastleResources.TalentsToPay
                    if objective["InstantCondition"]["ResourceType"] == CastleResources.TalentsToPay:
                        strVal = objective["InstantCondition"]["TotalValue"]
                        stack = []
                        dicc = {'(': ')'}
                        for char in strVal:
                            if char in dicc.keys():
                                stack.append(char)
                            elif char in dicc.values():
                                if len(stack) > 0:
                                    stack.pop()
                                else:
                                    raise Exception(
                                        "Illegal parentheses pairing in QuestTalentsToPayString {}".format(strVal))
                        if len(stack):
                            raise Exception("Illegal parentheses pairing in QuestTalentsToPayString {}".format(strVal))

                elif questCheckType == DynamicQuestCheckType.ModelData and "ModelDataCondition" in objective:
                    intVal = objective["ModelDataCondition"]["TypeToCollect"]
                    persistentIds = objective["ModelDataCondition"]["PersistentId"].split(",")
                    intVal = objective["ModelDataCondition"]["TotalValue"]
                strVal = objective["Description"]
                strVal = objective["ButtonDescription"]

            awards = staticQuest["Awards"][:] + staticQuest["AlternativeAwards"][:]
            for award in awards:
                awardType = award["AwardType"]
                if awardType in [DynamicQuestAwardType.Experience, DynamicQuestAwardType.Gold, DynamicQuestAwardType.Perl,
                    DynamicQuestAwardType.RedPerl, DynamicQuestAwardType.PremiumAcc, DynamicQuestAwardType.Resource1,
                    DynamicQuestAwardType.Resource2, DynamicQuestAwardType.Resource3, DynamicQuestAwardType.Silver, DynamicQuestAwardType.UpgradeHeroTalentsEvent]:
                    intVal = toint(award["Value"])
                elif awardType == DynamicQuestAwardType.RandomTalent:
                    strVal = award["TextData"]
                    if ":" in award["TextData"]:
                        talInfo = award["TextData"].split(":")
                        strVal = talInfo[0]
                        strVal = talInfo[1]
                    intVal = toint(award["Value"])
                    intVal = toint(award["AdditionalData2"])
                    if intVal < 1 or intVal > CC.max_talent_refine_rate:
                        int("Bad RefineLevel - " + str(intVal)) #throw validate exception
                elif awardType in [DynamicQuestAwardType.Construction,
                    DynamicQuestAwardType.Hero, DynamicQuestAwardType.Skin, DynamicQuestAwardType.HeroStatsReset]:
                    intVal = crc32(award["Value"])
                elif awardType == DynamicQuestAwardType.Talent:
                    intVal = crc32(award["TextData"])
                    intVal = toint(award["Value"])
                    intVal = toint(award["AdditionalData2"])
                    if intVal < 1 or intVal > CC.max_talent_refine_rate:
                        int("Bad RefineLevel - " + str(intVal))  # throw validate exception
                elif awardType == DynamicQuestAwardType.HeroExperience:
                    intVal = toint(award["Value"])
                    intVal = crc32(award["TextData"])
                elif awardType == DynamicQuestAwardType.Lamp:
                    lampInfo = award["TextData"].split(":")
                    strVal = lampInfo[0]
                    intVal = toint(lampInfo[1])
                    intVal = toint(lampInfo[2])
                    intVal = toint(lampInfo[3])
                elif awardType == DynamicQuestAwardType.CustomFlag:
                    strVal = award["Value"]
                elif awardType == DynamicQuestAwardType.Quest:
                    intVal = toint(award["Value"])
                elif awardType == DynamicQuestAwardType.RandomHero:
                    persistentIds = award["TextData"].split(",")
                elif awardType == DynamicQuestAwardType.RandomSkin:
                    persistentIds = award["TextData"].split(",")
                elif awardType == DynamicQuestAwardType.RandomTalentFromPool:
                    persistentIds = award["TextData"].split(",")
                    intVal = toint(award["AdditionalData2"])
                    if intVal < 1 or intVal > CC.max_talent_refine_rate:
                        raise Exception("Bad RefineLevel - " + str(intVal))  # throw validate exception
                elif awardType == DynamicQuestAwardType.AlreadyCompletedQuest:
                    persistentIds = award["TextData"].split(",")
                    intVal = toint(award["Value"])
        except Exception:
            info = catch()
            err("Can't add quest %r", staticQuest)
            return False, info
        return True, None

