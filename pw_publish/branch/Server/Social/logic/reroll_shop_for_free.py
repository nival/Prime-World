# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RerollShopForFreeRequest import *
import CC

class Reroll_shop_for_free( SubAction, RerollShopForFreeRequest ):
    debug = True
    action = "reroll_shop_for_free"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        self.acc.model.RerollShopInfo.RerollsToday = 0
        self.acc.model.rerollShopItems(self.acc)

        self.response["ok"] = 1
        self.fin()