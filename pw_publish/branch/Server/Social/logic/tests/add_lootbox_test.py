import sys
sys.path.append('../')
sys.path.append('../..')
from logic.add_lootbox import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class add_lootbox_test:

    def add_lootbox_test( self, env ):
        model_data = env.acc.model
        lootbox_id = crc32("LB_Violet345")
        initial_inv_len = len(model_data.Lootboxes)
        next_item_uid = model_data.next_uid_ + 1

        requests = [(Add_lootbox, AddLootboxRequest(model_data, {"lootboxId": [lootbox_id]}, False))]
        env.execActions(requests)

        lootbox = model_data.getLootboxByID(next_item_uid)
        assert lootbox is not None
        assert len(model_data.Lootboxes) == initial_inv_len + 1
        assert lootbox.PersistentId == lootbox_id

    def add_nonexistent_test(self, env):
        model_data = env.acc.model
        requests = [(Add_lootbox, AddLootboxRequest(model_data, {"lootboxId": [0]}, False))]
        env.execActions(requests)
        changes = env.getChangeList()
        changes_index = env.getChangeListIdx() - 1
        assert changes[changes_index]["ok"] == 0
