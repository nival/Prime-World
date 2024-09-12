# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.NotifyTutorialStateChangedRequest import *


class Notify_tutorial_state_changed(SubAction, NotifyTutorialStateChangedRequest):
    """action, который будет обрабатывать данный класс"""
    action = "notify_tutorial_state_changed"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        debug("Notify_tutorial_state_changed: Change tutorial state %s -> %s",
              enum2String(TutorialState, self.acc.model.LordInfo.TutorialState),
              enum2String(TutorialState, self.arguments.newState))
        self.acc.model.LordInfo.TutorialState = self.arguments.newState
        self.I.STATS.addTutorialStateChange(self.acc.auid,
                                            enum2String(TutorialState, self.acc.model.LordInfo.TutorialState))

        self.response["ok"] = 1
        self.fin()
