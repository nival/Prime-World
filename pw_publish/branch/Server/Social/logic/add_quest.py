#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddQuestRequest import AddQuestRequest

class Add_quest( SubAction, AddQuestRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "add_quest"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    staticQuest = self.acc.SD.getStaticQuestById( self.arguments.PersistentId )
    if staticQuest:
      addedQuest = self.acc.model.addQuest( staticQuest, None, self.acc.getConfigValue("ALTERNATIVE_QUESTS"), False, False, self.I.STATS, self.acc )
      if addedQuest == None:
        self.errorResponse( "Must be unique quest" )
        return
    else:
      self.errorResponse( "Static quest not found" )
      return
      
    self.response["ok"] = 1
    self.fin()
