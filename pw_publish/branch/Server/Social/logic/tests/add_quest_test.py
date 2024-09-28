import sys
sys.path.append('../')
from logic.add_quest import *
from binascii import crc32
sys.path.append('../..')
from enums import *

class add_quest_test:

  def add_quest_test( self, env ):
    modeldata = env.acc.model
    questId = crc32('c11_qA')
    # give fame to lord, because quest may require high level
    modeldata.LordInfo.Fame = 10000000
    id = modeldata.next_uid_ + 1
    questsCount = len(modeldata.ActiveQuests)

    requests =  [ ( Add_quest, AddQuestRequest( modeldata, { "PersistentId" : ["" + str(questId) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.ActiveQuests) == questsCount + 1

    assert( modeldata.getQuestByID(id).persistentId == questId )
    assert( modeldata.getQuestByID(id).state == QuestState.New )
    assert( len(modeldata.getQuestByID(id).objectives) > 0 )
    assert( id in modeldata.ActiveQuests )

  def add_oneTime_quest_test( self, env ):
    modeldata = env.acc.model
    # give fame to lord, because quest may require high level
    modeldata.LordInfo.Fame = 10000000
    for questId in env.acc.SD.data['Quests']:
      quest = env.acc.SD.data['Quests'][questId]
      if quest['oneTime'] and len(quest['prerequisiteQuests']) == 0:
        staticQuest = quest
        PersistentId = crc32(staticQuest['persistentId'])
        break

    questsCount = len(modeldata.ActiveQuests)

    config = env.I.Config.getConfig( env.acc.userlocale )
    addedQuest = modeldata.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, env.I.STATS, env.acc )
    modeldata.ActiveQuests.add(addedQuest)
    assert len(modeldata.ActiveQuests) == questsCount + 1

    requests =  [ ( Add_quest, AddQuestRequest( modeldata, { "PersistentId" : ["" + str(PersistentId) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.ActiveQuests) == questsCount + 1

  def add_oneTime_quest_test2( self, env ):
    modeldata = env.acc.model
    # give fame to lord, because quest may require high level
    modeldata.LordInfo.Fame = 10000000
    for questId in env.acc.SD.data['Quests']:
      quest = env.acc.SD.data['Quests'][questId]
      if quest['oneTime'] and len(quest['prerequisiteQuests']) == 0:
        staticQuest = quest
        PersistentId = crc32(staticQuest['persistentId'])
        break

    questsCount = len(modeldata.CompletedQuests)
    
    config = env.I.Config.getConfig( env.acc.userlocale )
    addedQuest = modeldata.addQuest( staticQuest, config.INVALID_QUESTS, config.ALTERNATIVE_QUESTS, config.ONE_TIME_QUESTS, True, env.I.STATS, env.acc )
    modeldata.CompletedQuests.add(addedQuest)
    assert len(modeldata.CompletedQuests) == questsCount + 1

    requests =  [ ( Add_quest, AddQuestRequest( modeldata, { "PersistentId" : ["" + str(PersistentId) + ""] }, False ) ) ]
    changeList = env.execActions( requests )

    assert len(modeldata.CompletedQuests) == questsCount + 1

  def add_quest_with_prerequisites_test( self, env ):
    modeldata = env.acc.model
    PersistentId = crc32("tutorialFinal_qB")

    id = modeldata.next_uid_+1
    wasQuests = len(modeldata.ActiveQuests)

    staticQuest = env.acc.SD.getStaticQuestById( PersistentId )
    addedQuest = modeldata.addQuest( staticQuest, None, None, True, True, env.I.STATS, env.acc )

    assert len(modeldata.ActiveQuests) == wasQuests