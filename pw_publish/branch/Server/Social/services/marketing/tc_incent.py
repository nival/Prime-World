# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url_quests = config.get("url_quests", "")
        self.url_log2 = str(config.get("url_log2", ""))
        
    def GetPartner(self):
        return 'tc_incent'
    
    def Install(self, events):
        events.OnCastleLogin.Bind(self.OnCastleLogin)
        events.OnQuest.Bind(self.OnQuest)

    def OnCastleLogin(self, user, faction, auid):
        if int(user.clogins) == 2:
            url = self.url_log2 % (str(user.puid))
            self.queue.Push(url)

    def OnQuest(self, user, quid, status, tm):
        if int(user.ctutorial) == 1:
            user_puid = str(user.puid)
            if dict(self.url_quests).has_key(quid) and str(status) == "2":
                url = self.url_quests[quid] % (user_puid)
                self.queue.Push(url)