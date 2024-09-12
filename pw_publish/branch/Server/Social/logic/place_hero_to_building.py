#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.PlaceHeroToBuildingRequest import PlaceHeroToBuildingRequest

class Place_hero_to_building( SubAction,PlaceHeroToBuildingRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "place_hero_to_building"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    hero = self.arguments.src_hero
    construction = self.arguments.construction

    if construction:
      if hero and hero.Hired:
        staticConstruction = self.acc.SD.getStaticConstruction( construction )
        if staticConstruction and staticConstruction['classType'] == "Tavern" and construction.ProductionState == ProductionState.Finished:
          self.errorResponse( "Can not place hero now" )
          return          
        
        
        for buildingId in hero.InBuildings.keys():
          building = self.acc.model.getConstructionByID( buildingId )
          if building:   
            stBuilding = self.acc.SD.getStaticConstruction( building )
            if stBuilding and stBuilding['classType'] == "Tavern" and building.ProductionState == ProductionState.Finished:
              self.errorResponse( "Can not place hero now" )
              return        
              
        # Remove from others construction
        buildings = self.acc.model.Buildings.keys()[:]
        buildings.sort()
        for buildingId in buildings:
          building = self.acc.model.getConstructionByID( buildingId )
          if buildingId != construction.id:
            if building.ProductionState == ProductionState.Busy:             
              heroes = building.HeroesInBuilding.keys()[:]
              heroes.sort()
              for heroId in heroes:
                if heroId == hero.id:
                  building.removeHeroFromBuilding( hero, self.acc, self.I )
                  break            
        
        maxHeroes = 0
        if staticConstruction and staticConstruction['classType'] == "Tavern":
          maxHeroes = construction.getTavernMaxHeroesCount( staticConstruction, self.acc.SD )       
        else:
          self.errorResponse( "Hero can not be placed here" )
          return
        if len(construction.HeroesInBuilding) < maxHeroes:
          if hero.InMatchmaking == False:
            if not hero.id  in construction.HeroesInBuilding:
              if construction.ProductionState == ProductionState.Busy:
                construction.stopProduction( self.acc, self.I )
              hero.InBuildings.add( construction )
              construction.HeroesInBuilding.add( hero )
            else:
              self.errorResponse( "Hero is already in building" )
              return
          else:
            self.errorResponse( "Hero is in MatchMaking" )
            return
        else:
          self.errorResponse( "Building is full. MaxHeroes = " + str(maxHeroes) )
          return        
      else:
        self.errorResponse( "Hero is not hired" )
        return
    else:
      self.errorResponse( "Construction is null" )
      return
   
    self.response["ok"] = 1 # success
    self.fin()
