# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SeasonEventBuyItemRequest import *

class Season_event_buy_item(SubAction, SeasonEventBuyItemRequest):
    action = "season_event_buy_item"

    event_guid = None
    itemId = -1
    item = None
    boughtCount = -1
    price = None

    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        # ACTION LOGIC

        acc = self.acc
        model = acc.model

        itemIndex = self.arguments.itemIndex

        available_season_events = self.acc.getConfigValue("SeasonEvents")
        if self.arguments.seasonEventId not in available_season_events:
            self.errorResponse('Event with persistentId {} is not in a list of available season events'.format(
                self.arguments.seasonEventId))
            return

        event = available_season_events[self.arguments.seasonEventId]

        if not event:
            self.errorResponse('Event with persistentId {} is null'.format(self.arguments.seasonEventId))
            return

        if event.EndTimestamp < self.acc.model.FatClientServerTime:
            self.errorResponse('Event with persistentId {} is not active anymore'.format(self.arguments.seasonEventId))
            return

        if event.Guid not in self.acc.model.SeasonEvents:
            self.errorResponse("There isn't progression for event with Guid {} in user data".format(self.event.Guid))
            return

        self.event_guid = event.Guid

        shopGroup = event.SeasonEventShopGroups[self.arguments.groupIndex]
        if not shopGroup:
            self.errorResponse("Can't find SeasonEventShopGroup with SeasonEvent id {}, with groupIdx {}".format(self.arguments.seasonEventId, self.arguments.groupIndex))
            return

        self.item = shopGroup.Items[itemIndex]
        if not self.item:
            self.errorResponse("Can't find SeasonEventShopItem with SeasonEvent id {}, with groupIdx {}, with intemIdx {}".format(
                                                                                                                self.arguments.seasonEventId,
                                                                                                                self.arguments.groupIndex,
                                                                                                                itemIndex))
            return

        self.itemId = '{0}'.format(self.arguments.groupIndex*1000+self.arguments.itemIndex)
        self.boughtCount = int(model.SeasonEvents[self.event_guid].BoughtItems.get(self.itemId, 0))
        if self.item.Limit != -1 and self.boughtCount >= self.item.Limit:
            self.errorResponse(
                "SeasonEventShopItem buy limit was reached with SeasonEvent id {}, with groupIdx {}, with intemIdx {}, boughtCount {}, limit {}".format(
                    self.arguments.seasonEventId, self.arguments.groupIndex, itemIndex, self.boughtCount, self.item.Limit))
            return

        self.price = acc.SD.emptyPrice()
        self.price.Currencies[event.ShopCurrencyId] = self.item.Cost

        if not self.acc.model.canBuy(self.price):
            self.errorResponse(EC.NOT_ENOUGH_RESOURCES, "Not enough resource for buy selected members")
            return

        reason = "PW!SEASONEVENTBUY"
        self.buy(self.price, self.onBuy, self.onBuyFunc, reason)

    @action_timing
    def onBuy(self, response):
        self.onBuyFunc(response)

    @model_callback
    def onBuyFunc(self, response):
        code = response['code']
        if code != ibilling.ERROR_CODE_OK:
            self.onBuyError(response, 0)
            return

        self.doConfirmWriteOff(response)
        self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.ContextBuyResource, "season_event_buy",
                                        self.price, self.acc.model.Resources)

        self.acc.model.SeasonEvents[self.event_guid].BoughtItems.set(self.itemId, self.boughtCount + 1)

        lootboxPersistentId = crc32(self.item.LootboxPersistentId)
        isOk, lootbox = self.acc.model.addLootbox(lootboxPersistentId, self.acc)
        if not isOk:
            self.errorResponse('Wrong lootbox id ({}) in season event shop group'.format(self.item.LootboxPersistentId))
            return
        self.response['ok'] = 1
        self.fin()

