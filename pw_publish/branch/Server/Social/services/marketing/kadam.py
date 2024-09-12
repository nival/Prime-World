# -*- coding: utf-8 -*-
import hashlib

class Module:

    def __init__(self, queue, config):
        self.queue = queue     
        self.url_track = str(config.get("url_track", ""))   

    def GetPartner(self):
        return 'kadam'
    
    def Install(self, events):
        events.OnCastleLogin.Bind(self.OnCastleLogin)         

    def OnCastleLogin(self, user, faction, auid):                        
        if int(user.clogins) == 1:
            url = self.url_track % (str(user.puid))
            self.queue.Push(url)              