#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.UnretireRequest import UnretireRequest

class Unretire( SubAction, UnretireRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "unretire"
  debug = True
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.acc.model.LordInfo.GuardInfo.RetiredTime = 0

    self.response["ok"] = 1
    self.fin()