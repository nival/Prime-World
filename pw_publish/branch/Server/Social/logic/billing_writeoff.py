#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BillingWriteOffRequest import BillingWriteOffRequest

class Billing_writeoff( SubAction, BillingWriteOffRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "billing_writeoff"
  debug = True
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    self.I.BILL.writeoff( self.acc.db.auid, self.arguments.sum, "WriteOff Cheat", self.onWriteOff )
    

  @model_callback
  def onWriteOff( self, response ):
    err( "Cheat billing! onWriteOff %r" % response )
    self.response["error"] = "Cheat billing! onWriteOff %r" % response
    self.response["ok"] = 1
    self.fin()
