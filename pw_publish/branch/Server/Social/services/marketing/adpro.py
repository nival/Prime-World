# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue        
        self.url_log1 = str(config.get("url_log1", ""))        
        
    def GetPartner(self):
        return 'adpro'
    
    def Install(self, events):        
        events.OnCastleLogin.Bind(self.OnCastleLogin)                

    def OnCastleLogin(self, user, faction, auid):                
        user_puid = str(user.puid)        
        if int(user.clogins) == 1:
            url = self.url_log1 % (user_puid,str(auid))
            self.queue.Push(url)