#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveHeroFromBuildingRequest import RemoveHeroFromBuildingRequest

class Remove_hero_from_building( SubAction, RemoveHeroFromBuildingRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "remove_hero_from_building"

  # клиент просит переместить вещь из инвентаря в талантсет
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
      staticConstruction = self.acc.SD.getStaticConstruction( construction )
      if staticConstruction and staticConstruction['classType'] == "Tavern" and construction.ProductionState == ProductionState.Finished:
        self.errorResponse( "Can not remove hero now" )
        return        
      if hero and hero.Hired:
        if hero.id in construction.HeroesInBuilding:
          construction.removeHeroFromBuilding( hero, self.acc, self.I )
        else:
          self.errorResponse( "Hero is not in building" )
          return
      else:
        self.errorResponse( "Hero is not hired" )
        return
    else:
      self.errorResponse( "Construction is null" )
      return
    
    self.response["ok"] = 1 # success
    self.fin()
