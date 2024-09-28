# -*- coding: utf-8 -*-

import sys

sys.path.append('../')
sys.path.append('../..')
from logic.reforge_talent import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC


class reforge_talent_test:
    def reforge_talent_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talent = env.add_talent(modeldata, "G381")  ##G326
        talent.Points = 20
        talent.IsNew = False
        modeldata.UserInventory.add(talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforging"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(talent)

        requests = [(Reforge_talent, ReforgeTalentRequest(modeldata, {"talents": ["" + str(talent.id) + ""],
                                                                      "selectedOrangeSet": [], "selectedRedSet": [],
                                                                      "aftercontext": ["false"]},
                                                          False))]  ##VampirePack
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(talent)

        price = env.acc.SD.data['ReforgeTalentPrices'][static_talent_before["rarity"]]['rerollPrices']['Item'][0][
            'priceWithoutSetFilter']
        pricePerl = price['Perl']

        assert talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] != static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert talent.Points == 0
        assert talent.IsNew
        assert modeldata.Resources.Perl == perl - pricePerl

    def reforge_red_talent_test(self, env):
        modeldata = env.acc.model
        redPerl = modeldata.Resources.RedPerl = 100
        talent = env.add_talent(modeldata, "G597")
        talent.Points = 20
        talent.IsNew = False
        modeldata.UserInventory.add(talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforging"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(talent)

        requests = [(Reforge_talent, ReforgeTalentRequest(modeldata, {"talents": ["" + str(talent.id) + ""],
                                                                      "selectedOrangeSet": [], "selectedRedSet": [],
                                                                      "aftercontext": ["false"]},
                                                          False))]  ##VampirePack
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(talent)

        price = env.acc.SD.data['ReforgeTalentPrices'][static_talent_before["rarity"]]['rerollPrices']['Item'][0]['priceWithoutSetFilter']
        priceRedPerl = price['RedPerl']

        assert static_talent_after["persistentId"] != static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert talent.Points == 0
        assert talent.IsNew
        assert modeldata.Resources.RedPerl == redPerl - priceRedPerl

    def reforge_exclusive_talent_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talent = env.add_talent(modeldata, "G296")
        talent.Points = 20
        talent.IsNew = False
        modeldata.UserInventory.add(talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(talent)

        requests = [(Reforge_talent,
                     ReforgeTalentRequest(modeldata,
                                          {
                                              "talents": ["" + str(talent.id) + ""],
                                              "aftercontext": ["false"]
                                          },
                                          False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(talent)

        price = env.acc.SD.data['ReforgeTalentPrices'][static_talent_before["rarity"]]['rerollPrices']['Item'][0][
            'priceWithoutSetFilter']
        pricePerl = price['Perl']

        assert talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] != static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert talent.Points == 0
        assert talent.IsNew
        assert modeldata.Resources.Perl == perl - pricePerl

    def reforge_talent_test_small_transmutation_level(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talent = env.add_talent(modeldata, "G012")
        talent.Points = 20
        talent.IsNew = False
        modeldata.UserInventory.add(talent)

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             int(staticConstruction["requiredLeveForReforging"]) - 1)
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(talent)

        requests = [(Reforge_talent, ReforgeTalentRequest(modeldata, {"talents": ["" + str(talent.id) + ""],
                                                                      "selectedOrangeSet": ["VampirePack"],
                                                                      "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(talent)

        assert talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] == static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert talent.Points == 20
        assert not talent.IsNew
        assert modeldata.Resources.Perl == perl

    def reforge_talent_test_small_transmutation_level_for_exclusive_talents(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talent = env.add_talent(modeldata, "G296")
        talent.Points = 20
        talent.IsNew = False
        modeldata.UserInventory.add(talent)

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             int(staticConstruction["requiredLeveForReforgingExclusiveTalents"]) - 1)
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(talent)

        requests = [(Reforge_talent,
                     ReforgeTalentRequest(modeldata, {"talents": ["" + str(talent.id) + ""],
                                                      "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(talent)

        assert talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] == static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert talent.Points == 20
        assert not talent.IsNew
        assert modeldata.Resources.Perl == perl

    def reforge_talent_test_different_rars(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talent1 = env.add_talent(modeldata, "G445")
        talent2 = env.add_talent(modeldata, "G381")
        talent1.Points = talent2.Points = 20
        talent1.IsNew = talent2.IsNew = False
        modeldata.UserInventory.add(talent1)
        modeldata.UserInventory.add(talent2)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent1_before = env.acc.SD.getStaticTalent(talent1)
        static_talent2_before = env.acc.SD.getStaticTalent(talent2)

        requests = [(Reforge_talent, ReforgeTalentRequest(modeldata, {
            "talents": ["" + str(talent1.id) + ", " + str(talent2.id) + ""],
            "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent1_after = env.acc.SD.getStaticTalent(talent1)
        static_talent2_after = env.acc.SD.getStaticTalent(talent2)

        price1 = env.acc.SD.data['ReforgeTalentPrices'][static_talent1_before["rarity"]]['rerollPrices']['Item'][0][
            'priceWithoutSetFilter']
        pricePerl1 = price1['Perl']

        price2 = env.acc.SD.data['ReforgeTalentPrices'][static_talent2_before["rarity"]]['rerollPrices']['Item'][0][
            'priceWithoutSetFilter']
        pricePerl2 = price2['Perl']

        assert talent1.id in modeldata.UserInventory
        assert static_talent1_after["persistentId"] != static_talent1_before["persistentId"]
        assert static_talent1_after["rarity"] == static_talent1_before["rarity"]
        assert talent1.Points == 0
        assert talent1.IsNew

        assert talent2.id in modeldata.UserInventory
        assert static_talent2_after["persistentId"] != static_talent2_before["persistentId"]
        assert static_talent2_after["rarity"] == static_talent2_before["rarity"]
        assert talent2.Points == 0
        assert talent2.IsNew

        assert modeldata.Resources.Perl == perl - pricePerl1 - pricePerl2

    def reforge_talent_test_different_rars_bad_talents(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talent1 = env.add_talent(modeldata, "G012")
        talent2 = env.add_talent(modeldata, "BBB")
        talent1.Points = talent2.Points = 20
        talent1.IsNew = talent2.IsNew = False
        modeldata.UserInventory.add(talent1)
        modeldata.UserInventory.add(talent2)

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent1_before = env.acc.SD.getStaticTalent(talent1)
        static_talent2_before = env.acc.SD.getStaticTalent(talent2)

        requests = [(Reforge_talent, ReforgeTalentRequest(modeldata, {
            "talents": ["" + str(talent1.id) + ", " + str(talent2.id) + ""], "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent1_after = env.acc.SD.getStaticTalent(talent1)
        static_talent2_after = env.acc.SD.getStaticTalent(talent2)

        assert talent1.id in modeldata.UserInventory
        assert static_talent1_after["persistentId"] == static_talent1_before["persistentId"]
        assert static_talent1_after["rarity"] == static_talent1_before["rarity"]
        assert talent1.Points == 20
        assert not talent1.IsNew

        assert talent2.id in modeldata.UserInventory
        assert static_talent2_after == static_talent2_before
        assert talent2.Points == 20
        assert not talent2.IsNew

        assert modeldata.Resources.Perl == perl

    def reforge_talent_test_different_rars_bad_rar(self, env):
        # no more bad rars
        return
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talent1 = env.add_talent(modeldata, "G015")
        talent2 = env.add_talent(modeldata, "G296")
        talent1.Points = talent2.Points = 20
        talent1.IsNew = talent2.IsNew = False
        modeldata.UserInventory.add(talent1)
        modeldata.UserInventory.add(talent2)

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent1_before = env.acc.SD.getStaticTalent(talent1)
        static_talent2_before = env.acc.SD.getStaticTalent(talent2)

        requests = [(Reforge_talent, ReforgeTalentRequest(modeldata, {
            "talents": ["" + str(talent1.id) + ", " + str(talent2.id) + ""], "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent1_after = env.acc.SD.getStaticTalent(talent1)
        static_talent2_after = env.acc.SD.getStaticTalent(talent2)

        assert talent1.id in modeldata.UserInventory
        assert static_talent1_after["persistentId"] == static_talent1_before["persistentId"]
        assert static_talent1_after["rarity"] == static_talent1_before["rarity"]
        assert talent1.Points == 20
        assert not talent1.IsNew

        assert talent2.id in modeldata.UserInventory
        assert static_talent2_after["persistentId"] == static_talent2_before["persistentId"]
        assert static_talent2_after["rarity"] == static_talent2_before["rarity"]
        assert talent2.Points == 20
        assert not talent2.IsNew

        assert modeldata.Resources.Perl == perl

    def reforge_talent_with_guild_bank_info_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talent = env.add_talent(modeldata, "G012")
        talent.Points = 20
        talent.IsNew = False
        gbi, gbi_id = modeldata.newGuildBankInfo()
        talent.GuildBankInfo = gbi_id
        talent.GuildBankInfo.OwnerId = env.acc.auid + 1
        modeldata.UserInventory.add(talent)

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforging"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(talent)

        requests = [(Reforge_talent,
                     ReforgeTalentRequest(modeldata, {"talents": ["" + str(talent.id) + ""], "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(talent)

        assert talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] == static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert talent.Points == 20
        assert not talent.IsNew
        assert modeldata.Resources.Perl == perl

    def reforge_talent_test_not_enough_resources(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 0
        talent = env.add_talent(modeldata, "G193")
        talent.Points = 20
        talent.IsNew = False
        modeldata.UserInventory.add(talent)

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforging"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(talent)

        requests = [(Reforge_talent,
                     ReforgeTalentRequest(modeldata, {"talents": ["" + str(talent.id) + ""], "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(talent)

        assert talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] == static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert talent.Points == 20
        assert not talent.IsNew
        assert modeldata.Resources.Perl == perl

    def reforge_talent_test_reforge_not_allowed_by_config(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 2000
        talent = env.add_talent(modeldata, "G012")
        talent.Points = 20
        talent.IsNew = False
        modeldata.UserInventory.add(talent)
        env.acc.getConfig().IS_REFORGE_ACTIVE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforging"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(talent)

        requests = [(Reforge_talent,
                     ReforgeTalentRequest(modeldata, {"talents": ["" + str(talent.id) + ""], "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(talent)

        assert talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] == static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert talent.Points == 20
        assert not talent.IsNew
        assert modeldata.Resources.Perl == perl

    # todo: kramarov: пока что берем цены из xml. цены из gm-tool игнорим
    def __reforge_talent_test_withEvent(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talent = env.add_talent(modeldata, "G012")  ##G326
        talent.Points = 20
        talent.IsNew = False
        modeldata.UserInventory.add(talent)

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforging"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(talent)


        event = {'persistentId': 3, 'defaultValue': {}, 'enabled': True,
                 'startTime': int(time.time()) - 60 *60, 'endTime': int(time.time()) + 60 *60, 'type': 8,
                 'newValue': {'listReforgeTalentPrices': [
                                  {'rerollPrice': 5, 'upgradePrice': 10, 'talentsToUpgrade': 2, 'rarity': 3},
                                  {'rerollPrice': 9, 'upgradePrice': 10, 'talentsToUpgrade': 4, 'rarity': 4},
                                  {'rerollPrice': 9, 'upgradePrice': 2,  'talentsToUpgrade': 1, 'rarity': 5}]
                    }
                 }

        if event["enabled"] and event["startTime"] < int(time.time()) < event["endTime"]:
            info("Loading event %r", event)
            changes, self.needUpdateSeeds = env.I.Config.applyEvent(env.I.SD, event)


        requests = [(Reforge_talent, ReforgeTalentRequest(modeldata, {"talents": ["" + str(talent.id) + ""],
                                                                      "selectedOrangeSet": [], "selectedRedSet": [],
                                                                      "aftercontext": ["false"]}, False))]  ##VampirePack
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(talent)
        pricePerl, priceRedPerl = modeldata.getReforgePriceByRarity(env.acc.getConfig(), static_talent_before["rarity"],
                                                                    0)

        assert talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] != static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert talent.Points == 0
        assert talent.IsNew
        assert modeldata.Resources.Perl == perl - pricePerl

        env.I.Config.setEventDefalutValue(env.I.SD, event)
        changes, self.needUpdateSeeds = env.I.Config.applyEvent(env.I.SD, event)
        changes = env.I.Config.revertEvent(env.I.SD, event)

    def reforge_pointed_talent_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talent = env.add_talent(modeldata, "G296")
        talent.Points = 6001    # 5
        talent.IsNew = False
        modeldata.UserInventory.add(talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = True

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(talent)

        requests = [(Reforge_talent,
                     ReforgeTalentRequest(modeldata,
                                          {
                                              "talents": ["" + str(talent.id) + ""],
                                              "aftercontext": ["false"]
                                          },
                                          False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(talent)

        price = env.acc.SD.data['ReforgeTalentPrices'][static_talent_before["rarity"]]['rerollPrices']['Item'][1][
            'priceWithoutSetFilter']
        pricePerl = price['Perl']

        assert talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] != static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert talent.Points == 6001
        assert talent.IsNew
        env.printAssert(modeldata.Resources.Perl, 85)


    def reforge_pointed_talent_from_set_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talent = env.add_talent(modeldata, "G397")
        talent.Points = 20
        talent.IsNew = False
        modeldata.UserInventory.add(talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = True
        env.acc.getConfig().ALLOW_REROLL_FROM_SET_FOR_UPGRADED_TALENTS_ON_REFORGE = True

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(talent)

        requests = [(Reforge_talent,
                     ReforgeTalentRequest(modeldata,
                                          {
                                              "talents": ["" + str(talent.id) + ""],
                                              "aftercontext": ["false"],
                                              "selectedOrangeSet": ['Resource']
                                          },
                                          False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(talent)

        price = env.acc.SD.data['ReforgeTalentPrices'][static_talent_before["rarity"]]['rerollPrices']['Item'][0][
            'priceWithSetFilter']
        pricePerl = price['Perl']

        assert talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] != static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert talent.Points == 20
        assert talent.IsNew
        assert modeldata.Resources.Perl == perl - pricePerl
        assert crc32(static_talent_after["persistentId"]) in env.acc.SD.TalentsByPack['Resource']


    def reforge_pointed_talent_from_set_skip_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        talent = env.add_talent(modeldata, "G397")
        talent.Points = 20
        talent.IsNew = False
        modeldata.UserInventory.add(talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = True
        env.acc.getConfig().ALLOW_REROLL_FROM_SET_FOR_UPGRADED_TALENTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(talent)

        requests = [(Reforge_talent,
                     ReforgeTalentRequest(modeldata,
                                          {
                                              "talents": ["" + str(talent.id) + ""],
                                              "aftercontext": ["false"],
                                              "selectedOrangeSet": ['Resource']
                                          },
                                          False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(talent)

        assert static_talent_after["persistentId"] == static_talent_before["persistentId"]

