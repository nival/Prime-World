#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetSteamSexRequest import SetSteamSexRequest

class Set_steam_sex( SubAction, SetSteamSexRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "set_steam_sex"
  
  @model_callback
  @parse
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    if self.acc.db.sex:
      self.errorResponse( "Gender was already setted")
      return       
    
    if self.acc.original_snid != 'st': 
      self.errorResponse( "Not Steam, but %s " % self.acc.original_snid)
      return       

    self.acc.db.sex = self.arguments.gender
    
    self.response["db"] = self.acc.db
    self.response["ok"] = 1
    self.fin()