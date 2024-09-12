#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.UpgradeTalentRequest import UpgradeTalentRequest

class Upgrade_talent( SubAction, UpgradeTalentRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "upgrade_talent"
  debug = True
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    talent = self.arguments.target_talent
    points = self.arguments.points
    
    target_staticTalent = self.acc.SD.getStaticTalent( talent )
    if target_staticTalent['rarity'] == "Class":
      self.errorResponse(  "Class talent can't be neither merged nor improved" )
      return
    
    talent.addPoints( points, self.acc.SD, self.acc.model, self.I.WS, self.acc )

    self.response["ok"] = 1
    self.fin()