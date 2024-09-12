#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.TryCompleteObjectiveRequest import TryCompleteObjectiveRequest

class Try_complete_objective( SubAction, TryCompleteObjectiveRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "try_complete_objective"

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
    clientValue = self.arguments.clientValue

    staticObjective = self.acc.SD.getStaticObjective(quest, objective)
    if staticObjective and quest.id in self.acc.model.ActiveQuests and quest.state == QuestState.InProgress:
      #MOVSIC: адский костыль - создает хотя бы одно изменение в ModelData
      quest.state = QuestState.InProgress
      #статистика не нужна, ибо костыль
      #self.I.STATS.addQuestChange( self.acc.auid, quest.persistentId, 2)
      if objective.value < int(staticObjective['value']):
        value = objective.update(staticObjective, self.acc, self.acc.model, self.acc.SD, self.acc.friendsdata)
        if value == None:
          value = clientValue
        objective.SetValue( value, staticObjective, self.acc.model, self.acc.SD, self.acc.sex, self.acc.db.fraction, self.I.WS, self.acc, self.acc.getConfig(), self.I.STATS, self.I.BILL, self.makeAccRandom(), self.I )
              
      if objective.value >= int(staticObjective['value']):
        if quest.isComplete(self.acc.model, self.acc.SD):
          quest.state = QuestState.Complete  
          self.I.STATS.addQuestChange( self.acc.auid, quest.persistentId, 2)
      else:
        if staticObjective['errorCode'] and int(staticObjective['errorCode']) != 0:
          #а если в objective был errorMessage, то его и отправим клиенту.
          self.errorResponse( int(staticObjective['errorCode']), "Complete objective [" + str(objective.id) + "] failed for quest [" + str(quest.id) + "]" )
          return
    else:         
      self.errorResponse(  "Quest error in StaticQuest or Id or state or not in ActiveQuests" )
      return
   
    self.response["ok"] = 1 # success
    self.fin()
