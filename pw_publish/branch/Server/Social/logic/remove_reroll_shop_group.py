# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveRerollShopGroupRequest import *
import CC

class Remove_reroll_shop_group( SubAction, RemoveRerollShopGroupRequest ):
    debug = True
    action = "remove_reroll_shop_group"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        stringId = str(self.arguments.persistentId)
        if stringId in self.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES]:
            self.acc.db.castle_roll[CC.REROLL_DAILY_PROBABILITIES][stringId] = 0
            self.response["ok"] = 1
        else:
            self.response["ok"] = 0

        self.fin()