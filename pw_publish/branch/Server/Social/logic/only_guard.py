#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.OnlyGuardRequest import OnlyGuardRequest

class Only_guard( SubAction, OnlyGuardRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "only_guard"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.acc.model.LordInfo.GuardInfo.OnlyGuard = self.arguments.only_guard

    self.response["ok"] = 1
    self.fin()