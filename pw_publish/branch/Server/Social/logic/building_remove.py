#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BuildingRemoveRequest import BuildingRemoveRequest

from modeldata.Construction import *

class Building_remove( SubAction, BuildingRemoveRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "building_remove"

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
      staticConstruction = self.acc.SD.getStaticConstruction( construction )
      if staticConstruction:
        removeFromPocket = False
        if construction.id in self.acc.model.Pocket:
          removeFromPocket = True

        if not Construction.canOperateConstruction( staticConstruction, self.acc.model.isInMatchmaking() ) and not removeFromPocket:
          self.errorResponse( EC.HERO_IN_MATCHMAKING, "Hero in matchmaking" )
          return
    
        construction.emptyAndStopBuilding( self.acc.model, self.I, self.acc )
        construction.clearCraftedTalents()  
        construction.sellConstruction( construction, staticConstruction, construction.Level, self.acc.model,
                                       self.acc.SD, True, self.I.STATS, self.acc, removeFromPocket )
        self.acc.model.Buildings.remove( construction )
        self.acc.model.Pocket.remove( construction )
      
        # Если убрали склад - пересчитаем лимиты
        if staticConstruction['classType'] == "StorageBuilding" or staticConstruction['classType'] == "LibraryBuilding" \
            or staticConstruction['classType'] == "HouseBuilding" or staticConstruction['classType'] == "FirstBuyBuilding"\
            or staticConstruction['classType'] == "GoldProductionBuilding":
          self.acc.model.calcResourcesLimit( self.acc.SD, self.acc.guest )
        if staticConstruction['classType'] == "HeroesBuilding":
          self.acc.model.updateHeroesForce( self.I.WS, self.acc )
        if staticConstruction['classType'] == "GuildBuilding":
          self.acc.model.resetGuild(self.I, self.acc)
        if staticConstruction['classType'] == "GoldProductionBuilding":
          self.acc.model.MarketingEventsInfo.GoldHouseActionState = GoldHouseActionState.ShowBuyHouseEvent
      else:
        self.errorResponse( "Static construction not found")
        return
    else:
      self.errorResponse( "Can not find building")
      return
  
    self.response["ok"] = 1
    self.fin()
