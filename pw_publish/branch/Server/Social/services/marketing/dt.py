# -*- coding: utf-8 -*-
import hashlib

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.reg_url = str(config.get("reg_url", ""))
        self.log_url = str(config.get("log_url", ""))

    def GetPartner(self):
        return 'dt'
    
    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin) 
        events.OnFirstCastleLogin.Bind(self.OnFirstCastleLogin)

    def OnFirstLogin(self, user):
    	if int(user.cregs) == 1:
	        affiliate_id = str(user.subid)
	        full_url = self.reg_url + affiliate_id
	        self.queue.Push(full_url)       
        
    def OnFirstCastleLogin(self, user, faction):
        affiliate_id = str(user.subid)
        full_url = self.log_url + affiliate_id
        self.queue.Push(full_url)