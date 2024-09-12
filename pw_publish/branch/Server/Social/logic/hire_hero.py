#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from MM import ESex
from logic.requests.HireHeroRequest import HireHeroRequest

class Hire_hero( SubAction, HireHeroRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "hire_hero"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
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
      
    discount, fameReqDecr = self.acc.model.getHeroDiscountFromBuilding( static_hero, self.acc.SD )
    
    lvl = self.acc.SD.getFameLevel( self.acc.model.LordInfo.Fame )
    if self.acc.sex == ESex.FEMALE:
      LevelRequire = static_hero['lobbyData']['LevelRequireFemale']
      self.price = self.acc.SD.copyPrice(static_hero['lobbyData']['CostFemale'])
      self.price.Silver = self.acc.getConfig().EventToolsChangeFields.HERO_SILVER_PRICES[static_hero['persistentId']]
    else:
      LevelRequire = static_hero['lobbyData']['LevelRequireMale']
      self.price = self.acc.SD.copyPrice(static_hero['lobbyData']['CostMale'])
      self.price.Silver = self.acc.getConfig().EventToolsChangeFields.HERO_SILVER_PRICES[static_hero['persistentId']]
    self.price.Silver = int(self.price.Silver) - self.acc.SD.roundFloatToInt(float(self.price.Silver) * discount / 100.0)
    
    if LevelRequire - fameReqDecr <= lvl:       
      self.needGold = int( self.price.Gold )
      self.fame = static_hero['lobbyData']['FameIncrement']['FameIncrement']['Item'][0]
      reason = "PW!HERO:" + str( static_hero['persistentId'] ) + "_" + str( self.acc.db.fraction )
      self.buy( self.price, self.onBuy, self.onBuyFunc, reason, True )
      return None
    else:
      self.errorResponse( "Not enough lvl")
      return
    
    
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
