#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BuySpecialHeroRequest import BuySpecialHeroRequest

class Buy_special_hero( SubAction, BuySpecialHeroRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "buy_special_hero"
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    if not "/UI/Content/MarketingEvents/BuySpecialHero" in self.acc.getConfig().MARKETING_EVENTS:
      self.errorResponse( EC.ACTION_CANNOT_BE_USED, "BuySpecialHero action expired" )  
      return      
    
    if self.acc.db.fraction == 'A':
      self.PersistentId = crc32(self.acc.getConfigValue("BuySpecialHeroEventInfo").HeroIdA)
    elif self.acc.db.fraction == 'B':
      self.PersistentId = crc32(self.acc.getConfigValue("BuySpecialHeroEventInfo").HeroIdB)
    else:
      self.errorResponse( EC.ACTION_CANNOT_BE_USED, "Wrong fraction" )  
      return      
    
    static_hero, self.hero, error_message = self.acc.model.canHireHero( self.PersistentId, self.acc )
    if not static_hero:
      self.errorResponse( error_message )
      return  
    
    self.price = self.acc.model.createResourcesTable( Gold = int(self.acc.getConfigValue("BuySpecialHeroEventInfo").Price) )        
    self.needGold = int( self.price.Gold )
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
