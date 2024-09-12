# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.AddGuildBuffRequest import *

class Add_guild_buff( SubAction, AddGuildBuffRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "add_guild_buff"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        """стартовый метод для обработки action"""
        self.log()
        if not self.checkParams():
            return

        staticBuff = self.acc.SD.getGuildBufById(self.arguments.persistentId)
        if not staticBuff:
            self.errorResponse(EC.BAD_PARAM, "Can't find buff with id %d", self.arguments.persistentId)
            return

        expireTime = int(time.time() + int(staticBuff['duration']))
        self.acc.model.addGuildBuff(self.acc, self.acc.SD, expireTime, staticBuff)
        self.response["ok"] = 1
        self.fin()