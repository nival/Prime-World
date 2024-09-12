# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetLastBuyValue import *


class Set_last_buy_value( SubAction, SetLastBuyValue ):
    action = "set_last_buy_value"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        model_data = self.acc.model
        model_data.LordInfo.LastBuyValue = self.arguments.lastBuyValue

        self.response["ok"] = 1
        self.fin()