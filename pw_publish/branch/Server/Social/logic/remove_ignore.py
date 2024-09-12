#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveIgnoreRequest import RemoveIgnoreRequest

class Remove_ignore( SubAction, RemoveIgnoreRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "remove_ignore"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    self.I.STATS.addRemoveIgnore( self.acc.auid, self.arguments.auid )
      
    self.response["ok"] = 1 # success 
    self.fin()