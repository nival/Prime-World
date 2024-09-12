#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ChangePAEndRequest import ChangePAEndRequest

class Change_pa_end( SubAction, ChangePAEndRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "change_pa_end"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    secs = self.arguments.secs
    self.acc.model.LordInfo.PremiumAccountEnd += secs
    
    self.response["ok"] = 1 # success 

    self.fin()