#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetLastPaymentRequest import SetLastPaymentRequest

class Set_last_payment( SubAction, SetLastPaymentRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "set_last_payment"
  debug = True
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    modeldata = self.acc.model
    modeldata.Statistics.LastPaymentTime = time.time() - self.arguments.secs

    self.response["ok"] = 1
    self.fin()