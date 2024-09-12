# -*- coding: utf-8 -*-
from email.Utils import formatdate
import urllib

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url = str(config.get("url", ""))

    def GetPartner(self):
        return None

    def Install(self, events):
        events.OnLandingRegister.Bind(self.OnLandingRegister)                 
        
    def OnLandingRegister(self, user):
        url = self.url + "?event=site_register&session=" + str(user.muid) + "&auid=" + str(user.auid) + "&partner_id=" + str(user.partner)
        self.queue.Push(url)         
  
        
        
