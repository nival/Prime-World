# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_flag import *
from logic.requests.BuyCustomFlagRequest import *

class Buy_custom_flag( SubAction, BuyCustomFlagRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "buy_custom_flag"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.flagId = self.arguments.flagId
        self.guardParty = self.arguments.guardParty
        self.master_auid = self.arguments.master_auid

        self.staticCustomFlag = self.acc.SD.getCustomFlagById(self.flagId)
        self.customFlag = self.acc.getConfig().getCustomFlagById(self.flagId)
        if not self.customFlag or not self.staticCustomFlag:
            self.errorResponse(EC.FLAG_NOT_FOUND, "Custom flag was not found")
            return

        if self.flagId in self.acc.model.Flags:
            self.errorResponse(EC.FLAG_IS_ALREADY_OWNED, "The flag is already bought")
            return

        self.price = self.acc.model.createResourcesTable(Gold=self.customFlag.Price)
        self.needGold = int(self.price.Gold)
        if not self.needGold:
            self.errorResponse("The flag does not have gold price")
            return

        reason = "PW!FLAG:" + self.flagId
        self.buy(self.price, self.onBuy, self.onBuyFunc, reason)
        return None

    @model_callback
    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            self.acc.model.Flags.append(self.staticCustomFlag['id'])
            self.acc.model.FlagInfo.PersistentId = self.staticCustomFlag['id']
            self.acc.model.FlagInfo.FlagType = FlagType.Special
            self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.BuyFlag, self.staticCustomFlag['id'], self.price, self.acc.model.Resources)
            try:
                if self.master_auid:
                    subParams = ClassDict(master_auid=[self.master_auid], flag_type=[self.acc.model.FlagInfo.FlagType], person_id=[self.acc.db.auid],
                                                                    flag_persistent_id=[self.acc.model.FlagInfo.PersistentId], guardParty=[self.guardParty])
                    self.arguments = self.arguments.arguments
                    partyAction = Party_flag(subParams, None, I=self.I, acc=self.acc, uid=self.acc.uid, request=self)
                    partyAction.onStart()
            except:
                catch()
            self.response["ok"] = 1  # success
        else:
            self.onBuyError(response, self.needGold)
            return

        self.fin()


    @action_timing
    def onBuy(self, response):
      self.onBuyFunc(response)