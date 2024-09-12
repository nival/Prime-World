#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddAllTalentsRequest import AddAllTalentsRequest

class Add_all_talents( SubAction, AddAllTalentsRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "add_all_talents"
  debug = True
  
  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    talents = []
    for talentID in self.acc.SD.data['Talents']:
      staticTalent = self.acc.SD.getStaticTalentByTalentId( talentID )
      if staticTalent['rarity'] != "Class" and talentID != 0:
        talents.append(talentID)
    
    talents.sort()
    
    for i in xrange(0, len(talents)):
      talent_id = self.acc.model.addNewTalent()
      talent = self.acc.model.getTalentByID( talent_id )
      talent.IsNew = True
      talent.PersistentId = talents[i]
      self.acc.model.UserInventory.add(talent_id)
      
    self.response["ok"] = 1 # success 
    self.fin()
