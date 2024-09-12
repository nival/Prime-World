#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetNewStatusRequest import SetNewStatusRequest

class Set_new_status( SubAction, SetNewStatusRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "set_new_status"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    self.arguments.talent.IsNew = True
      
    self.response["ok"] = 1 # success 
    self.fin()