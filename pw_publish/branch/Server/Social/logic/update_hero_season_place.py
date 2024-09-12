# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.UpdateHeroSeasonPlaceRequest import *

class Update_hero_season_place( SubAction, UpdateHeroSeasonPlaceRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "update_hero_season_place"
  
    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        self.I.EXPORT.getLegendRatingInfo(self.arguments.heroId, self.acc.db.auid, self.acc.SD.getCurrentSeasonId(), self.onReceiveLegendInfo)

    @model_callback
    @action_timing
    def onReceiveLegendInfo(self, sqlReply):
        self.response["callback"] = ["update_hero_season_place"]
        r = sqlReply["r"]
        if r and len(r):
            try:
                for legendRatingInfo in r:
                    info("onReceiveLegendInfo for auid %d, hero_id = %d, league_place = %d"%(self.acc.db.auid, legendRatingInfo.hero_id, legendRatingInfo.league_place))
                    self.acc.model.updateHeroLegendLeagueInfo(self.acc, self.acc.SD, legendRatingInfo.hero_id, legendRatingInfo.league_place)
            except Exception:
                catch()

        self.response["ok"] = 1
        self.fin()