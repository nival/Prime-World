#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.MoveFromPocketRequest import MoveFromPocketRequest
from modeldata.Construction import *

class Move_from_pocket( SubAction, MoveFromPocketRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "move_from_pocket"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    construction = self.arguments.building
    findInPocket = False
    if construction:
      for constructionId in self.acc.model.Pocket.keys():
        if constructionId == construction.getID():
          findInPocket = True
          break
      
    if findInPocket:
      staticConstruction = self.acc.SD.getStaticConstruction( construction )
      if staticConstruction:
        if Construction.canOperateConstruction( staticConstruction, self.acc.model.isInMatchmaking() ):
          if self.acc.model.validateFreeArea( self.acc.SD, staticConstruction):
            if self.acc.model.canPlaceBuilding( staticConstruction, self.acc.SD, True ):
              buildingPrice = self.acc.SD.getBuildingPrice( staticConstruction, construction.Level )
              self.price = self.acc.model.createResourcesTable( Population = buildingPrice.Population )
              self.staticConstruction = staticConstruction
              self.needGold = int( self.price.Gold )
              self.construction = construction
              reason = "PW!MOVE_FROM_POCKET:" + str( construction.PersistentId )
              self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
              return None
            else:
              self.errorResponse( "Reach max buildings number for id " + str(construction.PersistentId) )
              return
          else:
            self.errorResponse( "No space left" )
            return
        else:
          self.errorResponse( "Hero in matchmaking" )
          return
      else:   
        self.errorResponse( "Can not find static construction with id " + str(construction.PersistentId) )
        return
    else:
      self.errorResponse( "Can not find construction in pocket" )
      return

    self.response["ok"] = 1 # success
    self.fin()


  @model_callback
  def onBuyFunc( self, response ):
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:
      self.doConfirmWriteOff( response )
      self.construction.placeBuilding( self.arguments.x, self.arguments.y, self.arguments.pitch, self.construction.PersistentId, int(self.arguments.rid), self.staticConstruction, self.acc, self.I )
      self.acc.model.Pocket.remove( self.construction )
      if self.staticConstruction['classType'] == "HeroesBuilding":
        self.acc.model.updateHeroesForce( self.I.WS, self.acc )
      self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.MoveFromPocket, "%r (id=%r)" % ( self.staticConstruction['classType'], self.construction.id ), self.price, self.acc.model.Resources )
      if self.staticConstruction['classType'] == "GoldProductionBuilding":
        self.acc.model.MarketingEventsInfo.GoldHouseActionState = GoldHouseActionState.ShowNoEvent
      self.response["ok"] = 1 # success 
    else:
      self.onBuyError( response, self.needGold )
      return

    self.fin()


  @action_timing
  def onBuy( self, response ):
    self.onBuyFunc( response )

