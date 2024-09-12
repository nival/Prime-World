# -*- coding: utf-8 -*-
import sys

from modeldata.StaticData import StaticData
from subaction import *
from logic.requests.DbgTradeEventClearRequest import *

class Dbg_trade_clear_remove(SubAction, DbgTradeEventClearRequest):
    action = "dbg_trade_clear_remove"

    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        # ACTION LOGIC

        #todo: take custom currencies from event

        trade_event, progression, info = self.acc.model.findAndGetTradeEventData(self.acc, self.arguments.tradeEventId, validating=True)
        if not trade_event or not progression:
            self.errorResponse(info)
            return

        while len(progression.CollectedLootboxes):
            progression.CollectedLootboxes.pop()

        tradeEventAllMembers = [member for _, group in trade_event.TradeEventGroups.iteritems() for _, member in group.TradeGroupMembers.iteritems()]
        currenciesNamesFromSD = map(lambda e: e['Id'], self.acc.SD.data['currencies']['CurrencyList']['Item'])
        allCurrenciesInEvent = map(lambda e: e.CurrencyName, tradeEventAllMembers)
        allCurrenciesInEvent.append(trade_event.ExperienceCurrencyName)

        price = StaticData.emptyPrice()
        for currencyName in allCurrenciesInEvent:
            if currencyName not in currenciesNamesFromSD:
                self.errorResponse(info)
                return
            price.Currencies[currencyName] = -self.acc.model.Resources.Currencies[currencyName] if currencyName in self.acc.model.Resources.Currencies else 0
        self.acc.model.sell(price, None, False)

        self.response["ok"] = 1
        self.fin()
