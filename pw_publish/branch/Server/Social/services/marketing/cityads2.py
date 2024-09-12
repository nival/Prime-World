# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url_reg = str(config.get("url_reg", ""))
        self.url_quests = config.get("url_quests", "")
        
    def GetPartner(self):
        return 'cityads2'
    
    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin)            
        events.OnQuest.Bind(self.OnQuest) 
        
    def OnFirstLogin(self, user): 
    	if int(user.cregs) == 1:       
	        user_puid = str(user.puid)    
	        user_id = str(user.auid)
	        url = self.url_reg % (user_id,user_puid)
	        self.queue.Push(url)

    def OnQuest(self, user, quid, status, tm):
    	if int(user.ctutorial) == 1:
	        user_puid = str(user.puid)
	        user_id = str(user.auid)        
	        if dict(self.url_quests).has_key(quid) and str(status) == "2":
	            url = self.url_quests[quid] % (user_id,user_puid)
	            self.queue.Push(url)                    