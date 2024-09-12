# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.SetGuildBuffDurationRequest import *

class Set_guild_buff_duration( SubAction, SetGuildBuffDurationRequest ):
    """action, который будет обрабатывать данный класс"""
    action = "set_guild_buff_duration"
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

        for buffId, buff in self.acc.model.GuildBufs.iteritems():
            if buff.PersistentId == self.arguments.persistentId:
                buff.ExpireTime = int(time.time()) + self.arguments.duration

        self.response["ok"] = 1
        self.fin()