# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetAFKStateRequest import *

class Set_afk_state( SubAction, SetAFKStateRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "set_afk_state"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    if self.arguments.isAfk:
      self.I.PS.afk(self.acc.auid)
    else:
      self.I.PS.inCastle(self.acc.auid, True)

    self.response["ok"] = 1
    self.fin()