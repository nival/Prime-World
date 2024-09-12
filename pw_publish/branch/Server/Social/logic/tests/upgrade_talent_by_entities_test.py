#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
sys.path.append('../')
sys.path.append('../..')
from logic.upgrade_talent_by_entities import *
from logic.add_lootbox import *
from logic.open_lootbox import *
from logic.remove_lootbox import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class upgrade_talent_by_entities_test:

    def upgrade_talent_by_entities_test( self, env ):
        pass
        modeldata = env.acc.model
        target_talent = env.add_talent(modeldata, "G137")
        modeldata.UserInventory.add(target_talent)
        prev_talent_level = env.acc.SD.getTalentLevel(target_talent)
        target_level = 5 + 1  # хотим до 7 звезды прокачать, на 1 больше, чем можем заточить, чтобы проверить фейл

        uids = []

        num_iter = target_level - prev_talent_level
        for x in range(0, num_iter):
            ent = modeldata.addTalentUpgradeEntity(crc32("TalUpg_Abrasive6"))
            uids.append(ent.id)
            ent = modeldata.addTalentUpgradeEntity(crc32("TalUpg_Catalyst2"))
            uids.append(ent.id)

        assert len(modeldata.TalentUpgradeEntities) == num_iter * 2

        requests = []
        for x in range(0, num_iter):
            idx = x*2
            ent_id = uids[idx]
            ent_id_2 = uids[idx+1]
            requests.append((Upgrade_talent_by_entities, UpgradeTalentByEntityRequest(modeldata,
                                                              {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                               "rid": ["" + str(x) + ""],
                                                               "entities": ["" + str(ent_id) + "," + str(ent_id_2) + ""]},
                                                                                  False)))
        changeList = env.execActions(requests)

        new_talent_level = env.acc.SD.getTalentLevel(target_talent)

        assert target_talent.id in modeldata.UserInventory
        assert len(modeldata.TalentUpgradeEntities) == 2
        assert prev_talent_level < new_talent_level
        assert new_talent_level == target_level - 1

    def upgrade_talent_by_entities_reuse_test( self, env ):
        modeldata = env.acc.model
        target_talent = env.add_talent(modeldata, "G138")
        modeldata.UserInventory.add(target_talent)
        prev_talent_level = env.acc.SD.getTalentLevel(target_talent)
        target_level = 10  # хотим до 7 звезды прокачать, на 1 больше, чем можем заточить, чтобы проверить фейл

        uids = []
        #ent = modeldata.addTalentUpgradeEntity(crc32("TalUpg_Abrasive10"))

        lootbox_id = crc32("LB_TalUpg_Abrasive7")
        assert len(modeldata.TalentUpgradeEntities) == 0

        requests = [(Add_lootbox, AddLootboxRequest(modeldata, {"lootboxId": [lootbox_id]}, False))]
        changes = env.execActions(requests)

        assert len(modeldata.TalentUpgradeEntities) == 0

        #added_dict = changes[0]["ModelData"][0]["0"][0][2]
        ent_id = None

        li = 0
        for lootbox_id in modeldata.Lootboxes.keys():
            li += 1
            requests = [(Open_lootbox, OpenLootboxRequest(modeldata,
                                                          {"rid": [li], "lootbox_id": [lootbox_id]},
                                                          False))]
            changes2 = env.execActions(requests)
            #added_dict2 = changes2[1]["ModelData"][0][str(li)][0][2]
            for key in modeldata.TalentUpgradeEntities.keys():
                ent_id = key

            requests = [(Remove_lootbox, RemoveLootboxRequest(modeldata,
                                                          {"rid": [li], "lootbox_id": [lootbox_id]},
                                                          False))]
            env.execActions(requests)

        ent = modeldata.addTalentUpgradeEntity(crc32("TalUpg_Catalyst4"))
        ent_id_2 = ent.id
        ent = modeldata.addTalentUpgradeEntity(crc32("TalUpg_Catalyst4"))
        ent_id_3 = ent.id

        assert len(modeldata.TalentUpgradeEntities) == 3

        requests = []
        num_iter = 10
        for x in range(0, num_iter):
            requests.append((Upgrade_talent_by_entities, UpgradeTalentByEntityRequest(modeldata,
                                                              {"target_talent_id": ["" + str(target_talent.id) + ""],
                                                               "rid": ["" + str(x) + ""],
                                                               "entities": ["" + str(ent_id) + "," + str(ent_id_2) + "," + str(ent_id_3) + ""]},
                                                                                  False)))
        env.execActions(requests)

        modeldata.validateTalentUpgradeEntities(env.acc.SD)

        new_talent_level = env.acc.SD.getTalentLevel(target_talent)
        # res = modeldata.getTalentUpgradeEntityByID(ent_id)
        # assert res is None
        assert target_talent.id in modeldata.UserInventory
        assert len(modeldata.TalentUpgradeEntities) == 0
        assert prev_talent_level < new_talent_level
        assert new_talent_level == prev_talent_level + 1

