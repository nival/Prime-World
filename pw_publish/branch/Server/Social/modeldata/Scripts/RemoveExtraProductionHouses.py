# -*- coding: utf-8 -*-

from base.helpers import *
from binascii import crc32
from StaticData import StaticData
from enums.ProductionState import *

BUILDINGS_TO_REMOVE = ['Production_Silver_fromRes1', 'Production_Crystal', 'Production_Resource1',
                       'Production_Resource2', 'Production_Resource3', 'Storage', 'Library']
HOUSES = [crc32('House_1'), crc32('House_2'), crc32('House_3'), crc32('House_4')]
HOUSE_TO_STAY = 'House_4'
class RemoveExtraProductionHouses:
    oldLevels = None

    def __init__(self):
        if not self.oldLevels:
            with open(os.path.join(os.path.dirname(os.path.realpath(__file__)),
                                   "OldProductionPricesAndCycles/constructionLevels.json"), "r") as f:
                self.__class__.oldLevels = json_loads(f.read())


    def convertModelData( self, env, acc, md, dict ):
        # Сначала убираем все производилки
        for persistentId in self.oldLevels:
            if persistentId not in BUILDINGS_TO_REMOVE:
                continue
            self.processOneBuildingType(acc, md, persistentId)

        # Теперь разберёмся с домиками
        self.processHouses(acc, md)

        return md, acc.db

    def processHouses(self, acc, md):
        buildingId, building, staticBuilding = None, None, None # это про то здание, которое оставляем
        totalBuildings = {}
        maxLevel = 0

        for constructionId, construction in md.ConstructionsKeeper.iteritems():
            staticConstruction = acc.SD.getStaticConstruction(construction)
            if staticConstruction and staticConstruction['persistentId'] == HOUSE_TO_STAY:
                totalBuildings[constructionId] = (construction, staticConstruction)
                if construction.Level >= maxLevel:
                    maxLevel = construction.Level
                    buildingId = constructionId
            # для старых домиков надо вытащить данные их old_levels
            elif construction.PersistentId in HOUSES:
                for id in self.oldLevels:
                    if crc32(id) == construction.PersistentId:
                        totalBuildings[constructionId] = (construction, self.oldLevels[id])
                        break

        # Если домик был, остальные уровни будем навешивать на него
        if buildingId:
            building, staticBuilding = totalBuildings.get(buildingId)
        # Если у пользователя нужного домика и не было, но были другие, надо добавить
        elif len(totalBuildings):
            building, buildingId = md.newConstruction()
            building.PersistentId = crc32(HOUSE_TO_STAY)
            building.StartProductionTime = int(time.time())
            building.ProductionState = ProductionState.Finished
            md.Pocket.add(building)
        # Если домиков и не было, то пойдём отсюда
        else:
            return

        self.processRedundantBuildings(acc, md, building, totalBuildings)

    def processOneBuildingType(self, acc, md, persistentId):
        debug("processOneBuildingType processing %s", persistentId)
        buildingId, building, staticBuilding = None, None, None # это про то здание, которое оставляем
        totalBuildings = {}
        maxLevel = 0

        # найдём все здания одного типа, выделим одно максимального уровня
        for constructionId, construction in md.ConstructionsKeeper.iteritems():
            staticConstruction = acc.SD.getStaticConstruction(construction)
            if staticConstruction and staticConstruction['persistentId'] == persistentId:
                totalBuildings[constructionId] = (construction, staticConstruction)
                if construction.Level >= maxLevel:
                    # Постараемся выбрать здание, которое стоит на сцене
                    if not buildingId or construction.getID() in md.Buildings.keys():
                        maxLevel = construction.Level
                        buildingId = constructionId

        if not buildingId:
            return

        # отделяем здание максимального уровня
        building, staticBuilding = totalBuildings.get(buildingId)
        debug("ProductionValue for main building %r", building.ProductionValue)
        self.processRedundantBuildings(acc, md, building, totalBuildings)
        building.ProductionState = ProductionState.Finished
        if 'minimalCollectTime' in staticBuilding:
            building.StartProductionTime = int(time.time()) - staticBuilding['minimalCollectTime']

    def processRedundantBuildings(self, acc, md, building, totalBuildings):
        #оставляемый домик 30го увроня тоже надо пересчитывать, т.к апать его раньше и теперь вероятнее всего - две большие разницы
        resourcesForUpgrade = StaticData.emptyPrice()
        debug("processRedundantBuildings processing %d buildings", len(totalBuildings))

        for constructionId, (construction, staticConstruction) in totalBuildings.iteritems():
            if staticConstruction:
                price = self.getBuildingPrice(staticConstruction['persistentId'], construction.Level)
                debug("\t level: %d price: %s", construction.Level, price)
                resourcesForUpgrade = StaticData.getAddPrice(resourcesForUpgrade, price)

                # Для складов, библиотек и т.д. этого достаточно. Производственные здания обработаем отдельно
                building.ProductionValue += self.processBuildingWithCycle(construction, staticConstruction, acc, md)

            if building != construction:
                md.Buildings.remove(constructionId)
                md.Pocket.remove(constructionId)

        building.Level = 0
        self.upgradeBuilding(building, acc, md, resourcesForUpgrade)


    def processBuildingWithCycle(self, construction, staticConstruction, acc, md):
        productionValue = 0
        # Вернём деньги за уже запущенные или завершённые циклы
        if staticConstruction['persistentId'] == "Production_Crystal":
            if construction.ProductionState in (ProductionState.Busy, ProductionState.Finished):
                price = self.getProductionCost(acc, construction, staticConstruction, "ProductionLevels")
                if price:
                    md.sell(price, acc, False)
        elif staticConstruction['classType'] == "ProductionBuilding":
            if construction.ProductionState in (ProductionState.Busy, ProductionState.Finished):
                producedResources = self.getProductionBonus(acc, construction, staticConstruction)
                debug("\t producedResources from old cycle: %s", producedResources)
                productionValue += acc.SD.getFirstValue_old(producedResources)
                #md.sell(producedResources, acc, False)
        elif staticConstruction['classType'] == "HouseBuilding":
            if construction.ProductionState in (ProductionState.Busy, ProductionState.Finished):
                producedResources = self.getProductionBonus(acc, construction, staticConstruction)
                md.sell(producedResources, acc, False)
        return productionValue

    def upgradeBuilding(self, building, acc, md, resourcesForUpgrade):
        debug("\t total resources for upgrade: %s", resourcesForUpgrade)
        placePrice = acc.SD.GetBuyPrice(acc.SD.getStaticConstruction(building), acc.getConfig())
        acc.SD.getSubtractPrice(resourcesForUpgrade, placePrice)

        while True:
            upgradePrice, fame = building.getUpgradePrice(acc.SD)
            # Если цены нет - то и улучшать уже некуда
            if upgradePrice:
                upgradePrice['Population'] = 0
                if upgradePrice is not None and acc.SD.isEnoughResources(upgradePrice, resourcesForUpgrade):
                    acc.SD.getSubtractPrice(resourcesForUpgrade, upgradePrice)
                    building.Level += 1
                else:
                    break
            else:
                break

        debug("\t sell resources: %s", resourcesForUpgrade)
        md.sell(resourcesForUpgrade, acc, False)



    def getBuildingPrice(self, persistentId, level, startLevel=0):
        price = StaticData.emptyPrice()
        for item in self.oldLevels[persistentId]["Levels"]["Item"][startLevel:(level+1)]:
            price.Resource1 += item['price']['Resource1']
            price.Resource2 += item['price']['Resource2']
            price.Resource3 += item['price']['Resource3']
            price.Silver += item['price']['Silver']
            price.Population += item['price']['Population']
        return price

    def convertProductionLevels(self, staticConstruction):
        levels = self.oldLevels[staticConstruction['persistentId']]["ProductionLevels"]

        converted_levels = {"Item": []}
        for l in levels['Item']:
            _l = {}
            for k,v in l.iteritems():
                _v = v
                if k == "boosPrice" or k == "resourcesToProduce" or k == "totalProduceCapacity":
                    _v = StaticData.copyPrice(v)
                elif k == "cycles":
                    _v = {"Item": []}
                    for cycle in v["Item"]:
                        _c = {}
                        for ck, cv in cycle.iteritems():
                            _cv = cv
                            if ck == "priceToStart" or ck == "resourcesToProduce":
                                _cv = StaticData.copyPrice(cv)
                            _c[ck] = _cv
                        _v["Item"].append(_c)
                _l[k] = _v
            converted_levels["Item"].append(_l)

        return converted_levels

    def convertHouseLevels(self, staticConstruction):
        levels = self.oldLevels[staticConstruction['persistentId']]['HouseLevels']

        converted_levels = {"Item": []}
        for l in levels['Item']:
            _l = {}
            for k, v in l.iteritems():
                _v = v
                if k == "cycle":
                    _v = {}
                    for ck, cv in v.iteritems():
                        _cv = cv
                        if ck == "priceToStart" or ck == "resourcesToProduce":
                            _cv = StaticData.copyPrice(cv)
                        _v[ck] = _cv
                _l[k] = _v
            converted_levels["Item"].append(_l)

        return converted_levels


    def getProductionCost(self, acc, construction, staticConstruction, customValue):
        if construction.cycle == -1:
            return None

        _convertedOldProductionLevels = self.convertProductionLevels(staticConstruction)

        # Проверим на CustomCycle
        isCustom = False
        if staticConstruction['classType'] == "Production_Crystal":
            if self.oldLevels[staticConstruction['persistentId']]["ProductionLevels"]:
                prLevelFirst, prLevelSecond = StaticData.getInterpolLevels(_convertedOldProductionLevels, construction.Level)
                if prLevelFirst and prLevelSecond:
                    isCustom = prLevelFirst['cycles']['Item'][construction.cycle]['isCustom']
        if isCustom or staticConstruction['persistentId'] == "Production_Crystal":
            actualProduction = self.getNonCustomProductionBonus(acc, construction, staticConstruction)
            actualProduction = acc.SD.getFirstValue_old(actualProduction)

        price = acc.SD.getPriceInterpolated(_convertedOldProductionLevels,
                                            construction.Level, construction.cycle, "priceToStart", None)
        price = acc.model.CalcPrice(price, 1, acc.SD)
        if isCustom and actualProduction:
            ratio = (float(customValue) / float(actualProduction))
            price = acc.model.CalcPrice(price, ratio, acc.SD)
        return price

