# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.TradeEventBuyRequest import *

from enums.RollEventItemType import RollEventItemType

class Trade_event_buy(SubAction, TradeEventBuyRequest):
    action = "trade_event_buy"

    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        # ACTION LOGIC

        acc = self.acc
        model = acc.model

        memberIndex = self.arguments.memberIndex

        self.trade_event, event_progression, info = model.findAndGetTradeEventData(acc, self.arguments.tradeEventId)
        if not self.trade_event or not event_progression:
            self.errorResponse(info)
            return

        tradeEventGroup = self.trade_event.TradeEventGroups[self.arguments.groupIndex]
        if not tradeEventGroup:
            self.errorResponse("Can't find TradeEventGroup with TradeEvent id {}, with groupIdx {}".format(self.arguments.tradeEventId, self.arguments.groupIndex))
            return

        self.tradeEventMember = tradeEventGroup.TradeGroupMembers[memberIndex]
        if not self.tradeEventMember:
            self.errorResponse("Can't find TradeGroupMembers with TradeEvent id {}, with groupIdx {}, with memberIdx {}".format(
                                                                                                                self.arguments.tradeEventId,
                                                                                                                self.arguments.groupIndex,
                                                                                                                memberIndex))
            return

        self.price = acc.SD.emptyPrice()
        self.price.Currencies[self.tradeEventMember.CurrencyName] = self.tradeEventMember.RewardACost if self.arguments.isFirstChoice else self.tradeEventMember.RewardBCost

        if not self.acc.model.canBuy(self.price):
            self.errorResponse(EC.NOT_ENOUGH_RESOURCES, "Not enough resource for buy selected members")
            return

        reason = "PW!TRADEEVENTBUY"
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
        self.I.STATS.addResourcesChange(self.acc.auid, False, ResourceChangeItem.ContextBuyResource, "trade_event_buy", self.price,
                                        self.acc.model.Resources)

        memberReward = self.tradeEventMember.RewardA.get(0) if self.arguments.isFirstChoice else self.tradeEventMember.RewardB.get(0)
        if memberReward.ItemType == RollEventItemType.Lootbox:
            lootboxPersistentId = crc32(memberReward.PersistentId)
            isOk, lootbox = self.acc.model.addLootbox(lootboxPersistentId, self.acc)
            if not isOk:
                self.errorResponse('Wrong lootbox id trade event member group')
                return
            self.response['ok'] = 1
            self.fin()
        else:
            self.errorResponse('Unsupported reward type in trade event member group')
            return
