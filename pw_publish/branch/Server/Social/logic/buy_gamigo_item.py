# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BuyGamigoItemRequest import *

class Buy_gamigo_item( SubAction, BuyGamigoItemRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "buy_gamigo_item"
  
    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC

        self.response["ok"] = 1
        self.fin()