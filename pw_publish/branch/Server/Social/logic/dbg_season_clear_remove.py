# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.DbgSeasonEventClearRequest import *

class Dbg_season_clear_remove( SubAction, DbgSeasonEventClearRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "dbg_season_clear_remove"
  
    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC

        self.response["ok"] = 1
        self.fin()