# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url_reg = str(config.get("url_reg", ""))
        self.url_login = str(config.get("url_login", "")) 
        self.url_quests = config.get("url_quests", "")       
        
    def GetPartner(self):
        return 'socialleads2'
    
    def Install(self, events):
        events.OnFirstLogin.Bind(self.OnFirstLogin) 
        events.OnCastleLogin.Bind(self.OnCastleLogin) 
        events.OnQuest.Bind(self.OnQuest)   
        
    def OnFirstLogin(self, user):   
        if int(user.cregs) == 1:
            user_auid = hashlib.md5(str(user.auid)).hexdigest()
            user_puid = str(user.puid)
            url = self.url_reg % (user_puid,user_auid)
            self.queue.Push(url)

    def OnCastleLogin(self, user, faction, auid):                
        user_auid = hashlib.md5(str(auid)).hexdigest()
        user_puid = str(user.puid)    
        if int(user.clogins) == 2:
            url = self.url_login % (user_puid,"login2",user_auid)
            self.queue.Push(url)  

    def OnQuest(self, user, quid, status, tm):
        if int(user.ctutorial) == 1:
            user_puid = str(user.puid)
            user_auid = hashlib.md5(str(user.auid)).hexdigest()
            if dict(self.url_quests).has_key(quid) and str(status) == "2":
                url = self.url_quests[quid] % (user_puid,"login",user_auid)
                self.queue.Push(url)