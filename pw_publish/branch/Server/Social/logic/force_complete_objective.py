#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ForceCompleteObjectiveRequest import ForceCompleteObjectiveRequest

class Force_complete_objective( SubAction, ForceCompleteObjectiveRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "force_complete_objective"
  debug = True

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    quest = self.arguments.quest
    objective = self.arguments.objective
    value = self.arguments.value

    staticObjective = self.acc.SD.getStaticObjective(quest, objective)
    if staticObjective:
      objective.SetValue(value, staticObjective, self.acc.model, self.acc.SD, self.acc.sex, self.acc.db.fraction, self.I.WS, self.acc, self.acc.getConfigValue("ONE_TIME_QUESTS"), self.I.STATS, self.I.BILL, self.makeAccRandom(), self.I )

      if objective.value >= int(staticObjective['value']):
        if quest.isComplete(self.acc.model, self.acc.SD):
          quest.state = QuestState.Complete
          self.I.STATS.addQuestChange( self.acc.auid, quest.persistentId, 2)
          
   
    self.response["ok"] = 1 # success 
    self.fin()
