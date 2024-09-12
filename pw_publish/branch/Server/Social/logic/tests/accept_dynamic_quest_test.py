import sys
sys.path.append('../')
sys.path.append('../..')
from logic.accept_dynamic_quest import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class accept_dynamic_quest_test:

  def accept_dynamic_quest_test( self, env ):
    modeldata = env.acc.model

    questObjectiveId1 = modeldata.addNewDynamicObjective()
    questObjective1 = modeldata.getDynamicObjectiveByID(questObjectiveId1)
    questObjective1.QuestCheckType = DynamicQuestCheckType.Instant
    questObjective1.InstantCondition.ResourceType = CastleResources.Silver
    questObjective1.InstantCondition.TotalValue = 1000

    dynamicQuestId = modeldata.addNewDynamicQuest()
    dynamicQuest = modeldata.getDynamicQuestByID(dynamicQuestId)
    dynamicQuest.Objectives.add(questObjective1)
    modeldata.DynamicQuests.add(dynamicQuest)

    assert dynamicQuest.QuestState == QuestState.New

    requests =  [ ( Accept_dynamic_quest, AcceptDynamicQuestRequest( modeldata, { "quest_id" : ["" + str(dynamicQuest.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert dynamicQuest.QuestState == QuestState.InProgress
