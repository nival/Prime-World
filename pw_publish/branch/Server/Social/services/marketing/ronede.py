# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url_reg = str(config.get("url_reg", ""))        
        
    def GetPartner(self):
        return 'ronede'
    
    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin)                    
        
    def OnFirstLogin(self, user):   
        if int(user.cregs) == 1:
            user_puid = str(user.puid)
            url = self.url_reg % (user_puid)
            self.queue.Push(url)