#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AcceptQuestRequest import AcceptQuestRequest

class Accept_quest( SubAction, AcceptQuestRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "accept_quest"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    quest = self.arguments.quest
    if quest and quest.state == QuestState.New and quest.id in self.acc.model.ActiveQuests:
      quest.state = QuestState.InProgress
      self.I.STATS.addQuestChange( self.acc.auid, quest.persistentId, 1)
      objectives = quest.objectives.keys()[:]
      objectives.sort()
      for objectiveId in objectives:
        objective = self.acc.model.getObjectiveByID(objectiveId)
        staticObjective = self.acc.SD.getStaticObjective(quest, objective)
        if staticObjective:
          value = 0
          objective.lastEventId = self.acc.model.StatisticEventId;
          if 'autoCompleteCondition' in staticObjective and staticObjective['autoCompleteCondition'] and 'code' in staticObjective['autoCompleteCondition'] and staticObjective['autoCompleteCondition']['code']:
            value = self.acc.model.execQuestCondition( staticObjective['autoCompleteCondition']['code'], self.acc.sex, self.acc.SD, self.acc.getConfig() )
          else:
            value = objective.update(staticObjective, self.acc, self.acc.model, self.acc.SD, self.acc.friendsdata)
            if value == None:
              value = 0
          objective.SetValue(value, staticObjective, self.acc.model, self.acc.SD, self.acc.sex, self.acc.db.fraction, self.I.WS, self.acc, self.acc.getConfig(), self.I.STATS, self.I.BILL, self.makeAccRandom(int(objectiveId)), self.I)

      # Сразу же пытаемся закомплитить ( PF-43686 )
      if quest.isComplete(self.acc.model, self.acc.SD):
        quest.state = QuestState.Complete
        self.I.STATS.addQuestChange( self.acc.auid, quest.persistentId, 2)
        quest.IsAutoCompleted = True
      
    self.response["ok"] = 1 # success 
    self.fin()
