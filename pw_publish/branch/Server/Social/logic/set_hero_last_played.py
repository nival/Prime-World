# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetHeroLastPlayedRequest import *

class Set_hero_last_played( SubAction, SetHeroLastPlayedRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "set_hero_last_played"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if self.arguments.daysAgo > 0:
            self.arguments.hero.lastPlayed = int(time.time()) - 24*60*60*self.arguments.daysAgo

        self.response["ok"] = 1
        self.fin()