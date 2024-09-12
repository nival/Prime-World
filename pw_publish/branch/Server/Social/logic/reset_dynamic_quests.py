# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ResetDynamicQuestsRequest import *

class Reset_dynamic_quests( SubAction, ResetDynamicQuestsRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "reset_dynamic_quests"
  debug = True
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    while self.acc.model.CompletedDynamicQuests:
      self.acc.model.CompletedDynamicQuests.pop()

    while self.acc.model.LossDynamicQuests:
      self.acc.model.LossDynamicQuests.pop()

    self.response["ok"] = 1
    self.fin()