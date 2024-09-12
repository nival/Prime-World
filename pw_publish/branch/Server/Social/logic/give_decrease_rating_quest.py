# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GiveDecreaseRatingQuestRequest import *

class Give_decrease_rating_quest( SubAction, GiveDecreaseRatingQuestRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "give_decrease_rating_quest"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.acc.model.LordInfo.LastRankedGameTime = int(time.time()) - self.arguments.daysAway * 60*60*24

        self.response["ok"] = 1
        self.fin()