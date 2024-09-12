#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.FinishProductionRequest import FinishProductionRequest
from modeldata.StaticData import StaticData


class Finish_production(SubAction, FinishProductionRequest):
    """action, который будет обрабатывать данный класс"""
    action = "finish_production"
    debug = True


    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        buildings = self.acc.model.Buildings.keys()[:]
        buildings.sort()
        for buildingId in buildings:
            seconds = self.arguments.seconds

            construction = self.acc.model.getConstructionByID(buildingId)
            staticConstruction = self.acc.SD.getStaticConstruction(construction)
            if not staticConstruction:
                #self.errorResponse("Static constr is not found")
                continue

            info(" finish_production: construction: %s %r", staticConstruction['persistentId'], construction.generateJsonDict())

            if construction.ProductionState == ProductionState.Idle:
                debug(" finish_production: skip construction cause ProductionState is Idle" )
                continue

            now = int(round(time.time()))

            if staticConstruction["classType"] == "ProductionBuilding":# or staticConstruction["classType"] == "HouseBuilding":
                # производительность в перод productionTimePeriod
                resourcesToProduce = StaticData.getFirstValue_old(construction.getSingleProductionPriceValue(staticConstruction, construction.Level, "resourcesToProduce", self.acc.SD))
                # ёмкость домика
                constructionCapacity = StaticData.getFirstValue_old(construction.getSingleProductionPriceValue(staticConstruction, construction.Level, "totalProduceCapacity", self.acc.SD))

                if not resourcesToProduce or not constructionCapacity:
                    debug(" finish_production: skip construction: Static construction data doesn't contains required data")
                    continue

                #resourcesToProduce = StaticData.getFirstValue_old(construction.applyPremiumBonus(resourcesToProduce, self.acc.getConfig(), self.acc.SD, self.acc.model))
                #intConstrLimit = StaticData.getFirstValue_old(construction.applyPremiumBonus(constructionCapacity, self.acc.getConfig(), self.acc.SD, self.acc.model))

                #время, за которое здание заполняется полностью и перестает работать
                timeToFillUp = StaticData.roundFloatToInt(constructionCapacity / resourcesToProduce * staticConstruction['productionTimePeriod'])

                moveFrom = self.acc.model.FatClientServerTime
                if not seconds or seconds <= 0:
                    #если узали 0 - сдвигаем время на одно производство
                    timeToFillUp = staticConstruction['productionTimePeriod']
                    seconds = 10
                    moveFrom = construction.StartProductionTime

                #переносим в прошлое время запуска домика
                construction.StartProductionTime = moveFrom - (timeToFillUp - seconds)
                construction.ProductionValue = 0.0
                #construction.BoostEndTime = self.acc.model.FatClientServerTime - seconds

            elif seconds > 0:
                #это возможно еще кому-то где-то надо, но для домиков ресурсов более не используется
                construction.StartProductionTime = now - ( construction.EndProductionTime - construction.StartProductionTime ) + seconds
                construction.EndProductionTime = now + seconds
            else:
                construction.ProductionState = ProductionState.Finished

        self.response["ok"] = 1  # success
        self.fin()
