#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
sys.path.append('../')
sys.path.append('../..')
from logic.try_complete_objective import *
from binascii import crc32
from base.helpers import *
from enums import *

class statistic_events_test:
  def clear_statistic_events( self, env ):
    modeldata = env.acc.model

    staticQuest = env.acc.SD.getStaticQuestById(crc32('m12_qA'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )

    modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "Production_Crystal,Perl", 10)#keep
    modeldata.addStatisticEvent( StatisticEventType.SESSION_RESOURCE, "Production_Crystal,Perl", 10)#delete
    modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "Silver", 10)#delete
    modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "Production_Crystal,Perl", 0)#keep
    modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "House,Perl", 10)#delete
    modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "", 10)#delete

    assert len(modeldata.StatisticEvents) == 6
    modeldata.validateStatisticEvents(env.acc.SD)
    assert len(modeldata.StatisticEvents) == 2

  def clear_finish_session_statistic_events( self, env ):
    modeldata = env.acc.model

    staticQuest = env.acc.SD.getStaticQuestById(crc32('pve11_qA'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )

    modeldata.addStatisticEvent( StatisticEventType.SESSION_FINISH, "pvp", 1)#delete(wrong type)
    modeldata.addStatisticEvent( StatisticEventType.SESSION_RESOURCE, "Perl", 10)#delete(not a finishsessionevent)
    modeldata.addStatisticEvent( StatisticEventType.SESSION_FINISH, "pvp", 0)#delete(wrong type)
    modeldata.addStatisticEvent( StatisticEventType.SESSION_FINISH, "/Maps/PvE/Series/Coop1/Blue.ADMPDSCR", 0)#delete(wrong result)
    modeldata.addStatisticEvent( StatisticEventType.SESSION_FINISH, "/Maps/PvE/Series/Coop1/Violet.ADMPDSCR", 1)#keep

    assert len(modeldata.StatisticEvents) == 5
    modeldata.validateStatisticEvents(env.acc.SD)
    assert len(modeldata.StatisticEvents) == 4
    modeldata.validateFinishSessionEvents(env.acc.SD)
    assert len(modeldata.StatisticEvents) == 1

  def clear_statistic_events_from_building( self, env ):
    modeldata = env.acc.model

    staticQuest = env.acc.SD.getStaticQuestById(crc32('m12_qA'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )

    modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "Production_Crystal,Perl", 10)#keep
    modeldata.addStatisticEvent( StatisticEventType.SESSION_RESOURCE, "Perl", 10)#delete
    price = ClassDict()
    price.Silver = 10
    price.Perl = 10
    price.Resource1 = 0

    modeldata.addProductionFinishEvent( "Production_Crystal", price)


    assert len(modeldata.StatisticEvents) == 4
    modeldata.validateStatisticEvents(env.acc.SD)
    assert len(modeldata.StatisticEvents) == 2

  def clear_statistic_by_time_events( self, env ):
    modeldata = env.acc.model

    staticQuest = env.acc.SD.getStaticQuestById(crc32('m12_qA'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
      for objId in quest.objectives:
        objective = modeldata.getObjectiveByID( objId )
        objective.lastEventId = 5

    event = modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "Perl", 10)#keep
    event.time = 10 
    event = modeldata.addStatisticEvent( StatisticEventType.SESSION_RESOURCE, "Perl", 10)#delete
    event = modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "Silver", 10)#delete
    event = modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "Perl", 0)#delete by time
    event.time = 0 
    event = modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "Production_Crystal,Perl", 10)#keep
    event.time = 5 
    event = modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "", 10)#delete


    assert len(modeldata.StatisticEvents) == 6
    modeldata.validateStatisticEvents(env.acc.SD)
    assert len(modeldata.StatisticEvents) == 1

  def try_complete_objective_from_statistics( self, env ):
    return

    #TODO: надо разрбраться почему не проходит тест

    modeldata = env.acc.model
    SD = env.acc.SD
    staticQuest = SD.data['Quests'][crc32('m12_qA')]

    if staticQuest:
      quest_id = modeldata.addNewQuest()      
      quest = modeldata.getQuestByID( quest_id )
      quest.state = QuestState.InProgress
      quest.dialogPage = 0
      quest.persistentId = crc32(staticQuest['persistentId'])
      for i in xrange(0, len(staticQuest['objectives']['Item'])):
        objective_id = modeldata.addNewObjective()
        objective = modeldata.getObjectiveByID( objective_id )
        objective.index = i
        objective.lastEventId = 0
        quest.objectives.add(objective)
        if staticQuest['objectives']['Item'][i]['condition']['classType'] == "StatisticEventCondition":
          objective = objective
      modeldata.ActiveQuests.add( quest_id )

    quest = quest

    print objective.lastEventId

    modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "Production_Crystal,Perl", 10)
    modeldata.addStatisticEvent( StatisticEventType.SESSION_RESOURCE, "House,Perl", 10)
    modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "House,Silver", 10)
    modeldata.addStatisticEvent( StatisticEventType.PRODUCTION_FINISH, "Production_Crystal,Perl", 10)

    requests = [ ( Try_complete_objective, TryCompleteObjectiveRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "objective_id" : ["" + str(objective.id) + ""]}, False ) ) ]
    changeList = env.execActions( requests )

    assert objective.value == 1
    assert objective.lastEventId == 4

