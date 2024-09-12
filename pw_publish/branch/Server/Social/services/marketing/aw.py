# -*- coding: utf-8 -*-
import hashlib
import time


class Module:
    def __init__(self, queue, config):
        self.queue = queue
        self.option_cid = str(config.get("cid", ""))
        self.option_tid = str(config.get("tid", ""))

        self.url_reg = str(config.get("url_reg", ""))
        self.url_log1 = str(config.get("url_log1", ""))

    def GetPartner(self):
        return 'aw'

    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin)
        events.OnCastleLogin.Bind(self.OnCastleLogin)

    def OnFirstLogin(self, user):
        if int(user.cregs) == 1:
            url = self.url_reg % (self.option_cid, self.option_tid, str(user.puid))
            self.queue.Push(url)

    def OnCastleLogin(self, user, faction, auid):
        if int(user.clogins) == 1:
            url = self.url_log1 % (self.option_cid, self.option_tid, str(user.puid))
            self.queue.Push(url)
