# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url_reg = str(config.get("url_reg", ""))
        self.url_log1 = str(config.get("url_log1", ""))
        self.url_log2 = str(config.get("url_log2", ""))
        
    def GetPartner(self):
        return 'actionpay'
    
    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin) 
        events.OnCastleLogin.Bind(self.OnCastleLogin)    
        
    def OnFirstLogin(self, user):
    	if int(user.cregs) == 1:
	        user_id = str(user.auid)
	        user_puid = str(user.puid)    
	        url = self.url_reg + user_puid + '&apid=reg' + user_id
	        self.queue.Push(url)

    def OnCastleLogin(self, user, faction, auid):
        user_id = str(auid)
        user_puid = str(user.puid)
        if int(user.clogins) == 1:
            url = self.url_log1 + user_puid + '&apid=1log' + user_id
            self.queue.Push(url)
        if int(user.clogins) == 2:
            url = self.url_log2 + user_puid + '&apid=2log' + user_id
            self.queue.Push(url)                    