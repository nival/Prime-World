# -*- coding: utf-8 -*-
import sys, urllib, hashlib

import logging
import response

from fsm import PASSED_STATUS_OK, PASSED_STATUS_FAIL
import response

sys.path.append('../../')
from base.helpers import *

class Matchmaking:
    
    def __init__(self, mmid):
        self.mmid = mmid
        self.is_valid = 0
        self.progress = 0
        self.sessionId = None

    def Ping(self, tokens):
        self.is_valid = tokens.get('is_valid', 0)
        self.progress = tokens.get('progress', 0)
        self.sessionId = tokens.get('session_id', None)
        self.gameId = tokens.get('game_id', None)
        self.gameType = tokens.get('game_type', None)
        self.heroId = tokens.get('hero_id', None)

class UserContext:

    def __init__(self, channel, tag="", testkeypass=0, version='0.0.0', sex=1):
        self.channel = channel
        self.worker = None
        self.uid = None
        self.loaded = 0                  
        self.mm = None
        self.key = None
        self.failMessage = None
        self.passedStatus = 0
        self.expectedFailMessages = {}
        self.tag = tag
        self.who = None
        self.llogin = None
        self.ljoin = None
        self.lmerge = None
        self.auid = 0
        self.testkeypass = testkeypass
        self.version = version
        self.sex = sex
        self.hero_index = 0

    def Pass(self, message="passed"):
        self.passedStatus = PASSED_STATUS_OK
        
    def Fail(self, message):
        if message not in self.expectedFailMessages:
            error( "%s context.Fail: %s" % (self.tag, message) )
            self.passedStatus = PASSED_STATUS_FAIL
            self.failMessage = message
        else:
            # ок, мы ждем этой самой ошибки (возможно, даже проверяем ее наличие в тесте)
            warn( "%s context expectedFail: %s" % (self.tag, message) )
            self.expectedFailMessages[message] = 1 # отметим, что получили такую ошибку
            
    def expectFailMessage(self, message):
        self.expectedFailMessages[message] = 0
        
    def receivedFailMessage(self, message):
        return self.expectedFailMessages.get(message)
                    
    def GetFailMessage(self):
        return self.failMessage

    def GetPassedStatus(self):
        return self.passedStatus

    def send(self, args, callback):
        self.channel.send(None, args, response.Response(callback), self.worker)


    def Who(self, sn_id, sn_uid, sn_token, snrefresh_token):
        args =  {
            'snid': sn_id,
            'snuid' : sn_uid,
            'sntoken' : sn_token,
            'version' : self.version,
            'action' : 'l_who',
            'snrefresh_token' : snrefresh_token,
        }
        self.send(args, self.OnWho)

    def OnWho(self, data):
        self.who = data
        self.worker = data['response']['server']
                
    def LLogin(self, auid, logins):
        args =  {
            'auid': auid,
            'version' : self.version,
            'action' : 'l_login',
        }
        for index, (snid, snuid, sntoken, snrefresh_token) in enumerate(logins):
            args['snid'+str(index)] = snid
            args['snuid'+str(index)] = snuid
            args['sntoken'+str(index)] = sntoken
            args['snrefresh_token'+str(index)] = snrefresh_token
        self.send(args, self.OnLLogin)

    def OnLLogin(self, data):
        self.llogin = data

    def LMerge(self, auid0, token0, auid1, token1):
        args =  {
            'auid0': auid0,
            'auid1': auid1,
            'token0': token0,
            'token1': token1,
            'action' : 'l_merge',
        }
        self.send(args, self.OnLMerge)

    def OnLMerge(self, data):
        self.lmerge = data

    def LJoin(self, auid, snid, snuid, sntoken, snrefresh_token):
        args =  {
            'auid': auid,
            'version' : self.version,
            'action' : 'l_join',
            'snid' : snid,
            'snuid' : snuid,
            'sntoken' : sntoken,
            'snrefresh_token' : snrefresh_token,
        }
        self.send(args, self.OnLJoin)

    def OnLJoin(self, data):
        self.ljoin = data

    def Login(self, user, password_md5, loginType='zzima', comment=None):
        args =  {
            #'pretty' : 1,
            'testkey': 1,
            'key' : '12345',
            'ver' : self.version,
        }
        if loginType == 'zzima':
            args['action'] = 'zz_login'
            args['zz_user'] = user
            args['zz_auth'] = password_md5
        elif loginType == 'guest':
            args['action'] = 'login'
            args['guest'] = 1
        elif loginType == 'guest_relogin':
            # тестовый relogin для guest-аккаунтов (нужно для проверки фичи reconnect)
            args['action'] = 'login'
            args['user'] = user
            args['auth'] = '1' # надо хоть какой-то указывать
            args['key'] = password_md5
            args['_allow_guest_relogin_'] = 1
        elif loginType in ['fb', 'pw', 'ok']:
            args['action'] = 'sn_login'
            args['snid'] = loginType
            args['snuid'] = user
            args['sntoken'] = password_md5
        if comment:
            args['comment'] = urllib.quote(comment)
        self.send(args, self.OnLogin)
        
    def PersistentGuestLogin(self):
        args =  {
            'action':   'pguest_login',
            'testkey':  1,
            'testkeypass': self.testkeypass,
            'version':  self.version,
            'sex':   self.sex,
        }
        guest_uid = getattr(self, 'guest_uid', 0)
        if guest_uid: # есть uid от предыдущего захода как persistent-guest; можно делать relogin
            args['login'] = 'guest:%s' % guest_uid
        self.send(args, self.OnLogin)
        
    def OnLogin(self, data):
        self.uid = data['response']['uid']
        self.auid = data['response'].get('auid', 0)
        self.worker = data['response']['server']
        self.key = data['response']['key']

    def Logout(self):
        args =  {
            'action' : 'logout',
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
        }
        self.send(args, self.OnLogout)

    def OnLogout(self, data):
        self.uid = None
        self.worker = None
        self.loaded = 0                  
        
    def Auth(self):
        args =  {
            'action' : 'auth',
            'uid' : self.uid,
            'key' : self.key,
            #'pretty' : 1, # ни в коем случае не pretty! время заворачивания в json будет в 10-20 раз больше
        }
        self.send(args, self.OnAuth)

    def OnAuth(self, data):
        self.loaded = data['response']['loaded']
        class Container:
            pass
        self.db = Container()
        self.db.fraction = data['response']['db'].get('fraction', None)    
        self.db.auid = data['response']['db'].get('auid', 0)    
        self.mmid = data['response'].get('mmid', 0)
        self.db.save_counter = data['response']['db'].get('save_counter', 0)
        if self.mmid:
            self.mm = Matchmaking(self.mmid)
        self.chat = Container()
        self.chat.host = data['response'].get('chat', {}).get('host', None)
        self.chat.key = data['response'].get('chat', {}).get('key', None)
        self.model = data['response'].get('init')

    def SetFraction(self, fraction):
        args =  {
            'action' : 'set_fraction',
            'fraction' : fraction,
            'uid' : self.uid,
            'key' : self.key,
            'create_heroes' : -1,
            #'pretty' : 1, # ни в коем случае не pretty! время заворачивания в json будет в 10-20 раз больше
        }
        self.send(args, self.OnSetFraction)

    def OnSetFraction(self, data):
        class Container:
            pass
        self.db = Container()
        self.db.fraction = data['response']['db'].get('fraction', None)    
        self.mmid = data['response'].get('mmid', 0)
        if self.mmid:
            self.mm = Matchmaking(self.mmid)
        self.model = data['response'].get('init')
            
    def Keepalive(self):
        args =  {
            'action' : 'keepalive',
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
        }
        self.keepalive_ok = 0
        self.send(args, self.OnKeepalive)
        
    def OnKeepalive(self, data):
        self.keepalive_ok = 1

    def AddMM(self, hero_id, _fraction=None, _gameType = None):
        if _fraction == None:
            fraction = self.db.fraction
        else:
            fraction = _fraction
        if _gameType == None:
            gameType = 'pvp'
        else:
            gameType = _gameType
            
        self.hero_id = hero_id
            
        if not self.hero_id:
            info( "no valid hero specified: searching for hired hero in ModelData.." )
            # если герой не указан (или 0), нужно выбрать по списку первого подходящего (обязательно нанятого, а то ММ не стартует)
            if self.model:
                hk = pathFind(self.model, "ModelData/HeroesKeeper/Keeper")
                if hk:
                    for hero_id, value in hk.iteritems():
                        # info("checking hero_id %s, value %s" % (hero_id, value))
                        hero = value.get("Hero")
                        if hero and hero.get("Hired", False):
                            self.hero_id = hero_id
                            self.hero_crc = hero.get("PersistentId", 0)
                            info( "found hired hero: hero_id=%s, class=%s" % (self.hero_id, hero.get("class_name", "?")) )
                            break
                else:
                    return self.Fail("no HeroesKeeper found")
            else:
                return self.Fail("no ModelData found")
                
        if not hero_id:
            return self.Fail("no valid hero for matchmaking")
            
        args =  {
            'action' : 'mm_add',
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
            'src_hero_id' : self.hero_id,
            'fraction' : fraction,
            'game_type' : gameType,
        }
        self.send(args, self.OnAddMM)

    def OnAddMM(self, data):
        self.mm = Matchmaking(data['response']['mmid'])

    def AcceptMM(self):
        if self.mm:
            args =  {
                'action' : 'mm_accept',
                'uid' : self.uid,
                'key' : self.key,
                'pretty' : 1,
                'mmid' : self.mm.mmid,
            }
            self.send(args, self.OnAcceptMM)

    def OnAcceptMM(self, data):
        self.OnPingMM(data)

    def CancelMM(self):
        if self.mm:
            self.expectFailMessage("no active matchmaking sessions") # вполне может прийти на какой-нибудь отложенный mm_ping
            args =  {
                'action' : 'mm_cancel',
                'uid' : self.uid,
                'key' : self.key,
                'pretty' : 1,
                'mmid' : self.mm.mmid,
            }
            self.send(args, self.OnCancelMM)

    def OnCancelMM(self, data):
        ##print "OnCancelMM", str(data) # там сейчас все сессии cancel-ятся, не одна
        assert data['response']['mmid'] == self.mm.mmid
        assert data['response'].get('mm') is None
        self.mm = None

    def PingMM(self):
        if self.mm:
            args =  {
                'action' : 'mm_ping',
                'uid' : self.uid,
                'key' : self.key,
                'pretty' : 1,
                'mmid' : self.mm.mmid,
            }
            self.send(args, self.OnPingMM)
                                                 
    def OnPingMM(self, data):
        mmid = data['response']['mmid']
        assert mmid == self.mm.mmid, 'mmid should be equal'
        self.mm.Ping( data['response']['mm'] )
        warn("%s mm progress=%s, mmid=%s" % (self.tag, self.mm.progress, self.mm.mmid))

        
    def CheckNoPingMM(self):
        # выполняем обычный mm_ping, но предполагаеми ответ "нет активных mm-сессий"
        self.mm_ping_done = 0
        self.expectFailMessage("no active matchmaking sessions")
        args =  {
            'action' : 'mm_ping',
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
            'mmid' : 0,
        }
        self.send(args, self.OnNoPingMM)
                    
    # на самом деле сюда мы НЕ попадем, только почистится self.expectFailMessage в context.Fail
    def OnNoPingMM(self, data):
        warn("OnNoPingMM: SHOULDN'T COME HERE")
        
    def LeaveMM(self):
        self.mm_leave_ok = 0
        if self.mm:
            args =  {
                'action' : 'mm_leave',
                'uid' : self.uid,
                'key' : self.key,
                'pretty' : 1,
                'mmid' : self.mm.mmid,
            }
            self.send(args, self.OnLeaveMM)

    def OnLeaveMM(self, data):
        self.mm_leave_ok = 1
        
    def ReconnectMM(self):
        self.mm_reconnect_ok = 0
        if self.mm:
            args =  {
                'action' : 'mm_reconnect',
                'uid' : self.uid,
                'key' : self.key,
                'pretty' : 1,
                'mmid' : self.mm.mmid,
            }
            self.send(args, self.OnReconnectMM)

    def OnReconnectMM(self, data):
        self.mm_reconnect_ok = 1

    # тестовая админская команда, для отладки persistent-механизмов
    def IncSave(self):
        self.inc_save_ok = 0
        args =  {
            'action' : 'inc_save',
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
        }
        self.send(args, self.OnIncSaveMM)

    def OnIncSaveMM(self, data):
        self.inc_save_ok = 1
        self.inc_save_counter = data['response']['db']['save_counter'] # после загрузки/auth сравнивать с self.db.save_counter

    def SetGeolocation(self, geolocation):
        args =  {
            'action' : 'set_geolocation',
            'geolocation': geolocation,
            'uid' : self.uid,
            'key' : self.key,
            'pretty' : 1,
        }
        self.send(args, self.OnSetGeolocation)

    def OnSetGeolocation(self, data):
        self.db.geolocation = data['response']['db']['geolocation'] 
        
    def SetHeroIndex(self, hero_index):
        self.hero_index = hero_index

    def SetGuard(self, hero_id, is_guard):
        self.set_guard_ok = 0
        args =  {
            'action' : 'set_guard',
            'uid' : self.uid,
            'key' : self.key,
            'guard': bool(is_guard),
            'hero_id': int(hero_id)
        }
        self.send(args, self.OnSetGuard)
        
    def OnSetGuard(self, data):
        self.set_guard_ok = 1

    def SetLordWins(self, win_count):
        self.lord_wins_ok = 0
        args =  {
            'action' : 'set_wins',
            'uid' : self.uid,
            'key' : self.key,
            'wins': int(win_count)
        }
        self.send(args, self.OnSetLordWins)
        
    def OnSetLordWins(self, data):
        self.lord_wins_ok = 1
