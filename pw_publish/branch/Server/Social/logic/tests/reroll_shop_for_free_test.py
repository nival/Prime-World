import sys
sys.path.append('../')
sys.path.append('../..')
from logic.reroll_shop_for_free import *
from binascii import crc32
from base.helpers import *
from enums import *
import CC

class reroll_shop_for_free_test:

    def reroll_shop_for_free_test( self, env ):
        modeldata = env.acc.model
        env.acc.db.castle_roll = {CC.REROLL_ADDITIONAL_PROBABILITIES: {}, CC.REROLL_DAILY_PROBABILITIES: {}, CC.REROLL_DAILY_WEIGHTS: {}}

        modeldata.Resources.Gold = 100500
        oldGold = 100500
        env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS = 5
        for _id, item in modeldata.RerollShopInfo.ShopItems.items():
            modeldata.RerollShopInfo.ShopItems.remove(item)

        assert len(modeldata.RerollShopInfo.ShopItems) == 0
        requests = [(Reroll_shop_for_free, RerollShopForFreeRequest(modeldata, {}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.RerollShopInfo.ShopItems) == env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS + env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_PREMIUM_SLOTS

    def reroll_shop_for_free_all_items_bought( self, env ):
        modeldata = env.acc.model

        env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS = 5
        for _id, item in modeldata.RerollShopInfo.ShopItems.items():
            item.IsBought = True

        assert len(modeldata.RerollShopInfo.ShopItems) != 0
        requests = [(Reroll_shop_for_free, RerollShopForFreeRequest(modeldata, {}, False))]
        changeList = env.execActions(requests)

        for _id, item in modeldata.RerollShopInfo.ShopItems.items():
            assert not item.IsBought
        assert len(modeldata.RerollShopInfo.ShopItems) == env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_ORDINARY_SLOTS + env.acc.getConfig().EventToolsChangeFields.REROLL_SHOP_PREMIUM_SLOTS