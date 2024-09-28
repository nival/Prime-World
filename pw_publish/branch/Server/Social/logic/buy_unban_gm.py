#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BuyUnbanGMRequest import BuyUnbanGMRequest

class Buy_unban_gm( SubAction, BuyUnbanGMRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "buy_unban_gm"
  debug = True
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    self.needGold = int( self.acc.getConfigValue("GM_TOOL_UNBAN_COST") )
    self.price = self.acc.model.createResourcesTable( Gold = self.needGold )
    reason = "PW!UNBAN_BY_GM:"
    self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
    
  @model_callback
  def onBuyFunc( self, response ):
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:
      self.doConfirmWriteOff( response )
      self.acc.db.banned = False
      self.acc.db.bantime = 0
      self.acc.db.banreason = ""
      self.acc.db.autoban = False 
      self.response["ok"] = 1 # success
      self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.Unban, "", self.price, self.acc.model.Resources )
    else:
      self.onBuyError( response, self.price )
      return

    self.fin()


  @action_timing
  def onBuy( self, response ):
    self.onBuyFunc( response )