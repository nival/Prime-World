#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from party_action import *
from logic.requests.PartyAcceptRequest import PartyAcceptRequest
from itertools  import ifilter
class Party_accept( Party_action, PartyAcceptRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "party_accept"

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        # для party.accept требуется инфа о бане игрока за лив, берется из ModelData
        banEndTime = self.acc.model.getBanEndTime()
        if banEndTime <= int( time.time() ):
            banEndTime = 0
        self.addArguments(banEndTime=banEndTime)

        flagType = self.acc.model.FlagInfo.FlagType
        self.addArguments(flagType=flagType)

        flagPersistentId = self.acc.model.FlagInfo.PersistentId
        self.addArguments(flagPersistentId=flagPersistentId)

        isMMAllowed = self.acc.db.isRegularMMAllowed
        self.addArguments(isMMAllowed=isMMAllowed)

        isInventoryFull = self.acc.model.isInventoryFull()
        self.addArguments(isInventoryFull=isInventoryFull)

        leaver = True if LordStatus.Leaver == self.acc.model.getInternalUserStatus(self.acc.getConfig()) else False
        self.addArguments(isLeaver=leaver)

        tournamentDynQuestId , dependedTournamentQuests = self.acc.model.getActualTournamentQuestPersistentId()
        self.addArguments(tournamentDynQuestId=tournamentDynQuestId)
        self.addArguments(dependedTournamentQuests=dependedTournamentQuests)

        return Party_action.onStart(self)