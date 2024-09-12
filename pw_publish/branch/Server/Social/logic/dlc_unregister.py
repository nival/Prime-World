#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.UnregisterDLCRequest import UnregisterDLCRequest

class Dlc_unregister( SubAction, UnregisterDLCRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "dlc_unregister"
  debug = True
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.dlcIdx = self.arguments.dlcIdx

    if self.dlcIdx in self.acc.db.dlcs:
      self.acc.db.dlcs.remove( self.dlcIdx )

    self.response["ok"] = 1
    self.fin()