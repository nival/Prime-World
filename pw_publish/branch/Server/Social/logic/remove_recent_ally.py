# -*- coding: utf-8 -*-
import sys
from subaction import *
from logic.requests.RemoveRecentAllyRequest import *

class Remove_recent_ally(SubAction, RemoveRecentAllyRequest):
    """удаляем человека из списка тех, с кем недавно играли"""
    action = "remove_recent_ally"
  
    @model_callback
    @parse
    def onStart(self):
        self.log()
        if not self.checkParams():
            return

        self.I.FRIENDS.removeRecentAlly(self.acc.auid, self.arguments.allyAuid, self.onAllyRemoved)

    def onAllyRemoved(self, response):
        if response and response.get("ok", 0):
            info("RemoveRecentAllyRequest.onAllyRemoved: %r" % response)
            self.response["ok"] = 1
            self.fin()
            return
        self.errorResponse(EC.FRIEND_SERVER_CRASHED, "Friend not found")