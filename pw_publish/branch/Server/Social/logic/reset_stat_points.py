#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ResetStatPointsRequest import ResetStatPointsRequest


class Reset_stat_points(SubAction, ResetStatPointsRequest):
    """action, который будет обрабатывать данный класс"""
    action = "reset_stat_points"

    @model_callback  # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

            # if self.arguments.hero.InMatchmaking:
            # self.errorResponse( EC.HERO_IN_MATCHMAKING, "Hero in matchmaking" )
            # return
        self.tsId = self.arguments.talent_set_id
        self.priceCoef = self.acc.SD.getStatsResetPriceCoef()

        self.hero = self.arguments.hero
        if self.hero.areStatPointsReset(self.tsId):
            self.errorResponse(EC.HERO_STATS_ARE_ALREADY_RESET, "Hero stat points are already reset")
            return

        levelScale = 1
        if self.acc.getConfigValue("USE_LEVEL_SCALE_FOR_RESET_PRICE"):
            levelScale = self.acc.SD.getHeroExpLevel(self.hero.Experience) + 1
        self.price = self.acc.model.CalcPrice(self.priceCoef, levelScale, self.acc.SD)

        if self.price and not all(v == 0 for k, v in self.price.iteritems()):
            self.needGold = int(self.price.Gold)
            reason = "PW!RESET_HERO_STATS:" + str(self.hero.PersistentId)

            self.buy(self.price, self.onBuy, self.onBuyFunc, reason)
            return
        else:
            #PF-99353 получили нулевой прайз, ну ок
            self.hero.resetHeroStatPoints(self.acc, self.tsId)
            self.response["ok"] = 1
        self.fin()

    @model_callback
    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            self.hero.resetHeroStatPoints(self.acc, self.tsId)
            self.hero.CalcForce(self.acc.model, self.I.WS, self.acc, self.tsId)

            self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.ResetHeroStats,
                                            "%r (id=%r)" % (self.hero.PersistentId, self.hero.id),
                                            self.price, self.acc.model.Resources, self.arguments.afterContext)
            self.response["ok"] = 1  # success
        else:
            self.onBuyError(response, self.needGold)
            return

        self.fin()

    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)
