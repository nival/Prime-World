# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveLootboxRequest import *

class Remove_lootbox( SubAction, RemoveLootboxRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "remove_lootbox"
  
    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC
        lootbox = self.arguments.lootbox
        if not lootbox.Reward.IsApplied:
            self.errorResponse("Trying to remove unopened lootbox")
            return

        self.acc.model.deleteLootbox(lootbox)

        self.response["ok"] = 1
        self.fin()