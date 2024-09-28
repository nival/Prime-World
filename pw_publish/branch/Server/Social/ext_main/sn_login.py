# -*- coding: utf-8 -*-
#
# Social Aggregator Login
# (C) Dan Vorobiev 2011, Nival Network

import sys, os, time, logging, base64

# чтобы питон правильно понимал относительные пути модулей:
def _addPath(strPath):
    importPath = os.path.abspath(strPath)
    if not (importPath in sys.path):
        sys.path.append(importPath)

##import collections
## print type(_addPath), isinstance(_addPath, collections.Callable)

_addPath('..')
from handlers import * # JsonHandler, globals: peers, users..
from subaction import SubAction, action_timing, separate_timing
from instr import * 

import iaggregator
import imemcache

from login import BaseCheckVersionAction, LoginAction
from geo_cfg import DEFAULT_GEO_LOCATION
from pwc_actions import PWConnectLoginAction


import time
import json

import EC
import CC


def onDummyCallback( response ):
    info("onDummyCallback response: %s" % response)

##-------------------------------------------------------------------------------------
##-------------------------------------------------------------------------------------


class SocAggLoginAction( BaseCheckVersionAction ):
    action = "sn_login"
    
    """ Cлужебный handler, поддерживает 'action=sn_login'. """
    @separate_timing
    @action_timing  
    def onStart(self):
        self.sn_id = self.getParam("snid")
        self.sn_login = self.getParam("snuid")
        self.sn_token = self.getParam("sntoken")
        self.original_snid = self.sn_id
        self.original_snuid = self.sn_login
        self.nick = ''
        self.fame = 0
        self.sn_nick = self.sn_login
        self.hostid = self.getParam("hostid", '')
        self.muid = self.getParam('muid', '')
        self.ruid = self.getParam('ruid', '')
        self.rid = self.getIntParam('rid', 0)
        self.photoUrl = ''
        self.registration_date = 0
        self.sn_count = 0
        self.sn_count_prev = 0
        self.secret = ''
        
        self.client_ver = self.getParam("ver", self._DEFAULT_VERSION)
        self.testkey = self.getIntParam("testkey")
        self.testkeypass = self.getIntParam("testkeypass")
        self.key = self.getParam("key", "") # позволяем подхватить прошлую сессию, если она еще активна
        self._dont_log = options._dont_log
        self.rd = self.getParam("rd")
        self.user = None
        _user = self.getParam("user")
        if _user:
            self.user = ClassDict( json.loads(base64.urlsafe_b64decode(_user)) )
            self.user.snid = self.sn_id
            self.user.snuid = self.sn_login

        self.registering = False
        self.registered = 0
        self.isPwLogin = False
        
        self.response["ver"] = PWSOC_VERSION
        self.response["_depth"] = DEPTH_WS

        if self.sn_id == 'st':
            self.sn_token = self.RecodeSteamToken(self.sn_token)
        
        self.force_login = getattr(self.request, "force_login", 0)
        
        #~ ## пока что локаль ланчера и локаль клиента могут быть совершенно разными; поэтому пока будем верить локализации клиента.
        #~ self.locale = str(self.getParam("locale", cfg.MATCHMAKER_DEFAULT_LOCALE)).upper() # вполне может быть при отладочном fb login
        self.userlocale = self.getParam("userlocale", cfg.MATCHMAKER_DEFAULT_LOCALE)
        self.locale = str(self.userlocale).upper() # пока будем верить локализации клиента
        
        self.response["userlocale"] = self.userlocale
        self.response["locale"] = self.locale
        
        #TODO:LOFIK:ENCIPHER_TRAFFIC
        #if cfg.ENCIPHER_TRAFFIC:
        #  self.response["encipher"] = 1
        self.response["default_fraction"] = self.I.Config.getConfig( self.userlocale ).DEFAULT_FRACTION
        
        if not self.checkClientVersion():  #-- FAIL: отвечаем юзеру
            self.fin()
            return

        if not (self.sn_login and (not re.search( CC.SOCAGG_LOGIN_CHECK_EX, self.sn_login ))):
            return self.markLoginFailed("bad snuid", EC.AGGREGATOR_LOGIN_FAIL)



        # ок, похоже на логин.
        if not self.checkSnToken(self.sn_id, self.sn_token):
            return self.markLoginFailed("bad sntoken: %r" % self.sn_token, EC.AGGREGATOR_LOGIN_FAIL)

        isLoginRedirected = (str(self.rd) == options.server_name)
        if self.sn_id == 'pw' or isLoginRedirected:
            self.isPwLogin = True
            if not isLoginRedirected: # need to check token
                user = self.I.WS.checkLoginToken(self.sn_login, self.sn_token)
                if user:
                    self.copyUserFields(user)

                    if self.checkRid(self.action):
                        return self.markLoginFailed("bad param rid", EC.BAD_PARAM)

                    if self.checkUserRestriction( user.restriction_ok, user.auid ):
                        return

                    if getattr(user, "pwconnect", 0):
                        self.pwc_snuid = user.pwc_snuid
                        info("pwconnect login %r: pwc_snuid=%s, user.sn_count=%s, user.sn_count_prev=%s", self.login, self.pwc_snuid, user.sn_count, user.sn_count_prev)
                        return self.pwcLogin()
                    else:
                        info("pw login %r: user.sn_count=%s, user.sn_count_prev=%s", self.login, user.sn_count, user.sn_count_prev)
                        return self.subLogin()
                else:
                    return self.markLoginFailed("credentials failed, user not found (sn_uid=%s sn_token=%s)" % (self.sn_login, self.sn_token), EC.BAD_TOKEN)

            elif self.user:  # redirect sn_login, no need to check token
                self.copyUserFields( self.user )
                if self.checkRid(""):
                    return self.markLoginFailed("bad param rid", EC.BAD_PARAM)

                if self.nick == CC.NICK_EMPTY:
                    self.nick = ""
                if self.checkUserRestriction( self.restriction_ok, self.auid ):
                    return
                user = self.user
                user.auid = self.auid
                token = self.I.WS.registerLogin(self.auid, user, self.sn_token, primary=1)
                if token is not None:
                    return self.subLogin()
                else:
                    return self.markLoginFailed("error registering login", EC.AUTH_REGISTER_LOGIN_FAILED)
            else:
                return self.markLoginFailed("user info not found in sub login", EC.AGGREGATOR_LOGIN_FAIL)

        elif self.sn_id == CC.PWCONNECT_LAUNCHER_SNID:
            # 'pwe' = PW Connect
            self.parseGeolocation()  # TODO: remove me when direct auth will be removed
            self.pwc_snuid = self.sn_login
            if self.checkRid():
                return self.markLoginFailed("bad param rid", EC.BAD_PARAM)
            return self.pwcLogin()

        elif self.checkPossibleValue( self.sn_id, CC.AGG_SOCIAL_NETWORK_NAMES, error="bad snid" ):
            ## логинимся через SocialAggregator (sntoken нам дали в открытом виде)
            self.parseGeolocation()  # TODO: remove me when direct auth will be removed
            self.secret = md5(self.sn_token)
            if self.checkRid():
                return self.markLoginFailed("bad param rid", EC.BAD_PARAM)
            self.I.AGG.login( self.sn_login, self.sn_token, self.sn_id, False, 'DummyRefreshToken', callback=self.onAggregatorLogin, referral=self.getReferral())
            return

    def parseGeolocation(self):
        try:
            self.remote_ip = self.request.request.headers.get("X-Real-IP", "") # потенциальный облом при редиректах, где не будет правильных headers
            location, aux_info = self.I.GEO.getLocationInfoByIP( self.remote_ip )
            info( "headers: %s" % str(self.request.request.headers) )
            info( "(snuid %s) remote_ip: %s, location: %s, aux_info: %s" % (self.sn_login, self.remote_ip, location, aux_info) )
            self.geolocation = utf8convert( unicode(location, "latin1") ) 
            self.geo_info = str(aux_info)
        except:
            info( "(snuid %s) can't get location by IP: set default (%s)" % (self.sn_login, DEFAULT_GEO_LOCATION) )
            self.geolocation = DEFAULT_GEO_LOCATION
            self.geo_info = ""
        self.response["geolocation"] = self.geolocation
        self.response["geo_info"] = self.geo_info

    
    #------------------------------------------------------------------------------------
    # helper
    @separate_timing
    def copyUserFields(self, user):
        self.auid = user.auid
        self.sn_id = user.snid
        self.original_snid = user.original_snid
        self.original_snuid = user.original_snuid
        self.sn_login = user.snuid
        self.secret = user.secret
        self.sn_sex = user.sex
        self.sn_count = user.sn_count
        self.sn_count_prev = user.sn_count_prev
        self.photoUrl = user.photo or ""
        self.nick = utf8convert( user.nick )
        self.sn_nick = utf8convert( user.sn_nick )
        self.registered = user.registered
        self.registration_date = user.registration_date
        self.restriction_ok = user.restriction_ok
        self.muid = user.muid
        self.ruid = user.ruid
        self.locale = str(user.locale)
        self.agg_info = {}
        self.login = "%s#%s" % (str(user.snid), str(user.snuid))
        self.geolocation = user.geolocation
        self.remote_ip = user.remote_ip 
        self.geo_info = user.geo_info 

        self.response["geolocation"] = self.geolocation
        self.response["geo_info"] = self.geo_info

    #------------------------------------------------------------------------------------
    def getReferral(self):
        return '%s/%s' % (self.locale, self.geolocation)
    
    #------------------------------------------------------------------------------------
    # Social Aggregator ответил на авторизацию
    @separate_timing
    @action_timing  
    def onAggregatorLogin(self, reply): # reply теперь приходит сразу распарсенный до dict-содержимого
        try:
            if reply:
                info( "SocAggLoginAction.onAggregatorLogin: %s" % str(reply) )
                reason = reply.get("message", '')
                ecode = reply.get("error", 0)
                if ecode > 0 or reason:
                    if ecode != 8: # soc agr user not found  
                        return self.markLoginFailed("aggregator login fail (code=%d reason=%r)" % (ecode, reason), EC.AGGREGATOR_LOGIN_FAIL)
                    elif not self.registering:
                        self.registering = True
                        return self.I.AGG.register( self.sn_login, self.sn_token, self.sn_id, 'DummyRefreshToken', callback=self.onAggregatorLogin, referral=self.getReferral() )
                    else:
                        return self.markLoginFailed("aggregator registration fail (code=%d reason=%r)" % (ecode, reason), EC.AGGREGATOR_LOGIN_FAIL)
                else:
                    self.auid = reply.get("auid", None)
                    if self.auid != None:
                        if self.registering: 
                            # прошла успешная регистрация в аггрегаторе
                            self.registered = 1
                            self.I.AGG.setProperty( self.auid, 'reg', 1 ) # и отмечаем, что событие регистрации отправлено
                            self.I.STATS.addSocialRegister( str(self.hostid), str(self.auid), str(self.sn_id), str(self.sn_login), str(self.muid), str(self.ruid) )
                            self.response["registered"] = 1
                            
                        # социальный аггрегатор нас пустил, теперь вопрос только в регистрации внутри нашей database и логине
                        # для большинства соц.сетей логин имеет вид 'snid#sn_uid'
                        self.login = "%s#%s" % (self.sn_id, self.sn_login.lower())
                    else:
                        return self.markLoginFailed("bad auid (code=%d reason=%r)" % (ecode, reason), EC.AGGREGATOR_LOGIN_FAIL)
                    
                    # заодно давайте выкачаем из соц.сети user info
                    return self.I.AGG.getInfo( self.auid, "", include_secure_data=1, callback=self.onAggregatorGetInfo ) # self.sn_id пустой, пусть вернет инфу из всех сетей
        except:
            message = catch()
            agg_error = reply.get("error")
            if agg_error:
                self.response["agg_error"] = agg_error
            return self.markLoginFailed(message, EC.AGGREGATOR_LOGIN_FAIL)
        
        self.response["error"] = "aggregator login fail"
        self.response["ec"] = EC.AGGREGATOR_LOGIN_FAIL
        self.fin()
        
    #------------------------------------------------------------------------------------
    # Аггрегатор ответил на getInfo (можем вытащить пол игрока, никнейм, фото и проч.)
    @separate_timing
    @action_timing  
    def onAggregatorGetInfo(self, reply): # reply теперь приходит сразу распарсенный до dict-содержимого
        try:
            info( "onAggregatorGetInfo: response %s" % str(reply) )
            
            agg_info = reply.get("get_info")
            agg_properties = agg_info.get("props") or {}
            # self.response["get_info"] = agg_info
            
            # отдельно вытащим sex (нужен для матчмейкинга)
            self.sn_sex = toint( agg_info[self.sn_id]["gender"] )
            self.response["sex"] = self.sn_sex

            self.photoUrl = agg_info[self.sn_id]["photo"] or ""
            self.response["photoUrl"] = self.photoUrl
            
            self.nick = utf8convert( agg_properties.get("nick", CC.NICK_EMPTY) )
            self.fame = toint( agg_properties.get("fame", "0") )
            if self.nick == CC.NICK_EMPTY:
                self.nick = ""
            self.sn_nick = utf8convert( agg_info[self.sn_id].pop("name", "") or self.sn_nick )
            self.response["nick"] = self.nick or self.sn_nick
            self.registration_date = toint(agg_info["dt_register"])
            self.agg_info = agg_info[self.sn_id]
            self.fsn = agg_properties.get("fsn", None)
            self.registered = agg_properties.get("reg", 0) or self.registered
            
            # посчитаем количество зарегистрированных соц.сетей
            self.checkSocialNetworkCount( agg_info )
            
            # соберем список sn-реквизитов для проверки CBT user restrictions
            self.sn_pairs = [utf8convert( "ni:%s" % self.auid)]
            for name in CC.LOGIN_SOCIAL_NETWORK_NAMES:
                items = agg_info.get(name)
                if items:
                    snuid = items.get('snuid', None)
                    if snuid:
                        # в случае, если работаем со списком допущенных юзеров (напр. Test Realm), нужно будет проверить, нет ли данных реквизитов в списке допуска 
                        sn_pair = utf8convert( "%s:%s" % (name, snuid) )
                        self.sn_pairs.append( sn_pair )
                    else:
                        return self.markLoginFailed('no snuid found (sn=%s)' % name, EC.AGGREGATOR_LOGIN_FAIL)
                            
            return self.checkSqlUserRestrictions()            
            
        except:
            message = catch()
            self.sn_sex = 0
            self.response["warning"] = "social aggregator get_info fail: {"+message+'}'

            agg_error = reply.get("error")
            if agg_error:
                self.response["get_info_error"] = agg_error
                
            self.fin()
            
    #------------------------------------------------------------------------------------
    # гнусный копи-паст из WhoAction
    def checkSqlUserRestrictions(self):
        if cfg.RESTRICT_FACEBOOK_USERS:
            ## TEST REALM RESTRICTIONS: pre-registered social network users only!
            self.I.SQL.cbtCheckUserRestrictions( self.sn_pairs, self.onSqlCheckUserRestrictions )
        else:
            return self.continueLogin()
            
    def onSqlCheckUserRestrictions(self, sql_reply):
        try:
            info("onSqlCheckUserRestrictions(sn_login) sql_reply: %s" % sql_reply)
            r = sql_reply["r"]
            if r:
                return self.continueLogin()
        except:
            pass
        # fail:
        self.markLoginFailed( CC.TEXT_NOT_A_REGISTERED_AP_USER, EC.NOT_A_REGISTERED_AP_USER )

    def continueLogin(self):
        if not self.registering and self.fsn:
            return self.subLogin()
        else:
            return self.I.AGG.setProperty(self.auid, 'fsn', self.sn_id, self.onAggregatorSave)
        
    #------------------------------------------------------------------------------------
    @separate_timing
    @action_timing  
    def onAggregatorSave(self, reply): 
        info( "onAggregatorSave: response %s" % str(reply) )
        
        # в любом случае (даже если с установкой fsn не выгорело) продолжаем sublogin
        return self.subLogin()
        
    #------------------------------------------------------------------------------------
    # стартуем sublogin (нормальный "наш" login должен уже лежать в self.login)
    @separate_timing
    def subLogin(self):
        self.allow_login_underscores = 1 # чтобы login не ругался на "#" в имени юзера
        subParams = { "user":[self.login], "auth":["12345"], "key":[self.key], "testkey":[self.testkey],
                      "testkeypass":[self.testkeypass], "ver":[self.client_ver], "geo_info":[self.geo_info],
                      "userlocale": [self.userlocale], "rid":[self.rid]}
        loginAction = LoginAction( subParams, self.onSubLogin, self )
        loginAction.auid = self.auid # чтобы известный нам auid сразу попал на acc={}, создаваемый внутри LoginAction
        return loginAction.onStart()
    
    #------------------------------------------------------------------------------------
    # получили ответ на sublogin ( обычный питоновский response[] )
    @separate_timing
    @action_timing  
    def onSubLogin(self, sublogin_response):
        info( "SocAggLoginAction: sublogin response %s", str(sublogin_response) )
        self.response["sublogin_response"] = sublogin_response
        self.addResponseTiming( sublogin_response )
        if sublogin_response and sublogin_response.get("ok"):
            # юзер успешно залогинен, можно отвечать обычным auth
            self.uid = sublogin_response.get("uid")
            
            # перепиливаем дефолтные (левые, полученные в процессе sublogin) zz-реквизиты на правильные
            self.acc = users[self.uid]
            self.acc.auid = tolong( self.auid )
            self.I.WS.registerAuid( self.acc.auid, self.acc.uid )

            self.acc.sex = self.sn_sex
            self.acc.photoUrl = self.photoUrl or ""
            
            self.acc.nick = self.nick
            self.acc.sn_nick = self.sn_nick
            
            self.acc.snid = self.sn_id
            self.acc.original_snid = self.original_snid
            self.acc.original_snuid = self.original_snuid
            self.acc.snuid = self.sn_login
            self.acc.sninfo = self.agg_info
            self.acc.secret = self.secret

            self.acc.muid = self.muid
            self.acc.ruid = self.ruid
            
            self.acc.registration_date = self.registration_date

            self.acc.geolocation = self.geolocation
            self.acc.client_ver = self.client_ver
            
            self.acc.sn_count = self.sn_count
            self.acc.sn_count_prev = self.sn_count_prev
            self.acc.locale = str(self.locale)
            self.acc.userlocale = str(self.userlocale)
            
            self.acc.remote_ip = self.remote_ip
            
            
            if not self.force_login:
                self.acc.online = 1

            self.I.WS.subscribeAccToPersonServer( self.acc, self.fame )

            self.response["ok"] = 1
            self.response["uid"] = self.uid 
            self.response["key"] = sublogin_response.get("key")
            self.response["registration_date"] = self.registration_date
            self.response["auid"] = toint(self.acc.auid)

            if sublogin_response.get("re"):
                if self.acc.model:
                    self.I.PDM.fixLoadedData( self.acc )
                    # при релогине мы не грузим persistent data, поэтому проверку насчет выдачи бонусных талантов можно делать сразу
                    if not self.acc.locked:
                        try:
                          self.I.WS.checkGiveBonusTalents( self.acc )
                        except:
                          err("Fail checkGiveBonusTalents for auid %r acc %r", self.acc.db.auid, self.acc)
                else:
                    warn( "empty model for auid=%s, no subscribe" % self.acc.auid )
                
            self.I.WS.dumpAccount(self.acc, "sn_login")

            if (not self.acc.guest):
                # зарегистрируем биллинг
                self.I.BILL.initBilling( self.auid )
                
        elif sublogin_response.get("ec"):
            # юзер забанен, и прочие game logic error codes
            self.response["ec"] = sublogin_response.get("ec")
            self.response["error"] = sublogin_response.get("error")
            self.response["error_args"] = sublogin_response.get("error_args", {})
            
        elif sublogin_response.get("error") == "[sql] bad login":
            # Турнирный сервер - только по билетам
            if cfg.TOURNAMENT_SERVER and self.auid not in cfg.TOURNAMENT_SPECTATOR_AUIDS:
                self.response["ec"] = EC.TOURNAMENT_TICKET_NOT_BUY
                self.response["error"] = "Ticket not buyed"
                self.fin()
                return

            # 2) юзер еще не известен нашему кластеру (тогда надо завести нового, с тем самым именем "fb#<fb_uid>", и немедленно логнуть)
            self.response["msg"] = "new user: %s" % self.login

            if not getattr(self, "adding_new_user", 0):
                new_uid = self.I.WS.nextInt64GUID( "sql_uid" )
                pwd_hash = self.sn_token[:32] # SQL ESCAPE?..
                self.adding_new_user = 1
                return self.I.SQL.addNewLogin( new_uid, self.login, pwd_hash, callback=self.onNewLoginAdded )
            else:
                # если пришли сюда повторно, значит повторный subLogin тоже не удался; обламываемся.
                self.response["error"] = "[sql] fail adding new user login"

        elif sublogin_response.get("error") and not (sublogin_response.get("error").startswith("[sql] already logged")
          or sublogin_response.get("error").startswith("already logged")):
            self.response["ec"] = EC.SUBLOGIN_FAIL
            self.response["error"] = "subLogin failed"
                
        else: ## sublogin_response.get("ws", 0) or sublogin_response.get("error", "") == "already logged":
            # 1) юзер уже залоган (на другом рабочем сервере) 
            ws_id = sublogin_response.get("ws", 0)
            ws_name = sublogin_response.get("ws_name", "")
            
            if ws_id and ws_id != options.server_id and self.key:
                peer = self.I.WS.peers.get(ws_id)
                if peer:
                    self.redirect_to = peer["name"]
                    # внутрикластерный редирект 
                    redirect_args = dict(
                        action = "sn_login",
                        snid = self.sn_id,
                        snuid = self.sn_login,
                        sntoken = self.sn_token,
                        ver = self.client_ver,
                        key = self.key,
                    )
                    if self.isPwLogin:
                        redirect_args['rd'] = self.redirect_to # будем передавать имя ("two"), а не server_id 
                        user_args = dict(
                            auid = self.auid,
                            sn_sex = self.sn_sex,
                            photo = self.photoUrl,
                            nick = self.nick or CC.NICK_EMPTY,
                            sn_nick = self.sn_nick,
                            sn_count = self.sn_count,
                            sn_count_prev = self.sn_count_prev,
                            restriction_ok = self.restriction_ok,
                            registration_date = self.registration_date,
                            locale = self.locale,
                            secret = self.secret,
                            registered = self.registered,
                            original_snid = self.original_snid,
                            original_snuid = self.original_snuid,
                            remote_ip = self.remote_ip,
                            geolocation = self.geolocation,
                            geo_info = self.geo_info,
                            )
                        redirect_args['user'] = base64.urlsafe_b64encode(json.dumps(user_args))
                        self.I.WS.deleteLoginToken(self.auid)
                    info( "login_redirect: peer %s, args %s" % (peer, str(redirect_args)) )
                    self.I.WSX.fetch( peer["addr"], redirect_args, self.onRedirectLogin, subrequest="" ) # чтобы без всяких INTERNAL "x" (http://../x?..)
                    
                    return
                else:
                    info('peer not found: ws_id=%s' % ws_id)
            else:
                info('fail redirect: ws_id=%s server_id=%s key=%s' % (ws_id, options.server_id, self.key))
                        
            # fail redirect
            self.response["error"] = "already logged"
            if ws_name != options.server_name:
                self.response["ec"] = EC.ALREADY_LOGGED_ON_DIFF_SERVER
                self.response["ws_name"] = sublogin_response.get("ws_name", 0)
            else:
                self.response["ec"] = EC.ALREADY_LOGGED
            
        self.fin()


    #------------------------------------------------------------------------------------
    # в БД создался новый zzima_login; теперь subLogin должен пройти
    @action_timing  
    def onNewLoginAdded(self, sql_reply):
        if not self.registered:
            self.I.AGG.setProperty( self.auid, 'reg', 1 ) # отмечаем, что событие регистрации отправлено
            self.I.STATS.addSocialRegister( str(self.hostid), str(self.auid), str(self.sn_id), str(self.sn_login), str(self.muid), str(self.ruid) )
        self.subLogin()


    @separate_timing
    @action_timing  
    def onRedirectLogin(self, response_dict):
        info("onRedirectLogin response_dict: %s" % response_dict)
        self.response = response_dict
        if len(response_dict) == 0:
            self.response["error"] = "already logged"
            self.response["ec"] = EC.ALREADY_LOGGED
        self.response["redirect_from"] = options.server_name
        self.response["server"] = self.redirect_to # подменяем имя сервера, реально обработавшего запрос (по умолчанию handler вписывает наше имя, т.к. мы приняли этот запрос по http)
        self.fin()

    @separate_timing
    def checkUserRestriction(self, restriction_ok, auid):
        ## TEST REALM RESTRICTIONS: pre-registered facebook/OK users only!
        if cfg.RESTRICT_FACEBOOK_USERS:
            if not restriction_ok: 
                info( "[restrict] FAILED restriction_ok for auid=%s" % (auid) )
                self.response["error"] = CC.TEXT_NOT_A_REGISTERED_AP_USER
                self.response["ec"] = EC.NOT_A_REGISTERED_AP_USER
                self.fin()
                return True
            else:
                info( "[restrict] passed restriction_ok for auid=%s" % (auid) )
        
        
    #------------------------------------------------------------------------------------
    @separate_timing
    def pwcLogin(self):
        # PW Connect 
        original_params = self.getFlatParams() # копия исходных параметров запроса, для проверки подписи
        info("original params: %s" % original_params) 
        subparams = ClassDict(  snid=[self.sn_id], snuid=[self.pwc_snuid], challenge=[self.sn_token], _params=[original_params] )
        subaction = PWConnectLoginAction( subparams, self.onPwcLogin, I=self.I )
        subaction.request = self.request
        subaction.onStart()
    
    #------------------------------------------------------------------------------------
    @separate_timing
    @action_timing  
    def onPwcLogin(self, pwc_response):
        # финальный ok должен зависеть от результата sublogin, так что в self.response pwc_response.ok попасть не должен
        pwc_ok = pwc_response.pop('ok',0) 
        self.secret = pwc_response.pop('secret', '')
        # заливаем ответ Pwc Login поверх нашего собственного
        self.response.update( pwc_response )
        self.addResponseTiming( pwc_response )
        # ---------------
        if pwc_ok:
            self.auid = self.response.get('auid', 0)
            self.login = utf8convert( "%s#%s" % (self.sn_id, self.sn_login.lower()) )
            self.sn_sex = self.response.get('sex', 0)
            self.agg_info = self.response.get('info', {})
            self.photoUrl = ''
            return self.subLogin()
        # ---------------
        self.fin()
        
