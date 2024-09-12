# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.EndCurrentGuildWarEvent import *

class End_current_guild_war_event( SubAction, EndCurrentGuildWarEvent ):
    """ завершает текущий клановый ивент """
    action = "end_current_guild_war_event"
    debug = True

    @model_callback
    @parse
    def onStart(self):
        self.log()

        if not self.checkParams():
          return

        self.I.WS.addNewGuildWarEvent()

        self.response["ok"] = 1
        self.fin()