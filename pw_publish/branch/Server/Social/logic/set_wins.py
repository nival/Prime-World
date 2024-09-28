#!/usr/bin/env python
# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetWinsRequest import SetWinsRequest


class Set_wins(SubAction, SetWinsRequest):
    """action, который будет обрабатывать данный класс"""
    action = "set_wins"
    debug = True

    @model_callback
    @parse
    @action_timing
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.acc.model.LordInfo.GuardInfo.NumberOfWins = self.arguments.wins
        self.acc.model.LordInfo.Ratings.NumberOfWinsForPR = self.arguments.wins

        self.response["ok"] = 1
        self.fin()
