#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GiveExperienceRequest import GiveExperienceRequest

class Give_experience( SubAction, GiveExperienceRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "give_experience"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
            
    self.arguments.hero.changeExperience( self.arguments.value, self.acc.model, self.I.WS, self.acc, self.I )
      
    self.response["ok"] = 1 # success 
    self.fin()