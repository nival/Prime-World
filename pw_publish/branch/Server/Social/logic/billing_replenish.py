#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BillingReplenishRequest import BillingReplenishRequest

class Billing_replenish( SubAction, BillingReplenishRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "billing_replenish"
  debug = True
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.I.BILL.replenish( self.acc.db.auid, self.arguments.sum, "Replenish Cheat", self.onReplenish )
    

  @model_callback
  def onReplenish( self, response ):
    err( "Cheat billing! onReplenish %r" % response )
    self.response["error"] = "Cheat billing! onReplenish %r" % response
    self.response["ok"] = 1
    self.fin()
