#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetLampLastDropTimeRequest import SetLampLastDropTimeRequest

class Set_lamp_last_roll( SubAction, SetLampLastDropTimeRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "set_lamp_last_roll"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    modeldata = self.acc.model
    modeldata.Statistics.LastLampDropTime = time.time() - self.arguments.secs

    self.response["ok"] = 1
    self.fin()