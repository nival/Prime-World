# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url = str(config.get("url", ""))        
        
    def GetPartner(self):
        return 'zanox'
    
    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin) 
        events.OnCastleLogin.Bind(self.OnCastleLogin)    
        
    def OnFirstLogin(self, user):        
    	if int(user.cregs) == 1:
	        user_puid = str(user.puid)    
	        user_id = str(user.auid)
	        url = self.url % ("CID1",user_id,user_id,user_puid)
	        self.queue.Push(url)

    def OnCastleLogin(self, user, faction, auid):                
        user_puid = str(user.puid)
        user_id = str(auid)
        if int(user.clogins) == 1:
            url = self.url % ("CID2",user_id,user_id,user_puid)
            self.queue.Push(url)
        if int(user.clogins) == 2:
            url = self.url % ("CID3",user_id,user_id,user_puid)
            self.queue.Push(url)                    