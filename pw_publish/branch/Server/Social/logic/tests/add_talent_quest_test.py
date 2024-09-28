# coding=utf-8
import sys
sys.path.append('../')
sys.path.append('../..')
from logic.add_talent_quest import *
from binascii import crc32
from base.helpers import *
from enums import *
from xdb.xml2obj import xml2obj
import EC
from logic.complete_dynamic_quest import *
from logic.try_complete_dynamic_objective import *

class add_talent_quest_test:

    def __createDummySD(self, sd):
        pass

    def add_talent_quest_test_from_magnificent_talent( self, env ):
        self.__createDummySD(env.acc.SD)
        modeldata = env.acc.model

        modeldata.addResourcesForFree({"Shard": 500})
        #debug("Resources Before: " + str(modeldata.Resources.generateJsonDict()))

        requests = [(Add_talent_quest, AddTalentQuestRequest(modeldata, {"TalentPersistantId": ["" + str(crc32("G040")) + ""]}, False))]
        changeList = env.execActions(requests)

        #debug("Resources After: " + str(modeldata.Resources.generateJsonDict()) + "\n")
        assert len(modeldata.DynamicQuests.keys()) == 1
        dynamicQuest = modeldata.DynamicQuests.values()[0]
        assert dynamicQuest.QuestStartTime <= int(time.time())
        assert dynamicQuest.QuestEndTime > int(time.time())
        assert not dynamicQuest.isComplete()

    # pretest deleting quest in md if not exist in sd
    def delete_talent_quest_if_nonactually( self, env ):
        # todo; где ассерты?
        self.__createDummySD(env.acc.SD)
        modeldata = env.acc.model
        quest = lambda: None
        quest.DynamicQuestToTalentsMetaInf = lambda: None
        quest.DynamicQuestToTalentsMetaInf.questsGroup = 5
        quest.DynamicQuestToTalentsMetaInf.questIdx = 0

        modeldata.validateActuallyForDQToTal(quest, env.acc, None)

    def add_talent_quest_test_from_exclusive_talent(self, env):
        self.__createDummySD(env.acc.SD)
        modeldata = env.acc.model

        modeldata.addResourcesForFree({"Shard": 5000})
        #debug("Resources Before: " + str(modeldata.Resources.generateJsonDict()))

        limit = env.acc.getConfig().TalentsCollectionSettings.TALENTS_QUEST_LIMIT
        limit = 1 if limit < 0 else limit

        for i in range(0, limit + 1):
            requests = [(Add_talent_quest,
                         AddTalentQuestRequest(modeldata, {"rid": [i*100], "TalentPersistantId": ["" + str(crc32("G33" + str(5+i))) + ""]},
                                               False))]
            changeList = env.execActions(requests)

        #debug("Resources After: " + str(modeldata.Resources.generateJsonDict()) + "\n")
        assert len(modeldata.DynamicQuests.keys()) == limit
        dynamicQuest = modeldata.DynamicQuests.values()[0]
        assert dynamicQuest.QuestStartTime <= int(time.time())
        assert dynamicQuest.QuestEndTime > int(time.time())
        assert not dynamicQuest.isComplete()

    def add_talent_quest_test_from_outstanding_talent(self, env):
        self.__createDummySD(env.acc.SD)
        modeldata = env.acc.model

        modeldata.addResourcesForFree({"Shard": 522000})
        modeldata.Resources.Gold = 1

        #debug("Resources Before: " + str(modeldata.Resources.generateJsonDict()))

        requests = [(Add_talent_quest,
                     AddTalentQuestRequest(modeldata, {"TalentPersistantId": ["" + str(crc32("G451")) + ""]},
                                           False))]
        changeList = env.execActions(requests)

        #debug("Resources After: " + str(modeldata.Resources.generateJsonDict()) + "\n")

        #print env.pretty(modeldata.DynamicObjectivesKeeper.items()[0][1].generateJsonDict())
        time.sleep(0.01)

        assert len(modeldata.DynamicQuests.keys()) == 1
        dynamicQuest = modeldata.DynamicQuests.values()[0]
        assert dynamicQuest.QuestStartTime <= int(time.time())
        assert dynamicQuest.QuestEndTime > int(time.time())
        assert not dynamicQuest.isComplete()

    def add_talent_quest_test_with_overrided_pricemap(self, env):
        self.__createDummySD(env.acc.SD)
        modeldata = env.acc.model

        modeldata.addResourcesForFree({"Shard": 2000})
        #debug("Resources Before: " + str(modeldata.Resources.generateJsonDict()))

        requests = [(Add_talent_quest,
                     AddTalentQuestRequest(modeldata, {"TalentPersistantId": ["" + str(crc32("G001")) + ""]},
                                           False))]
        changeList = env.execActions(requests)

        #debug("Resources After: " + str(modeldata.Resources.generateJsonDict()) + "\n")
        assert len(modeldata.DynamicQuests.keys()) == 1
        dynamicQuest = modeldata.DynamicQuests.values()[0]
        assert dynamicQuest.QuestStartTime <= int(time.time())
        assert dynamicQuest.QuestEndTime > int(time.time())
        assert not dynamicQuest.isComplete()

    def add_talent_quest_test_with_overrided_difficultiesmap(self, env):
        self.__createDummySD(env.acc.SD)
        modeldata = env.acc.model

        modeldata.addResourcesForFree({"Shard": 2000, "Resource1": 1})
        #debug("Resources Before: " + str(modeldata.Resources.generateJsonDict()))

        requests = [(Add_talent_quest,
                     AddTalentQuestRequest(modeldata, {"TalentPersistantId": ["" + str(crc32("G059")) + ""]},
                                           False))]
        changeList = env.execActions(requests)

        #debug("Resources After: " + str(modeldata.Resources.generateJsonDict()) + "\n")
        assert len(modeldata.DynamicQuests.keys()) == 1
        dynamicQuest = modeldata.DynamicQuests.values()[0]
        assert dynamicQuest.QuestStartTime <= int(time.time())
        assert dynamicQuest.QuestEndTime > int(time.time())
        assert not dynamicQuest.isComplete()


    def add_talent_quest_test_with_no_resources( self, env ):
        self.__createDummySD(env.acc.SD)
        modeldata = env.acc.model

        requests = [(Add_talent_quest, AddTalentQuestRequest(modeldata, {"TalentPersistantId": ["" + str(crc32("G040")) + ""]}, False))]
        changeList = env.execActions(requests)

        assert changeList[0]['ec'] == EC.NOT_ENOUGH_RESOURCES
        assert len(modeldata.DynamicQuests.keys()) == 0

    def add_talent_quest_test_with_bad_config( self, env ):
        self.__createDummySD(env.acc.SD)
        modeldata = env.acc.model

        env.I.Config.getMainConfig().TalentsCollectionSettings.TALENTS_QUEST_DISABLED = True

        requests = [(Add_talent_quest, AddTalentQuestRequest(modeldata, {"TalentPersistantId": ["" + str(crc32("G040")) + ""]}, False))]
        changeList = env.execActions(requests)

        # for next tests return normal state data
        env.I.Config.getMainConfig().TalentsCollectionSettings.TALENTS_QUEST_DISABLED = False

        assert changeList[0]['ec'] == EC.BAD_ACTION_NAME
        assert len(modeldata.DynamicQuests.keys()) == 0

    def add_talent_quest_test_with_badTalent(self, env):
        self.__createDummySD(env.acc.SD)
        modeldata = env.acc.model

        requests = [(Add_talent_quest,
                     AddTalentQuestRequest(modeldata, {"TalentPersistantId": ["" + str(crc32("SUPERMEGATALENTFROMDOTA2")) + ""]},
                                           False))]
        changeList = env.execActions(requests)

        assert changeList[0]['ec'] == EC.BAD_PARAM
        assert len(modeldata.DynamicQuests.keys()) == 0

    def add_talent_quest_test_with_forbidden_tal(self, env):
        self.__createDummySD(env.acc.SD)
        modeldata = env.acc.model

        forbidden_talents = env.acc.SD.data['DynamicQuestForTalents']['ForbadeTalents'].keys()
        idx = random.randint(0, len(forbidden_talents)-1)
        forbidden_tal_id = crc32(forbidden_talents[idx])
        requests = [(Add_talent_quest, AddTalentQuestRequest(modeldata, {"TalentPersistantId": ["" + str(forbidden_tal_id) + ""]}, False))]
        changeList = env.execActions(requests)

        assert changeList[0]['ec'] == EC.BAD_PARAM
        assert len(modeldata.DynamicQuests.keys()) == 0


    def complete_dynamic_quest_instant_and_session_info_test(self, env):
        # print env.pretty(env.acc.SD.data['DynamicQuestForTalents'])
        modeldata = env.acc.model
        modeldata.Resources.Resource1 = 3000

        modeldata.addResourcesForFree({"Shard": 522000})

        requests = [(Add_talent_quest,
                     AddTalentQuestRequest(modeldata, {"TalentPersistantId": ["" + str(crc32("G451")) + ""]},
                                           False))]
        changeList = env.execActions(requests)
        extra = {"partySize": 1, "enemyPartySize": 1}

        quest = modeldata.DynamicQuests.values()[0]

        modeldata.Statistics.LastSessionResults.kills = 3
        modeldata.Statistics.LastSessionInfo.PickedHero = crc32("thundergod")
        modeldata.Statistics.LastSessionInfo.GameType = "/Maps/Multiplayer/MOBA/_.ADMPDSCR"
        modeldata.Statistics.LastSessionInfo.IsWinner = True


        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])

        for i in range(15):
            modeldata.tryCompleteAfterSessionObjectives(extra)

        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])
        changeList = env.execActions(requests)

        modeldata.validateDynamicQuestsActuality(env.acc, env.I)
        assert len(modeldata.DynamicQuests.keys()) == 0


    def gmtool_GetQuestsForTalentsByAuid(self, env):
        # todo: где ассерты?

        self.__createDummySD(env.acc.SD)
        modeldata = env.acc.model

        modeldata.addResourcesForFree({"Shard": 522000})
        modeldata.Resources.Gold = 1

        #debug("Resources Before: " + str(modeldata.Resources.generateJsonDict()))

        requests = [(Add_talent_quest,
                     AddTalentQuestRequest(modeldata, {"TalentPersistantId": ["" + str(crc32("G453")) + ""]},
                                           False))]
        changeList = env.execActions(requests)

        #debug("Resources After: " + str(modeldata.Resources.generateJsonDict()) + "\n")

        time.sleep(0.01)

        # COPIED FROM : acc_management_ws_handler.py : GetAccountQuestsForTalentsByAuid
        for id, quest in modeldata.DynamicQuests.items():

            # meta vars
            idAwardWithTalent = -1
            objectiveId = -1

            # fill raw data
            rawQuestData = "===============QuestInfo: " + "\n"
            rawQuestData += env.pretty(quest.generateJsonDict()) + "\n"
            for id, _ in quest.Objectives.items():
                objectiveId = objectiveId if objectiveId != -1 else id
                rawQuestData += env.pretty(modeldata.getDynamicObjectiveByID(id).generateJsonDict()) + "\n"
            rawQuestData += "===============DynamicAwards: " + "\n"
            for id, _ in quest.Awards.items():
                idAwardWithTalent = idAwardWithTalent if idAwardWithTalent != -1 else id
                rawQuestData += env.pretty(modeldata.getDynamicQuestAwardByID(id).generateJsonDict()) + "\n"

            # get talent from award
            talentFromAwardPersistentId = -1
            talentFromAwardName = "None"
            staticTalent = None
            if idAwardWithTalent != -1:
                award = modeldata.getDynamicQuestAwardByID(idAwardWithTalent)
                if award.QuestAwardType == DynamicQuestAwardType.Talent:
                    talentPersistentId = award.PersistentId
                    talentFromAwardPersistentId = talentPersistentId
                    staticTalent = env.acc.SD.getStaticTalentByTalentId(talentPersistentId)
                    talentFromAwardName = staticTalent['persistentId']

            # get shards spent
            shardsSpent = 0
            if staticTalent != None:
                overridenPriceMap = env.acc.SD.data['DynamicQuestForTalents']['OverridenPricesMap']
                overridenPrice = overridenPriceMap[staticTalent['persistentId']] if staticTalent[
                                                                                        'persistentId'] in overridenPriceMap else None
                if overridenPrice:
                    shardsSpent = env.acc.SD.copyPrice(overridenPrice).Shard
                else:
                    priceMap = env.acc.SD.data['DynamicQuestForTalents']['PricesMap']
                    shardsSpent = env.acc.SD.copyPrice(priceMap[staticTalent['rarity']]).Shard

            # get current quest progress
            currentObjectiveData = ""
            objective = modeldata.getDynamicObjectiveByID(objectiveId)
            currentObjectiveValue = objective.CurrentValue

            #print 'talentFromAwardPersistentId = ' + str(talentFromAwardPersistentId)
            #print 'talentFromAwardName = ' + str(talentFromAwardName)
            #print 'shardsSpent = ' + str(shardsSpent)
            #print 'currentObjectiveData = ' + str(currentObjectiveData)
            #print 'currentObjectiveValue = ' + str(currentObjectiveValue)
            #print 'rawQuestData = ' + str(rawQuestData)

        pass

