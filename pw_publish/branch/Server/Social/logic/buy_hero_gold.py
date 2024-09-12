#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from MM import ESex
from logic.requests.BuyHeroGoldRequest import BuyHeroGoldRequest

class Buy_hero_gold( SubAction, BuyHeroGoldRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "buy_hero_gold"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
   
    self.PersistentId = self.arguments.PersistentId
    static_hero, self.hero, error_message = self.acc.model.canHireHero( self.PersistentId, self.acc )
    if not static_hero:
      self.errorResponse( error_message )
      return
    
    self.overrideGoldCost = self.acc.SD.GetHeroGoldPrice(static_hero, self.acc.getConfig(), self.acc.sex == ESex.FEMALE)
          
    self.price = self.acc.model.createResourcesTable( Gold = int(self.overrideGoldCost) )        
    self.needGold = int( self.price.Gold )
    if not self.needGold:
      self.errorResponse( "Hero does not have gold price" )     
      return      
    
    self.fame = static_hero['lobbyData']['FameIncrement']['FameIncrement']['Item'][0]
    reason = "PW!HERO:" + str( static_hero['persistentId'] ) + "_" + str( self.acc.db.fraction )
    self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
    return None

  @model_callback
  def onBuyFunc( self, response ):
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:
      self.doConfirmWriteOff( response )
      if self.hero != None:
        self.hero.Hired = True
      else:
        self.hero = self.acc.model.hireHero( self.PersistentId, self.acc.sex, self.I.WS, self.acc, self.I )
      self.acc.model.addFame(self.fame, self.acc, self.acc.SD, self.I.STATS)
      self.I.STATS.addUnlockHero( self.acc.auid, self.hero.PersistentId, self.price, self.acc.model.Resources )
      self.response["ok"] = 1 # success
    else:
      self.onBuyError( response, self.needGold )
      return

    self.fin()


  @action_timing
  def onBuy( self, response ):
    self.onBuyFunc( response )
