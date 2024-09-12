# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.ClearDynamicQuestsFromServerRequest import *

class Clear_dynamic_quests_from_server( SubAction, ClearDynamicQuestsFromServerRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "clear_dynamic_quests_from_server"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        self.I.DATA.remove("quests", "quests", {"key": {"$exists": True}}, params=None, callback=self.onRemoveDynamicQuestFromMongo)


    def onRemoveDynamicQuestFromMongo(self, response):
        if response:
            info("Response = %r", response)
            self.I.DATA.update("quests", "quests", {"last_id": {"$exists": True}}, {"last_id": 0}, params=None, callback=self.onUpdateNextQuestIndex)
        else:
            self.errorResponse("Clear_dynamic_quests_from_server failed")

    def onUpdateNextQuestIndex(self, response):
        if response:
            info("Response = %r", response)
            self.response["ok"] = 1
            self.fin()
        else:
            self.errorResponse("Clear_dynamic_quests_from_server failed")