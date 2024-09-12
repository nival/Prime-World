#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GiveStatPointsRequest import GiveStatPointsRequest

class Give_stat_points( SubAction, GiveStatPointsRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "give_stat_points"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    self.arguments.hero.TalentSets[self.arguments.hero.ActiveTalentSet].Stats.StatPoints += self.arguments.value
    if self.arguments.hero.TalentSets[self.arguments.hero.ActiveTalentSet].Stats.StatPoints < 0:
      self.arguments.hero.TalentSets[self.arguments.hero.ActiveTalentSet].Stats.StatPoints = 0
          
    self.response["ok"] = 1 # success 
    self.fin()