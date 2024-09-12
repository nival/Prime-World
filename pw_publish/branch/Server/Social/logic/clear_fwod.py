#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ClearFWODRequest import ClearFWODRequest

class Clear_fwod( SubAction, ClearFWODRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "clear_fwod"
  debug = True
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    for key in self.acc.model.LordInfo.TodayWinMaps.keys():
      self.acc.model.LordInfo.TodayWinMaps.remove(key)

    self.response["ok"] = 1
    self.fin()