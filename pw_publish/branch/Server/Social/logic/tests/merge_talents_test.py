import sys, math

sys.path.append('../')
sys.path.append('../..')
from logic.merge_talents import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC


class merge_talents_test:
    def merge_different_talent_1rar_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G001")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points
        added_points = env.acc.SD.getConsumptionPoints(source_talent)

        assert added_points

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert target_talent.Points == points + added_points
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_different_talent_2rar_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G062")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points
        added_points = env.acc.SD.getConsumptionPoints(source_talent)

        assert added_points
        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert target_talent.Points == points + added_points
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_different_talent_3rar_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G067")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points
        added_points = env.acc.SD.getConsumptionPoints(source_talent)

        assert added_points
        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert target_talent.Points == points + added_points
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_different_talent_4rar_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G064")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points
        added_points = env.acc.SD.getConsumptionPoints(source_talent)

        assert added_points
        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert target_talent.Points == points + added_points
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_similar_talents_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        init_points = target_talent.Points

        target_talent_level = env.acc.SD.getTalentLevel(target_talent)
        static_talent = env.acc.SD.getStaticTalent(target_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert env.acc.SD.getTalentLevel(target_talent) == target_talent_level + 1

        staticTalent = env.acc.SD.getStaticTalent(target_talent)
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])
        levelToPoints = env.acc.SD.data['TalentLevelToPointsAndRarity']['Item'][intRarity]['levelToPoints']
        points = levelToPoints['Item'][target_talent_level]

        pearl_price = env.acc.SD.getTalentMergePrice(init_points, points, static_talent)

        assert points == target_talent.Points
        assert modeldata.Resources.Perl < perl
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_similar_talents_no_pearls_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 0
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        init_points = target_talent.Points

        target_talent_level = env.acc.SD.getTalentLevel(target_talent)
        static_talent = env.acc.SD.getStaticTalent(target_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert source_talent.id in modeldata.UserInventory
        assert init_points == target_talent.Points
        assert env.acc.SD.getTalentLevel(target_talent) == target_talent_level
        assert changeList[0].get('ec') == EC.NOT_ENOUGH_RESOURCES

    def merge_similar_talent_with_progress_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        static_talent = env.acc.SD.getStaticTalent(target_talent)
        points = env.acc.SD.getTalentPointsForCurrentAndNextLevels(target_talent.Points, static_talent)

        path = 0.2
        target_talent.Points += points[1] + (points[2] - points[1]) * path
        talent_points = target_talent.Points
        points = env.acc.SD.getTalentPointsForCurrentAndNextLevels(target_talent.Points, static_talent)
        target_talent_level = env.acc.SD.getTalentLevel(target_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert env.acc.SD.getTalentLevel(target_talent) == target_talent_level + 1
        must_be_points = int(points[1] + (points[2] - points[1]) * path)
        # becouse of rounding the differ
        assert must_be_points - target_talent.Points <= 1 and must_be_points - target_talent.Points >= -1
        assert modeldata.Resources.Perl < perl

    def merge_similar_talent_with_progress_and_points_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        static_talent = env.acc.SD.getStaticTalent(target_talent)
        points = env.acc.SD.getTalentPointsForCurrentAndNextLevels(target_talent.Points, static_talent)

        path = 0.2
        source_talent_points = 15
        target_talent.Points += int(points[1] + (points[2] - points[1]) * path)
        source_talent.Points = source_talent_points
        talent_points = target_talent.Points
        points = env.acc.SD.getTalentPointsForCurrentAndNextLevels(target_talent.Points, static_talent)
        target_talent_level = env.acc.SD.getTalentLevel(target_talent)


        # pearl_price = env.acc.SD.getTalentMergePrice( target_talent.Points, target_talent.Points + added_points, static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory
        must_be_points = int(points[1] + (points[2] - points[1]) * path + source_talent_points)
        # becouse of rounding the differ
        assert must_be_points - target_talent.Points <= 1 and must_be_points - target_talent.Points >= -1
        assert modeldata.Resources.Perl < perl

    def merge_different_talent_with_soulbound(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        hero = env.add_hero(modeldata, "mowgly")
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G001")
        source_talent.Soulbound = hero
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points
        added_points = env.acc.SD.getConsumptionPoints(source_talent)

        assert added_points

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert target_talent.Points == points + added_points
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_similar_talent_with_soulbound(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        hero = env.add_hero(modeldata, "mowgly")
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G137")
        source_talent.Soulbound = hero
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        init_points = target_talent.Points

        target_talent_level = env.acc.SD.getTalentLevel(target_talent)
        static_talent = env.acc.SD.getStaticTalent(target_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert env.acc.SD.getTalentLevel(target_talent) == target_talent_level + 1

        staticTalent = env.acc.SD.getStaticTalent(target_talent)
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])
        levelToPoints = env.acc.SD.data['TalentLevelToPointsAndRarity']['Item'][intRarity]['levelToPoints']
        points = levelToPoints['Item'][target_talent_level]

        pearl_price = env.acc.SD.getTalentMergePrice(init_points, points, static_talent)

        assert points == target_talent.Points
        assert modeldata.Resources.Perl < perl
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_different_talent_with_stars_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G001")
        source_talent.Points = 100
        level = env.acc.SD.getTalentLevel(source_talent) + 1
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points
        added_points = env.acc.SD.getConsumptionPoints(source_talent) * level

        assert added_points

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert target_talent.Points == points + added_points
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_talent_with_soulbound_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        hero = env.add_hero(modeldata, "mowgly")
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G001")
        target_talent.Soulbound = hero
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points
        added_points = env.acc.SD.getConsumptionPoints(source_talent)

        assert added_points

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        #assert not source_talent.id in modeldata.UserInventory

        assert target_talent.Points == points + added_points
        assert modeldata.Resources.Perl == perl - pearl_price
        assert target_talent.Soulbound == hero

    def merge_similar_talent_to_max_points_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)

        added_points = env.acc.SD.getConsumptionPoints(source_talent)
        max_points = env.acc.SD.getTalentMaxPoints(target_talent)
        target_talent.Points = max_points - 1

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)
        points = target_talent.Points
        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert target_talent.Points == max_points
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_similar_talent_at_max_points_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)

        added_points = env.acc.SD.getConsumptionPoints(source_talent)
        max_points = env.acc.SD.getTalentMaxPoints(target_talent)
        target_talent.Points = max_points

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)
        points = target_talent.Points
        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert source_talent.id in modeldata.UserInventory

        assert target_talent.Points == max_points
        assert pearl_price == 0
        assert modeldata.Resources.Perl == perl
        assert changeList[0].get('ec') == EC.DEBUG_MESSAGE

    def merge_different_talent_to_ts_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        hero = env.add_hero(modeldata, "mowgly")
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G001")
        modeldata.UserInventory.add(source_talent)

        target_staticTalent = env.acc.SD.getStaticTalent(target_talent)
        tsSlotId = target_staticTalent['minLevel'] + 1
        hero.TalentSets[0].Talents.add(tsSlotId, target_talent)

        points = target_talent.Points
        added_points = env.acc.SD.getConsumptionPoints(source_talent)

        assert added_points
        assert len(hero.TalentSets[0].Talents) == 1

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert len(hero.TalentSets[0].Talents) == 1
        assert not source_talent.id in modeldata.UserInventory

        assert target_talent.Points == points + added_points
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_different_talent_from_ts_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        hero = env.add_hero(modeldata, "mowgly")
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G001")
        modeldata.UserInventory.add(target_talent)

        source_staticTalent = env.acc.SD.getStaticTalent(source_talent)
        tsSlotId = source_staticTalent['minLevel'] + 1
        hero.TalentSets[0].Talents.add(tsSlotId, source_talent)

        points = target_talent.Points
        added_points = env.acc.SD.getConsumptionPoints(source_talent)

        assert added_points
        assert len(hero.TalentSets[0].Talents) == 1

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert len(hero.TalentSets[0].Talents) == 1
        assert target_talent.id in modeldata.UserInventory

        assert target_talent.Points == points
        assert modeldata.Resources.Perl == perl
        assert changeList[0].get('ec') == EC.DEBUG_MESSAGE

    def merge_class_talent_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        target_talent = env.add_talent(modeldata, "G001")
        source_talent = env.add_talent(modeldata, "Archeress_A0")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert source_talent.id in modeldata.UserInventory

        assert target_talent.Points == points
        assert modeldata.Resources.Perl == perl

        assert changeList[0].get('ec') == EC.DEBUG_MESSAGE

    def merge_into_class_talent_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        target_talent = env.add_talent(modeldata, "Archeress_A0")
        source_talent = env.add_talent(modeldata, "G001")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert source_talent.id not in modeldata.UserInventory

        assert target_talent.Points > points
        assert modeldata.Resources.Perl == perl

    def merge_levelup_1_2_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        init_points = target_talent.Points

        target_talent_level = env.acc.SD.getTalentLevel(target_talent)
        static_talent = env.acc.SD.getStaticTalent(target_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert env.acc.SD.getTalentLevel(target_talent) == target_talent_level + 1

        staticTalent = env.acc.SD.getStaticTalent(target_talent)
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])
        levelToPoints = env.acc.SD.data['TalentLevelToPointsAndRarity']['Item'][intRarity]['levelToPoints']
        points = levelToPoints['Item'][target_talent_level]

        price_table = env.acc.SD.data['TalentMergePriceToLevelAndRarity']['Item'][intRarity]['levelToPrice']
        pearl_price = price_table['Item'][target_talent_level]

        assert points == target_talent.Points
        assert modeldata.Resources.Perl < perl
        assert pearl_price > 0
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_levelup_beforelast_last_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)

        max_points = env.acc.SD.getTalentMaxPoints(target_talent)
        target_talent.Points = max_points - 1

        init_points = target_talent.Points

        target_talent_level = env.acc.SD.getTalentLevel(target_talent)
        static_talent = env.acc.SD.getStaticTalent(target_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert env.acc.SD.getTalentLevel(target_talent) == target_talent_level + 1

        staticTalent = env.acc.SD.getStaticTalent(target_talent)
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])
        levelToPoints = env.acc.SD.data['TalentLevelToPointsAndRarity']['Item'][intRarity]['levelToPoints']
        points = levelToPoints['Item'][target_talent_level]

        price_table = env.acc.SD.data['TalentMergePriceToLevelAndRarity']['Item'][intRarity]['levelToPrice']
        pearl_price = price_table['Item'][target_talent_level]

        assert points == target_talent.Points
        assert modeldata.Resources.Perl < perl
        assert pearl_price > 0
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_no_levelup_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G001")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points
        added_points = env.acc.SD.getConsumptionPoints(source_talent)

        assert added_points

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        assert target_talent.Points == points + added_points
        assert pearl_price == 0
        assert modeldata.Resources.Perl == perl

    def merge_1_lvl_to_max_similar_talents_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        init_points = target_talent.Points

        max_points = env.acc.SD.getTalentMaxPoints(target_talent)

        target_talent_level = env.acc.SD.getTalentLevel(target_talent)
        static_talent = env.acc.SD.getStaticTalent(target_talent)
        intRarity = getattr(ETalentRarity, static_talent['rarity'])
        pointsCap = int(env.acc.SD.data['TalentLevelToPointsAndRarity']['Item'][intRarity]['refinePointsCap'])
        max_levels = env.acc.SD.getTalentLevelByPoints(pointsCap, static_talent)

        source_talents_string = str(source_talent.id)
        count = 1
        for i in xrange(1, max_levels):
            count += 1
            source_talent = env.add_talent(modeldata, "G137")
            modeldata.UserInventory.add(source_talent)
            source_talents_string += ", " + str(source_talent.id)

        test = len(modeldata.UserInventory)
        requests = [
            (Merge_talents, MergeTalentsRequest(modeldata, {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                            "source_talents": ["" + source_talents_string + ""],
                                                            "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert test - count == len(modeldata.UserInventory)

        lvl = env.acc.SD.getTalentLevel(target_talent)
        assert env.acc.SD.getTalentLevel(target_talent) == target_talent_level + max_levels

        staticTalent = env.acc.SD.getStaticTalent(target_talent)
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])

        price_table = env.acc.SD.data['TalentMergePriceToLevelAndRarity']['Item'][intRarity]['levelToPrice']
        pearl_price = 0
        i = 0
        while i < max_levels:
            pearl_price += price_table['Item'][i]
            i += 1

        assert max_points == target_talent.Points
        assert modeldata.Resources.Perl < perl
        assert pearl_price > 0
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_1_lvl_to_max_different_talents_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)

        source_talent = env.add_talent(modeldata, "G001")
        modeldata.UserInventory.add(source_talent)
        added_points = env.acc.SD.getConsumptionPoints(source_talent)
        assert added_points
        max_points = env.acc.SD.getTalentMaxPoints(target_talent)

        points = added_points
        source_talents_string = str(source_talent.id)
        count = 1
        while points < max_points:
            count += 1
            source_talent = env.add_talent(modeldata, "G001")
            modeldata.UserInventory.add(source_talent)
            source_talents_string += ", " + str(source_talent.id)
            points += added_points

        test = len(modeldata.UserInventory)
        init_points = target_talent.Points

        target_talent_level = env.acc.SD.getTalentLevel(target_talent)
        static_talent = env.acc.SD.getStaticTalent(target_talent)
        intRarity = getattr(ETalentRarity, static_talent['rarity'])
        pointsCap = int(env.acc.SD.data['TalentLevelToPointsAndRarity']['Item'][intRarity]['refinePointsCap'])
        max_levels = env.acc.SD.getTalentLevelByPoints(pointsCap, static_talent)

        requests = [
            (Merge_talents, MergeTalentsRequest(modeldata, {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                            "source_talents": ["" + source_talents_string + ""],
                                                            "aftercontext": ["false"]}, False))]
        startTime = time.time()
        changeList = env.execActions(requests)
        endTime = time.time()
        time_spent = endTime - startTime

        assert time_spent / count < 0.01

        assert target_talent.id in modeldata.UserInventory

        #assert test - count == len(modeldata.UserInventory)

        lvl = env.acc.SD.getTalentLevel(target_talent)
        assert lvl == target_talent_level + max_levels

        staticTalent = env.acc.SD.getStaticTalent(target_talent)
        intRarity = getattr(ETalentRarity, staticTalent['rarity'])

        price_table = env.acc.SD.data['TalentMergePriceToLevelAndRarity']['Item'][intRarity]['levelToPrice']
        pearl_price = 0
        i = 0
        while i < max_levels:
            pearl_price += price_table['Item'][i]
            i += 1

        assert max_points == target_talent.Points
        assert modeldata.Resources.Perl < perl
        assert pearl_price > 0
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_multiple_talents_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10

        target_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)

        source_talent1 = env.add_talent(modeldata, "G137")
        source_talent2 = env.add_talent(modeldata, "G137")
        source_talent3 = env.add_talent(modeldata, "G001")
        source_talent4 = env.add_talent(modeldata, "G001")
        modeldata.UserInventory.add(source_talent1)
        modeldata.UserInventory.add(source_talent2)
        modeldata.UserInventory.add(source_talent3)
        modeldata.UserInventory.add(source_talent4)

        points = target_talent.Points
        static_talent = env.acc.SD.getStaticTalent(target_talent)

        added_points1 = env.acc.SD.getConsumptionPoints(source_talent3)
        added_points2 = env.acc.SD.getConsumptionPoints(source_talent4)
        total_points = target_talent.Points + added_points1 + added_points2

        points = env.acc.SD.getTalentPointsForCurrentAndNextLevels(total_points, static_talent)
        done = float(total_points - points[0]) / float(points[1] - points[0])
        path = points[1] + done * (points[2] - points[1])
        total_points = path

        points = env.acc.SD.getTalentPointsForCurrentAndNextLevels(total_points, static_talent)
        done = (total_points - points[0]) / (points[1] - points[0])
        path = points[1] + done * (points[2] - points[1])
        total_points = int(path)

        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, total_points, static_talent)
        test = len(modeldata.UserInventory)
        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent1.id) + ", " + str(
                                                             source_talent2.id) + ", " + str(
                                                             source_talent3.id) + ", " + str(source_talent4.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert test - 4 == len(modeldata.UserInventory)

        assert target_talent.Points == total_points
        assert pearl_price > 0
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_multiple_talents_levelup_while_consumption_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 1000

        target_talent = env.add_talent(modeldata, "G001")
        modeldata.UserInventory.add(target_talent)

        source_talent1 = env.add_talent(modeldata, "G337")
        source_talent2 = env.add_talent(modeldata, "G337")
        source_talent3 = env.add_talent(modeldata, "G001")
        source_talent4 = env.add_talent(modeldata, "G001")
        modeldata.UserInventory.add(source_talent1)
        modeldata.UserInventory.add(source_talent2)
        modeldata.UserInventory.add(source_talent3)
        modeldata.UserInventory.add(source_talent4)

        points = target_talent.Points
        #print points
        static_talent = env.acc.SD.getStaticTalent(target_talent)

        added_points1 = env.acc.SD.getConsumptionPoints(source_talent1)
        added_points2 = env.acc.SD.getConsumptionPoints(source_talent2)
        total_points = target_talent.Points + added_points1 + added_points2

        points = env.acc.SD.getTalentPointsForCurrentAndNextLevels(total_points, static_talent)
        done = float(total_points - points[0]) / float(points[1] - points[0])
        path = points[1] + done * (points[2] - points[1])
        total_points = path

        points = env.acc.SD.getTalentPointsForCurrentAndNextLevels(total_points, static_talent)
        done = (total_points - points[0]) / (points[1] - points[0])
        path = points[1] + done * (points[2] - points[1])
        total_points = int(path)

        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, total_points, static_talent)
        test = len(modeldata.UserInventory)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent1.id) + ", " + str(
                                                             source_talent2.id) + ", " + str(
                                                             source_talent3.id) + ", " + str(source_talent4.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert test - 4 == len(modeldata.UserInventory)

        #print target_talent.Points
        #print total_points
        assert target_talent.Points == total_points

        assert pearl_price > 0
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_multiple_different_talents_with_too_many_points_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talentsBefore = len(modeldata.UserInventory)
        target_talent = env.add_talent(modeldata, "G137")
        source_talent1 = env.add_talent(modeldata, "G137")
        source_talent2 = env.add_talent(modeldata, "G137")
        source_talent3 = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent1)
        modeldata.UserInventory.add(source_talent2)
        modeldata.UserInventory.add(source_talent3)

        source_talents_string = str(source_talent1.id) + "," + str(source_talent2.id) + "," + str(source_talent3.id)
        count = 0
        for i in xrange(0, 20):
            count += 1
            source_talent = env.add_talent(modeldata, "G001")
            modeldata.UserInventory.add(source_talent)
            source_talents_string += ", " + str(source_talent.id)

        max_points = env.acc.SD.getTalentMaxPoints(target_talent)

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(0, max_points, static_talent)
        points = target_talent.Points
        requests = [
            (Merge_talents, MergeTalentsRequest(modeldata, {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                            "source_talents": ["" + source_talents_string + ""], "aftercontext": ["false"]},
                                                False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent1.id in modeldata.UserInventory
        assert not source_talent2.id in modeldata.UserInventory
        assert len(modeldata.UserInventory) == talentsBefore + 6

        assert target_talent.Points == max_points
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_multiple_talents_with_too_many_points_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G137")
        source_talent1 = env.add_talent(modeldata, "G137")
        source_talent2 = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent1)
        modeldata.UserInventory.add(source_talent2)

        max_points = env.acc.SD.getTalentMaxPoints(target_talent)

        target_talent.Points = max_points - 1

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(max_points - 1, max_points, static_talent)
        points = target_talent.Points
        requests = [
            (Merge_talents, MergeTalentsRequest(modeldata, {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                            "source_talents": ["" + str(source_talent1.id) + "," + str(
                                                                source_talent2.id) + ""], "aftercontext": ["false"]},
                                                False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent1.id in modeldata.UserInventory
        assert source_talent2.id in modeldata.UserInventory

        assert target_talent.Points == max_points
        assert modeldata.Resources.Perl == perl - pearl_price

    def merge_different_talent_to_ts_check_force_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        hero = env.add_hero(modeldata, "mowgly")
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(source_talent)

        target_staticTalent = env.acc.SD.getStaticTalent(target_talent)
        tsSlotId = target_staticTalent['minLevel'] + 1
        hero.TalentSets[0].Talents.add(tsSlotId, target_talent.id)
        target_talent.Owner = hero
        target_talent.ParentTalentSets.add(0, hero.TalentSets[0].id )

        points = target_talent.Points
        added_points = env.acc.SD.getTalentPointsForCurrentAndNextLevels(target_talent.Points, target_staticTalent)[1]

        assert added_points
        assert len(hero.TalentSets[0].Talents) == 1
        lvl = env.acc.SD.getTalentLevel(target_talent)
        hero.CalcForce(modeldata, env.I.WS, env.acc, hero.ActiveTalentSet)
        startForce = hero.TalentSets[0].Force
        assert startForce > 0.0

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, target_talent.Points + added_points,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert len(hero.TalentSets[0].Talents) == 1
        assert source_talent.id not in modeldata.UserInventory

        assert target_talent.Points == points + added_points
        assert modeldata.Resources.Perl == perl - pearl_price
        assert env.acc.SD.getTalentLevel(target_talent) == lvl + 1
        assert hero.TalentSets[0].Force > startForce

    def merge_different_talent_with_bonus_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        consumptionBonusConstant = 10
        consumptionBonusPercent = 10
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G001")

        staticTargetTalent = env.acc.SD.getStaticTalent(target_talent)
        staticSourceTalent = env.acc.SD.getStaticTalent(source_talent)
        tmpBonusConstant = staticSourceTalent['consumptionBonus']['constant']
        tmpBonusPercent = staticSourceTalent['consumptionBonus']['percent']
        staticSourceTalent['consumptionBonus']['constant'] = consumptionBonusConstant
        staticSourceTalent['consumptionBonus']['percent'] = consumptionBonusPercent
        target_talent_max_points = env.acc.SD.getTalentMaxPoints(target_talent)

        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points
        added_points = env.acc.SD.getConsumptionPoints(source_talent)
        bonus = staticSourceTalent['consumptionBonus']['constant']
        percent = round(target_talent_max_points * staticSourceTalent['consumptionBonus']['percent'] / 100.0)

        assert added_points

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, points + added_points + bonus + percent,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent.id in modeldata.UserInventory

        percent = round(target_talent_max_points * float(consumptionBonusPercent) / float(100))
        assert target_talent.Points == points + added_points + bonus + percent
        assert modeldata.Resources.Perl == perl - pearl_price

        staticSourceTalent['consumptionBonus']['constant'] = tmpBonusConstant
        staticSourceTalent['consumptionBonus']['percent'] = tmpBonusPercent

    def merge_many_different_talent_with_bonus_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 10
        consumptionBonusConstant = 10
        consumptionBonusPercent = 0
        target_talent = env.add_talent(modeldata, "G100")
        source_talent1 = env.add_talent(modeldata, "G052")
        source_talent2 = env.add_talent(modeldata, "G150")

        staticTargetTalent = env.acc.SD.getStaticTalent(target_talent)
        staticSourceTalent1 = env.acc.SD.getStaticTalent(source_talent1)
        staticSourceTalent2 = env.acc.SD.getStaticTalent(source_talent2)
        tmpBonusConstant = staticSourceTalent1['consumptionBonus']['constant']
        tmpBonusPercent = staticSourceTalent1['consumptionBonus']['percent']
        staticSourceTalent2['consumptionBonus']['constant'] = consumptionBonusConstant
        staticSourceTalent2['consumptionBonus']['percent'] = consumptionBonusPercent
        target_talent_max_points = env.acc.SD.getTalentMaxPoints(target_talent)

        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent1)
        modeldata.UserInventory.add(source_talent2)
        points = target_talent.Points
        added_points1 = env.acc.SD.getConsumptionPoints(source_talent1)
        added_points2 = env.acc.SD.getConsumptionPoints(source_talent2)
        added_points = added_points1 + added_points2
        bonus = int(staticSourceTalent2['consumptionBonus']['constant'])
        percent = round(target_talent_max_points * staticSourceTalent2['consumptionBonus']['percent'] / 100.0)

        assert added_points

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(target_talent.Points, points + added_points + bonus + percent,
                                                     static_talent)

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent1.id) + ", " + str(
                                                             source_talent2.id) + ""], "aftercontext": ["false"]},
                                                        False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert not source_talent1.id in modeldata.UserInventory
        assert not source_talent2.id in modeldata.UserInventory

        percent = round(target_talent_max_points * float(consumptionBonusPercent) / float(100))
        assert target_talent.Points == points + added_points + bonus + percent
        assert modeldata.Resources.Perl == perl - pearl_price

        staticSourceTalent2['consumptionBonus']['constant'] = tmpBonusConstant
        staticSourceTalent2['consumptionBonus']['percent'] = tmpBonusPercent

    def merge_talent_two_levels_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G137")
        source_talent1 = env.add_talent(modeldata, "G001")
        source_talent2 = env.add_talent(modeldata, "G137")
        source_talent3 = env.add_talent(modeldata, "G137")
        source_talent4 = env.add_talent(modeldata, "G137")
        source_talent5 = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent1)
        modeldata.UserInventory.add(source_talent2)
        modeldata.UserInventory.add(source_talent3)
        modeldata.UserInventory.add(source_talent4)
        modeldata.UserInventory.add(source_talent5)

        assert env.acc.SD.getTalentLevel(target_talent) == 0

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent1.id) + ", " + str(
                                                             source_talent2.id) + ", " + str(
                                                             source_talent3.id) + ", " + str(
                                                             source_talent4.id) + ", " + str(source_talent5.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert source_talent1.id in modeldata.UserInventory
        assert source_talent2.id not in modeldata.UserInventory
        assert source_talent3.id not in modeldata.UserInventory
        assert source_talent4.id not in modeldata.UserInventory
        assert source_talent5.id not in modeldata.UserInventory

        assert env.acc.SD.getTalentLevel(target_talent) == 4

    def merge_talent_to_cap_reverse_order_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G137")
        source_talent1 = env.add_talent(modeldata, "G138")
        source_talent2 = env.add_talent(modeldata, "G138")
        source_talent3 = env.add_talent(modeldata, "G138")
        source_talent4 = env.add_talent(modeldata, "G138")
        source_talent5 = env.add_talent(modeldata, "G138")
        source_talent6 = env.add_talent(modeldata, "G138")
        source_talent7 = env.add_talent(modeldata, "G138")
        source_talent8 = env.add_talent(modeldata, "G138")
        source_talent9 = env.add_talent(modeldata, "G137")

        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent1)
        modeldata.UserInventory.add(source_talent2)
        modeldata.UserInventory.add(source_talent3)
        modeldata.UserInventory.add(source_talent4)
        modeldata.UserInventory.add(source_talent5)
        modeldata.UserInventory.add(source_talent6)
        modeldata.UserInventory.add(source_talent7)
        modeldata.UserInventory.add(source_talent8)
        modeldata.UserInventory.add(source_talent9)

        assert env.acc.SD.getTalentLevel(target_talent) == 0

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent1.id) + ", " + str(
                                                             source_talent2.id) + ", " + str(
                                                             source_talent3.id) + ", " + str(
                                                             source_talent4.id) + ", " + str(
                                                             source_talent5.id) + ", " + str(
                                                             source_talent6.id) + ", " + str(
                                                             source_talent7.id) + ", " + str(
                                                             source_talent8.id) + ", " + str(source_talent9.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert source_talent1.id not in modeldata.UserInventory
        assert source_talent2.id not in modeldata.UserInventory
        assert source_talent3.id not in modeldata.UserInventory
        assert source_talent4.id not in modeldata.UserInventory
        assert source_talent5.id not in modeldata.UserInventory
        assert source_talent6.id not in modeldata.UserInventory
        assert source_talent7.id not in modeldata.UserInventory
        assert source_talent8.id not in modeldata.UserInventory
        assert source_talent9.id not in modeldata.UserInventory

        assert env.acc.SD.getTalentLevel(target_talent) == 2

    def merge_guild_talent_as_source_test(self, env):
        modeldata = env.acc.model
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G001")
        gbi, gbi_id = modeldata.newGuildBankInfo()
        source_talent.GuildBankInfo = gbi_id
        source_talent.GuildBankInfo.OwnerId = env.acc.auid + 1
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert changeList[0].get("ec") == EC.GUILD_BANK_TALENT_IMPROPER_USE
        assert target_talent.id in modeldata.UserInventory
        assert source_talent.id in modeldata.UserInventory

        assert target_talent.Points == points

    def merge_self_guild_talent_as_source_test(self, env):
        modeldata = env.acc.model
        target_talent = env.add_talent(modeldata, "G137")
        source_talent = env.add_talent(modeldata, "G001")
        gbi, gbi_id = modeldata.newGuildBankInfo()
        source_talent.GuildBankInfo = gbi_id
        source_talent.GuildBankInfo.OwnerId = env.acc.auid
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent)
        points = target_talent.Points

        added_points = env.acc.SD.getConsumptionPoints(source_talent)

        assert added_points

        requests = [(Merge_talents, MergeTalentsRequest(modeldata,
                                                        {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                         "source_talents": ["" + str(source_talent.id) + ""],
                                                         "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        assert target_talent.id in modeldata.UserInventory
        assert source_talent.id not in modeldata.UserInventory

        assert target_talent.Points == points + added_points

    def merge_talents_from_talentset_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G137")
        source_talent1 = env.add_talent(modeldata, "G137")
        hero = env.add_hero(modeldata, "mowgly")
        source_talent1.Owner = hero
        modeldata.UserInventory.add(target_talent)
        modeldata.UserInventory.add(source_talent1)

        max_points = env.acc.SD.getTalentMaxPoints(target_talent)

        target_talent.Points = max_points - 1

        static_talent = env.acc.SD.getStaticTalent(target_talent)
        pearl_price = env.acc.SD.getTalentMergePrice(max_points - 1, max_points, static_talent)
        points = target_talent.Points
        requests = [
            (Merge_talents, MergeTalentsRequest(modeldata, {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                            "source_talents": ["" + str(source_talent1.id)  + ""], "aftercontext": ["false"]},
                                                False))]
        changeList = env.execActions(requests)
        assert changeList[0].get('ec') == EC.GUILD_BANK_TALENT_IMPROPER_USE

        #assert target_talent.id in modeldata.UserInventory
        #assert not source_talent1.id in modeldata.UserInventory


        #assert target_talent.Points == max_points
        #assert modeldata.Resources.Perl == perl - pearl_price
