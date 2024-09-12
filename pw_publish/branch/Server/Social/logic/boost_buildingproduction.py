# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BoostBuildingProductionRequest import *
from modeldata.Construction import *

class Boost_buildingproduction( SubAction, BoostBuildingProductionRequest ):
    """ выставляем флаг и время окончания Ускорения производства, если это возможно """
    action = "boost_buildingproduction"

    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        construction = self.arguments.construction
        ctime = self.arguments.client_time

        if not construction:
            self.errorResponse("Construction is null")
            return

        if ctime > self.acc.model.FatClientServerTime:
            self.errorResponse("Invalid client timestamp")
            return

        debug("boost_buildingproduction: construction.StartProductionTime = %s, client_time = %s", construction.StartProductionTime, ctime)

        staticConstruction = self.acc.SD.getStaticConstruction(construction)
        if staticConstruction:
            if not Construction.canOperateConstruction(staticConstruction, self.acc.model.isInMatchmaking()):
                self.errorResponse("Hero in matchmaking")
                return
        else:
            self.errorResponse("Construction '%s' without StaticConstruction" % construction.PersistentId)
            return

        if not construction.canBoost(self.acc.SD):
            self.errorResponse("Construction max level reached")
            return

        self.price = construction.getBoostPrice( self.acc.SD )
        if not self.price:
            self.errorResponse("Construction is hasn't boost price")
            return
        else:
            self.staticConstruction = staticConstruction
            self.construction = construction
            self.ctime = ctime
            self.needGold = int(self.price.Gold)
            reason = "PW!BUILDING_BOOST:" + str(construction.PersistentId) + ":" + str(construction.Level)
            self.buy(self.price, self.onBuy, self.onBuyFunc, reason)
            return None

        self.response["ok"] = 1  # success
        self.fin()


    @model_callback
    def onBuyFunc( self, response ):
        code = response["code"]
        if code != ibilling.ERROR_CODE_OK:
            self.onBuyError( response, self.needGold )
            return

        self.doConfirmWriteOff( response )
        acc = self.acc
        staticConstruction = self.staticConstruction
        classType = staticConstruction['classType']
        debug("boost_buildingproduction: classType=" + str(classType))
        if classType == 'ProductionBuilding':
            self.construction.storeTimeBasedProduction(staticConstruction, "ProductionLevels", acc.getConfig(), acc.SD, acc.model, self.ctime)

        self.construction.BoostEndTime = self.ctime + self.acc.getConfig().TOTAL_BOOST_TIME
        debug("boost_buildingproduction: set self.construction.BoostEndTime to " + str(self.construction.BoostEndTime))

        acc.model.addStatisticEvent(StatisticEventType.BUILDING_BOOST, staticConstruction['persistentId'], 0)
        self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.BoostProduction,
                                        "%r (id=%r)" % (classType, self.construction.id), self.price,
                                        acc.model.Resources, self.arguments.afterContext)

        self.response["ok"] = 1 # success
        self.fin()


    @action_timing
    def onBuy( self, response ):
        self.onBuyFunc(response)