#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BuildingMoveRequest import BuildingMoveRequest

class Building_move( SubAction, BuildingMoveRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "building_move"

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
      construction.Position.X = self.arguments.x
      construction.Position.Y = self.arguments.y
      construction.Position.Pitch = self.arguments.pitch
    else:
      self.errorResponse( "Construction is null" )
      return

    self.response["ok"] = 1
    self.fin()