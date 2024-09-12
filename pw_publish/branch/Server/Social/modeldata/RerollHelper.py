# -*- coding: utf-8 -*-
from base.helpers import *
import math

class RerollHelper:
    def __init__(self, SD):
        self.SD = SD
    def needRerollProbabilities(self, rollList, currentWeights, oldProbabilitiesList, config):
        for persistentId, staticGroup in config.EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS.iteritems():
            if str(persistentId) not in currentWeights:
                return True
            defaultWeight = config.getRollWeightByRollTimes(staticGroup.LevelToWeights, 0)
            if currentWeights[str(persistentId)] != defaultWeight:
                for persistentId in oldProbabilitiesList:
                    oldProbabilitiesList[persistentId] = max(0.0, oldProbabilitiesList[persistentId])
                return True
        if len(config.EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS) != len(currentWeights):
            return True
        for key, probability in rollList.iteritems():
            if probability != 0:
                return False
        return True

    def resetProbabilities(self, rollList, weightList, oldProbabilitiesList, rerolls, config):
        sumWeight = 0
        probabilitiesList = {}
        # Сначала найдём текущие веса групп и суммарный вес
        for persistentId, staticGroup in config.EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS.iteritems():
            newWeight = config.getRollWeightByRollTimes(staticGroup.LevelToWeights, rerolls)
            weightList[str(persistentId)] = newWeight
            sumWeight += newWeight
        # Высчитаем процент для каждой группы
        for persistentId in weightList:
            probabilitiesList[persistentId] = float(weightList[persistentId])/sumWeight*100
            groupProbability = probabilitiesList[persistentId]
            if persistentId in oldProbabilitiesList:
                groupProbability += oldProbabilitiesList[persistentId]
            if groupProbability > 0:
                rollList[persistentId] = random.randint(math.floor(groupProbability), math.ceil(groupProbability))
                oldProbabilitiesList[persistentId] = groupProbability - rollList[persistentId]
            else:
                rollList[persistentId] = 0
                oldProbabilitiesList[persistentId] = groupProbability
        # Проверим, нет ли каких-то лишних (старых) групп в списке у пользователя
        if len(weightList) != len(config.EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS):
            for persistentId in weightList.keys():
                if (toint(persistentId) not in config.EventToolsChangeFields.REROLL_SHOP_GROUP_WEIGHTS):
                    del weightList[persistentId]
                    del rollList[persistentId]
                    del oldProbabilitiesList[persistentId]

        for persistentId in weightList.keys():
            if not self.SD.getStaticRerollShopGroupById(toint(persistentId)):
                debug("ResetProbabilities: delete probabilities %s", persistentId)
                del weightList[persistentId]
                del rollList[persistentId]
                del oldProbabilitiesList[persistentId]


    def getNewGroup(self, rollProbabilities, acc):
        # находим суммарный вес всех элементов всех групп
        totalSum = 0
        for probability in rollProbabilities.values():
            totalSum += probability
        # берём случайное число из диапазона весов
        rolledProbability = acc.SD.getValueInRange(random.randint(0, totalSum), 0, totalSum)
        probabilityToFit = 0
        # находим группу, которая подходит под найденное число
        for key in rollProbabilities.keys():
            probabilityToFit += rollProbabilities[key]
            # когда группа нашлась, уменьшаем её вес и возвращаем id группы
            if probabilityToFit >= rolledProbability and rollProbabilities[key] != 0:
                rollProbabilities[key] -= 1
                return int(key)