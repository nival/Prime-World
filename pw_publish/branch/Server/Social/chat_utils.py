from base.helpers import *
import hashlib
import party_const

def generateKey(auid, uid, server):
    m = hashlib.md5()
    m.update(str(auid)+str(uid)+str(server))
    key = m.hexdigest()
    if uid % 2 == 0:
        return key[:len(key)/2]
    else:
        return key[len(key)/2:]

class ChatAddCallback:

    def __init__(self, acc, callback):
        self.acc = acc
        self.callback = callback

    def __call__(self, response):
        info( "onChatAddUser: response %s" % str(response) )
        if response and response.get("ok"):
            self.acc.chat = { 
                'host' : response['host'], 
                'key' : response['key'],
            }
        if self.callback:
            self.callback(response)

def addToChat(chatApi, _fraction, acc, serverId, callback=None, guildshortname=None):
    fraction = party_const.getPartyFraction(_fraction)
    nick = acc.getNickname()
    # print acc.auid, nick, fraction, acc.fraction, _fraction, acc.db, acc.chat
    # decorate
    if guildshortname:
        nick = "["+guildshortname+"]"+" "+nick
    if acc.auid and nick and fraction != party_const.PARTY_FRACTION.NONE:
        key = generateKey(acc.auid, acc.uid, serverId)
        info( "addUser to chat (auid=%s uid=%s nick=%r fraction=%d muted=%d mutetime=%d)" %
              (acc.auid, acc.uid, nick, fraction, acc.db.muted, acc.db.mutetime)  )
        chatApi.addUser(acc.auid, key, nick, fraction, acc.db.muted, acc.db.mutetime, acc.locale, ChatAddCallback(acc, callback))
        return True
    return False
