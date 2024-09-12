# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ResetLastPlayedTimeRequest import *

class Reset_last_played_time( SubAction, ResetLastPlayedTimeRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "reset_last_played_time"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if self.arguments.decreaseRating:
            decreaseLevel = self.acc.SD.getRatingToLooseLevel(self.acc.model.LordInfo.LastRankedGameTime)
            if decreaseLevel:
                for heroId in self.acc.model.Heroes:
                    hero = self.acc.model.getHeroByID(heroId)
                    if hero.Rating > self.acc.SD.data['RatingDecreaseByTime']['minRatingToLoose']:
                        hero.Rating = max(hero.Rating - decreaseLevel['ratingToLoose'], self.acc.SD.data['RatingDecreaseByTime']['minRatingToLoose'])

        self.acc.model.LordInfo.LastRankedGameTime = int(time.time())

        self.response["ok"] = 1
        self.fin()