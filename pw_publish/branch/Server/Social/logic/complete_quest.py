#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.CompleteQuestRequest import CompleteQuestRequest

class Complete_quest( SubAction, CompleteQuestRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "complete_quest"

  
  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    quest = self.arguments.quest
    reward_index = self.arguments.reward_index 
    questLine = None
    
    staticQuest = self.acc.SD.getStaticQuest( quest )
    if staticQuest:
      if quest.state == QuestState.Complete and quest.id in self.acc.model.ActiveQuests:
        for qstLine in self.acc.SD.data['QuestsLine']['Item']:
          for qst in qstLine['quests']['Item']:
            if staticQuest['persistentId'] == qst['persistentId']:
              questLine = qstLine
              break
          if questLine != None:
            break        
        self.acc.model.CompletedQuests.add(quest)
        self.acc.model.ActiveQuests.remove(quest)
        quest.completeQuest( questLine, staticQuest, reward_index, self.acc, self.I, self.makeAccRandom())
      else:
        self.errorResponse( "Quest is not in complete state" )
        return
    else:
      self.errorResponse( "Static quest not found" )
      return
      
    self.response["ok"] = 1 # success
    self.fin()
