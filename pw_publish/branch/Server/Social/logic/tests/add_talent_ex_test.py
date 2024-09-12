import sys
sys.path.append('../')
sys.path.append('../..')
from logic.add_talent_ex import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class add_talent_ex_test:

    def add_talent_test( self, env ):
        model_data = env.acc.model
        initial_inv_len = len(model_data.UserInventory)
        inventory_item_id = model_data.next_uid_ + 1
        persistent_id = crc32("G137")
        points = 1500

        requests = [(Add_talent_ex, AddTalentExRequest(model_data,
                                                       {"static_talent_id": [str(persistent_id)], "points": [1500]},
                                                       False))]
        env.execActions(requests)

        assert len(model_data.UserInventory) == initial_inv_len + 1
        inventory_item = model_data.getTalentByID(inventory_item_id)
        assert inventory_item is not None
        assert inventory_item.PersistentId == persistent_id
        assert inventory_item.IsNew
        assert inventory_item.Points == points
