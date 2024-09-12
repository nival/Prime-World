#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from enums import *
from logic.requests.ChangeMapRequest import ChangeMapRequest

class Change_map( SubAction, ChangeMapRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "change_map"
  debug = True

  # клиент просит переместить вещь из инвентаря в талантсет
  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    self.I.Config.eventMaps = []
    map_name = self.arguments.map
    self.acc.model.updateMap(MapType.CTF, map_name, True, 0, 0, True)
    
    self.response["ok"] = 1 # success 

    self.fin()