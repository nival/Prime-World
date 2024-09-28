# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RerollShopRequest import *

class Reroll_shop( SubAction, RerollShopRequest ):
    action = "reroll_shop"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        self.price = self.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_PRICE
        self.needGold = int(self.price.Gold)
        reason = "PW!REROLL_SHOP_REROLL"
        self.buy( self.price, self.onBuy, self.onBuyFunc, reason )

    @model_callback
    def onBuyFunc(self, response):
        code = response["code"]
        self.response["callback"] = ["reroll_shop"]
        if code == ibilling.ERROR_CODE_OK:
            self.acc.model.RerollShopInfo.RerollsToday += 1
            self.acc.model.rerollShopItems(self.acc)
            self.response["ok"] = 1
            self.fin()
        else:
            self.onBuyError(response, self.needGold)

    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)
