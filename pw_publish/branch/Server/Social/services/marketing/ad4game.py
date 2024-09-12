# -*- coding: utf-8 -*-
import hashlib
import time

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url_reg = str(config.get("url_reg", ""))               
        
    def GetPartner(self):
        return 'ad4game'
    
    def Install(self, events):
        events.OnLaunchInstall.Bind(self.OnLaunchInstall)
        
    def OnLaunchInstall(self, user):
        if int(user.clinstall) == 1:
            url = self.url_reg % (str(user.puid))
            self.queue.Push(url)