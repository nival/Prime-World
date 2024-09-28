#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.TavernRerollRequest import TavernRerollRequest

class Tavern_reroll( SubAction, TavernRerollRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "tavern_reroll"
  debug = True
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    all_buildings = self.acc.model.Buildings.keys()
    all_buildings.extend( self.acc.model.Pocket.keys() )    
    for buildingId in all_buildings:  
      building = self.acc.model.getConstructionByID( buildingId )
      if building and building.ProductionState == ProductionState.Idle:
        staticConstruction = self.acc.SD.getStaticConstruction( building )
        if staticConstruction and staticConstruction['classType'] == "Tavern":           
          if self.arguments.level >=0 and self.arguments.index>=0:
            building.BuildingQuest.Level = self.arguments.level
            building.BuildingQuest.Index = self.arguments.index
            building.BuildingQuest.IsDailyQuestFinished = False
            building.clearCraftedTalents()
            self.acc.model.rollTalentForTavernBuilding(building, staticConstruction, self.acc.SD,  self.acc.model.LordInfo.TavernRandomSeed )
            self.acc.model.LordInfo.TavernRandomSeed = self.acc.model.getRandom( self.acc.model.LordInfo.TavernRandomSeed )
          else:
            building.rollQuestForTavern( staticConstruction, self.acc.getConfig(), self.acc.SD, self.acc.model )
    self.response["ok"] = 1
    self.fin()
