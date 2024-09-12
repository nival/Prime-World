# -*- coding: utf-8 -*-
from base.helpers import *
from binascii import crc32   # zlib version is not cross-platform
from enums.ProductionState import *
from StaticData import StaticData

UPGRADELEVELS = (
 {'Population': 16,  'Resource1':      0,  'Resource2':   375,  'Resource3':     0},
 {'Population': 17,  'Resource1':      0,  'Resource2':   100,  'Resource3':   100},
 {'Population': 18,  'Resource1':    270,  'Resource2':     0,  'Resource3':   145},
 {'Population': 19,  'Resource1':    460,  'Resource2':   250,  'Resource3':     0},
 {'Population': 20,  'Resource1':    720,  'Resource2':     0,  'Resource3':   390},
 {'Population': 20,  'Resource1':   1040,  'Resource2':   560,  'Resource3':     0},
 {'Population': 20,  'Resource1':   1430,  'Resource2':     0,  'Resource3':   770},
 {'Population': 20,  'Resource1':   1890,  'Resource2':  1020,  'Resource3':     0},
 {'Population': 20,  'Resource1':   2420,  'Resource2':     0,  'Resource3':  1300},
 {'Population': 20,  'Resource1':   9100,  'Resource2':  4900,  'Resource3':     0},
 {'Population': 20,  'Resource1':  11175,  'Resource2':     0,  'Resource3':  6025},
 {'Population': 20,  'Resource1':  13500,  'Resource2':  7275,  'Resource3':     0},
 {'Population': 20,  'Resource1':  16075,  'Resource2':     0,  'Resource3':  8650},
 {'Population': 20,  'Resource1':  18900,  'Resource2': 10175,  'Resource3':     0},
 {'Population': 20,  'Resource1':  21975,  'Resource2':     0,  'Resource3': 11825},
 {'Population': 20,  'Resource1':  25325,  'Resource2': 13650,  'Resource3':     0},
 {'Population': 20,  'Resource1':  28975,  'Resource2':     0,  'Resource3': 15600},
 {'Population': 20,  'Resource1':  32875,  'Resource2': 17700,  'Resource3':     0},
 {'Population': 20,  'Resource1':  37050,  'Resource2':     0,  'Resource3': 19950},
 {'Population': 20,  'Resource1':  41550,  'Resource2': 22350,  'Resource3':     0},
 {'Population': 20,  'Resource1':  46300,  'Resource2':     0,  'Resource3': 24950},
 {'Population': 20,  'Resource1':  51350,  'Resource2': 27650,  'Resource3':     0},
 {'Population': 20,  'Resource1':  56700,  'Resource2':     0,  'Resource3': 30550},
 {'Population': 20,  'Resource1':  62350,  'Resource2': 33600,  'Resource3':     0},
 {'Population': 20,  'Resource1':  68350,  'Resource2':     0,  'Resource3': 36800},
 {'Population': 20,  'Resource1':  74600,  'Resource2': 40150,  'Resource3':     0},
 {'Population': 20,  'Resource1':  81200,  'Resource2':     0,  'Resource3': 43700},
 {'Population': 20,  'Resource1':  88100,  'Resource2': 47450,  'Resource3':     0},
 {'Population': 20,  'Resource1':  95350,  'Resource2':     0,  'Resource3': 51350},
 {'Population': 20,  'Resource1': 102900,  'Resource2': 55400,  'Resource3':     0},
)

TRANSMUTLEVELS = {'Item': (
# используем только Silver, остальные цены были по 0, а в кристаллах цена фиксированная
    {'currentLevel':  0, 'Silver': 260},
    {'currentLevel':  4, 'Silver': 240},
    {'currentLevel': 11, 'Silver': 205},
    {'currentLevel': 29, 'Silver': 115},
)}

