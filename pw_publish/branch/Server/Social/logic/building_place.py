#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *

sys.path.append('../modeldata')
from modeldata.Construction import *
from logic.requests.BuildingPlaceRequest import BuildingPlaceRequest

class Building_place( SubAction, BuildingPlaceRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "building_place"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    staticConstruction = self.acc.SD.getStaticConstructionByPersistentId( self.arguments.PersistentId )
    if self.acc.model.LordInfo.LevelOfExpansion != 0:
      if staticConstruction:
        lordLevel = self.acc.SD.getFameLevel( self.acc.model.LordInfo.Fame )
        if lordLevel < staticConstruction['LevelRequired']:
          self.errorResponse( "Building require more lord level" )
          return

        if staticConstruction['ConstructionTab'] == "Pocket":
          self.errorResponse( "Building is not allowed to buy" )
          return
        if Construction.canOperateConstruction( staticConstruction, self.acc.model.isInMatchmaking() ):
          if self.acc.model.validateFreeArea( self.acc.SD, staticConstruction ):
            if self.acc.model.canPlaceBuilding( staticConstruction, self.acc.SD ):
              self.price = self.acc.SD.GetBuyPrice(staticConstruction, self.acc.getConfig())
              self.fame = staticConstruction['Levels']['Item'][0]['fame']
              self.staticConstruction = staticConstruction
              self.needGold = int( self.price.Gold )
              reason = "PW!BUILDING:" + str( self.arguments.PersistentId )
              self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
              return None
            else:
              self.errorResponse( "Reach max buildings number for id " + str(self.arguments.PersistentId))
              return
          else:
            self.errorResponse( "No space left")
            return
        else:
          self.errorResponse( "Hero in matchmaking")
          return
      else:
        self.errorResponse( "Can not find static construction with id " + str(self.arguments.PersistentId))
        return
    else:
      self.errorResponse( "Building is not allowed on expansion level = 0")
      return
    self.response["ok"] = 1
    self.fin()


  @model_callback
  def onBuyFunc( self, response ):
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:
      self.doConfirmWriteOff( response )
      construction_uid = self.acc.model.addNewConstruction()
      construction = self.acc.model.getConstructionByID( construction_uid )
      construction.placeBuilding( self.arguments.x, self.arguments.y, self.arguments.pitch, self.arguments.PersistentId, int(self.arguments.rid), self.staticConstruction, self.acc, self.I )
      if self.staticConstruction['classType'] == "HeroesBuilding":
        self.acc.model.updateHeroesForce( self.I.WS, self.acc )
      self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.BuildingPlace, "%r (id=%r)" % ( self.staticConstruction['classType'], construction.id ), self.price, self.acc.model.Resources )
      if self.staticConstruction['classType'] == "GoldProductionBuilding":
        self.acc.model.MarketingEventsInfo.GoldHouseActionState = GoldHouseActionState.ShowNoEvent
      self.response["ok"] = 1
    else:
      self.onBuyError( response, self.needGold )
      return

    self.fin()


  @action_timing
  def onBuy( self, response ):
    self.onBuyFunc( response )
