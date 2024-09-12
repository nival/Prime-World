#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GiveMuidDLCRequest import GiveMuidDLCRequest

class Give_muid_dlc( SubAction, GiveMuidDLCRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "give_muid_dlc"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    self.muid = self.arguments.muid
    success = self.I.WS.tryApplyDLCsForMuid( self.muid, self.acc, self.I )
    if not success:
      self.errorResponse( EC.STEAM_DLC_APPLY_ERROR, "DLC for muid %r apply error" % self.muid)
      return

    self.response["ok"] = 1
    self.fin()