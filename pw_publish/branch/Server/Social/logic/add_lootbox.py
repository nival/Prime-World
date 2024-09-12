# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddLootboxRequest import *

class Add_lootbox( SubAction, AddLootboxRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "add_lootbox"
    debug = True
  
    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC
        if not self.acc.model.addLootbox(self.arguments.lootboxId, self.acc)[0]:
            self.errorResponse("AddLootbox error")
            return

        self.response["ok"] = 1
        self.fin()