#    def getFinalPrice(self, price1, price2, level):
#        finalprice = StaticData.emptyPrice()
#        if price1['currentLevel'] == price2['currentLevel']:
#            finalprice = StaticData.addPrice(finalprice, StaticData.copyPrice(price1['Silver']))
#            return finalprice
#
#        coeff = float(level - price1['currentLevel']) / float(price2['currentLevel'] - price1['currentLevel'])
#        finalprice.Silver = StaticData.roundFloatToInt(price1['Silver'] + (price2['Silver'] - price1['Silver']) * coeff)
#        return finalprice

    def getNonCustomProductionBonus(self, acc, construction, staticConstruction):
        _convertedOldProductionLevels = self.convertProductionLevels(staticConstruction)

        if staticConstruction['classType'] == "ProductionBuilding":
            finalprice = StaticData.getPriceInterpolated(_convertedOldProductionLevels,
                                                         construction.Level, construction.cycle, "resourcesToProduce", None)
            if finalprice:
                guildBonusPrice = construction.getGuildBufBonus(finalprice, acc.SD, acc.model,
                                                                construction.cycle, acc.getConfig().GUILD_WARS_ENABLED)
                finalprice = acc.SD.getAddPrice(finalprice, guildBonusPrice)
                finalprice = construction.applyPremiumBonus(finalprice, acc.getConfig(), acc.SD, acc.model)
                return finalprice
        return None

    def getProductionBonus(self, acc, construction, staticConstruction):

        if staticConstruction['classType'] == "ProductionBuilding":
            _convertedOldProductionLevels = self.convertProductionLevels(staticConstruction)
            finalprice = StaticData.getPriceInterpolated(_convertedOldProductionLevels,
                                                         construction.Level, construction.cycle, "resourcesToProduce", None)
            if finalprice:
                guildBonusPrice = construction.getGuildBufBonus(finalprice, acc.SD, acc.model, construction.cycle, acc.getConfig().GUILD_WARS_ENABLED)
                finalprice = acc.SD.getAddPrice(finalprice, guildBonusPrice)
                finalprice = construction.applyPremiumBonus(finalprice, acc.getConfig(), acc.SD, acc.model)
                return finalprice
        elif staticConstruction['classType'] == "HouseBuilding":
            _convertedOldHouseLevels = self.convertHouseLevels(staticConstruction)
            finalprice = acc.SD.getPriceInterpolated(_convertedOldHouseLevels,
                                                     construction.Level, -1, "resourcesToProduce", None)
            finalprice = self.getHousePremiumBonus(construction, finalprice, acc.getConfig(), acc.SD)
            if finalprice:
                return finalprice
        else:
            return None

        return None

    def getHousePremiumBonus(self, construction, price, configData, SD):
        if configData.PREMIUM_ACCOUNT_BONUS:
            if construction.ProductionState != ProductionState.Idle and construction.ProductionPremium:
                construction._updatePriceWithPremium(SD, price, configData.PREMIUM_ACCOUNT_BONUS, False, False)
        return price
