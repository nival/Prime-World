#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.StopBuildingProductionRequest import StopBuildingProductionRequest

class Stop_building_production( SubAction, StopBuildingProductionRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "stop_building_production"

  # клиент просит переместить вещь из инвентаря в талантсет
  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    construction = self.arguments.construction
    staticConstruction = self.acc.SD.getStaticConstruction( construction )
    
    if construction and staticConstruction:  
      if construction.ProductionState == ProductionState.Busy:
        construction.stopProduction( self.acc, self.I )
      else:
        self.errorResponse( "Construction is not in Busy state" )
        return
    else:
      self.errorResponse( "Construction is null" )
      return
    
    self.response["ok"] = 1 # success
    self.fin()
