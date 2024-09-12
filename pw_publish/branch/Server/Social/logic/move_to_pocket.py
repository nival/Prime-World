#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.MoveToPocketRequest import MoveToPocketRequest
from modeldata.Construction import *

class Move_to_pocket( SubAction, MoveToPocketRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "move_to_pocket"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    construction = self.arguments.building

    if construction:
      findInPocket = False
      for constructionId in self.acc.model.Pocket.keys():
        if constructionId == construction.getID():
          findInPocket = True
          break

      if findInPocket:
        self.response["ok"] = 1 # success
        self.fin()
        return

      staticConstruction = self.acc.SD.getStaticConstruction( construction )
      if staticConstruction:
        if not Construction.canOperateConstruction( staticConstruction, self.acc.model.isInMatchmaking() ):
          self.errorResponse( EC.HERO_IN_MATCHMAKING, "Hero in matchmaking" )
          return

        construction.emptyAndStopBuilding( self.acc.model, self.I, self.acc )
  
        self.acc.model.Pocket.add( construction )
        self.acc.model.Buildings.remove( construction )
        # Если убрали склад - пересчитаем лимиты
        buildingPrice = self.acc.SD.getBuildingPrice( staticConstruction, construction.Level )
        self.price = self.acc.model.createResourcesTable( Population = buildingPrice.Population )
        self.acc.model.sell( self.price, self.acc )
        Resource1 = self.acc.model.Resources.Resource1
        Resource2 = self.acc.model.Resources.Resource2
        Resource3 = self.acc.model.Resources.Resource3
        if staticConstruction['classType'] == "StorageBuilding" or staticConstruction['classType'] == "LibraryBuilding" \
            or staticConstruction['classType'] == "HouseBuilding" or staticConstruction['classType'] == "FirstBuyBuilding"\
            or staticConstruction['classType'] == "GoldProductionBuilding":
          self.acc.model.calcResourcesLimit( self.acc.SD, self.acc.guest )
        Resource1 = Resource1-self.acc.model.Resources.Resource1
        Resource2 = Resource2-self.acc.model.Resources.Resource2
        Resource3 = Resource3-self.acc.model.Resources.Resource3
        self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.MoveToPocket, "%r (id=%r)" % ( staticConstruction['classType'], construction.id ), self.acc.model.createResourcesTable(Resource1=Resource1, Resource2=Resource2, Resource3=Resource3, Population = buildingPrice.Population), self.acc.model.Resources )  
        if staticConstruction['classType'] == "HeroesBuilding":
          self.acc.model.updateHeroesForce( self.I.WS, self.acc )
      else:
        self.errorResponse( "Static construction is null")
        return
    else:
      self.errorResponse( "Construction is null" )
      return
        
    self.response["ok"] = 1 # success
    self.fin()
