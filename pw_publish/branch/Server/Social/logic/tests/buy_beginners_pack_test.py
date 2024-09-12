# -*- coding: utf-8 -*-

import sys
sys.path.append('../')
sys.path.append('../..')
from logic.buy_beginners_pack import *
from binascii import crc32
from base.helpers import *
from enums import *
import EC

class buy_beginners_pack_test:

    def buy_beginners_pack_test(self, env):
        modeldata = env.acc.model
        beginnersPack = env.acc.getConfig().BeginnersPackEventInfo.BeginnersPackItems[3]

        modeldata.Resources.Gold = 100500
        oldGold = 100500
        talentsBefore = len(modeldata.UserInventory)

        requests = [(Buy_beginners_pack, BuyBeginnersPackRequest(modeldata, {"packIndex": ["" + str(3) + ""]}, False))]
        changeList = env.execActions(requests)

        assert len(modeldata.UserInventory) == talentsBefore + len(beginnersPack.PackTalents)
        assert modeldata.Resources.Gold == oldGold - beginnersPack.Gold

    def buy_beginners_pack_wrong_pack_id_test(self, env):
        modeldata = env.acc.model
        beginnersPack = env.acc.getConfig().BeginnersPackEventInfo.BeginnersPackItems[3]

        modeldata.Resources.Gold = 100500
        oldGold = 100500
        talentsBefore = len(modeldata.UserInventory)

        requests = [(Buy_beginners_pack, BuyBeginnersPackRequest(modeldata, {"packIndex": ["" + str(666) + ""]}, False))]
        changeList = env.execActions(requests)

        assert changeList.get(0).get("error") == 'Beginners pack was not found'
        assert len(modeldata.UserInventory) == talentsBefore
        assert modeldata.Resources.Gold == oldGold

    def buy_beginners_pack_bad_talent_id_test(self, env):
        modeldata = env.acc.model
        env.acc.getConfig().addBeginnerPack(666, 10,  "UI/Textures/ArcGames/Items/RU/01zen_ru", "pack1", "Новичку 1", ["G6666", "G373", "G374", "G375", "G376"])

        modeldata.Resources.Gold = 100500
        oldGold = 100500
        talentsBefore = len(modeldata.UserInventory)

        requests = [(Buy_beginners_pack, BuyBeginnersPackRequest(modeldata, {"packIndex": ["" + str(666) + ""]}, False))]
        changeList = env.execActions(requests)

        assert changeList.get(0).get("error") == "Can't find talent with persistentId G6666"
        assert len(modeldata.UserInventory) == talentsBefore
        assert modeldata.Resources.Gold == oldGold

    def buy_beginners_pack_no_gold_price_test(self, env):
        modeldata = env.acc.model
        env.acc.getConfig().addBeginnerPack(666, -10,  "UI/Textures/ArcGames/Items/RU/01zen_ru", "pack1", "Новичку 1", ["G373", "G373", "G374", "G375", "G376"])

        modeldata.Resources.Gold = 100500
        oldGold = 100500
        talentsBefore = len(modeldata.UserInventory)

        requests = [(Buy_beginners_pack, BuyBeginnersPackRequest(modeldata, {"packIndex": ["" + str(666) + ""]}, False))]
        changeList = env.execActions(requests)

        assert changeList.get(0).get("error") == "The pack does not have gold price"
        assert len(modeldata.UserInventory) == talentsBefore
        assert modeldata.Resources.Gold == oldGold