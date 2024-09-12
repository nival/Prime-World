#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetGuardRequest import SetGuardRequest

class Set_guard( SubAction, SetGuardRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "set_guard"
  debug = True
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    hero = self.arguments.hero
    if hero:
      if self.arguments.guard:
        hero.Master = True
        hero.TalentSets[hero.ActiveTalentSet].Force = 160.0
      else:
        hero.Master = False
        hero.TalentSets[hero.ActiveTalentSet].Force = self.acc.SD.getHeroForce( hero, hero.ActiveTalentSet, self.acc.model.getStatPointsFromBuilding( self.acc.SD ) )
    info("hero Force now: %5.1f" % hero.TalentSets[hero.ActiveTalentSet].Force)

    self.response["ok"] = 1
    self.fin()