#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddToPocketRequest import AddToPocketRequest

class Add_to_pocket( SubAction, AddToPocketRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "add_to_pocket"
  debug = True
  
  @model_callback
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return

    staticConstruction = self.acc.SD.getStaticConstructionByPersistentId( self.arguments.PersistentId  )
    if staticConstruction:
      if self.arguments.level < len(staticConstruction['Levels']['Item']):
        construction_uid = self.acc.model.addNewConstruction()
        construction = self.acc.model.getConstructionByID( construction_uid )
        construction.PersistentId = self.arguments.PersistentId
        construction.Level = self.arguments.level
        self.acc.model.Pocket.add( construction )  
      else:
        self.errorResponse( "Static construction max level reached")
        return                  
    else:
      self.errorResponse( "Static construction not found")
      return          

    self.response["ok"] = 1
    self.fin()