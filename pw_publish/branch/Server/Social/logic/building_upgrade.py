# -*- coding: utf-8 -*-
from subaction import *
from logic.requests.BuildingUpgradeRequest import BuildingUpgradeRequest
from modeldata.Construction import *

class Building_upgrade( SubAction, BuildingUpgradeRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "building_upgrade"

    @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    @parse
    @action_timing
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        construction = self.arguments.building
        ctime = self.arguments.client_time

        if not construction:
            self.errorResponse("Construction is null")
            return

        if ctime > self.acc.model.FatClientServerTime:
            self.errorResponse("Invalid client timestamp")
            return

        staticConstruction = self.acc.SD.getStaticConstruction(construction)
        if staticConstruction:
            if not Construction.canOperateConstruction(staticConstruction, self.acc.model.isInMatchmaking()):
                self.errorResponse("Hero in matchmaking")
                return
        else:
            self.errorResponse("Construction '%s' without StaticConstruction" % construction.PersistentId)
            return

        if not construction.canUpgrade(1, self.acc.SD, self.acc.guilddata):
            self.errorResponse("Construction max level reached")
            return

        self.price, fame = construction.getUpgradePrice( self.acc.SD )
        if not self.price:
            #TODO: странное решение
            construction.Level += 1
        else:
            self.staticConstruction = staticConstruction
            self.construction = construction
            self.ctime = ctime
            self.fame = fame
            self.needGold = int(self.price.Gold)
            reason = "PW!BUILDING_UPGRADE:" + str(construction.PersistentId) + ":" + str(construction.Level+1)
            self.buy(self.price, self.onBuy, self.onBuyFunc, reason)
            return None

        self.response["ok"] = 1 # success
        self.fin()


    @model_callback
    def onBuyFunc( self, response ):
        code = response["code"]
        if code != ibilling.ERROR_CODE_OK:
            self.onBuyError( response, self.needGold )
            return

        self.doConfirmWriteOff( response )
        acc = self.acc
        acc.model.addFame(self.fame, acc, acc.SD, self.I.STATS)
        staticConstruction = self.staticConstruction
        classType = staticConstruction['classType']
        if classType == 'ProductionBuilding':
            self.construction.storeTimeBasedProduction(staticConstruction, "ProductionLevels", acc.getConfig(), acc.SD, acc.model, self.ctime)

        self.construction.Level += 1
        acc.model.addStatisticEvent(StatisticEventType.BUILDING_LEVEL, str(self.construction.PersistentId), self.construction.Level, 1)

        if classType in ("StorageBuilding", "LibraryBuilding", "HouseBuilding"):
            acc.model.calcResourcesLimit(acc.SD, acc.guest)

        if classType == "HouseBuilding":
            acc.model.recalcPopulation( acc.SD, acc.guest )
        elif classType == "HeroesBuilding":
            acc.model.updateHeroesForce( self.I.WS, acc )
        elif classType == "GuildBuilding":
            if self.construction.ProductionState == ProductionState.Idle:
                cycle = acc.SD.getGuildProductionCycle(self.construction.Level)
                if cycle != None:
                    duration = self.construction.getProductionDuration(acc, self.I, 0, self.construction.ProductionCustomValue)[1]
                    self.construction.startProduction( duration, 0, acc.model, acc.SD)
                    self.construction.ResourceToProduce = self.construction.getProductionRandomResource(cycle['percents'], self.makeAccRandom())
            self.construction.getGuildBonusByLevel(acc, self.I)
        elif classType == "Tavern" and self.construction.ProductionState == ProductionState.Idle and acc.getConfigValue("ENABLE_TAVERT_REROLL_ON_LEVELUP"):
            self.construction.rollQuestForTavern(staticConstruction, acc.getConfig(), acc.SD, acc.model)

        self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.BuildingUpgrade,
                                        "%r (id=%r)" % (classType, self.construction.id), self.price, acc.model.Resources, self.arguments.aftercontext)
        self.response["ok"] = 1 # success
        self.fin()


    @action_timing
    def onBuy( self, response ):
        self.onBuyFunc(response)
