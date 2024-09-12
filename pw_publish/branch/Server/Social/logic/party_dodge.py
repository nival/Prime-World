#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_action import *
from logic.requests.PartyDodgeRequest import PartyDodgeRequest

class Party_dodge( Party_action, PartyDodgeRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "party_dodge"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    # для party.dodge требуется инфа о бане игрока за лив, берется из ModelData
    banEndTime = self.acc.model.getBanEndTime()
    if banEndTime <= int( time.time() ):
        banEndTime = 0
    self.addArguments( banEndTime=banEndTime )
    return Party_action.onStart(self)
