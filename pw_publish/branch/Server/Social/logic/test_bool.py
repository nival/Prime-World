#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.TestBoolRequest import TestBoolRequest

class Test_bool( SubAction, TestBoolRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "test_bool"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    boolArg = self.arguments.boolArg

    if boolArg:
      self.acc.model.LordInfo.GuardInfo.OnlyGuard = True
    else:
      self.acc.model.LordInfo.GuardInfo.OnlyGuard = False
   
    self.response["ok"] = 1 # success 
    self.fin()
