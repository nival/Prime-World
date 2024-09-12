# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.TradeEventGiveRewardRequest import *


class Trade_event_give_reward( SubAction, TradeEventGiveRewardRequest ):
    action = "trade_event_give_reward"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
          return

        event = self.acc.getConfigValue("TradeEvents")[self.arguments.tradeEventId]

        if not event:
            self.errorResponse('Event is null with persistentId: {}'.format(self.arguments.tradeEventId))
            return

        experience = self.acc.model.recalcTradeEventExperience(event)

        isOk, resultInfo = self.acc.model.checkExperienceRewardsInTradeEventAndGiveIfNeeded(self.acc, event, experience)
        if not isOk:
            self.errorResponse('Error in checkExperienceRewardsInTradeEventAndGiveIfNeeded method: {}'.format(resultInfo))
            return

        self.I.WS.updateTradeEventExperience(self.acc.auid,
                                             event.Guid,
                                             experience,
                                             callback=lambda x: self.getTradeEventPlaceInWorld(event.Guid))

    @action_timing
    def getTradeEventPlaceInWorld(self, event_guid):
        self.I.WS.getTradeEventPlace(self.acc.auid, event_guid, callback=lambda x: self.onGetPlace(event_guid, x))

    @action_timing
    def onGetPlace(self, event_guid, sql_reply):
        self.setPlaceToMD(event_guid, sql_reply)

    @model_callback
    def setPlaceToMD(self, event_guid, sql_reply):
        reply = sql_reply['r']
        placeInWorld = 0
        if reply:
            placeInWorld = int(reply[0]['place'])

        self.acc.model.TradeEvents[event_guid].PlayerPlace = placeInWorld

        self.response["ok"] = 1
        self.fin()
