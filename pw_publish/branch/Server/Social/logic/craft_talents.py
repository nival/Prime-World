# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.CraftTalentsRequest import *
from modeldata.StaticData import StaticData
import math

class Craft_talents( SubAction, CraftTalentsRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "craft_talents"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()

        customValue = self.arguments.customValue
        if customValue < 0:
            warn("[StartBuildingProductionRequest] customValue < 0 ! ") # TODO remove this warn() later
            self.arguments.badParam("customValue") # let self.checkParams() to create an error message

        if not self.checkParams():
            return

        construction = self.arguments.construction

        if construction:
            # Проверка, что здание у нас на в замке, а не на складе
            isFound = False
            for buildingId in self.acc.model.Buildings:
                if construction.getID() == buildingId:
                    isFound = True
                    break

            if not isFound:
                self.errorResponse("Construction not found")
                return

            staticConstruction = self.acc.SD.getStaticConstruction(construction)

            if not staticConstruction['classType'] == "TransmutationBuilding":
                self.errorResponse("Wrong Building")
                return

            levels = staticConstruction['TransmutationLevels']

            price = StaticData.getPriceInterpolated(levels, construction.Level, None, "priceToStart", None)
            price.Perl = 1
            #talentsForCycle = StaticData.getIntInterpolated(levels, construction.Level, None, "perlForBonuse", None)
            talentsForCycle = self.acc.getConfig().EventToolsChangeFields.TRANSMUTATION_TALENTS_PER_PERL
            coef = math.ceil(customValue*1.0/talentsForCycle)

            self.price = self.acc.model.CalcPrice(price, coef, self.acc.SD)
            self.construction = construction
            self.customValue = customValue
            self.needGold = int(self.price.Gold)
            reason = "PW!CRAFT_TALENTS:" + str(construction.PersistentId) + ":" + str(customValue)
            self.buy(self.price, self.onBuy, self.onBuyFunc, reason)
            return None

        self.errorResponse("Construction is null")


    def onBuy(self, response):
        self.onBuyFunc(response)

    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            staticConstruction = self.acc.SD.getStaticConstruction(self.construction)

            self.construction.ProductionCustomValue = self.customValue

            restype = StatisticEventType.TALENT_START

            self.acc.model.addStatisticEvent(restype, "Perl", self.price.Perl)

            self.acc.model.rollTalentsForTransmutationBuilding(self.construction, self.acc, self.I, self.arguments.selectedOrangeSet, self.arguments.selectedRedSet)

            self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.Transmutation,
                                            "craft %s" % self.customValue, self.price, self.acc.model.Resources,
                                            self.arguments.afterContext)

            productionLevel = self.construction.Level
            self.construction.ProductionLevel = self.construction.Level
            fame = StaticData.getIntInterpolated(staticConstruction['TransmutationLevels'], productionLevel, None, "fameToProducePerCrystal", None)
            fame = self.construction.ProductionCustomValue*fame
            self.acc.model.addFame(fame, self.acc, self.acc.SD, self.I.STATS)

            self.response["ok"] = 1 # success
        else:
            self.onBuyError(response, self.needGold)
            return

        self.fin()