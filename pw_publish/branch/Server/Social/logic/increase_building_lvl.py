#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from enums import *
from logic.requests.IncreaseBuildingLvlRequest import IncreaseBuildingLvlRequest

class Increase_building_lvl( SubAction, IncreaseBuildingLvlRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "increase_building_lvl"
  debug = True

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
      if construction.canUpgrade( self.arguments.level, self.acc.SD, self.acc.guilddata ):
        construction.Level += self.arguments.level
        staticConstruction = self.acc.SD.getStaticConstruction( construction )
        if staticConstruction:
          if staticConstruction['classType'] == "StorageBuilding" or staticConstruction['classType'] == "LibraryBuilding" or staticConstruction['classType'] == "HouseBuilding":
            self.acc.model.calcResourcesLimit( self.acc.SD, self.acc.guest )
          if staticConstruction['classType'] == "HouseBuilding":        
            self.acc.model.recalcPopulation( self.acc.SD, self.acc.guest )
          if staticConstruction['classType'] == "HeroesBuilding":
            self.acc.model.updateHeroesForce( self.I.WS, self.acc )
          if staticConstruction['classType'] == "GuildBuilding":
            if construction.ProductionState == ProductionState.Idle:
              cycle = self.acc.SD.getGuildProductionCycle(construction.Level)
              if cycle != None:            
                duration = construction.getProductionDuration( self.acc, self.I, 0, construction.ProductionCustomValue )[1]
                construction.startProduction( duration, 0, self.acc.model, self.acc.SD)
                construction.ResourceToProduce = construction.getProductionRandomResource(cycle['percents'], self.makeAccRandom())
            construction.getGuildBonusByLevel(self.acc, self.I)           
          if staticConstruction['classType'] == "Tavern" and construction.ProductionState == ProductionState.Idle and self.acc.getConfigValue("ENABLE_TAVERT_REROLL_ON_LEVELUP"):
            construction.rollQuestForTavern( staticConstruction, self.acc.getConfig(), self.acc.SD, self.acc.model )
          
      else:
        self.errorResponse( "Construction max level reached" )
        return
    else:
      self.errorResponse( "Construction is null" )
      return

    self.response["ok"] = 1 # success
    self.fin()
