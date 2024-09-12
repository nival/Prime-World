#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from MM import ESex
from logic.requests.BuyHeroRequest import BuyHeroRequest

class Buy_hero( SubAction, BuyHeroRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "buy_hero"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    if self.acc.model.MarketingEventsInfo.IsBuyHeroComplete:
      self.errorResponse(EC.ACTION_CANNOT_BE_USED, "BuyHero action expired")
      return      

    self.PersistentId = self.arguments.PersistentId
    static_hero, self.hero, error_message = self.acc.model.canHireHero(self.PersistentId, self.acc)
    if not static_hero:
      self.errorResponse(error_message)
      return
    
    if self.acc.sex == ESex.FEMALE:
      self.cost = self.acc.SD.copyPrice(static_hero['lobbyData']['CostFemale'])
    else:
      self.cost = self.acc.SD.copyPrice(static_hero['lobbyData']['CostMale'])
    if self.cost.Silver > int(self.acc.getConfigValue("BUY_HERO_MAX_ORIGINAL_PRICE")):
      self.errorResponse(EC.ACTION_CANNOT_BE_USED, "Hero is not match this action")
      return      
    
    self.price = self.acc.model.createResourcesTable( Gold = int(self.acc.getConfigValue("BUY_HERO_PRICE")) )        
    self.needGold = int( self.price.Gold )
    self.fame = static_hero['lobbyData']['FameIncrement']['FameIncrement']['Item'][0]
    reason = "PW!HERO:" + str( static_hero['persistentId'] ) + "_" + str( self.acc.db.fraction )
    self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
    return None


  @model_callback
  def onBuyFunc(self, response):
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:
      self.doConfirmWriteOff(response)
      if self.hero != None:
        self.hero.Hired = True
      else:
        self.hero = self.acc.model.hireHero(self.PersistentId, self.acc.sex, self.I.WS, self.acc, self.I)
      self.acc.model.MarketingEventsInfo.IsBuyHeroComplete = True
      self.acc.model.addFame(self.fame, self.acc, self.acc.SD, self.I.STATS)
      self.I.STATS.addUnlockHero(self.acc.auid, self.hero.PersistentId, self.price, self.acc.model.Resources)

      self.response["ok"] = 1 # success 
    else:
      self.onBuyError(response, self.needGold)
      return

    self.fin()


  @action_timing
  def onBuy(self, response):
    self.onBuyFunc(response)
