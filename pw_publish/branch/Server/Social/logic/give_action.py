#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GiveActionRequest import GiveActionRequest

class Give_action( SubAction, GiveActionRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "give_action"
  debug = True
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    #ACTION LOGIC
    modeldata = self.acc.model
    bonus = self.getStringParam( "bonus_value", "" )
    if not bonus:
      bonus = "200"
    modeldata.replaceGoldLampEvent( bonus, 1000, 12, 300 )

    self.response["ok"] = 1
    self.fin()