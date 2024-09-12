#!/usr/bin/env python
# -*- coding: utf-8 -*-
# (C) Vadim Petrov 2011, Nival

import sys

sys.path.append('../')
sys.path.append('../..')
from logic.try_complete_objective import *
from logic.merge_talents import *
from logic.hire_hero import *
from logic.force_complete_objective import *
from logic.building_place import *
from binascii import crc32
import time
from enums import *


class try_complete_objective_test:
    def try_complete_objective_test(self, env):
        modeldata = env.acc.model
        modeldata.LordInfo.LevelOfExpansion = 0

        staticQuest = env.acc.SD.getStaticQuestById(crc32('c11_qA'))
        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objective = quest.objectives[quest.objectives.keys()[0]]
            quest.state = QuestState.InProgress

        assert len(modeldata.ActiveQuests) == 2
        assert len(modeldata.CompletedQuests) == 1
        assert len(modeldata.ObjectivesKeeper) >= len(staticQuest['objectives']['Item'])
        assert objective.value == 0

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        assert quest.state == QuestState.InProgress
        assert objective.value == 0

        modeldata.LordInfo.LevelOfExpansion = 1

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        assert quest.state == QuestState.Complete
        staticObj = env.acc.SD.getStaticObjective(quest, objective)
        assert objective.value == int(staticObj['value'])

    def force_complete_objective_test(self, env):
        modeldata = env.acc.model
        modeldata.LordInfo.LevelOfExpansion = 0

        staticQuest = env.acc.SD.getStaticQuestById(crc32('c11_qA'))
        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objective = quest.objectives[quest.objectives.keys()[0]]
            quest.state = QuestState.InProgress

        assert objective.value == 0
        assert modeldata.LordInfo.LevelOfExpansion == 0

        requests = [(Force_complete_objective, ForceCompleteObjectiveRequest(modeldata,
                                                                             {"quest_id": ["" + str(quest.id) + ""],
                                                                              "objective_id": [
                                                                                  "" + str(objective.id) + ""],
                                                                              "value": [10]}, False))]
        changeList = env.execActions(requests)

        staticObj = env.acc.SD.getStaticObjective(quest, objective)
        assert objective.value == int(staticObj['value'])
        assert modeldata.LordInfo.LevelOfExpansion == 0
        assert quest.state == QuestState.Complete

    def try_complete_completed_objective_test(self, env):
        modeldata = env.acc.model

        staticQuest = env.acc.SD.getStaticQuestById(crc32('m12_qA'))
        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objective0 = quest.objectives[quest.objectives.keys()[0]]
            objective1 = quest.objectives[quest.objectives.keys()[1]]
            objective2 = quest.objectives[quest.objectives.keys()[2]]
            quest.state = QuestState.InProgress

            objective2.value = staticQuest['objectives']['Item'][2]['value']

        assert objective2.value != 0

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective2.id) + ""],
                                                                          "clientValue": [10]}, False))]
        changeList = env.execActions(requests)

        assert objective2.value == staticQuest['objectives']['Item'][2]['value']
        assert quest.state == QuestState.InProgress

    def try_complete_user_value_objective_test(self, env):
        # Перестал работать после изменения туториала
        return
        modeldata = env.acc.model
        env.acc.db.fraction = "B"

        staticQuest = env.acc.SD.getStaticQuestById(crc32('s22_qB'))
        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objective0 = quest.objectives[quest.objectives.keys()[0]]
            objective1 = quest.objectives[quest.objectives.keys()[1]]
            quest.state = QuestState.InProgress

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective0.id) + ""],
                                                                          "clientValue": [10]}, False))]
        changeList = env.execActions(requests)

        assert objective0.value == 0
        assert objective1.value == 0
        assert quest.state == QuestState.InProgress

        for heroId in modeldata.Heroes:
            hero = modeldata.getHeroByID(heroId)
            hero.Stats.Intellect = 5
            break

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective0.id) + ""]}, False))]
        changeList = env.execActions(requests)

        staticObj = env.acc.SD.getStaticObjective(quest, objective0)
        assert objective0.value == int(staticObj['value'])
        assert objective1.value == 0
        assert quest.state == QuestState.InProgress

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective1.id) + ""],
                                                                          "clientValue": [10]}, False))]
        changeList = env.execActions(requests)

        staticObj0 = env.acc.SD.getStaticObjective(quest, objective0)
        assert objective0.value == int(staticObj['value'])
        staticObj1 = env.acc.SD.getStaticObjective(quest, objective1)
        assert objective1.value == int(staticObj['value'])
        assert quest.state == QuestState.Complete

        for heroId in modeldata.HeroesKeeper:
            hero = modeldata.getHeroByID(heroId)
            if hero.class_name == "thundergod":
                foundhero = True
                break

        assert foundhero == True
        assert hero.Experience == 300

    def try_complete_finish_session_condition_objective_test(self, env):
        # Туториал был сильно переделан, сейчас этот квест уже не соовтетствует условиям.
        return
        modeldata = env.acc.model

        staticQuest = env.acc.SD.getStaticQuestById(crc32('s11_qA'))
        if staticQuest:
            for quest_id in modeldata.ActiveQuests:
                quest = modeldata.getQuestByID(quest_id)
                if quest.persistentId == crc32('s11_qA'):
                    objective = quest.objectives[quest.objectives.keys()[0]]
                    objective_hidden = quest.objectives[quest.objectives.keys()[1]]
                    quest.state = QuestState.InProgress

        assert objective.value == 0

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        assert objective.value == 0
        assert quest.state == QuestState.InProgress

        modeldata.addStatisticEvent(StatisticEventType.SESSION_FINISH, "/Maps/Tutorial/_1.ADMPDSCR", 1)

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)
        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective_hidden.id) + ""]},
                                                                         False))]
        changeList = env.execActions(requests)

        staticObj = env.acc.SD.getStaticObjective(quest, objective)
        assert objective.value == int(staticObj['value'])
        assert quest.state == QuestState.Complete

    def try_complete_modeldata_condition_objective_test(self, env):
        modeldata = env.acc.model

        staticQuest = env.acc.SD.getStaticQuestById(crc32('c41_qA'))
        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objective = quest.objectives[quest.objectives.keys()[0]]

            quest.state = QuestState.InProgress

        assert objective.value == 0

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        assert objective.value == 0
        assert quest.state == QuestState.InProgress

        modeldata.LordInfo.LevelOfExpansion = 1
        Resources = env.generate_resources(2000)
        modeldata.Resources = env.generate_resources(2000)

        plan_id = crc32("Library");
        x = 100500
        y = 100500
        pitch = 0

        buildCount = len(modeldata.Buildings)

        requests = [(Building_place, BuildingPlaceRequest(modeldata, {"PersistentId": ["" + str(plan_id) + ""],
                                                                      "x": ["" + str(x) + ""], "y": ["" + str(y) + ""],
                                                                      "pitch": ["" + str(pitch) + ""]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.Buildings) == buildCount + 1

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        staticObj = env.acc.SD.getStaticObjective(quest, objective)
        assert objective.value == int(staticObj['value'])
        assert quest.state == QuestState.Complete

    def try_complete_statistic_data_condition_objective_test(self, env):
        modeldata = env.acc.model

        staticQuest = env.acc.SD.getStaticQuestById(crc32('m21_qA'))
        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objective = quest.objectives[quest.objectives.keys()[1]]

            quest.state = QuestState.InProgress

        assert objective.value == 0

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        assert objective.value == 0
        assert quest.state == QuestState.InProgress

        modeldata.addStatisticEvent(StatisticEventType.TALENT_FINISH, "100500", 10)
        building = env.add_construction(modeldata, "Talent_Production")

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        staticObj = env.acc.SD.getStaticObjective(quest, objective)
        assert objective.value == int(staticObj['value'])

    def try_complete_s51_objective_test(self, env):
        return
        modeldata = env.acc.model

        staticQuest = env.acc.SD.getStaticQuestById(crc32('c41_qA'))
        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objective = quest.objectives[quest.objectives.keys()[0]]

            quest.state = QuestState.InProgress

            assert quest.state == QuestState.InProgress

        assert objective.value == 0
        fame = 80000
        silver = 5000000
        modeldata.LordInfo.Fame = fame
        modeldata.Resources.Silver = silver

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32("prince")]}, False))]
        changeList = env.execActions(requests)

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        assert objective.value == 0
        assert quest.state == QuestState.InProgress

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32("frogenglut")]}, False))]
        changeList = env.execActions(requests)

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        staticObj = env.acc.SD.getStaticObjective(quest, objective)
        assert objective.value == int(staticObj['value'])
        assert quest.state == QuestState.Complete

    def try_complete_m11_objective_test(self, env):
        modeldata = env.acc.model
        staticQuest = env.acc.SD.getStaticQuestById(crc32('m11_qB'))
        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objective = quest.objectives[quest.objectives.keys()[0]]
            quest.state = QuestState.InProgress
            assert quest.state == QuestState.InProgress
        assert objective.value == 0
        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)
        assert objective.value == 0
        assert quest.state == QuestState.InProgress

        construction = env.add_construction(modeldata, "Production_Resource2")
        construction.Level = 8


        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)
        staticObj = env.acc.SD.getStaticObjective(quest, objective)
        assert objective.value == int(staticObj['value'])

    def try_complete_h21_objective_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Resource3 = 0
        staticQuest = env.acc.SD.getStaticQuestById(crc32('h21_qB'))
        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objective = quest.objectives[quest.objectives.keys()[0]]
            quest.state = QuestState.InProgress
            assert quest.state == QuestState.InProgress
        assert objective.value == 0
        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)
        assert objective.value == 0
        assert modeldata.Resources.Resource3 == 0
        assert quest.state == QuestState.InProgress

        modeldata.Resources.Resource3 = 5000

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)
        staticObj = env.acc.SD.getStaticObjective(quest, objective)
        assert objective.value == int(staticObj['value'])
        assert modeldata.Resources.Resource3 == 0

    def try_complete_m30_objective_test(self, env):
        modeldata = env.acc.model
        staticQuest = env.acc.SD.getStaticQuestById(crc32('m30_qA'))
        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objectives = quest.objectives.keys()[:]
            objectives.sort()
            objective = quest.objectives[objectives[0]]
            quest.state = QuestState.InProgress
            assert quest.state == QuestState.InProgress
        assert objective.value == 0
        num = 4

        staticObj = env.acc.SD.getStaticObjective(quest, objective)
        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)
        assert objective.value == 0
        assert quest.state == QuestState.InProgress
        eventCount = len(modeldata.StatisticEventsKeeper)

        # -----
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G137")
        source_talents = []
        for i in xrange(0, num):
            source_talents.append(env.add_talent(modeldata, "G137"))

        modeldata.UserInventory.add(target_talent)
        for i in xrange(0, num):
            modeldata.UserInventory.add(source_talents[i])

        init_points = target_talent.Points

        target_talent_level = env.acc.SD.getTalentLevel(target_talent)
        static_talent = env.acc.SD.getStaticTalent(target_talent)

        tal = str(source_talents[0].id)
        for i in xrange(1, num):
            tal += "," + str(source_talents[i].id)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": [tal], "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory

        for i in xrange(0, num):
            assert not source_talents[i].id in modeldata.UserInventory

        assert env.acc.SD.getTalentLevel(target_talent) == target_talent_level + num

        staticTalent = env.acc.SD.getStaticTalent(target_talent)
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])
        levelToPoints = env.acc.SD.data['TalentLevelToPointsAndRarity']['Item'][intRarity]['levelToPoints']
        points = levelToPoints['Item'][target_talent_level + num - 1]

        pearl_price = env.acc.SD.getTalentMergePrice(init_points, points, static_talent)

        assert points == target_talent.Points
        assert modeldata.Resources.Perl < perl
        assert modeldata.Resources.Perl == perl - pearl_price
        # -----

        assert eventCount + 1 == len(modeldata.StatisticEventsKeeper)

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)
        staticObj = env.acc.SD.getStaticObjective(quest, objective)
        assert objective.value == int(staticObj['value'])

    def complete_quest_with_remove_new_state_action(self, env):
        modeldata = env.acc.model

        staticQuest = env.acc.SD.getStaticQuestById(crc32('testQ'))
        talent_id = modeldata.addNewTalent()
        talent = modeldata.getTalentByID(talent_id)
        talent.IsNew = True
        talent.ActionBarIdx = -1
        talent.defaultForHero = None
        talent.PersistentId = 123
        talent.Points = 0
        talent.Soulbound = None
        talent.GuildBankInfo = None
        modeldata.UserInventory.add(talent_id)

        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objective = quest.objectives[quest.objectives.keys()[0]]
            quest.state = QuestState.InProgress

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        for talId in modeldata.UserInventory:
            talent = modeldata.getTalentByID(talId)
            assert talent.IsNew == False

    def complete_quest_with_soulbound_reward_action(self, env):
        return
        modeldata = env.acc.model

        staticQuest = env.acc.SD.getStaticQuestById(crc32('testQ'))
        thundergod = None
        for hero_id in modeldata.Heroes:
            hero = modeldata.getHeroByID(hero_id)
            if hero.PersistentId == crc32('thundergod'):
                thundergod = hero

        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objective = quest.objectives[quest.objectives.keys()[0]]
            quest.state = QuestState.InProgress

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        isSoulbounded = False
        for talId in modeldata.UserInventory:
            talent = modeldata.getTalentByID(talId)
            if talent.PersistentId == crc32("G135") and talent.Soulbound == thundergod:
                isSoulbounded = True
        assert isSoulbounded == True

    def complete_quest_with_remove_custom_talent_from_slot_action(self, env):
        return
        #TODO: надо разобраться почему не проходит тест
        modeldata = env.acc.model

        staticQuest = env.acc.SD.getStaticQuestById(crc32('testQ'))
        thundergod = None
        for hero_id in modeldata.Heroes:
            hero = modeldata.getHeroByID(hero_id)
            if hero.PersistentId == crc32('thundergod'):
                thundergod = hero

        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objective = quest.objectives[quest.objectives.keys()[0]]
            quest.state = QuestState.InProgress

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        isSoulbounded = False
        for talId in modeldata.UserInventory:
            talent = modeldata.getTalentByID(talId)
            if talent.PersistentId == crc32("Gender_M_1") and talent.Soulbound == thundergod:
                isSoulbounded = True
        assert isSoulbounded == True

    def complete_quest_with_remove_talent_from_custom_slot_action(self, env):
        modeldata = env.acc.model

        staticQuest = env.acc.SD.getStaticQuestById(crc32('testQ'))
        thundergod = None
        for hero_id in modeldata.Heroes:
            hero = modeldata.getHeroByID(hero_id)
            if hero.PersistentId == crc32('firefox'):
                thundergod = hero
        oldTal = thundergod.TalentSets[0].Talents.get(31)
        assert oldTal is not None
        quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
        objective = quest.objectives[quest.objectives.keys()[0]]
        quest.state = QuestState.InProgress

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata,
                                                                         {"quest_id": ["" + str(quest.id) + ""],
                                                                          "objective_id": [
                                                                              "" + str(objective.id) + ""]}, False))]
        changeList = env.execActions(requests)

        assert thundergod.TalentSets[0].Talents.get(31) is None
        assert oldTal in modeldata.UserInventory


    def try_complete_d11_objective_test(self, env):
        modeldata = env.acc.model
        staticQuest = env.acc.SD.getStaticQuestById(crc32('d11_qA'))
        if staticQuest:
            quest = modeldata.addQuest(staticQuest, None, None, False, False, env.I.STATS, env.acc)
            objectives = quest.objectives.keys()[:]
            objectives.sort()
            objective = quest.objectives[objectives[0]]
            quest.state = QuestState.InProgress
            assert quest.state == QuestState.InProgress
        assert objective.value == 0
        num = 4

        staticObj = env.acc.SD.getStaticObjective(quest, objective)
        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.id) + ""],
                                                                                     "objective_id": [
                                                                                         "" + str(objective.id) + ""]},
                                                                         False))]
        changeList = env.execActions(requests)
        assert objective.value == 0
        assert quest.state == QuestState.InProgress
        eventCount = len(modeldata.StatisticEventsKeeper)

        # -----
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G245")
        modeldata.UserInventory.add(target_talent)
        # -----
        thundergod = None
        for hero_id in modeldata.Heroes:
            hero = modeldata.getHeroByID(hero_id)
            if hero.PersistentId == crc32('thundergod'):
                thundergod = hero
                break
        thundergod.TalentSets[0].Talents[36] = target_talent.id
        target_talent.Owner = thundergod
        target_talent.ParentTalentSets.add(0, thundergod.TalentSets[0].id)

        requests = [(Try_complete_objective, TryCompleteObjectiveRequest(modeldata, {"quest_id": ["" + str(quest.id) + ""],
                                                                                     "objective_id": [
                                                                                         "" + str(objective.id) + ""]},
                                                                         False))]
        changeList = env.execActions(requests)
