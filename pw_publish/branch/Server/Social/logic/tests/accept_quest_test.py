from base.helpers import *
sys.path.append('../')
from logic.accept_quest import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class accept_quest_test:

  def accept_quest_test( self, env ):
    modeldata = env.acc.model

    staticQuest = env.acc.SD.getStaticQuestById(crc32('s12_qA'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
      objective = quest.objectives[quest.objectives.keys()[0]]


    requests = [ ( Accept_quest, AcceptQuestRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert quest.state == QuestState.InProgress

  def accept_quest_without_objectives( self, env ):
    modeldata = env.acc.model
    questLine = None

    staticQuest = ClassDict()
    staticQuest['Description'] = "Test"
    staticQuest['Title'] = "Test"
    staticQuest['altRewards'] = None
    staticQuest['autoOpen'] = None
    staticQuest['classType'] = "Quest"
    staticQuest['objectives'] = None
    staticQuest['persistentId'] = "test_quest"

    env.acc.SD.data['Quests'][crc32(staticQuest['persistentId'])] = staticQuest

    quest_id = modeldata.addNewQuest()
    quest = modeldata.getQuestByID( quest_id )
    quest.state = QuestState.New
    quest.dialogPage = 0
    quest.persistentId = crc32(staticQuest['persistentId'])
    modeldata.ActiveQuests.add( quest_id )  
    quest = quest
    staticQuest = staticQuest


    requests = [ ( Accept_quest, AcceptQuestRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert quest.state == QuestState.Complete   
    
  def accept_h21_no_autocomplete_test( self, env ):
    modeldata = env.acc.model
    modeldata.Resources.Resource3 = 21000
    staticQuest = env.acc.SD.getStaticQuestById(crc32('h21_qA'))
    if staticQuest:
      quest = modeldata.addQuest( staticQuest, None, None, False, False, env.I.STATS, env.acc )
      objective = quest.objectives[quest.objectives.keys()[0]]
      quest.state = QuestState.New   
    assert objective.value == 0
    
    requests = [ ( Accept_quest, AcceptQuestRequest( modeldata, { "quest_id" : ["" + str(quest.id) + ""] }, False ) ) ]
    changeList = env.execActions( requests )
    
    assert quest.state == QuestState.InProgress  
    assert objective.value == 0
    assert modeldata.Resources.Resource3 == 21000
    

