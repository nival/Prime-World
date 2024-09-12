#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BillingConfirmWriteOffRequest import BillingConfirmWriteOffRequest

class Billing_confirm_writeoff( SubAction, BillingConfirmWriteOffRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "billing_confirm_writeoff"
  debug = True
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.I.BILL.confirmWriteOff( self.acc.db.auid, self.arguments.reserveId, self.onResponse )
    

  @model_callback
  def onResponse( self, response ):
    err( "Cheat billing! onConfirmWriteOff %r" % response )
    self.response["error"] = "Cheat billing! onConfirmWriteOff %r" % response
    self.response["ok"] = 1
    self.fin()
