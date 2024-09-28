#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddDodgesRequest import AddDodgesRequest

class Add_dodges( SubAction, AddDodgesRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "add_dodges"
  debug = True
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    if self.arguments.dodges > 0:
      self.acc.model.addDodges( self.arguments.dodges, self.I.WS, self.acc )
    else:
      self.acc.model.clearDodges()

    self.response["ok"] = 1
    self.fin()