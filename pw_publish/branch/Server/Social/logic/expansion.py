#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ExpansionRequest import ExpansionRequest

class Expansion( SubAction, ExpansionRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "expansion"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    self.price = self.acc.SD.getExpansionPrice( self.acc.model.LordInfo.LevelOfExpansion+1 )
    if not self.price:
      self.errorResponse( "max expansion level" )
      return
    else:
      self.needGold = int( self.price.Gold )
      reason = "PW!EXPANSION:" + str( self.acc.model.LordInfo.LevelOfExpansion+1 )
      self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
      return None


  @model_callback
  def onBuyFunc( self, response ):
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:
      self.doConfirmWriteOff( response )
      self.acc.model.LordInfo.LevelOfExpansion += 1
      self.acc.model.recalcPopulation( self.acc.SD, self.acc.guest )
      self.acc.model.calcResourcesLimit( self.acc.SD, self.acc.guest )
      self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.Expansion, "", self.price, self.acc.model.Resources )  
      self.response["ok"] = 1 # success 
    else:
      self.onBuyError( response, self.needGold )
      return
      
    self.fin()


  @action_timing
  def onBuy( self, response ):
    self.onBuyFunc( response )
