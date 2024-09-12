# -*- coding: utf-8 -*-

import math, time, datetime, calendar, random, sys
from base.helpers import debug, info, warn, err, err_trace, ClassDict, addRelPath
from base.exceptions import CollectZeroError
from functools import partial
from modeldata.StaticData import StaticData

addRelPath('../thrift_pw/statistics/gen-py')
from StatisticCore.ttypes import ResourceChangeItem
from StatisticCore.ttypes import TalentInfo
from StatisticCore.ttypes import TalentChangeOperation
from enums import *


class ProductionPeriod:
    def __init__(self, s, e, f):
        self.start = s
        self.end = e
        self.functors = [x for x in f]

    def add(self, functor):
        self.functors.append(functor)

    def process_periods(self, production, limit, config, SD, model):
        debug("ProductionPeriod.Process: from " + str(self.start) + " to " + str(self.end) + " with " + self.toString())
        periodPrice = SD.copyPriceFloat(production)
        periodLimit = SD.copyPriceFloat(limit)
        debug("ProductionPeriod.Process: start price: " + str(periodPrice))

        for f in self.functors:
            f(periodPrice, periodLimit, config, SD, model)

        return periodPrice, periodLimit

    def apply_coefficient(self, production, limit, totalProductionTime, SD):
        coefficient = float(self.end - self.start) / totalProductionTime
        debug("ProductionPeriod.ApplyCoefficient: " + str(coefficient) +
              " (totalTime=" + str(totalProductionTime) + ")")
        periodPrice = SD.applyCoeffToPrice(SD.copyPriceFloat(production), coefficient)
        periodLimit = SD.copyPriceFloat(limit)

        return periodPrice, periodLimit

    def toString(self):
        return str(self.start) + "-" + str(self.end) + " " + str([x.func.__name__ if isinstance(x, partial) else x.__name__ for x in self.functors])


