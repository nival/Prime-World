# -*- coding: utf-8 -*-
from subaction import *
from logic.requests.CollectProductionResultsRequest import CollectProductionResultsRequest
from base.exceptions import CollectZeroError
from modeldata.ModelDataCustom import FAT_CLIENT_SERVER_TIME_MAX_LAG

_AUTO_CONTNUE = frozenset(("FirstBuyBuilding", "PineTreeBuilding", "GoldProductionBuilding"))
_TIME_BASED = frozenset(("", "ProductionBuilding"))

class Collect_production_results(SubAction, CollectProductionResultsRequest):
    """action, который будет обрабатывать данный класс"""
    action = "collect_production_results"

    @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return
        if self.I.Config.getMainConfig().CHECK_REQUESTS_REPEATABILITY and self.checkRid(self.action):
            return self.errorResponse(EC.BAD_PARAM, "bad param rid")

        constr = self.arguments.construction
        ctime = self.arguments.client_time

        debug("Collect_production_results: ServerTime %s, client_time %s", self.acc.model.ServerTime, ctime)

        staticConstruction = self.acc.SD.getStaticConstruction(constr)
        if not staticConstruction:
            self.errorResponse("Static constr is not found")
            return

        if ctime > self.acc.model.FatClientServerTime or (self.acc.model.FatClientServerTime - ctime) > FAT_CLIENT_SERVER_TIME_MAX_LAG:
            self.errorResponse("Invalid client timestamp")
            return

        if not self.isFinished(constr, self.acc.model, self.acc.getConfig(), self.acc.SD, staticConstruction, ctime):
            self.errorResponse(EC.CANT_COLLECT_RESOURCES,
                               "Can't collect production from building that not in finished state")
            return

        findInPocket = False
        for constructionId in self.acc.model.Pocket.keys():
            if constructionId == constr.getID():
                findInPocket = True
                break

        if findInPocket:
            self.errorResponse(EC.CANT_COLLECT_RESOURCES,
                               "Can't collect production from building that in pocket now" )
            return

        cType = staticConstruction['classType']
        debug("Collect_production_results: construction cycle: %s", constr.cycle)
        try:
            finalprice, fame = constr.getProduction(self.acc, self.I, constr.ProductionLevel, constr.cycle, ctime)
        except CollectZeroError:
            self.errorResponse(EC.CANT_COLLECT_RESOURCES, "Can't collect production from building that hasn't produced anything yet.")
            return


        debug("Collect_production_results: getProduction returns price %s, fame %s, stored in building %s", finalprice, fame, constr.ProductionValue)

        if finalprice:
            self.acc.model.sell(finalprice, self.acc)
            if cType != "Tavern":
                self.acc.model.addProductionFinishEvent(staticConstruction['persistentId'], finalprice)
            self.I.STATS.addResourcesChange(self.acc.auid, True, ResourceChangeItem.FinishProduction,
                                            "%r (id=%r)" % (cType, constr.id), finalprice, self.acc.model.Resources)
            self.acc.model.addFame(fame, self.acc, self.acc.SD, self.I.STATS)

        # по умолчанию выставляем "работающий" стейт после удачного скликивания
        constr.ProductionState = ProductionState.Busy

        if self.isAutoContinue(cType, constr.Level):
            debug("Collect_production_results: isAutoContinue")
            duration = constr.getProductionDuration(self.acc, self.I, constr.cycle, constr.ProductionCustomValue)[1]
            constr.startProduction(duration, 0, self.acc.model, self.acc.SD)
            if cType == "FirstBuyBuilding":
                constr.ResourceToProduce = constr.getFirstBuyProductionRandomResource(staticConstruction, self.makeAccRandom())
            elif cType == "GuildBuilding":
                cycle = self.acc.SD.getGuildProductionCycle(constr.ProductionLevel)
                if cycle != None:
                    constr.ResourceToProduce = constr.getProductionRandomResource(cycle['percents'], self.makeAccRandom())
        elif self.isTimeBased(cType):
            debug("Collect_production_results: isTimeBased")
            constr.StartProductionTime = ctime
        else:
            # этот тип зданий не умеет работать - переводим его в стейт idle
            debug("Collect_production_results: NOT (isAutoContinue OR isTimeBased)")
            constr.switchToIdle( self.acc.getConfig(), self.acc.SD, self.acc.model )

        if cType == "Tavern":
            constr.checkTavernForReroll( staticConstruction, self.acc.getConfig(), self.acc.SD, self.acc.model )

        if cType == "GoldProductionBuilding":
            self.needGold = finalprice.Gold
            self.construction = constr
            self.I.BILL.replenish( self.acc.db.auid, finalprice.Gold, "GoldBuilding production finished", self.onReplenish )
            return

        self.response["ok"] = 1 # success
        self.fin()


    def isAutoContinue(self, cType, level):
        return (cType in _AUTO_CONTNUE) or (cType == "GuildBuilding" and self.acc.SD.getGuildProductionCycle(level) is not None)

    def isTimeBased(self, cType):
        return cType in _TIME_BASED

    @staticmethod
    def isFinished(construction, model, config, SD, staticConstruction, clientTime):
        if staticConstruction['classType'] in 'ProductionBuilding':
            debug("Collect_production_results: construction.StartProductionTime=%s, minimalCollectTime=%s",
                  str(construction.StartProductionTime), staticConstruction['minimalCollectTime'])

            minimalTimeCoefficient = staticConstruction['minimalCollectTime'] / staticConstruction[
                'productionTimePeriod']
            (minProductionResult, limit,
             interpolatedFame) = construction.productionPerCycles(staticConstruction, "ProductionLevels", config, SD,
                                                                  model,
                                                                  construction.StartProductionTime + staticConstruction[
                                                                      'minimalCollectTime'],
                                                                  staticConstruction['minimalCollectTime'],
                                                                  minimalTimeCoefficient, True, 0)

            productionTime = clientTime - construction.StartProductionTime
            productionTime = productionTime  if productionTime >=0 else 0
            currentTimeCoefficient = productionTime / staticConstruction['productionTimePeriod']
            (currentResourcesToClick, limit,
             interpolatedFame) = construction.productionPerCycles(staticConstruction, "ProductionLevels", config, SD,
                                                                  model, clientTime, productionTime,
                                                                  currentTimeCoefficient, True,
                                                                  construction.ProductionValue)
            debug("minimalResourcesToClick = " + str(SD.getFirstValue_old(minProductionResult, 0)))
            debug("currentResourcesToClick = " + str(SD.getFirstValue_old(currentResourcesToClick, 0)))
            return ((staticConstruction['minimalCollectTime'] < productionTime) or
                    (SD.getFirstValue_old(currentResourcesToClick, 0) > SD.getFirstValue_old(minProductionResult, 0)))
        else:
            return construction.ProductionState == ProductionState.Finished

    @model_callback
    def onReplenish( self, response ):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.response["ok"] = 1 # success
        else:
            # вернём изменения обратно, а то пользователь потеряет свой золотой
            duration = self.construction.getProductionDuration(self.acc, self.I, 0, self.construction.ProductionCustomValue)[1]
            self.construction.ProductionState = ProductionState.Finished
            self.construction.StartProductionTime = int(round(time.time())) - duration
            self.construction.EndProductionTime = int(round(time.time()))
            self.onBuyError(response, self.needGold)
            return

        self.fin()
