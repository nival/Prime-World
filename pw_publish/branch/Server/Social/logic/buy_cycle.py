#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BuyCycleRequest import BuyCycleRequest

class Buy_cycle( SubAction, BuyCycleRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "buy_cycle"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    construction = self.arguments.construction
    if not construction:
      self.errorResponse( "Construction is null" )
      return

    staticConstruction = self.acc.SD.getStaticConstruction( construction )
    if not staticConstruction:
      self.errorResponse( "Static construction is null" )
      return
    
    if construction.ProductionState == ProductionState.Busy:
      self.price = None

      if staticConstruction['classType'] == "ProductionBuilding":
        gold = construction.getProductionCycleSkipPrice( self.acc, self.I )
        

      elif staticConstruction['classType'] == "Tavern":
        gold = construction.getTavernSkipPrice( self.acc.SD )
        
      else:
        self.errorResponse( "Building can't be accelerated for gold" )
        return

      if gold >= 0:
        self.price = self.acc.model.createResourcesTable( Gold = gold )
      else:
        self.errorResponse( "Gold price for ProductionBuilding less or equal 0" )
        return

      if self.price:
        self.staticConstruction = staticConstruction
        self.construction = construction
        self.needGold = int( self.price.Gold )
        if self.needGold >= 0:
          reason = "PW!CYCLE:" + str( construction.PersistentId ) + ":" + str( construction.cycle )
          self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
          return None
        else:
          self.errorResponse( "Can't buy cycle, the price is negative" )
          return
    else:
      self.errorResponse( "Building is not in production state" ) 
      return
      
    self.response["ok"] = 1 # success
    self.fin()


  @model_callback
  def onBuyFunc( self, response ):
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:      
      self.doConfirmWriteOff( response )
      self.construction.ProductionState = ProductionState.Finished
      staticBuilding = self.acc.SD.getStaticConstruction( self.construction )
      self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.BuildingBuyCycle, "%r (id=%r)" % ( staticBuilding['classType'], self.construction.id ), self.price, self.acc.model.Resources )  
      self.response["ok"] = 1 # success
    else:
      self.onBuyError( response, self.needGold )
      return

    self.fin()


  @action_timing
  def onBuy( self, response ):
    self.onBuyFunc( response )
