#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GiveFameRequest import GiveFameRequest

class Give_fame( SubAction, GiveFameRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "give_fame"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
             
    self.acc.model.addFame(self.arguments.value, self.acc, self.acc.SD, self.I.STATS)
      
    self.response["ok"] = 1 # success 
    self.fin()
