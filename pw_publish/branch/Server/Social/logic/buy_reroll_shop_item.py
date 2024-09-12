# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.BuyRerollShopItemRequest import *
from StatisticCore.ttypes import TalentChangeOperation
from StatisticCore.ttypes import RuneRollSource
from base.helpers import *
from enums import ERerollShopResources

class Buy_reroll_shop_item( SubAction, BuyRerollShopItemRequest ):
    action = "buy_reroll_shop_item"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        self.shopItem = self.arguments.item
        self.staticItem = self.acc.SD.getStaticRerollShopItemById(self.shopItem.PersistentId)
        if not self.staticItem:
            self.errorResponse(EC.BAD_PARAM, "No item with persistentId %r found in StaticData" % self.shopItem.PersistentId)
            return

        if self.shopItem.IsBought:
            self.errorResponse(EC.REROLL_SHOP_ITEM_ALREADY_BOUGHT, "Item already bought")
            return

        if self.shopItem.IsPremium and not self.acc.model.IsPremiumAccount():
            self.errorResponse(EC.REROLL_SHOP_NO_PREMIUM, "Can't buy premium item without premium")
            return

        if self.staticItem['classType'] == "HeroRerollSlot":
            for heroId, hero in self.acc.model.Heroes.iteritems():
                if hero.PersistentId == crc32(self.staticItem['hero']['persistentId']):
                    self.errorResponse(EC.HERO_ALREADY_OWNED, "Hero already owned")
                    return

        if self.staticItem['classType'] == "SkinRerollSlot":
            hero = self.acc.model.getHeroForSkin(self.staticItem['skin'], self.acc.SD)
            if not hero:
                self.errorResponse(EC.NO_HERO_FOR_SKIN, "No hero for skin")
                return
            for skinId, skin in self.acc.model.SkinsKeeper.iteritems():
                if skin.PersistentId == crc32(self.staticItem['skin']['persistentId']):
                    self.errorResponse(EC.SKIN_ALREADY_OWNED, "Skin already owned")
                    return

        self.price = self.acc.model.getRerollShopItemPrice(self.shopItem.PriceResource, self.shopItem.Price)
        self.needGold = int(self.price.Gold)
        reason = "PW!REROLL_SHOP_ITEM:" + str(self.staticItem['persistentId'])
        self.buy( self.price, self.onBuy, self.onBuyFunc, reason )

    @model_callback
    def onBuyFunc(self, response):
        code = response["code"]
        if code == ibilling.ERROR_CODE_OK:
            self.doConfirmWriteOff(response)
            if self.staticItem['classType'] == "ResourceRerollSlot":
                amount = self.acc.SD.copyPriceFloat(self.staticItem['resource'])
                self.acc.model.sell(amount, self.acc, False)
                self.I.STATS.addResourcesChange(self.acc.auid, True, ResourceChangeItem.RerollShopBuy,
                                                "rerollshopbuy " + str(self.staticItem['persistentId']), amount, self.acc.model.Resources)
                if amount.RedPerl > 0:
                    self.acc.model.addStatisticEvent(StatisticEventType.RED_PERL_BUY, "", amount.RedPerl)
            elif self.staticItem['classType'] == "PremiumRerollSlot":
                self.acc.model.addPremiumForFree(self.staticItem['days'], self.acc)
            elif self.staticItem['classType'] == "TalentRerollSlot":
                staticTalent = self.staticItem['talent']
                arg = "{0}:{1}".format(staticTalent["persistentId"], self.shopItem.TalentLevel)
                self.acc.model.addTalentsForFree("RerollShop", [arg], self.acc, self.I.STATS, TalentChangeOperation.RerollShopBuy)
            elif self.staticItem['classType'] == "TalentsListRerollSlot":
                staticTalent = self.staticItem['talents']['Item'][self.shopItem.RandomItemId]
                arg = "{0}:{1}".format(staticTalent["persistentId"], self.shopItem.TalentLevel)
                self.acc.model.addTalentsForFree("RerollShop", [arg], self.acc, self.I.STATS, TalentChangeOperation.RerollShopBuy)
            elif self.staticItem['classType'] == "SkinRerollSlot":
                staticSkin = self.staticItem['skin']
                self.acc.model.giveSkinForFree(crc32(staticSkin['persistentId']), self.acc, withoutCheck=True)
            elif self.staticItem['classType'] == "HeroRerollSlot":
                staticHero = self.staticItem['hero']
                self.acc.model.hireHero(crc32(staticHero['persistentId']), self.acc.sex, self.I.WS, self.acc, self.I)
            elif self.staticItem['classType'] == "LampRerollSlot":
                eventInfo = self.acc.model.MarketingEventsInfo.LampEventInfo
                eventInfo.dbId = self.staticItem['lamp']['dbid']
                eventInfo.BonusLeft = self.staticItem['maxBonus']
                eventInfo.StartTime = int( round( time.time() ) )
                eventInfo.EndTime = eventInfo.StartTime + self.staticItem['lifeTime']
                eventInfo.TransactionsLeft = self.staticItem['transaction']
                rune = self.acc.model.getGoldLampType(self.acc.SD)
                self.I.STATS.addLampRoll(self.acc.auid, rune, RuneRollSource.ReRollShop)
            elif self.staticItem['classType'] == 'UpgradeHeroTalentsRerollSlot':
                eventInfo = self.acc.model.MarketingEventsInfo.UpgradeHeroTalentsInfo
                oldUsesLeft = int(eventInfo.UsesLeft)
                eventInfo.UsesLeft += self.staticItem['uses']
                self.I.STATS.addLampRoll(self.acc.auid, self.acc.model.getUpgHeroLampType(), RuneRollSource.ReRollShop, runescountold=oldUsesLeft, runescountnew=eventInfo.UsesLeft)
            elif self.staticItem['classType'] == 'LootboxRerollSlot':
                lootbox_persistent_id = self.staticItem['lootboxPersistentId']
                lootboxes_count = self.staticItem['count']
                for i in range(lootboxes_count):
                    isOk, _ = self.acc.model.addLootbox(crc32(lootbox_persistent_id), self.acc)
                    if not isOk:
                        err('bad lootbox_persistent_id {} in RerollShopSlot. RerollShopSlot persistentId: {}'.format(lootbox_persistent_id, self.staticItem['persistentId']))


            self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.RerollShopBuy, "rerollshopbuy " + str(self.staticItem['persistentId']), self.price, self.acc.model.Resources)
            self.I.STATS.addReRollShop(self.acc.auid, self.shopItem.PersistentId, self.shopItem.GroupId, self.shopItem.Price, self.shopItem.PriceResource, self.acc.model.RerollShopInfo.RerollsToday, "Premium" if self.shopItem.IsPremium else "Not Premium")

            self.shopItem.IsBought = True
            boughtItems = 0
            for _id, item in self.acc.model.RerollShopInfo.ShopItems.iteritems():
                if item.IsBought:
                    boughtItems += 1
            self.shopItem.NumBought = boughtItems
            self.response["ok"] = 1  # success
        else:
            self.onBuyError(response, self.needGold)
            return

        self.fin()


    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)