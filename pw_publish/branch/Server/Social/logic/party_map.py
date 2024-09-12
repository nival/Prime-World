#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_action import *
from logic.requests.PartyMapRequest import PartyMapRequest

class Party_map( Party_action, PartyMapRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "party_map"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.acc.model.game_type = self.getParam("game_type", "")
    return Party_action.onStart(self)