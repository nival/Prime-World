# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetBoostedProductionRequest import *

class Set_boosted_production( SubAction, SetBoostedProductionRequest ):
    """Ставит для всех зданий, меющих буст, время начала производства, время начала буста и кол-во ресурсов на складе"""
    action = "set_boosted_production"
    debug = True
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        for _id, building in self.acc.model.Buildings.iteritems():
            staticConstruction = self.acc.SD.getStaticConstruction(building)
            if staticConstruction["classType"] == "ProductionBuilding" and staticConstruction["hasCustomProductionBoost"]:
                building.StartProductionTime = self.acc.model.FatClientServerTime - self.arguments.startTime
                building.BoostEndTime = self.acc.model.FatClientServerTime - self.arguments.boostStartTime + self.acc.getConfig().TOTAL_BOOST_TIME
                building.ProductionValue = self.arguments.valueInBuilding

        self.response["ok"] = 1
        self.fin()