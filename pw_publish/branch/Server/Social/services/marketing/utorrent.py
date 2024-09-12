# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue        
        self.url_log = str(config.get("url_log", ""))
        
    def GetPartner(self):
        return 'utorrent'        
    
    def Install(self, events):        
        events.OnCastleLogin.Bind(self.OnCastleLogin)                     
        
    def OnCastleLogin(self, user, faction, auid):
        user_id = str(auid)
        user_puid = str(user.puid)
        if int(user.clogins) == 1:
            url = self.url_log % (str(user.puid))
            self.queue.Push(url)          
             