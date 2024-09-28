# -*- coding: utf-8 -*-
# !/usr/bin/env python
import sys

sys.path.append('../')
sys.path.append('../../')
from logic.keepalive import *
from logic.hire_hero import *
from logic.show_error import *
from logic.item_move_inv2ts import *
from binascii import crc32
import time
import datetime
from Events.event import *
from Events.EventMap import *
from modeldata.validator import Validator
import EC

sys.path.append('../..')
from enums import *
from Events.EventSkin import *


class util_func_test:
    def is_first_day_login_test(self, env):
        modeldata = env.acc.model
        modeldata.LordInfo.CurrentLoginTime = 100000
        modeldata.LordInfo.LastLoginTime = modeldata.LordInfo.CurrentLoginTime - 3600

        test = modeldata.IsFirstDayLogin()

        assert not test

        modeldata.LordInfo.CurrentLoginTime = 100000
        modeldata.LordInfo.LastLoginTime = modeldata.LordInfo.CurrentLoginTime - 3600 * 25

        test = modeldata.IsFirstDayLogin()

        assert test

    def bad_param_request_test(self, env):
        modeldata = env.acc.model

        requests = [(Show_error, ShowErrorRequest(modeldata, {"stupid_param": ["param_taram"]}, False))]
        changeList = env.execActions(requests)

        assert changeList[0]['ec'] == EC.DEBUG_MESSAGE
        assert changeList[0]['error'].find("code") != -1

        # To generate this use DebugRandomGenTest in ModelData2Test\LogicTests\StuffTests.cs

    def random_gen_test(self, env):
        self.modeldata = env.acc.model
        assert self.modeldata.getRandomInRange(1000, 1, 100) == 53
        assert self.modeldata.getRandomInRange(1001, 1, 100) == 18
        assert self.modeldata.getRandomInRange(1002, 1, 100) == 84
        assert self.modeldata.getRandomInRange(1003, 1, 100) == 50
        assert self.modeldata.getRandomInRange(1004, 1, 100) == 15
        assert self.modeldata.getRandomInRange(1005, 1, 100) == 81
        assert self.modeldata.getRandomInRange(1006, 1, 100) == 47
        assert self.modeldata.getRandomInRange(1007, 1, 100) == 12
        assert self.modeldata.getRandomInRange(1008, 1, 100) == 78
        assert self.modeldata.getRandomInRange(1009, 1, 100) == 44
        assert self.modeldata.getRandomInRange(1010, 1, 100) == 9
        assert self.modeldata.getRandomInRange(1011, 1, 100) == 75
        assert self.modeldata.getRandomInRange(1012, 1, 100) == 41
        assert self.modeldata.getRandomInRange(1013, 1, 100) == 6
        assert self.modeldata.getRandomInRange(1014, 1, 100) == 72
        assert self.modeldata.getRandomInRange(1015, 1, 100) == 38
        assert self.modeldata.getRandomInRange(1016, 1, 100) == 3
        assert self.modeldata.getRandomInRange(1017, 1, 100) == 69
        assert self.modeldata.getRandomInRange(1018, 1, 100) == 35
        assert self.modeldata.getRandomInRange(1019, 1, 100) == 100
        assert self.modeldata.getRandomInRange(1020, 1, 100) == 66
        assert self.modeldata.getRandomInRange(1021, 1, 100) == 32
        assert self.modeldata.getRandomInRange(1022, 1, 100) == 97
        assert self.modeldata.getRandomInRange(1023, 1, 100) == 63
        assert self.modeldata.getRandomInRange(1024, 1, 100) == 29
        assert self.modeldata.getRandomInRange(1025, 1, 100) == 94
        assert self.modeldata.getRandomInRange(1026, 1, 100) == 60
        assert self.modeldata.getRandomInRange(1027, 1, 100) == 25
        assert self.modeldata.getRandomInRange(1028, 1, 100) == 91
        assert self.modeldata.getRandomInRange(1029, 1, 100) == 57
        assert self.modeldata.getRandomInRange(1030, 1, 100) == 22
        assert self.modeldata.getRandomInRange(1031, 1, 100) == 88
        assert self.modeldata.getRandomInRange(1032, 1, 100) == 54
        assert self.modeldata.getRandomInRange(1033, 1, 100) == 19
        assert self.modeldata.getRandomInRange(1034, 1, 100) == 85
        assert self.modeldata.getRandomInRange(1035, 1, 100) == 51
        assert self.modeldata.getRandomInRange(1036, 1, 100) == 16
        assert self.modeldata.getRandomInRange(1037, 1, 100) == 82
        assert self.modeldata.getRandomInRange(1038, 1, 100) == 48
        assert self.modeldata.getRandomInRange(1039, 1, 100) == 13
        assert self.modeldata.getRandomInRange(1040, 1, 100) == 79
        assert self.modeldata.getRandomInRange(1041, 1, 100) == 45
        assert self.modeldata.getRandomInRange(1042, 1, 100) == 10
        assert self.modeldata.getRandomInRange(1043, 1, 100) == 76
        assert self.modeldata.getRandomInRange(1044, 1, 100) == 42
        assert self.modeldata.getRandomInRange(1045, 1, 100) == 7
        assert self.modeldata.getRandomInRange(1046, 1, 100) == 73
        assert self.modeldata.getRandomInRange(1047, 1, 100) == 39
        assert self.modeldata.getRandomInRange(1048, 1, 100) == 4
        assert self.modeldata.getRandomInRange(1049, 1, 100) == 70
        assert self.modeldata.getRandomInRange(1050, 1, 100) == 35
        assert self.modeldata.getRandomInRange(1051, 1, 100) == 1
        assert self.modeldata.getRandomInRange(1052, 1, 100) == 67
        assert self.modeldata.getRandomInRange(1053, 1, 100) == 32
        assert self.modeldata.getRandomInRange(1054, 1, 100) == 98
        assert self.modeldata.getRandomInRange(1055, 1, 100) == 64
        assert self.modeldata.getRandomInRange(1056, 1, 100) == 29
        assert self.modeldata.getRandomInRange(1057, 1, 100) == 95
        assert self.modeldata.getRandomInRange(1058, 1, 100) == 61
        assert self.modeldata.getRandomInRange(1059, 1, 100) == 26
        assert self.modeldata.getRandomInRange(1060, 1, 100) == 92
        assert self.modeldata.getRandomInRange(1061, 1, 100) == 58
        assert self.modeldata.getRandomInRange(1062, 1, 100) == 23
        assert self.modeldata.getRandomInRange(1063, 1, 100) == 89
        assert self.modeldata.getRandomInRange(1064, 1, 100) == 55
        assert self.modeldata.getRandomInRange(1065, 1, 100) == 20
        assert self.modeldata.getRandomInRange(1066, 1, 100) == 86
        assert self.modeldata.getRandomInRange(1067, 1, 100) == 52
        assert self.modeldata.getRandomInRange(1068, 1, 100) == 17
        assert self.modeldata.getRandomInRange(1069, 1, 100) == 83
        assert self.modeldata.getRandomInRange(1070, 1, 100) == 49
        assert self.modeldata.getRandomInRange(1071, 1, 100) == 14
        assert self.modeldata.getRandomInRange(1072, 1, 100) == 80
        assert self.modeldata.getRandomInRange(1073, 1, 100) == 45
        assert self.modeldata.getRandomInRange(1074, 1, 100) == 11
        assert self.modeldata.getRandomInRange(1075, 1, 100) == 77
        assert self.modeldata.getRandomInRange(1076, 1, 100) == 42
        assert self.modeldata.getRandomInRange(1077, 1, 100) == 8
        assert self.modeldata.getRandomInRange(1078, 1, 100) == 74
        assert self.modeldata.getRandomInRange(1079, 1, 100) == 39
        assert self.modeldata.getRandomInRange(1080, 1, 100) == 5
        assert self.modeldata.getRandomInRange(1081, 1, 100) == 71
        assert self.modeldata.getRandomInRange(1082, 1, 100) == 36
        assert self.modeldata.getRandomInRange(1083, 1, 100) == 2
        assert self.modeldata.getRandomInRange(1084, 1, 100) == 68
        assert self.modeldata.getRandomInRange(1085, 1, 100) == 33
        assert self.modeldata.getRandomInRange(1086, 1, 100) == 99
        assert self.modeldata.getRandomInRange(1087, 1, 100) == 65
        assert self.modeldata.getRandomInRange(1088, 1, 100) == 30
        assert self.modeldata.getRandomInRange(1089, 1, 100) == 96
        assert self.modeldata.getRandomInRange(1090, 1, 100) == 62
        assert self.modeldata.getRandomInRange(1091, 1, 100) == 27
        assert self.modeldata.getRandomInRange(1092, 1, 100) == 93
        assert self.modeldata.getRandomInRange(1093, 1, 100) == 59
        assert self.modeldata.getRandomInRange(1094, 1, 100) == 24
        assert self.modeldata.getRandomInRange(1095, 1, 100) == 90
        assert self.modeldata.getRandomInRange(1096, 1, 100) == 55
        assert self.modeldata.getRandomInRange(1097, 1, 100) == 21
        assert self.modeldata.getRandomInRange(1098, 1, 100) == 87
        assert self.modeldata.getRandomInRange(1099, 1, 100) == 52
        assert self.modeldata.getRandomInRange(1100, 1, 100) == 18

    def applyDefaultTalentSetWithUnsoulbound_test(self, env):
        modeldata = env.acc.model

        modeldata.LordInfo.Fame = 100000
        modeldata.Resources = env.generate_resources(2000000)

        assert len(modeldata.HeroesKeeper) == 5
        assert len(modeldata.Heroes) == 5

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32("rockman")]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.HeroesKeeper) == 6
        assert len(modeldata.Heroes) == 6

        for heroId in modeldata.HeroesKeeper:
            hero = modeldata.getHeroByID(heroId)
            if hero.class_name == "rockman":
                foundHero = hero
                break

        TScount = len(foundHero.TalentSets[0].Talents)

        assert foundHero is not None
        foundHero.Experience = 100500

        talent = env.add_talent(modeldata, "G397")
        modeldata.UserInventory.add(talent)

        for tsSlotId in foundHero.TalentSets[0].Talents:
            destSlotId = tsSlotId
            destTalent = modeldata.getTalentByID(modeldata.getHeroByID(foundHero.id).TalentSets[0].Talents.get(tsSlotId))
            break
        for invTalentId in modeldata.UserInventory:
            sourceTalent = modeldata.UserInventory.get(invTalentId)
            sourceTalentPersistentId = sourceTalent.PersistentId
            talent_id, response_error = Validator.checkItemFit(env.acc, foundHero, sourceTalent, destSlotId, env.acc.SD,
                                                               1, modeldata.getHeroClassTalents(env.acc.getConfig(), foundHero.PersistentId,
                                                                                           env.acc.SD))
            if talent_id:
                break

        requests = [(Item_move_inv2ts, ItemMoveInvToTsRequest(modeldata, {"src_hero_id": ["" + str(foundHero.id) + ""],
                                                                          "src_item_id": ["" + str(sourceTalent.id) + ""],
                                                                          "dest_slot_id": ["" + str(tsSlotId) + ""],
                                                                          "dest_item_id": [ "" + str(destTalent.id) + ""],
                                                                          "useLamp": ["false"],
                                                                          "talent_set_id": ["0"]}, False))]
        changeList = env.execActions(requests)

        assert modeldata.UserInventory.get(destTalent.id) == destTalent
        assert modeldata.getHeroByID(foundHero.id).TalentSets[0].Talents.get(destSlotId) == sourceTalent.id
        #assert sourceTalent.Soulbound == foundHero

        foundHero.applyDefaultTalentSets(modeldata, env.acc.SD, env.acc.getConfig(), True)

        assert modeldata.UserInventory.get(sourceTalent.id) == sourceTalent
        # assert modeldata.getTalentByID(foundHero.TalentSet.getID(destSlotId)).PersistentId == destTalent.PersistentId
        assert sourceTalent.Soulbound == 0
        # assert TScount == len(foundHero.TalentSet)

    def applyDefaultTalentSetWithUnsoulboundClassTalent_test(self, env):
        modeldata = env.acc.model

        modeldata.LordInfo.Fame = 100000
        modeldata.Resources = env.generate_resources(2000000)

        assert len(modeldata.HeroesKeeper) == 5
        assert len(modeldata.Heroes) == 5

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32("rockman")]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.HeroesKeeper) == 6
        assert len(modeldata.Heroes) == 6

        for heroId in modeldata.HeroesKeeper:
            hero = modeldata.getHeroByID(heroId)
            if hero.class_name == "rockman":
                foundHero = hero
                break

        assert foundHero != None
        TScount = len(foundHero.TalentSets[0].Talents)

        done = False
        for tsSlotId in foundHero.TalentSets[0].Talents.keys():
            talent = modeldata.getTalentByID(foundHero.TalentSets[0].Talents.get(tsSlotId))
            staticTalent = env.acc.SD.getStaticTalent(talent)
            if staticTalent and staticTalent['rarity'] == "Class":
                foundHero.removeTalentFromTalentSet(0, talent, talent.id)
                done = True
                break

        assert done

        assert modeldata.UserInventory.get(talent.id) == talent
        assert modeldata.getHeroByID(foundHero.id).TalentSets[0].Talents.get(tsSlotId) == None
        assert talent.Soulbound == foundHero

        foundHero.applyDefaultTalentSets(modeldata, env.acc.SD, env.acc.getConfig(), True)

        assert modeldata.UserInventory.get(talent.id) == talent
        # assert modeldata.getTalentByID(foundHero.TalentSet.getID(destSlotId)).PersistentId == destTalent.PersistentId
        assert talent.Soulbound == foundHero
        # assert TScount == len(foundHero.TalentSet)

    def restore_md_fields_test(self, env):
        env.I.MD.events = []
        env.acc.model.version.events = []

        env.acc.model.LordInfo.PremiumAccountStart = 1050
        env.acc.model.LordInfo.PremiumAccountEnd = 100500
        env.acc.model.LordInfo.LastLoginTime = 10005000
        env.I.MD.newModel(env.acc, env.I, "1.2.3", random_heroes=-1, random_items=-1, fraction=env.acc.db.fraction,
                          db=env.acc.db, guest=1, old_md=env.acc.model)
        assert env.acc.model.LordInfo.PremiumAccountStart == 1050
        assert env.acc.model.LordInfo.PremiumAccountEnd == 100500
        assert env.acc.model.LordInfo.LastLoginTime == 0

    def restore_md_fields_with_events_test(self, env):
        env.acc.model.LordInfo.LastLoginTime = 100500
        env.I.MD.events = []
        env.acc.model.version.events = []
        env.acc.model.LordInfo.PremiumAccountStart = 0
        env.acc.model.LordInfo.PremiumAccountEnd = 0
        now = datetime.datetime.now()

        eventDict1 = {"persistentId": 1,
                      "startTime": int(time.time()) - 60 * 60,
                      "endTime": int(time.time()) + 60 * 60,
                      "newValue": {"eventDescription": utf8convert('extend_premium \"3\"')}}
        eventDict2 = {"persistentId": 2,
                      "startTime": int(time.time()) - 60 * 60,
                      "endTime": int(time.time()) + 60 * 60,
                      "newValue": {"eventDescription": utf8convert('resources \"Silver = 100\"')}}

        env.I.Config.events.append(event(eventDict1))
        env.I.Config.events.append(event(eventDict2))

        env.I.MD.newModel(env.acc, env.I, "1.2.3", random_heroes=-1, random_items=-1, fraction=env.acc.db.fraction,
                          db=env.acc.db, guest=1, old_md=env.acc.model)

        time1 = time.mktime(now.timetuple())
        # дельта - время между созданием эвента и его применением. при дебаге может не проходить следующую проверку
        delta = (env.acc.model.LordInfo.PremiumAccountStart - time1)
        assert delta < 5
        time2 = time.mktime((now + datetime.timedelta(days=3)).timetuple())
        assert env.acc.model.LordInfo.PremiumAccountEnd - delta == time2
        assert env.acc.model.Resources.Silver == 1000100
        assert env.acc.model.LordInfo.LastLoginTime == 0

    def restore_md_fields_with_applied_events_test(self, env):
        env.acc.model.LordInfo.LastLoginTime = 100500
        env.I.MD.events = []
        now = datetime.datetime.now()

        env.acc.model.LordInfo.PremiumAccountStart = time.mktime((now).timetuple())
        env.acc.model.LordInfo.PremiumAccountEnd = time.mktime((now + datetime.timedelta(days=1)).timetuple())

        eventDict1 = {"persistentId": 1,
                      "startTime": int(time.time()) - 60 * 60,
                      "endTime": int(time.time()) + 60 * 60,
                      "newValue": {"eventDescription": utf8convert('extend_premium \"3\"')}}
        eventDict2 = {"persistentId": 2,
                      "startTime": int(time.time()) - 60 * 60,
                      "endTime": int(time.time()) + 60 * 60,
                      "newValue": {"eventDescription": utf8convert('resources \"Silver = 100\"')}}

        env.I.Config.events.append(event(eventDict1))
        env.I.Config.events.append(event(eventDict2))

        # event with id 1 and 2 where already applied
        env.acc.model.version.events.append(1)
        env.acc.model.version.events.append(2)

        env.I.MD.newModel(env.acc, env.I, "1.2.3", random_heroes=-1, random_items=-1, fraction=env.acc.db.fraction,
                          db=env.acc.db, guest=1, old_md=env.acc.model)

        time1 = time.mktime(now.timetuple())
        # дельта - время между созданием эвента и его применением. при дебаге может не проходить следующую проверку
        delta = (env.acc.model.LordInfo.PremiumAccountStart - time1)
        assert delta < 5
        time2 = time.mktime((now + datetime.timedelta(days=1)).timetuple())
        assert env.acc.model.LordInfo.PremiumAccountEnd - delta == time2
        assert env.acc.model.Resources.Silver == 1000000
        assert env.acc.model.LordInfo.LastLoginTime == 0

    def missing_class_talent_fix_test(self, env):
        modeldata = env.acc.model
        #assert len(modeldata.UserInventory) == 0
        for heroId in modeldata.Heroes.keys():
            hero  = modeldata.getHeroByID(heroId)
            for tsId in hero.TalentSets.keys():
                for tid in hero.TalentSets[tsId].Talents.values():
                    talent = modeldata.getTalentByID(tid)
                    if talent:
                        staticTalent = env.acc.SD.getStaticTalent(talent)
                        if staticTalent and staticTalent['rarity'] == "Class":
                            if talent in modeldata.UserInventory.values():
                                hero.moveTalentFromTalentSetToLibrary(talent, talent.id)
                                modeldata.UserInventory.remove(talent)

            modeldata.Heroes.remove(heroId)
        assert len(modeldata.Heroes) == 0
        hero = env.add_hero(modeldata, 'mowgly')
        assert len(modeldata.Heroes) == 1
        assert len(hero.TalentSets[0].Talents) == 0
        is_valid, valid_info = modeldata.checkValidity(env.acc, env.acc.SD)
        assert not is_valid
        modeldata.fixAll(env.acc, env.acc.SD)
        is_valid, valid_info = modeldata.checkValidity(env.acc, env.acc.SD)
        assert is_valid
        assert len(modeldata.UserInventory) > 0 or len(hero.TalentSets[0].Talents) > 0

    def add_start_quest_test(self, env):
        modeldata = env.acc.model

        env.I.Config.getConfig(env.acc.userlocale).ADD_FIRST_QUEST = False
        for quest in modeldata.ActiveQuests.keys():
            modeldata.ActiveQuests.remove(quest)
        assert len(modeldata.ActiveQuests) == 0
        modeldata.GiveStartQuest(env.acc.SD.data["StartQuest"], env.acc, env.I)
        assert len(modeldata.ActiveQuests) == 0

        env.I.Config.getConfig(env.acc.userlocale).ADD_FIRST_QUEST = True
        for quest in modeldata.ActiveQuests.keys():
            modeldata.ActiveQuests.remove(quest)
        assert len(modeldata.ActiveQuests) == 0

        for quest in modeldata.CompletedQuests.keys():
            modeldata.CompletedQuests.remove(quest)

        modeldata.GiveStartQuest(env.acc.SD.data["StartQuest"], env.acc, env.I)
        assert len(modeldata.ActiveQuests) == 1

    def add_experience_test(self, env):
        modeldata = env.acc.model
        modeldata.LordInfo.Fame = 0
        hero = modeldata.hireHero(crc32("archeress"), env.acc.sex, env.I.WS, env.acc, env.I)
        assert hero
        assert hero.TalentSets[0].Stats.StatPoints == 0
        modeldata.LordInfo.Fame = 0
        hero.changeExperience(1005000, modeldata, env.I.WS, env.acc, env.I)

        total_points = 0
        for points in env.acc.SD.data['StatpointsToLevelTable']['StatPoints']['Item']:
            total_points += points

        static_hero = env.acc.SD.getStaticHeroByClassId(hero.PersistentId)
        total_fame = 0
        for fame in static_hero['lobbyData']['FameIncrement']['FameIncrement']['Item']:
            total_fame += fame
        total_fame -= static_hero['lobbyData']['FameIncrement']['FameIncrement']['Item'][0]
        total_fame -= static_hero['lobbyData']['FameIncrement']['FameIncrement']['Item'][-1]

        assert total_points <= hero.TalentSets[0].Stats.StatPoints
        assert total_fame <= modeldata.LordInfo.Fame

    def duplicate_default_ts_talents_test(self, env):
        modeldata = env.acc.model

        hero = modeldata.hireHero(crc32("archeress"), env.acc.sex, env.I.WS, env.acc, env.I)

        # sell talent in 36 slot
        t = modeldata.getTalentByID(hero.TalentSets[0].Talents.get(36))
        hero.removeTalentFromTalentSet(0, t, t.id)
        # sell talent in 35 slot
        t = modeldata.getTalentByID(hero.TalentSets[0].Talents[35])
        persistent_35 = t.PersistentId
        hero.removeTalentFromTalentSet(0, t, t.id)
        # add same talent as was in 35 slot to 36 slot
        talent_35 = env.add_talent(modeldata, persistent_35)
        hero.TalentSets[0].Talents.add(36, talent_35.id)
        talent_35.ParentTalentSets.add(0, hero.TalentSets[0].id)
        talent_35.Owner = hero
        talentDict = []
        for pos, tid in hero.TalentSets[0].Talents.iteritems():
            talent = modeldata.getTalentByID(tid)
            if not talent:
                info("talent id %r", tid)
            assert talent.PersistentId not in talentDict
            talentDict.append(talent.PersistentId)

        hero.applyDefaultTalentSets(modeldata, env.acc.SD, False, env.acc.getConfig())

        talentDict = []
        for pos, tid in hero.TalentSets[0].Talents.iteritems():
            talent = modeldata.getTalentByID(tid)
            assert talent.PersistentId not in talentDict
            talentDict.append(talent.PersistentId)

    def count_gold_spent_with_no_buildings_test(self, env):
        modeldata = env.acc.model

        gold = modeldata.getSpentGold(env.I, env.acc)

        assert gold == 0

    def count_gold_spent_for_building_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Gold = 0

        construction = env.add_construction(modeldata, "FirstBuy_Cat")
        gold = modeldata.getSpentGold(env.I, env.acc)

        assert gold > 0

    def count_gold_spent_for_building_with_lvlups_test(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "FirstBuy_Cat")
        construction.Level = 10
        gold = modeldata.getSpentGold(env.I, env.acc)

        assert gold > 0

    def count_gold_spent_for_building_in_pocket_test(self, env):
        modeldata = env.acc.model

        construction = env.add_construction(modeldata, "FirstBuy_Cat")
        modeldata.Pocket.add(construction)
        modeldata.Buildings.remove(construction)
        assert len(modeldata.Pocket) == 1
        assert len(modeldata.Buildings) == 0
        gold = modeldata.getSpentGold(env.I, env.acc)

        assert gold > 0

    def count_gold_spent_for_skins_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Gold = 0

        self.hero, heroId = modeldata.findHeroByCrc32(crc32("thundergod"))
        assert self.hero
        assert len(self.hero.HeroSkins.Skins) == 0

        skin_id = modeldata.addNewSkin()
        skin = modeldata.getSkinByID(skin_id)
        skin.PersistentId = crc32("thundergod_S1_A")
        skin.WasBought = True
        self.hero.HeroSkins.Skins.add(skin_id)
        self.hero.HeroSkins.CurrentSkin = skin

        skin_cost = int(env.acc.SD.getStaticSkinByPersistentId(skin.PersistentId)['cost'])

        gold = modeldata.getSpentGold(env.I, env.acc)

        assert gold == skin_cost

    def count_gold_spent_for_skins_no_gold_test(self, env):
        modeldata = env.acc.model
        modeldata.Resources.Gold = 0

        self.hero, heroId = modeldata.findHeroByCrc32(crc32("thundergod"))
        assert self.hero
        assert len(self.hero.HeroSkins.Skins) == 0

        skin_id = modeldata.addNewSkin()
        skin = modeldata.getSkinByID(skin_id)
        skin.PersistentId = crc32("thundergod_S1_A")
        skin.WasBought = False
        self.hero.HeroSkins.Skins.add(skin_id)
        self.hero.HeroSkins.CurrentSkin = skin

        skin_cost = int(env.acc.SD.getStaticSkinByPersistentId(skin.PersistentId)['cost'])

        gold = modeldata.getSpentGold(env.I, env.acc)

        assert gold == 0

    def count_gold_spent_with_flags(self, env):
        modeldata = env.acc.model
        modeldata.Flags.append("rak")
        modeldata.Flags.append("kote")
        modeldata.Flags.append("smile_admin")
        flagRak = env.I.Config.getMainConfig().getCustomFlagById("rak")
        flagKote = env.I.Config.getMainConfig().getCustomFlagById("kote")
        flagFromStaticData = env.acc.SD.getCustomFlagById("smile_admin")

        flagsPrice = flagRak.Price + flagKote.Price + int(flagFromStaticData['Price'])
        assert flagsPrice > 0
        gold = modeldata.getSpentGold(env.I, env.acc)

        assert gold == flagsPrice

    def newHeroVersionAndTalentWithUpgrade_test(self, env):
        modeldata = env.acc.model

        modeldata.LordInfo.Fame = 100000
        modeldata.Resources = env.generate_resources(2000000)

        assert len(modeldata.HeroesKeeper) == 5
        assert len(modeldata.Heroes) == 5

        requests = [(Hire_hero, HireHeroRequest(modeldata, {"PersistentId": [crc32("rockman")]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.HeroesKeeper) == 6
        assert len(modeldata.Heroes) == 6

        for heroId in modeldata.HeroesKeeper:
            hero = modeldata.getHeroByID(heroId)
            if hero.class_name == "rockman":
                foundHero = hero
                break

        assert foundHero != None

        talent = None
        for tsSlotId in foundHero.TalentSets[0].Talents:
            talent = modeldata.getTalentByID(foundHero.TalentSets[0].Talents.get(tsSlotId))
            staticTalent = env.acc.SD.getStaticTalent(talent)
            if staticTalent and staticTalent['rarity'] != "Class":
                break

        talent.Points = 221

        assert talent.Soulbound == 0

        foundHero.applyDefaultTalentSets(modeldata, env.acc.SD, env.acc.getConfig(), True)

        newTalent = None
        found = False
        for tsSlotId in foundHero.TalentSets[0].Talents:
            newTalent = modeldata.getTalentByID(foundHero.TalentSets[0].Talents.get(tsSlotId))
            if newTalent.id == talent.id:
                found = True
                break

        assert found
        assert talent.Soulbound == 0
        assert talent.Points == 221

    def events_add_skin_test(self, env):
        env.I.MD.events = []
        env.acc.model.version.events = []
        now = datetime.datetime.now()
        eventDict = {"persistentId": 2,
                     "startTime": int(time.time()) - 60 * 60,
                     "endTime": int(time.time()) + 60 * 60,
                     "newValue": {"eventDescription": utf8convert('skins \"add thundergod_S1_A\"')}}

        env.I.Config.events.append(event(eventDict))

        env.I.MD.newModel(env.acc, env.I, "1.2.3", random_heroes=-1, random_items=-1, sex=1, fraction='A',
                          db=env.acc.db, guest=0, old_md=env.acc.model)

        assert len(env.acc.model.SkinsKeeper) == 1
        for heroId in env.acc.model.HeroesKeeper:
            hero = env.acc.model.getHeroByID(heroId)
            if hero.class_name == "thundergod":
                foundHero = hero
                break
        assert foundHero
        assert len(foundHero.HeroSkins.Skins) == 1
        env.I.MD.events = []

    def events_add_skin_wrong_id_test(self, env):
        env.I.MD.events = []
        env.acc.model.version.events = []
        eventDict = {"persistentId": 2,
                     "startTime": int(time.time()) - 60 * 60,
                     "endTime": int(time.time()) + 60 * 60,
                     "newValue": {"eventDescription": utf8convert('skins \"add piece_of_sheep\"')}}

        env.I.Config.events.append(event(eventDict))
        env.I.MD.newModel(env.acc, env.I, "1.2.3", random_heroes=-1, random_items=-1, sex=1, fraction='A',
                          db=env.acc.db, guest=0, old_md=env.acc.model)

        assert len(env.acc.model.SkinsKeeper) == 0
        for heroId in env.acc.model.HeroesKeeper:
            hero = env.acc.model.getHeroByID(heroId)
            if hero.class_name == "thundergod":
                foundHero = hero
                break
        assert foundHero
        assert len(foundHero.HeroSkins.Skins) == 0
        env.I.MD.events = []

    def events_add_skin_wrong_fraction_test(self, env):
        env.I.MD.events = []
        env.acc.model.version.events = []
        eventDict = {"persistentId": 2,
                     "startTime": int(time.time()) - 60 * 60,
                     "endTime": int(time.time()) + 60 * 60,
                     "newValue": {"eventDescription": utf8convert('skins \"add thundergod_S1_B\"')}}

        env.I.Config.events.append(event(eventDict))
        env.I.MD.newModel(env.acc, env.I, "1.2.3", random_heroes=-1, random_items=-1, sex=1, fraction='A',
                          db=env.acc.db, guest=0, old_md=env.acc.model)

        assert len(env.acc.model.SkinsKeeper) == 1
        for heroId in env.acc.model.HeroesKeeper:
            hero = env.acc.model.getHeroByID(heroId)
            if hero.class_name == "thundergod":
                foundHero = hero
                break
        assert foundHero
        assert len(foundHero.HeroSkins.Skins) == 1
        env.I.MD.events = []

    def events_add_skin_no_hero_test(self, env):
        env.I.MD.events = []
        env.acc.model.version.events = []
        eventDict = {"persistentId": 2,
                     "startTime": int(time.time()) - 60 * 60,
                     "endTime": int(time.time()) + 60 * 60,
                     "newValue": {"eventDescription": utf8convert('skins \"add night_S1_A\"')}}

        env.I.Config.events.append(event(eventDict))
        env.I.MD.newModel(env.acc, env.I, "1.2.3", random_heroes=-1, random_items=-1, sex=1, fraction='A',
                          db=env.acc.db, guest=0, old_md=env.acc.model)

        assert len(env.acc.model.SkinsKeeper) == 0
        env.I.MD.events = []

    def events_add_skin_no_hero_twice_test(self, env):
        env.I.MD.events = []
        env.acc.model.version.events = []
        eventDict = {"persistentId": 2,
                     "startTime": int(time.time()) - 60 * 60,
                     "endTime": int(time.time()) + 60 * 60,
                     "newValue": {"eventDescription": utf8convert('skins \"add night_S1_A\"')}}

        skin_event = event(eventDict)
        env.acc.model = skin_event.apply(env.acc, 1, 'A', env.I)

        assert len(env.acc.model.SkinsKeeper) == 0

        hero = env.add_hero(env.acc.model, "night")

        env.acc.model = skin_event.apply(env.acc, 1, 'A', env.I)

        assert len(env.acc.model.SkinsKeeper) == 1

        for heroId in env.acc.model.HeroesKeeper:
            hero = env.acc.model.getHeroByID(heroId)
            if hero.class_name == "night":
                foundHero = hero
                break
        assert foundHero
        assert len(foundHero.HeroSkins.Skins) == 1

    def events_add_existing_skin_test(self, env):
        env.I.MD.events = []
        env.acc.model.version.events = []
        eventDict = {"persistentId": 2,
                     "startTime": int(time.time()) - 60 * 60,
                     "endTime": int(time.time()) + 60 * 60,
                     "newValue": {"eventDescription": utf8convert('skins \"add night_S1_A\"')}}

        skin_event = event(eventDict)



        hero = env.add_hero(env.acc.model, "night")
        static_skin = env.acc.SD.getStaticSkinByPersistentId(crc32("night_S1_A"))
        assert static_skin
        skin_id = env.acc.model.addNewSkin()
        skin = env.acc.model.getSkinByID(skin_id)
        skin.PersistentId = crc32(static_skin['persistentId'])
        skin.WasBought = True
        hero.HeroSkins.Skins.add(skin_id)

        assert len(env.acc.model.SkinsKeeper) == 1
        for heroId in env.acc.model.HeroesKeeper:
            hero = env.acc.model.getHeroByID(heroId)
            if hero.class_name == "night":
                foundHero2 = hero
                break
        assert foundHero2
        assert len(foundHero2.HeroSkins.Skins) == 1

        env.acc.model = skin_event.apply(env.acc, 1, 'A', env.I)

        assert len(env.acc.model.SkinsKeeper) == 1
        for heroId in env.acc.model.HeroesKeeper:
            hero = env.acc.model.getHeroByID(heroId)
            if hero.class_name == "night":
                foundHero2 = hero
                break
        assert foundHero2
        assert len(foundHero2.HeroSkins.Skins) == 1

    def events_delete_existing_skin_test(self, env):
        env.I.MD.events = []
        eventDict = {"persistentId": 2,
                     "startTime": int(time.time()) - 60 * 60,
                     "endTime": int(time.time()) + 60 * 60,
                     "newValue": {"eventDescription": utf8convert('skins \"delete night_S1_A\"')}}

        skin_event = event(eventDict)

        hero = env.add_hero(env.acc.model, "night")
        static_skin = env.acc.SD.getStaticSkinByPersistentId(crc32("night_S1_A"))
        assert static_skin
        skin_id = env.acc.model.addNewSkin()
        skin = env.acc.model.getSkinByID(skin_id)
        skin.PersistentId = crc32(static_skin['persistentId'])
        skin.WasBought = False
        hero.HeroSkins.Skins.add(skin_id)

        assert len(env.acc.model.SkinsKeeper) == 1
        for heroId in env.acc.model.HeroesKeeper:
            hero = env.acc.model.getHeroByID(heroId)
            if hero.class_name == "night":
                foundHero2 = hero
                break
        assert foundHero2
        assert len(foundHero2.HeroSkins.Skins) == 1

        env.acc.model = skin_event.apply(env.acc, 1, 'A', env.I)

        assert len(env.acc.model.SkinsKeeper) == 0
        for heroId in env.acc.model.HeroesKeeper:
            hero = env.acc.model.getHeroByID(heroId)
            if hero.class_name == "night":
                foundHero2 = hero
                break
        assert foundHero2
        assert len(foundHero2.HeroSkins.Skins) == 0

    def events_delete_bought_skin_test(self, env):
        env.I.MD.events = []
        env.acc.model.version.events = []
        eventDict = {"persistentId": 2,
                     "startTime": int(time.time()) - 60 * 60,
                     "endTime": int(time.time()) + 60 * 60,
                     "newValue": {"eventDescription": utf8convert('skins \"delete night_S1_A\"')}}

        skin_event = event(eventDict)

        hero = env.add_hero(env.acc.model, "night")
        static_skin = env.acc.SD.getStaticSkinByPersistentId(crc32("night_S1_A"))
        assert static_skin
        skin_id = env.acc.model.addNewSkin()
        skin = env.acc.model.getSkinByID(skin_id)
        skin.PersistentId = crc32(static_skin['persistentId'])
        skin.WasBought = True
        hero.HeroSkins.Skins.add(skin_id)

        assert len(env.acc.model.SkinsKeeper) == 1
        for heroId in env.acc.model.HeroesKeeper:
            hero = env.acc.model.getHeroByID(heroId)
            if hero.class_name == "night":
                foundHero2 = hero
                break
        assert foundHero2
        assert len(foundHero2.HeroSkins.Skins) == 1

        env.acc.model = skin_event.apply(env.acc, 1, 'A', env.I)

        assert len(env.acc.model.SkinsKeeper) == 1
        for heroId in env.acc.model.HeroesKeeper:
            hero = env.acc.model.getHeroByID(heroId)
            if hero.class_name == "night":
                foundHero2 = hero
                break
        assert foundHero2
        assert len(foundHero2.HeroSkins.Skins) == 1

    def events_delete_not_existing_skin_test(self, env):
        env.I.MD.events = []
        eventDict = {"persistentId": 2,
                     "startTime": int(time.time()) - 60 * 60,
                     "endTime": int(time.time()) + 60 * 60,
                     "newValue": {"eventDescription": utf8convert('skins \"delete piece_of_sheep\"')}}

        skin_event = event(eventDict)

        env.acc.model = skin_event.apply(env.acc, 1, 'A', env.I)

        assert len(env.acc.model.SkinsKeeper) == 0

    def events_apply_twice_test(self, env):
        return

        env.I.MD.events = []
        env.acc.model.version.events = []

        event1 = event('1 "' + start_time_string + '" "' + end_time_string + '" All fame "100"')
        event2 = event('* "' + start_time_string + '" "' + end_time_string + '" All fame "100"')

        env.acc.model.LordInfo.Fame = 0

        env.acc.model = event1.apply(env.acc, 1, 'A', env.I)
        env.acc.model = event2.apply(env.acc, 1, 'A', env.I)

        assert env.acc.model.LordInfo.Fame == 200

        env.acc.model = event1.apply(env.acc, 1, 'A', env.I)
        env.acc.model = event2.apply(env.acc, 1, 'A', env.I)

        assert env.acc.model.LordInfo.Fame == 300

    def validatingMap(self, env):
        modeldata = env.acc.model
        trainMapInfo = modeldata.LordInfo.MapsByType.get(MapType.Tutorial)

        assert trainMapInfo
        assert modeldata.isValidMap(trainMapInfo.MapId, env.acc)[0] == True

        modeldata.LordInfo.DisabledMaps.append(trainMapInfo.MapId)

        assert modeldata.isValidMap(trainMapInfo.MapId, env.acc)[0] == False

    def util_rank_diff_test(self, env):
        rank1 = 0
        rank2 = 1

        rating1 = env.acc.SD.data['AIGameLogic']['heroRanks']['ranks']['Item'][rank1]['rating']
        rating2 = env.acc.SD.data['AIGameLogic']['heroRanks']['ranks']['Item'][rank2]['rating']

        ratings = []
        ratings.append(rating1)
        ratings.append(rating2)

        minRank, maxRank = env.acc.SD.findMinMaxRanks(ratings)

        assert maxRank - minRank == rank2 - rank1

        rank1 = 1
        rank2 = 5

        rating1 = env.acc.SD.data['AIGameLogic']['heroRanks']['ranks']['Item'][rank1]['rating']
        rating2 = env.acc.SD.data['AIGameLogic']['heroRanks']['ranks']['Item'][rank2]['rating']

        ratings = []
        ratings.append(rating1)
        ratings.append(rating2)

        minRank, maxRank = env.acc.SD.findMinMaxRanks(ratings)

        assert maxRank - minRank == rank2 - rank1

    def load_skins_test1(self, env):
        # "12.03.2012 00:00" "13.03.2012 23:59" "mage_S2"
        modeldata = env.acc.model
        for skin in modeldata.ActiveEventSkins.keys():
            modeldata.ActiveEventSkins.remove(skin)
        for skin in modeldata.EventSkins.keys():
            modeldata.EventSkins.remove(skin)

        eventSkins = []

        numActiveEventSkins = len(modeldata.ActiveEventSkins)
        numEventSkins = len(modeldata.EventSkins)

        skin = "mage_S2"
        now = datetime.datetime.now()
        start_time_string = (now - datetime.timedelta(hours=1)).strftime("%d.%m.%Y %H:%M")
        end_time_string = (now + datetime.timedelta(hours=1)).strftime("%d.%m.%Y %H:%M")

        eventSkinInfo = EventSkin('"' + start_time_string + '" "' + end_time_string + '" "' + skin + '"')

        eventSkins.append(eventSkinInfo)

        assert len(eventSkins) == 1

        modeldata.calcEventSkin(eventSkins, env.acc)

        assert len(modeldata.ActiveEventSkins) == numActiveEventSkins + 1
        assert len(modeldata.EventSkins) == numEventSkins + 1

    # Цена не 0
    def load_free_skins_test1(self, env):
        # "12.03.2012 00:00" "13.03.2012 23:59" "mage_S2"
        modeldata = env.acc.model
        for skin in modeldata.ActiveEventSkins.keys():
            modeldata.ActiveEventSkins.remove(skin)
        for skin in modeldata.EventSkins.keys():
            modeldata.EventSkins.remove(skin)

        eventSkins = []

        numActiveEventSkins = len(modeldata.ActiveEventSkins)
        numEventSkins = len(modeldata.EventSkins)

        skin = "mage_S2"
        now = datetime.datetime.now()
        start_time_string = (now - datetime.timedelta(hours=1)).strftime("%d.%m.%Y %H:%M")
        end_time_string = (now + datetime.timedelta(hours=1)).strftime("%d.%m.%Y %H:%M")

        eventSkinInfo = EventSkin('"' + start_time_string + '" "' + end_time_string + '" "' + skin + '"')

        eventSkins.append(eventSkinInfo)

        assert len(eventSkins) == 1

        env.add_hero(modeldata, 'mage')

        modeldata.calcEventSkin(eventSkins, env.acc)

        assert len(modeldata.ActiveEventSkins) == numActiveEventSkins + 1
        assert len(modeldata.EventSkins) == numEventSkins + 1

        static_skin = env.acc.SD.getStaticSkinByPersistentId(crc32(skin))
        hero = modeldata.getHeroForSkin(static_skin, env.acc.SD)
        assert hero != None
        assert len(hero.HeroSkins.Skins) == 0

    # Цена 0, но герой не куплен
    def load_free_skins_test2(self, env):
        # "12.03.2012 00:00" "13.03.2012 23:59" "mage_S2"
        modeldata = env.acc.model
        for skin in modeldata.ActiveEventSkins.keys():
            modeldata.ActiveEventSkins.remove(skin)
        for skin in modeldata.EventSkins.keys():
            modeldata.EventSkins.remove(skin)

        eventSkins = []

        numActiveEventSkins = len(modeldata.ActiveEventSkins)
        numEventSkins = len(modeldata.EventSkins)

        skin = "mage_S2"
        now = datetime.datetime.now()
        start_time_string = (now - datetime.timedelta(hours=1)).strftime("%d.%m.%Y %H:%M")
        end_time_string = (now + datetime.timedelta(hours=1)).strftime("%d.%m.%Y %H:%M")

        eventSkinInfo = EventSkin('"' + start_time_string + '" "' + end_time_string + '" "' + skin + '"')

        eventSkins.append(eventSkinInfo)

        assert len(eventSkins) == 1

        config = env.acc.getConfig()
        config.EventToolsChangeFields.SKIN_GOLD_PRICES.add(skin, 0)

        modeldata.calcEventSkin(eventSkins, env.acc)

        assert len(modeldata.ActiveEventSkins) == numActiveEventSkins + 1
        assert len(modeldata.EventSkins) == numEventSkins + 1

        static_skin = env.acc.SD.getStaticSkinByPersistentId(crc32(skin))
        hero = modeldata.getHeroForSkin(static_skin, env.acc.SD)
        assert hero == None

    # Цена 0, герой куплен
    def load_free_skins_test3(self, env):
        # "12.03.2012 00:00" "13.03.2012 23:59" "mage_S2"
        modeldata = env.acc.model
        for skin in modeldata.ActiveEventSkins.keys():
            modeldata.ActiveEventSkins.remove(skin)
        for skin in modeldata.EventSkins.keys():
            modeldata.EventSkins.remove(skin)

        eventSkins = []

        numActiveEventSkins = len(modeldata.ActiveEventSkins)
        numEventSkins = len(modeldata.EventSkins)

        skin = "mage_S2"
        now = datetime.datetime.now()
        start_time_string = (now - datetime.timedelta(hours=1)).strftime("%d.%m.%Y %H:%M")
        end_time_string = (now + datetime.timedelta(hours=1)).strftime("%d.%m.%Y %H:%M")

        eventSkinInfo = EventSkin('"' + start_time_string + '" "' + end_time_string + '" "' + skin + '"')

        eventSkins.append(eventSkinInfo)

        assert len(eventSkins) == 1

        config = env.acc.getConfig()
        config.EventToolsChangeFields.SKIN_GOLD_PRICES[skin] = 0

        env.add_hero(modeldata, 'mage')

        modeldata.calcEventSkin(eventSkins, env.acc)

        assert len(modeldata.ActiveEventSkins) == numActiveEventSkins + 1
        assert len(modeldata.EventSkins) == numEventSkins + 1

        static_skin = env.acc.SD.getStaticSkinByPersistentId(crc32(skin))
        hero = modeldata.getHeroForSkin(static_skin, env.acc.SD)
        assert hero != None
        assert len(hero.HeroSkins.Skins) == 1

    def load_skins_test2(self, env):
        # "12.03.2012 00:00" "13.03.2012 23:59" "mage_S2"
        modeldata = env.acc.model
        for skin in modeldata.ActiveEventSkins.keys():
            modeldata.ActiveEventSkins.remove(skin)
        for skin in modeldata.EventSkins.keys():
            modeldata.EventSkins.remove(skin)

        eventSkins = []

        numActiveEventSkins = len(modeldata.ActiveEventSkins)
        numEventSkins = len(modeldata.EventSkins)

        skin = "mage_S2"
        now = datetime.datetime.now()
        start_time_string = (now - datetime.timedelta(hours=2)).strftime("%d.%m.%Y %H:%M")
        end_time_string = (now - datetime.timedelta(hours=1)).strftime("%d.%m.%Y %H:%M")

        eventSkinInfo = EventSkin('"' + start_time_string + '" "' + end_time_string + '" "' + skin + '"')

        eventSkins.append(eventSkinInfo)

        assert len(eventSkins) == 1

        modeldata.calcEventSkin(eventSkins, env.acc)

        assert len(modeldata.ActiveEventSkins) == numActiveEventSkins + 0
        assert len(modeldata.EventSkins) == numEventSkins + 1

    def load_skins_test3(self, env):
        # "12.03.2012 00:00" "13.03.2012 23:59" "mage_S2"
        modeldata = env.acc.model
        for skin in modeldata.ActiveEventSkins.keys():
            modeldata.ActiveEventSkins.remove(skin)
        for skin in modeldata.EventSkins.keys():
            modeldata.EventSkins.remove(skin)

        eventSkins = []

        numActiveEventSkins = len(modeldata.ActiveEventSkins)
        numEventSkins = len(modeldata.EventSkins)

        skin = "mage_S2"
        now = datetime.datetime.now()
        start_time_string = (now - datetime.timedelta(hours=1)).strftime("%d.%m.%Y %H:%M")
        end_time_string = (now + datetime.timedelta(hours=1)).strftime("%d.%m.%Y %H:%M")

        eventSkinInfo = EventSkin('"' + start_time_string + '" "' + end_time_string + '" "' + skin + '"')

        eventSkins.append(eventSkinInfo)

        assert len(eventSkins) == 1

        modeldata.calcEventSkin(eventSkins, env.acc)

        assert len(modeldata.ActiveEventSkins) == numActiveEventSkins + 1
        assert len(modeldata.EventSkins) == numEventSkins + 1

        eventSkins = []
        skin = "mage_S2"
        now = datetime.datetime.now()
        start_time_string = (now - datetime.timedelta(hours=2)).strftime("%d.%m.%Y %H:%M")
        end_time_string = (now - datetime.timedelta(hours=1)).strftime("%d.%m.%Y %H:%M")

        eventSkinInfo = EventSkin('"' + start_time_string + '" "' + end_time_string + '" "' + skin + '"')

        eventSkins.append(eventSkinInfo)

        assert len(eventSkins) == 1

        modeldata.calcEventSkin(eventSkins, env.acc)

        assert len(modeldata.ActiveEventSkins) == numActiveEventSkins
        assert len(modeldata.EventSkins) == numEventSkins + 1

    def reset_guild_building_test(self, env):
        modeldata = env.acc.model
        level = 5
        construction = env.add_construction(modeldata, "Guild", level)
        construction.ProductionLevel = level
        construction.ProductionState = ProductionState.Finished

        modeldata.resetGuildBuilding(env.I, env.acc)

        assert construction.ProductionState == ProductionState.Idle
        assert construction.Level == 0

    def reset_guild_building_test(self, env):
        modeldata = env.acc.model
        buildCount = len(modeldata.Buildings)
        modeldata.LordInfo.LevelOfExpansion = 1
        level = 5
        construction = env.add_construction(modeldata, "Guild", level)
        modeldata.Pocket.add(construction.id)
        modeldata.Buildings.remove(construction.id)

        assert len(modeldata.Pocket) == 1
        assert len(modeldata.Buildings) == buildCount

        modeldata.resetGuildBuilding(env.I, env.acc)

        assert construction.ProductionState == ProductionState.Idle
        assert construction.Level == 0

    def guild_bonus_members_test(self, env):
        exp = env.acc.SD.data['GuildLevels']['levels']['Item'][1]['requiredExp']
        env.acc.guilddata.GuildLevelInfo.Experience = exp

        baseMembers = env.I.Config.getMainConfig().GUILD_MAX_SIZE
        bonusMembers = int(env.acc.SD.data['GuildLevels']['levels']['Item'][1]['Bonuses']['Item'][0]['members'])

        tmpGuildLevel = env.acc.SD.data['GuildLevels']['levels']['Item'][1].copy()

        env.acc.SD.data['GuildLevels']['levels']['Item'][1]['Bonuses'] = {
            'Item': [{'members': bonusMembers, 'classType': 'GuildMemberBonus'}]}

        calcBonusMembers = env.acc.SD.getGuildMembersLimitByExp(exp, env.I)

        assert bonusMembers + baseMembers == calcBonusMembers

        env.acc.SD.data['GuildLevels']['levels']['Item'][1] = tmpGuildLevel.copy()

    def validate_guild_invite_expire_test(self, env):
        modeldata = env.acc.model

        invitesCount = len(modeldata.IncomingGuildInvites)

        inviteId = modeldata.addNewGuildInvite()
        invite = modeldata.getGuildInviteByID(inviteId)
        invite.timeToAutoDecline = time.time() - 100500
        modeldata.IncomingGuildInvites.add(invite)

        assert len(modeldata.IncomingGuildInvites) == invitesCount + 1

        modeldata.validateGuildInvites(env.acc, env.I)

        assert len(modeldata.IncomingGuildInvites) == invitesCount

    def validate_guild_invite_not_existing_guild_test(self, env):
        modeldata = env.acc.model

        invitesCount = len(modeldata.IncomingGuildInvites)

        inviteId = modeldata.addNewGuildInvite()
        invite = modeldata.getGuildInviteByID(inviteId)
        invite.guildAuid = 404
        invite.timeToAutoDecline = time.time() + 100500
        modeldata.IncomingGuildInvites.add(invite)

        assert len(modeldata.IncomingGuildInvites) == invitesCount + 1

        modeldata.validateGuildInvites(env.acc, env.I)

        assert len(modeldata.IncomingGuildInvites) == invitesCount

    def enum_2_string_test(self, env):
        assert enum2String(TutorialState, 3) == "SessionMMAccepted"
