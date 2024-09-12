# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url_reg = str(config.get("url_reg", ""))               
        
    def GetPartner(self):
        return 'wolf'
    
    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin)            
        
    def OnFirstLogin(self, user): 
    	if int(user.cregs) == 1:               
	        url = self.url_reg % (str(user.puid),str(user.auid))
	        self.queue.Push(url)