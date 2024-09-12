# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.NotifySessionEndedRequest import *


class Notify_session_ended(SubAction, NotifySessionEndedRequest):
    """action, который будет обрабатывать данный класс"""
    action = "notify_session_ended"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        if self.acc.model.LordInfo.TutorialState <= TutorialState.ClientReturnedFromSession:
            debug("Notify_session_ended: Change tutorial state %s -> %s",
                  enum2String(TutorialState, self.acc.model.LordInfo.TutorialState), enum2String(TutorialState, TutorialState.ClientReturnedFromSession))
            self.acc.model.LordInfo.TutorialState = TutorialState.ClientReturnedFromSession
            self.I.STATS.addTutorialStateChange(self.acc.auid,  enum2String(TutorialState, self.acc.model.LordInfo.TutorialState))

        self.response["ok"] = 1
        self.fin()
