# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveGuildBuffsRequest import *

class Remove_guild_buffs( SubAction, RemoveGuildBuffsRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "remove_guild_buffs"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        for buffId, buff in self.acc.model.GuildBufs.items():
            self.acc.model.GuildBufs.remove(buffId)

        self.response["ok"] = 1
        self.fin()