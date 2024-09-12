import sys
sys.path.append('../')
sys.path.append('../..')
from logic.reroll_shop import *
from binascii import crc32
from base.helpers import *
from enums import *
import CC

class reroll_shop_test:

    def reroll_shop_test( self, env ):
        modeldata = env.acc.model
        env.acc.db.castle_roll = {CC.REROLL_ADDITIONAL_PROBABILITIES: {}, CC.REROLL_DAILY_PROBABILITIES: {}, CC.REROLL_DAILY_WEIGHTS: {}}

        modeldata.Resources.Perl = 100500
        oldPerl = 100500
        for _id, item in modeldata.RerollShopInfo.ShopItems.items():
            item.IsBought = True

        requests = [(Reroll_shop, RerollShopRequest(modeldata, {}, False))]
        changeList = env.execActions(requests)

        activeItems = 0
        for _id, item in modeldata.RerollShopInfo.ShopItems.items():
            if not item.IsBought:
                activeItems += 1
        assert activeItems == len(modeldata.RerollShopInfo.ShopItems) - env.acc.getConfig().EventToolsChangeFields.INACTIVE_REROLL_SHOP_ORDINARY_SLOTS
        assert oldPerl > modeldata.Resources.Perl

    def reroll_shop_with_PA_test( self, env ):
        modeldata = env.acc.model
        env.acc.db.castle_roll = {CC.REROLL_ADDITIONAL_PROBABILITIES: {}, CC.REROLL_DAILY_PROBABILITIES: {}, CC.REROLL_DAILY_WEIGHTS: {}}
        modeldata.LordInfo.PremiumAccountEnd = modeldata.FatClientServerTime + 100500

        modeldata.Resources.Perl = 100500
        oldPerl = 100500
        for _id, item in modeldata.RerollShopInfo.ShopItems.items():
            item.IsBought = True

        requests = [(Reroll_shop, RerollShopRequest(modeldata, {}, False))]
        changeList = env.execActions(requests)

        activeItems = 0
        for _id, item in modeldata.RerollShopInfo.ShopItems.items():
            if not item.IsBought:
                activeItems += 1
        assert activeItems == len(modeldata.RerollShopInfo.ShopItems) - env.acc.getConfig().EventToolsChangeFields.INACTIVE_REROLL_SHOP_PREMIUM_SLOTS
        assert oldPerl > modeldata.Resources.Perl