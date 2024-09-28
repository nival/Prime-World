# -*- coding: utf-8 -*-

import time

class Module:
        
    def __init__(self, queue, config):
        self.queue = queue        
        self.url = str(config.get("url", ""))
        self.xml = '<?xml version="1.0" encoding="UTF-8" ?><request><referal_uid>%s</referal_uid><id>%s</id>%s</request>'             
        
    def GetPartner(self):
        return 'advaction'        
    
    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin) 
        events.OnCastleLogin.Bind(self.OnCastleLogin)            
        
    def OnFirstLogin(self, user):  
    	if int(user.cregs) == 1:       
	        user_puid = str(user.puid)   
	        user_id = str(user.auid)
	        timestamp = int(time.time())
	        register_node = "<registration>%d</registration>"%timestamp
	        data = self.xml % (user_puid,user_id,register_node)
	        self.queue.Push(self.url,data)

    def OnCastleLogin(self, user, faction, auid):                
        user_puid = str(user.puid)   
        user_id = str(auid)
        timestamp = int(time.time())
        if int(user.clogins) == 1:
            flogin_node = "<first_login>%d</first_login>"%timestamp
            data = self.xml % (user_puid,user_id,flogin_node)
            self.queue.Push(self.url,data)
        if int(user.clogins) == 2:
            slogin_node = "<second_login>%d</second_login>"%timestamp
            data = self.xml % (user_puid,user_id,slogin_node)
            self.queue.Push(self.url,data)