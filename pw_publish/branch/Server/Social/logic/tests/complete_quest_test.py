import sys
sys.path.append('../')
from logic.complete_quest import *
from logic.accept_quest import *
from logic.try_complete_objective import *
from logic.force_complete_objective import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class complete_quest_test:   
  def complete_quest_with_actions_test( self, env ):
    modeldata = env.acc.model

    staticQuest = env.acc.SD.getStaticQuestById(crc32('c31_qA'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc)
      objective = quest.objectives[quest.objectives.keys()[0]]
      quest.state = QuestState.Complete   

    assert modeldata.ActiveQuests.get(quest.id).id == quest.id
    assert modeldata.CompletedQuests.get(quest.id) == None
    modeldata.LordInfo.Fame = 1000
    fame = modeldata.LordInfo.Fame
    silver = modeldata.Resources.Silver
    talents = len(modeldata.UserInventory)

    requests =  [ ( Complete_quest, CompleteQuestRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "reward_index" : [0] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.ActiveQuests.get(quest.id) == None
    assert modeldata.CompletedQuests.get(quest.id).id == quest.id
    assert fame < modeldata.LordInfo.Fame
    assert modeldata.LordInfo.Fame - fame == int(staticQuest['rewards']['Item'][0]['fame'])
    assert silver < modeldata.Resources.Silver
    assert modeldata.Resources.Silver - silver == int(staticQuest['rewards']['Item'][0]['resources']['Silver'])

  def get_next_quest_by_default_test( self, env ):
    modeldata = env.acc.model

    #Resources = env.generate_resources(00)
    modeldata.Resources = env.generate_resources(0)
    modeldata.Resources.Gold = 100
    env.I.BILL.setGold( env.acc.auid, 100 )

    assert len( modeldata.ActiveQuests ) == 1
    assert len( modeldata.CompletedQuests ) == 1

    staticQuest = env.acc.SD.getStaticQuestById(crc32('s12_qA'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
      objective = quest.objectives[quest.objectives.keys()[0]]
      quest.state = QuestState.New

    assert len( modeldata.ActiveQuests ) == 2


    requests =  [( Accept_quest, AcceptQuestRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""] }, False ) ),
                 ( Force_complete_objective, ForceCompleteObjectiveRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "objective_id" : ["" + str(objective.id) + ""], "value" : [1000]}, False ) ),      
                 ( Try_complete_objective, TryCompleteObjectiveRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "objective_id" : ["" + str(objective.id) + ""]}, False ) ),     
                 ( Complete_quest, CompleteQuestRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "reward_index" : [0] }, False ) ) ]

    changeList = env.execActions( requests )

    assert len( modeldata.ActiveQuests ) == 2
    assert len( modeldata.CompletedQuests ) == 2
    assert modeldata.CompletedQuests.get(quest.id).id == quest.id

  def complete_quest_with_hero_reward_test1( self, env ):
    modeldata = env.acc.model

    staticQuest = env.acc.SD.getStaticQuestById(crc32('s13_qA'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
      objective = quest.objectives[quest.objectives.keys()[0]]
      quest.state = QuestState.Complete   

    heroesCount = len(modeldata.Heroes)

    requests =  [ ( Complete_quest, CompleteQuestRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "reward_index" : [0] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.Heroes) == heroesCount + 1

  def complete_quest_with_hero_reward_test2( self, env ):
    modeldata = env.acc.model

    staticQuest = env.acc.SD.getStaticQuestById(crc32('s13_qA'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
      objective = quest.objectives[quest.objectives.keys()[0]]
      quest.state = QuestState.Complete   

    heroesCount = len(modeldata.Heroes)
    modeldata.Resources = env.generate_resources(10000)  
    modeldata.hireHero( crc32('highlander'), 0 , env.I.WS, env.acc, env.I )
    assert len(modeldata.Heroes) == heroesCount + 1

    requests =  [ ( Complete_quest, CompleteQuestRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "reward_index" : [0] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.Heroes) + 1


  def complete_quest_with_actions_twice_test( self, env ):
    modeldata = env.acc.model

    staticQuest = env.acc.SD.getStaticQuestById(crc32('c21_qA'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
      objective = quest.objectives[quest.objectives.keys()[0]]
      quest.state = QuestState.Complete   

    assert modeldata.ActiveQuests.get(quest.id).id == quest.id
    assert modeldata.CompletedQuests.get(quest.id) == None
    modeldata.LordInfo.Fame = 100
    fame = modeldata.LordInfo.Fame
    silver = modeldata.Resources.Silver

    requests =  [ ( Complete_quest, CompleteQuestRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "reward_index" : [0] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.ActiveQuests.get(quest.id) == None
    assert modeldata.CompletedQuests.get(quest.id).id == quest.id
    assert fame < modeldata.LordInfo.Fame
    assert silver < modeldata.Resources.Silver

    fame = modeldata.LordInfo.Fame
    silver = modeldata.Resources.Silver

    requests =  [ ( Complete_quest, CompleteQuestRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "reward_index" : [0] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.ActiveQuests.get(quest.id) == None
    assert modeldata.CompletedQuests.get(quest.id).id == quest.id
    assert fame == modeldata.LordInfo.Fame
    assert silver == modeldata.Resources.Silver
    
  def complete_quest_with_pendings_quest( self, env ):
    # no more fairy-tale quests :((
    return
    modeldata = env.acc.model

    staticQuest = env.acc.SD.getStaticQuestById(crc32('tutorialFinal_qB'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
      quest.state = QuestState.Complete   

    assert len( modeldata.PendingQuests ) == 0

    requests =  [ ( Complete_quest, CompleteQuestRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "reward_index" : [0] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len( modeldata.PendingQuests ) == 1

  def complete_quest_with_lamp_action( self, env ):
    modeldata = env.acc.model

    staticQuest = env.acc.SD.getStaticQuestById(crc32('testQ'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
      quest.state = QuestState.Complete

    assert len( modeldata.PendingQuests ) == 0

    requests =  [ ( Complete_quest, CompleteQuestRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "reward_index" : [0] }, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.MarketingEventsInfo.LampEventInfo.dbId == "/UI/Content/MarketingEvents/GoldLamp_0"
    assert modeldata.MarketingEventsInfo.LampEventInfo.BonusLeft == 200
    assert (modeldata.MarketingEventsInfo.LampEventInfo.EndTime - modeldata.MarketingEventsInfo.LampEventInfo.StartTime) == 600
    assert modeldata.MarketingEventsInfo.LampEventInfo.TransactionsLeft == 10

