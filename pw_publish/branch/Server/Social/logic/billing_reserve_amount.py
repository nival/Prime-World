#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BillingReserveAmountRequest import BillingReserveAmountRequest

class Billing_reserve_amount( SubAction, BillingReserveAmountRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "billing_reserve_amount"
  debug = True
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.I.BILL.reserveAmount( self.acc.db.auid, self.arguments.sum, "Reserve Amount Cheat", self.onReserveAmount )
    

  @model_callback
  def onReserveAmount( self, response ):
    err( "Cheat billing! onReserveAmount %r" % response )
    self.response["error"] = "Cheat billing! onReserveAmount %r" % response
    self.response["ok"] = 1
    self.fin()
