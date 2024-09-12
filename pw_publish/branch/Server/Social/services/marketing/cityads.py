# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url = str(config.get("url", ""))
        self.partner_id = config.get("partner_id", "")
        self.max_login_count = config.get("max_login_count", "5")

    def GetPartner(self):
        return 'cityads'
    
    def Install(self, events):
        events.OnLandingRegister.Bind(self.OnLandingRegister)
        events.OnFirstLogin.Bind(self.OnFirstLogin) 
        events.OnCastleLogin.Bind(self.OnCastleLogin)

    def OnLandingRegister(self, user):
        user_id = str(user.muid)
        user_prx = str(user.puid)
        full_url = self.url + 'service/postback?id=' + user_id + '&prx=' + user_prx
        self.queue.Push(full_url) 

    def OnFirstLogin(self, user):
        if int(user.cregs) == 1:
            user_id = str(user.muid)
            user_prx = str(user.puid)
            url = self.url + 'service/postback?id=' + user_id + '&prx=' + user_prx + '&eff_reg=1'
            self.queue.Push(url)

    def OnCastleLogin(self, user, faction, auid):
        user_id = str(user.muid)
        user_prx = str(user.puid)
        count_logins = str(user.clogins)
        last_login_timestamp = str(int(time.time()))
        if int(user.clogins) <= int(self.max_login_count):
            url = self.url + 'service/postback?id=' + user_id + '&prx=' + user_prx + '&auth_count=' + count_logins + '&last_login=' + last_login_timestamp
            self.queue.Push(url) 
        