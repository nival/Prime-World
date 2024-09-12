# -*- coding: utf-8 -*-
import hashlib


class Module:
    def __init__(self, queue, config):
        self.queue = queue
        self.url_log1 = str(config.get("url_log1", ""))

    def GetPartner(self):
        return 'traforet2'

    def Install(self, events):
        events.OnCastleLogin.Bind(self.OnCastleLogin)

    def OnCastleLogin(self, user, faction, auid):
        if int(user.clogins) == 1:
            url = self.url_log1 % (str(user.subid), str(auid))
            self.queue.Push(url)