# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.OpenLootboxRequest import *

class Open_lootbox( SubAction, OpenLootboxRequest ):
    """
    action, который будет обрабатывать данный класс

    internal roll_result format:
        'talents' as list of tuples (id, points)
        'resource' as tuple (type, custom_id, value)
    """
    action = "open_lootbox"

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
          return

        #ACTION LOGIC
        lootbox = self.arguments.lootbox
        if lootbox.Reward.IsApplied:
            self.errorResponse("Lootbox %i is opened" % lootbox.id)
            return
        static_lootbox_id = lootbox.PersistentId
        static_lootbox = self.acc.SD.getStaticLootboxById(static_lootbox_id)
        if not static_lootbox:
            self.errorResponse("StaticLootbox with id %i not found" % static_lootbox_id)
            return
        roll_result = None
        try:
            roll_result = self.acc.model.openLootbox(self.acc, static_lootbox)
        except NotImplementedError as e:
            self.errorResponse(e.message)
            return
        self.acc.model.applyLootboxRoll(self.acc, self.I, self.I.STATS, 'open_lootbox', lootbox, roll_result)

        self.response["ok"] = 1
        self.fin()