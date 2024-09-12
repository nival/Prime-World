# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url_reg = str(config.get("url_reg", ""))
        self.url_log = str(config.get("url_log", ""))
        
    def GetPartner(self):
        return 'glispa'        
    
    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin)
        events.OnCastleLogin.Bind(self.OnCastleLogin)         
        
    def OnFirstLogin(self, user): 
    	if int(user.cregs) == 1:               
	        url = self.url_reg % (str(user.puid),str(user.auid))
	        self.queue.Push(url)
        
    def OnCastleLogin(self, user, faction, auid):
        user_id = str(user.auid)
        user_puid = str(user.puid)
        if int(user.clogins) == 1:
            url = self.url_log % (str(user.puid),str(auid),2)
            self.queue.Push(url)
        if int(user.clogins) == 2:
            url = self.url_log % (str(user.puid),str(auid),3)
            self.queue.Push(url)    
             