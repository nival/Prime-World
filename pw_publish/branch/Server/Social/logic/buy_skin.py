#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_hero import *
from logic.requests.BuySkinRequest import BuySkinRequest


class Buy_skin(SubAction, BuySkinRequest):
    """action, который будет обрабатывать данный класс"""
    action = "buy_skin"

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.PersistentId = self.arguments.PersistentId
        self.guardParty = self.arguments.guardParty
        self.master_auid = self.arguments.master_auid
        self.change_party_skin = self.arguments.change_party_skin

        validSkin, reason = self.acc.model.isValidSkin(self.PersistentId, self.acc)
        if not validSkin:
            self.errorResponse(reason)
            return

        self.static_skin = self.acc.SD.getStaticSkinByPersistentId(self.PersistentId)
        self.skinName = self.static_skin['persistentId'] + "_" + self.acc.db.fraction
        self.hero = self.acc.model.getHeroForSkin(self.static_skin, self.acc.SD)

        if not self.hero:
            self.errorResponse("Hero for skin not found")
            return

        self.price = self.acc.model.createResourcesTable(Gold=self.static_skin['cost'])
        self.config = self.acc.getConfig()
        if self.static_skin['persistentId'] in self.config.EventToolsChangeFields.SKIN_GOLD_PRICES:
            self.price.Gold = self.config.EventToolsChangeFields.SKIN_GOLD_PRICES[self.static_skin['persistentId']]

        self.needGold = int(self.price.Gold)
        reason = "PW!SKIN:" + str(self.static_skin['persistentId'])
        self.buy(self.price, self.onBuy, self.onBuyFunc, reason)
        return None

    @model_callback
    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            self.acc.model.addSkinForHero(self.PersistentId, self.hero, isDefault=True, wasBought=True,
                                          IsAnimatedAvatar=self.static_skin['persistentId'] not in self.config.SKIN_AVATAR_BLOCK)
            self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.BuySkin,
                                            "%r (id=%r)" % (self.skinName, self.hero.id), self.price,
                                            self.acc.model.Resources)

            try:
                if self.master_auid and self.change_party_skin:
                    subParams = ClassDict(master_auid=[self.master_auid], hero_id=[self.hero.getID()],
                                          hero_crc=[self.hero.PersistentId], guardParty=[self.guardParty])
                    self.arguments = self.arguments.arguments
                    self.arguments['hero_id'] = [self.hero.getID()]
                    self.arguments['hero_crc'] = [self.hero.PersistentId]
                    partyAction = Party_hero(subParams, None, I=self.I, acc=self.acc, uid=self.acc.uid, request=self)
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
