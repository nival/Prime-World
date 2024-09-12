# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetGamesRequest import *

class Set_games( SubAction, SetGamesRequest ):
    """action, ������� ����� ������������ ������ �����"""
    action = "set_games"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC
        self.acc.model.Statistics.PRSessionsStarted = self.arguments.games
        self.response["ok"] = 1
        self.fin()