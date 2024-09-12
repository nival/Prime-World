# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.UsesUpgHeroTalRequest import *

class Uses_upg_herotal( SubAction, UsesUpgHeroTalRequest ):
    """"action, который будет обрабатывать данный класс"""
    action = "uses_upg_herotal"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        self.acc.model.MarketingEventsInfo.UpgradeHeroTalentsInfo.UsesLeft = self.arguments.uses

        self.response["ok"] = 1
        self.fin()