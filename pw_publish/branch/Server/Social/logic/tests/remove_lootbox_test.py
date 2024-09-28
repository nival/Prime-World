import sys
sys.path.append('../')
sys.path.append('../..')
from logic.remove_lootbox import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class remove_lootbox_test:

    def remove_unopened_lootbox_test(self, env):
        model_data = env.acc.model
        static_lootbox_id = crc32("LB_Violet345")

        lootbox_id = model_data.addNewLootbox()
        lootbox = model_data.getLootboxByID(lootbox_id)
        lootbox.PersistentId = static_lootbox_id

        model_data.Lootboxes.add(lootbox)
        initial_len = len(model_data.Lootboxes)

        request = [(Remove_lootbox, RemoveLootboxRequest(model_data, {"lootbox_id": [lootbox_id]}, False))]
        env.execActions(request)

        assert len(model_data.Lootboxes) == initial_len


    def remove_opened_lootbox_test(self, env):
        model_data = env.acc.model
        static_lootbox_id = crc32("LB_Violet345")

        lootbox_id = model_data.addNewLootbox()
        lootbox = model_data.getLootboxByID(lootbox_id)
        lootbox.PersistentId = static_lootbox_id

        lootbox.Reward.IsApplied = True

        model_data.Lootboxes.add(lootbox)
        initial_len = len(model_data.Lootboxes)

        request = [(Remove_lootbox, RemoveLootboxRequest(model_data, {"lootbox_id": [lootbox_id]}, False))]
        env.execActions(request)

        assert len(model_data.Lootboxes) == initial_len - 1
