# -*- coding: utf-8 -*-
import hashlib
import time

class Module:
    def __init__(self, queue, config):
        self.queue = queue
        self.url_reg = str(config.get("url_reg", ""))
        self.url_log1 = str(config.get("url_log1", ""))
        self.url_log2 = str(config.get("url_log2", ""))
        self.url2_reg = config.get("url2_reg", "")
        self.url2_log1 = config.get("url2_log1", "")
        self.url2_log2 = config.get("url2_log2", "")
        self.url2_quests = config.get("url2_quests", "")

    def GetPartner(self):
        return 'admitad'

    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin)
        events.OnCastleLogin.Bind(self.OnCastleLogin)
        events.OnQuest.Bind(self.OnQuest)

    def OnFirstLogin(self, user):
        if int(user.cregs) == 1:
            user_puid = str(user.puid)
            puid = user_puid
            puid_list = user_puid.split('&')
            for param in puid_list:
                param_list = param.split('=')
                if param_list[0] == 'uid' and param_list[1]:
                    puid = param_list[1]
            url = self.url_reg % puid
            self.queue.Push(url)
            url2 = self.url2_reg % (str(user.puid), str(user.auid), str(time.time()))
            self.queue.Push(url2)

    def OnCastleLogin(self, user, faction, auid):
        user_puid = str(user.puid)
        user_auid = str(auid)
        puid = user_puid
        puid_list = user_puid.split('&')
        for param in puid_list:
            param_list = param.split('=')
            if param_list[0] == 'uid' and param_list[1]:
                puid = param_list[1]
        if int(user.clogins) == 1:
            url = self.url_log1 % (user_auid, puid)
            self.queue.Push(url)
            url2 = self.url2_log1 % (str(user.puid), str(user.auid), str(time.time()))
            self.queue.Push(url2)
        if int(user.clogins) == 2:
            url = self.url_log2 % (user_auid, puid)
            self.queue.Push(url)
            url2 = self.url2_log2 % (str(user.puid), str(user.auid), str(time.time()))
            self.queue.Push(url2)

    def OnQuest(self, user, quid, status, tm):
        if int(user.ctutorial) == 1:
            if dict(self.url2_quests).has_key(quid) and str(status) == "2":
                url = self.url2_quests[quid] % (str(user.puid), str(user.auid), str(time.time()))
                self.queue.Push(url)