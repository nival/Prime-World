# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue        
        
    def GetPartner(self):
        return 'testpartner'
    
    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin) 
        events.OnCastleLogin.Bind(self.OnCastleLogin)
        events.OnQuest.Bind(self.OnQuest)    
        
    def OnFirstLogin(self, user): 
    	if int(user.cregs) == 1:	       
			print user.cregs        

    def OnCastleLogin(self, user, faction, auid):                
        print user.clogins    
        
    def OnQuest(self, user, quid, status, tm):
    	print user.ctutorial                    