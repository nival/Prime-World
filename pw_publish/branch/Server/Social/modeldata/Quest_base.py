#!/usr/bin/env python
from binascii import crc32
from enums import *

class Quest_base:
  def isComplete(self, model, SD):
    complete = True
    for objectiveId in self.objectives:
      objective = model.getObjectiveByID(objectiveId)
      staticObjective = SD.getStaticObjective(self, objective)
      if staticObjective is not None and objective.value < int(staticObjective['value']):
        complete = False
        break
    return complete
      
      
  def getObjective(self, index, model):
    for objectiveId in self.objectives:
      objective = model.getObjectiveByID(objectiveId)
      if objective.index == index:
        return objective
    return None
  
  def resetQuest(self, model, SD):
    if self.state == QuestState.Complete:
      return False
    staticQuest = SD.getStaticQuest(self) 
    objectives = self.objectives.keys()[:]
    for key in objectives:
      self.objectives.remove(key)
    if 'objectives' in staticQuest and 'Item' in staticQuest['objectives']:
      for i in xrange(0, len(staticQuest['objectives']['Item'])):
        objective_id = model.addNewObjective()
        objective = model.getObjectiveByID( objective_id )
        objective.index = i
        objective.lastEventId = model.StatisticEventId
        self.objectives.add( objective )    
    self.state = QuestState.New    
    return True
    
  
  def completeQuest( self, questLine, staticQuest, actionIndex, acc, iDict, randVal ):
    isNextQuest = False
        
    if staticQuest['rewards'] != "" and staticQuest['rewards'] != None:
      acc.model.applyActions( staticQuest['rewards'], acc.SD, acc.db.sex, acc.db.fraction, iDict.WS, acc, iDict.Config.getConfig( acc.userlocale ), iDict.STATS, iDict.BILL, randVal, iDict )
                
    if 'answers' in staticQuest and staticQuest['answers'] != None and staticQuest['answers'] != "" and actionIndex < len(staticQuest['answers']['Item']) and actionIndex >= 0:
      altReward = staticQuest['answers']['Item'][actionIndex]
      if 'actions' in altReward:
        acc.model.applyActions( altReward['actions'], acc.SD, acc.db.sex, acc.db.fraction, iDict.WS, acc, iDict.Config.getConfig( acc.userlocale ), iDict.STATS, iDict.BILL, randVal, iDict )
        if 'Item' in altReward['actions']:
          for questAction in altReward['actions']['Item']:
            if questAction['classType'] == "NextQuestAction":
              isNextQuest = True
              break

    needDefaultNextQuest = not isNextQuest
    if needDefaultNextQuest and questLine != None:
      countQuests = len(questLine['quests']['Item'])
      for i in xrange( 0, countQuests ):
        if questLine['quests']['Item'][i]['persistentId'] == staticQuest['persistentId']:
          if i+1 < countQuests:
            config = iDict.Config.getConfig( acc.userlocale )
            acc.model.addQuest( questLine['quests']['Item'][i+1], config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, iDict.STATS, acc )
            break
                   
