# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url_reg = str(config.get("url_reg", ""))
        self.url_log1 = str(config.get("url_log1", ""))
        self.url_quests = config.get("url_quests", "")

    def GetPartner(self):
        return 'cpaden'

    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin)
        events.OnCastleLogin.Bind(self.OnCastleLogin)
        events.OnQuest.Bind(self.OnQuest)

    def OnFirstLogin(self, user):
        if int(user.cregs) == 1:
            url = self.url_reg % (str(user.puid))
            self.queue.Push(url)

    def OnCastleLogin(self, user, faction, auid):
        if int(user.clogins) == 1:
            url = self.url_log1 % (str(user.puid))
            self.queue.Push(url)

    def OnQuest(self, user, quid, status, tm):
        if int(user.ctutorial) == 1:
            if dict(self.url_quests).has_key(quid) and str(status) == "2":
                url = self.url_quests[quid] % (str(user.puid))
                self.queue.Push(url)