# ResourceN_Rare, Gold, Silver и Perl убраны, они всё равно были 0
def getBuildingPrice(level, startLevel=0):
    price = StaticData.emptyPrice()
    for item in UPGRADELEVELS[(startLevel):(level+1)]:
        price.Resource1 += item['Resource1']
        price.Resource2 += item['Resource2']
        price.Resource3 += item['Resource3']
        price.Population += item['Population']
    return price


def getFinalPrice(price1, price2, level):
    finalprice = StaticData.emptyPrice()
    if price1['currentLevel'] == price2['currentLevel']:
        finalprice.Silver = price1['Silver']
        return finalprice

    coeff = float(level - price1['currentLevel']) / float(price2['currentLevel'] - price1['currentLevel'])
    finalprice.Silver = StaticData.roundFloatToInt(price1['Silver'] + (price2['Silver'] - price1['Silver']) * coeff)
    return finalprice


def getProductionCost(acc, level, cycle, customValue):
    if cycle == -1:
        return None
    price1, price2 = StaticData.getInterpolLevels(TRANSMUTLEVELS, level)
    if price1 == None or price2 == None:
        return None
    price = getFinalPrice(price1, price2, level)
    price.Perl = 1
    price = acc.model.CalcPrice(price, customValue, acc.SD)
    return price


class DelevelTransmutation:
    """
    Понизить уровень кузницы/сада до 1, вернуть ресурсы, потраченные на прокачку.
    Также выполняет то, что было в RemoveExtraTransmutation -- удаляет лишние кузни/сады, возвращая за них ресы.
    Совмещение необходимо, поскольку в StaticData больше нет таблицы цен апгрейда -- она есть только в этом модуле.
    """

    def convertModelData(self, env, acc, md, dict):
        buildingId, building, staticBuilding = None, None, None # это про то здание, которое оставляем
        transmutationBuildings = {}
        maxLevel = 0

        # найдём все кузницы, выделим одну максимального уровня
        for constructionId, construction in md.ConstructionsKeeper.iteritems():
            staticConstruction = acc.SD.getStaticConstruction(construction)
            if staticConstruction and staticConstruction['classType'] == "TransmutationBuilding":
                transmutationBuildings[constructionId] = (construction, staticConstruction)
                if construction.Level >= maxLevel:
                    maxLevel = construction.Level
                    buildingId = constructionId

        if not buildingId:
            return md, acc.db

        # отделяем здание максимального уровня
        building, staticBuilding = transmutationBuildings.pop(buildingId)

        # за остальные возвращаем ресурсы
        if len(transmutationBuildings) >= 1:
            for constructionId, (construction, staticConstruction) in transmutationBuildings.iteritems():
                if staticConstruction:
                    price = getBuildingPrice(construction.Level)
                    md.sell(price, acc, False)
                    # Вернём деньги за уже запущенные или завершённые циклы
                    if construction.ProductionState in (ProductionState.Busy, ProductionState.Finished):
                        price = getProductionCost(acc, construction.ProductionLevel, construction.cycle, construction.ProductionCustomValue)
                        if price:
                            acc.model.sell(price, acc, True)
                md.Buildings.remove(constructionId)
                md.Pocket.remove(constructionId)

        if buildingId and building:
            # Вернём деньги за процесс в оставшейся кузнице (в этот акк не заходили со времён, когда процесс был долгий)
            if building.ProductionState in (ProductionState.Busy, ProductionState.Finished):
                price = getProductionCost(acc, building.ProductionLevel, building.cycle, building.ProductionCustomValue)
                if price:
                    acc.model.sell(price, acc, True)
                building.clearCraftedTalents()
                building.switchToIdle(acc.getConfig(), acc.SD, acc.model)

            # И теперь снижаем уровень до 1
            # цена апгрейдов, без цены начальной покупки
            price = getBuildingPrice(building.Level, 1)
            md.sell(price, acc, False)
            building.Level = 0
            building.ProductionLevel = 0

        return md, acc.db

