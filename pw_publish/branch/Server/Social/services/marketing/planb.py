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
        return 'planb'
    
    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin) 
        events.OnCastleLogin.Bind(self.OnCastleLogin) 
        events.OnQuest.Bind(self.OnQuest) 
        
    def OnFirstLogin(self, user):
    	if int(user.cregs) == 1:
	        user_puid = str(user.puid)    
	        url = self.url_reg + user_puid
	        self.queue.Push(url)

    def OnCastleLogin(self, user, faction, auid):
        user_puid = str(user.puid)
        if int(user.clogins) == 1:
            url = self.url_log1 + user_puid
            self.queue.Push(url)                   
            
    def OnQuest(self, user, quid, status, tm):
    	if int(user.ctutorial) == 1:
	        user_puid = str(user.puid)
	        print self.url_quests
	        if dict(self.url_quests).has_key(quid) and str(status) == "2":
	            url = str(self.url_quests[quid]) + user_puid
	            self.queue.Push(url)
        