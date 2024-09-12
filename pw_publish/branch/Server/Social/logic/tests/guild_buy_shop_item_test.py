import sys
sys.path.append('../')
sys.path.append('../..')
from logic.guild_buy_shop_item import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class guild_buy_shop_item_test:
    def guild_buy_shop_item_test( self, env ):
        env.acc.db.guildAuid = 100500
        modeldata = env.acc.model
        member, id = env.acc.guilddata.newGuildMember()
        member.Person = env.acc.auid
        member.IsOfficer = False
        member.JoinTime = int(time.time())
        modeldata.Resources.CWPoints_Player = 100
        env.acc.guilddata.GuildShopItems[str(crc32("CS063"))] = 2
        staticItem = env.acc.SD.getGuildShopItemById(crc32("CS063"))
        resBefore = modeldata.Resources.CWPoints_Player

        requests = [(Guild_buy_shop_item, GuildBuyShopItemRequest(modeldata, {"persistentId": [crc32("CS063")]}, False))]
        changeList = env.execActions(requests)

        assert modeldata.Resources.CWPoints_Player == resBefore - staticItem['price']['CWPoints_Player']
        assert env.acc.guilddata.GuildShopItems[str(crc32("CS063"))] == 1

    def guild_buy_shop_not_in_guild_test( self, env ):
        env.acc.db.guildAuid = 0
        modeldata = env.acc.model
        modeldata.Resources.CWPoints_Player = 100

        env.acc.guilddata.GuildShopItems[str(crc32("CS002"))] = 2

        requests = [(Guild_buy_shop_item, GuildBuyShopItemRequest(modeldata, {"persistentId": [crc32("CS002")]}, False))]
        changeList = env.execActions(requests)

        assert changeList[0]['ec'] == EC.NOT_IN_GUILD
        assert modeldata.Resources.CWPoints_Player == 100
        assert env.acc.guilddata.GuildShopItems[str(crc32("CS002"))] == 2

    def guild_buy_shop_item_item_not_in_config_test( self, env ):
        env.acc.db.guildAuid = 100500
        modeldata = env.acc.model
        modeldata.Resources.CWPoints_Player = 100
        env.acc.guilddata.GuildShopItems[str(crc32("CS202"))] = 2

        requests = [(Guild_buy_shop_item, GuildBuyShopItemRequest(modeldata, {"persistentId": [crc32("CS202")]}, False))]
        changeList = env.execActions(requests)

        assert changeList[0]['error'] == "Can't find shop item in config"
        assert modeldata.Resources.CWPoints_Player == 100

    def guild_buy_shop_item_item_not_in_static_data_test( self, env ):
        env.acc.db.guildAuid = 100500
        modeldata = env.acc.model
        modeldata.Resources.CWPoints_Player = 100
        env.acc.getConfig().GUILD_SHOP_ITEMS.append(crc32("health0"))
        requests = [(Guild_buy_shop_item, GuildBuyShopItemRequest(modeldata, {"persistentId": [crc32("health0")]}, False))]
        changeList = env.execActions(requests)

        assert changeList[0]['error'] == "Can't find shop item in static data"
        assert modeldata.Resources.CWPoints_Player == 100

    def guild_buy_shop_item_not_enough_points_test( self, env ):
        env.acc.db.guildAuid = 100500
        modeldata = env.acc.model
        member, id = env.acc.guilddata.newGuildMember()
        member.Person = env.acc.auid
        member.IsOfficer = True
        member.JoinTime = int(time.time())
        modeldata.Resources.CWPoints_Player = 0
        env.acc.guilddata.GuildShopItems[str(crc32("CS002"))] = 2

        requests = [(Guild_buy_shop_item, GuildBuyShopItemRequest(modeldata, {"persistentId": [crc32("CS002")]}, False))]
        changeList = env.execActions(requests)

        assert changeList[0]['ec'] == EC.NOT_ENOUGH_RESOURCES
        assert modeldata.Resources.CWPoints_Player == 0
        assert env.acc.guilddata.GuildShopItems[str(crc32("CS002"))] == 2

    def guild_buy_shop_item_no_item_in_guild_shop_test(self, env):
        env.acc.db.guildAuid = 100500
        modeldata = env.acc.model
        member, id = env.acc.guilddata.newGuildMember()
        member.Person = env.acc.auid
        member.IsOfficer = True
        member.JoinTime = int(time.time())
        modeldata.Resources.CWPoints_Player = 100

        requests = [(Guild_buy_shop_item, GuildBuyShopItemRequest(modeldata, {"persistentId": [crc32("CS063")]}, False))]
        changeList = env.execActions(requests)

        assert changeList[0]['error'] == ("BuyGuildShopItemAction: can not find shop item with id=" + str(crc32("CS063")))
        assert modeldata.Resources.CWPoints_Player == 100

    def guild_buy_shop_item_not_officer_test(self, env):
        env.acc.db.guildAuid = 100500
        modeldata = env.acc.model
        modeldata.Resources.CWPoints_Player = 100
        member, id = env.acc.guilddata.newGuildMember()
        member.Person = env.acc.auid
        member.IsOfficer = False
        member.JoinTime = int(time.time())
        env.acc.guilddata.GuildShopItems[str(crc32("CS002"))] = 2

        requests = [(Guild_buy_shop_item, GuildBuyShopItemRequest(modeldata, {"persistentId": [crc32("CS002")]}, False))]

        changeList = env.execActions(requests)

        assert changeList[0]['ec'] == EC.GUILD_SHOP_CANNOT_BUY_GUILD_POINTS_ONLY_ITEM
        assert modeldata.Resources.CWPoints_Player == 100
        assert env.acc.guilddata.GuildShopItems[str(crc32("CS002"))] == 2

    def guild_buy_shop_item_officer_test( self, env ):
        env.acc.db.guildAuid = 100500
        modeldata = env.acc.model
        env.acc.guilddata.GuildInfo.CWPoints_Clan = 100
        modeldata.Resources.CWPoints_Player = 100
        resBefore = modeldata.Resources.CWPoints_Player
        staticItem = env.acc.SD.getGuildShopItemById(crc32("CS063"))
        member, id = env.acc.guilddata.newGuildMember()
        member.Person = env.acc.auid
        member.IsOfficer = True
        member.JoinTime = int(time.time())
        env.acc.guilddata.GuildShopItems[str(crc32("CS063"))] = 2

        requests = [(Guild_buy_shop_item, GuildBuyShopItemRequest(modeldata, {"persistentId": [crc32("CS063")]}, False))]
        changeList = env.execActions(requests)

        assert env.acc.guilddata.GuildInfo.CWPoints_Clan == 100
        assert modeldata.Resources.CWPoints_Player == resBefore - staticItem['price']['CWPoints_Player']
        assert env.acc.guilddata.GuildShopItems[str(crc32("CS063"))] == 1

    def guild_buy_shop_item_no_available_items_test( self, env ):
        env.acc.db.guildAuid = 100500
        modeldata = env.acc.model
        modeldata.Resources.CWPoints_Player = 100
        env.acc.guilddata.GuildInfo.CWPoints_Clan = 1000
        env.acc.guilddata.GuildShopItems[str(crc32("CS002"))] = 0

        requests = [(Guild_buy_shop_item, GuildBuyShopItemRequest(modeldata, {"persistentId": [crc32("CS002")]}, False))]
        changeList = env.execActions(requests)

        assert changeList[0]['ec'] == EC.GUILD_SHOP_ITEM_DAY_LIMIT_EXCEEDED
        assert modeldata.Resources.CWPoints_Player == 100
        assert env.acc.guilddata.GuildShopItems[str(crc32("CS002"))] == 0

    def guild_buy_buf_shop_item_test( self, env ):
        env.acc.db.guildAuid = 100500
        modeldata = env.acc.model
        modeldata.Resources.CWPoints_Player = 100


        member, id = env.acc.guilddata.newGuildMember()
        member.Person = env.acc.auid
        member.IsOfficer = True
        member.JoinTime = int(time.time())

        bufsBefore = len(modeldata.GuildBufs)
        bufsBeforeInKeeper = len(modeldata.GuildBufsKeeper)

        itemId = "CS060"
        env.acc.guilddata.GuildInfo.CWPoints_Clan = 1000
        env.acc.guilddata.GuildShopItems[str(crc32(itemId))] = 2

        requests = [(Guild_buy_shop_item, GuildBuyShopItemRequest(modeldata, {"persistentId": [crc32(itemId)]}, False))]

        changeList = env.execActions(requests)

        #assert modeldata.Resources.CWPoints_Player == 100
        assert len(modeldata.GuildBufs) == bufsBefore + 1
        assert env.acc.guilddata.GuildShopItems[str(crc32(itemId))] == 1
        assert len(modeldata.GuildBufsKeeper) == bufsBeforeInKeeper + 1

    def guild_buy_lootbox_shop_item_test( self, env ):
        env.acc.db.guildAuid = 100500
        modeldata = env.acc.model
        modeldata.Resources.CWPoints_Player = 100

        member, id = env.acc.guilddata.newGuildMember()
        member.Person = env.acc.auid
        member.IsOfficer = True
        member.JoinTime = int(time.time())

        lootboxes_before = len(modeldata.Lootboxes)
        lootboxes_before_in_keeper = len(modeldata.LootboxKeeper)

        itemId = "CS121"
        env.acc.guilddata.GuildInfo.CWPoints_Clan = 12000
        env.acc.guilddata.GuildShopItems[str(crc32(itemId))] = 2
        env.acc.getConfig().GUILD_SHOP_ITEMS.append(crc32(itemId))

        requests = [(Guild_buy_shop_item, GuildBuyShopItemRequest(modeldata, {"persistentId": [crc32(itemId)]}, False))]

        changeList = env.execActions(requests)

        # assert modeldata.Resources.CWPoints_Player == 100
        assert len(modeldata.Lootboxes) == lootboxes_before + 1
        assert env.acc.guilddata.GuildShopItems[str(crc32(itemId))] == 1
        assert len(modeldata.LootboxKeeper) == lootboxes_before_in_keeper + 1