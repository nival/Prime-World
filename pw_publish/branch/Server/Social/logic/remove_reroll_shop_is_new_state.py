# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveRerollShopIsNewStateRequest import *

class Remove_reroll_shop_is_new_state( SubAction, RemoveRerollShopIsNewStateRequest ):
    action = "remove_reroll_shop_is_new_state"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        self.acc.model.RerollShopInfo.NewlyRerolled = False

        self.response["ok"] = 1
        self.fin()