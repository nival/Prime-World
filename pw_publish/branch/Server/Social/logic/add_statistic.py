#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddStatisticRequest import AddStatisticRequest

class Add_statistic( SubAction, AddStatisticRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "add_statistic"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.acc.model.addStatisticEvent( self.arguments.actionType, self.arguments.description, self.arguments.value )

    self.response["ok"] = 1 # success 
    self.fin()