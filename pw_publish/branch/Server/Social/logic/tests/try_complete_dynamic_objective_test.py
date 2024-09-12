import sys
sys.path.append('../')
sys.path.append('../..')
from logic.try_complete_dynamic_objective import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class try_complete_dynamic_objective_test:

  def try_complete_dynamic_objective_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Silver = 1000

    questObjectiveId1 = modeldata.addNewDynamicObjective()
    questObjective1 = modeldata.getDynamicObjectiveByID(questObjectiveId1)
    questObjective1.QuestCheckType = DynamicQuestCheckType.Instant
    questObjective1.InstantCondition.ResourceType = CastleResources.Silver
    questObjective1.InstantCondition.TotalValue = 1000

    questObjectiveId2 = modeldata.addNewDynamicObjective()
    questObjective2 = modeldata.getDynamicObjectiveByID(questObjectiveId2)
    questObjective2.QuestCheckType = DynamicQuestCheckType.Instant
    questObjective2.InstantCondition.ResourceType = CastleResources.Perl
    questObjective2.InstantCondition.TotalValue = 3

    dynamicQuestId = modeldata.addNewDynamicQuest()
    dynamicQuest = modeldata.getDynamicQuestByID(dynamicQuestId)
    dynamicQuest.Objectives.add(questObjective1)
    dynamicQuest.Objectives.add(questObjective2)
    dynamicQuest.QuestState = QuestState.InProgress

    modeldata.DynamicQuests.add(dynamicQuest)

    assert len(modeldata.DynamicQuests) >= 1
    assert not questObjective1.IsCompleted
    assert not questObjective2.IsCompleted
    silver = modeldata.Resources.Silver
    perl = modeldata.Resources.Perl

    requests =  [ ( Try_complete_dynamic_objective, TryCompleteDynamicObjectiveRequest( modeldata, { "quest_id" : ["" + str(dynamicQuestId) + ""],
                                                                                                     "objective_id": ["" + str(questObjectiveId1) + ""]}, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Silver == silver - questObjective1.InstantCondition.TotalValue
    assert questObjective1.IsCompleted
    assert not questObjective2.IsCompleted
    assert dynamicQuest.QuestState != QuestState.Complete
    assert modeldata.Resources.Perl == perl

  def try_complete_dynamic_objective_test_not_enough_resources( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Silver = 0

    questObjectiveId1 = modeldata.addNewDynamicObjective()
    questObjective1 = modeldata.getDynamicObjectiveByID(questObjectiveId1)
    questObjective1.QuestCheckType = DynamicQuestCheckType.Instant
    questObjective1.InstantCondition.ResourceType = CastleResources.Silver
    questObjective1.InstantCondition.TotalValue = 1000

    dynamicQuestId = modeldata.addNewDynamicQuest()
    dynamicQuest = modeldata.getDynamicQuestByID(dynamicQuestId)
    dynamicQuest.Objectives.add(questObjective1)
    dynamicQuest.QuestState = QuestState.InProgress

    modeldata.DynamicQuests.add(dynamicQuest)

    assert len(modeldata.DynamicQuests) >= 1
    assert not questObjective1.IsCompleted
    silver = modeldata.Resources.Silver

    requests =  [ ( Try_complete_dynamic_objective, TryCompleteDynamicObjectiveRequest( modeldata, { "quest_id" : ["" + str(dynamicQuestId) + ""],
                                                                                                     "objective_id": ["" + str(questObjectiveId1) + ""]}, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Silver == silver
    assert not questObjective1.IsCompleted
    assert dynamicQuest.QuestState != QuestState.Complete

  def try_complete_dynamic_objective_with_quest_complete_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Silver = 1000

    questObjectiveId1 = modeldata.addNewDynamicObjective()
    questObjective1 = modeldata.getDynamicObjectiveByID(questObjectiveId1)
    questObjective1.QuestCheckType = DynamicQuestCheckType.Instant
    questObjective1.InstantCondition.ResourceType = CastleResources.Silver
    questObjective1.InstantCondition.TotalValue = 1000

    dynamicQuestId = modeldata.addNewDynamicQuest()
    dynamicQuest = modeldata.getDynamicQuestByID(dynamicQuestId)
    dynamicQuest.Objectives.add(questObjective1)
    dynamicQuest.QuestState = QuestState.InProgress

    modeldata.DynamicQuests.add(dynamicQuest)

    assert len(modeldata.DynamicQuests) >= 1
    assert not questObjective1.IsCompleted
    silver = modeldata.Resources.Silver

    requests =  [ ( Try_complete_dynamic_objective, TryCompleteDynamicObjectiveRequest( modeldata, { "quest_id" : ["" + str(dynamicQuestId) + ""],
                                                                                                     "objective_id": ["" + str(questObjectiveId1) + ""]}, False ) ) ]
    changeList = env.execActions( requests )

    assert modeldata.Resources.Silver == silver - questObjective1.InstantCondition.TotalValue
    assert dynamicQuest.QuestState == QuestState.Complete
    assert questObjective1.IsCompleted