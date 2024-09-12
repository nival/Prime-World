#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddIgnoreRequest import AddIgnoreRequest

class Add_ignore( SubAction, AddIgnoreRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "add_ignore"

  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    self.I.STATS.addAddIgnore( self.acc.auid, self.arguments.auid, self.arguments.reason )
      
    self.response["ok"] = 1 # success 
    self.fin()