#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RegisterDLCRequest import RegisterDLCRequest

class Dlc_register( SubAction, RegisterDLCRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "dlc_register"
  debug = True
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.dlcIdx = self.arguments.dlcIdx

    if self.dlcIdx not in self.acc.db.dlcs:
      self.acc.db.dlcs.append( self.dlcIdx )

    self.response["ok"] = 1
    self.fin()