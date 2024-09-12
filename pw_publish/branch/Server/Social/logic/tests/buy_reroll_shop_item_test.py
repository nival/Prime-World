import sys
sys.path.append('../')
sys.path.append('../..')
from logic.buy_reroll_shop_item import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class buy_reroll_shop_item_test:

    def __setupLootboxRerollShop(self, env):
        self.oldSlots = env.acc.SD.data['RerollShopSlots']
        env.acc.SD.data['RerollShopSlots'] = {crc32('lootboxTestSlot'): {'persistentId': 'lootboxTestSlot', 'classType': 'LootboxRerollSlot',
                                                    'count': 1, 'lootboxPersistentId': 'LB_Red567'}}

    def __revertLootboxRerollShop(self, env):
        env.acc.SD.data['RerollShopSlots'] = self.oldSlots

    def buy_reroll_shop_item_test( self, env ):
        modeldata = env.acc.model
        modeldata.Resources.Perl = 100
        modeldata.Resources.Silver = 0
        perisitentId = crc32('silver_small')

        staticItem = env.acc.SD.getStaticRerollShopItemById(perisitentId)

        item, item_id = modeldata.newRerollShopItem()
        item.PersistentId = perisitentId
        item.Price = 10
        item.PriceResource = ERerollShopResources.Perl

        oldPerl = modeldata.Resources.Perl
        oldSilver = modeldata.Resources.Silver

        requests = [ ( Buy_reroll_shop_item, BuyRerollShopItemRequest( modeldata, { "item_id" : ["" + str(item_id) + ""], "afterContext": ["false"]}, False ) ) ]
        changeList = env.execActions(requests)

        assert item.IsBought
        assert modeldata.Resources.Perl == oldPerl - item.Price
        assert modeldata.Resources.Silver == int(staticItem['resource']['Silver'])

    def buy_talent_reroll_shop_item_test( self, env ):
        modeldata = env.acc.model
        modeldata.Resources.Perl = 100
        modeldata.Resources.Silver = 0
        perisitentId = crc32('talents_rar5_set5')

        staticItem = env.acc.SD.getStaticTalentByTalentId(perisitentId)

        item, item_id = modeldata.newRerollShopItem()
        item.PersistentId = perisitentId
        item.Price = 10
        item.PriceResource = ERerollShopResources.Perl

        oldPerl = modeldata.Resources.Perl
        defaultinventoryLength = len(modeldata.UserInventory)

        requests = [ ( Buy_reroll_shop_item, BuyRerollShopItemRequest( modeldata, { "item_id" : ["" + str(item_id) + ""], "afterContext": ["false"]}, False ) ) ]
        changeList = env.execActions(requests)

        assert item.IsBought
        assert modeldata.Resources.Perl == oldPerl - item.Price
        assert len(modeldata.UserInventory) == 1 + defaultinventoryLength

    def buy_skin_reroll_shop_item_test( self, env ):
        modeldata = env.acc.model
        modeldata.Resources.Perl = 100
        modeldata.Resources.Silver = 0
        perisitentId = crc32('talents_rar5_set5')

        staticItem = env.acc.SD.getStaticTalentByTalentId(perisitentId)

        item, item_id = modeldata.newRerollShopItem()
        item.PersistentId = perisitentId
        item.Price = 10
        item.PriceResource = ERerollShopResources.Perl

        oldPerl = modeldata.Resources.Perl
        defaultinventoryLength = len(modeldata.UserInventory)

        requests = [ ( Buy_reroll_shop_item, BuyRerollShopItemRequest( modeldata, { "item_id" : ["" + str(item_id) + ""], "afterContext": ["false"]}, False ) ) ]
        changeList = env.execActions(requests)

        assert item.IsBought
        assert modeldata.Resources.Perl == oldPerl - item.Price
        assert len(modeldata.UserInventory) == 1 + defaultinventoryLength

    def buy_lootbox_reroll_shop_item_test(self, env):
        self.__setupLootboxRerollShop(env)

        modeldata = env.acc.model
        modeldata.Resources.Perl = 100
        perisitentId = crc32('lootboxTestSlot')

        item, item_id = modeldata.newRerollShopItem()
        item.PersistentId = perisitentId
        item.Price = 10
        item.PriceResource = ERerollShopResources.Perl

        oldPerl = modeldata.Resources.Perl

        requests = [(Buy_reroll_shop_item, BuyRerollShopItemRequest(modeldata, {"item_id": ["" + str(item_id) + ""],
                                                                                "afterContext": ["false"]}, False))]
        env.execActions(requests)

        self.__revertLootboxRerollShop(env)

        assert item.IsBought
        assert modeldata.Resources.Perl == oldPerl - item.Price
        assert len(modeldata.Lootboxes) == 1
        assert modeldata.Lootboxes.items()[0][1].PersistentId == crc32('LB_Red567')
