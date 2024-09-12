# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ResetPunishedNextUpdateTimeRequest import *

class Reset_punished_last_update_time( SubAction, ResetPunishedNextUpdateTimeRequest ):
    """action, ������� ����� ������������ ������ �����"""
    action = "reset_punished_last_update_time"
    debug = True
  
    @model_callback
    @parse
    def onStart(self):
        """��������� ����� ��� ��������� action"""
        self.log()
        if not self.checkParams():
          return

        self.acc.model.LordInfo.PunishedNextUpdateTime = int(time.time())

        self.response["ok"] = 1
        self.fin()