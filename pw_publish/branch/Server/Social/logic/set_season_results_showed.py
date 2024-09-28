# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetSeasonsResultShowedRequest import *

class Set_season_results_showed( SubAction, SetSeasonsResultShowedRequest ):
    """action, ������� ����� ������������ ������ �����"""
    action = "set_season_results_showed"
  
    @model_callback
    @parse
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC
        for sa_id, season_awards_info in self.acc.model.SeasonAwardsKeeper.iteritems():
            debug("setSeasonShowedToUser: season_awards_info.SeasonId = %s, self.arguments.seasonId = %s, season_awards_info.IsShowedToUser = %s, self.arguments.isShowed = %s"%(
                str(season_awards_info.SeasonId), str(self.arguments.seasonId), str(season_awards_info.IsShowedToUser), str(self.arguments.isShowed)))
            if season_awards_info.SeasonId == self.arguments.seasonId:
                season_awards_info.IsShowedToUser = self.arguments.isShowed


        self.response["ok"] = 1
        self.fin()