#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddTalentRequest import AddTalentRequest

class Add_talent( SubAction, AddTalentRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "add_talent"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    staticTalent = self.acc.SD.getStaticTalentByTalentId( self.arguments.static_talent_id )
    if staticTalent:
      #if staticTalent['rarity'] != "Class":
        talent_id = self.acc.model.addNewTalent()
        talent = self.acc.model.getTalentByID( talent_id )
        talent.IsNew = True
        talent.PersistentId = self.arguments.static_talent_id
        self.acc.model.UserInventory.add(talent_id)
     # else:
     #   self.errorResponse( "Class talents are not allowed to be added")
     #   return
    else:
      self.errorResponse( "Static talent not found")
      return
      
    
    self.response["ok"] = 1                   
    self.fin()
