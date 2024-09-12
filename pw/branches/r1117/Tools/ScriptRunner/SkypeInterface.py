import time
import Skype4Py
SkypeUsers = {'Matt' : 'matt7-11', 'Oleg' : 'oleg.talalov', 'EugBel' : 'eugbel', 'Lorifel' : 'sc-lorifel', 'TestSrv' : 'DiTestSrv'}
#PersonsList=['Matt', 'Oleg', 'EugBel']
#Nicks = [SkypeUsers[x] for x in PersonsList]

class SkypeManager():
    def __init__(self, onMessage = None):
        self.skype = Skype4Py.Skype()
        if not self.skype.Client.IsRunning:
            print 'Starting Skype..'
            self.skype.Client.Start()
            time.sleep(15)
        self.skype.Attach()
        self.chat = self.skype.BookmarkedChats[0]
        if onMessage:
            self.skype.OnMessageStatus = onMessage
            print('Message-handling function was attached successfully')

    def sendMessage(self, msg):
        self.chat.SendMessage(msg)