#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
import base64
from base.helpers import utf8convert
from logic.requests.PurchaseGuildIconChangeRequest import PurchaseGuildIconChangeRequest

class Purchase_guild_icon_change( SubAction, PurchaseGuildIconChangeRequest ):
  """Gold write off operation for guild icon changing"""
  action = "purchase_guild_icon_change"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    self.logs_prefix = "Purchase_guild_icon_change %d:"%(self.acc.auid)
    info(self.logs_prefix)
    changeiter = self.getIntParam("changeiter")#self.arguments.changeiter
    changeCost = self.acc.getConfigValue("GUILD_ICON_CHANGE_COST")
    freeChanges = self.acc.getConfigValue("GUILD_FREE_ICON_CHANGES_COUNT")

    info("%s changeiter=%d, changeCost=%d, freeChanges=%d",self.logs_prefix, changeiter,changeCost,freeChanges)

    self.price = self.acc.model.createResourcesTable( Gold = changeCost )
    # hack for self.buy() execution
    self.needGold = changeCost
    if (changeiter >= freeChanges and self.acc.model.canBuy(self.price)):
      reason = "PW!GUILD_ICON_CHANGE: leader auid=%d %d/%d"%(self.acc.auid,changeiter+1,freeChanges)
      self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
      return None
    else:
      self.errorResponse( EC.NOT_ENOUGH_RESOURCES, "Not enough gold", {"cost" : changeCost, "gold" : self.acc.model.Resources.Gold } )
      return
 
    self.fin()

  @model_callback
  def onBuyFunc( self, response ):
    info("Purchase_guild_icon_change.onBuyFunc response: %s" % response)    
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:
      self.doConfirmWriteOff( response )
      self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.BuyGuildIconChange, "", self.price, self.acc.model.Resources )  
      self.response["ok"] = 1 # success 
    else:
      self.onBuyError( response )
      return

    self.fin()


  @action_timing
  def onBuy( self, response ):
    self.onBuyFunc( response )

