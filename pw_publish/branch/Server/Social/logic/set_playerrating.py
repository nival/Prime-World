# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetPlayerRatingRequest import *

class Set_playerrating( SubAction, SetPlayerRatingRequest ):
    """action, ������� ����� ������������ ������ �����"""
    action = "set_playerrating"
    debug = True
    @model_callback
    @parse
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC
        self.acc.model.setPlayerRating(self.arguments.rating, self.acc.getConfig())

        self.response["ok"] = 1
        self.fin()