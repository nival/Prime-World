#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SkipObjectiveRequest import SkipObjectiveRequest

class Skip_objective( SubAction, SkipObjectiveRequest ):
  """action, который будет обрабатывать данный класс"""
  action = "skip_objective"

  @model_callback # АВТОМАТИЧЕСКИ АПДЕЙТИМ ИЗМЕНЕНИЯ В MODEL DATA
  @parse
  @action_timing
  def onStart(self):
    """стартовый метод для обработки action"""
    self.log()
    if not self.checkParams():
      return
    
    self.quest = self.arguments.quest
    self.objective = self.arguments.objective
    self.clientValue = self.arguments.clientValue
    if self.quest.id not in self.acc.model.ActiveQuests or not self.quest.state == QuestState.InProgress:
      self.errorResponse( "Quest is not active or accepted" )
      return
    
    self.staticObjective = self.acc.SD.getStaticObjective(self.quest, self.objective)
    if self.staticObjective:
      if self.objective.value < int(self.staticObjective['value']):
        self.price = self.acc.SD.copyPrice( self.staticObjective['skipPrice'] )
        if self.price and self.acc.SD.isValidPrice(self.price):
          self.needGold = int( self.price['Gold'] )
          reason = "PW!SKIP_OBJECTIVE:QUEST:" + str( self.quest.persistentId) + ":OBJECTIVE:" + str( self.objective.index)
          self.buy( self.price, self.onBuy, self.onBuyFunc, reason )
          return None
        else:
          self.errorResponse( "Invalid skip price" )
          return

      if self.quest.isComplete(self.acc.model, self.acc.SD):
        self.quest.state = QuestState.Complete
        self.I.STATS.addQuestChange( self.acc.auid, self.quest.persistentId, 2)

    self.response["ok"] = 1 # success 
    self.fin()

    
  @model_callback
  def onBuyFunc( self, response ):
    code = response["code"]
    if code == ibilling.ERROR_CODE_OK:
      self.doConfirmWriteOff( response )
      self.objective.SetValue( int(self.staticObjective['value']), self.staticObjective, self.acc.model, self.acc.SD, self.acc.sex, self.acc.db.fraction, self.I.WS, self.acc, self.acc.getConfigValue("ONE_TIME_QUESTS"), self.I.STATS, self.I.BILL, self.makeAccRandom(), self.I )
      if self.quest.isComplete(self.acc.model, self.acc.SD):
        self.quest.state = QuestState.Complete
        self.I.STATS.addQuestChange( self.acc.auid, self.quest.persistentId, 2)
      
      self.I.STATS.addResourcesChange( self.acc.auid, False, ResourceChangeItem.SkipQuestObjective, "%r"%(self.quest.persistentId), self.price, self.acc.model.Resources )  
      self.response["ok"] = 1 # success
    else:
      self.onBuyError( response, self.needGold )
      return

    self.fin()


  @action_timing
  def onBuy( self, response ):
    self.onBuyFunc( response )
