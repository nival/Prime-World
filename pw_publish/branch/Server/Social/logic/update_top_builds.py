# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.UpdateTopBuildsRequest import *

class Update_top_builds( SubAction, UpdateTopBuildsRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "update_top_builds"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.I.WS.updateTopBuilds()

    self.response["ok"] = 1
    self.fin()