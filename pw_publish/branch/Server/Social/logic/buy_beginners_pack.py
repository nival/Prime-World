# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BuyBeginnersPackRequest import *

class Buy_beginners_pack( SubAction, BuyBeginnersPackRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "buy_beginners_pack"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if self.arguments.packIndex not in self.acc.getConfig().BeginnersPackEventInfo.BeginnersPackItems.keys():
            self.errorResponse(EC.BAD_PARAM, "Beginners pack was not found")
            return

        # Проверим, все ли таланты нормальные и можно ли их выдать
        self.beginnersPack = self.acc.getConfig().BeginnersPackEventInfo.BeginnersPackItems.get(self.arguments.packIndex)
        for talentId in self.beginnersPack.PackTalents:
            if self.acc.SD.getStaticTalentByTalentId(crc32(talentId)) == None:
                self.errorResponse(EC.BAD_PARAM, "Can't find talent with persistentId %s" % talentId)
                return

        self.price = self.acc.model.createResourcesTable(Gold=self.beginnersPack.Gold)
        self.needGold = int(self.price.Gold)
        if not self.needGold or self.needGold < 0:
            self.errorResponse("The pack does not have gold price")
            return

        reason = "PW!BeginnersPack:" + self.beginnersPack.PersistentId
        self.buy(self.price, self.onBuy, self.onBuyFunc, reason)
        return None


    @model_callback
    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            for talentId in self.beginnersPack.PackTalents:
                staticTalent = self.acc.SD.getStaticTalentByTalentId(crc32(talentId))
                if staticTalent and staticTalent['rarity'] != "Class":
                    self.acc.model.addTalent(crc32(talentId))
                else:
                    warn("Class talents are not allowed to be added")

            self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.BuyBeginnersPack, self.beginnersPack.PersistentId, self.price, self.acc.model.Resources)
            self.response["ok"] = 1  # success
        else:
            self.onBuyError(response, self.needGold)
            return

        self.fin()


    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)