# -*- coding: utf-8 -*-
import sys

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url = str(config.get("url", ""))
        self.project_id = str(config.get("project_id", ""))

    def GetPartner(self):
        return 'playground'
    
    def Install(self, events):
        events.OnFirstCastleLogin.Bind(self.OnFirstCastleLogin)

    def OnFirstCastleLogin(self, user, faction):
        user_prx = str(user.puid)
        full_url = self.url % (self.project_id,user_prx)
        self.queue.Push(full_url) 

