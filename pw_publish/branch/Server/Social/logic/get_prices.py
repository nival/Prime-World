#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.GetPricesRequest import GetPricesRequest

sys.path.append('thrift_pw/account_management/gen-py')
sys.path.append('../thrift_pw/account_management/gen-py')
sys.path.append('../../thrift_pw/account_management/gen-py')
from AccountManagementAPI.ttypes import PayServiceType

class Get_prices( SubAction, GetPricesRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "get_prices"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    if self.arguments.servicetype == PayServiceType.PremiumAccount:
      self.response["prices"] = [ { "price": int( self.acc.getConfigValue("PREMIUM_ACCOUNT_PRICE") ), "duration" : int( self.acc.getConfigValue("PREMIUM_ACCOUNT_DURATION") ) }, 
                                { "price": int( self.acc.getConfigValue("PREMIUM_ACCOUNT_PRICE2") ), "duration" : int( self.acc.getConfigValue("PREMIUM_ACCOUNT_DURATION2") ) },
                                { "price": int( self.acc.getConfigValue("PREMIUM_ACCOUNT_PRICE3") ), "duration" : int( self.acc.getConfigValue("PREMIUM_ACCOUNT_DURATION3") ) } ]

    self.response["ok"] = 1
    self.fin()