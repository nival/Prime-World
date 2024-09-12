# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SeasonEventGiveRewardRequest import *


class Season_event_give_reward(SubAction, SeasonEventGiveRewardRequest):
    action = "season_event_give_reward"

    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        available_season_events = self.acc.getConfigValue("SeasonEvents")
        if self.arguments.seasonEventId not in available_season_events:
            self.errorResponse('Event with persistentId {} is not in a list of available season events'.format(self.arguments.seasonEventId))
            return

        self.event = available_season_events[self.arguments.seasonEventId]

        if not self.event:
            self.errorResponse('Event with persistentId {} is null'.format(self.arguments.seasonEventId))
            return

        if self.event.EndTimestamp < self.acc.model.FatClientServerTime:
            self.errorResponse('Event with persistentId {} is not active anymore'.format(self.arguments.seasonEventId))
            return

        if self.event.Guid not in self.acc.model.SeasonEvents:
            self.errorResponse("There isn't progression for event with Guid {} in user data".format(self.event.Guid))
            return

        self.progress = self.acc.model.recalcSeasonEventProgress(self.event)

        if self.acc.model.SeasonEvents[self.event.Guid].PlayerProgress >= self.progress:
            self.response["ok"] = 1
            self.fin()
        else:
            self.I.WS.updateSeasonEventProgress(self.acc.auid, self.event.Guid, self.progress,
                                             callback=lambda x: self.getSeasonEventPlaceInWorld())

    @action_timing
    def getSeasonEventPlaceInWorld(self):
        self.I.WS.getSeasonEventPlace(self.acc.auid, self.event.Guid, callback=lambda x: self.onGetPlace(x))

    @action_timing
    def onGetPlace(self, sql_reply):
        self.setPlaceToMD(sql_reply)

    @model_callback
    def setPlaceToMD(self, sql_reply):
        reply = sql_reply['r']
        placeInWorld = 0
        if reply:
            placeInWorld = int(reply[0]['place'])

        isOk, resultInfo = self.acc.model.checkProgressRewardsInSeasonEventAndGiveIfNeeded(self.acc, self.event, self.progress)
        if not isOk:
            self.errorResponse(
                'Error in checkProgressRewardsInSeasonEventAndGiveIfNeeded method: {}'.format(resultInfo))
            return

        self.acc.model.SeasonEvents[self.event.Guid].PlayerProgress = self.progress
        self.acc.model.SeasonEvents[self.event.Guid].PlayerPlace = placeInWorld

        self.response["ok"] = 1
        self.fin()
