import sys

sys.path.append('../')
sys.path.append('../..')
from logic.reforge_upgrade_talent import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC


class reforge_upgrade_talent_test:

    def reforge_upgrade_talent_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G260")
        target_talent.Points = 20
        target_talent.IsNew = False
        modeldata.UserInventory.add(target_talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforging"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(target_talent)
        assert static_talent_before["rarity"] == "magnificent"

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata,
                                                                         {"talents": ["" + str(target_talent.id) + ""],
                                                                          "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(target_talent)

        price = env.acc.SD.data['ReforgeTalentPrices'][static_talent_before["rarity"]]['upgradePrice']
        pricePerl = price['Perl']

        assert target_talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] != static_talent_before["persistentId"]
        env.printAssert(static_talent_after["rarity"], "exclusive")
        assert target_talent.Points == 0
        assert target_talent.IsNew
        assert modeldata.Resources.Perl == perl - pricePerl

    def reforge_upgrade_magnificent_talent_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G272")
        target_talent.Points = 20
        target_talent.IsNew = False
        modeldata.UserInventory.add(target_talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(target_talent)

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata,
                                                                         {"talents": ["" + str(target_talent.id) + ""],
                                                                          "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(target_talent)
        price = env.acc.SD.data['ReforgeTalentPrices'][static_talent_before["rarity"]]['upgradePrice']
        pricePerl = price['Perl']

        assert target_talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] != static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == "exclusive"
        assert target_talent.Points == 0
        assert target_talent.IsNew
        assert modeldata.Resources.Perl == perl - pricePerl

    def reforge_upgrade_outstanding_talent_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G463")
        target_talent.Points = 20
        target_talent.IsNew = False
        modeldata.UserInventory.add(target_talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(target_talent)

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata,
                                                                         {"talents": ["" + str(target_talent.id) + ""],
                                                                          "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(target_talent)

        assert target_talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] == static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert target_talent.Points == 20
        assert not target_talent.IsNew
        assert modeldata.Resources.Perl == perl

    def reforge_upgrade_talent_test_small_transmutation_level(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G012")
        target_talent.Points = 20
        target_talent.IsNew = False
        modeldata.UserInventory.add(target_talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             int(staticConstruction["requiredLeveForReforging"]) - 1)
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(target_talent)

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata,
                                                                         {"talents": ["" + str(target_talent.id) + ""],
                                                                          "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(target_talent)

        assert target_talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] == static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert target_talent.Points == 20
        assert not target_talent.IsNew
        assert modeldata.Resources.Perl == perl

    def reforge_upgrade_talent_test_small_transmutation_level_for_exclusive_talents(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G272")
        target_talent.Points = 20
        target_talent.IsNew = False
        modeldata.UserInventory.add(target_talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             int(staticConstruction["requiredLeveForReforgingExclusiveTalents"]) - 1)
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(target_talent)

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata,
                                                                         {"talents": ["" + str(target_talent.id) + ""],
                                                                          "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(target_talent)

        assert target_talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] == static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert target_talent.Points == 20
        assert not target_talent.IsNew
        assert modeldata.Resources.Perl == perl

    def reforge_upgrade_talent_test_different_rars(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 200
        target_talent1 = env.add_talent(modeldata, "G260")
        target_talent2 = env.add_talent(modeldata, "G272")
        target_talent1.Points = target_talent2.Points = 20
        target_talent1.IsNew = target_talent2.IsNew = False
        modeldata.UserInventory.add(target_talent1)
        modeldata.UserInventory.add(target_talent2)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent1_before = env.acc.SD.getStaticTalent(target_talent1)
        static_talent2_before = env.acc.SD.getStaticTalent(target_talent2)

        assert static_talent1_before["rarity"] == "magnificent"
        assert static_talent2_before["rarity"] == "magnificent"

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata, {
            "talents": ["" + str(target_talent1.id) + ", " + str(target_talent2.id) + ""], "aftercontext": ["false"]},
                                                                         False))]
        changeList = env.execActions(requests)

        static_talent1_after = env.acc.SD.getStaticTalent(target_talent1)
        static_talent2_after = env.acc.SD.getStaticTalent(target_talent2)

        price1 = env.acc.SD.data['ReforgeTalentPrices'][static_talent1_before["rarity"]]['upgradePrice']
        pricePerl1 = price1['Perl']

        price2 = env.acc.SD.data['ReforgeTalentPrices'][static_talent2_before["rarity"]]['upgradePrice']
        pricePerl2 = price2['Perl']

        assert target_talent1.id in modeldata.UserInventory
        assert static_talent1_after["persistentId"] != static_talent1_before["persistentId"]
        env.printAssert(static_talent1_after["rarity"], "exclusive")
        assert target_talent1.Points == 0
        assert target_talent1.IsNew

        assert target_talent2.id in modeldata.UserInventory
        assert static_talent2_after["persistentId"] != static_talent2_before["persistentId"]
        env.printAssert(static_talent2_after["rarity"], "exclusive")
        assert target_talent2.Points == 0
        assert target_talent2.IsNew
        assert modeldata.Resources.Perl == perl - pricePerl1 - pricePerl2

    def reforge_upgrade_talent_test_different_rars_bad_talents(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent1 = env.add_talent(modeldata, "G203")
        target_talent2 = env.add_talent(modeldata, "BBB")
        target_talent1.Points = target_talent2.Points = 20
        target_talent1.IsNew = target_talent2.IsNew = False
        modeldata.UserInventory.add(target_talent1)
        modeldata.UserInventory.add(target_talent2)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent1_before = env.acc.SD.getStaticTalent(target_talent1)
        static_talent2_before = env.acc.SD.getStaticTalent(target_talent2)

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata, {
            "talents": ["" + str(target_talent1.id) + ", " + str(target_talent2.id) + ""], "aftercontext": ["false"]},
                                                                         False))]
        changeList = env.execActions(requests)

        static_talent1_after = env.acc.SD.getStaticTalent(target_talent1)
        static_talent2_after = env.acc.SD.getStaticTalent(target_talent2)

        assert target_talent1.id in modeldata.UserInventory
        assert static_talent1_after["persistentId"] == static_talent1_before["persistentId"]
        assert static_talent1_after["rarity"] == static_talent1_before["rarity"]
        assert target_talent1.Points == 20
        assert not target_talent1.IsNew

        assert target_talent2.id in modeldata.UserInventory
        assert static_talent2_after == static_talent2_before
        assert target_talent2.Points == 20
        assert not target_talent2.IsNew

        assert modeldata.Resources.Perl == perl

    def reforge_upgrade_talent_test_different_rars_bad_rar(self, env):
        # no more bad rars
        return
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent1 = env.add_talent(modeldata, "G015")
        target_talent2 = env.add_talent(modeldata, "G272")
        target_talent1.Points = target_talent2.Points = 20
        target_talent1.IsNew = target_talent2.IsNew = False
        modeldata.UserInventory.add(target_talent1)
        modeldata.UserInventory.add(target_talent2)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent1_before = env.acc.SD.getStaticTalent(target_talent1)
        static_talent2_before = env.acc.SD.getStaticTalent(target_talent2)

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata, {
            "talents": ["" + str(target_talent1.id) + ", " + str(target_talent2.id) + ""], "aftercontext": ["false"]},
                                                                         False))]
        changeList = env.execActions(requests)

        static_talent1_after = env.acc.SD.getStaticTalent(target_talent1)
        static_talent2_after = env.acc.SD.getStaticTalent(target_talent2)

        assert target_talent1.id in modeldata.UserInventory
        assert static_talent1_after["persistentId"] == static_talent1_before["persistentId"]
        assert static_talent1_after["rarity"] == static_talent1_before["rarity"]
        assert target_talent1.Points == 20
        assert not target_talent1.IsNew

        assert target_talent2.id in modeldata.UserInventory
        assert static_talent2_after["persistentId"] == static_talent2_before["persistentId"]
        assert static_talent2_after["rarity"] == static_talent2_before["rarity"]
        assert target_talent2.Points == 20
        assert not target_talent2.IsNew

        assert modeldata.Resources.Perl == perl

    def reforge_upgrade_talent_with_guild_bank_info_test(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 100
        target_talent = env.add_talent(modeldata, "G012")
        target_talent.Points = 20
        target_talent.IsNew = False
        gbi, gbi_id = modeldata.newGuildBankInfo()
        target_talent.GuildBankInfo = gbi_id
        target_talent.GuildBankInfo.OwnerId = env.acc.auid + 1
        modeldata.UserInventory.add(target_talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforging"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(target_talent)

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata,
                                                                         {"talents": ["" + str(target_talent.id) + ""],
                                                                          "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(target_talent)

        assert target_talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] == static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert target_talent.Points == 20
        assert not target_talent.IsNew
        assert modeldata.Resources.Perl == perl

    def reforge_upgrade_talent_test_not_enough_resources(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 0
        target_talent = env.add_talent(modeldata, "G193")
        target_talent.Points = 20
        target_talent.IsNew = False
        modeldata.UserInventory.add(target_talent)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforging"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(target_talent)

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata,
                                                                         {"talents": ["" + str(target_talent.id) + ""],
                                                                          "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(target_talent)

        assert target_talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] == static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert target_talent.Points == 20
        assert not target_talent.IsNew
        assert modeldata.Resources.Perl == perl

    def reforge_upgrade_talent_test_reforge_not_allowed_by_config(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 2000
        target_talent = env.add_talent(modeldata, "G012")
        target_talent.Points = 20
        target_talent.IsNew = False
        modeldata.UserInventory.add(target_talent)
        env.acc.getConfig().IS_REFORGE_ACTIVE = False
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforging"])
        modeldata.Buildings.add(transmutation)

        static_talent_before = env.acc.SD.getStaticTalent(target_talent)

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata,
                                                                         {"talents": ["" + str(target_talent.id) + ""],
                                                                          "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent_after = env.acc.SD.getStaticTalent(target_talent)

        assert target_talent.id in modeldata.UserInventory
        assert static_talent_after["persistentId"] == static_talent_before["persistentId"]
        assert static_talent_after["rarity"] == static_talent_before["rarity"]
        assert target_talent.Points == 20
        assert not target_talent.IsNew
        assert modeldata.Resources.Perl == perl

    def reforge_upgrade_talent_test_different_rars_with_red(self, env):
        modeldata = env.acc.model
        for _id, item in env.acc.getConfig().EventToolsChangeFields.ReforgePrices.iteritems():
            if toETalentRarity(item.Rarity) == "magnificent":
                item.TalentsToUpgrade = 2
        perl = modeldata.Resources.Perl = 200
        redperl = modeldata.Resources.RedPerl = 200
        target_talent1 = env.add_talent(modeldata, "G170")
        target_talent2 = env.add_talent(modeldata, "G272")
        target_talent3 = env.add_talent(modeldata, "G260")
        target_talent4 = env.add_talent(modeldata, "G063")
        target_talent1.Points = target_talent2.Points = 20
        target_talent1.IsNew = target_talent2.IsNew = False
        modeldata.UserInventory.add(target_talent1)
        modeldata.UserInventory.add(target_talent2)
        modeldata.UserInventory.add(target_talent3)
        modeldata.UserInventory.add(target_talent4)
        inventoryBefore = len(modeldata.UserInventory)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent1_before = env.acc.SD.getStaticTalent(target_talent1)
        static_talent2_before = env.acc.SD.getStaticTalent(target_talent2)
        static_talent3_before = env.acc.SD.getStaticTalent(target_talent3)
        static_talent4_before = env.acc.SD.getStaticTalent(target_talent4)

        assert static_talent1_before["rarity"] == "magnificent"
        assert static_talent2_before["rarity"] == "magnificent"
        assert static_talent3_before["rarity"] == "magnificent"
        assert static_talent4_before["rarity"] == "magnificent"

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata, {"talents": [
            "" + str(target_talent1.id) + ", " + str(target_talent2.id) + ", " + str(target_talent3.id) + ", " + str(
                target_talent4.id) + ""], "aftercontext": ["false"]}, False))]
        changeList = env.execActions(requests)

        static_talent1_after = env.acc.SD.getStaticTalent(target_talent1)
        static_talent2_after = env.acc.SD.getStaticTalent(target_talent2)
        static_talent3_after = env.acc.SD.getStaticTalent(target_talent3)

        price1 = env.acc.SD.data['ReforgeTalentPrices'][static_talent1_before["rarity"]]['upgradePrice']
        pricePerl1 = price1['Perl']
        priceRedPerl1 = price1['RedPerl']

        price2 = env.acc.SD.data['ReforgeTalentPrices'][static_talent2_before["rarity"]]['upgradePrice']
        pricePerl2 = price2['Perl']
        priceRedPerl2 = price2['RedPerl']

        price3 = env.acc.SD.data['ReforgeTalentPrices'][static_talent3_before["rarity"]]['upgradePrice']
        pricePerl3 = price3['Perl']
        priceRedPerl3 = price3['RedPerl']

        assert target_talent1.id in modeldata.UserInventory
        assert static_talent1_after["persistentId"] != static_talent1_before["persistentId"]
        env.printAssert(static_talent1_after["rarity"], "exclusive")
        assert target_talent1.Points == 0
        assert target_talent1.IsNew

        assert target_talent2.id in modeldata.UserInventory
        assert static_talent2_after["persistentId"] != static_talent2_before["persistentId"]
        assert static_talent2_after["rarity"] == "exclusive"
        assert target_talent2.Points == 0
        assert target_talent2.IsNew

        assert target_talent3.id in modeldata.UserInventory
        assert static_talent3_after["persistentId"] != static_talent2_before["persistentId"]
        env.printAssert(static_talent3_after["rarity"], "exclusive")
        assert target_talent3.Points == 0
        assert target_talent3.IsNew

        assert target_talent4.id in modeldata.UserInventory

        env.printAssert(modeldata.Resources.Perl, perl - pricePerl1 - pricePerl2 - pricePerl3 - pricePerl3 )
        assert modeldata.Resources.RedPerl == redperl - priceRedPerl1 - priceRedPerl2 - priceRedPerl3

        assert inventoryBefore == len(modeldata.UserInventory)

    def reforge_upgrade_talent_test_not_round_amount_for_red(self, env):
        modeldata = env.acc.model
        for _id, item in env.acc.getConfig().EventToolsChangeFields.ReforgePrices.iteritems():
            if toETalentRarity(item.Rarity) == "magnificent":
                item.TalentsToUpgrade = 2
        perl = modeldata.Resources.Perl = 200
        redperl = modeldata.Resources.RedPerl = 200
        target_talent1 = env.add_talent(modeldata, "G063")
        target_talent2 = env.add_talent(modeldata, "G063")
        target_talent3 = env.add_talent(modeldata, "G063")

        target_talent1.Points = target_talent2.Points = 20
        target_talent1.IsNew = target_talent2.IsNew = False
        modeldata.UserInventory.add(target_talent1)
        modeldata.UserInventory.add(target_talent2)
        modeldata.UserInventory.add(target_talent3)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = False

        inventoryBefore = len(modeldata.UserInventory)

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent1_before = env.acc.SD.getStaticTalent(target_talent1)
        static_talent2_before = env.acc.SD.getStaticTalent(target_talent2)
        static_talent3_before = env.acc.SD.getStaticTalent(target_talent3)

        assert static_talent1_before["rarity"] == "magnificent"
        assert static_talent2_before["rarity"] == "magnificent"
        assert static_talent3_before["rarity"] == "magnificent"

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata, {"talents": [
            "" + str(target_talent1.id) + ", " + str(target_talent2.id) + ", " + str(target_talent3.id) + ""],
                                                                                     "aftercontext": ["false"]},
                                                                         False))]
        changeList = env.execActions(requests)

        static_talent1_after = env.acc.SD.getStaticTalent(target_talent1)
        static_talent2_after = env.acc.SD.getStaticTalent(target_talent2)

        price = env.acc.SD.data['ReforgeTalentPrices'][static_talent1_before["rarity"]]['upgradePrice']
        pricePerl = price['Perl']
        priceRedPerl = price['RedPerl']

        assert target_talent1.id in modeldata.UserInventory
        env.printAssert(static_talent1_after["rarity"], "exclusive")
        env.printAssert(target_talent1.Points, 0)
        assert target_talent1.IsNew

        assert target_talent3.id in modeldata.UserInventory

        assert target_talent2.id in modeldata.UserInventory
        assert static_talent2_after["persistentId"] != static_talent2_before["persistentId"]
        assert static_talent2_after["rarity"] == "exclusive"
        assert target_talent2.Points == 0
        assert target_talent2.IsNew

        env.printAssert(modeldata.Resources.Perl, 176)
        assert modeldata.Resources.RedPerl == redperl - priceRedPerl

        env.printAssert(inventoryBefore, len(modeldata.UserInventory))

    def reforge_upgrade_talent_test_points(self, env):
        modeldata = env.acc.model
        perl = modeldata.Resources.Perl = 200
        target_talent1 = env.add_talent(modeldata, "G012")
        target_talent2 = env.add_talent(modeldata, "G272")
        target_talent1.Points = 20
        target_talent2.Points = 0
        target_talent1.IsNew = target_talent2.IsNew = False
        modeldata.UserInventory.add(target_talent1)
        modeldata.UserInventory.add(target_talent2)
        env.acc.getConfig().SAVE_TALENTS_POINTS_ON_REFORGE = True

        staticConstruction = env.acc.SD.getStaticConstructionByPersistentId(crc32("Talent_Production"))
        transmutation = env.add_construction(modeldata, "Talent_Production",
                                             staticConstruction["requiredLeveForReforgingExclusiveTalents"])
        modeldata.Buildings.add(transmutation)

        static_talent1_before = env.acc.SD.getStaticTalent(target_talent1)
        static_talent2_before = env.acc.SD.getStaticTalent(target_talent2)

        assert static_talent1_before["rarity"] == "excellent"
        assert static_talent2_before["rarity"] == "magnificent"

        requests = [(Reforge_upgrade_talent, ReforgeUpgradeTalentRequest(modeldata, {
            "talents": ["" + str(target_talent1.id) + ", " + str(target_talent2.id) + ""], "aftercontext": ["false"]},
                                                                         False))]
        changeList = env.execActions(requests)

        static_talent1_after = env.acc.SD.getStaticTalent(target_talent1)
        static_talent2_after = env.acc.SD.getStaticTalent(target_talent2)

        price2 = env.acc.SD.data['ReforgeTalentPrices'][static_talent2_before["rarity"]]['upgradePrice']
        pricePerl2 = price2['Perl']

        assert static_talent1_after["persistentId"] == static_talent1_before["persistentId"]
        assert target_talent1.Points == 20
        assert not target_talent1.IsNew

        assert target_talent2.id in modeldata.UserInventory
        assert static_talent2_after["persistentId"] != static_talent2_before["persistentId"]
        assert static_talent2_after["rarity"] == "exclusive"
        assert target_talent2.Points == 0
        assert target_talent2.IsNew
        assert modeldata.Resources.Perl == perl - pricePerl2

