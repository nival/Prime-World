# -*- coding: utf-8 -*-
import sys
from subaction import *
from StatisticCore.ttypes import TalentInfo, TalentChangeOperation
from logic.requests.CollectTalentRequest import CollectTalentRequest

class Collect_talent( SubAction, CollectTalentRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "collect_talent"

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
      self.acc.model.addStatisticEvent( StatisticEventType.TALENT_FINISH, "", len(construction.CraftedTalentsToLibrary) )
      allCrafted = construction.CraftedTalentsToLibrary.keys()[:]
      allCrafted.sort()
      for talId in allCrafted:
        construction.CraftedTalentsToLibrary.remove(talId)

      self.response["ok"] = 1 # success
    else:
      self.errorResponse( "Building is not exist")
      return
      
    self.fin()
