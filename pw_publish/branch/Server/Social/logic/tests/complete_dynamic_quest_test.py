import sys

sys.path.append('../')
sys.path.append('../..')
from logic.complete_dynamic_quest import *
from logic.try_complete_dynamic_objective import *
from binascii import crc32
from base.helpers import *
from enums import *
from StatisticCore.ttypes import TalentChangeOperation

import EC


class complete_dynamic_quest_test:
    def complete_dynamic_quest_test(self, env):
        modeldata = env.acc.model

        questObjectiveId = modeldata.addNewDynamicObjective()
        questObjective = modeldata.getDynamicObjectiveByID(questObjectiveId)
        questObjective.IsCompleted = True

        dynamicQuestId = modeldata.addNewDynamicQuest()
        dynamicQuest = modeldata.getDynamicQuestByID(dynamicQuestId)
        dynamicQuest.Objectives.add(questObjective)
        dynamicQuest.QuestState = QuestState.Complete

        objectiveAwardId = modeldata.addNewDynamicQuestAward()
        objectiveAward = modeldata.getDynamicQuestAwardByID(objectiveAwardId)
        objectiveAward.QuestAwardType = DynamicQuestAwardType.Silver
        objectiveAward.Value = 1000
        dynamicQuest.Awards.add(objectiveAward)

        objectiveAwardId = modeldata.addNewDynamicQuestAward()
        objectiveAward = modeldata.getDynamicQuestAwardByID(objectiveAwardId)
        objectiveAward.QuestAwardType = DynamicQuestAwardType.Perl
        objectiveAward.Value = 3
        dynamicQuest.Awards.add(objectiveAward)

        modeldata.DynamicQuests.add(dynamicQuest)

        questsLen = len(modeldata.DynamicQuests)
        silver = modeldata.Resources.Silver
        perl = modeldata.Resources.Perl

        requests = [(Complete_dynamic_quest,
                     CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(dynamicQuest.id) + ""]}, False))]
        changeList = env.execActions(requests)

        assert modeldata.Resources.Silver == silver + 1000
        assert modeldata.Resources.Perl == perl + 3
        assert len(modeldata.DynamicQuests) == questsLen - 1

    def complete_dynamic_quest_instant_dragon_session_info_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Resource1 = 3000

        test_json_file = open("session_info_drg_quest.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()
        extra = {"numBossKillsAssist": 3, "numCatKillAssist": 0, "numDragonKillAssist": 3}
        # To execute this test with error (PF-99916):
        # extra = {"numBossKillsAssist": 3, "numCatKillAssist": 0, "numDragonKillAssist": 1}

        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        questsLen = len(modeldata.DynamicQuests)
        silver = modeldata.Resources.Silver
        perl = modeldata.Resources.Perl

        modeldata.Statistics.LastSessionResults.kills = 3
        modeldata.Statistics.LastSessionInfo.PickedHero = crc32("thundergod")
        modeldata.Statistics.LastSessionInfo.GameType = "PvE"
        modeldata.Statistics.LastSessionInfo.IsWinner = False

        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        modeldata.tryCompleteAfterSessionObjectives(extra)
        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])
        changeList = env.execActions(requests)

        # Checking condition correct size of boss killed (PF-99916):
        for objId in quest.Objectives:
            objective = modeldata.getDynamicObjectiveByID(objId)
            if objective is not None:
                assert objective.IsCompleted

        assert len(modeldata.DynamicQuests) == questsLen - 1

    def complete_dynamic_quest_instant_cat_session_info_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Resource1 = 3000

        test_json_file = open("session_info_cat_quest.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()
        extra = {"numBossKillsAssist": 3, "numCatKillAssist": 3, "numDragonKillAssist": 0}
        # To execute this test with error (PF-99916):
        # extra = {"numBossKillsAssist": 3, "numCatKillAssist": 1, "numDragonKillAssist": 0}

        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        questsLen = len(modeldata.DynamicQuests)
        silver = modeldata.Resources.Silver
        perl = modeldata.Resources.Perl

        modeldata.Statistics.LastSessionResults.kills = 3
        modeldata.Statistics.LastSessionInfo.PickedHero = crc32("thundergod")
        modeldata.Statistics.LastSessionInfo.GameType = "PvE"
        modeldata.Statistics.LastSessionInfo.IsWinner = False

        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        modeldata.tryCompleteAfterSessionObjectives(extra)
        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])
        changeList = env.execActions(requests)

        # Checking condition correct size of boss killed (PF-99916):
        for objId in quest.Objectives:
            objective = modeldata.getDynamicObjectiveByID(objId)
            if objective is not None:
                assert objective.IsCompleted

        assert len(modeldata.DynamicQuests) == questsLen - 1

    def complete_dynamic_quest_instant_boss_session_info_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Resource1 = 3000

        test_json_file = open("session_info_boss_quest.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()
        extra = {"numBossKillsAssist": 3, "numCatKillAssist": 2, "numDragonKillAssist": 1}
        quest = None
        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        questsLen = len(modeldata.DynamicQuests)
        silver = modeldata.Resources.Silver
        perl = modeldata.Resources.Perl

        modeldata.Statistics.LastSessionResults.kills = 3
        modeldata.Statistics.LastSessionInfo.PickedHero = crc32("thundergod")
        modeldata.Statistics.LastSessionInfo.GameType = "PvE"
        modeldata.Statistics.LastSessionInfo.IsWinner = False

        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        modeldata.tryCompleteAfterSessionObjectives(extra)
        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])
        changeList = env.execActions(requests)

        # Checking condition correct size of boss killed (PF-99916):
        for objId in quest.Objectives:
            objective = modeldata.getDynamicObjectiveByID(objId)
            if objective is not None:
                assert objective.IsCompleted

        assert len(modeldata.DynamicQuests) == questsLen - 1

    def complete_dynamic_quest_instant_and_session_strong_cond_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Resource1 = 3000

        test_json_file = open("session_info_quest.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()
        extra = {"partySize": 1, "enemyPartySize": 1, "isPlayerPartySizeStrongCond": 1, "isEnemyPartySizeStrongCond": 1}
        # To execute this test with error (PF-98150):
        # extra = {"partySize": 2, "enemyPartySize": 2, "isPlayerPartySizeStrongCond": 1, "isEnemyPartySizeStrongCond": 1}
        info("test_json_file = open=")
        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        questsLen = len(modeldata.DynamicQuests)
        silver = modeldata.Resources.Silver
        perl = modeldata.Resources.Perl

        modeldata.Statistics.LastSessionResults.kills = 3
        modeldata.Statistics.LastSessionInfo.PickedHero = crc32("thundergod")
        modeldata.Statistics.LastSessionInfo.GameType = "PvE"
        modeldata.Statistics.LastSessionInfo.IsWinner = False

        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        modeldata.tryCompleteAfterSessionObjectives(extra)
        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])
        changeList = env.execActions(requests)

        # Checking strong conditions for party size (PF-98150):
        for objId in quest.Objectives:
            objective = modeldata.getDynamicObjectiveByID(objId)
            if objective is not None:
                assert objective.IsCompleted

        assert len(modeldata.DynamicQuests) == questsLen - 1

    def complete_dynamic_quest_instant_and_session_info_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Resource1 = 3000

        test_json_file = open("session_info_quest.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()
        extra = {"partySize": 1, "enemyPartySize": 1}

        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        questsLen = len(modeldata.DynamicQuests)
        silver = modeldata.Resources.Silver
        perl = modeldata.Resources.Perl

        modeldata.Statistics.LastSessionResults.kills = 3
        modeldata.Statistics.LastSessionInfo.PickedHero = crc32("thundergod")
        modeldata.Statistics.LastSessionInfo.GameType = "PvE"
        modeldata.Statistics.LastSessionInfo.IsWinner = False

        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        modeldata.tryCompleteAfterSessionObjectives(extra)
        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])
        changeList = env.execActions(requests)

        assert modeldata.Resources.Silver == silver + staticQuest["Awards"][0]["Value"]
        assert modeldata.Resources.Perl == perl + staticQuest["Awards"][1]["Value"]
        assert modeldata.Resources.Resource1 == 0
        assert len(modeldata.DynamicQuests) == questsLen - 1

    def complete_dynamic_quest_instant_and_session_info_alternative_line_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Resource2 = 3000

        test_json_file = open("session_info_alternative_quest.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()
        extra = {"partySize": 1, "enemyPartySize": 1}

        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        questsLen = len(modeldata.DynamicQuests)
        silver = modeldata.Resources.Silver
        perl = modeldata.Resources.Perl

        modeldata.Statistics.LastSessionResults.kills = 3
        modeldata.Statistics.LastSessionInfo.PickedHero = crc32("firefox")
        modeldata.Statistics.LastSessionInfo.GameType = "PvE"
        modeldata.Statistics.LastSessionInfo.IsWinner = True

        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        for objectiveId in quest.AlternativeObjectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        modeldata.tryCompleteAfterSessionObjectives(extra)
        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])
        changeList = env.execActions(requests)

        assert modeldata.Resources.Silver == silver + staticQuest["AlternativeAwards"][0]["Value"]
        assert modeldata.Resources.Perl == perl + staticQuest["AlternativeAwards"][1]["Value"]
        assert modeldata.Resources.Resource2 == 0
        assert len(modeldata.DynamicQuests) == questsLen - 1

    def complete_dynamic_session_info_quest_test(self, env):
        return
        modeldata = env.acc.model

        test_json_file = open("session_info_quest.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()

        env.acc.SD.staticQuestInfo = staticQuest
        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        assert len(modeldata.DynamicQuests) == 1
        fame = modeldata.LordInfo.Fame

        modeldata.Statistics.LastSessionInfo.GameType = "PvE"
        modeldata.tryCompleteAfterSessionObjectives(env.acc.SD)
        modeldata.tryCompleteAfterSessionObjectives(env.acc.SD)
        modeldata.tryCompleteAfterSessionObjectives(env.acc.SD)

        requests = [(Complete_dynamic_quest, CompleteDynamicQuestRequest(modeldata, {
            "quest_id": ["" + str(modeldata.DynamicQuests.keys()[0]) + ""]}, False))]
        changeList = env.execActions(requests)

        assert modeldata.LordInfo.Fame == fame + toint(staticQuest["QuestData"][0]["Awards"][0]["Value"])

    def complete_dynamic_instant_quest_test_all_award_types(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Silver = 100500
        hero = modeldata.hireHero(crc32("rockman"), env.acc.sex, env.I.WS, env.acc, env.I)
        hero.changeExperience(500, env.acc.model, env.I.WS, env.acc, env.I)
        setattr(hero.TalentSets[0].Stats, "Agility", 2)
        hero.TalentSets[0].Stats.StatPoints -= 2
        assert hero.TalentSets[0].Stats.StatPoints == 0
        assert len(hero.HeroSkins.Skins) == 0
        assert len(modeldata.Flags) == 0

        test_json_file = open("instant_quest_all_awards.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()

        env.acc.SD.staticQuestInfo = staticQuest
        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        fame = modeldata.LordInfo.Fame
        inventoryLen = len(modeldata.UserInventory)
        res1 = modeldata.Resources.Resource1
        res2 = modeldata.Resources.Resource2
        res3 = modeldata.Resources.Resource3
        silver = modeldata.Resources.Silver
        perl = modeldata.Resources.Perl
        redperl = modeldata.Resources.RedPerl
        gold = modeldata.Resources.Gold
        premiumEnd = modeldata.LordInfo.PremiumAccountEnd
        constructions = len(modeldata.ConstructionsKeeper)
        questsLen = len(modeldata.DynamicQuests)
        heroes = len(modeldata.Heroes)
        nicknameChanges = env.acc.db.nickChanged
        factionChanges = env.acc.db.fractionChanged

        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])
        changeList = env.execActions(requests)

        lvl = env.acc.SD.getFameLevel(modeldata.LordInfo.Fame)
        for i in xrange(2, lvl + 1):
            resTable = env.acc.SD.getResourcesForLevelUp(i)
            silver += resTable.Silver
            perl += resTable.Perl
            redperl += resTable.RedPerl
            res1 += resTable.Resource1
            res2 += resTable.Resource2
            res3 += resTable.Resource3

        assert len(modeldata.DynamicQuests) == questsLen - 1

        assert premiumEnd < modeldata.LordInfo.PremiumAccountEnd  # 0
        assert modeldata.Resources.Resource1 == res1 + 3000  # 2
        assert modeldata.Resources.Resource2 == res2 + 3000  # 3
        assert modeldata.Resources.Resource3 == res3 + 3000  # 4
        assert modeldata.Resources.Silver == silver + 7000  # 5
        assert modeldata.Resources.Perl == perl + 20  # 6
        assert modeldata.Resources.RedPerl == redperl + 25  # 6

        # award + award + talentset (witcher) + alt_ult (witcher) + BonusTalentsForLevel(3) + alt_sup (witcher) + award x 3
        assert len(modeldata.UserInventory) == inventoryLen + 1 + 1 + (36 + 2 + 2 + 1) + 3
        assert len(modeldata.ConstructionsKeeper) == constructions + 1  # 9
        assert modeldata.LordInfo.Fame == fame + 1050  # 10 + 13
        assert modeldata.MarketingEventsInfo.LampEventInfo.dbId == "/UI/Content/MarketingEvents/GoldLamp_30"  # 11
        assert modeldata.MarketingEventsInfo.LampEventInfo.BonusLeft == 1000  # 11
        assert modeldata.MarketingEventsInfo.LampEventInfo.EndTime <= (int(time.time()) + 500)  # 11
        assert modeldata.MarketingEventsInfo.LampEventInfo.TransactionsLeft == 12  # 11
        assert len(modeldata.Flags) == 1  # 12
        assert len(modeldata.Heroes) == heroes + 1  # 13
        assert len(hero.HeroSkins.Skins) == 1  # 14
        assert env.acc.db.nickChanged == nicknameChanges - 1  # 15
        assert env.acc.db.fractionChanged == factionChanges - 1  # 16
        assert hero.Experience > 500  # 19
        assert hero.TalentSets[0].Stats.StatPoints == 2  # 20

    def complete_dynamic_quest_instant_and_session_info_alternative_line_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Resource2 = 3000

        test_json_file = open("tournament_quest_1.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()
        extra = {"partySize": 1, "enemyPartySize": 1}

        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        modeldata.Statistics.LastSessionResults.kills = 3
        modeldata.Statistics.LastSessionInfo.PickedHero = crc32("firefox")
        modeldata.Statistics.LastSessionInfo.GameType = "/Maps/Multiplayer/MOBA/Mod7/_.ADMPDSCR"
        modeldata.Statistics.LastSessionInfo.IsWinner = False

        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        for objectiveId in quest.AlternativeObjectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        modeldata.tryCompleteAfterSessionObjectives(extra)
        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])
        changeList = env.execActions(requests)
        assert changeList[2].get("ok", 0) == 1

        # modeldata.CompletedDynamicQuests.append(quest.PersistentId)
        # modeldata.removeDynamicQuest(quest, env.acc, env.I)

        test_json_file = open("tournament_quest_2.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()
        extra = {"partySize": 1, "enemyPartySize": 1}

        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, 0)

        assert not bool(modeldata.DynamicQuests)

    def complete_dynamic_quest_instant_and_session_info_alternative_line_with_skipping_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Resource2 = 3000

        test_json_file = open("tournament_quest_1.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()
        extra = {"partySize": 1, "enemyPartySize": 1}

        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        modeldata.Statistics.LastSessionResults.kills = 3
        modeldata.Statistics.LastSessionInfo.PickedHero = crc32("firefox")
        modeldata.Statistics.LastSessionInfo.GameType = "/Maps/Multiplayer/MOBA/Mod7/_.ADMPDSCR"
        modeldata.Statistics.LastSessionInfo.IsWinner = False

        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        for objectiveId in quest.AlternativeObjectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        # modeldata.tryCompleteAfterSessionObjectives(extra)
        quest.QuestEndTime = 1
        silver = modeldata.Resources.Silver
        modeldata.validateDynamicQuests(env.acc, env.I)

        assert silver + 125 == modeldata.Resources.Silver
        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])
        changeList = env.execActions(requests)
        assert changeList[2].get("ok", 0) == 0

        # modeldata.CompletedDynamicQuests.append(quest.PersistentId)
        # modeldata.removeDynamicQuest(quest, env.acc, env.I)

        test_json_file = open("tournament_quest_2.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()
        extra = {"partySize": 1, "enemyPartySize": 1}

        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, 0)

        assert not bool(modeldata.DynamicQuests)

    def complete_dynamic_quest_with_skipping_and_repeat_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Resource2 = 3000

        test_json_file = open("tournament_quest_1.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()
        extra = {"partySize": 1, "enemyPartySize": 1}

        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)
            quest.RepeatOnMiss = True

        modeldata.Statistics.LastSessionResults.kills = 3
        modeldata.Statistics.LastSessionInfo.PickedHero = crc32("firefox")
        modeldata.Statistics.LastSessionInfo.GameType = "/Maps/Multiplayer/MOBA/Mod7/_.ADMPDSCR"
        modeldata.Statistics.LastSessionInfo.IsWinner = False

        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        for objectiveId in quest.AlternativeObjectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        # modeldata.tryCompleteAfterSessionObjectives(extra)
        quest.QuestEndTime = 1
        silver = modeldata.Resources.Silver
        modeldata.validateDynamicQuests(env.acc, env.I)

        assert silver + 125 == modeldata.Resources.Silver
        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])
        changeList = env.execActions(requests)
        assert changeList[2].get("ok", 0) == 0
        assert len(modeldata.DynamicQuests) == 0

        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        assert len(modeldata.DynamicQuests) == 1

    def complete_dynamic_quest_with_talents_awards_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Resource2 = 3000

        test_json_file = open("talent_awards_quest.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()
        extra = {"partySize": 1, "enemyPartySize": 1}

        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        modeldata.Statistics.LastSessionResults.kills = 3
        modeldata.Statistics.LastSessionInfo.PickedHero = crc32("firefox")
        modeldata.Statistics.LastSessionInfo.GameType = "/Maps/Multiplayer/MOBA/Mod7/_.ADMPDSCR"
        modeldata.Statistics.LastSessionInfo.IsWinner = True

        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        for objectiveId in quest.AlternativeObjectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        modeldata.tryCompleteAfterSessionObjectives(extra)
        silver = modeldata.Resources.Silver
        modeldata.validateDynamicQuests(env.acc, env.I)

        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])
        changeList = env.execActions(requests)
        assert changeList[0].get("ok", 0) == 1

    def complete_dynamic_quest_with_lootbox_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Resource2 = 3000

        test_json_file = open("lootbox_in_award_quest.json", "r")
        staticQuest = ujson.load(test_json_file)
        test_json_file.close()

        if modeldata.canAcceptDynamicQuest(staticQuest, env.acc.SD, env.acc.db.fraction, False, env.acc.auid):
            quest = modeldata.addDynamicQuest(env.acc, staticQuest, 1, env.I, 0)

        assert len(modeldata.DynamicQuests) == 1

        requests = []
        for objectiveId in quest.Objectives:
            requests.append([Try_complete_dynamic_objective,
                             TryCompleteDynamicObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""],
                                                                            "objective_id": [
                                                                                "" + str(objectiveId) + ""]}, False)])
        modeldata.validateDynamicQuests(env.acc, env.I)

        requests.append([Complete_dynamic_quest,
                         CompleteDynamicQuestRequest(modeldata, {"quest_id": ["" + str(quest.getID()) + ""]}, False)])

        changeList = env.execActions(requests)

        # print pprint.PrettyPrinter(indent=1).pformat(changeList)
        assert changeList[0].get("ok", 0) == 1

        mdLootboxes = [l for _, l in modeldata.Lootboxes.iteritems()]
        assert len(mdLootboxes) == 4
        crcLootbox1 = crc32('LB_Orange567')
        assert sum(1 for lb in mdLootboxes if lb.PersistentId == crcLootbox1) == 2
        crcLootbox2 = crc32('LB_Orange456')
        assert sum(1 for lb in mdLootboxes if lb.PersistentId == crcLootbox2) == 2

    def adding_tal_with_refscale(self, env):
        refine = "3"

        tals = [pprint.PrettyPrinter(indent=1, depth=3).pformat(l.__dict__) for _, l in
                env.acc.model.ItemsKeeper.iteritems() if l.PersistentId == crc32('G600')]
        # print 'tals before: [{}]'.format(tals)
        env.acc.model.addTalentsForFree('QuestName',
                               ['G600' + ':' + str(toint(refine, default=1))],
                               env.acc, env.I.STATS, TalentChangeOperation.GetFromQuest, pointsInArgs=True)

        tals = [pprint.PrettyPrinter(indent=1, depth=3).pformat(l.__dict__) for _, l in env.acc.model.ItemsKeeper.iteritems() if l.PersistentId == crc32('G600')]
        # print 'tals after: [{}]'.format(tals)
        env.printAssert(1, len(tals))

        tal = [l for _, l in env.acc.model.ItemsKeeper.iteritems() if l.PersistentId == crc32('G600')][0]
        staticTalent = env.acc.SD.getStaticTalentByTalentId(tal.PersistentId)
        talentPointsToLevel = env.acc.SD.getTalentPointsToLevel(staticTalent)
        env.printAssert(tal.Points, toint(refine))




