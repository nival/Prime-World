import sys
sys.path.append('../')
sys.path.append('../..')
from logic.add_reroll_shop_item import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class add_reroll_shop_item_test:

    def add_reroll_shop_item_test(self, env):
        modeldata = env.acc.model
        PersistentId = crc32("res1_medium")

        id = modeldata.next_uid_ + 1
        for _id, item in modeldata.RerollShopInfo.ShopItems.items():
            modeldata.RerollShopInfo.ShopItems.remove(item)
        assert len(modeldata.RerollShopInfo.ShopItems) == 0
        requests = [ ( Add_reroll_shop_item, AddRerollShopItemRequest( modeldata, { "persistentId" : ["" + str(PersistentId) + ""], "price": ["100"], "resourceType": ["3"], "isPremium": ["" + str(False) + ""] }, False ) ) ]
        changeList = env.execActions( requests )

        itemId = id

        assert(modeldata.getRerollShopItemByID(itemId).PersistentId == PersistentId)
        assert(modeldata.getRerollShopItemByID(itemId).PriceResource == 3)
        assert(not modeldata.getRerollShopItemByID(itemId).IsBought)
        assert(modeldata.getRerollShopItemByID(itemId).Price == 100)
        assert(itemId in modeldata.RerollShopInfo.ShopItems)