import sandbox
import logging
import sys
import base64
import time

'''
{
    "password": "436795320",
    "login_url": "https://www.facebook.com/platform/test_account_login.php?user_id=100003376225119&n=9pyBm0THYOZ4JQy",
    "id": "100003376225119",
    "email": "sandman_xvygvyw_sandman@tfbnw.net"
}
'''

def PingChat(chat):
    if chat:
        msg = chat.ping()
        if msg.response.ec == 0:
            text = base64.b64decode(msg.response.chat)
            if text:
                logging.debug(text)

def LoginFB(url, snuid, sntoken):
    chat = None
    ss = sandbox.Caller(url, ver='0.0.0')
    ss.SetDefault(rid=sandbox.AutoIncrement())

    login = ss.sn_login(snid='fb', snuid=snuid, sntoken=sntoken)
    
    if login.response.ok:
        ss.SetPage(login.response.server)
        ss.SetDefault(uid=login.response.uid, key=login.response.key)

        auth = ss.auth()
        if auth.response.db.fraction == 'N':
            ss.set_nickname(nickname=str(snuid))
            auth = ss.set_fraction(create_heroes=-1, fraction='B')  
        try:
            host = auth.response.chat.host
            chat = sandbox.Caller(url, ver='0.0.0')
            chat.SetPage(host)
            chat.SetDefault(key=auth.response.chat.key, auid=login.response.auid)
        except AttributeError:
            pass
        PingChat(chat)

    else:
        ss = None
    return ss, chat, login

def group_chat(args):
    ss0, chat0, login0 = LoginFB(args.login, '100000204558976', 'AAAB9M8ptmXMBANJZCCfJ0SvDx6Ph1LGtHZAIZAJRBdp5PHBZCWyZBHjyZBHkisZCLz2cmrQXBnyjgZBZBJZAPLkMFx3WUz11ilGwvZBUJASlnfsNgZDZD')
    ss1, chat1, login1 = LoginFB(args.login, '100003376225119', 'AAAB9M8ptmXMBAN9UfBWFaRpHhMcG78gv4WXZA4LJUv8hjRmkeIFYoq2OP3YVrIabf2Lr8ZCitdZBEaOC8USSeS6mOYcN5eprS4ZAjPYDEAZDZD')

    if ss0 and ss1:
        ss0.party_invite(invite_auid=login1.response.auid)
        for i in range(10):
            ss0.keepalive()
            keepalive = ss1.keepalive()
            pending_events = keepalive.response.get('pending_events', [])
            for event in pending_events:
                if 'party' in event:
                    cmd = event.party.get('cmd', None)
                    if cmd != None and cmd == 'invite':
                        ss1.party_accept(master_auid=event.party.master_auid, party_id = event.party.party_id)
            PingChat(chat0)
            PingChat(chat1)

    if ss0:
        ss0.logout()
    if ss1:
        ss1.logout()

def xmute(args, mute):
    snuid = '100000204558976'

    sys.path.append('../../thrift_pw/account_management/gen-py/AccountManagementAPI')
    import AccountManagement    
    tm = ThriftCaller('http://IVANOV-MAC:8706/thrift?service=account_management', AccountManagement)

    acc = tm.GetAccountBySNUid("fb", snuid)
    if acc.result == 0:
        if not mute:
            tm.UnmuteUser(acc.accountInfo.login, acc.accountInfo.auid, 'Admin')
        else:
            tm.MuteUser(acc.accountInfo.login, acc.accountInfo.auid, 1, 'because', 'Admin')    
    acc = tm.GetAccountBySNUid("fb", snuid)

def mute(args):
    xmute(args, True)

def unmute(args):
    xmute(args, False)

def login_xmute(args, mute):
    snuid = '100000204558976'
    ss1, chat1, login1 = LoginFB(args.login, snuid, 'AAAB9M8ptmXMBANJZCCfJ0SvDx6Ph1LGtHZAIZAJRBdp5PHBZCWyZBHjyZBHkisZCLz2cmrQXBnyjgZBZBJZAPLkMFx3WUz11ilGwvZBUJASlnfsNgZDZD')

    if ss1:
        sys.path.append('../../thrift_pw/account_management/gen-py/AccountManagementAPI')
        import AccountManagement    
        tm = ThriftCaller('http://IVANOV-MAC:8706/thrift?service=account_management', AccountManagement)

        acc = tm.GetAccountBySNUid("fb", snuid)
        if acc.result == 0:
            if not mute:
                tm.UnmuteUser(acc.accountInfo.login, acc.accountInfo.auid, 'Admin')
            else:
                tm.MuteUser(acc.accountInfo.login, acc.accountInfo.auid, 1, 'because', 'Admin')    
        acc = tm.GetAccountBySNUid("fb", snuid)

        if chat1:   
            for i in range(5):
                PingChat(chat1)
                time.sleep(1)

        ss1.logout()

def login_mute(args):
    login_xmute(args, True)

def login_unmute(args):
    login_xmute(args, False)
    

import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--login', default='http://pw.nivalnetwork.com:88', help='Login address')
parser.add_argument('--logfile', default='', help='Log file name')
parser.add_argument('--scenario', choices=[ 
        'group_chat', 'login_mute', 'mute', 'login_unmute', 'unmute'
    ], required=True, help='Scenario')
args = parser.parse_args()

def loggingSeverity( name ):
    return getattr( logging, name.upper(), 0) if name else 0

if args.logfile:
    logfile = args.logfile
else:
    logfile = None

logging.basicConfig( filename=logfile, filemode="w", level=loggingSeverity( 'debug' ), format='[%(asctime)s %(levelname)8s] %(message)s' )

eval(args.scenario+'(args)')    
