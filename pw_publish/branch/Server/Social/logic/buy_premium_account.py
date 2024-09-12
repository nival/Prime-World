#!/usr/bin/env python
# -*- coding: utf-8 -*-
from subaction import *
from logic.requests.BuyPremiumAccountRequest import BuyPremiumAccountRequest

CONFIG_PARAMS = {
    0: ("PREMIUM_ACCOUNT_PRICE","PREMIUM_ACCOUNT_DURATION"),
    1: ("PREMIUM_ACCOUNT_PRICE2", "PREMIUM_ACCOUNT_DURATION2"),
    2: ("PREMIUM_ACCOUNT_PRICE3", "PREMIUM_ACCOUNT_DURATION3"),
}

class Buy_premium_account( SubAction, BuyPremiumAccountRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "buy_premium_account"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    try:
        param = CONFIG_PARAMS[self.arguments.type]
    except KeyError:
        self.errorResponse(EC.BAD_PARAM, "Can not buy, invalid cycle %s", self.arguments.type)
        return
    self.needGold = int( self.acc.getConfigValue(param[0]) )
    self.duration = int( self.acc.getConfigValue(param[1]) )

    if self.needGold >= 0:         
      self.price = self.acc.model.createResourcesTable(Gold = self.needGold)
      reason = "PW!BUY_PREMIUM_ACCOUNT:"+str( self.duration )
      self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
    else:
      self.errorResponse(EC.BAD_PARAM, "Can not buy cycle, price is negative")
    return


  @model_callback
  def onBuyFunc( self, response ):
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:
      self.doConfirmWriteOff( response )
      self.acc.model.addPremiumAccount( self.duration, self.acc )
      durationInDays = self.duration / 86400.0
      self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.BuyPremiumAccount, str(durationInDays), self.price, self.acc.model.Resources )  
      self.response["ok"] = 1 # success
    else:
      self.onBuyError( response, self.needGold )
      return

    self.fin()


  @action_timing
  def onBuy( self, response ):
    self.onBuyFunc( response )
