#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ResetCountersRequest import ResetCountersRequest

class Reset_counters( SubAction, ResetCountersRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "reset_counters"
  debug = True

  # клиент просит переместить вещь из инвентаря в талантсет
  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.acc.db.fractionChanged = 0
    self.acc.db.nickChanged = 0
    
    self.acc.model.MarketingEventsInfo.IsBuyHeroComplete = False
    
    self.response["ok"] = 1 # success 

    self.fin()