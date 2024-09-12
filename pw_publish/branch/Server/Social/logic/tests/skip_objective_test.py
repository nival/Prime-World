import sys
sys.path.append('../')
from logic.skip_objective import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class skip_objective_test:
  def skip_objective_test( self, env ):
    modeldata = env.acc.model

    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)

    staticQuest = env.acc.SD.getStaticQuestById(crc32('c24_qB'))
    quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
    quest.state = QuestState.InProgress
    objective = quest.objectives[quest.objectives.keys()[0]]
    staticObjective = env.acc.SD.getStaticObjective(quest, objective)
    staticObjective['skipPrice']['Silver'] = 100


    assert len(modeldata.ActiveQuests) == 2
    assert len(modeldata.ObjectivesKeeper) >= len(staticQuest['objectives']['Item'])
    assert objective.value == 0

    requests = [ ( Skip_objective, SkipObjectiveRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "objective_id" : ["" + str(objective.id) + ""]}, False ) ) ]
    changeList = env.execActions( requests )

    #assert len(modeldata.ActiveQuests) == 1
    assert len(modeldata.CompletedQuests) == 1

    staticObj = env.acc.SD.getStaticObjective(quest, objective)
    assert objective.value == int(staticObj['value'])
    assert quest.state == QuestState.Complete

  def skip_unaccepted_objective_test( self, env ):
    modeldata = env.acc.model

    Resources = env.generate_resources(2000)
    modeldata.Resources = env.generate_resources(2000)

    staticQuest = env.acc.SD.getStaticQuestById(crc32('c24_qB'))
    quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
    objective = quest.objectives[quest.objectives.keys()[0]]
    staticObjective = env.acc.SD.getStaticObjective(quest, objective)
    staticObjective['skipPrice']['Silver'] = 100

    assert len(modeldata.ActiveQuests) == 2
    assert len(modeldata.ObjectivesKeeper) >= len(staticQuest['objectives']['Item'])
    assert objective.value == 0

    requests = [ ( Skip_objective, SkipObjectiveRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "objective_id" : ["" + str(objective.id) + ""]}, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.ActiveQuests) == 2

    assert objective.value == 0
    assert quest.state == QuestState.New