class Construction_base:

    def stopProduction( self, acc, I ):
        if self.ProductionState == ProductionState.Busy:
            cycle = self.cycle
            level = self.ProductionLevel
            price = self.getProductionCost( acc, I, level, cycle, self.ProductionCustomValue )

            staticConstruction = acc.SD.getStaticConstruction( self )

            if not staticConstruction:
                warn("stopProduction: staticConstruction is None")
                return
            if staticConstruction['classType'] == "ProductionBuilding":
                self.storeTimeBasedProduction(staticConstruction, "ProductionLevels", acc.getConfig(), acc.SD, acc.model)

            noMoneyBack = staticConstruction and staticConstruction['classType'] == "TransmutationBuilding" and self.CraftedTalents

            if price and not noMoneyBack:
                acc.model.sell( price, acc )
                I.STATS.addResourcesChange( acc.auid, True, ResourceChangeItem.FinishProduction, "%r (id=%r)" % ( staticConstruction['classType'], self.id ), price, acc.model.Resources )
            self.switchToIdle( acc.getConfig(), acc.SD, acc.model )
        if self.ProductionState == ProductionState.Finished:
            self.switchToIdle( acc.getConfig(), acc.SD, acc.model )


    def startProduction( self, duration, cycle, model, SD ):
        staticConstruction = SD.getStaticConstruction( self )
        self.ProductionPremium = model.IsPremiumAccount()
        if duration == 0 and staticConstruction['classType'] == "TransmutationBuilding":
            self.ProductionState = ProductionState.Finished
        else:
            self.ProductionState = ProductionState.Busy

        self.ProductionLevel = self.Level
        self.cycle = cycle
        self.StartProductionTime = int( round( time.time() ) )
        self.EndProductionTime = self.StartProductionTime + duration

    def checkTavernForReroll( self, staticConstruction, config, SD, model ):
        if int(round(time.time())) >= self.BuildingQuest.TimeForReroll:
            self.rollQuestForTavern( staticConstruction, config, SD, model )


    def switchToIdle( self, config, SD, model ):
        staticConstruction = SD.getStaticConstruction( self )
        if staticConstruction and staticConstruction['classType'] == "Tavern" and self.ProductionLevel < self.Level and config.ENABLE_TAVERT_REROLL_ON_LEVELUP:
            self.rollQuestForTavern( staticConstruction, config, SD, model )
        self.ProductionState = ProductionState.Idle
        self.cycle = -1
        self.ProductionPremium = False
        self.StartProductionTime = 0
        self.EndProductionTime = 0
        self.ProductionLevel = 0
        self.BuildingQuest.StatSum = 0


    def emptyAndStopBuilding( self, modeldata, I, acc ):
        #let's stop building first, as empteing it before could change cycle cost.
        self.stopProduction( acc, I )

        staticConstruction = acc.SD.getStaticConstruction( self )
        if staticConstruction['classType'] == "TransmutationBuilding":
            craftedTalents = self.CraftedTalents.keys()[:]
            craftedTalents.sort()
            for talId in craftedTalents:
                talent = modeldata.addTalent(talId)
                talInfo = TalentInfo( talent.PersistentId, talent.getID(), 0 )
                I.STATS.addTalentChange( acc.db.auid, talInfo, TalentChangeOperation.GetFromTransmutation )

                staticTalent = acc.SD.getStaticTalent( talent )
                if staticTalent:
                    modeldata.addStatisticEvent( StatisticEventType.TALENT_FINISH, staticTalent['persistentId'], 1 )
            self.clearCraftedTalents()

        for heroId in self.HeroesInBuilding.keys():
            hero = modeldata.getHeroByID( heroId )
            self.removeHeroFromBuilding( hero, acc, I )

    def removeHeroFromBuilding( self, hero, acc, I ):
        if self.ProductionState == ProductionState.Busy and len(self.HeroesInBuilding) == 1:
            self.stopProduction( acc, I )

        self.HeroesInBuilding.remove( hero )
        hero.InBuildings.remove( self )

        staticConstruction = acc.SD.getStaticConstruction( self )
        if not staticConstruction:
            warn("removeHeroFromBuilding: staticConstruction is None")
            return

        if self.ProductionState == ProductionState.Busy and staticConstruction['classType'] == "Tavern":
            self.BuildingQuest.StatSum = self.getSumStatForTavern(acc.SD, acc, staticConstruction)

    def getBoostPrice(self, SD):
        staticConstruction = SD.getStaticConstruction( self )
        #val = staticConstruction.getSingleProductionPriceValue(staticConstruction, self.Level, "boostPrice")
        price = SD.getPriceInterpolated(staticConstruction["ProductionLevels"], self.Level, None, "boostPrice", None)
        return price

    def getTavernSkipPrice(self, SD):
        staticConstruction = SD.getStaticConstruction( self )
        if staticConstruction['classType'] == "Tavern":
            percentDone = self.getPercentDone()
            if percentDone != None:
                quest = self.getCurrentQuest(staticConstruction)
                if quest and 'estimate' in quest and quest['estimate']:
                    maxGold = quest['estimate']['gold']
                    goldNeed = SD.getActualGold( maxGold, percentDone )
                    return goldNeed
        return 0

    def getSumStatForTavern(self, SD, acc, staticTavern):
        if len(self.HeroesInBuilding) >0:
            quest = self.getCurrentQuest(staticTavern)
            if quest:
                sumStat = 0
                for heroId in self.HeroesInBuilding:
                    hero = acc.model.getHeroByID( heroId )
                    sumStat += int(math.floor(float(acc.model.getHeroMaxLevelStat(hero, quest['statType'], SD)) + 0.5))
                return sumStat
        return 0

    def isDailyQuestConditionFulfilled(self, staticTavern):
        if not self.BuildingQuest.IsDailyQuestFinished:
            quest = self.getCurrentQuest(staticTavern, True)
            if quest:
                return self.BuildingQuest.StatSum >= quest['questStatCount']
        return False

    def getProductionCycleSkipPrice( self, acc, I ):
        # возвращает кол-во голды за которое можно скипануть запущенный цикл производства (после 10.2 в прозиводственных зданиях не используется, т.к. нет циклов)
        SD = acc.SD
        staticConstruction = SD.getStaticConstruction( self )
        levels = staticConstruction['ProductionLevels']

        percentDone = self.getPercentDone()
        if percentDone != None:
            level = self.ProductionLevel
            cycle = self.cycle
            customValue = self.ProductionCustomValue

            prLevelFirst, prLevelSecond = SD.getInterpolLevels( levels, level )

            if prLevelFirst == None or prLevelSecond == None:
                return 0

            maxGold = prLevelFirst['cycles']['Item'][cycle]['timeblock']['gold']
            goldNeed = SD.getActualGold( maxGold, percentDone )

            actualProduction, fame = self.getNonCustomProductionBonus(acc, I, level, cycle)
            actualProduction = SD.getFirstValue_old(actualProduction)
            if actualProduction:
                isCustom = self.isCustomCycle(SD, level, cycle)
                goldPerItem = float(goldNeed) / float(actualProduction)
                if isCustom:
                    goldNeed = SD.roundGold( float(customValue) * float(goldPerItem)* self.getDiscount(SD, acc.getConfig(), level, cycle, customValue, 1)) #GoldType
            return goldNeed
        return 0

    def isCustomCycle(self, SD, level, cycle):
        if cycle == -1:
            return False
        staticConstruction = SD.getStaticConstruction(self)
        if staticConstruction:
            if staticConstruction['classType'] == "ProductionBuilding":
                levels = staticConstruction['ProductionLevels']
                if levels:
                    prLevelFirst, prLevelSecond = SD.getInterpolLevels(levels, level)

                    if prLevelFirst == None or prLevelSecond == None or not prLevelFirst['cycles']:
                        return False

                    return prLevelFirst['cycles']['Item'][cycle]['isCustom']

        return False

    def getDiscount(self, SD, config, level, cycle, customValue, discountType):
        if cycle == -1:
            return 1.0
        staticConstruction = SD.getStaticConstruction( self )
        if staticConstruction:
            if staticConstruction['classType'] == "ProductionBuilding":
                levels = staticConstruction['ProductionLevels']
                if levels:
                    prLevelFirst, prLevelSecond = SD.getInterpolLevels( levels, level )

                    if prLevelFirst == None or prLevelSecond == None:
                        return 1.0

                    if int(prLevelFirst['cycles']['Item'][cycle]['discountType'])& int(discountType) != 0 :
                        if staticConstruction['persistentId'] == "Production_Crystal":
                            if (config.ProductionDiscount.MaxCrystalsForDiscount - config.ProductionDiscount.MinCrystalsForDiscount) != 0:
                                coeff = float(customValue - config.ProductionDiscount.MinCrystalsForDiscount) / float(config.ProductionDiscount.MaxCrystalsForDiscount -config.ProductionDiscount.MinCrystalsForDiscount)
                                percent = min( float(config.ProductionDiscount.MaxDiscount), float(max(0.0, float(config.ProductionDiscount.MaxDiscount * coeff))))
                                return 1.0 - (percent * 0.01)
        return 1.0

    def clearCraftedTalents(self):
        allCrafted = self.CraftedTalents.keys()[:]
        allCrafted.sort()
        for talId in allCrafted:
            self.CraftedTalents.remove(talId)

    def rollQuestForTavern( self, staticTavern, config, SD, model ):
        rollHour = 0
        if config.START_HOUR_FOR_TAVERN_REROLL >=0 and config.START_HOUR_FOR_TAVERN_REROLL <=23:
            rollHour = config.START_HOUR_FOR_TAVERN_REROLL
        curTime = datetime.datetime.utcfromtimestamp(int(round(time.time())))
        needNextDay = False
        if curTime.hour >= rollHour:
            needNextDay = True
        curTime = curTime.replace(hour=rollHour, minute = 0, second=0, microsecond=0)
        timestamp = int(round(calendar.timegm(curTime.timetuple())))
        if needNextDay:
            timestamp += 86400 # add 1 day
        self.BuildingQuest.TimeForReroll = timestamp
        # self.BuildingQuest.TimeForReroll = int(round(time.time())) + 30  # FOR DEBUG

        self.BuildingQuest.IsDailyQuestFinished = False
        self.clearCraftedTalents()

        questsForRoll = []
        minQuestLevel = 0
        if self.Level >= staticTavern['questRollRange']:
            minQuestLevel = self.Level - staticTavern['questRollRange'] +1
        for i in xrange(minQuestLevel, self.Level + 1):
            for index in xrange(0, len(staticTavern['tavernLevelQuests']['Item'][i]['tavernQuests']['Item'])):
                if self.BuildingQuest.Level == i and self.BuildingQuest.Index == index:
                    continue
                quest = []
                quest.append(i)
                quest.append(index)
                questsForRoll.append(quest)

        if len(questsForRoll) == 0:
            return

        val = SD.getValueInRange(model.LordInfo.TavernRandomSeed, 0, len(questsForRoll)-1)
        curQuest = questsForRoll[val]
        self.BuildingQuest.Level = curQuest[0]
        self.BuildingQuest.Index = curQuest[1]

        model.rollTalentForTavernBuilding( self, staticTavern, SD, model.LordInfo.TavernRandomSeed )
        model.LordInfo.TavernRandomSeed = model.getRandom( model.LordInfo.TavernRandomSeed )


    def getCurrentQuest(self, staticTavern, isDailyOnly=False):
        if not self.BuildingQuest.IsDailyQuestFinished and len(staticTavern['tavernLevelQuests']['Item']) > self.BuildingQuest.Level and self.BuildingQuest.Level >= 0:
            levelQuests = staticTavern['tavernLevelQuests']['Item'][self.BuildingQuest.Level]['tavernQuests']
            if levelQuests and len(levelQuests['Item'])> self.BuildingQuest.Index and self.BuildingQuest.Index >= 0:
                return levelQuests['Item'][self.BuildingQuest.Index]
        if isDailyOnly:
            return None
        return staticTavern['patrollQuest']

    def getProductionDuration( self, acc, I, cycle, customValue ):
        modeldata = acc.model
        SD = acc.SD
        if cycle == -1:
            return False, 0
        staticConstruction = SD.getStaticConstruction( self )
        levels = None
        if staticConstruction:
            if staticConstruction['classType'] == "Tavern":
                quest = self.getCurrentQuest(staticConstruction)
                if quest and 'estimate' in quest and quest['estimate'] and quest['estimate']['time'] > 0:
                    return True, quest['estimate']['time']
                return False, 0

            elif staticConstruction['classType'] == "ProductionBuilding":
                levels = staticConstruction['ProductionLevels']
            elif staticConstruction['classType'] == "HouseBuilding":
                levels = staticConstruction['HouseLevels']
            elif staticConstruction['classType'] == "PineTreeBuilding":
                levels = staticConstruction['PineTreeLevels']
            elif staticConstruction['classType'] == "FirstBuyBuilding":
                levels = staticConstruction['FirstBuyLevels']
            elif staticConstruction['classType'] == "TransmutationBuilding":
                levels = staticConstruction['TransmutationLevels']

            level = self.Level
            if self.ProductionState == ProductionState.Busy and self.cycle == cycle:
                level = self.ProductionLevel

            if levels:
                prLevelFirst, prLevelSecond = SD.getInterpolLevels( levels, level )

                if prLevelFirst == None or prLevelSecond == None:
                    return False, 0
                elif staticConstruction['classType'] == "ProductionBuilding":
                    baseDuration = prLevelFirst['cycles']['Item'][cycle]['timeblock']['time']
                    if self.isCustomCycle(SD, level, cycle):
                        actualProduction, fame = self.getNonCustomProductionBonus(acc, I, level, cycle)
                        actualProduction = SD.getFirstValue_old(actualProduction)
                        if actualProduction:
                            durationPerItem = float(baseDuration) / float(actualProduction)
                            baseDuration = SD.roundGold( float(customValue) * float(durationPerItem)* self.getDiscount(acc.SD, acc.getConfig(), level, cycle, customValue, 2)) #TimeType
                    return True, baseDuration
                elif staticConstruction['classType'] == "TransmutationBuilding":
                    return True, staticConstruction['time']
                else:
                    return True, prLevelFirst['cycle']['timeblock']['time']

            if staticConstruction['classType'] == "GuildBuilding":
                cycle = SD.getGuildProductionCycle(level)
                if cycle != None:
                    return True, cycle['timeblock']['time']
            elif staticConstruction['classType'] == "GoldProductionBuilding":
                cycle = staticConstruction['HouseLevels']['Item'][0]['cycle']
                if cycle != None:
                    return True, int(cycle['timeblock']['time'])

        return False, 0


    def getProductionCost( self, acc, I, level, cycle, customValue ):
        if cycle == -1:
            return None
        #it's bath
        staticConstruction = acc.SD.getStaticConstruction( self )
        levels = None
        if staticConstruction:
            if staticConstruction['classType'] == "Tavern":
                quest = self.getCurrentQuest(staticConstruction)
                if quest and 'priceToStart' in quest and quest['priceToStart']:
                    return acc.SD.copyPrice(quest['priceToStart'] )
                return None

            if staticConstruction['classType'] == "HouseBuilding":
                finalprice = acc.model.createResourcesTable()
                return finalprice

            if staticConstruction['classType'] == "ProductionBuilding":
                #в 10.2 производственные здания не требуют ресурсов для производства, т.к. они работают постоянно
                return None

            elif staticConstruction['classType'] == "TransmutationBuilding":
                levels = staticConstruction['TransmutationLevels']

            if levels:
                if staticConstruction['classType'] == "TransmutationBuilding":
                    cycle = None

                price = acc.SD.getPriceInterpolated( levels, level, cycle, "priceToStart", None )

                if staticConstruction['persistentId'] == "Production_Crystal":
                    price = acc.model.CalcPrice( price, 1, acc.SD )

                if staticConstruction['persistentId'] == "Talent_Production":
                    #getPriceInterpolated может вернуть None!
                    if price is None:
                        err("StaticData.getPriceInterpolated returned None for construction: %r with levels %r, level = %s, cycle = %s",
                            staticConstruction, levels, level, cycle)
                    else:
                        price.Perl = 1
                        price = acc.model.CalcPrice( price, customValue, acc.SD )
                return price
        return None

    def getNonCustomProductionBonus(self, acc, I, level, cycle ):
        staticConstruction = acc.SD.getStaticConstruction( self )
        if staticConstruction:
            if staticConstruction['classType'] == "ProductionBuilding":
                debug("getNonCustomProductionBonus: cycle %r, %s", cycle, type(cycle))
                finalprice = acc.SD.getPriceInterpolated( staticConstruction['ProductionLevels'], level, cycle, "resourcesToProduce", None )
                fame = acc.SD.getIntInterpolated( staticConstruction['ProductionLevels'], level, cycle, "fameToProduce", None )
                if finalprice and fame != None:
                    guildBonusPrice = self.getGuildBufBonus(finalprice, acc.SD, acc.model, cycle, acc.getConfig().GUILD_WARS_ENABLED)
                    finalprice = acc.SD.getAddPrice(finalprice, guildBonusPrice)
                    finalprice = self.applyPremiumBonus(finalprice, acc.getConfig(), acc.SD, acc.model)
                    return finalprice, fame
        return None, None


    def getProduction( self, acc, I, level, cycle, clientTime = None ):
        staticConstruction = acc.SD.getStaticConstruction( self )
        if staticConstruction:
            if staticConstruction['classType'] == "Tavern":
                finalprice = None
                if len(self.HeroesInBuilding) > 0:
                    expFull = acc.SD.getTavernQuestExpBonus(staticConstruction, staticConstruction['patrollQuest'], level)
                    expFull = self.getTavernExpPremiumBonus(expFull, acc.getConfig(), acc.SD, acc.model)
                    if expFull:
                        heroExp = float(expFull)/float(len(self.HeroesInBuilding))
                        for heroId in self.HeroesInBuilding:
                            hero = acc.model.getHeroByID( heroId )
                            staticHero = acc.SD.getStaticHero( hero )
                            if staticHero:
                                currentHeroExp = acc.SD.getHeroExpBonusInTavern(hero, staticConstruction, heroExp)
                                hero.changeExperience( currentHeroExp, acc.model, I.WS, acc, I )

                if self.isDailyQuestConditionFulfilled(staticConstruction):
                    curQuest = self.getCurrentQuest(staticConstruction, True)
                    if len(self.CraftedTalents):
                        craftedTalents = self.CraftedTalents.keys()[:]
                        craftedTalents.sort()
                        for talId in craftedTalents:
                            talent = acc.model.addTalent(talId)
                            talInfo = TalentInfo(talent.PersistentId, talent.getID(), 0)
                            I.STATS.addTalentChange(acc.db.auid, talInfo, TalentChangeOperation.GetFromTavern)

                    else:
                        expFull = acc.SD.getTavernQuestExpBonus(staticConstruction, curQuest, level)
                        expFull = self.getTavernExpPremiumBonus(expFull, acc.getConfig(), acc.SD, acc.model)
                        if expFull:
                            if len(self.HeroesInBuilding) > 0:
                                heroExp = float(expFull)/float(len(self.HeroesInBuilding))
                                for heroId in self.HeroesInBuilding:
                                    hero = acc.model.getHeroByID( heroId )
                                    staticHero = acc.SD.getStaticHero( hero )
                                    if staticHero:
                                        currentHeroExp = acc.SD.getHeroExpBonusInTavern(hero, staticConstruction, heroExp)
                                        hero.changeExperience( currentHeroExp, acc.model, I.WS, acc, I )
                        else:
                            finalprice = acc.SD.getConvertedTavernQuestResources(staticConstruction, curQuest, level)
                            finalprice = self.applyPremiumBonus(finalprice, acc.getConfig(), acc.SD, acc.model)

                    if curQuest:
                        acc.model.addStatisticEvent(StatisticEventType.DAILY_COMPLETE, curQuest['statType'], int(self.BuildingQuest.StatSum))

                self.BuildingQuest.IsDailyQuestFinished = True
                self.clearCraftedTalents()
                return finalprice, 0

            if staticConstruction['classType'] == "ProductionBuilding":
                finalprice, fame = self.getProductionBuildingBonus(staticConstruction, "ProductionLevels", acc.getConfig(), acc.SD, acc.model, clientTime)
                if finalprice and (fame is not None):
                    if self.isCustomCycle(acc.SD, level, cycle):
                        famePerItem = float(fame) / float(acc.SD.getFirstValue_old(finalprice))
                        fame = acc.SD.roundGold(self.ProductionCustomValue * famePerItem)
                        acc.SD.overrideNonZeroValuesInPrice(finalprice, self.ProductionCustomValue)
                    return finalprice, fame

            elif staticConstruction['classType'] == "HouseBuilding":
                err_trace("getProduction call for HouseBuilding")
                return None, None # No production in houses!
                # https://confluence.nivalnetwork.com/display/dot/Castle+Buildings+Resources#CastleBuildingsResources-%D0%9D%D0%BE%D0%B2%D1%8B%D0%B5%D0%BD%D0%B0%D1%81%D1%82%D1%80%D0%BE%D0%B9%D0%BA%D0%B8%D0%B7%D0%B4%D0%B0%D0%BD%D0%B8%D0%B9
                #finalprice, fame = self.getTimeBasedProduction(staticConstruction, "HouseLevels", acc.getConfig(), acc.SD, acc.model)
                #if finalprice and fame != None:
                #    return finalprice, fame

            elif staticConstruction['classType'] == "PineTreeBuilding":
                cycle = -1
                finalprice = acc.SD.getPriceInterpolated( staticConstruction['PineTreeLevels'], level, cycle, "resourcesToProduce", None )
                fame = acc.SD.getIntInterpolated( staticConstruction['PineTreeLevels'], level, cycle, "fameToProduce", None )
                finalprice = self.applyPremiumBonus(finalprice, acc.getConfig(), acc.SD, acc.model)
                if finalprice and fame != None:
                    return finalprice, fame

            elif staticConstruction['classType'] == "FirstBuyBuilding":
                cycle = -1
                finalprice = acc.SD.getPriceInterpolated( staticConstruction['FirstBuyLevels'], level, cycle, "resourcesToProduce", None )
                fame = acc.SD.getIntInterpolated( staticConstruction['FirstBuyLevels'], level, cycle, "fameToProduce", None )
                if finalprice and fame != None:
                    finalprice = self.getFirstBuyProductionRandomPrice(finalprice)
                    finalprice = self.applyPremiumBonus(finalprice, acc.getConfig(), acc.SD, acc.model)
                    return finalprice, fame

            elif staticConstruction['classType'] == "GuildBuilding":
                cycleGuild = acc.SD.getGuildProductionCycle(level)
                if cycleGuild != None:
                    finalprice = acc.SD.copyPrice(cycleGuild['resourcesToProduce'])
                    fame = cycleGuild['fameToProduce']
                    if finalprice and fame != None:
                        finalprice = self.applyPremiumBonus(finalprice, acc.getConfig(), acc.SD, acc.model)
                        return finalprice, fame

            elif staticConstruction['classType'] == "GoldProductionBuilding":
                cycle = -1
                price, fame = self.getGoldHouseProduction(staticConstruction)
                finalprice = acc.SD.copyPrice(price)
                finalprice = self.applyPremiumBonus(finalprice, acc.getConfig(), acc.SD, acc.model)
                if finalprice and fame != None:
                    return finalprice, fame
            else:
                return None, None
        else:
            return None, None

        return None, None

    _premiumAffectedBuildings = ("ProductionBuilding", "FirstBuyBuilding", "HouseBuilding", "PineTreeBuilding", "GuildBuilding", "Tavern")

    def applyPremiumBonus(self, price, configData, SD, model, force=False):
        staticConstruction = SD.getStaticConstruction(self)
        premiumAccountBoost = (
            configData.PREMIUM_ACCOUNT_TAVERN_BONUS if staticConstruction['classType'] == "Tavern" else
            configData.PREMIUM_ACCOUNT_BONUS)
        full = staticConstruction['classType'] in ("PineTreeBuilding", "GuildBuilding")
        if force:
            return self._updatePriceWithPremium(SD, price, premiumAccountBoost, full, False)
        if staticConstruction['classType'] in self._premiumAffectedBuildings:
            if premiumAccountBoost:
                if self.isPremiumProduction(model, SD):
                    self._updatePriceWithPremium(SD, price, premiumAccountBoost, full, False)
        return price

    def applyFloatPremiumBonus(self, price, configData, SD, model, force=False):
        staticConstruction = SD.getStaticConstruction(self)
        premiumAccountBoost = (
            configData.PREMIUM_ACCOUNT_TAVERN_BONUS if staticConstruction['classType'] == "Tavern" else
            configData.PREMIUM_ACCOUNT_BONUS)
        full = staticConstruction['classType'] in ("PineTreeBuilding", "GuildBuilding")
        if force:
            return self._updatePriceWithPremium(SD, price, premiumAccountBoost, full, True)
        if staticConstruction['classType'] in self._premiumAffectedBuildings:
            if premiumAccountBoost:
                if self.isPremiumProduction(model, SD):
                    self._updatePriceWithPremium(SD, price, premiumAccountBoost, full, True)
        return price

    @staticmethod
    def _updatePriceWithPremium(SD, price, premiumAccountBoost, full, floatResult):
        debug("Update price with premium")
        if floatResult:
            price.Resource1 = price.Resource1 * premiumAccountBoost
            price.Resource2 = price.Resource2 * premiumAccountBoost
            price.Resource3 = price.Resource3 * premiumAccountBoost
            price.Silver = price.Silver * premiumAccountBoost
            price.Shard = price.Shard * premiumAccountBoost
            if full:
                price.Perl = price.Perl * premiumAccountBoost
                price.RedPerl = price.RedPerl * premiumAccountBoost
            return price
        else:
            price.Resource1 = SD.roundFloatToInt(price.Resource1 * premiumAccountBoost)
            price.Resource2 = SD.roundFloatToInt(price.Resource2 * premiumAccountBoost)
            price.Resource3 = SD.roundFloatToInt(price.Resource3 * premiumAccountBoost)
            price.Silver = SD.roundFloatToInt(price.Silver * premiumAccountBoost)
            price.Shard = SD.roundFloatToInt(price.Shard * premiumAccountBoost)
            if full:
                if price.Perl != 0:
                    price.Perl = SD.roundFloatToInt(price.Perl * premiumAccountBoost)
                if price.RedPerl != 0:
                    price.RedPerl = SD.roundFloatToInt(price.RedPerl * premiumAccountBoost)
            return price

    def getGuildBufBonus(self, price, SD, model, cycle, guildBuffsEnabled):
        if not guildBuffsEnabled:
            return SD.emptyPrice()

        staticConstruction = SD.getStaticConstruction(self)
        if staticConstruction['classType'] == "ProductionBuilding":
            bonusPrice = SD.emptyPrice()
            for bufId in model.GuildBufs:
                buf = model.getGuildBufByID(bufId)
                if not buf.IsEnabled:
                    continue

                staticBonus = SD.getGuildBufById(buf.PersistentId)
                for bonus in staticBonus['bonuses']['Item']:
                    if bonus['classType'] == 'CastleResourceBonus':
                        if price.get(bonus['resource']):
                            if SD.isValidCycleForGuildBuf(cycle, bonus):
                                bonusPrice[bonus['resource']] += SD.roundFloatToInt(price.get(bonus['resource']) * float(bonus['modifiers']['multiplicativeValue']))
                                bonusPrice[bonus['resource']] += SD.roundFloatToInt(float(bonus['modifiers']['additiveValue']))
        return bonusPrice

    def isPremiumProduction(self, model, SD):
        staticConstruction = SD.getStaticConstruction(self)
        isTimeBased = False
        if staticConstruction['classType'] == "ProductionBuilding":
            isTimeBased = model.IsPremiumAccount()
        return (self.ProductionState != ProductionState.Idle and self.ProductionPremium) or isTimeBased

    def getTavernExpPremiumBonus(self, exp, configdata, SD, model):
        premiumAccountBoost = configdata.PREMIUM_ACCOUNT_TAVERN_BONUS
        if premiumAccountBoost:
            if self.isPremiumProduction(model, SD):
                exp = SD.roundFloatToInt(exp * premiumAccountBoost)
        return exp

    def getPercentDone( self ):
        if self.ProductionState == ProductionState.Busy:
            length = float(self.EndProductionTime - self.StartProductionTime)
            curTime = float(time.time() - self.StartProductionTime)
            if length == 0:
                return None
            percentDone = int( curTime/length * 100)
            return percentDone
        return None

    def getGuildBonusByLevel( self, acc, I ):
        statPoints = acc.SD.getGuildStatPointsBonus( self.Level )
        if statPoints:
            for heroId in acc.model.Heroes:
                hero = acc.model.getHeroByID( heroId )
                for tsId in hero.TalentSets.keys():
                    ts = hero.TalentSets[tsId]
                    ts.GuildStats.StatPoints += statPoints

    def getGuildBonusFull( self, acc, I ):
        guildStatpoints  = 0
        guildLevel = self.Level
        if guildLevel >= 0:
            for lvl in xrange( 0, guildLevel + 1 ):
                guildStatpoints += acc.SD.getGuildStatPointsBonus( lvl )

        if guildStatpoints:
            for heroId in acc.model.Heroes:
                hero = acc.model.getHeroByID( heroId )
                for tsId in hero.TalentSets.keys():
                    ts = hero.TalentSets[tsId]
                    ts.GuildStats.StatPoints = guildStatpoints

    def canUpgrade( self, addLevel, SD, guilddata ):
        guildExp = -1
        if guilddata:
            guildExp = long(guilddata.GuildLevelInfo.Experience)

        staticBuilding = SD.getStaticConstruction( self )
        level = self.Level+addLevel

        if staticBuilding['classType'] == "GuildBuilding" :
            if guildExp == -1 or SD.getGuildLevel(guildExp) < level:
                return False
        if level < len(staticBuilding['Levels']['Item']):
            return True
        return False

    def canBoost( self, SD ):
        staticBuilding = SD.getStaticConstruction( self )
        if staticBuilding['persistentId'] == "Production_Crystal":
            return True
        return False

    @staticmethod
    def canOperateConstruction( staticConstruction, inMatchmaking ):
        #Отключили ограничение при нахождении в мм
        #if staticConstruction['classType'] == "HeroesBuilding" and inMatchmaking:
        #return False
        return True


    def getUpgradePrice( self, SD ):
        staticBuilding = SD.getStaticConstruction( self )
        level = self.Level + 1
        if level < len(staticBuilding['Levels']['Item']):
            return SD.copyPrice(staticBuilding['Levels']['Item'][level]['price']), staticBuilding['Levels']['Item'][level]['fame']
        return None, None


    @staticmethod
    def sellConstruction( building, staticBuilding, level, modeldata, SD, realSell, STATS, acc, removeFromPocket, afterContext=False ):
        if staticBuilding['Levels'] == "" or staticBuilding['Levels']['Item'] == None:
            return

        buildingPrice = SD.getBuildingPrice(staticBuilding, level)
        price = ClassDict()
        price.Gold = 0

        if realSell: price.Perl = SD.roundFloatToInt(buildingPrice.Perl*float(staticBuilding['SellPricePercent']))
        else: price.Perl = SD.roundFloatToInt(buildingPrice.Perl)

        if realSell: price.RedPerl = SD.roundFloatToInt(buildingPrice.RedPerl*float(staticBuilding['SellPricePercent']))
        else: price.RedPerl = SD.roundFloatToInt(buildingPrice.RedPerl)

        if realSell: price.Resource1 = SD.roundFloatToInt(buildingPrice.Resource1*float(staticBuilding['SellPricePercent']))
        else: price.Resource1 = SD.roundFloatToInt(buildingPrice.Resource1)

        if realSell: price.Resource2 = SD.roundFloatToInt(buildingPrice.Resource2*float(staticBuilding['SellPricePercent']))
        else: price.Resource2 = SD.roundFloatToInt(buildingPrice.Resource2)

        if realSell: price.Resource3 = SD.roundFloatToInt(buildingPrice.Resource3*float(staticBuilding['SellPricePercent']))
        else: price.Resource3 = SD.roundFloatToInt(buildingPrice.Resource3)

        if realSell: price.Silver = SD.roundFloatToInt(buildingPrice.Silver*float(staticBuilding['SellPricePercent']))
        else: price.Silver = SD.roundFloatToInt(buildingPrice.Silver)

        price.Population = 0
        if not removeFromPocket:
            price.Population = SD.roundFloatToInt(buildingPrice.Population)

        if realSell: price.Resource1_Rare = SD.roundFloatToInt(buildingPrice.Resource1_Rare*float(staticBuilding['SellPricePercent']))
        else: price.Resource1_Rare = SD.roundFloatToInt(buildingPrice.Resource1_Rare)

        if realSell: price.Resource2_Rare = SD.roundFloatToInt(buildingPrice.Resource2_Rare*float(staticBuilding['SellPricePercent']))
        else: price.Resource2_Rare = SD.roundFloatToInt(buildingPrice.Resource2_Rare)

        if realSell: price.Resource3_Rare = SD.roundFloatToInt(buildingPrice.Resource3_Rare*float(staticBuilding['SellPricePercent']))
        else: price.Resource3_Rare = SD.roundFloatToInt(buildingPrice.Resource3_Rare)

        modeldata.sell( price, acc )
        STATS.addResourcesChange( acc.auid, True, ResourceChangeItem.BuildingSell,
                                  "%r (id=%r)" % ( staticBuilding['classType'], building.id ),
                                  price, modeldata.Resources, afterContext )


    def getMaxPopulation( self, staticConstruction, SD ):
        if staticConstruction['classType'] == "HouseBuilding" or staticConstruction['classType'] == "GoldProductionBuilding":
            return SD.getIntInterpolated( staticConstruction['HouseLevels'], self.Level, None, "currentMaxPopulation", 0 )
        return 0


    def getTavernMaxHeroesCount( self, staticConstruction, SD ):
        if staticConstruction['classType'] == "Tavern":
            return SD.getIntInterpolated( staticConstruction['tavernLevels'], self.Level, None, "heroesCount", 0 )
        return 0

    def getFirstBuyProductionRandomResource( self, staticConstruction, randValue):
        percents = staticConstruction['FirstBuyLevels']['Item'][0]['cycle']['percents']
        return self.getProductionRandomResource(percents, randValue)

    def getGoldHouseProduction(self, construction):
        price = construction['HouseLevels']['Item'][0]['cycle']['resourcesToProduce']
        fame = int(construction['HouseLevels']['Item'][0]['cycle']['fameToProduce'])
        return price, fame

    def getProductionRandomResource( self, percents, randValue):
        totalPercents = percents['Item'][0]+percents['Item'][1]+percents['Item'][2]+percents['Item'][3]+percents['Item'][4]+percents['Item'][5]+percents['Item'][6]
        if totalPercents == 0:
            return CastleResources.Resource1
        randValue = randValue % totalPercents + 1;
        curPercent = percents['Item'][0]
        if ( randValue <= curPercent ):
            return CastleResources.Silver
        curPercent += percents['Item'][1]
        if ( randValue <= curPercent ):
            return CastleResources.Perl
        curPercent += percents['Item'][2]
        if ( randValue <= curPercent ):
            return CastleResources.Resource1
        curPercent += percents['Item'][3]
        if ( randValue <= curPercent ):
            return CastleResources.Resource2
        curPercent += percents['Item'][4]
        if ( randValue <= curPercent ):
            return CastleResources.Resource3
        curPercent += percents['Item'][5]
        if (randValue <= curPercent):
            return CastleResources.RedPerl
        curPercent += percents['Item'][6]
        if (randValue <= curPercent):
            return CastleResources.Shard

    def getFirstBuyProductionRandomPrice(self, price):
        final_price = StaticData.emptyPrice()
        if self.ResourceToProduce is None:
            return final_price
        resource_name = StaticData.getCastleResourceTypeName(self.ResourceToProduce)
        if resource_name is None or resource_name == '':
            return final_price
        final_price[resource_name] = price[resource_name]
        return final_price

    def placeBuilding( self, x, y, pitch, planId, rid, staticConstruction, acc, iDict ):
        self.PersistentId = planId
        self.Position.X = x
        self.Position.Y = y
        self.Position.Pitch = pitch

        if staticConstruction['classType'] == "HouseBuilding":
            self.ProductionState = ProductionState.Idle

        if staticConstruction['classType'] == "ProductionBuilding":
            self.StartProductionTime = acc.model.FatClientServerTime
            self.ProductionState = ProductionState.Busy

        if staticConstruction['classType'] == "FirstBuyBuilding" or staticConstruction['classType'] == "PineTreeBuilding" \
                or staticConstruction['classType'] == "GoldProductionBuilding" \
                or (staticConstruction['classType'] == "GuildBuilding" and acc.SD.getGuildProductionCycle(self.Level) != None):
            duration = self.getProductionDuration( acc, iDict, 0, 0 )[1]
            self.startProduction( duration, 0, acc.model, acc.SD )
        acc.model.Buildings.add( self )

        # Если добавили склад - пересчитаем лимиты
        if staticConstruction['classType'] == "StorageBuilding" or staticConstruction['classType'] == "LibraryBuilding" \
                or staticConstruction['classType'] == "HouseBuilding" or staticConstruction['classType'] == "FirstBuyBuilding" \
                or staticConstruction['classType'] == "GoldProductionBuilding":
            acc.model.calcResourcesLimit( acc.SD, acc.guest )

        acc.model.initialPlaceOnScene( iDict.WS, acc, staticConstruction, self, rid, acc.SD, iDict )




    def _addProductionPeriod(self, periods, t1, t2, functor):
        debug("Try to add period from " + str(t1) + " to " + str(t2))
        if t2 <= t1:
            return periods
        res = []
        if not periods:
            res.append(ProductionPeriod(t1,t2,[functor]))
            return res

        for period in periods:
            ps = period.start
            pe = period.end

            if t1 > pe or t2 < ps:
                res.append(ProductionPeriod(ps, pe, period.functors))
                continue

            if t1 > ps:
                res.append(ProductionPeriod(ps, t1, period.functors))
                ps = t1
            if t2 < pe:
                newSubPeriod = ProductionPeriod(ps, t2, period.functors)
                newSubPeriod.add(functor)
                res.append(newSubPeriod)
                res.append(ProductionPeriod(t2, pe, period.functors))
            else:
                newSubPeriod = ProductionPeriod(ps, pe, period.functors)
                newSubPeriod.add(functor)
                res.append(newSubPeriod)

        return res

    def _updateProducedWithBosted(self, production, limit, config, SD, model):
        staticConstruction = SD.getStaticConstruction( self )
        if self.canBoost(SD):
            production.Resource1 = production.Resource1 * 2.0
            production.Resource2 = production.Resource2 * 2.0
            production.Resource3 = production.Resource3 * 2.0
            production.Silver = production.Silver * 2.0
            production.Perl = production.Perl * 2.0
        else:
            debug("_updateProducedWithBosted: can't boost %s", staticConstruction["persistentId"])

        #debug("_updateProducedWithBosted: %r", production)
        #return production, limit

    def _updateProducedWithPremium(self, production, limit, config, SD, model):
        self.applyFloatPremiumBonus(production, config, SD, model, True)
        self.applyPremiumBonus(limit, config, SD, model, True)
        debug("_updateProducedWithPremium: %r", production)
        #return production, limit

    def _dummyFunctor(self, production, limit, config, SD, model):
        pass
        #return production, limit

    def _updateProduceWithBuff(self, production, limit, config, SD, model, buffId):
       self.applyBuffBonus(SD, production, limit, buffId)

    def _addProductionPeriodForBufs(self, model, SD, timePeriods, StartProductionTime, callback):
        t = timePeriods
        for bufId in model.GuildBufs:
            buf = model.getGuildBufByID(bufId)
            if not buf.IsEnabled:
                continue

            _callback = partial(callback, buffId=buf.PersistentId)
            t = self._addProductionPeriod(t, StartProductionTime, buf.ExpireTime, _callback)
        return t

    def productionPerCycles(self, staticConstruction, levels, config, SD, model, serverTime, totalProductionTime, coefficient, limitProduction, initialValue):
        timePeriods = []
        if coefficient != 0:
            debug("Add dummy period")
            timePeriods = self._addProductionPeriod(timePeriods, self.StartProductionTime, serverTime, self._dummyFunctor)

            debug("Add boosted period")
            timePeriods = self._addProductionPeriod(timePeriods, self.StartProductionTime, self.BoostEndTime, self._updateProducedWithBosted)

            debug("Add buff period")
            timePeriods = self._addProductionPeriodForBufs(model, SD, timePeriods, self.StartProductionTime, self._updateProduceWithBuff)

            debug("Add premium period")
            timePeriods = self._addProductionPeriod(timePeriods, self.StartProductionTime, model.LordInfo.PremiumAccountEnd, self._updateProducedWithPremium)

        interpolatedProductionResult = SD.getPriceInterpolated(staticConstruction[levels], self.Level, None,
                                                               "resourcesToProduce", None, True)

        interpolatedLimit = SD.getPriceInterpolated(staticConstruction[levels], self.Level, None,
                                                    "totalProduceCapacity", None, True)
        interpolatedFame = SD.getFloatInterpolated(staticConstruction[levels], self.Level, None, "fameToProduce", None)

        debug("Before process: interpolatedProductionResult=" + str(
            interpolatedProductionResult) + "; interpolatedLimit=" + str(
            interpolatedLimit) + "; interpolatedFame=" + str(interpolatedFame) + "; initialValue=" + str(
            initialValue) + ";")

        if interpolatedProductionResult and interpolatedLimit and interpolatedFame:
            productionResult = SD.emptyPrice()
            limitedProductionValue = initialValue
            limit = SD.emptyPrice()
            periods = sorted(timePeriods, key=lambda x: x.start)
            for period in periods:
                productionEthalone, limitEthalone = period.process_periods(interpolatedProductionResult, interpolatedLimit, config, SD,
                    model)
                productionInPeriod, limitInPeriod = period.apply_coefficient(productionEthalone, limitEthalone,
                                                                             totalProductionTime, SD)
                debug("period result: %r", productionInPeriod)
                productionInTime = SD.copyPriceFloat(productionInPeriod)
                productionInTime = SD.applyCoeffToPrice(productionInTime, coefficient)
                productionInTimeValue = SD.getFirstValue_old(productionInTime, 0)
                SD.getAddPrice(productionResult, productionInPeriod)
                if limit == SD.emptyPrice():
                    limit = SD.copyPriceFloat(limitEthalone)
                limitValue = SD.getFirstValue_old(limitInPeriod, 0)

                if limitValue > limitedProductionValue:
                    limitedProductionValue += min(productionInTimeValue, limitValue - limitedProductionValue)
                debug("productionPerCycles: cumulative production=" + str(productionResult))
                debug("productionPerCycles: limited production=" + str(limitedProductionValue))

            if limit == SD.emptyPrice():
                limit = SD.copyPriceFloat(interpolatedLimit)

            limitedProduction = SD.copyPriceFloat(interpolatedProductionResult)
            limitedProduction = SD.overrideNonZeroValuesInPrice(limitedProduction, limitedProductionValue)
            debug("sum periods result: %r", productionResult)
            if limitProduction:
                return limitedProduction, SD.getFirstValue_old(limit, 0), interpolatedFame
            return productionResult, SD.getFirstValue_old(limit, 0), interpolatedFame

        return None, None, None, None

    def applyBuffBonus(self, SD, interpolatedProductionResult, interpolatedLimit, buffId):
        if not buffId:
            return

        staticConstruction = SD.getStaticConstruction(self)
        staticBonus = SD.getGuildBufById(buffId)
        for bonus in staticBonus['bonuses']['Item']:
            if not bonus:
                continue

            if bonus['classType'] != 'CastleResourceBonus':
                continue

            affected = False
            for building in bonus['buildingsToAffect']['Item']:
                debug( "buildingsToAffect: %r", building['persistentId'] )
                if building['persistentId'] == staticConstruction['persistentId']:
                    affected = True
                    break

            if not affected:
                continue

            if float(bonus['modifiers']['additiveValue']):
                production = SD.copyPriceFloat(interpolatedProductionResult)
                limit = SD.copyPriceFloat(interpolatedLimit)
                debug("Apply add bonus to " + str(interpolatedProductionResult))
                SD.getAddValuePrice(bonus["resource"], interpolatedProductionResult, float(bonus['modifiers']['additiveValue']))
                debug("production result: " + str(interpolatedProductionResult))
                SD.getAddPrice(interpolatedLimit, SD.applyCoeffToPrice(SD.getDividePrice(limit, production), float(bonus['modifiers']['additiveValue'])))
                debug("limit result: " + str(interpolatedLimit))
            elif float(bonus['modifiers']['multiplicativeValue']):
                SD.applyCoeffToPrice(interpolatedProductionResult, 1.0 + float(bonus['modifiers']['multiplicativeValue']))
                SD.applyCoeffToPrice(interpolatedLimit, 1.0 + float(bonus['modifiers']['multiplicativeValue']))

    def isStopped(self):
        return self.StartProductionTime == 0

    def getProductionBuildingBonus(self, staticConstruction, levels, config, SD, model, clientTime = None):
        """Calculates produced resource amount, return it's part to put into storage and corresponding fame value"""
        if clientTime is None:
            clientTime = model.FatClientServerTime

        # здание ничего не производит, если было остановленно перед этим
        if self.isStopped():
            return None, None

        totalProductionTime = clientTime - self.StartProductionTime
        if totalProductionTime == 0 and self.ProductionValue < 0.01:
            return None, None

        debug("getProductionBuildingBonus: clientTime=" + str(clientTime))
        timeCoefficient = float(totalProductionTime) / staticConstruction['productionTimePeriod']
        debug("getProductionBuildingBonus: timeCoefficient=" + str(timeCoefficient))
        productionResult, limit, interpolatedFame = self.productionPerCycles(
            staticConstruction, levels, config, SD, model, clientTime, totalProductionTime, timeCoefficient, True,
            self.ProductionValue)

        return self.getStorageLimitedProduction(productionResult, productionResult, interpolatedFame, limit, SD, model)

    def getStorageLimitedProduction(self, productionResult, productionValue, interpolatedFame, limit, SD, model):
        intProduction = 0
        resultFame = 0
        debug("After prepare: productionResult=" + str(productionResult) + "; limit=" + str(
            limit) + "; productionValue=" + str(productionValue) + "; interpolatedFame=" + str(interpolatedFame))

        # GetTimeBasedProductionBonus
        if productionResult and interpolatedFame and productionValue and limit is not None:
            # готовая к выгрузке продукция - только целая часть
            debug("pre limit: %r", limit)
            intProduction = int(SD.getFirstValue_old(productionResult))
            debug("post limitedProduction: %r", SD.getFirstValue_old(productionResult))
            if intProduction:
                # Сколько есть места на основном складе
                debug("model.ResourcesLimit: %r", model.ResourcesLimit.generateJsonDict())
                resourceLimit = SD.getSameValueFromOtherPrice(productionResult, model.ResourcesLimit)
                mdLimit = resourceLimit - SD.getSameValueFromOtherPrice(productionResult, model.Resources)
                if resourceLimit and intProduction > mdLimit:
                    intProduction = mdLimit  # выгружаем из домика не больше, чем влазит на склад
            self.ProductionValue = SD.getFirstValue_old(productionResult) - intProduction
            resultFame = interpolatedFame * float(intProduction) / limit
        if intProduction:
            return SD.overrideNonZeroValuesInPrice(productionResult, intProduction), resultFame
        else:
            raise CollectZeroError()

    def storeTimeBasedProduction(self, staticConstruction, levels, config, SD, model, clientTime = None):
        if clientTime is None:
            clientTime = model.FatClientServerTime

        if self.isStopped():
            return

        totalProductionTime = clientTime - self.StartProductionTime
        if self.ProductionState == ProductionState.Idle or totalProductionTime <= 0:
            return

        timeCoefficient = float(totalProductionTime) / staticConstruction['productionTimePeriod']
        productionResult, limit, interpolatedFame = self.productionPerCycles(
            staticConstruction, levels, config, SD, model, clientTime, totalProductionTime, timeCoefficient, True,
            self.ProductionValue)
        debug("storeTimeBasedProduction: productionResult=" + str(productionResult))

        if productionResult:
            self.ProductionValue = SD.getFirstValue_old(productionResult, 0)
        self.StartProductionTime = clientTime


    def recalcMDindex( self, inc, config ):
        # Генерируем "рандомно" mdIndex
        # mdIndex = 0xABCDEFGH
        random.seed()
        # A - просто рандомное число от 0 до 7
        A = random.randint(0, 7)
        # B - счетчик, от 0 до 15
        B = (self.mdIndex & 0x0F000000) >> 24
        # C - просто рандомное число от 0 до 15
        C = random.randint(0, 15)
        # D - просто рандомное число от 0 до 15
        D = random.randint(0, 15)

        if not inc:
            B = 0
        else:
            if B + 1 < 15:
                B += 1
            else:
                B = config.NUM_CHEAT_CYCLES

        needVise = False
        if B >= config.NUM_CHEAT_CYCLES:
            if random.randint(0, 100) >= config.PERCENT_TO_CYCLES_CHANGE:
                needVise = True

        self.mdIndex = self.genMDIndex( A, B, C, D, needVise )


    @staticmethod
    def genMDIndex( A, B, C, D, needVise ):
        if needVise:
            E = C^3
            F = 1^D^2
            G = 2^D
            H = E
        else:
            E = C^3
            F = 1^D^2
            G = 1^D
            H = C
        index = 0
        index += A << 28
        index += B << 24
        index += C << 20
        index += D << 16
        index += E << 12
        index += F << 8
        index += G << 4
        index += H << 0
        return index

    @staticmethod
    def getSingleProductionPriceValue(staticConstruction, level, valueKey, SD):
        price = SD.getPriceInterpolated(staticConstruction["ProductionLevels"], level, None, valueKey, None)
        return None if not price else price
