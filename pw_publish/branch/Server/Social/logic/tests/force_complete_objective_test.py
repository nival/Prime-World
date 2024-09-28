import sys
sys.path.append('../')
from logic.force_complete_objective import *
from binascii import crc32
from base.helpers import *
sys.path.append('../..')
from enums import *

class force_complete_objective_test:

  def force_complete_objective_test( self, env ):
    modeldata = env.acc.model
    value = 100500

    staticQuest = env.acc.SD.getStaticQuestById(crc32('c11_qA'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
      objective = quest.objectives[quest.objectives.keys()[0]]

      quest.state = QuestState.InProgress


    assert objective.value == 0

    requests = [ ( Force_complete_objective, ForceCompleteObjectiveRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""], "objective_id" : ["" + str(objective.id) + ""], "value" : [value]}, False ) ) ]
    changeList = env.execActions( requests )
    
    staticObj = env.acc.SD.getStaticObjective(quest, objective)

    assert objective.value == int(staticObj['value'])
    assert quest.state == QuestState.Complete