# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url_quests = config.get("url_quests", "")
        
    def GetPartner(self):
        return 'wasd'
    
    def Install(self, events):
        events.OnQuest.Bind(self.OnQuest)

    def OnQuest(self, user, quid, status, tm):
        if int(user.ctutorial) == 1:
            if dict(self.url_quests).has_key(quid) and str(status) == "2":
                url = self.url_quests[quid] % (str(user.puid))
                self.queue.Push(url)