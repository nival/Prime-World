# -*- coding: utf-8 -*-
import hashlib

class Module:

    def __init__(self, queue, config):
        self.queue = queue        

    def GetPartner(self):
        return 'cbn'
    
    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin)         

    def OnFirstLogin(self, user):
    	if int(user.cregs) == 1:
	        tracker_url = str(user.subid)
	        partner_params = str(user.puid)
	        partner_params = partner_params.replace("(|)","&")        
	        self.queue.Push(tracker_url+"&"+partner_params)                   