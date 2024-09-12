# -*- coding: utf-8 -*-
class Module:

    def __init__(self, queue, config):
        self.queue = queue

    def GetPartner(self):
        return 'gameguru'
    
    def Install(self, events):
        events.OnBeginInstall.Bind(self.OnBeginInstall)

    def OnBeginInstall(self, user):
        url = "http://pix.gameguru.ru/m/С…С…С…/complete.gif"
        self.queue.Push(url) 

    