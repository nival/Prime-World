#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BuyPremiumAccountGMRequest import BuyPremiumAccountGMRequest

class Buy_premium_account_gm( SubAction, BuyPremiumAccountGMRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "buy_premium_account_gm"
  debug = True
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    days = (24*60*60)*self.arguments.duration
    self.acc.model.addPremiumAccount( days, self.acc )

    self.response["ok"] = 1
    self.fin()
