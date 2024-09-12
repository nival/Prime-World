# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ResetRerollShopRequest import *
import CC
from RerollHelper import RerollHelper

class Reset_reroll_shop( SubAction, ResetRerollShopRequest ):
    debug = True
    action = "reset_reroll_shop"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        self.acc.model.RerollShopInfo.RerollsToday = 0
        self.acc.model.RerollShopInfo.checkSize(self.acc.model, self.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS,
                                                self.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_PREMIUM_SLOTS)
        self.acc.db.castle_roll = {CC.REROLL_ADDITIONAL_PROBABILITIES: {}, CC.REROLL_DAILY_PROBABILITIES: {},
                                   CC.REROLL_DAILY_WEIGHTS: {}}
        rerollHelper = RerollHelper(self.acc.SD)
        rerollHelper.resetProbabilities(self.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES],
                                        self.acc.db.castle_roll[CC.REROLL_DAILY_WEIGHTS],
                                        self.acc.db.castle_roll[CC.REROLL_ADDITIONAL_PROBABILITIES], 0, self.acc.getConfig())

        self.response["ok"] = 1
        self.fin()