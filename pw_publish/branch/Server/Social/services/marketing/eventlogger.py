# -*- coding: utf-8 -*-
from email.Utils import formatdate
import urllib

class Module:

    def __init__(self, queue, config):
        self.queue = queue
        self.url = str(config.get("url", ""))
        self.max_login_count = config.get("max_login_count", "5")
        self.quest_to_send = config.get("quests_to_send","")
        self.muid_presets = config.get("muid_presets","")

    def GetPartner(self):
        return None

    def Install(self, events):
        events.OnLinkPartner.Bind(self.OnLinkPartner)      
        events.OnBeginInstall.Bind(self.OnBeginInstall)
        events.OnEndInstall.Bind(self.OnEndInstall)
        events.OnReInstall.Bind(self.OnReInstall)
        events.OnUnInstall.Bind(self.OnUnInstall)
        events.OnLaunchInstall.Bind(self.OnLaunchInstall)
        events.OnCancelInstall.Bind(self.OnCancelInstall)
        events.OnLandingRegister.Bind(self.OnLandingRegister)
        events.OnFirstLogin.Bind(self.OnFirstLogin)        
        events.OnDownloadClientBegin.Bind(self.OnDownloadClientBegin)
        events.OnDownloadClientEnd.Bind(self.OnDownloadClientEnd)
        events.OnCastleLogin.Bind(self.OnCastleLogin)
        events.OnPayment.Bind(self.OnPayment)  
        events.OnQuest.Bind(self.OnQuest)      
        
    def OnLinkPartner(self, user):
        if user.subid:
            url = self.url + "?event=visit&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid) + "&partner=" + str(user.partner) + "&subid=" + str(user.subid)
        else:
            url = self.url + "?event=visit&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid) + "&partner=" + str(user.partner)
        self.queue.Push(url)       
        
    def OnBeginInstall(self, user):
        url = self.url + "?event=install_start&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid)
        self.queue.Push(url)

    def OnEndInstall(self, user):
        url = self.url + "?event=install_finish&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid)
        self.queue.Push(url)   

    def OnUnInstall(self, user):
        url = self.url + "?event=install_uninstall&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid)
        self.queue.Push(url)   

    def OnReInstall(self, user):
        url = self.url + "?event=install_reinstall&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid)
        self.queue.Push(url)           

    def OnLaunchInstall(self, user):
        url = self.url + "?event=install_launch&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid)
        self.queue.Push(url)  
        
    def OnCancelInstall(self, user):
        url = self.url + "?event=install_cancel&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid)
        self.queue.Push(url)          
        
    def OnLandingRegister(self, user):
        url = self.url + "?event=register&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid) + "&auid=" + str(user.auid)
        self.queue.Push(url)         

    def OnFirstLogin(self, user):
        if user.partner in self.muid_presets:       
            url = self.url + "?event=visit&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid) + "&partner=" + str(user.partner)
            self.queue.Push(url)
        url = self.url + "?event=register&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid) + "&auid=" + str(user.auid)
        self.queue.Push(url)                 

    def OnDownloadClientBegin(self, user):
        url = self.url + "?event=update_start&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid)
        self.queue.Push(url) 
        
    def OnDownloadClientEnd(self, user):
        url = self.url + "?event=update_finish&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid)
        self.queue.Push(url) 
        
    def OnCastleLogin(self, user, faction, auid):
        url = self.url + "?event=login&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid) + "&auid=" + str(auid)
        self.queue.Push(url)        

    def OnPayment(self, user, cvalue, source, ovalue):
        url = self.url + "?event=user_payed&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid) + "&auid=" + str(user.auid) + "&amount=" + str(ovalue)
        self.queue.Push(url)    
        
    def OnQuest(self, user, quid, status, tm):      
        if dict(self.quest_to_send).has_key(quid) and str(status) == "2":
            url = self.url + "?event=quest_end&timestamp=" + urllib.quote_plus(formatdate()) + "&session=" + str(user.muid) + "&auid=" + str(user.auid) + "&questid="+str(quid)
            self.queue.Push(url)       
        
        
